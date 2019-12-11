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
 *  Modified on: 22.08.2019, baumeister
 *
 */

#include "SDCLib/Data/SDC/SDCProviderStateHandler.h"
#include "SDCLib/Data/SDC/SDCProvider.h"

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

namespace SDCLib {
namespace Data {
namespace SDC {

SDCProviderStateHandler::SDCProviderStateHandler(std::string p_desriptorHandle)
: OSELib::Helper::WithLogger(OSELib::Log::sdcProvider)
, descriptorHandle(p_desriptorHandle)
{ }

void SDCProviderStateHandler::notifyOperationInvoked(const OperationInvocationContext& p_oic, InvocationState p_is)
{
    if (parentProvider == nullptr) {
    	log_error([] { return "Handler is used without calling SDCProvider::addMDStateHandler!"; });
    } else {
    	parentProvider->notifyOperationInvoked(p_oic, p_is);
    }
}

void SDCProviderStateHandler::setAlertConditionPresence(const std::string p_alertConditionHandle, bool p_conditionPresence, const OperationInvocationContext& p_oic) {
    if (parentProvider == nullptr) {
    	log_error([&] { return "Handler is used without calling SDCProvider::addMDStateHandler!"; });
    } else {
    	parentProvider->setAlertConditionPresence(p_alertConditionHandle, p_conditionPresence, p_oic);
    }
}

std::string SDCProviderStateHandler::getDescriptorHandle() const
{
	return descriptorHandle;
}


template void SDCProviderStateHandler::updateState(const AlertConditionState& p_object);
template void SDCProviderStateHandler::updateState(const AlertSignalState& p_object);
template void SDCProviderStateHandler::updateState(const AlertSystemState& p_object);
template void SDCProviderStateHandler::updateState(const EnsembleContextState& p_object);
template void SDCProviderStateHandler::updateState(const EnumStringMetricState& p_object);
template void SDCProviderStateHandler::updateState(const LimitAlertConditionState& p_object);
template void SDCProviderStateHandler::updateState(const LocationContextState& p_object);
template void SDCProviderStateHandler::updateState(const NumericMetricState& p_object);
template void SDCProviderStateHandler::updateState(const OperatorContextState& p_object);
template void SDCProviderStateHandler::updateState(const PatientContextState& p_object);
template void SDCProviderStateHandler::updateState(const RealTimeSampleArrayMetricState& p_object);
template void SDCProviderStateHandler::updateState(const StringMetricState& p_object);
template void SDCProviderStateHandler::updateState(const WorkflowContextState& p_object);
template void SDCProviderStateHandler::updateState(const DistributionSampleArrayMetricState& p_object);

template<class TState>
void SDCProviderStateHandler::updateState(const TState& p_object)
{
    if (parentProvider == nullptr)
    {
    	log_error([&] { return "Handler is used without calling SDCProvider::addMdStateHandler!"; });
    }
    else
    {
    	parentProvider->updateState(p_object);
    }
}

SDCProvider& SDCProviderStateHandler::getParentProvider()
{
	assert(nullptr != parentProvider && "Handler is used without calling SDCProvider::addMdStateHandler!");
	return *parentProvider; // FIXME: Check on nullptr?!
}

}
}
}
