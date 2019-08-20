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
 * SDCProviderStateHandler.tpp
 *
 *	Templated base class for all provider side state handlers
 *
 *  @Copyright (C) 2018, SurgiTAIX AG
 *  Author: buerger
 *
 */


// todo: decide -> kick??
#include "SDCLib/Data/SDC/MDIB/AlertConditionState.h"
#include "SDCLib/Data/SDC/MDIB/AlertSignalState.h"
#include "SDCLib/Data/SDC/MDIB/AlertSystemState.h"
#include "SDCLib/Data/SDC/MDIB/LimitAlertConditionState.h"
#include "SDCLib/Data/SDC/MDIB/LocationContextState.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricState.h"
#include "SDCLib/Data/SDC/MDIB/OperatorContextState.h"
#include "SDCLib/Data/SDC/MDIB/PatientContextState.h"
#include "SDCLib/Data/SDC/MDIB/RealTimeSampleArrayMetricState.h"
#include "SDCLib/Data/SDC/MDIB/StringMetricState.h"
#include "SDCLib/Data/SDC/MDIB/WorkflowContextState.h"

#include "SDCLib/Data/SDC/SDCProvider.h"
#include "SDCLib/Data/SDC/SDCProviderStateHandler.h"

namespace SDCLib {
namespace Data {
namespace SDC {

SDCProviderStateHandler::SDCProviderStateHandler(std::string desriptorHandle)
: OSELib::Helper::WithLogger(OSELib::Log::sdcProvider)
, descriptorHandle(desriptorHandle)
, parentProvider(nullptr)
{
}

SDCProviderStateHandler::~SDCProviderStateHandler() {
}

void SDCProviderStateHandler::notifyOperationInvoked(const OperationInvocationContext & oic, InvocationState is) {
    if (parentProvider == nullptr) {
    	log_error([] { return "Handler is used without calling SDCProvider::addMDStateHandler!"; });
    } else {
    	parentProvider->notifyOperationInvoked(oic, is);
    }
}

void SDCProviderStateHandler::setAlertConditionPresence(const std::string alertConditionHandle, bool conditionPresence, const OperationInvocationContext & oic) {
    if (parentProvider == nullptr) {
    	log_error([&] { return "Handler is used without calling SDCProvider::addMDStateHandler!"; });
    } else {
        parentProvider->setAlertConditionPresence(alertConditionHandle, conditionPresence, oic);
    }
}

std::string SDCProviderStateHandler::getDescriptorHandle() {
	return descriptorHandle;
}


template void SDCProviderStateHandler::updateState(const AlertConditionState & object);
template void SDCProviderStateHandler::updateState(const AlertSignalState & object);
template void SDCProviderStateHandler::updateState(const AlertSystemState & object);
template void SDCProviderStateHandler::updateState(const EnsembleContextState & object);
template void SDCProviderStateHandler::updateState(const EnumStringMetricState & object);
template void SDCProviderStateHandler::updateState(const LimitAlertConditionState & object);
template void SDCProviderStateHandler::updateState(const LocationContextState & object);
template void SDCProviderStateHandler::updateState(const NumericMetricState & object);
template void SDCProviderStateHandler::updateState(const OperatorContextState & object);
template void SDCProviderStateHandler::updateState(const PatientContextState & object);
template void SDCProviderStateHandler::updateState(const RealTimeSampleArrayMetricState & object);
template void SDCProviderStateHandler::updateState(const StringMetricState & object);
template void SDCProviderStateHandler::updateState(const WorkflowContextState & object);
template void SDCProviderStateHandler::updateState(const DistributionSampleArrayMetricState & object);

template<class TState>
void SDCProviderStateHandler::updateState(const TState & object) {
    if (parentProvider == nullptr) {
    	log_error([&] { return "Handler is used without calling SDCProvider::addMdStateHandler!"; });
    } else {
        parentProvider->updateState(object);
    }
}

SDCProvider & SDCProviderStateHandler::getParentProvider() {
	return *parentProvider;
}

} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */
