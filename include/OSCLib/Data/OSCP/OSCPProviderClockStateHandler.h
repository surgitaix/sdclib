/*
 * OSCPProviderNumericMetricStateHandler.h
 *
 *  Created on: 05.05.2015
 *      Author: roehser
 */

#ifndef DATA_OSCP_OSCPPROVIDERCLOCKSTATEHANDLER_H_
#define DATA_OSCP_OSCPPROVIDERCLOCKSTATEHANDLER_H_

#include "OSCLib/Data/OSCP/OSCPProviderMDStateHandler.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

class OSCPProviderClockStateHandler : public OSCPProviderMDStateHandler {
public:
	OSCPProviderClockStateHandler();
	virtual ~OSCPProviderClockStateHandler();

    virtual ClockState getInitialClonedState() = 0;

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

#endif /* DATA_OSCP_OSCPPROVIDERCLOCKSTATEHANDLER_H_ */
