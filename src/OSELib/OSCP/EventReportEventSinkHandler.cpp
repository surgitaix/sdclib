/*
 * EventReportEventSinkHandler.cpp
 *
 *  Created on: 10.12.2015
 *      Author: matthias
 */

#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"

#include "NormalizedMessageModel.hxx"

#include "OSELib/DPWS/OperationTraits.h"
#include "OSELib/Helper/Message.h"
#include "OSELib/Helper/XercesDocumentWrapper.h"
#include "OSELib/Helper/XercesGrammarPoolProvider.h"
#include "OSELib/OSCP/EventReportEventSinkHandler.h"
#include "OSELib/OSCP/IGetService.h"
#include "OSELib/OSCP/ReportTraits.h"
#include "OSELib/SOAP/Command.h"
#include "OSELib/SOAP/CommonSoapPreprocessing.h"
#include "OSELib/SOAP/GenericSoapEventCommand.h"
#include "OSELib/SOAP/NormalizedMessageSerializer.h"
#include "OSELib/SOAP/SoapFaultCommand.h"
#include "OSELib/SOAP/SoapHTTPResponseWrapper.h"

namespace OSELib {
namespace SDC {

EventReportEventSinkHandler::EventReportEventSinkHandler(IEventReportEventSink & service, Helper::XercesGrammarPoolProvider & grammarProvider) :
	_service(service),
	_grammarProvider(grammarProvider)
{
}

void EventReportEventSinkHandler::handleRequestImpl(Poco::Net::HTTPServerRequest & httpRequest, Poco::Net::HTTPServerResponse & httpResponse) {

	SOAP::CommonSoapPreprocessing soapHandling(_grammarProvider);
	soapHandling.parse(httpRequest.stream());

	const auto soapAction(soapHandling.normalizedMessage->Header().Action().get());

	std::unique_ptr<SOAP::Command> command(new SOAP::SoapFaultCommand(httpResponse));

	if (soapAction == EpisodicAlertReportTraits::Action()) {
		command = std::unique_ptr<SOAP::Command>(new SOAP::GenericSoapEventCommand<EpisodicAlertReportTraits>(std::move(soapHandling.normalizedMessage), _service));
	} else if (soapAction == EpisodicMetricReportTraits::Action()) {
		command = std::unique_ptr<SOAP::Command>(new SOAP::GenericSoapEventCommand<EpisodicMetricReportTraits>(std::move(soapHandling.normalizedMessage), _service));
	} else if (soapAction == OperationInvokedReportTraits::Action()) {
		command = std::unique_ptr<SOAP::Command>(new SOAP::GenericSoapEventCommand<OperationInvokedReportTraits>(std::move(soapHandling.normalizedMessage), _service));
	} else if (soapAction == PeriodicAlertReportTraits::Action()) {
		command = std::unique_ptr<SOAP::Command>(new SOAP::GenericSoapEventCommand<PeriodicAlertReportTraits>(std::move(soapHandling.normalizedMessage), _service));
	} else if (soapAction == PeriodicMetricReportTraits::Action()) {
		command = std::unique_ptr<SOAP::Command>(new SOAP::GenericSoapEventCommand<PeriodicMetricReportTraits>(std::move(soapHandling.normalizedMessage), _service));
	} else {
		log_error([&] { return "EventReportEventSinkHandler can't handle action: " + soapAction; });
	}

	std::unique_ptr<MESSAGEMODEL::Envelope> responseMessage(command->Run());

	// todo add proper soap fault handling in response

	SOAP::SoapHTTPResponseWrapper response(httpResponse, SOAP::SoapHTTPResponseWrapper::HTTPStatus::HTTP_ACCEPTED);
	response.send("");
}

} /* namespace SDC */
} /* namespace OSELib */
