/**
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  *
  */

/*
 * OSCPProviderDistributionSampleArrayMetricStateHandler.cpp
 *
 *  @Copyright (C) 2017, SurgiTAIX AG
 *  Author: buerger
 */

#include "OSCLib/Data/OSCP/OSCPProviderDistributionSampleArrayMetricStateHandler.h"
#include "OSCLib/Data/OSCP/MDIB/DistributionSampleArrayMetricState.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

OSCPProviderDistributionSampleArrayMetricStateHandler::OSCPProviderDistributionSampleArrayMetricStateHandler() {

}

OSCPProviderDistributionSampleArrayMetricStateHandler::~OSCPProviderDistributionSampleArrayMetricStateHandler() {

}

InvocationState OSCPProviderDistributionSampleArrayMetricStateHandler::onStateChangeRequest(const DistributionSampleArrayMetricState & , const OperationInvocationContext & ) {
	log_error([] { return "Method not overridden: onStateChangeRequest(NumericMetricState)!"; });
    return InvocationState::Fail;
}

void OSCPProviderDistributionSampleArrayMetricStateHandler::updateState(const OSCLib::Data::OSCP::DistributionSampleArrayMetricState & object) {
	notifyMDIBObjectChangedImpl(object);
}

std::string OSCPProviderDistributionSampleArrayMetricStateHandler::getDescriptorHandle() {
    return getInitialState().getDescriptorHandle();
}

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */


