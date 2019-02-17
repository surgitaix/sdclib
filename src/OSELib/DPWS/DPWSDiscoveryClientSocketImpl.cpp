/*
 * DPWSDiscoveryClientSocketImpl.cpp
 *
 *  Created on: 11.12.2015
 *      Author: matthias
 */

#include "OSELib/DPWS/DPWSDiscoveryClientSocketImpl.h"
#include "OSCLib/SDCInstance.h"
#include "OSELib/DPWS/DPWS11Constants.h"
#include "OSELib/DPWS/DPWSCommon.h"
#include "OSELib/Helper/BufferAdapter.h"

#include "NormalizedMessageModel.hxx"

#include <iostream>

#include <Poco/Buffer.h>
#include <Poco/UUIDGenerator.h>
#include <Poco/Net/SocketAddress.h>


using namespace OSELib::DPWS::Impl;

struct SendMulticastMessage : public Poco::Notification {
	SendMulticastMessage(const std::string & message) :
		content_(message) {}
	const std::string content_;
};

const MESSAGEMODEL::Envelope buildProbeMessage(const OSELib::DPWS::ProbeType & filter) {
	MESSAGEMODEL::Envelope::HeaderType header;
	{
		header.Action(probeUri);
		header.To(discoveryUri);
		header.MessageID(xml_schema::Uri(Poco::UUIDGenerator().create().toString()));
	}
	MESSAGEMODEL::Envelope::BodyType body;
	{
		body.Probe(filter);
	}

	return MESSAGEMODEL::Envelope(header, body);
}

const MESSAGEMODEL::Envelope buildResolveMessage(const OSELib::DPWS::ResolveType & filter) {
	MESSAGEMODEL::Envelope::HeaderType header;
	{
		header.Action(resolveUri);
		header.To(discoveryUri);
		header.MessageID(xml_schema::Uri(Poco::UUIDGenerator().create().toString()));
	}
	MESSAGEMODEL::Envelope::BodyType body;
	{
		body.Resolve(filter);
	}

	return MESSAGEMODEL::Envelope(header, body);
}

