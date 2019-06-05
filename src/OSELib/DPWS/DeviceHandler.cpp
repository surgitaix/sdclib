/*
 * DeviceHandler.cpp
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"

#include "NormalizedMessageModel.hxx"

#include "OSELib/DPWS/DeviceHandler.h"
#include "OSELib/DPWS/IDevice.h"
#include "OSELib/DPWS/OperationTraits.h"
#include "OSELib/Helper/Message.h"
#include "OSELib/Helper/XercesDocumentWrapper.h"
#include "OSELib/Helper/XercesGrammarPoolProvider.h"
#include "OSELib/SOAP/Command.h"
#include "OSELib/SOAP/CommonSoapPreprocessing.h"
#include "OSELib/SOAP/GetActionCommand.h"
#include "OSELib/SOAP/GenericSoapActionCommand.h"
#include "OSELib/SOAP/NormalizedMessageAdapter.h"
#include "OSELib/SOAP/NormalizedMessageSerializer.h"
#include "OSELib/SOAP/SoapFaultCommand.h"
#include "OSELib/SOAP/SoapHTTPResponseWrapper.h"

namespace OSELib {
namespace DPWS {

DeviceHandler::DeviceHandler(IDevice & service, bool p_SSL) :
	_service(service)
    , m_SSL(p_SSL)
{
}

void DeviceHandler::handleRequestImpl(Poco::Net::HTTPServerRequest & httpRequest, Poco::Net::HTTPServerResponse & httpResponse) {

	Helper::EmptyXercesGrammarPoolProvider pool;
	SOAP::CommonSoapPreprocessing soapHandling(pool);
	soapHandling.parse(httpRequest.stream());

	const auto soapAction(soapHandling.normalizedMessage->Header().Action().get());

	std::unique_ptr<SOAP::Command> command(new SOAP::SoapFaultCommand(httpResponse));

	if (soapAction == GetTraits::RequestAction()) {
		const std::string serverAddress(httpRequest.serverAddress().toString());
		command = std::unique_ptr<SOAP::Command>(new SOAP::GetActionCommand(std::move(soapHandling.normalizedMessage), _service.getMetadata(serverAddress, m_SSL)));
	} else if (soapAction == ProbeTraits::RequestAction()) {
		command = std::unique_ptr<SOAP::Command>(new SOAP::GenericSoapActionCommand<ProbeTraits>(std::move(soapHandling.normalizedMessage), _service));
	} else {
		log_error([&] { return "DeviceHandler can't handle action: " + soapAction; });
	}

	std::unique_ptr<MESSAGEMODEL::Envelope> responseMessage(command->Run());

	SOAP::SoapHTTPResponseWrapper response(httpResponse);
	response.send(SOAP::NormalizedMessageSerializer::serialize(*responseMessage));
}

} /* namespace SDC */
} /* namespace OSELib */
