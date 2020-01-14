/*
 * SetServiceHandler.cpp
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 18.09.2019, baumeister
 *
 */

#include "OSELib/SDC/SetServiceHandler.h"
#include "OSELib/DPWS/OperationTraits.h"
#include "OSELib/SDC/ISetService.h"
#include "OSELib/SOAP/Command.h"
#include "OSELib/SOAP/CommonSoapPreprocessing.h"
#include "OSELib/SOAP/GenericSoapActionCommand.h"
#include "OSELib/SOAP/GetMetadataActionCommand.h"
#include "OSELib/SOAP/NormalizedMessageSerializer.h"
#include "OSELib/SOAP/SoapFaultCommand.h"
#include "OSELib/SOAP/SoapHTTPResponseWrapper.h"
#include "OSELib/SOAP/SubscribeActionCommand.h"
#include "OSELib/SOAP/UnsubscribeActionCommand.h"
#include "OSELib/SOAP/RenewActionCommand.h"
#include "OSELib/SOAP/GetStatusActionCommand.h"

#include "DataModel/NormalizedMessageModel.hxx"

#include <Poco/Net/HTTPServerRequest.h>


namespace OSELib {
namespace SDC {

SetServiceHandler::SetServiceHandler(ISetService & p_service, Helper::XercesGrammarPoolProvider & p_grammarProvider, bool p_SSL)
: m_service(p_service)
, m_grammarProvider(p_grammarProvider)
, m_SSL(p_SSL)
{ }

void SetServiceHandler::handleRequestImpl(Poco::Net::HTTPServerRequest & p_httpRequest, Poco::Net::HTTPServerResponse & p_httpResponse) {

	SOAP::CommonSoapPreprocessing t_soapHandling(m_grammarProvider);
	t_soapHandling.parse(p_httpRequest.stream());

	const auto t_soapAction(t_soapHandling.normalizedMessage->getHeader().getAction().get());

	std::unique_ptr<SOAP::Command> t_command(new SOAP::SoapFaultCommand(p_httpResponse));

	if (t_soapAction == DPWS::GetMetadataTraits::RequestAction()) {
		const std::string t_serverAddress(p_httpRequest.serverAddress().toString());
		t_command = std::unique_ptr<SOAP::Command>(new SOAP::GetMetadataActionCommand(std::move(t_soapHandling.normalizedMessage), m_service.getMetadata(t_serverAddress, m_SSL)));
	} else if (t_soapAction == ActivateTraits::RequestAction()) {
		t_command = std::unique_ptr<SOAP::Command>(new SOAP::GenericSoapActionCommand<ActivateTraits>(std::move(t_soapHandling.normalizedMessage), m_service));
	} else if (t_soapAction == SetAlertStateTraits::RequestAction()) {
		t_command = std::unique_ptr<SOAP::Command>(new SOAP::GenericSoapActionCommand<SetAlertStateTraits>(std::move(t_soapHandling.normalizedMessage), m_service));
	} else if (t_soapAction == SetStringTraits::RequestAction()) {
		t_command = std::unique_ptr<SOAP::Command>(new SOAP::GenericSoapActionCommand<SetStringTraits>(std::move(t_soapHandling.normalizedMessage), m_service));
	} else if (t_soapAction == SetValueTraits::RequestAction()) {
		t_command = std::unique_ptr<SOAP::Command>(new SOAP::GenericSoapActionCommand<SetValueTraits>(std::move(t_soapHandling.normalizedMessage), m_service));
	} else if (t_soapAction == DPWS::SubscribeTraits::RequestAction()) {
        std::string t_PROTOCOL = "http";
        if(m_SSL) { t_PROTOCOL.append("s"); }
		const std::string subscriptionManagerAddress(t_PROTOCOL + "://" + p_httpRequest.serverAddress().toString() + m_service.getBaseUri());
		t_command = std::unique_ptr<SOAP::Command>(new SOAP::SubscribeActionCommand(std::move(t_soapHandling.normalizedMessage), m_service, subscriptionManagerAddress));
	} else if (t_soapAction == DPWS::UnsubscribeTraits::RequestAction()) {
		t_command = std::unique_ptr<SOAP::Command>(new SOAP::UnsubscribeActionCommand(std::move(t_soapHandling.normalizedMessage), m_service));
	} else if (t_soapAction == DPWS::RenewTraits::RequestAction()) {
		t_command = std::unique_ptr<SOAP::Command>(new SOAP::RenewActionCommand(std::move(t_soapHandling.normalizedMessage), m_service));
    } else if (t_soapAction == DPWS::GetStatusTraits::RequestAction()) {
    	t_command = std::unique_ptr<SOAP::Command>(new SOAP::GetStatusActionCommand(std::move(t_soapHandling.normalizedMessage), m_service));
	} else {
		log_error([&] { return "SetServiceHandler can't handle action: " + t_soapAction; });
	}

	auto t_responseMessage(t_command->Run());
	if(nullptr == t_responseMessage) {
		log_error([&] { return "SetServiceHandler failed to generate Response for Action: " + t_soapAction; });
		return;
	}

	SOAP::SoapHTTPResponseWrapper t_response(p_httpResponse);
	t_response.send(SOAP::NormalizedMessageSerializer::serialize(*t_responseMessage));
}

}
}
