/*
 * MDPWSStreamingAdapter.h
 *
 *  Created on: Nov 3, 2016
 *      Author: sebastian
 */

#ifndef INCLUDE_OSELIB_DPWS_DPWSSTREAMINGCLIENTSOCKETIMPL_H_
#define INCLUDE_OSELIB_DPWS_DPWSSTREAMINGCLIENTSOCKETIMPL_H_


#include "OSCLib/Prerequisites.h"
#include "OSELib/DPWS/DeviceDescription.h"
#include "OSELib/fwd.h"
#include "OSELib/DPWS/Types.h"
#include "OSELib/Helper/WithLogger.h"

#include <Poco/NotificationQueue.h>
#include <Poco/Thread.h>
#include <Poco/Net/MulticastSocket.h>
#include <Poco/Net/SocketNotification.h>
#include <Poco/Net/SocketReactor.h>


namespace OSELib {
namespace DPWS {
namespace Impl {


class MDPWSStreamingAdapter : public WithLogger {
public:
    MDPWSStreamingAdapter(SDCLib::SDCInstance_shared_ptr p_SDCInstance, StreamNotificationDispatcher & streamNotificationDispatcher, const DeviceDescription & deviceDescription);

	~MDPWSStreamingAdapter();

private:
	void onMulticastSocketReadable(Poco::Net::ReadableNotification * notification);

	// todo: implement verify msg
	//	bool verifyStreamingMessage(const MESSAGEMODEL::Envelope & message);

    SDCLib::SDCInstance_shared_ptr m_SDCInstance = nullptr;
    //  callback function, implemented in SDCConsumerAdapter
	StreamNotificationDispatcher & m_streamNotificationDispatcher;

    const DeviceDescription & m_deviceDescription;

	// todo: make list of socket for compatibility with other frameworks

	const Poco::Net::SocketAddress m_ipv4MulticastAddress;
	const Poco::Net::SocketAddress m_ipv6MulticastAddress;
	Poco::Net::MulticastSocket m_ipv4MulticastSocket;
	Poco::Net::MulticastSocket m_ipv6MulticastSocket;

	Poco::Thread m_reactorThread;
	Poco::Net::SocketReactor m_reactor;

    bool m_SO_REUSEADDR_FLAG = true; // Default flag when binding to all adapters
    bool m_SO_REUSEPORT_FLAG = true; // Default flag when binding to all adapters
};

} /* namespace Impl */
} /* namespace DPWS */
} /* namespace OSELib */


#endif /* INCLUDE_OSELIB_DPWS_DPWSSTREAMINGCLIENTSOCKETIMPL_H_ */
