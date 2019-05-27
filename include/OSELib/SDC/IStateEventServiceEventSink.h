/*
 * IStateEventServiceEventSink.h
 *
 *  Created on: 10.12.2015
 *      Author: matthias
 */

#ifndef OSELIB_SDC_IEVENTREPORTEVENTSINK_H_
#define OSELIB_SDC_IEVENTREPORTEVENTSINK_H_

#include "OSELib/fwd.h"
#include "OSELib/DPWS/IEventSink.h"
#include "OSELib/SDC/ReportTraits.h"

namespace OSELib {
namespace SDC {

class IStateEventServiceEventSink : public DPWS::IEventSink {
public:
	virtual ~IStateEventServiceEventSink() = default;

	virtual void dispatch(const EpisodicAlertReportTraits::ReportType & request) = 0;
	virtual void dispatch(const EpisodicMetricReportTraits::ReportType & request) = 0;
	virtual void dispatch(const PeriodicAlertReportTraits::ReportType & request) = 0;
	virtual void dispatch(const PeriodicMetricReportTraits::ReportType & request) = 0;
	virtual void dispatch(const WaveformStreamTraits::ReportType & request) = 0;
};

} /* namespace SDC */
} /* namespace OSELib */

#endif /* OSELIB_SDC_IEVENTREPORTEVENTSINK_H_ */
