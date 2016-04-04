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
 *  @file Message.h
 *  @project OSCLib
 *  @date 07.07.2011
 *  @author besting
 *  @copyright (c) SurgiTAIX AG
 */


#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <string>
#include <memory>
namespace OSCLib {
namespace Comm {

class IPBinding;
class Binding;

class Message {
public:

	typedef enum
	{
		UNKNOWN_PROTOCOL,
		UDP_UNICAST,
		UDP_MULTICAST,
		TCP_HTTP,
		TCP_HTTP_BODY
	} Protocol;

	typedef enum
	{
		UNKNOWN_ROUTING,
		UNICAST,
		MULTICAST
	} RoutingScheme;

	Message();
	virtual ~Message();

    RoutingScheme getRouting() const;
    void setRouting(RoutingScheme routing);

    void setReceiveProtocol(Message::Protocol protocol);
    Message::Protocol getReceiveProtocol() const;
    void setSendProtocol(Message::Protocol protocol);
    Message::Protocol getSendProtocol() const;
    void setDestination(std::shared_ptr<Binding> destination);
    std::shared_ptr<Binding> getDestination() const;
    void setSource(std::shared_ptr<IPBinding> destination);
    std::shared_ptr<IPBinding> getSource() const;
    void setDispatcher(std::shared_ptr<IPBinding> dispatcher);
    std::shared_ptr<IPBinding> getDispatcher() const;
    void setRawBuffer(const std::string& raw);
    std::string getRawBuffer() const;

    static std::string getProtocolString(const Protocol & protocol) {
    	switch(protocol) {
    	case UNKNOWN_PROTOCOL: return "Unknown"; break;
    	case UDP_UNICAST: return "UDP Unicast"; break;
    	case UDP_MULTICAST: return "UDP Multicast"; break;
    	case TCP_HTTP: return "TCP HTTP"; break;
    	case TCP_HTTP_BODY: return "TCP HTTP_BODY"; break;
    	}
		return "ERROR";
    }

private:
    RoutingScheme routing;
    std::shared_ptr<Binding> destination;
    std::shared_ptr<IPBinding> source;
    std::shared_ptr<IPBinding> dispatcher;
    Protocol recProtocol, sendProtocol;
    std::string rawBuffer;
};

}
}

#endif /* MESSAGE_H_ */
