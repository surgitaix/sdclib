/*
 * DPWSDiscoveryClientSocketImpl.h
 *
 *  Created on: 11.12.2015
 *      Author: matthias
 */

#ifndef OSELIB_DPWS_DPWSDISCOVERYCLIENTSOCKETIMPL_H_
#define OSELIB_DPWS_DPWSDISCOVERYCLIENTSOCKETIMPL_H_

#include "Poco/NotificationQueue.h"
#include "Poco/Thread.h"
#include "Poco/Net/DatagramSocket.h"
#include "Poco/Net/MulticastSocket.h"
#include "Poco/Net/SocketNotification.h"
#include "Poco/Net/SocketReactor.h"

#include "OSELib/fwd.h"
#include "OSELib/DPWS/MessagingContext.h"
#include "OSELib/DPWS/Types.h"
#include "OSELib/Helper/WithLogger.h"

namespace OSELib {
namespace DPWS {
namespace Impl {

class DPWSDiscoveryClientSocketImpl : public WithLogger {
public:
	DPWSDiscoveryClientSocketImpl(
			ByeNotificationDispatcher & byeDispatcher,
			HelloNotificationDispatcher & helloDispatcher,
			ProbeMatchNotificationDispatcher & probeMatchDispatcher,
			ResolveMatchNotificationDispatcher & resolveDispatcher);

	~DPWSDiscoveryClientSocketImpl();

	void sendProbe(const ProbeType & filter);

	void sendResolve(const ResolveType & filter);

private:
	void onMulticastSocketReadable(Poco::Net::ReadableNotification * notification);
	void onDatagrammSocketReadable(Poco::Net::ReadableNotification * notification);
	void onDatagrammSocketWritable(Poco::Net::WritableNotification * notification) ;


	bool verifyBye(const MESSAGEMODEL::Envelope & message);
	bool verifyHello(const MESSAGEMODEL::Envelope & message);

	ByeNotificationDispatcher & _byeDispatcher;
	HelloNotificationDispatcher & _helloDispatcher;
	ProbeMatchNotificationDispatcher & _probeMatchDispatcher;
	ResolveMatchNotificationDispatcher & _resolveDispatcher;

	Poco::Net::SocketAddress _ipv4MulticastAddress;
	Poco::Net::SocketAddress _ipv6MulticastAddress;
	Poco::Net::SocketAddress _ipv4BindingAddress;
	Poco::Net::SocketAddress _ipv6BindingAddress;
	Poco::Net::MulticastSocket _ipv4MulticastDiscoverySocket;
	Poco::Net::MulticastSocket _ipv6MulticastDiscoverySocket;

	std::map<Poco::Net::DatagramSocket, Poco::NotificationQueue> _socketSendMessageQueue;

	MessagingContext context;

	Poco::Thread _reactorThread;
	Poco::Net::SocketReactor _reactor;
};

} /* namespace Impl */
} /* namespace DPWS */
} /* namespace OSELib */

#endif /* OSELIB_DPWS_DPWSDISCOVERYCLIENTSOCKETIMPL_H_ */
