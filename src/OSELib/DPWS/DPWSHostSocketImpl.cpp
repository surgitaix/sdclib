/*
 * DPWSHostSocketImpl.cpp
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#include <chrono>
#include <iostream>

#include "Poco/Buffer.h"
#include "Poco/UUIDGenerator.h"

#include "NormalizedMessageModel.hxx"

#include "OSELib/OSCP/SDCConstants.h"
#include "OSELib/DPWS/DPWS11Constants.h"
#include "OSELib/DPWS/DPWSCommon.h"
#include "OSELib/DPWS/DPWSHostSocketImpl.h"
#include "OSELib/DPWS/MessageAdapter.h"
#include "OSELib/Helper/BufferAdapter.h"
#include "OSCLib/SDCLibrary.h"

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

const MESSAGEMODEL::Envelope buildStreamMessage(const MDM::WaveformStream  & notification, const AddressType epr) {
	MESSAGEMODEL::Envelope::HeaderType header;
	{
		header.Action(xml_schema::Uri(OSCP::EVENT_ACTION_CDM_WAVEFORM_STREAM_REPORT));
		header.MessageID(xml_schema::Uri(Poco::UUIDGenerator().create().toString()));
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
		ProbeNotificationDispatcher & probeDispatcher,
		ResolveNotificationDispatcher & resolveDispatcher) :
	WithLogger(Log::DISCOVERY),
	probeDispatcher(probeDispatcher),
	resolveDispatcher(resolveDispatcher),
	ipv4DiscoveryMulticastAddress(Poco::Net::SocketAddress(OSELib::UDP_MULTICAST_DISCOVERY_IP_V4, OSELib::UPD_MULTICAST_DISCOVERY_PORT)),
	ipv6DiscoveryMulticastAddress(Poco::Net::SocketAddress(OSELib::UDP_MULTICAST_DISCOVERY_IP_V6, OSELib::UPD_MULTICAST_DISCOVERY_PORT)),
	ipv4StreamMulticastAddress(Poco::Net::SocketAddress(OSELib::UDP_MULTICAST_STREAMING_IP_V4, OSELib::UPD_MULTICAST_STREAMING_PORT)),
	ipv6StreamMulticastAddress(Poco::Net::SocketAddress(OSELib::UDP_MULTICAST_STREAMING_IP_V6, OSELib::UPD_MULTICAST_STREAMING_PORT)),
	ipv4BindingAddress(Poco::Net::SocketAddress(Poco::Net::IPAddress(Poco::Net::IPAddress::Family::IPv4), ipv4DiscoveryMulticastAddress.port())),
	ipv6BindingAddress(Poco::Net::SocketAddress(Poco::Net::IPAddress(Poco::Net::IPAddress::Family::IPv6), ipv6DiscoveryMulticastAddress.port())),
	ipv4MulticastListeningSocket(Poco::Net::MulticastSocket(ipv4BindingAddress.family())),
	ipv6MulticastListeningSocket(Poco::Net::MulticastSocket(ipv6BindingAddress.family())),
	generator(std::chrono::system_clock::now().time_since_epoch().count()),
	distribution(0, OSELib::APP_MAX_DELAY)
{
	xercesc::XMLPlatformUtils::Initialize ();

	if ( OSCLib::SDCLibrary::getInstance().getIP4enabled() ) {
		ipv4MulticastListeningSocket.bind(ipv4BindingAddress, true);
		for (const auto & nextIf : Poco::Net::NetworkInterface::list()) {
			if (nextIf.supportsIPv4()
				&& nextIf.address().isUnicast()
				&& !nextIf.address().isLoopback()) {
				ipv4MulticastListeningSocket.joinGroup(ipv4DiscoveryMulticastAddress.host(), nextIf);
				Poco::Net::DatagramSocket datagramSocket(Poco::Net::SocketAddress(nextIf.firstAddress(Poco::Net::IPAddress::Family::IPv4), 0), true);
				datagramSocket.setBlocking(false);
				// adds datagramSocket to the queue with a clear entry
				socketSendMessageQueue[datagramSocket].clear();
			}
		}
		ipv4MulticastListeningSocket.setBlocking(false);
		reactor.addEventHandler(ipv4MulticastListeningSocket, Poco::Observer<DPWSHostSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSHostSocketImpl::onMulticastSocketReadable));
		reactor.addEventHandler(ipv4MulticastListeningSocket, Poco::Observer<DPWSHostSocketImpl, Poco::Net::TimeoutNotification>(*this, &DPWSHostSocketImpl::onTimeOut));
	}


	if ( OSCLib::SDCLibrary::getInstance().getIP6enabled() ) {
		ipv6MulticastListeningSocket.bind(ipv6BindingAddress, true);
		for (const auto & nextIf : Poco::Net::NetworkInterface::list()) {
			if (nextIf.supportsIPv6()
				&& nextIf.address().isUnicast()
				&& !nextIf.address().isLoopback()) {
				try {
				ipv6MulticastListeningSocket.joinGroup(ipv6DiscoveryMulticastAddress.host(), nextIf);
				Poco::Net::DatagramSocket datagramSocket(Poco::Net::SocketAddress(nextIf.firstAddress(Poco::Net::IPAddress::Family::IPv6), 0), true);
				datagramSocket.setBlocking(false);
				// adds datagramSocket to the queue with a clear entry
				socketSendMessageQueue[datagramSocket].clear();
				} catch (...) {
					// todo fixme. This loop fails, when a network interface has several network addresses, i.e. 2 IPv6 global scoped addresses
					log_error([&] { return "Another thing went wrong"; });
				}
			}
		}
		ipv6MulticastListeningSocket.setBlocking(false);

		reactor.addEventHandler(ipv6MulticastListeningSocket, Poco::Observer<DPWSHostSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSHostSocketImpl::onMulticastSocketReadable));
		reactor.addEventHandler(ipv6MulticastListeningSocket, Poco::Observer<DPWSHostSocketImpl, Poco::Net::TimeoutNotification>(*this, &DPWSHostSocketImpl::onTimeOut));
	}



	reactorThread.start(reactor);
}

DPWSHostSocketImpl::~DPWSHostSocketImpl() {
	reactor.removeEventHandler(ipv4MulticastListeningSocket, Poco::Observer<DPWSHostSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSHostSocketImpl::onMulticastSocketReadable));
	reactor.removeEventHandler(ipv6MulticastListeningSocket, Poco::Observer<DPWSHostSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSHostSocketImpl::onMulticastSocketReadable));

	for (auto & messagingSocketMapping : socketSendMessageQueue) {
		reactor.removeEventHandler(messagingSocketMapping.first, Poco::Observer<DPWSHostSocketImpl, Poco::Net::WritableNotification>(*this, &DPWSHostSocketImpl::onDatagrammSocketWritable));
		reactor.removeEventHandler(messagingSocketMapping.first, Poco::Observer<DPWSHostSocketImpl, Poco::Net::TimeoutNotification>(*this, &DPWSHostSocketImpl::onTimeOut));
	}

	reactor.stop();
	reactorThread.join();

	xercesc::XMLPlatformUtils::Terminate ();
}

void DPWSHostSocketImpl::sendBye(const ByeType & bye) {
	MESSAGEMODEL::Envelope message(buildByeMessage(bye));
	MESSAGEMODEL::Envelope::HeaderType::AppSequenceType appSequence(context.getInstanceId(), context.getNextMessageCounter());
	message.Header().AppSequence(appSequence);
	if (message.Header().MessageID().present()) {
		context.registerMessageId(message.Header().MessageID().get());
	}
	for (auto & socketQueue : socketSendMessageQueue) {
		socketQueue.second.enqueueNotification(new SendMulticastMessage(serializeMessage(message), ipv4DiscoveryMulticastAddress, ipv6DiscoveryMulticastAddress));
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
		socketQueue.second.enqueueNotification(new SendMulticastMessage(serializeMessage(message), ipv4StreamMulticastAddress, ipv6StreamMulticastAddress));
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
		socketQueue.second.enqueueNotification(new SendMulticastMessage(serializeMessage(message), ipv4DiscoveryMulticastAddress, ipv6DiscoveryMulticastAddress));
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
		if (not context.registerMessageId(requestMessage->Header().MessageID().get())) {
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

void DPWSHostSocketImpl::onDatagrammSocketWritable(Poco::Net::WritableNotification * notification) {
	processDelayedMessages();
	const Poco::AutoPtr<Poco::Net::WritableNotification> pNf(notification);
	Poco::Net::DatagramSocket socket(pNf->socket());

	const Poco::AutoPtr<Poco::Notification> rawMessage(socketSendMessageQueue[socket].dequeueNotification());
	if (rawMessage.isNull()) {
		notification->source().removeEventHandler(socket, Poco::Observer<DPWSHostSocketImpl, Poco::Net::WritableNotification>(*this, &DPWSHostSocketImpl::onDatagrammSocketWritable));
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

Poco::Timestamp DPWSHostSocketImpl::createDelay() {
	return Poco::Timestamp() + Poco::Timespan(0, 0, 0, 0, distribution(generator));
}

void DPWSHostSocketImpl::processDelayedMessages() {
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
