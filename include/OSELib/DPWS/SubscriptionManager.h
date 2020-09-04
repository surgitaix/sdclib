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
            const std::vector<xml_schema::Uri> m_allowedEventActions;
            std::unique_ptr<HTTP::HTTPSessionManager> m_sessionManager{nullptr};

            Poco::RunnableAdapter<SubscriptionManager> m_runnableAdapter;
            Poco::Thread m_thread;

        public:
            SubscriptionManager(const std::vector<xml_schema::Uri>&, SDCLib::Config::SSLConfig_shared_ptr);
            SubscriptionManager(const SubscriptionManager&) = default;
            SubscriptionManager(SubscriptionManager&&) = default;
            SubscriptionManager& operator=(const SubscriptionManager&) = default;
            SubscriptionManager& operator=(SubscriptionManager&&) = default;
            ~SubscriptionManager();

            template<class TraitsType> void fireEvent(const typename TraitsType::ReportType&);

            std::unique_ptr<SubscribeTraits::Response> dispatch(const SubscribeTraits::Request&) override;
            std::unique_ptr<RenewTraits::Response> dispatch(const RenewTraits::Request&, const RenewTraits::RequestIdentifier&) override;
            std::unique_ptr<GetStatusTraits::Response> dispatch(const GetStatusTraits::Request&,
                                                                const GetStatusTraits::RequestIdentifier&) override;
            std::unique_ptr<UnsubscribeTraits::Response> dispatch(const UnsubscribeTraits::Request&,
                                                                  const UnsubscribeTraits::RequestIdentifier&) override;

            void endSubscription(const SubscriptionEndTraits::RequestIdentifier&);

        private:
            void houseKeeping();
            void run();
        };
    } // namespace DPWS
} // namespace OSELib

#endif
