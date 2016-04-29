/*
 * OSCPProviderAlertSystemStateHandler.h
 *
 *  Created on: 05.05.2015
 *      Author: roehser
 */

#ifndef DATA_OSCP_OSCPPROVIDERALERTSYSTEMSTATEHANDLER_H_
#define DATA_OSCP_OSCPPROVIDERALERTSYSTEMSTATEHANDLER_H_

#include "OSCLib/Data/OSCP/OSCPProviderMDStateHandler.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

class OSCPProviderAlertSystemStateHandler : public OSCPProviderMDStateHandler {
public:
	OSCPProviderAlertSystemStateHandler();
	virtual ~OSCPProviderAlertSystemStateHandler();

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
    virtual InvocationState onStateChangeRequest(const AlertSystemState & state, const OperationInvocationContext & oic);

    void updateState(const OSCLib::Data::OSCP::AlertSystemState & object);

    virtual AlertSystemState getInitialState() = 0;

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

#endif /* DATA_OSCP_OSCPPROVIDERALERTSYSTEMSTATEHANDLER_H_ */
