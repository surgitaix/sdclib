#include <algorithm>
#include <chrono>
#include <deque>
#include <iostream>
#include <memory>
#include <mutex>
#include <random>
#include <string>
#include <tuple>

#include "Poco/Buffer.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/NotificationQueue.h"
#include "Poco/Observer.h"
#include "Poco/Thread.h"
#include "Poco/Timestamp.h"
#include "Poco/TimedNotificationQueue.h"
#include "Poco/UnbufferedStreamBuf.h"
#include "Poco/UUIDGenerator.h"
#include "Poco/Net/DatagramSocket.h"
#include "Poco/Net/MulticastSocket.h"
#include "Poco/Net/NetworkInterface.h"
#include "Poco/Net/SocketNotification.h"
#include "Poco/Net/SocketReactor.h"

#include <xercesc/util/PlatformUtils.hpp>

#include "MessageModel-Discovery.hxx"

namespace DPWSDiscovery {

namespace Helpers {

struct BufferAdapter : public std::istream, public Poco::UnbufferedStreamBuf {
	BufferAdapter(const Poco::Buffer<char> & buffer, std::size_t length) :
	std::istream(this),
	_buffer(buffer),
	_length(std::min(length, buffer.size())),
	_position(0)
	{
	}

	virtual ~BufferAdapter() = default;

	virtual int readFromDevice() override {
		if (_position < _length) {
			return charToInt(_buffer[_position++]);
		} else {
			return char_traits::eof();
		}
	}

private:
	const Poco::Buffer<char> & _buffer;
	const std::size_t _length;
	std::size_t _position;
};

}

namespace Types {

typedef xml_schema::Uri UriType;
typedef UriType XAddressType;
typedef ::WS::DISCOVERY::UriListType XAddressesType;
typedef UriType ScopeType;
typedef ::WS::DISCOVERY::UriListType ScopesType;
typedef xml_schema::Qname QName;
typedef QName TypeType;
typedef ::WS::DISCOVERY::QNameListType TypesType;

typedef WS::ADDRESSING::AttributedURIType AddressType;
typedef WS::ADDRESSING::EndpointReferenceType EndpointReferenceType;
typedef unsigned int MetadataVersionType;
typedef WS::DISCOVERY::ProbeType ProbeType;
typedef WS::DISCOVERY::ResolveType ResolveType;
typedef WS::DISCOVERY::ByeType ByeType;
typedef WS::DISCOVERY::HelloType HelloType;
typedef WS::DISCOVERY::ProbeMatchType ProbeMatchType;
typedef WS::DISCOVERY::ResolveMatchType ResolveMatchType;

struct Get {
	template<class Message>
	static AddressType EPRAddress(const Message & message) {
		return message.EndpointReference().Address();
	}

	template<class Message>
	static MetadataVersionType MetadataVersion(const Message & message) {
		return message.MetadataVersion();
	}

	template<class Message>
	static XAddressesType XAddresses(const Message & message) {
		if (message.XAddrs().present()) {
			return message.XAddrs().get();
		} else {
			return XAddressesType();
		}
	}

	template<class Message>
	static ScopesType Scopes(const Message & message) {
		if (message.Scopes().present()) {
			return message.Scopes().get();
		} else {
			return ScopesType();
		}
	}

	template<class Message>
	static TypesType Types(const Message & message) {
		if (message.Types().present()) {
			return message.Types().get();
		} else {
			return TypesType();
		}
	}

	static UriType URI(const QName & qname) {
		return qname.namespace_();
	}

