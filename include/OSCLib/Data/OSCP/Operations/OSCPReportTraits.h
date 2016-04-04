
#ifndef OSCPREPORTRAITS_H_
#define OSCPREPORTRAITS_H_

#include "OSCLib/Data/QName.h"
#include "OSCLib/Data/OSCP/OSCPConstants.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

struct DescriptionModificationReportTraits {
	typedef CDM::DescriptionModificationReport ReportType;
	static Data::QName MessageType();
	static std::string NotificationName();
	static Data::QName PortType();
	static std::string Action();
};

struct EpisodicAlertReportTraits {
	typedef CDM::EpisodicAlertReport ReportType;
	static Data::QName MessageType();
	static std::string NotificationName();
	static Data::QName PortType();
	static std::string Action();
};

struct EpisodicContextChangedReportTraits {
	typedef CDM::EpisodicContextChangedReport ReportType;
	static Data::QName MessageType();
	static std::string NotificationName();	
	static Data::QName PortType();
	static std::string Action();
};

struct EpisodicMetricReportTraits {
	typedef CDM::EpisodicMetricReport ReportType;
	static Data::QName MessageType();
	static std::string NotificationName();
	static Data::QName PortType();
	static std::string Action();
};

struct OperationInvokedReportTraits {
	typedef CDM::OperationInvokedReport ReportType;
	static Data::QName MessageType();
	static std::string NotificationName();
	static Data::QName PortType();
	static std::string Action();
};

struct PeriodicAlertReportTraits {
	typedef CDM::PeriodicAlertReport ReportType;
	static Data::QName MessageType();
	static std::string NotificationName();
	static Data::QName PortType();
	static std::string Action();
};

struct PeriodicContextChangedReportTraits {
	typedef CDM::PeriodicContextChangedReport ReportType;
	static Data::QName MessageType();
	static std::string NotificationName();	
	static Data::QName PortType();
	static std::string Action();
};

struct PeriodicMetricReportTraits {
	typedef CDM::PeriodicMetricReport ReportType;
	static Data::QName MessageType();
	static std::string NotificationName();
	static Data::QName PortType();
	static std::string Action();
};

struct WaveformStreamTraits {
	typedef CDM::WaveformStream ReportType;
	static Data::QName MessageType();
	static std::string NotificationName();
	static Data::QName PortType();
	static std::string Action();
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* OSCPREPORTRAITS_H_ */
