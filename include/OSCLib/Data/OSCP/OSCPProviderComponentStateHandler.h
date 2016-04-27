/*
 * OSCPProviderContextStateHandler.h
 *
 *  Created on: 29.05.2015
 *      Author: roehser
 */

#ifndef DATA_OSCP_OSCPPROVIDERCOMPONENTSTATEHANDLER_H_
#define DATA_OSCP_OSCPPROVIDERCOMPONENTSTATEHANDLER_H_

#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "OSCLib/Data/OSCP/OSCPProviderMDStateHandler.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

class OSCPProviderComponentStateHandler : public OSCPProviderMDStateHandler {
public:
	OSCPProviderComponentStateHandler();
	virtual ~OSCPProviderComponentStateHandler();

    virtual ComponentState getInitialState() = 0;

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

#endif /* DATA_OSCP_OSCPPROVIDERCOMPONENTSTATEHANDLER_H_ */
