/*
 * SDCProviderAdapter.cpp
 *
 *  Created on: 09.12.2015, matthias
 *  Modified on: 22.08.2019, baumeister
 *
 */


#include "SDCLib/Data/SDC/SDCProviderAdapter.h"
#include "SDCLib/Data/SDC/SDCProvider.h"
#include "SDCLib/SDCInstance.h"

#include "OSELib/fwd.h"
#include "OSELib/DPWS/DeviceServiceController.h"
#include "OSELib/DPWS/IDevice.h"
#include "OSELib/DPWS/MetadataProvider.h"
#include "OSELib/HTTP/FrontController.h"
#include "OSELib/HTTP/FrontControllerAdapter.h"
#include "OSELib/HTTP/HTTPRequestHandlerFactory.h"
#include "OSELib/SDC/GetServiceHandler.h"
#include "OSELib/SDC/IContextService.h"
#include "OSELib/SDC/IEventReport.h"
#include "OSELib/SDC/IGetService.h"
#include "OSELib/SDC/ISetService.h"
#include "OSELib/SDC/IWaveformService.h"
#include "OSELib/SDC/OperationTraits.h"
#include "OSELib/SDC/SDCConstants.h"
#include "OSELib/SDC/SDCServiceController.h"
#include "OSELib/SDC/ReportTraits.h"
#include "OSELib/SDC/SetServiceHandler.h"
#include "OSELib/SDC/IBICEPSService.h"
#include "OSELib/SDC/BICEPSServiceHandler.h"
#include "OSELib/WSDL/WSDLLoader.h"

#include "DataModel/NormalizedMessageModel.hxx"

namespace OSELib {

using GetServiceController = SDC::SDCServiceController<SDC::IGetService, SDC::GetServiceHandler>;
using SetServiceController = SDC::SDCServiceController<SDC::ISetService, SDC::SetServiceHandler>;
using BICEPSServiceController = SDC::SDCServiceController<SDC::IBICEPSService, SDC::BICEPSServiceHandler>;

class DeviceImpl : public DPWS::IDevice
{
private:
	const DPWS::MetadataProvider m_metadata;
	DPWS::MDPWSHostAdapter & m_host;

public:
	DeviceImpl(const DPWS::MetadataProvider & p_metadata, DPWS::MDPWSHostAdapter & p_host)
	: m_metadata(p_metadata)
	, m_host(p_host)
	{ }

	std::string getBaseUri() const override {
		return m_metadata.getDeviceServicePath();
	}

	DPWS::GetTraits::Response getMetadata(const std::string & serverAddress, bool p_SSL) override {
		return m_metadata.createDeviceMetadata(serverAddress, p_SSL);
	}

	std::unique_ptr<DPWS::ProbeTraits::Response> dispatch(const DPWS::ProbeTraits::Request & p_request) override {
		std::unique_ptr<DPWS::ProbeTraits::Response> t_response(new DPWS::ProbeTraits::Response());
		for (const auto & t_item : m_host.dispatch(p_request)) {
			t_response->getProbeMatch().push_back(t_item);
		}
		return t_response;
	}
};

class GetServiceImpl : public SDC::IGetService
{
private:
	SDCLib::Data::SDC::SDCProvider & m_provider;
	const DPWS::MetadataProvider m_metadata;

public:
	GetServiceImpl(SDCLib::Data::SDC::SDCProvider & p_provider, const DPWS::MetadataProvider & p_metadata)
	: m_provider(p_provider)
	, m_metadata(p_metadata)
	{ }

	std::string getBaseUri() const override {
		return m_metadata.getGetServicePath();
	}

	std::string getWSDL() override {
		OSELib::WSDL::WSDLLoader t_wsdlLoader; // FIXME: Always create a new Loader?
		return t_wsdlLoader.getGetServiceWSDL();
	}

	DPWS::GetMetadataTraits::Response getMetadata(const std::string & p_serverAddress, bool p_SSL) override {
		return m_metadata.createGetServiceMetadata(p_serverAddress, p_SSL);
	}

