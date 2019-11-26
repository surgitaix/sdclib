/*
 * DeviceHandler.cpp
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 23.08.2019, baumeister
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


namespace OSELib {
namespace DPWS {

DeviceHandler::DeviceHandler(IDevice & p_service, bool p_SSL)
: m_service(p_service)
, m_SSL(p_SSL)
{ }

void DeviceHandler::handleRequestImpl(Poco::Net::HTTPServerRequest & p_httpRequest, Poco::Net::HTTPServerResponse & p_httpResponse)
{
	Helper::EmptyXercesGrammarPoolProvider t_pool;
	SOAP::CommonSoapPreprocessing t_soapHandling(t_pool);
	t_soapHandling.parse(p_httpRequest.stream());

	const auto t_soapAction(t_soapHandling.normalizedMessage->getHeader().getAction().get());

	std::unique_ptr<SOAP::Command> t_command(new SOAP::SoapFaultCommand(p_httpResponse));

	if (t_soapAction == GetTraits::RequestAction()) {
		const std::string t_serverAddress(p_httpRequest.serverAddress().toString());
		t_command = std::unique_ptr<SOAP::Command>(new SOAP::GetActionCommand(std::move(t_soapHandling.normalizedMessage), m_service.getMetadata(t_serverAddress, m_SSL)));
	} else if (t_soapAction == ProbeTraits::RequestAction()) {
		t_command = std::unique_ptr<SOAP::Command>(new SOAP::GenericSoapActionCommand<ProbeTraits>(std::move(t_soapHandling.normalizedMessage), m_service));
	} else {
		log_error([&] { return "DeviceHandler can't handle action: " + t_soapAction; });
	}

	std::unique_ptr<MESSAGEMODEL::Envelope> t_responseMessage(t_command->Run());

	SOAP::SoapHTTPResponseWrapper t_response(p_httpResponse);
	t_response.send(SOAP::NormalizedMessageSerializer::serialize(*t_responseMessage));
}

}
}
