/**
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  *
  */

/*
 * HTTPClientExchanger.h
 *
 *  @Copyright (C) 2015, SurgiTAIX AG
 *  Author: besting, roehser, baumeister
 */

#ifndef OSELIB_HTTP_HTTPCLIENTEXCHANGER_H_
#define OSELIB_HTTP_HTTPCLIENTEXCHANGER_H_

#include "OSELib/fwd.h"
#include "OSELib/Helper/WithLogger.h"

#include <string>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPSClientSession.h>

namespace OSELib
{
	namespace HTTP
	{
		class HTTPClientExchanger : public OSELib::Helper::WithLogger
		{
		public:
			HTTPClientExchanger();
			// Special Member Functions
			HTTPClientExchanger(const HTTPClientExchanger& p_obj) = default;
			HTTPClientExchanger(HTTPClientExchanger&& p_obj) = default;
			HTTPClientExchanger& operator=(const HTTPClientExchanger& p_obj) = default;
			HTTPClientExchanger& operator=(HTTPClientExchanger&& p_obj) = default;
			virtual ~HTTPClientExchanger() = default;

			std::string exchangeHttp(Poco::Net::HTTPClientSession & p_session, const std::string & p_path, const std::string & p_requestData);
			std::string exchangeHttp(Poco::Net::HTTPSClientSession & p_session, const std::string & p_path, const std::string & p_requestData);
		};
	}
}

#endif
