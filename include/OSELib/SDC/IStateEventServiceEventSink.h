/*
 * IStateEventServiceEventSink.h
 *
 *  Created on: 10.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 *
 */

#ifndef OSELIB_SDC_IEVENTREPORTEVENTSINK_H_
#define OSELIB_SDC_IEVENTREPORTEVENTSINK_H_

#include "OSELib/DPWS/IEventSink.h"
#include "OSELib/SDC/ReportTraits.h"

namespace OSELib
{
	namespace SDC
	{
		class IStateEventServiceEventSink : public OSELib::DPWS::IEventSink
		{
		public:
			// Special Member Functions
			IStateEventServiceEventSink() = default;
			IStateEventServiceEventSink(const IStateEventServiceEventSink& p_obj) = default;
			IStateEventServiceEventSink(IStateEventServiceEventSink&& p_obj) = default;
			IStateEventServiceEventSink& operator=(const IStateEventServiceEventSink& p_obj) = default;
			IStateEventServiceEventSink& operator=(IStateEventServiceEventSink&& p_obj) = default;
			virtual ~IStateEventServiceEventSink() = default;

			virtual void dispatch(const EpisodicAlertReportTraits::ReportType & p_request) = 0;
			virtual void dispatch(const EpisodicMetricReportTraits::ReportType & p_request) = 0;
			virtual void dispatch(const PeriodicAlertReportTraits::ReportType & p_request) = 0;
			virtual void dispatch(const PeriodicMetricReportTraits::ReportType & p_request) = 0;
			virtual void dispatch(const WaveformStreamTraits::ReportType & p_request) = 0;
		};
	}
}

#endif
