/*
 * ServiceManager.cpp
 *
 *  Created on: 11.12.2015, matthias
 *  Modified on: 22.08.2019, baumeister
 *
 */

#include "OSELib/SDC/ServiceManager.h"
#include "OSELib/SDC/SDCConstants.h"
#include "OSELib/DPWS/DeviceDescription.h"
#include "OSELib/DPWS/DPWS11Constants.h"
#include "OSELib/DPWS/MDPWSDiscoveryClientAdapter.h"
#include "OSELib/SOAP/GenericSoapInvoke.h"
#include "OSELib/Helper/XercesGrammarPoolProvider.h"
#include "SDCLib/SDCInstance.h"
#include "SDCLib/Config/SDCConfig.h"
#include "SDCLib/Data/SDC/SDCConsumer.h"

#include "DataModel/ws-addressing.hxx"
#include "DataModel/wsdd-discovery-1.1-schema-os.hxx"

#include <Poco/Event.h>
#include <Poco/URI.h>
#include <Poco/Net/SocketAddress.h>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/SecureStreamSocket.h>


using namespace OSELib;
using namespace OSELib::SDC;

void HelloReceivedHandler::helloReceived(const std::string & ) {
	OSELib::Helper::WithLogger(Log::BASE).log_error([] { return "Method 'helloReceived' must be overridden!"; });
}

ServiceManager::ServiceManager(SDCLib::SDCInstance_shared_ptr p_SDCInstance)
 : OSELib::Helper::WithLogger(Log::SERVICEMANAGER)
 , m_SDCInstance(p_SDCInstance)
 , m_dpwsClient(new DPWS::MDPWSDiscoveryClientAdapter(m_SDCInstance->getNetworkConfig()))
{ }


ServiceManager::~ServiceManager()
{
	std::lock_guard<std::mutex> t_lock(m_mutex);
	if (m_helloCallback) {
		m_dpwsClient->removeHelloEventHandler(*m_helloCallback);
		m_helloCallback.reset();
	}
}

void ServiceManager::setHelloReceivedHandler(HelloReceivedHandler * p_handler)
{
	struct HelloCallback : public DPWS::HelloCallback {
		HelloCallback(HelloReceivedHandler * p_handler) : m_handler(p_handler) {}
		virtual ~HelloCallback() = default;

		virtual void hello(const DPWS::HelloType & n) override {
			m_handler->helloReceived(n.getEndpointReference().getAddress());
		}

		HelloReceivedHandler * m_handler = nullptr;
	};

	std::lock_guard<std::mutex> t_lock(m_mutex);

	if (m_helloCallback) {
		m_dpwsClient->removeHelloEventHandler(*m_helloCallback);
		m_helloCallback.reset();
	}

	m_helloCallback = std::unique_ptr<HelloCallback>(new HelloCallback(p_handler));
	// Add the new Callback
	m_dpwsClient->addHelloEventHandler(*m_helloCallback);
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

	struct ResolveMatchCallback : public DPWS::ResolveMatchCallback
	{
		ResolveMatchCallback(Poco::Event & p_matchEvent)
		: m_matchEvent(p_matchEvent)
		{ }
		virtual ~ResolveMatchCallback() = default;

		virtual void resolveMatch(const DPWS::ResolveMatchType & n) override
		{
			m_result = std::unique_ptr<DPWS::ResolveMatchType>(new DPWS::ResolveMatchType(n));
			m_matchEvent.set();
		}
		Poco::Event & m_matchEvent;
		std::unique_ptr<DPWS::ResolveMatchType> m_result = nullptr;
	};

	Poco::Event t_matchEvent;
	ResolveMatchCallback t_resolveCb(t_matchEvent);

	DPWS::ResolveType resolveFilter((WS::ADDRESSING::EndpointReferenceType(WS::ADDRESSING::AttributedURIType(p_epr))));
	m_dpwsClient->addResolveMatchEventHandler(resolveFilter, t_resolveCb);
	try {
		// FIXME: CRASH HERE... MUTEX ISSUE? WAKEUP (UNLOCK) FROM DIFFERENT THREAD NOT ALLOWED? OWNER PROBLEM?
		bool t_result = t_matchEvent.tryWait(m_SDCInstance->getDiscoveryTime().count());
		if (!t_result) {
			log_debug([] { return "ServiceManager: discoverEndpointReference::TIMEOUT."; });
		}
		if(nullptr != t_resolveCb.m_result) {
			log_debug([&] { return "Received ResolveMatch for: " + t_resolveCb.m_result->getEndpointReference().getAddress(); });
		}
	}
	catch (...)
	{
		// TODO:
		log_debug([] { return "ServiceManager: discoverEndpointReference::CATCH..."; });
	}

	m_dpwsClient->removeResolveMatchEventHandler(t_resolveCb);

	if(nullptr == t_resolveCb.m_result) {
		return nullptr;
	}

	SDCLib::StringVector tl_xAddresses;
    if (t_resolveCb.m_result && t_resolveCb.m_result->getXAddrs().present()) {
		for (const auto & t_xaddr : t_resolveCb.m_result->getXAddrs().get()) {
			tl_xAddresses.emplace_back(t_xaddr);
		}
		auto t_result(connectXAddress(tl_xAddresses, t_resolveCb.m_result->getEndpointReference().getAddress()));
		if (t_result) {
			return t_result;
		}
	}

	return nullptr;
}

