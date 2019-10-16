/*
 * DPWSHostSocketImpl.cpp
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 20.08.2019, baumeister
 */
#include "OSELib/DPWS/DPWSHostSocketImpl.h"
#include "OSELib/SDC/SDCConstants.h"
#include "OSELib/DPWS/DPWS11Constants.h"
#include "OSELib/DPWS/DPWSCommon.h"
#include "OSELib/DPWS/MessageAdapter.h"
#include "OSELib/Helper/BufferAdapter.h"
#include "SDCLib/Config/NetworkConfig.h"
#include "SDCLib/SDCInstance.h"

#include "DataModel/NormalizedMessageModel.hxx"

#include <chrono>

#include <Poco/Buffer.h>


namespace OSELib {
namespace DPWS {
namespace Impl {

const MESSAGEMODEL::Envelope buildByeMessage(const ByeType & p_notification)
{
	MESSAGEMODEL::Envelope::HeaderType t_header;
	{
		t_header.Action(byeUri);
		t_header.To(discoveryUri);
		t_header.MessageID(xml_schema::Uri(SDCLib::SDCInstance::calcMSGID()));
	}
	MESSAGEMODEL::Envelope::BodyType t_body;
	{
		t_body.Bye(p_notification);
	}
	return MESSAGEMODEL::Envelope(t_header, t_body);
}

const MESSAGEMODEL::Envelope buildHelloMessage(const HelloType & p_notification)
{
	MESSAGEMODEL::Envelope::HeaderType t_header;
	{
		t_header.Action(helloUri);
		t_header.To(discoveryUri);
		t_header.MessageID(xml_schema::Uri(SDCLib::SDCInstance::calcMSGID()));
	}
	MESSAGEMODEL::Envelope::BodyType t_body;
	{
		t_body.Hello(p_notification);
	}

	return MESSAGEMODEL::Envelope(t_header, t_body);
}

const MESSAGEMODEL::Envelope buildStreamMessage(const MDM::WaveformStream  & p_notification, const AddressType p_epr)
{
	MESSAGEMODEL::Envelope::HeaderType t_header;
	{
		t_header.Action(xml_schema::Uri(SDC::ACT_WAVEFORM_STREAM_REPORT));
		t_header.MessageID(xml_schema::Uri(SDCLib::SDCInstance::calcMSGID()));
		t_header.From(p_epr);
	}
	MESSAGEMODEL::Envelope::BodyType t_body;
	{
		t_body.WaveformStream(p_notification);
	}
	return MESSAGEMODEL::Envelope(t_header,t_body);
}


const MESSAGEMODEL::Envelope buildProbeMatchMessage(const std::vector<ProbeMatchType> & pl_notifications, const MESSAGEMODEL::Envelope & p_request)
{
	MESSAGEMODEL::Envelope::HeaderType t_header;
	{
		t_header.Action(probeMatchesUri);
		if (p_request.Header().ReplyTo().present()) {
			t_header.To(p_request.Header().ReplyTo().get().Address());
		} else {
			t_header.To(addressingAnonymousUri);
		}
		if (p_request.Header().MessageID().present()) {
			t_header.RelatesTo(p_request.Header().MessageID().get());
		}
		t_header.MessageID(xml_schema::Uri(SDCLib::SDCInstance::calcMSGID()));
	}
	MESSAGEMODEL::Envelope::BodyType t_body;
	{
		MESSAGEMODEL::Envelope::BodyType::ProbeMatchesType t_probeMatches;
		for (const auto & t_match: pl_notifications) {
			t_probeMatches.ProbeMatch().push_back(t_match);
		}
		t_body.ProbeMatches(t_probeMatches);
	}

	return MESSAGEMODEL::Envelope(t_header, t_body);
}

const MESSAGEMODEL::Envelope buildResolveMatchMessage(const ResolveMatchType & p_notification, const MESSAGEMODEL::Envelope & p_request) {
	MESSAGEMODEL::Envelope::HeaderType t_header;
	{
		t_header.Action(resolveMatchesUri);
		if (p_request.Header().ReplyTo().present()) {
			t_header.To(p_request.Header().ReplyTo().get().Address());
		} else {
			t_header.To(addressingAnonymousUri);
		}
		if (p_request.Header().MessageID().present()) {
			t_header.RelatesTo(p_request.Header().MessageID().get());
		}
		t_header.MessageID(xml_schema::Uri(SDCLib::SDCInstance::calcMSGID()));
	}
	MESSAGEMODEL::Envelope::BodyType t_body;
	{
		MESSAGEMODEL::Envelope::BodyType::ResolveMatchesType resolveMatches;
		resolveMatches.ResolveMatch(p_notification);
		t_body.ResolveMatches(resolveMatches);
	}

	return MESSAGEMODEL::Envelope(t_header, t_body);
}

struct DPWSHostSocketImpl::SendMulticastMessage : public Poco::Notification
{
	const std::string m_content;
	Poco::Net::SocketAddress m_ipv4MulticastAddress;
	Poco::Net::SocketAddress m_ipv6MulticastAddress;

