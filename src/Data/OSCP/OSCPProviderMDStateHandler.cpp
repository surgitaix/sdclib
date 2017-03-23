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
 * OSCPProviderMDStateHandler.cpp
 *
 *  @Copyright (C) 2014, SurgiTAIX AG
 *  Author: roehser, besting
 */

#include "OSCLib/Data/OSCP/MDIB/AlertConditionState.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSignalState.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSystemState.h"
#include "OSCLib/Data/OSCP/MDIB/LimitAlertConditionState.h"
#include "OSCLib/Data/OSCP/MDIB/LocationContextState.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/OperatorContextState.h"
#include "OSCLib/Data/OSCP/MDIB/PatientContextState.h"
#include "OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/StringMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/WorkflowContextState.h"

#include "OSCLib/Data/OSCP/OSCPProvider.h"
#include "OSCLib/Data/OSCP/OSCPProviderMDStateHandler.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

OSCPProviderMDStateHandler::OSCPProviderMDStateHandler() :
	WithLogger(OSELib::Log::OSCPPROVIDER),
	parentProvider(nullptr)
{
}

OSCPProviderMDStateHandler::~OSCPProviderMDStateHandler() {
}

void OSCPProviderMDStateHandler::notifyOperationInvoked(const OperationInvocationContext & oic, InvocationState is) {
    if (parentProvider == nullptr) {
    	log_error([] { return "Handler is used without calling OSCPProvider::addMDStateHandler!"; });
    } else {
    	parentProvider->notifyOperationInvoked(oic, is);
    }
}

void OSCPProviderMDStateHandler::setAlertConditionPresence(const std::string alertConditionHandle, bool conditionPresence, const OperationInvocationContext & oic) {
    if (parentProvider == nullptr) {
    	log_error([&] { return "Handler is used without calling OSCPProvider::addMDStateHandler!"; });
    } else {
        parentProvider->setAlertConditionPresence(alertConditionHandle, conditionPresence, oic);
    }
}

template void OSCPProviderMDStateHandler::notifyMDIBObjectChangedImpl(const AlertConditionState & object);
template void OSCPProviderMDStateHandler::notifyMDIBObjectChangedImpl(const AlertSignalState & object);
template void OSCPProviderMDStateHandler::notifyMDIBObjectChangedImpl(const AlertSystemState & object);
template void OSCPProviderMDStateHandler::notifyMDIBObjectChangedImpl(const EnsembleContextState & object);
template void OSCPProviderMDStateHandler::notifyMDIBObjectChangedImpl(const EnumStringMetricState & object);
template void OSCPProviderMDStateHandler::notifyMDIBObjectChangedImpl(const LimitAlertConditionState & object);
template void OSCPProviderMDStateHandler::notifyMDIBObjectChangedImpl(const LocationContextState & object);
template void OSCPProviderMDStateHandler::notifyMDIBObjectChangedImpl(const NumericMetricState & object);
template void OSCPProviderMDStateHandler::notifyMDIBObjectChangedImpl(const OperatorContextState & object);
template void OSCPProviderMDStateHandler::notifyMDIBObjectChangedImpl(const PatientContextState & object);
template void OSCPProviderMDStateHandler::notifyMDIBObjectChangedImpl(const RealTimeSampleArrayMetricState & object);
template void OSCPProviderMDStateHandler::notifyMDIBObjectChangedImpl(const StringMetricState & object);
template void OSCPProviderMDStateHandler::notifyMDIBObjectChangedImpl(const WorkflowContextState & object);

template<class T> void OSCPProviderMDStateHandler::notifyMDIBObjectChangedImpl(const T & object) {
    if (parentProvider == nullptr) {
    	log_error([&] { return "Handler is used without calling OSCPProvider::addMDStateHandler!"; });
    } else {
        parentProvider->updateState(object);
    }
}

OSCPProvider & OSCPProviderMDStateHandler::getParentProvider() {
	return *parentProvider;
}

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
