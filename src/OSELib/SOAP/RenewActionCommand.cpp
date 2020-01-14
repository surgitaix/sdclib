/*
 * RenewActionCommand.cpp
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 *
 */


#include "OSELib/SOAP/RenewActionCommand.h"
#include "OSELib/SOAP/NormalizedMessageAdapter.h"

namespace OSELib {
namespace SOAP {

RenewActionCommand::RenewActionCommand(std::unique_ptr<MESSAGEMODEL::Envelope> p_requestMessage, DPWS::RenewTraits::Dispatcher & p_dispatcher)
: SoapActionCommand(std::move(p_requestMessage))
, m_dispatcher(p_dispatcher)
{ }

std::unique_ptr<MESSAGEMODEL::Envelope> RenewActionCommand::dispatch(const MESSAGEMODEL::Envelope & p_request)
{
	NormalizedMessageAdapter<DPWS::RenewTraits::Request> t_requestAdapter;
	if (!t_requestAdapter.present(p_request)) {
		throw MissingRequestBody("Request body missing for " + DPWS::RenewTraits::RequestAction());
	}

	NormalizedMessageAdapter<DPWS::RenewTraits::RequestIdentifier> t_requestIdentifierAdapter;
	if (!t_requestIdentifierAdapter.present(p_request)) {
		throw MissingRequestBody("Event identifier in request header missing for " + DPWS::RenewTraits::RequestAction());
	}

	const DPWS::RenewTraits::Request & t_requestBody(t_requestAdapter.get(p_request));
	const DPWS::RenewTraits::RequestIdentifier & t_requestIdentifier(t_requestIdentifierAdapter.get(p_request));

	auto t_responseBody(DPWS::RenewTraits::dispatch(m_dispatcher, t_requestBody, t_requestIdentifier));

	if (!t_responseBody) {
		throw DispatchingFailed("Internal error. Dispatching failed for " + DPWS::RenewTraits::RequestAction());
	}

	auto t_responseMessage(createResponseMessageFromRequestMessage(p_request));
	t_responseMessage->getHeader().getAction().set(WS::ADDRESSING::AttributedURIType(DPWS::RenewTraits::ResponseAction()));

	NormalizedMessageAdapter<DPWS::RenewTraits::Response> t_responseAdapter;
	t_responseAdapter.set(*t_responseMessage, std::move(t_responseBody));

	return t_responseMessage;
}

}
}
