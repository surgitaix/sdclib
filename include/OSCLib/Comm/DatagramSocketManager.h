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

#ifndef DATAGRAMSOCKETMANAGER_H_
#define DATAGRAMSOCKETMANAGER_H_

#include "PendingMessage.h"

#include <vector>
#include <map>
#include <list>
#include <set>

#include "Poco/Timestamp.h"
#include "Poco/Net/DatagramSocket.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/NetworkInterface.h"

namespace OSCLib {
namespace Comm {

class UnicastCallback;

class DatagramSocketManager {
public:
	DatagramSocketManager();
	virtual ~DatagramSocketManager();

	void addConnection(std::shared_ptr<Poco::Net::DatagramSocket> ss, const UnicastCallback * callback, bool hasTimeout = true);
	void addConnection(const Poco::Net::SocketAddress & bindAddress, const UnicastCallback * callback, bool hasTimeout = true);
	void releaseConnection(std::shared_ptr<Poco::Net::DatagramSocket> ds);
	void releaseConnection(const Poco::Net::SocketAddress & listeningSocketAddress);
	void releaseCallback(const UnicastCallback * callback);

	void send(const Message & msg, const UnicastCallback * callback);
	void receive(std::list<PendingMessage> & inMessages);

private:
	std::shared_ptr<Poco::Net::DatagramSocket> createOrGetSocket(const Poco::Net::SocketAddress & dest, 
		std::shared_ptr<Poco::Net::NetworkInterface> netIf, const UnicastCallback * callback, bool hasTimeout = true);
	std::map<std::shared_ptr<Poco::Net::DatagramSocket>, const UnicastCallback *> connections;
	std::map<std::shared_ptr<Poco::Net::DatagramSocket>, Poco::Timestamp> timeouts;
	std::set<std::shared_ptr<Poco::Net::DatagramSocket>> persistentOutgoingMCSockets;

	Poco::Mutex mutex;
};

} /* namespace Comm */
} /* namespace OSCLib */
#endif /* DATAGRAMSOCKETMANAGER_H_ */
