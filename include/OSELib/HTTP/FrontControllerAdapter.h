/*
 * FrontControllerAdapter.h
 *
 *  Created on: 18.11.2015
 *      Author: matthias
 */

#ifndef FRONTCONTROLLERADAPTER_H_
#define FRONTCONTROLLERADAPTER_H_

#include "Poco/Net/HTTPRequestHandlerFactory.h"

#include "OSELib/fwd.h"
#include "OSELib/Helper/WithLogger.h"

namespace OSELib {
namespace HTTP {

class FrontControllerAdapter : public Poco::Net::HTTPRequestHandlerFactory, public WithLogger {
public:
	FrontControllerAdapter(FrontController & controller);
	virtual ~FrontControllerAdapter();

	Poco::Net::HTTPRequestHandler * createRequestHandler(const Poco::Net::HTTPServerRequest & request) override;

private:
	FrontController & _controller;
};

}
} /* namespace OSELib */

#endif /* FRONTCONTROLLERADAPTER_H_ */
