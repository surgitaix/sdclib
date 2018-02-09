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
 * SDCConsumerAlertConditionStateHandler.h
 *
 *  @Copyright (C) 2018, SurgiTAIX AG
 *  Author: buerger
 */

#ifndef SDCCONSUMERMDSTATEHANDLER_H_
#define SDCCONSUMERMDSTATEHANDLER_H_

#include "OSCLib/Data/SDC/SDCConsumerOperationInvokedHandler.h"

namespace OSCLib {
namespace Data {
namespace SDC {

template<typename TState>
class SDCConsumerMDStateHandler: public SDCConsumerOperationInvokedHandler {
public:
	SDCConsumerMDStateHandler(const std::string handle) : SDCConsumerOperationInvokedHandler(handle) {}
	virtual ~SDCConsumerMDStateHandler() {}

	typedef TState StateType;

    /**
    * @brief Receive notifications about the state.
    *
    * @param state The state on which a notification event occurred.
    */
    virtual void onStateChanged(const TState & state) = 0;
};

} /* namespace SDC */
} /* namespace Data */
} /* namespace OSCLib */

#endif /* SDCCONSUMERMDSTATEHANDLER_H_ */
