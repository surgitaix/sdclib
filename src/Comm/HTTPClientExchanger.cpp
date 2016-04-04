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
 * HTTPClientExchanger.cpp
 *
 *  @Copyright (C) 2015, SurgiTAIX AG
 *  Author: besting, roehser
 */

#include "OSCLib/Comm/DPWS/DPWS11Message.h"
#include "OSCLib/Comm/Binding.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/NetException.h"
#include "OSCLib/Comm/HTTPClientExchanger.h"
#include <sstream>
#include "OSCLib/Util/DebugOut.h"

using namespace OSCLib::Util;

namespace OSCLib {
namespace Comm {

HTTPClientExchanger::HTTPClientExchanger() {

}

HTTPClientExchanger::~HTTPClientExchanger() {

}

bool HTTPClientExchanger::getContentFromStream(std::istream & req, std::string & result) {
    std::string tmp;
    tmp.reserve(16384);
    while (!req.eof()) {
        if (req.fail())
            return false;
        getline(req, tmp);
        result += tmp;
    }
    return true;
}


std::string HTTPClientExchanger::exchangeHttp(Poco::Net::HTTPClientSession & session, std::string path, std::string requestData, bool isGet, int timeout) {
    Poco::Mutex::ScopedLock lock(mutexHttpClient);
    std::string responseContent;
    try {
        path = path.empty() ? "/" : path.at(0) != '/'? "/" + path : path;
        Poco::Net::HTTPRequest req(isGet ? Poco::Net::HTTPRequest::HTTP_GET : Poco::Net::HTTPRequest::HTTP_POST,
            path, Poco::Net::HTTPMessage::HTTP_1_1);
        if (!isGet) {
            req.setContentType("application/soap+xml");
            req.setContentLength(requestData.length());
        }

        req.setKeepAlive(true);
        //if (timeout != 0) {
        //    Poco::Timespan ts(0L, timeout * 1000);
        //    session.setTimeout(ts);
        //}

        std::ostream& ostr = session.sendRequest(req);
        if (!isGet)
        {
            ostr << requestData;
            ostr.flush();
        }

        if (timeout < 0) {
        	// One-way message
        	return "";
        }

        if (timeout > 0) {
            Poco::Timespan ts(0L, timeout * 1000);
            Poco::Net::StreamSocket &str = session.socket();
            str.setReceiveTimeout(ts);
        }

        Poco::Net::HTTPResponse res;
        std::istream & is = session.receiveResponse(res);
        if (res.getStatus() != Poco::Net::HTTPResponse::HTTP_OK && res.getStatus() != Poco::Net::HTTPResponse::HTTP_ACCEPTED) {
            Util::DebugOut(Util::DebugOut::Error, "HTTPClientExchanger") << "HTTP request failed due to invalid HTTP response: " << res.getReason();
            return "";
        }
        responseContent.reserve(16384);
        if (!getContentFromStream(is, responseContent)) {
            Util::DebugOut(Util::DebugOut::Error, "HTTPClientExchanger") << "HTTP request failed due to stream fail.";
            return "";
        }
        return responseContent;
    }
    catch (Poco::Net::NoMessageException & e) {
    }
    catch (Poco::Exception & e) {
        DebugOut(DebugOut::Error, "HTTPClientExchanger") << "exchangeHttp() caused exception: " << e.message();
    }
    catch (...) {
        DebugOut(DebugOut::Error, "HTTPClientExchanger") << "exchangeHttp() caused exception.";
    }
    return responseContent;
}

std::shared_ptr<DPWS::DPWS11Message> HTTPClientExchanger::exchangeHttp(const DPWS::DPWS11Message & dpws11Msg, int timeout) {
	Poco::Mutex::ScopedLock lock(mutexHttpClient);
    Poco::Net::HTTPClientSession session(dpws11Msg.getDestination()->getIp(), dpws11Msg.getDestination()->getPort());

    std::string responseContent = exchangeHttp(session, dpws11Msg.getDestination()->getPath(), dpws11Msg.getRawBuffer(), false, timeout);
    if (responseContent.empty())
        return nullptr;

    std::shared_ptr<DPWS::DPWS11Message> incomingMsg = std::make_shared<DPWS::DPWS11Message>();
    incomingMsg->setSource(dpws11Msg.getDestination());
    incomingMsg->setReceiveProtocol(Message::TCP_HTTP);
    incomingMsg->setRouting(Message::UNICAST);
    incomingMsg->setRawBuffer(responseContent);

    return incomingMsg;
}

} /* namespace Comm */
} /* namespace OSCLib */
