/*
 * SoapActionCommand.cpp
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#include "OSELib/SOAP/SoapActionCommand.h"

#include "NormalizedMessageModel.hxx"

#include <Poco/UUIDGenerator.h>


namespace OSELib {
namespace SOAP {

SoapActionCommand::SoapActionCommand(std::unique_ptr<MESSAGEMODEL::Envelope> request) :
	_request(std::move(request))
{
}
SoapActionCommand::~SoapActionCommand() = default;

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

	_request = preprocessRequest(std::move(_request));
	_request = checkDispatchPreconditions(std::move(_request));

	_response = dispatch(*_request);

	_response = checkDispatchPostConditions(std::move(_response));
	_response = postprocessResponse(std::move(_response));

	return std::move(_response);
}

std::unique_ptr<MESSAGEMODEL::Envelope> SoapActionCommand::preprocessRequest(std::unique_ptr<MESSAGEMODEL::Envelope> request) {
	return std::move(request);
}

std::unique_ptr<MESSAGEMODEL::Envelope> SoapActionCommand::postprocessResponse(std::unique_ptr<MESSAGEMODEL::Envelope> response) {
	return std::move(response);
}

std::unique_ptr<MESSAGEMODEL::Envelope> SoapActionCommand::checkDispatchPreconditions(std::unique_ptr<MESSAGEMODEL::Envelope> request) {
	return std::move(request);
}

std::unique_ptr<MESSAGEMODEL::Envelope> SoapActionCommand::checkDispatchPostConditions(std::unique_ptr<MESSAGEMODEL::Envelope> response) {
	return std::move(response);
}

std::unique_ptr<MESSAGEMODEL::Envelope> SoapActionCommand::createResponseMessageFromRequestMessage(const MESSAGEMODEL::Envelope & request) {
	std::unique_ptr<MESSAGEMODEL::Envelope::HeaderType> header(new MESSAGEMODEL::Envelope::HeaderType());
	using MessageIDType = MESSAGEMODEL::Envelope::HeaderType::MessageIDType;
	header->MessageID().set(MessageIDType(Poco::UUIDGenerator::defaultGenerator().create().toString()));
	header->RelatesTo().set(request.Header().MessageID().get());

	std::unique_ptr<MESSAGEMODEL::Envelope::BodyType> body(new MESSAGEMODEL::Envelope::BodyType());
	return std::unique_ptr<MESSAGEMODEL::Envelope>(new MESSAGEMODEL::Envelope(std::move(header), std::move(body)));
}

} /* namespace SOAP */
} /* namespace OSELib */
