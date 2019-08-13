/*
 * EventReportServiceHandler.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef OSELib_SDC_EVENTREPORTSERVICEHANDLER_H_
#define OSELib_SDC_EVENTREPORTSERVICEHANDLER_H_

#include "OSELib/fwd.h"
#include "OSELib/SOAP/HTTPRequestHandlerExceptionTrap.h"

namespace OSELib {
namespace SDC {

class EventReportServiceHandler : public SOAP::HTTPRequestHandlerExceptionTrap {
public:
	EventReportServiceHandler(IEventReport & service, Helper::XercesGrammarPoolProvider & grammarProvider, bool p_SSL);

private:
	void handleRequestImpl(Poco::Net::HTTPServerRequest & httpRequest, Poco::Net::HTTPServerResponse & httpResponse) override;

	IEventReport & _service;
	Helper::XercesGrammarPoolProvider & _grammarProvider;
    const bool m_SSL = true;
};

} /* namespace SDC */
} /* namespace OSELib */

#endif /* OSELib_SDC_EVENTREPORTSERVICEHANDLER_H_ */
