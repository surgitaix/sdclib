/*
 * DPWSGetMetadataRequestHandler.cpp
 *
 *  Created on: 25.07.2014
 *      Author: roehser
 */

#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"

#include "OSELib/HTTP/GenericContentHandler.h"

namespace OSELib {
namespace HTTP {

GenericContentHandler::GenericContentHandler(const std::string & content) :
		_content(content)
{

}

void GenericContentHandler::handleRequest(Poco::Net::HTTPServerRequest & , Poco::Net::HTTPServerResponse & resp) {
	resp.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
	resp.setContentType("application/xml");
	resp.setChunkedTransferEncoding(false);
	resp.setContentLength(_content.length());

	std::ostream & out = resp.send();
	out << _content << std::flush;
}

}
} /* namespace OSELib */
