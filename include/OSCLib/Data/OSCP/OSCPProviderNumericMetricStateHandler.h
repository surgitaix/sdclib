/*
 * OSCPProviderNumericMetricStateHandler.h
 *
 *  Created on: 05.05.2015
 *      Author: roehser
 */

#ifndef DATA_OSCP_OSCPPROVIDERNUMERICMETRICSTATEHANDLER_H_
#define DATA_OSCP_OSCPPROVIDERNUMERICMETRICSTATEHANDLER_H_

#include "OSCLib/Data/OSCP/OSCPProviderMDStateHandler.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

class OSCPProviderNumericMetricStateHandler : public OSCPProviderMDStateHandler {
public:
	OSCPProviderNumericMetricStateHandler();
	virtual ~OSCPProviderNumericMetricStateHandler();

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
    virtual InvocationState onStateChangeRequest(const NumericMetricState & state, const OperationInvocationContext & oic);

    void updateState(const OSCLib::Data::OSCP::NumericMetricState & object);

    virtual NumericMetricState getInitialState() = 0;

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

#endif /* DATA_OSCP_OSCPPROVIDERNUMERICMETRICSTATEHANDLER_H_ */
