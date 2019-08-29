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
 * SDCProvider.cpp
 *
 *  @Copyright (C) 2018, SurgiTAIX AG
 *  Author: roehser, besting, buerger
 *  Modified on: 29.08.2019, baumeister
 *
 */

#include "SDCLib/Data/SDC/SDCProvider.h"
#include "SDCLib/Data/SDC/SDCProviderAdapter.h"
#include "SDCLib/Data/SDC/SDCProviderStateHandler.h"
#include "SDCLib/Data/SDC/SDCProviderActivateOperationHandler.h"
#include "SDCLib/Data/SDC/SDCProviderAlertConditionStateHandler.h"
#include "SDCLib/Data/SDC/SDCProviderComponentStateHandler.h"
#include "SDCLib/Data/SDC/SDCProviderMDStateHandler.h"
#include "SDCLib/Data/SDC/MDIB/ActivateOperationDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/AlertConditionDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/AlertConditionState.h"
#include "SDCLib/Data/SDC/MDIB/AlertSignalDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/AlertSignalState.h"
#include "SDCLib/Data/SDC/MDIB/AlertSystemDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/AlertSystemState.h"
#include "SDCLib/Data/SDC/MDIB/AllowedValue.h"
#include "SDCLib/Data/SDC/MDIB/ClockState.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"
#include "SDCLib/Data/SDC/MDIB/DistributionSampleArrayMetricState.h"
#include "SDCLib/Data/SDC/MDIB/SimpleTypesMapping.h"
#include "SDCLib/Data/SDC/MDIB/EnumStringMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/EnumStringMetricState.h"
#include "SDCLib/Data/SDC/MDIB/MdsDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/MdsState.h"
#include "SDCLib/Data/SDC/MDIB/VmdState.h"
#include "SDCLib/Data/SDC/MDIB/ChannelState.h"
#include "SDCLib/Data/SDC/MDIB/LimitAlertConditionDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/LimitAlertConditionState.h"
#include "SDCLib/Data/SDC/MDIB/LocationContextState.h"
#include "SDCLib/Data/SDC/MDIB/custom/MdibContainer.h"
#include "SDCLib/Data/SDC/MDIB/MdDescription.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricState.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricValue.h"
#include "SDCLib/Data/SDC/MDIB/custom/OperationInvocationContext.h"
#include "SDCLib/Data/SDC/MDIB/PatientContextState.h"
#include "SDCLib/Data/SDC/MDIB/PatientContextDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/LocationContextDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/EnsembleContextDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/EnsembleContextState.h"
#include "SDCLib/Data/SDC/MDIB/OperatorContextDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/OperatorContextState.h"
#include "SDCLib/Data/SDC/MDIB/WorkflowContextDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/WorkflowContextState.h"
#include "SDCLib/Data/SDC/MDIB/MeansContextDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/MeansContextState.h"
#include "SDCLib/Data/SDC/MDIB/ScoDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/StringMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/StringMetricState.h"
#include "SDCLib/Data/SDC/MDIB/StringMetricValue.h"
#include "SDCLib/Data/SDC/MDIB/RealTimeSampleArrayMetricState.h"
#include "SDCLib/Data/SDC/MDIB/SetValueOperationState.h"
#include "SDCLib/Data/SDC/MDIB/SetStringOperationState.h"
#include "SDCLib/Data/SDC/MDIB/SetAlertStateOperationState.h"
#include "SDCLib/Data/SDC/MDIB/SetComponentStateOperationState.h"
#include "SDCLib/Data/SDC/MDIB/SetContextStateOperationState.h"
#include "SDCLib/Data/SDC/MDIB/SetMetricStateOperationState.h"
#include "SDCLib/Util/Task.h"
#include "OSELib/DPWS/DPWS11Constants.h"
#include "OSELib/Helper/Message.h"
#include "OSELib/Helper/XercesDocumentWrapper.h"
#include "OSELib/Helper/XercesParserWrapper.h"
#include "OSELib/SDC/DefaultSDCSchemaGrammarProvider.h"

#include "SDCLib/SDCInstance.h"
#include "OSELib/SDC/SDCConstants.h"


#include "DataModel/osdm.hxx"

#include <memory>
#include <sstream>

#include <Poco/AutoPtr.h>
#include <Poco/Net/NetException.h>
#include <Poco/Notification.h>


namespace SDCLib {
namespace Data {
namespace SDC {

template<class T>
class SetNotification : public Poco::Notification
{
public:
	SetNotification(const T & p_request, const OperationInvocationContext & p_oic)
	: m_request(p_request)
	, m_oic(p_oic)
	{ }
    const T m_request;
    const OperationInvocationContext m_oic;
};


// FIXME - Task class and this class need to be fixed!

class AsyncProviderInvoker : public Util::Task, OSELib::Helper::WithLogger
{
private:
    SDCProvider & m_provider;
    Poco::NotificationQueue & m_queue;

public:
	AsyncProviderInvoker(SDCProvider & p_provider, Poco::NotificationQueue & p_queue)
	: OSELib::Helper::WithLogger(OSELib::Log::sdcProvider)
	, m_provider(p_provider)
	, m_queue(p_queue)
	{ }

