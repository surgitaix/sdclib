/*
 * MDPWSStreamingAdapter.h
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

#include "OSELib/DPWS/DeviceDescription.h"

namespace OSELib {
namespace DPWS {
namespace Impl {


class MDPWSStreamingAdapter : public WithLogger {
public:
	MDPWSStreamingAdapter(StreamNotificationDispatcher & streamNotificationDispatcher, const DeviceDescription & deviceDescription);

	~MDPWSStreamingAdapter();

private:
	void onMulticastSocketReadable(Poco::Net::ReadableNotification * notification);

	// todo: implement verify msg
	//	bool verifyStreamingMessage(const MESSAGEMODEL::Envelope & message);

	//  callback function, implemented in OSELibConsumerAdapter
	StreamNotificationDispatcher & m_streamNotificationDispatcher;

	// todo: make list of socket for compatibility with other frameworks

	Poco::Net::SocketAddress m_ipv4MulticastAddress;
	Poco::Net::SocketAddress m_ipv6MulticastAddress;
	const Poco::Net::SocketAddress m_ipv4BindingAddress;
	const Poco::Net::SocketAddress m_ipv6BindingAddress;
	Poco::Net::MulticastSocket m_ipv4MulticastSocket;
	Poco::Net::MulticastSocket m_ipv6MulticastSocket;

	const DeviceDescription & m_deviceDescription;

//	std::map<Poco::Net::DatagramSocket, Poco::NotificationQueue> _socketSendMessageQueue;

//	MessagingContext context; ?????

	Poco::Thread _reactorThread;
	Poco::Net::SocketReactor _reactor;
};

} /* namespace Impl */
} /* namespace DPWS */
} /* namespace OSELib */


#endif /* INCLUDE_OSELIB_DPWS_DPWSSTREAMINGCLIENTSOCKETIMPL_H_ */
