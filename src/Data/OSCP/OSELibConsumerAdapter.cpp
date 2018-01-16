/*
 * OSELibConsumerAdapter.cpp
 *
 *  Created on: 10.12.2015
 *      Author: matthias
 */

#include <iostream>
#include <list>

#include "Poco/Mutex.h"
#include "Poco/ThreadPool.h"
#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/NetworkInterface.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/MulticastSocket.h"

#include "BICEPS_ParticipantModel.hxx"
#include "BICEPS_MessageModel.hxx"
#include "eventing.hxx"
#include "NormalizedMessageModel.hxx"
#include "ws-addressing.hxx"

#include "OSCLib/OSCLibrary.h"

#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/AlertConditionState.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSignalState.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSystemState.h"
#include "OSCLib/Data/OSCP/MDIB/EnumStringMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/LimitAlertConditionState.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/StringMetricState.h"

#include "OSCLib/Data/OSCP/MDIB/LocationContextState.h"
#include "OSCLib/Data/OSCP/MDIB/PatientContextState.h"
#include "OSCLib/Data/OSCP/MDIB/WorkflowContextState.h"
#include "OSCLib/Data/OSCP/MDIB/MeansContextState.h"
#include "OSCLib/Data/OSCP/MDIB/OperatorContextState.h"
#include "OSCLib/Data/OSCP/MDIB/EnsembleContextState.h"

#include "OSCLib/Data/OSCP/OSCPConsumer.h"
#include "OSCLib/Data/OSCP/MDIB/custom/OperationInvocationContext.h"
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

struct ContextServiceEventSink : public OSCP::IContextServiceEventSink, public OSELib::WithLogger  {
	ContextServiceEventSink(OSCLib::Data::OSCP::OSCPConsumer & consumer) :
		WithLogger(OSELib::Log::EVENTSINK),
		_consumer(consumer)
	{
	}

	virtual std::string getBaseUri() const override {
		return "/ContextReportSink";
	}
	// FIXME!!:
	// FIXME!!: edit this contex dispacher as well! -> put together as a template
	virtual void dispatch(const OSCP::EpisodicContextChangedReportTraits::ReportType & report) override {

		if (report.MdibVersion().present()) {
			_consumer.updateLastKnownMdibVersion(report.MdibVersion().get());
		}

		for (const auto & reportPart: report.ReportPart()) {
			// get the part of the report, that is defined by the message model
			if (const auto part = dynamic_cast<const MDM::ReportPart *>(&reportPart)) {
				// get all ContextStates. ContextStates are all states inheriting from AbstractContextState
				for (const auto & contextState : part->ContextState()) {
					// cast to right inherited type and call the regarding method of the consumer
					if (const auto state = dynamic_cast<const CDM::LocationContextState *>(&contextState)) {
						// dispach to multi state callback
						_consumer.onMultiStateChanged(OSCLib::Data::OSCP::ConvertFromCDM::convert(*state));
						// dispach to state callback referenced by the multistate descriptor
						_consumer.onStateChanged(OSCLib::Data::OSCP::ConvertFromCDM::convert(*state));
						continue;
					}
					if (const auto state = dynamic_cast<const CDM::PatientContextState *>(&contextState)) {
						// dispach to multi state callback
						_consumer.onMultiStateChanged(OSCLib::Data::OSCP::ConvertFromCDM::convert(*state));
						// dispach to state callback referenced by the multistate descriptor
						_consumer.onStateChanged(OSCLib::Data::OSCP::ConvertFromCDM::convert(*state));
						continue;
					}
					if (const auto state = dynamic_cast<const CDM::WorkflowContextState *>(&contextState)) {
						// dispach to multi state callback
						_consumer.onMultiStateChanged(OSCLib::Data::OSCP::ConvertFromCDM::convert(*state));
						// dispach to state callback referenced by the multistate descriptor
						_consumer.onStateChanged(OSCLib::Data::OSCP::ConvertFromCDM::convert(*state));
						continue;
					}
					if (const auto state = dynamic_cast<const CDM::EnsembleContextState *>(&contextState)) {
						// dispach to multi state callback
						_consumer.onMultiStateChanged(OSCLib::Data::OSCP::ConvertFromCDM::convert(*state));
						// dispach to state callback referenced by the multistate descriptor
						_consumer.onStateChanged(OSCLib::Data::OSCP::ConvertFromCDM::convert(*state));
						continue;
					}
					if (const auto state = dynamic_cast<const CDM::OperatorContextState *>(&contextState)) {
						// dispach to multi state callback
						_consumer.onMultiStateChanged(OSCLib::Data::OSCP::ConvertFromCDM::convert(*state));
						// dispach to state callback referenced by the multistate descriptor
						_consumer.onStateChanged(OSCLib::Data::OSCP::ConvertFromCDM::convert(*state));
						continue;
					}
					if (const auto state = dynamic_cast<const CDM::MeansContextState *>(&contextState)) {
						// dispach to multi state callback
						_consumer.onMultiStateChanged(OSCLib::Data::OSCP::ConvertFromCDM::convert(*state));
						// dispach to state callback referenced by the multistate descriptor
						_consumer.onStateChanged(OSCLib::Data::OSCP::ConvertFromCDM::convert(*state));
						continue;
					}
					log_error([&] { return "Unknown context state type, event will not be forwarded to handler!"; });
				}
			}
		}
	}


