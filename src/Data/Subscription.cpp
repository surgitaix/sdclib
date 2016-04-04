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
 *  @file Subscription.cpp
 *  @project OSCLib
 *  @date 09.08.2012
 *  @author besting
 *  @copyright (c) SurgiTAIX AG
 *
 */

#include "OSCLib/Data/Subscription.h"

#include <time.h>
#include <stdio.h>

#include "Poco/ScopedLock.h"

namespace OSCLib {
namespace Data {

Subscription::Subscription() : timeStamp(time((time_t*) 0)), canceled(false) {

}

Subscription::~Subscription()
{
}

const std::string & Subscription::getDeliveryMode() const {
	return deliveryMode;
}

const Dev::EndpointReference & Subscription::getEndTo() const {
	return endTo;
}

const std::string & Subscription::getExpires() const {
	return expires;
}

const std::string & Subscription::getFilterAction() const {
	return action;
}

const Dev::EndpointReference & Subscription::getNotifyTo() const {
	return notifyTo;
}

void Subscription::setDeliveryMode(const std::string & deliveryMode) {
	this->deliveryMode = deliveryMode;
}

void Subscription::setEndTo(const Dev::EndpointReference & endTo) {
	this->endTo = endTo;
}

void Subscription::setExpires(const std::string & expires) {
	this->expires = expires;
}

void Subscription::setFilterAction(const std::string & action) {
	this->action = action;
}

void Subscription::setNotifyTo(const Dev::EndpointReference & notifyTo) {
	this->notifyTo = notifyTo;
}

void Subscription::setTimeStamp() {
	Poco::Mutex::ScopedLock lock(mutex);
    timeStamp = time((time_t*) 0);
}

bool Subscription::isExpired() {
	Poco::Mutex::ScopedLock lock(mutex);
	if (expires.length() == 0)
		return false;
    int seconds = 0;
    int minutes = 0;
    if (sscanf(expires.c_str(), "PT%16dM%16dS", &minutes, &seconds) != 2) {
        seconds = 0;
        minutes = 0;
        if (sscanf(expires.c_str(), "PT%16dS", &seconds) != 1) {
            minutes = 0;
            seconds = 30;
        }
    }
    int duration = minutes * 60 + seconds;
	time_t now;
	now = time((time_t*) 0);
	return (now - timeStamp) > duration;
}

void Subscription::cancel() {
	canceled = true;
}

bool Subscription::isCanceled() const {
	return canceled;
}

} /* namespace Data */
} /* namespace OSCLib */
