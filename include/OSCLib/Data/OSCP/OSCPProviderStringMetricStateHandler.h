/*
 * OSCPProviderStringMetricStateHandler.h
 *
 *  Created on: 05.05.2015
 *      Author: roehser
 */

#ifndef DATA_OSCP_OSCPPROVIDERSTRINGMETRICSTATEHANDLER_H_
#define DATA_OSCP_OSCPPROVIDERSTRINGMETRICSTATEHANDLER_H_

#include "OSCLib/Data/OSCP/OSCPProviderMdStateHandler.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

class OSCPProviderStringMetricStateHandler : public OSCPProviderMdStateHandler {
public:
	OSCPProviderStringMetricStateHandler();
	virtual ~OSCPProviderStringMetricStateHandler();

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
    virtual InvocationState onStateChangeRequest(const StringMetricState & state, const OperationInvocationContext & oic);

    void updateState(const OSCLib::Data::OSCP::StringMetricState & object);

    virtual StringMetricState getInitialState() = 0;

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

#endif /* DATA_OSCP_OSCPPROVIDERSTRINGMETRICSTATEHANDLER_H_ */
