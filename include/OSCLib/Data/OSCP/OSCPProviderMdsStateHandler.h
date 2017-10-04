/*
 * OSCPProviderNumericMetricStateHandler.h
 *
 *  Created on: 05.05.2015
 *      Author: roehser
 */

#ifndef DATA_OSCP_OSCPProviderMdsStateHandler_H_
#define DATA_OSCP_OSCPProviderMdsStateHandler_H_

#include "OSCLib/Data/OSCP/OSCPProviderMdStateHandler.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

class OSCPProviderMdsStateHandler : public OSCPProviderMdStateHandler {
public:
	OSCPProviderMdsStateHandler();
	virtual ~OSCPProviderMdsStateHandler();

    virtual MdsState getInitialState() = 0;

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

#endif /* DATA_OSCP_OSCPProviderMdsStateHandler_H_ */
