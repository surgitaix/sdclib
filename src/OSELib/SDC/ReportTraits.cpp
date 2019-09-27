/*
 * ReportTraits.cpp
 *
 *  Created on: 09.06.2015, roehser
 *  Modified on: 24.09.2019, baumeister
 *
 */
#include "OSELib/SDC/ReportTraits.h"
#include "OSELib/SDC/SDCConstants.h"
#include "OSELib/SDC/IContextServiceEventSink.h"
#include "OSELib/SDC/IStateEventServiceEventSink.h"
#include "OSELib/SDC/ISetServiceEventSink.h"

namespace OSELib {
namespace SDC {

// B.2 SetService
// OperationInvoked
xml_schema::Qname OperationInvokedReportTraits::MessageType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, OP_OPERATION_INVOKED_REPORT);
}
std::string OperationInvokedReportTraits::NotificationName() {
	return OPERATION_INVOKED_REPORT;
}
xml_schema::Qname OperationInvokedReportTraits::PortType() {
	return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_STATEEVENTSERVICE_PORTTYPE);
}
std::string OperationInvokedReportTraits::Action() {
	return ACT_OPERATION_INVOKED_REPORT;
}
void OperationInvokedReportTraits::dispatch(Dispatcher & p_dispatcher, const ReportType & p_report) {
	p_dispatcher.dispatch(p_report);
}


// B.3 Description Event Service
// Description Modification Report
xml_schema::Qname DescriptionModificationReportTraits::MessageType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, OP_DESCRIPTION_MODIFICATION_REPORT);
}
std::string DescriptionModificationReportTraits::NotificationName() {
	return DESCRIPTION_MODIFICATION_REPORT;
}
xml_schema::Qname DescriptionModificationReportTraits::PortType() {
	return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_STATEEVENTSERVICE_PORTTYPE);
}
std::string DescriptionModificationReportTraits::Action() {
	return ACT_DESCRIPTION_MODIFICATION_REPORT;
}


// B.4 State Event Service
// AlertReport
xml_schema::Qname EpisodicAlertReportTraits::MessageType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, OP_EPISODIC_ALERT_REPORT);
}
std::string EpisodicAlertReportTraits::NotificationName() {
	return EPISODIC_ALERT_REPORT;
}
xml_schema::Qname EpisodicAlertReportTraits::PortType() {
	return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_STATEEVENTSERVICE_PORTTYPE);
}
std::string EpisodicAlertReportTraits::Action() {
	return ACT_EPISODIC_ALERT_REPORT;
}
void EpisodicAlertReportTraits::dispatch(Dispatcher & p_dispatcher, const ReportType & p_report) {
	p_dispatcher.dispatch(p_report);
}
xml_schema::Qname PeriodicAlertReportTraits::MessageType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, OP_PERIODIC_ALERT_REPORT);
}
std::string PeriodicAlertReportTraits::NotificationName() {
	return PERIODIC_ALERT_REPORT;
}
xml_schema::Qname PeriodicAlertReportTraits::PortType() {
	return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_STATEEVENTSERVICE_PORTTYPE);
}
std::string PeriodicAlertReportTraits::Action() {
	return ACT_PERIODIC_ALERT_REPORT;
}
void PeriodicAlertReportTraits::dispatch(Dispatcher & p_dispatcher, const ReportType & p_report) {
	p_dispatcher.dispatch(p_report);
}

// Component Report
xml_schema::Qname EpisodicComponentReportTraits::MessageType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, OP_EPISODIC_COMPONENT_REPORT);
}
std::string EpisodicComponentReportTraits::NotificationName() {
	return EPISODIC_COMPONENT_REPORT;
}
xml_schema::Qname EpisodicComponentReportTraits::PortType() {
	return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_STATEEVENTSERVICE_PORTTYPE);
}
std::string EpisodicComponentReportTraits::Action() {
	return ACT_EPISODIC_COMPONENT_REPORT;
}
void EpisodicComponentReportTraits::dispatch(Dispatcher & p_dispatcher, const ReportType & p_report) {
	p_dispatcher.dispatch(p_report);
}

