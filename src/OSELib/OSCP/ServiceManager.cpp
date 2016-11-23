/*
 * ServiceManager.cpp
 *
 *  Created on: 11.12.2015
 *      Author: matthias
 */

#include "Poco/Event.h"
#include "Poco/URI.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/StreamSocket.h"

#include "ws-addressing.hxx"
#include "wsdd-discovery-1.1-schema-os.hxx"

#include "OSCLib/Data/OSCP/OSCPConsumer.h"

#include "OSELib/DPWS/DPWS11Constants.h"
#include "OSELib/DPWS/DPWSClient.h"
#include "OSELib/Helper/XercesGrammarPoolProvider.h"
#include "OSELib/OSCP/OSCPConstants.h"
#include "OSELib/OSCP/ServiceManager.h"
#include "OSELib/SOAP/GenericSoapInvoke.h"

namespace OSELib {
namespace OSCP {

void HelloReceivedHandler::helloReceived(const std::string & ) {
	WithLogger(Log::BASE).log_error([] { return "Method 'helloReceived' must be overridden!"; });
}

ServiceManager::ServiceManager() :
	WithLogger(Log::SERVICEMANAGER),
	_dpwsClient(new DPWS::DPWSClient())
{
}

ServiceManager::~ServiceManager() {
	Poco::Mutex::ScopedLock lock(_mutex);
	if (_helloCallback) {
		_dpwsClient->removeHelloEventHandler(*_helloCallback);
		_helloCallback.reset();
	}
}

void ServiceManager::setHelloReceivedHandler(HelloReceivedHandler * handler) {
	struct HelloCallback : public DPWS::HelloCallback {
		HelloCallback(HelloReceivedHandler * handler) : _handler(handler) {}
		virtual ~HelloCallback() = default;

		virtual void hello(const DPWS::HelloType & n) override {
			_handler->helloReceived(n.EndpointReference().Address());
		}

		HelloReceivedHandler * _handler;
	};

	Poco::Mutex::ScopedLock lock(_mutex);

	if (_helloCallback) {
		_dpwsClient->removeHelloEventHandler(*_helloCallback);
		_helloCallback.reset();
	}

	_helloCallback = std::unique_ptr<HelloCallback>(new HelloCallback(handler));
}

std::unique_ptr<OSCLib::Data::OSCP::OSCPConsumer> ServiceManager::connect(const std::string & xaddr) {
	return connectXAddress(xaddr, "Unknown");
}

std::unique_ptr<OSCLib::Data::OSCP::OSCPConsumer> ServiceManager::discoverEndpointReference(const std::string & epr) {

	struct ResolveMatchCallback : public DPWS::ResolveMatchCallback  {
		ResolveMatchCallback(Poco::Event & matchEvent) :
			_matchEvent(matchEvent) {
		}
		virtual ~ResolveMatchCallback() = default;

		virtual void resolveMatch(const DPWS::ResolveMatchType & n) override {
			_result = std::unique_ptr<DPWS::ResolveMatchType>(new DPWS::ResolveMatchType(n));
			_matchEvent.set();
		}
		Poco::Event & _matchEvent;
		std::unique_ptr<DPWS::ResolveMatchType> _result;
	};

	Poco::Event matchEvent;
	ResolveMatchCallback resolveCb(matchEvent);

	DPWS::ResolveType resolveFilter((WS::ADDRESSING::EndpointReferenceType(WS::ADDRESSING::AttributedURIType(epr))));
	_dpwsClient->addResolveMatchEventHandler(resolveFilter, resolveCb);
	try {
		matchEvent.wait(5000);
		log_debug([&] { return "Received ResolveMatch for: " + resolveCb._result->EndpointReference().Address(); });
	} catch (const Poco::TimeoutException & e) {
	}
	_dpwsClient->removeResolveMatchEventHandler(resolveCb);

	if (resolveCb._result && resolveCb._result->XAddrs().present()) {
		for (const auto & xaddr : resolveCb._result->XAddrs().get()) {
			auto result(connectXAddress(xaddr, resolveCb._result->EndpointReference().Address()));
			if (result) {
				return std::move(result);
			}
		}
	}

	return nullptr;
}

std::vector<std::unique_ptr<OSCLib::Data::OSCP::OSCPConsumer>> ServiceManager::discoverOSCP() {

	struct ProbeMatchCallback : public DPWS::ProbeMatchCallback  {
		ProbeMatchCallback() {}
		virtual ~ProbeMatchCallback() = default;

		virtual void probeMatch(const DPWS::ProbeMatchType & n) override {
			_results.emplace_back(n);
		}

		std::vector<DPWS::ProbeMatchType> _results;
	};

	DPWS::TypesType types;
	types.push_back(xml_schema::Qname(OSCP::NS_MESSAGE_MODEL, "MedicalDevice"));

	DPWS::ProbeType probeFilter;
	probeFilter.Types().set(types);


	ProbeMatchCallback probeCb;
	_dpwsClient->addProbeMatchEventHandler(probeFilter, probeCb);
	Poco::Thread::sleep(10000);
	_dpwsClient->removeProbeMatchEventHandler(probeCb);
	log_debug([&] { return "Probing done. Got responses: " + std::to_string(probeCb._results.size()); });

	std::vector<std::unique_ptr<OSCLib::Data::OSCP::OSCPConsumer>> results;

	for (const auto & probeResult : probeCb._results) {
		if (!probeResult.XAddrs().present()) {
			log_debug([&] { return "No xAddresses in response for epr: " + probeResult.EndpointReference().Address(); });
			continue;
		}

		for (const auto & xaddr : probeResult.XAddrs().get()) {
//			log_trace([&] { return "Trying xAddress: " + xaddr; });
			log_notice([&] { return "Trying xAddress: " + xaddr; });
			auto result(connectXAddress(xaddr, probeResult.EndpointReference().Address()));
			if (result) {
				log_information([&] { return "Using xAddress: " + xaddr; });
				results.emplace_back(std::move(result));
			}
		}
	}

	return results;
}

std::unique_ptr<OSCLib::Data::OSCP::OSCPConsumer> ServiceManager::connectXAddress(const std::string & xaddress, const std::string & epr) {
	DPWS::DeviceDescription deviceDescription;
	try {
		deviceDescription.setDeviceURI(Poco::URI(xaddress));
	} catch (...) {
		log_error([&] { return "XAddress has invalid format: " + xaddress; });
		return nullptr;
	}
	deviceDescription.setEPR(epr);

	try {
		const Poco::URI remoteURI(deviceDescription.getDeviceURI());
		Poco::Net::StreamSocket connection;
		connection.connect(Poco::Net::SocketAddress(remoteURI.getHost(), remoteURI.getPort()), Poco::Timespan(1, 0));
		deviceDescription.setLocalIP(connection.address().host());
	} catch (...) {
		log_debug([&] { return "Contacting xAddress failed: " + deviceDescription.getDeviceURI().toString(); });
		return nullptr;
	}

	try {
		const DPWS::GetTraits::Request request;
		using Invoker = OSELib::SOAP::GenericSoapInvoke<DPWS::GetTraits>;
		// todo use real grammar for validation
		Helper::XercesGrammarPoolProvider grammarPool;
		std::unique_ptr<Invoker> invoker(new Invoker(deviceDescription.getDeviceURI(), grammarPool));

		auto response(invoker->invoke(request));

		if (response != nullptr) {
			for (const auto & metadata : response->MetadataSection()) {
				if (metadata.Dialect() != OSELib::WS_MEX_DIALECT_REL
					|| !metadata.Relationship().present()
					|| metadata.Relationship().get().Hosted().empty()
					) {
					continue;
				}

				for (const auto & hosted : metadata.Relationship().get().Hosted()) {
					if (hosted.ServiceId() == "PHI") {
						deviceDescription.setContextServiceURI(Poco::URI(hosted.EndpointReference().front().Address()));
					} else if (hosted.ServiceId() == "EventReport") {
						deviceDescription.setEventServiceURI(Poco::URI(hosted.EndpointReference().front().Address()));
					} else if (hosted.ServiceId() == "GetService") {
						deviceDescription.setGetServiceURI(Poco::URI(hosted.EndpointReference().front().Address()));
					} else if (hosted.ServiceId() == "SetService") {
						deviceDescription.setSetServiceURI(Poco::URI(hosted.EndpointReference().front().Address()));
					} else if (hosted.ServiceId() == "WaveformEventReport") {
						deviceDescription.setWaveformEventReportURI(Poco::URI(hosted.EndpointReference().front().Address()));

						// if a streaming service is initialized (by registering a handler) the metadata (i.e. the multicast address should be saved)
						const DPWS::GetMetadataTraits::Request request_metadata;
						using Invoker_metadata = OSELib::SOAP::GenericSoapInvoke<DPWS::GetMetadataTraits>;
						// todo use real grammar for validation
						Helper::XercesGrammarPoolProvider grammarPool;
						std::unique_ptr<Invoker_metadata> invoker_metadata(new Invoker_metadata(deviceDescription.getWaveformEventReportURI(), grammarPool));

						auto response_metadata(invoker_metadata->invoke(request_metadata));

						if (response_metadata != nullptr) {
							for (const auto & metadata_iter : response_metadata->MetadataSection()) {
								if (metadata_iter.Dialect() != OSELib::WS_MEX_DIALECT_STREAM
									|| !metadata_iter.StreamDescriptions().present()
									|| metadata_iter.StreamDescriptions().get().StreamType().empty()
									|| !metadata_iter.StreamDescriptions().get().StreamType().front().StreamTransmission().StreamAddress().present()
									) {
									continue;
								}
								deviceDescription.addStreamMulticastAddressURI(Poco::URI(metadata_iter.StreamDescriptions().get().StreamType().front().StreamTransmission().StreamAddress().get()));
							}
						}
					}
				}
			}
		}
	} catch (...) {
		log_debug([&] { return "Retrieving Device Metadata failed: " + deviceDescription.getDeviceURI().toString(); });
		return nullptr;
	}

	if (deviceDescription.getDeviceURI().empty()
		|| deviceDescription.getContextServiceURI().empty()
		|| deviceDescription.getEventServiceURI().empty()
		|| deviceDescription.getGetServiceURI().empty()
		|| deviceDescription.getSetServiceURI().empty()
		|| deviceDescription.getWaveformEventReportURI().empty()
	) {
		log_error([&] { return "Missing service uri! Discovery incomplete for device with uri: " + deviceDescription.getDeviceURI().toString(); });
		return nullptr;
	}

	log_debug([&] { return "Discovery complete for device with uri: " + deviceDescription.getDeviceURI().toString(); });

	std::unique_ptr<OSCLib::Data::OSCP::OSCPConsumer> result(new OSCLib::Data::OSCP::OSCPConsumer(deviceDescription));
	if (!result->requestMDIB()) {
		result->disconnect();
		return nullptr;
	}
	return std::move(result);
}

} /* namespace OSCP */
} /* namespace OSELib */
