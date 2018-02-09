/*
 * OSCPReportTraits.cpp
 *
 *  Created on: 09.06.2015
 *      Author: roehser
 */

#include "OSELib/SDC/IContextServiceEventSink.h"
#include "OSELib/SDC/IEventReportEventSink.h"
#include "OSELib/SDC/SDCConstants.h"
#include "OSELib/SDC/ReportTraits.h"

namespace OSELib {
namespace SDC {

xml_schema::Qname DescriptionModificationReportTraits::MessageType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, NotificationName());
}
std::string DescriptionModificationReportTraits::NotificationName() {
	return "DescriptionModificationReport";
}
xml_schema::Qname DescriptionModificationReportTraits::PortType() {
	return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_REPORTSERVICE_PORTTYPE);
}
std::string DescriptionModificationReportTraits::Action() {
	return EVENT_ACTION_CDM_DESCRIPTION_MODIFICATION_REPORT;
}

xml_schema::Qname EpisodicAlertReportTraits::MessageType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, NotificationName());
}
std::string EpisodicAlertReportTraits::NotificationName() {
	return "EpisodicAlertReport";
}
xml_schema::Qname EpisodicAlertReportTraits::PortType() {
	return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_REPORTSERVICE_PORTTYPE);
}
std::string EpisodicAlertReportTraits::Action() {
	return EVENT_ACTION_CDM_EPISODIC_ALERT_REPORT;
}
void EpisodicAlertReportTraits::dispatch(Dispatcher & dispatcher, const ReportType & report) {
	dispatcher.dispatch(report);
}

xml_schema::Qname EpisodicContextChangedReportTraits::MessageType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, NotificationName());
}
std::string EpisodicContextChangedReportTraits::NotificationName() {
	return "EpisodicContextChangedReport";
}
xml_schema::Qname EpisodicContextChangedReportTraits::PortType() {
	return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_CONTEXTSERVICE_PORTTYPE);
}
std::string EpisodicContextChangedReportTraits::Action() {
	return EVENT_ACTION_CDM_EPISODIC_CONTEXT_REPORT;
}
void EpisodicContextChangedReportTraits::dispatch(Dispatcher & dispatcher, const ReportType & report) {
	dispatcher.dispatch(report);
}

xml_schema::Qname EpisodicMetricReportTraits::MessageType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, NotificationName());
}
std::string EpisodicMetricReportTraits::NotificationName() {
	return "EpisodicMetricReport";
}
xml_schema::Qname EpisodicMetricReportTraits::PortType() {
	return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_REPORTSERVICE_PORTTYPE);
}
std::string EpisodicMetricReportTraits::Action() {
	return EVENT_ACTION_CDM_EPISODIC_METRIC_REPORT;
}
void EpisodicMetricReportTraits::dispatch(Dispatcher & dispatcher, const ReportType & report) {
	dispatcher.dispatch(report);
}

xml_schema::Qname OperationInvokedReportTraits::MessageType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, NotificationName());
}
std::string OperationInvokedReportTraits::NotificationName() {
	return "OperationInvokedReport";
}
xml_schema::Qname OperationInvokedReportTraits::PortType() {
	return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_REPORTSERVICE_PORTTYPE);
}
std::string OperationInvokedReportTraits::Action() {
	return EVENT_ACTION_CDM_OPERATION_INVOKED_REPORT;
}
void OperationInvokedReportTraits::dispatch(Dispatcher & dispatcher, const ReportType & report) {
	dispatcher.dispatch(report);
}

xml_schema::Qname PeriodicAlertReportTraits::MessageType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, NotificationName());
}
std::string PeriodicAlertReportTraits::NotificationName() {
	return "PeriodicAlertReport";
}
xml_schema::Qname PeriodicAlertReportTraits::PortType() {
	return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_REPORTSERVICE_PORTTYPE);
}
std::string PeriodicAlertReportTraits::Action() {
	return EVENT_ACTION_CDM_PERIODIC_ALERT_REPORT;
}
void PeriodicAlertReportTraits::dispatch(Dispatcher & dispatcher, const ReportType & report) {
	dispatcher.dispatch(report);
}

xml_schema::Qname PeriodicContextChangedReportTraits::MessageType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, NotificationName());
}
std::string PeriodicContextChangedReportTraits::NotificationName() {
	return "PeriodicContextChangedReport";
}
xml_schema::Qname PeriodicContextChangedReportTraits::PortType() {
	return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_CONTEXTSERVICE_PORTTYPE);
}
std::string PeriodicContextChangedReportTraits::Action() {
	return EVENT_ACTION_CDM_PERIODIC_CONTEXT_REPORT;
}
void PeriodicContextChangedReportTraits::dispatch(Dispatcher & dispatcher, const ReportType & report) {
	dispatcher.dispatch(report);
}

xml_schema::Qname PeriodicMetricReportTraits::MessageType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, NotificationName());
}
std::string PeriodicMetricReportTraits::NotificationName() {
	return "PeriodicMetricReport";
}
xml_schema::Qname PeriodicMetricReportTraits::PortType() {
	return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_REPORTSERVICE_PORTTYPE);
}
std::string PeriodicMetricReportTraits::Action() {
	return EVENT_ACTION_CDM_PERIODIC_METRIC_REPORT;
}
void PeriodicMetricReportTraits::dispatch(Dispatcher & dispatcher, const ReportType & report) {
	dispatcher.dispatch(report);
}


xml_schema::Qname WaveformStreamTraits::MessageType() {
	return xml_schema::Qname(NS_MESSAGE_MODEL, NotificationName());
}
std::string WaveformStreamTraits::NotificationName() {
	return "WaveformStreamReport";
}
xml_schema::Qname WaveformStreamTraits::PortType() {
	return xml_schema::Qname(NS_WSDL_TARGET_NAMESPACE, QNAME_STREAMSERVICE_PORTTYPE);
}
std::string WaveformStreamTraits::Action() {
	return EVENT_ACTION_CDM_WAVEFORM_STREAM_REPORT;
}
void WaveformStreamTraits::dispatch(Dispatcher & dispatcher, const ReportType & report) {
	dispatcher.dispatch(report);
}

}
}
