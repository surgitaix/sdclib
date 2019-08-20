/*
 * DPWSDiscoveryClientSocketImpl.h
 *
 *  Created on: 11.12.2015
 *      Author: matthias
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
#include <Poco/Net/SocketNotification.h>
#include <Poco/Net/SocketReactor.h>



namespace OSELib {
namespace DPWS {
namespace Impl {

class DPWSDiscoveryClientSocketImpl : public OSELib::Helper::WithLogger {
public:
	DPWSDiscoveryClientSocketImpl(
            SDCLib::Config::NetworkConfig_shared_ptr p_config,
			ByeNotificationDispatcher & byeDispatcher,
			HelloNotificationDispatcher & helloDispatcher,
			ProbeMatchNotificationDispatcher & probeMatchDispatcher,
			ResolveMatchNotificationDispatcher & resolveDispatcher);

	~DPWSDiscoveryClientSocketImpl();

	void sendProbe(const ProbeType& filter);

	void sendResolve(const ResolveType& filter);

private:
	void onMulticastSocketReadable(Poco::Net::ReadableNotification * notification);
	void onDatagrammSocketReadable(Poco::Net::ReadableNotification * notification);
	void onDatagrammSocketWritable(Poco::Net::WritableNotification * notification) ;


	bool verifyBye(const MESSAGEMODEL::Envelope & message);
	bool verifyHello(const MESSAGEMODEL::Envelope & message);

	SDCLib::Config::NetworkConfig_shared_ptr m_networkConfig = nullptr;
	ByeNotificationDispatcher & _byeDispatcher;
	HelloNotificationDispatcher & _helloDispatcher;
	ProbeMatchNotificationDispatcher & _probeMatchDispatcher;
	ResolveMatchNotificationDispatcher & _resolveDispatcher;

	const Poco::Net::SocketAddress m_ipv4MulticastAddress;
	const Poco::Net::SocketAddress m_ipv6MulticastAddress;
	Poco::Net::MulticastSocket m_ipv4DiscoverySocket;
	Poco::Net::MulticastSocket m_ipv6DiscoverySocket;

    SDCLib::SDCPort m_ipv4DatagrammSocketPort = 0; // 0 = Any free Port
    SDCLib::SDCPort m_ipv6DatagrammSocketPort = 0; // 0 = Any free Port

	std::map<Poco::Net::DatagramSocket, Poco::NotificationQueue> m_socketSendMessageQueue;

	MessagingContext m_messagingContext;

	Poco::Thread m_reactorThread;
	Poco::Net::SocketReactor m_reactor;

    bool m_SO_REUSEADDR_FLAG = true; // Default flag when binding to all adapters
    bool m_SO_REUSEPORT_FLAG = true; // Default flag when binding to all adapters
};

} /* namespace Impl */
} /* namespace DPWS */
} /* namespace OSELib */

#endif /* OSELIB_DPWS_DPWSDISCOVERYCLIENTSOCKETIMPL_H_ */
