/*
 * DeviceServiceController.h
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 20.08.2019, baumeister
 */

#ifndef OSELIB_DPWS_DEVICESERVICECONTROLLER_H_
#define OSELIB_DPWS_DEVICESERVICECONTROLLER_H_

#include "OSELib/fwd.h"
#include "OSELib/HTTP/Service.h"

namespace OSELib
{
	namespace DPWS
	{
		class DeviceServiceController : public HTTP::Service
		{
		private:
			IDevice & m_serviceImpl;

		public:

			DeviceServiceController(HTTP::FrontController & p_controller, IDevice & p_serviceImpl);
			// Special Member Functions
			DeviceServiceController(const DeviceServiceController& p_obj) = delete;
			DeviceServiceController(DeviceServiceController&& p_obj) = delete;
			DeviceServiceController& operator=(const DeviceServiceController& p_obj) = delete;
			DeviceServiceController& operator=(DeviceServiceController&& p_obj) = delete;
			virtual ~DeviceServiceController() = default;

			Poco::Net::HTTPRequestHandler * createRequestHandler(const Poco::Net::HTTPServerRequest & p_request, bool p_SSL) override;
		};

	}
}

#endif
