/*
 * EventReportServiceHandler.h
 *
 * Copyright 2016 SurgiTAIX AG
 *      Author: besting
 */

#ifndef OSELIB_SDC_WAVEFORMREPORTSERVICEHANDLER_H_
#define OSELIB_SDC_WAVEFORMREPORTSERVICEHANDLER_H_

#include "OSELib/fwd.h"
#include "OSELib/SOAP/HTTPRequestHandlerExceptionTrap.h"

namespace OSELib {
namespace SDC {

class WaveformReportServiceHandler : public SOAP::HTTPRequestHandlerExceptionTrap {
public:
	WaveformReportServiceHandler(IWaveformService & service, Helper::XercesGrammarPoolProvider & grammarProvider, bool p_SSL);

private:
	void handleRequestImpl(Poco::Net::HTTPServerRequest & httpRequest, Poco::Net::HTTPServerResponse & httpResponse) override;

	IWaveformService & _service;
	Helper::XercesGrammarPoolProvider & _grammarProvider;
    const bool m_SSL = true;
};

} /* namespace SDC */
} /* namespace OSELib */

#endif /* OSELIB_SDC_WAVEFORMREPORTSERVICEHANDLER_H_ */
