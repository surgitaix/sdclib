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
 * OSCPProvider.cpp
 *
 *  @Copyright (C) 2014, SurgiTAIX AG
 *  Author: roehser, besting, buerger
 */

#include <memory>

#include "Poco/AutoPtr.h"
#include "Poco/Net/NetException.h"
#include "Poco/Notification.h"
#include "Poco/UUIDGenerator.h"

#include "osdm.hxx"

#include "OSCLib/OSCLibrary.h"
#include "OSCLib/Data/OSCP/OSCPConstants.h"
#include "OSCLib/Data/OSCP/OSCPProvider.h"
#include "OSCLib/Data/OSCP/OSCPProviderMDStateHandler.h"
#include "OSCLib/Data/OSCP/MDIB/ActivateOperationDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AlertConditionDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AlertConditionState.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSignalDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSignalState.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSystemDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSystemState.h"
#include "OSCLib/Data/OSCP/MDIB/ClockState.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"
#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/MDIB/EnsembleContextState.h"
#include "OSCLib/Data/OSCP/MDIB/EnumStringMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/EnumStringMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/MdsDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/MdsState.h"
#include "OSCLib/Data/OSCP/MDIB/LimitAlertConditionDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/LimitAlertConditionState.h"
#include "OSCLib/Data/OSCP/MDIB/LocationContextState.h"
#include "OSCLib/Data/OSCP/MDIB/custom/MDIBContainer.h"
#include "OSCLib/Data/OSCP/MDIB/MdDescription.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricValue.h"
#include "OSCLib/Data/OSCP/MDIB/custom/OperationInvocationContext.h"
#include "OSCLib/Data/OSCP/MDIB/OperatorContextState.h"
#include "OSCLib/Data/OSCP/MDIB/PatientContextState.h"
#include "OSCLib/Data/OSCP/MDIB/PatientContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/LocationContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/EnsembleContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/OperatorContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/WorkflowContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ScoDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/StringMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/StringMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/StringMetricValue.h"
#include "OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/SystemContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/WorkflowContextState.h"
#include "OSCLib/Data/OSCP/OSCPProviderActivateOperationHandler.h"
#include "OSCLib/Data/OSCP/OSCPProviderAlertConditionStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPProviderAlertSignalStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPProviderAlertSystemStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPProviderComponentStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPProviderClockStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPProviderContextStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPProviderEnumStringMetricStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPProviderHydraMDSStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPProviderLimitAlertConditionStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPProviderNumericMetricStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPProviderRealTimeSampleArrayMetricStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPProviderStringMetricStateHandler.h"
#include "OSCLib/Dev/DeviceCharacteristics.h"
#include "OSCLib/Util/Task.h"
#include "OSELib/DPWS/DPWS11Constants.h"
#include "OSELib/Helper/Message.h"
#include "OSELib/Helper/XercesDocumentWrapper.h"
#include "OSELib/Helper/XercesParserWrapper.h"
#include "OSELib/OSCP/DefaultOSCPSchemaGrammarProvider.h"
#include "OSCLib/Data/OSCP/OSELibProviderAdapter.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

template<class T>
class SetNotification : public Poco::Notification {
public:
	SetNotification(const T & request, const OperationInvocationContext & oic) : request(request), oic(oic) {
	}

    const T request;
    const OperationInvocationContext oic;
};

class AsyncProviderInvoker : public Util::Task, OSELib::WithLogger {
public:
	AsyncProviderInvoker(OSCPProvider & provider,
			Poco::NotificationQueue & queue) :
		WithLogger(OSELib::Log::OSCPPROVIDER),
		provider(provider),
		queue(queue){
    }

    void runImpl() {
		Poco::AutoPtr<Poco::Notification> pNf(queue.waitDequeueNotification(100));
		if (pNf) {
			try {
				if (auto n = dynamic_cast<const SetNotification<MDM::SetValue> *>(pNf.get())) {
					provider.SetValue(n->request, n->oic);
				}
				else if (auto n = dynamic_cast<const SetNotification<MDM::SetString> *>(pNf.get())) {
					provider.SetString(n->request, n->oic);
				}
				else if (auto n = dynamic_cast<const SetNotification<MDM::Activate> *>(pNf.get())) {
					provider.OnActivate(n->oic);
				}
				else if (auto n = dynamic_cast<const SetNotification<MDM::SetAlertState> *>(pNf.get())) {
					provider.SetAlertState(n->request, n->oic);
				}
				else if (auto n = dynamic_cast<const SetNotification<MDM::SetContextState> *>(pNf.get())) {
					provider.SetContextState(n->request, n->oic);
				}
				else {
					log_error([&] { return "Unknown invoke data type!"; });
				}
			}
			catch (...) {
				log_error([&] { return "Exception caught during async provider invoke."; });
			}
		}

		if (this->isInterrupted()) {
			return;
		}

		Poco::Mutex::ScopedLock lock(provider.getMutex());
		if (provider.periodicEventInterval < provider.lastPeriodicEvent.elapsed()) {
			provider.firePeriodicReportImpl(provider.getHandlesForPeriodicUpdate());
			provider.lastPeriodicEvent.update();
		}
    }

private:
    OSCPProvider & provider;
    Poco::NotificationQueue & queue;
};

template<class StateType>
bool isMetricChangeAllowed(const StateType & state, OSCPProvider & provider) {
	typename StateType::DescriptorType descriptor;
	if (!provider.getMDDescription().findDescriptor(state.getDescriptorHandle(), descriptor)) {
		return false;
	}
	if (descriptor.getMetricCategory() == MetricCategory::Msrmt) {
		return false;
	}
	if (state.hasComponentActivationState()) {
		return state.getComponentActivationState() == ComponentActivation::On;
	} else {
		return true;
	}
}

OSCPProvider::OSCPProvider() :
	WithLogger(OSELib::Log::OSCPPROVIDER),
	periodicEventInterval(10, 0)
{
	atomicTransactionId.store(0);
	mdibVersion.store(0);
    setEndpointReference(Poco::UUIDGenerator::defaultGenerator().create().toString());
    const unsigned int port(OSCLibrary::getInstance().extractFreePort());
    m_mdDescription = std::unique_ptr<MdDescription>(new MdDescription());
	_adapter = std::unique_ptr<OSELibProviderAdapter>(new OSELibProviderAdapter(*this, port));
}

OSCPProvider::~OSCPProvider() {

}

unsigned int OSCPProvider::incrementAndGetTransactionId() {
	const unsigned int result = ++atomicTransactionId;
	return result;
}

