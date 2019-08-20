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
 *  Author: besting, roehser
 */

#ifndef OSELIB_HTTP_HTTPCLIENTEXCHANGER_H_
#define OSELIB_HTTP_HTTPCLIENTEXCHANGER_H_

#include "OSELib/fwd.h"
#include "OSELib/Helper/WithLogger.h"

namespace OSELib {
namespace HTTP {

class HTTPClientExchanger : public OSELib::Helper::WithLogger
{
public:
	HTTPClientExchanger();
	virtual ~HTTPClientExchanger() = default;

    std::string exchangeHttp(Poco::Net::HTTPClientSession & session, const std::string & path, const std::string & requestData);
    std::string exchangeHttp(Poco::Net::HTTPSClientSession & session, const std::string & path, const std::string & requestData);
};

} /* namespace Comm */
} /* namespace SDCLib */

#endif /* OSELIB_HTTP_HTTPCLIENTEXCHANGER_H_ */
