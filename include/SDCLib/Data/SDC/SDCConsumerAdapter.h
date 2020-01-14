/*
 * SDCConsumerAdapter.h
 *
 *  Created on: 10.12.2015
 *      Author: matthias, buerger
 *  Modified on: 26.09.2019, baumeister
 *
 */

#ifndef SDCLIB_DATA_SDC_SDCCONSUMERADAPTER_H_
#define SDCLIB_DATA_SDC_SDCCONSUMERADAPTER_H_

#include "SDC-fwd.h"
#include "OSELib/fwd.h"
#include "OSELib/DPWS/SubscriptionClient.h"
#include "OSELib/DPWS/MDPWSStreamingAdapter.h"
#include "OSELib/DPWS/PingManager.h"
#include "OSELib/HTTP/HTTPServer.h"
#include "OSELib/SDC/DefaultSDCSchemaGrammarProvider.h"
#include "OSELib/DPWS/Types.h"
#include "OSELib/Helper/WithLogger.h"

#include "SDCLib/Prerequisites.h"

#include <Poco/Net/Context.h>

// Declare in cpp defined
namespace OSELib
{
	class SetServiceEventSink;
	class BICEPSServiceEventSink;
}

namespace SDCLib
{
	namespace Data
	{
		namespace SDC
		{
			class SDCConsumerAdapter : public OSELib::DPWS::StreamNotificationDispatcher, public OSELib::Helper::WithLogger
			{
			private:
				SDCConsumer & m_consumer;

				mutable std::mutex m_mutex;

				OSELib::DPWS::DeviceDescription_shared_ptr m_deviceDescription = nullptr;
				OSELib::SDC::DefaultSDCSchemaGrammarProvider m_grammarProvider;
				std::unique_ptr<OSELib::HTTP::HTTPServer> m_httpServer = nullptr;
			//	std::unique_ptr<OSELib::DPWS::Impl::DPWSStreamingClientSocketImpl> _streamClientSocketImpl;
				OSELib::DPWS::Impl::MDPWSStreamingAdapter m_streamClientSocketImpl;
				std::unique_ptr<OSELib::DPWS::SubscriptionClient> m_subscriptionClient = nullptr;
				std::unique_ptr<OSELib::DPWS::PingManager> m_pingManager = nullptr;

			public:
				SDCConsumerAdapter(SDCConsumer & p_consumer, OSELib::DPWS::DeviceDescription_shared_ptr p_deviceDescription);
				// Special Member Functions
				SDCConsumerAdapter() = delete;
				SDCConsumerAdapter(const SDCConsumerAdapter& p_obj) = delete;
				SDCConsumerAdapter(SDCConsumerAdapter&& p_obj) = delete;
				SDCConsumerAdapter& operator=(const SDCConsumerAdapter& p_obj) = delete;
				SDCConsumerAdapter& operator=(SDCConsumerAdapter&& p_obj) = delete;
				~SDCConsumerAdapter();

				bool start();

				std::unique_ptr<MDM::GetMdDescriptionResponse> invoke(const MDM::GetMdDescription & p_request, Poco::Net::Context::Ptr p_context);
				std::unique_ptr<MDM::GetMdibResponse> invoke(const MDM::GetMdib & p_request, Poco::Net::Context::Ptr p_context);
				std::unique_ptr<MDM::GetMdStateResponse> invoke(const MDM::GetMdState & p_request, Poco::Net::Context::Ptr p_context);

				std::unique_ptr<MDM::ActivateResponse> invoke(const MDM::Activate & p_request, Poco::Net::Context::Ptr p_context);
				std::unique_ptr<MDM::SetAlertStateResponse> invoke(const MDM::SetAlertState & p_request, Poco::Net::Context::Ptr p_context);
				std::unique_ptr<MDM::SetValueResponse> invoke(const MDM::SetValue & p_request, Poco::Net::Context::Ptr p_context);
				std::unique_ptr<MDM::SetStringResponse> invoke(const MDM::SetString & p_request, Poco::Net::Context::Ptr p_context);

				std::unique_ptr<MDM::SetContextStateResponse> invoke(const MDM::SetContextState & p_request, Poco::Net::Context::Ptr p_context);

				void subscribeEvents();
				void unsubscribeEvents();

			private:

				// callback from _streamClientSocketImpl
				void dispatch(const OSELib::DPWS::WaveformStreamType & p_notification) override;

				// Variables
				template<class TraitsType>
				std::unique_ptr<typename TraitsType::Response> invokeImpl(const typename TraitsType::Request & p_request, const Poco::URI & p_requestURI, Poco::Net::Context::Ptr p_context);

				template<class TraitsType>
				std::unique_ptr<typename TraitsType::Response> invokeImplWithEventSubscription(const typename TraitsType::Request & p_request, const Poco::URI & p_requestURI, Poco::Net::Context::Ptr p_context);

				template<class RequestType>
				Poco::URI getRequestURIFromDeviceDescription(const RequestType & p_request) const;

			};
		}
	}
}

#endif
