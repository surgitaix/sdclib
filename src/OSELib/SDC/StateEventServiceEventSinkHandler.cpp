/*
 * StateEventServiceEventSinkHandler.cpp
 *
 *  Created on: 10.12.2015
 *  Modified on: 21.08.2019, baumeister
 *
 */

#include "OSELib/SDC/StateEventServiceEventSinkHandler.h"
#include "OSELib/SDC/IGetService.h"
#include "OSELib/SDC/ReportTraits.h"
#include "OSELib/SOAP/Command.h"
#include "OSELib/SOAP/CommonSoapPreprocessing.h"
#include "OSELib/SOAP/GenericSoapEventCommand.h"
#include "OSELib/SOAP/NormalizedMessageSerializer.h"
#include "OSELib/SOAP/SoapFaultCommand.h"
#include "OSELib/SOAP/SoapHTTPResponseWrapper.h"

#include "DataModel/NormalizedMessageModel.hxx"

#include <Poco/Net/HTTPServerRequest.h>

namespace OSELib {
namespace SDC {

StateEventServiceEventSinkHandler::StateEventServiceEventSinkHandler(IStateEventServiceEventSink & p_service, Helper::XercesGrammarPoolProvider & p_grammarProvider)
: m_service(p_service)
, m_grammarProvider(p_grammarProvider)
{ }

void StateEventServiceEventSinkHandler::handleRequestImpl(Poco::Net::HTTPServerRequest & p_httpRequest, Poco::Net::HTTPServerResponse & p_httpResponse)
{
	SOAP::CommonSoapPreprocessing t_soapHandling(m_grammarProvider);
	t_soapHandling.parse(p_httpRequest.stream());

	const auto t_soapAction(t_soapHandling.normalizedMessage->Header().Action().get());

	std::unique_ptr<SOAP::Command> t_command(new SOAP::SoapFaultCommand(p_httpResponse));

	if (t_soapAction == EpisodicAlertReportTraits::Action()) {
		t_command = std::unique_ptr<SOAP::Command>(new SOAP::GenericSoapEventCommand<EpisodicAlertReportTraits>(std::move(t_soapHandling.normalizedMessage), m_service));
	} else if (t_soapAction == EpisodicComponentReportTraits::Action()) {
		t_command = std::unique_ptr<SOAP::Command>(new SOAP::GenericSoapEventCommand<EpisodicComponentReportTraits>(std::move(t_soapHandling.normalizedMessage), m_service));
	} else if (t_soapAction == EpisodicMetricReportTraits::Action()) {
		t_command = std::unique_ptr<SOAP::Command>(new SOAP::GenericSoapEventCommand<EpisodicMetricReportTraits>(std::move(t_soapHandling.normalizedMessage), m_service));
	} else if (t_soapAction == EpisodicOperationalStateReportTraits::Action()) {
		t_command = std::unique_ptr<SOAP::Command>(new SOAP::GenericSoapEventCommand<EpisodicOperationalStateReportTraits>(std::move(t_soapHandling.normalizedMessage), m_service));
	} else if (t_soapAction == PeriodicAlertReportTraits::Action()) {
		t_command = std::unique_ptr<SOAP::Command>(new SOAP::GenericSoapEventCommand<PeriodicAlertReportTraits>(std::move(t_soapHandling.normalizedMessage), m_service));
	} else if (t_soapAction == PeriodicMetricReportTraits::Action()) {
		t_command = std::unique_ptr<SOAP::Command>(new SOAP::GenericSoapEventCommand<PeriodicMetricReportTraits>(std::move(t_soapHandling.normalizedMessage), m_service));
	} else {
		log_error([&] { return "StateEventServiceEventSinkHandler can't handle action: " + t_soapAction; });
	}

	std::unique_ptr<MESSAGEMODEL::Envelope> t_responseMessage(t_command->Run());

	// todo add proper soap fault handling in response

	SOAP::SoapHTTPResponseWrapper t_response(p_httpResponse, SOAP::SoapHTTPResponseWrapper::HTTPStatus::HTTP_ACCEPTED);
	t_response.send("");
}

}
}
