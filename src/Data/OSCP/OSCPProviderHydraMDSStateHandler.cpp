/*
 * OSCPProviderNumericMetricStateHandler.cpp
 *
 *  Created on: 05.05.2015
 *      Author: roehser
 */

#include "OSCLib/Data/OSCP/OSCPProviderHydraMDSStateHandler.h"
#include "OSCLib/Data/OSCP/MDIB/MdsState.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

OSCPProviderHydraMDSStateHandler::OSCPProviderHydraMDSStateHandler() {

}

OSCPProviderHydraMDSStateHandler::~OSCPProviderHydraMDSStateHandler() {

}

std::string OSCPProviderHydraMDSStateHandler::getDescriptorHandle() {
    return getInitialState().getDescriptorHandle();
}

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
