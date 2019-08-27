/*
 * SoapFaultCommand.cpp
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 *
 */

#include "OSELib/SOAP/SoapFaultCommand.h"

#include "DataModel/NormalizedMessageModel.hxx"

#include <Poco/Net/HTTPServerResponse.h>

namespace OSELib {
namespace SOAP {

SoapFaultCommand::SoapFaultCommand(Poco::Net::HTTPServerResponse & p_httpResponse)
: m_httpResponse(p_httpResponse)
{ }

std::unique_ptr<MESSAGEMODEL::Envelope> SoapFaultCommand::Run()
{
	std::unique_ptr<MESSAGEMODEL::Envelope::HeaderType> t_header(new MESSAGEMODEL::Envelope::HeaderType());
	t_header->Action().set(WS::ADDRESSING::AttributedURIType("http://schemas.xmlsoap.org/ws/2004/08/addressing/fault"));

	std::unique_ptr<MESSAGEMODEL::Envelope::BodyType> t_body(new MESSAGEMODEL::Envelope::BodyType());
	return std::unique_ptr<MESSAGEMODEL::Envelope>(new MESSAGEMODEL::Envelope(std::move(t_header), std::move(t_body)));
}

}
}
