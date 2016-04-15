/*
 * OSCPProviderNumericMetricStateHandler.cpp
 *
 *  Created on: 05.05.2015
 *      Author: roehser
 */

#include "OSCLib/Data/OSCP/OSCPProviderClockStateHandler.h"
#include "OSCLib/Data/OSCP/MDIB/ClockState.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

OSCPProviderClockStateHandler::OSCPProviderClockStateHandler() {

}

OSCPProviderClockStateHandler::~OSCPProviderClockStateHandler() {

}

std::string OSCPProviderClockStateHandler::getDescriptorHandle() {
    return getInitialClonedState().getDescriptorHandle();
}

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
