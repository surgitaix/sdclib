/*
 * EventReportServiceHandler.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef OSCP_EVENTREPORTSERVICEHANDLER_H_
#define OSCP_EVENTREPORTSERVICEHANDLER_H_

#include "OSELib/fwd.h"
#include "OSELib/SOAP/HTTPRequestHandlerExceptionTrap.h"

namespace OSELib {
namespace OSCP {

class EventReportServiceHandler : public SOAP::HTTPRequestHandlerExceptionTrap {
public:
	EventReportServiceHandler(IEventReport & service, Helper::XercesGrammarPoolProvider & grammarProvider);

private:
	virtual void handleRequestImpl(Poco::Net::HTTPServerRequest & httpRequest, Poco::Net::HTTPServerResponse & httpResponse) override;

	IEventReport & _service;
	Helper::XercesGrammarPoolProvider & _grammarProvider;
};

} /* namespace OSCP */
} /* namespace OSELib */

#endif /* OSCP_EVENTREPORTSERVICEHANDLER_H_ */
