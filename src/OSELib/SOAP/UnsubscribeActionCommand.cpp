/*
 * UnsubscribeActionCommand.cpp
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#include "NormalizedMessageModel.hxx"

#include "OSELib/DPWS/OperationTraits.h"
#include "OSELib/SOAP/NormalizedMessageAdapter.h"
#include "OSELib/SOAP/UnsubscribeActionCommand.h"

namespace OSELib {
namespace SOAP {

UnsubscribeActionCommand::UnsubscribeActionCommand(std::unique_ptr<MESSAGEMODEL::Envelope> requestMessage, DPWS::UnsubscribeTraits::Dispatcher & dispatcher) :
	SoapActionCommand(std::move(requestMessage)),
	_dispatcher(dispatcher)
{
}

UnsubscribeActionCommand::~UnsubscribeActionCommand() = default;

std::unique_ptr<MESSAGEMODEL::Envelope> UnsubscribeActionCommand::dispatch(const MESSAGEMODEL::Envelope & request) {

	NormalizedMessageAdapter<DPWS::UnsubscribeTraits::Request> requestAdapter;
	if (!requestAdapter.present(request)) {
		throw MissingRequestBody("Request body missing for " + DPWS::UnsubscribeTraits::RequestAction());
	}

	NormalizedMessageAdapter<DPWS::UnsubscribeTraits::RequestIdentifier> requestIdentifierAdapter;
	if (!requestIdentifierAdapter.present(request)) {
		throw MissingRequestBody("Event identifier in request header missing for " + DPWS::UnsubscribeTraits::RequestAction());
	}

	const DPWS::UnsubscribeTraits::Request & requestBody(requestAdapter.get(request));
	const DPWS::UnsubscribeTraits::RequestIdentifier & requestIdentifier(requestIdentifierAdapter.get(request));

	std::unique_ptr<DPWS::UnsubscribeTraits::Response> responseBody(DPWS::UnsubscribeTraits::dispatch(_dispatcher, requestBody, requestIdentifier));

	if (!responseBody) {
		throw DispatchingFailed("Internal error. Dispatching failed for " + DPWS::UnsubscribeTraits::RequestAction());
	}

	std::unique_ptr<MESSAGEMODEL::Envelope> responseMessage(createResponseMessageFromRequestMessage(request));
	responseMessage->Header().Action().set(WS::ADDRESSING::AttributedURIType(DPWS::UnsubscribeTraits::ResponseAction()));

	return std::move(responseMessage);
}

} /* namespace SOAP */
} /* namespace OSELib */
