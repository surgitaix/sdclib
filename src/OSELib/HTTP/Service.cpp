/*
 * Service.cpp
 *
 *  Created on: 18.11.2015
 *      Author: matthias
 */

#include "OSELib/HTTP/FrontController.h"
#include "OSELib/HTTP/Service.h"

namespace OSELib {
namespace HTTP {

Service::Service(FrontController & controller, const std::vector<std::string> & uris) : _uris(uris) {
	for (const auto & uri : uris) {
		controller.addService(uri, *this);
	}
}

Service::~Service() = default;

const std::vector<std::string> & Service::getUris() const {
	return _uris;
}

}
} /* namespace OSELib */