template<class T>
void OSCPProvider::enqueueInvokeNotification(const T & request, const OperationInvocationContext & oic) {
	invokeQueue.enqueueNotification(new SetNotification<T>(request, oic));
}

MDM::SetValueResponse OSCPProvider::SetValueAsync(const MDM::SetValue & request) {
	const OperationInvocationContext oic(request.OperationHandleRef(), incrementAndGetTransactionId());
	const std::string metricHandle(getMDDescription().getOperationTargetForOperationHandle(oic.operationHandle));

	auto genResponse = [this, &oic](InvocationState v) {
		notifyOperationInvoked(oic, v);
		return MDM::SetValueResponse(oic.transactionId, ConvertToCDM::convert(v), getMDIBVersion());
	};

	NumericMetricState nms;
	if (!getMdState().findState(metricHandle, nms)) {
		return genResponse(InvocationState::Fail);
	}
	if (!isMetricChangeAllowed(nms, *this)) {
		return genResponse(InvocationState::Fail);
	}

	enqueueInvokeNotification(request, oic);
	return genResponse(InvocationState::WAITING);
}

void OSCPProvider::SetValue(const MDM::SetValue & request, const OperationInvocationContext & oic) {
	const std::string metricHandle(getMDDescription().getOperationTargetForOperationHandle(oic.operationHandle));

	NumericMetricState nms;
	if (!getMdState().findState(metricHandle, nms)) {
		notifyOperationInvoked(oic, InvocationState::Fail);
		return;
	}
	if (!isMetricChangeAllowed(nms, *this)) {
		notifyOperationInvoked(oic, InvocationState::Fail);
		return;
	}

	nms.setObservedValue(NumericMetricValue().setValue(request.RequestedNumericValue()));

	const InvocationState outState(onStateChangeRequest(nms, oic));
	notifyOperationInvoked(oic, outState);

	if (outState == InvocationState::Fin) {
		// Success
		updateState(nms);
	}
}

MDM::ActivateResponse OSCPProvider::OnActivateAsync(const MDM::Activate & request) {
	const OperationInvocationContext oic(request.OperationHandleRef(), incrementAndGetTransactionId());
	notifyOperationInvoked(oic, InvocationState::WAITING);
	enqueueInvokeNotification(request, oic);
	return MDM::ActivateResponse(oic.transactionId, ConvertToCDM::convert(InvocationState::WAITING), getMDIBVersion());
}

void OSCPProvider::OnActivate(const OperationInvocationContext & oic) {
	std::map<std::string, OSCPProviderMdStateHandler *>::iterator it = stateHandlers.find(oic.operationHandle);
    if (it != stateHandlers.end()) {
    	if (OSCPProviderActivateOperationHandler * handler = dynamic_cast<OSCPProviderActivateOperationHandler *>(it->second)) {
    		const InvocationState isVal(handler->onActivateRequest(getMDIB(), oic));
    		notifyOperationInvoked(oic, isVal);
    		return;
    	}
    }
    notifyOperationInvoked(oic, InvocationState::Fail);
}

MDM::SetStringResponse OSCPProvider::SetStringAsync(const MDM::SetString & request) {
	const OperationInvocationContext oic(request.OperationHandleRef(), incrementAndGetTransactionId());
	const MdDescription mdd(getMDDescription());

	const std::string metricHandle(mdd.getOperationTargetForOperationHandle(oic.operationHandle));
	const MdState mdsc(getMdState());

	auto genResponse = [this, &oic](InvocationState v) {
		notifyOperationInvoked(oic, v);
		return MDM::SetStringResponse(oic.transactionId, ConvertToCDM::convert(v), getMDIBVersion());
	};

	{
		StringMetricState sms;
		if (mdsc.findState(metricHandle, sms)) {
            if (!isMetricChangeAllowed(sms, *this)) {
                return genResponse(InvocationState::Fail);
            }
			enqueueInvokeNotification(request, oic);
			return genResponse(InvocationState::WAITING);
		}
	}
	{
		EnumStringMetricState state;
		if (mdsc.findState(metricHandle, state)) {
			EnumStringMetricDescriptor descriptor;
			if (!mdd.findDescriptor(state.getDescriptorHandle(), descriptor)) {
				return genResponse(InvocationState::Fail);
			}
            if (!isMetricChangeAllowed(state, *this)) {
                return genResponse(InvocationState::Fail);
            }

			const std::vector<std::string> allowedValues(descriptor.getAllowedValues());
			const std::string & requestedStringVal(request.RequestedStringValue());
			std::vector<std::string>::const_iterator it = std::find(allowedValues.begin(), allowedValues.end(), requestedStringVal);
			if (it == allowedValues.end()) {
				return genResponse(InvocationState::Fail);
			}

			enqueueInvokeNotification(request, oic);
			return genResponse(InvocationState::WAITING);
		}
	}

	return genResponse(InvocationState::Fail);
}

template<class T>
void OSCPProvider::SetStringImpl(const T & state, const OperationInvocationContext & oic) {

	const InvocationState outState(onStateChangeRequest(state, oic));
	notifyOperationInvoked(oic, outState);

	if (outState == InvocationState::Fin) {
		// Success
		updateState(state);
	}
}

void OSCPProvider::SetString(const MDM::SetString & request, const OperationInvocationContext & oic) {

	const std::string & requestedStringVal(request.RequestedStringValue());

	const MdState mdsc(getMdState());
	const MdDescription mdd(getMDDescription());

	const std::string metricHandle(mdd.getOperationTargetForOperationHandle(oic.operationHandle));

	{
		StringMetricState sms;
		if (mdsc.findState(metricHandle, sms)) {
			sms.setObservedValue(StringMetricValue().setValue(requestedStringVal));
			SetStringImpl(sms, oic);
			return;
		}
	}
	{
		EnumStringMetricState state;
		if (mdsc.findState(metricHandle, state)) {
			EnumStringMetricDescriptor descriptor;
			if (!mdd.findDescriptor(state.getDescriptorHandle(), descriptor)) {
				notifyOperationInvoked(oic, InvocationState::Fail);
				return;
			}

			const std::vector<std::string> allowedValues(descriptor.getAllowedValues());
			std::vector<std::string>::const_iterator it = std::find(allowedValues.begin(), allowedValues.end(), requestedStringVal);
			if (it == allowedValues.end()) {
				notifyOperationInvoked(oic, InvocationState::Fail);
			} else {
				state.setObservedValue(StringMetricValue().setValue(*it));
				SetStringImpl(state, oic);
			}

			return;
		}
	}

	notifyOperationInvoked(oic, InvocationState::Fail);
}