	static std::string LocalName(const QName & qname) {
		return qname.name();
	}
};

class ByeNotificationDispatcher {
protected:
	ByeNotificationDispatcher() = default;
	virtual ~ByeNotificationDispatcher() = default;

public:
	virtual void dispatch(const ByeType & notification) = 0;
};

class HelloNotificationDispatcher {
protected:
	HelloNotificationDispatcher() = default;
	virtual ~HelloNotificationDispatcher() = default;

public:
	virtual void dispatch(const HelloType & notification) = 0;
};

class ProbeNotificationDispatcher {
protected:
	ProbeNotificationDispatcher() = default;
	virtual ~ProbeNotificationDispatcher() = default;

public:
	virtual std::vector<ProbeMatchType> dispatch(const ProbeType & filter) = 0;
};

class ProbeMatchNotificationDispatcher {
protected:
	ProbeMatchNotificationDispatcher() = default;
	virtual ~ProbeMatchNotificationDispatcher() = default;

public:
	virtual void dispatch(const ProbeMatchType & notification) = 0;
};

class ResolveNotificationDispatcher {
protected:
	ResolveNotificationDispatcher() = default;
	virtual ~ResolveNotificationDispatcher() = default;

public:
	virtual std::unique_ptr<ResolveMatchType> dispatch(const ResolveType & filter) = 0;
};

class ResolveMatchNotificationDispatcher {
protected:
	ResolveMatchNotificationDispatcher() = default;
	virtual ~ResolveMatchNotificationDispatcher() = default;

public:
	virtual void dispatch(const ResolveMatchType & notification) = 0;
};

template<class MessageType>
void dump(std::ostream & stream, const MessageType & n) {
	stream << "  EPR: " << Get::EPRAddress(n) << std::endl;
	stream << "  Metadata version: " << Get::MetadataVersion(n) << std::endl;
	stream << "  XAddresses: " << std::endl;
	for (const auto & xaddr : Get::XAddresses(n)) {
		stream << "    " << xaddr << std::endl;
	}
	stream << "  Types: " << std::endl;
	for (const auto & type : Get::Types(n)) {
		stream << "    " << Get::URI(type) << ":"  << Get::LocalName(type) << std::endl;
	}
	stream << "  Scopes: " << std::endl;
	for (const auto & scope : Get::Scopes(n)) {
		stream << "    " << scope << std::endl;
	}
}

template<>
void dump(std::ostream & stream, const ByeType & n) {
	stream << "  EPR: " << Get::EPRAddress(n) << std::endl;
	stream << "  XAddresses: " << std::endl;
	for (const auto & xaddr : Get::XAddresses(n)) {
		stream << "    " << xaddr << std::endl;
	}
	stream << "  Types: " << std::endl;
	for (const auto & type : Get::Types(n)) {
		stream << "    " << Get::URI(type) << ":"  << Get::LocalName(type) << std::endl;
	}
	stream << "  Scopes: " << std::endl;
	for (const auto & scope : Get::Scopes(n)) {
		stream << "    " << scope << std::endl;
	}
}

std::ostream & operator<<(std::ostream & stream, const ProbeMatchType & n) {
	stream << "ProbeMatch Notification" << std::endl;
	dump(stream, n);
	return stream;
}

std::ostream & operator<<(std::ostream & stream, const ResolveMatchType & n) {
	stream << "ResolveMatch Notification" << std::endl;
	dump(stream, n);
	return stream;
}

std::ostream & operator<<(std::ostream & stream, const ByeType & n) {
	stream << "Bye Notification" << std::endl;
	dump(stream, n);
	return stream;
}

std::ostream & operator<<(std::ostream & stream, const HelloType & n) {
	stream << "Hello Notification" << std::endl;
	dump(stream, n);
	return stream;
}

}

namespace Impl {

const std::string UDP_MULTICAST_IP_V4("239.255.255.250");
const std::string UDP_MULTICAST_IP_V6("FF02::C");
constexpr uint16_t UPD_MULTICAST_DISCOVERY_PORT(3702);

constexpr unsigned int APP_MAX_DELAY(500000);

const xml_schema::Flags xercesFlags(::xml_schema::Flags::no_xml_declaration | ::xml_schema::Flags::dont_validate | ::xml_schema::Flags::dont_initialize);
const xml_schema::Uri discoveryUri("urn:docs-oasis-open-org:ws-dd:ns:discovery:2009:01");
const xml_schema::Uri byeUri("http://docs.oasis-open.org/ws-dd/ns/discovery/2009/01/Bye");
const xml_schema::Uri helloUri("http://docs.oasis-open.org/ws-dd/ns/discovery/2009/01/Hello");
const xml_schema::Uri probeUri("http://docs.oasis-open.org/ws-dd/ns/discovery/2009/01/Probe");
const xml_schema::Uri probeMatchesUri("http://docs.oasis-open.org/ws-dd/ns/discovery/2009/01/ProbeMatches");
const xml_schema::Uri resolveUri("http://docs.oasis-open.org/ws-dd/ns/discovery/2009/01/Resolve");
const xml_schema::Uri resolveMatchesUri("http://docs.oasis-open.org/ws-dd/ns/discovery/2009/01/ResolveMatches");
const xml_schema::Uri addressingAnonymousUri("http://www.w3.org/2005/08/addressing/anonymous");
const std::string XML_ENCODING("UTF-8");

std::unique_ptr<WS::MESSAGEMODEL::DISCOVERY::Envelope> parseMessage(std::istream & stream) {
	try {
		return WS::MESSAGEMODEL::DISCOVERY::Envelope_(stream, xercesFlags);
	} catch (const xml_schema::Exception& e) {
		std::cout << "Parsing failed with error: " << e << std::endl;
	} catch (...) {
		std::cout << "Parsing failed with unknown error." << std::endl;
	}
	return nullptr;
}

const WS::MESSAGEMODEL::DISCOVERY::Envelope buildByeMessage(const Types::ByeType & notification) {
	::WS::MESSAGEMODEL::DISCOVERY::Header header;
	{
		header.Action(byeUri);
		header.To(discoveryUri);
		header.MessageID(xml_schema::Uri(Poco::UUIDGenerator().create().toString()));
	}
	::WS::MESSAGEMODEL::DISCOVERY::Body body;
	{
		body.Bye(notification);
	}
	return WS::MESSAGEMODEL::DISCOVERY::Envelope(header, body);
}

const WS::MESSAGEMODEL::DISCOVERY::Envelope buildHelloMessage(const Types::HelloType & notification) {
	::WS::MESSAGEMODEL::DISCOVERY::Header header;
	{
		header.Action(helloUri);
		header.To(discoveryUri);
		header.MessageID(xml_schema::Uri(Poco::UUIDGenerator().create().toString()));
	}
	::WS::MESSAGEMODEL::DISCOVERY::Body body;
	{
		body.Hello(notification);
	}

	return WS::MESSAGEMODEL::DISCOVERY::Envelope(header, body);
}

const WS::MESSAGEMODEL::DISCOVERY::Envelope buildProbeMessage(const Types::ProbeType & filter) {
	::WS::MESSAGEMODEL::DISCOVERY::Header header;
	{
		header.Action(probeUri);
		header.To(discoveryUri);
		header.MessageID(xml_schema::Uri(Poco::UUIDGenerator().create().toString()));
	}
	::WS::MESSAGEMODEL::DISCOVERY::Body body;
	{
		body.Probe(filter);
	}

	return WS::MESSAGEMODEL::DISCOVERY::Envelope(header, body);
}

const WS::MESSAGEMODEL::DISCOVERY::Envelope buildProbeMatchMessage(const std::vector<Types::ProbeMatchType> & notifications, const ::WS::MESSAGEMODEL::DISCOVERY::Envelope & request) {
	::WS::MESSAGEMODEL::DISCOVERY::Header header;
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
	::WS::MESSAGEMODEL::DISCOVERY::Body body;
	{
		::WS::MESSAGEMODEL::DISCOVERY::Body::ProbeMatchesType probeMatches;
		for (const auto & match: notifications) {
			probeMatches.ProbeMatch().push_back(match);
		}
		body.ProbeMatches(probeMatches);
	}

	return WS::MESSAGEMODEL::DISCOVERY::Envelope(header, body);
}

const WS::MESSAGEMODEL::DISCOVERY::Envelope buildResolveMessage(const Types::ResolveType & filter) {
	::WS::MESSAGEMODEL::DISCOVERY::Header header;
	{
		header.Action(resolveUri);
		header.To(discoveryUri);
		header.MessageID(xml_schema::Uri(Poco::UUIDGenerator().create().toString()));
	}
	::WS::MESSAGEMODEL::DISCOVERY::Body body;
	{
		body.Resolve(filter);
	}

	return WS::MESSAGEMODEL::DISCOVERY::Envelope(header, body);
}

const WS::MESSAGEMODEL::DISCOVERY::Envelope buildResolveMatchMessage(const Types::ResolveMatchType & notification, const ::WS::MESSAGEMODEL::DISCOVERY::Envelope & request) {
	::WS::MESSAGEMODEL::DISCOVERY::Header header;
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
	::WS::MESSAGEMODEL::DISCOVERY::Body body;
	{
		::WS::MESSAGEMODEL::DISCOVERY::Body::ResolveMatchesType resolveMatches;
		resolveMatches.ResolveMatch(notification);
		body.ResolveMatches(resolveMatches);
	}

	return WS::MESSAGEMODEL::DISCOVERY::Envelope(header, body);
}

const std::string serializeMessage(const WS::MESSAGEMODEL::DISCOVERY::Envelope & message) {
	std::ostringstream stream;
	xml_schema::NamespaceInfomap map;
	WS::MESSAGEMODEL::DISCOVERY::Envelope_(stream, message, map, XML_ENCODING, xercesFlags);
	return stream.str();
}

bool compare(const Types::ProbeType & filter, const Types::ProbeMatchType & n) {
	using namespace Types;
	const ScopesType foundScopes(Get::Scopes(n));
	const TypesType foundTypes(Get::Types(n));
	const auto matchScopes =
		[&](const ScopeType & scope) {
			return std::find(foundScopes.begin(), foundScopes.end(), scope) != foundScopes.end();
		};
	const auto matchTypes =
		[&](const TypeType & qname) {
			return std::find(foundTypes.begin(), foundTypes.end(), qname) != foundTypes.end();
		};

	const ScopesType filterScopes(Get::Scopes(filter));
	const TypesType filterTypes(Get::Types(filter));
	return std::all_of(filterScopes.begin(), filterScopes.end(), matchScopes)
		&& std::all_of(filterTypes.begin(), filterTypes.end(), matchTypes);
}

bool compare(const Types::ResolveType & filter, const Types::ResolveMatchType & n) {
	using namespace Types;
	const AddressType foundType(Get::EPRAddress(n));
	const AddressType filterType(Get::EPRAddress(filter));
	return foundType == filterType;
}

struct MessagingContext {
	MessagingContext() :
		_instanceId(0),
		_messageCounter(0)
	{
	}

