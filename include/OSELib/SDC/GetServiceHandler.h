/*
 * GetServiceHandler.h
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 *
 */

#ifndef OSELIB_SDC_GETSERVICEHANDLER_H_
#define OSELIB_SDC_GETSERVICEHANDLER_H_

#include "OSELib/fwd.h"
#include "OSELib/SOAP/HTTPRequestHandlerExceptionTrap.h"

namespace OSELib
{
	namespace SDC
	{
		class GetServiceHandler : public SOAP::HTTPRequestHandlerExceptionTrap
		{
		private:
			IGetService & m_service;
			Helper::XercesGrammarPoolProvider & m_grammarProvider;
			const bool m_SSL = true;
		public:
			GetServiceHandler(IGetService & p_service, Helper::XercesGrammarPoolProvider & p_grammarProvider, bool p_SSL);
			// Special Member Functions
			GetServiceHandler(const GetServiceHandler& p_obj) = delete;
			GetServiceHandler(GetServiceHandler&& p_obj) = delete;
			GetServiceHandler& operator=(const GetServiceHandler& p_obj) = delete;
			GetServiceHandler& operator=(GetServiceHandler&& p_obj) = delete;
			~GetServiceHandler() = default;

		private:
			virtual void handleRequestImpl(Poco::Net::HTTPServerRequest & p_httpRequest, Poco::Net::HTTPServerResponse & p_httpResponse);

		};
	}
}

#endif
