/*
 * ServiceManager.cpp
 *
 *  Created on: 11.12.2015, matthias
 *  Modified on: 05.08.2019, baumeister
 *
 */

#include "OSELib/SDC/ServiceManager.h"

#include "OSELib/DPWS/DPWS11Constants.h"
#include "OSELib/DPWS/MDPWSDiscoveryClientAdapter.h"
#include "OSELib/Helper/XercesGrammarPoolProvider.h"
#include "OSELib/SDC/SDCConstants.h"
#include "OSELib/SOAP/GenericSoapInvoke.h"

#include "SDCLib/SDCInstance.h"
#include "SDCLib/Config/SDCConfig.h"
#include "SDCLib/Data/SDC/SDCConsumer.h"

#include <Poco/Event.h>
#include <Poco/URI.h>
#include <Poco/Net/SocketAddress.h>
#include <Poco/Net/StreamSocket.h>

#include "ws-addressing.hxx"
#include "wsdd-discovery-1.1-schema-os.hxx"



using namespace OSELib;
using namespace OSELib::SDC;

void HelloReceivedHandler::helloReceived(const std::string & ) {
	WithLogger(Log::BASE).log_error([] { return "Method 'helloReceived' must be overridden!"; });
}

ServiceManager::ServiceManager(SDCLib::SDCInstance_shared_ptr p_SDCInstance)
 : WithLogger(Log::SERVICEMANAGER)
 , m_SDCInstance(p_SDCInstance)
 , _dpwsClient(new DPWS::MDPWSDiscoveryClientAdapter(m_SDCInstance->getNetworkConfig()))
{

}


ServiceManager::~ServiceManager() {
	std::lock_guard<std::mutex> t_lock(m_mutex);
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

	std::lock_guard<std::mutex> t_lock(m_mutex);

	if (_helloCallback) {
		_dpwsClient->removeHelloEventHandler(*_helloCallback);
		_helloCallback.reset();
	}

	_helloCallback = std::unique_ptr<HelloCallback>(new HelloCallback(handler));
}

std::unique_ptr<SDCLib::Data::SDC::SDCConsumer> ServiceManager::connect(const std::string & p_xaddr)
{
	SDCLib::StringVector tl_xAddresses;
	tl_xAddresses.emplace_back(p_xaddr);
	return connectXAddress(tl_xAddresses, "Unknown");
}

std::unique_ptr<SDCLib::Data::SDC::SDCConsumer> ServiceManager::discoverEndpointReference(const std::string & p_epr)
{
	assert(!p_epr.empty());
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

	DPWS::ResolveType resolveFilter((WS::ADDRESSING::EndpointReferenceType(WS::ADDRESSING::AttributedURIType(p_epr))));
	_dpwsClient->addResolveMatchEventHandler(resolveFilter, resolveCb);
	try {

     // FIXME: CRASH HERE... MUTEX ISSUE? WAKEUP (UNLOCK) FROM DIFFERENT THREAD NOT ALLOWED? OWNER PROBLEM? BUG IN POCO?
        bool t_result = matchEvent.tryWait(m_SDCInstance->getDiscoveryTime().count());
		if (!t_result) {
            log_debug([] { return "ServiceManager: discoverEndpointReference::TIMEOUT."; });
        }
		log_debug([&] { return "Received ResolveMatch for: " + resolveCb._result->EndpointReference().Address(); });
     }
     catch (...)
     {
         log_debug([] { return "ServiceManager: discoverEndpointReference::CATCH..."; });
     }
    /*try {
        matchEvent.wait(SDCLib::SDCLibrary::getInstance().getDiscoveryTime());
        log_debug([&] { return "Received ResolveMatch for: " + resolveCb._result->EndpointReference().Address(); });
      } catch (const Poco::TimeoutException & e) {
        } */
	_dpwsClient->removeResolveMatchEventHandler(resolveCb);

	SDCLib::StringVector tl_xAddresses;

	if (resolveCb._result && resolveCb._result->XAddrs().present()) {
		for (const auto & t_xaddr : resolveCb._result->XAddrs().get()) {
			tl_xAddresses.emplace_back(t_xaddr);
		}
		auto t_result(connectXAddress(tl_xAddresses, resolveCb._result->EndpointReference().Address()));
		if (t_result) {
			return t_result;
		}
	}

	return nullptr;
}

ServiceManager::AsyncDiscoverResults ServiceManager::async_discover()
{
    auto t_invoke = [](OSELib::SDC::ServiceManager* p_serviceManager) {
        return p_serviceManager->discover();
    };
    return std::async(std::launch::async, t_invoke, this);
}

