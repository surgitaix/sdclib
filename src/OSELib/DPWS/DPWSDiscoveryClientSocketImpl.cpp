/*
 * DPWSDiscoveryClientSocketImpl.cpp
 *
 *  Created on: 11.12.2015
 *      Author: matthias
 */

#include <iostream>

#include "Poco/Buffer.h"
#include "Poco/UUIDGenerator.h"
#include "Poco/Net/SocketAddress.h"

#include "NormalizedMessageModel.hxx"

#include "OSCLib/SDCLibrary.h"
#include "OSELib/DPWS/DPWS11Constants.h"
#include "OSELib/DPWS/DPWSCommon.h"
#include "OSELib/DPWS/DPWSDiscoveryClientSocketImpl.h"
#include "OSELib/Helper/BufferAdapter.h"

namespace OSELib {
namespace DPWS {
namespace Impl {

struct SendMulticastMessage : public Poco::Notification {
	SendMulticastMessage(const std::string & message) :
		content_(message) {}
	const std::string content_;
};

const MESSAGEMODEL::Envelope buildProbeMessage(const ProbeType & filter) {
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

const MESSAGEMODEL::Envelope buildResolveMessage(const ResolveType & filter) {
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
		ByeNotificationDispatcher & byeDispatcher,
		HelloNotificationDispatcher & helloDispatcher,
		ProbeMatchNotificationDispatcher & probeMatchDispatcher,
		ResolveMatchNotificationDispatcher & resolveDispatcher) :
	WithLogger(Log::DISCOVERY),
	_byeDispatcher(byeDispatcher),
	_helloDispatcher(helloDispatcher),
	_probeMatchDispatcher(probeMatchDispatcher),
	_resolveDispatcher(resolveDispatcher)
{

	if (SDCLib::SDCLibrary::getInstance().getIP4enabled()) {
		_ipv4MulticastAddress = Poco::Net::SocketAddress(OSELib::UDP_MULTICAST_DISCOVERY_IP_V4, OSELib::UPD_MULTICAST_DISCOVERY_PORT);
		_ipv4BindingAddress = Poco::Net::SocketAddress(Poco::Net::IPAddress(Poco::Net::IPAddress::Family::IPv4), _ipv4MulticastAddress.port());
		_ipv4MulticastDiscoverySocket = Poco::Net::MulticastSocket(_ipv4BindingAddress.family());

		_ipv4MulticastDiscoverySocket.bind(_ipv4BindingAddress, true);
		for (const auto & nextIf : Poco::Net::NetworkInterface::list()) {
			if (nextIf.supportsIPv4()
				&& nextIf.address().isUnicast()
				&& !nextIf.address().isLoopback()) {
				_ipv4MulticastDiscoverySocket.joinGroup(_ipv4MulticastAddress.host(), nextIf);
				Poco::Net::DatagramSocket datagramSocket(Poco::Net::SocketAddress(nextIf.firstAddress(Poco::Net::IPAddress::Family::IPv4), 0), true);
				datagramSocket.setBlocking(false);
				_reactor.addEventHandler(datagramSocket, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onDatagrammSocketReadable));
				_socketSendMessageQueue[datagramSocket].clear();
			}
		}
		_ipv4MulticastDiscoverySocket.setBlocking(false);

		_reactor.addEventHandler(_ipv4MulticastDiscoverySocket, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onMulticastSocketReadable));
	}


	if (SDCLib::SDCLibrary::getInstance().getIP6enabled()) {
		_ipv6MulticastAddress = Poco::Net::SocketAddress (OSELib::UDP_MULTICAST_DISCOVERY_IP_V6, OSELib::UPD_MULTICAST_DISCOVERY_PORT);
		_ipv6BindingAddress = Poco::Net::SocketAddress (Poco::Net::IPAddress(Poco::Net::IPAddress::Family::IPv6), _ipv6MulticastAddress.port());
		_ipv6MulticastDiscoverySocket = Poco::Net::MulticastSocket(_ipv6BindingAddress.family());

		_ipv6MulticastDiscoverySocket.bind(_ipv6BindingAddress, true);
		for (const auto & nextIf : Poco::Net::NetworkInterface::list()) {
			if (nextIf.supportsIPv6()
				&& nextIf.address().isUnicast()
				&& !nextIf.address().isLoopback()) {
				try {
				_ipv6MulticastDiscoverySocket.joinGroup(_ipv6MulticastAddress.host(), nextIf);
				Poco::Net::DatagramSocket datagramSocket(Poco::Net::SocketAddress(nextIf.firstAddress(Poco::Net::IPAddress::Family::IPv6), 0), true);
				datagramSocket.setBlocking(false);
				_reactor.addEventHandler(datagramSocket, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onDatagrammSocketReadable));
				_socketSendMessageQueue[datagramSocket].clear();
				} catch (...) {
					// todo fixme. This loop fails, when a network interface has serveral network addresses, i.e. 2 IPv6 global scoped addresses
					log_error([&] { return "Some thing went wrong"; });
				}
			}
		}
		_ipv6MulticastDiscoverySocket.setBlocking(false);

		_reactor.addEventHandler(_ipv6MulticastDiscoverySocket, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onMulticastSocketReadable));
	}