std::vector<std::string> ServiceManager::discoverEndpointReferences() {

	struct ProbeMatchCallback : public DPWS::ProbeMatchCallback {
		ProbeMatchCallback() {}
		virtual ~ProbeMatchCallback() = default;

		virtual void probeMatch(const DPWS::ProbeMatchType & n) override {
			_results.emplace_back(n);
		}

		std::vector<DPWS::ProbeMatchType> _results;
	};

	DPWS::TypesType types;
	types.push_back(xml_schema::Qname(SDC::NS_MDPWS, "MedicalDevice"));

	xml_schema::Qname asdf(SDC::NS_MDPWS, "MedicalDevice");

	DPWS::ProbeType probeFilter;
	probeFilter.getTypes().set(types);


	ProbeMatchCallback probeCb;
	m_dpwsClient->addProbeMatchEventHandler(probeFilter, probeCb);
	Poco::Thread::sleep(m_SDCInstance->getDiscoveryTime().count());
	m_dpwsClient->removeProbeMatchEventHandler(probeCb);
	log_debug([&] { return "Probing done. Got responses: " + std::to_string(probeCb._results.size()); });

	std::vector<std::string> results;

	// probeCb._results contains the exact number of unique EPR in the network
	for (const auto & probeResult : probeCb._results) {
		if (!probeResult.getXAddrs().present()) {
			log_debug([&] { return "No xAddresses in response for epr: " + probeResult.getEndpointReference().getAddress(); });
			continue;
		}

		results.push_back(probeResult.getEndpointReference().getAddress());
	}

	//remove duplicates, we could use a set as well, but might be a bit slower, due to checking with each insert
		// see (https://stackoverflow.com/questions/1041620/whats-the-most-efficient-way-to-erase-duplicates-and-sort-a-vector)
	sort(results.begin(), results.end());
	results.erase(unique(results.begin(), results.end()), results.end());

	return results;
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

		virtual void probeMatch(const DPWS::ProbeMatchType & p_type) override {
			ml_results.emplace_back(p_type);
		}

		std::vector<DPWS::ProbeMatchType> ml_results;
	};

	DPWS::TypesType t_types;
	t_types.push_back(xml_schema::Qname(SDC::NS_MDPWS, "MedicalDevice"));

	DPWS::ProbeType t_probeFilter;
	t_probeFilter.getTypes().set(t_types);

	ProbeMatchCallback t_probeCb;
	m_dpwsClient->addProbeMatchEventHandler(t_probeFilter, t_probeCb);
	// BLOCKING THE WHOLE THREAD?...
	Poco::Thread::sleep(m_SDCInstance->getDiscoveryTime().count());
	m_dpwsClient->removeProbeMatchEventHandler(t_probeCb);
	log_debug([&] { return "Probing done. Got responses: " + std::to_string(t_probeCb.ml_results.size()); });

	ServiceManager::DiscoverResults t_results;
	SDCLib::StringVector tl_xAddresses;

	// probeCb._results contains the exact number of unique EPR in the network
	for (const auto & t_probeResult : t_probeCb.ml_results) {
		if (!t_probeResult.getXAddrs().present()) {
			log_debug([&] { return "No xAddresses in response for epr: " + t_probeResult.getEndpointReference().getAddress(); });
			continue;
		}

		// one EPR may be connected via multiple network interfaces
		for (const auto & t_xaddr : t_probeResult.getXAddrs().get()) {
			log_notice([&] { return "Trying xAddress: " + t_xaddr; });
			tl_xAddresses.emplace_back(t_xaddr);
		}
		auto result(connectXAddress(tl_xAddresses, t_probeResult.getEndpointReference().getAddress()));
		if (result) {
			t_results.emplace_back(std::move(result));
		}
		tl_xAddresses.clear();
	}
	return t_results;
}


