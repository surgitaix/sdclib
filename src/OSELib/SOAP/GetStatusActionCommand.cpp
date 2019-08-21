/*
 * GetStatusActionCommand.cpp
 *
 *  Created on: 05.08.2019, baumeister
 *
 */


#include "OSELib/SOAP/GetStatusActionCommand.h"
#include "OSELib/SOAP/NormalizedMessageAdapter.h"


using namespace OSELib;
using namespace OSELib::SOAP;

GetStatusActionCommand::GetStatusActionCommand(std::unique_ptr<MESSAGEMODEL::Envelope> p_requestMessage, DPWS::GetStatusTraits::Dispatcher & p_dispatcher)
: SoapActionCommand(std::move(p_requestMessage))
, m_dispatcher(p_dispatcher)
{ }

std::unique_ptr<MESSAGEMODEL::Envelope> GetStatusActionCommand::dispatch(const MESSAGEMODEL::Envelope & p_request)
{
	NormalizedMessageAdapter<DPWS::GetStatusTraits::Request> t_requestAdapter;
	if (!t_requestAdapter.present(p_request)) {
		throw MissingRequestBody("Request body missing for " + DPWS::GetStatusTraits::RequestAction());
	}

	NormalizedMessageAdapter<DPWS::GetStatusTraits::RequestIdentifier> t_requestIdentifierAdapter;
	if (!t_requestIdentifierAdapter.present(p_request)) {
		throw MissingRequestBody("Event identifier in request header missing for " + DPWS::GetStatusTraits::RequestAction());
	}

	const DPWS::GetStatusTraits::Request & t_requestBody(t_requestAdapter.get(p_request));
	const DPWS::GetStatusTraits::RequestIdentifier & t_requestIdentifier(t_requestIdentifierAdapter.get(p_request));

	std::unique_ptr<DPWS::GetStatusTraits::Response> t_responseBody(DPWS::GetStatusTraits::dispatch(m_dispatcher, t_requestBody, t_requestIdentifier));

	if (!t_responseBody) {
		throw DispatchingFailed("Internal error. Dispatching failed for " + DPWS::GetStatusTraits::RequestAction());
	}

	std::unique_ptr<MESSAGEMODEL::Envelope> t_responseMessage(createResponseMessageFromRequestMessage(p_request));
	t_responseMessage->Header().Action().set(WS::ADDRESSING::AttributedURIType(DPWS::GetStatusTraits::ResponseAction()));

	NormalizedMessageAdapter<DPWS::GetStatusTraits::Response> t_responseAdapter;
	t_responseAdapter.set(*t_responseMessage, std::move(t_responseBody));

	return t_responseMessage;
}