	xercesc::XMLPlatformUtils::Initialize ();

	_reactorThread.start(_reactor);
}

DPWSDiscoveryClientSocketImpl::~DPWSDiscoveryClientSocketImpl() {
	_reactor.removeEventHandler(_ipv4MulticastDiscoverySocket, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onMulticastSocketReadable));
	_reactor.removeEventHandler(_ipv6MulticastDiscoverySocket, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onMulticastSocketReadable));

	for (auto & messagingSocketMapping : _socketSendMessageQueue) {
		_reactor.removeEventHandler(messagingSocketMapping.first, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onDatagrammSocketReadable));
		_reactor.removeEventHandler(messagingSocketMapping.first, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::WritableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onDatagrammSocketWritable));
	}

	_reactor.stop();
	_reactorThread.join();

	xercesc::XMLPlatformUtils::Terminate ();
}

void DPWSDiscoveryClientSocketImpl::sendProbe(const ProbeType & filter) {
	const MESSAGEMODEL::Envelope message(buildProbeMessage(filter));
	if (message.Header().MessageID().present()) {
		context.registerMessageId(message.Header().MessageID().get());
	}
	for (auto & socketQueue : _socketSendMessageQueue) {
		socketQueue.second.enqueueNotification(new SendMulticastMessage(serializeMessage(message)));
		_reactor.addEventHandler(socketQueue.first, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::WritableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onDatagrammSocketWritable));
	}
}

void DPWSDiscoveryClientSocketImpl::sendResolve(const ResolveType & filter) {
	const MESSAGEMODEL::Envelope message(buildResolveMessage(filter));
	if (message.Header().MessageID().present()) {
		context.registerMessageId(message.Header().MessageID().get());
	}
	for (auto & socketQueue : _socketSendMessageQueue) {
		socketQueue.second.enqueueNotification(new SendMulticastMessage(serializeMessage(message)));
		_reactor.addEventHandler(socketQueue.first, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::WritableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onDatagrammSocketWritable));
	}
}

void DPWSDiscoveryClientSocketImpl::onMulticastSocketReadable(Poco::Net::ReadableNotification * notification) {
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
		if (not verifyHello(*message)) {
			return;
		}
		_helloDispatcher.dispatch(message->Body().Hello().get());
	} else if (message->Body().Bye().present()) {
		if (not verifyBye(*message)) {
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
		if (not context.registerMessageId(message->Header().MessageID().get())) {
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
	Poco::Net::DatagramSocket socket(pNf->socket());

	const Poco::AutoPtr<Poco::Notification> rawMessage(_socketSendMessageQueue[socket].dequeueNotification());
	if (rawMessage.isNull()) {
		notification->source().removeEventHandler(socket, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::WritableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onDatagrammSocketWritable));
		return;
	}
	const Poco::AutoPtr<SendMulticastMessage> message(rawMessage.cast<SendMulticastMessage>());
	Poco::Net::SocketAddress multicastAddress(_ipv4MulticastAddress);
	if (socket.address().family() == Poco::Net::IPAddress::Family::IPv6) {
		multicastAddress = _ipv6MulticastAddress;
	}

	socket.sendTo(message->content_.c_str(), message->content_.size(), multicastAddress, 0);
}

bool DPWSDiscoveryClientSocketImpl::verifyBye(const MESSAGEMODEL::Envelope & message) {
	if (not message.Header().MessageID().present()) {
		log_error([&] { return "Bye message: Missing MessageID."; });
		return false;
	}
	if (not message.Header().Action().present()) {
		log_error([&] { return "Bye message: Missing Action."; });
		return false;
	}
	if (message.Header().Action().get() != byeUri) {
		log_error([&] { return "Bye message: Invalid Action."; });
		return false;
	}
	if (not message.Header().To().present()) {
		log_error([&] { return "Bye message: Missing To."; });
		return false;
	}
	if (message.Header().To().get() != discoveryUri) {
		log_error([&] { return "Bye message: Invalid value of To."; });
		return false;
	}
	if (not message.Header().AppSequence().present()) {
		log_error([&] { return "Bye message: Missing AppSequence."; });
		return false;
	}
	if (not message.Body().Bye().present()) {
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
	if (not message.Header().MessageID().present()) {
		log_error([&] { return "Hello message: Missing MessageID."; });
		return false;
	}
	if (not message.Header().Action().present()) {
		log_error([&] { return "Hello message: Missing Action."; });
		return false;
	}
	if (message.Header().Action().get() != helloUri) {
		log_error([&] { return "Hello message: Invalid Action."; });
		return false;
	}
	if (not message.Header().To().present()) {
		log_error([&] { return "Hello message: Missing To."; });
		return false;
	}
	if (message.Header().To().get() != discoveryUri) {
		log_error([&] { return "Hello message: Invalid value of To."; });
		return false;
	}
	if (not message.Header().AppSequence().present()) {
		log_error([&] { return "Hello message: Missing AppSequence."; });
		return false;
	}
	if (not message.Body().Hello().present()) {
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

} /* namespace Impl */
} /* namespace DPWS */
} /* namespace OSELib */
