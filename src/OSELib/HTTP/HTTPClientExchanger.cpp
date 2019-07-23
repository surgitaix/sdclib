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

#include <sstream>

#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPSClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/NetException.h"

#include "OSELib/Helper/StreamReader.h"
#include "OSELib/HTTP/HTTPClientExchanger.h"

namespace OSELib {
namespace HTTP {

HTTPClientExchanger::HTTPClientExchanger() : WithLogger(Log::HTTP){

}

HTTPClientExchanger::~HTTPClientExchanger() {

}

std::string HTTPClientExchanger::exchangeHttp(Poco::Net::HTTPClientSession & session, const std::string & path, const std::string & requestData) {
    try {
    	Poco::Net::HTTPRequest req(Poco::Net::HTTPRequest::HTTP_POST, path, Poco::Net::HTTPMessage::HTTP_1_1);
        req.setContentType("application/soap+xml");
        req.setContentLength(requestData.length());
        req.setKeepAlive(false);

        session.setTimeout(1000000);
        std::ostream & ostr = session.sendRequest(req);
        ostr << requestData << std::flush;

        Poco::Net::HTTPResponse res;
        std::istream & is = session.receiveResponse(res);
        if (res.getStatus() != Poco::Net::HTTPResponse::HTTP_OK && res.getStatus() != Poco::Net::HTTPResponse::HTTP_ACCEPTED) {
        	// todo throw instead of debug out
        	log_error([&] { return "HTTP request failed due to invalid HTTP response: " + res.getReason(); });
//        	SDCLib::Util::DebugOut(SDCLib::Util::DebugOut::Error, "HTTPClientExchanger") << "HTTP request failed due to invalid HTTP response: " << res.getReason();
            return "";
        }
        std::string responseContent;
        responseContent.reserve(16384);

        Helper::StreamReader streamReader(is);
        responseContent = streamReader.getContent();
        return responseContent;
    } catch (const std::exception & e) {
    	log_error([&] { return std::string("Exception: " + std::string(e.what())); });
    	throw e;
    } catch (...) {
    	throw std::logic_error("Unknown error.");
    }
    return "";
}
std::string HTTPClientExchanger::exchangeHttp(Poco::Net::HTTPSClientSession & session, const std::string & path, const std::string & requestData) {
    try {
    	Poco::Net::HTTPRequest req(Poco::Net::HTTPRequest::HTTP_POST, path, Poco::Net::HTTPMessage::HTTP_1_1);
        req.setContentType("application/soap+xml");
        req.setContentLength(requestData.length());
        req.setKeepAlive(false);

        session.setTimeout(1000000);
        std::ostream & ostr = session.sendRequest(req);
        ostr << requestData << std::flush;

        Poco::Net::HTTPResponse res;
        std::istream & is = session.receiveResponse(res);
        if (res.getStatus() != Poco::Net::HTTPResponse::HTTP_OK && res.getStatus() != Poco::Net::HTTPResponse::HTTP_ACCEPTED) {
        	// todo throw instead of debug out
        	log_error([&] { return "HTTP request failed due to invalid HTTP response: " + res.getReason(); });
//        	SDCLib::Util::DebugOut(SDCLib::Util::DebugOut::Error, "HTTPClientExchanger") << "HTTP request failed due to invalid HTTP response: " << res.getReason();
            return "";
        }
        std::string responseContent;
        responseContent.reserve(16384);

        Helper::StreamReader streamReader(is);
        responseContent = streamReader.getContent();
        return responseContent;
    } catch (const std::exception & e) {
    	log_error([&] { return std::string("Exception: " + std::string(e.what())); });
    	throw e;
    } catch (...) {
    	throw std::logic_error("Unknown error.");
    }
    return "";
}

} /* namespace Comm */
} /* namespace SDCLib */
