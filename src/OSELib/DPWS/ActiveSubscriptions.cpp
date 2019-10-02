/*
 * ActiveSubscriptions.cpp
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 01.08.2019, baumeister
 */

#include "OSELib/DPWS/ActiveSubscriptions.h"

#include "SDCLib/SDCInstance.h"

#include <sstream>

using namespace OSELib;
using namespace OSELib::DPWS;

ActiveSubscriptions::ActiveSubscriptions()
: WithLogger(Log::EVENTSOURCE)
, m_runnableAdapter(*this, &ActiveSubscriptions::run)
{
    m_thread.start(m_runnableAdapter);
}

ActiveSubscriptions::~ActiveSubscriptions()
{
    m_thread.wakeUp();
    m_thread.join();
}

void ActiveSubscriptions::printSubscriptions() const
{
	std::lock_guard<std::mutex> t_lock(m_mutex);

	log_information([&] { return "Active Subscriptions: " + std::to_string(ml_subscriptions.size()); });

	log_trace([&] {
		std::ostringstream logInfo;
		logInfo << std::endl;
		for (const auto & t_item : ml_subscriptions) {
			logInfo << "Subscription with my id: " << t_item.first << std::endl;
			logInfo << "Sink: " << t_item.second.m_notifyTo.Address() << std::endl;
			logInfo << "Actions: " << std::endl;
			for (const auto & t_action : t_item.second.m_actions) {
				logInfo << "" << t_action << std::endl;
			}
			logInfo << std::endl;
		}
		return logInfo.str(); });
}

void ActiveSubscriptions::unsubscribe(const WS::EVENTING::Identifier & p_identifier)
{
	std::lock_guard<std::mutex> t_lock(m_mutex);

	auto t_subscription = ml_subscriptions.find(p_identifier);
	if (t_subscription != ml_subscriptions.end()) {
		ml_subscriptions.erase(t_subscription);
	}
}

std::string ActiveSubscriptions::subscribe(const SubscriptionInformation & subscription)
{
	std::lock_guard<std::mutex> t_lock(m_mutex);

	const auto mySubscriptionID(SDCLib::SDCInstance::calcUUID());
	ml_subscriptions.emplace(mySubscriptionID, subscription);
	return mySubscriptionID;
}

bool ActiveSubscriptions::renew(const WS::EVENTING::Identifier & identifier, std::chrono::system_clock::time_point p_timestamp)
{
	std::lock_guard<std::mutex> t_lock(m_mutex);

	auto subscription = ml_subscriptions.find(identifier);
	if (subscription != ml_subscriptions.end()) {
		subscription->second.m_expirationTime = p_timestamp;
		return true;
	}
	return false;
}

void ActiveSubscriptions::houseKeeping()
{
	std::vector<WS::EVENTING::Identifier> tl_expiredSubscriptions;

	//m_mutex locked
	{
		std::lock_guard<std::mutex> t_lock(m_mutex);
		auto t_now = std::chrono::system_clock::now();

		// 1. Collect all expired
		for (auto & t_item : ml_subscriptions) {
			if (t_item.second.m_expirationTime.time_since_epoch() < t_now.time_since_epoch()) {
				tl_expiredSubscriptions.emplace_back(t_item.first);
			}
		}
	}

	// 2. Unsubscribe all
	for (const auto & t_item : tl_expiredSubscriptions) {
		unsubscribe(t_item);
		log_information([&] { return "Expired Subscription: " + t_item; });
	}
}

void ActiveSubscriptions::run()
{
	while (Poco::Thread::trySleep(8000)) {
		log_debug([&] { return "Checking for expired subscription"; });
		houseKeeping();
	}
}

std::map<xml_schema::Uri, WS::ADDRESSING::EndpointReferenceType> ActiveSubscriptions::getSubscriptions(const std::string & p_action)
{
	// Cleanup first
	houseKeeping();

	std::map<xml_schema::Uri, WS::ADDRESSING::EndpointReferenceType> t_result;
	// Collect and return
	std::lock_guard<std::mutex> t_lock(m_mutex);
	for (const auto & t_item : ml_subscriptions) {
		const auto t_actionFilter(t_item.second.m_actions);
		if (std::find(t_actionFilter.begin(), t_actionFilter.end(), p_action) != t_actionFilter.end()) {
			t_result.emplace(t_item.first, t_item.second.m_notifyTo);
		}
	}
	return t_result;
}
ActiveSubscriptions::GetStatusResult ActiveSubscriptions::getStatus(const WS::EVENTING::Identifier & identifier) const
{
	std::lock_guard<std::mutex> t_lock(m_mutex);
	auto t_subscription = ml_subscriptions.find(identifier);
	if (t_subscription != ml_subscriptions.end()) {
		return {true, t_subscription->second};
	}

	// Note: Not nice but working... Create an empty SubscriptionInformation... REWORK!
	return {false, ActiveSubscriptions::SubscriptionInformation(
	WS::ADDRESSING::EndpointReferenceType(WS::ADDRESSING::AttributedURIType("")),
	std::chrono::system_clock::time_point(),
	WS::EVENTING::FilterType())};
}
