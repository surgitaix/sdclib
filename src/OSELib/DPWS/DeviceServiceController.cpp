/*
 * DeviceServiceController.cpp
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 20.08.2019, baumeister
 */

#include "OSELib/DPWS/DeviceHandler.h"
#include "OSELib/DPWS/DeviceServiceController.h"
#include "OSELib/DPWS/IDevice.h"

namespace OSELib {
namespace DPWS {

DeviceServiceController::DeviceServiceController(HTTP::FrontController & p_controller, IDevice & p_serviceImpl)
: Service(p_controller, { p_serviceImpl.getBaseUri() })
, m_serviceImpl(p_serviceImpl)
{ }

Poco::Net::HTTPRequestHandler * DeviceServiceController::createRequestHandler(const Poco::Net::HTTPServerRequest & , bool p_SSL)
{
	return new DeviceHandler(m_serviceImpl, p_SSL);
}

} /* namespace DPWS */
} /* namespace OSELib */
