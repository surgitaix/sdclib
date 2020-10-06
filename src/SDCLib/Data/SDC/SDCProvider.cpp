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
#include "SDCLib/Data/SDC/MDIB/ActivateOperationState.h"
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
#include "SDCLib/Data/SDC/MDIB/VmdDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/VmdState.h"
#include "SDCLib/Data/SDC/MDIB/ChannelDescriptor.h"
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
#include "SDCLib/Data/SDC/MDIB/SampleArrayValue.h"
#include "SDCLib/Data/SDC/MDIB/SetValueOperationState.h"
#include "SDCLib/Data/SDC/MDIB/SetStringOperationState.h"
#include "SDCLib/Data/SDC/MDIB/SetAlertStateOperationState.h"
#include "SDCLib/Data/SDC/MDIB/SetAlertStateOperationDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/SetComponentStateOperationState.h"
#include "SDCLib/Data/SDC/MDIB/SetContextStateOperationState.h"
#include "SDCLib/Data/SDC/MDIB/SetContextStateOperationDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/SetMetricStateOperationState.h"
#include "SDCLib/Data/SDC/MDIB/SetStringOperationDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/SetValueOperationDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ScoDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ScoState.h"
#include "SDCLib/Data/SDC/MDIB/SystemContextDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/SystemContextState.h"
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
#include <Poco/Notification.h>

const std::size_t INITIAL_STATE_VERSION = 0;

namespace SDCLib
{
    namespace Data
    {
        namespace SDC
        {
            template<class T> class SetNotification : public Poco::Notification
            {
            public:
                SetNotification(const T& p_request, const OperationInvocationContext& p_oic)
                    : m_request(p_request)
                    , m_oic(p_oic)
                {
                }
                const T m_request;
                const OperationInvocationContext m_oic;
            };


            // FIXME - Task class and this class need to be fixed!

            class AsyncProviderInvoker : public Util::Task, OSELib::Helper::WithLogger
            {
            private:
                SDCProvider& m_provider;
                Poco::NotificationQueue&
                    m_queue; // FIXME: Non const ref to notification queue! -> Who is the "owner" and syncs the read/write access?

            public:
                AsyncProviderInvoker(SDCProvider& p_provider, Poco::NotificationQueue& p_queue)
                    : OSELib::Helper::WithLogger(OSELib::Log::sdcProvider)
                    , m_provider(p_provider)
                    , m_queue(p_queue)
                {
                }

                void runImpl() override
                {
                    Poco::AutoPtr<Poco::Notification> t_pNf(m_queue.waitDequeueNotification(100));
                    if(t_pNf)
                    {
                        try
                        {
                            if(auto t_notification_SetValue = dynamic_cast<const SetNotification<MDM::SetValue>*>(t_pNf.get()))
                            {
                                m_provider.SetValue(t_notification_SetValue->m_request, t_notification_SetValue->m_oic);
                            }
                            else if(auto t_notification_SetString = dynamic_cast<const SetNotification<MDM::SetString>*>(t_pNf.get()))
                            {
                                m_provider.SetString(t_notification_SetString->m_request, t_notification_SetString->m_oic);
                            }
                            else if(auto t_notification_Activate = dynamic_cast<const SetNotification<MDM::Activate>*>(t_pNf.get()))
                            {
                                m_provider.OnActivate(t_notification_Activate->m_oic);
                            }
                            else if(auto t_notification_SetAlertState = dynamic_cast<const SetNotification<MDM::SetAlertState>*>(
                                        t_pNf.get()))
                            {
                                m_provider.SetAlertState(t_notification_SetAlertState->m_request, t_notification_SetAlertState->m_oic);
                            }
                            else if(auto t_notification_SetContextState = dynamic_cast<const SetNotification<MDM::SetContextState>*>(
                                        t_pNf.get()))
                            {
                                m_provider.SetContextState(t_notification_SetContextState->m_request,
                                                           t_notification_SetContextState->m_oic);
                            }
                            else
                            {
                                log_error([] { return "Unknown invoke data type!"; });
                                // FIXME: What to do here?
                            }
                        }
                        catch(...)
                        {
                            log_error([] { return "Exception caught during async provider invoke."; });
                        }
                    }

                    if(this->isInterrupted())
                    {
                        return;
                    }

                    if(m_provider.getPeriodicEventInterval() < (std::chrono::system_clock::now() - m_provider.getLastPeriodicEvent()))
                    {
                        m_provider.firePeriodicReportImpl();
                        m_provider.setLastPeriodicEvent(m_provider.getLastPeriodicEvent()); // FIXME: Correct impl?
                    }
                }
            };

            //template SDCProviderStateHandler<NumericMetricState>;


            template<class StateType> bool SDCProvider::isMetricChangeAllowed(const StateType& p_state, SDCProvider& p_provider)
            {
                if(!isStarted())
                {
                    return false;
                }

                typename StateType::DescriptorType t_descriptor;
                if(!p_provider.getMdDescription().findDescriptor(p_state.getDescriptorHandle(),
                                                                 t_descriptor)) // FIXME: Put this logic somewhere else!
                {
                    return false;
                }
                if(t_descriptor.getMetricCategory() == MetricCategory::Msrmt) // FIXME: Put this logic somewhere else!
                {
                    return false;
                }
                if(p_state.hasActivationState()) // FIXME: Put this logic somewhere else!
                {
                    return (p_state.getActivationState() == ComponentActivation::On);
                }

                return true;
            }

        } // namespace SDC
    }     // namespace Data
} // namespace SDCLib


using namespace SDCLib;
using namespace SDCLib::Data;
using namespace SDCLib::Data::SDC;

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
    // FIXME: This really needs to be fixed... Shutdown takes some time, synchro etc...
    stopAsyncProviderInvoker();

    if(m_adapter)
    {
        m_adapter.reset();
    }

    if(m_MdDescription != nullptr)
    {
        m_MdDescription->clearMdsList();
        m_MdDescription.reset();
    }
}


unsigned int SDCProvider::incrementAndGetTransactionId()
{
    return (++atomicTransactionId);
}

template<class T> void SDCProvider::enqueueInvokeNotification(const T& p_request, const OperationInvocationContext& p_oic)
{
    std::lock_guard<std::mutex> t_lock{m_mutex_invokeQueue};
    m_invokeQueue.enqueueNotification(new SetNotification<T>(p_request, p_oic));
}

MDM::SetValueResponse SDCProvider::SetValueAsync(const MDM::SetValue& p_request)
{
    const OperationInvocationContext t_oic(p_request.getOperationHandleRef(), incrementAndGetTransactionId());
    const auto t_metricHandle(getMdDescription().getOperationTargetForOperationHandle(t_oic.operationHandle));

    auto genResponse = [this, &t_oic](InvocationState v) {
        notifyOperationInvoked(t_oic, v);
        // TODO: 0 = replace with real sequence ID
        MDM::SetValueResponse svr(MDM::InvocationInfo(t_oic.transactionId, MDM::InvocationState(ConvertToCDM::convert(v))),
                                  xml_schema::Uri("0"));
        svr.setMdibVersion(getMdibVersion());

        return svr;
    };

    NumericMetricState t_nms;
    if(!getMdState().findState(t_metricHandle, t_nms))
    {
        return genResponse(InvocationState::Fail);
    }
    if(!isMetricChangeAllowed(t_nms, *this))
    {
        return genResponse(InvocationState::Fail);
    }

    enqueueInvokeNotification(p_request, t_oic);
    return genResponse(InvocationState::Wait);
}

void SDCProvider::SetValue(const MDM::SetValue& p_request, const OperationInvocationContext& p_oic)
{
    const auto metricHandle(getMdDescription().getOperationTargetForOperationHandle(p_oic.operationHandle));

    NumericMetricState t_nms;
    if(!getMdState().findState(metricHandle, t_nms))
    {
        notifyOperationInvoked(p_oic, InvocationState::Fail);
        return;
    }
    if(!isMetricChangeAllowed(t_nms, *this))
    {
        notifyOperationInvoked(p_oic, InvocationState::Fail);
        return;
    }
    t_nms.setMetricValue(t_nms.getMetricValue().setValue(p_request.getRequestedNumericValue()));

    const InvocationState t_outState(onStateChangeRequest(t_nms, p_oic));
    notifyOperationInvoked(p_oic, t_outState);

    if(InvocationState::Fin == t_outState)
    {
        // Success
        updateState(t_nms);
    }
}

MDM::SetStringResponse SDCProvider::SetStringAsync(const MDM::SetString& p_request)
{
    const OperationInvocationContext t_oic(p_request.getOperationHandleRef(), incrementAndGetTransactionId());

    const MdDescription t_mdd(getMdDescription());

    const auto t_metricHandle(t_mdd.getOperationTargetForOperationHandle(t_oic.operationHandle));
    const auto t_mdsc(getMdState());

    auto genResponse = [this, &t_oic](InvocationState v) {
        notifyOperationInvoked(t_oic, v);
        MDM::SetStringResponse t_ssr(MDM::InvocationInfo(t_oic.transactionId, MDM::InvocationState(ConvertToCDM::convert(v))),
                                     xml_schema::Uri("0"));
        t_ssr.setMdibVersion(getMdibVersion());
        return t_ssr;
    };

    { // TODO: Why { }? Is there a lock somewhere?
        StringMetricState t_sms;
        if(t_mdsc.findState(t_metricHandle, t_sms))
        {
            if(!isMetricChangeAllowed(t_sms, *this))
            {
                return genResponse(InvocationState::Fail);
            }
            enqueueInvokeNotification(p_request, t_oic);
            return genResponse(InvocationState::Wait);
        }
    }
    { // TODO: Why { }? Is there a lock somewhere?
        EnumStringMetricState t_state;
        if(t_mdsc.findState(t_metricHandle, t_state))
        {
            EnumStringMetricDescriptor t_descriptor;
            if(!t_mdd.findDescriptor(t_state.getDescriptorHandle(), t_descriptor))
            {
                return genResponse(InvocationState::Fail);
            }
            if(!isMetricChangeAllowed(t_state, *this))
            {
                return genResponse(InvocationState::Fail);
            }
            const auto tl_allowedValues(t_descriptor.getAllowedValueList());

            const auto& t_requestedStringVal(p_request.getRequestedStringValue());
            std::vector<std::string> tl_allowedValuesString;
            for(const auto t_allowedValue : tl_allowedValues)
            {
                tl_allowedValuesString.push_back(t_allowedValue.getValue());
            }

            auto t_iter = std::find(tl_allowedValuesString.begin(), tl_allowedValuesString.end(), t_requestedStringVal);
            if(t_iter == tl_allowedValuesString.end())
            {
                return genResponse(InvocationState::Fail);
            }
            enqueueInvokeNotification(p_request, t_oic);
            return genResponse(InvocationState::Wait);
        }
    }

    return genResponse(InvocationState::Fail);
}