bool ServiceManager::resolveServiceURIsFromMetadata(const WS::MEX::MetadataSection & p_metadata, DPWS::DeviceDescription & p_deviceDescription)
{
	// TODO: Is there a better way than so many nested for loops?

	bool t_getServiceFound = false;

	for (const auto & t_hosted : p_metadata.getRelationship().get().getHosted())
	{

		// NOTE: GetService is MANDATORY!

		for (auto t_hosted_type : t_hosted.getTypes()) {
			if (t_hosted_type.name() == QNAME_GETSERVICE_PORTTYPE) {
				log_debug([]{return QNAME_GETSERVICE_PORTTYPE + " found";});
				for (const auto & t_iter : t_hosted.getEndpointReference()) {
					p_deviceDescription.addGetServiceURI(Poco::URI(t_iter.getAddress()));
					t_getServiceFound = true;
				}
			}
		}

		for (auto t_hosted_type : t_hosted.getTypes()) {
			if (t_hosted_type.name() == QNAME_CONTEXTSERVICE_PORTTYPE) {
				log_debug([&]{return QNAME_CONTEXTSERVICE_PORTTYPE + " found";});
				for (const auto & t_iter : t_hosted.getEndpointReference()) {
					p_deviceDescription.addContextServiceURI(Poco::URI(t_iter.getAddress()));
				}
			}
		}
		for (auto t_hosted_type : t_hosted.getTypes()) {
			if (t_hosted_type.name() == QNAME_STATEEVENTSERVICE_PORTTYPE) {
				log_debug([&]{return QNAME_STATEEVENTSERVICE_PORTTYPE + " found";});
				for (const auto & t_iter : t_hosted.getEndpointReference()) {
					p_deviceDescription.addStateEventReportServiceURI(Poco::URI(t_iter.getAddress()));
				}
			}
		}
		for (auto t_hosted_type : t_hosted.getTypes()) {
			if (t_hosted_type.name() == QNAME_SETSERVICE_PORTTYPE) {
				log_debug([]{return QNAME_SETSERVICE_PORTTYPE + " found";});
				for (const auto & t_iter : t_hosted.getEndpointReference()) {
					p_deviceDescription.addSetServiceURI(Poco::URI(t_iter.getAddress()));
				}
			}
		}
		for (auto t_hosted_type : t_hosted.getTypes()) {
			if (t_hosted_type.name() == QNAME_WAVEFORMSERVICE_PORTTYPE) {
				log_debug([]{return QNAME_WAVEFORMSERVICE_PORTTYPE + " found";});
				for (const auto & t_iter : t_hosted.getEndpointReference()) {
					p_deviceDescription.addWaveformServiceURI(Poco::URI(t_iter.getAddress()));
				}
			}
		}
	}

	// Mandatory GetService was not found! -> FAIL!
	if(!t_getServiceFound) {
		return false;
	}

	return true;
}


