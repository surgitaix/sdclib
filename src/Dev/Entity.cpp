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
 *  @file Entity.cpp
 *  @project OSCLib
 *  @date 03.01.2012
 *  @author besting
 *  @copyright (c) SurgiTAIX AG
 */

#include "OSCLib/Comm/Binding.h"
#include "OSCLib/Comm/DPWS/DPWS11Constants.h"
#include "OSCLib/Dev/Entity.h"

#include <vector>

using namespace OSCLib::Comm;

namespace OSCLib {
namespace Dev {

Entity::Entity()
{
}

Entity::~Entity()
{
}

void Entity::addType(const Data::QName & type)
{
	types.push_back(type);
}

void Entity::addTypes(const Data::QVector & types) {
	for (unsigned int i = 0; i < types.size(); i++) {
		addType(types[i]);
	}
}

const ProtocolBindingMap & Entity::getProtocolBindings() const
{
	return protocolBindings;
}

void Entity::addBinding(const std::string & protocol, std::shared_ptr<Comm::AbstractBinding> binding)
{
	if (protocolBindings.find(protocol) == protocolBindings.end())
		protocolBindings[protocol] = std::vector<std::shared_ptr<OSCLib::Comm::AbstractBinding>>();
	protocolBindings[protocol].push_back(binding);
}

void Entity::addBindingStr(const std::string & protocol, const std::string & bndStr)
{
	std::shared_ptr<Binding> binding(new Binding(bndStr));
	addBinding(protocol, binding);
}

std::string Entity::getDefaultTransportAddr(const std::string & protocol, std::shared_ptr<Comm::IPBinding> dispatcherBinding) const
{
	std::string addr;
	if (!getProtocolBindings().empty())
	{
		const std::vector<std::shared_ptr<AbstractBinding>> entityBindings = getProtocolBindings().find(protocol)->second;
		if (!entityBindings.empty())
		{
			// Generate default transport address from first available unicast binding
			for (const auto & nextBnd : entityBindings)
			{
				std::shared_ptr<IPBinding> ipb(std::dynamic_pointer_cast<IPBinding>(nextBnd));
				if (ipb->getType() != AbstractBinding::UDP_MULTICAST)
				{
					// If dispatcher binding given, use dispatcher's IP and service binding's as 'real' address for the service
					if (dispatcherBinding != nullptr) {
						Binding clone(ipb->toString());
						clone.setSocketAddress(Poco::Net::SocketAddress(dispatcherBinding->getIp(), clone.getPort()));
						addr = clone.toString();
						return addr;
					}
					addr = ipb->toString();
					return addr;
				}
			}
		}
	}
	return addr;
}

const Data::QVector & Entity::getTypes() const
{
	return types;
}

void Entity::clearTypes() {
	types.clear();
}

void Entity::setEndpointReference(const EndpointReference & epr)
{
	endpoint = epr;
}

const EndpointReference & Entity::getEndpointReference() const
{
	return endpoint;
}

void Entity::setEPRAddress(const std::string & adr)
{
	endpoint.setAddress(adr);
}

} /* namespace Dev */
} /* namespace OSCLib */
