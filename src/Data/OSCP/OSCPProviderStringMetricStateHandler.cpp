/*
 * OSCPProviderStringMetricStateHandler.cpp
 *
 *  Created on: 05.05.2015
 *      Author: roehser
 */

#include "OSCLib/Data/OSCP/OSCPProviderStringMetricStateHandler.h"
#include "OSCLib/Data/OSCP/MDIB/StringMetricState.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

OSCPProviderStringMetricStateHandler::OSCPProviderStringMetricStateHandler() {

}

OSCPProviderStringMetricStateHandler::~OSCPProviderStringMetricStateHandler() {

}

InvocationState OSCPProviderStringMetricStateHandler::onStateChangeRequest(const StringMetricState & , const OperationInvocationContext & ) {
	log_error([] { return "Method not overridden: onStateChangeRequest(StringMetricState)!"; });
    return InvocationState::FAILED;
}

void OSCPProviderStringMetricStateHandler::updateState(const OSCLib::Data::OSCP::StringMetricState & object) {
	notifyMDIBObjectChangedImpl(object);
}

std::string OSCPProviderStringMetricStateHandler::getDescriptorHandle() {
    return getInitialState().getDescriptorHandle();
}

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