template<typename StateType>
void OSCPProvider::SetAlertStateImpl(const StateType & state, const OperationInvocationContext & oic) {

	const MdDescription mdd(getMDDescription());

	typename StateType::DescriptorType descriptor;
	if (!mdd.findDescriptor(state.getDescriptorHandle(), descriptor)) {
		notifyOperationInvoked(oic, InvocationState::Fail);
		return;
	}

	const InvocationState outIS(onStateChangeRequest(state, oic));
	notifyOperationInvoked(oic, outIS);

	// Only signal changed value of metric, when invocation successful.
	if (outIS == InvocationState::Fin) {
		updateState(state);
    }
}

MDM::SetAlertStateResponse OSCPProvider::SetAlertStateAsync(const MDM::SetAlertState & request) {
	const OperationInvocationContext oic(request.OperationHandleRef(), incrementAndGetTransactionId());
	const MDM::AbstractAlertState * incomingCDMState = &(request.RequestedAlertState());

	auto genResponse = [this, &oic](InvocationState v) {
		notifyOperationInvoked(oic, v);
		return MDM::SetAlertStateResponse(oic.transactionId, ConvertToCDM::convert(v), getMDIBVersion());
	};

	const std::string targetHandle(getMDDescription().getOperationTargetForOperationHandle(oic.operationHandle));
	if (targetHandle.empty()) {
		return genResponse(InvocationState::Fail);
	}
	if ((incomingCDMState->DescriptorHandle() != targetHandle) &&
		(incomingCDMState->Handle().present() == false || incomingCDMState->Handle().get() != targetHandle)) {
		return genResponse(InvocationState::Fail);
	}

	// Cast and convert, then call into user code
	if (dynamic_cast<const MDM::AlertConditionState *>(incomingCDMState)) {
		enqueueInvokeNotification(request, oic);
		return genResponse(InvocationState::WAITING);
	} else if (dynamic_cast<const MDM::AlertSignalState *>(incomingCDMState)) {
		enqueueInvokeNotification(request, oic);
		return genResponse(InvocationState::WAITING);
	} else if (dynamic_cast<const MDM::AlertSystemState *>(incomingCDMState)) {
		enqueueInvokeNotification(request, oic);
		return genResponse(InvocationState::WAITING);
	} else if (dynamic_cast<const MDM::LimitAlertConditionState *>(incomingCDMState)) {
		enqueueInvokeNotification(request, oic);
		return genResponse(InvocationState::WAITING);
	} else {
		// cast failed.
		return genResponse(InvocationState::Fail);
	}
}

void OSCPProvider::SetAlertState(const MDM::SetAlertState & request, const OperationInvocationContext & oic) {

	const MDM::AbstractAlertState * incomingCDMState = &(request.RequestedAlertState());

	const std::string targetHandle(getMDDescription().getOperationTargetForOperationHandle(oic.operationHandle));
	if (targetHandle.empty()) {
		return notifyOperationInvoked(oic, InvocationState::Fail);
	}
	if ((incomingCDMState->DescriptorHandle() != targetHandle) &&
		(incomingCDMState->Handle().present() == false || incomingCDMState->Handle().get() != targetHandle)) {
		return notifyOperationInvoked(oic, InvocationState::Fail);
	}

	// Cast and convert, then call into user code
	if (const MDM::AlertConditionState * state = dynamic_cast<const MDM::AlertConditionState *>(incomingCDMState)) {
		SetAlertStateImpl(ConvertFromCDM::convert(*state), oic);
	} else if (const MDM::AlertSignalState * state = dynamic_cast<const MDM::AlertSignalState *>(incomingCDMState)) {
		SetAlertStateImpl(ConvertFromCDM::convert(*state), oic);
	} else if (const MDM::AlertSystemState * state = dynamic_cast<const MDM::AlertSystemState *>(incomingCDMState)) {
		SetAlertStateImpl(ConvertFromCDM::convert(*state), oic);
	} else if (const MDM::LimitAlertConditionState * state = dynamic_cast<const MDM::LimitAlertConditionState *>(incomingCDMState)) {
		SetAlertStateImpl(ConvertFromCDM::convert(*state), oic);
	} else {
		// cast failed.
		notifyOperationInvoked(oic, InvocationState::Fail);
		return;
	}
}

MDM::GetMdStateResponse OSCPProvider::GetMdState(const MDM::GetMdState & request) {
    auto sdmMdStates(ConvertToCDM::convert(getMdState()));

    if (request.HandleRef().empty()) {
        return MDM::GetMdStateResponse(getMDIBVersion(), std::move(sdmMdStates));
    } else {
    	MDM::MdState tmpmds;
    	const std::set<std::string> reqHandles(request.HandleRef().begin(), request.HandleRef().end());
    	for (const auto & nextState : sdmMdStates->State()) {
			if ((nextState.Handle().present() && reqHandles.find(nextState.Handle().get()) != reqHandles.end()) ||
				reqHandles.find(nextState.DescriptorHandle()) != reqHandles.end()) {
				tmpmds.State().push_back(nextState);
			}
    	}
    	return MDM::GetMdStateResponse(getMDIBVersion(), tmpmds);
    }
}

MDM::GetContextStatesResponse OSCPProvider::GetContextStates(const MDM::GetContextStates & request) {
	const auto states(ConvertToCDM::convert(getMdState()));

	MDM::GetContextStatesResponse contextStates(getMDIBVersion());
	for (const auto & state : states->State()) {
		if (const MDM::EnsembleContextState * s = dynamic_cast<const MDM::EnsembleContextState *>(&state)) {
			contextStates.ContextState().push_back(*s);
		} else if (const MDM::LocationContextState * s = dynamic_cast<const MDM::LocationContextState *>(&state)) {
			contextStates.ContextState().push_back(*s);
		} else if (const MDM::OperatorContextState * s = dynamic_cast<const MDM::OperatorContextState *>(&state)) {
			contextStates.ContextState().push_back(*s);
		} else if (const MDM::PatientContextState * s = dynamic_cast<const MDM::PatientContextState *>(&state)) {
			contextStates.ContextState().push_back(*s);
		} else if (const MDM::WorkflowContextState * s = dynamic_cast<const MDM::WorkflowContextState *>(&state)) {
			contextStates.ContextState().push_back(*s);
		}
	}

	if (request.HandleRef().empty()) {
		MDM::GetContextStatesResponse result(getMDIBVersion());
		for (const auto & state : contextStates.ContextState()) {
			result.ContextState().push_back(state);
		}
		return result;
	} else {
		MDM::GetContextStatesResponse result(getMDIBVersion());
		const std::set<std::string> reqHandles(request.HandleRef().begin(), request.HandleRef().end());
		for (const auto & state : contextStates.ContextState()) {
			if ((state.Handle().present() && reqHandles.find(state.Handle().get()) != reqHandles.end()) ||
				reqHandles.find(state.DescriptorHandle()) != reqHandles.end()) {
				result.ContextState().push_back(state);
			}
		}
		return result;
	}

	return MDM::GetContextStatesResponse(getMDIBVersion());
}

