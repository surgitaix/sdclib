/*
 * SoapActionCommand.cpp
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 *
 */

#include "OSELib/SOAP/SoapActionCommand.h"
#include "SDCLib/SDCInstance.h"

#include "NormalizedMessageModel.hxx"


namespace OSELib {
namespace SOAP {

SoapActionCommand::SoapActionCommand(std::unique_ptr<MESSAGEMODEL::Envelope> p_request)
: m_request(std::move(p_request))
{ }

std::unique_ptr<MESSAGEMODEL::Envelope> SoapActionCommand::Run() {
	return RunWithExceptionTrap();
}

std::unique_ptr<MESSAGEMODEL::Envelope> SoapActionCommand::RunWithExceptionTrap() {
	try {
		return RunImpl();
	} catch (...) {
		throw;
	}
	return nullptr;
}

std::unique_ptr<MESSAGEMODEL::Envelope> SoapActionCommand::RunImpl() {

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
	t_header->MessageID().set(MessageIDType(SDCLib::SDCInstance::calcMSGID()));
	t_header->RelatesTo().set(p_request.Header().MessageID().get());

	std::unique_ptr<MESSAGEMODEL::Envelope::BodyType> t_body(new MESSAGEMODEL::Envelope::BodyType());
	return std::unique_ptr<MESSAGEMODEL::Envelope>(new MESSAGEMODEL::Envelope(std::move(t_header), std::move(t_body)));
}

}
}
