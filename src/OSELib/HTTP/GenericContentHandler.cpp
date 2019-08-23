/*
 * GenericContentHandler.cpp
 *
 *  Created on: 25.07.2014, roehser
 *  Modified on: 20.08.2019, baumeister
 */

#include "OSELib/HTTP/GenericContentHandler.h"

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>


using namespace OSELib;
using namespace OSELib::HTTP;

GenericContentHandler::GenericContentHandler(const std::string & p_content)
: m_content(p_content)
{ }

void GenericContentHandler::handleRequest(Poco::Net::HTTPServerRequest&, Poco::Net::HTTPServerResponse & p_response)
{
	p_response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
	p_response.setContentType("application/xml");
	p_response.setChunkedTransferEncoding(false);
	p_response.setContentLength(m_content.length());

	std::ostream & t_out = p_response.send();
	t_out << m_content << std::flush;
}

