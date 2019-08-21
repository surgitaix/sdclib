/*
 * Service.cpp
 *
 *  Created on: 18.11.2015, matthias
 *  Modified on: 20.08.2019, baumeister
 */

#include "OSELib/HTTP/Service.h"
#include "OSELib/HTTP/FrontController.h"


using namespace OSELib;
using namespace OSELib::HTTP;

Service::Service(FrontController & p_controller, const std::vector<std::string> & p_uris)
: m_uris(p_uris)
{
	for (const auto & t_uri : p_uris) {
		p_controller.addService(t_uri, *this);
	}
}

const std::vector<std::string> & Service::getUris() const {
	return m_uris;
}
