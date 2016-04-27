/*
 * OSCPProviderContextStateHandler.cpp
 *
 *  Created on: 29.05.2015
 *      Author: roehser
 */

#include "OSCLib/Data/OSCP/MDIB/ComponentState.h"
#include "OSCLib/Data/OSCP/OSCPProviderComponentStateHandler.h"
#include "OSCLib/Util/DebugOut.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

OSCPProviderComponentStateHandler::OSCPProviderComponentStateHandler() {

}

OSCPProviderComponentStateHandler::~OSCPProviderComponentStateHandler() {

}

std::string OSCPProviderComponentStateHandler::getDescriptorHandle() {
    return getInitialState().getDescriptorHandle();
}

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
