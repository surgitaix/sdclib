/*
 * GetMetadataActionCommand.cpp
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 *
 */

#include "OSELib/SOAP/GetMetadataActionCommand.h"
#include "OSELib/SOAP/NormalizedMessageAdapter.h"

namespace OSELib {
namespace SOAP {

GetMetadataActionCommand::GetMetadataActionCommand(std::unique_ptr<MESSAGEMODEL::Envelope> p_requestMessage, const WS::MEX::Metadata & p_metadata)
: SoapActionCommand(std::move(p_requestMessage))
, m_metadata(new WS::MEX::Metadata(p_metadata))
{ }

std::unique_ptr<MESSAGEMODEL::Envelope> GetMetadataActionCommand::dispatch(const MESSAGEMODEL::Envelope & p_request)
{
	std::unique_ptr<MESSAGEMODEL::Envelope> t_response(createResponseMessageFromRequestMessage(p_request));
	t_response->Header().Action().set(WS::ADDRESSING::AttributedURIType(DPWS::GetMetadataTraits::ResponseAction()));

	NormalizedMessageAdapter<DPWS::GetMetadataTraits::Response> t_responseAdapter;
	t_responseAdapter.set(*t_response, std::move(m_metadata));

	return t_response;
}

std::unique_ptr<MESSAGEMODEL::Envelope> GetMetadataActionCommand::checkDispatchPreconditions(std::unique_ptr<MESSAGEMODEL::Envelope> p_request)
{
	NormalizedMessageAdapter<DPWS::GetMetadataTraits::Request> t_requestAdapter;
	if (!t_requestAdapter.present(*p_request)) {
		throw SoapActionCommand::MissingRequestBody("Request body missing for " + DPWS::GetMetadataTraits::RequestAction());
	}
	return p_request;
}

}
}
