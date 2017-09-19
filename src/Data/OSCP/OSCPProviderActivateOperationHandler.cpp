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
 * OSCPProviderOperationHandler.cpp
 *
 *  @Copyright (C) 2015, SurgiTAIX AG
 *  Author: besting, roehser
 */

#include "OSCLib/Data/OSCP/OSCPProviderActivateOperationHandler.h"
#include "OSCLib/Data/OSCP/MDIB/AlertConditionState.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSignalState.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSystemState.h"
#include "OSCLib/Data/OSCP/MDIB/LimitAlertConditionState.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/StringMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/custom/MDIBContainer.h"
#include "OSCLib/Data/OSCP/OSCPProvider.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

OSCPProviderActivateOperationHandler::OSCPProviderActivateOperationHandler() {

}

OSCPProviderActivateOperationHandler::~OSCPProviderActivateOperationHandler() {

}

InvocationState OSCPProviderActivateOperationHandler::onActivateRequest(const MDIBContainer & , const OperationInvocationContext & ) {
	log_error([] { return "Method not overridden: onActivateRequest()!"; });
    return InvocationState::Fail;
}

void OSCPProviderActivateOperationHandler::updateState(const OSCLib::Data::OSCP::NumericMetricState & object) {
	notifyMDIBObjectChangedImpl(object);
}

void OSCPProviderActivateOperationHandler::updateState(const OSCLib::Data::OSCP::RealTimeSampleArrayMetricState & object) {
	notifyMDIBObjectChangedImpl(object);
}

void OSCPProviderActivateOperationHandler::updateState(const OSCLib::Data::OSCP::StringMetricState & object) {
	notifyMDIBObjectChangedImpl(object);
}

void OSCPProviderActivateOperationHandler::updateState(const OSCLib::Data::OSCP::AlertConditionState & object) {
	notifyMDIBObjectChangedImpl(object);
}

void OSCPProviderActivateOperationHandler::updateState(const OSCLib::Data::OSCP::AlertSystemState & object) {
	notifyMDIBObjectChangedImpl(object);
}

void OSCPProviderActivateOperationHandler::updateState(const OSCLib::Data::OSCP::AlertSignalState & object) {
	notifyMDIBObjectChangedImpl(object);
}

void OSCPProviderActivateOperationHandler::updateState(const OSCLib::Data::OSCP::LimitAlertConditionState & object) {
	notifyMDIBObjectChangedImpl(object);
}

template<class T> void OSCPProviderActivateOperationHandler::notifyMDIBObjectChangedImpl(const T & object) {
    if (parentProvider == nullptr) {
    	log_error([] { return "Handler is used without calling OSCPProvider::addMDStateHandler!"; });
    } else {
        parentProvider->updateState(object);
    }
}

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
