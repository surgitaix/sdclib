/*
 * Service.h
 *
 *  Created on: 18.11.2015, matthias
 *  Modified on: 23.08.2019, baumeister
 *
 */

#ifndef OSELIB_HTTP_SERVICE_H_
#define OSELIB_HTTP_SERVICE_H_

#include <string>
#include <vector>

#include "OSELib/fwd.h"

namespace OSELib
{
	namespace HTTP
	{
		class Service
		{
		private:
			const std::vector<std::string> ml_uris;

		public:
			Service(FrontController & controller, const std::vector<std::string> & uris);
			// Special Member Functions
			Service(const Service& p_obj) = default;
			Service(Service&& p_obj) = default;
			Service& operator=(const Service& p_obj) = default;
			Service& operator=(Service&& p_obj) = default;
			virtual ~Service() = default;

			virtual Poco::Net::HTTPRequestHandler * createRequestHandler(const Poco::Net::HTTPServerRequest & request, bool p_SSL) = 0;

			const std::vector<std::string> & getUris() const;
		};
	}
}

#endif
