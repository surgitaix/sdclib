/*
 * SDCProviderAdapter.cpp
 *
 *  Created on: 09.12.2015
 *      Author: matthias
 */

#include <iostream>

#include "Poco/Mutex.h"
#include "Poco/ThreadPool.h"
#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/NetworkInterface.h"
#include "Poco/Net/ServerSocket.h"

#include "BICEPS_ParticipantModel.hxx"
#include "BICEPS_MessageModel.hxx"
#include "MetadataExchange.hxx"
#include "NormalizedMessageModel.hxx"
#include "ws-addressing.hxx"
#include "wsdd-discovery-1.1-schema-os.hxx"

#include "OSCLib/SDCInstance.h"
#include "OSCLib/Data/SDC/SDCProvider.h"
#include "OSCLib/Data/SDC/SDCProviderAdapter.h"

#include "OSELib/fwd.h"
#include "OSELib/DPWS/DeviceServiceController.h"
#include "OSELib/DPWS/MDPWSHostAdapter.h"
#include "OSELib/DPWS/IDevice.h"
#include "OSELib/DPWS/MetadataProvider.h"
#include "OSELib/DPWS/SubscriptionManager.h"
#include "OSELib/HTTP/FrontControllerAdapter.h"
#include "OSELib/HTTP/HTTPSessionManager.h"
#include "OSELib/SDC/ContextServiceHandler.h"
#include "OSELib/SDC/EventReportServiceHandler.h"
#include "OSELib/SDC/WaveformReportServiceHandler.h"
#include "OSELib/SDC/GetServiceHandler.h"
#include "OSELib/SDC/IContextService.h"
#include "OSELib/SDC/IEventReport.h"
#include "OSELib/SDC/IGetService.h"
#include "OSELib/SDC/ISetService.h"
#include "OSELib/SDC/OperationTraits.h"
#include "OSELib/SDC/SDCConstants.h"
#include "OSELib/SDC/SDCServiceController.h"
#include "OSELib/SDC/ReportTraits.h"
#include "OSELib/SDC/SetServiceHandler.h"
#include "OSELib/WSDL/WSDLBuilder.h"

namespace OSELib {

using ContextServiceController = SDC::SDCServiceController<SDC::IContextService , SDC::ContextServiceHandler>;
using EventReportServiceController = SDC::SDCServiceController<SDC::IEventReport, SDC::EventReportServiceHandler>;
using GetServiceController = SDC::SDCServiceController<SDC::IGetService, SDC::GetServiceHandler>;
using SetServiceController = SDC::SDCServiceController<SDC::ISetService, SDC::SetServiceHandler>;
using WaveformEventReportServiceController = SDC::SDCServiceController<SDC::IEventReport, SDC::WaveformReportServiceHandler>;

struct DeviceImpl : public DPWS::IDevice {
	DeviceImpl(const DPWS::MetadataProvider & metadata, DPWS::MDPWSHostAdapter & host) :
		_metadata(metadata),
		_host(host)
	{
	}

	virtual std::string getBaseUri() const override {
		return _metadata.getDeviceServicePath();
	}

	virtual DPWS::GetTraits::Response getMetadata(const std::string & serverAddress) override {
		return _metadata.createDeviceMetadata(serverAddress);
	}

	virtual std::unique_ptr<DPWS::ProbeTraits::Response> dispatch(const DPWS::ProbeTraits::Request & request) override {
		std::unique_ptr<DPWS::ProbeTraits::Response> response(new DPWS::ProbeTraits::Response());
		for (const auto & item : _host.dispatch(request)) {
			response->ProbeMatch().push_back(item);
		}

		return std::move(response);
	}

private:
	const DPWS::MetadataProvider _metadata;
	DPWS::MDPWSHostAdapter & _host;
};

struct ContextReportServiceImpl : public SDC::IContextService {

	ContextReportServiceImpl(SDCLib::Data::SDC::SDCProvider & provider, const DPWS::MetadataProvider & metadata, DPWS::SubscriptionManager & subscriptionManager) :
		_provider(provider),
		_metadata(metadata),
		_subscriptionManager(subscriptionManager)
	{
	}

	virtual std::string getBaseUri() const override {
		return _metadata.getContextServicePath();
	}

