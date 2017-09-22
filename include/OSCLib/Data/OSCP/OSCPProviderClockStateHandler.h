/*
 * OSCPProviderNumericMetricStateHandler.h
 *
 *  Created on: 05.05.2015
 *      Author: roehser
 */

#ifndef DATA_OSCP_OSCPPROVIDERCLOCKSTATEHANDLER_H_
#define DATA_OSCP_OSCPPROVIDERCLOCKSTATEHANDLER_H_

#include "OSCLib/Data/OSCP/OSCPProviderMdStateHandler.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

class OSCPProviderClockStateHandler : public OSCPProviderMdStateHandler {
public:
	OSCPProviderClockStateHandler();
	virtual ~OSCPProviderClockStateHandler();

    virtual ClockState getInitialState() = 0;

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