	~MessagingContext() {
	}

	bool registerMessageId(const std::string & id) {
		if (std::find(_knownMessageIds.begin(), _knownMessageIds.end(), id) != _knownMessageIds.end()) {
			return false;
		} else {
			if (_knownMessageIds.size() >= 100) {
				_knownMessageIds.pop_back();
			}
			_knownMessageIds.push_front(id);
			return true;
		}
	}

	void clearAppSequenceCache() {
		_knownAppsequences.clear();
	}

	void resetInstanceId() {
		_instanceId = std::chrono::system_clock::now().time_since_epoch().count() / 1000000;
	}

	unsigned long long int getInstanceId() const {
		return _instanceId;
	}

	unsigned long long int getCurrentMessageCounter() const {
		return _messageCounter;
	}

	unsigned long long int getNextMessageCounter() {
		return ++_messageCounter;
	}

	bool registerAppSequence(::WS::DISCOVERY::AppSequenceType & appSequence) {
		if (appSequence.SequenceId().present()) {
			return registerAppSequence(appSequence.InstanceId(), appSequence.MessageNumber(), appSequence.SequenceId().get());
		} else {
			return registerAppSequence(appSequence.InstanceId(), appSequence.MessageNumber());
		}
	}

	bool registerAppSequence(unsigned long long int instanceId, unsigned long long int messageNumber, const std::string & sequenceId = "NULL") {
		auto appsequenceIterator = _knownAppsequences.find(instanceId);
		if (appsequenceIterator == _knownAppsequences.end()) {
			// instance id unknown => add new mapping and store sequence id and message number
			SequenceMapping sequenceMapping;
			sequenceMapping[sequenceId] = messageNumber;
			_knownAppsequences[instanceId] = sequenceMapping;
			return true;
		}
		// instance id known => search for sequence id
		SequenceMapping & sequenceMapping(appsequenceIterator->second);
		auto sequenceMappingIterator = sequenceMapping.find(sequenceId);
		if (sequenceMappingIterator == sequenceMapping.end()) {
			//instance id known, sequence id unknown => add new mapping and store message number
			sequenceMapping[sequenceId] = messageNumber;
			return true;
		}

		// instance id and sequence id known => compare message number
		if (sequenceMappingIterator->second < messageNumber) {
			// message number is newer than cached value => accept and update
			sequenceMappingIterator->second = messageNumber;
			return true;
		}

		// instance id and sequence id known, cached message number is higher than received value => reject new value
		return false;
	}

private:
	unsigned long long int _instanceId;
	unsigned long long int _messageCounter;

