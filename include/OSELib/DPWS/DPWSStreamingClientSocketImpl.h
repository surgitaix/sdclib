/*
 * DPWSStreamingClientSocketImpl.h
 *
 *  Created on: Nov 3, 2016
 *      Author: sebastian
 */

#ifndef INCLUDE_OSELIB_DPWS_DPWSSTREAMINGCLIENTSOCKETIMPL_H_
#define INCLUDE_OSELIB_DPWS_DPWSSTREAMINGCLIENTSOCKETIMPL_H_


#include "Poco/NotificationQueue.h"
#include "Poco/Thread.h"
//#include "Poco/Net/DatagramSocket.h"
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

//todo:
//: public WithLogger

class DPWSStreamingClientSocketImpl {
public:
	// todo: add stream dispatcher for callback
	DPWSStreamingClientSocketImpl(StreamNotificationDispatcher & streamNotificationDispatcher);

	~DPWSStreamingClientSocketImpl();

private:
	void onMulticastSocketReadable(Poco::Net::ReadableNotification * notification);

	// todo: implement verify msg
//	bool verifyStreamingMessage(const MESSAGEMODEL::Envelope & message);

//  callback function
	StreamNotificationDispatcher & _streamNotificationDispatcher;

	// todo: cosmetics: save addresses nicely
//	const Poco::Net::SocketAddress _ipv4MulticastAddress;
//	const Poco::Net::SocketAddress _ipv6MulticastAddress;
//	const Poco::Net::SocketAddress _ipv4BindingAddress;
//	const Poco::Net::SocketAddress _ipv6BindingAddress;
	Poco::Net::MulticastSocket _ipv4MulticastSocket;
	Poco::Net::MulticastSocket _ipv6MulticastSocket;

//	std::map<Poco::Net::DatagramSocket, Poco::NotificationQueue> _socketSendMessageQueue;

//	MessagingContext context; ?????

	Poco::Thread _reactorThread;
	Poco::Net::SocketReactor _reactor;
};

} /* namespace Impl */
} /* namespace DPWS */
} /* namespace OSELib */


#endif /* INCLUDE_OSELIB_DPWS_DPWSSTREAMINGCLIENTSOCKETIMPL_H_ */
