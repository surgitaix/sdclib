/*
 * ActiveSubscriptions.cpp
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 02.09.2019, baumeister
 */

#include "OSELib/DPWS/ActiveSubscriptions.h"

#include "SDCLib/SDCInstance.h"

#include <sstream>

using namespace OSELib;
using namespace OSELib::DPWS;

ActiveSubscriptions::ActiveSubscriptions()
    : Helper::WithLogger(Log::EVENTSOURCE)
{
}

std::vector<WS::EVENTING::Identifier> ActiveSubscriptions::collectExpiredSubscriptions()
{
    // Protect from double execution
    std::lock_guard<std::mutex> lockHouseKeeping{m_mutex_houseKeeping};

    std::vector<WS::EVENTING::Identifier> expiredSubscriptionIDs;

    { // LOCK
        std::lock_guard<std::mutex> lock(m_mutex);
        if(m_subscriptions.empty())
        {
            return expiredSubscriptionIDs;
        }

        // 1. Collect all expired
        auto now = std::chrono::system_clock::now();
        for(auto& subscriptionPair : m_subscriptions)
        {
            if(subscriptionPair.second.m_expirationTime.time_since_epoch() < now.time_since_epoch())
            {
                expiredSubscriptionIDs.emplace_back(subscriptionPair.first);
            }
        }
    } // UNLOCK

    return expiredSubscriptionIDs;
}

void ActiveSubscriptions::printSubscriptions() const
{
    std::lock_guard<std::mutex> lock(m_mutex);

    log_information([&] { return "Active Subscriptions: " + std::to_string(m_subscriptions.size()); });

    log_trace([&] {
        std::ostringstream logInfo;
        logInfo << std::endl;
        for(const auto& t_item : m_subscriptions)
        {
            logInfo << "Subscription with my id: " << t_item.first << std::endl;
            logInfo << "Sink: " << t_item.second.m_notifyTo.getAddress() << std::endl;
            logInfo << "Actions: " << std::endl;
            for(const auto& t_action : t_item.second.m_actions)
            {
                logInfo << "" << t_action << std::endl;
            }
            logInfo << std::endl;
        }
        return logInfo.str();
    });
}


std::string ActiveSubscriptions::addSubscription(const SubscriptionInformation& p_subscription)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    const auto mySubscriptionID{SDCLib::SDCInstance::calcUUID()};
    m_subscriptions.emplace(mySubscriptionID, p_subscription);
    return mySubscriptionID;
}

bool ActiveSubscriptions::renewSubscription(const WS::EVENTING::Identifier& p_identifier, std::chrono::system_clock::time_point p_timestamp)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    auto subscription = m_subscriptions.find(p_identifier);
    if(subscription != m_subscriptions.end())
    {
        subscription->second.m_expirationTime = p_timestamp;
        return true;
    }
    return false;
}

ActiveSubscriptions::GetStatusResult ActiveSubscriptions::getSubscriptionStatus(const WS::EVENTING::Identifier& p_identifier) const
{
    std::lock_guard<std::mutex> lock(m_mutex);

    auto subscriptionPair = m_subscriptions.find(p_identifier);
    if(subscriptionPair != m_subscriptions.end())
    {
        return {true, subscriptionPair->second};
    }

    // Note: Not nice but working... Create an empty SubscriptionInformation... REWORK!
    return {false,
            ActiveSubscriptions::SubscriptionInformation(WS::ADDRESSING::EndpointReferenceType{WS::ADDRESSING::AttributedURIType{""}},
                                                         std::chrono::system_clock::time_point(),
                                                         WS::EVENTING::FilterType())};
}


void ActiveSubscriptions::removeSubscription(const WS::EVENTING::Identifier& p_identifier)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    auto ubsubscribeIterator = m_subscriptions.find(p_identifier);
    if(ubsubscribeIterator != m_subscriptions.end())
    {
        m_subscriptions.erase(ubsubscribeIterator);
    }
}

std::map<xml_schema::Uri, ActiveSubscriptions::SubscriptionInformation> ActiveSubscriptions::getAllSubscriptions() const
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_subscriptions;
}

std::map<xml_schema::Uri, WS::ADDRESSING::EndpointReferenceType> ActiveSubscriptions::getSubscriptionsForAction(const std::string& p_action)
{
    std::map<xml_schema::Uri, WS::ADDRESSING::EndpointReferenceType> activeSubscriptions;

    // Collect and return
    std::lock_guard<std::mutex> lock(m_mutex);
    for(const auto& subscriptionPair : m_subscriptions)
    {
        const auto actionFilter{subscriptionPair.second.m_actions};
        if(std::find(actionFilter.begin(), actionFilter.end(), p_action) != actionFilter.end())
        {
            activeSubscriptions.emplace(subscriptionPair.first, subscriptionPair.second.m_notifyTo);
        }
    }

    return activeSubscriptions;
}
