/*
 * OSCPProviderAlertSignalStateHandler.h
 *
 *  Created on: 05.05.2015
 *      Author: roehser
 */

#ifndef DATA_OSCP_OSCPPROVIDERALERTSIGNALSTATEHANDLER_H_
#define DATA_OSCP_OSCPPROVIDERALERTSIGNALSTATEHANDLER_H_

#include "OSCLib/Data/OSCP/OSCPProviderMDStateHandler.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

class OSCPProviderAlertSignalStateHandler : public OSCPProviderMDStateHandler {
public:
	OSCPProviderAlertSignalStateHandler();
	virtual ~OSCPProviderAlertSignalStateHandler();

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
    virtual InvocationState onStateChangeRequest(const AlertSignalState & state, const OperationInvocationContext & oic);

    void updateState(const OSCLib::Data::OSCP::AlertSignalState & object);

    virtual AlertSignalState getInitialClonedState() = 0;

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

#endif /* DATA_OSCP_OSCPPROVIDERALERTSIGNALSTATEHANDLER_H_ */
