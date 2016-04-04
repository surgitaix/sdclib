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
 * SocketManager.cpp
 *
 *  @Copyright (C) 2014, SurgiTAIX AG
 *  Author: besting, roehser
 */

#include "OSCLib/Comm/Binding.h"
#include "OSCLib/OSCLibrary.h"
#include "OSCLib/Comm/DatagramSocketManager.h"

#include "OSCLib/Comm/Message.h"
#include "OSCLib/Comm/UnicastCallback.h"
#include "OSCLib/Util/DebugOut.h"
#include "OSCLib/Util/Helpers.h"
#include "Poco/Buffer.h"

using namespace OSCLib::Util;

namespace OSCLib {
namespace Comm {

DatagramSocketManager::DatagramSocketManager() {

}

DatagramSocketManager::~DatagramSocketManager() {

}

void DatagramSocketManager::addConnection(std::shared_ptr<Poco::Net::DatagramSocket> ss, const UnicastCallback * callback, bool hasTimeout) {

	Poco::Mutex::ScopedLock lock(mutex);

	DebugOut(DebugOut::Full, "DatagrammSocketManager") << "UDP socket added. ";
	ss->setReceiveBufferSize(1000000);
	ss->setSendBufferSize(1000000);
	connections[ss] = callback;
	timeouts[ss] = Poco::Timestamp();
	if (!hasTimeout) {
		persistentOutgoingMCSockets.insert(ss);
	}
}

void DatagramSocketManager::addConnection(const Poco::Net::SocketAddress & bindAddress, const UnicastCallback * callback, bool hasTimeout) {

	std::shared_ptr<Poco::Net::DatagramSocket> datagramSocket(new Poco::Net::DatagramSocket(bindAddress));
	addConnection(datagramSocket, callback, hasTimeout);
}

void DatagramSocketManager::receive(std::list<PendingMessage> & inMessages) {

	Poco::Mutex::ScopedLock lock(mutex);

	const Poco::Timestamp::TimeDiff elapsedTimeOut(10000000);

	std::map<std::shared_ptr<Poco::Net::DatagramSocket>, const UnicastCallback *> toErase;

	for (const auto & nextConnection : connections) {
		const Poco::Timespan timeout(0);
		if (!nextConnection.first->poll(timeout, Poco::Net::DatagramSocket::SELECT_READ)) {
			if (persistentOutgoingMCSockets.find(nextConnection.first) == persistentOutgoingMCSockets.end() && timeouts[nextConnection.first].elapsed() > elapsedTimeOut) {
				DebugOut(DebugOut::Full, "DatagrammSocketManager") << "Socket not used for more than "<< (double)(elapsedTimeOut)/1000000 << " s. Closing ...";
				toErase[nextConnection.first] = nextConnection.second;
			}
			continue;
		}
		std::shared_ptr<Poco::Net::DatagramSocket> ds(nextConnection.first);
		const UnicastCallback * callback = nextConnection.second;

		int available = ds->available();
		if (available != 0) {
			timeouts[ds].update();
		} else if (persistentOutgoingMCSockets.find(ds) == persistentOutgoingMCSockets.end() && timeouts[ds].elapsed() > elapsedTimeOut) {
			DebugOut(DebugOut::Full, "DatagrammSocketManager") << "Socket not used for more than "<< (double)(elapsedTimeOut)/1000000 << " s. Closing ...";
			toErase[ds] = callback;
			continue;
		}

		if (available <= 0) {
			continue;
		}

		Poco::Buffer<char> buf(available);
		Poco::Net::SocketAddress remoteAddr;
        int received = 0;
        try
        {
            received = ds->receiveFrom(buf.begin(), available, remoteAddr, 0);
        }
        catch (...)
        {
            DebugOut(DebugOut::Error, "DatagrammSocketManager") << "Socket I/O Error.";
            continue;
        }
        Poco::Net::SocketAddress dispatcherAddress(ds->address());

        std::string data(std::string(buf.begin(), received));

        if (DebugOut::Info <= DebugOut::DEBUG_LEVEL) {
            DebugOut(DebugOut::Info, "DatagrammSocketManager") << "IN, raw udp unicast message received from " << remoteAddr.toString();
        }
        if (DebugOut::Verbose <= DebugOut::DEBUG_LEVEL) {
            DebugOut(DebugOut::Verbose, "DatagrammSocketManager") << data;
        }

		if (Util::containedMessagesComplete(data) && data.size() > 0)
		{
			bool inValid = (data.length() < 32 && data.find('<') == std::string::npos);

			if (!inValid)
			{
				PendingMessage pendingMsg;
				pendingMsg.source = callback;
				std::shared_ptr<IPBinding> remoteAddress(new IPBinding(remoteAddr));
				remoteAddress->setType(AbstractBinding::UDP);
				pendingMsg.msg.setSource(remoteAddress);
				std::shared_ptr<IPBinding> dispatcher(new IPBinding(dispatcherAddress));
				dispatcher->setType(AbstractBinding::UDP);
				pendingMsg.msg.setDispatcher(dispatcher);
				pendingMsg.msg.setRawBuffer(data);
				pendingMsg.msg.setReceiveProtocol(Message::UDP_UNICAST);

				inMessages.push_back(pendingMsg);
				if (DebugOut::Full <= DebugOut::DEBUG_LEVEL) {
					DebugOut(DebugOut::Full, "DatagrammSocketManager") << "inMessage queued. ";
				}
				if (DebugOut::Verbose <= DebugOut::DEBUG_LEVEL) {
					DebugOut(DebugOut::Verbose, "DatagrammSocketManager") << pendingMsg.msg;
				}
			}

		} else {
			if (DebugOut::Error <= DebugOut::DEBUG_LEVEL) {
				DebugOut(DebugOut::Error, "DatagrammSocketManager") << "EXTRACTED DATA INVALID. Message skipped.";
			}
		}
	}

	for (auto &nextKill : toErase) {
		releaseConnection(nextKill.first);
	}

}

void DatagramSocketManager::send(const Message & msg, const UnicastCallback * callback) {

	Poco::Mutex::ScopedLock lock(mutex);

	Poco::Net::SocketAddress destinationAddress(msg.getDestination()->getIp(), msg.getDestination()->getPort());

    if (DebugOut::Full <= DebugOut::DEBUG_LEVEL) {
        DebugOut(DebugOut::Full, "DatagrammSocketManager") << "Sending message to datagram socket. ";
    }
    if (DebugOut::Verbose <= DebugOut::DEBUG_LEVEL) {
        DebugOut(DebugOut::Verbose, "DatagrammSocketManager") << msg;
    }

    if (msg.getSendProtocol() != Message::UDP_MULTICAST) {
		std::shared_ptr<Poco::Net::DatagramSocket> datagramSocket = createOrGetSocket(destinationAddress, nullptr, callback);
        const std::string msgBuf(msg.getRawBuffer());
        datagramSocket->sendTo(msgBuf.c_str(), msgBuf.length(), destinationAddress, 0);
    }
    else
    {
        // Since mcast addresses are reachable on all interfaces, we must send them on all.
		// Otherwise, we could catch the wrong one, and the message would be lost.
        std::vector<Poco::Net::NetworkInterface> ifList;
        const std::string msgBuf(msg.getRawBuffer());
        for (const auto & nextIf : Poco::Net::NetworkInterface::list())
        {
            const std::string bindInt(OSCLibrary::getInstance()->getBindInterface());
            if (!nextIf.supportsIPv4() || nextIf.address().isLoopback() 
                // If a target adapter is specified (other than 0.0.0.0 - which is the default), we discard all others
                || (!bindInt.empty() && bindInt.compare("0.0.0.0") != 0 && bindInt.compare(nextIf.address().toString()) != 0))
                continue;
            // Create persistent socket for MC
            std::shared_ptr<Poco::Net::DatagramSocket> datagramSocket = createOrGetSocket(destinationAddress, std::make_shared<Poco::Net::NetworkInterface>(nextIf), callback, false);
            datagramSocket->sendTo(msgBuf.c_str(), msgBuf.length(), destinationAddress, 0);
        }
    }
}

std::shared_ptr<Poco::Net::DatagramSocket> DatagramSocketManager::createOrGetSocket(const Poco::Net::SocketAddress & dest, 
    std::shared_ptr<Poco::Net::NetworkInterface> netIf, const UnicastCallback * callback, bool hasTimeout) {
    if (!hasTimeout) {
        for (const auto & socket : persistentOutgoingMCSockets) {
            if (connections.find(socket) != connections.end()) {
                if (connections[socket] == callback)
                    return socket;
            }
        }
    }
	std::shared_ptr<Poco::Net::DatagramSocket> datagramSocket(new Poco::Net::DatagramSocket(dest.family()));
	timeouts[datagramSocket].update();
    addConnection(datagramSocket, callback, hasTimeout);
	if (netIf != nullptr) {
		datagramSocket->bind(Poco::Net::SocketAddress(netIf->address(), 0));
	}
	return datagramSocket;
}

void DatagramSocketManager::releaseCallback(const UnicastCallback * callback) {

	Poco::Mutex::ScopedLock lock(mutex);

	std::map<std::shared_ptr<Poco::Net::DatagramSocket>, const UnicastCallback *> toErase;

	for (auto &nextConn : connections) {
		if (nextConn.second == callback) {
			toErase[nextConn.first] = nextConn.second;
		}
	}

	for (auto &nextKill : toErase) {
		releaseConnection(nextKill.first);
	}
}

void DatagramSocketManager::releaseConnection(const Poco::Net::SocketAddress & listeningSocketAddress) {

	Poco::Mutex::ScopedLock lock(mutex);

	for (auto &nextConn : connections) {
		if (nextConn.first->address() == listeningSocketAddress) {
			releaseConnection(nextConn.first);
			break;
		}
	}
}

void DatagramSocketManager::releaseConnection(std::shared_ptr<Poco::Net::DatagramSocket> ds) {

	Poco::Mutex::ScopedLock lock(mutex);

	if (persistentOutgoingMCSockets.find(ds) != persistentOutgoingMCSockets.end()) {
		DebugOut(DebugOut::Full, "DatagrammSocketManager") << "Persistent UDP socket closing. ";
		persistentOutgoingMCSockets.erase(ds);
	} else {
		DebugOut(DebugOut::Full, "DatagrammSocketManager") << "UDP socket closing. ";
	}

	ds->close();
	connections.erase(ds);
	timeouts.erase(ds);
	DebugOut(DebugOut::Full, "DatagrammSocketManager") << "A total of " << this->connections.size() << " open sockets remaining.";
}

} /* namespace Comm */
} /* namespace OSCLib */
