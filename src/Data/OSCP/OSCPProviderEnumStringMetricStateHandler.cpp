/*
 * OSCPProviderEnumStringMetricStateHandler.cpp
 *
 *  Created on: 13.05.2015
 *      Author: roehser
 */

#include "OSCLib/Data/OSCP/OSCPProviderEnumStringMetricStateHandler.h"
#include "OSCLib/Data/OSCP/MDIB/EnumStringMetricState.h"
#include "OSCLib/Util/DebugOut.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

OSCPProviderEnumStringMetricStateHandler::OSCPProviderEnumStringMetricStateHandler() {

}

OSCPProviderEnumStringMetricStateHandler::~OSCPProviderEnumStringMetricStateHandler() {

}

InvocationState OSCPProviderEnumStringMetricStateHandler::onStateChangeRequest(const EnumStringMetricState & , const OperationInvocationContext & ) {
    Util::DebugOut(Util::DebugOut::Error, "OSCPProviderEnumStringMetricStateHandler") << "Method not overridden: onStateChangeRequest(EnumStringMetricState)!";
    return InvocationState::FAILED;
}

void OSCPProviderEnumStringMetricStateHandler::updateState(const OSCLib::Data::OSCP::EnumStringMetricState & object) {
	notifyMDIBObjectChangedImpl(object);
}

std::string OSCPProviderEnumStringMetricStateHandler::getDescriptorHandle() {
    return getInitialState().getDescriptorHandle();
}

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