	virtual std::string getWSDL() override {
		WSDL::WSDLBuilder builder(SDC::NS_WSDL_TARGET_NAMESPACE, SDC::QNAME_CONTEXTSERVICE_PORTTYPE);
		WSDL::WSDLBuilderTraitAdapter<SDC::EpisodicContextChangedReportTraits> EpisodicContextChangedReportTraitsAdapter(builder);
		WSDL::WSDLBuilderTraitAdapter<SDC::PeriodicContextChangedReportTraits> PeriodicContextChangedReportTraits(builder);
		WSDL::WSDLBuilderTraitAdapter<SDC::GetContextStatesTraits> GetContextStatesTraitsAdapter(builder);
		WSDL::WSDLBuilderTraitAdapter<SDC::SetContextStateTraits> SetContextStateTraits(builder);
		WSDL::WSDLBuilderTraitAdapter<SDC::WaveformStreamTraits> WaveformStreamTraits(builder);
		return builder.serialize();
	}

	virtual DPWS::GetMetadataTraits::Response getMetadata(const std::string & serverAddress) override {
		return _metadata.createContextServiceMetadata(serverAddress);
	}

	virtual std::unique_ptr<DPWS::SubscribeTraits::Response> dispatch(const DPWS::SubscribeTraits::Request & request) override {
		return _subscriptionManager.dispatch(request);
	}
	virtual std::unique_ptr<DPWS::UnsubscribeTraits::Response> dispatch(const DPWS::UnsubscribeTraits::Request & request, const DPWS::UnsubscribeTraits::RequestIdentifier & identifier) override {
		return _subscriptionManager.dispatch(request, identifier);
	}
	virtual std::unique_ptr<DPWS::RenewTraits::Response> dispatch(const DPWS::RenewTraits::Request & request, const DPWS::RenewTraits::RequestIdentifier & identifier) override {
		return _subscriptionManager.dispatch(request, identifier);
	}
	virtual std::unique_ptr<SDC::GetContextStatesTraits::Response> dispatch(const SDC::GetContextStatesTraits::Request & request) override {
		Poco::Mutex::ScopedLock lock(_provider.getMutex());
		return std::unique_ptr<SDC::GetContextStatesTraits::Response>(new SDC::GetContextStatesTraits::Response(_provider.GetContextStates(request)));
	}
	virtual std::unique_ptr<SDC::SetContextStateTraits::Response> dispatch(const SDC::SetContextStateTraits::Request & request) override {
		Poco::Mutex::ScopedLock lock(_provider.getMutex());
		return std::unique_ptr<SDC::SetContextStateTraits::Response>(new SDC::SetContextStateTraits::Response(_provider.SetContextStateAsync(request)));
	}

private:
	SDCLib::Data::SDC::SDCProvider & _provider;
	const DPWS::MetadataProvider _metadata;
	DPWS::SubscriptionManager & _subscriptionManager;
};

struct EventReportServiceImpl : public SDC::IEventReport {

	EventReportServiceImpl(const DPWS::MetadataProvider & metadata, DPWS::SubscriptionManager & subscriptionManager) :
		_metadata(metadata),
		_subscriptionManager(subscriptionManager)
	{
	}

	virtual std::string getBaseUri() const override {
		return _metadata.getStateEventReportServicePath();
	}

	virtual std::string getWSDL() override {
		WSDL::WSDLBuilder builder(SDC::NS_WSDL_TARGET_NAMESPACE, SDC::QNAME_STATEEVENTREPORTSERVICE_PORTTYPE);
		WSDL::WSDLBuilderTraitAdapter<SDC::EpisodicAlertReportTraits> EpisodicAlertReportTraitsAdapter(builder);
		WSDL::WSDLBuilderTraitAdapter<SDC::EpisodicMetricReportTraits> EpisodicMetricReportTraitsAdapter(builder);
		WSDL::WSDLBuilderTraitAdapter<SDC::OperationInvokedReportTraits> OperationInvokedReportAdapter(builder);
		WSDL::WSDLBuilderTraitAdapter<SDC::PeriodicAlertReportTraits> PeriodicAlertReportTraitsAdapter(builder);
		WSDL::WSDLBuilderTraitAdapter<SDC::PeriodicMetricReportTraits> PeriodicMetricReportTraitsAdapter(builder);
		return builder.serialize();
	}

