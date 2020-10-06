/*
 * ActiveSubscriptions.h
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 22.08.2019, baumeister
 *
 */

#ifndef OSELIB_DPWS_ACTIVESUBSCRIPTIONS_H_
#define OSELIB_DPWS_ACTIVESUBSCRIPTIONS_H_

#include <Poco/Thread.h>
#include <Poco/RunnableAdapter.h>

#include "DataModel/eventing.hxx"
#include "DataModel/ws-addressing.hxx"

#include "OSELib/fwd.h"
#include "OSELib/Helper/WithLogger.h"

#include <mutex>
#include <chrono>

namespace OSELib
{
    namespace DPWS
    {
        class ActiveSubscriptions : public Helper::WithLogger
        {
        public:
            struct SubscriptionInformation
            {
                explicit SubscriptionInformation(WS::ADDRESSING::EndpointReferenceType p_notifyTo,
                                                 std::chrono::system_clock::time_point p_expirationTime,
                                                 WS::EVENTING::FilterType p_actions)
                    : m_notifyTo(p_notifyTo)
                    , m_expirationTime(p_expirationTime)
                    , m_actions(p_actions)
                {
                }
                const WS::ADDRESSING::EndpointReferenceType m_notifyTo;
                std::chrono::system_clock::time_point m_expirationTime;
                const WS::EVENTING::FilterType m_actions;
            };

            using GetStatusResult = std::pair<bool, SubscriptionInformation>;

        private:
            std::mutex m_mutex_houseKeeping;
            mutable std::mutex m_mutex;
            std::map<xml_schema::Uri, SubscriptionInformation> m_subscriptions;

        public:
            ActiveSubscriptions();
            // Special Member Functions
            ActiveSubscriptions(const ActiveSubscriptions&) = delete;
            ActiveSubscriptions(ActiveSubscriptions&&) = delete;
            ActiveSubscriptions& operator=(const ActiveSubscriptions&) = delete;
            ActiveSubscriptions& operator=(ActiveSubscriptions&&) = delete;
            ~ActiveSubscriptions() = default;

            void printSubscriptions() const;

            std::string addSubscription(const SubscriptionInformation&);
            bool renewSubscription(const WS::EVENTING::Identifier&, std::chrono::system_clock::time_point);
            GetStatusResult getSubscriptionStatus(const WS::EVENTING::Identifier&) const;
            void removeSubscription(const WS::EVENTING::Identifier&);

            std::map<xml_schema::Uri, ActiveSubscriptions::SubscriptionInformation> getAllSubscriptions() const;
            std::map<xml_schema::Uri, WS::ADDRESSING::EndpointReferenceType> getSubscriptionsForAction(const std::string&);

            std::vector<WS::EVENTING::Identifier> collectExpiredSubscriptions();
        };

    } // namespace DPWS
} // namespace OSELib

#endif
