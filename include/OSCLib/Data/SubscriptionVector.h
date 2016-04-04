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
 * SubscriptionVector.h
 *
 *  Created on: 29.04.2014
 *      Author: roehser
 */

#ifndef SUBSCRIPTIONVECTOR_H_
#define SUBSCRIPTIONVECTOR_H_

#include "Poco/Mutex.h"

#include <string>
#include <vector>
#include <memory>

namespace OSCLib {
namespace Data {

class Subscription;

class SubscriptionVector {
public:
	SubscriptionVector();
	virtual ~SubscriptionVector();

	void addSubscription(std::shared_ptr<Data::Subscription> subscription);
	void cleanExpiredSubscriptions();

	void cancelSubscription(const std::string & ident);
	bool renewSubscription(const std::string & ident, const std::string & expires);

	std::vector<std::shared_ptr<Data::Subscription>> getActiveSubscriptions(const std::string & actionString);

private:
	std::vector<std::shared_ptr<Data::Subscription>> subscriptions;
	Poco::Mutex mutex;
};

} /* namespace Data */
} /* namespace OSCLib */

#endif /* SUBSCRIPTIONVECTOR_H_ */