	std::deque<std::string> _knownMessageIds;
	typedef std::map<std::string, unsigned long long int> SequenceMapping;
	std::map<unsigned long long  int, SequenceMapping> _knownAppsequences;
};

class DPWSDiscoveryClientSocketImpl {
public:
	DPWSDiscoveryClientSocketImpl(
			Types::ByeNotificationDispatcher & byeDispatcher,
			Types::HelloNotificationDispatcher & helloDispatcher,
			Types::ProbeMatchNotificationDispatcher & probeMatchDispatcher,
			Types::ResolveMatchNotificationDispatcher & resolveDispatcher) :
		_byeDispatcher(byeDispatcher),
		_helloDispatcher(helloDispatcher),
		_probeMatchDispatcher(probeMatchDispatcher),
		_resolveDispatcher(resolveDispatcher),
		_ipv4MulticastAddress(Poco::Net::SocketAddress(UDP_MULTICAST_IP_V4, UPD_MULTICAST_DISCOVERY_PORT)),
		_ipv6MulticastAddress(Poco::Net::SocketAddress (UDP_MULTICAST_IP_V6, UPD_MULTICAST_DISCOVERY_PORT)),
		_ipv4BindingAddress(Poco::Net::SocketAddress(Poco::Net::IPAddress(Poco::Net::IPAddress::Family::IPv4), _ipv4MulticastAddress.port())),
		_ipv6BindingAddress(Poco::Net::SocketAddress (Poco::Net::IPAddress(Poco::Net::IPAddress::Family::IPv6), _ipv6MulticastAddress.port())),
		_ipv4MulticastListeningSocket(Poco::Net::MulticastSocket(_ipv4BindingAddress.family())),
		_ipv6MulticastListeningSocket(Poco::Net::MulticastSocket(_ipv6MulticastAddress.family()))
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
				_reactor.addEventHandler(datagramSocket, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onDatagrammSocketReadable));
				_socketSendMessageQueue[datagramSocket].clear();
			}
		}
		_ipv4MulticastListeningSocket.setBlocking(false);

		_ipv6MulticastListeningSocket.bind(_ipv6BindingAddress, true);
		for (const auto & nextIf : Poco::Net::NetworkInterface::list()) {
			if (nextIf.supportsIPv6()
				&& nextIf.address().isUnicast()
				&& !nextIf.address().isLoopback()) {
				_ipv6MulticastListeningSocket.joinGroup(_ipv6MulticastAddress.host(), nextIf);
				Poco::Net::DatagramSocket datagramSocket(Poco::Net::SocketAddress(nextIf.firstAddress(Poco::Net::IPAddress::Family::IPv6), 0), true);
				datagramSocket.setBlocking(false);
				_reactor.addEventHandler(datagramSocket, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onDatagrammSocketReadable));
				_socketSendMessageQueue[datagramSocket].clear();
			}
		}
		_ipv6MulticastListeningSocket.setBlocking(false);

		_reactor.addEventHandler(_ipv4MulticastListeningSocket, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onMulticastSocketReadable));
		_reactor.addEventHandler(_ipv6MulticastListeningSocket, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onMulticastSocketReadable));

		_reactorThread.start(_reactor);
	}

	~DPWSDiscoveryClientSocketImpl() {
		_reactor.removeEventHandler(_ipv4MulticastListeningSocket, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onMulticastSocketReadable));
		_reactor.removeEventHandler(_ipv6MulticastListeningSocket, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onMulticastSocketReadable));

		for (auto & messagingSocketMapping : _socketSendMessageQueue) {
			_reactor.removeEventHandler(messagingSocketMapping.first, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onDatagrammSocketReadable));
			_reactor.removeEventHandler(messagingSocketMapping.first, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::WritableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onDatagrammSocketWritable));
		}

		_reactor.stop();
		_reactorThread.join();

		xercesc::XMLPlatformUtils::Terminate ();
	}

	void sendProbe(const Types::ProbeType & filter) {
		const WS::MESSAGEMODEL::DISCOVERY::Envelope message(buildProbeMessage(filter));
		if (message.Header().MessageID().present()) {
			context.registerMessageId(message.Header().MessageID().get());
		}
		for (auto & socketQueue : _socketSendMessageQueue) {
			socketQueue.second.enqueueNotification(new SendMulticastMessage(serializeMessage(message)));
			_reactor.addEventHandler(socketQueue.first, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::WritableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onDatagrammSocketWritable));
		}
	}

	void sendResolve(const Types::ResolveType & filter) {
		const WS::MESSAGEMODEL::DISCOVERY::Envelope message(buildResolveMessage(filter));
		if (message.Header().MessageID().present()) {
			context.registerMessageId(message.Header().MessageID().get());
		}
		for (auto & socketQueue : _socketSendMessageQueue) {
			socketQueue.second.enqueueNotification(new SendMulticastMessage(serializeMessage(message)));
			_reactor.addEventHandler(socketQueue.first, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::WritableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onDatagrammSocketWritable));
		}
	}

