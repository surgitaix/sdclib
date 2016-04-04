/*
 * OSCPProviderAlertConditionStateHandler.h
 *
 *  Created on: 05.05.2015
 *      Author: roehser
 */

#ifndef DATA_OSCP_OSCPPROVIDERALERTCONDITIONSTATEHANDLER_H_
#define DATA_OSCP_OSCPPROVIDERALERTCONDITIONSTATEHANDLER_H_

#include "OSCLib/Data/OSCP/OSCPProviderMDStateHandler.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

class OSCPProviderAlertConditionStateHandler : public OSCPProviderMDStateHandler {
public:
	OSCPProviderAlertConditionStateHandler();
	virtual ~OSCPProviderAlertConditionStateHandler();

    /**
    * @brief Called on incoming consumer request for a state change
    *
    * Notes:
    * - The consumer will wait for this method to complete.
    *
    * @param state The requested state containing fields to be updated.
    *
    * @return invocation state
    */
    virtual InvocationState onStateChangeRequest(const AlertConditionState & state, const OperationInvocationContext & oic);
    virtual void sourceHasChanged(const std::string & sourceHandle);

    void updateState(const OSCLib::Data::OSCP::AlertConditionState & object);

    /**
    * @brief Return the state of this handler.
    *
    * @return The state
    */
    virtual AlertConditionState getInitialClonedState() = 0;

    /**
    * @brief Return the handle of this handler's state.
    *
    * @return The handle
    */
    std::string getDescriptorHandle();
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

#endif /* DATA_OSCP_OSCPPROVIDERALERTCONDITIONSTATEHANDLER_H_ */
