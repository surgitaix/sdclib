/*
 * DPWSGetMetadataRequestHandler.cpp
 *
 *  Created on: 25.07.2014
 *      Author: roehser
 */

#include <fstream>

#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"

#include "OSELib/HTTP/GenericFileHandler.h"

namespace OSELib {
namespace HTTP {

GenericFileHandler::GenericFileHandler(const std::string & fileName) :
		fileName(fileName)
{

}

void GenericFileHandler::handleRequest(Poco::Net::HTTPServerRequest&, Poco::Net::HTTPServerResponse & resp) {

	std::ifstream file;

	try {
		file.open(fileName.c_str(), std::ifstream::in);
	} catch (...) {
	}

	if (!file.is_open()) {
		resp.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
		resp.send();
		return;
	}

	std::string wsdl;
	while (!file.eof()) {
		std::string tmp;
		std::getline(file, tmp);
		wsdl += tmp;
	}
	file.close();

	resp.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
	resp.setContentType("application/xml");
	resp.setChunkedTransferEncoding(false);
	resp.setContentLength(wsdl.length());

	std::ostream & out = resp.send();
	out << wsdl << std::flush;
}

}
} /* namespace OSELib */
