/*
 * StaticContentController.h
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 20.08.2019, baumeister
 *
 */

#ifndef OSELIB_HTTP_STATICCONTENTCONTROLLER_H_
#define OSELIB_HTTP_STATICCONTENTCONTROLLER_H_

#include "OSELib/HTTP/Service.h"

namespace OSELib
{
	namespace HTTP
	{

		class StaticContentController : public Service
		{
		private:
			const std::string m_content;
		public:
			StaticContentController(FrontController & p_controller, const std::string & p_uri, const std::string & p_content);
			// Special Member Functions
			StaticContentController(const StaticContentController& p_obj) = default;
			StaticContentController(StaticContentController&& p_obj) = default;
			StaticContentController& operator=(const StaticContentController& p_obj) = default;
			StaticContentController& operator=(StaticContentController&& p_obj) = default;
			~StaticContentController() = default;

			Poco::Net::HTTPRequestHandler * createRequestHandler(const Poco::Net::HTTPServerRequest & p_httpRequest, bool p_SSL) override;

		};
	}
}

#endif