std::unique_ptr<SDCLib::Data::SDC::SDCConsumer> ServiceManager::connectXAddress(const SDCLib::StringVector& pl_xAddresses, const std::string & p_epr)
{
	if(pl_xAddresses.empty())
	{
		return nullptr;
	}
	if(p_epr.empty())
	{
		return nullptr;
	}

	auto SSL_INIT = m_SDCInstance->getSSLConfig()->isInit();
	auto t_deviceDescription = std::make_shared<DPWS::DeviceDescription>(SSL_INIT);

	bool t_connectionPossible_flag = false;
	for (const auto t_xaddress : pl_xAddresses)
	{
		try
		{
			t_deviceDescription->addDeviceURI(Poco::URI(t_xaddress));
			log_debug([&] { return "XAddress reachable: " + t_xaddress; });
			t_connectionPossible_flag = true;
		}
		catch (...)
		{
			log_debug([&] { return "XAddress not reachable: " + t_xaddress; });
		}
	}

	if (t_connectionPossible_flag)
	{
		t_deviceDescription->setEPR(p_epr);
	}
	else
	{
		return nullptr;
	}

	try
	{
		const Poco::URI t_remoteURI(t_deviceDescription->getDeviceURI());
		if(SSL_INIT)
		{
			Poco::Net::SecureStreamSocket t_connection;
			t_connection.connect(Poco::Net::SocketAddress(t_remoteURI.getHost(), t_remoteURI.getPort()), Poco::Timespan(1, 0));
			t_deviceDescription->setLocalIP(t_connection.address().host());
			t_connection.shutdown();
			t_connection.close();
		}
		else
		{
			Poco::Net::StreamSocket t_connection;
			t_connection.connect(Poco::Net::SocketAddress(t_remoteURI.getHost(), t_remoteURI.getPort()), Poco::Timespan(1, 0));
			t_deviceDescription->setLocalIP(t_connection.address().host());
			t_connection.shutdown();
			t_connection.close();
		}
	}
	catch (...)
	{
		log_debug([&] { return "Contacting xAddress failed: " + t_deviceDescription->getDeviceURI().toString(); });
		return nullptr;
	}

	try
	{
		// get metadata for services
		const DPWS::GetTraits::Request t_request;
		using Invoker = OSELib::SOAP::GenericSoapInvoke<DPWS::GetTraits>;
		// todo use real grammar for validation
		Helper::XercesGrammarPoolProvider t_grammarPool;
		std::unique_ptr<Invoker> t_invoker(new Invoker(t_deviceDescription->getDeviceURI(), t_grammarPool));

		auto t_response(t_invoker->invoke(t_request, m_SDCInstance->getSSLConfig()->getClientContext()));

		bool t_metadataFound = false;
		if (t_response != nullptr)
		{
			for (const auto & t_metadata : t_response->getMetadataSection())
			{
				if(t_metadata.getDialect() != OSELib::WS_MEX_DIALECT_REL) {
					continue;
				}
				else {
					t_metadataFound = true;
				}

				if(!t_metadata.getRelationship().present()) {
					continue;
				}
				if(t_metadata.getRelationship()->getHosted().empty()) {
					log_error([&] { return "Metadata Relationship part does not contain any hosted services!"; });
					continue;
				}

				// Try to resolve (at least all mandatory services)
				if(!resolveServiceURIsFromMetadata(t_metadata, *t_deviceDescription)) {
					return nullptr;
				}
			}
		}

		// No metadata -> violating R5020 of DPWS 1.1
		if(!t_metadataFound)
		{
			log_error([&] { return "## No Metadata found. Violating R5020 of DPWS 1.1. !"; }); // Todo: Is that fully correct?
			return nullptr;
		}


		// get metadata for streaming
		const DPWS::GetMetadataTraits::Request t_request_metadata;
		using Invoker_metadata = OSELib::SOAP::GenericSoapInvoke<DPWS::GetMetadataTraits>;
		std::unique_ptr<Invoker_metadata> t_invoker_metadata(new Invoker_metadata(t_deviceDescription->getWaveformEventReportURI(), t_grammarPool));

		auto t_response_metadata(t_invoker_metadata->invoke(t_request_metadata, m_SDCInstance->getSSLConfig()->getClientContext()));

		if (t_response_metadata != nullptr)
		{
			for (const auto & t_metadata_iter : t_response_metadata->getMetadataSection())
			{
				if (t_metadata_iter.getDialect() != SDC::WS_MEX_DIALECT_STREAM
					|| !t_metadata_iter.getStreamDescriptions().present()
					|| t_metadata_iter.getStreamDescriptions()->getStreamType().empty()
					|| !t_metadata_iter.getStreamDescriptions()->getStreamType().front().getStreamTransmission().getStreamAddress().present())
				{
					continue;
				}
				t_deviceDescription->addStreamMulticastAddressURI(Poco::URI(t_metadata_iter.getStreamDescriptions()->getStreamType().front().getStreamTransmission().getStreamAddress().get()));
			}
		}
	}
	catch (...)
	{
		log_debug([&] { return "Retrieving Device Metadata failed: " + t_deviceDescription->getDeviceURI().toString(); });
		return nullptr;
	}

	// GetService is the only mandatory service
	if (t_deviceDescription->getDeviceURI().empty() || t_deviceDescription->getGetServiceURI().empty())
	{
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
	SDCLib::Data::SDC::SDCConsumer_unique_ptr t_consumer(new SDCLib::Data::SDC::SDCConsumer(t_SDCInstance, t_deviceDescription));

	if (!t_consumer->isConnected()) {
		t_consumer->disconnect();
		return nullptr;
	}

	if (!t_consumer->requestMdib()) {
		t_consumer->disconnect();
		return nullptr;
	}
	return t_consumer;
}
