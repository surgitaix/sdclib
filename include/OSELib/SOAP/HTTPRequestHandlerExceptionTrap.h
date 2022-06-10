/*
 * HTTPRequestHandlerExceptionTrap.h
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 *
 */

#ifndef SOAP_HTTPREQUESTHANDLEREXCEPTIONTRAP_H_
#define SOAP_HTTPREQUESTHANDLEREXCEPTIONTRAP_H_

#include "OSELib/Helper/WithLogger.h"
#include <Poco/Net/HTTPRequestHandler.h>

namespace OSELib
{
	namespace SOAP
	{
		class HTTPRequestHandlerExceptionTrap : public Poco::Net::HTTPRequestHandler, public OSELib::Helper::WithLogger
		{
		public:
			HTTPRequestHandlerExceptionTrap();
			virtual ~HTTPRequestHandlerExceptionTrap() = default;

			void handleRequest(Poco::Net::HTTPServerRequest & p_httpRequest, Poco::Net::HTTPServerResponse & p_httpResponse) override;
			virtual void handleRequestImpl(Poco::Net::HTTPServerRequest & p_httpRequest, Poco::Net::HTTPServerResponse & p_httpResponse) = 0;
		};
	}
}

#endif
