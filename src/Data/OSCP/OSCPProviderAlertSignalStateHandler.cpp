/*
 * OSCPProviderAlertSignalStateHandler.cpp
 *
 *  Created on: 05.05.2015
 *      Author: roehser
 */

#include "OSCLib/Data/OSCP/OSCPProviderAlertSignalStateHandler.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSignalState.h"
#include "OSCLib/Util/DebugOut.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

OSCPProviderAlertSignalStateHandler::OSCPProviderAlertSignalStateHandler() {

}

OSCPProviderAlertSignalStateHandler::~OSCPProviderAlertSignalStateHandler() {

}

InvocationState OSCPProviderAlertSignalStateHandler::onStateChangeRequest(const AlertSignalState & , const OperationInvocationContext & ) {
    Util::DebugOut(Util::DebugOut::Error, "OSCPProviderMDStateHandler") << "Method not overridden: onStateChangeRequest(AlertSignalState)!";
    return InvocationState::FAILED;
}

void OSCPProviderAlertSignalStateHandler::updateState(const OSCLib::Data::OSCP::AlertSignalState & object) {
	notifyMDIBObjectChangedImpl(object);
}

std::string OSCPProviderAlertSignalStateHandler::getDescriptorHandle() {
    return getInitialState().getDescriptorHandle();
}

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