DPWSDiscoveryClientSocketImpl::DPWSDiscoveryClientSocketImpl(
        SDCLib::SDCInstance_shared_ptr p_SDCInstance,
		ByeNotificationDispatcher & byeDispatcher,
		HelloNotificationDispatcher & helloDispatcher,
		ProbeMatchNotificationDispatcher & probeMatchDispatcher,
		ResolveMatchNotificationDispatcher & resolveDispatcher) :
	WithLogger(Log::DISCOVERY),
	m_SDCInstance(p_SDCInstance),
	_byeDispatcher(byeDispatcher),
	_helloDispatcher(helloDispatcher),
	_probeMatchDispatcher(probeMatchDispatcher),
	_resolveDispatcher(resolveDispatcher),
    m_ipv4MulticastAddress(Poco::Net::SocketAddress(p_SDCInstance->_getMulticastIPv4(), p_SDCInstance->_getMulticastPortv4())),
    m_ipv6MulticastAddress(Poco::Net::SocketAddress(p_SDCInstance->_getMulticastIPv6(), p_SDCInstance->_getMulticastPortv6()))
{

    if (m_SDCInstance->getIP4enabled()) {
        // Bind only interfaces we specified
        if (m_SDCInstance->isBound()) {
            m_ipv4DiscoverySocket = Poco::Net::MulticastSocket(Poco::Net::IPAddress::Family::IPv4);
            for (auto t_interface : m_SDCInstance->getNetworkInterfaces()) {
                try
                {
                    auto t_IP = Poco::Net::IPAddress::Family::IPv4;
                    auto t_ipv4BindingAddress = Poco::Net::SocketAddress(t_IP, m_ipv4MulticastAddress.port());
                    m_ipv4DiscoverySocket.bind(t_ipv4BindingAddress, t_interface->SO_REUSEADDR_FLAG, t_interface->SO_REUSEPORT_FLAG);
                    m_ipv4DiscoverySocket.joinGroup(m_ipv4MulticastAddress.host(), t_interface->m_if);
                    // DatagramSocket
                    Poco::Net::DatagramSocket t_datagramSocket(Poco::Net::SocketAddress(t_interface->m_IPv4, m_ipv4DatagrammSocketPort), t_interface->SO_REUSEADDR_FLAG);
                    t_datagramSocket.setReusePort(t_interface->SO_REUSEPORT_FLAG);
                    t_datagramSocket.setBlocking(false);
                    m_reactor.addEventHandler(t_datagramSocket, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onDatagrammSocketReadable));
                    m_socketSendMessageQueue[t_datagramSocket].clear();
                }
                catch (...) {
                    // todo fixme. This loop fails, when a network interface has serveral network addresses, i.e. 2 IPv6 global scoped addresses
                    log_error([&] { return "Something went wrong in binding to : " + t_interface->m_name; });
                    continue;
                }
            }
        }
        else
        {
            // Bind on 0.0.0.0
            auto t_ipv4BindingAddress = Poco::Net::SocketAddress(Poco::Net::IPAddress(Poco::Net::IPAddress::Family::IPv4), m_ipv4MulticastAddress.port());
            m_ipv4DiscoverySocket.bind(t_ipv4BindingAddress, m_SO_REUSEADDR_FLAG, m_SO_REUSEPORT_FLAG);
            // Add all interfaces
            for (const auto & nextIf : Poco::Net::NetworkInterface::list()) {
                if (nextIf.supportsIPv4() && nextIf.address().isUnicast() && !nextIf.firstAddress(Poco::Net::IPAddress::Family::IPv4).isLoopback()) {
                    try
                    {
                        // Note: Fails if we enumerate a bridge that is already connected
                        m_ipv4DiscoverySocket.joinGroup(m_ipv4MulticastAddress.host(), nextIf);
                        Poco::Net::DatagramSocket t_datagramSocket(Poco::Net::SocketAddress(nextIf.firstAddress(Poco::Net::IPAddress::Family::IPv4), m_ipv4DatagrammSocketPort), m_SO_REUSEADDR_FLAG);
                        t_datagramSocket.setReusePort(m_SO_REUSEPORT_FLAG);
                        t_datagramSocket.setBlocking(false);
                        m_reactor.addEventHandler(t_datagramSocket, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onDatagrammSocketReadable));
                        m_socketSendMessageQueue[t_datagramSocket].clear();
                    }
                    catch (...) {
                        log_error([&] { return "Something went wrong in binding to : " + nextIf.adapterName(); });
                        continue;
                    }
                }
            }
        }
        // Nonblocking
        m_ipv4DiscoverySocket.setBlocking(false);
        // Add Ipv4 Socket EventHandler
        m_reactor.addEventHandler(m_ipv4DiscoverySocket, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onMulticastSocketReadable));
	}
    if (m_SDCInstance->getIP6enabled()) {

        // Bind only interfaces we specified
        if (m_SDCInstance->isBound()) {
            for (auto t_interface : m_SDCInstance->getNetworkInterfaces()) {
                auto t_ipv6BindingAddress = Poco::Net::SocketAddress (Poco::Net::IPAddress::Family::IPv6, m_ipv6MulticastAddress.port());
                m_ipv6DiscoverySocket.bind(t_ipv6BindingAddress, m_SO_REUSEADDR_FLAG, m_SO_REUSEPORT_FLAG);
                m_ipv6DiscoverySocket.joinGroup(m_ipv6MulticastAddress.host(), t_interface->m_if);
                // DatagramSocket
                Poco::Net::DatagramSocket t_datagramSocket(Poco::Net::SocketAddress(t_interface->m_IPv6, m_ipv6DatagrammSocketPort), t_interface->SO_REUSEADDR_FLAG);
                t_datagramSocket.setReusePort(t_interface->SO_REUSEPORT_FLAG);
                t_datagramSocket.setBlocking(false);
                m_reactor.addEventHandler(t_datagramSocket, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onDatagrammSocketReadable));
                m_socketSendMessageQueue[t_datagramSocket].clear();
            }
          }
        else {
            // Bind on 0.0.0.0
            auto t_ipv6BindingAddress = Poco::Net::SocketAddress (Poco::Net::IPAddress(Poco::Net::IPAddress::Family::IPv6), m_ipv6MulticastAddress.port());
            m_ipv6DiscoverySocket.bind(t_ipv6BindingAddress, m_SO_REUSEADDR_FLAG, m_SO_REUSEPORT_FLAG);

            // Add all interfaces
            for (const auto & nextIf : Poco::Net::NetworkInterface::list()) {
                if (nextIf.supportsIPv6() && nextIf.address().isUnicast() && !nextIf.firstAddress(Poco::Net::IPAddress::Family::IPv6).isLoopback()) {
                        try {
                            m_ipv6DiscoverySocket.joinGroup(m_ipv6MulticastAddress.host(), nextIf);
                            Poco::Net::DatagramSocket t_datagramSocket(Poco::Net::SocketAddress(nextIf.firstAddress(Poco::Net::IPAddress::Family::IPv6), m_ipv6DatagrammSocketPort), m_SO_REUSEADDR_FLAG);
                            t_datagramSocket.setReusePort(m_SO_REUSEPORT_FLAG);
                            t_datagramSocket.setBlocking(false);
                            m_reactor.addEventHandler(t_datagramSocket, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onDatagrammSocketReadable));
                            m_socketSendMessageQueue[t_datagramSocket].clear();
                          } catch (...) {
                              // todo fixme. This loop fails, when a network interface has serveral network addresses, i.e. 2 IPv6 global scoped addresses
                              log_error([&] { return "Something went wrong"; });
                            }
                      }
            }
        }
        // Nonblocking
        m_ipv6DiscoverySocket.setBlocking(false);
        // Add Ipv6 Socket EventHandler
        m_reactor.addEventHandler(m_ipv6DiscoverySocket, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onMulticastSocketReadable));
    }
	xercesc::XMLPlatformUtils::Initialize ();

	m_reactorThread.start(m_reactor);
}

