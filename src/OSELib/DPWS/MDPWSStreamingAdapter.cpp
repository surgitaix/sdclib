/*
 * MDPWSStreamingAdapter.cpp
 *
 *  Created on: Nov 3, 2016
 *      Author: sebastian
 */

#include <iostream>

#include "Poco/Buffer.h"
#include "Poco/UUIDGenerator.h"
#include "Poco/Net/SocketAddress.h"

#include "NormalizedMessageModel.hxx"

#include "OSELib/DPWS/MDPWSStreamingAdapter.h"
#include "OSELib/DPWS/DPWS11Constants.h"
#include "OSELib/DPWS/DPWSCommon.h"
#include "OSELib/Helper/BufferAdapter.h"

#include "OSCLib/Data/SDC/MDIB/RealTimeSampleArrayMetricState.h"

#include "OSCLib/SDCInstance.h"


using namespace OSELib::DPWS::Impl;

MDPWSStreamingAdapter::MDPWSStreamingAdapter(SDCLib::SDCInstance_shared_ptr p_SDCInstance, StreamNotificationDispatcher & streamNotificationDispatcher, const DeviceDescription & deviceDescription):
	WithLogger(Log::DISCOVERY),
    m_SDCInstance(p_SDCInstance),
	m_streamNotificationDispatcher(streamNotificationDispatcher),
	m_deviceDescription(deviceDescription)
{
	xercesc::XMLPlatformUtils::Initialize();
	// todo: implement ipv6
    // only open a streaming socket, if the provider is providing a streaming service
    // BUT: BIND IT TO THE SDC INSTANCE ADDRESS!
    if (!m_deviceDescription.getStreamMulticastAddressURIs().empty()) {
        if ( m_SDCInstance->getIP4enabled() ) {
            log_debug([&] {return "Host:" + m_deviceDescription.getStreamMulticastAddressURIs().front().getHost() + "Port: " + std::to_string(m_deviceDescription.getStreamMulticastAddressURIs().front().getPort());});
            //m_ipv4MulticastAddress = Poco::Net::SocketAddress(m_deviceDescription.getStreamMulticastAddressURIs().front().getHost(), m_deviceDescription.getStreamMulticastAddressURIs().front().getPort());
            m_ipv4MulticastAddress = Poco::Net::SocketAddress(m_SDCInstance->_getStreamingIPv4(), m_SDCInstance->_getStreamingPortv4());

            // Bind only interfaces we specified
            if (m_SDCInstance->isBound()) {
                m_ipv4MulticastSocket = Poco::Net::MulticastSocket(Poco::Net::IPAddress::Family::IPv4);
                for (auto t_interface : m_SDCInstance->getNetworkInterfaces()) {
                    try {
                        auto t_ipv4MulticastStreamingBindingAddress = Poco::Net::SocketAddress(Poco::Net::IPAddress::Family::IPv4, m_ipv4MulticastAddress.port());
                        m_ipv4MulticastSocket.bind(m_ipv4MulticastAddress, t_interface->SO_REUSEADDR_FLAG, t_interface->SO_REUSEPORT_FLAG);
                        m_ipv4MulticastSocket.joinGroup(m_ipv4MulticastAddress.host(), t_interface->m_if);
                    } catch (...) {
                      // todo fixme. This loop fails, when a network interface has several network addresses, i.e. 2 IPv6 global scoped addresses
                      log_error([&] { return "Another thing went wrong"; });
                    }
                }
            }
            else {
                // bind all network adapters to socket
                for (const auto & nextIf : Poco::Net::NetworkInterface::list()) {
                    // devices network adapters have a unicast IP
                    if (nextIf.supportsIPv4() && !nextIf.address().isLoopback() && nextIf.address().isUnicast()) {
                            // make member vars
                            const Poco::Net::SocketAddress _ipv4MulticastStreamingBindingAddress(nextIf.firstAddress(Poco::Net::IPAddress::Family::IPv4), m_ipv4MulticastAddress.port());
                            m_ipv4MulticastSocket = Poco::Net::MulticastSocket(_ipv4MulticastStreamingBindingAddress.family());
                            m_ipv4MulticastSocket.bind(m_ipv4MulticastAddress, true);
                            m_ipv4MulticastSocket.joinGroup(m_ipv4MulticastAddress.host(), nextIf);
                          }
                  }
            }
			m_ipv4MulticastSocket.setBlocking(false);
		}
        if ( m_SDCInstance->getIP6enabled() )
				{
//			m_deviceDescription.getStreamMulticastAddressURIs().front().
//					DebugOut(DebugOut::Default, std::cerr, "streamsdc") << "Host IPv6:" + m_deviceDescription.getStreamMulticastAddressURIs().front().getHost() << "Port: " + m_deviceDescription.getStreamMulticastAddressURIs().front().getPort() << std::endl;
//					m_ipv4MulticastAddress = Poco::Net::SocketAddress(m_deviceDescription.getStreamMulticastAddressURIs().front().getHost(), m_deviceDescription.getStreamMulticastAddressURIs().front().getPort());
//
//					const Poco::Net::SocketAddress _ipv4MulticastStreamingBindingAddress(Poco::Net::IPAddress(Poco::Net::IPAddress::Family::IPv4), m_ipv4MulticastAddress.port()); // make member vars
//					m_ipv4MulticastSocket = Poco::Net::MulticastSocket(_ipv4MulticastStreamingBindingAddress.family());
//
//					m_ipv4MulticastSocket.bind(m_ipv4MulticastAddress, true);
//					// bind all network adapters to socket
//					for (const auto & nextIf : Poco::Net::NetworkInterface::list()) {
//						if (nextIf.supportsIPv4()
//							&& !nextIf.address().isLoopback()
//							&& nextIf.address().isUnicast()) { // devices network adapters have a unicast IP
//							m_ipv4MulticastSocket.joinGroup(m_ipv4MulticastAddress.host(), nextIf);
//						}
//					}
//					m_ipv4MulticastSocket.setBlocking(false);
				}


		_reactor.addEventHandler(m_ipv4MulticastSocket, Poco::Observer<MDPWSStreamingAdapter, Poco::Net::ReadableNotification>(*this, &MDPWSStreamingAdapter::onMulticastSocketReadable));

		_reactorThread.start(_reactor);
	}
}

