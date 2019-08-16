/*
 * SDCConsumerAdapter.cpp
 *
 *  Created on: 10.12.2015
 *      Author: matthias
 */

#include "SDCLib/Data/SDC/SDCConsumerAdapter.h"

#include "SDCLib/SDCInstance.h"
#include "SDCLib/Data/SDC/SDCConsumer.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/AlertConditionState.h"
#include "SDCLib/Data/SDC/MDIB/AlertSignalState.h"
#include "SDCLib/Data/SDC/MDIB/AlertSystemState.h"
#include "SDCLib/Data/SDC/MDIB/DistributionSampleArrayMetricState.h"
#include "SDCLib/Data/SDC/MDIB/EnumStringMetricState.h"
#include "SDCLib/Data/SDC/MDIB/LimitAlertConditionState.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricState.h"
#include "SDCLib/Data/SDC/MDIB/RealTimeSampleArrayMetricState.h"
#include "SDCLib/Data/SDC/MDIB/StringMetricState.h"
#include "SDCLib/Data/SDC/MDIB/LocationContextState.h"
#include "SDCLib/Data/SDC/MDIB/PatientContextState.h"
#include "SDCLib/Data/SDC/MDIB/WorkflowContextState.h"
#include "SDCLib/Data/SDC/MDIB/MeansContextState.h"
#include "SDCLib/Data/SDC/MDIB/OperatorContextState.h"
#include "SDCLib/Data/SDC/MDIB/EnsembleContextState.h"
#include "SDCLib/Data/SDC/MDIB/custom/OperationInvocationContext.h"

#include "OSELib/DPWS/PingManager.h"
#include "OSELib/DPWS/SubscriptionClient.h"
#include "OSELib/Helper/WithLogger.h"
#include "OSELib/HTTP/FrontControllerAdapter.h"
#include "OSELib/SDC/ContextEventSinkHandler.h"
#include "OSELib/SDC/StateEventServiceEventSinkHandler.h"
#include "OSELib/SDC/SetServiceEventSinkHandler.h"
#include "OSELib/SDC/IContextServiceEventSink.h"
#include "OSELib/SDC/IStateEventServiceEventSink.h"
#include "OSELib/SDC/ISetServiceEventSink.h"
#include "OSELib/SDC/OperationTraits.h"
#include "OSELib/SDC/SDCConstants.h"
#include "OSELib/SDC/SDCEventServiceController.h"
#include "OSELib/SDC/ReportTraits.h"
#include "OSELib/SOAP/GenericSoapInvoke.h"

#include <Poco/ThreadPool.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/NetworkInterface.h>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/SecureServerSocket.h>


namespace OSELib {

using ContextServiceEventSinkController = SDC::SDCEventServiceController<SDC::IContextServiceEventSink , SDC::ContextEventSinkHandler>;
using StateEventServiceEventSinkController = SDC::SDCEventServiceController<SDC::IStateEventServiceEventSink, SDC::StateEventServiceEventSinkHandler>;
using SetServiceEventSinkController = SDC::SDCEventServiceController<SDC::ISetServiceEventSink, SDC::SetServiceEventSinkHandler>;


struct ContextServiceEventSink : public SDC::IContextServiceEventSink, public OSELib::WithLogger  {
	ContextServiceEventSink(SDCLib::Data::SDC::SDCConsumer & consumer) :
		WithLogger(OSELib::Log::EVENTSINK),
		_consumer(consumer)
	{
	}