DPWSDiscoveryClientSocketImpl::~DPWSDiscoveryClientSocketImpl() {
	m_reactor.removeEventHandler(m_ipv4DiscoverySocket, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onMulticastSocketReadable));
	m_reactor.removeEventHandler(m_ipv6DiscoverySocket, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onMulticastSocketReadable));

    for (auto t_interface : m_SDCInstance->getNetworkInterfaces()) {
        try
        {
            if (m_SDCInstance->getIP4enabled()) { m_ipv4DiscoverySocket.leaveGroup(m_ipv4MulticastAddress.host(), t_interface->m_if); }
            if (m_SDCInstance->getIP6enabled()) { m_ipv6DiscoverySocket.leaveGroup(m_ipv6MulticastAddress.host(), t_interface->m_if); }
        }
        catch (...) {
            // todo fixme. This loop fails, when a network interface has serveral network addresses, i.e. 2 IPv6 global scoped addresses
            log_error([&] { return "Some thing went wrong leaving : " + t_interface->m_name; });
            continue;
        }
    }

	for (auto & messagingSocketMapping : m_socketSendMessageQueue) {
		m_reactor.removeEventHandler(messagingSocketMapping.first, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onDatagrammSocketReadable));
		m_reactor.removeEventHandler(messagingSocketMapping.first, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::WritableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onDatagrammSocketWritable));
	}

	m_reactor.stop();
	m_reactorThread.join();

	xercesc::XMLPlatformUtils::Terminate ();
}

void DPWSDiscoveryClientSocketImpl::sendProbe(const ProbeType& filter) {
	const MESSAGEMODEL::Envelope message(buildProbeMessage(filter));
	if (message.Header().MessageID().present()) {
		context.registerMessageId(message.Header().MessageID().get());
	}
	for (auto & socketQueue : m_socketSendMessageQueue) {
		socketQueue.second.enqueueNotification(new SendMulticastMessage(serializeMessage(message)));
		m_reactor.addEventHandler(socketQueue.first, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::WritableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onDatagrammSocketWritable));
	}
}

