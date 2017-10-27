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
 * OSCPConsumerEventHandler.h
 *
 *  @Copyright (C) 2014, SurgiTAIX AG
 *  Author: roehser, besting
 */

#ifndef OSCPCONSUMEREVENTHANDLER_H_
#define OSCPCONSUMEREVENTHANDLER_H_

#include <string>
#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/MDIB/MDIB-fwd.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

class OSCPConsumerEventHandler {
public:
	OSCPConsumerEventHandler();
    virtual ~OSCPConsumerEventHandler();

    /**
    * @brief Receive notifications about the invocation state.
    *
    * @param transactionId The transaction id.
    * @param is The invocation state.
    */
    virtual void onOperationInvoked(const OperationInvocationContext & oic, InvocationState is);

    /**
    * @brief Define the descriptor handle.
    *
    * @return The handle
    */
    virtual std::string getHandle() = 0;

};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

#endif /* OSCPCONSUMEREVENTHANDLER_H_ */
