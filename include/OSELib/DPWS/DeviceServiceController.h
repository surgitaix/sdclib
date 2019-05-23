/*
 * DeviceServiceController.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef DPWS_DEVICESERVICECONTROLLER_H_
#define DPWS_DEVICESERVICECONTROLLER_H_

#include "OSELib/fwd.h"
#include "OSELib/HTTP/Service.h"

namespace OSELib {
namespace DPWS {

class DeviceServiceController : public HTTP::Service {
public:
	DeviceServiceController(HTTP::FrontController & controller, IDevice & serviceImpl);

	virtual ~DeviceServiceController();

	Poco::Net::HTTPRequestHandler * createRequestHandler(const Poco::Net::HTTPServerRequest & request) override;

private:
	IDevice & _serviceImpl;
};

} /* namespace DPWS */
} /* namespace OSELib */

#endif /* DPWS_DEVICESERVICECONTROLLER_H_ */
