/*
 * DPWSDiscoveryClientSocketImpl.h
 *
 *  Created on: 11.12.2015, matthias
 *  Modified on: 23.08.2019, baumeister
 *
 */

#ifndef OSELIB_DPWS_DPWSDISCOVERYCLIENTSOCKETIMPL_H_
#define OSELIB_DPWS_DPWSDISCOVERYCLIENTSOCKETIMPL_H_

#include "SDCLib/Prerequisites.h"
#include "OSELib/fwd.h"
#include "OSELib/DPWS/MessagingContext.h"
#include "OSELib/DPWS/Types.h"
#include "OSELib/Helper/WithLogger.h"

#include <Poco/NotificationQueue.h>
#include <Poco/Thread.h>
#include <Poco/Net/DatagramSocket.h>
#include <Poco/Net/MulticastSocket.h>
#include <Poco/Net/SocketReactor.h>

namespace OSELib
{
	namespace DPWS
	{
		namespace Impl
		{
			class DPWSDiscoveryClientSocketImpl : public OSELib::Helper::WithLogger
			{
			private:
					SDCLib::Config::NetworkConfig_shared_ptr m_networkConfig = nullptr;
					ByeNotificationDispatcher & m_byeDispatcher;
					HelloNotificationDispatcher & m_helloDispatcher;
					ProbeMatchNotificationDispatcher & m_probeMatchDispatcher;
					ResolveMatchNotificationDispatcher & m_resolveDispatcher;

					const Poco::Net::SocketAddress m_ipv4MulticastAddress;
					const Poco::Net::SocketAddress m_ipv6MulticastAddress;
					Poco::Net::MulticastSocket m_ipv4DiscoverySocket;
					Poco::Net::MulticastSocket m_ipv6DiscoverySocket;

					SDCLib::SDCPort m_ipv4DatagrammSocketPort = 0; // 0 = Any free Port
					SDCLib::SDCPort m_ipv6DatagrammSocketPort = 0; // 0 = Any free Port

					std::map<Poco::Net::DatagramSocket, Poco::NotificationQueue> ml_socketSendMessageQueue;

					MessagingContext m_messagingContext;

					Poco::Thread m_reactorThread;
					Poco::Net::SocketReactor m_reactor;

					bool m_SO_REUSEADDR_FLAG = true; // Default flag when binding to all adapters
					bool m_SO_REUSEPORT_FLAG = true; // Default flag when binding to all adapters

			public:
				DPWSDiscoveryClientSocketImpl(
						SDCLib::Config::NetworkConfig_shared_ptr p_config,
						ByeNotificationDispatcher & p_byeDispatcher,
						HelloNotificationDispatcher & p_helloDispatcher,
						ProbeMatchNotificationDispatcher & p_probeMatchDispatcher,
						ResolveMatchNotificationDispatcher & p_resolveDispatcher);
				// Special Member Functions
				DPWSDiscoveryClientSocketImpl(const DPWSDiscoveryClientSocketImpl& p_obj) = delete;
				DPWSDiscoveryClientSocketImpl(DPWSDiscoveryClientSocketImpl&& p_obj) = delete;
				DPWSDiscoveryClientSocketImpl& operator=(const DPWSDiscoveryClientSocketImpl& p_obj) = delete;
				DPWSDiscoveryClientSocketImpl& operator=(DPWSDiscoveryClientSocketImpl&& p_obj) = delete;
				~DPWSDiscoveryClientSocketImpl();


				void sendProbe(const ProbeType& p_filter);
				void sendResolve(const ResolveType& p_filter);


			private:

				void onMulticastSocketReadable(Poco::Net::ReadableNotification* p_notification);
				void onDatagrammSocketReadable(Poco::Net::ReadableNotification* p_notification);
				void onDatagrammSocketWritable(Poco::Net::WritableNotification* p_notification);


				bool verifyBye(const MESSAGEMODEL::Envelope & p_message);
				bool verifyHello(const MESSAGEMODEL::Envelope & p_message);
			};
		}
	}
}

#endif
