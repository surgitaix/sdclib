/*
 * FrontController.cpp
 *
 *  Created on: 18.11.2015
 *      Author: matthias
 */

#include <iostream>
#include <string>

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"

#include "OSELib/HTTP/FrontController.h"
#include "OSELib/HTTP/Service.h"

namespace OSELib {
namespace HTTP {

FrontController::FrontController() :
	WithLogger(Log::HTTP)
{
}

void FrontController::addService(const std::string & uri, Service & service) {
	serviceControllers.emplace(uri, service);
}

Poco::Net::HTTPRequestHandler * FrontController::dispatchRequest(const Poco::Net::HTTPServerRequest & request) {
	auto match(serviceControllers.find(request.getURI()));
	if (match == serviceControllers.end()) {
		log_error([&] { return "No service controller for uri: " + request.getURI(); });
		return nullptr;
	} else {
		log_debug([&] { return "Dispatching to service controller for uri: " + request.getURI(); });
		if (request.getURI() == "/SetService") {
			log_debug([&] { return "Lalalalala"; });
		}
		return match->second.get().createRequestHandler(request);
	}
}

}
} /* namespace OSELib */
