/*
 * OSELibProviderAdapter.cpp
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

#include "BICEPS_DomainModel.hxx"
#include "BICEPS_MessageModel.hxx"
#include "MetadataExchange.hxx"
#include "NormalizedMessageModel.hxx"
#include "ws-addressing.hxx"
#include "wsdd-discovery-1.1-schema-os.hxx"

#include "OSCLib/Data/OSCP/OSCPProvider.h"
#include "OSCLib/Data/OSCP/OSELibProviderAdapter.h"

#include "OSELib/fwd.h"
#include "OSELib/DPWS/DeviceServiceController.h"
#include "OSELib/DPWS/DPWSHost.h"
#include "OSELib/DPWS/IDevice.h"
#include "OSELib/DPWS/MetadataProvider.h"
#include "OSELib/DPWS/SubscriptionManager.h"
#include "OSELib/HTTP/FrontControllerAdapter.h"
#include "OSELib/HTTP/HTTPSessionManager.h"
#include "OSELib/OSCP/ContextServiceHandler.h"
#include "OSELib/OSCP/EventReportServiceHandler.h"
#include "OSELib/OSCP/WaveformReportServiceHandler.h"
#include "OSELib/OSCP/GetServiceHandler.h"
#include "OSELib/OSCP/IContextService.h"
#include "OSELib/OSCP/IEventReport.h"
#include "OSELib/OSCP/IGetService.h"
#include "OSELib/OSCP/ISetService.h"
#include "OSELib/OSCP/OperationTraits.h"
#include "OSELib/OSCP/OSCPConstants.h"
#include "OSELib/OSCP/OSCPServiceController.h"
#include "OSELib/OSCP/ReportTraits.h"
#include "OSELib/OSCP/SetServiceHandler.h"
#include "OSELib/WSDL/WSDLBuilder.h"

namespace OSELib {

using ContextServiceController = OSCP::OSCPServiceController<OSCP::IContextService , OSCP::ContextServiceHandler>;
using EventReportServiceController = OSCP::OSCPServiceController<OSCP::IEventReport, OSCP::EventReportServiceHandler>;
using GetServiceController = OSCP::OSCPServiceController<OSCP::IGetService, OSCP::GetServiceHandler>;
using SetServiceController = OSCP::OSCPServiceController<OSCP::ISetService, OSCP::SetServiceHandler>;
using WaveformEventReportServiceController = OSCP::OSCPServiceController<OSCP::IEventReport, OSCP::WaveformReportServiceHandler>;

struct DeviceImpl : public DPWS::IDevice {
	DeviceImpl(const DPWS::MetadataProvider & metadata, DPWS::DPWSHost & host) :
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
	DPWS::DPWSHost & _host;
};

struct ContextReportServiceImpl : public OSCP::IContextService {

	ContextReportServiceImpl(OSCLib::Data::OSCP::OSCPProvider & provider, const DPWS::MetadataProvider & metadata, DPWS::SubscriptionManager & subscriptionManager) :
		_provider(provider),
		_metadata(metadata),
		_subscriptionManager(subscriptionManager)
	{
	}

	virtual std::string getBaseUri() const override {
		return _metadata.getPHIServicePath();
	}

	virtual std::string getWSDL() override {
		WSDL::WSDLBuilder builder(OSCP::NS_WSDL_TARGET_NAMESPACE, OSCP::QNAME_CONTEXTSERVICE_PORTTYPE);
		WSDL::WSDLBuilderTraitAdapter<OSCP::EpisodicContextChangedReportTraits> EpisodicContextChangedReportTraitsAdapter(builder);
		WSDL::WSDLBuilderTraitAdapter<OSCP::PeriodicContextChangedReportTraits> PeriodicContextChangedReportTraits(builder);
		WSDL::WSDLBuilderTraitAdapter<OSCP::GetContextStatesTraits> GetContextStatesTraitsAdapter(builder);
		WSDL::WSDLBuilderTraitAdapter<OSCP::SetContextStateTraits> SetContextStateTraits(builder);
		WSDL::WSDLBuilderTraitAdapter<OSCP::WaveformStreamTraits> WaveformStreamTraits(builder);
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
	virtual std::unique_ptr<OSCP::GetContextStatesTraits::Response> dispatch(const OSCP::GetContextStatesTraits::Request & request) override {
		Poco::Mutex::ScopedLock lock(_provider.getMutex());
		return std::unique_ptr<OSCP::GetContextStatesTraits::Response>(new OSCP::GetContextStatesTraits::Response(_provider.GetContextStates(request)));
	}
	virtual std::unique_ptr<OSCP::SetContextStateTraits::Response> dispatch(const OSCP::SetContextStateTraits::Request & request) override {
		Poco::Mutex::ScopedLock lock(_provider.getMutex());
		return std::unique_ptr<OSCP::SetContextStateTraits::Response>(new OSCP::SetContextStateTraits::Response(_provider.SetContextStateAsync(request)));
	}

private:
	OSCLib::Data::OSCP::OSCPProvider & _provider;
	const DPWS::MetadataProvider _metadata;
	DPWS::SubscriptionManager & _subscriptionManager;
};

struct EventReportServiceImpl : public OSCP::IEventReport {

	EventReportServiceImpl(const DPWS::MetadataProvider & metadata, DPWS::SubscriptionManager & subscriptionManager) :
		_metadata(metadata),
		_subscriptionManager(subscriptionManager)
	{
	}

	virtual std::string getBaseUri() const override {
		return _metadata.getEventReportServicePath();
	}

	virtual std::string getWSDL() override {
		WSDL::WSDLBuilder builder(OSCP::NS_WSDL_TARGET_NAMESPACE, OSCP::QNAME_REPORTSERVICE_PORTTYPE);
		WSDL::WSDLBuilderTraitAdapter<OSCP::EpisodicAlertReportTraits> EpisodicAlertReportTraitsAdapter(builder);
		WSDL::WSDLBuilderTraitAdapter<OSCP::EpisodicMetricReportTraits> EpisodicMetricReportTraitsAdapter(builder);
		WSDL::WSDLBuilderTraitAdapter<OSCP::OperationInvokedReportTraits> OperationInvokedReportAdapter(builder);
		WSDL::WSDLBuilderTraitAdapter<OSCP::PeriodicAlertReportTraits> PeriodicAlertReportTraitsAdapter(builder);
		WSDL::WSDLBuilderTraitAdapter<OSCP::PeriodicMetricReportTraits> PeriodicMetricReportTraitsAdapter(builder);
		return builder.serialize();
	}

	virtual DPWS::GetMetadataTraits::Response getMetadata(const std::string & serverAddress) override {
		DPWS::MetadataProvider metadata;
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

struct WaveformReportServiceImpl : public OSCP::IEventReport {

	WaveformReportServiceImpl(const DPWS::MetadataProvider & metadata, std::set<int> & streamingPorts) :
		_metadata(metadata)
	{
	}

	virtual std::string getBaseUri() const override {
		return _metadata.getWaveformStreamServicePath();
	}

	virtual std::string getWSDL() override {
		WSDL::WSDLBuilder builder(OSCP::NS_WSDL_TARGET_NAMESPACE, OSCP::QNAME_STREAMSERVICE_PORTTYPE);
		builder.addStreamType(OSCP::WS_MEX_ORNET_STREAM_IDENTIFIER, OSCP::ACTION_ORNET_STREAM, OSCP::WS_MEX_ORNET_STREAM_TYPE, "WaveformStream");
		return builder.serialize();
	}

	virtual DPWS::GetMetadataTraits::Response getMetadata(const std::string & serverAddress) override {
		DPWS::MetadataProvider metadata;
		return _metadata.createStreamServiceMetadata(serverAddress, streamingPorts);
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
	const std::set<int> streamingPorts;
};

struct GetServiceImpl : public OSCP::IGetService {

	GetServiceImpl(OSCLib::Data::OSCP::OSCPProvider & provider, const DPWS::MetadataProvider & metadata) :
		_provider(provider),
		_metadata(metadata)
	{
	}

	virtual std::string getBaseUri() const override {
		return _metadata.getGetServicePath();
	}

	virtual std::string getWSDL() override {
		WSDL::WSDLBuilder builder(OSCP::NS_WSDL_TARGET_NAMESPACE, OSCP::QNAME_GETSERVICE_PORTTYPE);
		WSDL::WSDLBuilderTraitAdapter<OSCP::GetMDDescriptionTraits> GetMDDescriptionTraitsAdapter(builder);
		WSDL::WSDLBuilderTraitAdapter<OSCP::GetMDIBTraits> GetMDIBTraitsAdapter(builder);
		WSDL::WSDLBuilderTraitAdapter<OSCP::GetMDStateTraits> GetMDStateOperationAdapter(builder);
		return builder.serialize();
	}

	virtual DPWS::GetMetadataTraits::Response getMetadata(const std::string & serverAddress) override {
		DPWS::MetadataProvider metadata;
		return _metadata.createGetServiceMetadata(serverAddress);
	}

	virtual std::unique_ptr<OSCP::GetMDDescriptionTraits::Response> dispatch(const OSCP::GetMDDescriptionTraits::Request & request) override {
		Poco::Mutex::ScopedLock lock(_provider.getMutex());
		return std::unique_ptr<OSCP::GetMDDescriptionTraits::Response>(new OSCP::GetMDDescriptionTraits::Response(_provider.GetMDDescription(request)));
	}
	virtual std::unique_ptr<OSCP::GetMDIBTraits::Response> dispatch(const OSCP::GetMDIBTraits::Request & request) override {
		Poco::Mutex::ScopedLock lock(_provider.getMutex());
		return std::unique_ptr<OSCP::GetMDIBTraits::Response>(new OSCP::GetMDIBTraits::Response(_provider.GetMDIB(request)));
	}
	virtual std::unique_ptr<OSCP::GetMDStateTraits::Response> dispatch(const OSCP::GetMDStateTraits::Request & request) override {
		Poco::Mutex::ScopedLock lock(_provider.getMutex());
		return std::unique_ptr<OSCP::GetMDStateTraits::Response>(new OSCP::GetMDStateTraits::Response(_provider.GetMDState(request)));
	}

private:
	OSCLib::Data::OSCP::OSCPProvider & _provider;
	const DPWS::MetadataProvider _metadata;
};

struct SetServiceImpl : public OSCP::ISetService {

	SetServiceImpl(OSCLib::Data::OSCP::OSCPProvider & provider, const DPWS::MetadataProvider & metadata) :
		_provider(provider),
		_metadata(metadata)
	{
	}

	virtual std::string getBaseUri() const override {
		return _metadata.getSetServicePath();
	}

	virtual std::string getWSDL() override {
		WSDL::WSDLBuilder builder(OSCP::NS_WSDL_TARGET_NAMESPACE, OSCP::QNAME_SETSERVICE_PORTTYPE);
		WSDL::WSDLBuilderTraitAdapter<OSCP::ActivateTraits> ActivateTraitsAdapter(builder);
		WSDL::WSDLBuilderTraitAdapter<OSCP::SetAlertStateTraits> SetAlertStateTraitsAdapter(builder);
		WSDL::WSDLBuilderTraitAdapter<OSCP::SetStringTraits> SetStringTraitsAdapter(builder);
		WSDL::WSDLBuilderTraitAdapter<OSCP::SetValueTraits> SetValueTraitsAdapter(builder);

		return builder.serialize();
	}

	virtual DPWS::GetMetadataTraits::Response getMetadata(const std::string & serverAddress) override {
		return _metadata.createSetServiceMetadata(serverAddress);
	}

	virtual std::unique_ptr<OSCP::ActivateTraits::Response> dispatch(const OSCP::ActivateTraits::Request & request) override {
		Poco::Mutex::ScopedLock lock(_provider.getMutex());
		return std::unique_ptr<OSCP::ActivateTraits::Response>(new OSCP::ActivateTraits::Response(_provider.OnActivateAsync(request)));
	}

	virtual std::unique_ptr<OSCP::SetAlertStateTraits::Response> dispatch(const OSCP::SetAlertStateTraits::Request & request) override {
		Poco::Mutex::ScopedLock lock(_provider.getMutex());
		return std::unique_ptr<OSCP::SetAlertStateTraits::Response>(new OSCP::SetAlertStateTraits::Response(_provider.SetAlertStateAsync(request)));
	}

	virtual std::unique_ptr<OSCP::SetStringTraits::Response> dispatch(const OSCP::SetStringTraits::Request & request) override {
		Poco::Mutex::ScopedLock lock(_provider.getMutex());
		return std::unique_ptr<OSCP::SetStringTraits::Response>(new OSCP::SetStringTraits::Response(_provider.SetStringAsync(request)));
	}

	virtual std::unique_ptr<OSCP::SetValueTraits::Response> dispatch(const OSCP::SetValueTraits::Request & request) override {
		Poco::Mutex::ScopedLock lock(_provider.getMutex());
		return std::unique_ptr<OSCP::SetValueTraits::Response>(new OSCP::SetValueTraits::Response(_provider.SetValueAsync(request)));
	}

private:
	OSCLib::Data::OSCP::OSCPProvider & _provider;
	const DPWS::MetadataProvider _metadata;
};

}

namespace OSCLib {
namespace Data {
namespace OSCP {

OSELibProviderAdapter::OSELibProviderAdapter(OSCPProvider & provider, const unsigned int port) :
	_provider(provider),
	_threadPool(new Poco::ThreadPool()),
	_port(port)
{
}

OSELibProviderAdapter::~OSELibProviderAdapter() {

}

void OSELibProviderAdapter::start() {

	Poco::Mutex::ScopedLock lock(mutex);
	if (_dpwsHost || _subscriptionManager || _httpServer) {
		return;
		//todo maybe throw because starting twice is clearly an error
	}

	// todo make this configurable by the provider. The best would be to get all neccessary dpws device/model information in the provider constructor and directly forward it here
	// this should be done as copy, because the metadata should NOT be changeable during runtime.
	OSELib::DPWS::MetadataProvider metadata;

	Poco::Net::ServerSocket ss;
	const Poco::Net::IPAddress address(Poco::Net::IPAddress::Family::IPv4);
	const Poco::Net::SocketAddress socketAddress(address, _port);
	ss.bind(socketAddress);
	ss.listen();

	OSELib::DPWS::XAddressesType xAddresses;
	for (const auto & nextIf : Poco::Net::NetworkInterface::list()) {
		if (nextIf.supportsIPv4()
			&& nextIf.address().isUnicast()
			&& !nextIf.address().isLoopback()) {
			xAddresses.push_back(OSELib::DPWS::AddressType("http://" + nextIf.address().toString() + ":" + std::to_string(_port) + metadata.getDeviceServicePath()));
		}
	}

	OSELib::DPWS::TypesType types;
	types.push_back(OSELib::DPWS::QName("http://docs.oasis-open.org/ws-dd/ns/dpws/2009/01", "Device"));
	types.push_back(OSELib::DPWS::QName("http://message-model-uri/15/04", "MedicalDevice"));
	types.push_back(OSELib::DPWS::QName("http://www.draeger.com/projects/DSC/CMDM/2012/05", "MedicalDevice"));

	_dpwsHost = std::unique_ptr<OSELib::DPWS::DPWSHost>(new OSELib::DPWS::DPWSHost(
			OSELib::DPWS::AddressType(_provider.getEndpointReference()),
			OSELib::DPWS::ScopesType(),
			types,
			xAddresses));

	const std::vector<xml_schema::Uri> allowedSubscriptionEventActions {
				OSELib::OSCP::EpisodicAlertReportTraits::Action(),
				OSELib::OSCP::EpisodicContextChangedReportTraits::Action(),
				OSELib::OSCP::EpisodicMetricReportTraits::Action(),
				OSELib::OSCP::OperationInvokedReportTraits::Action(),
				OSELib::OSCP::PeriodicAlertReportTraits::Action(),
				OSELib::OSCP::PeriodicContextChangedReportTraits::Action(),
				OSELib::OSCP::PeriodicMetricReportTraits::Action() };
	_subscriptionManager = std::unique_ptr<OSELib::DPWS::SubscriptionManager>(new OSELib::DPWS::SubscriptionManager(allowedSubscriptionEventActions));

	class Factory : public OSELib::HTTP::FrontControllerAdapter {
	public:
		Factory(OSCPProvider & provider,
				const OSELib::DPWS::MetadataProvider & metadata,
				OSELib::DPWS::DPWSHost & dpwsHost,
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

void OSELibProviderAdapter::stop() {

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

void OSELibProviderAdapter::notifyEvent(const CDM::EpisodicAlertReport & report) {
	Poco::Mutex::ScopedLock lock(mutex);
	if (_subscriptionManager) {
		_subscriptionManager->fireEvent<OSELib::OSCP::EpisodicAlertReportTraits>(report);
	}
}

void OSELibProviderAdapter::notifyEvent(const CDM::EpisodicContextChangedReport & report) {
	Poco::Mutex::ScopedLock lock(mutex);
	if (_subscriptionManager) {
		_subscriptionManager->fireEvent<OSELib::OSCP::EpisodicContextChangedReportTraits>(report);
	}
}

void OSELibProviderAdapter::notifyEvent(const CDM::EpisodicMetricReport & report) {
	Poco::Mutex::ScopedLock lock(mutex);
	if (_subscriptionManager) {
		_subscriptionManager->fireEvent<OSELib::OSCP::EpisodicMetricReportTraits>(report);
	}
}

void OSELibProviderAdapter::notifyEvent(const CDM::PeriodicAlertReport & report) {
	Poco::Mutex::ScopedLock lock(mutex);
	if (_subscriptionManager) {
		_subscriptionManager->fireEvent<OSELib::OSCP::PeriodicAlertReportTraits>(report);
	}
}

void OSELibProviderAdapter::notifyEvent(const CDM::PeriodicContextChangedReport & report) {
	Poco::Mutex::ScopedLock lock(mutex);
	if (_subscriptionManager) {
		_subscriptionManager->fireEvent<OSELib::OSCP::PeriodicContextChangedReportTraits>(report);
	}
}

void OSELibProviderAdapter::notifyEvent(const CDM::PeriodicMetricReport & report) {
	Poco::Mutex::ScopedLock lock(mutex);
	if (_subscriptionManager) {
		_subscriptionManager->fireEvent<OSELib::OSCP::PeriodicMetricReportTraits>(report);
	}
}

void OSELibProviderAdapter::notifyEvent(const CDM::OperationInvokedReport & report) {
	Poco::Mutex::ScopedLock lock(mutex);
	if (_subscriptionManager) {
		_subscriptionManager->fireEvent<OSELib::OSCP::OperationInvokedReportTraits>(report);
	}
}

void OSELibProviderAdapter::notifyEvent(const CDM::WaveformStream & stream, int port) {
	// TODO: implement
}

void OSELibProviderAdapter::addStreamingPort(const int port) {
	streamingPorts.insert(port);
}

void OSELibProviderAdapter::removeStreamingPort(const int port) {
	streamingPorts.erase(port);
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
