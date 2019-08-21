/*
 * SetServiceEventSinkHandler.h
 *
 *  Created on: 12.03.2019, buerger
 *  Modified on: 21.08.2019, baumeister
 *
 */

#ifndef OSELIB_SDC_SETSERVICEEVENTSINKHANDLER_H_
#define OSELIB_SDC_SETSERVICEEVENTSINKHANDLER_H_

#include "OSELib/fwd.h"
#include "OSELib/SOAP/HTTPRequestHandlerExceptionTrap.h"

namespace OSELib
{
	namespace SDC
	{
		class SetServiceEventSinkHandler : public SOAP::HTTPRequestHandlerExceptionTrap
		{
		private:
			ISetServiceEventSink & m_service;
			Helper::XercesGrammarPoolProvider & m_grammarProvider;

		public:
			SetServiceEventSinkHandler(ISetServiceEventSink & p_service, Helper::XercesGrammarPoolProvider & p_grammarProvider);
			// Special Member Functions
			SetServiceEventSinkHandler(const SetServiceEventSinkHandler& p_obj) = delete;
			SetServiceEventSinkHandler(SetServiceEventSinkHandler&& p_obj) = delete;
			SetServiceEventSinkHandler& operator=(const SetServiceEventSinkHandler& p_obj) = delete;
			SetServiceEventSinkHandler& operator=(SetServiceEventSinkHandler&& p_obj) = delete;
			~SetServiceEventSinkHandler() = default;

		private:
			virtual void handleRequestImpl(Poco::Net::HTTPServerRequest & p_httpRequest, Poco::Net::HTTPServerResponse & p_httpResponse);
		};
	}
}

#endif