MDM::SetContextStateResponse OSCPProvider::SetContextStateAsync(const MDM::SetContextState & request) {
	const OperationInvocationContext oic(request.OperationHandleRef(), incrementAndGetTransactionId());

	auto genResponse = [this, &oic](InvocationState v) {
		notifyOperationInvoked(oic, v);
		return MDM::SetContextStateResponse(oic.transactionId, ConvertToCDM::convert(v), getMDIBVersion());
	};

	const std::string targetHandle(getMDDescription().getOperationTargetForOperationHandle(oic.operationHandle));
	if (targetHandle.empty()) {
		return genResponse(InvocationState::Fail);
	}

	enqueueInvokeNotification(request, oic);
	return genResponse(InvocationState::WAITING);
}

void OSCPProvider::SetContextState(const MDM::SetContextState & request, const OperationInvocationContext & oic) {
	std::vector<EnsembleContextState> ecStates;
	std::vector<LocationContextState> lcStates;
	std::vector<OperatorContextState> ocStates;
	std::vector<PatientContextState> pcStates;
	std::vector<WorkflowContextState> wcStates;

	for (const auto & nextState : request.ProposedContextState()) {
		if (const MDM::PatientContextState * state = dynamic_cast<const MDM::PatientContextState *>(&nextState)) {
			pcStates.push_back(ConvertFromCDM::convert(*state));
		}
		else if (const MDM::LocationContextState * state = dynamic_cast<const MDM::LocationContextState *>(&nextState)) {
			lcStates.push_back(ConvertFromCDM::convert(*state));
		}
		else if (const MDM::EnsembleContextState * state = dynamic_cast<const MDM::EnsembleContextState *>(&nextState)) {
			ecStates.push_back(ConvertFromCDM::convert(*state));
		}
		else if (const MDM::OperatorContextState * state = dynamic_cast<const MDM::OperatorContextState *>(&nextState)) {
			ocStates.push_back(ConvertFromCDM::convert(*state));
		}
		else if (const MDM::WorkflowContextState * state = dynamic_cast<const MDM::WorkflowContextState *>(&nextState)) {
			wcStates.push_back(ConvertFromCDM::convert(*state));
		}
	}

	for (auto & nextHandler : stateHandlers) {
		if (OSCPProviderContextStateHandler * handler = dynamic_cast<OSCPProviderContextStateHandler *>(nextHandler.second)) {
			const InvocationState outIS(handler->onStateChangeRequest(
					ecStates, lcStates, ocStates, pcStates, wcStates, oic));
			notifyOperationInvoked(oic, outIS);
			return;
		}
	}

	notifyOperationInvoked(oic, InvocationState::Fail);
}

MDM::GetMDIBResponse OSCPProvider::GetMDIB(const MDM::GetMDIB & ) {
    return MDM::GetMDIBResponse(getMDIBVersion(), ConvertToCDM::convert(getMDIB()));
}

MDM::GetMDDescriptionResponse OSCPProvider::GetMDDescription(const MDM::GetMDDescription & request) {
	auto cdmMdd(ConvertToCDM::convert(getMDDescription()));

	if (request.HandleRef().empty()) {
		return MDM::GetMDDescriptionResponse(getMDIBVersion(), std::move(cdmMdd));
	} else {
		MDM::MdDescription filteredDescription;
		for (const auto & mds : cdmMdd->MDS()) {
			if (std::find(request.HandleRef().begin(), request.HandleRef().end(), mds.Handle()) != request.HandleRef().end()) {
				filteredDescription.MDS().push_back(mds);
			}
		}
		return MDM::GetMDDescriptionResponse(getMDIBVersion(), filteredDescription);
	}
}

void OSCPProvider::updateState(const AlertSystemState & object) {
	notifyAlertEventImpl(object);
}

void OSCPProvider::updateState(const AlertSignalState & object) {
	notifyAlertEventImpl(object);
}

void OSCPProvider::updateState(const AlertConditionState & object) {
	notifyAlertEventImpl(object);
}

void OSCPProvider::updateState(const EnsembleContextState & object) {
	notifyContextEventImpl(object);
}

void OSCPProvider::updateState(const EnumStringMetricState & object) {
	evaluateAlertConditions(object.getDescriptorHandle());
	if (object.hasHandle()) {
		evaluateAlertConditions(object.getHandle());
	}
	notifyEpisodicMetricImpl(object);
}

void OSCPProvider::updateState(const LimitAlertConditionState & object) {
	notifyAlertEventImpl(object);
}

void OSCPProvider::updateState(const LocationContextState & object) {
	notifyContextEventImpl(object);
}

void OSCPProvider::updateState(const NumericMetricState & object) {
	evaluateAlertConditions(object.getDescriptorHandle());
	if (object.hasHandle()) {
		evaluateAlertConditions(object.getHandle());
	}
	notifyEpisodicMetricImpl(object);
}

void OSCPProvider::updateState(const OperatorContextState & object) {
	notifyContextEventImpl(object);
}

void OSCPProvider::updateState(const PatientContextState & object) {
	notifyContextEventImpl(object);
}

void OSCPProvider::updateState(const RealTimeSampleArrayMetricState & object) {
	incrementMDIBVersion();
	MDM::RealTimeSampleArrayMetricState cdmState = *ConvertToCDM::convert(object);

	MDM::WaveformStream waveformStream;
	waveformStream.RealTimeSampleArray().push_back(cdmState);

	_adapter->notifyEvent(waveformStream);
}

void OSCPProvider::updateState(const StringMetricState & object) {
	evaluateAlertConditions(object.getDescriptorHandle());
	if (object.hasHandle()) {
		evaluateAlertConditions(object.getHandle());
	}
	notifyEpisodicMetricImpl(object);
}

void OSCPProvider::updateState(const WorkflowContextState & object) {
	notifyContextEventImpl(object);
}

template<class T> void OSCPProvider::notifyAlertEventImpl(const T & object) {
	if (object.getDescriptorHandle().empty()) {
		log_error([&] { return "State's descriptor handle is empty, event will not be fired!"; });
		return;
	}

	incrementMDIBVersion();
	replaceState(object);
	
	MDM::AlertReportPart reportPart;
	reportPart.AlertState().push_back(ConvertToCDM::convert(object));

	MDM::EpisodicAlertReport report(getMDIBVersion());
	report.AlertReportDetail().push_back(reportPart);

	_adapter->notifyEvent(report);
}

