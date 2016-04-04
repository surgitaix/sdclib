/*
 * OSCPProviderNumericMetricStateHandler.cpp
 *
 *  Created on: 05.05.2015
 *      Author: roehser
 */

#include "OSCLib/Data/OSCP/OSCPProviderHydraMDSStateHandler.h"
#include "OSCLib/Data/OSCP/MDIB/HydraMDSState.h"
#include "OSCLib/Util/DebugOut.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

OSCPProviderHydraMDSStateHandler::OSCPProviderHydraMDSStateHandler() {

}

OSCPProviderHydraMDSStateHandler::~OSCPProviderHydraMDSStateHandler() {

}

std::string OSCPProviderHydraMDSStateHandler::getDescriptorHandle() {
    return getInitialClonedState().getDescriptorHandle();
}

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
