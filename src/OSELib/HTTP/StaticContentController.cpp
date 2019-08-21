/*
 * StaticContentController.cpp
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 20.08.2019, baumeister
 *
 */

#include "OSELib/HTTP/StaticContentController.h"
#include "OSELib/HTTP/FrontController.h"
#include "OSELib/HTTP/GenericContentHandler.h"

using namespace OSELib;
using namespace OSELib::HTTP;

StaticContentController::StaticContentController(FrontController & p_controller, const std::string & p_uri, const std::string & p_content)
: Service(p_controller, { p_uri })
, m_content(p_content)
{ }

Poco::Net::HTTPRequestHandler * StaticContentController::createRequestHandler(const Poco::Net::HTTPServerRequest & , bool)
{
	return new GenericContentHandler(m_content);
}