template<class T> void OSCPProvider::notifyContextEventImpl(const T & object) {
	if (object.getDescriptorHandle().empty()) {
		log_error([&] { return "State's descriptor handle is empty, event will not be fired!"; });
		return;
	}

	incrementMDIBVersion();
	replaceState(object);
	
	MDM::ContextChangedReportPart reportPart;
    reportPart.ChangedContextState().push_back(object.getDescriptorHandle());

	MDM::EpisodicContextChangedReport report(getMDIBVersion());
	report.ReportPart().push_back(reportPart);

	_adapter->notifyEvent(report);
}

template<class T> void OSCPProvider::notifyEpisodicMetricImpl(const T & object) {
	if (object.getDescriptorHandle().empty()) {
		log_error([&] { return "State's descriptor handle is empty, event will not be fired!"; });
		return;
	}

	incrementMDIBVersion();
	replaceState(object);

	MDM::MetricReportPart mrp;
	mrp.MetricState().push_back(ConvertToCDM::convert(object));

	MDM::EpisodicMetricReport report(getMDIBVersion());
	report.ReportPart().push_back(mrp);

	_adapter->notifyEvent(report);
}

void OSCPProvider::firePeriodicReportImpl(const std::vector<std::string> & handles) {
	if (handles.empty()) {
		log_debug([&] { return "List of handles is empty, event will not be fired!"; });
		return;
	}

	Poco::Mutex::ScopedLock lock(mutex);
	const auto mdstate(ConvertToCDM::convert(getMdState()));

	MDM::AlertReportPart periodicAlertReportPart;
	MDM::ContextChangedReportPart periodicContextChangedReportPart;
	MDM::MetricReportPart periodicMetricReportPart;

	for(const auto & state: mdstate->State()) {
		if (std::find(handles.begin(), handles.end(), state.DescriptorHandle()) != handles.end()
				|| (state.Handle().present() && std::find(handles.begin(), handles.end(), state.Handle().get()) != handles.end())) {
			if (auto castedState = dynamic_cast<const MDM::AbstractAlertState *>(&state)) {
				periodicAlertReportPart.AlertState().push_back(*castedState);
			}
			if (auto castedState = dynamic_cast<const MDM::AbstractContextState *>(&state)) {
				if (state.Handle().present()) {
					periodicContextChangedReportPart.ChangedContextState().push_back(castedState->Handle().get());
				} else {
					periodicContextChangedReportPart.ChangedContextState().push_back(castedState->DescriptorHandle());
				}
			}
			if (auto castedState = dynamic_cast<const MDM::AbstractMetricState *>(&state)) {
				periodicMetricReportPart.MetricState().push_back(*castedState);
			}
		}
	}

	MDM::PeriodicAlertReport periodicAlertReport(getMDIBVersion());
	periodicAlertReport.AlertReportDetail().push_back(periodicAlertReportPart);
	_adapter->notifyEvent(periodicAlertReport);

	MDM::PeriodicContextChangedReport periodicContextReport(getMDIBVersion());
	periodicContextReport.ReportPart().push_back(periodicContextChangedReportPart);
	_adapter->notifyEvent(periodicContextReport);

	MDM::PeriodicMetricReport periodicMetricReport(getMDIBVersion());
	periodicMetricReport.ReportPart().push_back(periodicMetricReportPart);
	_adapter->notifyEvent(periodicMetricReport);
}

void OSCPProvider::setAlertConditionPresence(const std::string & alertConditionHandle, bool conditionPresence, const OperationInvocationContext & oic) {
	const MdState mdsc(getMdState());

	// Modify alert condition's presence
	AlertConditionState condState;
	LimitAlertConditionState limitCondState;
	if (mdsc.findState(alertConditionHandle, condState)) {
		condState.setPresence(conditionPresence);
		const InvocationState is(onStateChangeRequest(condState, oic));
		if (is == InvocationState::Fin) {
			// Success
			updateState(condState);
		}
	} else if (mdsc.findState(alertConditionHandle, limitCondState)) {
		limitCondState.setPresence(conditionPresence);
		const InvocationState is(onStateChangeRequest(limitCondState, oic));
		if (is == InvocationState::Fin) {
			// Success
			updateState(limitCondState);
		}
	} else {
		return;
	}

	// Search all alert signal descriptors with reference to the alert condition descriptor handle
	const std::vector<AlertSignalDescriptor> asds(getMDDescription().collectAllAlertSignalDescriptors());
	std::map<std::string, AlertSignalDescriptor> matchingDescriptors;
	for (const auto & descriptor : asds) {
		if (descriptor.getConditionSignaled() == alertConditionHandle) {
			matchingDescriptors[descriptor.getHandle()] = descriptor;
		}
	}

	// Check and modify all found alert signal states, call into state handler, if needed
	auto informUser = [this, &oic](AlertSignalState & state, const SignalPresence & presence) {
		state.setPresence(presence);
		const InvocationState is(onStateChangeRequest(state, oic));
		if (is == InvocationState::Fin) {
			updateState(state);
		}
	};

	// Search all alert signal states
	std::vector<AlertSignalState> ass(mdsc.findAlertSignalStates());
	for (auto & nextState : ass) {
		auto descriptor = matchingDescriptors.find(nextState.getDescriptorHandle());
		if (descriptor == matchingDescriptors.end()) {
			continue;
		}

		if (conditionPresence) {
			informUser(nextState, SignalPresence::On);
		} else {
			if (!nextState.hasPresence()) {
				informUser(nextState, SignalPresence::Off);
			}
			if (descriptor->second.getLatching()) {
				switch (nextState.getPresence()) {
					case SignalPresence::On: informUser(nextState, SignalPresence::Latch); break;
					case SignalPresence::Off: break;
					case SignalPresence::Ack: break;
					case SignalPresence::Latch: break;
				}
			} else {
				informUser(nextState, SignalPresence::Off);
			}
		}
	}
}

