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

class GenericContentHandler : public Poco::Net::HTTPRequestHandler {
public:
	GenericContentHandler(const std::string & content);
	void handleRequest(Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse & resp);

private:
	const std::string _content;
};

}
} /* namespace OSCLib */

#endif /* GENERICWSDLHANDLER_H_ */
