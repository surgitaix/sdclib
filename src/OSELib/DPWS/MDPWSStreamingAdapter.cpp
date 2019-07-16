/*
 * MDPWSStreamingAdapter.cpp
 *
 *  Created on: Nov 3, 2016
 *      Author: sebastian, baumeister
 */

#include "OSELib/DPWS/MDPWSStreamingAdapter.h"
#include "SDCLib/Config/NetworkConfig.h"
#include "OSELib/DPWS/DPWSCommon.h"
#include "OSELib/Helper/BufferAdapter.h"

#include "NormalizedMessageModel.hxx"

using namespace OSELib;
using namespace OSELib::DPWS;
using namespace OSELib::DPWS::Impl;

MDPWSStreamingAdapter::MDPWSStreamingAdapter(SDCLib::Config::NetworkConfig_shared_ptr p_config, StreamNotificationDispatcher & streamNotificationDispatcher, const DeviceDescription & deviceDescription) :
	WithLogger(Log::DISCOVERY),
	m_networkConfig(p_config),
	m_streamNotificationDispatcher(streamNotificationDispatcher),
	m_deviceDescription(deviceDescription),
	m_ipv4MulticastAddress(Poco::Net::SocketAddress(p_config->_getStreamingIPv4(), p_config->_getStreamingPortv4())),
	m_ipv6MulticastAddress(Poco::Net::SocketAddress(p_config->_getStreamingIPv6(), p_config->_getStreamingPortv6()))
{
    if (m_networkConfig->getIP4enabled())
    {
        // Create MulticastSocket
        m_ipv4MulticastSocket = Poco::Net::MulticastSocket(Poco::Net::IPAddress::Family::IPv4);

        // Add only interfaces bound to this Config
        if (m_networkConfig->isBound()) {
            // Bind MulticastSocket
            auto t_bindingAddress = Poco::Net::SocketAddress(Poco::Net::IPAddress::Family::IPv4, m_ipv4MulticastAddress.port());
            m_ipv4MulticastSocket.bind(t_bindingAddress, m_SO_REUSEADDR_FLAG, m_SO_REUSEPORT_FLAG);
            for (auto t_interface : m_networkConfig->getNetworkInterfaces()) {
                try {
                    // Interface - Join group: Note: Fails if we enumerate a bridge that is already connected
                    m_ipv4MulticastSocket.joinGroup(m_ipv4MulticastAddress.host(), t_interface->m_if);
                }
                catch (...) {
                    log_error([&] { return "Something went wrong in binding to : " + t_interface->m_name; });
                    continue;
                }
            }
        }
        else {
            // Bind MulticastSocket
            const Poco::Net::SocketAddress t_bindingAddress(Poco::Net::IPAddress::Family::IPv4, m_ipv4MulticastAddress.port());
            m_ipv4MulticastSocket.bind(m_ipv4MulticastAddress, m_SO_REUSEADDR_FLAG, m_SO_REUSEPORT_FLAG);
            // Add all interfaces
            for (const auto & nextIf : Poco::Net::NetworkInterface::list()) {
                if (nextIf.supportsIPv4() && !nextIf.address().isLoopback() && nextIf.address().isUnicast()) {
                    try
                    {
                        // Interface - Join group: Note: Fails if we enumerate a bridge that is already connected
                        m_ipv4MulticastSocket.joinGroup(m_ipv4MulticastAddress.host(), nextIf);
                    }
                    catch (...) {
                        log_error([&] { return "Something went wrong in binding to : " + nextIf.adapterName(); });
                        continue;
                    }
                }
            }
        }
        // Nonblocking
        m_ipv4MulticastSocket.setBlocking(false);
        // Add Ipv4 Socket EventHandler
        m_reactor.addEventHandler(m_ipv4MulticastSocket, Poco::Observer<MDPWSStreamingAdapter, Poco::Net::ReadableNotification>(*this, &MDPWSStreamingAdapter::onMulticastSocketReadable));
    }
    if (m_networkConfig->getIP6enabled())
    {
        // Create MulticastSocket
        m_ipv6MulticastSocket = Poco::Net::MulticastSocket(Poco::Net::IPAddress::Family::IPv6);

        // Add only interfaces bound to this Config
        if (m_networkConfig->isBound()) {
            // Bind MulticastSocket
            auto t_bindingAddress = Poco::Net::SocketAddress(Poco::Net::IPAddress::Family::IPv6, m_ipv6MulticastAddress.port());
            m_ipv6MulticastSocket.bind(t_bindingAddress, m_SO_REUSEADDR_FLAG, m_SO_REUSEPORT_FLAG);
            for (auto t_interface : m_networkConfig->getNetworkInterfaces()) {
                try
                {
                    // Interface - Join group: Note: Fails if we enumerate a bridge that is already connected
                    m_ipv6MulticastSocket.joinGroup(m_ipv6MulticastAddress.host(), t_interface->m_if);
                }
                catch (...) {
                    log_error([&] { return "Something went wrong in binding to : " + t_interface->m_name; });
                    continue;
                }
            }
        }
        else {
            // Bind MulticastSocket
            const Poco::Net::SocketAddress t_bindingAddress(Poco::Net::IPAddress::Family::IPv6, m_ipv6MulticastAddress.port());
            m_ipv6MulticastSocket.bind(m_ipv6MulticastAddress, m_SO_REUSEADDR_FLAG, m_SO_REUSEPORT_FLAG);
            // Add all interfaces
            for (const auto & nextIf : Poco::Net::NetworkInterface::list()) {
                // devices network adapters have a unicast IP
                if (nextIf.supportsIPv6() && !nextIf.address().isLoopback() && nextIf.address().isUnicast()) {
                    try
                    {
                        // Interface - Join group: Note: Fails if we enumerate a bridge that is already connected
                        m_ipv6MulticastSocket.joinGroup(m_ipv6MulticastAddress.host(), nextIf);
                    }
                    catch (...) {
                        log_error([&] { return "Something went wrong in binding to : " + nextIf.adapterName(); });
                        continue;
                    }
                }
            }
        }
        // Nonblocking
        m_ipv6MulticastSocket.setBlocking(false);
        // Add Ipv6 Socket EventHandler
        m_reactor.addEventHandler(m_ipv6MulticastSocket, Poco::Observer<MDPWSStreamingAdapter, Poco::Net::ReadableNotification>(*this, &MDPWSStreamingAdapter::onMulticastSocketReadable));
    }

    xercesc::XMLPlatformUtils::Initialize();

    m_reactorThread.start(m_reactor);
}

