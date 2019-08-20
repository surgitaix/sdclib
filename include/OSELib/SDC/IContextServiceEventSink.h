/*
 * IContextServiceEventSink.h
 *
 *  Created on: 10.12.2015
 *      Author: matthias
 */

#ifndef OSELIB_SDC_ICONTEXTSERVICEEVENTSINK_H_
#define OSELIB_SDC_ICONTEXTSERVICEEVENTSINK_H_

#include "OSELib/fwd.h"
#include "OSELib/DPWS/IEventSink.h"
#include "OSELib/SDC/ReportTraits.h"

namespace OSELib {
namespace SDC {

class IContextServiceEventSink : public DPWS::IEventSink {
public:
	virtual ~IContextServiceEventSink() = default;

	virtual void dispatch(const EpisodicContextReportTraits::ReportType & request) = 0;
	virtual void dispatch(const PeriodicContextReportTraits::ReportType & request) = 0;
};

} /* namespace SDC */
} /* namespace OSELib */

#endif /* OSELIB_SDC_ICONTEXTSERVICEEVENTSINK_H_ */
