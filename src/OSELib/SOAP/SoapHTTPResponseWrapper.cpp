/*
 * SoapHTTPResponseWrapper.cpp
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */
#include "OSELib/SOAP/SoapHTTPResponseWrapper.h"
#include "TCP/TCPClientEventHandler.h"


namespace OSELib {
namespace SOAP {

SoapHTTPResponseWrapper::SoapHTTPResponseWrapper(
		Poco::Net::HTTPServerResponse & httpResponse,
		HTTPStatus httpStatus
		) :
	WithLogger(Log::HTTP),
	_httpResponse(httpResponse),
	_httpStatus(httpStatus)
{
}

void SoapHTTPResponseWrapper::send(const std::string & content) {

	if(Network::TCPClientEventHandler::getInstance("127.0.0.1", 5000)->isConnected() && content != "")
	{
		std::cout << "OUTGOING SOAPHTTPResponseWar \n" << content << std::endl;
		Network::TCPClientEventHandler::getInstance("127.0.0.1", 5000)->sendRequest(content);
	}

	log_debug([&] { return "Delivering http response: " + content; });
	_httpResponse.setStatus(_httpStatus);
	_httpResponse.setContentType("application/soap+xml");
	_httpResponse.setContentLength(content.size());
	_httpResponse.send() << content << std::flush;
}

} /* namespace SOAP */
} /* namespace OSELib */
