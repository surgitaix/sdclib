/*
 * DPWSHostSocketImpl.cpp
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 26.07.2019, baumeister
 */

#include <chrono>
#include <iostream>

#include <Poco/Buffer.h>

#include "NormalizedMessageModel.hxx"

#include "OSELib/SDC/SDCConstants.h"
#include "OSELib/DPWS/DPWS11Constants.h"
#include "OSELib/DPWS/DPWSCommon.h"
#include "OSELib/DPWS/DPWSHostSocketImpl.h"
#include "OSELib/DPWS/MessageAdapter.h"
#include "OSELib/Helper/BufferAdapter.h"
#include "SDCLib/Config/NetworkConfig.h"
#include "SDCLib/SDCInstance.h"

namespace OSELib {
namespace DPWS {
namespace Impl {

const MESSAGEMODEL::Envelope buildByeMessage(const ByeType & notification) {
	MESSAGEMODEL::Envelope::HeaderType header;
	{
		header.Action(byeUri);
		header.To(discoveryUri);
		header.MessageID(xml_schema::Uri(SDCLib::SDCInstance::calcMSGID()));
	}
	MESSAGEMODEL::Envelope::BodyType body;
	{
		body.Bye(notification);
	}
	return MESSAGEMODEL::Envelope(header, body);
}

const MESSAGEMODEL::Envelope buildHelloMessage(const HelloType & notification) {
	MESSAGEMODEL::Envelope::HeaderType header;
	{
		header.Action(helloUri);
		header.To(discoveryUri);
		header.MessageID(xml_schema::Uri(SDCLib::SDCInstance::calcMSGID()));
	}
	MESSAGEMODEL::Envelope::BodyType body;
	{
		body.Hello(notification);
	}

	return MESSAGEMODEL::Envelope(header, body);
}

const MESSAGEMODEL::Envelope buildStreamMessage(const MDM::WaveformStream  & notification, const AddressType epr) {
	MESSAGEMODEL::Envelope::HeaderType header;
	{
		header.Action(xml_schema::Uri(SDC::EVENT_ACTION_CDM_WAVEFORM_STREAM_REPORT));
		header.MessageID(xml_schema::Uri(SDCLib::SDCInstance::calcMSGID()));
		header.From(epr);
	}
	MESSAGEMODEL::Envelope::BodyType body;
	{
		body.WaveformStream(notification);
	}

	return MESSAGEMODEL::Envelope(header,body);

}





const MESSAGEMODEL::Envelope buildProbeMatchMessage(const std::vector<ProbeMatchType> & notifications, const MESSAGEMODEL::Envelope & request) {
	MESSAGEMODEL::Envelope::HeaderType header;
	{
		header.Action(probeMatchesUri);
		if (request.Header().ReplyTo().present()) {
			header.To(request.Header().ReplyTo().get().Address());
		} else {
			header.To(addressingAnonymousUri);
		}
		if (request.Header().MessageID().present()) {
			header.RelatesTo(request.Header().MessageID().get());
		}
		header.MessageID(xml_schema::Uri(SDCLib::SDCInstance::calcMSGID()));
	}
	MESSAGEMODEL::Envelope::BodyType body;
	{
		MESSAGEMODEL::Envelope::BodyType::ProbeMatchesType probeMatches;
		for (const auto & match: notifications) {
			probeMatches.ProbeMatch().push_back(match);
		}
		body.ProbeMatches(probeMatches);
	}

	return MESSAGEMODEL::Envelope(header, body);
}

const MESSAGEMODEL::Envelope buildResolveMatchMessage(const ResolveMatchType & notification, const MESSAGEMODEL::Envelope & request) {
	MESSAGEMODEL::Envelope::HeaderType header;
	{
		header.Action(resolveMatchesUri);
		if (request.Header().ReplyTo().present()) {
			header.To(request.Header().ReplyTo().get().Address());
		} else {
			header.To(addressingAnonymousUri);
		}
		if (request.Header().MessageID().present()) {
			header.RelatesTo(request.Header().MessageID().get());
		}
		header.MessageID(xml_schema::Uri(SDCLib::SDCInstance::calcMSGID()));
	}
	MESSAGEMODEL::Envelope::BodyType body;
	{
		MESSAGEMODEL::Envelope::BodyType::ResolveMatchesType resolveMatches;
		resolveMatches.ResolveMatch(notification);
		body.ResolveMatches(resolveMatches);
	}

	return MESSAGEMODEL::Envelope(header, body);
}

struct DPWSHostSocketImpl::SendMulticastMessage : public Poco::Notification {
	SendMulticastMessage(const std::string & message, Poco::Net::SocketAddress ipv4MulticastAdress, Poco::Net::SocketAddress ipv6MulticastAdress) :
		content(message), ipv4MulticastAddress(ipv4MulticastAdress), ipv6MulticastAddress(ipv6MulticastAdress) {}

