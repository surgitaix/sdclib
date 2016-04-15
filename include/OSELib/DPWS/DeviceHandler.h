/*
 * DeviceHandler.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef DPWS_DEVICEHANDLER_H_
#define DPWS_DEVICEHANDLER_H_

#include "OSELib/fwd.h"
#include "OSELib/SOAP/HTTPRequestHandlerExceptionTrap.h"

namespace OSELib {
namespace DPWS {

class DeviceHandler : public SOAP::HTTPRequestHandlerExceptionTrap {
public:
	DeviceHandler(IDevice & service);

private:
	virtual void handleRequestImpl(Poco::Net::HTTPServerRequest & httpRequest, Poco::Net::HTTPServerResponse & httpResponse);

	IDevice & _service;
};

} /* namespace OSCP */
} /* namespace OSELib */

#endif /* DPWS_DEVICEHANDLER_H_ */
