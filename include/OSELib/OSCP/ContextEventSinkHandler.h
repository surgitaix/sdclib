/*
 * ContextEventSinkHandler.h
 *
 *  Created on: 10.12.2015
 *      Author: matthias
 */

#ifndef OSELIB_OSCP_CONTEXTEVENTSINKHANDLER_H_
#define OSELIB_OSCP_CONTEXTEVENTSINKHANDLER_H_

#include "OSELib/fwd.h"
#include "OSELib/SOAP/HTTPRequestHandlerExceptionTrap.h"

namespace OSELib {
namespace OSCP {

class ContextEventSinkHandler : public SOAP::HTTPRequestHandlerExceptionTrap {
public:
	ContextEventSinkHandler(IContextServiceEventSink & service, Helper::XercesGrammarPoolProvider & grammarProvider);

private:
	virtual void handleRequestImpl(Poco::Net::HTTPServerRequest & httpRequest, Poco::Net::HTTPServerResponse & httpResponse);

	IContextServiceEventSink & _service;
	Helper::XercesGrammarPoolProvider & _grammarProvider;
};

} /* namespace OSCP */
} /* namespace OSELib */

#endif /* OSELIB_OSCP_CONTEXTEVENTSINKHANDLER_H_ */