private:
	void onMulticastSocketReadable(Poco::Net::ReadableNotification * notification) {
		const Poco::AutoPtr<Poco::Net::ReadableNotification> pNf(notification);
		Poco::Net::MulticastSocket socket(pNf->socket());
		const int available(socket.available());
		if (available == 0) {
			return;
		}

		Poco::Buffer<char> buf(available);
		Poco::Net::SocketAddress remoteAddr;
		const int received(socket.receiveFrom(buf.begin(), available, remoteAddr, 0));
		Helpers::BufferAdapter adapter(buf, received);
		std::unique_ptr<WS::MESSAGEMODEL::DISCOVERY::Envelope> message(parseMessage(adapter));

		if (message == nullptr) {
			return;
		}
		if (not message->Header().MessageID().present()) {
			return;
		}
		if (not context.registerMessageId(message->Header().MessageID().get())) {
			return;
		}
		if (not message->Header().AppSequence().present()) {
			return;
		}
		if (not context.registerAppSequence(message->Header().AppSequence().get())) {
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

	void onDatagrammSocketReadable(Poco::Net::ReadableNotification * notification) {
		const Poco::AutoPtr<Poco::Net::ReadableNotification> pNf(notification);
		Poco::Net::DatagramSocket socket(pNf->socket());
		const int available(socket.available());
		if (available == 0) {
			return;
		}

		Poco::Buffer<char> buf(available);
		Poco::Net::SocketAddress remoteAddr;
		const int received(socket.receiveFrom(buf.begin(), available, remoteAddr, 0));
		Helpers::BufferAdapter adapter(buf, received);
		std::unique_ptr<WS::MESSAGEMODEL::DISCOVERY::Envelope> message(parseMessage(adapter));

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

	void onDatagrammSocketWritable(Poco::Net::WritableNotification * notification) {
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

	struct SendMulticastMessage : public Poco::Notification {
		SendMulticastMessage(const std::string & message) :
			content_(message) {}
		const std::string content_;
	};

	bool verifyBye(const WS::MESSAGEMODEL::DISCOVERY::Envelope & message) {
		if (not message.Header().MessageID().present()) {
			std::cout << "Missing MessageID." << std::endl;
			return false;
		}
		if (not message.Header().Action().present()) {
			std::cout << "Missing Action." << std::endl;
			return false;
		}
		if (message.Header().Action().get() != byeUri) {
			std::cout << "Invalid bye action." << std::endl;
			return false;
		}
		if (not message.Header().To().present()) {
			std::cout << "Missing To." << std::endl;
			return false;
		}
		if (message.Header().To().get() != discoveryUri) {
			std::cout << "Invalid value of 'to'." << std::endl;
			return false;
		}
		if (not message.Header().AppSequence().present()) {
			std::cout << "Missing AppSequence." << std::endl;
			return false;
		}
		if (not message.Body().Bye().present()) {
			std::cout << "Missing hello body." << std::endl;
			return false;
		}
		if (message.Body().Bye().get().EndpointReference().Address() == "") {
			std::cout << "EndpointReference address empty." << std::endl;
			return false;
		}
		if (message.Header().RelatesTo().present()) {
			std::cout << "RelatesTo field should not be present."<< std::endl;
			return false;
		}

		return true;
	}

	bool verifyHello(const WS::MESSAGEMODEL::DISCOVERY::Envelope & message) {
		if (not message.Header().MessageID().present()) {
			std::cout << "Missing MessageID." << std::endl;
			return false;
		}
		if (not message.Header().Action().present()) {
			std::cout << "Missing Action." << std::endl;
			return false;
		}
		if (message.Header().Action().get() != helloUri) {
			std::cout << "Invalid hello action." << std::endl;
			return false;
		}
		if (not message.Header().To().present()) {
			std::cout << "Missing To." << std::endl;
			return false;
		}
		if (message.Header().To().get() != discoveryUri) {
			std::cout << "Invalid value of 'to'." << std::endl;
			return false;
		}
		if (not message.Header().AppSequence().present()) {
			std::cout << "Missing AppSequence." << std::endl;
			return false;
		}
		if (not message.Body().Hello().present()) {
			std::cout << "Missing hello body." << std::endl;
			return false;
		}
		if (message.Body().Hello().get().EndpointReference().Address() == "") {
			std::cout << "EndpointReference address empty." << std::endl;
			return false;
		}
		if (message.Header().RelatesTo().present()) {
			std::cout << "RelatesTo field should not be present."<< std::endl;
			return false;
		}

		return true;
	}

	Types::ByeNotificationDispatcher & _byeDispatcher;
	Types::HelloNotificationDispatcher & _helloDispatcher;
	Types::ProbeMatchNotificationDispatcher & _probeMatchDispatcher;
	Types::ResolveMatchNotificationDispatcher & _resolveDispatcher;

	const Poco::Net::SocketAddress _ipv4MulticastAddress;
	const Poco::Net::SocketAddress _ipv6MulticastAddress;
	const Poco::Net::SocketAddress _ipv4BindingAddress;
	const Poco::Net::SocketAddress _ipv6BindingAddress;
	Poco::Net::MulticastSocket _ipv4MulticastListeningSocket;
	Poco::Net::MulticastSocket _ipv6MulticastListeningSocket;

	std::map<Poco::Net::DatagramSocket, Poco::NotificationQueue> _socketSendMessageQueue;

	MessagingContext context;

	Poco::Thread _reactorThread;
	Poco::Net::SocketReactor _reactor;
};

class DPWSDiscoveryHostSocketImpl {
public:
	DPWSDiscoveryHostSocketImpl(
			Types::ProbeNotificationDispatcher & probeDispatcher,
			Types::ResolveNotificationDispatcher & resolveDispatcher) :
		_probeDispatcher(probeDispatcher),
		_resolveDispatcher(resolveDispatcher),
		_ipv4MulticastAddress(Poco::Net::SocketAddress(UDP_MULTICAST_IP_V4, UPD_MULTICAST_DISCOVERY_PORT)),
		_ipv6MulticastAddress(Poco::Net::SocketAddress (UDP_MULTICAST_IP_V6, UPD_MULTICAST_DISCOVERY_PORT)),
		_ipv4BindingAddress(Poco::Net::SocketAddress(Poco::Net::IPAddress(Poco::Net::IPAddress::Family::IPv4), _ipv4MulticastAddress.port())),
		_ipv6BindingAddress(Poco::Net::SocketAddress (Poco::Net::IPAddress(Poco::Net::IPAddress::Family::IPv6), _ipv6MulticastAddress.port())),
		_ipv4MulticastListeningSocket(Poco::Net::MulticastSocket(_ipv4BindingAddress.family())),
		_ipv6MulticastListeningSocket(Poco::Net::MulticastSocket(_ipv6MulticastAddress.family())),
		_generator(std::chrono::system_clock::now().time_since_epoch().count()),
		_distribution(0, APP_MAX_DELAY)
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
				_ipv6MulticastListeningSocket.joinGroup(_ipv6MulticastAddress.host(), nextIf);
				Poco::Net::DatagramSocket datagramSocket(Poco::Net::SocketAddress(nextIf.firstAddress(Poco::Net::IPAddress::Family::IPv6), 0), true);
				datagramSocket.setBlocking(false);
				_socketSendMessageQueue[datagramSocket].clear();
			}
		}
		_ipv6MulticastListeningSocket.setBlocking(false);

		_reactor.addEventHandler(_ipv4MulticastListeningSocket, Poco::Observer<DPWSDiscoveryHostSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSDiscoveryHostSocketImpl::onMulticastSocketReadable));
		_reactor.addEventHandler(_ipv6MulticastListeningSocket, Poco::Observer<DPWSDiscoveryHostSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSDiscoveryHostSocketImpl::onMulticastSocketReadable));

		_reactor.addEventHandler(_ipv4MulticastListeningSocket, Poco::Observer<DPWSDiscoveryHostSocketImpl, Poco::Net::TimeoutNotification>(*this, &DPWSDiscoveryHostSocketImpl::onTimeOut));
		_reactor.addEventHandler(_ipv6MulticastListeningSocket, Poco::Observer<DPWSDiscoveryHostSocketImpl, Poco::Net::TimeoutNotification>(*this, &DPWSDiscoveryHostSocketImpl::onTimeOut));

		_reactorThread.start(_reactor);
	}

	~DPWSDiscoveryHostSocketImpl() {
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

	void sendBye(const Types::ByeType & bye) {
		WS::MESSAGEMODEL::DISCOVERY::Envelope message(buildByeMessage(bye));
		WS::MESSAGEMODEL::DISCOVERY::Envelope::HeaderType::AppSequenceType appSequence(context.getInstanceId(), context.getNextMessageCounter());
		message.Header().AppSequence(appSequence);
		if (message.Header().MessageID().present()) {
			context.registerMessageId(message.Header().MessageID().get());
		}
		for (auto & socketQueue : _socketSendMessageQueue) {
			socketQueue.second.enqueueNotification(new SendMulticastMessage(serializeMessage(message)));
			_reactor.addEventHandler(socketQueue.first, Poco::Observer<DPWSDiscoveryHostSocketImpl, Poco::Net::WritableNotification>(*this, &DPWSDiscoveryHostSocketImpl::onDatagrammSocketWritable));
		}
	}

	void sendHello(const Types::HelloType & hello) {
		context.resetInstanceId();
		WS::MESSAGEMODEL::DISCOVERY::Envelope message(buildHelloMessage(hello));
		WS::MESSAGEMODEL::DISCOVERY::Envelope::HeaderType::AppSequenceType appSequence(context.getInstanceId(), context.getNextMessageCounter());
		message.Header().AppSequence(appSequence);
		if (message.Header().MessageID().present()) {
			context.registerMessageId(message.Header().MessageID().get());
		}
		for (auto & socketQueue : _socketSendMessageQueue) {
			socketQueue.second.enqueueNotification(new SendMulticastMessage(serializeMessage(message)));
			_reactor.addEventHandler(socketQueue.first, Poco::Observer<DPWSDiscoveryHostSocketImpl, Poco::Net::WritableNotification>(*this, &DPWSDiscoveryHostSocketImpl::onDatagrammSocketWritable));
		}
	}

private:
	void onMulticastSocketReadable(Poco::Net::ReadableNotification * notification) {
		const Poco::AutoPtr<Poco::Net::ReadableNotification> pNf(notification);
		Poco::Net::MulticastSocket socket(pNf->socket());
		const int available(socket.available());
		if (available == 0) {
			return;
		}

		Poco::Buffer<char> buf(available);
		Poco::Net::SocketAddress remoteAddr;
		const int received(socket.receiveFrom(buf.begin(), available, remoteAddr, 0));
		Helpers::BufferAdapter adapter(buf, received);
		std::unique_ptr<WS::MESSAGEMODEL::DISCOVERY::Envelope> requestMessage(parseMessage(adapter));

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
			std::vector<Types::ProbeMatchType> result(_probeDispatcher.dispatch(probe));
			if (result.empty()) {
				return;
			}
			const WS::MESSAGEMODEL::DISCOVERY::Envelope responseMessage(buildProbeMatchMessage(result, *requestMessage));
			_delayedMessages.enqueueNotification(new SendUnicastMessage(responseMessage, remoteAddr), createDelay());
		} else if (requestMessage->Body().Resolve().present()) {
			const WS::DISCOVERY::ResolveType & resolve(requestMessage->Body().Resolve().get());
			std::unique_ptr<Types::ResolveMatchType> result(_resolveDispatcher.dispatch(resolve));
			if (result == nullptr) {
				return;
			}
			const WS::MESSAGEMODEL::DISCOVERY::Envelope responseMessage(buildResolveMatchMessage(*result, *requestMessage));
			_delayedMessages.enqueueNotification(new SendUnicastMessage(responseMessage, remoteAddr), createDelay());
		}
		processDelayedMessages();
	}

	void onDatagrammSocketWritable(Poco::Net::WritableNotification * notification) {
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
				WS::MESSAGEMODEL::DISCOVERY::Envelope messageEnvelope(message->content);
				WS::MESSAGEMODEL::DISCOVERY::Envelope::HeaderType::AppSequenceType appSequence(context.getInstanceId(), context.getNextMessageCounter());
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

	void onTimeOut(Poco::Net::TimeoutNotification * notification) {
		const Poco::AutoPtr<Poco::Net::TimeoutNotification> pNf(notification);
		processDelayedMessages();
	}

	Poco::Timestamp createDelay() {
		return Poco::Timestamp() + Poco::Timespan(0, 0, 0, 0, _distribution(_generator));
	}

	void processDelayedMessages() {
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

	struct SendMulticastMessage : public Poco::Notification {
		SendMulticastMessage(const std::string & message) :
			content(message) {}
		const std::string content;
	};

	struct SendUnicastMessage : public Poco::Notification {
		SendUnicastMessage(const WS::MESSAGEMODEL::DISCOVERY::Envelope & message, const Poco::Net::SocketAddress & address) :
			content(message), address(address) {}
		const WS::MESSAGEMODEL::DISCOVERY::Envelope content;
		const Poco::Net::SocketAddress address;
	};

	Types::ProbeNotificationDispatcher & _probeDispatcher;
	Types::ResolveNotificationDispatcher & _resolveDispatcher;

	const Poco::Net::SocketAddress _ipv4MulticastAddress;
	const Poco::Net::SocketAddress _ipv6MulticastAddress;
	const Poco::Net::SocketAddress _ipv4BindingAddress;
	const Poco::Net::SocketAddress _ipv6BindingAddress;
	Poco::Net::MulticastSocket _ipv4MulticastListeningSocket;
	Poco::Net::MulticastSocket _ipv6MulticastListeningSocket;

	std::map<Poco::Net::DatagramSocket, Poco::NotificationQueue> _socketSendMessageQueue;
	Poco::TimedNotificationQueue _delayedMessages;
	std::default_random_engine _generator;
	std::uniform_int_distribution<unsigned int> _distribution;

	MessagingContext context;

	Poco::Thread _reactorThread;
	Poco::Net::SocketReactor _reactor;
};

}

