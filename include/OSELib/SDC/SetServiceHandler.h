/*
 * SetServiceHandler.h
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 *
 */

#ifndef OSELIB_SDC_SETSERVICEHANDLER_H_
#define OSELIB_SDC_SETSERVICEHANDLER_H_

#include "OSELib/fwd.h"
#include "OSELib/SOAP/HTTPRequestHandlerExceptionTrap.h"

namespace OSELib
{
	namespace SDC
	{
		class SetServiceHandler : public SOAP::HTTPRequestHandlerExceptionTrap
		{
		private:
			ISetService & m_service;
			Helper::XercesGrammarPoolProvider & m_grammarProvider;
			const bool m_SSL = true;
		public:

			SetServiceHandler(ISetService & service, Helper::XercesGrammarPoolProvider & grammarProvider, bool p_SSL);
			// Special Member Functions
			SetServiceHandler(const SetServiceHandler& p_obj) = delete;
			SetServiceHandler(SetServiceHandler&& p_obj) = delete;
			SetServiceHandler& operator=(const SetServiceHandler& p_obj) = delete;
			SetServiceHandler& operator=(SetServiceHandler&& p_obj) = delete;
			~SetServiceHandler() = default;

		private:
			virtual void handleRequestImpl(Poco::Net::HTTPServerRequest & httpRequest, Poco::Net::HTTPServerResponse & httpResponse);

		};
	}
}

#endif