void OSCPProvider::evaluateAlertConditions(const std::string & source) {
	Poco::Mutex::ScopedLock lock(mutex);
	const MdDescription description(getMDDescription());

	std::vector<std::string> relevantDescriptors;
	for (const auto & alertCondition : description.collectAllAlertConditionDescriptors()) {
		const auto sources(alertCondition.getSources());
		if (std::find(sources.begin(), sources.end(), source) != sources.end()) {
			relevantDescriptors.push_back(alertCondition.getHandle());
		}
	}
	for (const auto & limitAlertCondition : description.collectAllLimitAlertConditionDescriptors()) {
		const auto sources(limitAlertCondition.getSources());
		if (std::find(sources.begin(), sources.end(), source) != sources.end()) {
			relevantDescriptors.push_back(limitAlertCondition.getHandle());
		}
	}

	if (relevantDescriptors.empty()) {
		return;
	}

	for (const auto & handler : stateHandlers) {
		if (OSCPProviderAlertConditionStateHandler * h = dynamic_cast<OSCPProviderAlertConditionStateHandler *>(handler.second)) {
			if (std::find(relevantDescriptors.begin(), relevantDescriptors.end(), h->getDescriptorHandle()) != relevantDescriptors.end()) {
				h->sourceHasChanged(source);
			}
		} else if (OSCPProviderLimitAlertConditionStateHandler * h = dynamic_cast<OSCPProviderLimitAlertConditionStateHandler *>(handler.second)) {
			if (std::find(relevantDescriptors.begin(), relevantDescriptors.end(), h->getDescriptorHandle()) != relevantDescriptors.end()) {
				h->sourceHasChanged(source);
			}
		}
	}
}

MDIBContainer OSCPProvider::getMDIB() {
    MDIBContainer container;
	Poco::Mutex::ScopedLock lock(mutex);
    container.setMDDescription(getMDDescription());
	container.setMdState(getMdState());
	container.setMDIBVersion(getMDIBVersion());
    return container;
}

MdDescription OSCPProvider::getMDDescription() const {
	return *m_mdDescription;
}

MdState OSCPProvider::getMdState() {
	Poco::Mutex::ScopedLock lock(mutex);
	return mdibStates;
}

void OSCPProvider::startup() {
	try {
		_adapter->start();
	} catch (const Poco::Net::NetException & e) {
		// Case: poco exception saying that the socket is not free
		// -> retry with another port
		unsigned int port(OSCLibrary::getInstance().extractFreePort());
		log_notice([&] { return "Exception: " + std::string(e.what()) + " Retrying with port: " + std::to_string(port); });

		OSCLibrary::getInstance().returnPortToPool(_adapter->getPort());
		_adapter.reset();
		_adapter = std::unique_ptr<OSELibProviderAdapter>(new OSELibProviderAdapter(*this, port));
		this->startup();
		return;
	} catch (std::runtime_error & ex_re) {
		log_error([&] { return ex_re.what(); });

	}

    // Grab all states (start with all operation states and add states from user handlers)
    Poco::Mutex::ScopedLock lock(mutex);
    mdibStates = MdState(operationStates);
    for (const auto & handler : stateHandlers) {
		if (OSCPProviderAlertConditionStateHandler * h = dynamic_cast<OSCPProviderAlertConditionStateHandler *>(handler.second)) {
			mdibStates.addState(h->getInitialState());
		} else if (OSCPProviderAlertSignalStateHandler * h = dynamic_cast<OSCPProviderAlertSignalStateHandler *>(handler.second)) {
			mdibStates.addState(h->getInitialState());
		} else if (OSCPProviderEnumStringMetricStateHandler * h = dynamic_cast<OSCPProviderEnumStringMetricStateHandler *>(handler.second)) {
			mdibStates.addState(h->getInitialState());
		} else if (OSCPProviderAlertSystemStateHandler * h = dynamic_cast<OSCPProviderAlertSystemStateHandler *>(handler.second)) {
			mdibStates.addState(h->getInitialState());
		} else if (OSCPProviderLimitAlertConditionStateHandler * h = dynamic_cast<OSCPProviderLimitAlertConditionStateHandler *>(handler.second)) {
			mdibStates.addState(h->getInitialState());
		} else if (OSCPProviderNumericMetricStateHandler * h = dynamic_cast<OSCPProviderNumericMetricStateHandler *>(handler.second)) {
			mdibStates.addState(h->getInitialState());
		} else if (OSCPProviderRealTimeSampleArrayMetricStateHandler * h = dynamic_cast<OSCPProviderRealTimeSampleArrayMetricStateHandler *>(handler.second)) {
			mdibStates.addState(h->getInitialState());
		} else if (OSCPProviderStringMetricStateHandler * h = dynamic_cast<OSCPProviderStringMetricStateHandler *>(handler.second)) {
			mdibStates.addState(h->getInitialState());
		} else if (OSCPProviderClockStateHandler * h = dynamic_cast<OSCPProviderClockStateHandler *>(handler.second)) {
			mdibStates.addState(h->getInitialState());
		} else if (OSCPProviderComponentStateHandler * h = dynamic_cast<OSCPProviderComponentStateHandler *>(handler.second)) {
			mdibStates.addState(h->getInitialState());
		} else if (OSCPProviderHydraMDSStateHandler * h = dynamic_cast<OSCPProviderHydraMDSStateHandler*>(handler.second)) {
			mdibStates.addState(h->getInitialState());
		} else if (dynamic_cast<OSCPProviderActivateOperationHandler *>(handler.second)) {
			// NOOP
		} else if (OSCPProviderContextStateHandler * h = dynamic_cast<OSCPProviderContextStateHandler *>(handler.second)) {
			for (const auto & state : h->getEnsembleContextStates()) {
				mdibStates.addState(state);
			}
			for (const auto & state : h->getLocationContextStates()) {
				mdibStates.addState(state);
			}
			for (const auto & state : h->getOperatorContextStates()) {
				mdibStates.addState(state);
			}
			for (const auto & state : h->getPatientContextStates()) {
				mdibStates.addState(state);
			}
			for (const auto & state : h->getWorkflowContextStates()) {
				mdibStates.addState(state);
			}
		} else {
    		log_fatal([&] { return "Unknown handler type! This is an implementation error in the OSCLib!"; });
    		exit(1);
   		}
	}
    providerInvoker.reset(new AsyncProviderInvoker(*this, invokeQueue));
    providerInvoker->start();
    // Validation
    {
		const xml_schema::Flags xercesFlags(xml_schema::Flags::dont_validate | xml_schema::Flags::no_xml_declaration | xml_schema::Flags::dont_initialize);
		std::ostringstream xml;
		xml_schema::NamespaceInfomap map;
		MDM::MDIBContainer(xml, *ConvertToCDM::convert(getMDIB()), map, OSELib::XML_ENCODING, xercesFlags);

		OSELib::OSCP::DefaultOSCPSchemaGrammarProvider grammarProvider;
		auto rawMessage = OSELib::Helper::Message::create(xml.str());
		auto xercesDocument = OSELib::Helper::XercesDocumentWrapper::create(*rawMessage, grammarProvider);
		std::unique_ptr<MDM::MDIB> result(MDM::MDIBContainer(xercesDocument->getDocument()));
		if (result == nullptr) {
			log_fatal([&] { return "Fatal error, can't create MDIB - schema validation error! Offending MDIB: \n" + xml.str(); });
			std::exit(1);
		}
    }
}

