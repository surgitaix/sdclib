/*
 * ContextServiceHandler.cpp
 *
 *  Created on: 09.12.2015, matthias
 *  Modified on: 22.08.2019, baumeister
 *
 */

#include "OSELib/SDC/ContextServiceHandler.h"
#include "OSELib/SDC/IContextService.h"
#include "OSELib/SOAP/Command.h"
#include "OSELib/SOAP/CommonSoapPreprocessing.h"
#include "OSELib/SOAP/GetMetadataActionCommand.h"
#include "OSELib/SOAP/GenericSoapActionCommand.h"
#include "OSELib/SOAP/NormalizedMessageSerializer.h"
#include "OSELib/SOAP/RenewActionCommand.h"
#include "OSELib/SOAP/SoapFaultCommand.h"
#include "OSELib/SOAP/SoapHTTPResponseWrapper.h"
#include "OSELib/SOAP/SubscribeActionCommand.h"
#include "OSELib/SOAP/UnsubscribeActionCommand.h"
#include "OSELib/SOAP/GetStatusActionCommand.h"

#include "DataModel/NormalizedMessageModel.hxx"

#include <Poco/Net/HTTPServerRequest.h>


namespace OSELib {
namespace SDC {

ContextServiceHandler::ContextServiceHandler(IContextService & p_service, Helper::XercesGrammarPoolProvider & p_grammarProvider, bool p_SSL)
: m_service(p_service)
, m_grammarProvider(p_grammarProvider)
, m_SSL(p_SSL)
{ }

void ContextServiceHandler::handleRequestImpl(Poco::Net::HTTPServerRequest & p_httpRequest, Poco::Net::HTTPServerResponse & p_httpResponse)
{
	SOAP::CommonSoapPreprocessing t_soapHandling(m_grammarProvider);
	t_soapHandling.parse(p_httpRequest.stream());

	const auto t_soapAction(t_soapHandling.normalizedMessage->Header().Action().get());

	std::unique_ptr<SOAP::Command> t_command(new SOAP::SoapFaultCommand(p_httpResponse));

	if (t_soapAction == DPWS::GetMetadataTraits::RequestAction()) {
		const std::string t_serverAddress(p_httpRequest.serverAddress().toString());
		t_command = std::unique_ptr<SOAP::Command>(new SOAP::GetMetadataActionCommand(std::move(t_soapHandling.normalizedMessage), m_service.getMetadata(t_serverAddress, m_SSL)));
	} else if (t_soapAction == GetContextStatesTraits::RequestAction()) {
		t_command = std::unique_ptr<SOAP::Command>(new SOAP::GenericSoapActionCommand<GetContextStatesTraits>(std::move(t_soapHandling.normalizedMessage), m_service));
	} else if (t_soapAction == SetContextStateTraits::RequestAction()) {
		t_command = std::unique_ptr<SOAP::Command>(new SOAP::GenericSoapActionCommand<SetContextStateTraits>(std::move(t_soapHandling.normalizedMessage), m_service));
	} else if (t_soapAction == DPWS::SubscribeTraits::RequestAction()) {
        std::string ts_PROTOCOL = "http";
        if(m_SSL) { ts_PROTOCOL.append("s"); }
		const std::string t_subscriptionManagerAddress(ts_PROTOCOL + "://" + p_httpRequest.serverAddress().toString() + m_service.getBaseUri());
		t_command = std::unique_ptr<SOAP::Command>(new SOAP::SubscribeActionCommand(std::move(t_soapHandling.normalizedMessage), m_service, t_subscriptionManagerAddress));
	} else if (t_soapAction == DPWS::UnsubscribeTraits::RequestAction()) {
		t_command = std::unique_ptr<SOAP::Command>(new SOAP::UnsubscribeActionCommand(std::move(t_soapHandling.normalizedMessage), m_service));
	} else if (t_soapAction == DPWS::RenewTraits::RequestAction()) {
		t_command = std::unique_ptr<SOAP::Command>(new SOAP::RenewActionCommand(std::move(t_soapHandling.normalizedMessage), m_service));
    } else if (t_soapAction == DPWS::GetStatusTraits::RequestAction()) {
    	t_command = std::unique_ptr<SOAP::Command>(new SOAP::GetStatusActionCommand(std::move(t_soapHandling.normalizedMessage), m_service));
	} else {
		log_error([&] { return "ContextServiceHandler can't handle action: " + t_soapAction; });
	}

	std::unique_ptr<MESSAGEMODEL::Envelope> t_responseMessage(t_command->Run());

	SOAP::SoapHTTPResponseWrapper t_response(p_httpResponse);
	t_response.send(SOAP::NormalizedMessageSerializer::serialize(*t_responseMessage));
}

}
}
