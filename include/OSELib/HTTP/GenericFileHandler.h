/*
 * GenericFileHandler.h
 *
 *  Created on: 25.07.2014, roehser
 *  Modified on: 20.08.2019, baumeister
 *
 */

#ifndef OSELIB_HTTP_GENERICFILEHANDLER_H_
#define OSELIB_HTTP_GENERICFILEHANDLER_H_

#include <string>
#include <Poco/Net/HTTPRequestHandler.h>

namespace OSELib
{
	namespace HTTP
	{
		class GenericFileHandler : public Poco::Net::HTTPRequestHandler
		{
		private:
			const std::string m_fileName;
		public:
			GenericFileHandler(const std::string & p_fileName);
			// Special Member Functions
			GenericFileHandler(const GenericFileHandler& p_obj) = default;
			GenericFileHandler(GenericFileHandler&& p_obj) = default;
			GenericFileHandler& operator=(const GenericFileHandler& p_obj) = default;
			GenericFileHandler& operator=(GenericFileHandler&& p_obj) = default;
			~GenericFileHandler() = default;

			void handleRequest(Poco::Net::HTTPServerRequest& p_request, Poco::Net::HTTPServerResponse & p_response);
		};
	}
}

#endif
