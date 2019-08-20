/*
 * DPWSDiscoveryClientSocketImpl.cpp
 *
 *  Created on: 11.12.2015, matthias
*  Modified on: 26.07.2019, baumeister
 */

#include "OSELib/DPWS/DPWSDiscoveryClientSocketImpl.h"
#include "SDCLib/Config/NetworkConfig.h"
#include "OSELib/DPWS/DPWS11Constants.h"
#include "OSELib/DPWS/DPWSCommon.h"
#include "OSELib/Helper/BufferAdapter.h"

#include "SDCLib/SDCInstance.h"

#include "NormalizedMessageModel.hxx"

#include <Poco/Buffer.h>
#include <Poco/Net/SocketAddress.h>


using namespace OSELib;
using namespace OSELib::DPWS;
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
		header.MessageID(xml_schema::Uri(SDCLib::SDCInstance::calcMSGID()));
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
		header.MessageID(xml_schema::Uri(SDCLib::SDCInstance::calcMSGID()));
	}
	MESSAGEMODEL::Envelope::BodyType body;
	{
		body.Resolve(filter);
	}

	return MESSAGEMODEL::Envelope(header, body);
}

DPWSDiscoveryClientSocketImpl::DPWSDiscoveryClientSocketImpl(
        SDCLib::Config::NetworkConfig_shared_ptr p_config,
		ByeNotificationDispatcher & byeDispatcher,
		HelloNotificationDispatcher & helloDispatcher,
		ProbeMatchNotificationDispatcher & probeMatchDispatcher,
		ResolveMatchNotificationDispatcher & resolveDispatcher)
