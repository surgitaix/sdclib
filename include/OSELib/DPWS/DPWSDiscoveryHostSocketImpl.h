/*
 * DPWSDiscoveryHostSocketImpl.h
 *
 *  Created on: 07.12.2015
 *      Author: matthias
 */

#ifndef DPWS_DPWSDISCOVERYHOSTSOCKETIMPL_H_
#define DPWS_DPWSDISCOVERYHOSTSOCKETIMPL_H_

#include <map>

#include "Poco/NotificationQueue.h"
#include "Poco/TimedNotificationQueue.h"
#include "Poco/Thread.h"
#include "Poco/Net/MulticastSocket.h"
#include "Poco/Net/SocketNotification.h"
#include "Poco/Net/SocketReactor.h"

#include "NormalizedMessageModel-fwd.hxx"

#include "OSELib/DPWS/MessagingContext.h"
#include "OSELib/DPWS/Types.h"
#include "OSELib/Helper/WithLogger.h"

namespace OSELib {
namespace DPWS {
namespace Impl {

class DPWSDiscoveryHostSocketImpl : public WithLogger {
public:
	DPWSDiscoveryHostSocketImpl(
			ProbeNotificationDispatcher & probeDispatcher,
			ResolveNotificationDispatcher & resolveDispatcher);
	~DPWSDiscoveryHostSocketImpl();

	void sendBye(const ByeType & bye);
	void sendHello(const HelloType & hello);
	void sendStream(const CDM::WaveformStream & stream);

private:
	void onMulticastSocketReadable(Poco::Net::ReadableNotification * notification);
	void onDatagrammSocketWritable(Poco::Net::WritableNotification * notification);
	void onTimeOut(Poco::Net::TimeoutNotification * notification);

	Poco::Timestamp createDelay();
	void processDelayedMessages();

	struct SendMulticastMessage;
	struct SendUnicastMessage;

	ProbeNotificationDispatcher & probeDispatcher;
	ResolveNotificationDispatcher & _resolveDispatcher;

	const Poco::Net::SocketAddress ipv4StreamMulticastAddress;
	const Poco::Net::SocketAddress ipv6StreamMulticastAddress;
	const Poco::Net::SocketAddress ipv4DiscoveryMulticastAddress;
	const Poco::Net::SocketAddress ipv6DiscoveryMulticastAddress;
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

} /* namespace Impl */
} /* namespace DPWS */
} /* namespace OSELib */

#endif /* DPWS_DPWSDISCOVERYHOSTSOCKETIMPL_H_ */
