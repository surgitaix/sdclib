/*
 * OSCPProviderVmdStateHandler.h
 *
 *  Created on: 24.10.2017
 *      Author: buerger
 */

#ifndef DATA_OSCP_OSCPProviderVMDStateHandler_H_
#define DATA_OSCP_OSCPProviderVmdStateHandler_H_

#include "OSCLib/Data/OSCP/OSCPProviderMdStateHandler.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

class OSCPProviderVmdStateHandler : public OSCPProviderMdStateHandler {
public:
	OSCPProviderVmdStateHandler();
	virtual ~OSCPProviderVmdStateHandler();

    virtual VmdState getInitialState() = 0;

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

#endif /* DATA_OSCP_OSCPProviderVmdStateHandler_H_ */
