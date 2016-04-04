/**
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  *
  */

/*
 * SubscriptionVector.cpp
 *
 *  Created on: 29.04.2014
 *      Author: roehser
 */

#include "OSCLib/Data/Subscription.h"
#include "OSCLib/Data/SubscriptionVector.h"

#include <algorithm>

#include "Poco/ScopedLock.h"

namespace OSCLib {
namespace Data {

SubscriptionVector::SubscriptionVector() {

}

SubscriptionVector::~SubscriptionVector() {
}

void SubscriptionVector::addSubscription(std::shared_ptr<Data::Subscription> subscription) {
	Poco::Mutex::ScopedLock lock(mutex);

	subscriptions.push_back(subscription);
}

void SubscriptionVector::cleanExpiredSubscriptions() {

	Poco::Mutex::ScopedLock lock(mutex);

	std::vector<std::shared_ptr<Data::Subscription>> toErase;
	std::vector<std::shared_ptr<Data::Subscription>>::iterator subIt = subscriptions.begin();

	// collect expired items
	while (subIt != subscriptions.end()) {
		if ((*subIt)->isExpired() || (*subIt)->isCanceled()) {
			toErase.push_back(*subIt);
		}
		++subIt;
	}

	// erase and free expired items
	for (unsigned int i = 0; i < toErase.size(); ++i){
		subIt = std::find(subscriptions.begin(), subscriptions.end(), toErase[i]);
		subscriptions.erase(subIt);
	}
	toErase.clear();
}

void SubscriptionVector::cancelSubscription(const std::string & ident) {
	Poco::Mutex::ScopedLock lock(mutex);

	std::vector<std::shared_ptr<Data::Subscription>>::const_iterator subIt = subscriptions.begin();

	while (subIt != subscriptions.end())
	{
		// If no reference parameter / identifier present, renew all
		if (ident.compare((*subIt)->getNotifyTo().getReferenceParameters()) == 0)
		{
			(*subIt)->cancel();
		}
		++subIt;
	}
}

bool SubscriptionVector::renewSubscription(const std::string & ident, const std::string & expires) {
	Poco::Mutex::ScopedLock lock(mutex);

	std::vector<std::shared_ptr<Data::Subscription>>::const_iterator subIt = subscriptions.begin();
    bool success = false;
	while (subIt != subscriptions.end())
	{
		// If no reference parameter / identifier present, renew all
		if (ident.length() == 0 || ident.compare((*subIt)->getNotifyTo().getReferenceParameters()) == 0)
		{
			// Renew (mark current time, update expired value)
			(*subIt)->setTimeStamp();
			(*subIt)->setExpires(expires);
            success = true;
		}
		++subIt;
	}

    return success;
}

std::vector<std::shared_ptr<Data::Subscription>> SubscriptionVector::getActiveSubscriptions(const std::string & actionString) {
	Poco::Mutex::ScopedLock lock(mutex);

	std::vector<std::shared_ptr<Data::Subscription>> result;
	for (const auto & subscription : subscriptions) {
		// Skip subscriptions that are expired (remove them if necessary)
		if (subscription->isExpired() || subscription->isCanceled()) {
			continue;
		}

		// Check if subscription filter action matches action of this event source
		if (subscription->getFilterAction().empty() || subscription->getFilterAction() == actionString) {
			result.push_back(subscription);
		}
	}

	return result;
}

} /* namespace Dat */
} /* namespace OSCLib */
