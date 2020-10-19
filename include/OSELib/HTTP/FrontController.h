/*
 * FrontController.h
 *
 *  Created on: 18.11.2015, matthias
 *  Modified on: 20.08.2019, baumeister
 *
 */

#ifndef OSELIB_HTTP_FRONTCONTROLLER_H_
#define OSELIB_HTTP_FRONTCONTROLLER_H_

#include "OSELib/fwd.h"
#include "OSELib/Helper/WithLogger.h"

#include <functional>
#include <map>
#include <string>
#include <mutex>

namespace OSELib
{
	namespace HTTP {

		class FrontController : public OSELib::Helper::WithLogger
		{
		private:
			std::mutex m_mutex;
			bool m_SSL = true;
			std::map<std::string, std::reference_wrapper<Service>> ml_serviceControllers;

		public:

			FrontController();
			// Special Member Functions
			FrontController(const FrontController& p_obj) = delete;
			FrontController(FrontController&& p_obj) = delete;
			FrontController& operator=(const FrontController& p_obj) = delete;
			FrontController& operator=(FrontController&& p_obj) = delete;
			~FrontController() = default;


			void addService(const std::string & p_uri, Service & p_service);
			Poco::Net::HTTPRequestHandler * dispatchRequest(const Poco::Net::HTTPServerRequest & p_request);

			void setSSL(bool p_SSL) { m_SSL = p_SSL; }

		};
	}
}

#endif
