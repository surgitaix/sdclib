/*
 * OSCPProviderVmdStateHandler.cpp
 *
 *  Created on: 24.10.2017
 *      Author: buerger
 */

#include "OSCLib/Data/OSCP/OSCPProviderVmdStateHandler.h"
#include "OSCLib/Data/OSCP/MDIB/VmdState.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

OSCPProviderVmdStateHandler::OSCPProviderVmdStateHandler() {

}

OSCPProviderVmdStateHandler::~OSCPProviderVmdStateHandler() {

}

std::string OSCPProviderVmdStateHandler::getDescriptorHandle() {
    return getInitialState().getDescriptorHandle();
}

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
