/*
 * GenericContentHandler.h
 *
 *  Created on: 25.07.2014, roehser
 *  Modified on: 20.08.2019, baumeister
 *
 */

#ifndef OSELIB_HTTP_GENERICCONTENTHANDLER_H_
#define OSELIB_HTTP_GENERICCONTENTHANDLER_H_

#include <string>
#include <Poco/Net/HTTPRequestHandler.h>

namespace OSELib
{
	namespace HTTP
	{
		class GenericContentHandler : public Poco::Net::HTTPRequestHandler
		{
		private:
			const std::string m_content;

		public:
			GenericContentHandler(const std::string & p_content);
			// Special Member Functions
			GenericContentHandler(const GenericContentHandler& p_obj) = default;
			GenericContentHandler(GenericContentHandler&& p_obj) = default;
			GenericContentHandler& operator=(const GenericContentHandler& p_obj) = default;
			GenericContentHandler& operator=(GenericContentHandler&& p_obj) = default;
			~GenericContentHandler() = default;

			void handleRequest(Poco::Net::HTTPServerRequest& p_request, Poco::Net::HTTPServerResponse & p_response);

		};
	}
}

#endif
