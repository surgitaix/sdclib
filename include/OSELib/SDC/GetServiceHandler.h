/*
 * GetServiceHandler.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef OSELIB_SDC_GETSERVICEHANDLER_H_
#define OSELIB_SDC_GETSERVICEHANDLER_H_

#include "OSELib/fwd.h"
#include "OSELib/SOAP/HTTPRequestHandlerExceptionTrap.h"

namespace OSELib {
namespace SDC {

class GetServiceHandler : public SOAP::HTTPRequestHandlerExceptionTrap {
public:
	GetServiceHandler(IGetService & service, Helper::XercesGrammarPoolProvider & grammarProvider, bool p_SSL);

private:
	virtual void handleRequestImpl(Poco::Net::HTTPServerRequest & httpRequest, Poco::Net::HTTPServerResponse & httpResponse);

	IGetService & _service;
	Helper::XercesGrammarPoolProvider & _grammarProvider;
    const bool m_SSL = true;
};

} /* namespace SDC */
} /* namespace OSELib */

#endif /* OSELIB_SDC_GETSERVICEHANDLER_H_ */
