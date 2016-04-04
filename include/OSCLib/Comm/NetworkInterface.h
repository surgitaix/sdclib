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
 *  @file NetworkInterface.h
 *  @project OSCLib
 *  @date 24.08.2011
 *  @author besting
 *  @copyright (c) SurgiTAIX AG
 */


#ifndef NETWORKINTERFACE_H_
#define NETWORKINTERFACE_H_

#include <string>

namespace OSCLib {
namespace Comm {

class Message;
class MulticastCallback;
class UnicastCallback;

class NetworkInterface {
public:
	NetworkInterface();
	virtual ~NetworkInterface();

	virtual bool sendMessage(const UnicastCallback * const source, Message & msg, const std::string& logInfo) = 0;

	virtual void addUDPMulticastListener(const MulticastCallback * const callback, const std::string & ip, unsigned int port) = 0;
	virtual void removeUDPMulticastListener(const MulticastCallback * const callback, const std::string & ip, unsigned int port) = 0;
	virtual void addUDPListener(const UnicastCallback * const callback, const std::string& hostIp, unsigned int hostPort) = 0;
	virtual void removeListener(const UnicastCallback * const callback, const std::string& hostIp, unsigned int hostPort) = 0;

	virtual void processIn() = 0;

	virtual void addValidUnicastCallback(const UnicastCallback * const cb) = 0;
	virtual void removeValidUnicastCallback(const UnicastCallback * const cb) = 0;
	virtual bool isValidUnicastCallback(const UnicastCallback * const cb) = 0;
    virtual void addValidMulticastCallback(const MulticastCallback * const cb) = 0;
    virtual void removeValidMulticastCallback(const MulticastCallback * const cb) = 0;
    virtual bool isValidMulticastCallback(const MulticastCallback * const cb) = 0;

};

} /* namespace Comm */
} /* namespace OSCLib */
#endif /* NETWORKINTERFACE_H_ */