ServiceManager::DiscoverResults ServiceManager::discover()
{

    // Note: Replaces discoverOSCP
	struct ProbeMatchCallback : public DPWS::ProbeMatchCallback  {
		ProbeMatchCallback() {}
		virtual ~ProbeMatchCallback() = default;

		virtual void probeMatch(const DPWS::ProbeMatchType & n) override {
			_results.emplace_back(n);
		}

		std::vector<DPWS::ProbeMatchType> _results;
	};

	DPWS::TypesType types;
	types.push_back(xml_schema::Qname(SDC::NS_MDPWS, "MedicalDevice"));

	DPWS::ProbeType probeFilter;
	probeFilter.Types().set(types);


	ProbeMatchCallback probeCb;
	_dpwsClient->addProbeMatchEventHandler(probeFilter, probeCb);
	// BLOCKING THE WHOLE THREAD?...
	Poco::Thread::sleep(m_SDCInstance->getDiscoveryTime().count());
	_dpwsClient->removeProbeMatchEventHandler(probeCb);
	log_debug([&] { return "Probing done. Got responses: " + std::to_string(probeCb._results.size()); });

	ServiceManager::DiscoverResults results;
	SDCLib::StringVector tl_xAddresses;

	// probeCb._results contains the exact number of unique EPR in the network
	for (const auto & probeResult : probeCb._results) {
		if (!probeResult.XAddrs().present()) {
			log_debug([&] { return "No xAddresses in response for epr: " + probeResult.EndpointReference().Address(); });
			continue;
		}

		// one EPR may be connected via multiple network interfaces
		for (const auto & t_xaddr : probeResult.XAddrs().get()) {
			log_notice([&] { return "Trying xAddress: " + t_xaddr; });
			tl_xAddresses.emplace_back(t_xaddr);
		}
		auto result(connectXAddress(tl_xAddresses, probeResult.EndpointReference().Address()));
		if (result) {
			results.emplace_back(std::move(result));
		}
		tl_xAddresses.clear();
	}
	return results;
}


void ServiceManager::resolveServiceURIsFromMetadata(const WS::MEX::MetadataSection & metadata,	DPWS::DeviceDescription & deviceDescription) {
	for (const auto & hosted : metadata.Relationship().get().Hosted()) {
		for (auto hosted_type : hosted.Types()) {
			if (hosted_type.name() == QNAME_CONTEXTSERVICE_PORTTYPE) {
				log_debug([&]{return "ContextService found";});
				for (const auto & iter : hosted.EndpointReference()) {
					deviceDescription.addContextServiceURI(Poco::URI(iter.Address()));
				}
			}
		}
		for (auto hosted_type : hosted.Types()) {
			if (hosted_type.name() == QNAME_STATEEVENTREPORTSERVICE_PORTTYPE) {
				log_debug([&]{return "StateEventReportService found";});
				for (const auto & iter : hosted.EndpointReference()) {
					deviceDescription.addStateEventReportServiceURI(Poco::URI(iter.Address()));
				}
			}
		}
		for (auto hosted_type : hosted.Types()) {
			if (hosted_type.name() == QNAME_GETSERVICE_PORTTYPE) {
				log_debug([&]{return "GetService found";});
				for (const auto & iter : hosted.EndpointReference()) {
					deviceDescription.addGetServiceURI(Poco::URI(iter.Address()));
				}
			}
		}
		for (auto hosted_type : hosted.Types()) {
			if (hosted_type.name() == QNAME_SETSERVICE_PORTTYPE) {
				log_debug([&]{return "SetService found";});
				for (const auto & iter : hosted.EndpointReference()) {
					deviceDescription.addSetServiceURI(Poco::URI(iter.Address()));
				}
			}
		}
		for (auto hosted_type : hosted.Types()) {
			if (hosted_type.name() == QNAME_WAVEFORMSERVICE_PORTTYPE) {
				log_debug([&]{return "WaveformService found";});
				for (const auto & iter : hosted.EndpointReference()) {
					deviceDescription.addWaveformServiceURI(Poco::URI(iter.Address()));
				}
			}
		}
	}

}


