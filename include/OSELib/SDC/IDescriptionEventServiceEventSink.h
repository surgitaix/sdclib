/*
 * IDescriptionEventServiceEventSink.h
 *
 *  Created on: 09.10.2019, baumeister
 *
 */

#ifndef OSELIB_SDC_IDESCRIPTIONEVENTSERVICEEVENTSINK_H_
#define OSELIB_SDC_IDESCRIPTIONEVENTSERVICEEVENTSINK_H_

#include "OSELib/DPWS/IEventSink.h"
#include "OSELib/SDC/ReportTraits.h"

namespace OSELib
{
	namespace SDC
	{
		class IDescriptionEventServiceEventSink : public virtual OSELib::DPWS::IEventSink
		{
		public:
			// Special Member Functions
			IDescriptionEventServiceEventSink() = default;
			IDescriptionEventServiceEventSink(const IDescriptionEventServiceEventSink& p_obj) = delete;
			IDescriptionEventServiceEventSink(IDescriptionEventServiceEventSink&& p_obj) = delete;
			IDescriptionEventServiceEventSink& operator=(const IDescriptionEventServiceEventSink& p_obj) = delete;
			IDescriptionEventServiceEventSink& operator=(IDescriptionEventServiceEventSink&& p_obj) = delete;
			virtual ~IDescriptionEventServiceEventSink() = default;

			virtual void dispatch(const DescriptionModificationReportTraits::ReportType& p_request) = 0;
		};
	}
}

#endif