MDPWSStreamingAdapter::~MDPWSStreamingAdapter() {
	if (!m_deviceDescription.getStreamMulticastAddressURIs().empty()) {
		_reactor.removeEventHandler(m_ipv4MulticastSocket, Poco::Observer<MDPWSStreamingAdapter, Poco::Net::ReadableNotification>(*this, &MDPWSStreamingAdapter::onMulticastSocketReadable));
	}

//	for (auto & messagingSocketMapping : _socketSendMessageQueue) {
//		_reactor.removeEventHandler(messagingSocketMapping.first, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::ReadableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onDatagrammSocketReadable));
//		_reactor.removeEventHandler(messagingSocketMapping.first, Poco::Observer<DPWSDiscoveryClientSocketImpl, Poco::Net::WritableNotification>(*this, &DPWSDiscoveryClientSocketImpl::onDatagrammSocketWritable));
//	}

	_reactor.stop();
	_reactorThread.join();

	xercesc::XMLPlatformUtils::Terminate ();
}

void MDPWSStreamingAdapter::onMulticastSocketReadable(Poco::Net::ReadableNotification * notification) {

	const Poco::AutoPtr<Poco::Net::ReadableNotification> pNf(notification);

	Poco::Net::MulticastSocket socket(pNf->socket());
	const int available(socket.available());
	if (available == 0) {
		return;
	}
    // Only read if this belongs to this SDCInstance!
    if (!m_SDCInstance->belongsToSDCInstance(socket.address().host())) {
        return;
    }

	Poco::Buffer<char> buf(available);
	Poco::Net::SocketAddress remoteAddr;
	const int received(socket.receiveFrom(buf.begin(), available, remoteAddr, 0));
	Helper::BufferAdapter adapter(buf, received);
	std::unique_ptr<MESSAGEMODEL::Envelope> message(parseMessage(adapter));

	if (message == nullptr
		|| !message->Header().MessageID().present()
		|| !message->Body().WaveformStream().present()) {
		log_error([&]{return "Message is invalid";});
		return;
	}


	if (!message->Header().From().present()) {
		log_warning([&]{return "From-field in streaming message does not exist";});
		m_streamNotificationDispatcher.dispatch(message->Body().WaveformStream().get());
	} else {
		if (message->Header().From().get().Address() == m_deviceDescription.getEPR()) {
			m_streamNotificationDispatcher.dispatch(message->Body().WaveformStream().get());
		} else {
			log_error([&]{return "Message has wrong endpoint reference. Message not dispatched.";});
		}
	}
}

