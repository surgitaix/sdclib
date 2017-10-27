/*
 * OSCPProviderAlertConditionStateHandler.cpp
 *
 *  Created on: 05.05.2015
 *      Author: roehser
 */

#include "OSCLib/Data/OSCP/OSCPProviderAlertConditionStateHandler.h"
#include "OSCLib/Data/OSCP/MDIB/AlertConditionState.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

OSCPProviderAlertConditionStateHandler::OSCPProviderAlertConditionStateHandler() {

}

OSCPProviderAlertConditionStateHandler::~OSCPProviderAlertConditionStateHandler() {

}

InvocationState OSCPProviderAlertConditionStateHandler::onStateChangeRequest(const AlertConditionState & , const OperationInvocationContext & ) {
	log_error([] { return "Method not overridden: onStateChangeRequest(AlertConditionState)!"; });
    return InvocationState::Fail;
}

void OSCPProviderAlertConditionStateHandler::sourceHasChanged(const std::string & ) {
	// NOOP
}

void OSCPProviderAlertConditionStateHandler::updateState(const OSCLib::Data::OSCP::AlertConditionState & object) {
	notifyMDIBObjectChangedImpl(object);
}

std::string OSCPProviderAlertConditionStateHandler::getDescriptorHandle() {
    return getInitialState().getDescriptorHandle();
}

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
