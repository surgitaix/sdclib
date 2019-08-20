/*
 * FrontController.cpp
 *
 *  Created on: 18.11.2015
 *      Author: matthias
 */

#include "OSELib/HTTP/FrontController.h"
#include "OSELib/HTTP/Service.h"

#include <Poco/Net/HTTPServerRequest.h>

using namespace OSELib;
using namespace OSELib::HTTP;

FrontController::FrontController()
: OSELib::Helper::WithLogger(Log::HTTP)
{ }

void FrontController::addService(const std::string & uri, Service & service)
{
	std::lock_guard<std::mutex> t_lock(m_mutex);
	ml_serviceControllers.emplace(uri, service);
}

Poco::Net::HTTPRequestHandler * FrontController::dispatchRequest(const Poco::Net::HTTPServerRequest & request)
{
	std::lock_guard<std::mutex> t_lock(m_mutex);
	auto match(ml_serviceControllers.find(request.getURI()));
	if (match == ml_serviceControllers.end()) {
		log_error([&] { return "No service controller for uri: " + request.getURI(); });
		return nullptr;
	}
	log_debug([&] { return "Dispatching to service controller for uri: " + request.getURI(); });
	return match->second.get().createRequestHandler(request, m_SSL);
}
