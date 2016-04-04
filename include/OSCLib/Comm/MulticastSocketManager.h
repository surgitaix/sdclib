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

/*
 * SocketManager.h
 *
 *  @Copyright (C) 2014, SurgiTAIX AG
 *  Author: besting, roehser
 */

#ifndef MULTICASTSOCKETMANAGER_H_
#define MULTICASTSOCKETMANAGER_H_

#include <map>
#include <list>
#include "PendingMessage.h"
#include "Poco/Mutex.h"
#include "Poco/Net/MulticastSocket.h"
#include "Poco/Net/SocketAddress.h"

namespace OSCLib {
namespace Comm {

class MulticastCallback;

class MulticastSocketManager {
public:
	MulticastSocketManager();
	virtual ~MulticastSocketManager();

	void addMulticastListener(const Poco::Net::SocketAddress & sa, const MulticastCallback * callback);
    void releaseCallback(const MulticastCallback * callback);
	void removeMulticastListener(const Poco::Net::SocketAddress & sa, const MulticastCallback * callback);

	bool hasMulticastListener(const Poco::Net::SocketAddress & sa) const;

    void receive(std::list<PendingMessage> & inMessages);

private:
	bool createMulticastSocket(const Poco::Net::SocketAddress & sa);
	void destroyMulticastSocket(Poco::Net::MulticastSocket * ms);

	std::map<Poco::Net::SocketAddress, std::shared_ptr<Poco::Net::MulticastSocket>> multicastSockets;
	std::map<Poco::Net::SocketAddress, std::vector<const MulticastCallback * >> multicastCallbacks;

	mutable Poco::Mutex mutex;
};

} /* namespace Comm */
} /* namespace OSCLib */
#endif /* MULTICASTSOCKETMANAGER_H_ */
