/*
 * StateEventServiceEventSinkHandler.h
 *
 *  Created on: 10.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 *
 */

#ifndef OSELIB_SDC_STATEEVENTSERVICEEVENTSINKHANDLER_H_
#define OSELIB_SDC_STATEEVENTSERVICEEVENTSINKHANDLER_H_

#include "OSELib/fwd.h"
#include "OSELib/SOAP/HTTPRequestHandlerExceptionTrap.h"

namespace OSELib
{
	namespace SDC
	{
		class StateEventServiceEventSinkHandler : public SOAP::HTTPRequestHandlerExceptionTrap
		{
		private:
			IStateEventServiceEventSink & m_service;
			Helper::XercesGrammarPoolProvider & m_grammarProvider;

		public:
			StateEventServiceEventSinkHandler(IStateEventServiceEventSink & p_service, Helper::XercesGrammarPoolProvider & p_grammarProvider);
			// Special Member Functions
			StateEventServiceEventSinkHandler(const StateEventServiceEventSinkHandler& p_obj) = delete;
			StateEventServiceEventSinkHandler(StateEventServiceEventSinkHandler&& p_obj) = delete;
			StateEventServiceEventSinkHandler& operator=(const StateEventServiceEventSinkHandler& p_obj) = delete;
			StateEventServiceEventSinkHandler& operator=(StateEventServiceEventSinkHandler&& p_obj) = delete;
			~StateEventServiceEventSinkHandler() = default;

		private:
			virtual void handleRequestImpl(Poco::Net::HTTPServerRequest & p_httpRequest, Poco::Net::HTTPServerResponse & p_httpResponse);
		};
	}
}

#endif
