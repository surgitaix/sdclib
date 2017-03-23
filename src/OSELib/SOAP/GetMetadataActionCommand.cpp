/*
 * GetMetadataActionCommand.cpp
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#include "ws-addressing.hxx"
#include "MetadataExchange.hxx"

#include "OSELib/SOAP/GetMetadataActionCommand.h"
#include "OSELib/SOAP/NormalizedMessageAdapter.h"

namespace OSELib {
namespace SOAP {

GetMetadataActionCommand::GetMetadataActionCommand(std::unique_ptr<MESSAGEMODEL::Envelope> requestMessage, const WS::MEX::Metadata & metadata) :
	SoapActionCommand(std::move(requestMessage)),
	_metadata(new WS::MEX::Metadata(metadata))
{
}

GetMetadataActionCommand::~GetMetadataActionCommand() = default;

std::unique_ptr<MESSAGEMODEL::Envelope> GetMetadataActionCommand::dispatch(const MESSAGEMODEL::Envelope & request) {
	std::unique_ptr<MESSAGEMODEL::Envelope> response(createResponseMessageFromRequestMessage(request));
	response->Header().Action().set(WS::ADDRESSING::AttributedURIType(DPWS::GetMetadataTraits::ResponseAction()));

	NormalizedMessageAdapter<DPWS::GetTraits::Response> responseAdapter;
	responseAdapter.set(*response, std::move(_metadata));

	return std::move(response);
}

std::unique_ptr<MESSAGEMODEL::Envelope> GetMetadataActionCommand::checkDispatchPreconditions(std::unique_ptr<MESSAGEMODEL::Envelope> request) {
	NormalizedMessageAdapter<DPWS::GetMetadataTraits::Request> requestAdapter;
	if (!requestAdapter.present(*request)) {
		throw SoapActionCommand::MissingRequestBody("Request body missing for " + DPWS::GetMetadataTraits::RequestAction());
	}
	return std::move(request);
}

} /* namespace SOAP */
} /* namespace OSELib */
