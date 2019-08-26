/*
 * DPWSHostSocketImpl.h
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 20.08.2019, baumeister
 */

#ifndef DPWS_DPWSDISCOVERYHOSTSOCKETIMPL_H_
#define DPWS_DPWSDISCOVERYHOSTSOCKETIMPL_H_


#include "SDCLib/Prerequisites.h"
#include "OSELib/DPWS/MessagingContext.h"
#include "OSELib/DPWS/Types.h"
#include "OSELib/Helper/WithLogger.h"

#include "DataModel/NormalizedMessageModel-fwd.hxx"

#include <map>
#include <random>

#include <Poco/NotificationQueue.h>
#include <Poco/TimedNotificationQueue.h>
#include <Poco/Thread.h>
#include <Poco/Net/MulticastSocket.h>
#include <Poco/Net/SocketNotification.h>
#include <Poco/Net/SocketReactor.h>


namespace OSELib
{
	namespace DPWS
	{
		namespace Impl
		{

			class DPWSHostSocketImpl : public OSELib::Helper::WithLogger
			{
			private:

				struct SendMulticastMessage;
				struct SendUnicastMessage;

				std::mutex m_mutex;

				SDCLib::Config::NetworkConfig_shared_ptr m_networkConfig = nullptr;
				ProbeNotificationDispatcher & m_probeDispatcher;
				ResolveNotificationDispatcher & m_resolveDispatcher;

				const Poco::Net::SocketAddress m_ipv4DiscoveryMulticastAddress;
				const Poco::Net::SocketAddress m_ipv6DiscoveryMulticastAddress;
				const Poco::Net::SocketAddress m_ipv4StreamMulticastAddress;
				const Poco::Net::SocketAddress m_ipv6StreamMulticastAddress;
				Poco::Net::MulticastSocket m_ipv4MulticastListeningSocket;
				Poco::Net::MulticastSocket m_ipv6MulticastListeningSocket;

				std::map<Poco::Net::DatagramSocket, Poco::NotificationQueue> ml_socketSendMessageQueue;
				Poco::TimedNotificationQueue m_delayedMessages;
				std::default_random_engine m_generator;
				std::uniform_int_distribution<unsigned int> m_distribution;

				MessagingContext m_context;

				Poco::Thread m_reactorThread;
				Poco::Net::SocketReactor m_reactor;

				bool m_SO_REUSEADDR_FLAG = true;
				bool m_SO_REUSEPORT_FLAG = true;

			public:
				DPWSHostSocketImpl(
						SDCLib::Config::NetworkConfig_shared_ptr p_config,
						ProbeNotificationDispatcher & p_probeDispatcher,
						ResolveNotificationDispatcher & p_resolveDispatcher);
				// Special Member Functions
				DPWSHostSocketImpl(const DPWSHostSocketImpl& p_obj) = delete;
				DPWSHostSocketImpl(DPWSHostSocketImpl&& p_obj) = delete;
				DPWSHostSocketImpl& operator=(const DPWSHostSocketImpl& p_obj) = delete;
				DPWSHostSocketImpl& operator=(DPWSHostSocketImpl&& p_obj) = delete;
				~DPWSHostSocketImpl();

				void sendBye(const ByeType & p_bye);
				void sendHello(const HelloType & p_hello);
				void sendStream(const MDM::WaveformStream & p_stream, const AddressType p_epr);

			private:

				void onMulticastSocketReadable(Poco::Net::ReadableNotification * p_notification);
				void onDatagrammSocketWritable(Poco::Net::WritableNotification * p_notification);
				void onTimeOut(Poco::Net::TimeoutNotification * p_notification);

				Poco::Timestamp createDelay();
				void processDelayedMessages();
			};

		}
	}
}

#endif
