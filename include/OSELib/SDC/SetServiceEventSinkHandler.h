/*
 * SetServiceEventSink.h
 *
 *  Created on: 12.03.2019
 *      Author: buerger
 */

#ifndef OSELIB_SDC_SETSERVICEEVENTSINKHANDLER_H_
#define OSELIB_SDC_SETSERVICEEVENTSINKHANDLER_H_

#include "OSELib/fwd.h"
#include "OSELib/SOAP/HTTPRequestHandlerExceptionTrap.h"

namespace OSELib {
namespace SDC {

class SetServiceEventSinkHandler : public SOAP::HTTPRequestHandlerExceptionTrap {
public:
	SetServiceEventSinkHandler(ISetServiceEventSink & service, Helper::XercesGrammarPoolProvider & grammarProvider);

private:
	virtual void handleRequestImpl(Poco::Net::HTTPServerRequest & httpRequest, Poco::Net::HTTPServerResponse & httpResponse);

	ISetServiceEventSink & _service;
	Helper::XercesGrammarPoolProvider & _grammarProvider;
};

} /* namespace SDC */
} /* namespace OSELib */

#endif /* OSELIB_SDC_SETSERVICEEVENTSINKHANDLER_H_ */
