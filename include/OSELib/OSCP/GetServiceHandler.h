/*
 * GetServiceHandler.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef OSCP_GETSERVICEHANDLER_H_
#define OSCP_GETSERVICEHANDLER_H_

#include "OSELib/fwd.h"
#include "OSELib/SOAP/HTTPRequestHandlerExceptionTrap.h"

namespace OSELib {
namespace OSCP {

class GetServiceHandler : public SOAP::HTTPRequestHandlerExceptionTrap {
public:
	GetServiceHandler(IGetService & service, Helper::XercesGrammarPoolProvider & grammarProvider);

private:
	virtual void handleRequestImpl(Poco::Net::HTTPServerRequest & httpRequest, Poco::Net::HTTPServerResponse & httpResponse);

	IGetService & _service;
	Helper::XercesGrammarPoolProvider & _grammarProvider;
};

} /* namespace OSCP */
} /* namespace OSELib */

#endif /* OSCP_GETSERVICEHANDLER_H_ */
