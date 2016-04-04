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
 *  @file Message.cpp
 *  @project OSCLib
 *  @date 07.07.2011
 *  @author besting
 *  @copyright (c) SurgiTAIX AG
 */

#include "OSCLib/Comm/Binding.h"
#include "OSCLib/Comm/IPBinding.h"
#include "OSCLib/Comm/Message.h"

namespace OSCLib {
namespace Comm {

Message::Message() :
		routing(UNKNOWN_ROUTING),
		destination(nullptr),
		source(nullptr),
		dispatcher(nullptr),
		recProtocol(UNKNOWN_PROTOCOL),
		sendProtocol(UNKNOWN_PROTOCOL),
		rawBuffer("")
{

}

Message::~Message()
{
}

Message::RoutingScheme Message::getRouting() const
{
	return routing;
}

void Message::setReceiveProtocol(Message::Protocol protocol)
{
	this->recProtocol = protocol;
}

Message::Protocol Message::getReceiveProtocol() const
{
	return this->recProtocol;
}

void Message::setSendProtocol(Message::Protocol protocol)
{
	this->sendProtocol = protocol;
}

Message::Protocol Message::getSendProtocol() const
{
	return this->sendProtocol;
}

void Message::setRouting(Message::RoutingScheme routing)
{
	this->routing = routing;
}

void Message::setDestination(std::shared_ptr<Binding> binding)
{
	this->destination = binding;
}

std::shared_ptr<Binding> Message::getDestination() const
{
	return this->destination;
}

void Message::setSource(std::shared_ptr<IPBinding> binding)
{
	this->source = binding;
}

std::shared_ptr<IPBinding> Message::getSource() const
{
	return this->source;
}

void Message::setDispatcher(std::shared_ptr<IPBinding> binding)
{
	this->dispatcher = binding;
}

std::shared_ptr<IPBinding> Message::getDispatcher() const
{
	return this->dispatcher;
}

void Message::setRawBuffer(const std::string & raw)
{
	this->rawBuffer = raw;
}

std::string Message::getRawBuffer() const
{
	return rawBuffer;
}

}
}
