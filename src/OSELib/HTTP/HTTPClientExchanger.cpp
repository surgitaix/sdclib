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
 *  Author: besting, roehser, baumeister
 */


#include "OSELib/HTTP/HTTPClientExchanger.h"
#include "OSELib/Helper/StreamReader.h"
#include "config/config.h"

#include <sstream>

#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/NetException.h>
#include <Poco/Net/SSLException.h>


namespace OSELib {
namespace HTTP {

HTTPClientExchanger::HTTPClientExchanger()
: OSELib::Helper::WithLogger(Log::HTTP)
{ }

std::string HTTPClientExchanger::exchangeHttp(Poco::Net::HTTPClientSession & p_session, const std::string & p_path, const std::string & p_requestData)
{

    std::string t_responseContent;
    t_responseContent.reserve(16384);
    Poco::Net::HTTPResponse t_response;
	try {
    	Poco::Net::HTTPRequest t_request(Poco::Net::HTTPRequest::HTTP_POST, p_path, Poco::Net::HTTPMessage::HTTP_1_1);
        t_request.setContentType("application/soap+xml");
        t_request.setContentLength(p_requestData.length());
        t_request.setKeepAlive(p_session.getKeepAlive());

        // Send
        std::ostream & t_ostr = p_session.sendRequest(t_request);
        t_ostr << p_requestData << std::flush;

        // Change socket timeout
		auto t_timeout_us = SDCLib::Config::SDC_CONNECTION_TIMEOUT_MS*1000;  // Convert to microseconds
		p_session.setTimeout(Poco::Timespan(t_timeout_us));
		p_session.setKeepAliveTimeout(Poco::Timespan(t_timeout_us));

        std::istream & t_is = p_session.receiveResponse(t_response);
        if (t_response.getStatus() != Poco::Net::HTTPResponse::HTTP_OK && t_response.getStatus() != Poco::Net::HTTPResponse::HTTP_ACCEPTED) {
        	// todo throw instead of debug out
        	log_error([&] { return "HTTP request failed due to invalid HTTP response: " + t_response.getReason(); });
//        	SDCLib::Util::DebugOut(SDCLib::Util::DebugOut::Error, "HTTPClientExchanger") << "HTTP request failed due to invalid HTTP response: " << res.getReason();
            return "";
        }
        Helper::StreamReader t_streamReader(t_is);
        t_responseContent = t_streamReader.getContent();
        return t_responseContent;
    } catch (Poco::Net::NetException& e) {
		log_error([&] { return "NetException: " + std::string(e.what()) + "\nResponse: " + t_responseContent; });
		throw e;
    } catch (const std::exception & e) {
    	log_error([&] { return std::string("Exception: " + std::string(e.what())) + "\nResponse: " + t_responseContent; });
    	throw e;
    } catch (...) {
    	throw std::logic_error("Unknown error.");
    }
    return "";
}
std::string HTTPClientExchanger::exchangeHttp(Poco::Net::HTTPSClientSession & p_session, const std::string & p_path, const std::string & p_requestData) {

    std::string t_responseContent;
    t_responseContent.reserve(16384);
	try {
    	Poco::Net::HTTPRequest t_request(Poco::Net::HTTPRequest::HTTP_POST, p_path, Poco::Net::HTTPMessage::HTTP_1_1);
    	t_request.setContentType("application/soap+xml");
    	t_request.setContentLength(p_requestData.length());
    	t_request.setKeepAlive(p_session.getKeepAlive());

    	// Send
        std::ostream & t_ostr = p_session.sendRequest(t_request);
        t_ostr << p_requestData << std::flush;

        // Change socket timeout
		auto t_timeout_us = SDCLib::Config::SDC_CONNECTION_TIMEOUT_MS*1000;  // Convert to microseconds
		p_session.setTimeout(Poco::Timespan(t_timeout_us));
		p_session.setKeepAliveTimeout(Poco::Timespan(t_timeout_us));

        Poco::Net::HTTPResponse t_response;
        std::istream & t_is = p_session.receiveResponse(t_response);
        if (t_response.getStatus() != Poco::Net::HTTPResponse::HTTP_OK && t_response.getStatus() != Poco::Net::HTTPResponse::HTTP_ACCEPTED) {
        	// todo throw instead of debug out
        	log_error([&] { return "HTTP request failed due to invalid HTTP response: " + t_response.getReason(); });
//        	SDCLib::Util::DebugOut(SDCLib::Util::DebugOut::Error, "HTTPClientExchanger") << "HTTP request failed due to invalid HTTP response: " << res.getReason();
            return "";
        }
        Helper::StreamReader t_streamReader(t_is);
        t_responseContent = t_streamReader.getContent();
        return t_responseContent;
	} catch (Poco::Net::SSLException& e) {
		log_error([&] { return "SSLException: " + std::string(e.what()) + "\nResponse: " + t_responseContent; });
    } catch (Poco::Net::NetException& e) {
		log_error([&] { return "NetException: " + std::string(e.what()) + "\nResponse: " + t_responseContent; });
		throw e;
	} catch (const std::exception & e) {
		log_error([&] { return std::string("Exception: " + std::string(e.what())) + "\nResponse: " + t_responseContent; });
		throw e;
    } catch (...) {
    	throw std::logic_error("Unknown error.");
    }
    return "";
}

}
}