	const std::string content;
	Poco::Net::SocketAddress ipv4MulticastAddress;
	Poco::Net::SocketAddress ipv6MulticastAddress;
};

struct DPWSHostSocketImpl::SendUnicastMessage : public Poco::Notification {
	SendUnicastMessage(const MESSAGEMODEL::Envelope & message, const Poco::Net::SocketAddress & address) :
		content(message), address(address) {}
	const MESSAGEMODEL::Envelope content;
	const Poco::Net::SocketAddress address;
};

DPWSHostSocketImpl::DPWSHostSocketImpl(
        SDCLib::Config::NetworkConfig_shared_ptr p_config,
		ProbeNotificationDispatcher & probeDispatcher,
		ResolveNotificationDispatcher & resolveDispatcher):
	WithLogger(Log::DISCOVERY),
	m_networkConfig(p_config),
	probeDispatcher(probeDispatcher),
	resolveDispatcher(resolveDispatcher),
    m_ipv4DiscoveryMulticastAddress(Poco::Net::SocketAddress(p_config->_getMulticastIPv4(), p_config->_getMulticastPortv4())),
    m_ipv6DiscoveryMulticastAddress(Poco::Net::SocketAddress(p_config->_getMulticastIPv6(), p_config->_getMulticastPortv6())),
    m_ipv4StreamMulticastAddress(Poco::Net::SocketAddress(p_config->_getStreamingIPv4(), p_config->_getStreamingPortv4())),
    m_ipv6StreamMulticastAddress(Poco::Net::SocketAddress(p_config->_getStreamingIPv6(), p_config->_getStreamingPortv6())),
	generator(std::chrono::system_clock::now().time_since_epoch().count()),
	distribution(0, OSELib::APP_MAX_DELAY)
{
    if (m_networkConfig->getIP4enabled())
    {
        // Create ListeningSocket
        m_ipv4MulticastListeningSocket = Poco::Net::MulticastSocket(Poco::Net::IPAddress::Family::IPv4);

        // Add only interfaces bound to this Config
        if (m_networkConfig->isBound()) {
            // Bind ListeningSocket
            auto t_ipv4BindingAddress = m_ipv4DiscoveryMulticastAddress;
            m_ipv4MulticastListeningSocket.bind(t_ipv4BindingAddress, m_SO_REUSEADDR_FLAG, m_SO_REUSEPORT_FLAG);
            for (auto t_interface : m_networkConfig->getNetworkInterfaces()) {
                try
                {
                    // Interface - Join group: Note: Fails if we enumerate a bridge that is already connected
                    m_ipv4MulticastListeningSocket.joinGroup(m_ipv4DiscoveryMulticastAddress.host(), t_interface->m_if);
                    // DatagramSocket
                    Poco::Net::DatagramSocket t_datagramSocket(Poco::Net::SocketAddress(t_interface->m_IPv4, m_ipv4DiscoveryMulticastAddress.port()), t_interface->SO_REUSEADDR_FLAG);
                    t_datagramSocket.setReusePort(t_interface->SO_REUSEPORT_FLAG);
                    t_datagramSocket.setBlocking(false);
                    // adds datagramSocket to the queue with a clear entry
                    socketSendMessageQueue[t_datagramSocket].clear();
                }
                catch (...) {
                    log_error([&] { return "Something went wrong in binding to : " + t_interface->m_name; });
                    continue;
                }
            }
        }
        else {
            // Bind ListeningSocket
            auto t_ipv4BindingAddress = Poco::Net::SocketAddress(Poco::Net::IPAddress::Family::IPv4, m_ipv4DiscoveryMulticastAddress.port());
            m_ipv4MulticastListeningSocket.bind(t_ipv4BindingAddress, m_SO_REUSEADDR_FLAG, m_SO_REUSEPORT_FLAG);
            // Add all interfaces
            for (const auto & nextIf : Poco::Net::NetworkInterface::list()) {
                if (nextIf.supportsIPv4() && nextIf.address().isUnicast() && !nextIf.firstAddress(Poco::Net::IPAddress::Family::IPv4).isLoopback()) {
                    try
                    {
                        // Interface - Join group: Note: Fails if we enumerate a bridge that is already connected
                        m_ipv4MulticastListeningSocket.joinGroup(m_ipv4DiscoveryMulticastAddress.host(), nextIf);
                        // DatagramSocket
                        Poco::Net::DatagramSocket t_datagramSocket(Poco::Net::SocketAddress(nextIf.firstAddress(Poco::Net::IPAddress::Family::IPv4), m_ipv4DiscoveryMulticastAddress.port()), m_SO_REUSEADDR_FLAG);
                        t_datagramSocket.setReusePort(m_SO_REUSEPORT_FLAG);
                        t_datagramSocket.setBlocking(false);
                        // adds datagramSocket to the queue with a clear entry
                        socketSendMessageQueue[t_datagramSocket].clear();
                    }
                    catch (...) {
                        log_error([&] { return "Something went wrong in binding to : " + nextIf.adapterName(); });
                        continue;
                    }
                }
            }
        }
        // Nonblocking
        m_ipv4MulticastListeningSocket.setBlocking(false);
        // Add Ipv4 Socket EventHandler
        reactor.addEventHandler(m_ipv4MulticastListeningSocket, Poco::Observer<DPWSHostSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSHostSocketImpl::onMulticastSocketReadable));
        reactor.addEventHandler(m_ipv4MulticastListeningSocket, Poco::Observer<DPWSHostSocketImpl, Poco::Net::TimeoutNotification>(*this, &DPWSHostSocketImpl::onTimeOut));
    }
    if (m_networkConfig->getIP6enabled())
    {
        // Create ListeningSocket
        m_ipv6MulticastListeningSocket = Poco::Net::MulticastSocket(Poco::Net::IPAddress::Family::IPv6);

        // Add only interfaces bound to this Config
        if (m_networkConfig->isBound()) {
            // Bind ListeningSocket
            auto t_ipv6BindingAddress = Poco::Net::SocketAddress(Poco::Net::IPAddress::Family::IPv6, m_ipv6DiscoveryMulticastAddress.port());
            m_ipv6MulticastListeningSocket.bind(t_ipv6BindingAddress, m_SO_REUSEADDR_FLAG, m_SO_REUSEPORT_FLAG);
            for (auto t_interface : m_networkConfig->getNetworkInterfaces()) {
                try
                {
                    // Interface - Join group: Note: Fails if we enumerate a bridge that is already connected
                    m_ipv6MulticastListeningSocket.joinGroup(m_ipv6DiscoveryMulticastAddress.host(), t_interface->m_if);
                    // DatagramSocket
                    Poco::Net::DatagramSocket t_datagramSocket(Poco::Net::SocketAddress(t_interface->m_IPv6, m_ipv6DiscoveryMulticastAddress.port()), t_interface->SO_REUSEADDR_FLAG);
                    t_datagramSocket.setReusePort(t_interface->SO_REUSEPORT_FLAG);
                    t_datagramSocket.setBlocking(false);
                    // adds t_datagramSocket to the queue with a clear entry
                    socketSendMessageQueue[t_datagramSocket].clear();
                }
                catch (...) {
                    // todo fixme. This loop fails, when a network interface has serveral network addresses, i.e. 2 IPv6 global scoped addresses
                    log_error([&] { return "Something went wrong in binding to : " + t_interface->m_name; });
                    continue;
                }
            }
        }
        else {
            // Bind ListeningSocket
            auto t_ipv6BindingAddress = Poco::Net::SocketAddress(Poco::Net::IPAddress(Poco::Net::IPAddress::Family::IPv6), m_ipv6DiscoveryMulticastAddress.port());
            m_ipv6MulticastListeningSocket.bind(t_ipv6BindingAddress, m_SO_REUSEADDR_FLAG, m_SO_REUSEPORT_FLAG);
            // Add all interfaces
            for (const auto & nextIf : Poco::Net::NetworkInterface::list()) {
                if (nextIf.supportsIPv6() && nextIf.address().isUnicast() && !nextIf.firstAddress(Poco::Net::IPAddress::Family::IPv6).isLoopback()) {
                    try {
                        // Interface - Join group: Note: Fails if we enumerate a bridge that is already connected
                        m_ipv6MulticastListeningSocket.joinGroup(m_ipv6DiscoveryMulticastAddress.host(), nextIf);
                        // DatagramSocket
                        Poco::Net::DatagramSocket t_datagramSocket(Poco::Net::SocketAddress(nextIf.firstAddress(Poco::Net::IPAddress::Family::IPv6), m_ipv6DiscoveryMulticastAddress.port()), m_SO_REUSEADDR_FLAG);
                        t_datagramSocket.setReusePort(m_SO_REUSEPORT_FLAG);
                        t_datagramSocket.setBlocking(false);
                        socketSendMessageQueue[t_datagramSocket].clear();
                    } catch (...) {
                        // todo fixme. This loop fails, when a network interface has several network addresses, i.e. 2 IPv6 global scoped addresses
                        log_error([&] { return "Another thing went wrong"; });
                    }
                }
            }
        }
        // Nonblocking
        m_ipv6MulticastListeningSocket.setBlocking(false);
        // Add Ipv6 Socket EventHandler
        reactor.addEventHandler(m_ipv6MulticastListeningSocket, Poco::Observer<DPWSHostSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSHostSocketImpl::onMulticastSocketReadable));
        reactor.addEventHandler(m_ipv6MulticastListeningSocket, Poco::Observer<DPWSHostSocketImpl, Poco::Net::TimeoutNotification>(*this, &DPWSHostSocketImpl::onTimeOut));
    }

