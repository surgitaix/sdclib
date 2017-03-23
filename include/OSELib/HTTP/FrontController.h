/*
 * FrontController.h
 *
 *  Created on: 18.11.2015
 *      Author: matthias
 */

#ifndef FRONTCONTROLLER_H_
#define FRONTCONTROLLER_H_

#include <functional>
#include <map>
#include <string>

#include "OSELib/fwd.h"
#include "OSELib/Helper/WithLogger.h"

namespace OSELib {
namespace HTTP {

class FrontController : public WithLogger {
public:
	FrontController();

	void addService(const std::string & uri, Service & service);
	Poco::Net::HTTPRequestHandler * dispatchRequest(const Poco::Net::HTTPServerRequest & request);

private:
	std::map<std::string, std::reference_wrapper<Service>> serviceControllers;
};

}
} /* namespace OSELib */

#endif /* FRONTCONTROLLER_H_ */
