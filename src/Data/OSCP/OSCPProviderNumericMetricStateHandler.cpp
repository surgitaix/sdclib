/*
 * OSCPProviderNumericMetricStateHandler.cpp
 *
 *  Created on: 05.05.2015
 *      Author: roehser
 */

#include "OSCLib/Data/OSCP/OSCPProviderNumericMetricStateHandler.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricState.h"
#include "OSCLib/Util/DebugOut.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

OSCPProviderNumericMetricStateHandler::OSCPProviderNumericMetricStateHandler() {

}

OSCPProviderNumericMetricStateHandler::~OSCPProviderNumericMetricStateHandler() {

}

InvocationState OSCPProviderNumericMetricStateHandler::onStateChangeRequest(const NumericMetricState & , const OperationInvocationContext & ) {
    Util::DebugOut(Util::DebugOut::Error, "OSCPProviderMDStateHandler") << "Method not overridden: onStateChangeRequest(NumericMetricState)!";
    return InvocationState::FAILED;
}

void OSCPProviderNumericMetricStateHandler::updateState(const OSCLib::Data::OSCP::NumericMetricState & object) {
	notifyMDIBObjectChangedImpl(object);
}

std::string OSCPProviderNumericMetricStateHandler::getDescriptorHandle() {
    return getInitialClonedState().getDescriptorHandle();
}

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
