/*
 * SubscriptionManager.h
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 26.08.2019, baumeister
 *
 */

#ifndef OSELIB_DPWS_SUBSCRIPTIONMANAGER_H_
#define OSELIB_DPWS_SUBSCRIPTIONMANAGER_H_

#include "OSELib/DPWS/ISubscriptionManager.h"
#include "OSELib/Helper/WithLogger.h"
#include "OSELib/DPWS/ActiveSubscriptions.h"
#include "OSELib/HTTP/HTTPSessionManager.h"

#include "SDCLib/Prerequisites.h"

namespace OSELib
{
	namespace DPWS
	{
		class SubscriptionManager : public ISubscriptionManager, public OSELib::Helper::WithLogger
		{
		private:
			ActiveSubscriptions m_subscriptions;
			const std::vector<xml_schema::Uri> ml_allowedEventActions;
			std::unique_ptr<HTTP::HTTPSessionManager> m_sessionManager = nullptr;

		public:
			SubscriptionManager(const std::vector<xml_schema::Uri> & pl_allowedEventActions, SDCLib::Config::SSLConfig_shared_ptr p_SSLConfig);
			// Special Member Functions
			SubscriptionManager(const SubscriptionManager& p_obj) = default;
			SubscriptionManager(SubscriptionManager&& p_obj) = default;
			SubscriptionManager& operator=(const SubscriptionManager& p_obj) = default;
			SubscriptionManager& operator=(SubscriptionManager&& p_obj) = default;
			~SubscriptionManager() = default;

			template <class TraitsType>
			void fireEvent(const typename TraitsType::ReportType & p_report);

			std::unique_ptr<SubscribeTraits::Response> dispatch(const SubscribeTraits::Request & p_request) override;
			std::unique_ptr<UnsubscribeTraits::Response> dispatch(const UnsubscribeTraits::Request & p_request, const UnsubscribeTraits::RequestIdentifier & p_identifier) override;
			std::unique_ptr<RenewTraits::Response> dispatch(const RenewTraits::Request & p_request, const RenewTraits::RequestIdentifier & p_identifier) override;
			std::unique_ptr<GetStatusTraits::Response> dispatch(const GetStatusTraits::Request & p_request, const GetStatusTraits::RequestIdentifier & p_identifier) override;
		};
	}
}

#endif
