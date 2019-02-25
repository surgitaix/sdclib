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

#include "OSCLib/SDCInstance.h"
#include "OSCLib/Data/SDC/SDCConsumer.h"
#include "OSCLib/Util/DebugOut.h"

#include "OSELib/DPWS/DPWS11Constants.h"
#include "OSELib/DPWS/MDPWSDiscoveryClientAdapter.h"
#include "OSELib/Helper/XercesGrammarPoolProvider.h"
#include "OSELib/SDC/SDCConstants.h"
#include "OSELib/SDC/ServiceManager.h"
#include "OSELib/SOAP/GenericSoapInvoke.h"
#include "OSELib/DPWS/MetadataProvider.h"


using namespace OSELib::SDC;

void HelloReceivedHandler::helloReceived(const std::string & ) {
	WithLogger(Log::BASE).log_error([] { return "Method 'helloReceived' must be overridden!"; });
}

ServiceManager::ServiceManager(SDCLib::SDCInstance_shared_ptr p_SDCInstance)
 : WithLogger(Log::SERVICEMANAGER)
 , m_SDCInstance(p_SDCInstance)
 , _dpwsClient(new DPWS::MDPWSDiscoveryClientAdapter(m_SDCInstance))
 , configuration(m_SDCInstance)
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

SDCLib::Data::SDC::SDCConsumer_unique_ptr ServiceManager::connect(const std::string & xaddr) {
	return connectXAddress({ xaddr }, "Unknown");
}

SDCLib::Data::SDC::SDCConsumer_unique_ptr ServiceManager::discoverEndpointReference(const std::string & epr, SDCLib::Data::SDC::MDPWSTransportLayerConfiguration consumerConfig) {
    // FIXME: MDPWSTransportLayerConfiguration !
    std::cout << "FIXME! ServiceManager::discoverEndpointReference() MDPWSTransportLayerConfiguration passed by value!" << std::endl;
    // Note: Diese Methode sollte eig. nicht mehr nötig sein, da nun alles SDCInstance zentriert ist...
	configuration = consumerConfig;
	return discoverEndpointReference(epr);
}