class Client :
		public Types::ByeNotificationDispatcher,
		public Types::HelloNotificationDispatcher,
		public Types::ProbeMatchNotificationDispatcher,
		public Types::ResolveMatchNotificationDispatcher
{
public:
	Client() :
		_impl(new Impl::DPWSDiscoveryClientSocketImpl(*this, *this, *this, *this))
	{
	}
	virtual ~Client() = default;

	struct ByeCallback {
		virtual void bye(const Types::ByeType & notification) = 0;
	};

	struct HelloCallback {
		virtual void hello(const Types::HelloType & notification) = 0;
	};

	struct ProbeMatchCallback {
		virtual void probeMatch(const Types::ProbeMatchType & notification) = 0;
	};

	struct ResolveMatchCallback {
		virtual void resolveMatch(const Types::ResolveMatchType & notification) = 0;
	};

	void addProbeMatchEventHandler(const Types::ProbeType & filter, ProbeMatchCallback & callback) {
		std::lock_guard<std::mutex> lock(_mutex);
		_probeMatchHandlers.push_back(ProbeMatchHandler(filter, &callback));
		_impl->sendProbe(filter);
	}

	void removeProbeMatchEventHandler(ProbeMatchCallback & callback) {
		std::lock_guard<std::mutex> lock(_mutex);
		auto iterator = std::find_if(_probeMatchHandlers.begin(), _probeMatchHandlers.end(), [&](const ProbeMatchHandler & handler) { return std::get<1>(handler) == &callback; } );
		if (iterator != _probeMatchHandlers.end()) {
			_probeMatchHandlers.erase(iterator);
		}
	}

	void addResolveMatchEventHandler(const Types::ResolveType & filter, ResolveMatchCallback & callback) {
		std::lock_guard<std::mutex> lock(_mutex);
		_resolveMatchHandlers.push_back(ResolveMatchHandler(filter, &callback));
		_impl->sendResolve(filter);
	}

	void removeResolveMatchEventHandler(ResolveMatchCallback & callback) {
		std::lock_guard<std::mutex> lock(_mutex);
		auto iterator = std::find_if(_resolveMatchHandlers.begin(), _resolveMatchHandlers.end(), [&](const ResolveMatchHandler & handler) { return std::get<1>(handler) == &callback; } );
		if (iterator != _resolveMatchHandlers.end()) {
			_resolveMatchHandlers.erase(iterator);
		}
	}

	void addHelloEventHandler(HelloCallback & callback) {
		std::lock_guard<std::mutex> lock(_mutex);
		_helloHandlers.push_back(&callback);
	}

	void removeHelloEventHandler(HelloCallback & callback) {
		std::lock_guard<std::mutex> lock(_mutex);
		auto iterator = std::find(_helloHandlers.begin(), _helloHandlers.end(), &callback);
		if (iterator != _helloHandlers.end()) {
			_helloHandlers.erase(iterator);
		}
	}

	void addByeEventHandler(ByeCallback & callback) {
		std::lock_guard<std::mutex> lock(_mutex);
		_byeHandlers.push_back(&callback);
	}

	void removeByeEventHandler(ByeCallback & callback) {
		std::lock_guard<std::mutex> lock(_mutex);
		auto iterator = std::find(_byeHandlers.begin(), _byeHandlers.end(), &callback);
		if (iterator != _byeHandlers.end()) {
			_byeHandlers.erase(iterator);
		}
	}

private:
	virtual void dispatch(const Types::ProbeMatchType & notification) override {
		std::lock_guard<std::mutex> lock(_mutex);
		std::vector<ProbeMatchHandler> matchingHandlers;
		for (const auto & handler : _probeMatchHandlers) {
			if (Impl::compare(std::get<0>(handler), notification)) {
				matchingHandlers.push_back(handler);
			}
		};
		for (const auto & handler : matchingHandlers) {
			std::get<1>(handler)->probeMatch(notification);
		}
	}

	virtual void dispatch(const Types::ResolveMatchType & notification) override {
		std::lock_guard<std::mutex> lock(_mutex);
		std::vector<ResolveMatchHandler> matchingHandlers;
		for (const auto & handler : _resolveMatchHandlers) {
			if (Impl::compare(std::get<0>(handler), notification)) {
				matchingHandlers.push_back(handler);
			}
		};
		for (const auto & handler : matchingHandlers) {
			std::get<1>(handler)->resolveMatch(notification);
		}
	}

	virtual void dispatch(const Types::ByeType & notification) override {
		std::lock_guard<std::mutex> lock(_mutex);
		for (auto & callback : _byeHandlers) {
			callback->bye(notification);
		}
	}

	virtual void dispatch(const Types::HelloType & notification) override {
		std::lock_guard<std::mutex> lock(_mutex);
		for (auto & callback : _helloHandlers) {
			callback->hello(notification);
		}
	}

	typedef std::tuple<Types::ProbeType, ProbeMatchCallback *> ProbeMatchHandler;
	typedef std::tuple<Types::ResolveType, ResolveMatchCallback *> ResolveMatchHandler;
	std::vector<ProbeMatchHandler> _probeMatchHandlers;
	std::vector<ResolveMatchHandler> _resolveMatchHandlers;
	std::vector<HelloCallback*> _helloHandlers;
	std::vector<ByeCallback*> _byeHandlers;

	mutable std::mutex _mutex;

	std::unique_ptr<Impl::DPWSDiscoveryClientSocketImpl> _impl;
};