	virtual DPWS::GetMetadataTraits::Response getMetadata(const std::string & serverAddress) override {
		return _metadata.createEventServiceMetadata(serverAddress);
	}

	virtual std::unique_ptr<DPWS::SubscribeTraits::Response> dispatch(const DPWS::SubscribeTraits::Request & request) override {
		return _subscriptionManager.dispatch(request);
	}
	virtual std::unique_ptr<DPWS::UnsubscribeTraits::Response> dispatch(const DPWS::UnsubscribeTraits::Request & request, const DPWS::UnsubscribeTraits::RequestIdentifier & identifier) override {
		return _subscriptionManager.dispatch(request, identifier);
	}
	virtual std::unique_ptr<DPWS::RenewTraits::Response> dispatch(const DPWS::RenewTraits::Request & request, const DPWS::RenewTraits::RequestIdentifier & identifier) override {
		return _subscriptionManager.dispatch(request, identifier);
	}

private:
	const DPWS::MetadataProvider _metadata;
	DPWS::SubscriptionManager & _subscriptionManager;
};

struct WaveformReportServiceImpl : public SDC::IEventReport {

	WaveformReportServiceImpl(const DPWS::MetadataProvider & metadata, std::set<int> & streamingPorts) :
		_metadata(metadata), _streamingPorts(streamingPorts)
	{
	}

	virtual std::string getBaseUri() const override {
		return _metadata.getWaveformServicePath();
	}

	virtual std::string getWSDL() override {
		WSDL::WSDLBuilder builder(SDC::NS_WSDL_TARGET_NAMESPACE, SDC::QNAME_WAVEFORMSERVICE_PORTTYPE);
		builder.addStreamType(SDC::WS_MEX_ORNET_STREAM_IDENTIFIER, SDC::ACTION_ORNET_STREAM, SDC::WS_MEX_ORNET_STREAM_TYPE, "WaveformStream");
		return builder.serialize();
	}

	virtual DPWS::GetMetadataTraits::Response getMetadata(const std::string & serverAddress) override {
		return _metadata.createStreamServiceMetadata(serverAddress, _streamingPorts);
	}

	virtual std::unique_ptr<DPWS::SubscribeTraits::Response> dispatch(const DPWS::SubscribeTraits::Request & request) override {
		return nullptr;
	}
	virtual std::unique_ptr<DPWS::UnsubscribeTraits::Response> dispatch(const DPWS::UnsubscribeTraits::Request & request, const DPWS::UnsubscribeTraits::RequestIdentifier & identifier) override {
		return nullptr;
	}
	virtual std::unique_ptr<DPWS::RenewTraits::Response> dispatch(const DPWS::RenewTraits::Request & request, const DPWS::RenewTraits::RequestIdentifier & identifier) override {
		return nullptr;
	}

private:
	const DPWS::MetadataProvider _metadata;
	const std::set<int> & _streamingPorts;
};

struct GetServiceImpl : public SDC::IGetService {

	GetServiceImpl(SDCLib::Data::SDC::SDCProvider & provider, const DPWS::MetadataProvider & metadata) :
		_provider(provider),
		_metadata(metadata)
	{
	}

	virtual std::string getBaseUri() const override {
		return _metadata.getGetServicePath();
	}

	virtual std::string getWSDL() override {
		WSDL::WSDLBuilder builder(SDC::NS_WSDL_TARGET_NAMESPACE, SDC::QNAME_GETSERVICE_PORTTYPE);
		WSDL::WSDLBuilderTraitAdapter<SDC::GetMDDescriptionTraits> GetMDDescriptionTraitsAdapter(builder);
		WSDL::WSDLBuilderTraitAdapter<SDC::GetMDIBTraits> GetMDIBTraitsAdapter(builder);
		WSDL::WSDLBuilderTraitAdapter<SDC::GetMdStateTraits> GetMDStateOperationAdapter(builder);
		return builder.serialize();
	}

	virtual DPWS::GetMetadataTraits::Response getMetadata(const std::string & serverAddress) override {
		return _metadata.createGetServiceMetadata(serverAddress);
	}

