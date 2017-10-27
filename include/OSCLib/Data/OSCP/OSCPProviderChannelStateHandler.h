/*
 * OSCPProviderChannelStateHandler.h
 *
 *  Created on: 24.10.17
 *      Author: buerger
 */

#ifndef DATA_OSCP_OSCPProviderChannelStateHandler_H_
#define DATA_OSCP_OSCPProviderChannelStateHandler_H_

#include "OSCLib/Data/OSCP/OSCPProviderMdStateHandler.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

class OSCPProviderChannelStateHandler : public OSCPProviderMdStateHandler {
public:
	OSCPProviderChannelStateHandler();
	virtual ~OSCPProviderChannelStateHandler();

    virtual ChannelState getInitialState() = 0;

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

#endif /* DATA_OSCP_OSCPProviderChannelStateHandler_H_ */
