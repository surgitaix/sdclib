/*
 * ISetServiceEventSink.h
 *
 *
 *	Dispatcher interface providing dispatcher functions for HTTP requests (HTTPRequesHandlerExeptionTrap).
 *	Called in GenericSoapInvoke and dispatching to SetServiceEventSinkHandler in the Consumer Adapter.
 *
 *  Created on: 12.03.2019
 *      Author: buerger
 */

#ifndef DATA_OSCP_ISETSERVICEEVENTSINK_H_
#define DATA_OSCP_ISETSERVICEEVENTSINK_H_

#include "OSELib/fwd.h"
#include "OSELib/DPWS/IEventSink.h"
#include "OSELib/SDC/ReportTraits.h"

namespace OSELib {
namespace SDC {

class ISetServiceEventSink : public DPWS::IEventSink {
public:
	virtual ~ISetServiceEventSink() = default;

	virtual void dispatch(const OperationInvokedReportTraits::ReportType & request) = 0;
};

} /* namespace SDC */
} /* namespace OSELib */

#endif /* DATA_OSCP_ISETSERVICEEVENTSINK_H_ */
