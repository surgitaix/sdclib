/*
 * ContextServiceHandler.h
 *
 *  Created on: 09.12.2015
 *      Author: matthias
 */

#ifndef OSELIB_SDC_CONTEXTSERVICEHANDLER_H_
#define OSELIB_SDC_CONTEXTSERVICEHANDLER_H_

#include "OSELib/fwd.h"
#include "OSELib/SOAP/HTTPRequestHandlerExceptionTrap.h"

namespace OSELib {
namespace SDC {

class ContextServiceHandler : public SOAP::HTTPRequestHandlerExceptionTrap {
public:
	ContextServiceHandler(IContextService & service, Helper::XercesGrammarPoolProvider & grammarProvider);

private:
	void handleRequestImpl(Poco::Net::HTTPServerRequest & httpRequest, Poco::Net::HTTPServerResponse & httpResponse) override;

	IContextService & _service;
	Helper::XercesGrammarPoolProvider & _grammarProvider;
};

} /* namespace SDC */
} /* namespace OSELib */

#endif /* OSELIB_SDC_CONTEXTSERVICEHANDLER_H_ */
