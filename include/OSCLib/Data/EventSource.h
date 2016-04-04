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
 *  @file EventSource.h
 *  @project OSCLib
 *  @date 08.08.2012
 *  @author besting
 *  @copyright (c) SurgiTAIX AG
 *
 */

#ifndef EVENTSOURCE_H_
#define EVENTSOURCE_H_

#include "Operation.h"

namespace OSCLib {
namespace Data {

/**
 * @brief An instance of this class represents an event source of a service
 * that a client can subscribe to.
 */
class EventSource : public OSCLib::Data::Operation
{
public:

	typedef enum
	{
		NOTIFICATION,
		SOLICIT_RESPONSE
	} EventType;

	EventSource();
	virtual ~EventSource();

	/**
	 * @brief Get the event type.
	 *
	 * @return The event type
	 */
	EventSource::EventType getEventType();

	/**
	 * @brief Fire an event to all subscribed sinks.
	 *
	 * @param p Parameters for the event
	 * @return Number of event sinks that have been notified.
	 */
	unsigned int fire(Parameters& p);

	/**
	 * @brief Fire an event using multicast
	 *
	 * @param p Parameters for the event
	 * @return Number of event sinks that have been notified.
	 */
	unsigned int mcast(Parameters& p, const std::string handle);

    Parameters invoke(Parameters & p);

	virtual std::string getDefaultInputAction() const;
	virtual std::string getDefaultOutputAction() const;

	/**
	 * @brief Method to override to receive a solicit response.
	 *
	 * @param p Parameters of the response send from the event sink back
	 */
    virtual void responseReceived(Parameters & p) = 0;
};

} /* namespace Data */
} /* namespace OSCLib */
#endif /* EVENTSOURCE_H_ */
