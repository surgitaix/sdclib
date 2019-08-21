/*
 * FrontController.cpp
 *
 *  Created on: 18.11.2015, matthias
 *  Modified on: 20.08.2019, baumeister
 *
 */

#include "OSELib/HTTP/FrontController.h"
#include "OSELib/HTTP/Service.h"

#include <Poco/Net/HTTPServerRequest.h>

using namespace OSELib;
using namespace OSELib::HTTP;

FrontController::FrontController()
: OSELib::Helper::WithLogger(Log::HTTP)
{ }

void FrontController::addService(const std::string & p_uri, Service & p_service)
{
	std::lock_guard<std::mutex> t_lock(m_mutex);
	ml_serviceControllers.emplace(p_uri, p_service);
}

Poco::Net::HTTPRequestHandler * FrontController::dispatchRequest(const Poco::Net::HTTPServerRequest & p_request)
{
	std::lock_guard<std::mutex> t_lock(m_mutex);
	auto t_match(ml_serviceControllers.find(p_request.getURI()));
	if (t_match == ml_serviceControllers.end()) {
		log_error([&] { return "No service controller for uri: " + p_request.getURI(); });
		return nullptr;
	}
	log_debug([&] { return "Dispatching to service controller for uri: " + p_request.getURI(); });
	return t_match->second.get().createRequestHandler(p_request, m_SSL);
}
