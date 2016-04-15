/*
 * IContextServiceEventSink.h
 *
 *  Created on: 10.12.2015
 *      Author: matthias
 */

#ifndef DATA_OSCP_ICONTEXTSERVICEEVENTSINK_H_
#define DATA_OSCP_ICONTEXTSERVICEEVENTSINK_H_

#include "OSELib/fwd.h"
#include "OSELib/DPWS/IEventSink.h"
#include "OSELib/OSCP/ReportTraits.h"

namespace OSELib {
namespace OSCP {

class IContextServiceEventSink : public DPWS::IEventSink {
public:
	virtual ~IContextServiceEventSink() = default;

	virtual void dispatch(const EpisodicContextChangedReportTraits::ReportType & request) = 0;
	virtual void dispatch(const PeriodicContextChangedReportTraits::ReportType & request) = 0;
};

} /* namespace OSCP */
} /* namespace OSELib */

#endif /* DATA_OSCP_ICONTEXTSERVICEEVENTSINK_H_ */
