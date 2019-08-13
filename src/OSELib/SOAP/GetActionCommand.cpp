/*
 * GetActionCommand.cpp
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#include "OSELib/SOAP/GetActionCommand.h"
#include "OSELib/SOAP/NormalizedMessageAdapter.h"

namespace OSELib {
namespace SOAP {

GetActionCommand::GetActionCommand(std::unique_ptr<MESSAGEMODEL::Envelope> requestMessage, const WS::MEX::Metadata & metadata) :
	SoapActionCommand(std::move(requestMessage)),
	_metadata(new WS::MEX::Metadata(metadata))
{
}

GetActionCommand::~GetActionCommand() = default;

std::unique_ptr<MESSAGEMODEL::Envelope> GetActionCommand::dispatch(const MESSAGEMODEL::Envelope & request) {
	std::unique_ptr<MESSAGEMODEL::Envelope> response(createResponseMessageFromRequestMessage(request));
	response->Header().Action().set(WS::ADDRESSING::AttributedURIType(DPWS::GetTraits::ResponseAction()));

	NormalizedMessageAdapter<DPWS::GetTraits::Response> responseAdapter;
	responseAdapter.set(*response, std::move(_metadata));

	return response;
}

} /* namespace SOAP */
} /* namespace OSELib */
