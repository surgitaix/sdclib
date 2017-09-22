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
#include "OSCLib/Data/OSCP/OSCPProviderMdStateHandler.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

OSCPProviderMdStateHandler::OSCPProviderMdStateHandler() :
	WithLogger(OSELib::Log::OSCPPROVIDER),
	parentProvider(nullptr)
{
}

OSCPProviderMdStateHandler::~OSCPProviderMdStateHandler() {
}

void OSCPProviderMdStateHandler::notifyOperationInvoked(const OperationInvocationContext & oic, InvocationState is) {
    if (parentProvider == nullptr) {
    	log_error([] { return "Handler is used without calling OSCPProvider::addMDStateHandler!"; });
    } else {
    	parentProvider->notifyOperationInvoked(oic, is);
    }
}

void OSCPProviderMdStateHandler::setAlertConditionPresence(const std::string alertConditionHandle, bool conditionPresence, const OperationInvocationContext & oic) {
    if (parentProvider == nullptr) {
    	log_error([&] { return "Handler is used without calling OSCPProvider::addMDStateHandler!"; });
    } else {
        parentProvider->setAlertConditionPresence(alertConditionHandle, conditionPresence, oic);
    }
}

template void OSCPProviderMdStateHandler::notifyMDIBObjectChangedImpl(const AlertConditionState & object);
template void OSCPProviderMdStateHandler::notifyMDIBObjectChangedImpl(const AlertSignalState & object);
template void OSCPProviderMdStateHandler::notifyMDIBObjectChangedImpl(const AlertSystemState & object);
template void OSCPProviderMdStateHandler::notifyMDIBObjectChangedImpl(const EnsembleContextState & object);
template void OSCPProviderMdStateHandler::notifyMDIBObjectChangedImpl(const EnumStringMetricState & object);
template void OSCPProviderMdStateHandler::notifyMDIBObjectChangedImpl(const LimitAlertConditionState & object);
template void OSCPProviderMdStateHandler::notifyMDIBObjectChangedImpl(const LocationContextState & object);
template void OSCPProviderMdStateHandler::notifyMDIBObjectChangedImpl(const NumericMetricState & object);
template void OSCPProviderMdStateHandler::notifyMDIBObjectChangedImpl(const OperatorContextState & object);
template void OSCPProviderMdStateHandler::notifyMDIBObjectChangedImpl(const PatientContextState & object);
template void OSCPProviderMdStateHandler::notifyMDIBObjectChangedImpl(const RealTimeSampleArrayMetricState & object);
template void OSCPProviderMdStateHandler::notifyMDIBObjectChangedImpl(const StringMetricState & object);
template void OSCPProviderMdStateHandler::notifyMDIBObjectChangedImpl(const WorkflowContextState & object);

template<class T> void OSCPProviderMdStateHandler::notifyMDIBObjectChangedImpl(const T & object) {
    if (parentProvider == nullptr) {
    	log_error([&] { return "Handler is used without calling OSCPProvider::addMDStateHandler!"; });
    } else {
        parentProvider->updateState(object);
    }
}

OSCPProvider & OSCPProviderMdStateHandler::getParentProvider() {
	return *parentProvider;
}

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