	std::unique_ptr<SDC::GetMDDescriptionTraits::Response> dispatch(const SDC::GetMDDescriptionTraits::Request & p_request) override {
		std::lock_guard<std::mutex> t_lock{m_provider.getMutex()}; // FIXME: Mutex should not be used outside of the class!
		return std::unique_ptr<SDC::GetMDDescriptionTraits::Response>(new SDC::GetMDDescriptionTraits::Response(m_provider.GetMdDescription(p_request)));
	}
	std::unique_ptr<SDC::GetMDIBTraits::Response> dispatch(const SDC::GetMDIBTraits::Request & p_request) override {
		std::lock_guard<std::mutex> t_lock{m_provider.getMutex()}; // FIXME: Mutex should not be used outside of the class!
		return std::unique_ptr<SDC::GetMDIBTraits::Response>(new SDC::GetMDIBTraits::Response(m_provider.GetMdib(p_request)));
	}
	std::unique_ptr<SDC::GetMdStateTraits::Response> dispatch(const SDC::GetMdStateTraits::Request & p_request) override {
		std::lock_guard<std::mutex> t_lock{m_provider.getMutex()}; // FIXME: Mutex should not be used outside of the class!
		return std::unique_ptr<SDC::GetMdStateTraits::Response>(new SDC::GetMdStateTraits::Response(m_provider.GetMdState(p_request)));
	}
};

class SetServiceImpl : public SDC::ISetService
{
private:
	SDCLib::Data::SDC::SDCProvider & m_provider;
	const DPWS::MetadataProvider m_metadata;
	// for managing OperationInvokedReports
	DPWS::SubscriptionManager & m_subscriptionManager;

public:

	SetServiceImpl(SDCLib::Data::SDC::SDCProvider & p_provider, const DPWS::MetadataProvider & p_metadata, DPWS::SubscriptionManager & p_subscriptionManager)
	: m_provider(p_provider)
	, m_metadata(p_metadata)
	, m_subscriptionManager(p_subscriptionManager)
	{ }

	std::string getBaseUri() const override {
		return m_metadata.getSetServicePath();
	}

	std::string getWSDL() override {
		OSELib::WSDL::WSDLLoader t_wsdlLoader; // FIXME: Always create a new Loader?
		return t_wsdlLoader.getSetServiceWSDL();
	}

	DPWS::GetMetadataTraits::Response getMetadata(const std::string & p_serverAddress, bool p_SSL) override {
		return m_metadata.createSetServiceMetadata(p_serverAddress, p_SSL);
	}

	std::unique_ptr<SDC::ActivateTraits::Response> dispatch(const SDC::ActivateTraits::Request & p_request) override {
		std::lock_guard<std::mutex> t_lock{m_provider.getMutex()}; // FIXME: Mutex should not be used outside of the class!
		return std::unique_ptr<SDC::ActivateTraits::Response>(new SDC::ActivateTraits::Response(m_provider.OnActivateAsync(p_request)));
	}

	std::unique_ptr<SDC::SetAlertStateTraits::Response> dispatch(const SDC::SetAlertStateTraits::Request & p_request) override {
		std::lock_guard<std::mutex> t_lock{m_provider.getMutex()}; // FIXME: Mutex should not be used outside of the class!
		return std::unique_ptr<SDC::SetAlertStateTraits::Response>(new SDC::SetAlertStateTraits::Response(m_provider.SetAlertStateAsync(p_request)));
	}

	std::unique_ptr<SDC::SetStringTraits::Response> dispatch(const SDC::SetStringTraits::Request & p_request) override {
		std::lock_guard<std::mutex> t_lock{m_provider.getMutex()}; // FIXME: Mutex should not be used outside of the class!
		return std::unique_ptr<SDC::SetStringTraits::Response>(new SDC::SetStringTraits::Response(m_provider.SetStringAsync(p_request)));
	}

	std::unique_ptr<SDC::SetValueTraits::Response> dispatch(const SDC::SetValueTraits::Request & p_request) override {
		std::lock_guard<std::mutex> t_lock{m_provider.getMutex()}; // FIXME: Mutex should not be used outside of the class!
		return std::unique_ptr<SDC::SetValueTraits::Response>(new SDC::SetValueTraits::Response(m_provider.SetValueAsync(p_request)));
	}

	std::unique_ptr<DPWS::SubscribeTraits::Response> dispatch(const DPWS::SubscribeTraits::Request & p_request) override {
		return m_subscriptionManager.dispatch(p_request);
	}
	std::unique_ptr<DPWS::UnsubscribeTraits::Response> dispatch(const DPWS::UnsubscribeTraits::Request & p_request, const DPWS::UnsubscribeTraits::RequestIdentifier & p_identifier) override {
			return m_subscriptionManager.dispatch(p_request, p_identifier);
	}
	std::unique_ptr<DPWS::RenewTraits::Response> dispatch(const DPWS::RenewTraits::Request & p_request, const DPWS::RenewTraits::RequestIdentifier & p_identifier) override {
		return m_subscriptionManager.dispatch(p_request, p_identifier);
	}
	std::unique_ptr<DPWS::GetStatusTraits::Response> dispatch(const DPWS::GetStatusTraits::Request & p_request, const DPWS::GetStatusTraits::RequestIdentifier & p_identifier) override {
		return m_subscriptionManager.dispatch(p_request, p_identifier);
	}
};

class BICEPSServiceImpl : public SDC::IBICEPSService
{
private:
	SDCLib::Data::SDC::SDCProvider & m_provider;
	const DPWS::MetadataProvider m_metadata;
	DPWS::SubscriptionManager & m_subscriptionManager;

public:
	BICEPSServiceImpl(SDCLib::Data::SDC::SDCProvider & p_provider, const DPWS::MetadataProvider & p_metadata, DPWS::SubscriptionManager & p_subscriptionManager)
	: m_provider(p_provider)
	, m_metadata(p_metadata)
	, m_subscriptionManager(p_subscriptionManager)
	{ }

