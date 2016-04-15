/*
 * OSCPProviderLimitAlertConditionStateHandler.cpp
 *
 *  Created on: 05.05.2015
 *      Author: roehser
 */

#include "OSCLib/Data/OSCP/OSCPProviderLimitAlertConditionStateHandler.h"
#include "OSCLib/Data/OSCP/MDIB/LimitAlertConditionState.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

OSCPProviderLimitAlertConditionStateHandler::OSCPProviderLimitAlertConditionStateHandler() {

}

OSCPProviderLimitAlertConditionStateHandler::~OSCPProviderLimitAlertConditionStateHandler() {

}

InvocationState OSCPProviderLimitAlertConditionStateHandler::onStateChangeRequest(const LimitAlertConditionState & , const OperationInvocationContext & ) {
	log_error([] { return "Method not overridden: onStateChangeRequest(LimitAlertConditionState)!"; });
    return InvocationState::FAILED;
}

void OSCPProviderLimitAlertConditionStateHandler::sourceHasChanged(const std::string & ) {
	// NOOP
}

void OSCPProviderLimitAlertConditionStateHandler::updateState(const OSCLib::Data::OSCP::LimitAlertConditionState & object) {
	notifyMDIBObjectChangedImpl(object);
}

std::string OSCPProviderLimitAlertConditionStateHandler::getDescriptorHandle() {
    return getInitialClonedState().getDescriptorHandle();
}

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
