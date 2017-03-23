/*
 * SetServiceHandler.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef OSCP_SETSERVICEHANDLER_H_
#define OSCP_SETSERVICEHANDLER_H_

#include "OSELib/fwd.h"
#include "OSELib/SOAP/HTTPRequestHandlerExceptionTrap.h"

namespace OSELib {
namespace OSCP {

class SetServiceHandler : public SOAP::HTTPRequestHandlerExceptionTrap {
public:
	SetServiceHandler(ISetService & service, Helper::XercesGrammarPoolProvider & grammarProvider);

private:
	virtual void handleRequestImpl(Poco::Net::HTTPServerRequest & httpRequest, Poco::Net::HTTPServerResponse & httpResponse);

	ISetService & _service;
	Helper::XercesGrammarPoolProvider & _grammarProvider;
};

} /* namespace OSCP */
} /* namespace OSELib */

#endif /* OSCP_SETSERVICEHANDLER_H_ */