    // Start the Thread with the SocketReactor
	reactorThread.start(reactor);
}

DPWSHostSocketImpl::~DPWSHostSocketImpl() {
    reactor.removeEventHandler(m_ipv4MulticastListeningSocket, Poco::Observer<DPWSHostSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSHostSocketImpl::onMulticastSocketReadable));
    reactor.removeEventHandler(m_ipv6MulticastListeningSocket, Poco::Observer<DPWSHostSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSHostSocketImpl::onMulticastSocketReadable));

    for (auto t_interface : m_networkConfig->getNetworkInterfaces()) {
        try
        {
            if (m_networkConfig->getIP4enabled()) { m_ipv4MulticastListeningSocket.leaveGroup(m_ipv4DiscoveryMulticastAddress.host(), t_interface->m_if); }
            if (m_networkConfig->getIP6enabled()) { m_ipv6MulticastListeningSocket.leaveGroup(m_ipv6DiscoveryMulticastAddress.host(), t_interface->m_if); }
        }
        catch (...) {
            // todo fixme. This loop fails, when a network interface has serveral network addresses, i.e. 2 IPv6 global scoped addresses
            log_error([&] { return "Some thing went wrong leaving : " + t_interface->m_name; });
            continue;
        }
    }

	for (auto & messagingSocketMapping : socketSendMessageQueue) {
		reactor.removeEventHandler(messagingSocketMapping.first, Poco::Observer<DPWSHostSocketImpl, Poco::Net::WritableNotification>(*this, &DPWSHostSocketImpl::onDatagrammSocketWritable));
		reactor.removeEventHandler(messagingSocketMapping.first, Poco::Observer<DPWSHostSocketImpl, Poco::Net::TimeoutNotification>(*this, &DPWSHostSocketImpl::onTimeOut));
	}

	reactor.stop();
	reactorThread.join();
}