	SendMulticastMessage(const std::string & p_message, Poco::Net::SocketAddress p_ipv4MulticastAdress, Poco::Net::SocketAddress p_ipv6MulticastAdress)
	: m_content(p_message), m_ipv4MulticastAddress(p_ipv4MulticastAdress), m_ipv6MulticastAddress(p_ipv6MulticastAdress)
	{ }
};

struct DPWSHostSocketImpl::SendUnicastMessage : public Poco::Notification
{
	const MESSAGEMODEL::Envelope m_content;
	const Poco::Net::SocketAddress m_address;

	SendUnicastMessage(const MESSAGEMODEL::Envelope & p_message, const Poco::Net::SocketAddress & p_address)
	: m_content(p_message), m_address(p_address)
	{ }
};

DPWSHostSocketImpl::DPWSHostSocketImpl(SDCLib::Config::NetworkConfig_shared_ptr p_config,
		ProbeNotificationDispatcher & p_probeDispatcher,
		ResolveNotificationDispatcher & p_resolveDispatcher):
	OSELib::Helper::WithLogger(Log::DISCOVERY),
	m_networkConfig(p_config),
	m_probeDispatcher(p_probeDispatcher),
	m_resolveDispatcher(p_resolveDispatcher),
    m_ipv4DiscoveryMulticastAddress(Poco::Net::SocketAddress(p_config->_getMulticastIPv4(), p_config->_getMulticastPortv4())),
    m_ipv6DiscoveryMulticastAddress(Poco::Net::SocketAddress(p_config->_getMulticastIPv6(), p_config->_getMulticastPortv6())),
    m_ipv4StreamMulticastAddress(Poco::Net::SocketAddress(p_config->_getStreamingIPv4(), p_config->_getStreamingPortv4())),
    m_ipv6StreamMulticastAddress(Poco::Net::SocketAddress(p_config->_getStreamingIPv6(), p_config->_getStreamingPortv6())),
	m_generator(std::chrono::system_clock::now().time_since_epoch().count()),
	m_distribution(0, OSELib::APP_MAX_DELAY)
{
    if (m_networkConfig->getIP4enabled())
    {
        // Create ListeningSocket
        m_ipv4MulticastListeningSocket = Poco::Net::MulticastSocket(Poco::Net::IPAddress::Family::IPv4);

        // Add only interfaces bound to this Config
        if (m_networkConfig->isBound()) {
            // Bind ListeningSocket
            //auto t_ipv4BindingAddress = m_ipv4DiscoveryMulticastAddress;
			auto t_ipv4BindingAddress = Poco::Net::SocketAddress(Poco::Net::IPAddress::Family::IPv4, m_ipv4DiscoveryMulticastAddress.port());
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
                    ml_socketSendMessageQueue[t_datagramSocket].clear();
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
            for (const auto & t_nextIf : Poco::Net::NetworkInterface::list()) {
                if (t_nextIf.supportsIPv4() && t_nextIf.address().isUnicast() && !t_nextIf.firstAddress(Poco::Net::IPAddress::Family::IPv4).isLoopback()) {
                    try
                    {
                        // Interface - Join group: Note: Fails if we enumerate a bridge that is already connected
                        m_ipv4MulticastListeningSocket.joinGroup(m_ipv4DiscoveryMulticastAddress.host(), t_nextIf);
                        // DatagramSocket
                        Poco::Net::DatagramSocket t_datagramSocket(Poco::Net::SocketAddress(t_nextIf.firstAddress(Poco::Net::IPAddress::Family::IPv4), m_ipv4DiscoveryMulticastAddress.port()), m_SO_REUSEADDR_FLAG);
                        t_datagramSocket.setReusePort(m_SO_REUSEPORT_FLAG);
                        t_datagramSocket.setBlocking(false);
                        // adds datagramSocket to the queue with a clear entry
                        ml_socketSendMessageQueue[t_datagramSocket].clear();
                    }
                    catch (...) {
                        log_error([&] { return "Something went wrong in binding to : " + t_nextIf.adapterName(); });
                        continue;
                    }
                }
            }
        }
        // Nonblocking
        m_ipv4MulticastListeningSocket.setBlocking(false);
        // Add Ipv4 Socket EventHandler
        m_reactor.addEventHandler(m_ipv4MulticastListeningSocket, Poco::Observer<DPWSHostSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSHostSocketImpl::onMulticastSocketReadable));
        m_reactor.addEventHandler(m_ipv4MulticastListeningSocket, Poco::Observer<DPWSHostSocketImpl, Poco::Net::TimeoutNotification>(*this, &DPWSHostSocketImpl::onTimeOut));
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
                    ml_socketSendMessageQueue[t_datagramSocket].clear();
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
            for (const auto & t_nextIf : Poco::Net::NetworkInterface::list()) {
                if (t_nextIf.supportsIPv6() && t_nextIf.address().isUnicast() && !t_nextIf.firstAddress(Poco::Net::IPAddress::Family::IPv6).isLoopback()) {
                    try {
                        // Interface - Join group: Note: Fails if we enumerate a bridge that is already connected
                        m_ipv6MulticastListeningSocket.joinGroup(m_ipv6DiscoveryMulticastAddress.host(), t_nextIf);
                        // DatagramSocket
                        Poco::Net::DatagramSocket t_datagramSocket(Poco::Net::SocketAddress(t_nextIf.firstAddress(Poco::Net::IPAddress::Family::IPv6), m_ipv6DiscoveryMulticastAddress.port()), m_SO_REUSEADDR_FLAG);
                        t_datagramSocket.setReusePort(m_SO_REUSEPORT_FLAG);
                        t_datagramSocket.setBlocking(false);
                        ml_socketSendMessageQueue[t_datagramSocket].clear();
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
        m_reactor.addEventHandler(m_ipv6MulticastListeningSocket, Poco::Observer<DPWSHostSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSHostSocketImpl::onMulticastSocketReadable));
        m_reactor.addEventHandler(m_ipv6MulticastListeningSocket, Poco::Observer<DPWSHostSocketImpl, Poco::Net::TimeoutNotification>(*this, &DPWSHostSocketImpl::onTimeOut));
    }

    // Start the Thread with the SocketReactor
    m_reactorThread.start(m_reactor);
}

DPWSHostSocketImpl::~DPWSHostSocketImpl()
{
	m_reactor.removeEventHandler(m_ipv4MulticastListeningSocket, Poco::Observer<DPWSHostSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSHostSocketImpl::onMulticastSocketReadable));
	m_reactor.removeEventHandler(m_ipv6MulticastListeningSocket, Poco::Observer<DPWSHostSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSHostSocketImpl::onMulticastSocketReadable));

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

