/*
 * ContextServiceHandler.h
 *
 *  Created on: 09.12.2015
 *      Author: matthias
 */

#ifndef OSELIB_OSCP_CONTEXTSERVICEHANDLER_H_
#define OSELIB_OSCP_CONTEXTSERVICEHANDLER_H_

#include "OSELib/fwd.h"
#include "OSELib/SOAP/HTTPRequestHandlerExceptionTrap.h"

namespace OSELib {
namespace OSCP {

class ContextServiceHandler : public SOAP::HTTPRequestHandlerExceptionTrap {
public:
	ContextServiceHandler(IContextService & service, Helper::XercesGrammarPoolProvider & grammarProvider);

private:
	virtual void handleRequestImpl(Poco::Net::HTTPServerRequest & httpRequest, Poco::Net::HTTPServerResponse & httpResponse) override;

	IContextService & _service;
	Helper::XercesGrammarPoolProvider & _grammarProvider;
};

} /* namespace OSCP */
} /* namespace OSELib */

#endif /* OSELIB_OSCP_CONTEXTSERVICEHANDLER_H_ */
