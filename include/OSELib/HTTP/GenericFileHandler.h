/*
 * DPWSGetMetadataRequestHandler.h
 *
 *  Created on: 25.07.2014
 *      Author: roehser
 */

#ifndef GENERICWSDLHANDLER_H_
#define GENERICWSDLHANDLER_H_

#include <string>

#include "Poco/Net/HTTPRequestHandler.h"

namespace OSELib {
namespace HTTP {

class GenericFileHandler : public Poco::Net::HTTPRequestHandler {
public:
	GenericFileHandler(const std::string & fileName);
	void handleRequest(Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse & resp);

private:
	const std::string fileName;
};

}
} /* namespace SDCLib */

#endif /* GENERICWSDLHANDLER_H_ */
