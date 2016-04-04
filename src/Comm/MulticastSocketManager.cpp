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

#include "OSCLib/Comm/IPBinding.h"
#include "OSCLib/Comm/Message.h"
#include "OSCLib/Comm/MulticastCallback.h"
#include "OSCLib/Comm/MulticastSocketManager.h"
#include "OSCLib/OSCLibrary.h"
#include "OSCLib/Comm/NetworkInterface.h"
#include "OSCLib/Util/DebugOut.h"

#include <algorithm>

#include "Poco/Buffer.h"
#include "Poco/ScopedLock.h"
#include "Poco/Net/IPAddress.h"

namespace OSCLib {
namespace Comm {

using namespace Util;

MulticastSocketManager::MulticastSocketManager() {

}

MulticastSocketManager::~MulticastSocketManager() {

	Poco::Mutex::ScopedLock lock(mutex);

	std::map<Poco::Net::SocketAddress, std::vector<const MulticastCallback * > >::iterator mIt;

	while (!multicastCallbacks.empty()) {
		mIt = multicastCallbacks.begin();
		const Poco::Net::SocketAddress sa = mIt->first;
		const MulticastCallback * callback = *(mIt->second).begin();

		removeMulticastListener(sa, callback);
	}
}

void MulticastSocketManager::addMulticastListener(const Poco::Net::SocketAddress & sa, const MulticastCallback * callback) {
	Poco::Mutex::ScopedLock lock(mutex);

	if (!hasMulticastListener(sa)) {

		if (!createMulticastSocket(sa)) {
			DebugOut(DebugOut::Error, "MulticastSocketManager") << "Adding multicast listener failed.";
		}

		std::vector<const MulticastCallback *> newCallback;
		newCallback.push_back(callback);
		multicastCallbacks[sa] = newCallback;
	} else {
		std::vector<const MulticastCallback*> & existingCallbacks = multicastCallbacks[sa];

		if (find(existingCallbacks.begin(), existingCallbacks.end(), callback) == existingCallbacks.end()) {
			existingCallbacks.push_back(callback);
		}
	}
	DebugOut(DebugOut::Full, "MulticastSocketManager") << "Multicast listener added for socket " << sa.toString() << " with callback UUID " << callback->getMulticastCallbackUUID();
}

void MulticastSocketManager::receive(std::list<PendingMessage> & inMessages) {
	Poco::Mutex::ScopedLock lock(mutex);

	for (auto &nextSocket : multicastSockets) {
		const Poco::Net::SocketAddress sa(nextSocket.first);
		std::shared_ptr<Poco::Net::MulticastSocket> ms(nextSocket.second);

		int available = ms->available();
		if (available == 0) {
			continue;
		}

		Poco::Buffer<char> buf(available);
		Poco::Net::SocketAddress remoteAddr;
		int received = ms->receiveFrom(buf.begin(), available, remoteAddr, 0);

		const std::string socketData(buf.begin(), received);

		if (DebugOut::Info <= DebugOut::DEBUG_LEVEL) {
			DebugOut(DebugOut::Info, "MulticastSocketManager") << "IN, raw multicast message received from " << remoteAddr.toString();
		}
		if (DebugOut::Verbose <= DebugOut::DEBUG_LEVEL) {
			DebugOut(DebugOut::Verbose, "MulticastSocketManager") << socketData;
		}

		std::vector<const MulticastCallback*> & callbacks = multicastCallbacks[sa];
		std::vector<const MulticastCallback*>::iterator mIt;

		for (mIt = callbacks.begin(); mIt != callbacks.end(); ++mIt) {
			if (DebugOut::Info <= DebugOut::DEBUG_LEVEL) {
				DebugOut(DebugOut::Info, "MulticastSocketManager") << "Passing multicast message to callback " << (*mIt)->getMulticastCallbackUUID();
			}
            PendingMessage pendingMsg;
            pendingMsg.sourcemc = *mIt;
            pendingMsg.msg.setRawBuffer(socketData);
            if (DebugOut::Verbose <= DebugOut::DEBUG_LEVEL) {
                std::cout << pendingMsg.msg.getRawBuffer() << std::endl;
                std::cout << std::flush;
            }
            pendingMsg.msg.setSource(std::shared_ptr<IPBinding>(new IPBinding(remoteAddr)));
            // This supports unicast responses to multicast messages
            pendingMsg.msg.setDispatcher(std::shared_ptr<IPBinding>(new IPBinding(sa)));
            pendingMsg.msg.setReceiveProtocol(Message::UDP_MULTICAST);

            pendingMsg.msg.setReceiveProtocol(Message::UDP_UNICAST);

            inMessages.push_back(pendingMsg);
		}
	}
}

bool MulticastSocketManager::hasMulticastListener(const Poco::Net::SocketAddress & sa) const {
	Poco::Mutex::ScopedLock lock(mutex);
	return !(multicastSockets.find(sa) == multicastSockets.end());
}

void MulticastSocketManager::releaseCallback(const MulticastCallback * callback) {

    Poco::Mutex::ScopedLock lock(mutex);
    std::vector<Poco::Net::SocketAddress> toErase;

    for (auto &nextEntry : multicastCallbacks) {
        for (auto &nextCallBck : nextEntry.second) {
            if (nextCallBck == callback) {
                toErase.push_back(nextEntry.first);
            }
        }
    }

    for (auto &nextKill : toErase) {
        removeMulticastListener(nextKill, callback);
    }
}

void MulticastSocketManager::removeMulticastListener(const Poco::Net::SocketAddress & sa, const MulticastCallback * callback) {

	Poco::Mutex::ScopedLock lock(mutex);

	std::vector<const MulticastCallback*> & callbacks = multicastCallbacks[sa];
	std::vector<const MulticastCallback*>::iterator mIt = find(callbacks.begin(), callbacks.end(), callback);

	if (mIt != callbacks.end()) {
		callbacks.erase(mIt);
	}

	if (callbacks.empty()) {
		destroyMulticastSocket(multicastSockets[sa].get());
		multicastCallbacks.erase(sa);
		multicastSockets.erase(sa);
	}
	DebugOut(DebugOut::Full, "MulticastSocketManager") << "Multicast listener removed for socket " << sa.toString() << " with callback UUID " << callback->getMulticastCallbackUUID();
}

bool MulticastSocketManager::createMulticastSocket(const Poco::Net::SocketAddress & sa) {

	Poco::Mutex::ScopedLock lock(mutex);

	std::shared_ptr<Poco::Net::MulticastSocket> ms;

	try {
		ms.reset(new Poco::Net::MulticastSocket(sa.family()));
	} catch(...) {
		ms = nullptr;
		return false;
	}

	try {
		ms->bind(Poco::Net::SocketAddress(Poco::Net::IPAddress(Poco::Net::IPAddress::Family::IPv4), sa.port()), true);
        // We want to receive on all suitable interfaces, so we must call join for each interface
        std::vector<Poco::Net::NetworkInterface> ifList;
        for (const auto & nextIf : Poco::Net::NetworkInterface::list())
        {
            const std::string bindInt(OSCLibrary::getInstance()->getBindInterface());
            if (!nextIf.supportsIPv4() || nextIf.address().isLoopback()
                // If a target adapter is specified (other than 0.0.0.0 - which is the default), we discard all others
                || (!bindInt.empty() && bindInt.compare("0.0.0.0") != 0 && bindInt.compare(nextIf.address().toString()) != 0))
                continue;
            ms->joinGroup(sa.host(), nextIf);
        }		
        ms->setBlocking(false);
	} catch (Poco::IOException & e) {
		ms = nullptr;
		DebugOut(DebugOut::Error, "MulticastSocketManager") << "Failed binding multicast listening socket to " << sa.toString() << " with error " << e.displayText();
		return false;
	} catch (...) {
		DebugOut(DebugOut::Error, "MulticastSocketManager") << "Failed binding multicast listening socket with unknown socket error! " << std::endl;
		return false;
	}

	DebugOut(DebugOut::Info, "MulticastSocketManager") << "Multicast listening socket opened: " << sa.toString();

	multicastSockets[sa] = ms;

	return true;
}

void MulticastSocketManager::destroyMulticastSocket(Poco::Net::MulticastSocket * ms) {
	if (ms == nullptr) {
		return;
	}
	DebugOut(DebugOut::Info, "MulticastSocketManager") << "Multicast listening socket closing.";
	ms->close();
}


} /* namespace Comm */
} /* namespace OSCLib */
