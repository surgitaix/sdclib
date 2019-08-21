/*
 * DeviceHandler.cpp
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 20.08.2019, baumeister
 *
 */

#include "OSELib/DPWS/DeviceHandler.h"
#include "OSELib/DPWS/IDevice.h"
#include "OSELib/DPWS/OperationTraits.h"
#include "OSELib/Helper/XercesGrammarPoolProvider.h"
#include "OSELib/SOAP/Command.h"
#include "OSELib/SOAP/CommonSoapPreprocessing.h"
#include "OSELib/SOAP/GetActionCommand.h"
#include "OSELib/SOAP/GenericSoapActionCommand.h"
#include "OSELib/SOAP/NormalizedMessageSerializer.h"
#include "OSELib/SOAP/SoapFaultCommand.h"
#include "OSELib/SOAP/SoapHTTPResponseWrapper.h"

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>


namespace OSELib {
namespace DPWS {

DeviceHandler::DeviceHandler(IDevice & p_service, bool p_SSL)
: m_service(p_service)
, m_SSL(p_SSL)
{ }

void DeviceHandler::handleRequestImpl(Poco::Net::HTTPServerRequest & httpRequest, Poco::Net::HTTPServerResponse & httpResponse)
{
	Helper::EmptyXercesGrammarPoolProvider pool;
	SOAP::CommonSoapPreprocessing soapHandling(pool);
	soapHandling.parse(httpRequest.stream());

	const auto soapAction(soapHandling.normalizedMessage->Header().Action().get());

	std::unique_ptr<SOAP::Command> t_command(new SOAP::SoapFaultCommand(httpResponse));

	if (soapAction == GetTraits::RequestAction()) {
		const std::string serverAddress(httpRequest.serverAddress().toString());
		t_command = std::unique_ptr<SOAP::Command>(new SOAP::GetActionCommand(std::move(soapHandling.normalizedMessage), m_service.getMetadata(serverAddress, m_SSL)));
	} else if (soapAction == ProbeTraits::RequestAction()) {
		t_command = std::unique_ptr<SOAP::Command>(new SOAP::GenericSoapActionCommand<ProbeTraits>(std::move(soapHandling.normalizedMessage), m_service));
	} else {
		log_error([&] { return "DeviceHandler can't handle action: " + soapAction; });
	}

	std::unique_ptr<MESSAGEMODEL::Envelope> responseMessage(t_command->Run());

	SOAP::SoapHTTPResponseWrapper response(httpResponse);
	response.send(SOAP::NormalizedMessageSerializer::serialize(*responseMessage));
}

} /* namespace SDC */
} /* namespace OSELib */
