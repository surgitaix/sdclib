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
 *  @file EventSink.h
 *  @project OSCLib
 *  @date 10.08.2012
 *  @author besting
 *  @copyright (c) SurgiTAIX AG
 *
 */

#ifndef EVENTSINK_H_
#define EVENTSINK_H_

#include "OSCLib/Data/Operation.h"

namespace OSCLib {
namespace Data {

/**
 * @brief An instance of this class represents an event sink of a client
 * to receive events from an event source that the client subscribes to.
 */
class EventSink : public Data::Operation
{
public:
	EventSink();
	virtual ~EventSink();

    Parameters invoke(Parameters & p)
    {
        return eventReceived(p);
    }

	/**
	 * @brief Method to override to receive an event from an event source.
	 *
	 * @param p Parameters of the event source
	 *
	 * @return Parameters to send back to the source as solicit response
	 */
    virtual Parameters eventReceived(Parameters & p) = 0;
};

} /* namespace Data */
} /* namespace OSCLib */
#endif /* EVENTSINK_H_ */