: OSELib::Helper::WithLogger(Log::DISCOVERY)
, m_networkConfig(p_config)
, _byeDispatcher(byeDispatcher)
, _helloDispatcher(helloDispatcher)
, _probeMatchDispatcher(probeMatchDispatcher)
, _resolveDispatcher(resolveDispatcher)
, m_ipv4MulticastAddress(Poco::Net::SocketAddress(p_config->_getMulticastIPv4(), p_config->_getMulticastPortv4()))
, m_ipv6MulticastAddress(Poco::Net::SocketAddress(p_config->_getMulticastIPv6(), p_config->_getMulticastPortv6()))
{

    if (m_networkConfig->getIP4enabled())
    {
        // Create DiscoverySocket
        m_ipv4DiscoverySocket = Poco::Net::MulticastSocket(Poco::Net::IPAddress::Family::IPv4);

        // Add only interfaces bound to the SDCInstance
        if (m_networkConfig->isBound()) {
            // Bind DiscoverySocket
            auto t_ipv4BindingAddress = Poco::Net::SocketAddress(Poco::Net::IPAddress::Family::IPv4, m_ipv4MulticastAddress.port());
            m_ipv4DiscoverySocket.bind(t_ipv4BindingAddress, m_SO_REUSEADDR_FLAG, m_SO_REUSEPORT_FLAG);
            // Add all interfaces
            for (auto t_interface : m_networkConfig->getNetworkInterfaces()) {
                try
                {
                    // Interface - Join group: Note: Fails if we enumerate a bridge that is already connected
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
        else {
            // Bind DiscoverySocket
            auto t_ipv4BindingAddress = Poco::Net::SocketAddress(Poco::Net::IPAddress(Poco::Net::IPAddress::Family::IPv4), m_ipv4MulticastAddress.port());
            m_ipv4DiscoverySocket.bind(t_ipv4BindingAddress, m_SO_REUSEADDR_FLAG, m_SO_REUSEPORT_FLAG);
            // Add all interfaces
            for (const auto & nextIf : Poco::Net::NetworkInterface::list()) {
                if (nextIf.supportsIPv4() && nextIf.address().isUnicast() && !nextIf.firstAddress(Poco::Net::IPAddress::Family::IPv4).isLoopback()) {
                    try
                    {
                        // Interface - Join group: Note: Fails if we enumerate a bridge that is already connected
                        m_ipv4DiscoverySocket.joinGroup(m_ipv4MulticastAddress.host(), nextIf);
                        // DatagramSocket
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
        // TTL
        m_ipv4DiscoverySocket.setTimeToLive(UPD_MULTICAST_TIMETOLIVE);
        // Add Ipv4 Socket EventHandler
        m_reactor.addEventHandler(m_ipv4DiscoverySocket, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onMulticastSocketReadable));
	}
    if (m_networkConfig->getIP6enabled())
    {
        // Create DiscoverySocket
        m_ipv6DiscoverySocket = Poco::Net::MulticastSocket(Poco::Net::IPAddress::Family::IPv6);

        // Add only interfaces bound to the SDCInstance
        if (m_networkConfig->isBound()) {
            // Bind DiscoverySocket
            auto t_ipv6BindingAddress = Poco::Net::SocketAddress (Poco::Net::IPAddress::Family::IPv6, m_ipv6MulticastAddress.port());
            m_ipv6DiscoverySocket.bind(t_ipv6BindingAddress, m_SO_REUSEADDR_FLAG, m_SO_REUSEPORT_FLAG);
            for (auto t_interface : m_networkConfig->getNetworkInterfaces()) {
                try {
                    // Interface - Join group: Note: Fails if we enumerate a bridge that is already connected
                    m_ipv6DiscoverySocket.joinGroup(m_ipv6MulticastAddress.host(), t_interface->m_if);
                    // DatagramSocket
                    Poco::Net::DatagramSocket t_datagramSocket(Poco::Net::SocketAddress(t_interface->m_IPv6, m_ipv6DatagrammSocketPort), t_interface->SO_REUSEADDR_FLAG);
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
        else {
            // Bind DiscoverySocket
            auto t_ipv6BindingAddress = Poco::Net::SocketAddress (Poco::Net::IPAddress(Poco::Net::IPAddress::Family::IPv6), m_ipv6MulticastAddress.port());
            m_ipv6DiscoverySocket.bind(t_ipv6BindingAddress, m_SO_REUSEADDR_FLAG, m_SO_REUSEPORT_FLAG);
            // Add all interfaces
            for (const auto & nextIf : Poco::Net::NetworkInterface::list()) {
                if (nextIf.supportsIPv6() && nextIf.address().isUnicast() && !nextIf.firstAddress(Poco::Net::IPAddress::Family::IPv6).isLoopback()) {
                    try {
                        // Interface - Join group: Note: Fails if we enumerate a bridge that is already connected
                        m_ipv6DiscoverySocket.joinGroup(m_ipv6MulticastAddress.host(), nextIf);
                        // DatagramSocket
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
        // TTL
        m_ipv6DiscoverySocket.setTimeToLive(UPD_MULTICAST_TIMETOLIVE);
        // Add Ipv6 Socket EventHandler
        m_reactor.addEventHandler(m_ipv6DiscoverySocket, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onMulticastSocketReadable));
    }

    // Start the Thread with the SocketReactor
	m_reactorThread.start(m_reactor);
}

DPWSDiscoveryClientSocketImpl::~DPWSDiscoveryClientSocketImpl() {
	m_reactor.removeEventHandler(m_ipv4DiscoverySocket, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onMulticastSocketReadable));
	m_reactor.removeEventHandler(m_ipv6DiscoverySocket, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onMulticastSocketReadable));

    for (auto t_interface : m_networkConfig->getNetworkInterfaces()) {
        try
        {
            if (m_networkConfig->getIP4enabled()) { m_ipv4DiscoverySocket.leaveGroup(m_ipv4MulticastAddress.host(), t_interface->m_if); }
            if (m_networkConfig->getIP6enabled()) { m_ipv6DiscoverySocket.leaveGroup(m_ipv6MulticastAddress.host(), t_interface->m_if); }
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
}

void DPWSDiscoveryClientSocketImpl::sendProbe(const ProbeType& filter) {
	const MESSAGEMODEL::Envelope message(buildProbeMessage(filter));
	if (message.Header().MessageID().present()) {
		m_messagingContext.registerMessageId(message.Header().MessageID().get());
	}
	for (auto & socketQueue : m_socketSendMessageQueue) {
		socketQueue.second.enqueueNotification(new SendMulticastMessage(serializeMessage(message)));
		m_reactor.addEventHandler(socketQueue.first, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::WritableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onDatagrammSocketWritable));
	}
}

void DPWSDiscoveryClientSocketImpl::sendResolve(const ResolveType& filter) {
	const MESSAGEMODEL::Envelope message(buildResolveMessage(filter));
	if (message.Header().MessageID().present()) {
		m_messagingContext.registerMessageId(message.Header().MessageID().get());
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

    // Only read if this belongs to this Config! - Peek first
    Poco::Net::SocketAddress t_sender;
    Poco::Buffer<char> t_peekBuf(1);
    socket.receiveFrom(t_peekBuf.begin(), 1, t_sender, MSG_PEEK);
    if (m_networkConfig->isBound() && !m_networkConfig->belongsTo(t_sender.host())) {
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
	if (! m_messagingContext.registerMessageId(message->Header().MessageID().get())) {
        log_debug([&] { return "DPWSDiscoveryClientSocketImpl::onMulticastSocketReadable. registerMessageId failed!"; });
		return;
	}
	if (! message->Header().AppSequence().present()) {
		return;
	}
	if (! m_messagingContext.registerAppSequence(message->Header().AppSequence().get())) {
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

	Poco::Buffer<char> buf(available);
	Poco::Net::SocketAddress remoteAddr;
	const int received(socket.receiveFrom(buf.begin(), available, remoteAddr, 0));
	Helper::BufferAdapter adapter(buf, received);
	std::unique_ptr<MESSAGEMODEL::Envelope> message(parseMessage(adapter));

	if (message == nullptr) {
		return;
	}
	if (message->Header().MessageID().present()) {
		if (!m_messagingContext.registerMessageId(message->Header().MessageID().get())) {
            log_debug([&] { return "DPWSDiscoveryClientSocketImpl::onDatagrammSocketReadable. registerMessageId failed!"; });
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
