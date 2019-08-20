/*
 * FrontControllerAdapter.cpp
 *
 *  Created on: 18.11.2015
 *      Author: matthias
 */
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>

#include "OSELib/HTTP/FrontController.h"
#include "OSELib/HTTP/FrontControllerAdapter.h"

namespace OSELib {
namespace HTTP {

FrontControllerAdapter::FrontControllerAdapter(FrontController & controller) :
	Poco::Net::HTTPRequestHandlerFactory(),
	OSELib::Helper::WithLogger(Log::HTTP),
	_controller(controller)
{
}

FrontControllerAdapter::~FrontControllerAdapter() = default;

Poco::Net::HTTPRequestHandler * FrontControllerAdapter::createRequestHandler(const Poco::Net::HTTPServerRequest & request) {
	log_debug([&] { return "Request for " + request.serverAddress().toString() + request.getURI(); });
	return _controller.dispatchRequest(request);
}

}
} /* namespace OSELib */
