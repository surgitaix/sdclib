/*
 * SoapActionCommand.cpp
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 18.09.2019, baumeister
 *
 */

#include "OSELib/SOAP/SoapActionCommand.h"
#include "SDCLib/SDCInstance.h"

#include "DataModel/NormalizedMessageModel.hxx"


namespace OSELib {
namespace SOAP {

SoapActionCommand::SoapActionCommand(std::unique_ptr<MESSAGEMODEL::Envelope> p_request)
: m_request(std::move(p_request))
{
	assert(m_request != nullptr);
}

std::unique_ptr<MESSAGEMODEL::Envelope> SoapActionCommand::Run() {
	return RunWithExceptionTrap();
}

std::unique_ptr<MESSAGEMODEL::Envelope> SoapActionCommand::RunWithExceptionTrap()
{
	try {
		return RunImpl();
	} catch (...) {
		throw;
	}
	return nullptr;
}

std::unique_ptr<MESSAGEMODEL::Envelope> SoapActionCommand::RunImpl()
{
	if(nullptr == m_request) {
		return nullptr;
	}

	m_request = preprocessRequest(std::move(m_request));
	m_request = checkDispatchPreconditions(std::move(m_request));

	m_response = dispatch(*m_request);

	m_response = checkDispatchPostConditions(std::move(m_response));
	m_response = postprocessResponse(std::move(m_response));

	return std::move(m_response);
}

std::unique_ptr<MESSAGEMODEL::Envelope> SoapActionCommand::preprocessRequest(std::unique_ptr<MESSAGEMODEL::Envelope> p_request) {
	return p_request;
}

std::unique_ptr<MESSAGEMODEL::Envelope> SoapActionCommand::postprocessResponse(std::unique_ptr<MESSAGEMODEL::Envelope> p_response) {
	return p_response;
}

std::unique_ptr<MESSAGEMODEL::Envelope> SoapActionCommand::checkDispatchPreconditions(std::unique_ptr<MESSAGEMODEL::Envelope> p_request) {
	return p_request;
}

std::unique_ptr<MESSAGEMODEL::Envelope> SoapActionCommand::checkDispatchPostConditions(std::unique_ptr<MESSAGEMODEL::Envelope> p_response) {
	return p_response;
}

std::unique_ptr<MESSAGEMODEL::Envelope> SoapActionCommand::createResponseMessageFromRequestMessage(const MESSAGEMODEL::Envelope & p_request)
{
	std::unique_ptr<MESSAGEMODEL::Envelope::HeaderType> t_header(new MESSAGEMODEL::Envelope::HeaderType());
	using MessageIDType = MESSAGEMODEL::Envelope::HeaderType::MessageIDType;
	t_header->getMessageID().set(MessageIDType(SDCLib::SDCInstance::calcMSGID()));
	// Only if the request had a MessageID to relate to (OPTIONAL under some conditions)
	if(p_request.getHeader().getMessageID().present()) {
		t_header->getRelatesTo().set(p_request.getHeader().getMessageID().get());
	}
	std::unique_ptr<MESSAGEMODEL::Envelope::BodyType> t_body(new MESSAGEMODEL::Envelope::BodyType());
	return std::unique_ptr<MESSAGEMODEL::Envelope>(new MESSAGEMODEL::Envelope(std::move(t_header), std::move(t_body)));
}

}
}