template<class T> void SDCProvider::SetStringImpl(const T& p_state, const OperationInvocationContext& p_oic)
{
    const InvocationState t_outState(onStateChangeRequest(p_state, p_oic));
    notifyOperationInvoked(p_oic, t_outState);

    if(InvocationState::Fin == t_outState)
    {
        // Success
        updateState(p_state);
    }
}

void SDCProvider::SetString(const MDM::SetString& p_request, const OperationInvocationContext& p_oic)
{
    const auto& t_requestedStringVal(p_request.getRequestedStringValue());

    const auto t_mdsc(getMdState());
    const auto t_mdd(getMdDescription());

    const auto t_metricHandle(t_mdd.getOperationTargetForOperationHandle(p_oic.operationHandle));

    { // TODO: Why { }? Is there a lock somewhere?
        StringMetricState t_sms;
        if(t_mdsc.findState(t_metricHandle, t_sms))
        {
            t_sms.setMetricValue(t_sms.getMetricValue().setValue(t_requestedStringVal));
            SetStringImpl(t_sms, p_oic);
            return;
        }
    }

    { // TODO: Why { }? Is there a lock somewhere?
        EnumStringMetricState t_state;
        if(t_mdsc.findState(t_metricHandle, t_state))
        {
            EnumStringMetricDescriptor t_descriptor;
            if(!t_mdd.findDescriptor(t_state.getDescriptorHandle(), t_descriptor))
            {
                notifyOperationInvoked(p_oic, InvocationState::Fail);
                return;
            }

            const auto tl_allowedValues(t_descriptor.getAllowedValueList());
            std::vector<std::string> tl_allowedValuesString;
            for(auto t_allowedValue : tl_allowedValues)
            {
                tl_allowedValuesString.push_back(t_allowedValue.getValue());
            }

            auto t_iter = std::find(tl_allowedValuesString.begin(), tl_allowedValuesString.end(), t_requestedStringVal);
            if(t_iter == tl_allowedValuesString.end())
            {
                notifyOperationInvoked(p_oic, InvocationState::Fail);
            }
            else
            {
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

MDM::ActivateResponse SDCProvider::OnActivateAsync(const MDM::Activate& p_request)
{
    const OperationInvocationContext t_oic(p_request.getOperationHandleRef(), incrementAndGetTransactionId());
    notifyOperationInvoked(t_oic, InvocationState::Wait);
    enqueueInvokeNotification(p_request, t_oic);

    MDM::ActivateResponse t_ar(MDM::InvocationInfo(t_oic.transactionId, MDM::InvocationState(ConvertToCDM::convert(InvocationState::Wait))),
                               xml_schema::Uri("0"));
    t_ar.setMdibVersion(getMdibVersion());

    return t_ar;
}


void SDCProvider::OnActivate(const OperationInvocationContext& p_oic)
{
    auto t_iter = ml_stateHandlers.find(p_oic.operationHandle);
    if(t_iter != ml_stateHandlers.end())
    {
        if(SDCProviderActivateOperationHandler* t_handler = dynamic_cast<SDCProviderActivateOperationHandler*>(t_iter->second))
        {
            const InvocationState t_isVal(t_handler->onActivateRequest(p_oic));
            notifyOperationInvoked(p_oic, t_isVal);
            return;
        }
    }
    notifyOperationInvoked(p_oic, InvocationState::Fail);
}


template<typename StateType> void SDCProvider::SetAlertStateImpl(const StateType& state, const OperationInvocationContext& oic)
{
    const MdDescription mdd(getMdDescription());

    typename StateType::DescriptorType descriptor;
    if(!mdd.findDescriptor(state.getDescriptorHandle(), descriptor))
    {
        notifyOperationInvoked(oic, InvocationState::Fail);
        return;
    }

    const InvocationState outIS(onStateChangeRequest(state, oic));
    notifyOperationInvoked(oic, outIS);

    // Only signal changed value of metric, when invocation successful.
    if(InvocationState::Fin == outIS)
    {
        updateState(state);
    }
}

MDM::SetAlertStateResponse SDCProvider::SetAlertStateAsync(const MDM::SetAlertState& p_request)
{
    const OperationInvocationContext t_oic(p_request.getOperationHandleRef(), incrementAndGetTransactionId());
    const CDM::AbstractAlertState* t_incomingCDMState = &(p_request.getProposedAlertState());

    auto genResponse = [this, &t_oic](InvocationState v) {
        notifyOperationInvoked(t_oic, v);
        // TODO: 0 = replace with real sequence ID
        MDM::SetAlertStateResponse t_sasr(MDM::InvocationInfo(t_oic.transactionId, MDM::InvocationState(ConvertToCDM::convert(v))),
                                          xml_schema::Uri("0"));
        t_sasr.setMdibVersion(getMdibVersion());

        return t_sasr;
    };

    const auto t_targetHandle(getMdDescription().getOperationTargetForOperationHandle(t_oic.operationHandle));
    if(t_targetHandle.empty())
    {
        return genResponse(InvocationState::Fail);
    }
    if((t_incomingCDMState->getDescriptorHandle() != t_targetHandle))
    {
        return genResponse(InvocationState::Fail);
    }

    // Cast and convert, then call into user code
    if(dynamic_cast<const CDM::AlertConditionState*>(t_incomingCDMState))
    {
        enqueueInvokeNotification(p_request, t_oic);
        return genResponse(InvocationState::Wait);
    }
    else if(dynamic_cast<const CDM::AlertSignalState*>(t_incomingCDMState))
    {
        enqueueInvokeNotification(p_request, t_oic);
        return genResponse(InvocationState::Wait);
    }
    else if(dynamic_cast<const CDM::AlertSystemState*>(t_incomingCDMState))
    {
        enqueueInvokeNotification(p_request, t_oic);
        return genResponse(InvocationState::Wait);
    }
    else if(dynamic_cast<const CDM::LimitAlertConditionState*>(t_incomingCDMState))
    {
        enqueueInvokeNotification(p_request, t_oic);
        return genResponse(InvocationState::Wait);
    }

    // cast failed.
    return genResponse(InvocationState::Fail);
}

void SDCProvider::SetAlertState(const MDM::SetAlertState& p_request, const OperationInvocationContext& p_oic)
{
    const auto t_incomingCDMState = std::addressof(p_request.getProposedAlertState());

    const auto t_targetHandle(getMdDescription().getOperationTargetForOperationHandle(p_oic.operationHandle));
    if(t_targetHandle.empty())
    {
        return notifyOperationInvoked(p_oic, InvocationState::Fail);
    }
    if((t_incomingCDMState->getDescriptorHandle() != t_targetHandle))
    {
        return notifyOperationInvoked(p_oic, InvocationState::Fail);
    }

    // Cast and convert, then call into user code
    if(const auto t_state_AlertConditionState = dynamic_cast<const CDM::AlertConditionState*>(t_incomingCDMState))
    {
        SetAlertStateImpl(ConvertFromCDM::convert(*t_state_AlertConditionState), p_oic);
    }
    else if(const auto t_state_AlertSignalState = dynamic_cast<const CDM::AlertSignalState*>(t_incomingCDMState))
    {
        SetAlertStateImpl(ConvertFromCDM::convert(*t_state_AlertSignalState), p_oic);
    }
    else if(const auto t_state_AlertSystemState = dynamic_cast<const CDM::AlertSystemState*>(t_incomingCDMState))
    {
        SetAlertStateImpl(ConvertFromCDM::convert(*t_state_AlertSystemState), p_oic);
    }
    else if(const auto t_state_LimitAlertConditionState = dynamic_cast<const CDM::LimitAlertConditionState*>(t_incomingCDMState))
    {
        SetAlertStateImpl(ConvertFromCDM::convert(*t_state_LimitAlertConditionState), p_oic);
    }
    else
    {
        notifyOperationInvoked(p_oic, InvocationState::Fail);
    }

    return;
}

MDM::GetMdStateResponse SDCProvider::GetMdState(const MDM::GetMdState& p_request)
{
    auto t_sdmMdStates(ConvertToCDM::convert(getMdState()));
    if(p_request.getHandleRef().empty())
    {
        //TODO: use real SequenceID, not 0
        MDM::GetMdStateResponse t_mdstateResponse(xml_schema::Uri("0"), std::move(t_sdmMdStates));
        t_mdstateResponse.setMdibVersion(getMdibVersion());
        return t_mdstateResponse;
    }

    CDM::MdState t_tmpmds;
    const std::set<std::string> t_reqHandles(p_request.getHandleRef().begin(), p_request.getHandleRef().end());
    for(const auto& t_nextState : t_sdmMdStates->getState())
    {
        if(t_reqHandles.find(t_nextState.getDescriptorHandle()) != t_reqHandles.end())
        {
            t_tmpmds.getState().push_back(t_nextState);
        }
    }

    //TODO: use real SequenceID, not 0
    MDM::GetMdStateResponse t_mdstateResponse(xml_schema::Uri("0"), t_tmpmds);
    t_mdstateResponse.setMdibVersion(getMdibVersion());
    return t_mdstateResponse;
}

MDM::GetContextStatesResponse SDCProvider::GetContextStates(const MDM::GetContextStates& p_request)
{
    const auto t_states(ConvertToCDM::convert(getMdState()));

    //TODO: use real SequenceID, not 0
    MDM::GetContextStatesResponse t_contextStates(xml_schema::Uri("0"));
    for(const auto& t_state : t_states->getState())
    {
        if(const auto t_state_EnsembleContextState = dynamic_cast<const CDM::EnsembleContextState*>(&t_state)) // FIXME: std::addressof?
        {
            t_contextStates.getContextState().push_back(*t_state_EnsembleContextState);
        }
        else if(const auto t_state_LocationContextState = dynamic_cast<const CDM::LocationContextState*>(
                    &t_state)) // FIXME: std::addressof?
        {
            t_contextStates.getContextState().push_back(*t_state_LocationContextState);
        }
        else if(const auto t_state_OperatorContextState = dynamic_cast<const CDM::OperatorContextState*>(
                    &t_state)) // FIXME: std::addressof?
        {
            t_contextStates.getContextState().push_back(*t_state_OperatorContextState);
        }
        else if(const auto t_state_PatientContextState = dynamic_cast<const CDM::PatientContextState*>(&t_state)) // FIXME: std::addressof?
        {
            t_contextStates.getContextState().push_back(*t_state_PatientContextState);
        }
        else if(const auto t_state_WorkflowContextState = dynamic_cast<const CDM::WorkflowContextState*>(
                    &t_state)) // FIXME: std::addressof?
        {
            t_contextStates.getContextState().push_back(*t_state_WorkflowContextState);
        }
    }

    if(p_request.getHandleRef().empty())
    {
        // TODO: 0 = replace with real sequence ID
        MDM::GetContextStatesResponse t_result(xml_schema::Uri("0"));
        t_result.setMdibVersion(getMdibVersion());
        for(const auto& t_state : t_contextStates.getContextState())
        {
            t_result.getContextState().push_back(t_state);
        }
        return t_result;
    }
    else
    {
        // TODO: 0 = replace with real sequence ID
        MDM::GetContextStatesResponse t_result(xml_schema::Uri("0"));
        t_result.setMdibVersion(getMdibVersion());
        const std::set<std::string> t_reqHandles(p_request.getHandleRef().begin(), p_request.getHandleRef().end());
        for(const auto& state : t_contextStates.getContextState())
        {
            if(t_reqHandles.find(state.getDescriptorHandle()) != t_reqHandles.end())
            {
                t_result.getContextState().push_back(state);
            }
        }
        return t_result;
    }
    // TODO: 0 = replace with real sequence ID
    MDM::GetContextStatesResponse t_result(xml_schema::Uri("0"));
    log_warning([] { return "The requested states handle or descriptor handle does not fit any of the provider's states"; });
    t_result.setMdibVersion(getMdibVersion());
    return t_result;
}

MDM::SetContextStateResponse SDCProvider::SetContextStateAsync(const MDM::SetContextState& p_request)
{
    const OperationInvocationContext t_oic(p_request.getOperationHandleRef(), incrementAndGetTransactionId());

    auto genResponse = [this, &t_oic](InvocationState v) {
        notifyOperationInvoked(t_oic, v);
        // TODO: 0 = replace with real sequence ID
        MDM::SetContextStateResponse t_scsr(MDM::InvocationInfo(t_oic.transactionId, ConvertToCDM::convert(v)), xml_schema::Uri("0"));
        t_scsr.setMdibVersion(getMdibVersion());
        return t_scsr;
    };

    const auto t_targetHandle(getMdDescription().getOperationTargetForOperationHandle(t_oic.operationHandle));
    if(t_targetHandle.empty())
    {
        return genResponse(InvocationState::Fail);
    }

    enqueueInvokeNotification(p_request, t_oic);
    return genResponse(InvocationState::Wait);
}


template<class TState> void SDCProvider::SetContextStateImpl(const TState& p_state, const OperationInvocationContext& p_oic)
{
    // FIXME: check if writing to context state is allowed! = SCO exists
    const InvocationState t_outState(onStateChangeRequest(p_state, p_oic));
    notifyOperationInvoked(p_oic, t_outState);
    if(InvocationState::Fin == t_outState)
    {
        // Success
        updateState(p_state);
    }
}

void SDCProvider::SetContextState(const MDM::SetContextState& p_request, const OperationInvocationContext& p_oic)
{
    // FIXME: for-loop + dynamic_cast: Refactor(?)
    for(const auto& t_nextState : p_request.getProposedContextState())
    {
        if(const auto t_state_PatientContextState = dynamic_cast<const CDM::PatientContextState*>(&t_nextState)) // FIXME: std::addressof ?
        {
            SetContextStateImpl(ConvertFromCDM::convert(*t_state_PatientContextState), p_oic);
        }
        else if(const auto t_state_LocationContextState = dynamic_cast<const CDM::LocationContextState*>(
                    &t_nextState)) // FIXME: std::addressof ?
        {
            SetContextStateImpl(ConvertFromCDM::convert(*t_state_LocationContextState), p_oic);
        }
        else if(const auto t_state_EnsembleContextState = dynamic_cast<const CDM::EnsembleContextState*>(
                    &t_nextState)) // FIXME: std::addressof ?
        {
            SetContextStateImpl(ConvertFromCDM::convert(*t_state_EnsembleContextState), p_oic);
        }
        else if(const auto t_state_OperatorContextState = dynamic_cast<const CDM::OperatorContextState*>(
                    &t_nextState)) // FIXME: std::addressof ?
        {
            SetContextStateImpl(ConvertFromCDM::convert(*t_state_OperatorContextState), p_oic);
        }
        else if(const auto t_state_WorkflowContextState = dynamic_cast<const CDM::WorkflowContextState*>(
                    &t_nextState)) // FIXME: std::addressof ?
        {
            SetContextStateImpl(ConvertFromCDM::convert(*t_state_WorkflowContextState), p_oic);
        }
        else if(const auto t_state_MeansContextState = dynamic_cast<const CDM::MeansContextState*>(&t_nextState)) // FIXME: std::addressof ?
        {
            SetContextStateImpl(ConvertFromCDM::convert(*t_state_MeansContextState), p_oic);
        }
    }
}


MDM::GetMdibResponse SDCProvider::GetMdib(const MDM::GetMdib&) // FIXME: Signature?
{
    // TODO: 0 = replace with real sequence ID
    MDM::GetMdibResponse t_mdib(xml_schema::Uri("0"), ConvertToCDM::convert(getMdib()));
    t_mdib.setMdibVersion(getMdibVersion());
    return t_mdib;
}

MDM::GetMdDescriptionResponse SDCProvider::GetMdDescription(const MDM::GetMdDescription& p_request)
{
    auto t_cdmMdd(ConvertToCDM::convert(getMdDescription()));
    if(p_request.getHandleRef().empty())
    {
        // TODO: 0 = replace with real sequence ID
        MDM::GetMdDescriptionResponse t_mddr(xml_schema::Uri("0"), std::move(t_cdmMdd));
        t_mddr.setMdibVersion(getMdibVersion());
        return t_mddr;
    }
    CDM::MdDescription t_filteredDescription;
    for(const auto& t_mds : t_cdmMdd->getMds())
    {
        if(std::find(p_request.getHandleRef().begin(), p_request.getHandleRef().end(), t_mds.getHandle()) != p_request.getHandleRef().end())
        {
            t_filteredDescription.getMds().push_back(t_mds);
        }
    }
    MDM::GetMdDescriptionResponse t_gmddr(xml_schema::Uri("0"), t_filteredDescription);
    t_gmddr.setMdibVersion(getMdibVersion());
    return t_gmddr;
}

void SDCProvider::updateState(const AlertSystemState& p_object)
{
    updateMDIB(p_object);
    notifyAlertEventImpl(p_object);
}

void SDCProvider::updateState(const AlertSignalState& p_object)
{
    updateMDIB(p_object);
    notifyAlertEventImpl(p_object);
}

void SDCProvider::updateState(const AlertConditionState& p_object)
{
    updateMDIB(p_object);
    reevaluateAlertConditions(p_object.getDescriptorHandle());
    notifyAlertEventImpl(p_object);
}

void SDCProvider::updateState(const EnumStringMetricState& p_object)
{
    updateMDIB(p_object);
    evaluateAlertConditions(p_object.getDescriptorHandle());
    notifyEpisodicMetricImpl(p_object);
}

void SDCProvider::updateState(const LimitAlertConditionState& p_object)
{
    updateMDIB(p_object);
    //Evaluate Alert Conditions sources, based on changes to the AlertCoditionState
    reevaluateAlertConditions(p_object.getDescriptorHandle());
    notifyAlertEventImpl(p_object);
}

void SDCProvider::updateState(const NumericMetricState& p_object)
{
    updateMDIB(p_object);
    evaluateAlertConditions(p_object.getDescriptorHandle());
    notifyEpisodicMetricImpl(p_object);
}


void SDCProvider::updateState(const StringMetricState& p_object)
{
    updateMDIB(p_object);
    evaluateAlertConditions(p_object.getDescriptorHandle());
    notifyEpisodicMetricImpl(p_object);
}


// regarding to the given standard the DSAMS is implemented as an TCP transported Metric
void SDCProvider::updateState(const DistributionSampleArrayMetricState& p_object)
{
    updateMDIB(p_object);
    evaluateAlertConditions(p_object.getDescriptorHandle());
    notifyEpisodicMetricImpl(p_object);
}

// UDP metrices
void SDCProvider::updateState(const RealTimeSampleArrayMetricState& p_object)
{
    // FIXME: This increments the MDIB but does not dispatch an event -> see notifyStreamMetricImpl
    updateMDIB(p_object);
    evaluateAlertConditions(p_object.getDescriptorHandle());
    notifyStreamMetricImpl(p_object);
}


// context states
void SDCProvider::updateState(const EnsembleContextState& p_object)
{
    updateMDIB(p_object);
    notifyContextEventImpl(p_object);
}

void SDCProvider::updateState(const MeansContextState& p_object)
{
    updateMDIB(p_object);
    notifyContextEventImpl(p_object);
}

void SDCProvider::updateState(const LocationContextState& p_object)
{
    updateMDIB(p_object);
    notifyContextEventImpl(p_object);
}

void SDCProvider::updateState(const WorkflowContextState& p_object)
{
    updateMDIB(p_object);
    notifyContextEventImpl(p_object);
}

void SDCProvider::updateState(const PatientContextState& p_object)
{
    updateMDIB(p_object);
    notifyContextEventImpl(p_object);
}

void SDCProvider::updateState(const OperatorContextState& p_object)
{
    updateMDIB(p_object);
    notifyContextEventImpl(p_object);
}

template<class T> void SDCProvider::updateMDIB(const T& p_object)
{
    //Changing the MDIB -> MDIB Version gets increased.
    incrementMDIBVersion();
    replaceState(p_object);
}

template<class T> void SDCProvider::notifyAlertEventImpl(const T& p_object)
{
    if(nullptr == m_adapter) // FIXME: Should not be necessary: Fix Provider thread handling on shutdown!
    {
        return;
    }

    if(p_object.getDescriptorHandle().empty())
    {
        log_error([] { return "State's descriptor handle is empty, event will not be fired!"; });
        return;
    }

    // TODO: replace sequence id
    MDM::EpisodicAlertReport t_report(xml_schema::Uri("0"));

    MDM::ReportPart3 t_reportPart;
    t_reportPart.getAlertState().push_back(ConvertToCDM::convert(p_object));
    t_report.getReportPart().push_back(t_reportPart);
    t_report.setMdibVersion(getMdibVersion());

    m_adapter->notifyEvent(t_report);
}

template<class T> void SDCProvider::notifyContextEventImpl(const T& p_object)
{
    if(nullptr == m_adapter) // FIXME: Should not be necessary: Fix Provider thread handling on shutdown!
    {
        return;
    }

    if(p_object.getDescriptorHandle().empty())
    {
        log_error([] { return "State's descriptor handle is empty, event will not be fired!"; });
        return;
    }

    MDM::ReportPart t_reportPart;
    t_reportPart.getContextState().push_back(ConvertToCDM::convert(p_object));

    MDM::EpisodicContextReport t_report(xml_schema::Uri("0"));
    t_report.getReportPart().push_back(t_reportPart);
    t_report.setMdibVersion(getMdibVersion());

    m_adapter->notifyEvent(t_report);
}

template<class T> void SDCProvider::notifyEpisodicMetricImpl(const T& p_object)
{
    if(nullptr == m_adapter) // FIXME: Should not be necessary: Fix Provider thread handling on shutdown!
    {
        return;
    }

    if(p_object.getDescriptorHandle().empty())
    {
        log_error([] { return "State's descriptor handle is empty, event will not be fired!"; });
        return;
    }

    MDM::ReportPart1 t_reportPart;
    t_reportPart.getMetricState().push_back(ConvertToCDM::convert(p_object));

    // TODO: replace sequence id
    MDM::EpisodicMetricReport t_report(xml_schema::Uri("0"));
    t_report.getReportPart().push_back(t_reportPart);
    t_report.setMdibVersion(getMdibVersion());

    m_adapter->notifyEvent(t_report);
}

template<class T> void SDCProvider::notifyEpisodicOperationalStateImpl(const T& p_object)
{
    if(nullptr == m_adapter) // FIXME: Should not be necessary: Fix Provider thread handling on shutdown!
    {
        return;
    }

    if(p_object.getDescriptorHandle().empty())
    {
        log_error([] { return "State's descriptor handle is empty, event will not be fired!"; });
        return;
    }

    MDM::ReportPart4 t_reportPart;
    t_reportPart.getOperationState().push_back(ConvertToCDM::convert(p_object));

    // TODO: replace sequence id
    MDM::EpisodicOperationalStateReport t_report(xml_schema::Uri("0"));
    t_report.getReportPart().push_back(t_reportPart);
    t_report.setMdibVersion(getMdibVersion());

    m_adapter->notifyEvent(t_report);
}

template<class T> void SDCProvider::notifyStreamMetricImpl(const T& p_object)
{
    if(nullptr == m_adapter) // FIXME: Should not be necessary: Fix Provider thread handling on shutdown!
    {
        return;
    }

    if(p_object.getDescriptorHandle().empty())
    {
        log_error([] { return "State's descriptor handle is empty, event will not be fired!"; });
        return;
    }

    // TODO: replace sequence id
    MDM::WaveformStream t_waveformStream(xml_schema::Uri("0"));

    t_waveformStream.getState().push_back(ConvertToCDM::convert(p_object));

    // FIXME: No dispatching here
    // -> Consumer will get no "Event" but the MDIB Version was changed. See updateState(...) above -> MISMATCH!
    m_adapter->notifyEvent(t_waveformStream);
}


void SDCProvider::firePeriodicReportImpl()
{
    if(nullptr == m_adapter) // FIXME: Should not be necessary: Fix Provider thread handling on shutdown!
    {
        return;
    }

    std::lock_guard<std::mutex> t_lock{m_mutex_PeriodicUpdateHandles};

    if(ml_handlesForPeriodicUpdates.empty())
    {
        //log_debug([] { return "List of handles is empty, event will not be fired!"; });
        return;
    }

    const auto t_mdstate(ConvertToCDM::convert(getMdState()));

    MDM::ReportPart3 t_periodicAlertReportPart;
    MDM::ReportPart t_periodicContextChangedReportPart;
    MDM::ReportPart1 t_periodicMetricReportPart;

    // FIXME: for-loop and dynamic_cast : Refactor (?)
    for(const auto& t_state : t_mdstate->getState())
    {
        if(std::find(ml_handlesForPeriodicUpdates.begin(), ml_handlesForPeriodicUpdates.end(), t_state.getDescriptorHandle())
           != ml_handlesForPeriodicUpdates.end())
        {
            if(auto t_castedState = dynamic_cast<const CDM::AbstractAlertState*>(&t_state))
            { // FIXME: std::addressof?
                t_periodicAlertReportPart.getAlertState().push_back(*t_castedState);
            }
            if(auto t_castedState = dynamic_cast<const CDM::AbstractContextState*>(&t_state))
            { // FIXME: std::addressof?
                t_periodicContextChangedReportPart.getContextState().push_back(*t_castedState);
            }
            if(auto t_castedState = dynamic_cast<const CDM::AbstractMetricState*>(&t_state))
            { // FIXME: std::addressof?
                t_periodicMetricReportPart.getMetricState().push_back(*t_castedState);
            }
        }
    }

    // TODO: replace sequence id s
    MDM::PeriodicAlertReport t_periodicAlertReport(xml_schema::Uri("0"));
    t_periodicAlertReport.setMdibVersion(getMdibVersion());
    t_periodicAlertReport.getReportPart().push_back(t_periodicAlertReportPart);
    m_adapter->notifyEvent(t_periodicAlertReport);

    MDM::PeriodicContextReport t_periodicContextReport(xml_schema::Uri("0"));
    t_periodicContextReport.setMdibVersion(getMdibVersion());
    t_periodicContextReport.getReportPart().push_back(t_periodicContextChangedReportPart);
    m_adapter->notifyEvent(t_periodicContextReport);

    MDM::PeriodicMetricReport t_periodicMetricReport(xml_schema::Uri("0"));
    t_periodicMetricReport.getReportPart().push_back(t_periodicMetricReportPart);
    m_adapter->notifyEvent(t_periodicMetricReport);
}

void SDCProvider::setAlertConditionPresence(const std::string& p_alertConditionHandle,
                                            bool p_conditionPresence,
                                            const OperationInvocationContext& p_oic)
{
    const MdState t_mdsc(getMdState());

    // Modify alert condition's presence
    AlertConditionState t_condState;
    LimitAlertConditionState t_limitCondState;
    if(t_mdsc.findState(p_alertConditionHandle, t_condState))
    {
        t_condState.setPresence(p_conditionPresence);
        const InvocationState is(onStateChangeRequest(t_condState, p_oic));
        if(is == InvocationState::Fin)
        {
            // Success
            updateState(t_condState);
        }
    }
    else if(t_mdsc.findState(p_alertConditionHandle, t_limitCondState))
    {
        t_limitCondState.setPresence(p_conditionPresence);
        const InvocationState t_is(onStateChangeRequest(t_limitCondState, p_oic));
        if(InvocationState::Fin == t_is)
        {
            // Success
            updateState(t_limitCondState);
        }
    }
    else
    {
        return;
    }

    // Search all alert signal descriptors with reference to the alert condition descriptor handle
    const std::vector<AlertSignalDescriptor> tl_asds(getMdDescription().collectAllAlertSignalDescriptors());
    std::map<std::string, AlertSignalDescriptor> tl_matchingDescriptors;

    for(const auto& t_descriptor : tl_asds)
    {
        if(t_descriptor.getConditionSignaled() == p_alertConditionHandle)
        {
            tl_matchingDescriptors.insert(std::map<std::string, AlertSignalDescriptor>::value_type(t_descriptor.getHandle(), t_descriptor));
        }
    }

    // Check and modify all found alert signal states, call into state handler, if needed
    auto informUser = [this, &p_oic](AlertSignalState& state, const AlertSignalPresence& presence) {
        state.setPresence(presence);
        const InvocationState is(onStateChangeRequest(state, p_oic));
        if(is == InvocationState::Fin)
        {
            updateState(state);
        }
    };

    // Search all alert signal states
    auto tl_ass(t_mdsc.findAlertSignalStates());
    for(auto& t_nextState : tl_ass)
    {
        auto descriptor = tl_matchingDescriptors.find(t_nextState.getDescriptorHandle());
        if(descriptor == tl_matchingDescriptors.end())
        {
            continue;
        }

        if(p_conditionPresence)
        {
            informUser(t_nextState, AlertSignalPresence::On);
        }
        else
        {
            if(!t_nextState.hasPresence())
            {
                informUser(t_nextState, AlertSignalPresence::Off);
            }
            if(descriptor->second.getLatching())
            {
                switch(t_nextState.getPresence())
                {
                case AlertSignalPresence::On: informUser(t_nextState, AlertSignalPresence::Latch); break;
                case AlertSignalPresence::Off: break;
                case AlertSignalPresence::Ack: break;
                case AlertSignalPresence::Latch: break;
                }
            }
            else
            {
                informUser(t_nextState, AlertSignalPresence::Off);
            }
        }
    }
}

void SDCProvider::evaluateAlertConditions(const std::string& p_source) const
{
    const MdDescription t_description(getMdDescription());

    std::vector<std::string> tl_relevantDescriptors;
    for(const auto& t_alertCondition : t_description.collectAllAlertConditionDescriptors())
    {
        const auto tl_sources(t_alertCondition.getSourceList());
        if(std::find(tl_sources.begin(), tl_sources.end(), p_source) != tl_sources.end())
        {
            tl_relevantDescriptors.push_back(t_alertCondition.getHandle());
        }
    }
    for(const auto& t_limitAlertCondition : t_description.collectAllLimitAlertConditionDescriptors())
    {
        const auto tl_sources(t_limitAlertCondition.getSourceList());
        if(std::find(tl_sources.begin(), tl_sources.end(), p_source) != tl_sources.end())
        {
            tl_relevantDescriptors.push_back(t_limitAlertCondition.getHandle());
        }
    }

    if(tl_relevantDescriptors.empty())
    {
        return;
    }

    using AlertCondition_ptr = SDCProviderAlertConditionStateHandler<AlertConditionState>*;
    std::vector<AlertCondition_ptr> tl_states;
    { // LOCK
        std::lock_guard<std::mutex> t_lock{m_mutex_MdStateHandler};
        for(const auto& t_handler : ml_stateHandlers)
        {
            if(auto t_handler_AlertConditionState = dynamic_cast<SDCProviderAlertConditionStateHandler<AlertConditionState>*>(
                   t_handler.second))
            {
                if(std::find(tl_relevantDescriptors.begin(),
                             tl_relevantDescriptors.end(),
                             t_handler_AlertConditionState->getDescriptorHandle())
                   != tl_relevantDescriptors.end())
                {
                    tl_states.push_back(static_cast<AlertCondition_ptr>(t_handler.second));
                }
            }
            else if(auto t_handler_LimitAlertConditionState = dynamic_cast<SDCProviderAlertConditionStateHandler<LimitAlertConditionState>*>(
                        t_handler.second))
            {
                if(std::find(tl_relevantDescriptors.begin(),
                             tl_relevantDescriptors.end(),
                             t_handler_LimitAlertConditionState->getDescriptorHandle())
                   != tl_relevantDescriptors.end())
                {
                    tl_states.push_back(static_cast<AlertCondition_ptr>(t_handler.second));
                }
            }
        }
    } // UNLOCK

    // Update
    for(const auto& t_handler : tl_states)
    {
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
        for(const auto& t_handler : ml_stateHandlers)
        {
            if(auto t_handler_AlertConditionState = dynamic_cast<SDCProviderAlertConditionStateHandler<AlertConditionState>*>(
                   t_handler.second))
            {
                if(t_handler_AlertConditionState->getDescriptorHandle() == p_alertConditionDescriptor)
                {
                    tl_states.push_back(static_cast<AlertCondition_ptr>(t_handler.second));
                }
            }
            else if(auto t_handler_LimitAlertConditionState = dynamic_cast<SDCProviderAlertConditionStateHandler<LimitAlertConditionState>*>(
                        t_handler.second))
            {
                if(t_handler_LimitAlertConditionState->getDescriptorHandle() == p_alertConditionDescriptor)
                {
                    tl_states.push_back(static_cast<AlertCondition_ptr>(t_handler.second));
                }
            }
        }
    } // UNLOCK

    // Update
    for(const auto& t_state : tl_states)
    {
        t_state->alertConditionHasChanged();
    }
}

MdibContainer SDCProvider::getMdib() const
{
    MdibContainer t_container;
    t_container.setMdDescription(getMdDescription());
    t_container.setMdState(getMdState());
    t_container.setMdibVersion(getMdibVersion());
    return t_container;
}

MdState SDCProvider::getMdState() const
{
    std::lock_guard<std::mutex> t_lock{m_mutex_MdState};
    return m_MdState;
}


bool SDCProvider::startup()
{
    if(isStarted())
    {
        log_error([] { return "Provider already started!"; });
        return false;
    }

    std::lock_guard<std::mutex> t_lock{m_mutex};
    try
    {
        m_adapter->start();
    }
    catch(std::runtime_error& ex_re)
    {
        log_error([&] { return ex_re.what(); });
        return false;
    }
    catch(...)
    {
        throw;
    }

    // Grab all states (start with all operation states and add states from user handlers)
    { // LOCK MdState(/Handler)
        std::lock_guard<std::mutex> t_lockMdStates{m_mutex_MdState};
        std::lock_guard<std::mutex> t_lockMdStateHandler{m_mutex_MdStateHandler};
        m_MdState = MdState(m_operationStates);
        for(const auto& t_handler : ml_stateHandlers)
        {
            if(auto t_casted_AlertConditionState = dynamic_cast<SDCProviderAlertConditionStateHandler<AlertConditionState>*>(
                   t_handler.second))
            {
                auto t_state = t_casted_AlertConditionState->getInitialState();
                _initAbstractStateDefaults(t_state);
                m_MdState.addState(t_state);
            }
            else if(auto t_casted_AlertSignalState = dynamic_cast<SDCProviderMDStateHandler<AlertSignalState>*>(t_handler.second))
            {
                auto t_state = t_casted_AlertSignalState->getInitialState();
                _initAbstractStateDefaults(t_state);
                m_MdState.addState(t_state);
            }
            else if(auto t_casted_EnumStringMetricState = dynamic_cast<SDCProviderMDStateHandler<EnumStringMetricState>*>(t_handler.second))
            {
                auto t_state = t_casted_EnumStringMetricState->getInitialState();
                _initAbstractStateDefaults(t_state);
                _initStateMetricValueDefaults(t_state);
                m_MdState.addState(t_state);
            }
            else if(auto t_casted_AlertSystemState = dynamic_cast<SDCProviderMDStateHandler<AlertSystemState>*>(t_handler.second))
            {
                auto t_state = t_casted_AlertSystemState->getInitialState();
                _initAbstractStateDefaults(t_state);
                m_MdState.addState(t_state);
            }
            else if(auto t_casted_LimitAlertConditionState = dynamic_cast<SDCProviderAlertConditionStateHandler<LimitAlertConditionState>*>(
                        t_handler.second))
            {
                auto t_state = t_casted_LimitAlertConditionState->getInitialState();
                _initAbstractStateDefaults(t_state);
                m_MdState.addState(t_state);
            }
            else if(auto t_casted_NumericMetricState = dynamic_cast<SDCProviderMDStateHandler<NumericMetricState>*>(t_handler.second))
            {
                auto t_state = t_casted_NumericMetricState->getInitialState();
                _initAbstractStateDefaults(t_state);
                _initComponentStateDefaults(t_state);
                _initStateMetricValueDefaults(t_state);
                m_MdState.addState(t_state);
            }
            else if(auto t_casted_RealTimeSampleArrayMetricState = dynamic_cast<SDCProviderMDStateHandler<RealTimeSampleArrayMetricState>*>(
                        t_handler.second))
            {
                auto t_state = t_casted_RealTimeSampleArrayMetricState->getInitialState();
                _initAbstractStateDefaults(t_state);
                _initStateMetricValueDefaults(t_state);
                m_MdState.addState(t_state);
            }
            else if(auto t_casted_DistributionSampleArrayMetricState = dynamic_cast<
                        SDCProviderMDStateHandler<DistributionSampleArrayMetricState>*>(t_handler.second))
            {
                auto t_state = t_casted_DistributionSampleArrayMetricState->getInitialState();
                _initAbstractStateDefaults(t_state);
                _initStateMetricValueDefaults(t_state);
                m_MdState.addState(t_state);
            }
            else if(auto t_casted_StringMetricState = dynamic_cast<SDCProviderMDStateHandler<StringMetricState>*>(t_handler.second))
            {
                auto t_state = t_casted_StringMetricState->getInitialState();
                _initAbstractStateDefaults(t_state);
                _initComponentStateDefaults(t_state);
                _initStateMetricValueDefaults(t_state);
                m_MdState.addState(t_state);
            }
            else if(auto t_casted_ClockState = dynamic_cast<SDCProviderComponentStateHandler<ClockState>*>(t_handler.second))
            {
                auto t_state = t_casted_ClockState->getInitialState();
                _initAbstractStateDefaults(t_state);
                _initComponentStateDefaults(t_state);
                m_MdState.addState(t_state);
            }
            else if(auto t_casted_MdsState = dynamic_cast<SDCProviderComponentStateHandler<MdsState>*>(t_handler.second))
            {
                auto t_state = t_casted_MdsState->getInitialState();
                _initAbstractStateDefaults(t_state);
                _initComponentStateDefaults(t_state);
                m_MdState.addState(t_state);
            }
            else if(auto t_casted_VmdState = dynamic_cast<SDCProviderComponentStateHandler<VmdState>*>(t_handler.second))
            {
                auto t_state = t_casted_VmdState->getInitialState();
                _initAbstractStateDefaults(t_state);
                _initComponentStateDefaults(t_state);
                m_MdState.addState(t_state);
            }
            else if(auto t_casted_ChannelState = dynamic_cast<SDCProviderComponentStateHandler<ChannelState>*>(t_handler.second))
            {
                auto t_state = t_casted_ChannelState->getInitialState();
                _initAbstractStateDefaults(t_state);
                _initComponentStateDefaults(t_state);
                m_MdState.addState(t_state);
            }
            else if(dynamic_cast<SDCProviderActivateOperationHandler*>(t_handler.second))
            {
                // NOOP
                // well I gess not... // TODO
            }
            else if(auto t_casted_SystemContextState = dynamic_cast<SDCProviderMDStateHandler<SystemContextState>*>(t_handler.second))
            {
                auto t_state = t_casted_SystemContextState->getInitialState();
                _initAbstractStateDefaults(t_state);
                m_MdState.addState(t_state);
            }
            else if(auto t_casted_LocationContextState = dynamic_cast<SDCProviderMDStateHandler<LocationContextState>*>(t_handler.second))
            {
                auto t_state = t_casted_LocationContextState->getInitialState();
                _initAbstractStateDefaults(t_state);
                m_MdState.addState(t_state);
            }
            else if(auto t_casted_PatientContextState = dynamic_cast<SDCProviderMDStateHandler<PatientContextState>*>(t_handler.second))
            {
                auto t_state = t_casted_PatientContextState->getInitialState();
                _initAbstractStateDefaults(t_state);
                m_MdState.addState(t_state);
            }
            else if(auto t_casted_MeansContextState = dynamic_cast<SDCProviderMDStateHandler<MeansContextState>*>(t_handler.second))
            {
                auto t_state = t_casted_MeansContextState->getInitialState();
                _initAbstractStateDefaults(t_state);
                m_MdState.addState(t_state);
            }
            else if(auto t_casted_WorkflowContextState = dynamic_cast<SDCProviderMDStateHandler<WorkflowContextState>*>(t_handler.second))
            {
                auto t_state = t_casted_WorkflowContextState->getInitialState();
                _initAbstractStateDefaults(t_state);
                m_MdState.addState(t_state);
            }
            else if(auto t_casted_OperatorContextState = dynamic_cast<SDCProviderMDStateHandler<OperatorContextState>*>(t_handler.second))
            {
                auto t_state = t_casted_OperatorContextState->getInitialState();
                _initAbstractStateDefaults(t_state);
                m_MdState.addState(t_state);
            }
            else if(auto t_casted_EnsembleContextState = dynamic_cast<SDCProviderMDStateHandler<EnsembleContextState>*>(t_handler.second))
            {
                auto t_state = t_casted_EnsembleContextState->getInitialState();
                _initAbstractStateDefaults(t_state);
                m_MdState.addState(t_state);
            }
            else
            {
                log_fatal([] { return "Unknown handler type! This is an implementation error in the SDCLib!"; });
                return false;
            }
        }
    } // UNLOCK

    // Iterate over MdDescription and Add States for all Descriptors not added yet -> TODO REWORK!
    auto t_description = getMdDescription();

    { // LOCK
        std::lock_guard<std::mutex> t_lockMdState{m_mutex_MdState};

        // Mds
        for(const auto& t_Mds : t_description.getMdsList())
        {
            // Not added yet - Add
            if(!m_MdState.findState<MdsState>(t_Mds.getHandle()))
            {
                auto t_state = MdsState(t_Mds.getHandle());
                _initAbstractStateDefaults(t_state);
                _initComponentStateDefaults(t_state);
                m_MdState.addState(t_state);
            }
            // Sco Mds
            if(t_Mds.hasSco())
            {
                if(!m_MdState.findState<ScoState>(t_Mds.getSco().getHandle()))
                {
                    auto t_scoState = ScoState(t_Mds.getSco().getHandle());
                    _initAbstractStateDefaults(t_scoState);
                    m_MdState.addState(t_scoState);
                    for(const auto& t_activateOperation : t_Mds.getSco().collectAllActivateOperationDescriptors())
                    {
                        if(!m_MdState.findState<ActivateOperationState>(t_activateOperation.getHandle()))
                        {
                            auto t_state = ActivateOperationState(t_activateOperation.getHandle(), OperatingMode::NA);
                            _initAbstractStateDefaults(t_state);
                            m_MdState.addState(t_state);
                        }
                    }
                    for(const auto& t_setAlertStateOperation : t_Mds.getSco().collectAllSetAlertStateOperationDescriptors())
                    {
                        if(!m_MdState.findState<SetAlertStateOperationState>(t_setAlertStateOperation.getHandle()))
                        {
                            auto t_state = SetAlertStateOperationState(t_setAlertStateOperation.getHandle(), OperatingMode::NA);
                            _initAbstractStateDefaults(t_state);
                            m_MdState.addState(t_state);
                        }
                    }
                    for(const auto& t_setContextOperation : t_Mds.getSco().collectAllSetContextOperationDescriptors())
                    {
                        if(!m_MdState.findState<SetContextStateOperationState>(t_setContextOperation.getHandle()))
                        {
                            auto t_state = SetContextStateOperationState(t_setContextOperation.getHandle(), OperatingMode::NA);
                            _initAbstractStateDefaults(t_state);
                            m_MdState.addState(t_state);
                        }
                    }
                    for(const auto& t_setStringOperation : t_Mds.getSco().collectAllSetStringOperationDescriptors())
                    {
                        if(!m_MdState.findState<SetStringOperationState>(t_setStringOperation.getHandle()))
                        {
                            auto t_state = SetStringOperationState(t_setStringOperation.getHandle(), OperatingMode::NA);
                            _initAbstractStateDefaults(t_state);
                            m_MdState.addState(t_state);
                        }
                    }
                    for(const auto& t_setValueOperation : t_Mds.getSco().collectAllSetValueOperationDescriptors())
                    {
                        if(!m_MdState.findState<SetValueOperationState>(t_setValueOperation.getHandle()))
                        {
                            auto t_state = SetValueOperationState(t_setValueOperation.getHandle(), OperatingMode::NA);
                            _initAbstractStateDefaults(t_state);
                            m_MdState.addState(t_state);
                        }
                    }
                }
            }

            // SystemContext ?
            if(t_Mds.hasSystemContext())
            {
                if(!m_MdState.findState<SystemContextState>(t_Mds.getSystemContext().getHandle()))
                {
                    auto t_state = SystemContextState(t_Mds.getSystemContext().getHandle());
                    _initAbstractStateDefaults(t_state);
                    _initComponentStateDefaults(t_state);
                    m_MdState.addState(t_state);
                }
            }

            // Vmd
            for(const auto& t_vmd : t_Mds.getVmdList())
            {
                // Not added yet - Add
                if(!m_MdState.findState<VmdState>(t_vmd.getHandle()))
                {
                    auto t_state = VmdState(t_vmd.getHandle());
                    _initAbstractStateDefaults(t_state);
                    _initComponentStateDefaults(t_state);
                    m_MdState.addState(t_state);
                }

                // Sco Vmd
                if(t_vmd.hasSco())
                {
                    if(!m_MdState.findState<ScoState>(t_vmd.getSco().getHandle()))
                    {
                        auto t_scoState = ScoState(t_vmd.getSco().getHandle());
                        _initAbstractStateDefaults(t_scoState);
                        m_MdState.addState(t_scoState);
                        for(const auto& t_activateOperation : t_vmd.getSco().collectAllActivateOperationDescriptors())
                        {
                            if(!m_MdState.findState<ActivateOperationState>(t_activateOperation.getHandle()))
                            {
                                auto t_state = ActivateOperationState(t_activateOperation.getHandle(), OperatingMode::NA);
                                _initAbstractStateDefaults(t_state);
                                m_MdState.addState(t_state);
                            }
                        }
                        for(const auto& t_setAlertStateOperation : t_vmd.getSco().collectAllSetAlertStateOperationDescriptors())
                        {
                            if(!m_MdState.findState<SetAlertStateOperationState>(t_setAlertStateOperation.getHandle()))
                            {
                                auto t_state = SetAlertStateOperationState(t_setAlertStateOperation.getHandle(), OperatingMode::NA);
                                _initAbstractStateDefaults(t_state);
                                m_MdState.addState(t_state);
                            }
                        }
                        for(const auto& t_setContextOperation : t_vmd.getSco().collectAllSetContextOperationDescriptors())
                        {
                            if(!m_MdState.findState<SetContextStateOperationState>(t_setContextOperation.getHandle()))
                            {
                                auto t_state = SetContextStateOperationState(t_setContextOperation.getHandle(), OperatingMode::NA);
                                _initAbstractStateDefaults(t_state);
                                m_MdState.addState(t_state);
                            }
                        }
                        for(const auto& t_setStringOperation : t_vmd.getSco().collectAllSetStringOperationDescriptors())
                        {
                            if(!m_MdState.findState<SetStringOperationState>(t_setStringOperation.getHandle()))
                            {
                                auto t_state = SetStringOperationState(t_setStringOperation.getHandle(), OperatingMode::NA);
                                _initAbstractStateDefaults(t_state);
                                m_MdState.addState(t_state);
                            }
                        }
                        for(const auto& t_setValueOperation : t_vmd.getSco().collectAllSetValueOperationDescriptors())
                        {
                            if(!m_MdState.findState<SetValueOperationState>(t_setValueOperation.getHandle()))
                            {
                                auto t_state = SetValueOperationState(t_setValueOperation.getHandle(), OperatingMode::NA);
                                _initAbstractStateDefaults(t_state);
                                m_MdState.addState(t_state);
                            }
                        }
                    }
                }


                // Channel
                for(const auto& t_channel : t_vmd.getChannelList())
                {
                    if(!m_MdState.findState<ChannelState>(t_channel.getHandle()))
                    {
                        auto t_state = ChannelState(t_channel.getHandle());
                        _initAbstractStateDefaults(t_state);
                        _initComponentStateDefaults(t_state);
                        m_MdState.addState(t_state);
                    }

                    // Activate

                    // Numeric Metrics
                    for(const auto& t_metric : t_channel.getNumericMetricDescriptorList())
                    {
                        if(!m_MdState.findState<NumericMetricState>(t_metric.getHandle()))
                        {
                            auto t_state = NumericMetricState(t_metric.getHandle());
                            _initAbstractStateDefaults(t_state);
                            _initStateMetricValueDefaults(t_state);
                            m_MdState.addState(t_state);
                        }
                    }
                    // String Metrics
                    for(const auto& t_metric : t_channel.getStringMetricDescriptorList())
                    {
                        if(!m_MdState.findState<StringMetricState>(t_metric.getHandle())
                           && !m_MdState.findState<EnumStringMetricState>(t_metric.getHandle()))
                        {
                            auto t_state = StringMetricState(t_metric.getHandle());
                            _initAbstractStateDefaults(t_state);
                            _initStateMetricValueDefaults(t_state);
                            m_MdState.addState(t_state);
                        }
                    }
                    // Enum String Metrics
                    for(const auto& t_metric : t_channel.getEnumStringMetricDescriptorList())
                    {
                        if(!m_MdState.findState<EnumStringMetricState>(t_metric.getHandle())
                           && !m_MdState.findState<StringMetricState>(t_metric.getHandle()))
                        {
                            auto t_state = EnumStringMetricState(t_metric.getHandle());
                            _initAbstractStateDefaults(t_state);
                            _initStateMetricValueDefaults(t_state);
                            m_MdState.addState(t_state);
                        }
                    }

                    // TODO: More MetricStates...
                }
            }
        }
    } // UNLOCK


    // Validation
    {
        // FIXME: "dont_validate" Flag?
        const xml_schema::Flags t_xercesFlags(xml_schema::Flags::dont_validate | xml_schema::Flags::no_xml_declaration
                                              | xml_schema::Flags::dont_initialize);
        std::ostringstream t_xml;
        xml_schema::NamespaceInfomap tl_map;
        CDM::serializeMdibContainer(t_xml, *ConvertToCDM::convert(getMdib()), tl_map, OSELib::XML_ENCODING, t_xercesFlags);

        OSELib::SDC::DefaultSDCSchemaGrammarProvider t_grammarProvider;
        auto t_rawMessage = OSELib::Helper::Message::create(t_xml.str());
        auto t_xercesDocument = OSELib::Helper::XercesDocumentWrapper::create(*t_rawMessage, t_grammarProvider);
        if(nullptr == t_xercesDocument)
        {
            log_fatal([&] { return "Fatal error, can't create MDIB - schema validation error! Offending MDIB: \n" + t_xml.str(); });
            return false;
        }
        auto t_result(CDM::parseMdibContainer(t_xercesDocument->getDocument()));
        if(nullptr == t_result)
        {
            log_fatal([&] { return "Fatal error, can't create MDIB - schema validation error! Offending MDIB: \n" + t_xml.str(); });
            return false;
        }
    }

    // Start AsyncProviderInvoker
    startAsyncProviderInvoker();

    // Set the flag
    m_started = true;
    return true;
}

void SDCProvider::shutdown()
{
    log_information([] {
        return "######### SDCProvider::shutdown is deprecated and will be removed in future versions! SDCProvider Destructor handles this functionality now.";
    });
}

template<class T> void SDCProvider::replaceState(T p_object) // FIXME: return value (bool)?
{
    { // LOCK
        std::lock_guard<std::mutex> t_lock{m_mutex_MdState};
        // Check for existing state
        std::unique_ptr<CDM::MdState> t_cachedStates(ConvertToCDM::convert(m_MdState));
        CDM::MdState t_target;
        for(const auto& t_state : t_cachedStates->getState())
        {
            if(t_state.getDescriptorHandle() == p_object.getDescriptorHandle())
            {
                // Increment StateVersion
                if(!p_object.hasStateVersion())
                { // No state version -> Set the initial one + 1
                    p_object.setStateVersion(VersionCounter(INITIAL_STATE_VERSION + 1));
                }
                else
                { // Increment
                    p_object.setStateVersion(p_object.getStateVersion() + 1);
                }
                // Found, add parameter instead of current
                t_target.getState().push_back(*ConvertToCDM::convert(p_object));

                continue;
            }
            // Copy
            t_target.getState().push_back(t_state);
        }
        m_MdState = ConvertFromCDM::convert(t_target);
    } // UNLOCK

    // Increment StateVersion
    _incrementMdStateVersion();
}


void SDCProvider::addMdStateHandler(SDCProviderStateHandler* p_handler) // FIXME: return value (bool)?
{
    assert(p_handler != nullptr);

    // Safety check
    if(p_handler == nullptr)
    {
        return;
    }

    std::lock_guard<std::mutex> t_lock{m_mutex_MdStateHandler};

    p_handler->parentProvider = this;

    // TODO: Multistates implementation.. regarding to the SDC standard it should be possible to define states with the same descriptor handle!
    // this is only possible for context states. maybe do a type check.
    // but before implementing -> check the whole frameworks mechanics
    if(ml_stateHandlers.find(p_handler->getDescriptorHandle()) != ml_stateHandlers.end())
    {
        log_error([&] {
            return "A SDCProvider handler for handle " + p_handler->getDescriptorHandle() + " already exists. It will be overridden.";
        });
    }

    // ToDo: Behold! check with simpleSDC if this really works°! TODO
    if(auto t_activate_handler = dynamic_cast<SDCProviderActivateOperationHandler*>(p_handler))
    {
        const MdDescription t_mddescription(getMdDescription());

        for(const auto& t_mds : t_mddescription.collectAllMdsDescriptors())
        {
            if(!t_mds.hasSco())
            {
                continue;
            }

            const auto t_sco(ConvertToCDM::convert(t_mds.getSco()));
            for(const auto& t_operation : t_sco->getOperation())
            {
                if(t_operation.getHandle() == t_activate_handler->getDescriptorHandle()
                   && nullptr != dynamic_cast<const CDM::ActivateOperationDescriptor*>(&t_operation))
                { // FIXME: std::addressof?
                    ml_stateHandlers[p_handler->getDescriptorHandle()] = p_handler;
                    return;
                }
            }
            for(const auto& t_vdm : t_mds.getVmdList())
            {
                if(!t_vdm.hasSco())
                {
                    continue;
                }
                const auto t_scoVdm(ConvertToCDM::convert(t_vdm.getSco()));
                for(const auto& t_operationVdm : t_scoVdm->getOperation())
                {
                    if(t_operationVdm.getHandle() == t_activate_handler->getDescriptorHandle()
                       && nullptr != dynamic_cast<const CDM::ActivateOperationDescriptor*>(&t_operationVdm))
                    { // FIXME: std::addressof?
                        ml_stateHandlers[p_handler->getDescriptorHandle()] = p_handler;
                        return;
                    }
                }
            }
        }
        log_error([] { return "Could not add handler because no ActivateOperationDescriptor with matching handle was found."; });
    }
    // TODO: Move streaming service to service controller
    // add DistributionArray...
    else if(/*auto streamHandler = */ dynamic_cast<SDCProviderMDStateHandler<RealTimeSampleArrayMetricState>*>(p_handler))
    {
        //int port = SDCLibrary::getInstance().extractFreePort();
        //m_adapter->addStreamingPort(4444);
        // FIXME: delete after testing that streaming works on more than one address!
        // FIXME: MAGIC NUMBERS...!!!!
        //m_adapter->addStreamingPort(OSELib::SDC::MDPWS_MCAST_PORT);
        ml_stateHandlers[p_handler->getDescriptorHandle()] = p_handler;
    }
    else
    {
        ml_stateHandlers[p_handler->getDescriptorHandle()] = p_handler;
    }
}


void SDCProvider::removeMDStateHandler(SDCProviderStateHandler* p_handler)
{
    assert(p_handler != nullptr);
    std::lock_guard<std::mutex> t_lock{m_mutex_MdStateHandler};
    ml_stateHandlers.erase(p_handler->getDescriptorHandle());
}


bool SDCProvider::setMdDescription(const MdDescription& p_MdDescription)
{
    std::lock_guard<std::mutex> t_lock{m_mutex_MdDescription};
    m_MdDescription = std::unique_ptr<MdDescription>(new MdDescription(p_MdDescription));
    return true; // Interface consistency with std::string (parsing) version
}

bool SDCProvider::setMdDescription(std::string p_xml)
{
    if(p_xml.empty())
    {
        return false;
    }

    std::lock_guard<std::mutex> t_lock{m_mutex_MdDescription};
    OSELib::SDC::DefaultSDCSchemaGrammarProvider t_grammarProvider;
    auto t_rawMessage = OSELib::Helper::Message::create(p_xml);
    auto t_xercesDocument = OSELib::Helper::XercesDocumentWrapper::create(*t_rawMessage, t_grammarProvider);

    auto t_result(CDM::parseMdibContainer(t_xercesDocument->getDocument()));

    if((nullptr != t_result) && (t_result->getMdDescription().present()))
    {
        std::unique_ptr<MdDescription> t_MdDescription(new MdDescription(ConvertFromCDM::convert(t_result->getMdDescription().get())));
        if(nullptr == t_MdDescription)
        {
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


void SDCProvider::setEndpointReference(const std::string& p_epr) // FIXME: return value (bool)?
{
    if(p_epr.empty())
    {
        return;
    }
    // Set EPR
    std::lock_guard<std::mutex> t_lock{m_mutex_EPR};
    m_endpointReference = p_epr;
}
void SDCProvider::setEndpointReferenceByName(const std::string& p_name) // FIXME: return value (bool)?
{
    if(p_name.empty())
    {
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

template<typename T> InvocationState SDCProvider::onStateChangeRequest(const T& p_state, const OperationInvocationContext& p_oic)
{
    // Try to find the StateHandler
    std::map<std::string, SDCProviderStateHandler*>::const_iterator t_iter = ml_stateHandlers.end();
    { // LOCK
        std::lock_guard<std::mutex> t_lock{m_mutex_MdStateHandler};
        t_iter = ml_stateHandlers.find(p_state.getDescriptorHandle());
        if(t_iter == ml_stateHandlers.end())
        {
            return InvocationState::Fail;
        }
    } // UNLOCK

    // Send the StateChangeRequest
    if(auto t_handler = dynamic_cast<SDCProviderMDStateHandler<T>*>(t_iter->second))
    {
        return t_handler->onStateChangeRequest(p_state, p_oic);
    }
    return InvocationState::Fail;
}

void SDCProvider::notifyOperationInvoked(const OperationInvocationContext& p_oic, Data::SDC::InvocationState p_is)
{
    if(nullptr == m_adapter) // FIXME: Should not be necessary: Fix Provider thread handling on shutdown!
    {
        return;
    }

    if(p_oic.transactionId == 0 && p_oic.operationHandle.empty())
    {
        return;
    }

    // todo: replace IstanceIdentifier by real value
    MDM::ReportPart5 t_oirPart(MDM::InvocationInfo(p_oic.transactionId, ConvertToCDM::convert(p_is)),
                               CDM::InstanceIdentifier(),
                               p_oic.operationHandle);
    // todo: replace sequence id
    MDM::OperationInvokedReport t_oir(xml_schema::Uri("0"));
    t_oir.setMdibVersion(getMdibVersion());
    t_oir.getReportPart().push_back(t_oirPart);

    m_adapter->notifyEvent(t_oir);
}

template<class T> bool SDCProvider::addSetOperationToSCOObjectImpl(const T& p_source, MdsDescriptor& p_ownerMDS)
{
    // get sco object or create new
    std::unique_ptr<CDM::ScoDescriptor> t_scoDescriptor(Defaults::ScoDescriptorInit(xml_schema::Uri("")));
    if(p_ownerMDS.hasSco())
    {
        t_scoDescriptor = ConvertToCDM::convert(p_ownerMDS.getSco());
    }
    else
    {
        // only set handle if previously created
        t_scoDescriptor->setHandle(p_ownerMDS.getHandle() + "_sco");
    }

    // add operation descriptor to sco and write back to mds
    t_scoDescriptor->getOperation().push_back(p_source);
    p_ownerMDS.setSco(ConvertFromCDM::convert(*t_scoDescriptor));


    // Search if already exists - 2 Matching criteria: HandleName and Type
    auto tl_cachedOperationStates(ConvertToCDM::convert(m_operationStates));
    for(const auto& t_state : tl_cachedOperationStates->getState())
    {
        if(t_state.getDescriptorHandle() == p_source.getHandle())
        {
            if(dynamic_cast<const CDM::AbstractOperationState*>(std::addressof(t_state)))
            {
                return false;
            }
        }
    }

    // Now add a state object for the sco descriptor to the cached states.
    // Add new operation state and Emit OperationalState event
    if(dynamic_cast<const CDM::SetValueOperationDescriptor*>(std::addressof(p_source)))
    {
        auto t_operationState = CDM::SetValueOperationState(p_source.getHandle(), CDM::OperatingMode::En);
        tl_cachedOperationStates->getState().push_back(t_operationState);
        notifyEpisodicOperationalStateImpl(SetValueOperationState(t_operationState)); // Emit an event!
    }
    else if(dynamic_cast<const CDM::SetStringOperationDescriptor*>(std::addressof(p_source)))
    {
        auto t_operationState = CDM::SetStringOperationState(p_source.getHandle(), CDM::OperatingMode::En);
        tl_cachedOperationStates->getState().push_back(t_operationState);
        notifyEpisodicOperationalStateImpl(SetStringOperationState(t_operationState)); // Emit an event!
    }
    else if(dynamic_cast<const CDM::SetAlertStateOperationDescriptor*>(std::addressof(p_source)))
    {
        auto t_operationState = CDM::SetAlertStateOperationState(p_source.getHandle(), CDM::OperatingMode::En);
        tl_cachedOperationStates->getState().push_back(t_operationState);
        notifyEpisodicOperationalStateImpl(SetAlertStateOperationState(t_operationState)); // Emit an event!
    }
    else if(dynamic_cast<const CDM::SetComponentStateOperationDescriptor*>(std::addressof(p_source)))
    {
        auto t_operationState = CDM::SetComponentStateOperationState(p_source.getHandle(), CDM::OperatingMode::En);
        tl_cachedOperationStates->getState().push_back(t_operationState);
        notifyEpisodicOperationalStateImpl(SetComponentStateOperationState(t_operationState)); // Emit an event!
    }
    else if(dynamic_cast<const CDM::SetContextStateOperationDescriptor*>(std::addressof(p_source)))
    {
        auto t_operationState = CDM::SetContextStateOperationState(p_source.getHandle(), CDM::OperatingMode::En);
        tl_cachedOperationStates->getState().push_back(t_operationState);
        notifyEpisodicOperationalStateImpl(SetContextStateOperationState(t_operationState)); // Emit an event!
    }
    else if(dynamic_cast<const CDM::SetMetricStateOperationDescriptor*>(std::addressof(p_source)))
    {
        auto t_operationState = CDM::SetMetricStateOperationState(p_source.getHandle(), CDM::OperatingMode::En);
        tl_cachedOperationStates->getState().push_back(t_operationState);
        notifyEpisodicOperationalStateImpl(SetMetricStateOperationState(t_operationState)); // Emit an event!
    }
    else if(dynamic_cast<const CDM::ActivateOperationDescriptor*>(std::addressof(p_source)))
    {
        auto t_operationState = CDM::ActivateOperationState(p_source.getHandle(), CDM::OperatingMode::En);
        tl_cachedOperationStates->getState().push_back(t_operationState);
        notifyEpisodicOperationalStateImpl(ActivateOperationState(t_operationState)); // Emit an event!
    }
    else
    {
        log_error([] { return "SDCProvider::addSetOperationToSCOObjectImpl: dynamic_cast found no match for source!"; });
        return false;
    }
    // replace cached states by update.
    m_operationStates = ConvertFromCDM::convert(*tl_cachedOperationStates);
    return true;
}

void SDCProvider::addActivateOperationForDescriptor(const ActivateOperationDescriptor& p_descriptor, MdsDescriptor& p_ownerMDS)
{
    addSetOperationToSCOObjectImpl(*ConvertToCDM::convert(p_descriptor), p_ownerMDS);
}

void SDCProvider::createSetOperationForDescriptor(const AlertConditionDescriptor& p_descriptor, MdsDescriptor& p_ownerMDS)
{
    const CDM::SetAlertStateOperationDescriptor t_setOperation(p_descriptor.getHandle() + "_sco", p_descriptor.getHandle());
    addSetOperationToSCOObjectImpl(t_setOperation, p_ownerMDS);
}

void SDCProvider::createSetOperationForDescriptor(const AlertSignalDescriptor& p_descriptor, MdsDescriptor& p_ownerMDS)
{
    const CDM::SetAlertStateOperationDescriptor t_setOperation(p_descriptor.getHandle() + "_sco", p_descriptor.getHandle());
    addSetOperationToSCOObjectImpl(t_setOperation, p_ownerMDS);
}

void SDCProvider::createSetOperationForDescriptor(const AlertSystemDescriptor& p_descriptor, MdsDescriptor& p_ownerMDS)
{
    const CDM::SetAlertStateOperationDescriptor t_setOperation(p_descriptor.getHandle() + "_sco", p_descriptor.getHandle());
    addSetOperationToSCOObjectImpl(t_setOperation, p_ownerMDS);
}

void SDCProvider::createSetOperationForDescriptor(const EnumStringMetricDescriptor& p_descriptor, MdsDescriptor& p_ownerMDS)
{
    const CDM::SetStringOperationDescriptor t_setOperation(p_descriptor.getHandle() + "_sco", p_descriptor.getHandle());
    addSetOperationToSCOObjectImpl(t_setOperation, p_ownerMDS);
}

void SDCProvider::createSetOperationForDescriptor(const LimitAlertConditionDescriptor& p_descriptor, MdsDescriptor& p_ownerMDS)
{
    const CDM::SetAlertStateOperationDescriptor t_setOperation(p_descriptor.getHandle() + "_sco", p_descriptor.getHandle());
    addSetOperationToSCOObjectImpl(t_setOperation, p_ownerMDS);
}

void SDCProvider::createSetOperationForDescriptor(const NumericMetricDescriptor& p_descriptor, MdsDescriptor& p_ownerMDS)
{
    const CDM::SetValueOperationDescriptor t_setOperation(p_descriptor.getHandle() + "_sco", p_descriptor.getHandle());
    addSetOperationToSCOObjectImpl(t_setOperation, p_ownerMDS);
}

void SDCProvider::createSetOperationForDescriptor(const StringMetricDescriptor& p_descriptor, MdsDescriptor& p_ownerMDS)
{
    const CDM::SetStringOperationDescriptor t_setOperation(p_descriptor.getHandle() + "_sco", p_descriptor.getHandle());
    addSetOperationToSCOObjectImpl(t_setOperation, p_ownerMDS);
}

template<class T> void SDCProvider::createSetOperationForContextDescriptor(const T& p_descriptor, MdsDescriptor& p_ownerMDS)
{
    const CDM::SetContextStateOperationDescriptor t_setOperation(p_descriptor.getHandle() + "_sco", p_descriptor.getHandle());
    addSetOperationToSCOObjectImpl(t_setOperation, p_ownerMDS);
}

void SDCProvider::createSetOperationForDescriptor(const PatientContextDescriptor& p_descriptor, MdsDescriptor& p_ownerMDS)
{
    createSetOperationForContextDescriptor(p_descriptor, p_ownerMDS);
}

void SDCProvider::createSetOperationForDescriptor(const LocationContextDescriptor& p_descriptor, MdsDescriptor& p_ownerMDS)
{
    createSetOperationForContextDescriptor(p_descriptor, p_ownerMDS);
}

void SDCProvider::createSetOperationForDescriptor(const EnsembleContextDescriptor& p_descriptor, MdsDescriptor& p_ownerMDS)
{
    createSetOperationForContextDescriptor(p_descriptor, p_ownerMDS);
}

void SDCProvider::createSetOperationForDescriptor(const OperatorContextDescriptor& p_descriptor, MdsDescriptor& p_ownerMDS)
{
    createSetOperationForContextDescriptor(p_descriptor, p_ownerMDS);
}

void SDCProvider::createSetOperationForDescriptor(const WorkflowContextDescriptor& p_descriptor, MdsDescriptor& p_ownerMDS)
{
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
    m_devicecharacteristics.setEndpointReference(getEndpointReference());
}

unsigned long long int SDCProvider::getMdibVersion() const
{
    return mdibVersion;
}

void SDCProvider::incrementMDIBVersion()
{
    mdibVersion++;
}
void SDCProvider::_incrementMdStateVersion()
{
    std::lock_guard<std::mutex> t_lock{m_mutex_MdState};

    // Set Initial Version
    if(!m_MdState.hasStateVersion())
    {
        m_MdState.setStateVersion(VersionCounter(1));
        incrementMDIBVersion();
        return;
    }

    // Update MdState
    m_MdState.setStateVersion(m_MdState.getStateVersion() + 1);
}

void SDCProvider::setPeriodicEventInterval(std::chrono::milliseconds p_interval)
{
    // TODO: Why 250?
    if(p_interval > std::chrono::milliseconds(250))
    {
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

void SDCProvider::addHandleForPeriodicEvent(const std::string& p_handle)
{
    std::lock_guard<std::mutex> t_lock{m_mutex_PeriodicUpdateHandles};
    ml_handlesForPeriodicUpdates.push_back(p_handle);
}
void SDCProvider::removeHandleForPeriodicEvent(const std::string& p_handle)
{
    std::lock_guard<std::mutex> t_lock{m_mutex_PeriodicUpdateHandles};
    ml_handlesForPeriodicUpdates.erase(std::remove(ml_handlesForPeriodicUpdates.begin(), ml_handlesForPeriodicUpdates.end(), p_handle),
                                       ml_handlesForPeriodicUpdates.end());
}

void SDCProvider::startAsyncProviderInvoker()
{
    if(m_providerInvoker == nullptr)
    {
        m_providerInvoker = std::make_shared<AsyncProviderInvoker>(*this, m_invokeQueue);
        m_providerInvoker->start();
    }
}
void SDCProvider::stopAsyncProviderInvoker()
{
    if(m_providerInvoker == nullptr)
    {
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

template<class T> void SDCProvider::_initAbstractStateDefaults(T& p_state)
{
    if(!p_state.hasStateVersion())
    {
        p_state.setStateVersion(VersionCounter(INITIAL_STATE_VERSION));
    }
}

template<class T> void SDCProvider::_initComponentStateDefaults(T& p_state)
{
    if(!p_state.hasActivationState())
    {
        p_state.setActivationState(ComponentActivation::On);
    }
}

template<class T> void SDCProvider::_initStateMetricValueDefaults(T& p_state)
{
    if(!p_state.hasMetricValue())
    {
        return;
    }

    if(!p_state.getMetricValue().hasDeterminationTime())
    {
        p_state.setMetricValue(p_state.getMetricValue().setDeterminationTime(Timestamp(0)));
    }
}
