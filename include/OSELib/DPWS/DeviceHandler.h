/*
 * DeviceHandler.h
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 20.08.2019, baumeister
 *
 */

#ifndef OSELIB_DPWS_DEVICEHANDLER_H_
#define OSELIB_DPWS_DEVICEHANDLER_H_

#include "OSELib/fwd.h"
#include "OSELib/SOAP/HTTPRequestHandlerExceptionTrap.h"

namespace OSELib
{
	namespace DPWS
	{
		class DeviceHandler : public SOAP::HTTPRequestHandlerExceptionTrap
		{
		private:
			IDevice & m_service;
			const bool m_SSL = true;

		public:
			DeviceHandler(IDevice & p_service, bool p_SSL);
			// Special Member Functions
			DeviceHandler(const DeviceHandler& p_obj) = default;
			DeviceHandler(DeviceHandler&& p_obj) = default;
			DeviceHandler& operator=(const DeviceHandler& p_obj) = default;
			DeviceHandler& operator=(DeviceHandler&& p_obj) = default;
			~DeviceHandler() = default;

		private:
			virtual void handleRequestImpl(Poco::Net::HTTPServerRequest & p_httpRequest, Poco::Net::HTTPServerResponse & p_httpResponse);
		};

	}
}

#endif
