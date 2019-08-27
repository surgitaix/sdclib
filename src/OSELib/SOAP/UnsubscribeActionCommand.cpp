/*
 * UnsubscribeActionCommand.cpp
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 *
 */

#include "OSELib/SOAP/UnsubscribeActionCommand.h"
#include "OSELib/SOAP/NormalizedMessageAdapter.h"

#include "DataModel/NormalizedMessageModel.hxx"

namespace OSELib {
namespace SOAP {

UnsubscribeActionCommand::UnsubscribeActionCommand(std::unique_ptr<MESSAGEMODEL::Envelope> p_requestMessage, DPWS::UnsubscribeTraits::Dispatcher & p_dispatcher)
: SoapActionCommand(std::move(p_requestMessage))
, m_dispatcher(p_dispatcher)
{ }

std::unique_ptr<MESSAGEMODEL::Envelope> UnsubscribeActionCommand::dispatch(const MESSAGEMODEL::Envelope & p_request)
{
	NormalizedMessageAdapter<DPWS::UnsubscribeTraits::Request> t_requestAdapter;
	if (!t_requestAdapter.present(p_request)) {
		throw MissingRequestBody("Request body missing for " + DPWS::UnsubscribeTraits::RequestAction());
	}

	NormalizedMessageAdapter<DPWS::UnsubscribeTraits::RequestIdentifier> t_requestIdentifierAdapter;
	if (!t_requestIdentifierAdapter.present(p_request)) {
		throw MissingRequestBody("Event identifier in request header missing for " + DPWS::UnsubscribeTraits::RequestAction());
	}

	const DPWS::UnsubscribeTraits::Request & t_requestBody(t_requestAdapter.get(p_request));
	const DPWS::UnsubscribeTraits::RequestIdentifier & t_requestIdentifier(t_requestIdentifierAdapter.get(p_request));

	auto t_responseBody(DPWS::UnsubscribeTraits::dispatch(m_dispatcher, t_requestBody, t_requestIdentifier));

	if (!t_responseBody) {
		throw DispatchingFailed("Internal error. Dispatching failed for " + DPWS::UnsubscribeTraits::RequestAction());
	}

	auto t_responseMessage(createResponseMessageFromRequestMessage(p_request));
	t_responseMessage->Header().Action().set(WS::ADDRESSING::AttributedURIType(DPWS::UnsubscribeTraits::ResponseAction()));
	return t_responseMessage;
}

}
}
