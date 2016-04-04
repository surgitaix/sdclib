/**
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  *
  */

/**
 *  @file EventSource.cpp
 *  @project OSCLib
 *  @date 08.08.2012
 *  @author besting
 *  @copyright (c) SurgiTAIX AG
 *
 */

#include "OSCLib/Comm/DPWS/DPWS11Constants.h"
#include "OSCLib/Comm/DPWS/DPWS11Message.h"
#include "OSCLib/Comm/DPWS/DPWS11CommunicationManager.h"
#include "OSCLib/Data/EventSource.h"
#include "OSCLib/Data/OperationHelpers.h"
#include "OSCLib/Data/Subscription.h"
#include "OSCLib/Dev/Device.h"
#include "OSCLib/Dev/Service.h"

#include <string>

using namespace OSCLib::Data;
using namespace OSCLib::Dev;

namespace OSCLib {
namespace Data {

EventSource::EventSource() {
	setInternalType(EVENT_SOURCE);
}

EventSource::~EventSource()
{
}

std::string EventSource::getDefaultInputAction() const {
	return Data::OperationHelpers::getDefaultInputActionForEventSource(EventSource::getName(), getPortType());
}

std::string EventSource::getDefaultOutputAction() const {
	return Data::OperationHelpers::getDefaultOutputActionForEventSource(EventSource::getName(), getPortType());
}

EventSource::EventType EventSource::getEventType()
{
	if (getInput().size() == 0)
		return NOTIFICATION;
	else
		return SOLICIT_RESPONSE;
}

unsigned int EventSource::fire(Parameters& p) {
	unsigned int count = 0;
	Device * parentDevice = getParentService()->getParentDevice();

	for (const auto & protocolBinding : parentDevice->getProtocolBindings()) {
		// If there's a DPWS binding there must be a DPWS communication manager
		if (protocolBinding.first == Comm::DPWS::DPWS11) {
			Comm::CommunicationManager * man = parentDevice->getDefaultCommunicationManager(Comm::DPWS::DPWS11);
			if (man == nullptr) {
				continue;
			}
			Comm::DPWS::DPWS11CommunicationManager * dpwsMan = dynamic_cast<Comm::DPWS::DPWS11CommunicationManager*>(man);
			for (const auto & subscription : getParentService()->getActiveSubscriptions(Operation::getOutputAction())) {
				// Create invoke message
				Comm::DPWS::DPWS11Message msg;
				msg.createEventMessage(*subscription, p, getName(), getPortType());
				// Send invoke to sink
				dpwsMan->sendMessage(msg);
				++count;
			}
		}
	}
	getParentService()->cleanExpiredSubscriptions();
	return count;
}

unsigned int EventSource::mcast(Parameters& p, const std::string handle) {
	Device * parentDevice = getParentService()->getParentDevice();
	Comm::CommunicationManager * man = parentDevice->getDefaultCommunicationManager(Comm::DPWS::DPWS11);
	if (man == nullptr) {
		return 0;
	}
	Comm::DPWS::DPWS11CommunicationManager * dpwsMan = dynamic_cast<Comm::DPWS::DPWS11CommunicationManager*>(man);
	// MCast bindings are stored in the streaming service using the handle as key
	auto mcastBndVectorIt = getParentService()->getProtocolBindings().find(handle);
	if (mcastBndVectorIt == getParentService()->getProtocolBindings().end())
		return 0;
	if (mcastBndVectorIt->second.size() == 0)
		return 0;
	auto mcastBnd = (mcastBndVectorIt->second)[0];
	Comm::DPWS::DPWS11Message msg;
    msg.createStreamMessage(p, getParentService()->getDefaultTransportAddr(OSCLib::Comm::DPWS::DPWS11), mcastBnd->toString(), *parentDevice);
	// Send mcast stream event to all
	dpwsMan->sendMessage(msg);
	return 1;
}

Parameters EventSource::invoke(Parameters & p) {
	responseReceived(p);
    return Parameters();
}

} /* namespace Data */
} /* namespace OSCLib */
