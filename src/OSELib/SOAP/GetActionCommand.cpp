/*
 * GetActionCommand.cpp
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 *
 */

#include "OSELib/SOAP/GetActionCommand.h"
#include "OSELib/SOAP/NormalizedMessageAdapter.h"

namespace OSELib {
namespace SOAP {

GetActionCommand::GetActionCommand(std::unique_ptr<MESSAGEMODEL::Envelope> p_requestMessage, const WS::MEX::Metadata & p_metadata)
: SoapActionCommand(std::move(p_requestMessage))
, m_metadata(new WS::MEX::Metadata(p_metadata))
{ }

std::unique_ptr<MESSAGEMODEL::Envelope> GetActionCommand::dispatch(const MESSAGEMODEL::Envelope & p_request)
{
	std::unique_ptr<MESSAGEMODEL::Envelope> t_response(createResponseMessageFromRequestMessage(p_request));
	t_response->Header().Action().set(WS::ADDRESSING::AttributedURIType(DPWS::GetTraits::ResponseAction()));

	NormalizedMessageAdapter<DPWS::GetTraits::Response> t_responseAdapter;
	t_responseAdapter.set(*t_response, std::move(m_metadata));

	return t_response;
}

}
}