void DPWSHostSocketImpl::sendBye(const ByeType & bye) {
	MESSAGEMODEL::Envelope message(buildByeMessage(bye));
	MESSAGEMODEL::Envelope::HeaderType::AppSequenceType appSequence(context.getInstanceId(), context.getNextMessageCounter());
	message.Header().AppSequence(appSequence);
	if (message.Header().MessageID().present()) {
		context.registerMessageId(message.Header().MessageID().get());
	}
	for (auto & socketQueue : socketSendMessageQueue) {
        socketQueue.second.enqueueNotification(new SendMulticastMessage(serializeMessage(message), m_ipv4DiscoveryMulticastAddress, m_ipv6DiscoveryMulticastAddress));
		reactor.addEventHandler(socketQueue.first, Poco::Observer<DPWSHostSocketImpl, Poco::Net::WritableNotification>(*this, &DPWSHostSocketImpl::onDatagrammSocketWritable));
	}
}


void DPWSHostSocketImpl::sendStream(const MDM::WaveformStream & stream, const AddressType epr) {
	MESSAGEMODEL::Envelope message(buildStreamMessage(stream, epr));
	MESSAGEMODEL::Envelope::HeaderType::AppSequenceType appSequence(context.getInstanceId(), context.getNextMessageCounter());
	message.Header().AppSequence(appSequence);
	if (message.Header().MessageID().present()) {
		context.registerMessageId(message.Header().MessageID().get());
	}
	for (auto & socketQueue : socketSendMessageQueue) {
        socketQueue.second.enqueueNotification(new SendMulticastMessage(serializeMessage(message), m_ipv4StreamMulticastAddress, m_ipv6StreamMulticastAddress));
		reactor.addEventHandler(socketQueue.first, Poco::Observer<DPWSHostSocketImpl, Poco::Net::WritableNotification>(*this, &DPWSHostSocketImpl::onDatagrammSocketWritable));
	}
}


