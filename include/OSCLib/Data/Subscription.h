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

/**
 *  @file Subscription.h
 *  @project OSCLib
 *  @date 09.08.2012
 *  @author besting
 *  @copyright (c) SurgiTAIX AG
 *
 */

#ifndef SUBSCRIPTION_H_
#define SUBSCRIPTION_H_

#include "OSCLib/Dev/EndpointReference.h"

#include <string>
#include <vector>

#include "Poco/Mutex.h"

namespace OSCLib {
namespace Data {

/**
 * @brief Class holding values for a client subscription to an event source.
 */
class Subscription {
public:
	Subscription();
	virtual ~Subscription();
    const std::string & getDeliveryMode() const;
    const Dev::EndpointReference & getEndTo() const;
    const std::string & getExpires() const;
    const std::string & getFilterAction() const;
    const Dev::EndpointReference & getNotifyTo() const;
    void setDeliveryMode(const std::string & deliveryMode);
    void setEndTo(const Dev::EndpointReference & endTo);
    void setExpires(const std::string & expires);
    void setFilterAction(const std::string & action);
    void setNotifyTo(const Dev::EndpointReference & notifyTo);
    void setTimeStamp();
    bool isExpired();
	void cancel();
	bool isCanceled() const;

private:
	Poco::Mutex mutex;
	std::string deliveryMode;
	std::string expires;
	std::string action;
	Dev::EndpointReference notifyTo;
	Dev::EndpointReference endTo;
	time_t timeStamp;
	bool canceled;
};

} /* namespace Data */
} /* namespace OSCLib */
#endif /* SUBSCRIPTION_H_ */
