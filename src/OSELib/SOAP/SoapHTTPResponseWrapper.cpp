/*
 * SoapHTTPResponseWrapper.cpp
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 *
 */
#include "OSELib/SOAP/SoapHTTPResponseWrapper.h"

#include <Poco/Net/HTTPServerResponse.h>

namespace OSELib {
namespace SOAP {

SoapHTTPResponseWrapper::SoapHTTPResponseWrapper(Poco::Net::HTTPServerResponse & p_httpResponse, HTTPStatus p_httpStatus)
: OSELib::Helper::WithLogger(Log::HTTP)
, m_httpResponse(p_httpResponse)
, m_httpStatus(p_httpStatus)
{ }

void SoapHTTPResponseWrapper::send(const std::string & p_content)
{
	log_trace([&] { return "Delivering http response: " + p_content; });
	m_httpResponse.setStatus(m_httpStatus);
	m_httpResponse.setContentType("application/soap+xml");
	m_httpResponse.setContentLength(p_content.size());
	m_httpResponse.send() << p_content << std::flush;
}

}
}
