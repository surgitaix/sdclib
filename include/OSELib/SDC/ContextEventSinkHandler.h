/*
 * ContextEventSinkHandler.h
 *
 *  Created on: 10.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 *
 */

#ifndef OSELIB_SDC_CONTEXTEVENTSINKHANDLER_H_
#define OSELIB_SDC_CONTEXTEVENTSINKHANDLER_H_

#include "OSELib/fwd.h"
#include "OSELib/SOAP/HTTPRequestHandlerExceptionTrap.h"

namespace OSELib
{
	namespace SDC
	{
		class ContextEventSinkHandler : public SOAP::HTTPRequestHandlerExceptionTrap
		{
		private:
			IContextServiceEventSink & m_service;
			Helper::XercesGrammarPoolProvider & m_grammarProvider;

		public:
			ContextEventSinkHandler(IContextServiceEventSink & service, Helper::XercesGrammarPoolProvider & grammarProvider);
			// Special Member Functions
			ContextEventSinkHandler(const ContextEventSinkHandler& p_obj) = delete;
			ContextEventSinkHandler(ContextEventSinkHandler&& p_obj) = delete;
			ContextEventSinkHandler& operator=(const ContextEventSinkHandler& p_obj) = delete;
			ContextEventSinkHandler& operator=(ContextEventSinkHandler&& p_obj) = delete;
			~ContextEventSinkHandler() = default;

		private:

			virtual void handleRequestImpl(Poco::Net::HTTPServerRequest & httpRequest, Poco::Net::HTTPServerResponse & httpResponse);

		};
	}
}

#endif
