/*
 * ContextServiceHandler.cpp
 *
 *  Created on: 09.12.2015
 *      Author: matthias
 */

#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"

#include "NormalizedMessageModel.hxx"

#include "OSELib/DPWS/OperationTraits.h"
#include "OSELib/Helper/Message.h"
#include "OSELib/Helper/XercesDocumentWrapper.h"
#include "OSELib/Helper/XercesGrammarPoolProvider.h"
#include "OSELib/OSCP/ContextServiceHandler.h"
#include "OSELib/OSCP/IContextService.h"
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

namespace OSELib {
namespace OSCP {

ContextServiceHandler::ContextServiceHandler(IContextService & service, Helper::XercesGrammarPoolProvider & grammarProvider) :
	_service(service),
	_grammarProvider(grammarProvider)
{
}

void ContextServiceHandler::handleRequestImpl(Poco::Net::HTTPServerRequest & httpRequest, Poco::Net::HTTPServerResponse & httpResponse) {

	SOAP::CommonSoapPreprocessing soapHandling(_grammarProvider);
	soapHandling.parse(httpRequest.stream());

	const auto soapAction(soapHandling.normalizedMessage->Header().Action().get());

	std::unique_ptr<SOAP::Command> command(new SOAP::SoapFaultCommand(httpResponse));

	if (soapAction == DPWS::GetMetadataTraits::RequestAction()) {
		const std::string serverAddress(httpRequest.serverAddress().toString());
		command = std::unique_ptr<SOAP::Command>(new SOAP::GetMetadataActionCommand(std::move(soapHandling.normalizedMessage), _service.getMetadata(serverAddress)));
	} else if (soapAction == GetContextStatesTraits::RequestAction()) {
		command = std::unique_ptr<SOAP::Command>(new SOAP::GenericSoapActionCommand<GetContextStatesTraits>(std::move(soapHandling.normalizedMessage), _service));
	} else if (soapAction == SetContextStateTraits::RequestAction()) {
		command = std::unique_ptr<SOAP::Command>(new SOAP::GenericSoapActionCommand<SetContextStateTraits>(std::move(soapHandling.normalizedMessage), _service));
	} else if (soapAction == DPWS::SubscribeTraits::RequestAction()) {
		const std::string subscriptionManagerAddress("http://" + httpRequest.serverAddress().toString() + _service.getBaseUri());
		command = std::unique_ptr<SOAP::Command>(new SOAP::SubscribeActionCommand(std::move(soapHandling.normalizedMessage), _service, subscriptionManagerAddress));
	} else if (soapAction == DPWS::UnsubscribeTraits::RequestAction()) {
		command = std::unique_ptr<SOAP::Command>(new SOAP::UnsubscribeActionCommand(std::move(soapHandling.normalizedMessage), _service));
	} else if (soapAction == DPWS::RenewTraits::RequestAction()) {
		command = std::unique_ptr<SOAP::Command>(new SOAP::RenewActionCommand(std::move(soapHandling.normalizedMessage), _service));
	} else {
		log_error([&] { return "ContextServiceHandler can't handle action: " + soapAction; });
	}

	std::unique_ptr<MESSAGEMODEL::Envelope> responseMessage(command->Run());

	SOAP::SoapHTTPResponseWrapper response(httpResponse);
	response.send(SOAP::NormalizedMessageSerializer::serialize(*responseMessage));
}

} /* namespace OSCP */
} /* namespace OSELib */
