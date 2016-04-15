/*
 * StaticContentController.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef HTTP_STATICCONTENTCONTROLLER_H_
#define HTTP_STATICCONTENTCONTROLLER_H_

#include "OSELib/HTTP/FrontController.h"
#include "OSELib/HTTP/GenericContentHandler.h"
#include "OSELib/HTTP/Service.h"

namespace OSELib {
namespace HTTP {

class StaticContentController : public Service {
public:
	StaticContentController(FrontController & controller, const std::string & uri, const std::string & content);

	virtual Poco::Net::HTTPRequestHandler * createRequestHandler(const Poco::Net::HTTPServerRequest & httpRequest) override;

private:
	const std::string _content;
};

} /* namespace HTTP */
} /* namespace OSELib */

#endif /* HTTP_STATICCONTENTCONTROLLER_H_ */
