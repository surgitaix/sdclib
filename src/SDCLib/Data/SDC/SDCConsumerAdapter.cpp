/*
 * SDCConsumerAdapter.cpp
 *
 *  Created on: 10.12.2015, matthias
 *  Modified on: 26.09.2019, baumeister
 *
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
#include "SDCLib/Data/SDC/MDIB/ScoState.h"
#include "SDCLib/Data/SDC/MDIB/BatteryState.h"
#include "SDCLib/Data/SDC/MDIB/ClockState.h"
#include "SDCLib/Data/SDC/MDIB/MdsState.h"
#include "SDCLib/Data/SDC/MDIB/VmdState.h"
#include "SDCLib/Data/SDC/MDIB/SetValueOperationState.h"
#include "SDCLib/Data/SDC/MDIB/SetStringOperationState.h"
#include "SDCLib/Data/SDC/MDIB/ActivateOperationState.h"
#include "SDCLib/Data/SDC/MDIB/SetContextStateOperationState.h"
#include "SDCLib/Data/SDC/MDIB/SetMetricStateOperationState.h"
#include "SDCLib/Data/SDC/MDIB/SetComponentStateOperationState.h"
#include "SDCLib/Data/SDC/MDIB/SetAlertStateOperationState.h"

#include "OSELib/DPWS/DeviceDescription.h"
#include "OSELib/Helper/WithLogger.h"
#include "OSELib/HTTP/FrontController.h"
#include "OSELib/HTTP/FrontControllerAdapter.h"
#include "OSELib/HTTP/HTTPRequestHandlerFactory.h"
#include "OSELib/SDC/SetServiceEventSinkHandler.h"
#include "OSELib/SDC/IBICEPSServiceEventSink.h"
#include "OSELib/SDC/BICEPSServiceEventSinkHandler.h"
#include "OSELib/SDC/ISetServiceEventSink.h"
#include "OSELib/SDC/OperationTraits.h"
#include "OSELib/SDC/SDCConstants.h"
#include "OSELib/SDC/SDCEventServiceController.h"
#include "OSELib/SDC/ReportTraits.h"
#include "OSELib/SOAP/GenericSoapInvoke.h"


namespace OSELib
{

using SetServiceEventSinkController = SDC::SDCEventServiceController<SDC::ISetServiceEventSink, SDC::SetServiceEventSinkHandler>;
using BICEPSServiceEventSinkController = SDC::SDCEventServiceController<SDC::IBICEPSServiceEventSink , SDC::BICEPSServiceEventSinkHandler>;

class SetServiceEventSink : public SDC::ISetServiceEventSink, public OSELib::Helper::WithLogger
{
private:

	SDCLib::Data::SDC::SDCConsumer & m_consumer;
public:

	SetServiceEventSink(SDCLib::Data::SDC::SDCConsumer & p_consumer)
	: OSELib::Helper::WithLogger(Log::EVENTSINK)
	, m_consumer(p_consumer)
	{ }

	std::string getBaseUri() const override {
		return "/" + OSELib::SDC::QNAME_SETSERVICE_PORTTYPE;
	}

	void dispatch(const SDC::OperationInvokedReportTraits::ReportType & p_report) override {
		// fixme move all to SDCConsumer and change interface, so this method here only delegates. This should be done for all events
		if (p_report.MdibVersion().present()) {
			m_consumer.updateLastKnownMdibVersion(p_report.MdibVersion().get());
		}
		for (const auto & t_irp : p_report.ReportPart()) {
			m_consumer.onOperationInvoked(
				SDCLib::Data::SDC::OperationInvocationContext(t_irp.OperationHandleRef(), t_irp.InvocationInfo().TransactionId()),
				SDCLib::Data::SDC::ConvertFromCDM::convert(t_irp.InvocationInfo().InvocationState()));
		}
	}
};

class BICEPSServiceEventSink : public SDC::IBICEPSServiceEventSink, public OSELib::Helper::WithLogger
{
private:
	SDCLib::Data::SDC::SDCConsumer& m_consumer;

public:

	BICEPSServiceEventSink(SDCLib::Data::SDC::SDCConsumer& p_consumer)
	: OSELib::Helper::WithLogger(Log::EVENTSINK)
	, m_consumer(p_consumer)
	{ }

	std::string getBaseUri() const override {
		return "/" + OSELib::SDC::QNAME_BICEPSSERVICE_PORTTYPE;
	}


	// Description Event Service
	void dispatch(const SDC::DescriptionModificationReportTraits::ReportType &) override
	{
		// TODO
	}

	// StateEvent
	void dispatch(const SDC::EpisodicAlertReportTraits::ReportType & p_report) override
	{
		if (p_report.MdibVersion().present()) {
			m_consumer.updateLastKnownMdibVersion(p_report.MdibVersion().get());
		}
		for (const auto & t_reportPart : p_report.ReportPart()) {
			for (const auto & t_state : t_reportPart.AlertState()) {
				dispatchAlertState(t_state);
			}
		}
	}

	void dispatch(const SDC::EpisodicComponentReportTraits::ReportType & p_report) override {
		if (p_report.MdibVersion().present()) {
			m_consumer.updateLastKnownMdibVersion(p_report.MdibVersion().get());
		}
		for (const auto & t_reportPart : p_report.ReportPart()) {
			for (const auto & t_state : t_reportPart.ComponentState()) {
				dispatchComponentState(t_state);
			}
		}
	}

	void dispatch(const SDC::EpisodicMetricReportTraits::ReportType& p_report) override {
		if (p_report.MdibVersion().present()) {
			m_consumer.updateLastKnownMdibVersion(p_report.MdibVersion().get());
		}
		for (const auto & t_reportPart : p_report.ReportPart()) {
			for (const auto & t_state : t_reportPart.MetricState()) {
				dispatchMetricState(t_state);
			}
		}
	}

	void dispatch(const SDC::EpisodicOperationalStateReportTraits::ReportType& p_report) override {
		if (p_report.MdibVersion().present()) {
			m_consumer.updateLastKnownMdibVersion(p_report.MdibVersion().get());
		}
		for (const auto & t_reportPart : p_report.ReportPart()) {
			for (const auto & t_state : t_reportPart.OperationState()) {
				dispatchOperationState(t_state);
			}
		}
	}

	void dispatch(const SDC::PeriodicAlertReportTraits::ReportType & p_report) override {
		if (p_report.MdibVersion().present()) {
			m_consumer.updateLastKnownMdibVersion(p_report.MdibVersion().get());
		}
		for (const auto & reportPart : p_report.ReportPart()) {
			for (const auto & state : reportPart.AlertState()) {
				dispatchAlertState(state);
			}
		}
	}

	void dispatch(const SDC::PeriodicMetricReportTraits::ReportType & p_report) override {
		if (p_report.MdibVersion().present()) {
			m_consumer.updateLastKnownMdibVersion(p_report.MdibVersion().get());
		}
		for (const auto & t_reportPart : p_report.ReportPart()) {
			for (const auto & t_state : t_reportPart.MetricState()) {
				dispatchMetricState(t_state);
			}
		}
	}

	// todo: more elegant implementation of streaming possible?
	void dispatch(const SDC::WaveformStreamTraits::ReportType&) override { }


	// Context Service
	// todo: fix multistate implementation. this one only calls the state handlers which reference the descriptorsHandles
		// when a state with a defined handle updated also the state with the regarding descriptor Handle is called.
		// this is not right.

		// casts to right inherited type and call the regarding method of the consumer
		void delegateContextState(const CDM::AbstractContextState & p_contextState) {
			if (const auto t_state = dynamic_cast<const CDM::LocationContextState *>(&p_contextState)) {
				// dispatch to multi state callback
	//			_consumer.onMultiStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(*state));
				// dispatch to state callback referenced by the multistate descriptor
				m_consumer.onStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(*t_state));
				return;
			}
			if (const auto t_state = dynamic_cast<const CDM::PatientContextState *>(&p_contextState)) {
				// dispatch to multi state callback
	//			_consumer.onMultiStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(*state));
				// dispatch to state callback referenced by the multistate descriptor
				m_consumer.onStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(*t_state));
				return;
			}
			if (const auto t_state = dynamic_cast<const CDM::WorkflowContextState *>(&p_contextState)) {
				// dispatch to multi state callback
	//			_consumer.onMultiStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(*state));
				// dispatch to state callback referenced by the multistate descriptor
				m_consumer.onStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(*t_state));
				return;
			}
			if (const auto t_state = dynamic_cast<const CDM::EnsembleContextState *>(&p_contextState)) {
				// dispatch to multi state callback
	//			_consumer.onMultiStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(*state));
				// dispatch to state callback referenced by the multistate descriptor
				m_consumer.onStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(*t_state));
				return;
			}
			if (const auto t_state = dynamic_cast<const CDM::OperatorContextState *>(&p_contextState)) {
				// dispatch to multi state callback
	//			_consumer.onMultiStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(*state));
				// dispatch to state callback referenced by the multistate descriptor
				m_consumer.onStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(*t_state));
				return;
			}
			if (const auto t_state = dynamic_cast<const CDM::MeansContextState *>(&p_contextState)) {
				// dispatch to multi state callback
	//			_consumer.onMultiStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(*state));
				// dispatch to state callback referenced by the multistate descriptor
				m_consumer.onStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(*t_state));
				return;
			}
			log_error([] { return "Unknown context state type, event will not be forwarded to handler!"; });
		}


		// dispatch episodic reports and delegate the contained context states
		void dispatch(const SDC::EpisodicContextReportTraits::ReportType & p_report) override {

			if (p_report.MdibVersion().present()) {
				m_consumer.updateLastKnownMdibVersion(p_report.MdibVersion().get());
			}

			for (const auto & t_reportPart: p_report.ReportPart()) {
				// get the part of the report, as defined by the message model
				if (const auto part = dynamic_cast<const MDM::ReportPart *>(&t_reportPart)) { // FIXME: std::addressof?
					// get all ContextStates. ContextStates are all states inheriting from AbstractContextState
					for (const auto & t_contextState : part->ContextState()) {
						delegateContextState(t_contextState);
					}
				}
			}
		}

		// dispatch periodic reports and delegate the contained context states
		void dispatch(const SDC::PeriodicContextReportTraits::ReportType & p_report) override {
			if (p_report.MdibVersion().present()) {
				m_consumer.updateLastKnownMdibVersion(p_report.MdibVersion().get());
			}

			for (const auto & t_reportPart: p_report.ReportPart()) { // FIXME: Nested for loops AND dynamic_cast! -> REFACTOR!
				// get the part of the report, that is defined by the message model
				if (const auto t_part = dynamic_cast<const MDM::ReportPart *>(&t_reportPart)) { // FIXME: std::addressif?
					// get all ContextStates. ContextStates are all states inheriting from AbstractContextState
					for (const auto & t_contextState : t_part->ContextState()) {
						delegateContextState(t_contextState);
					}
				}
			}
		}


	private:

		void dispatchAlertState(const CDM::AbstractAlertState & p_alertState) {
			if (const auto t_state = dynamic_cast<const CDM::AlertSystemState *>(&p_alertState)) {
				m_consumer.onStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(*t_state));
				return;
			}
			if (const auto t_state = dynamic_cast<const CDM::AlertSignalState *>(&p_alertState)) {
				m_consumer.onStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(*t_state));
				return;
			}
			if (const auto t_state = dynamic_cast<const CDM::LimitAlertConditionState *>(&p_alertState)) {
				m_consumer.onStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(*t_state));
				return;
			}
			// the order does matter here, because AlertConditionState is the parent class of LimitAlertConditionState
			if (const auto t_state = dynamic_cast<const CDM::AlertConditionState *>(&p_alertState)) {
				m_consumer.onStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(*t_state));
				return;
			}
			log_error([] { return "Unknown alert state type, event will not be forwarded to handler!"; });
		}

		void dispatchComponentState(const CDM::AbstractDeviceComponentState & p_state)
		{
			if (const auto t_state = dynamic_cast<const CDM::ScoState *>(&p_state)) {
				m_consumer.onStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(*t_state));
				return;
			}
			if (const auto t_state = dynamic_cast<const CDM::BatteryState *>(&p_state)) {
				m_consumer.onStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(*t_state));
				return;
			}
			if (const auto t_state = dynamic_cast<const CDM::ClockState *>(&p_state)) {
				m_consumer.onStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(*t_state));
				return;
			}

			// Derived by AbstractComplexDeviceComponentState
			if (const auto t_state = dynamic_cast<const CDM::MdsState *>(&p_state)) {
				m_consumer.onStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(*t_state));
				return;
			}
			if (const auto t_state = dynamic_cast<const CDM::VmdState *>(&p_state)) {
				m_consumer.onStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(*t_state));
				return;
			}
			log_error([] { return "Unknown component state type, event will not be forwarded to handler!"; });
		}

		void dispatchMetricState(const CDM::AbstractMetricState & p_metricState) {
			if (const auto t_state = dynamic_cast<const CDM::EnumStringMetricState *>(&p_metricState)) {
				m_consumer.onStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(*t_state));
				return;
			}
			if (const auto t_state = dynamic_cast<const CDM::NumericMetricState *>(&p_metricState)) {
				m_consumer.onStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(*t_state));
				return;
			}
			if (const auto t_state = dynamic_cast<const CDM::StringMetricState *>(&p_metricState)) {
				m_consumer.onStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(*t_state));
				return;
			}
			if (const auto t_state = dynamic_cast<const CDM::RealTimeSampleArrayMetricState *>(&p_metricState)) {
				m_consumer.onStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(*t_state));
				return;
			}
			if (const auto t_state = dynamic_cast<const CDM::DistributionSampleArrayMetricState *>(&p_metricState)) {
				m_consumer.onStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(*t_state));
				return;
			}

			log_error([] { return "Unknown metric state type, event will not be forwarded to handler!"; });
		}


		void dispatchOperationState(const CDM::AbstractOperationState& p_state)
		{
			if (const auto t_state = dynamic_cast<const CDM::SetValueOperationState *>(&p_state)) {
				m_consumer.onStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(*t_state));
				return;
			}
			if (const auto t_state = dynamic_cast<const CDM::SetStringOperationState *>(&p_state)) {
				m_consumer.onStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(*t_state));
				return;
			}
			if (const auto t_state = dynamic_cast<const CDM::ActivateOperationState *>(&p_state)) {
				m_consumer.onStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(*t_state));
				return;
			}
			if (const auto t_state = dynamic_cast<const CDM::SetContextStateOperationState *>(&p_state)) {
				m_consumer.onStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(*t_state));
				return;
			}
			if (const auto t_state = dynamic_cast<const CDM::SetMetricStateOperationState *>(&p_state)) {
				m_consumer.onStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(*t_state));
				return;
			}
			if (const auto t_state = dynamic_cast<const CDM::SetComponentStateOperationState *>(&p_state)) {
				m_consumer.onStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(*t_state));
				return;
			}
			if (const auto t_state = dynamic_cast<const CDM::SetAlertStateOperationState *>(&p_state)) {
				m_consumer.onStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(*t_state));
				return;
			}
			log_error([] { return "Unknown metric state type, event will not be forwarded to handler!"; });
		}

};


}

namespace SDCLib {
namespace Data {
namespace SDC {


class ConsumerFactory : public OSELib::HTTP::FrontControllerAdapter
{
private:
	OSELib::HTTP::FrontController m_frontController;

	OSELib::SetServiceEventSink m_setServiceEventSink;
	OSELib::BICEPSServiceEventSink m_BICEPSServiceEventSink;

	OSELib::SetServiceEventSinkController m_setServiceEventSinkController;
	OSELib::BICEPSServiceEventSinkController m_BICEPSServiceEventSinkServiceController;

public:
	ConsumerFactory(SDCLib::Data::SDC::SDCConsumer& p_consumer, bool p_SSL)
	: FrontControllerAdapter(m_frontController)
	, m_setServiceEventSink(p_consumer)
	, m_BICEPSServiceEventSink(p_consumer)
	, m_setServiceEventSinkController(m_frontController, m_setServiceEventSink)
	, m_BICEPSServiceEventSinkServiceController(m_frontController, m_BICEPSServiceEventSink)
	{
		m_frontController.setSSL(p_SSL);
	}
};



SDCConsumerAdapter::SDCConsumerAdapter(SDCConsumer & p_consumer, OSELib::DPWS::DeviceDescription_shared_ptr p_deviceDescription)
: OSELib::Helper::WithLogger(OSELib::Log::SDCCONSUMERADAPTER)
, m_consumer(p_consumer)
, m_deviceDescription(p_deviceDescription)
, m_streamClientSocketImpl(p_consumer.getSDCInstance()->getNetworkConfig(), *this, p_deviceDescription)
{
	assert(m_deviceDescription != nullptr);
}
SDCConsumerAdapter::~SDCConsumerAdapter()
{
	stop();
}

bool SDCConsumerAdapter::start()
{
	std::lock_guard<std::mutex> t_lock(m_mutex);
	if (m_httpServer) {
		return false;
	}

    auto t_networkConfig = m_consumer.getSDCInstance()->getNetworkConfig();
	auto t_SSLConfig = m_consumer.getSDCInstance()->getSSLConfig();
    assert(t_networkConfig != nullptr);
    assert(t_SSLConfig != nullptr);

	// HTTP Server
    m_httpServer = std::unique_ptr<OSELib::HTTP::HTTPServer>(new OSELib::HTTP::HTTPServer(t_networkConfig, t_SSLConfig));

    // Init

    auto t_factory = new ConsumerFactory(m_consumer, m_consumer.getSDCInstance()->getSSLConfig()->isInit());
    if(!m_httpServer->init(std::make_shared<OSELib::HTTP::HTTPRequestHandlerFactory>(t_factory))) {
    	OSELib::Helper::WithLogger(OSELib::Log::SDCCONSUMER).log_error([] { return "SDCConsumerAdapter: Failed to init HTTPServer!";});
    	return false;
    }
	m_httpServer->start();

	if (m_pingManager) {
		//todo maybe throw because starting twice is clearly an error
        // FIXME:
        // (ERROR != THROWING) DONT USE EXCEPTIONS AS FLOW CONTROL... assert, static_assert + logging etc.
		return false;
	}

	m_pingManager = std::unique_ptr<OSELib::DPWS::PingManager>(new OSELib::DPWS::PingManager(m_consumer));
    return true;
}


void SDCConsumerAdapter::stop()
{
	std::lock_guard<std::mutex> t_lock(m_mutex);

	if (m_httpServer) {
		m_httpServer->stopAll(false); // Comment: Why false?
		// TODO: Why wait here?
		while (m_httpServer->currentConnections() != 0) {
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}
		m_httpServer.reset();
	}

	if (m_pingManager) { // Todo: Why dump it? -> PINGMANAGER: FIX CLEANUP / RAII... FIXME
		m_pingManager->disable();
		m_consumer.getSDCInstance()->dumpPingManager(std::move(m_pingManager));
	}
}

void SDCConsumerAdapter::subscribeEvents()
{
	if (m_subscriptionClient) {
		return;
	}

	auto t_port = m_consumer.getSDCInstance()->getNetworkConfig()->getMDPWSPort();

    std::string t_PROTOCOL = "http";
    if(m_consumer.getSDCInstance()->getSSLConfig()->isInit()) {
        t_PROTOCOL.append("s");
    }


    // R0035 - Subscribe with one Subscribe

	std::vector<OSELib::DPWS::SubscriptionClient::SubscriptionInformation> tl_subscriptions;

	{
		WS::EVENTING::FilterType t_filter;
		// Event reports
		t_filter.push_back(OSELib::SDC::EpisodicAlertReportTraits::Action());
		t_filter.push_back(OSELib::SDC::EpisodicMetricReportTraits::Action());
		t_filter.push_back(OSELib::SDC::PeriodicAlertReportTraits::Action());
		t_filter.push_back(OSELib::SDC::PeriodicMetricReportTraits::Action());
		// Context reports
		t_filter.push_back(OSELib::SDC::EpisodicContextReportTraits::Action());
		t_filter.push_back(OSELib::SDC::PeriodicContextReportTraits::Action());

		tl_subscriptions.emplace_back(
				Poco::URI(t_PROTOCOL + "://" + m_deviceDescription->getLocalIP().toString() + ":" + std::to_string(t_port) + "/" + OSELib::SDC::QNAME_BICEPSSERVICE_PORTTYPE),
				m_deviceDescription->getBICEPSServiceURI(),
				t_filter);
	}

	{
		WS::EVENTING::FilterType t_filter;
		// fixme: move to SetService
		t_filter.push_back(OSELib::SDC::OperationInvokedReportTraits::Action());
		tl_subscriptions.emplace_back(
				Poco::URI(t_PROTOCOL + "://" + m_deviceDescription->getLocalIP().toString() + ":" + std::to_string(t_port) + "/" + OSELib::SDC::QNAME_SETSERVICE_PORTTYPE),
				m_deviceDescription->getSetServiceURI(),
				t_filter);
	}

	// Note: Just passing Poco::Net::Context::Ptr means SSL has to be initialized when
	//       the SubscriptionClient is created. Else nullptr is passed. Maybe rebuild
	//       and pass SSLHandler if this causes errors.
	m_subscriptionClient = std::unique_ptr<OSELib::DPWS::SubscriptionClient>(new OSELib::DPWS::SubscriptionClient(tl_subscriptions, m_consumer.getSDCInstance()->getSSLConfig()->getClientContext()));
}

void SDCConsumerAdapter::unsubscribeEvents() {
	if (m_subscriptionClient) {
		m_subscriptionClient.reset();
	}
}

template<class TraitsType>
std::unique_ptr<typename TraitsType::Response> SDCConsumerAdapter::invokeImplWithEventSubscription(const typename TraitsType::Request & p_request, const Poco::URI & p_requestURI, Poco::Net::Context::Ptr p_context) {
	// We need to receive operation invoked events, so we do kind of emergency subscriptions here
	subscribeEvents();
	return invokeImpl<TraitsType>(p_request, p_requestURI, p_context);
}

template<class TraitsType>
std::unique_ptr<typename TraitsType::Response> SDCConsumerAdapter::invokeImpl(const typename TraitsType::Request & p_request, const Poco::URI & p_requestURI, Poco::Net::Context::Ptr p_context) {

	using Invoker = OSELib::SOAP::GenericSoapInvoke<TraitsType>;
	std::unique_ptr<Invoker> t_invoker(new Invoker(p_requestURI, m_grammarProvider));

	auto t_response(t_invoker->invoke(p_request, p_context));
	if (t_response != nullptr) {
		if (t_response->MdibVersion().present()) {
			m_consumer.updateLastKnownMdibVersion(t_response->MdibVersion().get());
		}
		return t_response;
	}
	return nullptr;
}

void SDCConsumerAdapter::dispatch(const OSELib::DPWS::WaveformStreamType & p_notification) {
	m_consumer.onStateChanged(SDCLib::Data::SDC::ConvertFromCDM::convert(p_notification.State().front()));
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

std::unique_ptr<MDM::GetMdDescriptionResponse> SDCConsumerAdapter::invoke(const MDM::GetMdDescription & p_request, Poco::Net::Context::Ptr p_context) {
	return invokeImpl<OSELib::SDC::GetMDDescriptionTraits>(p_request, getRequestURIFromDeviceDescription(p_request), p_context);
}

std::unique_ptr<MDM::GetMdibResponse> SDCConsumerAdapter::invoke(const MDM::GetMdib & p_request, Poco::Net::Context::Ptr p_context) {
	return invokeImpl<OSELib::SDC::GetMDIBTraits>(p_request, getRequestURIFromDeviceDescription(p_request), p_context);
}

std::unique_ptr<MDM::GetMdStateResponse> SDCConsumerAdapter::invoke(const MDM::GetMdState & p_request, Poco::Net::Context::Ptr p_context) {
	return invokeImpl<OSELib::SDC::GetMdStateTraits>(p_request, getRequestURIFromDeviceDescription(p_request), p_context);
}


std::unique_ptr<MDM::ActivateResponse> SDCConsumerAdapter::invoke(const MDM::Activate & p_request, Poco::Net::Context::Ptr p_context) {
	return invokeImplWithEventSubscription<OSELib::SDC::ActivateTraits>(p_request, getRequestURIFromDeviceDescription(p_request), p_context);
}

std::unique_ptr<MDM::SetAlertStateResponse> SDCConsumerAdapter::invoke(const MDM::SetAlertState & p_request, Poco::Net::Context::Ptr p_context) {
	return invokeImplWithEventSubscription<OSELib::SDC::SetAlertStateTraits>(p_request, getRequestURIFromDeviceDescription(p_request), p_context);
}

std::unique_ptr<MDM::SetValueResponse> SDCConsumerAdapter::invoke(const MDM::SetValue & p_request, Poco::Net::Context::Ptr p_context) {
	return invokeImplWithEventSubscription<OSELib::SDC::SetValueTraits>(p_request, getRequestURIFromDeviceDescription(p_request), p_context);
}

std::unique_ptr<MDM::SetStringResponse> SDCConsumerAdapter::invoke(const MDM::SetString & p_request, Poco::Net::Context::Ptr p_context) {
	return invokeImplWithEventSubscription<OSELib::SDC::SetStringTraits>(p_request, getRequestURIFromDeviceDescription(p_request), p_context);
}


std::unique_ptr<MDM::SetContextStateResponse> SDCConsumerAdapter::invoke(const MDM::SetContextState & p_request, Poco::Net::Context::Ptr p_context) {
	return invokeImplWithEventSubscription<OSELib::SDC::SetContextStateTraits>(p_request, getRequestURIFromDeviceDescription(p_request), p_context);
}

}
}
}
