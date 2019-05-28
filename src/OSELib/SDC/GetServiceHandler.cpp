/*
 * GetServiceHandler.cpp
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"

#include "NormalizedMessageModel.hxx"

#include "OSELib/Helper/Message.h"
#include "OSELib/Helper/XercesDocumentWrapper.h"
#include "OSELib/Helper/XercesGrammarPoolProvider.h"
#include "OSELib/SDC/GetServiceHandler.h"
#include "OSELib/SDC/IGetService.h"
#include "OSELib/SDC/OperationTraits.h"
#include "OSELib/SOAP/Command.h"
#include "OSELib/SOAP/CommonSoapPreprocessing.h"
#include "OSELib/SOAP/GenericSoapActionCommand.h"
#include "OSELib/SOAP/GetMetadataActionCommand.h"
#include "OSELib/SOAP/NormalizedMessageSerializer.h"
#include "OSELib/SOAP/SoapFaultCommand.h"
#include "OSELib/SOAP/SoapHTTPResponseWrapper.h"

namespace OSELib {
namespace SDC {

GetServiceHandler::GetServiceHandler(IGetService & service, Helper::XercesGrammarPoolProvider & grammarProvider) :
	_service(service),
	_grammarProvider(grammarProvider)
{
}

void GetServiceHandler::handleRequestImpl(Poco::Net::HTTPServerRequest & httpRequest, Poco::Net::HTTPServerResponse & httpResponse) {

	SOAP::CommonSoapPreprocessing soapHandling(_grammarProvider);
	soapHandling.parse(httpRequest.stream());

	const auto soapAction(soapHandling.normalizedMessage->Header().Action().get());

	std::unique_ptr<SOAP::Command> command(new SOAP::SoapFaultCommand(httpResponse));

	if (soapAction == DPWS::GetMetadataTraits::RequestAction()) {
		const std::string serverAddress(httpRequest.serverAddress().toString());
		command = std::unique_ptr<SOAP::Command>(new SOAP::GetMetadataActionCommand(std::move(soapHandling.normalizedMessage), _service.getMetadata(serverAddress)));
	} else if (soapAction == GetMDIBTraits::RequestAction()) {
		command = std::unique_ptr<SOAP::Command>(new SOAP::GenericSoapActionCommand<GetMDIBTraits>(std::move(soapHandling.normalizedMessage), _service));
	} else if (soapAction == GetMDDescriptionTraits::RequestAction()) {
		command = std::unique_ptr<SOAP::Command>(new SOAP::GenericSoapActionCommand<GetMDDescriptionTraits>(std::move(soapHandling.normalizedMessage), _service));
	} else if (soapAction == GetMdStateTraits::RequestAction()) {
		command = std::unique_ptr<SOAP::Command>(new SOAP::GenericSoapActionCommand<GetMdStateTraits>(std::move(soapHandling.normalizedMessage), _service));
	} else {
		log_error([&] { return "GetServiceHandler can't handle action: " + soapAction; });
	}

	std::unique_ptr<MESSAGEMODEL::Envelope> responseMessage(command->Run());

	SOAP::SoapHTTPResponseWrapper response(httpResponse);
	response.send(SOAP::NormalizedMessageSerializer::serialize(*responseMessage));
}

} /* namespace SDC */
} /* namespace OSELib */