	virtual std::string getBaseUri() const override {
		return "/" + OSELib::SDC::QNAME_CONTEXTSERVICE_PORTTYPE;
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

struct EventReportEventSink : public SDC::IStateEventServiceEventSink, public OSELib::WithLogger {
	EventReportEventSink(SDCLib::Data::SDC::SDCConsumer & consumer) :
		WithLogger(Log::EVENTSINK),
		_consumer(consumer)
	{
	}

	virtual std::string getBaseUri() const override {
		return std::string("/" + SDC::QNAME_STATEEVENTREPORTSERVICE_PORTTYPE);
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


struct SetServiceEventSink : public SDC::ISetServiceEventSink, public OSELib::WithLogger {
	SetServiceEventSink(SDCLib::Data::SDC::SDCConsumer & consumer) :
		WithLogger(Log::EVENTSINK),
		_consumer(consumer)
	{
	}

	virtual std::string getBaseUri() const override {
		return "/" + OSELib::SDC::QNAME_SETSERVICE_PORTTYPE;
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

private:

	SDCLib::Data::SDC::SDCConsumer & _consumer;
};


}

namespace SDCLib {
namespace Data {
namespace SDC {

SDCConsumerAdapter::SDCConsumerAdapter(SDCConsumer & consumer, OSELib::DPWS::DeviceDescription_shared_ptr p_deviceDescription) :
	WithLogger(OSELib::Log::SDCCONSUMERADAPTER),
	_consumer(consumer),
	_threadPool(new Poco::ThreadPool()),
	m_deviceDescription(p_deviceDescription),
	_streamClientSocketImpl(consumer.getSDCInstance()->getNetworkConfig(), *this, p_deviceDescription)
{
	assert(m_deviceDescription != nullptr);
}

SDCConsumerAdapter::~SDCConsumerAdapter() = default;

bool SDCConsumerAdapter::start()
{
	std::lock_guard<std::mutex> t_lock(m_mutex);
	if (_httpServer) {
		return false;
	}

    auto t_networkConfig = _consumer.getSDCInstance()->getNetworkConfig();
    assert(t_networkConfig != nullptr);

    auto t_interface = t_networkConfig->getMDPWSInterface();
    if(!t_interface) {
    	log_error([&] { return "Failed to start SDCProviderAdapter: Set MDPWSInterface first!"; });
        return false;
    }


    auto t_bindingAddress = t_interface->m_if.address();
    auto t_port = t_networkConfig->getMDPWSPort();

	// todo: IPv6 implementation here!
	const Poco::Net::SocketAddress socketAddress(t_bindingAddress, t_port);

	class Factory : public OSELib::HTTP::FrontControllerAdapter {
	public:
		Factory(SDCConsumer & consumer, bool p_SSL) :
			FrontControllerAdapter(_frontController),
			_contextServiceEventSink(consumer),
			_eventReportEventSink(consumer),
			_setServiceEventSink(consumer),
			_contextServiceEventSinkServiceController(_frontController, _contextServiceEventSink),
			_eventReportEventSinkServiceController(_frontController, _eventReportEventSink),
			_setServiceEventSinkController(_frontController, _setServiceEventSink)
		{
            _frontController.setSSL(p_SSL);
		}

		virtual ~Factory() = default;

	private:
		OSELib::HTTP::FrontController _frontController;

		OSELib::ContextServiceEventSink _contextServiceEventSink;
		OSELib::EventReportEventSink _eventReportEventSink;
		OSELib::SetServiceEventSink _setServiceEventSink;

		OSELib::ContextServiceEventSinkController _contextServiceEventSinkServiceController;
		OSELib::StateEventServiceEventSinkController _eventReportEventSinkServiceController;
		OSELib::SetServiceEventSinkController _setServiceEventSinkController;

	};

    bool SSL_INIT = _consumer.getSDCInstance()->getSSLConfig()->isInit();
    // Use SSL
    if(SSL_INIT)
    {
        // ServerSocket
        Poco::Net::SecureServerSocket t_sslSocket(_consumer.getSDCInstance()->getSSLConfig()->getServerContext());
        t_sslSocket.bind(socketAddress);
        t_sslSocket.listen();
        t_sslSocket.setKeepAlive(true);

        // Create the Server
        _httpServer = std::unique_ptr<Poco::Net::HTTPServer>(new Poco::Net::HTTPServer(new Factory(_consumer, SSL_INIT), *_threadPool, t_sslSocket, new Poco::Net::HTTPServerParams));
    }
    else {
        // ServerSocket
        Poco::Net::ServerSocket t_socket;
        t_socket.bind(socketAddress);
        t_socket.listen();

        // Create the Server
        _httpServer = std::unique_ptr<Poco::Net::HTTPServer>(new Poco::Net::HTTPServer(new Factory(_consumer, SSL_INIT), *_threadPool, t_socket, new Poco::Net::HTTPServerParams));
    }

	_httpServer->start();

	if (_pingManager) {
		//todo maybe throw because starting twice is clearly an error
        // FIXME FIXME FIXME:
        // (ERROR != THROWING) DONT USE EXCEPTIONS AS FLOW CONTROL AND DONT JUST THROW JUST BECAUSE... THIS IS NOT JAVA... USE assert, static_assert, logging etc.
		return false;
	}

	_pingManager = std::unique_ptr<OSELib::DPWS::PingManager>(new OSELib::DPWS::PingManager(_consumer));
    return true;
}


void SDCConsumerAdapter::stop() {
	std::lock_guard<std::mutex> t_lock(m_mutex);

	if (_httpServer) {
		_httpServer->stopAll(false);
	}

	while (_httpServer->currentConnections() != 0) {
		Poco::Thread::sleep(100);
		_httpServer.reset();
	}


	if (_pingManager) {
		_pingManager->disable();
		_consumer.getSDCInstance()->dumpPingManager(std::move(_pingManager));
	}
}

void SDCConsumerAdapter::subscribeEvents() {
	if (_subscriptionClient) {
		return;
	}

	auto t_port = _consumer.getSDCInstance()->getNetworkConfig()->getMDPWSPort();

    std::string ts_PROTOCOL = "http";
    if(_consumer.getSDCInstance()->getSSLConfig()->isInit()) {
        ts_PROTOCOL.append("s");
    }

	std::vector<OSELib::DPWS::SubscriptionClient::SubscriptionInformation> subscriptions;
	// context reports
	{
		WS::EVENTING::FilterType filter;
		filter.push_back(OSELib::SDC::EpisodicContextChangedReportTraits::Action());
		filter.push_back(OSELib::SDC::PeriodicContextChangedReportTraits::Action());
		subscriptions.emplace_back(
				Poco::URI(ts_PROTOCOL + "://" + m_deviceDescription->getLocalIP().toString() + ":" + std::to_string(t_port) + "/" + OSELib::SDC::QNAME_CONTEXTSERVICE_PORTTYPE),
				m_deviceDescription->getContextServiceURI(),
				filter);
	}
	// Event reports
	{
		WS::EVENTING::FilterType filter;
		filter.push_back(OSELib::SDC::EpisodicAlertReportTraits::Action());
		filter.push_back(OSELib::SDC::EpisodicMetricReportTraits::Action());
		filter.push_back(OSELib::SDC::PeriodicAlertReportTraits::Action());
		filter.push_back(OSELib::SDC::PeriodicMetricReportTraits::Action());
		subscriptions.emplace_back(
				Poco::URI(ts_PROTOCOL + "://" + m_deviceDescription->getLocalIP().toString() + ":" + std::to_string(t_port) + "/" + OSELib::SDC::QNAME_STATEEVENTREPORTSERVICE_PORTTYPE),
				m_deviceDescription->getEventServiceURI(),
				filter);
	}
	{
		WS::EVENTING::FilterType filter;
		// fixme: move to SetService
		filter.push_back(OSELib::SDC::OperationInvokedReportTraits::Action());
		subscriptions.emplace_back(
				Poco::URI(ts_PROTOCOL + "://" + m_deviceDescription->getLocalIP().toString() + ":" + std::to_string(t_port) + "/" + OSELib::SDC::QNAME_SETSERVICE_PORTTYPE),
				m_deviceDescription->getSetServiceURI(),
				filter);
	}

	// Note: Just passing Poco::Net::Context::Ptr means SSL has to be initialized when
	//       the SubscriptionClient is created. Else nullptr is passed. Maybe rebuild
	//       and pass SSLHandler if this causes errors.
	_subscriptionClient = std::unique_ptr<OSELib::DPWS::SubscriptionClient>(new OSELib::DPWS::SubscriptionClient(subscriptions, _consumer.getSDCInstance()->getSSLConfig()->getClientContext()));
}

void SDCConsumerAdapter::unsubscribeEvents() {
	if (_subscriptionClient) {
		_subscriptionClient.reset();
	}
}

template<class TraitsType>
std::unique_ptr<typename TraitsType::Response> SDCConsumerAdapter::invokeImplWithEventSubscription(const typename TraitsType::Request & request, const Poco::URI & requestURI, Poco::Net::Context::Ptr p_context) {
	// We need to receive operation invoked events, so we do kind of emergency subscriptions here
	subscribeEvents();
	return invokeImpl<TraitsType>(request, requestURI, p_context);
}

template<class TraitsType>
std::unique_ptr<typename TraitsType::Response> SDCConsumerAdapter::invokeImpl(const typename TraitsType::Request & request, const Poco::URI & requestURI, Poco::Net::Context::Ptr p_context) {

	using Invoker = OSELib::SOAP::GenericSoapInvoke<TraitsType>;
	std::unique_ptr<Invoker> invoker(new Invoker(requestURI, _grammarProvider));

	auto t_response(invoker->invoke(request, p_context));
	if (t_response != nullptr) {
		if (t_response->MdibVersion().present()) {
			_consumer.updateLastKnownMdibVersion(t_response->MdibVersion().get());
		}
		return t_response;
	}

	return nullptr;
}

void SDCConsumerAdapter::dispatch(const OSELib::DPWS::WaveformStreamType & notification) {
	_consumer.onStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(notification.State().front()));
}


template<>
Poco::URI SDCConsumerAdapter::getRequestURIFromDeviceDescription(const OSELib::SDC::GetMDDescriptionTraits::Request & ) const {
	return m_deviceDescription->getGetServiceURI();
}

template<>
Poco::URI SDCConsumerAdapter::getRequestURIFromDeviceDescription(const OSELib::SDC::GetMDIBTraits::Request & ) const {
	return m_deviceDescription->getGetServiceURI();
}

template<>
Poco::URI SDCConsumerAdapter::getRequestURIFromDeviceDescription(const OSELib::SDC::GetMdStateTraits::Request & ) const {
	return m_deviceDescription->getGetServiceURI();
}

template<>
Poco::URI SDCConsumerAdapter::getRequestURIFromDeviceDescription(const OSELib::SDC::ActivateTraits::Request & ) const {
	return m_deviceDescription->getSetServiceURI();
}

template<>
Poco::URI SDCConsumerAdapter::getRequestURIFromDeviceDescription(const OSELib::SDC::SetAlertStateTraits::Request & ) const {
	return m_deviceDescription->getSetServiceURI();
}

template<>
Poco::URI SDCConsumerAdapter::getRequestURIFromDeviceDescription(const OSELib::SDC::SetStringTraits::Request & ) const {
	return m_deviceDescription->getSetServiceURI();
}

template<>
Poco::URI SDCConsumerAdapter::getRequestURIFromDeviceDescription(const OSELib::SDC::SetValueTraits::Request & ) const {
	return m_deviceDescription->getSetServiceURI();
}

template<>
Poco::URI SDCConsumerAdapter::getRequestURIFromDeviceDescription(const OSELib::SDC::SetContextStateTraits::Request & ) const {
	return m_deviceDescription->getContextServiceURI();
}

std::unique_ptr<MDM::GetMdDescriptionResponse> SDCConsumerAdapter::invoke(const MDM::GetMdDescription & request, Poco::Net::Context::Ptr p_context) {
	return invokeImpl<OSELib::SDC::GetMDDescriptionTraits>(request, getRequestURIFromDeviceDescription(request), p_context);
}

std::unique_ptr<MDM::GetMdibResponse> SDCConsumerAdapter::invoke(const MDM::GetMdib & request, Poco::Net::Context::Ptr p_context) {
	return invokeImpl<OSELib::SDC::GetMDIBTraits>(request, getRequestURIFromDeviceDescription(request), p_context);
}

std::unique_ptr<MDM::GetMdStateResponse> SDCConsumerAdapter::invoke(const MDM::GetMdState & request, Poco::Net::Context::Ptr p_context) {
	return invokeImpl<OSELib::SDC::GetMdStateTraits>(request, getRequestURIFromDeviceDescription(request), p_context);
}


std::unique_ptr<MDM::ActivateResponse> SDCConsumerAdapter::invoke(const MDM::Activate & request, Poco::Net::Context::Ptr p_context) {
	return invokeImplWithEventSubscription<OSELib::SDC::ActivateTraits>(request, getRequestURIFromDeviceDescription(request), p_context);
}

std::unique_ptr<MDM::SetAlertStateResponse> SDCConsumerAdapter::invoke(const MDM::SetAlertState & request, Poco::Net::Context::Ptr p_context) {
	return invokeImplWithEventSubscription<OSELib::SDC::SetAlertStateTraits>(request, getRequestURIFromDeviceDescription(request), p_context);
}

std::unique_ptr<MDM::SetValueResponse> SDCConsumerAdapter::invoke(const MDM::SetValue & request, Poco::Net::Context::Ptr p_context) {
	return invokeImplWithEventSubscription<OSELib::SDC::SetValueTraits>(request, getRequestURIFromDeviceDescription(request), p_context);
}

std::unique_ptr<MDM::SetStringResponse> SDCConsumerAdapter::invoke(const MDM::SetString & request, Poco::Net::Context::Ptr p_context) {
	return invokeImplWithEventSubscription<OSELib::SDC::SetStringTraits>(request, getRequestURIFromDeviceDescription(request), p_context);
}


std::unique_ptr<MDM::SetContextStateResponse> SDCConsumerAdapter::invoke(const MDM::SetContextState & request, Poco::Net::Context::Ptr p_context) {
	return invokeImplWithEventSubscription<OSELib::SDC::SetContextStateTraits>(request, getRequestURIFromDeviceDescription(request), p_context);
}

} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */
