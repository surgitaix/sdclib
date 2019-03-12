/*
 * EventReportEventSinkHandler.h
 *
 *  Created on: 10.12.2015
 *      Author: matthias
 */

#ifndef OSELIB_OSCP_EVENTREPORTEVENTSINKHANDLER_H_
#define OSELIB_OSCP_EVENTREPORTEVENTSINKHANDLER_H_

#include "OSELib/fwd.h"
#include "OSELib/SOAP/HTTPRequestHandlerExceptionTrap.h"

namespace OSELib {
namespace SDC {

class StateEventServiceEventSinkHandler : public SOAP::HTTPRequestHandlerExceptionTrap {
public:
	StateEventServiceEventSinkHandler(IStateEventServiceEventSink & service, Helper::XercesGrammarPoolProvider & grammarProvider);

private:
	virtual void handleRequestImpl(Poco::Net::HTTPServerRequest & httpRequest, Poco::Net::HTTPServerResponse & httpResponse);

	IStateEventServiceEventSink & _service;
	Helper::XercesGrammarPoolProvider & _grammarProvider;
};

} /* namespace SDC */
} /* namespace OSELib */

#endif /* OSELIB_OSCP_EVENTREPORTEVENTSINKHANDLER_H_ */