	for (auto & t_messagingSocketMapping : ml_socketSendMessageQueue) {
		m_reactor.removeEventHandler(t_messagingSocketMapping.first, Poco::Observer<DPWSHostSocketImpl, Poco::Net::WritableNotification>(*this, &DPWSHostSocketImpl::onDatagrammSocketWritable));
		m_reactor.removeEventHandler(t_messagingSocketMapping.first, Poco::Observer<DPWSHostSocketImpl, Poco::Net::TimeoutNotification>(*this, &DPWSHostSocketImpl::onTimeOut));
	}

	m_reactor.stop();
	m_reactorThread.join();
}

void DPWSHostSocketImpl::sendBye(const ByeType & p_bye)
{
	MESSAGEMODEL::Envelope t_message(buildByeMessage(p_bye));
	MESSAGEMODEL::Envelope::HeaderType::AppSequenceType t_appSequence(m_context.getInstanceId(), m_context.getNextMessageCounter());
	t_message.Header().AppSequence(t_appSequence);
	if (t_message.Header().MessageID().present()) {
		m_context.registerMessageId(t_message.Header().MessageID().get());
	}
	for (auto & t_socketQueue : ml_socketSendMessageQueue) {
		t_socketQueue.second.enqueueNotification(new SendMulticastMessage(serializeMessage(t_message), m_ipv4DiscoveryMulticastAddress, m_ipv6DiscoveryMulticastAddress));
		m_reactor.addEventHandler(t_socketQueue.first, Poco::Observer<DPWSHostSocketImpl, Poco::Net::WritableNotification>(*this, &DPWSHostSocketImpl::onDatagrammSocketWritable));
	}
}


void DPWSHostSocketImpl::sendStream(const MDM::WaveformStream & p_stream, const AddressType p_epr)
{
	MESSAGEMODEL::Envelope t_message(buildStreamMessage(p_stream, p_epr));
	MESSAGEMODEL::Envelope::HeaderType::AppSequenceType t_appSequence(m_context.getInstanceId(), m_context.getNextMessageCounter());
	t_message.Header().AppSequence(t_appSequence);
	if (t_message.Header().MessageID().present()) {
		m_context.registerMessageId(t_message.Header().MessageID().get());
	}
	for (auto & t_socketQueue : ml_socketSendMessageQueue) {
		t_socketQueue.second.enqueueNotification(new SendMulticastMessage(serializeMessage(t_message), m_ipv4StreamMulticastAddress, m_ipv6StreamMulticastAddress));
		m_reactor.addEventHandler(t_socketQueue.first, Poco::Observer<DPWSHostSocketImpl, Poco::Net::WritableNotification>(*this, &DPWSHostSocketImpl::onDatagrammSocketWritable));
	}
}


void DPWSHostSocketImpl::sendHello(const HelloType & p_hello)
{
	m_context.resetInstanceId();
	MESSAGEMODEL::Envelope t_message(buildHelloMessage(p_hello));
	MESSAGEMODEL::Envelope::HeaderType::AppSequenceType t_appSequence(m_context.getInstanceId(), m_context.getNextMessageCounter());
	t_message.Header().AppSequence(t_appSequence);
	if (t_message.Header().MessageID().present()) {
		m_context.registerMessageId(t_message.Header().MessageID().get());
	}
	for (auto & t_socketQueue : ml_socketSendMessageQueue) {
		t_socketQueue.second.enqueueNotification(new SendMulticastMessage(serializeMessage(t_message), m_ipv4DiscoveryMulticastAddress, m_ipv6DiscoveryMulticastAddress));
		m_reactor.addEventHandler(t_socketQueue.first, Poco::Observer<DPWSHostSocketImpl, Poco::Net::WritableNotification>(*this, &DPWSHostSocketImpl::onDatagrammSocketWritable));
	}
}

void DPWSHostSocketImpl::onMulticastSocketReadable(Poco::Net::ReadableNotification * p_notification)
{
	const Poco::AutoPtr<Poco::Net::ReadableNotification> t_pNf(p_notification);
	Poco::Net::MulticastSocket t_socket(t_pNf->socket());
	const int t_available(t_socket.available());
	if (t_available == 0) {
		return;
	}

	Poco::Buffer<char> t_buf(t_available);
	Poco::Net::SocketAddress t_remoteAddr;
	const int t_received(t_socket.receiveFrom(t_buf.begin(), t_available, t_remoteAddr, 0));
	Helper::BufferAdapter t_adapter(t_buf, t_received);
	auto t_requestMessage(parseMessage(t_adapter));

	if (nullptr == t_requestMessage) {
		return;
	}
	if (t_requestMessage->Header().MessageID().present()) {
		if(t_requestMessage->Header().MessageID().get().empty()) {
			log_debug([] { return "DPWSHostSocketImpl::onMulticastSocketReadable. <MessageID> EMPTY!"; });
			return;
		}
		if (!m_context.registerMessageId(t_requestMessage->Header().MessageID().get())) {
			log_debug([] { return "DPWSHostSocketImpl::onMulticastSocketReadable. registerMessageId failed!"; });
			return;
		}
	}
	if (t_requestMessage->Body().Probe().present()) {
		const WS::DISCOVERY::ProbeType & t_probe(t_requestMessage->Body().Probe().get());
		auto tl_result(m_probeDispatcher.dispatch(t_probe));
		if (tl_result.empty()) {
			return;
		}
		const MESSAGEMODEL::Envelope t_responseMessage(buildProbeMatchMessage(tl_result, *t_requestMessage));
		m_delayedMessages.enqueueNotification(new SendUnicastMessage(t_responseMessage, t_remoteAddr), createDelay());
	} else if (t_requestMessage->Body().Resolve().present()) {
		const WS::DISCOVERY::ResolveType & t_resolve(t_requestMessage->Body().Resolve().get());
		auto t_result(m_resolveDispatcher.dispatch(t_resolve));
		if (nullptr == t_result) {
			return;
		}
		const MESSAGEMODEL::Envelope t_responseMessage(buildResolveMatchMessage(*t_result, *t_requestMessage));
		m_delayedMessages.enqueueNotification(new SendUnicastMessage(t_responseMessage, t_remoteAddr), createDelay());
	}
	processDelayedMessages();
}

void DPWSHostSocketImpl::onDatagrammSocketWritable(Poco::Net::WritableNotification * p_notification)
{
	processDelayedMessages();

    std::lock_guard<std::mutex> t_lock(m_mutex);

    const Poco::AutoPtr<Poco::Net::WritableNotification> t_pNf(p_notification);
    // By Sebastian TTL
    // Poco::Net::DatagramSocket socket(pNf->socket());
    Poco::Net::MulticastSocket t_socket(t_pNf->socket());
    t_socket.setTimeToLive(OSELib::UPD_MULTICAST_TIMETOLIVE);

	const Poco::AutoPtr<Poco::Notification> t_rawMessage(ml_socketSendMessageQueue[t_socket].dequeueNotification());
	if (t_rawMessage.isNull()) {
		p_notification->source().removeEventHandler(t_socket, Poco::Observer<DPWSHostSocketImpl, Poco::Net::WritableNotification>(*this, &DPWSHostSocketImpl::onDatagrammSocketWritable));
		return;
	}

	{ // send unicast
		const Poco::AutoPtr<SendUnicastMessage> t_message(t_rawMessage.cast<SendUnicastMessage>());
		if (! t_message.isNull()) {
			MESSAGEMODEL::Envelope t_messageEnvelope(t_message->m_content);
			MESSAGEMODEL::Envelope::HeaderType::AppSequenceType t_appSequence(m_context.getInstanceId(), m_context.getNextMessageCounter());
			t_messageEnvelope.Header().AppSequence(t_appSequence);
			const std::string t_content(serializeMessage(t_messageEnvelope));
			t_socket.sendTo(t_content.c_str(), t_content.size(), t_message->m_address, 0);
		}
	}
	{ // send multicast
		const Poco::AutoPtr<SendMulticastMessage> t_message(t_rawMessage.cast<SendMulticastMessage>());
		if (! t_message.isNull()) {
			Poco::Net::SocketAddress t_multicastAddress(t_message->m_ipv4MulticastAddress);
			if (Poco::Net::IPAddress::Family::IPv6 == t_socket.address().family()) {
				t_multicastAddress = t_message->m_ipv6MulticastAddress;
			}
			t_socket.sendTo(t_message->m_content.c_str(), t_message->m_content.size(), t_multicastAddress, 0);
		}
	}
}

void DPWSHostSocketImpl::onTimeOut(Poco::Net::TimeoutNotification * p_notification)
{
	const Poco::AutoPtr<Poco::Net::TimeoutNotification> t_pNf(p_notification); // TODO?
	processDelayedMessages();
}

Poco::Timestamp DPWSHostSocketImpl::createDelay()
{
	return Poco::Timestamp() + Poco::Timespan(0, 0, 0, 0, m_distribution(m_generator)*1000); // Microseconds!
}

void DPWSHostSocketImpl::processDelayedMessages()
{

    std::lock_guard<std::mutex> t_lock(m_mutex);

    // FIXME!
	if (m_delayedMessages.empty()) {
		m_reactor.setTimeout(Poco::Timespan(0, 0, 0, 0, 250000));
		return;
	} else {
		m_reactor.setTimeout(Poco::Timespan(0, 0, 0, 0, 10000));
	}

	Poco::AutoPtr<Poco::Notification> t_notification(m_delayedMessages.dequeueNotification());
	if (t_notification.isNull()) {
		return;
	}
	Poco::AutoPtr<SendUnicastMessage> t_unicastMessage(t_notification.cast<SendUnicastMessage>());
	if (t_unicastMessage.isNull()) {
		return;
	}
	for (auto & t_socketQueue : ml_socketSendMessageQueue) {
		if (t_socketQueue.first.address().family() == t_unicastMessage->m_address.family()) {
			t_socketQueue.second.enqueueNotification(new SendUnicastMessage(std::move(t_unicastMessage->m_content), t_unicastMessage->m_address));
			m_reactor.addEventHandler(t_socketQueue.first, Poco::Observer<DPWSHostSocketImpl, Poco::Net::WritableNotification>(*this, &DPWSHostSocketImpl::onDatagrammSocketWritable));
		}
	}
}

}
}
}