    void runImpl() override {
		Poco::AutoPtr<Poco::Notification> t_pNf(m_queue.waitDequeueNotification(100));
		if (t_pNf) {
			try {
				if (auto t_notification = dynamic_cast<const SetNotification<MDM::SetValue> *>(t_pNf.get())) {
					m_provider.SetValue(t_notification->m_request, t_notification->m_oic);
				}
				else if (auto t_notification = dynamic_cast<const SetNotification<MDM::SetString> *>(t_pNf.get())) {
					m_provider.SetString(t_notification->m_request, t_notification->m_oic);
				}
				else if (auto t_notification = dynamic_cast<const SetNotification<MDM::Activate> *>(t_pNf.get())) {
					m_provider.OnActivate(t_notification->m_oic);
				}
				else if (auto t_notification = dynamic_cast<const SetNotification<MDM::SetAlertState> *>(t_pNf.get())) {
					m_provider.SetAlertState(t_notification->m_request, t_notification->m_oic);
				}
				else if (auto t_notification = dynamic_cast<const SetNotification<MDM::SetContextState> *>(t_pNf.get())) {
					m_provider.SetContextState(t_notification->m_request, t_notification->m_oic);
				}
				else {
					log_error([] { return "Unknown invoke data type!"; });
				}
			}
			catch (...) {
				log_error([] { return "Exception caught during async provider invoke."; });
			}
		}

		if (this->isInterrupted()) {
			return;
		}

		if (m_provider.getPeriodicEventInterval() < (std::chrono::system_clock::now() - m_provider.getLastPeriodicEvent())) {
			m_provider.firePeriodicReportImpl();
			m_provider.setLastPeriodicEvent(m_provider.getLastPeriodicEvent());
		}
    }
};

//template SDCProviderStateHandler<NumericMetricState>;


template<class StateType>
bool SDCProvider::isMetricChangeAllowed(const StateType & p_state, SDCProvider & p_provider)
{
    if(!isStarted()) {
        return false;
    }
	typename StateType::DescriptorType t_descriptor;
	if (!p_provider.getMdDescription().findDescriptor(p_state.getDescriptorHandle(), t_descriptor)) {
		return false;
	}
	if (t_descriptor.getMetricCategory() == MetricCategory::Msrmt) {
		return false;
	}

	if (p_state.hasActivationState()) {
		return p_state.getActivationState() == ComponentActivation::On;
	} else {
		return true;
	}
	// FIXME: Return "else part" here?
}



SDCProvider::SDCProvider(SDCInstance_shared_ptr p_SDCInstance)
 : OSELib::Helper::WithLogger(OSELib::Log::sdcProvider)
 , m_SDCInstance(p_SDCInstance)
{
	// Set a random EndpointReference
    setEndpointReference(SDCInstance::calcUUIDv5(std::string("SDCProvider" + SDCInstance::calcUUID()), true));
    m_MdDescription = std::unique_ptr<MdDescription>(new MdDescription());
	m_adapter = std::unique_ptr<SDCProviderAdapter>(new SDCProviderAdapter(*this));
}


SDCProvider::~SDCProvider()
{
    if (m_SDCInstance->isInit() && m_adapter)
    {
        log_warning([] { return "SDCProvider deleted before shutdown. For proper handling please shutdown the provider first"; });
        shutdown();
    }
}


unsigned int SDCProvider::incrementAndGetTransactionId()
{
    return (++atomicTransactionId);
}

template<class T>
void SDCProvider::enqueueInvokeNotification(const T & p_request, const OperationInvocationContext & p_oic) {
	m_invokeQueue.enqueueNotification(new SetNotification<T>(p_request, p_oic));
}

MDM::SetValueResponse SDCProvider::SetValueAsync(const MDM::SetValue & p_request)
{
	const OperationInvocationContext t_oic(p_request.OperationHandleRef(), incrementAndGetTransactionId());
	const auto t_metricHandle(getMdDescription().getOperationTargetForOperationHandle(t_oic.operationHandle));

	auto genResponse = [this, &t_oic](InvocationState v) {
		notifyOperationInvoked(t_oic, v);
		// TODO: 0 = replace with real sequence ID
		MDM::SetValueResponse svr(MDM::InvocationInfo(t_oic.transactionId,MDM::InvocationState(ConvertToCDM::convert(v))),xml_schema::Uri("0"));
		svr.MdibVersion(getMdibVersion());

		return svr;
	};

	NumericMetricState t_nms;
	if (!getMdState().findState(t_metricHandle, t_nms)) {
		return genResponse(InvocationState::Fail);
	}
	if (!isMetricChangeAllowed(t_nms, *this)) {
		return genResponse(InvocationState::Fail);
	}

	enqueueInvokeNotification(p_request, t_oic);
	return genResponse(InvocationState::Wait);
}

void SDCProvider::SetValue(const MDM::SetValue & p_request, const OperationInvocationContext & p_oic)
{
	const auto metricHandle(getMdDescription().getOperationTargetForOperationHandle(p_oic.operationHandle));

	NumericMetricState t_nms;
	if (!getMdState().findState(metricHandle, t_nms)) {
		notifyOperationInvoked(p_oic, InvocationState::Fail);
		return;
	}
	if (!isMetricChangeAllowed(t_nms, *this)) {
		notifyOperationInvoked(p_oic, InvocationState::Fail);
		return;
	}
	t_nms.setMetricValue(t_nms.getMetricValue().setValue(p_request.RequestedNumericValue()));

	const InvocationState t_outState(onStateChangeRequest(t_nms, p_oic));
	notifyOperationInvoked(p_oic, t_outState);

	if (InvocationState::Fin == t_outState) {
		// Success
		updateState(t_nms);
	}
}

MDM::ActivateResponse SDCProvider::OnActivateAsync(const MDM::Activate & p_request)
{
	const OperationInvocationContext t_oic(p_request.OperationHandleRef(), incrementAndGetTransactionId());
	notifyOperationInvoked(t_oic, InvocationState::Wait);
	enqueueInvokeNotification(p_request, t_oic);

	MDM::ActivateResponse t_ar(MDM::InvocationInfo(t_oic.transactionId,MDM::InvocationState(ConvertToCDM::convert(InvocationState::Wait))),xml_schema::Uri("0"));
	t_ar.MdibVersion(getMdibVersion());

	return t_ar;
}


void SDCProvider::OnActivate(const OperationInvocationContext & p_oic)
{
	auto t_iter = ml_stateHandlers.find(p_oic.operationHandle);
    if (t_iter != ml_stateHandlers.end()) {
        if (SDCProviderActivateOperationHandler * t_handler = dynamic_cast<SDCProviderActivateOperationHandler *>(t_iter->second)) {
            const InvocationState t_isVal(t_handler->onActivateRequest(p_oic));
            notifyOperationInvoked(p_oic, t_isVal);
            return;
        }
    }
    notifyOperationInvoked(p_oic, InvocationState::Fail);
}

MDM::SetStringResponse SDCProvider::SetStringAsync(const MDM::SetString & p_request)
{
    const OperationInvocationContext t_oic(p_request.OperationHandleRef(), incrementAndGetTransactionId());

	const MdDescription t_mdd(getMdDescription());

	const auto t_metricHandle(t_mdd.getOperationTargetForOperationHandle(t_oic.operationHandle));
	const auto t_mdsc(getMdState());

	auto genResponse = [this, &t_oic](InvocationState v) {
		notifyOperationInvoked(t_oic, v);
		MDM::SetStringResponse t_ssr(MDM::InvocationInfo(t_oic.transactionId,MDM::InvocationState(ConvertToCDM::convert(v))),xml_schema::Uri("0"));
		t_ssr.MdibVersion(getMdibVersion());
		return t_ssr;
	};

	{ // TODO: Why { } ?
		StringMetricState t_sms;
		if (t_mdsc.findState(t_metricHandle, t_sms)) {
            if (!isMetricChangeAllowed(t_sms, *this)) {
                return genResponse(InvocationState::Fail);
            }
			enqueueInvokeNotification(p_request, t_oic);
			return genResponse(InvocationState::Wait);
		}
	}
	{
		EnumStringMetricState t_state;
		if (t_mdsc.findState(t_metricHandle, t_state)) {
			EnumStringMetricDescriptor t_descriptor;
			if (!t_mdd.findDescriptor(t_state.getDescriptorHandle(), t_descriptor)) {
				return genResponse(InvocationState::Fail);
			}
            if (!isMetricChangeAllowed(t_state, *this)) {
                return genResponse(InvocationState::Fail);
            }
			const auto tl_allowedValues(t_descriptor.getAllowedValueList());

			const auto & t_requestedStringVal(p_request.RequestedStringValue());
			std::vector<std::string> tl_allowedValuesString;
			for (auto t_allowedValue : tl_allowedValues) {
				tl_allowedValuesString.push_back(t_allowedValue.getValue());
			}

			auto t_iter = std::find(tl_allowedValuesString.begin(), tl_allowedValuesString.end(), t_requestedStringVal);
			if (t_iter == tl_allowedValuesString.end()) {
				return genResponse(InvocationState::Fail);
			}
			enqueueInvokeNotification(p_request, t_oic);
			return genResponse(InvocationState::Wait);
		}
	}

	return genResponse(InvocationState::Fail);
}

template<class T>
void SDCProvider::SetStringImpl(const T & p_state, const OperationInvocationContext & p_oic)
{
	const InvocationState t_outState(onStateChangeRequest(p_state, p_oic));
	notifyOperationInvoked(p_oic, t_outState);

	if (InvocationState::Fin == t_outState) {
		// Success
		updateState(p_state);
	}
}

void SDCProvider::SetString(const MDM::SetString & p_request, const OperationInvocationContext & p_oic)
{
	const auto & t_requestedStringVal(p_request.RequestedStringValue());

	const auto t_mdsc(getMdState());
	const auto t_mdd(getMdDescription());

	const auto t_metricHandle(t_mdd.getOperationTargetForOperationHandle(p_oic.operationHandle));

	{
		StringMetricState t_sms;
		if (t_mdsc.findState(t_metricHandle, t_sms)) {
			t_sms.setMetricValue(t_sms.getMetricValue().setValue(t_requestedStringVal));
			SetStringImpl(t_sms, p_oic);
			return;
		}
	}
	{ // TODO: Why { }
		EnumStringMetricState t_state;
		if (t_mdsc.findState(t_metricHandle, t_state)) {
			EnumStringMetricDescriptor t_descriptor;
			if (!t_mdd.findDescriptor(t_state.getDescriptorHandle(), t_descriptor)) {
				notifyOperationInvoked(p_oic, InvocationState::Fail);
				return;
			}

			const auto tl_allowedValues(t_descriptor.getAllowedValueList());
			std::vector<std::string> tl_allowedValuesString;
			for (auto t_allowedValue : tl_allowedValues) {
				tl_allowedValuesString.push_back(t_allowedValue.getValue());
			}

			auto t_iter = std::find(tl_allowedValuesString.begin(), tl_allowedValuesString.end(), t_requestedStringVal);
			if (t_iter == tl_allowedValuesString.end()) {
				notifyOperationInvoked(p_oic, InvocationState::Fail);
			} else {
				StringMetricValue t_smv = t_state.getMetricValue();
				t_smv.setValue(t_iter->data());
				t_state.setMetricValue(t_smv);
				SetStringImpl(t_state, p_oic);
			}
			return;
		}
	}

	notifyOperationInvoked(p_oic, InvocationState::Fail);
}


template<typename StateType>
void SDCProvider::SetAlertStateImpl(const StateType & state, const OperationInvocationContext & oic) {

	const MdDescription mdd(getMdDescription());

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

MDM::SetAlertStateResponse SDCProvider::SetAlertStateAsync(const MDM::SetAlertState & p_request)
{
	const OperationInvocationContext t_oic(p_request.OperationHandleRef(), incrementAndGetTransactionId());
	const CDM::AbstractAlertState * t_incomingCDMState = &(p_request.ProposedAlertState()); // FIXME: std::addressof ?

	auto genResponse = [this, &t_oic](InvocationState v) {
		notifyOperationInvoked(t_oic, v);
		// TODO: 0 = replace with real sequence ID
		MDM::SetAlertStateResponse t_sasr(MDM::InvocationInfo(t_oic.transactionId,MDM::InvocationState(ConvertToCDM::convert(v))),xml_schema::Uri("0"));
		t_sasr.MdibVersion(getMdibVersion());

		return t_sasr;
	};

	const auto t_targetHandle(getMdDescription().getOperationTargetForOperationHandle(t_oic.operationHandle));
	if (t_targetHandle.empty()) {
		return genResponse(InvocationState::Fail);
	}
	if ((t_incomingCDMState->DescriptorHandle() != t_targetHandle)) {
		return genResponse(InvocationState::Fail);
	}

	// Cast and convert, then call into user code
	if (dynamic_cast<const CDM::AlertConditionState *>(t_incomingCDMState)) {
		enqueueInvokeNotification(p_request, t_oic);
		return genResponse(InvocationState::Wait);
	} else if (dynamic_cast<const CDM::AlertSignalState *>(t_incomingCDMState)) {
		enqueueInvokeNotification(p_request, t_oic);
		return genResponse(InvocationState::Wait);
	} else if (dynamic_cast<const CDM::AlertSystemState *>(t_incomingCDMState)) {
		enqueueInvokeNotification(p_request, t_oic);
		return genResponse(InvocationState::Wait);
	} else if (dynamic_cast<const CDM::LimitAlertConditionState *>(t_incomingCDMState)) {
		enqueueInvokeNotification(p_request, t_oic);
		return genResponse(InvocationState::Wait);
	} else {
		// cast failed.
		return genResponse(InvocationState::Fail);
	}
	// FIXME: Return "else part" here?
}

void SDCProvider::SetAlertState(const MDM::SetAlertState & p_request, const OperationInvocationContext & p_oic) {

	const CDM::AbstractAlertState * t_incomingCDMState = &(p_request.ProposedAlertState()); // FIXME: std::addressof ?

	const auto t_targetHandle(getMdDescription().getOperationTargetForOperationHandle(p_oic.operationHandle));
	if (t_targetHandle.empty()) {
		return notifyOperationInvoked(p_oic, InvocationState::Fail);
	}
	if ((t_incomingCDMState->DescriptorHandle() != t_targetHandle)) {
		return notifyOperationInvoked(p_oic, InvocationState::Fail);
	}

	// Cast and convert, then call into user code
	if (const CDM::AlertConditionState * t_state = dynamic_cast<const CDM::AlertConditionState *>(t_incomingCDMState)) {
		SetAlertStateImpl(ConvertFromCDM::convert(*t_state), p_oic);
	} else if (const CDM::AlertSignalState * t_state = dynamic_cast<const CDM::AlertSignalState *>(t_incomingCDMState)) {
		SetAlertStateImpl(ConvertFromCDM::convert(*t_state), p_oic);
	} else if (const CDM::AlertSystemState * t_state = dynamic_cast<const CDM::AlertSystemState *>(t_incomingCDMState)) {
		SetAlertStateImpl(ConvertFromCDM::convert(*t_state), p_oic);
	} else if (const CDM::LimitAlertConditionState * t_state = dynamic_cast<const CDM::LimitAlertConditionState *>(t_incomingCDMState)) {
		SetAlertStateImpl(ConvertFromCDM::convert(*t_state), p_oic);
	} else {
		// cast failed.
		notifyOperationInvoked(p_oic, InvocationState::Fail);
		return;
	}
	// FIXME: Return "else part" here?
}

MDM::GetMdStateResponse SDCProvider::GetMdState(const MDM::GetMdState & p_request)
{
    auto t_sdmMdStates(ConvertToCDM::convert(getMdState()));

    if (p_request.HandleRef().empty()) {
    	//TODO: use real SequenceID, not 0
        return MDM::GetMdStateResponse(xml_schema::Uri("0"), std::move(t_sdmMdStates));
    } else {
    	CDM::MdState t_tmpmds;
    	const std::set<std::string> t_reqHandles(p_request.HandleRef().begin(), p_request.HandleRef().end());
    	for (const auto & t_nextState : t_sdmMdStates->State()) {
			if (t_reqHandles.find(t_nextState.DescriptorHandle()) != t_reqHandles.end()) {
				t_tmpmds.State().push_back(t_nextState);
			}
    	}
    	//TODO: use real SequenceID, not 0
    	return MDM::GetMdStateResponse(xml_schema::Uri("0"), t_tmpmds);
    }
    // FIXME: What to return here?
}

MDM::GetContextStatesResponse SDCProvider::GetContextStates(const MDM::GetContextStates & p_request)
{
    const auto t_states(ConvertToCDM::convert(getMdState()));

	//TODO: use real SequenceID, not 0
	MDM::GetContextStatesResponse t_contextStates(xml_schema::Uri("0"));
	for (const auto & t_state : t_states->State()) {
		if (const CDM::EnsembleContextState * t_s = dynamic_cast<const CDM::EnsembleContextState *>(&t_state)) { // FIXME: std::addressof?
			t_contextStates.ContextState().push_back(*t_s);
		} else if (const CDM::LocationContextState * t_s = dynamic_cast<const CDM::LocationContextState *>(&t_state)) { // FIXME: std::addressof?
			t_contextStates.ContextState().push_back(*t_s);
		} else if (const CDM::OperatorContextState * t_s = dynamic_cast<const CDM::OperatorContextState *>(&t_state)) { // FIXME: std::addressof?
			t_contextStates.ContextState().push_back(*t_s);
		} else if (const CDM::PatientContextState * t_s = dynamic_cast<const CDM::PatientContextState *>(&t_state)) { // FIXME: std::addressof?
			t_contextStates.ContextState().push_back(*t_s);
		} else if (const CDM::WorkflowContextState * t_s = dynamic_cast<const CDM::WorkflowContextState *>(&t_state)) { // FIXME: std::addressof?
			t_contextStates.ContextState().push_back(*t_s);
		}
	}

	if (p_request.HandleRef().empty()) {
		// TODO: 0 = replace with real sequence ID
		MDM::GetContextStatesResponse t_result(xml_schema::Uri("0"));
		t_result.MdibVersion(getMdibVersion());
		for (const auto & t_state : t_contextStates.ContextState()) {
			t_result.ContextState().push_back(t_state);
		}
		return t_result;
	} else {
		// TODO: 0 = replace with real sequence ID
		MDM::GetContextStatesResponse t_result(xml_schema::Uri("0"));
		t_result.MdibVersion(getMdibVersion());
		const std::set<std::string> t_reqHandles(p_request.HandleRef().begin(), p_request.HandleRef().end());
		for (const auto & state : t_contextStates.ContextState()) {
			if (t_reqHandles.find(state.DescriptorHandle()) != t_reqHandles.end()) {
				t_result.ContextState().push_back(state);
			}
		}
		return t_result;
	}
	// TODO: 0 = replace with real sequence ID
	MDM::GetContextStatesResponse t_result(xml_schema::Uri("0"));
	log_warning([&] { return "The requested states handle or descriptor handle does not fit any of the provider's states"; });
	t_result.MdibVersion(getMdibVersion());
	return t_result;
}

MDM::SetContextStateResponse SDCProvider::SetContextStateAsync(const MDM::SetContextState & p_request)
{
    const OperationInvocationContext t_oic(p_request.OperationHandleRef(), incrementAndGetTransactionId());

	auto genResponse = [this, &t_oic](InvocationState v) {
		notifyOperationInvoked(t_oic, v);
		// TODO: 0 = replace with real sequence ID
		MDM::SetContextStateResponse t_scsr(MDM::InvocationInfo(t_oic.transactionId, ConvertToCDM::convert(v)),xml_schema::Uri("0"));
		t_scsr.MdibVersion(getMdibVersion());
		return t_scsr;
	};

	const auto t_targetHandle(getMdDescription().getOperationTargetForOperationHandle(t_oic.operationHandle));
	if (t_targetHandle.empty()) {
		return genResponse(InvocationState::Fail);
	}

	enqueueInvokeNotification(p_request, t_oic);
	return genResponse(InvocationState::Wait);
}



template<class TState>
void SDCProvider::SetContextStateImpl(const TState & p_state,  const OperationInvocationContext & p_oic) {
	// FIXME: check if writing to context state is allowed! = SCO exists
	const InvocationState t_outState(onStateChangeRequest(p_state, p_oic));
	notifyOperationInvoked(p_oic, t_outState);
	if (t_outState == InvocationState::Fin) {
		// Success
		updateState(p_state);
	}
}

void SDCProvider::SetContextState(const MDM::SetContextState & p_request, const OperationInvocationContext & p_oic)
{
	// FIXME: for-loop + dynamic_cast: Refactor(?)
	for (const auto & t_nextState : p_request.ProposedContextState()) {
		if (const CDM::PatientContextState * t_state = dynamic_cast<const CDM::PatientContextState *>(&t_nextState)) { // FIXME: std::addressof ?
			SetContextStateImpl(ConvertFromCDM::convert(*t_state), p_oic);
		}
		else if (const CDM::LocationContextState * t_state = dynamic_cast<const CDM::LocationContextState *>(&t_nextState)) { // FIXME: std::addressof ?
			SetContextStateImpl(ConvertFromCDM::convert(*t_state), p_oic);
		}
		else if (const CDM::EnsembleContextState * t_state = dynamic_cast<const CDM::EnsembleContextState *>(&t_nextState)) { // FIXME: std::addressof ?
			SetContextStateImpl(ConvertFromCDM::convert(*t_state), p_oic);
		}
		else if (const CDM::OperatorContextState * t_state = dynamic_cast<const CDM::OperatorContextState *>(&t_nextState)) { // FIXME: std::addressof ?
			SetContextStateImpl(ConvertFromCDM::convert(*t_state), p_oic);
		}
		else if (const CDM::WorkflowContextState * t_state = dynamic_cast<const CDM::WorkflowContextState *>(&t_nextState)) { // FIXME: std::addressof ?
			SetContextStateImpl(ConvertFromCDM::convert(*t_state), p_oic);
		}
		else if (const CDM::MeansContextState * t_state = dynamic_cast<const CDM::MeansContextState *>(&t_nextState)) { // FIXME: std::addressof ?
			SetContextStateImpl(ConvertFromCDM::convert(*t_state), p_oic);
		}
	}
}


MDM::GetMdibResponse SDCProvider::GetMdib(const MDM::GetMdib & ) {
	// TODO: 0 = replace with real sequence ID
	MDM::GetMdibResponse t_mdib(xml_schema::Uri("0"),ConvertToCDM::convert(getMdib()));
	t_mdib.MdibVersion(getMdibVersion());
    return t_mdib;
}

MDM::GetMdDescriptionResponse SDCProvider::GetMdDescription(const MDM::GetMdDescription & p_request)
{
    auto t_cdmMdd(ConvertToCDM::convert(getMdDescription()));
	if (p_request.HandleRef().empty()) {
		// TODO: 0 = replace with real sequence ID
		MDM::GetMdDescriptionResponse t_mddr(xml_schema::Uri("0"),std::move(t_cdmMdd));
		t_mddr.MdibVersion(getMdibVersion());
		return t_mddr;
	} else {
		CDM::MdDescription t_filteredDescription;
		for (const auto & t_mds : t_cdmMdd->Mds()) {
			if (std::find(p_request.HandleRef().begin(), p_request.HandleRef().end(), t_mds.Handle()) != p_request.HandleRef().end()) {
				t_filteredDescription.Mds().push_back(t_mds);
			}
		}
		MDM::GetMdDescriptionResponse t_gmddr(xml_schema::Uri("0"), t_filteredDescription);
		t_gmddr.MdibVersion(getMdibVersion());
		return t_gmddr;
	}
	// FIXME: Return ?
}

void SDCProvider::updateState(const AlertSystemState & p_object) {
	updateMDIB(p_object);
	notifyAlertEventImpl(p_object);
}

void SDCProvider::updateState(const AlertSignalState & p_object) {
	updateMDIB(p_object);
	notifyAlertEventImpl(p_object);
}

void SDCProvider::updateState(const AlertConditionState & p_object) {
	updateMDIB(p_object);
	reevaluateAlertConditions(p_object.getDescriptorHandle());
	notifyAlertEventImpl(p_object);
}

void SDCProvider::updateState(const EnumStringMetricState & p_object) {
	updateMDIB(p_object);
	evaluateAlertConditions(p_object.getDescriptorHandle());
	notifyEpisodicMetricImpl(p_object);
}

void SDCProvider::updateState(const LimitAlertConditionState & p_object) {
	updateMDIB(p_object);
	//Evaluate Alert Conditions sources, based on changes to the AlertCoditionState
	reevaluateAlertConditions(p_object.getDescriptorHandle());
	notifyAlertEventImpl(p_object);
}

void SDCProvider::updateState(const NumericMetricState & p_object) {
	updateMDIB(p_object);
	evaluateAlertConditions(p_object.getDescriptorHandle());
	notifyEpisodicMetricImpl(p_object);
}


void SDCProvider::updateState(const StringMetricState & p_object) {
	updateMDIB(p_object);
	evaluateAlertConditions(p_object.getDescriptorHandle());
	notifyEpisodicMetricImpl(p_object);
}


// regarding to the given standard the DSAMS is implemented as an TCP transported Metric
void SDCProvider::updateState(const DistributionSampleArrayMetricState & p_object) {
	updateMDIB(p_object);
	evaluateAlertConditions(p_object.getDescriptorHandle());
	notifyEpisodicMetricImpl(p_object);
}

// UDP metrices
void SDCProvider::updateState(const RealTimeSampleArrayMetricState & p_object) {
	// FIXME: This increments the MDIB but does not dispatch an event -> see notifyStreamMetricImpl
	updateMDIB(p_object);
	evaluateAlertConditions(p_object.getDescriptorHandle());
	notifyStreamMetricImpl(p_object);
}



// context states
void SDCProvider::updateState(const EnsembleContextState & p_object) {
	updateMDIB(p_object);
	notifyContextEventImpl(p_object);
}

void SDCProvider::updateState(const MeansContextState & p_object) {
	updateMDIB(p_object);
	notifyContextEventImpl(p_object);
}

void SDCProvider::updateState(const LocationContextState & p_object) {
	updateMDIB(p_object);
	notifyContextEventImpl(p_object);
}

void SDCProvider::updateState(const WorkflowContextState & p_object) {
	updateMDIB(p_object);
	notifyContextEventImpl(p_object);
}

void SDCProvider::updateState(const PatientContextState & p_object) {
	updateMDIB(p_object);
	notifyContextEventImpl(p_object);
}

void SDCProvider::updateState(const OperatorContextState & p_object) {
	updateMDIB(p_object);
	notifyContextEventImpl(p_object);
}

template<class T> void SDCProvider::updateMDIB(const T & p_object) {
	//Changing the MDIB -> MDIB Version gets increased.
	incrementMDIBVersion();
	replaceState(p_object);
}

template<class T> void SDCProvider::notifyAlertEventImpl(const T & p_object)
{
	if (p_object.getDescriptorHandle().empty()) {
		log_error([] { return "State's descriptor handle is empty, event will not be fired!"; });
		return;
	}
	
	// TODO: replace sequence id
	MDM::EpisodicAlertReport t_report(xml_schema::Uri("0"));

	MDM::ReportPart3 t_reportPart;
	t_reportPart.AlertState().push_back(ConvertToCDM::convert(p_object));
	t_report.ReportPart().push_back(t_reportPart);

	m_adapter->notifyEvent(t_report);
}

template<class T> void SDCProvider::notifyContextEventImpl(const T & p_object)
{
	if (p_object.getDescriptorHandle().empty()) {
		log_error([] { return "State's descriptor handle is empty, event will not be fired!"; });
		return;
	}

	MDM::ReportPart t_reportPart;
	t_reportPart.ContextState().push_back(ConvertToCDM::convert(p_object));

	MDM::EpisodicContextReport t_report(xml_schema::Uri("0"));
	t_report.ReportPart().push_back(t_reportPart);

	m_adapter->notifyEvent(t_report);
}

template<class T>
void SDCProvider::notifyEpisodicMetricImpl(const T & p_object)
{
	if (p_object.getDescriptorHandle().empty()) {
		log_error([] { return "State's descriptor handle is empty, event will not be fired!"; });
		return;
	}

	MDM::ReportPart1 t_reportPart;
	t_reportPart.MetricState().push_back(ConvertToCDM::convert(p_object));

	// TODO: replace sequence id
	MDM::EpisodicMetricReport t_report(xml_schema::Uri("0"));
	t_report.ReportPart().push_back(t_reportPart);
	t_report.MdibVersion(getMdibVersion());

	m_adapter->notifyEvent(t_report);
}

template<class T>
void SDCProvider::notifyEpisodicOperationalStateImpl(const T & p_object)
{
	if (p_object.getDescriptorHandle().empty()) {
		log_error([] { return "State's descriptor handle is empty, event will not be fired!"; });
		return;
	}

	MDM::ReportPart4 t_reportPart;
	t_reportPart.OperationState().push_back(ConvertToCDM::convert(p_object));

	// TODO: replace sequence id
	MDM::EpisodicOperationalStateReport t_report(xml_schema::Uri("0"));
	t_report.ReportPart().push_back(t_reportPart);
	t_report.MdibVersion(getMdibVersion());

	m_adapter->notifyEvent(t_report);
}

template<class T>
void SDCProvider::notifyStreamMetricImpl(const T & p_object)
{
	if (p_object.getDescriptorHandle().empty()) {
		log_error([] { return "State's descriptor handle is empty, event will not be fired!"; });
		return;
	}

	// TODO: replace sequence id
	MDM::WaveformStream t_waveformStream(xml_schema::Uri("0"));

	t_waveformStream.State().push_back(ConvertToCDM::convert(p_object));

	// FIXME: No dispatching here
	// -> Consumer will get no "Event" but the MDIB Version was changed. See updateState(...) above -> MISMATCH!
	m_adapter->notifyEvent(t_waveformStream);
}



void SDCProvider::firePeriodicReportImpl()
{
    std::lock_guard<std::mutex> t_lock{m_mutex_PeriodicUpdateHandles};

	if (ml_handlesForPeriodicUpdates.empty()) {
		//log_debug([] { return "List of handles is empty, event will not be fired!"; });
		return;
	}

	const auto t_mdstate(ConvertToCDM::convert(getMdState()));

	MDM::ReportPart3 t_periodicAlertReportPart;
	MDM::ReportPart t_periodicContextChangedReportPart;
	MDM::ReportPart1 t_periodicMetricReportPart;

	// FIXME: for-loop and dynamic_cast : Refactor (?)
	for(const auto & t_state: t_mdstate->State()) {
		if (std::find(ml_handlesForPeriodicUpdates.begin(), ml_handlesForPeriodicUpdates.end(), t_state.DescriptorHandle()) != ml_handlesForPeriodicUpdates.end()) {
			if (auto t_castedState = dynamic_cast<const CDM::AbstractAlertState *>(&t_state)) { // FIXME: std::addressof?
				t_periodicAlertReportPart.AlertState().push_back(*t_castedState);
			}
			if (auto t_castedState = dynamic_cast<const CDM::AbstractContextState *>(&t_state)) { // FIXME: std::addressof?
				t_periodicContextChangedReportPart.ContextState().push_back(*t_castedState);
			}
			if (auto t_castedState = dynamic_cast<const CDM::AbstractMetricState *>(&t_state)) { // FIXME: std::addressof?
				t_periodicMetricReportPart.MetricState().push_back(*t_castedState);
			}
		}
	}

	// TODO: replace sequence id s
	MDM::PeriodicAlertReport t_periodicAlertReport(xml_schema::Uri("0"));
	t_periodicAlertReport.MdibVersion(getMdibVersion());
	t_periodicAlertReport.ReportPart().push_back(t_periodicAlertReportPart);
	m_adapter->notifyEvent(t_periodicAlertReport);

	MDM::PeriodicContextReport t_periodicContextReport(xml_schema::Uri("0"));
	t_periodicContextReport.MdibVersion(getMdibVersion());
	t_periodicContextReport.ReportPart().push_back(t_periodicContextChangedReportPart);
	m_adapter->notifyEvent(t_periodicContextReport);

	MDM::PeriodicMetricReport t_periodicMetricReport(xml_schema::Uri("0"));
	t_periodicMetricReport.ReportPart().push_back(t_periodicMetricReportPart);
	m_adapter->notifyEvent(t_periodicMetricReport);
}

void SDCProvider::setAlertConditionPresence(const std::string & p_alertConditionHandle, bool p_conditionPresence, const OperationInvocationContext & p_oic)
{
	const MdState t_mdsc(getMdState());

	// Modify alert condition's presence
	AlertConditionState t_condState;
	LimitAlertConditionState t_limitCondState;
	if (t_mdsc.findState(p_alertConditionHandle, t_condState)) {
		t_condState.setPresence(p_conditionPresence);
		const InvocationState is(onStateChangeRequest(t_condState, p_oic));
		if (is == InvocationState::Fin) {
			// Success
			updateState(t_condState);
		}
	} else if (t_mdsc.findState(p_alertConditionHandle, t_limitCondState)) {
		t_limitCondState.setPresence(p_conditionPresence);
		const InvocationState t_is(onStateChangeRequest(t_limitCondState, p_oic));
		if (InvocationState::Fin == t_is) {
			// Success
			updateState(t_limitCondState);
		}
	} else {
		return;
	}

	// Search all alert signal descriptors with reference to the alert condition descriptor handle
	const std::vector<AlertSignalDescriptor> tl_asds(getMdDescription().collectAllAlertSignalDescriptors());
	std::map<std::string, AlertSignalDescriptor> tl_matchingDescriptors;
	std::list<AlertSignalDescriptor> tl_listDescriptors;

	for (const auto & t_descriptor : tl_asds) {
		if (t_descriptor.getConditionSignaled() == p_alertConditionHandle) {
			tl_matchingDescriptors.insert( std::map<std::string, AlertSignalDescriptor>::value_type ( t_descriptor.getHandle(), t_descriptor) );
		}
	}

	// Check and modify all found alert signal states, call into state handler, if needed
	auto informUser = [this, &p_oic](AlertSignalState & state, const AlertSignalPresence & presence) {
		state.setPresence(presence);
		const InvocationState is(onStateChangeRequest(state, p_oic));
		if (is == InvocationState::Fin) {
			updateState(state);
		}
	};

	// Search all alert signal states
	auto tl_ass(t_mdsc.findAlertSignalStates());
	for (auto & t_nextState : tl_ass) {
		auto descriptor = tl_matchingDescriptors.find(t_nextState.getDescriptorHandle());
		if (descriptor == tl_matchingDescriptors.end()) {
			continue;
		}

		if (p_conditionPresence) {
			informUser(t_nextState, AlertSignalPresence::On);
		} else {
			if (!t_nextState.hasPresence()) {
				informUser(t_nextState, AlertSignalPresence::Off);
			}
			if (descriptor->second.getLatching()) {
				switch (t_nextState.getPresence()) {
					case AlertSignalPresence::On: informUser(t_nextState, AlertSignalPresence::Latch); break;
					case AlertSignalPresence::Off: break;
					case AlertSignalPresence::Ack: break;
					case AlertSignalPresence::Latch: break;
				}
			} else {
				informUser(t_nextState, AlertSignalPresence::Off);
			}
		}
	}
}

void SDCProvider::evaluateAlertConditions(const std::string & p_source) const
{
    const MdDescription t_description(getMdDescription());

	std::vector<std::string> tl_relevantDescriptors;
	for (const auto & t_alertCondition : t_description.collectAllAlertConditionDescriptors()) {
		const auto tl_sources(t_alertCondition.getSourceList());
		if (std::find(tl_sources.begin(), tl_sources.end(), p_source) != tl_sources.end()) {
			tl_relevantDescriptors.push_back(t_alertCondition.getHandle());
		}
	}
	for (const auto & t_limitAlertCondition : t_description.collectAllLimitAlertConditionDescriptors()) {
		const auto tl_sources(t_limitAlertCondition.getSourceList());
		if (std::find(tl_sources.begin(), tl_sources.end(), p_source) != tl_sources.end()) {
			tl_relevantDescriptors.push_back(t_limitAlertCondition.getHandle());
		}
	}

	if (tl_relevantDescriptors.empty()) {
        return;
	}

	using AlertCondition_ptr = SDCProviderAlertConditionStateHandler<AlertConditionState>*;
    std::vector<AlertCondition_ptr> tl_states;
    {   // LOCK
        std::lock_guard<std::mutex> t_lock{m_mutex_MdStateHandler};
        for (const auto & t_handler : ml_stateHandlers) {
            if (SDCProviderAlertConditionStateHandler<AlertConditionState> * t_h = dynamic_cast<SDCProviderAlertConditionStateHandler<AlertConditionState> *>(t_handler.second)) {
                if (std::find(tl_relevantDescriptors.begin(), tl_relevantDescriptors.end(), t_h->getDescriptorHandle()) != tl_relevantDescriptors.end()) {
                    tl_states.push_back(static_cast<AlertCondition_ptr>(t_handler.second));
                }
            } else if (SDCProviderAlertConditionStateHandler<LimitAlertConditionState> * t_h = dynamic_cast<SDCProviderAlertConditionStateHandler<LimitAlertConditionState> *>(t_handler.second)) {
                if (std::find(tl_relevantDescriptors.begin(), tl_relevantDescriptors.end(), t_h->getDescriptorHandle()) != tl_relevantDescriptors.end()) {
                    tl_states.push_back(static_cast<AlertCondition_ptr>(t_handler.second));
                }
            }
        }
    } // UNLOCK

    // Update
    for(const auto& t_handler : tl_states) {
        t_handler->sourceHasChanged(p_source);
    }
}

void SDCProvider::reevaluateAlertConditions(const std::string& p_alertConditionDescriptor) const
{
    const MdDescription t_description(getMdDescription());

    using AlertCondition_ptr = SDCProviderAlertConditionStateHandler<AlertConditionState>*;
    std::vector<AlertCondition_ptr> tl_states;
    { //LOCK
        std::lock_guard<std::mutex> t_lock{m_mutex_MdStateHandler};
        for (const auto & t_handler : ml_stateHandlers) {
            if (SDCProviderAlertConditionStateHandler<AlertConditionState> * t_h = dynamic_cast<SDCProviderAlertConditionStateHandler<AlertConditionState> *>(t_handler.second)) {
                if (t_h->getDescriptorHandle() == p_alertConditionDescriptor) {
                    tl_states.push_back(static_cast<AlertCondition_ptr>(t_handler.second));
                }
            } else if (SDCProviderAlertConditionStateHandler<LimitAlertConditionState> * t_h = dynamic_cast<SDCProviderAlertConditionStateHandler<LimitAlertConditionState> *>(t_handler.second)) {
                if (t_h->getDescriptorHandle() == p_alertConditionDescriptor) {
                    tl_states.push_back(static_cast<AlertCondition_ptr>(t_handler.second));
                }
            }
        }
    } // UNLOCK

    // Update
    for(const auto& t_state : tl_states) {
        t_state->alertConditionHasChanged();
    }
}

MdibContainer SDCProvider::getMdib() const {
    MdibContainer t_container;
    t_container.setMdDescription(getMdDescription());
    t_container.setMdState(getMdState());
    t_container.setMdibVersion(getMdibVersion());
    return t_container;
}

MdState SDCProvider::getMdState() const {
    std::lock_guard<std::mutex> t_lock{m_mutex_MdState};
    return m_MdState;
}


bool SDCProvider::startup()
{
    if(isStarted()) {
        log_error([] { return "Provider already started!";});
        return false;
    }

    std::lock_guard<std::mutex> t_lock{m_mutex};
    try {
        m_adapter->start();
    } catch (const Poco::Net::NetException & e) {
        log_error([&] { return "Net Exception: " + std::string(e.what()) + " Socket unable to be opened. Provider startup aborted.";});
        return false;
    } catch (std::runtime_error & ex_re) {
        log_error([&] { return ex_re.what(); });
        return false;
    }

    // Grab all states (start with all operation states and add states from user handlers)
    {   // LOCK MdState(/Handler)
        std::lock_guard<std::mutex> t_lockMdStates{m_mutex_MdState};
        std::lock_guard<std::mutex> t_lockMdStateHandler{m_mutex_MdStateHandler};
        m_MdState = MdState(m_operationStates);
        for (const auto & t_handler : ml_stateHandlers) {
            if (SDCProviderAlertConditionStateHandler<AlertConditionState> * t_casted = dynamic_cast<SDCProviderAlertConditionStateHandler<AlertConditionState> *>(t_handler.second)) {
                m_MdState.addState(t_casted->getInitialState());
            } else if (SDCProviderMDStateHandler<AlertSignalState> * t_casted = dynamic_cast<SDCProviderMDStateHandler<AlertSignalState> *>(t_handler.second)) {
                m_MdState.addState(t_casted->getInitialState());
            } else if (SDCProviderMDStateHandler<EnumStringMetricState> * t_casted = dynamic_cast<SDCProviderMDStateHandler<EnumStringMetricState> *>(t_handler.second)) {
                m_MdState.addState(t_casted->getInitialState());
            } else if (SDCProviderMDStateHandler<AlertSystemState> * t_casted = dynamic_cast<SDCProviderMDStateHandler<AlertSystemState> *>(t_handler.second)) {
                m_MdState.addState(t_casted->getInitialState());
            } else if (SDCProviderAlertConditionStateHandler<LimitAlertConditionState> * t_casted = dynamic_cast<SDCProviderAlertConditionStateHandler<LimitAlertConditionState> *>(t_handler.second)) {
                m_MdState.addState(t_casted->getInitialState());
            } else if (SDCProviderMDStateHandler<NumericMetricState> * t_casted = dynamic_cast<SDCProviderMDStateHandler<NumericMetricState> *>(t_handler.second)) {
                m_MdState.addState(t_casted->getInitialState());
            } else if (SDCProviderMDStateHandler<RealTimeSampleArrayMetricState> * t_casted = dynamic_cast<SDCProviderMDStateHandler<RealTimeSampleArrayMetricState> *>(t_handler.second)) {
                m_MdState.addState(t_casted->getInitialState());
            } else if (SDCProviderMDStateHandler<DistributionSampleArrayMetricState> * t_casted = dynamic_cast<SDCProviderMDStateHandler<DistributionSampleArrayMetricState> *>(t_handler.second)) {
                m_MdState.addState(t_casted->getInitialState());
            } else if (SDCProviderMDStateHandler<StringMetricState> * t_casted = dynamic_cast<SDCProviderMDStateHandler<StringMetricState> *>(t_handler.second)) {
                m_MdState.addState(t_casted->getInitialState());
            } else if (SDCProviderComponentStateHandler<ClockState> * t_casted = dynamic_cast<SDCProviderComponentStateHandler<ClockState> *>(t_handler.second)) {
                m_MdState.addState(t_casted->getInitialState());
            } else if (SDCProviderComponentStateHandler<MdsState> * t_casted = dynamic_cast<SDCProviderComponentStateHandler<MdsState>*>(t_handler.second)) {
                m_MdState.addState(t_casted->getInitialState());
            } else if (SDCProviderComponentStateHandler<VmdState> * t_casted = dynamic_cast<SDCProviderComponentStateHandler<VmdState> *>(t_handler.second)) {
                m_MdState.addState(t_casted->getInitialState());
            } else if (SDCProviderComponentStateHandler<ChannelState> * t_casted = dynamic_cast<SDCProviderComponentStateHandler<ChannelState>*>(t_handler.second)) {
                m_MdState.addState(t_casted->getInitialState());
            } else if (dynamic_cast<SDCProviderActivateOperationHandler *>(t_handler.second)) {
                // NOOP
                // well I gess not...
            } else if (SDCProviderMDStateHandler<LocationContextState>  * t_casted = dynamic_cast<SDCProviderMDStateHandler<LocationContextState>*>(t_handler.second)) {
                m_MdState.addState(t_casted->getInitialState());
            } else if (SDCProviderMDStateHandler<PatientContextState>  * t_casted = dynamic_cast<SDCProviderMDStateHandler<PatientContextState>*>(t_handler.second)) {
                m_MdState.addState(t_casted->getInitialState());
            } else if (SDCProviderMDStateHandler<MeansContextState>  * t_casted = dynamic_cast<SDCProviderMDStateHandler<MeansContextState>*>(t_handler.second)) {
                m_MdState.addState(t_casted->getInitialState());
            } else if (SDCProviderMDStateHandler<WorkflowContextState>  * t_casted = dynamic_cast<SDCProviderMDStateHandler<WorkflowContextState>*>(t_handler.second)) {
                m_MdState.addState(t_casted->getInitialState());
            } else if (SDCProviderMDStateHandler<OperatorContextState>  * t_casted = dynamic_cast<SDCProviderMDStateHandler<OperatorContextState>*>(t_handler.second)) {
                m_MdState.addState(t_casted->getInitialState());
            } else if (SDCProviderMDStateHandler<EnsembleContextState>  * t_casted = dynamic_cast<SDCProviderMDStateHandler<EnsembleContextState>*>(t_handler.second)) {
                m_MdState.addState(t_casted->getInitialState());
            } else {
                log_fatal([] { return "Unknown handler type! This is an implementation error in the SDCLib!"; });
                return false;
            }
        }
    } // UNLOCK

    // Start AsyncProviderInvoker
    startAsyncProviderInvoker();

    // Validation
    {
		const xml_schema::Flags t_xercesFlags(xml_schema::Flags::dont_validate | xml_schema::Flags::no_xml_declaration | xml_schema::Flags::dont_initialize);
		std::ostringstream t_xml;
		xml_schema::NamespaceInfomap tl_map;
		CDM::MdibContainer(t_xml, *ConvertToCDM::convert(getMdib()), tl_map, OSELib::XML_ENCODING, t_xercesFlags);

		OSELib::SDC::DefaultSDCSchemaGrammarProvider t_grammarProvider;
		auto t_rawMessage = OSELib::Helper::Message::create(t_xml.str());
		auto t_xercesDocument = OSELib::Helper::XercesDocumentWrapper::create(*t_rawMessage, t_grammarProvider);
		std::unique_ptr<CDM::Mdib> t_result(CDM::MdibContainer(t_xercesDocument->getDocument()));
		if (nullptr == t_result) {
			log_fatal([&] { return "Fatal error, can't create MDIB - schema validation error! Offending MDIB: \n" + t_xml.str(); });
			return false;
		}
    }

    // Set the flag
    m_started = true;
    return true;
}

void SDCProvider::shutdown()
{
    std::lock_guard<std::mutex> t_lock{m_mutex};
    // FIXME: This really needs to be fixed... Shutdown takes some time, synchro etc...
    stopAsyncProviderInvoker();

	if (m_adapter) {
		m_adapter->stop();
		m_adapter.reset();
	}

	{ // LOCK - Clear MdDescription
        std::lock_guard<std::mutex> t_lock{m_mutex_MdDescription};
        if(m_MdDescription != nullptr) {
            m_MdDescription->clearMdsList();
            m_MdDescription.reset();
        }
    }
}

template<class T> void SDCProvider::replaceState(const T & p_object)
{
    std::lock_guard<std::mutex> t_lock{m_mutex_MdState};
    // Check for existing state
    std::unique_ptr<CDM::MdState> t_cachedStates(ConvertToCDM::convert(m_MdState));
    CDM::MdState t_target;
    for (const auto & t_state : t_cachedStates->State()) {
        if (t_state.DescriptorHandle() == p_object.getDescriptorHandle()) {
            // Found, add parameter instead of current
        	t_target.State().push_back(*ConvertToCDM::convert(p_object));
            continue;
        }
        // Copy
        t_target.State().push_back(t_state);
    }
    m_MdState = ConvertFromCDM::convert(t_target);
}


void SDCProvider::addMdStateHandler(SDCProviderStateHandler* p_handler)
{
    assert(p_handler != nullptr);

    // Safety check
    if(p_handler == nullptr) {
        return;
    }

    std::lock_guard<std::mutex> t_lock{m_mutex_MdStateHandler};

    p_handler->parentProvider = this;

    // TODO: Multistates implementation.. regarding to the SDC standard it should be possible to define states with the same descriptor handle!
    // this is only possible for context states. maybe do a type check.
    // but before implementing -> check the whole frameworks mechanics
    if (ml_stateHandlers.find(p_handler->getDescriptorHandle()) != ml_stateHandlers.end()) {
        log_error([&] { return "A SDCProvider handler for handle " + p_handler->getDescriptorHandle() + " already exists. It will be overridden."; });
    }

    // ToDo: Behold! check with simpleSDC if this really works°!
    if (auto t_activate_handler = dynamic_cast<SDCProviderActivateOperationHandler *>(p_handler)) {
    	const MdDescription t_mddescription(getMdDescription());

        for (const auto & t_mds : t_mddescription.collectAllMdsDescriptors()) {
    		if (!t_mds.hasSco()) {
    			continue;
    		}

    		const auto t_sco(ConvertToCDM::convert(t_mds.getSco()));
    		for (const auto & t_operation : t_sco->Operation()) {
    			if (t_operation.Handle() == t_activate_handler->getDescriptorHandle()
    					&& nullptr != dynamic_cast<const CDM::ActivateOperationDescriptor *>(&t_operation)) { // FIXME: std::addressof?
    				ml_stateHandlers[p_handler->getDescriptorHandle()] = p_handler;
    				return;
    			}
    		}
    	}
    	log_error([] { return "Could not add handler because no ActivateOperationDescriptor with matching handle was found."; });
    }

    // TODO: Move streaming service to service controller
    // add DistributionArray...
    else if (/*auto streamHandler = */dynamic_cast<SDCProviderMDStateHandler<RealTimeSampleArrayMetricState> *>(p_handler)) {
        //int port = SDCLibrary::getInstance().extractFreePort();
        //m_adapter->addStreamingPort(4444);
        // FIXME: delete after testing that streaming works on more than one address!
        // FIXME: MAGIC NUMBERS...!!!!
        //m_adapter->addStreamingPort(OSELib::SDC::MDPWS_MCAST_PORT);
    	ml_stateHandlers[p_handler->getDescriptorHandle()] = p_handler;
    }
    else {
		ml_stateHandlers[p_handler->getDescriptorHandle()] = p_handler;
	}
}


void SDCProvider::removeMDStateHandler(SDCProviderStateHandler* p_handler)
{
    assert(p_handler != nullptr);
    std::lock_guard<std::mutex> t_lock{m_mutex_MdStateHandler};
    ml_stateHandlers.erase(p_handler->getDescriptorHandle());
}



bool SDCProvider::setMdDescription(const MdDescription & p_MdDescription)
{
	std::lock_guard<std::mutex> t_lock{m_mutex_MdDescription};
	m_MdDescription = std::unique_ptr<MdDescription>(new MdDescription(p_MdDescription));
    return true; // Interface consistency with std::string (parsing) version
}

bool SDCProvider::setMdDescription(std::string p_xml)
{
    if(p_xml.empty()) {
        return false;
    }

    std::lock_guard<std::mutex> t_lock{m_mutex_MdDescription};
	OSELib::SDC::DefaultSDCSchemaGrammarProvider t_grammarProvider;
	auto t_rawMessage = OSELib::Helper::Message::create(p_xml);
	auto t_xercesDocument = OSELib::Helper::XercesDocumentWrapper::create(*t_rawMessage, t_grammarProvider);

	std::unique_ptr<CDM::Mdib> t_result(CDM::MdibContainer(t_xercesDocument->getDocument()));

	if ((nullptr != t_result) && (t_result->MdDescription().present())) {
        std::unique_ptr<MdDescription> t_MdDescription(new MdDescription(ConvertFromCDM::convert(t_result->MdDescription().get())));
        if(nullptr == t_MdDescription) {
            return false;
        }
        m_MdDescription = std::move(t_MdDescription);
        return true;
    }
    log_fatal([&] { return " Fatal error, can't create MDIB - schema validation error! Offending MDIB: \n" + p_xml; });
    return false;
}
MdDescription SDCProvider::getMdDescription() const
{
    std::lock_guard<std::mutex> t_lock{m_mutex_MdDescription};
    return *m_MdDescription; // FIXME: What if nullptr?
}


void SDCProvider::setEndpointReference(const std::string& p_epr)
{
    if(p_epr.empty()) {
        return;
    }
    // Set EPR
    std::lock_guard<std::mutex> t_lock{m_mutex_EPR};
    m_endpointReference = p_epr;
}
void SDCProvider::setEndpointReferenceByName(const std::string& p_name)
{
    if(p_name.empty()) {
        return;
    }

    // Set EPR
    std::lock_guard<std::mutex> t_lock{m_mutex_EPR};
    m_endpointReference = SDCInstance::calcUUIDv5(p_name, true);
}

std::string SDCProvider::getEndpointReference() const
{
    std::lock_guard<std::mutex> t_lock{m_mutex_EPR};
    return std::string(m_endpointReference);
}

template<typename T> InvocationState SDCProvider::onStateChangeRequest(const T & p_state, const OperationInvocationContext & p_oic)
{
    auto t_iter(ml_stateHandlers.find(p_state.getDescriptorHandle()));
    if (t_iter != ml_stateHandlers.end()) {
    	if (SDCProviderMDStateHandler<T> * t_handler = dynamic_cast<SDCProviderMDStateHandler<T> *>(t_iter->second)) {
        	return t_handler->onStateChangeRequest(p_state, p_oic);
    	}
    }
    return InvocationState::Fail;
}

void SDCProvider::notifyOperationInvoked(const OperationInvocationContext & p_oic, Data::SDC::InvocationState p_is)
{
	if (p_oic.transactionId == 0 && p_oic.operationHandle.empty()) {
		return;
	}

	// todo: replace IstanceIdentifier by real value
	MDM::ReportPart5 t_oirPart(MDM::InvocationInfo(p_oic.transactionId, ConvertToCDM::convert(p_is)), CDM::InstanceIdentifier(), p_oic.operationHandle);
	// todo: replace sequence id
	MDM::OperationInvokedReport t_oir(xml_schema::Uri("0"));
	t_oir.MdibVersion(getMdibVersion());
	t_oir.ReportPart().push_back(t_oirPart);

	m_adapter->notifyEvent(t_oir);
}

template<class T>
bool SDCProvider::addSetOperationToSCOObjectImpl(const T & p_source, MdsDescriptor & p_ownerMDS)
{
	// get sco object or create new
	std::unique_ptr<CDM::ScoDescriptor> t_scoDescriptor(Defaults::ScoDescriptorInit(xml_schema::Uri("")));
	if (p_ownerMDS.hasSco()) {
		t_scoDescriptor = ConvertToCDM::convert(p_ownerMDS.getSco());
	} else {
		// only set handle if previously created
		t_scoDescriptor->Handle(p_ownerMDS.getHandle() + "_sco");
	}

	// add operation descriptor to sco and write back to mds
	t_scoDescriptor->Operation().push_back(p_source);
	p_ownerMDS.setSco(ConvertFromCDM::convert(*t_scoDescriptor));


	// Search if already exists - 2 Matching criteria: HandleName and Type
	std::unique_ptr<CDM::MdState> tl_cachedOperationStates(ConvertToCDM::convert(m_operationStates));
	for (const auto & t_state : tl_cachedOperationStates->State()) {
		if (t_state.DescriptorHandle() == p_source.Handle()) {
			if (dynamic_cast<const CDM::AbstractOperationState *>(std::addressof(t_state))) {
				return false;
			}
		}
	}

	// Now add a state object for the sco descriptor to the cached states.
	// Add new operation state and Emit OperationalState event
	if (dynamic_cast<const CDM::SetValueOperationDescriptor *>(std::addressof(p_source))) {
		auto t_operationState = CDM::SetValueOperationState(p_source.Handle(), CDM::OperatingMode::En);
		tl_cachedOperationStates->State().push_back(t_operationState);
		notifyEpisodicOperationalStateImpl(SetValueOperationState(t_operationState)); // Emit an event!
	} else if (dynamic_cast<const CDM::SetStringOperationDescriptor *>(std::addressof(p_source))) {
		auto t_operationState = CDM::SetStringOperationState(p_source.Handle(), CDM::OperatingMode::En);
		tl_cachedOperationStates->State().push_back(t_operationState);
		notifyEpisodicOperationalStateImpl(SetStringOperationState(t_operationState)); // Emit an event!
	} else if (dynamic_cast<const CDM::SetAlertStateOperationDescriptor *>(std::addressof(p_source))) {
		auto t_operationState = CDM::SetAlertStateOperationState(p_source.Handle(), CDM::OperatingMode::En);
		tl_cachedOperationStates->State().push_back(t_operationState);
		notifyEpisodicOperationalStateImpl(SetAlertStateOperationState(t_operationState)); // Emit an event!
	} else if (dynamic_cast<const CDM::SetComponentStateOperationDescriptor*>(std::addressof(p_source))) {
		auto t_operationState = CDM::SetComponentStateOperationState(p_source.Handle(), CDM::OperatingMode::En);
		tl_cachedOperationStates->State().push_back(t_operationState);
		notifyEpisodicOperationalStateImpl(SetComponentStateOperationState(t_operationState)); // Emit an event!
	} else if (dynamic_cast<const CDM::SetContextStateOperationDescriptor *>(std::addressof(p_source))) {
		auto t_operationState = CDM::SetContextStateOperationState(p_source.Handle(), CDM::OperatingMode::En);
		tl_cachedOperationStates->State().push_back(t_operationState);
		notifyEpisodicOperationalStateImpl(SetContextStateOperationState(t_operationState)); // Emit an event!
	} else if (dynamic_cast<const CDM::SetMetricStateOperationDescriptor *>(std::addressof(p_source))) {
		auto t_operationState = CDM::SetMetricStateOperationState(p_source.Handle(), CDM::OperatingMode::En);
		tl_cachedOperationStates->State().push_back(t_operationState);
		notifyEpisodicOperationalStateImpl(SetMetricStateOperationState(t_operationState)); // Emit an event!
	} else {
		log_error([] { return "SDCProvider::addSetOperationToSCOObjectImpl: dynamic_cast found no match for source!"; });
		return false;
	}
	// replace cached states by update.
	m_operationStates = ConvertFromCDM::convert(*tl_cachedOperationStates);
	return true;
}

void SDCProvider::addActivateOperationForDescriptor(const ActivateOperationDescriptor & p_descriptor, MdsDescriptor & p_ownerMDS) {
	addSetOperationToSCOObjectImpl(*ConvertToCDM::convert(p_descriptor), p_ownerMDS);
}

void SDCProvider::createSetOperationForDescriptor(const AlertConditionDescriptor & p_descriptor, MdsDescriptor & p_ownerMDS)
{
	const CDM::SetAlertStateOperationDescriptor t_setOperation(p_descriptor.getHandle() + "_sco", p_descriptor.getHandle());
	addSetOperationToSCOObjectImpl(t_setOperation, p_ownerMDS);
}

void SDCProvider::createSetOperationForDescriptor(const AlertSignalDescriptor & p_descriptor, MdsDescriptor & p_ownerMDS)
{
	const CDM::SetAlertStateOperationDescriptor t_setOperation(p_descriptor.getHandle() + "_sco", p_descriptor.getHandle());
	addSetOperationToSCOObjectImpl(t_setOperation, p_ownerMDS);
}

void SDCProvider::createSetOperationForDescriptor(const AlertSystemDescriptor & p_descriptor, MdsDescriptor & p_ownerMDS)
{
	const CDM::SetAlertStateOperationDescriptor t_setOperation(p_descriptor.getHandle() + "_sco", p_descriptor.getHandle());
	addSetOperationToSCOObjectImpl(t_setOperation, p_ownerMDS);
}

void SDCProvider::createSetOperationForDescriptor(const EnumStringMetricDescriptor & p_descriptor, MdsDescriptor & p_ownerMDS)
{
	const CDM::SetStringOperationDescriptor t_setOperation(p_descriptor.getHandle() + "_sco", p_descriptor.getHandle());
	addSetOperationToSCOObjectImpl(t_setOperation, p_ownerMDS);
}

void SDCProvider::createSetOperationForDescriptor(const LimitAlertConditionDescriptor & p_descriptor, MdsDescriptor & p_ownerMDS)
{
	const CDM::SetAlertStateOperationDescriptor t_setOperation(p_descriptor.getHandle() + "_sco", p_descriptor.getHandle());
	addSetOperationToSCOObjectImpl(t_setOperation, p_ownerMDS);
}

void SDCProvider::createSetOperationForDescriptor(const NumericMetricDescriptor & p_descriptor, MdsDescriptor & p_ownerMDS)
{
	const CDM::SetValueOperationDescriptor t_setOperation(p_descriptor.getHandle() + "_sco", p_descriptor.getHandle());
	addSetOperationToSCOObjectImpl(t_setOperation, p_ownerMDS);
}

void SDCProvider::createSetOperationForDescriptor(const StringMetricDescriptor & p_descriptor, MdsDescriptor & p_ownerMDS)
{
	const CDM::SetStringOperationDescriptor t_setOperation(p_descriptor.getHandle() + "_sco", p_descriptor.getHandle());
	addSetOperationToSCOObjectImpl(t_setOperation, p_ownerMDS);
}

template<class T>
void SDCProvider::createSetOperationForContextDescriptor(const T & p_descriptor, MdsDescriptor & p_ownerMDS)
{
	const CDM::SetContextStateOperationDescriptor t_setOperation(p_descriptor.getHandle() + "_sco", p_descriptor.getHandle());
	addSetOperationToSCOObjectImpl(t_setOperation, p_ownerMDS);
}

void SDCProvider::createSetOperationForDescriptor(const PatientContextDescriptor & p_descriptor, MdsDescriptor & p_ownerMDS) {
	createSetOperationForContextDescriptor(p_descriptor, p_ownerMDS);
}

void SDCProvider::createSetOperationForDescriptor(const LocationContextDescriptor & p_descriptor, MdsDescriptor & p_ownerMDS) {
	createSetOperationForContextDescriptor(p_descriptor, p_ownerMDS);
}

void SDCProvider::createSetOperationForDescriptor(const EnsembleContextDescriptor & p_descriptor, MdsDescriptor & p_ownerMDS) {
	createSetOperationForContextDescriptor(p_descriptor, p_ownerMDS);
}

void SDCProvider::createSetOperationForDescriptor(const OperatorContextDescriptor & p_descriptor, MdsDescriptor & p_ownerMDS) {
	createSetOperationForContextDescriptor(p_descriptor, p_ownerMDS);
}

void SDCProvider::createSetOperationForDescriptor(const WorkflowContextDescriptor & p_descriptor, MdsDescriptor & p_ownerMDS) {
	createSetOperationForContextDescriptor(p_descriptor, p_ownerMDS);
}

Dev::DeviceCharacteristics SDCProvider::getDeviceCharacteristics() const
{
    std::lock_guard<std::mutex> t_lock{m_mutex_DevC};
    return m_devicecharacteristics;
}

void SDCProvider::setDeviceCharacteristics(const Dev::DeviceCharacteristics p_deviceCharacteristics)
{
    std::lock_guard<std::mutex> t_lock{m_mutex_DevC};
    // add endpointReference to deviceCharacteristics because the host metadata need to provide the endpoint reference
	m_devicecharacteristics = p_deviceCharacteristics;
    // add endpointReference to deviceCharacteristics because the host metadata need to provide the endpoint reference
	m_devicecharacteristics.setEndpointReference(m_endpointReference);
}

unsigned long long int SDCProvider::getMdibVersion() const {
	return mdibVersion;
}

void SDCProvider::incrementMDIBVersion() {
	mdibVersion++;
}

void SDCProvider::setPeriodicEventInterval(std::chrono::milliseconds p_interval)
{
	// TODO: Why 250?
	if (p_interval > std::chrono::milliseconds(250)) {
		m_periodicEventInterval = p_interval;
	}
}
std::chrono::milliseconds SDCProvider::getPeriodicEventInterval() const
{
    return m_periodicEventInterval;
}
std::vector<std::string> SDCProvider::getHandlesForPeriodicUpdate() const
{
    std::lock_guard<std::mutex> t_lock{m_mutex_PeriodicUpdateHandles};
    return ml_handlesForPeriodicUpdates;
}

void SDCProvider::addHandleForPeriodicEvent(const std::string & p_handle)
{
    std::lock_guard<std::mutex> t_lock{m_mutex_PeriodicUpdateHandles};
    ml_handlesForPeriodicUpdates.push_back(p_handle);
}
void SDCProvider::removeHandleForPeriodicEvent(const std::string & p_handle)
{
    std::lock_guard<std::mutex> t_lock{m_mutex_PeriodicUpdateHandles};
    ml_handlesForPeriodicUpdates.erase(
    std::remove(ml_handlesForPeriodicUpdates.begin(), ml_handlesForPeriodicUpdates.end(), p_handle), ml_handlesForPeriodicUpdates.end());
}

void SDCProvider::startAsyncProviderInvoker()
{
    if(m_providerInvoker == nullptr) {
        m_providerInvoker = std::make_shared<AsyncProviderInvoker>(*this, m_invokeQueue);
        m_providerInvoker->start();
    }
}
void SDCProvider::stopAsyncProviderInvoker()
{
    if(m_providerInvoker == nullptr) {
        return;
    }
    m_providerInvoker->interrupt();
    m_providerInvoker.reset();
}

void SDCProvider::setLastPeriodicEvent(TimePoint p_timepoint)
{
    std::lock_guard<std::mutex> t_lock{m_mutex_PeriodicEvent};
    m_lastPeriodicEvent = p_timepoint;
}
TimePoint SDCProvider::getLastPeriodicEvent() const
{
    std::lock_guard<std::mutex> t_lock{m_mutex_PeriodicEvent};
    return m_lastPeriodicEvent;
}

}
}
}
