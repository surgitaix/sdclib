/*
 * RenewActionCommand.cpp
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#include "OSELib/DPWS/OperationTraits.h"
#include "OSELib/SOAP/NormalizedMessageAdapter.h"
#include "OSELib/SOAP/RenewActionCommand.h"

namespace OSELib {
namespace SOAP {

RenewActionCommand::RenewActionCommand(std::unique_ptr<MESSAGEMODEL::Envelope> requestMessage, DPWS::RenewTraits::Dispatcher & dispatcher) :
	SoapActionCommand(std::move(requestMessage)),
	_dispatcher(dispatcher)
{
}

RenewActionCommand::~RenewActionCommand() = default;

std::unique_ptr<MESSAGEMODEL::Envelope> RenewActionCommand::dispatch(const MESSAGEMODEL::Envelope & request) {

	NormalizedMessageAdapter<DPWS::RenewTraits::Request> requestAdapter;
	if (!requestAdapter.present(request)) {
		throw MissingRequestBody("Request body missing for " + DPWS::RenewTraits::RequestAction());
	}

	NormalizedMessageAdapter<DPWS::RenewTraits::RequestIdentifier> requestIdentifierAdapter;
	if (!requestIdentifierAdapter.present(request)) {
		throw MissingRequestBody("Event identifier in request header missing for " + DPWS::UnsubscribeTraits::RequestAction());
	}

	const DPWS::RenewTraits::Request & requestBody(requestAdapter.get(request));
	const DPWS::RenewTraits::RequestIdentifier & requestIdentifier(requestIdentifierAdapter.get(request));

	std::unique_ptr<DPWS::RenewTraits::Response> responseBody(DPWS::RenewTraits::dispatch(_dispatcher, requestBody, requestIdentifier));

	if (!responseBody) {
		throw DispatchingFailed("Internal error. Dispatching failed for " + DPWS::RenewTraits::RequestAction());
	}

	std::unique_ptr<MESSAGEMODEL::Envelope> responseMessage(createResponseMessageFromRequestMessage(request));
	responseMessage->Header().Action().set(WS::ADDRESSING::AttributedURIType(DPWS::RenewTraits::ResponseAction()));

	NormalizedMessageAdapter<DPWS::RenewTraits::Response> responseAdapter;
	responseAdapter.set(*responseMessage, std::move(responseBody));

	return responseMessage;
}

} /* namespace SOAP */
} /* namespace OSELib */