	std::string getBaseUri() const override {
		return m_metadata.getBICEPSServicePath();
	}

	std::string getWSDL() override {
		OSELib::WSDL::WSDLLoader t_wsdlLoader; // FIXME: Always create a new Loader?
		return t_wsdlLoader.getBICEPSServiceWSDL();
	}

	DPWS::GetMetadataTraits::Response getMetadata(const std::string & p_serverAddress, bool p_SSL) override {
		return m_metadata.createBICEPSServiceMetadata(p_serverAddress, p_SSL);
	}

	std::unique_ptr<DPWS::SubscribeTraits::Response> dispatch(const DPWS::SubscribeTraits::Request & request) override {
		return m_subscriptionManager.dispatch(request);
	}
	std::unique_ptr<DPWS::UnsubscribeTraits::Response> dispatch(const DPWS::UnsubscribeTraits::Request & p_request, const DPWS::UnsubscribeTraits::RequestIdentifier & p_identifier) override {
		return m_subscriptionManager.dispatch(p_request, p_identifier);
	}
	std::unique_ptr<DPWS::RenewTraits::Response> dispatch(const DPWS::RenewTraits::Request & p_request, const DPWS::RenewTraits::RequestIdentifier & p_identifier) override {
		return m_subscriptionManager.dispatch(p_request, p_identifier);
	}
	std::unique_ptr<DPWS::GetStatusTraits::Response> dispatch(const DPWS::GetStatusTraits::Request & p_request, const DPWS::GetStatusTraits::RequestIdentifier & p_identifier) override {
		return m_subscriptionManager.dispatch(p_request, p_identifier);
	}

	std::unique_ptr<SDC::GetContextStatesTraits::Response> dispatch(const SDC::GetContextStatesTraits::Request & p_request) override {
        std::lock_guard<std::mutex> t_lock{m_provider.getMutex()}; // FIXME: Mutex should not be used outside of the class!
		return std::unique_ptr<SDC::GetContextStatesTraits::Response>(new SDC::GetContextStatesTraits::Response(m_provider.GetContextStates(p_request)));
	}
	std::unique_ptr<SDC::SetContextStateTraits::Response> dispatch(const SDC::SetContextStateTraits::Request & p_request) override {
		std::lock_guard<std::mutex> t_lock{m_provider.getMutex()}; // FIXME: Mutex should not be used outside of the class!
		return std::unique_ptr<SDC::SetContextStateTraits::Response>(new SDC::SetContextStateTraits::Response(m_provider.SetContextStateAsync(p_request)));
	}
};


}

namespace SDCLib {
namespace Data {
namespace SDC {

class ProviderFactory : public OSELib::HTTP::FrontControllerAdapter
{
private:
		OSELib::HTTP::FrontController m_frontController;

        OSELib::DeviceImpl deviceStub;
        OSELib::GetServiceImpl getServiceStub;
        OSELib::SetServiceImpl setServiceStub;
        OSELib::BICEPSServiceImpl BICEPSServiceStub;

        OSELib::DPWS::DeviceServiceController m_deviceService;

