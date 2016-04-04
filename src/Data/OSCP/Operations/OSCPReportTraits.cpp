/*
 * OSCPReportTraits.cpp
 *
 *  Created on: 09.06.2015
 *      Author: roehser
 */

#include "OSCLib/Data/OSCP/OSCPProvider.h"
#include "OSCLib/Data/OSCP/Operations/OSCPReportTraits.h"
#include "osdm.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

Data::QName DescriptionModificationReportTraits::MessageType() {
	return OSCLib::Data::QName("DescriptionModificationReport", NS_MESSAGE_MODEL);
}
std::string DescriptionModificationReportTraits::NotificationName() {
	return "DescriptionModificationReport";
}
Data::QName DescriptionModificationReportTraits::PortType() {
	return OSCLib::Data::QName(QNAME_REPORTSERVICE_PORTTYPE, NS_WSDL_TARGET_NAMESPACE);
}
std::string DescriptionModificationReportTraits::Action() {
	return EVENT_ACTION_CDM_DESCRIPTION_MODIFICATION_REPORT;
}

Data::QName EpisodicAlertReportTraits::MessageType() {
	return OSCLib::Data::QName("EpisodicAlertReport", NS_MESSAGE_MODEL);
}
std::string EpisodicAlertReportTraits::NotificationName() {
	return "EpisodicAlertReport";
}
Data::QName EpisodicAlertReportTraits::PortType() {
	return OSCLib::Data::QName(QNAME_REPORTSERVICE_PORTTYPE, NS_WSDL_TARGET_NAMESPACE);
}
std::string EpisodicAlertReportTraits::Action() {
	return EVENT_ACTION_CDM_EPISODIC_ALERT_REPORT;
}

Data::QName EpisodicContextChangedReportTraits::MessageType() {
	return OSCLib::Data::QName("EpisodicContextChangedReport", NS_MESSAGE_MODEL);
}
std::string EpisodicContextChangedReportTraits::NotificationName() {
	return "EpisodicContextChangedReport";
}
Data::QName EpisodicContextChangedReportTraits::PortType() {
	return OSCLib::Data::QName(QNAME_CONTEXTSERVICE_PORTTYPE, NS_WSDL_TARGET_NAMESPACE);
}
std::string EpisodicContextChangedReportTraits::Action() {
	return EVENT_ACTION_CDM_EPISODIC_CONTEXT_REPORT;
}

Data::QName EpisodicMetricReportTraits::MessageType() {
	return OSCLib::Data::QName("EpisodicMetricReport", NS_MESSAGE_MODEL);
}
std::string EpisodicMetricReportTraits::NotificationName() {
	return "EpisodicMetricReport";
}
Data::QName EpisodicMetricReportTraits::PortType() {
	return OSCLib::Data::QName(QNAME_REPORTSERVICE_PORTTYPE, NS_WSDL_TARGET_NAMESPACE);
}
std::string EpisodicMetricReportTraits::Action() {
	return EVENT_ACTION_CDM_EPISODIC_METRIC_REPORT;
}

Data::QName OperationInvokedReportTraits::MessageType() {
	return OSCLib::Data::QName("OperationInvokedReport", NS_MESSAGE_MODEL);
}
std::string OperationInvokedReportTraits::NotificationName() {
	return "OperationInvokedReport";
}
Data::QName OperationInvokedReportTraits::PortType() {
	return OSCLib::Data::QName(QNAME_REPORTSERVICE_PORTTYPE, NS_WSDL_TARGET_NAMESPACE);
}
std::string OperationInvokedReportTraits::Action() {
	return EVENT_ACTION_CDM_OPERATION_INVOKED_REPORT;
}

Data::QName PeriodicAlertReportTraits::MessageType() {
	return OSCLib::Data::QName("PeriodicAlertReport", NS_MESSAGE_MODEL);
}
std::string PeriodicAlertReportTraits::NotificationName() {
	return "PeriodicAlertReport";
}
Data::QName PeriodicAlertReportTraits::PortType() {
	return OSCLib::Data::QName(QNAME_REPORTSERVICE_PORTTYPE, NS_WSDL_TARGET_NAMESPACE);
}
std::string PeriodicAlertReportTraits::Action() {
	return EVENT_ACTION_CDM_PERIODIC_ALERT_REPORT;
}

Data::QName PeriodicContextChangedReportTraits::MessageType() {
	return OSCLib::Data::QName("PeriodicContextChangedReport", NS_MESSAGE_MODEL);
}
std::string PeriodicContextChangedReportTraits::NotificationName() {
	return "PeriodicContextChangedReport";
}
Data::QName PeriodicContextChangedReportTraits::PortType() {
	return OSCLib::Data::QName(QNAME_CONTEXTSERVICE_PORTTYPE, NS_WSDL_TARGET_NAMESPACE);
}
std::string PeriodicContextChangedReportTraits::Action() {
	return EVENT_ACTION_CDM_PERIODIC_CONTEXT_REPORT;
}

Data::QName PeriodicMetricReportTraits::MessageType() {
	return OSCLib::Data::QName("PeriodicMetricReport", NS_MESSAGE_MODEL);
}
std::string PeriodicMetricReportTraits::NotificationName() {
	return "PeriodicMetricReport";
}
Data::QName PeriodicMetricReportTraits::PortType() {
	return OSCLib::Data::QName(QNAME_REPORTSERVICE_PORTTYPE, NS_WSDL_TARGET_NAMESPACE);
}
std::string PeriodicMetricReportTraits::Action() {
	return EVENT_ACTION_CDM_PERIODIC_METRIC_REPORT;
}

Data::QName WaveformStreamTraits::MessageType() {
	return OSCLib::Data::QName("Notification", NS_MESSAGE_MODEL);
}
std::string WaveformStreamTraits::NotificationName() {
	return "WaveformStreamReport";
}
Data::QName WaveformStreamTraits::PortType() {
	return OSCLib::Data::QName(QNAME_STREAMSERVICE_PORTTYPE, NS_WSDL_TARGET_NAMESPACE);
}
std::string WaveformStreamTraits::Action() {
	return EVENT_ACTION_CDM_WAVEFORM_STREAM_REPORT;
}

}
}
}
