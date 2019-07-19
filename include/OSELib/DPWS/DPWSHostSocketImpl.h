/*
 * DPWSHostSocketImpl.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef DPWS_DPWSDISCOVERYHOSTSOCKETIMPL_H_
#define DPWS_DPWSDISCOVERYHOSTSOCKETIMPL_H_

#include <map>
#include <random>

#include "Poco/NotificationQueue.h"
#include "Poco/TimedNotificationQueue.h"
#include "Poco/Thread.h"
#include "Poco/Net/MulticastSocket.h"
#include "Poco/Net/SocketNotification.h"
#include "Poco/Net/SocketReactor.h"

#include "NormalizedMessageModel-fwd.hxx"

#include "SDCLib/Prerequisites.h"
#include "OSELib/DPWS/MessagingContext.h"
#include "OSELib/DPWS/Types.h"
#include "OSELib/Helper/WithLogger.h"

namespace OSELib {
namespace DPWS {
namespace Impl {

class DPWSHostSocketImpl : public WithLogger {
public:
	DPWSHostSocketImpl(
            SDCLib::Config::NetworkConfig_shared_ptr p_config,
			ProbeNotificationDispatcher & probeDispatcher,
			ResolveNotificationDispatcher & resolveDispatcher);

    DPWSHostSocketImpl(const DPWSHostSocketImpl& p_obj) = delete;
    DPWSHostSocketImpl(DPWSHostSocketImpl&& p_obj) = delete;
    DPWSHostSocketImpl& operator=(const DPWSHostSocketImpl& p_obj) = delete;
    DPWSHostSocketImpl& operator=(DPWSHostSocketImpl&& p_obj) = delete;

	~DPWSHostSocketImpl();

	void sendBye(const ByeType & bye);
	void sendHello(const HelloType & hello);
	void sendStream(const MDM::WaveformStream & stream, const AddressType epr);

private:

    std::mutex m_mutex;

	void onMulticastSocketReadable(Poco::Net::ReadableNotification * notification);
	void onDatagrammSocketWritable(Poco::Net::WritableNotification * notification);
	void onTimeOut(Poco::Net::TimeoutNotification * notification);

	Poco::Timestamp createDelay();
	void processDelayedMessages();

	struct SendMulticastMessage;
	struct SendUnicastMessage;

    SDCLib::Config::NetworkConfig_shared_ptr m_networkConfig = nullptr;
	ProbeNotificationDispatcher & probeDispatcher;
	ResolveNotificationDispatcher & resolveDispatcher;

    const Poco::Net::SocketAddress m_ipv4DiscoveryMulticastAddress;
    const Poco::Net::SocketAddress m_ipv6DiscoveryMulticastAddress;
    const Poco::Net::SocketAddress m_ipv4StreamMulticastAddress;
    const Poco::Net::SocketAddress m_ipv6StreamMulticastAddress;
    Poco::Net::MulticastSocket m_ipv4MulticastListeningSocket;
    Poco::Net::MulticastSocket m_ipv6MulticastListeningSocket;

	std::map<Poco::Net::DatagramSocket, Poco::NotificationQueue> socketSendMessageQueue;
	Poco::TimedNotificationQueue delayedMessages;
	std::default_random_engine generator;
	std::uniform_int_distribution<unsigned int> distribution;

	MessagingContext context;

	Poco::Thread reactorThread;
	Poco::Net::SocketReactor reactor;

    bool m_SO_REUSEADDR_FLAG = true;
    bool m_SO_REUSEPORT_FLAG = true;
};

} /* namespace Impl */
} /* namespace DPWS */
} /* namespace OSELib */

#endif /* DPWS_DPWSDISCOVERYHOSTSOCKETIMPL_H_ */