void OSCPProvider::shutdown() {
    if (providerInvoker) {
    	providerInvoker->interrupt();
    	providerInvoker.reset();
    }
	if (_adapter) {
		_adapter->stop();
		_adapter.reset();
	}
}

template<class T> void OSCPProvider::replaceState(const T & object) {
    Poco::Mutex::ScopedLock lock(mutex);
    // Check for existing state
    std::unique_ptr<CDM::MdState> cachedStates(ConvertToCDM::convert(mdibStates));
    CDM::MdState target;
    for (const auto & state : cachedStates->State()) {
        if (state.DescriptorHandle() == object.getDescriptorHandle() || (state.Handle().present() && object.hasHandle() && state.Handle().get() == object.getHandle())) {
            // Found, add parameter instead of current
            target.State().push_back(*ConvertToCDM::convert(object));
            continue;
        }
        // Copy
        target.State().push_back(state);
    }
    mdibStates = ConvertFromCDM::convert(target);
}


void OSCPProvider::addMDStateHandler(OSCPProviderMDStateHandler * handler) {
    handler->parentProvider = this;

    if (stateHandlers.find(handler->getDescriptorHandle()) != stateHandlers.end()) {
    	log_error([&] { return "A OSCPProvider handler for handle " + handler->getDescriptorHandle() + " already exists. It will be overridden."; });
    }

    if (auto activate_handler = dynamic_cast<OSCPProviderActivateOperationHandler *>(handler)) {
    	const MdDescription mddescription(getMDDescription());
    	for (const auto & hydra : mddescription.collectAllHydraMDSDescriptors()) {
    		if (!hydra.hasSCO()) {
    			continue;
    		}

    		const auto sco(ConvertToCDM::convert(hydra.getSCO()));
    		for (const auto & operation : sco->Operation()) {
    			if (operation.Handle() == activate_handler->getDescriptorHandle()
    					&& nullptr != dynamic_cast<const MDM::ActivateOperationDescriptor *>(&operation)) {
    				stateHandlers[handler->getDescriptorHandle()] = handler;
    				return;
    			}
    		}
    	}
    	log_error([&] { return "Could not add handler because no ActivateOperationDescriptor with matching handle was found."; });
    }
    else if (auto streamHandler = dynamic_cast<OSCPProviderRealTimeSampleArrayMetricStateHandler *>(handler)) {
    	int port = OSCLibrary::getInstance().extractFreePort();
//    	_adapter->addStreamingPort(4444);
    	// FIXME: delete after testing that streaming works on more than one address!
    	_adapter->addStreamingPort(5555);


    	stateHandlers[handler->getDescriptorHandle()] = handler;
    }
    else {
		stateHandlers[handler->getDescriptorHandle()] = handler;
	}
}


void OSCPProvider::removeMDStateHandler(OSCPProviderMDStateHandler * handler) {
    stateHandlers.erase(handler->getDescriptorHandle());
}

void OSCPProvider::setEndpointReference(const std::string & epr) {
	this->endpointReference = epr;
}


void OSCPProvider::setMDDescription(const MdDescription & mdDescription) {
	Poco::Mutex::ScopedLock lock(getMutex());
	m_mdDescription = std::make_shared<MdDescription>(mdDescription);
}

void OSCPProvider::setMDDescription(std::string xml) {
	OSELib::OSCP::DefaultOSCPSchemaGrammarProvider grammarProvider;
	auto rawMessage = OSELib::Helper::Message::create(xml);
	auto xercesDocument = OSELib::Helper::XercesDocumentWrapper::create(*rawMessage, grammarProvider);

	std::unique_ptr<MDM::MDIB> result(MDM::MDIBContainer(xercesDocument->getDocument()));

	if (result != nullptr) {
		Poco::Mutex::ScopedLock lock(getMutex());
		this->m_mdDescription.reset(new MdDescription(ConvertFromCDM::convert(result->MdDescription())));
	} else {
		log_fatal([&] { return " Fatal error, can't create MDIB - schema validation error! Offending MDIB: \n" + xml; });
		//todo: proper exeption handling
		std::exit(1);
	}

}



const std::string OSCPProvider::getEndpointReference() const {
	return endpointReference;
}

template<typename T> InvocationState OSCPProvider::onStateChangeRequest(const T & state, const OperationInvocationContext & oic) {
	// Search by state handle AND by descriptor handle
	std::map<std::string, OSCPProviderMdStateHandler *>::iterator it(stateHandlers.find(state.getDescriptorHandle()));
    if (it == stateHandlers.end() && state.hasHandle()) {
	     it = stateHandlers.find(state.getHandle());
    }
    if (it != stateHandlers.end()) {
    	if (typename T::ProviderHandlerType * handler = dynamic_cast<typename T::ProviderHandlerType *>(it->second)) {
        	return handler->onStateChangeRequest(state, oic);
    	}
    }
    return InvocationState::Fail;
}

void OSCPProvider::notifyOperationInvoked(const OperationInvocationContext & oic, Data::OSCP::InvocationState is) {
	if (oic.transactionId == 0 && oic.operationHandle.empty())
		return;

	const MDM::OperationInvokedReportPart oirPart(oic.transactionId, oic.operationHandle, ConvertToCDM::convert(is));
	MDM::OperationInvokedReport oir(getMDIBVersion());
	oir.ReportDetail().push_back(oirPart);

	_adapter->notifyEvent(oir);
}

template<class T>
void OSCPProvider::addSetOperationToSCOObjectImpl(const T & source, MdsDescriptor & ownerMDS) {
	// get sco object or create new
	std::unique_ptr<MDM::ScoDescriptor> scoDescriptor(Defaults::ScoDescriptor());
	if (ownerMDS.hasSCO()) {
		scoDescriptor = ConvertToCDM::convert(ownerMDS.getSCO());
	} else {
		// only set handle if previously created
		scoDescriptor->Handle(ownerMDS.getHandle() + "_sco");
	}

	// add operation descriptor to sco and write back to mds
	scoDescriptor->Operation().push_back(source);
	ownerMDS.setSCO(ConvertFromCDM::convert(*scoDescriptor));

	Poco::Mutex::ScopedLock lock(mutex);

	// Now add a state object for the sco descriptor to the cached states.

	std::unique_ptr<MDM::MdState> cachedOperationStates(ConvertToCDM::convert(operationStates));
	bool existingOperationStateFound(false);
	for (const auto & state : cachedOperationStates->State()) {
		if (state.DescriptorHandle() == source.Handle()) {
			if (dynamic_cast<const MDM::OperationState *>(&state)) {
				existingOperationStateFound = true;
				break;
			}
		}
	}

	if (existingOperationStateFound) {
		// NOOP
		return;
	} else {
		// add new operation state
		MDM::OperationState operationState(
				source.Handle(),
				MDM::OperatingMode::En);
		cachedOperationStates->State().push_back(operationState);
		// replace cached states by update.
		operationStates = ConvertFromCDM::convert(*cachedOperationStates);
	}
}

