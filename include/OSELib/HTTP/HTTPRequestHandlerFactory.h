/*
 * HTTPRequestHandlerFactory.h
 *
 *  Created on: 26.09.2019, baumeister
 *
 */

#ifndef OSELIB_HTTP_HTTPREQUESTHANDLERFACTORY_H_
#define OSELIB_HTTP_HTTPREQUESTHANDLERFACTORY_H_

#include "OSELib/fwd.h"
#include <memory>

namespace OSELib
{
	namespace HTTP
	{
		// NOTE: Currently just a qnd wrapper for Poco class!
		class HTTPRequestHandlerFactory
		{
		private:
			Poco::Net::HTTPRequestHandlerFactory* m_factory;

		public:
			HTTPRequestHandlerFactory(Poco::Net::HTTPRequestHandlerFactory* p_factory);
			// Special Member Functions
			HTTPRequestHandlerFactory(const HTTPRequestHandlerFactory& p_obj) = delete;
			HTTPRequestHandlerFactory(HTTPRequestHandlerFactory&& p_obj) = delete;
			HTTPRequestHandlerFactory& operator=(const HTTPRequestHandlerFactory& p_obj) = delete;
			HTTPRequestHandlerFactory& operator=(HTTPRequestHandlerFactory&& p_obj) = delete;
			~HTTPRequestHandlerFactory() = default;

			Poco::Net::HTTPRequestHandlerFactory* getFactory() { return m_factory; }
		};
	}
}

#endif
