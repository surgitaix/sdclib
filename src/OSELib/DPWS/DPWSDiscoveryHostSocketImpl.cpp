/*
 * DPWSDiscoveryHostSocketImpl.cpp
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#include <chrono>
#include <iostream>

#include "Poco/Buffer.h"
#include "Poco/UUIDGenerator.h"

#include "NormalizedMessageModel.hxx"

#include "OSELib/DPWS/DPWS11Constants.h"
#include "OSELib/DPWS/DPWSCommon.h"
#include "OSELib/DPWS/DPWSDiscoveryHostSocketImpl.h"
#include "OSELib/DPWS/MessageAdapter.h"
#include "OSELib/Helper/BufferAdapter.h"

namespace OSELib {
namespace DPWS {
namespace Impl {

const MESSAGEMODEL::Envelope buildByeMessage(const ByeType & notification) {
	MESSAGEMODEL::Envelope::HeaderType header;
	{
		header.Action(byeUri);
		header.To(discoveryUri);
		header.MessageID(xml_schema::Uri(Poco::UUIDGenerator().create().toString()));
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
		header.MessageID(xml_schema::Uri(Poco::UUIDGenerator().create().toString()));
	}
	MESSAGEMODEL::Envelope::BodyType body;
	{
		body.Hello(notification);
	}

	return MESSAGEMODEL::Envelope(header, body);
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
		header.MessageID(xml_schema::Uri(Poco::UUIDGenerator().create().toString()));
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
		header.MessageID(xml_schema::Uri(Poco::UUIDGenerator().create().toString()));
	}
	MESSAGEMODEL::Envelope::BodyType body;
	{
		MESSAGEMODEL::Envelope::BodyType::ResolveMatchesType resolveMatches;
		resolveMatches.ResolveMatch(notification);
		body.ResolveMatches(resolveMatches);
	}

	return MESSAGEMODEL::Envelope(header, body);
}

struct DPWSDiscoveryHostSocketImpl::SendMulticastMessage : public Poco::Notification {
	SendMulticastMessage(const std::string & message) :
		content(message) {}
	const std::string content;
};

struct DPWSDiscoveryHostSocketImpl::SendUnicastMessage : public Poco::Notification {
	SendUnicastMessage(const MESSAGEMODEL::Envelope & message, const Poco::Net::SocketAddress & address) :
		content(message), address(address) {}
	const MESSAGEMODEL::Envelope content;
	const Poco::Net::SocketAddress address;
};

DPWSDiscoveryHostSocketImpl::DPWSDiscoveryHostSocketImpl(
		ProbeNotificationDispatcher & probeDispatcher,
		ResolveNotificationDispatcher & resolveDispatcher) :
	WithLogger(Log::DISCOVERY),
	_probeDispatcher(probeDispatcher),
	_resolveDispatcher(resolveDispatcher),
	_ipv4MulticastAddress(Poco::Net::SocketAddress(OSELib::UDP_MULTICAST_IP_V4, OSELib::UPD_MULTICAST_DISCOVERY_PORT)),
	_ipv6MulticastAddress(Poco::Net::SocketAddress (OSELib::UDP_MULTICAST_IP_V6, OSELib::UPD_MULTICAST_DISCOVERY_PORT)),
	_ipv4BindingAddress(Poco::Net::SocketAddress(Poco::Net::IPAddress(Poco::Net::IPAddress::Family::IPv4), _ipv4MulticastAddress.port())),
	_ipv6BindingAddress(Poco::Net::SocketAddress (Poco::Net::IPAddress(Poco::Net::IPAddress::Family::IPv6), _ipv6MulticastAddress.port())),
	_ipv4MulticastListeningSocket(Poco::Net::MulticastSocket(_ipv4BindingAddress.family())),
	_ipv6MulticastListeningSocket(Poco::Net::MulticastSocket(_ipv6MulticastAddress.family())),
	_generator(std::chrono::system_clock::now().time_since_epoch().count()),
	_distribution(0, OSELib::APP_MAX_DELAY)
{
	xercesc::XMLPlatformUtils::Initialize ();

	_ipv4MulticastListeningSocket.bind(_ipv4BindingAddress, true);
	for (const auto & nextIf : Poco::Net::NetworkInterface::list()) {
		if (nextIf.supportsIPv4()
			&& nextIf.address().isUnicast()
			&& !nextIf.address().isLoopback()) {
			_ipv4MulticastListeningSocket.joinGroup(_ipv4MulticastAddress.host(), nextIf);
			Poco::Net::DatagramSocket datagramSocket(Poco::Net::SocketAddress(nextIf.firstAddress(Poco::Net::IPAddress::Family::IPv4), 0), true);
			datagramSocket.setBlocking(false);
			_socketSendMessageQueue[datagramSocket].clear();
		}
	}
	_ipv4MulticastListeningSocket.setBlocking(false);

	_ipv6MulticastListeningSocket.bind(_ipv6BindingAddress, true);
	for (const auto & nextIf : Poco::Net::NetworkInterface::list()) {
		if (nextIf.supportsIPv6()
			&& nextIf.address().isUnicast()
			&& !nextIf.address().isLoopback()) {
			try {
			_ipv6MulticastListeningSocket.joinGroup(_ipv6MulticastAddress.host(), nextIf);
			Poco::Net::DatagramSocket datagramSocket(Poco::Net::SocketAddress(nextIf.firstAddress(Poco::Net::IPAddress::Family::IPv6), 0), true);
			datagramSocket.setBlocking(false);
			_socketSendMessageQueue[datagramSocket].clear();
			} catch (...) {
				// todo fixme. This loop fails, when a network interface has serveral network addresses, i.e. 2 IPv6 global scoped addresses
				log_error([&] { return "Another thing went wrong"; });
			}
		}
	}
	_ipv6MulticastListeningSocket.setBlocking(false);

	_reactor.addEventHandler(_ipv4MulticastListeningSocket, Poco::Observer<DPWSDiscoveryHostSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSDiscoveryHostSocketImpl::onMulticastSocketReadable));
	_reactor.addEventHandler(_ipv6MulticastListeningSocket, Poco::Observer<DPWSDiscoveryHostSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSDiscoveryHostSocketImpl::onMulticastSocketReadable));

	_reactor.addEventHandler(_ipv4MulticastListeningSocket, Poco::Observer<DPWSDiscoveryHostSocketImpl, Poco::Net::TimeoutNotification>(*this, &DPWSDiscoveryHostSocketImpl::onTimeOut));
	_reactor.addEventHandler(_ipv6MulticastListeningSocket, Poco::Observer<DPWSDiscoveryHostSocketImpl, Poco::Net::TimeoutNotification>(*this, &DPWSDiscoveryHostSocketImpl::onTimeOut));

	_reactorThread.start(_reactor);
}

DPWSDiscoveryHostSocketImpl::~DPWSDiscoveryHostSocketImpl() {
	_reactor.removeEventHandler(_ipv4MulticastListeningSocket, Poco::Observer<DPWSDiscoveryHostSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSDiscoveryHostSocketImpl::onMulticastSocketReadable));
	_reactor.removeEventHandler(_ipv6MulticastListeningSocket, Poco::Observer<DPWSDiscoveryHostSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSDiscoveryHostSocketImpl::onMulticastSocketReadable));

	for (auto & messagingSocketMapping : _socketSendMessageQueue) {
		_reactor.removeEventHandler(messagingSocketMapping.first, Poco::Observer<DPWSDiscoveryHostSocketImpl, Poco::Net::WritableNotification>(*this, &DPWSDiscoveryHostSocketImpl::onDatagrammSocketWritable));
		_reactor.removeEventHandler(messagingSocketMapping.first, Poco::Observer<DPWSDiscoveryHostSocketImpl, Poco::Net::TimeoutNotification>(*this, &DPWSDiscoveryHostSocketImpl::onTimeOut));
	}

	_reactor.stop();
	_reactorThread.join();

	xercesc::XMLPlatformUtils::Terminate ();
}

void DPWSDiscoveryHostSocketImpl::sendBye(const ByeType & bye) {
	MESSAGEMODEL::Envelope message(buildByeMessage(bye));
	MESSAGEMODEL::Envelope::HeaderType::AppSequenceType appSequence(context.getInstanceId(), context.getNextMessageCounter());
	message.Header().AppSequence(appSequence);
	if (message.Header().MessageID().present()) {
		context.registerMessageId(message.Header().MessageID().get());
	}
	for (auto & socketQueue : _socketSendMessageQueue) {
		socketQueue.second.enqueueNotification(new SendMulticastMessage(serializeMessage(message)));
		_reactor.addEventHandler(socketQueue.first, Poco::Observer<DPWSDiscoveryHostSocketImpl, Poco::Net::WritableNotification>(*this, &DPWSDiscoveryHostSocketImpl::onDatagrammSocketWritable));
	}
}

void DPWSDiscoveryHostSocketImpl::sendHello(const HelloType & hello) {
	context.resetInstanceId();
	MESSAGEMODEL::Envelope message(buildHelloMessage(hello));
	MESSAGEMODEL::Envelope::HeaderType::AppSequenceType appSequence(context.getInstanceId(), context.getNextMessageCounter());
	message.Header().AppSequence(appSequence);
	if (message.Header().MessageID().present()) {
		context.registerMessageId(message.Header().MessageID().get());
	}
	for (auto & socketQueue : _socketSendMessageQueue) {
		socketQueue.second.enqueueNotification(new SendMulticastMessage(serializeMessage(message)));
		_reactor.addEventHandler(socketQueue.first, Poco::Observer<DPWSDiscoveryHostSocketImpl, Poco::Net::WritableNotification>(*this, &DPWSDiscoveryHostSocketImpl::onDatagrammSocketWritable));
	}
}

void DPWSDiscoveryHostSocketImpl::onMulticastSocketReadable(Poco::Net::ReadableNotification * notification) {
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
		if (not context.registerMessageId(requestMessage->Header().MessageID().get())) {
			return;
		}
	}
	if (requestMessage->Body().Probe().present()) {
		const WS::DISCOVERY::ProbeType & probe(requestMessage->Body().Probe().get());
		std::vector<ProbeMatchType> result(_probeDispatcher.dispatch(probe));
		if (result.empty()) {
			return;
		}
		const MESSAGEMODEL::Envelope responseMessage(buildProbeMatchMessage(result, *requestMessage));
		_delayedMessages.enqueueNotification(new SendUnicastMessage(responseMessage, remoteAddr), createDelay());
	} else if (requestMessage->Body().Resolve().present()) {
		const WS::DISCOVERY::ResolveType & resolve(requestMessage->Body().Resolve().get());
		std::unique_ptr<ResolveMatchType> result(_resolveDispatcher.dispatch(resolve));
		if (result == nullptr) {
			return;
		}
		const MESSAGEMODEL::Envelope responseMessage(buildResolveMatchMessage(*result, *requestMessage));
		_delayedMessages.enqueueNotification(new SendUnicastMessage(responseMessage, remoteAddr), createDelay());
	}
	processDelayedMessages();
}

void DPWSDiscoveryHostSocketImpl::onDatagrammSocketWritable(Poco::Net::WritableNotification * notification) {
	const Poco::AutoPtr<Poco::Net::WritableNotification> pNf(notification);
	Poco::Net::DatagramSocket socket(pNf->socket());

	const Poco::AutoPtr<Poco::Notification> rawMessage(_socketSendMessageQueue[socket].dequeueNotification());
	if (rawMessage.isNull()) {
		notification->source().removeEventHandler(socket, Poco::Observer<DPWSDiscoveryHostSocketImpl, Poco::Net::WritableNotification>(*this, &DPWSDiscoveryHostSocketImpl::onDatagrammSocketWritable));
		return;
	}
	{ // send unicast
		const Poco::AutoPtr<SendUnicastMessage> message(rawMessage.cast<SendUnicastMessage>());
		if (not message.isNull()) {
			MESSAGEMODEL::Envelope messageEnvelope(message->content);
			MESSAGEMODEL::Envelope::HeaderType::AppSequenceType appSequence(context.getInstanceId(), context.getNextMessageCounter());
			messageEnvelope.Header().AppSequence(appSequence);
			const std::string content(serializeMessage(messageEnvelope));
			socket.sendTo(content.c_str(), content.size(), message->address, 0);
		}
	}
	{ // send multicast
		const Poco::AutoPtr<SendMulticastMessage> message(rawMessage.cast<SendMulticastMessage>());
		if (not message.isNull()) {
			Poco::Net::SocketAddress multicastAddress(_ipv4MulticastAddress);
			if (socket.address().family() == Poco::Net::IPAddress::Family::IPv6) {
				multicastAddress = _ipv6MulticastAddress;
			}
			socket.sendTo(message->content.c_str(), message->content.size(), multicastAddress, 0);
		}
	}
	processDelayedMessages();
}

void DPWSDiscoveryHostSocketImpl::onTimeOut(Poco::Net::TimeoutNotification * notification) {
	const Poco::AutoPtr<Poco::Net::TimeoutNotification> pNf(notification);
	processDelayedMessages();
}

Poco::Timestamp DPWSDiscoveryHostSocketImpl::createDelay() {
	return Poco::Timestamp() + Poco::Timespan(0, 0, 0, 0, _distribution(_generator));
}

void DPWSDiscoveryHostSocketImpl::processDelayedMessages() {
	if (_delayedMessages.empty()) {
		_reactor.setTimeout(Poco::Timespan(0, 0, 0, 0, 250000));
		return;
	} else {
		_reactor.setTimeout(Poco::Timespan(0, 0, 0, 0, 10000));
	}

	Poco::AutoPtr<Poco::Notification> notification(_delayedMessages.dequeueNotification());
	if (notification.isNull()) {
		return;
	}
	Poco::AutoPtr<SendUnicastMessage> unicastMessage(notification.cast<SendUnicastMessage>());
	if (unicastMessage.isNull()) {
		return;
	}
	for (auto & socketQueue : _socketSendMessageQueue) {
		if (socketQueue.first.address().family() == unicastMessage->address.family()) {
			socketQueue.second.enqueueNotification(new SendUnicastMessage(std::move(unicastMessage->content), unicastMessage->address));
			_reactor.addEventHandler(socketQueue.first, Poco::Observer<DPWSDiscoveryHostSocketImpl, Poco::Net::WritableNotification>(*this, &DPWSDiscoveryHostSocketImpl::onDatagrammSocketWritable));
		}
	}
}

} /* namespace Impl */
} /* namespace DPWS */
} /* namespace OSELib */
