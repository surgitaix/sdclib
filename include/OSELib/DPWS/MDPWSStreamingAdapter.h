/*
 * MDPWSStreamingAdapter.h
 *
 *  Created on: 03.11.2016, buerger
 *  Modified on: 23.08.2019, baumeister
 *
 */

#ifndef OSELIB_DPWS_IMPL_MDPWSSTREAMINGADAPTER_H_
#define OSELIB_DPWS_IMPL_MDPWSSTREAMINGADAPTER_H_


#include "SDCLib/Prerequisites.h"
#include "OSELib/fwd.h"
#include "OSELib/DPWS/Types.h"
#include "OSELib/Helper/WithLogger.h"

#include <Poco/Thread.h>
#include <Poco/Net/MulticastSocket.h>
#include <Poco/Net/SocketReactor.h>


namespace OSELib
{
	namespace DPWS
	{
		namespace Impl
		{
			class MDPWSStreamingAdapter : public OSELib::Helper::WithLogger
			{
				// todo: implement verify msg
				//	bool verifyStreamingMessage(const MESSAGEMODEL::Envelope & message);

				SDCLib::Config::NetworkConfig_shared_ptr m_networkConfig = nullptr;
				//  callback function, implemented in SDCConsumerAdapter
				StreamNotificationDispatcher & m_streamNotificationDispatcher;

				DeviceDescription_shared_ptr m_deviceDescription = nullptr;

				// todo: make list of socket for compatibility with other frameworks

				const Poco::Net::SocketAddress m_ipv4MulticastAddress;
				const Poco::Net::SocketAddress m_ipv6MulticastAddress;
				Poco::Net::MulticastSocket m_ipv4MulticastSocket;
				Poco::Net::MulticastSocket m_ipv6MulticastSocket;

				Poco::Thread m_reactorThread;
				Poco::Net::SocketReactor m_reactor;

				bool m_SO_REUSEADDR_FLAG = true; // Default flag when binding to all adapters
				bool m_SO_REUSEPORT_FLAG = true; // Default flag when binding to all adapters

			public:

				MDPWSStreamingAdapter(SDCLib::Config::NetworkConfig_shared_ptr p_config, StreamNotificationDispatcher & streamNotificationDispatcher, DeviceDescription_shared_ptr p_deviceDescription);
				// Special Member Functions
				MDPWSStreamingAdapter(const MDPWSStreamingAdapter& p_obj) = default;
				MDPWSStreamingAdapter(MDPWSStreamingAdapter&& p_obj) = default;
				MDPWSStreamingAdapter& operator=(const MDPWSStreamingAdapter& p_obj) = default;
				MDPWSStreamingAdapter& operator=(MDPWSStreamingAdapter&& p_obj) = default;
				~MDPWSStreamingAdapter();

			private:
				void onMulticastSocketReadable(Poco::Net::ReadableNotification * p_notification);

			};
		}
	}
}

#endif
