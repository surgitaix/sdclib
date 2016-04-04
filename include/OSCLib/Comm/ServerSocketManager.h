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

#ifndef SERVERSOCKETMANAGER_H_
#define SERVERSOCKETMANAGER_H_

#include <map>

#include "Poco/Mutex.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/ServerSocket.h"

namespace OSCLib {
namespace Comm {

class UnicastCallback;
class StreamSocketManager;

class ServerSocketManager {
public:
	ServerSocketManager();
	virtual ~ServerSocketManager();

	void addTCPListener(const Poco::Net::SocketAddress & sa, const UnicastCallback * callback);
	void removeTCPListener(const Poco::Net::SocketAddress & sa, const UnicastCallback * callback);

	bool hasTCPListener(const Poco::Net::SocketAddress & sa) const;

	void acceptNewConnections(StreamSocketManager & streamSocketManager);

private:
	bool createServerSocket(const Poco::Net::SocketAddress & sa);
	void destroyServerSocket(const Poco::Net::SocketAddress & sa);

	std::map<const Poco::Net::SocketAddress, std::shared_ptr<Poco::Net::ServerSocket>> serverSockets;
	std::map<const Poco::Net::SocketAddress, const UnicastCallback * > socketCallbacks;

	mutable Poco::Mutex mutex;
};

} /* namespace Comm */
} /* namespace OSCLib */
#endif /* SERVERSOCKETMANAGER_H_ */
