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
 *  @file IPBinding.cpp
 *  @project OSCLib
 *  @date 24.08.2011
 *  @author besting
 *  @copyright (c) SurgiTAIX AG
 */


#include "OSCLib/Comm/IPBinding.h"

#include "Poco/Net/SocketAddress.h"

using Poco::Net::SocketAddress;
using Poco::Net::IPAddress;

namespace OSCLib {
namespace Comm {

IPBinding::IPBinding(const std::string & ip, unsigned int port): PROTOCOL_HTTP("http://"), PROTOCOL_UDP("soap.udp://"), socketAddress(ip, port)
{

}

IPBinding::IPBinding(const IPBinding & source) : AbstractBinding(source), PROTOCOL_HTTP("http://"), PROTOCOL_UDP("soap.udp://"), socketAddress(source.socketAddress)
{

}

IPBinding::IPBinding(const Poco::Net::SocketAddress sa) : PROTOCOL_HTTP("http://"), PROTOCOL_UDP("soap.udp://"), socketAddress(sa) {

}

IPBinding::~IPBinding()
{
}

void IPBinding::setSocketAddress(const Poco::Net::SocketAddress sa) {
	socketAddress = sa;
}

const std::string IPBinding::getIp() const
{
	return socketAddress.host().toString();
}

unsigned int IPBinding::getPort() const
{
	return socketAddress.port();
}

std::string IPBinding::getPortStr() const
{
	return std::to_string(socketAddress.port());
}

std::string IPBinding::toString() const
{
	if(getType() == AbstractBinding::TCP_HTTP) {
		return PROTOCOL_HTTP + socketAddress.toString();
	} else {
		return PROTOCOL_UDP + socketAddress.toString();
	}
}

} /* namespace Comm */
} /* namespace OSCLib */