// MetricReport
xml_schema::Qname EpisodicMetricReportTraits::MessageType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, OP_EPISODIC_METRIC_REPORT);
}
std::string EpisodicMetricReportTraits::NotificationName() {
	return EPISODIC_METRIC_REPORT;
}
xml_schema::Qname EpisodicMetricReportTraits::PortType() {
	return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_STATEEVENTSERVICE_PORTTYPE);
}
std::string EpisodicMetricReportTraits::Action() {
	return ACT_EPISODIC_METRIC_REPORT;
}
void EpisodicMetricReportTraits::dispatch(Dispatcher & p_dispatcher, const ReportType & p_report) {
	p_dispatcher.dispatch(p_report);
}
xml_schema::Qname PeriodicMetricReportTraits::MessageType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, OP_PERIODIC_METRIC_REPORT);
}
std::string PeriodicMetricReportTraits::NotificationName() {
	return PERIODIC_METRIC_REPORT;
}
xml_schema::Qname PeriodicMetricReportTraits::PortType() {
	return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_STATEEVENTSERVICE_PORTTYPE);
}
std::string PeriodicMetricReportTraits::Action() {
	return ACT_PERIODIC_METRIC_REPORT;
}
void PeriodicMetricReportTraits::dispatch(Dispatcher & p_dispatcher, const ReportType & p_report) {
	p_dispatcher.dispatch(p_report);
}

// OperationalState
xml_schema::Qname EpisodicOperationalStateReportTraits::MessageType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, OP_EPISODIC_OPERATIONALSTATE_REPORT);
}
std::string EpisodicOperationalStateReportTraits::NotificationName() {
	return EPISODIC_OPERATIONALSTATE_REPORT;
}
xml_schema::Qname EpisodicOperationalStateReportTraits::PortType() {
	return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_STATEEVENTSERVICE_PORTTYPE);
}
std::string EpisodicOperationalStateReportTraits::Action() {
	return ACT_EPISODIC_OPERATIONALSTATE_REPORT;
}
void EpisodicOperationalStateReportTraits::dispatch(Dispatcher& p_dispatcher, const ReportType& p_report) {
	p_dispatcher.dispatch(p_report);
}


// B.5 Context Service
// ContextReport
xml_schema::Qname EpisodicContextReportTraits::MessageType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, OP_EPISODIC_CONTEXT_REPORT);
}
std::string EpisodicContextReportTraits::NotificationName() {
	return EPISODIC_CONTEXT_REPORT;
}
xml_schema::Qname EpisodicContextReportTraits::PortType() {
	return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_CONTEXTSERVICE_PORTTYPE);
}
std::string EpisodicContextReportTraits::Action() {
	return ACT_EPISODIC_CONTEXT_REPORT;
}
void EpisodicContextReportTraits::dispatch(Dispatcher & p_dispatcher, const ReportType & p_report) {
	p_dispatcher.dispatch(p_report);
}
xml_schema::Qname PeriodicContextReportTraits::MessageType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, OP_PERIODIC_CONTEXT_REPORT);
}
std::string PeriodicContextReportTraits::NotificationName() {
	return PERIODIC_CONTEXT_REPORT;
}
xml_schema::Qname PeriodicContextReportTraits::PortType() {
	return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_CONTEXTSERVICE_PORTTYPE);
}
std::string PeriodicContextReportTraits::Action() {
	return ACT_PERIODIC_CONTEXT_REPORT;
}
void PeriodicContextReportTraits::dispatch(Dispatcher & p_dispatcher, const ReportType & p_report) {
	p_dispatcher.dispatch(p_report);
}



// B.6 Waveform Service
// WaveformStream
xml_schema::Qname WaveformStreamTraits::MessageType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, OP_WAVEFORM_STREAM_REPORT);
}
std::string WaveformStreamTraits::NotificationName() {
	return WAVEFORM_STREAM;
}
xml_schema::Qname WaveformStreamTraits::PortType() {
	return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_WAVEFORMSERVICE_PORTTYPE);
}
std::string WaveformStreamTraits::Action() {
	return ACT_WAVEFORM_STREAM_REPORT;
}
void WaveformStreamTraits::dispatch(Dispatcher & p_dispatcher, const ReportType & p_report) {
	p_dispatcher.dispatch(p_report);
}

}
}
