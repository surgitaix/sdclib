/*
 * SDCConsumerAdapter.cpp
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

#include "OSCLib/SDCInstance.h"

#include "OSCLib/Data/SDC/MDIB/ConvertFromCDM.h"

#include "OSCLib/Data/SDC/MDIB/AlertConditionState.h"
#include "OSCLib/Data/SDC/MDIB/AlertSignalState.h"
#include "OSCLib/Data/SDC/MDIB/AlertSystemState.h"
#include "OSCLib/Data/SDC/MDIB/DistributionSampleArrayMetricState.h"
#include "OSCLib/Data/SDC/MDIB/EnumStringMetricState.h"
#include "OSCLib/Data/SDC/MDIB/LimitAlertConditionState.h"
#include "OSCLib/Data/SDC/MDIB/NumericMetricState.h"
#include "OSCLib/Data/SDC/MDIB/RealTimeSampleArrayMetricState.h"
#include "OSCLib/Data/SDC/MDIB/StringMetricState.h"

#include "OSCLib/Data/SDC/MDIB/LocationContextState.h"
#include "OSCLib/Data/SDC/MDIB/PatientContextState.h"
#include "OSCLib/Data/SDC/MDIB/WorkflowContextState.h"
#include "OSCLib/Data/SDC/MDIB/MeansContextState.h"
#include "OSCLib/Data/SDC/MDIB/OperatorContextState.h"
#include "OSCLib/Data/SDC/MDIB/EnsembleContextState.h"

#include "OSCLib/Data/SDC/SDCConsumer.h"
#include "OSCLib/Data/SDC/MDIB/custom/OperationInvocationContext.h"
#include "OSCLib/Data/SDC/SDCConsumerAdapter.h"
#include "OSCLib/Data/SDC/MDPWSTransportLayerConfiguration.h"

#include "OSELib/DPWS/PingManager.h"
#include "OSELib/DPWS/SubscriptionClient.h"
#include "OSELib/Helper/WithLogger.h"
#include "OSELib/HTTP/FrontControllerAdapter.h"
#include "OSELib/SDC/ContextEventSinkHandler.h"
#include "OSELib/SDC/EventReportEventSinkHandler.h"
#include "OSELib/SDC/IContextServiceEventSink.h"
#include "OSELib/SDC/IEventReportEventSink.h"
#include "OSELib/SDC/OperationTraits.h"
#include "OSELib/SDC/SDCConstants.h"
#include "OSELib/SDC/SDCEventServiceController.h"
#include "OSELib/SDC/ReportTraits.h"
#include "OSELib/SOAP/GenericSoapInvoke.h"

namespace OSELib {

using ContextServiceEventSinkController = SDC::SDCEventServiceController<SDC::IContextServiceEventSink , SDC::ContextEventSinkHandler>;
using EventReportEventSinkController = SDC::SDCEventServiceController<SDC::IEventReportEventSink, SDC::EventReportEventSinkHandler>;

struct ContextServiceEventSink : public SDC::IContextServiceEventSink, public OSELib::WithLogger  {
	ContextServiceEventSink(SDCLib::Data::SDC::SDCConsumer & consumer) :
		WithLogger(OSELib::Log::EVENTSINK),
		_consumer(consumer)
	{
	}

	virtual std::string getBaseUri() const override {
		return "/ContextReportSink";
	}

	// todo: fix multistate implementation. this one only calls the state handlers which reference the descriptorsHandles
	// when a state with a defined handle updated also the state with the regarding descriptor Handle is called.
	// this is not right.

	// casts to right inherited type and call the regarding method of the consumer
	void delegateContextState(const CDM::AbstractContextState &contextState) {
		if (const auto state = dynamic_cast<const CDM::LocationContextState *>(&contextState)) {
			// dispatch to multi state callback
//			_consumer.onMultiStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(*state));
			// dispatch to state callback referenced by the multistate descriptor
			_consumer.onStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(*state));
			return;
		}
		if (const auto state = dynamic_cast<const CDM::PatientContextState *>(&contextState)) {
			// dispatch to multi state callback
//			_consumer.onMultiStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(*state));
			// dispatch to state callback referenced by the multistate descriptor
			_consumer.onStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(*state));
			return;
		}
		if (const auto state = dynamic_cast<const CDM::WorkflowContextState *>(&contextState)) {
			// dispatch to multi state callback
//			_consumer.onMultiStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(*state));
			// dispatch to state callback referenced by the multistate descriptor
			_consumer.onStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(*state));
			return;
		}
		if (const auto state = dynamic_cast<const CDM::EnsembleContextState *>(&contextState)) {
			// dispatch to multi state callback
//			_consumer.onMultiStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(*state));
			// dispatch to state callback referenced by the multistate descriptor
			_consumer.onStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(*state));
			return;
		}
		if (const auto state = dynamic_cast<const CDM::OperatorContextState *>(&contextState)) {
			// dispatch to multi state callback
//			_consumer.onMultiStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(*state));
			// dispatch to state callback referenced by the multistate descriptor
			_consumer.onStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(*state));
			return;
		}
		if (const auto state = dynamic_cast<const CDM::MeansContextState *>(&contextState)) {
			// dispatch to multi state callback
//			_consumer.onMultiStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(*state));
			// dispatch to state callback referenced by the multistate descriptor
			_consumer.onStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(*state));
			return;
		}
		log_error([&] { return "Unknown context state type, event will not be forwarded to handler!"; });
	}


	// dispatch episodic reports and delegate the contained context states
	virtual void dispatch(const SDC::EpisodicContextChangedReportTraits::ReportType & report) override {

		if (report.MdibVersion().present()) {
			_consumer.updateLastKnownMdibVersion(report.MdibVersion().get());
		}

		for (const auto & reportPart: report.ReportPart()) {
			// get the part of the report, as defined by the message model
			if (const auto part = dynamic_cast<const MDM::ReportPart *>(&reportPart)) {
				// get all ContextStates. ContextStates are all states inheriting from AbstractContextState
				for (const auto & contextState : part->ContextState()) {
					delegateContextState(contextState);
				}
			}
		}
	}

	// dispatch periodic reports and delegate the contained context states
	virtual void dispatch(const SDC::PeriodicContextChangedReportTraits::ReportType & report) override {
		if (report.MdibVersion().present()) {
			_consumer.updateLastKnownMdibVersion(report.MdibVersion().get());
		}

		for (const auto & reportPart: report.ReportPart()) {
			// get the part of the report, that is defined by the message model
			if (const auto part = dynamic_cast<const MDM::ReportPart *>(&reportPart)) {
				// get all ContextStates. ContextStates are all states inheriting from AbstractContextState
				for (const auto & contextState : part->ContextState()) {
					delegateContextState(contextState);
				}
			}
		}
	}

private:
	SDCLib::Data::SDC::SDCConsumer & _consumer;
};

struct EventReportEventSink : public SDC::IEventReportEventSink, public OSELib::WithLogger {
	EventReportEventSink(SDCLib::Data::SDC::SDCConsumer & consumer) :
		WithLogger(Log::EVENTSINK),
		_consumer(consumer)
	{
	}

	virtual std::string getBaseUri() const override {
		return "/EventReportSink";
	}

	virtual void dispatch(const SDC::EpisodicAlertReportTraits::ReportType & report) override {
		if (report.MdibVersion().present()) {
			_consumer.updateLastKnownMdibVersion(report.MdibVersion().get());
		}
		for (const auto & reportPart : report.ReportPart()) {
			for (const auto & state : reportPart.AlertState()) {
				dispatchAlertState(state);
			}
		}
	}

	virtual void dispatch(const SDC::EpisodicMetricReportTraits::ReportType & report) override {
		if (report.MdibVersion().present()) {
			_consumer.updateLastKnownMdibVersion(report.MdibVersion().get());
		}
		for (const auto & reportPart : report.ReportPart()) {
			for (const auto & state : reportPart.MetricState()) {
				dispatchMetricState(state);
			}
		}
	}

	virtual void dispatch(const SDC::PeriodicAlertReportTraits::ReportType & report) override {
		if (report.MdibVersion().present()) {
			_consumer.updateLastKnownMdibVersion(report.MdibVersion().get());
		}
		for (const auto & reportPart : report.ReportPart()) {
			for (const auto & state : reportPart.AlertState()) {
				dispatchAlertState(state);
			}
		}
	}

	virtual void dispatch(const SDC::PeriodicMetricReportTraits::ReportType & report) override {
		if (report.MdibVersion().present()) {
			_consumer.updateLastKnownMdibVersion(report.MdibVersion().get());
		}
		for (const auto & reportPart : report.ReportPart()) {
			for (const auto & state : reportPart.MetricState()) {
				dispatchMetricState(state);
			}
		}
	}

	virtual void dispatch(const SDC::OperationInvokedReportTraits::ReportType & report) override {
		// fixme move all to SDCConsumer and change interface, so this method here only delegates. This should be done for all events
		if (report.MdibVersion().present()) {
			_consumer.updateLastKnownMdibVersion(report.MdibVersion().get());
		}
		for (const auto & irp : report.ReportPart()) {
			_consumer.onOperationInvoked(
				SDCLib::Data::SDC::OperationInvocationContext(irp.OperationHandleRef(), irp.InvocationInfo().TransactionId()),
				SDCLib::Data::SDC::ConvertFromCDM::convert(irp.InvocationInfo().InvocationState()));
		}
	}

	// todo: more elegant implementation of streaming possible?
	virtual void dispatch(const SDC::WaveformStreamTraits::ReportType&) override {
		//
	}

private:

	void dispatchAlertState(const CDM::AbstractAlertState & alertState) {
		if (const auto state = dynamic_cast<const CDM::AlertSystemState *>(&alertState)) {
			_consumer.onStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(*state));
			return;
		}
		if (const auto state = dynamic_cast<const CDM::AlertSignalState *>(&alertState)) {
			_consumer.onStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(*state));
			return;
		}
		if (const auto state = dynamic_cast<const CDM::LimitAlertConditionState *>(&alertState)) {
			_consumer.onStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(*state));
			return;
		}
		// the order does matter here, because AlertConditionState is the parent class of LimitAlertConditionState
		if (const auto state = dynamic_cast<const CDM::AlertConditionState *>(&alertState)) {
			_consumer.onStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(*state));
			return;
		}
		log_error([&] { return "Unknown alert state type, event will not be forwarded to handler!"; });
	}

	void dispatchMetricState(const CDM::AbstractMetricState & metricState) {
		if (const auto state = dynamic_cast<const CDM::EnumStringMetricState *>(&metricState)) {
			_consumer.onStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(*state));
			return;
		}
		if (const auto state = dynamic_cast<const CDM::NumericMetricState *>(&metricState)) {
			_consumer.onStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(*state));
			return;
		}
		if (const auto state = dynamic_cast<const CDM::StringMetricState *>(&metricState)) {
			_consumer.onStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(*state));
			return;
		}
		if (const auto state = dynamic_cast<const CDM::RealTimeSampleArrayMetricState *>(&metricState)) {
			_consumer.onStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(*state));
			return;
		}
		if (const auto state = dynamic_cast<const CDM::DistributionSampleArrayMetricState *>(&metricState)) {
			_consumer.onStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(*state));
			return;
		}

		log_error([&] { return "Unknown metric state type, event will not be forwarded to handler!"; });
	}

	SDCLib::Data::SDC::SDCConsumer & _consumer;
};

}

namespace SDCLib {
namespace Data {
namespace SDC {

SDCConsumerAdapter::SDCConsumerAdapter(SDCLib::SDCInstance_shared_ptr p_SDCInstance, SDCConsumer & consumer, const OSELib::DPWS::DeviceDescription & deviceDescription, const MDPWSTransportLayerConfiguration& config) :
	WithLogger(OSELib::Log::OSCPCONSUMERADAPTER),
	_consumer(consumer),
	_threadPool(new Poco::ThreadPool()),
	_deviceDescription(deviceDescription),
	_streamClientSocketImpl(p_SDCInstance, *this, deviceDescription),
	configuration(config)
{

}

SDCConsumerAdapter::~SDCConsumerAdapter() = default;

bool SDCConsumerAdapter::start() {
	Poco::Mutex::ScopedLock lock(mutex);
	if (_httpServer) {
		return false;
	}

	Poco::Net::ServerSocket ss;
	// todo: IPv6 implementation here!
	const Poco::Net::IPAddress address(configuration.getBindAddress());
	const Poco::Net::SocketAddress socketAddress(address, configuration.getPort());
	ss.bind(socketAddress);
	ss.listen();

	class Factory : public OSELib::HTTP::FrontControllerAdapter {
	public:
		Factory(SDCConsumer & consumer) :
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
        // FIXME FIXME FIXME:
        // (ERROR != THROWING) DONT USE EXCEPTIONS AS FLOW CONTROL AND DONT JUST THROW JUST BECAUSE YOU CAN... THIS IS NOT JAVA... USE assert, static_assert, logging etc.
		return false;
	}

	_pingManager = std::unique_ptr<OSELib::DPWS::PingManager>(new OSELib::DPWS::PingManager(_consumer));
    return true;
}


void SDCConsumerAdapter::stop() {
	Poco::Mutex::ScopedLock lock(mutex);

	if (_httpServer) {
		_httpServer->stopAll(false);
	}

	while (_httpServer->currentConnections() != 0) {
		Poco::Thread::sleep(100);
		_httpServer.reset();
	}


	if (_pingManager) {
		_pingManager->disable();
		configuration.getSDCInstance()->dumpPingManager(std::move(_pingManager));
	}
}

void SDCConsumerAdapter::subscribeEvents() {
	if (_subscriptionClient) {
		return;
	}

	std::vector<OSELib::DPWS::SubscriptionClient::SubscriptionInformation> subscriptions;
	{
		WS::EVENTING::FilterType filter;
		filter.push_back(OSELib::SDC::EpisodicContextChangedReportTraits::Action());
		filter.push_back(OSELib::SDC::PeriodicContextChangedReportTraits::Action());
		subscriptions.emplace_back(
				Poco::URI("http://" + _deviceDescription.getLocalIP().toString() + ":" + std::to_string(configuration.getPort()) + "/ContextReportSink"),
				_deviceDescription.getContextServiceURI(),
				filter);
	}
	{
		WS::EVENTING::FilterType filter;
		filter.push_back(OSELib::SDC::EpisodicAlertReportTraits::Action());
		filter.push_back(OSELib::SDC::EpisodicMetricReportTraits::Action());
		filter.push_back(OSELib::SDC::PeriodicAlertReportTraits::Action());
		filter.push_back(OSELib::SDC::PeriodicMetricReportTraits::Action());
		// fixme: move to SetService
		filter.push_back(OSELib::SDC::OperationInvokedReportTraits::Action());
		subscriptions.emplace_back(
				Poco::URI("http://" + _deviceDescription.getLocalIP().toString() + ":" + std::to_string(configuration.getPort()) + "/EventReportSink"),
				_deviceDescription.getEventServiceURI(),
				filter);
	}
//	{
//		WS::EVENTING::FilterType filter;
//		// fixme: move to SetService
//		//filter.push_back(OSELib::SDC::OperationInvokedReportTraits::Action());
//		subscriptions.emplace_back(
//				Poco::URI("http://" + _deviceDescription.getLocalIP().toString() + ":" + std::to_string(configuration.getPort()) + "/EventReportSink"),
//				_deviceDescription.getEventServiceURI(),
//				filter);
//	}

	_subscriptionClient = std::unique_ptr<OSELib::DPWS::SubscriptionClient>(new OSELib::DPWS::SubscriptionClient(subscriptions));
}

void SDCConsumerAdapter::unsubscribeEvents() {
	if (_subscriptionClient) {
		_subscriptionClient.reset();
	}
}

template<class TraitsType>
std::unique_ptr<typename TraitsType::Response> SDCConsumerAdapter::invokeImplWithEventSubscription(const typename TraitsType::Request & request, const Poco::URI & requestURI) {
	// We need to receive operation invoked events, so we do kind of emergency subscriptions here
	subscribeEvents();
	return invokeImpl<TraitsType>(request, requestURI);
}

template<class TraitsType>
std::unique_ptr<typename TraitsType::Response> SDCConsumerAdapter::invokeImpl(const typename TraitsType::Request & request, const Poco::URI & requestURI) {

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

void SDCConsumerAdapter::dispatch(const OSELib::DPWS::WaveformStreamType & notification) {
	_consumer.onStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(notification.State().front()));
}


template<>
Poco::URI SDCConsumerAdapter::getRequestURIFromDeviceDescription(const OSELib::SDC::GetMDDescriptionTraits::Request & ) {
	return _deviceDescription.getGetServiceURI();
}

template<>
Poco::URI SDCConsumerAdapter::getRequestURIFromDeviceDescription(const OSELib::SDC::GetMDIBTraits::Request & ) {
	return _deviceDescription.getGetServiceURI();
}

template<>
Poco::URI SDCConsumerAdapter::getRequestURIFromDeviceDescription(const OSELib::SDC::GetMdStateTraits::Request & ) {
	return _deviceDescription.getGetServiceURI();
}

template<>
Poco::URI SDCConsumerAdapter::getRequestURIFromDeviceDescription(const OSELib::SDC::ActivateTraits::Request & ) {
	return _deviceDescription.getSetServiceURI();
}

template<>
Poco::URI SDCConsumerAdapter::getRequestURIFromDeviceDescription(const OSELib::SDC::SetAlertStateTraits::Request & ) {
	return _deviceDescription.getSetServiceURI();
}

template<>
Poco::URI SDCConsumerAdapter::getRequestURIFromDeviceDescription(const OSELib::SDC::SetStringTraits::Request & ) {
	return _deviceDescription.getSetServiceURI();
}

template<>
Poco::URI SDCConsumerAdapter::getRequestURIFromDeviceDescription(const OSELib::SDC::SetValueTraits::Request & ) {
	return _deviceDescription.getSetServiceURI();
}

template<>
Poco::URI SDCConsumerAdapter::getRequestURIFromDeviceDescription(const OSELib::SDC::SetContextStateTraits::Request & ) {
	return _deviceDescription.getContextServiceURI();
}

std::unique_ptr<MDM::GetMdDescriptionResponse> SDCConsumerAdapter::invoke(const MDM::GetMdDescription & request) {
	return invokeImpl<OSELib::SDC::GetMDDescriptionTraits>(request, getRequestURIFromDeviceDescription(request));
}

std::unique_ptr<MDM::GetMdibResponse> SDCConsumerAdapter::invoke(const MDM::GetMdib & request) {
	return invokeImpl<OSELib::SDC::GetMDIBTraits>(request, getRequestURIFromDeviceDescription(request));
}

std::unique_ptr<MDM::GetMdStateResponse> SDCConsumerAdapter::invoke(const MDM::GetMdState & request) {
	return invokeImpl<OSELib::SDC::GetMdStateTraits>(request, getRequestURIFromDeviceDescription(request));
}


std::unique_ptr<MDM::ActivateResponse> SDCConsumerAdapter::invoke(const MDM::Activate & request) {
	return invokeImplWithEventSubscription<OSELib::SDC::ActivateTraits>(request, getRequestURIFromDeviceDescription(request));
}

std::unique_ptr<MDM::SetAlertStateResponse> SDCConsumerAdapter::invoke(const MDM::SetAlertState & request) {
	return invokeImplWithEventSubscription<OSELib::SDC::SetAlertStateTraits>(request, getRequestURIFromDeviceDescription(request));
}

std::unique_ptr<MDM::SetValueResponse> SDCConsumerAdapter::invoke(const MDM::SetValue & request) {
	return invokeImplWithEventSubscription<OSELib::SDC::SetValueTraits>(request, getRequestURIFromDeviceDescription(request));
}

std::unique_ptr<MDM::SetStringResponse> SDCConsumerAdapter::invoke(const MDM::SetString & request) {
	return invokeImplWithEventSubscription<OSELib::SDC::SetStringTraits>(request, getRequestURIFromDeviceDescription(request));
}


std::unique_ptr<MDM::SetContextStateResponse> SDCConsumerAdapter::invoke(const MDM::SetContextState & request) {
	return invokeImplWithEventSubscription<OSELib::SDC::SetContextStateTraits>(request, getRequestURIFromDeviceDescription(request));
}

}
}
} /* namespace OSELib */