class Host :
		public Types::ProbeNotificationDispatcher,
		public Types::ResolveNotificationDispatcher
{
public:
	Host(const Types::AddressType & epr,
			const Types::ScopesType & scopes = Types::ScopesType(),
			const Types::TypesType & types = Types::TypesType(),
			const Types::XAddressesType & xaddresses = Types::XAddressesType(),
			int metadataVersion = 1) :
		_started(false),
		_epr(epr),
		_scopes(scopes),
		_types(types),
		_xaddresses(xaddresses),
		_metadataVersion(metadataVersion),
		_impl(new Impl::DPWSDiscoveryHostSocketImpl(*this, *this))
	{
	}
	virtual ~Host() = default;

	void start() {
		_started = true;
		sendHello();
	}

	void stop() {
		Types::EndpointReferenceType epr(_epr);
		Types::ByeType bye(epr);
		_impl->sendBye(bye);
		_started = false;
	}

	void setScopes(const Types::ScopesType & scopes) {
		_scopes = scopes;
		++_metadataVersion;
		sendHello();
	}

	void setTypes(const Types::TypesType & types) {
		_types.clear();
		std::copy(types.begin(), types.end(), std::back_inserter(_types));
		++_metadataVersion;
		sendHello();
	}

	void setXAddresses(const Types::XAddressesType & xaddresses) {
		_xaddresses = xaddresses;
		++_metadataVersion;
		sendHello();
	}

private:
	void sendHello() {
		if (not _started) {
			return;
		}
		Types::HelloType hello(
				_epr,
				_metadataVersion);
		if (not _scopes.empty()) {
			hello.Scopes(_scopes);
		}
		if (not _types.empty()) {
			hello.Types(_types);
		}
		if (not _xaddresses.empty()) {
			hello.XAddrs(_xaddresses);
		}
		_impl->sendHello(hello);
	}

	virtual std::vector<Types::ProbeMatchType> dispatch(const Types::ProbeType & filter) override {
		Types::ProbeMatchType match(_epr, _metadataVersion);
		if (not _scopes.empty()) {
			match.Scopes(_scopes);
		}
		if (not _types.empty()) {
			match.Types(_types);
		}
		if (not _xaddresses.empty()) {
			match.XAddrs(_xaddresses);
		}
		std::vector<Types::ProbeMatchType> result;
		if (not Impl::compare(filter, match)) {
			return result;
		} else {
			result.push_back(match);
			return result;
		}
	}

	virtual std::unique_ptr<Types::ResolveMatchType> dispatch(const Types::ResolveType & filter) override {
		std::unique_ptr<Types::ResolveMatchType> result(new Types::ResolveMatchType(_epr, _metadataVersion));
		if (not _scopes.empty()) {
			result->Scopes(_scopes);
		}
		if (not _types.empty()) {
			result->Types(_types);
		}
		if (not _xaddresses.empty()) {
			result->XAddrs(_xaddresses);
		}
		if (not Impl::compare(filter, *result)) {
			return nullptr;
		} else {
			return result;
		}
	}

	bool _started;
	const Types::AddressType _epr;
	Types::ScopesType _scopes;
	Types::TypesType _types;
	Types::XAddressesType _xaddresses;
	int _metadataVersion;

	std::unique_ptr<Impl::DPWSDiscoveryHostSocketImpl> _impl;
};

}

