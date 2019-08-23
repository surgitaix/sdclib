/*
 * DPWSGetMetadataRequestHandler.cpp
 *
 *  Created on: 25.07.2014, roehser
 *  Modified on: 20.08.2019, baumeister
 *
 */


#include "OSELib/HTTP/GenericFileHandler.h"

#include <fstream>

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>


using namespace OSELib;
using namespace OSELib::HTTP;

GenericFileHandler::GenericFileHandler(const std::string & p_fileName)
: m_fileName(p_fileName)
{ }

void GenericFileHandler::handleRequest(Poco::Net::HTTPServerRequest&, Poco::Net::HTTPServerResponse & p_response) {

	std::ifstream t_file;

	try {
		t_file.open(m_fileName.c_str(), std::ifstream::in);
	} catch (...) {
	}

	if (!t_file.is_open()) {
		p_response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
		p_response.send();
		return;
	}

	std::string t_wsdl;
	while (!t_file.eof()) {
		std::string tmp;
		std::getline(t_file, tmp);
		t_wsdl += tmp;
	}
	t_file.close();

	p_response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
	p_response.setContentType("application/xml");
	p_response.setChunkedTransferEncoding(false);
	p_response.setContentLength(t_wsdl.length());

	std::ostream & t_out = p_response.send();
	t_out << t_wsdl << std::flush;
}