	virtual std::unique_ptr<SDC::GetMDDescriptionTraits::Response> dispatch(const SDC::GetMDDescriptionTraits::Request & request) override {
		Poco::Mutex::ScopedLock lock(_provider.getMutex());
		return std::unique_ptr<SDC::GetMDDescriptionTraits::Response>(new SDC::GetMDDescriptionTraits::Response(_provider.GetMdDescription(request)));
	}
	virtual std::unique_ptr<SDC::GetMDIBTraits::Response> dispatch(const SDC::GetMDIBTraits::Request & request) override {
		Poco::Mutex::ScopedLock lock(_provider.getMutex());
		return std::unique_ptr<SDC::GetMDIBTraits::Response>(new SDC::GetMDIBTraits::Response(_provider.GetMdib(request)));
	}
	virtual std::unique_ptr<SDC::GetMdStateTraits::Response> dispatch(const SDC::GetMdStateTraits::Request & request) override {
		Poco::Mutex::ScopedLock lock(_provider.getMutex());
		return std::unique_ptr<SDC::GetMdStateTraits::Response>(new SDC::GetMdStateTraits::Response(_provider.GetMdState(request)));
	}

private:
	SDCLib::Data::SDC::SDCProvider & _provider;
	const DPWS::MetadataProvider _metadata;
};

struct SetServiceImpl : public SDC::ISetService {

	SetServiceImpl(SDCLib::Data::SDC::SDCProvider & provider, const DPWS::MetadataProvider & metadata) :
		_provider(provider),
		_metadata(metadata)
	{
	}

	virtual std::string getBaseUri() const override {
		return _metadata.getSetServicePath();
	}

	virtual std::string getWSDL() override {
		WSDL::WSDLBuilder builder(SDC::NS_WSDL_TARGET_NAMESPACE, SDC::QNAME_SETSERVICE_PORTTYPE);
		WSDL::WSDLBuilderTraitAdapter<SDC::ActivateTraits> ActivateTraitsAdapter(builder);
		WSDL::WSDLBuilderTraitAdapter<SDC::SetAlertStateTraits> SetAlertStateTraitsAdapter(builder);
		WSDL::WSDLBuilderTraitAdapter<SDC::SetStringTraits> SetStringTraitsAdapter(builder);
		WSDL::WSDLBuilderTraitAdapter<SDC::SetValueTraits> SetValueTraitsAdapter(builder);

		return builder.serialize();
	}

	virtual DPWS::GetMetadataTraits::Response getMetadata(const std::string & serverAddress) override {
		return _metadata.createSetServiceMetadata(serverAddress);
	}

	virtual std::unique_ptr<SDC::ActivateTraits::Response> dispatch(const SDC::ActivateTraits::Request & request) override {
		Poco::Mutex::ScopedLock lock(_provider.getMutex());
		return std::unique_ptr<SDC::ActivateTraits::Response>(new SDC::ActivateTraits::Response(_provider.OnActivateAsync(request)));
	}

	virtual std::unique_ptr<SDC::SetAlertStateTraits::Response> dispatch(const SDC::SetAlertStateTraits::Request & request) override {
		Poco::Mutex::ScopedLock lock(_provider.getMutex());
		return std::unique_ptr<SDC::SetAlertStateTraits::Response>(new SDC::SetAlertStateTraits::Response(_provider.SetAlertStateAsync(request)));
	}

	virtual std::unique_ptr<SDC::SetStringTraits::Response> dispatch(const SDC::SetStringTraits::Request & request) override {
		Poco::Mutex::ScopedLock lock(_provider.getMutex());
		return std::unique_ptr<SDC::SetStringTraits::Response>(new SDC::SetStringTraits::Response(_provider.SetStringAsync(request)));
	}

	virtual std::unique_ptr<SDC::SetValueTraits::Response> dispatch(const SDC::SetValueTraits::Request & request) override {
		Poco::Mutex::ScopedLock lock(_provider.getMutex());
		return std::unique_ptr<SDC::SetValueTraits::Response>(new SDC::SetValueTraits::Response(_provider.SetValueAsync(request)));
	}

private:
	SDCLib::Data::SDC::SDCProvider & _provider;
	const DPWS::MetadataProvider _metadata;
};

}

