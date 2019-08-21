/*
 * ContextServiceHandler.h
 *
 *  Created on: 09.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 *
 */

#ifndef OSELIB_SDC_CONTEXTSERVICEHANDLER_H_
#define OSELIB_SDC_CONTEXTSERVICEHANDLER_H_

#include "OSELib/fwd.h"
#include "OSELib/SOAP/HTTPRequestHandlerExceptionTrap.h"

namespace OSELib
{
	namespace SDC
	{
		class ContextServiceHandler : public SOAP::HTTPRequestHandlerExceptionTrap
		{
		private:
			IContextService & m_service;
			Helper::XercesGrammarPoolProvider & m_grammarProvider;
			const bool m_SSL = true;

		public:
			ContextServiceHandler(IContextService & p_service, Helper::XercesGrammarPoolProvider & p_grammarProvider, bool p_SSL);
			// Special Member Functions
			ContextServiceHandler(const ContextServiceHandler& p_obj) = default;
			ContextServiceHandler(ContextServiceHandler&& p_obj) = default;
			ContextServiceHandler& operator=(const ContextServiceHandler& p_obj) = default;
			ContextServiceHandler& operator=(ContextServiceHandler&& p_obj) = default;
			~ContextServiceHandler() = default;

		private:
			void handleRequestImpl(Poco::Net::HTTPServerRequest & p_httpRequest, Poco::Net::HTTPServerResponse & p_httpResponse) override;
		};
	}
}

#endif