void DPWSDiscoveryClientSocketImpl::sendResolve(const ResolveType& filter) {
	const MESSAGEMODEL::Envelope message(buildResolveMessage(filter));
	if (message.Header().MessageID().present()) {
		context.registerMessageId(message.Header().MessageID().get());
	}
	for (auto & socketQueue : m_socketSendMessageQueue) {
		socketQueue.second.enqueueNotification(new SendMulticastMessage(serializeMessage(message)));
		m_reactor.addEventHandler(socketQueue.first, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::WritableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onDatagrammSocketWritable));
	}
}

void DPWSDiscoveryClientSocketImpl::onMulticastSocketReadable(Poco::Net::ReadableNotification * notification) {
	const Poco::AutoPtr<Poco::Net::ReadableNotification> pNf(notification);
	Poco::Net::MulticastSocket socket(pNf->socket());
	const int available(socket.available());
	if (available == 0) {
		return;
	}

    // Only read if this belongs to this SDCInstance! - Peek first
    Poco::Net::SocketAddress t_sender;
    socket.receiveFrom(nullptr, 0, t_sender, MSG_PEEK);
    if (m_SDCInstance->isBound() && !m_SDCInstance->belongsToSDCInstance(t_sender.host())) {
        return;
    }

	Poco::Buffer<char> buf(available);
	Poco::Net::SocketAddress remoteAddr;
	const int received(socket.receiveFrom(buf.begin(), available, remoteAddr, 0));
	Helper::BufferAdapter adapter(buf, received);
	std::unique_ptr<MESSAGEMODEL::Envelope> message(parseMessage(adapter));

	if (message == nullptr) {
		return;
	}
	if (! message->Header().MessageID().present()) {
		return;
	}
	if (! context.registerMessageId(message->Header().MessageID().get())) {
		return;
	}
	if (! message->Header().AppSequence().present()) {
		return;
	}
	if (! context.registerAppSequence(message->Header().AppSequence().get())) {
		return;
	}
	if (message->Body().Hello().present()) {
		if (! verifyHello(*message)) {
			return;
		}
		_helloDispatcher.dispatch(message->Body().Hello().get());
	} else if (message->Body().Bye().present()) {
		if (! verifyBye(*message)) {
			return;
		}
		_byeDispatcher.dispatch(message->Body().Bye().get());
	}
}

// for receiving the probe / resolve match messages that are send unicast
void DPWSDiscoveryClientSocketImpl::onDatagrammSocketReadable(Poco::Net::ReadableNotification * notification) {
	const Poco::AutoPtr<Poco::Net::ReadableNotification> pNf(notification);
	Poco::Net::DatagramSocket socket(pNf->socket());
	const int available(socket.available());
	if (available == 0) {
		return;
	}

	// Only read if this belongs to this SDCInstance! - Peek first
    Poco::Net::SocketAddress t_sender;
    socket.receiveFrom(nullptr, 0, t_sender, MSG_PEEK);
    if (m_SDCInstance->isBound() && !m_SDCInstance->belongsToSDCInstance(t_sender.host())) {
        return;
    }

	Poco::Buffer<char> buf(available);
	Poco::Net::SocketAddress remoteAddr;
	const int received(socket.receiveFrom(buf.begin(), available, remoteAddr, 0));
	Helper::BufferAdapter adapter(buf, received);
	std::unique_ptr<MESSAGEMODEL::Envelope> message(parseMessage(adapter));

	if (message == nullptr) {
		return;
	}
	if (message->Header().MessageID().present()) {
		if (! context.registerMessageId(message->Header().MessageID().get())) {
			return;
		}
	}
	if (message->Body().ProbeMatches().present()) {
		const WS::DISCOVERY::ProbeMatchesType & probeMatches(message->Body().ProbeMatches().get());
		for (const auto & probeMatch : probeMatches.ProbeMatch()) {
			_probeMatchDispatcher.dispatch(probeMatch);
		}
	} else if (message->Body().ResolveMatches().present()) {
		const WS::DISCOVERY::ResolveMatchesType & resolveMatches(message->Body().ResolveMatches().get());
		if (resolveMatches.ResolveMatch().present()) {
			_resolveDispatcher.dispatch(resolveMatches.ResolveMatch().get());
		}
	}
}

