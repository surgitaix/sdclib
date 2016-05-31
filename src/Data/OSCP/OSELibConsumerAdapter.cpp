/*
 * OSELibConsumerAdapter.cpp
 *
 *  Created on: 10.12.2015
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
#include "eventing.hxx"
#include "NormalizedMessageModel.hxx"
#include "ws-addressing.hxx"

#include "OSCLib/OSCLibrary.h"

#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/OperationInvocationContext.h"
#include "OSCLib/Data/OSCP/MDIB/AlertConditionState.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSignalState.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSystemState.h"
#include "OSCLib/Data/OSCP/MDIB/EnumStringMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/LimitAlertConditionState.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/StringMetricState.h"
#include "OSCLib/Data/OSCP/OSCPConsumer.h"
#include "OSCLib/Data/OSCP/OSELibConsumerAdapter.h"

#include "OSELib/DPWS/PingManager.h"
#include "OSELib/DPWS/SubscriptionClient.h"
#include "OSELib/Helper/WithLogger.h"
#include "OSELib/HTTP/FrontControllerAdapter.h"
#include "OSELib/OSCP/ContextEventSinkHandler.h"
#include "OSELib/OSCP/EventReportEventSinkHandler.h"
#include "OSELib/OSCP/IContextServiceEventSink.h"
#include "OSELib/OSCP/IEventReportEventSink.h"
#include "OSELib/OSCP/OperationTraits.h"
#include "OSELib/OSCP/OSCPConstants.h"
#include "OSELib/OSCP/OSCPEventServiceController.h"
#include "OSELib/OSCP/ReportTraits.h"
#include "OSELib/SOAP/GenericSoapInvoke.h"

namespace OSELib {

using ContextServiceEventSinkController = OSCP::OSCPEventServiceController<OSCP::IContextServiceEventSink , OSCP::ContextEventSinkHandler>;
using EventReportEventSinkController = OSCP::OSCPEventServiceController<OSCP::IEventReportEventSink, OSCP::EventReportEventSinkHandler>;

struct ContextServiceEventSink : public OSCP::IContextServiceEventSink {
	ContextServiceEventSink(OSCLib::Data::OSCP::OSCPConsumer & consumer) :
		_consumer(consumer)
	{
	}

	virtual std::string getBaseUri() const override {
		return "/ContextReportSink";
	}

	virtual void dispatch(const OSCP::EpisodicContextChangedReportTraits::ReportType & report) override {
		_consumer.updateLastKnownMDIBVersion(report.MDIBVersion());
		std::vector<std::string> changedStatesHandles;

		for (const auto & reportPart: report.ReportPart()) {
			if (const auto part = dynamic_cast<const CDM::ContextChangedReportPart *>(&reportPart)) {
				for (const auto & handle : part->ChangedContextState()) {
					changedStatesHandles.push_back(handle);
				}
			}
		}

		_consumer.onContextStateChanged(changedStatesHandles);
	}

	virtual void dispatch(const OSCP::PeriodicContextChangedReportTraits::ReportType & report) override {
		_consumer.updateLastKnownMDIBVersion(report.MDIBVersion());
		std::vector<std::string> changedStatesHandles;

		for (const auto & reportPart: report.ReportPart()) {
			if (const auto part = dynamic_cast<const CDM::ContextChangedReportPart *>(&reportPart)) {
				for (const auto & handle : part->ChangedContextState()) {
					changedStatesHandles.push_back(handle);
				}
			}
		}

		_consumer.onContextStateChanged(changedStatesHandles);
	}

private:
	OSCLib::Data::OSCP::OSCPConsumer & _consumer;
};

struct EventReportEventSink : public OSCP::IEventReportEventSink, public OSELib::WithLogger {
	EventReportEventSink(OSCLib::Data::OSCP::OSCPConsumer & consumer) :
		WithLogger(Log::EVENTSINK),
		_consumer(consumer)
	{
	}

	virtual std::string getBaseUri() const override {
		return "/EventReportSink";
	}

	virtual void dispatch(const OSCP::EpisodicAlertReportTraits::ReportType & report) override {
		_consumer.updateLastKnownMDIBVersion(report.MDIBVersion());
		for (const auto & reportPart : report.AlertReportDetail()) {
			for (const auto & state : reportPart.AlertState()) {
				dispatchAlertState(state);
			}
		}
	}

	virtual void dispatch(const OSCP::EpisodicMetricReportTraits::ReportType & report) override {
		_consumer.updateLastKnownMDIBVersion(report.MDIBVersion());
		for (const auto & reportPart : report.ReportPart()) {
			for (const auto & state : reportPart.MetricState()) {
				dispatchMetricState(state);
			}
		}
	}

	virtual void dispatch(const OSCP::PeriodicAlertReportTraits::ReportType & report) override {
		_consumer.updateLastKnownMDIBVersion(report.MDIBVersion());
		for (const auto & reportPart : report.AlertReportDetail()) {
			for (const auto & state : reportPart.AlertState()) {
				dispatchAlertState(state);
			}
		}
	}

	virtual void dispatch(const OSCP::PeriodicMetricReportTraits::ReportType & report) override {
		_consumer.updateLastKnownMDIBVersion(report.MDIBVersion());
		for (const auto & reportPart : report.ReportPart()) {
			for (const auto & state : reportPart.MetricState()) {
				dispatchMetricState(state);
			}
		}
	}

	virtual void dispatch(const OSCP::OperationInvokedReportTraits::ReportType & report) override {
		// fixme move all to OSCPConsumer and change interface, so this method here only delegates. This should be done for all events
		_consumer.updateLastKnownMDIBVersion(report.MDIBVersion());
		for (const auto & irp : report.ReportDetail()) {
			_consumer.onOperationInvoked(
				OSCLib::Data::OSCP::OperationInvocationContext(irp.OperationHandleRef(), irp.TransactionId()),
				OSCLib::Data::OSCP::ConvertFromCDM::convert(irp.OperationState()));
		}
	}

	virtual void dispatch(const OSCP::WaveformStreamTraits::ReportType & report) override {
		// NOOP
	}

private:

	void dispatchAlertState(const CDM::AbstractAlertState & alertState) {
		if (const auto state = dynamic_cast<const CDM::AlertSystemState *>(&alertState)) {
			_consumer.onStateChanged(OSCLib::Data::OSCP::ConvertFromCDM::convert(*state));
			return;
		}
		if (const auto state = dynamic_cast<const CDM::AlertSignalState *>(&alertState)) {
			_consumer.onStateChanged(OSCLib::Data::OSCP::ConvertFromCDM::convert(*state));
			return;
		}
		if (const auto state = dynamic_cast<const CDM::LimitAlertConditionState *>(&alertState)) {
			_consumer.onStateChanged(OSCLib::Data::OSCP::ConvertFromCDM::convert(*state));
			return;
		}
		// the order does matter here, because AlertConditionState is the parent class of LimitAlertConditionState
		if (const auto state = dynamic_cast<const CDM::AlertConditionState *>(&alertState)) {
			_consumer.onStateChanged(OSCLib::Data::OSCP::ConvertFromCDM::convert(*state));
			return;
		}
		log_error([&] { return "Unknown alert state type, event will not be forwarded to handler!"; });
	}

	void dispatchMetricState(const CDM::AbstractMetricState & metricState) {
		if (const auto state = dynamic_cast<const CDM::EnumStringMetricState *>(&metricState)) {
			_consumer.onStateChanged(OSCLib::Data::OSCP::ConvertFromCDM::convert(*state));
			return;
		}
		if (const auto state = dynamic_cast<const CDM::NumericMetricState *>(&metricState)) {
			_consumer.onStateChanged(OSCLib::Data::OSCP::ConvertFromCDM::convert(*state));
			return;
		}
		if (const auto state = dynamic_cast<const CDM::StringMetricState *>(&metricState)) {
			_consumer.onStateChanged(OSCLib::Data::OSCP::ConvertFromCDM::convert(*state));
			return;
		}
		if (const auto state = dynamic_cast<const CDM::RealTimeSampleArrayMetricState *>(&metricState)) {
			_consumer.onStateChanged(OSCLib::Data::OSCP::ConvertFromCDM::convert(*state));
			return;
		}
		log_error([&] { return "Unknown metric state type, event will not be forwarded to handler!"; });
	}

	OSCLib::Data::OSCP::OSCPConsumer & _consumer;
};

}

namespace OSCLib {
namespace Data {
namespace OSCP {

OSELibConsumerAdapter::OSELibConsumerAdapter(OSCPConsumer & consumer, const unsigned int port, const OSELib::DPWS::DeviceDescription & deviceDescription) :
	_consumer(consumer),
	_threadPool(new Poco::ThreadPool()),
	_port(port),
	_deviceDescription(deviceDescription)
{
}

OSELibConsumerAdapter::~OSELibConsumerAdapter() {
}

void OSELibConsumerAdapter::start() {
	Poco::Mutex::ScopedLock lock(mutex);
	if (_httpServer) {
		return;
		//todo maybe throw because starting twice is clearly an error
	}

	Poco::Net::ServerSocket ss;
	const Poco::Net::IPAddress address(Poco::Net::IPAddress::Family::IPv4);
	const Poco::Net::SocketAddress socketAddress(address, _port);
	ss.bind(socketAddress);
	ss.listen();

	class Factory : public OSELib::HTTP::FrontControllerAdapter {
	public:
		Factory(OSCPConsumer & consumer) :
			FrontControllerAdapter(_frontController),
			contextServiceEventSink(consumer),
			eventReportEventSink(consumer),
			_contextServiceEventSinkService(_frontController, contextServiceEventSink),
			_eventReportEventSinkService(_frontController, eventReportEventSink)
		{
		}

		virtual ~Factory() = default;

	private:
		OSELib::HTTP::FrontController _frontController;

		OSELib::ContextServiceEventSink contextServiceEventSink;
		OSELib::EventReportEventSink eventReportEventSink;

		OSELib::ContextServiceEventSinkController _contextServiceEventSinkService;
		OSELib::EventReportEventSinkController _eventReportEventSinkService;
	};

	_httpServer = std::unique_ptr<Poco::Net::HTTPServer>(new Poco::Net::HTTPServer(new Factory(_consumer), *_threadPool, ss,  new Poco::Net::HTTPServerParams));

	_httpServer->start();

	if (_pingManager) {
		//todo maybe throw because starting twice is clearly an error
		return;
	}

	_pingManager = std::unique_ptr<OSELib::DPWS::PingManager>(new OSELib::DPWS::PingManager(_consumer));
}

void OSELibConsumerAdapter::stop() {
	Poco::Mutex::ScopedLock lock(mutex);

	if (_httpServer) {
		_httpServer->stopAll(false);
	}

	while (_httpServer->currentConnections() != 0) {
		Poco::Thread::sleep(100);
	}

	_httpServer.reset();

	if (_pingManager) {
		_pingManager->disable();
		OSCLibrary::getInstance().dumpPingManager(std::move(_pingManager));
	}
}

void OSELibConsumerAdapter::subscribeEvents() {
	if (_subscriptionClient) {
		return;
	}

	std::vector<OSELib::DPWS::SubscriptionClient::SubscriptionInformation> subscriptions;
	{
		WS::EVENTING::FilterType filter;
		filter.push_back(OSELib::OSCP::EpisodicContextChangedReportTraits::Action());
		filter.push_back(OSELib::OSCP::PeriodicContextChangedReportTraits::Action());
		subscriptions.emplace_back(
				Poco::URI("http://" + _deviceDescription.getLocalIP().toString() + ":" + std::to_string(_port) + "/ContextReportSink"),
				_deviceDescription.getContextServiceURI(),
				filter);
	}
	{
		WS::EVENTING::FilterType filter;
		filter.push_back(OSELib::OSCP::EpisodicAlertReportTraits::Action());
		filter.push_back(OSELib::OSCP::EpisodicMetricReportTraits::Action());
		filter.push_back(OSELib::OSCP::PeriodicAlertReportTraits::Action());
		filter.push_back(OSELib::OSCP::PeriodicMetricReportTraits::Action());
		filter.push_back(OSELib::OSCP::OperationInvokedReportTraits::Action());
		subscriptions.emplace_back(
				Poco::URI("http://" + _deviceDescription.getLocalIP().toString() + ":" + std::to_string(_port) + "/EventReportSink"),
				_deviceDescription.getEventServiceURI(),
				filter);
	}

	_subscriptionClient = std::unique_ptr<OSELib::DPWS::SubscriptionClient>(new OSELib::DPWS::SubscriptionClient(subscriptions));
}

void OSELibConsumerAdapter::unsubscribeEvents() {
	if (_subscriptionClient) {
		_subscriptionClient.reset();
	}
}

template<class TraitsType>
std::unique_ptr<typename TraitsType::Response> OSELibConsumerAdapter::invokeImplWithEventSubscription(const typename TraitsType::Request & request, const Poco::URI & requestURI) {
	// We need to receive operation invoked events, so we do kind of emergency subscriptions here
	subscribeEvents();
	return invokeImpl<TraitsType>(request, requestURI);
}

template<class TraitsType>
std::unique_ptr<typename TraitsType::Response> OSELibConsumerAdapter::invokeImpl(const typename TraitsType::Request & request, const Poco::URI & requestURI) {

	using Invoker = OSELib::SOAP::GenericSoapInvoke<TraitsType>;
	std::unique_ptr<Invoker> invoker(new Invoker(requestURI, _grammarProvider));

	auto response(invoker->invoke(request));

	if (response != nullptr) {
		_consumer.updateLastKnownMDIBVersion(response->MDIBVersion());
		return std::move(response);
	}

	return nullptr;
}

template<>
Poco::URI OSELibConsumerAdapter::getRequestURIFromDeviceDescription(const OSELib::OSCP::GetMDDescriptionTraits::Request & ) {
	return _deviceDescription.getGetServiceURI();
}

template<>
Poco::URI OSELibConsumerAdapter::getRequestURIFromDeviceDescription(const OSELib::OSCP::GetMDIBTraits::Request & ) {
	return _deviceDescription.getGetServiceURI();
}

template<>
Poco::URI OSELibConsumerAdapter::getRequestURIFromDeviceDescription(const OSELib::OSCP::GetMDStateTraits::Request & ) {
	return _deviceDescription.getGetServiceURI();
}

template<>
Poco::URI OSELibConsumerAdapter::getRequestURIFromDeviceDescription(const OSELib::OSCP::ActivateTraits::Request & ) {
	return _deviceDescription.getSetServiceURI();
}

template<>
Poco::URI OSELibConsumerAdapter::getRequestURIFromDeviceDescription(const OSELib::OSCP::SetAlertStateTraits::Request & ) {
	return _deviceDescription.getSetServiceURI();
}

template<>
Poco::URI OSELibConsumerAdapter::getRequestURIFromDeviceDescription(const OSELib::OSCP::SetStringTraits::Request & ) {
	return _deviceDescription.getSetServiceURI();
}

template<>
Poco::URI OSELibConsumerAdapter::getRequestURIFromDeviceDescription(const OSELib::OSCP::SetValueTraits::Request & ) {
	return _deviceDescription.getSetServiceURI();
}

template<>
Poco::URI OSELibConsumerAdapter::getRequestURIFromDeviceDescription(const OSELib::OSCP::SetContextStateTraits::Request & ) {
	return _deviceDescription.getContextServiceURI();
}

std::unique_ptr<CDM::GetMDDescriptionResponse> OSELibConsumerAdapter::invoke(const CDM::GetMDDescription & request) {
	return invokeImpl<OSELib::OSCP::GetMDDescriptionTraits>(request, getRequestURIFromDeviceDescription(request));
}

std::unique_ptr<CDM::GetMDIBResponse> OSELibConsumerAdapter::invoke(const CDM::GetMDIB & request) {
	return invokeImpl<OSELib::OSCP::GetMDIBTraits>(request, getRequestURIFromDeviceDescription(request));
}

std::unique_ptr<CDM::GetMDStateResponse> OSELibConsumerAdapter::invoke(const CDM::GetMDState & request) {
	return invokeImpl<OSELib::OSCP::GetMDStateTraits>(request, getRequestURIFromDeviceDescription(request));
}


std::unique_ptr<CDM::ActivateResponse> OSELibConsumerAdapter::invoke(const CDM::Activate & request) {
	return invokeImplWithEventSubscription<OSELib::OSCP::ActivateTraits>(request, getRequestURIFromDeviceDescription(request));
}

std::unique_ptr<CDM::SetAlertStateResponse> OSELibConsumerAdapter::invoke(const CDM::SetAlertState & request) {
	return invokeImplWithEventSubscription<OSELib::OSCP::SetAlertStateTraits>(request, getRequestURIFromDeviceDescription(request));
}

std::unique_ptr<CDM::SetValueResponse> OSELibConsumerAdapter::invoke(const CDM::SetValue & request) {
	return invokeImplWithEventSubscription<OSELib::OSCP::SetValueTraits>(request, getRequestURIFromDeviceDescription(request));
}

std::unique_ptr<CDM::SetStringResponse> OSELibConsumerAdapter::invoke(const CDM::SetString & request) {
	return invokeImplWithEventSubscription<OSELib::OSCP::SetStringTraits>(request, getRequestURIFromDeviceDescription(request));
}


std::unique_ptr<CDM::SetContextStateResponse> OSELibConsumerAdapter::invoke(const CDM::SetContextState & request) {
	return invokeImplWithEventSubscription<OSELib::OSCP::SetContextStateTraits>(request, getRequestURIFromDeviceDescription(request));
}

}
}
} /* namespace OSELib */