        OSELib::GetServiceController m_getService;
        OSELib::SetServiceController m_setService;
        OSELib::BICEPSServiceController m_BICEPSService;

public:
    ProviderFactory(SDCProvider & p_provider,
            const OSELib::DPWS::MetadataProvider & p_metadata,
            OSELib::DPWS::MDPWSHostAdapter & p_dpwsHost,
            OSELib::DPWS::SubscriptionManager & p_subscriptionManager,
            //std::set<int> & p_strPorts, // FIXME: Streaming Ports!
            bool p_SSL) :
        FrontControllerAdapter(m_frontController),
        deviceStub(p_metadata, p_dpwsHost),
		getServiceStub(p_provider, p_metadata),
		setServiceStub(p_provider, p_metadata, p_subscriptionManager),
		BICEPSServiceStub(p_provider, p_metadata, p_subscriptionManager),
        m_deviceService(m_frontController, deviceStub),
        m_getService(m_frontController, getServiceStub),
        m_setService(m_frontController, setServiceStub),
		m_BICEPSService(m_frontController, BICEPSServiceStub)
    {
        m_frontController.setSSL(p_SSL);
    }
};

SDCProviderAdapter::SDCProviderAdapter(SDCProvider & p_provider)
: m_provider(p_provider)
{ }

SDCProviderAdapter::~SDCProviderAdapter()
{
	std::lock_guard<std::mutex> t_lock{m_mutex};

	if (m_dpwsHost)
	{
		m_dpwsHost->stop();
	}

	if (m_httpServer)
	{
		m_httpServer->stopAll(false);
		while (m_httpServer->currentConnections() != 0) {
	        std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	}

	m_httpServer.reset();
	m_dpwsHost.reset();
	m_subscriptionManager.reset();
}


bool SDCProviderAdapter::start()
{
	std::lock_guard<std::mutex> t_lock{m_mutex};
	if (m_dpwsHost || m_subscriptionManager || m_httpServer) {
		throw std::runtime_error("Service is already running..");
	}

	OSELib::DPWS::MetadataProvider t_metadata(m_provider.getDeviceCharacteristics());


    auto t_networkConfig = m_provider.getSDCInstance()->getNetworkConfig();
	auto t_SSLConfig = m_provider.getSDCInstance()->getSSLConfig();
    assert(t_networkConfig != nullptr);
    assert(t_SSLConfig != nullptr);

    auto t_interface = t_networkConfig->getMDPWSInterface();
    if(!t_interface) {
    	OSELib::Helper::WithLogger(OSELib::Log::sdcProvider).log_error([] { return "Failed to start SDCProviderAdapter: Set MDPWSInterface first!";});
        return false;
    }

    // todo: right now only binding to one interface is possible -> implementation for more than one interface is needed!
    auto t_bindingAddress = t_interface->m_if.address();
    auto t_port = t_networkConfig->getMDPWSPort();

    // Use SSL - HTTP'S'
    std::string t_PROTOCOL = "http";
    if(m_provider.getSDCInstance()->getSSLConfig()->isInit()) {
        t_PROTOCOL.append("s");
    }

	// add address to to DPWS xAddresses so that searching devices know on which address to connect to device
	OSELib::DPWS::XAddressesType t_xAddresses;
	t_xAddresses.push_back(OSELib::DPWS::AddressType(t_PROTOCOL + "://" + t_bindingAddress.toString() + ":" + std::to_string(t_port) + t_metadata.getDeviceServicePath()));

	OSELib::DPWS::TypesType t_types;
	t_types.push_back(OSELib::DPWS::QName(OSELib::SDC::NS_DPWS, "Device"));
	t_types.push_back(OSELib::DPWS::QName(OSELib::SDC::NS_MDPWS, "MedicalDevice"));

	m_dpwsHost = std::unique_ptr<OSELib::DPWS::MDPWSHostAdapter>(new OSELib::DPWS::MDPWSHostAdapter(m_provider.getSDCInstance()->getNetworkConfig(),
			OSELib::DPWS::AddressType(m_provider.getEndpointReference()),
			OSELib::DPWS::ScopesType(),
			t_types,
			t_xAddresses));

	const std::vector<xml_schema::Uri> tl_allowedSubscriptionEventActions {
				OSELib::SDC::DescriptionModificationReportTraits::Action(),
				OSELib::SDC::EpisodicAlertReportTraits::Action(),
				OSELib::SDC::EpisodicComponentReportTraits::Action(),
				OSELib::SDC::EpisodicContextReportTraits::Action(),
				OSELib::SDC::EpisodicMetricReportTraits::Action(),
				OSELib::SDC::EpisodicOperationalStateReportTraits::Action(),
				OSELib::SDC::OperationInvokedReportTraits::Action(),
				OSELib::SDC::PeriodicAlertReportTraits::Action(),
				OSELib::SDC::PeriodicContextReportTraits::Action(),
				OSELib::SDC::WaveformStreamTraits::Action(),
				OSELib::SDC::PeriodicMetricReportTraits::Action() };

	m_subscriptionManager = std::unique_ptr<OSELib::DPWS::SubscriptionManager>(new OSELib::DPWS::SubscriptionManager(tl_allowedSubscriptionEventActions, m_provider.getSDCInstance()->getSSLConfig()));


	// HTTP Server
    m_httpServer = std::unique_ptr<OSELib::HTTP::HTTPServer>(new OSELib::HTTP::HTTPServer(t_networkConfig, t_SSLConfig));

    // Init
    auto t_factory = new ProviderFactory(m_provider, t_metadata, *m_dpwsHost, *m_subscriptionManager, /*ml_streamingPorts,*/ m_provider.getSDCInstance()->getSSLConfig()->isInit());
    if(!m_httpServer->init(std::make_shared<OSELib::HTTP::HTTPRequestHandlerFactory>(t_factory))) {
    	OSELib::Helper::WithLogger(OSELib::Log::sdcProvider).log_error([] { return "SDCProviderAdapter: Failed to init HTTPServer!";});
    	return false;
    }

    // Start all components
	m_httpServer->start();
	m_dpwsHost->start();
    return true;
}

void SDCProviderAdapter::notifyEvent(const MDM::DescriptionModificationReport & p_report) {
	std::lock_guard<std::mutex> t_lock{m_mutex};
	if (m_subscriptionManager) {
		m_subscriptionManager->fireEvent<OSELib::SDC::DescriptionModificationReportTraits>(p_report);
	}
}

void SDCProviderAdapter::notifyEvent(const MDM::EpisodicAlertReport & p_report) {
	std::lock_guard<std::mutex> t_lock{m_mutex};
	if (m_subscriptionManager) {
		m_subscriptionManager->fireEvent<OSELib::SDC::EpisodicAlertReportTraits>(p_report);
	}
}
void SDCProviderAdapter::notifyEvent(const MDM::EpisodicComponentReport & p_report) {
	std::lock_guard<std::mutex> t_lock{m_mutex};
	if (m_subscriptionManager) {
		m_subscriptionManager->fireEvent<OSELib::SDC::EpisodicComponentReportTraits>(p_report);
	}
}

void SDCProviderAdapter::notifyEvent(const MDM::EpisodicContextReport & p_report) {
	std::lock_guard<std::mutex> t_lock{m_mutex};
	if (m_subscriptionManager) {
		m_subscriptionManager->fireEvent<OSELib::SDC::EpisodicContextReportTraits>(p_report);
	}
}

void SDCProviderAdapter::notifyEvent(const MDM::EpisodicMetricReport & p_report) {
	std::lock_guard<std::mutex> t_lock{m_mutex};
	if (m_subscriptionManager) {
		m_subscriptionManager->fireEvent<OSELib::SDC::EpisodicMetricReportTraits>(p_report);
	}
}

void SDCProviderAdapter::notifyEvent(const MDM::EpisodicOperationalStateReport & p_report) {
	std::lock_guard<std::mutex> t_lock{m_mutex};
	if (m_subscriptionManager) {
		m_subscriptionManager->fireEvent<OSELib::SDC::EpisodicOperationalStateReportTraits>(p_report);
	}
}

// WaveformStream uses UDP multicast, thus no subscription management is needed
void SDCProviderAdapter::notifyEvent(const MDM::WaveformStream & p_stream) {
	m_dpwsHost->sendStream(p_stream);
}



void SDCProviderAdapter::notifyEvent(const MDM::PeriodicAlertReport & p_report) {
	std::lock_guard<std::mutex> t_lock{m_mutex};
	if (m_subscriptionManager) {
		m_subscriptionManager->fireEvent<OSELib::SDC::PeriodicAlertReportTraits>(p_report);
	}
}

void SDCProviderAdapter::notifyEvent(const MDM::PeriodicContextReport & report) {
	std::lock_guard<std::mutex> lock{m_mutex};
	if (m_subscriptionManager) {
		m_subscriptionManager->fireEvent<OSELib::SDC::PeriodicContextReportTraits>(report);
	}
}

void SDCProviderAdapter::notifyEvent(const MDM::PeriodicMetricReport & p_report)
{
	std::lock_guard<std::mutex> t_lock{m_mutex};
	if (m_subscriptionManager) {
		m_subscriptionManager->fireEvent<OSELib::SDC::PeriodicMetricReportTraits>(p_report);
	}
}

void SDCProviderAdapter::notifyEvent(const MDM::OperationInvokedReport & p_report)
{
	std::lock_guard<std::mutex> t_lock{m_mutex};
	if (m_subscriptionManager) {
		m_subscriptionManager->fireEvent<OSELib::SDC::OperationInvokedReportTraits>(p_report);
	}
}

void SDCProviderAdapter::addStreamingPort(const int port) {
	ml_streamingPorts.insert(port);
}

void SDCProviderAdapter::removeStreamingPort(const int port) {
	ml_streamingPorts.erase(port);
}

}
}
}