	// FIXME: combine with above

	virtual void dispatch(const OSCP::PeriodicContextChangedReportTraits::ReportType & report) override {
		if (report.MdibVersion().present()) {
			_consumer.updateLastKnownMdibVersion(report.MdibVersion().get());
		}

		for (const auto & reportPart: report.ReportPart()) {
			// get the part of the report, that is defined by the message model
			if (const auto part = dynamic_cast<const MDM::ReportPart *>(&reportPart)) {
				// get all ContextStates. ContextStates are all states inheriting from AbstractContextState
				for (const auto & contextState : part->ContextState()) {
					// cast to right inherited type and call the regarding method of the consumer
					if (const auto state = dynamic_cast<const CDM::LocationContextState *>(&contextState)) {
						_consumer.onMultiStateChanged(OSCLib::Data::OSCP::ConvertFromCDM::convert(*state));
						continue;
					}
					if (const auto state = dynamic_cast<const CDM::PatientContextState *>(&contextState)) {
						_consumer.onMultiStateChanged(OSCLib::Data::OSCP::ConvertFromCDM::convert(*state));
						continue;
					}
					if (const auto state = dynamic_cast<const CDM::WorkflowContextState *>(&contextState)) {
						_consumer.onMultiStateChanged(OSCLib::Data::OSCP::ConvertFromCDM::convert(*state));
						continue;
					}
					if (const auto state = dynamic_cast<const CDM::EnsembleContextState *>(&contextState)) {
						_consumer.onMultiStateChanged(OSCLib::Data::OSCP::ConvertFromCDM::convert(*state));
						continue;
					}
					if (const auto state = dynamic_cast<const CDM::OperatorContextState *>(&contextState)) {
						_consumer.onMultiStateChanged(OSCLib::Data::OSCP::ConvertFromCDM::convert(*state));
						continue;
					}
					if (const auto state = dynamic_cast<const CDM::MeansContextState *>(&contextState)) {
						_consumer.onMultiStateChanged(OSCLib::Data::OSCP::ConvertFromCDM::convert(*state));
						continue;
					}
					log_error([&] { return "Unknown context state type, event will not be forwarded to handler!"; });
				}
			}
		}
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

	// Todo!!!!
	// Todo!!!!
	// Todo!!!!
	// Todo!!!!
	// continue here!!!!!
// alert dispaching does not work properly!


	virtual void dispatch(const OSCP::EpisodicAlertReportTraits::ReportType & report) override {
		if (report.MdibVersion().present()) {
			_consumer.updateLastKnownMdibVersion(report.MdibVersion().get());
		}
		for (const auto & reportPart : report.ReportPart()) {
			for (const auto & state : reportPart.AlertState()) {
				dispatchAlertState(state);
			}
		}
	}

	virtual void dispatch(const OSCP::EpisodicMetricReportTraits::ReportType & report) override {
		if (report.MdibVersion().present()) {
			_consumer.updateLastKnownMdibVersion(report.MdibVersion().get());
		}
		for (const auto & reportPart : report.ReportPart()) {
			for (const auto & state : reportPart.MetricState()) {
				dispatchMetricState(state);
			}
		}
	}

	virtual void dispatch(const OSCP::PeriodicAlertReportTraits::ReportType & report) override {
		if (report.MdibVersion().present()) {
			_consumer.updateLastKnownMdibVersion(report.MdibVersion().get());
		}
		for (const auto & reportPart : report.ReportPart()) {
			for (const auto & state : reportPart.AlertState()) {
				dispatchAlertState(state);
			}
		}
	}

	virtual void dispatch(const OSCP::PeriodicMetricReportTraits::ReportType & report) override {
		if (report.MdibVersion().present()) {
			_consumer.updateLastKnownMdibVersion(report.MdibVersion().get());
		}
		for (const auto & reportPart : report.ReportPart()) {
			for (const auto & state : reportPart.MetricState()) {
				dispatchMetricState(state);
			}
		}
	}

	virtual void dispatch(const OSCP::OperationInvokedReportTraits::ReportType & report) override {
		// fixme move all to OSCPConsumer and change interface, so this method here only delegates. This should be done for all events
		if (report.MdibVersion().present()) {
			_consumer.updateLastKnownMdibVersion(report.MdibVersion().get());
		}
		for (const auto & irp : report.ReportPart()) {
			_consumer.onOperationInvoked(
				OSCLib::Data::OSCP::OperationInvocationContext(irp.OperationHandleRef(), irp.InvocationInfo().TransactionId()),
				OSCLib::Data::OSCP::ConvertFromCDM::convert(irp.InvocationInfo().InvocationState()));
		}
	}

	// todo: more elegant implementation of streaming possible?
	virtual void dispatch(const OSCP::WaveformStreamTraits::ReportType & report) override {
		//
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
			return; //todo: !!!!!!!!!!s distribution state type
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
	_deviceDescription(deviceDescription),
	_streamClientSocketImpl(*this, deviceDescription),
	WithLogger(OSELib::Log::OSCPCONSUMERADAPTER)
{
}

OSELibConsumerAdapter::~OSELibConsumerAdapter() {
}

void OSELibConsumerAdapter::start() {
	Poco::Mutex::ScopedLock lock(mutex);
	if (_httpServer) {
		throw std::runtime_error("An http-Server is already running.");
	}

	Poco::Net::ServerSocket ss;
	// todo: IPv6 implementation
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
		if (response->MdibVersion().present()) {
			_consumer.updateLastKnownMdibVersion(response->MdibVersion().get());
		}
		return std::move(response);
	}

	return nullptr;
}

void OSELibConsumerAdapter::dispatch(const OSELib::DPWS::WaveformStreamType & notification) {
	_consumer.onStateChanged(OSCLib::Data::OSCP::ConvertFromCDM::convert(notification.State().front()));
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
Poco::URI OSELibConsumerAdapter::getRequestURIFromDeviceDescription(const OSELib::OSCP::GetMdStateTraits::Request & ) {
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

std::unique_ptr<MDM::GetMdDescriptionResponse> OSELibConsumerAdapter::invoke(const MDM::GetMdDescription & request) {
	return invokeImpl<OSELib::OSCP::GetMDDescriptionTraits>(request, getRequestURIFromDeviceDescription(request));
}

std::unique_ptr<MDM::GetMdibResponse> OSELibConsumerAdapter::invoke(const MDM::GetMdib & request) {
	return invokeImpl<OSELib::OSCP::GetMDIBTraits>(request, getRequestURIFromDeviceDescription(request));
}

std::unique_ptr<MDM::GetMdStateResponse> OSELibConsumerAdapter::invoke(const MDM::GetMdState & request) {
	return invokeImpl<OSELib::OSCP::GetMdStateTraits>(request, getRequestURIFromDeviceDescription(request));
}


std::unique_ptr<MDM::ActivateResponse> OSELibConsumerAdapter::invoke(const MDM::Activate & request) {
	return invokeImplWithEventSubscription<OSELib::OSCP::ActivateTraits>(request, getRequestURIFromDeviceDescription(request));
}

std::unique_ptr<MDM::SetAlertStateResponse> OSELibConsumerAdapter::invoke(const MDM::SetAlertState & request) {
	return invokeImplWithEventSubscription<OSELib::OSCP::SetAlertStateTraits>(request, getRequestURIFromDeviceDescription(request));
}

std::unique_ptr<MDM::SetValueResponse> OSELibConsumerAdapter::invoke(const MDM::SetValue & request) {
	return invokeImplWithEventSubscription<OSELib::OSCP::SetValueTraits>(request, getRequestURIFromDeviceDescription(request));
}

std::unique_ptr<MDM::SetStringResponse> OSELibConsumerAdapter::invoke(const MDM::SetString & request) {
	return invokeImplWithEventSubscription<OSELib::OSCP::SetStringTraits>(request, getRequestURIFromDeviceDescription(request));
}


std::unique_ptr<MDM::SetContextStateResponse> OSELibConsumerAdapter::invoke(const MDM::SetContextState & request) {
	return invokeImplWithEventSubscription<OSELib::OSCP::SetContextStateTraits>(request, getRequestURIFromDeviceDescription(request));
}

}
}
} /* namespace OSELib */
