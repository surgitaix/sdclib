/*
 * EventReportServiceHandler.h
 *
 * Copyright 2016 SurgiTAIX AG
 *      Author: besting
 * Modified on: 21.08.2019, baumeister
 *
 */

#ifndef OSELIB_SDC_WAVEFORMREPORTSERVICEHANDLER_H_
#define OSELIB_SDC_WAVEFORMREPORTSERVICEHANDLER_H_

#include "OSELib/fwd.h"
#include "OSELib/SOAP/HTTPRequestHandlerExceptionTrap.h"

namespace OSELib
{
	namespace SDC
	{
		class WaveformReportServiceHandler : public SOAP::HTTPRequestHandlerExceptionTrap
		{
		private:
			IWaveformService & m_service;
			Helper::XercesGrammarPoolProvider & m_grammarProvider;
			const bool m_SSL = true;
		public:
			WaveformReportServiceHandler(IWaveformService & p_service, Helper::XercesGrammarPoolProvider & p_grammarProvider, bool p_SSL);
			// Special Member Functions
			WaveformReportServiceHandler(const WaveformReportServiceHandler& p_obj) = delete;
			WaveformReportServiceHandler(WaveformReportServiceHandler&& p_obj) = delete;
			WaveformReportServiceHandler& operator=(const WaveformReportServiceHandler& p_obj) = delete;
			WaveformReportServiceHandler& operator=(WaveformReportServiceHandler&& p_obj) = delete;
			~WaveformReportServiceHandler() = default;

		private:

			void handleRequestImpl(Poco::Net::HTTPServerRequest & p_httpRequest, Poco::Net::HTTPServerResponse & p_httpResponse) override;

		};
	}
}

#endif
