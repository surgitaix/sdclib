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
 *  @file DefaultNetworkInterface.cpp
 *  @project OSCLib
 *  @date 24.08.2011
 *  @author besting
 *  @copyright (c) SurgiTAIX AG
 */

#include "OSCLib/OSCLibrary.h"
#include "OSCLib/Comm/Binding.h"
#include "OSCLib/Comm/DefaultNetworkInterface.h"
#include "OSCLib/Comm/Message.h"
#include "OSCLib/Comm/UnicastCallback.h"
#include "OSCLib/Comm/MulticastCallback.h"
#include "OSCLib/Util/DebugOut.h"
#include "OSCLib/Util/TypeConversion.h"
#include "Poco/Notification.h"

#include <string>

#include "Poco/ScopedLock.h"

using namespace OSCLib::Util;

namespace OSCLib {
namespace Comm {

class MessageNotification : public Poco::Notification {
public:

	MessageNotification(std::shared_ptr<PendingMessage> pm) : pm(pm) {
	}

	std::shared_ptr<PendingMessage> getPendingMessage() const {
		return pm;
	}

private:
	std::shared_ptr<PendingMessage> pm;
};

class AsyncMessageWriter : public Util::Task {
public:
	AsyncMessageWriter(DefaultNetworkInterface & dni,
			Poco::NotificationQueue & queue) :
		dni(dni),
		queue(queue) {
    }

    ~AsyncMessageWriter() {
    }

    void runImpl() {
    	Poco::AutoPtr<Poco::Notification> pNf(queue.waitDequeueNotification(1000));
		while (pNf)
		{
			MessageNotification * outNf = dynamic_cast<MessageNotification*>(pNf.get());
			std::shared_ptr<PendingMessage> pm(outNf->getPendingMessage());
            if (pm->msg.getSource() != nullptr && !dni.isValidUnicastCallback(pm->source)) {
                DebugOut(DebugOut::Error, "DefaultNetworkInterface (AsyncMessageWriter)") << "Callback invalid, message discarded (out): " << pm->logInfo;
            }
            else {
                dni.sendOutNow(pm->source, pm->msg);
            }

			pNf = queue.waitDequeueNotification(1000);
		}
    }

private:
    DefaultNetworkInterface & dni;
    Poco::NotificationQueue & queue;
};

class AsyncMessageDispatcher : public Util::Task {
public:
	AsyncMessageDispatcher(DefaultNetworkInterface & dni,
			Poco::NotificationQueue & queue) :
		dni(dni),
		queue(queue) {
    }

    ~AsyncMessageDispatcher() {
    }

