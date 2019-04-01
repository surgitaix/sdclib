/*
 * EventReportServiceHandler.h
 *
 * Copyright 2016 SurgiTAIX AG
 *      Author: besting
 */

#ifndef OSCP_WAVEFORMREPORTSERVICEHANDLER_H_
#define OSCP_WAVEFORMREPORTSERVICEHANDLER_H_

#include "OSELib/fwd.h"
#include "OSELib/SOAP/HTTPRequestHandlerExceptionTrap.h"

namespace OSELib {
namespace SDC {

class WaveformReportServiceHandler : public SOAP::HTTPRequestHandlerExceptionTrap {
public:
	WaveformReportServiceHandler(IWaveformService & service, Helper::XercesGrammarPoolProvider & grammarProvider);

private:
	virtual void handleRequestImpl(Poco::Net::HTTPServerRequest & httpRequest, Poco::Net::HTTPServerResponse & httpResponse) override;

	IWaveformService & _service;
	Helper::XercesGrammarPoolProvider & _grammarProvider;
};

} /* namespace SDC */
} /* namespace OSELib */

#endif /* OSCP_WAVEFORMREPORTSERVICEHANDLER_H_ */
