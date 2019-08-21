/*
 * FrontControllerAdapter.cpp
 *
 *  Created on: 18.11.2015, matthias
 *  Modified on: 20.08.2019, baumeister
 *
 */

#include "OSELib/HTTP/FrontControllerAdapter.h"
#include "OSELib/HTTP/FrontController.h"


#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>


using namespace OSELib;
using namespace OSELib::HTTP;

FrontControllerAdapter::FrontControllerAdapter(FrontController & p_controller)
: Poco::Net::HTTPRequestHandlerFactory()
, OSELib::Helper::WithLogger(Log::HTTP)
, m_controller(p_controller)
{ }


Poco::Net::HTTPRequestHandler * FrontControllerAdapter::createRequestHandler(const Poco::Net::HTTPServerRequest & p_request)
{
	log_debug([&] { return "Request for " + p_request.serverAddress().toString() + p_request.getURI(); });
	return m_controller.dispatchRequest(p_request);
}
