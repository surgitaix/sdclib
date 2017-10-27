/*
 * OSCPProviderAlertSystemStateHandler.cpp
 *
 *  Created on: 05.05.2015
 *      Author: roehser
 */

#include "OSCLib/Data/OSCP/OSCPProviderAlertSystemStateHandler.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSystemState.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

OSCPProviderAlertSystemStateHandler::OSCPProviderAlertSystemStateHandler() {

}

OSCPProviderAlertSystemStateHandler::~OSCPProviderAlertSystemStateHandler() {

}

InvocationState OSCPProviderAlertSystemStateHandler::onStateChangeRequest(const AlertSystemState & , const OperationInvocationContext & ) {
	log_error([] { return "Method not overridden: onStateChangeRequest(AlertSystemState)!"; });
    return InvocationState::Fail;
}

void OSCPProviderAlertSystemStateHandler::updateState(const OSCLib::Data::OSCP::AlertSystemState & object) {
	notifyMDIBObjectChangedImpl(object);
}

std::string OSCPProviderAlertSystemStateHandler::getDescriptorHandle() {
    return getInitialState().getDescriptorHandle();
}

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
