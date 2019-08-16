/*
 * GetStatusActionCommand.cpp
 *
 *  Created on: 07.12.2015, baumeister
 *
 */


#include "OSELib/SOAP/GetStatusActionCommand.h"

#include "OSELib/DPWS/OperationTraits.h"
#include "OSELib/SOAP/NormalizedMessageAdapter.h"


using namespace OSELib;
using namespace OSELib::SOAP;

GetStatusActionCommand::GetStatusActionCommand(std::unique_ptr<MESSAGEMODEL::Envelope> requestMessage, DPWS::GetStatusTraits::Dispatcher & dispatcher)
: SoapActionCommand(std::move(requestMessage))
, _dispatcher(dispatcher)
{ }

GetStatusActionCommand::~GetStatusActionCommand() = default;

std::unique_ptr<MESSAGEMODEL::Envelope> GetStatusActionCommand::dispatch(const MESSAGEMODEL::Envelope & request)
{

	NormalizedMessageAdapter<DPWS::GetStatusTraits::Request> requestAdapter;
	if (!requestAdapter.present(request)) {
		throw MissingRequestBody("Request body missing for " + DPWS::GetStatusTraits::RequestAction());
	}

	NormalizedMessageAdapter<DPWS::GetStatusTraits::RequestIdentifier> requestIdentifierAdapter;
	if (!requestIdentifierAdapter.present(request)) {
		throw MissingRequestBody("Event identifier in request header missing for " + DPWS::GetStatusTraits::RequestAction());
	}

	const DPWS::GetStatusTraits::Request & requestBody(requestAdapter.get(request));
	const DPWS::GetStatusTraits::RequestIdentifier & requestIdentifier(requestIdentifierAdapter.get(request));

	std::unique_ptr<DPWS::GetStatusTraits::Response> responseBody(DPWS::GetStatusTraits::dispatch(_dispatcher, requestBody, requestIdentifier));

	if (!responseBody) {
		throw DispatchingFailed("Internal error. Dispatching failed for " + DPWS::GetStatusTraits::RequestAction());
	}

	std::unique_ptr<MESSAGEMODEL::Envelope> responseMessage(createResponseMessageFromRequestMessage(request));
	responseMessage->Header().Action().set(WS::ADDRESSING::AttributedURIType(DPWS::GetStatusTraits::ResponseAction()));

	NormalizedMessageAdapter<DPWS::GetStatusTraits::Response> responseAdapter;
	responseAdapter.set(*responseMessage, std::move(responseBody));

	return responseMessage;
}
