/*
 * ContextEventSinkHandler.cpp
 *
 *  Created on: 10.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 *
 */

#include "OSELib/SDC/ContextEventSinkHandler.h"
#include "OSELib/SDC/ReportTraits.h"
#include "OSELib/SOAP/Command.h"
#include "OSELib/SOAP/CommonSoapPreprocessing.h"
#include "OSELib/SOAP/GenericSoapEventCommand.h"
#include "OSELib/SOAP/SoapFaultCommand.h"
#include "OSELib/SOAP/SoapHTTPResponseWrapper.h"
#include "OSELib/Helper/Message.h"
#include "OSELib/Helper/XercesGrammarPoolProvider.h"


#include <Poco/Net/HTTPServerRequest.h>


namespace OSELib {
namespace SDC {

ContextEventSinkHandler::ContextEventSinkHandler(IContextServiceEventSink & p_service, Helper::XercesGrammarPoolProvider & p_grammarProvider)
: m_service(p_service)
, m_grammarProvider(p_grammarProvider)
{ }

void ContextEventSinkHandler::handleRequestImpl(Poco::Net::HTTPServerRequest & p_httpRequest, Poco::Net::HTTPServerResponse & p_httpResponse) {

	SOAP::CommonSoapPreprocessing t_soapHandling(m_grammarProvider);
	t_soapHandling.parse(p_httpRequest.stream());

	const auto t_soapAction(t_soapHandling.normalizedMessage->Header().Action().get());

	std::unique_ptr<SOAP::Command> t_command(new SOAP::SoapFaultCommand(p_httpResponse));

	if (t_soapAction == EpisodicContextReportTraits::Action()) {
		t_command = std::unique_ptr<SOAP::Command>(new SOAP::GenericSoapEventCommand<EpisodicContextReportTraits>(std::move(t_soapHandling.normalizedMessage), m_service));
	} else if (t_soapAction == PeriodicContextReportTraits::Action()) {
		t_command = std::unique_ptr<SOAP::Command>(new SOAP::GenericSoapEventCommand<PeriodicContextReportTraits>(std::move(t_soapHandling.normalizedMessage), m_service));
	} else {
		log_error([&] { return "ContextEventSinkHandler can't handle action: " + t_soapAction; });
	}

	std::unique_ptr<MESSAGEMODEL::Envelope> t_responseMessage(t_command->Run());

	// todo add proper soap fault handling in response

	SOAP::SoapHTTPResponseWrapper t_response(p_httpResponse, SOAP::SoapHTTPResponseWrapper::HTTPStatus::HTTP_ACCEPTED);
	t_response.send("");
	//fixme: Empty?
}

}
}
