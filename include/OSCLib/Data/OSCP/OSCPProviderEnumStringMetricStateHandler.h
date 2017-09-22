/*
 * OSCPProviderEnumStringMetricStateHandler.h
 *
 *  Created on: 13.05.2015
 *      Author: roehser
 */

#ifndef OSCLIB_DATA_OSCP_OSCPPROVIDERENUMSTRINGMETRICSTATEHANDLER_H_
#define OSCLIB_DATA_OSCP_OSCPPROVIDERENUMSTRINGMETRICSTATEHANDLER_H_

#include "OSCLib/Data/OSCP/OSCPProviderMdStateHandler.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

class OSCPProviderEnumStringMetricStateHandler : public OSCPProviderMdStateHandler {
public:
	OSCPProviderEnumStringMetricStateHandler();
	virtual ~OSCPProviderEnumStringMetricStateHandler();

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
    virtual InvocationState onStateChangeRequest(const EnumStringMetricState & state, const OperationInvocationContext & oic);

    void updateState(const OSCLib::Data::OSCP::EnumStringMetricState & object);

    virtual EnumStringMetricState getInitialState() = 0;

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

#endif /* OSCLIB_DATA_OSCP_OSCPPROVIDERENUMSTRINGMETRICSTATEHANDLER_H_ */