SDCLib::Data::SDC::SDCConsumer_unique_ptr ServiceManager::discoverEndpointReference(const std::string & epr) {

	struct ResolveMatchCallback : public DPWS::ResolveMatchCallback  {
		explicit ResolveMatchCallback(Poco::Event & matchEvent) :
			_matchEvent(matchEvent) {
		}
		~ResolveMatchCallback() = default;

		void resolveMatch(const DPWS::ResolveMatchType & n) override {
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

     // FIXME: CRASH HERE... MUTEX ISSUE? WAKEUP (UNLOCK) FROM DIFFERENT THREAD NOT ALLOWED? OWNER PROBLEM? BUG IN POCO?
        bool t_result = matchEvent.tryWait(m_SDCInstance->getDiscoveryTime().count());
		if (!t_result) {
             SDCLib::Util::DebugOut(SDCLib::Util::DebugOut::Default, "ServiceManager") <<  "discoverEndpointReference::TIMEOUT." << std::endl;
        }
		log_debug([&] { return "Received ResolveMatch for: " + resolveCb._result->EndpointReference().Address(); });
     }
     catch (...)
     {
         SDCLib::Util::DebugOut(SDCLib::Util::DebugOut::Default, "ServiceManager") <<  "discoverEndpointReference::CATCH..." << std::endl;
     }
    /*try {
        matchEvent.wait(SDCLib::SDCLibrary::getInstance().getDiscoveryTime());
        log_debug([&] { return "Received ResolveMatch for: " + resolveCb._result->EndpointReference().Address(); });
      } catch (const Poco::TimeoutException & e) {
        } */
    _dpwsClient->removeResolveMatchEventHandler(resolveCb);

    std::vector<std::string> xAddress_list;

    if (resolveCb._result && resolveCb._result->XAddrs().present()) {
        for (const auto & xaddr : resolveCb._result->XAddrs().get()) {
            xAddress_list.emplace_back(xaddr);
        }
        return connectXAddress(xAddress_list, resolveCb._result->EndpointReference().Address());
    }

    return nullptr;
}

ServiceManager::AsyncDiscoverResults ServiceManager::async_discoverOSCP() const
{
    auto t_invoke = [](const OSELib::SDC::ServiceManager* p_serviceManager) {
        return p_serviceManager->discoverOSCP();
      };
    return std::async(std::launch::async, t_invoke, this);
}

ServiceManager::DiscoverResults ServiceManager::discoverOSCP() const {

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
	std::vector<std::string> xAddress_list;

	// probeCb._results contains the exact number of unique EPR in the network
	for (const auto & probeResult : probeCb._results) {
		if (!probeResult.XAddrs().present()) {
			log_debug([&] { return "No xAddresses in response for epr: " + probeResult.EndpointReference().Address(); });
			continue;
		}
		
		// one EPR may be connected via multiple network interfaces
		// TODO: Optimize this by using a std::vector for xAddress_list and reserve space for xAddress_list before running this loop!
		for (const auto & xaddr : probeResult.XAddrs().get()) {
			log_notice([&] { return "Trying xAddress: " + xaddr; });
			xAddress_list.emplace_back(xaddr);
		}
        // TODO:    You can optimize this by taking this step into the connectXAddress function!
        results.emplace_back(connectXAddress(xAddress_list, probeResult.EndpointReference().Address()));
		
		// TODO: Clear the list at the beginning of a new loop, so we dont clear it at the last loop (destroyed anyway) -> performance!
		xAddress_list.clear();
	}

	return results;
}

SDCLib::Data::SDC::SDCConsumer_unique_ptr ServiceManager::connectXAddress(const std::vector<std::string>& xaddress_list, const std::string & epr) const {
	DPWS::DeviceDescription deviceDescription;

	bool connectionPossible_flag = 0;
	for (const auto xaddress : xaddress_list) {
		try {
				deviceDescription.addDeviceURI(Poco::URI(xaddress));
				log_debug([&] { return "XAddress reachable: " + xaddress; });
				connectionPossible_flag = 1;
			} catch (...) {
				log_debug([&] { return "XAddress not reachable: " + xaddress; });
			}
	}

	if (connectionPossible_flag) {
		deviceDescription.setEPR(epr);
	} else {
		return nullptr;
	}



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
		// get metadata for services
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
					if (hosted.ServiceId() == QNAME_CONTEXTSERVICE_PORTTYPE) {
						for (const auto & iter : hosted.EndpointReference()) {
							deviceDescription.addContextServiceURI(Poco::URI(iter.Address()));
						}
					} else if (hosted.ServiceId() == QNAME_STATEEVENTREPORTSERVICE_PORTTYPE) {
						for (const auto & iter : hosted.EndpointReference()) {
							deviceDescription.addStateEventReportServiceURI(Poco::URI(iter.Address()));
						}
					} else if (hosted.ServiceId() == QNAME_GETSERVICE_PORTTYPE) {
						for (const auto & iter : hosted.EndpointReference()) {
							deviceDescription.addGetServiceURI(Poco::URI(iter.Address()));
						}
					} else if (hosted.ServiceId() == QNAME_SETSERVICE_PORTTYPE) {
						for (const auto & iter : hosted.EndpointReference()) {
							deviceDescription.addSetServiceURI(Poco::URI(iter.Address()));
						}
					} else if (hosted.ServiceId() == QNAME_WAVEFORMSERVICE_PORTTYPE) {
						for (const auto & iter : hosted.EndpointReference()) {
							deviceDescription.addWaveformServiceURI(Poco::URI(iter.Address()));
						}
					}
					else {
                        log_error([&]() { return std::string("ServiceManager::connectXAddress failed! No match for ServiceId: " + hosted.ServiceId() + "!"); });
                        return nullptr; // FIXME if an unknown ServiceId is passed everything crashes. This has to be taken care of!
                    }
				}
			}
		}

		// get metadata for streaming
		const DPWS::GetMetadataTraits::Request request_metadata;
		using Invoker_metadata = OSELib::SOAP::GenericSoapInvoke<DPWS::GetMetadataTraits>;
		std::unique_ptr<Invoker_metadata> invoker_metadata(new Invoker_metadata(deviceDescription.getWaveformEventReportURI(), grammarPool));

		auto response_metadata(invoker_metadata->invoke(request_metadata));

		if (response_metadata != nullptr) {

			for (const auto & metadata_iter : response_metadata->MetadataSection()) {
				if (metadata_iter.Dialect() != SDC::WS_MEX_DIALECT_STREAM
					|| !metadata_iter.StreamDescriptions().present()
					|| metadata_iter.StreamDescriptions().get().StreamType().empty()
					|| !metadata_iter.StreamDescriptions().get().StreamType().front().StreamTransmission().StreamAddress().present()
					) {
					continue;
				}
				deviceDescription.addStreamMulticastAddressURI(Poco::URI(metadata_iter.StreamDescriptions().get().StreamType().front().StreamTransmission().StreamAddress().get()));
			}
		}

	} catch (...) {
		log_debug([&] { return "Retrieving Device Metadata failed: " + deviceDescription.getDeviceURI().toString(); });
		return nullptr;
	}

	// GetService is the only mandatory service
	if (deviceDescription.getDeviceURI().empty()
		|| deviceDescription.getGetServiceURI().empty()
	) {
		log_error([&] { return "Missing get-service uri! Discovery incomplete for device with uri: " + deviceDescription.getDeviceURI().toString(); });
		return nullptr;
	}

	log_debug([&] { return "Discovery complete for device with uri: " + deviceDescription.getDeviceURI().toString(); });

	SDCLib::Data::SDC::SDCConsumer_unique_ptr result(new SDCLib::Data::SDC::SDCConsumer(m_SDCInstance, deviceDescription, configuration));

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
