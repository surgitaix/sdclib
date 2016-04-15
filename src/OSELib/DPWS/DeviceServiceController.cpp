/*
 * DeviceServiceController.cpp
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#include "OSELib/DPWS/DeviceHandler.h"
#include "OSELib/DPWS/DeviceServiceController.h"
#include "OSELib/DPWS/IDevice.h"

namespace OSELib {
namespace DPWS {

DeviceServiceController::DeviceServiceController(HTTP::FrontController & controller, IDevice & serviceImpl) :
	Service(controller, { serviceImpl.getBaseUri() }),
	_serviceImpl(serviceImpl)
{
}

DeviceServiceController::~DeviceServiceController() = default;

Poco::Net::HTTPRequestHandler * DeviceServiceController::createRequestHandler(const Poco::Net::HTTPServerRequest & ) {
	return new DeviceHandler(_serviceImpl);
}

} /* namespace DPWS */
} /* namespace OSELib */
