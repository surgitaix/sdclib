/*
 * OSCPProviderMdsStateHandler.cpp
 *
 *  Created on: 05.05.2015
 *      Author: roehser
 */

#include "OSCLib/Data/OSCP/OSCPProviderMdsStateHandler.h"
#include "OSCLib/Data/OSCP/MDIB/MdsState.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

OSCPProviderMdsStateHandler::OSCPProviderMdsStateHandler() {

}

OSCPProviderMdsStateHandler::~OSCPProviderMdsStateHandler() {

}

std::string OSCPProviderMdsStateHandler::getDescriptorHandle() {
    return getInitialState().getDescriptorHandle();
}

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
