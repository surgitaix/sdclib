/*
 * SoapFaultCommand.cpp
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#include "Poco/Net/HTTPServerResponse.h"

#include "NormalizedMessageModel.hxx"

#include "OSELib/SOAP/SoapFaultCommand.h"

namespace OSELib {
namespace SOAP {

SoapFaultCommand::SoapFaultCommand(Poco::Net::HTTPServerResponse & httpResponse) :
	_httpResponse(httpResponse)
{
}

SoapFaultCommand::~SoapFaultCommand() = default;

std::unique_ptr<MESSAGEMODEL::Envelope> SoapFaultCommand::Run() {
	std::unique_ptr<MESSAGEMODEL::Envelope::HeaderType> header(new MESSAGEMODEL::Envelope::HeaderType());
	header->Action().set(WS::ADDRESSING::AttributedURIType("http://schemas.xmlsoap.org/ws/2004/08/addressing/fault"));

	std::unique_ptr<MESSAGEMODEL::Envelope::BodyType> body(new MESSAGEMODEL::Envelope::BodyType());
	return std::unique_ptr<MESSAGEMODEL::Envelope>(new MESSAGEMODEL::Envelope(std::move(header), std::move(body)));
}

} /* namespace SOAP */
} /* namespace OSELib */
