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
 *  @file DefaultNetworkInterface.h
 *  @project OSCLib
 *  @date 24.08.2011
 *  @author besting
 *  @copyright (c) SurgiTAIX AG
 */


#ifndef DEFAULTNETWORKINTERFACE_H_
#define DEFAULTNETWORKINTERFACE_H_

#include "DatagramSocketManager.h"
#include "MulticastSocketManager.h"
#include "NetworkInterface.h"
#include "Poco/NotificationQueue.h"
#include "Poco/Mutex.h"

#include <list>
#include <set>
#include <string>
#include <vector>

namespace OSCLib {
namespace Comm {

class AsyncMessageWriter;
class AsyncMessageDispatcher;


class DefaultNetworkInterface: public OSCLib::Comm::NetworkInterface {
friend class AsyncMessageWriter;
friend class AsyncMessageDispatcher;
public:
	DefaultNetworkInterface();
	virtual ~DefaultNetworkInterface();

    void interruptMessaging();
	bool sendMessage(const UnicastCallback * const source, Message & msg, const std::string & logInfo);

	void addUDPMulticastListener(const MulticastCallback * const callback, const std::string & groupIp = "", unsigned int groupPort = 0);
	void removeUDPMulticastListener(const MulticastCallback * const callback, const std::string & ip, unsigned int port);
	void addTCPListener(const UnicastCallback * const callback, const std::string & hostIp, unsigned int hostPort);
	void addUDPListener(const UnicastCallback * const callback, const std::string & hostIp, unsigned int hostPort);
	void removeListener(const UnicastCallback * const callback, const std::string & hostIp, unsigned int hostPort);

	void processIn();

	void addValidUnicastCallback(const UnicastCallback * const cb);
	void removeValidUnicastCallback(const UnicastCallback * const cb);
	bool isValidUnicastCallback(const UnicastCallback * const cb);
    void addValidMulticastCallback(const MulticastCallback * const cb);
    void removeValidMulticastCallback(const MulticastCallback * const cb);
    bool isValidMulticastCallback(const MulticastCallback * const cb);

private:

    bool sendOutNow(const UnicastCallback * const source, const Message& msg);
    std::shared_ptr<AsyncMessageWriter> messageWriter;
    std::shared_ptr<AsyncMessageDispatcher> messageDispatcher;

	void receiveMulticast();
    void receiveClient();
    void acceptNewConnections();

    Poco::NotificationQueue outMessageQueue, inMessageQueue;
	std::list<PendingMessage> inMessages;
	std::set<const UnicastCallback *> validUnicastCallbacks;
    std::set<const MulticastCallback *> validMulticastCallbacks;

    MulticastSocketManager multicastSocketManager;
    DatagramSocketManager datagramSocketManager;

    Poco::Mutex mutex;
};

} /* namespace Comm */
} /* namespace OSCLib */
#endif /* DEFAULTNETWORKINTERFACE_H_ */
