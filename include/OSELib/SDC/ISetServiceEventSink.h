/*
 * ISetServiceEventSink.h
 *
 *
 *	Dispatcher interface providing dispatcher functions for HTTP requests (HTTPRequesHandlerExeptionTrap).
 *	Called in GenericSoapInvoke and dispatching to SetServiceEventSinkHandler in the Consumer Adapter.
 *
 *  Created on: 12.03.2019, buerger
 *  Modified on: 21.08.2019, baumeister
 *
 */

#ifndef OSELIB_SDC_ISETSERVICEEVENTSINK_H_
#define OSELIB_SDC_ISETSERVICEEVENTSINK_H_

#include "OSELib/DPWS/IEventSink.h"
#include "OSELib/SDC/ReportTraits.h"

namespace OSELib
{
	namespace SDC
	{
		class ISetServiceEventSink : public DPWS::IEventSink
		{
		public:
			// Special Member Functions
			ISetServiceEventSink() = default;
			ISetServiceEventSink(const ISetServiceEventSink& p_obj) = default;
			ISetServiceEventSink(ISetServiceEventSink&& p_obj) = default;
			ISetServiceEventSink& operator=(const ISetServiceEventSink& p_obj) = default;
			ISetServiceEventSink& operator=(ISetServiceEventSink&& p_obj) = default;
			virtual ~ISetServiceEventSink() = default;

			virtual void dispatch(const OperationInvokedReportTraits::ReportType & request) = 0;
		};
	}
}

#endif