void DPWSDiscoveryClientSocketImpl::onDatagrammSocketWritable(Poco::Net::WritableNotification * notification) {
	const Poco::AutoPtr<Poco::Net::WritableNotification> pNf(notification);
    // By Sebastian TTL
	// Poco::Net::DatagramSocket socket(pNf->socket());
    Poco::Net::MulticastSocket socket(pNf->socket());
    socket.setTimeToLive(OSELib::UPD_MULTICAST_TIMETOLIVE);
	
	const Poco::AutoPtr<Poco::Notification> rawMessage(m_socketSendMessageQueue[socket].dequeueNotification());
	if (rawMessage.isNull()) {
		notification->source().removeEventHandler(socket, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::WritableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onDatagrammSocketWritable));
		return;
	}
	const Poco::AutoPtr<SendMulticastMessage> message(rawMessage.cast<SendMulticastMessage>());
	Poco::Net::SocketAddress multicastAddress(m_ipv4MulticastAddress);
	if (socket.address().family() == Poco::Net::IPAddress::Family::IPv6) {
		multicastAddress = m_ipv6MulticastAddress;
	}

	socket.sendTo(message->content_.c_str(), message->content_.size(), multicastAddress, 0);
}

bool DPWSDiscoveryClientSocketImpl::verifyBye(const MESSAGEMODEL::Envelope & message) {
	if (! message.Header().MessageID().present()) {
		log_error([&] { return "Bye message: Missing MessageID."; });
		return false;
	}
	if (! message.Header().Action().present()) {
		log_error([&] { return "Bye message: Missing Action."; });
		return false;
	}
	if (message.Header().Action().get() != byeUri) {
		log_error([&] { return "Bye message: Invalid Action."; });
		return false;
	}
	if (! message.Header().To().present()) {
		log_error([&] { return "Bye message: Missing To."; });
		return false;
	}
	if (message.Header().To().get() != discoveryUri) {
		log_error([&] { return "Bye message: Invalid value of To."; });
		return false;
	}
	if (! message.Header().AppSequence().present()) {
		log_error([&] { return "Bye message: Missing AppSequence."; });
		return false;
	}
	if (! message.Body().Bye().present()) {
		log_error([&] { return "Bye message: Missing Body."; });
		return false;
	}
	if (message.Body().Bye().get().EndpointReference().Address() == "") {
		log_error([&] { return "Bye message: Empty EndpointReference."; });
		return false;
	}
	if (message.Header().RelatesTo().present()) {
		log_error([&] { return "Bye message: RelatesTo field should not be present."; });
		return false;
	}

	return true;
}

bool DPWSDiscoveryClientSocketImpl::verifyHello(const MESSAGEMODEL::Envelope & message) {
	if (! message.Header().MessageID().present()) {
		log_error([&] { return "Hello message: Missing MessageID."; });
		return false;
	}
	if (! message.Header().Action().present()) {
		log_error([&] { return "Hello message: Missing Action."; });
		return false;
	}
	if (message.Header().Action().get() != helloUri) {
		log_error([&] { return "Hello message: Invalid Action."; });
		return false;
	}
	if (! message.Header().To().present()) {
		log_error([&] { return "Hello message: Missing To."; });
		return false;
	}
	if (message.Header().To().get() != discoveryUri) {
		log_error([&] { return "Hello message: Invalid value of To."; });
		return false;
	}
	if (! message.Header().AppSequence().present()) {
		log_error([&] { return "Hello message: Missing AppSequence."; });
		return false;
	}
	if (! message.Body().Hello().present()) {
		log_error([&] { return "Hello message: Missing body."; });
		return false;
	}
	if (message.Body().Hello().get().EndpointReference().Address() == "") {
		log_error([&] { return "Hello message: Empty EndpointReference."; });
		return false;
	}
	if (message.Header().RelatesTo().present()) {
		log_error([&] { return "Hello message: RelatesTo field should not be present."; });
		return false;
	}

	return true;
}
