/*
 * SubscribeActionCommand.cpp
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 21.08.2019, baumeister
 *
 */

#include "OSELib/SOAP/SubscribeActionCommand.h"
#include "OSELib/SOAP/NormalizedMessageAdapter.h"

#include "DataModel/NormalizedMessageModel.hxx"

namespace OSELib {
namespace SOAP {

SubscribeActionCommand::SubscribeActionCommand(std::unique_ptr<MESSAGEMODEL::Envelope> p_requestMessage, DPWS::SubscribeTraits::Dispatcher & p_dispatcher, const std::string & p_subscriptionManagerAddress)
: GenericSoapActionCommand<DPWS::SubscribeTraits>(std::move(p_requestMessage), p_dispatcher)
, m_subscriptionManagerAddress(p_subscriptionManagerAddress)
{ }

std::unique_ptr<MESSAGEMODEL::Envelope> SubscribeActionCommand::postprocessResponse(std::unique_ptr<MESSAGEMODEL::Envelope> p_response)
{
	NormalizedMessageAdapter<DPWS::SubscribeTraits::Response> t_responseAdapter;
	std::unique_ptr<DPWS::SubscribeTraits::Response> t_responseBody(new DPWS::SubscribeTraits::Response(t_responseAdapter.get(*p_response)));
	t_responseBody->getSubscriptionManager().setAddress(m_subscriptionManagerAddress);
	t_responseAdapter.set(*p_response, std::move(t_responseBody));
	return p_response;
}

}
}
