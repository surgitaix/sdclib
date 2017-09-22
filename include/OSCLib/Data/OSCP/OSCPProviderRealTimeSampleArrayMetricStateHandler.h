/*
 * OSCPProviderRealTimeSampleArrayMetricStateHandler.h
 *
 *  Created on: 05.05.2015
 *      Author: roehser
 */

#ifndef DATA_OSCP_OSCPPROVIDERREALTIMESAMPLEARRAYMETRICSTATEHANDLER_H_
#define DATA_OSCP_OSCPPROVIDERREALTIMESAMPLEARRAYMETRICSTATEHANDLER_H_

#include "OSCLib/Data/OSCP/OSCPProviderMdStateHandler.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

class OSCPProviderRealTimeSampleArrayMetricStateHandler : public OSCPProviderMdStateHandler {
public:
	OSCPProviderRealTimeSampleArrayMetricStateHandler();
	virtual ~OSCPProviderRealTimeSampleArrayMetricStateHandler();

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
    virtual InvocationState onStateChangeRequest(const RealTimeSampleArrayMetricState & state, const OperationInvocationContext & oic);

    void updateState(const OSCLib::Data::OSCP::RealTimeSampleArrayMetricState & object);

    virtual RealTimeSampleArrayMetricState getInitialState() = 0;

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

#endif /* DATA_OSCP_OSCPPROVIDERREALTIMESAMPLEARRAYMETRICSTATEHANDLER_H_ */
