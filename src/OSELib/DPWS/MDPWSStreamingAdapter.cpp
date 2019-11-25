/*
 * MDPWSStreamingAdapter.cpp
 *
 *  Created on: 03.11.2016, buerger
 *  Modified on: 23.08.2019, baumeister
 *
 */

#include "OSELib/DPWS/MDPWSStreamingAdapter.h"
#include "SDCLib/Config/NetworkConfig.h"
#include "OSELib/DPWS/DPWSCommon.h"
#include "OSELib/Helper/BufferAdapter.h"
#include "OSELib/DPWS/DeviceDescription.h"

#include "DataModel/NormalizedMessageModel.hxx"

#include <Poco/Net/SocketNotification.h>

using namespace OSELib;
using namespace OSELib::DPWS;
using namespace OSELib::DPWS::Impl;

MDPWSStreamingAdapter::MDPWSStreamingAdapter(SDCLib::Config::NetworkConfig_shared_ptr p_config, StreamNotificationDispatcher & streamNotificationDispatcher, DeviceDescription_shared_ptr p_deviceDescription) :
	OSELib::Helper::WithLogger(Log::DISCOVERY),
	m_networkConfig(p_config),
	m_streamNotificationDispatcher(streamNotificationDispatcher),
	m_deviceDescription(p_deviceDescription),
	m_ipv4MulticastAddress(Poco::Net::SocketAddress(p_config->_getStreamingIPv4(), p_config->_getStreamingPortv4())),
	m_ipv6MulticastAddress(Poco::Net::SocketAddress(p_config->_getStreamingIPv6(), p_config->_getStreamingPortv6()))
{
	assert(p_deviceDescription != nullptr);

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
            for (const auto & t_nextIf : Poco::Net::NetworkInterface::list()) {
                if (t_nextIf.supportsIPv4() && !t_nextIf.address().isLoopback() && t_nextIf.address().isUnicast()) {
                    try
                    {
                        // Interface - Join group: Note: Fails if we enumerate a bridge that is already connected
                        m_ipv4MulticastSocket.joinGroup(m_ipv4MulticastAddress.host(), t_nextIf);
                    }
                    catch (...) {
                        log_error([&] { return "Something went wrong in binding to : " + t_nextIf.adapterName(); });
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
            for (const auto & t_nextIf : Poco::Net::NetworkInterface::list()) {
                // devices network adapters have a unicast IP
                if (t_nextIf.supportsIPv6() && !t_nextIf.address().isLoopback() && t_nextIf.address().isUnicast()) {
                    try
                    {
                        // Interface - Join group: Note: Fails if we enumerate a bridge that is already connected
                        m_ipv6MulticastSocket.joinGroup(m_ipv6MulticastAddress.host(), t_nextIf);
                    }
                    catch (...) {
                        log_error([&] { return "Something went wrong in binding to : " + t_nextIf.adapterName(); });
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

    // Start the Thread with the SocketReactor
    m_reactorThread.start(m_reactor);
}

MDPWSStreamingAdapter::~MDPWSStreamingAdapter()
{
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
}

void MDPWSStreamingAdapter::onMulticastSocketReadable(Poco::Net::ReadableNotification * p_notification)
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
	auto t_message(parseMessage(t_adapter));

	if (nullptr == t_message
		|| !t_message->getHeader().getMessageID().present()
		|| !t_message->getBody().getWaveformStream().present()) {
		log_error([]{return "Message is invalid";});
		return;
	}


	if (!t_message->getHeader().getFrom().present()) {
		log_warning([]{return "From-field in streaming message does not exist";});
		m_streamNotificationDispatcher.dispatch(t_message->getBody().getWaveformStream().get());
	} else {
		if((m_deviceDescription == nullptr)) {
			log_error([]{return "Invalid device Description! Message not dispatched.";});
			return;
		}
		if (t_message->getHeader().getFrom().get().getAddress() == m_deviceDescription->getEPR()) {
			m_streamNotificationDispatcher.dispatch(t_message->getBody().getWaveformStream().get());
		} else {
			log_error([]{return "Message has wrong endpoint reference. Message not dispatched.";});
		}
	}
}

