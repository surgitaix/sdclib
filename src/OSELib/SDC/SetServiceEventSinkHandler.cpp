/*
 *  SetServiceEventSinkHandler.cpp
 *
 *  Created on: 10.12.2015, matthias
 *  Modified on: 18.09.2019, baumeister
 *
 */

#include "OSELib/SDC/SetServiceEventSinkHandler.h"
#include "OSELib/DPWS/OperationTraits.h"
#include "OSELib/SDC/ReportTraits.h"
#include "OSELib/SOAP/Command.h"
#include "OSELib/SOAP/CommonSoapPreprocessing.h"
#include "OSELib/SOAP/GenericSoapEventCommand.h"
#include "OSELib/SOAP/SoapFaultCommand.h"
#include "OSELib/SOAP/SoapHTTPResponseWrapper.h"

#include "DataModel/NormalizedMessageModel.hxx"

#include <Poco/Net/HTTPServerRequest.h>

namespace OSELib {
namespace SDC {

SetServiceEventSinkHandler::SetServiceEventSinkHandler(ISetServiceEventSink& p_service, Helper::XercesGrammarPoolProvider & p_grammarProvider)
: m_service(p_service)
, m_grammarProvider(p_grammarProvider)
{ }

void SetServiceEventSinkHandler::handleRequestImpl(Poco::Net::HTTPServerRequest & p_httpRequest, Poco::Net::HTTPServerResponse & p_httpResponse) {

	SOAP::CommonSoapPreprocessing t_soapHandling(m_grammarProvider);
	t_soapHandling.parse(p_httpRequest.stream());

	const auto t_soapAction(t_soapHandling.normalizedMessage->getHeader().getAction().get());

	std::unique_ptr<SOAP::Command> t_command(new SOAP::SoapFaultCommand(p_httpResponse));


	if (t_soapAction == OperationInvokedReportTraits::Action()) {
		t_command = std::unique_ptr<SOAP::Command>(new SOAP::GenericSoapEventCommand<OperationInvokedReportTraits>(std::move(t_soapHandling.normalizedMessage), m_service));
	} else {
		log_error([&] { return "SetServiceEventSinkHandler can't handle action: " + t_soapAction; });
	}

	auto t_responseMessage(t_command->Run());

	// todo add proper soap fault handling in response

	SOAP::SoapHTTPResponseWrapper t_response(p_httpResponse, SOAP::SoapHTTPResponseWrapper::HTTPStatus::HTTP_ACCEPTED);
	t_response.send("");
}

}
}