void DPWSHostSocketImpl::sendHello(const HelloType & hello) {
	context.resetInstanceId();
	MESSAGEMODEL::Envelope message(buildHelloMessage(hello));
	MESSAGEMODEL::Envelope::HeaderType::AppSequenceType appSequence(context.getInstanceId(), context.getNextMessageCounter());
	message.Header().AppSequence(appSequence);
	if (message.Header().MessageID().present()) {
		context.registerMessageId(message.Header().MessageID().get());
	}
	for (auto & socketQueue : socketSendMessageQueue) {
        socketQueue.second.enqueueNotification(new SendMulticastMessage(serializeMessage(message), m_ipv4DiscoveryMulticastAddress, m_ipv6DiscoveryMulticastAddress));
		reactor.addEventHandler(socketQueue.first, Poco::Observer<DPWSHostSocketImpl, Poco::Net::WritableNotification>(*this, &DPWSHostSocketImpl::onDatagrammSocketWritable));
	}
}

void DPWSHostSocketImpl::onMulticastSocketReadable(Poco::Net::ReadableNotification * notification) {
	const Poco::AutoPtr<Poco::Net::ReadableNotification> pNf(notification);
	Poco::Net::MulticastSocket socket(pNf->socket());
	const int available(socket.available());
	if (available == 0) {
		return;
	}

	Poco::Buffer<char> buf(available);
	Poco::Net::SocketAddress remoteAddr;
	const int received(socket.receiveFrom(buf.begin(), available, remoteAddr, 0));
	Helper::BufferAdapter adapter(buf, received);
	std::unique_ptr<MESSAGEMODEL::Envelope> requestMessage(parseMessage(adapter));

	if (requestMessage == nullptr) {
		return;
	}
	if (requestMessage->Header().MessageID().present()) {
		if(requestMessage->Header().MessageID().get().empty()) {
			log_debug([&] { return "DPWSHostSocketImpl::onMulticastSocketReadable. <MessageID> EMPTY!"; });
			return;
		}
		if (!context.registerMessageId(requestMessage->Header().MessageID().get())) {
			log_debug([&] { return "DPWSHostSocketImpl::onMulticastSocketReadable. registerMessageId failed!"; });
			return;
		}
	}
	if (requestMessage->Body().Probe().present()) {
		const WS::DISCOVERY::ProbeType & probe(requestMessage->Body().Probe().get());
		std::vector<ProbeMatchType> result(probeDispatcher.dispatch(probe));
		if (result.empty()) {
			return;
		}
		const MESSAGEMODEL::Envelope responseMessage(buildProbeMatchMessage(result, *requestMessage));
		delayedMessages.enqueueNotification(new SendUnicastMessage(responseMessage, remoteAddr), createDelay());
	} else if (requestMessage->Body().Resolve().present()) {
		const WS::DISCOVERY::ResolveType & resolve(requestMessage->Body().Resolve().get());
		std::unique_ptr<ResolveMatchType> result(resolveDispatcher.dispatch(resolve));
		if (result == nullptr) {
			return;
		}
		const MESSAGEMODEL::Envelope responseMessage(buildResolveMatchMessage(*result, *requestMessage));
		delayedMessages.enqueueNotification(new SendUnicastMessage(responseMessage, remoteAddr), createDelay());
	}
	processDelayedMessages();
}

