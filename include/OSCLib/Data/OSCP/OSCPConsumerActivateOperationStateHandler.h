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
 * OSCPConsumerActivateOperationStateHandler.h
 *
 *  @Copyright (C) 2017, SurgiTAIX AG
 *  Author: buerger
 */

#ifndef INCLUDE_OSCLIB_DATA_OSCP_OSCPCONSUMERACTIVATEOPERATIONSTATEHANDLER_H_
#define INCLUDE_OSCLIB_DATA_OSCP_OSCPCONSUMERACTIVATEOPERATIONSTATEHANDLER_H_

#include "OSCLib/Data/OSCP/OSCPConsumerEventHandler.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

class OSCPConsumerActivateOperationStateHandler: public OSCPConsumerEventHandler {
public:
	OSCPConsumerActivateOperationStateHandler() {}
	virtual ~OSCPConsumerActivateOperationStateHandler() {}

	typedef ActivateOperationState StateType;

    /**
    * @brief Receive notifications about the activation state of a component (on, not ready, standby, off)
    *
    * @param state The state on which a notification event occurred.
    */
    virtual void onStateChanged(const AlertConditionState & state) = 0;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

#endif /* INCLUDE_OSCLIB_DATA_OSCP_OSCPCONSUMERACTIVATEOPERATIONSTATEHANDLER_H_ */
