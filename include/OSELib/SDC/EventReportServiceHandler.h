/*
 * EventReportServiceHandler.h
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 *
 */

#ifndef OSELib_SDC_EVENTREPORTSERVICEHANDLER_H_
#define OSELib_SDC_EVENTREPORTSERVICEHANDLER_H_

#include "OSELib/fwd.h"
#include "OSELib/SOAP/HTTPRequestHandlerExceptionTrap.h"

namespace OSELib
{
	namespace SDC
	{
		class EventReportServiceHandler : public SOAP::HTTPRequestHandlerExceptionTrap
		{
		private:
			IEventReport & m_service;
			Helper::XercesGrammarPoolProvider & m_grammarProvider;
			const bool m_SSL = true;

		public:
			EventReportServiceHandler(IEventReport & p_service, Helper::XercesGrammarPoolProvider & p_grammarProvider, bool p_SSL);
			// Special Member Functions
			EventReportServiceHandler(const EventReportServiceHandler& p_obj) = delete;
			EventReportServiceHandler(EventReportServiceHandler&& p_obj) = delete;
			EventReportServiceHandler& operator=(const EventReportServiceHandler& p_obj) = delete;
			EventReportServiceHandler& operator=(EventReportServiceHandler&& p_obj) = delete;
			~EventReportServiceHandler() = default;

		private:
			void handleRequestImpl(Poco::Net::HTTPServerRequest & p_httpRequest, Poco::Net::HTTPServerResponse & p_httpResponse) override;

		};

	}
}

#endif
