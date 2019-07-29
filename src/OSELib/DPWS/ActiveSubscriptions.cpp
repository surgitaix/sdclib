/*
 * ActiveSubscriptions.cpp
 *
 *  Created on: 07.12.2015, matthias
 *  Modified on: 26.07.2019, baumeister
 */

#include "OSELib/DPWS/ActiveSubscriptions.h"

#include "SDCLib/SDCInstance.h"

#include <sstream>
#include <Poco/Timestamp.h>

#include "eventing.hxx"
#include "ws-addressing.hxx"

using namespace OSELib;
using namespace OSELib::DPWS;

ActiveSubscriptions::ActiveSubscriptions()
: WithLogger(Log::EVENTSOURCE)
, _runnableAdapter(*this, &ActiveSubscriptions::run)
{
    _thread.start(_runnableAdapter);
}

ActiveSubscriptions::~ActiveSubscriptions()
{
    _thread.wakeUp();
    _thread.join();
}

void ActiveSubscriptions::printSubscriptions() const {
	Poco::Mutex::ScopedLock lock(_mutex);

	log_information([&] { return "Active Subscriptions: " + std::to_string(_subscriptions.size()); });

	log_trace([&] {
		std::ostringstream logInfo;
		logInfo << std::endl;
		for (const auto & item : _subscriptions) {
			logInfo << "Subscription with my id: " << item.first << std::endl;
			logInfo << "Sink: " << item.second._notifyTo.Address() << std::endl;
			logInfo << "Actions: " << std::endl;
			for (const auto & action : item.second._actions) {
				logInfo << "" << action << std::endl;
			}
			logInfo << std::endl;
		}
		return logInfo.str(); });
}

void ActiveSubscriptions::unsubscribe(const WS::EVENTING::Identifier & identifier) {
	Poco::Mutex::ScopedLock lock(_mutex);

	auto subscription = _subscriptions.find(identifier);
	if (subscription != _subscriptions.end()) {
		_subscriptions.erase(subscription);
	}
}

std::string ActiveSubscriptions::subscribe(const SubscriptionInformation & subscription) {
	Poco::Mutex::ScopedLock lock(_mutex);

	const auto mySubscriptionID(SDCLib::SDCInstance::calcUUID());
	_subscriptions.emplace(mySubscriptionID, subscription);
	return mySubscriptionID;
}

bool ActiveSubscriptions::renew(const WS::EVENTING::Identifier & identifier, const Poco::Timestamp & timestamp) {
	Poco::Mutex::ScopedLock lock(_mutex);

	auto subscription = _subscriptions.find(identifier);
	if (subscription != _subscriptions.end()) {
		subscription->second._expirationTime = timestamp;
		return true;
	}
	return false;
}

void ActiveSubscriptions::houseKeeping() {
	std::vector<WS::EVENTING::Identifier> expiredSubscriptions;

	Poco::Mutex::ScopedLock lock(_mutex);
	const Poco::Timestamp now;
	for (auto & item : _subscriptions) {
		if (item.second._expirationTime < now) {
			expiredSubscriptions.emplace_back(item.first);
		}
	}
	for (const auto & item : expiredSubscriptions) {
		unsubscribe(item);
		log_information([&] { return "Expired Subscription: " + item; });
	}
}

void ActiveSubscriptions::run() {
	while (Poco::Thread::trySleep(10000)) {
		log_debug([&] { return "Checking for expired subscription"; });
		houseKeeping();
	}
}

std::map<xml_schema::Uri, WS::ADDRESSING::EndpointReferenceType> ActiveSubscriptions::getSubscriptions(const std::string & action) {

	houseKeeping();

	std::map<xml_schema::Uri, WS::ADDRESSING::EndpointReferenceType> result;
	Poco::Mutex::ScopedLock lock(_mutex);
	for (const auto & item : this->_subscriptions) {
		const auto actionFilter(item.second._actions);
		if (std::find(actionFilter.begin(), actionFilter.end(), action) != actionFilter.end()) {
			result.emplace(item.first, item.second._notifyTo);
		}
	}
	return result;
}
