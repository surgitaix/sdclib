/*
 * SetServiceHandler.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef OSELIB_SDC_SETSERVICEHANDLER_H_
#define OSELIB_SDC_SETSERVICEHANDLER_H_

#include "OSELib/fwd.h"
#include "OSELib/SOAP/HTTPRequestHandlerExceptionTrap.h"

namespace OSELib {
namespace SDC {

class SetServiceHandler : public SOAP::HTTPRequestHandlerExceptionTrap {
public:
	SetServiceHandler(ISetService & service, Helper::XercesGrammarPoolProvider & grammarProvider);

private:
	virtual void handleRequestImpl(Poco::Net::HTTPServerRequest & httpRequest, Poco::Net::HTTPServerResponse & httpResponse);

	ISetService & _service;
	Helper::XercesGrammarPoolProvider & _grammarProvider;
};

} /* namespace SDC */
} /* namespace OSELib */

#endif /* OSELIB_SDC_SETSERVICEHANDLER_H_ */
