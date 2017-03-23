/*
 * HTTPRequestHandlerExceptionTrap.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef SOAP_HTTPREQUESTHANDLEREXCEPTIONTRAP_H_
#define SOAP_HTTPREQUESTHANDLEREXCEPTIONTRAP_H_

#include "Poco/Net/HTTPRequestHandler.h"
#include "OSELib/Helper/WithLogger.h"

namespace OSELib {
namespace SOAP {

class HTTPRequestHandlerExceptionTrap : public Poco::Net::HTTPRequestHandler, public WithLogger {
public:
	HTTPRequestHandlerExceptionTrap();
	virtual ~HTTPRequestHandlerExceptionTrap();

	virtual void handleRequest(Poco::Net::HTTPServerRequest & httpRequest, Poco::Net::HTTPServerResponse & httpResponse) override;
	virtual void handleRequestImpl(Poco::Net::HTTPServerRequest & httpRequest, Poco::Net::HTTPServerResponse & httpResponse) = 0;
};

} /* namespace SOAP */
} /* namespace OSELib */

#endif /* SOAP_HTTPREQUESTHANDLEREXCEPTIONTRAP_H_ */