    void runImpl() {
    	Poco::AutoPtr<Poco::Notification> pNf(queue.waitDequeueNotification(1000));
		while (pNf)
		{
			MessageNotification * outNf = dynamic_cast<MessageNotification*>(pNf.get());
			std::shared_ptr<PendingMessage> pm = outNf->getPendingMessage();
            if (pm->source != nullptr && dni.isValidUnicastCallback(pm->source)) {
				const_cast<UnicastCallback *>(pm->source)->unicastCallback(pm->msg);
			}
            else if (pm->sourcemc != nullptr && dni.isValidMulticastCallback(pm->sourcemc)) {
                const_cast<MulticastCallback *>(pm->sourcemc)->udpMulticastCallback(pm->msg);
            }
            else {
                DebugOut(DebugOut::Error, "DefaultNetworkInterface (AsyncMessageDispatcher)") << "Callback invalid, message discarded (in). " << pm->logInfo;
			}

			pNf = queue.waitDequeueNotification(1000);
		}
    }

private:
    DefaultNetworkInterface & dni;
    Poco::NotificationQueue & queue;
};


DefaultNetworkInterface::DefaultNetworkInterface()
{
	messageWriter.reset(new AsyncMessageWriter(*this, outMessageQueue));
	messageWriter->start();
	messageDispatcher.reset(new AsyncMessageDispatcher(*this, inMessageQueue));
	messageDispatcher->start();
}

DefaultNetworkInterface::~DefaultNetworkInterface()
{
}

void DefaultNetworkInterface::interruptMessaging() {
    inMessages.clear();
    messageWriter->interrupt();
    messageDispatcher->interrupt();
}

bool DefaultNetworkInterface::sendMessage(const UnicastCallback * const source, Message& msg, const std::string& logInfo)
{
	DebugOut(DebugOut::Full, "DefaultNetworkInterface") << "Queuing message: " << logInfo;

	Poco::Mutex::ScopedLock lock(mutex);
	std::shared_ptr<PendingMessage> pendingMsg(new PendingMessage(source, msg, logInfo));
	outMessageQueue.enqueueNotification(new MessageNotification(pendingMsg));

	return true;
}

bool DefaultNetworkInterface::sendOutNow(const UnicastCallback * const source, const Message & msg)
{
	// No mutex here, this method is currently only called by the async message writer.
	try {
		// new multicast message
		if (msg.getSendProtocol() == Message::UDP_MULTICAST && msg.getReceiveProtocol() == Message::UNKNOWN_PROTOCOL) {
			DebugOut(DebugOut::Full, "DefaultNetworkInterface") << "Sending message (new UDP multicast).";
			DebugOut(DebugOut::Verbose, "DefaultNetworkInterface") << msg;
			datagramSocketManager.send(msg, source);
			return true;
		}

		// udp unicast reply to incoming multicast message
		if (msg.getSendProtocol() == Message::UDP_UNICAST && msg.getReceiveProtocol() == Message::UDP_MULTICAST) {
			DebugOut(DebugOut::Full, "DefaultNetworkInterface") << "Sending message (unicast UDP reply to UDP multicast request).";
			DebugOut(DebugOut::Verbose, "DefaultNetworkInterface") << msg;
			datagramSocketManager.send(msg, source);
			return true;
		}

		// new udp unicast message
		if (msg.getSendProtocol() == Message::UDP_UNICAST && msg.getReceiveProtocol() == Message::UNKNOWN_PROTOCOL) {
			DebugOut(DebugOut::Full, "DefaultNetworkInterface") << "Sending message (new UDP unicast).";
			DebugOut(DebugOut::Verbose, "DefaultNetworkInterface") << msg;
			datagramSocketManager.send(msg, source);
			return true;
		}

		// udp unicast reply to incoming udp unicast message
		if (msg.getSendProtocol() == Message::UDP_UNICAST && msg.getReceiveProtocol() == Message::UDP_UNICAST) {
			DebugOut(DebugOut::Full, "DefaultNetworkInterface") << "Sending message (unicast UDP reply to UDP unicast request).";
			DebugOut(DebugOut::Verbose, "DefaultNetworkInterface") << msg;
			datagramSocketManager.send(msg, source);
			return true;
		}

		// tcp message
		if (msg.getSendProtocol() == Message::TCP_HTTP) {
            throw std::runtime_error("TCP/HTTP not supported any more by default network interface!");
		}
	} catch(Poco::Exception& e) {
		DebugOut(DebugOut::Error, "DefaultNetworkInterface") << "Exception during send process: " << e.what();
		DebugOut(DebugOut::Verbose, "DefaultNetworkInterface") << msg;
		return false;
	}

	DebugOut(DebugOut::Error, "DefaultNetworkInterface") << "Message not sent due to unknown protocol!";
	DebugOut(DebugOut::Verbose, "DefaultNetworkInterface") << msg;

	return false;
}

void DefaultNetworkInterface::addUDPMulticastListener(const MulticastCallback * const callback, const std::string & groupIp, unsigned int groupPort)
{
	DebugOut(DebugOut::Info, "DefaultNetworkInterface") << "Adding multicast listener.";

	Poco::Net::SocketAddress sa(groupIp, groupPort);
	multicastSocketManager.addMulticastListener(sa, callback);
}

void DefaultNetworkInterface::removeUDPMulticastListener(const MulticastCallback * const callback, const std::string& ip, unsigned int port)
{
	DebugOut(DebugOut::Info, "DefaultNetworkInterface") << "Removing multicast listener.";

	Poco::Net::SocketAddress sa(ip, port);
	multicastSocketManager.removeMulticastListener(sa, callback);
}

void DefaultNetworkInterface::addUDPListener(const UnicastCallback * const callback, const std::string& hostIp, unsigned int hostPort)
{
	Poco::Net::SocketAddress sa(hostPort);
	if (hostIp != "0.0.0.0")
		sa = Poco::Net::SocketAddress(hostIp, hostPort);
	datagramSocketManager.addConnection(sa, callback, false);
}

void DefaultNetworkInterface::removeListener(const UnicastCallback * const callback, const std::string& hostIp, unsigned int hostPort)
{
	Poco::Net::SocketAddress sa(hostPort);
	if (hostIp != "0.0.0.0")
		sa = Poco::Net::SocketAddress(hostIp, hostPort);
	datagramSocketManager.releaseConnection(sa);
}

void DefaultNetworkInterface::processIn()
{
    multicastSocketManager.receive(inMessages);
	datagramSocketManager.receive(inMessages);

	// Process
	while(true) {
		if (inMessages.empty()) {
			break;
		} else {
			PendingMessage pendingMsg = inMessages.front();
			inMessages.pop_front();
			std::shared_ptr<PendingMessage> msg(new PendingMessage(pendingMsg));
			inMessageQueue.enqueueNotification(new MessageNotification(msg));
		}
	}
}

void DefaultNetworkInterface::addValidUnicastCallback(const UnicastCallback * const cb) {
	Poco::Mutex::ScopedLock lock(mutex);
	validUnicastCallbacks.insert(cb);
}

void DefaultNetworkInterface::removeValidUnicastCallback(const UnicastCallback * const cb) {
	Poco::Mutex::ScopedLock lock(mutex);
	validUnicastCallbacks.erase(cb);
	datagramSocketManager.releaseCallback(cb);
}

bool DefaultNetworkInterface::isValidUnicastCallback(const UnicastCallback * const cb) {
	Poco::Mutex::ScopedLock lock(mutex);
	return validUnicastCallbacks.find(cb) != validUnicastCallbacks.end();
}

void DefaultNetworkInterface::addValidMulticastCallback(const MulticastCallback * const cb) {
    Poco::Mutex::ScopedLock lock(mutex);
    validMulticastCallbacks.insert(cb);
}

void DefaultNetworkInterface::removeValidMulticastCallback(const MulticastCallback * const cb) {
    Poco::Mutex::ScopedLock lock(mutex);
    validMulticastCallbacks.erase(cb);
    multicastSocketManager.releaseCallback(cb);
}

bool DefaultNetworkInterface::isValidMulticastCallback(const MulticastCallback * const cb) {
    Poco::Mutex::ScopedLock lock(mutex);
    return validMulticastCallbacks.find(cb) != validMulticastCallbacks.end();
}

} /* namespace Comm */
} /* namespace OSCLib */