/* Example usage of Discovery host.
	Host host(AddressType("UDI_123456"));
	XAddressesType dummyAddresses;
	dummyAddresses.push_back(AddressType("http://some.server:1234"));
	host.setXAddresses(dummyAddresses);
	host.start();

	host.stop();
 */

int main() {

	using DPWSDiscovery::Client;
	using DPWSDiscovery::Host;
	using namespace DPWSDiscovery::Types;

	struct ProbeMatchCallback : public Client::ProbeMatchCallback  {
		ProbeMatchCallback(Poco::Timestamp & time) : _time(time) {}
		virtual ~ProbeMatchCallback() = default;

		virtual void probeMatch(const ProbeMatchType & n) override {
			std::cout << "Response after " << Poco::DateTimeFormatter::format(Poco::Timespan(_time.elapsed()), "%s:%i") << " s:ms." << std::endl;
			std::cout << n << std::endl;
		}

		Poco::Timestamp & _time;
	};

	struct ByeCallback : public Client::ByeCallback {
		ByeCallback() {}
		virtual ~ByeCallback() = default;

		virtual void bye(const ByeType & n) override {
			std::cout << n << std::endl;
		}
	};

	struct HelloCallback : public Client::HelloCallback {
		HelloCallback() {}
		virtual ~HelloCallback() = default;

		virtual void hello(const HelloType & n) override {
			std::cout << n << std::endl;
		}
	};

	ByeCallback byeCb;
	HelloCallback helloCb;

	std::cout << "Listening for DPWS discovery messages ..." << std::endl;
	Client client;
	client.addByeEventHandler(byeCb);
	client.addHelloEventHandler(helloCb);

	/* Example for Resolving an EPR


	struct ResolveMatchCallback : public Client::ResolveMatchCallback  {
		ResolveMatchCallback() {}
		virtual ~ResolveMatchCallback() = default;

		virtual void resolveMatch(const ResolveMatchType & n) override {
			std::cout << n << std::endl;
		}
	};

	ResolveMatchCallback resolveCb;

	while (true) {
		ResolveType resolveFilter(WS::ADDRESSING::EndpointReferenceType(WS::ADDRESSING::AttributedURIType("UDI-PUMP-157Propofol")));
		std::cout << "Resolving ..." << std::endl;
		client.addResolveMatchEventHandler(resolveFilter, resolveCb);
		Poco::Thread::sleep(10000);
		client.removeResolveMatchEventHandler(resolveCb);
		std::cout << "Resolving done." << std::endl;
	}*/

	while (true) {
		std::cout << "Probing ..." << std::endl;

		ProbeType probeFilter;
		//i.e. probeFilter.types.emplace_back("http://ornet.org/sm/14/06", "MedicalDevice");

		Poco::Timestamp started;
		ProbeMatchCallback probeCb(started);
		
		client.addProbeMatchEventHandler(probeFilter, probeCb);
		Poco::Thread::sleep(10000);
		client.removeProbeMatchEventHandler(probeCb);
		std::cout << "Probing done." << std::endl;
	}

	client.removeHelloEventHandler(helloCb);
	client.removeByeEventHandler(byeCb);
}

