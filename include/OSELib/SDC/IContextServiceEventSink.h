/*
 * IContextServiceEventSink.h
 *
 *  Created on: 10.12.2015, matthias
 *  Modified on: 26.09.2019, baumeister
 *
 */

#ifndef OSELIB_SDC_ICONTEXTSERVICEEVENTSINK_H_
#define OSELIB_SDC_ICONTEXTSERVICEEVENTSINK_H_

#include "OSELib/fwd.h"
#include "OSELib/DPWS/IEventSink.h"
#include "OSELib/SDC/ReportTraits.h"

namespace OSELib
{
	namespace SDC
	{
		class IContextServiceEventSink : public virtual DPWS::IEventSink
		{
		public:
			// Special Member Functions
			IContextServiceEventSink() = default;
			IContextServiceEventSink(const IContextServiceEventSink& p_obj) = delete;
			IContextServiceEventSink(IContextServiceEventSink&& p_obj) = delete;
			IContextServiceEventSink& operator=(const IContextServiceEventSink& p_obj) = delete;
			IContextServiceEventSink& operator=(IContextServiceEventSink&& p_obj) = delete;
			virtual ~IContextServiceEventSink() = default;

			virtual void dispatch(const EpisodicContextReportTraits::ReportType & p_request) = 0;
			virtual void dispatch(const PeriodicContextReportTraits::ReportType & p_request) = 0;
		};
	}
}

#endif