void OSCPProvider::addActivateOperationForDescriptor(const ActivateOperationDescriptor & descriptor, MdsDescriptor & ownerMDS) {
	addSetOperationToSCOObjectImpl(*ConvertToCDM::convert(descriptor), ownerMDS);
}

void OSCPProvider::createSetOperationForDescriptor(const AlertConditionDescriptor & descriptor, MdsDescriptor & ownerMDS) {
	const MDM::SetAlertStateOperationDescriptor setOperation(descriptor.getHandle() + "_sco", descriptor.getHandle());
	addSetOperationToSCOObjectImpl(setOperation, ownerMDS);
}

void OSCPProvider::createSetOperationForDescriptor(const AlertSignalDescriptor & descriptor, MdsDescriptor & ownerMDS) {
	const MDM::SetAlertStateOperationDescriptor setOperation(descriptor.getHandle() + "_sco", descriptor.getHandle());
	addSetOperationToSCOObjectImpl(setOperation, ownerMDS);
}

void OSCPProvider::createSetOperationForDescriptor(const AlertSystemDescriptor & descriptor, MdsDescriptor & ownerMDS) {
	const MDM::SetAlertStateOperationDescriptor setOperation(descriptor.getHandle() + "_sco", descriptor.getHandle());
	addSetOperationToSCOObjectImpl(setOperation, ownerMDS);
}

void OSCPProvider::createSetOperationForDescriptor(const EnumStringMetricDescriptor & descriptor, MdsDescriptor & ownerMDS) {
	const MDM::SetStringOperationDescriptor setOperation(descriptor.getHandle() + "_sco", descriptor.getHandle());
	addSetOperationToSCOObjectImpl(setOperation, ownerMDS);
}

void OSCPProvider::createSetOperationForDescriptor(const LimitAlertConditionDescriptor & descriptor, MdsDescriptor & ownerMDS) {
	const MDM::SetAlertStateOperationDescriptor setOperation(descriptor.getHandle() + "_sco", descriptor.getHandle());
	addSetOperationToSCOObjectImpl(setOperation, ownerMDS);
}

void OSCPProvider::createSetOperationForDescriptor(const NumericMetricDescriptor & descriptor, MdsDescriptor & ownerMDS) {
	const MDM::SetValueOperationDescriptor setOperation(descriptor.getHandle() + "_sco", descriptor.getHandle());
	addSetOperationToSCOObjectImpl(setOperation, ownerMDS);
}

void OSCPProvider::createSetOperationForDescriptor(const StringMetricDescriptor & descriptor, MdsDescriptor & ownerMDS) {
	const MDM::SetStringOperationDescriptor setOperation(descriptor.getHandle() + "_sco", descriptor.getHandle());
	addSetOperationToSCOObjectImpl(setOperation, ownerMDS);
}

template<class T>
void OSCPProvider::createSetOperationForContextDescriptor(const T & descriptor, MdsDescriptor & ownerMDS) {
	const MDM::SetContextOperationDescriptor setOperation(descriptor.getHandle() + "_sco", descriptor.getHandle());
	addSetOperationToSCOObjectImpl(setOperation, ownerMDS);
}

void OSCPProvider::createSetOperationForDescriptor(const PatientContextDescriptor & descriptor, MdsDescriptor & ownerMDS) {
	createSetOperationForContextDescriptor(descriptor, ownerMDS);
}

void OSCPProvider::createSetOperationForDescriptor(const LocationContextDescriptor & descriptor, MdsDescriptor & ownerMDS) {
	createSetOperationForContextDescriptor(descriptor, ownerMDS);
}

void OSCPProvider::createSetOperationForDescriptor(const EnsembleContextDescriptor & descriptor, MdsDescriptor & ownerMDS) {
	createSetOperationForContextDescriptor(descriptor, ownerMDS);
}

void OSCPProvider::createSetOperationForDescriptor(const OperatorContextDescriptor & descriptor, MdsDescriptor & ownerMDS) {
	createSetOperationForContextDescriptor(descriptor, ownerMDS);
}

void OSCPProvider::createSetOperationForDescriptor(const WorkflowContextDescriptor & descriptor, MdsDescriptor & ownerMDS) {
	createSetOperationForContextDescriptor(descriptor, ownerMDS);
}

const Dev::DeviceCharacteristics& OSCPProvider::getDeviceCharacteristics() const {
	return devicecharacteristics;
}

void OSCPProvider::setDeviceCharacteristics(const Dev::DeviceCharacteristics& deviceCharacteristics) {
	this->devicecharacteristics = deviceCharacteristics;
}

unsigned long long int OSCPProvider::getMDIBVersion() const {
	return mdibVersion;
}

void OSCPProvider::incrementMDIBVersion() {
	mdibVersion++;
}

Poco::Mutex & OSCPProvider::getMutex() {
	return mutex;
}

void OSCPProvider::setPeriodicEventInterval(const int seconds, const int milliseconds) {
	const Poco::Timespan interval (seconds, milliseconds);
	if (interval > Poco::Timespan(0, 250)) {
		Poco::Mutex::ScopedLock lock(mutex);
		periodicEventInterval = interval;
	}
}

std::vector<std::string> OSCPProvider::getHandlesForPeriodicUpdate() {
	Poco::Mutex::ScopedLock lock(mutex);
	return handlesForPeriodicUpdates;
}

void OSCPProvider::addHandleForPeriodicEvent(const std::string & handle) {
	Poco::Mutex::ScopedLock lock(mutex);
	handlesForPeriodicUpdates.push_back(handle);
}

void OSCPProvider::removeHandleForPeriodicEvent(const std::string & handle) {
	Poco::Mutex::ScopedLock lock(mutex);
	auto iterator = std::find(handlesForPeriodicUpdates.begin(), handlesForPeriodicUpdates.end(), handle);
	if (iterator != handlesForPeriodicUpdates.end()) {
		handlesForPeriodicUpdates.erase(iterator);
	}
}

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
