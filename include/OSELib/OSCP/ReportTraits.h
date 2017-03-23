
#ifndef OSCPREPORTRAITS_H_
#define OSCPREPORTRAITS_H_

#include "osdm-fwd.hxx"

namespace OSELib {
namespace OSCP {

struct DescriptionModificationReportTraits {
	typedef CDM::DescriptionModificationReport ReportType;
	static xml_schema::Qname MessageType();
	static std::string NotificationName();
	static xml_schema::Qname PortType();
	static std::string Action();
};

struct EpisodicAlertReportTraits {
	typedef CDM::EpisodicAlertReport ReportType;
	typedef IEventReportEventSink Dispatcher;
	static xml_schema::Qname MessageType();
	static std::string NotificationName();
	static xml_schema::Qname PortType();
	static std::string Action();
	static void dispatch(Dispatcher & dispatcher, const ReportType & request);
};

struct EpisodicContextChangedReportTraits {
	typedef CDM::EpisodicContextChangedReport ReportType;
	typedef IContextServiceEventSink Dispatcher;
	static xml_schema::Qname MessageType();
	static std::string NotificationName();	
	static xml_schema::Qname PortType();
	static std::string Action();
	static void dispatch(Dispatcher & dispatcher, const ReportType & request);
};

struct EpisodicMetricReportTraits {
	typedef CDM::EpisodicMetricReport ReportType;
	typedef IEventReportEventSink Dispatcher;
	static xml_schema::Qname MessageType();
	static std::string NotificationName();
	static xml_schema::Qname PortType();
	static std::string Action();
	static void dispatch(Dispatcher & dispatcher, const ReportType & request);
};

struct OperationInvokedReportTraits {
	typedef CDM::OperationInvokedReport ReportType;
	typedef IEventReportEventSink Dispatcher;
	static xml_schema::Qname MessageType();
	static std::string NotificationName();
	static xml_schema::Qname PortType();
	static std::string Action();
	static void dispatch(Dispatcher & dispatcher, const ReportType & request);
};

struct PeriodicAlertReportTraits {
	typedef CDM::PeriodicAlertReport ReportType;
	typedef IEventReportEventSink Dispatcher;
	static xml_schema::Qname MessageType();
	static std::string NotificationName();
	static xml_schema::Qname PortType();
	static std::string Action();
	static void dispatch(Dispatcher & dispatcher, const ReportType & request);
};

struct PeriodicContextChangedReportTraits {
	typedef CDM::PeriodicContextChangedReport ReportType;
	typedef IContextServiceEventSink Dispatcher;
	static xml_schema::Qname MessageType();
	static std::string NotificationName();	
	static xml_schema::Qname PortType();
	static std::string Action();
	static void dispatch(Dispatcher & dispatcher, const ReportType & request);
};

struct PeriodicMetricReportTraits {
	typedef CDM::PeriodicMetricReport ReportType;
	typedef IEventReportEventSink Dispatcher;
	static xml_schema::Qname MessageType();
	static std::string NotificationName();
	static xml_schema::Qname PortType();
	static std::string Action();
	static void dispatch(Dispatcher & dispatcher, const ReportType & request);
};

struct WaveformStreamTraits {
	typedef CDM::WaveformStream ReportType;
	typedef IEventReportEventSink Dispatcher;
	static xml_schema::Qname MessageType();
	static std::string NotificationName();
	static xml_schema::Qname PortType();
	static std::string Action();
	static void dispatch(Dispatcher & dispatcher, const ReportType & request);
};

}
} /* namespace OSCLib */
#endif /* OSCPREPORTRAITS_H_ */
