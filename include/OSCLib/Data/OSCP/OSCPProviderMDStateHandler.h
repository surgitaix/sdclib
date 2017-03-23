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
 * OSCPProviderMDStateHandler.h
 *
 *  Created on: 18.07.2014
 *      Author: roehser
 */

#ifndef OSCPPROVIDERMDSTATEHANDLER_H_
#define OSCPPROVIDERMDSTATEHANDLER_H_

#include <memory>
#include <string>

#include "Poco/Mutex.h"

#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "OSCLib/Data/OSCP/MDIB/EnumMappings.h"

#include "OSELib/Helper/WithLogger.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

class OSCPProviderMDStateHandler : public OSELib::WithLogger {
	friend class OSCPProvider;
public:
	OSCPProviderMDStateHandler();
	virtual ~OSCPProviderMDStateHandler();

    /**
    * @brief Return the handle of this handler's state.
    *
    * @return The handle
    */
    virtual std::string getDescriptorHandle() = 0;

    /**
    * @brief Notify all registered consumers about an operation changed event
    *
    * @param object The MDIB object
    */
    void notifyOperationInvoked(const OperationInvocationContext & oic, InvocationState is);

    /**
    * @brief Trigger an alert condition using a flag to indicate the condition's presence.
    *
    * Calling this method will handle all alert signals which reference this condition automatically.
    *
    * Depending on the condition's presence (true or false), alert signals will be handled as follows:
    * 1. True: the alert signal's presence state will be set ON (no matter what the previous value was)
    * 2. False: if an alert signal's presence state is currently set to ON, it will be set to LATCHED
    * However, it will never be set OFF or ACK (see notes below).
    * Due to the modification of signal states by this method, condition and signal state handlers implemented by user
    * code will be invoked. This implementation should trigger an event to inform all consumers about
    * that modification of the modified alert signal states.
    *
    * @param alertConditionHandle The handle of the alert condition state.
    * @param conditionPresence True, if the condition has been detected.
    * @param oic operation invocation context
    */
    void setAlertConditionPresence(const std::string alertConditionHandle, bool conditionPresence, const OperationInvocationContext & oic);

    OSCPProvider & getParentProvider();

protected:
    template<class T> void notifyMDIBObjectChangedImpl(const T & object);

    OSCPProvider * parentProvider;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

#endif /* OSCPPROVIDERMDSTATEHANDLER_H_ */