namespace SDCLib {
namespace Data {
namespace SDC {

SDCProviderAdapter::SDCProviderAdapter(SDCProvider & provider) :
	_provider(provider),
	_threadPool(new Poco::ThreadPool())
{
}

SDCProviderAdapter::~SDCProviderAdapter() {

}
void SDCProviderAdapter::start(const MDPWSTransportLayerConfiguration config) {

	Poco::Mutex::ScopedLock lock(mutex);
	if (_dpwsHost || _subscriptionManager || _httpServer) {
		throw std::runtime_error("Service is already running..");
	}

	// todo make this configurable by the provider. The best would be to get all neccessary dpws device/model information in the provider constructor and directly forward it here
	// this should be done as copy, because the metadata should NOT be changeable during runtime.
	OSELib::DPWS::MetadataProvider metadata(_provider.getDeviceCharacteristics());

	Poco::Net::ServerSocket ss;
	const Poco::Net::IPAddress address(config.getBindAddress());
	const Poco::Net::SocketAddress socketAddress(address, config.getPort());
	ss.bind(socketAddress);
	ss.listen();

	OSELib::DPWS::XAddressesType xAddresses;

    auto t_SDCInstance = _provider.getSDCInstance();
	// Bound: Only add the bound address
	if (t_SDCInstance->isBound()) {
        xAddresses.push_back(OSELib::DPWS::AddressType("http://" + config.getBindAddress().toString() + ":" + std::to_string(config.getPort()) + metadata.getDeviceServicePath()));
    }
    else {
        // Add all interfaces
        for (const auto & nextIf : Poco::Net::NetworkInterface::list()) {
            if (nextIf.supportsIPv4()
                && nextIf.address().isUnicast()
                && !nextIf.address().isLoopback()) {
                xAddresses.push_back(OSELib::DPWS::AddressType("http://" + nextIf.address().toString() + ":" + std::to_string(config.getPort()) + metadata.getDeviceServicePath()));
            }
        }
    }

	OSELib::DPWS::TypesType types;
	types.push_back(OSELib::DPWS::QName(OSELib::SDC::NS_DPWS, "MedicalDevice"));
	types.push_back(OSELib::DPWS::QName(OSELib::SDC::NS_MDPWS, "MedicalDevice"));

    _dpwsHost = std::unique_ptr<OSELib::DPWS::MDPWSHostAdapter>(new OSELib::DPWS::MDPWSHostAdapter(t_SDCInstance,
			OSELib::DPWS::AddressType(_provider.getEndpointReference()),
			OSELib::DPWS::ScopesType(),
			types,
			xAddresses));

	const std::vector<xml_schema::Uri> allowedSubscriptionEventActions {
				OSELib::SDC::EpisodicAlertReportTraits::Action(),
				OSELib::SDC::EpisodicContextChangedReportTraits::Action(),
				OSELib::SDC::EpisodicMetricReportTraits::Action(),
				OSELib::SDC::OperationInvokedReportTraits::Action(),
				OSELib::SDC::PeriodicAlertReportTraits::Action(),
				OSELib::SDC::PeriodicContextChangedReportTraits::Action(),
				OSELib::SDC::PeriodicMetricReportTraits::Action() };
	_subscriptionManager = std::unique_ptr<OSELib::DPWS::SubscriptionManager>(new OSELib::DPWS::SubscriptionManager(allowedSubscriptionEventActions));

	class Factory : public OSELib::HTTP::FrontControllerAdapter {
	public:
		Factory(SDCProvider & provider,
				const OSELib::DPWS::MetadataProvider & metadata,
				OSELib::DPWS::MDPWSHostAdapter & dpwsHost,
				OSELib::DPWS::SubscriptionManager & subscriptionManager,
				std::set<int> & strPorts) :
			FrontControllerAdapter(_frontController),
			deviceStub(metadata, dpwsHost),
			contextStub(provider, metadata, subscriptionManager),
			eventReportStub(metadata, subscriptionManager),
			getServiceStub(provider, metadata),
			setServiceStub(provider, metadata),
			waveformReportStub(metadata, strPorts),
			_deviceService(_frontController, deviceStub),
			_contextService(_frontController, contextStub),
			_getService(_frontController, getServiceStub),
			_setService(_frontController, setServiceStub),
			_eventReportService(_frontController, eventReportStub),
			_waveformReportService(_frontController, waveformReportStub)
		{
		}

		virtual ~Factory() = default;

		private:
			OSELib::DeviceImpl deviceStub;
			OSELib::ContextReportServiceImpl contextStub;
			OSELib::EventReportServiceImpl eventReportStub;
			OSELib::GetServiceImpl getServiceStub;
			OSELib::SetServiceImpl setServiceStub;
			OSELib::WaveformReportServiceImpl waveformReportStub;

			OSELib::HTTP::FrontController _frontController;
			OSELib::DPWS::DeviceServiceController _deviceService;
			OSELib::ContextServiceController _contextService;
			OSELib::GetServiceController _getService;
			OSELib::SetServiceController _setService;
			OSELib::EventReportServiceController _eventReportService;
			OSELib::WaveformEventReportServiceController _waveformReportService;
	};

	_httpServer = std::unique_ptr<Poco::Net::HTTPServer>(new Poco::Net::HTTPServer(new Factory(_provider, metadata, *_dpwsHost, *_subscriptionManager, streamingPorts), *_threadPool, ss,  new Poco::Net::HTTPServerParams));


	_httpServer->start();
	_dpwsHost->start();
}

void SDCProviderAdapter::stop() {

	Poco::Mutex::ScopedLock lock(mutex);

	if (_dpwsHost) {
		_dpwsHost->stop();
	}
	if (_httpServer) {
		_httpServer->stopAll(false);
	}

	while (_httpServer->currentConnections() != 0) {
		Poco::Thread::sleep(100);
	}

	_dpwsHost.reset();
	_httpServer.reset();
	_subscriptionManager.reset();
}

void SDCProviderAdapter::notifyEvent(const MDM::EpisodicAlertReport & report) {
	Poco::Mutex::ScopedLock lock(mutex);
	if (_subscriptionManager) {
		_subscriptionManager->fireEvent<OSELib::SDC::EpisodicAlertReportTraits>(report);
	}
}

void SDCProviderAdapter::notifyEvent(const MDM::EpisodicContextReport & report) {
	Poco::Mutex::ScopedLock lock(mutex);
	if (_subscriptionManager) {
		_subscriptionManager->fireEvent<OSELib::SDC::EpisodicContextChangedReportTraits>(report);
	}
}

void SDCProviderAdapter::notifyEvent(const MDM::EpisodicMetricReport & report) {
	Poco::Mutex::ScopedLock lock(mutex);
	if (_subscriptionManager) {
		_subscriptionManager->fireEvent<OSELib::SDC::EpisodicMetricReportTraits>(report);
	}
}

// WaveformStream uses UDP multicast, thus no subscription management is needed
void SDCProviderAdapter::notifyEvent(const MDM::WaveformStream & stream) {
	_dpwsHost->sendStream(stream);
}



void SDCProviderAdapter::notifyEvent(const MDM::PeriodicAlertReport & report) {
	Poco::Mutex::ScopedLock lock(mutex);
	if (_subscriptionManager) {
		_subscriptionManager->fireEvent<OSELib::SDC::PeriodicAlertReportTraits>(report);
	}
}

void SDCProviderAdapter::notifyEvent(const MDM::PeriodicContextReport & report) {
	Poco::Mutex::ScopedLock lock(mutex);
	if (_subscriptionManager) {
		_subscriptionManager->fireEvent<OSELib::SDC::PeriodicContextChangedReportTraits>(report);
	}
}

void SDCProviderAdapter::notifyEvent(const MDM::PeriodicMetricReport & report) {
	Poco::Mutex::ScopedLock lock(mutex);
	if (_subscriptionManager) {
		_subscriptionManager->fireEvent<OSELib::SDC::PeriodicMetricReportTraits>(report);
	}
}

void SDCProviderAdapter::notifyEvent(const MDM::OperationInvokedReport & report) {
	Poco::Mutex::ScopedLock lock(mutex);
	if (_subscriptionManager) {
		_subscriptionManager->fireEvent<OSELib::SDC::OperationInvokedReportTraits>(report);
	}
}

void SDCProviderAdapter::addStreamingPort(const int port) {
	streamingPorts.insert(port);
}

void SDCProviderAdapter::removeStreamingPort(const int port) {
	streamingPorts.erase(port);
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */
