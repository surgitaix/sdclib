/*
 * StaticContentController.cpp
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#include "OSELib/HTTP/StaticContentController.h"

namespace OSELib {
namespace HTTP {

StaticContentController::StaticContentController(FrontController & controller, const std::string & uri, const std::string & content) :
	Service(controller, { uri }),
	_content(content)
{
}

Poco::Net::HTTPRequestHandler * StaticContentController::createRequestHandler(const Poco::Net::HTTPServerRequest & , bool) {
	return new GenericContentHandler(_content);
}

} /* namespace HTTP */
} /* namespace OSELib */
