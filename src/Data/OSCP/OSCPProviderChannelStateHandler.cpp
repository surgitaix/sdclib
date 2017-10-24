/*
 * OSCPProviderChannelStateHandler.cpp
 *
 *  Created on: 24.10.17
 *      Author: buerger
 */

#include "OSCLib/Data/OSCP/OSCPProviderChannelStateHandler.h"
#include "OSCLib/Data/OSCP/MDIB/ChannelState.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

OSCPProviderChannelStateHandler::OSCPProviderChannelStateHandler() {

}

OSCPProviderChannelStateHandler::~OSCPProviderChannelStateHandler() {

}

std::string OSCPProviderChannelStateHandler::getDescriptorHandle() {
    return getInitialState().getDescriptorHandle();
}

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