void DPWSHostSocketImpl::onDatagrammSocketWritable(Poco::Net::WritableNotification * notification)
{
	processDelayedMessages();

    std::lock_guard<std::mutex> t_lock(m_mutex);

    const Poco::AutoPtr<Poco::Net::WritableNotification> pNf(notification);
    // By Sebastian TTL
    // Poco::Net::DatagramSocket socket(pNf->socket());
    Poco::Net::MulticastSocket socket(pNf->socket());
    socket.setTimeToLive(OSELib::UPD_MULTICAST_TIMETOLIVE);

	const Poco::AutoPtr<Poco::Notification> rawMessage(socketSendMessageQueue[socket].dequeueNotification());
	if (rawMessage.isNull()) {
		notification->source().removeEventHandler(socket, Poco::Observer<DPWSHostSocketImpl, Poco::Net::WritableNotification>(*this, &DPWSHostSocketImpl::onDatagrammSocketWritable));
		return;
	}

	{ // send unicast
		const Poco::AutoPtr<SendUnicastMessage> message(rawMessage.cast<SendUnicastMessage>());
		if (! message.isNull()) {
			MESSAGEMODEL::Envelope messageEnvelope(message->content);
			MESSAGEMODEL::Envelope::HeaderType::AppSequenceType appSequence(context.getInstanceId(), context.getNextMessageCounter());
			messageEnvelope.Header().AppSequence(appSequence);
			const std::string content(serializeMessage(messageEnvelope));
            socket.sendTo(content.c_str(), content.size(), message->address, 0);
		}
	}
	{ // send multicast
		const Poco::AutoPtr<SendMulticastMessage> message(rawMessage.cast<SendMulticastMessage>());
		if (! message.isNull()) {

			Poco::Net::SocketAddress multicastAddress(message->ipv4MulticastAddress);
			if (socket.address().family() == Poco::Net::IPAddress::Family::IPv6) {
				multicastAddress = message->ipv6MulticastAddress;
			}
            socket.sendTo(message->content.c_str(), message->content.size(), multicastAddress, 0);
		}
	}
}

void DPWSHostSocketImpl::onTimeOut(Poco::Net::TimeoutNotification * notification) {
	const Poco::AutoPtr<Poco::Net::TimeoutNotification> pNf(notification);
	processDelayedMessages();
}

Poco::Timestamp DPWSHostSocketImpl::createDelay()
{
	return Poco::Timestamp() + Poco::Timespan(0, 0, 0, 0, distribution(generator)*1000); // Microseconds!
}

void DPWSHostSocketImpl::processDelayedMessages()
{

    std::lock_guard<std::mutex> t_lock(m_mutex);

    // FIXME!
	if (delayedMessages.empty()) {
		reactor.setTimeout(Poco::Timespan(0, 0, 0, 0, 250000));
		return;
	} else {
		reactor.setTimeout(Poco::Timespan(0, 0, 0, 0, 10000));
	}

	Poco::AutoPtr<Poco::Notification> notification(delayedMessages.dequeueNotification());
	if (notification.isNull()) {
		return;
	}
	Poco::AutoPtr<SendUnicastMessage> unicastMessage(notification.cast<SendUnicastMessage>());
	if (unicastMessage.isNull()) {
		return;
	}
	for (auto & socketQueue : socketSendMessageQueue) {
		if (socketQueue.first.address().family() == unicastMessage->address.family()) {
			socketQueue.second.enqueueNotification(new SendUnicastMessage(std::move(unicastMessage->content), unicastMessage->address));
			reactor.addEventHandler(socketQueue.first, Poco::Observer<DPWSHostSocketImpl, Poco::Net::WritableNotification>(*this, &DPWSHostSocketImpl::onDatagrammSocketWritable));
		}
	}
}

} /* namespace Impl */
} /* namespace DPWS */
} /* namespace OSELib */
