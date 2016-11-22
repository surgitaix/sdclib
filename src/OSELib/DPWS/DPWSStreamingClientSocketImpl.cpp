/*
 * DPWSStreamingClientSocketImpl.cpp
 *
 *  Created on: Nov 3, 2016
 *      Author: sebastian
 */

#include <iostream>

#include "Poco/Buffer.h"
#include "Poco/UUIDGenerator.h"
#include "Poco/Net/SocketAddress.h"

#include "NormalizedMessageModel.hxx"

#include "OSELib/DPWS/DPWSStreamingClientSocketImpl.h"
#include "OSELib/DPWS/DPWS11Constants.h"
#include "OSELib/DPWS/DPWSCommon.h"
#include "OSELib/Helper/BufferAdapter.h"

// todo: kick after dev
#include "OSCLib/Util/DebugOut.h"
using namespace OSCLib::Util;



//#include "OSELib/Helper/BufferAdapter.h"

namespace OSELib {
namespace DPWS {
namespace Impl {

//struct SendMulticastMessage : public Poco::Notification {
//	SendMulticastMessage(const std::string & message) :
//		content_(message) {}
//	const std::string content_;
//};


// todo: logger impl
// init addresses in constants
// WithLogger(Log::DISCOVERY)
//
//_ipv4MulticastAddress(Poco::Net::SocketAddress(OSELib::UDP_MULTICAST_DISCOVERY_IP_V4, OSELib::UPD_MULTICAST_DISCOVERY_PORT)),
//	_ipv6MulticastAddress(Poco::Net::SocketAddress (OSELib::UDP_MULTICAST_DISCOVERY_IP_V6, OSELib::UPD_MULTICAST_DISCOVERY_PORT)),
//	_ipv4BindingAddress(Poco::Net::SocketAddress(Poco::Net::IPAddress(Poco::Net::IPAddress::Family::IPv4), _ipv4MulticastAddress.port())),
//	_ipv6BindingAddress(Poco::Net::SocketAddress (Poco::Net::IPAddress(Poco::Net::IPAddress::Family::IPv6), _ipv6MulticastAddress.port())),
//	m_ipv4MulticastSocket(Poco::Net::MulticastSocket(_ipv4BindingAddress.family())),
//	_ipv6MulticastDiscoverySocket(Poco::Net::MulticastSocket(_ipv6BindingAddress.family()))

DPWSStreamingClientSocketImpl::DPWSStreamingClientSocketImpl(StreamNotificationDispatcher & streamNotificationDispatcher, const DeviceDescription & deviceDescription):
		m_streamNotificationDispatcher(streamNotificationDispatcher),
		m_deviceDescription(deviceDescription)
{
	xercesc::XMLPlatformUtils::Initialize ();

	// todo:
		// implementation of streaming multicast
		// testwise

//		const Poco::Net::SocketAddress m_ipv4MulticastAddress("239.239.239.235", 5555); // make member vars

	// only open a streaming socket, if the provider is providing a streaming service
	if (!m_deviceDescription.getStreamMulticastAddressURIs().empty()) {
		m_ipv4MulticastAddress = Poco::Net::SocketAddress(m_deviceDescription.getStreamMulticastAddressURIs().front().getHost(), m_deviceDescription.getStreamMulticastAddressURIs().front().getPort());

		const Poco::Net::SocketAddress _ipv4MulticastStreamingBindingAddress(Poco::Net::IPAddress(Poco::Net::IPAddress::Family::IPv4), m_ipv4MulticastAddress.port()); // make member vars
		m_ipv4MulticastSocket = Poco::Net::MulticastSocket(_ipv4MulticastStreamingBindingAddress.family());

		m_ipv4MulticastSocket.bind(m_ipv4MulticastAddress, true);
		// bind all network adapters to socket
		for (const auto & nextIf : Poco::Net::NetworkInterface::list()) {
			if (nextIf.supportsIPv4()
				&& !nextIf.address().isLoopback()
				&& nextIf.address().isUnicast()) { // devices network adapters have a unicast IP
				m_ipv4MulticastSocket.joinGroup(m_ipv4MulticastAddress.host(), nextIf);
			}
		}
		m_ipv4MulticastSocket.setBlocking(false);




		_reactor.addEventHandler(m_ipv4MulticastSocket, Poco::Observer<DPWSStreamingClientSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSStreamingClientSocketImpl::onMulticastSocketReadable));

		_reactorThread.start(_reactor);
	} else {
		DebugOut(DebugOut::Default, std::cerr, "DPWSStreamingClilentSocketImpl") << "No streaming service.\n";
	}
}

DPWSStreamingClientSocketImpl::~DPWSStreamingClientSocketImpl() {
//	_reactor.removeEventHandler(m_ipv4MulticastSocket, Poco::Observer<DPWSStreamingClientSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSStreamingClientSocketImpl::onMulticastSocketReadable));

//	for (auto & messagingSocketMapping : _socketSendMessageQueue) {
//		_reactor.removeEventHandler(messagingSocketMapping.first, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onDatagrammSocketReadable));
//		_reactor.removeEventHandler(messagingSocketMapping.first, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::WritableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onDatagrammSocketWritable));
//	}

	_reactor.stop();
	_reactorThread.join();

	xercesc::XMLPlatformUtils::Terminate ();
}

void DPWSStreamingClientSocketImpl::onMulticastSocketReadable(Poco::Net::ReadableNotification * notification) {

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

	if (message == nullptr
		|| !message->Header().MessageID().present() ) {
//		|| !message->Header().From().present() // todo: add later
		return;
	}

	if (message->Body().WaveformStream().present()) {
//			if (not verifyHello(*message)) {
//				return;
//			}

//		auto helper = message->Body().WaveformStream().get().RealTimeSampleArray().front().ObservedValue().get().Samples().get();
//		RealTimeSampleArrayMetricState

//		auto helper = message->Body().WaveformStream().get().RealTimeSampleArray().front();
		m_streamNotificationDispatcher.dispatch(message->Body().WaveformStream().get());



//		DebugOut(DebugOut::Default, std::cerr, "streamoscp") << helper[10];
	}

}


} /* namespace Impl */
} /* namespace DPWS */
} /* namespace OSELib */


