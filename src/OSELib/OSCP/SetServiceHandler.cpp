/*
 * SetServiceHandler.cpp
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"

#include "NormalizedMessageModel.hxx"

#include "OSELib/DPWS/OperationTraits.h"
#include "OSELib/Helper/Message.h"
#include "OSELib/Helper/XercesDocumentWrapper.h"
#include "OSELib/Helper/XercesGrammarPoolProvider.h"
#include "OSELib/OSCP/ISetService.h"
#include "OSELib/OSCP/OperationTraits.h"
#include "OSELib/OSCP/SetServiceHandler.h"
#include "OSELib/SOAP/Command.h"
#include "OSELib/SOAP/CommonSoapPreprocessing.h"
#include "OSELib/SOAP/GenericSoapActionCommand.h"
#include "OSELib/SOAP/GetMetadataActionCommand.h"
#include "OSELib/SOAP/NormalizedMessageSerializer.h"
#include "OSELib/SOAP/SoapFaultCommand.h"
#include "OSELib/SOAP/SoapHTTPResponseWrapper.h"

namespace OSELib {
namespace OSCP {

SetServiceHandler::SetServiceHandler(ISetService & service, Helper::XercesGrammarPoolProvider & grammarProvider) :
	_service(service),
	_grammarProvider(grammarProvider)
{
}

void SetServiceHandler::handleRequestImpl(Poco::Net::HTTPServerRequest & httpRequest, Poco::Net::HTTPServerResponse & httpResponse) {

	SOAP::CommonSoapPreprocessing soapHandling(_grammarProvider);
	soapHandling.parse(httpRequest.stream());

	const auto soapAction(soapHandling.normalizedMessage->Header().Action().get());

	std::unique_ptr<SOAP::Command> command(new SOAP::SoapFaultCommand(httpResponse));

	if (soapAction == DPWS::GetMetadataTraits::RequestAction()) {
		const std::string serverAddress(httpRequest.serverAddress().toString());
		command = std::unique_ptr<SOAP::Command>(new SOAP::GetMetadataActionCommand(std::move(soapHandling.normalizedMessage), _service.getMetadata(serverAddress)));
	} else if (soapAction == ActivateTraits::RequestAction()) {
		command = std::unique_ptr<SOAP::Command>(new SOAP::GenericSoapActionCommand<ActivateTraits>(std::move(soapHandling.normalizedMessage), _service));
	} else if (soapAction == SetAlertStateTraits::RequestAction()) {
		command = std::unique_ptr<SOAP::Command>(new SOAP::GenericSoapActionCommand<SetAlertStateTraits>(std::move(soapHandling.normalizedMessage), _service));
	} else if (soapAction == SetStringTraits::RequestAction()) {
		command = std::unique_ptr<SOAP::Command>(new SOAP::GenericSoapActionCommand<SetStringTraits>(std::move(soapHandling.normalizedMessage), _service));
	} else if (soapAction == SetValueTraits::RequestAction()) {
		command = std::unique_ptr<SOAP::Command>(new SOAP::GenericSoapActionCommand<SetValueTraits>(std::move(soapHandling.normalizedMessage), _service));
	} else {
		log_error([&] { return "SetServiceHandler can't handle action: " + soapAction; });
	}

	std::unique_ptr<MESSAGEMODEL::Envelope> responseMessage(command->Run());

	SOAP::SoapHTTPResponseWrapper response(httpResponse);
	response.send(SOAP::NormalizedMessageSerializer::serialize(*responseMessage));
}

} /* namespace OSCP */
} /* namespace OSELib */
