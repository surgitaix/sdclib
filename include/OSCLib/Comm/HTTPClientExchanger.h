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

#ifndef INCLUDE_OSCLIB_COMM_HTTPCLIENTEXCHANGER_H_
#define INCLUDE_OSCLIB_COMM_HTTPCLIENTEXCHANGER_H_

#include <string>
#include <memory>
#include "Poco/Mutex.h"

namespace Poco {
namespace Net {
    class HTTPClientSession;
}
}

namespace OSCLib {
namespace Comm {

namespace DPWS {
	class DPWS11Message;
}

class HTTPClientExchanger {
public:
	HTTPClientExchanger();
	virtual ~HTTPClientExchanger();

    std::string exchangeHttp(Poco::Net::HTTPClientSession & session, std::string path, std::string requestData, bool isGet, int timeout = 0);
    std::shared_ptr<Comm::DPWS::DPWS11Message> exchangeHttp(const Comm::DPWS::DPWS11Message & dpws11Msg, int timeout = 0);


private:
    bool getContentFromStream(std::istream & req, std::string & result);
    mutable Poco::Mutex mutexHttpClient;

};

} /* namespace Comm */
} /* namespace OSCLib */

#endif /* INCLUDE_OSCLIB_COMM_HTTPCLIENTEXCHANGER_H_ */