MDPWSStreamingAdapter::~MDPWSStreamingAdapter() {
    m_reactor.removeEventHandler(m_ipv4MulticastSocket, Poco::Observer<MDPWSStreamingAdapter, Poco::Net::ReadableNotification>(*this, &MDPWSStreamingAdapter::onMulticastSocketReadable));
    m_reactor.removeEventHandler(m_ipv6MulticastSocket, Poco::Observer<MDPWSStreamingAdapter, Poco::Net::ReadableNotification>(*this, &MDPWSStreamingAdapter::onMulticastSocketReadable));

    for (auto t_interface : m_networkConfig->getNetworkInterfaces()) {
        try
        {
            if (m_networkConfig->getIP4enabled()) { m_ipv4MulticastSocket.leaveGroup(m_ipv4MulticastAddress.host(), t_interface->m_if); }
            if (m_networkConfig->getIP6enabled()) { m_ipv6MulticastSocket.leaveGroup(m_ipv6MulticastAddress.host(), t_interface->m_if); }
        }
        catch (...) {
            // todo fixme. This loop fails, when a network interface has serveral network addresses, i.e. 2 IPv6 global scoped addresses
            log_error([&] { return "Some thing went wrong leaving : " + t_interface->m_name; });
            continue;
        }
    }

	m_reactor.stop();
	m_reactorThread.join();

	xercesc::XMLPlatformUtils::Terminate ();
}

void MDPWSStreamingAdapter::onMulticastSocketReadable(Poco::Net::ReadableNotification * notification) {

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

