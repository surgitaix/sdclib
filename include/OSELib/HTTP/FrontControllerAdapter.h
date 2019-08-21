/*
 * FrontControllerAdapter.h
 *
 *  Created on: 18.11.2015
 *      Author: matthias
 */

#ifndef OSELIB_HTTP_FRONTCONTROLLERADAPTER_H_
#define OSELIB_HTTP_FRONTCONTROLLERADAPTER_H_

#include "OSELib/fwd.h"
#include "OSELib/Helper/WithLogger.h"

#include <Poco/Net/HTTPRequestHandlerFactory.h>

namespace OSELib
{
	namespace HTTP
	{
		class FrontControllerAdapter : public Poco::Net::HTTPRequestHandlerFactory, public OSELib::Helper::WithLogger
		{
		private:
			FrontController & m_controller;

		public:
			FrontControllerAdapter(FrontController & p_controller);
			// Special Member Functions
			FrontControllerAdapter(const FrontControllerAdapter& p_obj) = delete;
			FrontControllerAdapter(FrontControllerAdapter&& p_obj) = delete;
			FrontControllerAdapter& operator=(const FrontControllerAdapter& p_obj) = delete;
			FrontControllerAdapter& operator=(FrontControllerAdapter&& p_obj) = delete;
			virtual ~FrontControllerAdapter() = default;

			Poco::Net::HTTPRequestHandler * createRequestHandler(const Poco::Net::HTTPServerRequest & p_request) override;
		};
	}
}

#endif