std::unique_ptr<SDCLib::Data::SDC::SDCConsumer> ServiceManager::connectXAddress(const SDCLib::StringVector& pl_xAddresses, const std::string & p_epr)
{
	if(pl_xAddresses.empty()) {
		return nullptr;
	}
	if(p_epr.empty()) {
		return nullptr;
	}

	auto t_deviceDescription = std::make_shared<DPWS::DeviceDescription>();

	bool t_connectionPossible_flag = false;
	for (const auto xaddress : pl_xAddresses) {
		try
		{
			t_deviceDescription->addDeviceURI(Poco::URI(xaddress));
			log_debug([&] { return "XAddress reachable: " + xaddress; });
			t_connectionPossible_flag = true;
		} catch (...) {
			log_debug([&] { return "XAddress not reachable: " + xaddress; });
		}
	}

	if (t_connectionPossible_flag) {
		t_deviceDescription->setEPR(p_epr);
	} else {
		return nullptr;
	}



	try {
		const Poco::URI remoteURI(t_deviceDescription->getDeviceURI());
		Poco::Net::StreamSocket connection;
		connection.connect(Poco::Net::SocketAddress(remoteURI.getHost(), remoteURI.getPort()), Poco::Timespan(1, 0));
		t_deviceDescription->setLocalIP(connection.address().host());
	} catch (...) {
		log_debug([&] { return "Contacting xAddress failed: " + t_deviceDescription->getDeviceURI().toString(); });
		return nullptr;
	}

	try {
		// get metadata for services
		const DPWS::GetTraits::Request request;
		using Invoker = OSELib::SOAP::GenericSoapInvoke<DPWS::GetTraits>;
		// todo use real grammar for validation
		Helper::XercesGrammarPoolProvider grammarPool;
		std::unique_ptr<Invoker> invoker(new Invoker(t_deviceDescription->getDeviceURI(), grammarPool));

		auto response(invoker->invoke(request, m_SDCInstance->getSSLConfig()->getClientContext()));

		if (response != nullptr) {
			for (const auto & metadata : response->MetadataSection()) {
				if (metadata.Dialect() != OSELib::WS_MEX_DIALECT_REL
					|| !metadata.Relationship().present()
					|| metadata.Relationship().get().Hosted().empty()
					) {
					continue;
				}

				// Resolve
				resolveServiceURIsFromMetadata(metadata, *t_deviceDescription);
			}
		}

		// get metadata for streaming
		const DPWS::GetMetadataTraits::Request request_metadata;
		using Invoker_metadata = OSELib::SOAP::GenericSoapInvoke<DPWS::GetMetadataTraits>;
		std::unique_ptr<Invoker_metadata> invoker_metadata(new Invoker_metadata(t_deviceDescription->getWaveformEventReportURI(), grammarPool));

		auto response_metadata(invoker_metadata->invoke(request_metadata, m_SDCInstance->getSSLConfig()->getClientContext()));

		if (response_metadata != nullptr) {

			for (const auto & metadata_iter : response_metadata->MetadataSection()) {
				if (metadata_iter.Dialect() != SDC::WS_MEX_DIALECT_STREAM
					|| !metadata_iter.StreamDescriptions().present()
					|| metadata_iter.StreamDescriptions().get().StreamType().empty()
					|| !metadata_iter.StreamDescriptions().get().StreamType().front().StreamTransmission().StreamAddress().present()
					) {
					continue;
				}
				t_deviceDescription->addStreamMulticastAddressURI(Poco::URI(metadata_iter.StreamDescriptions().get().StreamType().front().StreamTransmission().StreamAddress().get()));
			}
		}

	} catch (...) {
		log_debug([&] { return "Retrieving Device Metadata failed: " + t_deviceDescription->getDeviceURI().toString(); });
		return nullptr;
	}

	// GetService is the only mandatory service
	if (t_deviceDescription->getDeviceURI().empty() || t_deviceDescription->getGetServiceURI().empty()) {
		log_error([&] { return "Missing get-service uri! Discovery incomplete for device with uri: " + t_deviceDescription->getDeviceURI().toString(); });
		return nullptr;
	}

	log_debug([&] { return "Discovery complete for device with uri: " + t_deviceDescription->getDeviceURI().toString(); });

    // Create new SDCInstance with a NEW SDCConfiguration !
    auto t_config = SDCLib::Config::SDCConfig::randomMDPWSConfig(m_SDCInstance->getSDCConfig());
    if(!t_config) {
        return nullptr;
    }
    auto t_SDCInstance = std::make_shared<SDCLib::SDCInstance>(t_config);
	std::unique_ptr<SDCLib::Data::SDC::SDCConsumer> result(new SDCLib::Data::SDC::SDCConsumer(t_SDCInstance, t_deviceDescription));

	if (!result->isConnected()) {
		result->disconnect();
		return nullptr;
	}

	if (!result->requestMdib()) {
		result->disconnect();
		return nullptr;
	}
	return result;
}
