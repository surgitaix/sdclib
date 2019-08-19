/*
 * SubscribeActionCommand.cpp
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#include "NormalizedMessageModel.hxx"

#include "OSELib/DPWS/OperationTraits.h"
#include "OSELib/SOAP/NormalizedMessageAdapter.h"
#include "OSELib/SOAP/SubscribeActionCommand.h"

namespace OSELib {
namespace SOAP {

SubscribeActionCommand::SubscribeActionCommand(std::unique_ptr<MESSAGEMODEL::Envelope> requestMessage, DPWS::SubscribeTraits::Dispatcher & dispatcher, const std::string & subscriptionManagerAddress) :
	GenericSoapActionCommand<DPWS::SubscribeTraits>(std::move(requestMessage), dispatcher),
	_subscriptionManagerAddress(subscriptionManagerAddress)
{
}

std::unique_ptr<MESSAGEMODEL::Envelope> SubscribeActionCommand::postprocessResponse(std::unique_ptr<MESSAGEMODEL::Envelope> response) {
	NormalizedMessageAdapter<DPWS::SubscribeTraits::Response> responseAdapter;
	std::unique_ptr<DPWS::SubscribeTraits::Response> responseBody(new DPWS::SubscribeTraits::Response(responseAdapter.get(*response)));
	responseBody->SubscriptionManager().Address(_subscriptionManagerAddress);
	responseAdapter.set(*response, std::move(responseBody));
	return response;
}

} /* namespace SOAP */
} /* namespace OSELib */
