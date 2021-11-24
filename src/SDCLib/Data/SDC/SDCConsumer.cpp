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
 * SDCConsumer.cpp
 *
 *  @Copyright (C) 2017, SurgiTAIX AG
 *  Author: buerger, besting, roehser
 *  Modified on: 26.08.2019, baumeister
 *
 */

#include "SDCLib/Data/SDC/SDCConsumer.h"
#include "SDCLib/Data/SDC/SDCConsumerMDStateHandler.h"
#include "SDCLib/Data/SDC/SDCConsumerConnectionLostHandler.h"
#include "SDCLib/Data/SDC/SDCConsumerOperationInvokedHandler.h"
#include "SDCLib/Data/SDC/SDCConsumerSubscriptionLostHandler.h"
#include "SDCLib/Data/SDC/FutureInvocationState.h"
#include "SDCLib/SDCInstance.h"
#include "SDCLib/Data/SDC/MDIB/AlertSystemDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/AlertSystemState.h"
#include "SDCLib/Data/SDC/MDIB/AlertSignalDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/AlertSignalState.h"
#include "SDCLib/Data/SDC/MDIB/AlertConditionDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/AlertConditionState.h"
#include "SDCLib/Data/SDC/MDIB/ClockState.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/DistributionSampleArrayMetricState.h"
#include "SDCLib/Data/SDC/MDIB/EnumStringMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/EnumStringMetricState.h"
#include "SDCLib/Data/SDC/MDIB/LimitAlertConditionState.h"
#include "SDCLib/Data/SDC/MDIB/LimitAlertConditionDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/LocationContextState.h"
#include "SDCLib/Data/SDC/MDIB/PatientContextState.h"
#include "SDCLib/Data/SDC/MDIB/EnsembleContextState.h"
#include "SDCLib/Data/SDC/MDIB/OperatorContextState.h"
#include "SDCLib/Data/SDC/MDIB/WorkflowContextState.h"
#include "SDCLib/Data/SDC/MDIB/MeansContextState.h"
#include "SDCLib/Data/SDC/MDIB/LocationContextDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/PatientContextDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/EnsembleContextDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/OperatorContextDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/WorkflowContextDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/MdsDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricState.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricValue.h"
#include "SDCLib/Data/SDC/MDIB/custom/OperationInvocationContext.h"
#include "SDCLib/Data/SDC/MDIB/RealTimeSampleArrayMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/RealTimeSampleArrayMetricState.h"
#include "SDCLib/Data/SDC/MDIB/StringMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/StringMetricState.h"
#include "SDCLib/Data/SDC/MDIB/StringMetricValue.h"
#include "SDCLib/Data/SDC/MDIB/ScoState.h"
#include "SDCLib/Data/SDC/MDIB/BatteryState.h"
#include "SDCLib/Data/SDC/MDIB/ClockState.h"
#include "SDCLib/Data/SDC/MDIB/MdsState.h"
#include "SDCLib/Data/SDC/MDIB/VmdState.h"
#include "SDCLib/Data/SDC/MDIB/SetValueOperationState.h"
#include "SDCLib/Data/SDC/MDIB/SetStringOperationState.h"
#include "SDCLib/Data/SDC/MDIB/ActivateOperationState.h"
#include "SDCLib/Data/SDC/MDIB/SetContextStateOperationState.h"
#include "SDCLib/Data/SDC/MDIB/SetMetricStateOperationState.h"
#include "SDCLib/Data/SDC/MDIB/SetComponentStateOperationState.h"
#include "SDCLib/Data/SDC/MDIB/SetAlertStateOperationState.h"
#include "OSELib/SDC/SDCConstants.h"
#include "OSELib/DPWS/DeviceDescription.h"
#include "OSELib/SDC/OperationTraits.h"

#include "DataModel/osdm.hxx"

#include <ostream>
#include <vector>

#include <Poco/Net/NetException.h>


using namespace SDCLib;
using namespace SDCLib::Data;
using namespace SDCLib::Data::SDC;


MDM::SetAlertState createRequestMessage(const AlertConditionState & p_state, const std::string & p_operationHandle) {
	return MDM::SetAlertState(p_operationHandle, ConvertToCDM::convert(p_state));
}

MDM::SetAlertState createRequestMessage(const AlertSignalState & p_state, const std::string & p_operationHandle) {
	return MDM::SetAlertState(p_operationHandle, ConvertToCDM::convert(p_state));
}

MDM::SetAlertState createRequestMessage(const AlertSystemState & p_state, const std::string & p_operationHandle) {
	return MDM::SetAlertState(p_operationHandle, ConvertToCDM::convert(p_state));
}

MDM::SetString createRequestMessage(const EnumStringMetricState & p_state, const std::string & p_operationHandle) {
	return MDM::SetString(p_operationHandle, p_state.getMetricValue().getValue());
}

MDM::SetAlertState createRequestMessage(const LimitAlertConditionState & p_state, const std::string & p_operationHandle) {
	return MDM::SetAlertState(p_operationHandle, ConvertToCDM::convert(p_state));
}

MDM::SetValue createRequestMessage(const NumericMetricState & p_state, const std::string & p_operationHandle) {
	return MDM::SetValue(p_operationHandle, p_state.getMetricValue().getValue());
}

MDM::SetString createRequestMessage(const StringMetricState & p_state, const std::string & p_operationHandle) {
	return MDM::SetString(p_operationHandle, p_state.getMetricValue().getValue());
}

MDM::Activate createRequestMessage(const std::string & p_operationHandle) {
	return MDM::Activate(p_operationHandle);
}

MDM::SetContextState createRequestMessage(const LocationContextState & p_state, const std::string & p_operationHandle) {
	MDM::SetContextState t_result(p_operationHandle);
	t_result.getProposedContextState().push_back(ConvertToCDM::convert(p_state));
	return t_result;
}


MDM::SetContextState createRequestMessage(const PatientContextState & p_state, const std::string & p_operationHandle) {
	MDM::SetContextState t_result(p_operationHandle);
	t_result.getProposedContextState().push_back(ConvertToCDM::convert(p_state));
	return t_result;
}

MDM::SetContextState createRequestMessage(const EnsembleContextState & p_state, const std::string & p_operationHandle) {
	MDM::SetContextState t_result(p_operationHandle);
	t_result.getProposedContextState().push_back(ConvertToCDM::convert(p_state));
	return t_result;
}

MDM::SetContextState createRequestMessage(const OperatorContextState & p_state, const std::string & p_operationHandle) {
	MDM::SetContextState t_result(p_operationHandle);
	t_result.getProposedContextState().push_back(ConvertToCDM::convert(p_state));
	return t_result;
}

MDM::SetContextState createRequestMessage(const WorkflowContextState & p_state, const std::string & p_operationHandle) {
	MDM::SetContextState t_result(p_operationHandle);
	t_result.getProposedContextState().push_back(ConvertToCDM::convert(p_state));
	return t_result;
}

SDCConsumer::SDCConsumer(SDCLib::SDCInstance_shared_ptr p_SDCInstance, OSELib::DPWS::DeviceDescription_shared_ptr p_deviceDescription)
: OSELib::Helper::WithLogger(OSELib::Log::SDCCONSUMER)
, m_SDCInstance(p_SDCInstance)
, m_deviceDescription(p_deviceDescription)
{
	assert(m_deviceDescription != nullptr);

    // FIXME! Rework this part! This might result in a zombie state!
	try {
		m_adapter = std::unique_ptr<SDCConsumerAdapter>(new SDCConsumerAdapter(*this, m_deviceDescription));
		if(!m_adapter->start()) {
            log_error([] { return "Could not start ConsumerAdapter!"; });
            disconnect();
        }
	} catch (const Poco::Net::NetException & e) {
		log_error([&] { return "Exception: " + std::string(e.what()) + " Opening socket impossible. Aborted."; });
        disconnect();
    }
	catch(...) {
        log_error([] {return "Unknown Exception: Could not create ConsumerAdapter!"; });
        disconnect();
        // FIXME: Zombie state?
    }

	if (!isConnected()) {
		log_error([&] { return "Connecting to " + m_deviceDescription->getEPR() + " failed."; });
	}
}

SDCConsumer::~SDCConsumer()
{
	// TODO: Why?
    for (auto & t_fis : ml_fisMap) {
       t_fis.second->m_consumer = nullptr;
    }

    // FIXME: This is not threadsafe + RAII
    if (m_adapter != nullptr)
    {
        log_warning([] { return "SDCConsumer deleted before disconnected. For proper handling please disconnect the consumer first"; });
        disconnect();
        // FIXME: What does this tell us? The dtor should handle a proper disconnect for us! RAII
    }
}
bool SDCConsumer::isConnected() const
{
	return (nullptr != m_adapter);
}
void SDCConsumer::disconnect()
{
	if (m_adapter) {
		m_adapter.reset();
	}
}

void SDCConsumer::setConnectionLostHandler(SDCConsumerConnectionLostHandler * p_handler) {
    m_connectionLostHandler = p_handler;
}

void SDCConsumer::setSubscriptionLostHandler(SDCConsumerSubscriptionLostHandler * p_handler) {
    m_subscriptionLostHandler = p_handler;
}

void SDCConsumer::onConnectionLost() {
    if (m_connectionLostHandler != nullptr) {
        m_connectionLostHandler->onConnectionLost();
    }
}

void SDCConsumer::onSubscriptionLost() {
    if (m_subscriptionLostHandler != nullptr) {
        m_subscriptionLostHandler->onSubscriptionLost();
    }
}

MdibContainer SDCConsumer::getMdib()
{
	if (!requestMdib()) {
		onConnectionLost(); // Todo: Why? Unclear handling of connecion!
	}
    return *m_mdib; // FIXME: What if nullptr?
}

MdDescription SDCConsumer::getMdDescription()
{
	if(nullptr == m_adapter) { // Todo: Temp workaround
		return MdDescription();
	}

    const MDM::GetMdDescription request;
    auto t_response(m_adapter->invoke(request, getSDCInstance()->getSSLConfig()->getClientContext()));
	if (t_response == nullptr) {
        log_error([] { return "GetMdDescription request failed!"; });
		onConnectionLost(); // Todo: Why? Unclear handling of connecion!
		return MdDescription();
	}

	const MdDescription t_description(ConvertFromCDM::convert(t_response->getMdDescription()));

	// refresh cashed version
	m_mdib->setMdDescription(t_description);
	if (t_response->getMdibVersion().present()) {
		m_mdib->setMdibVersion(t_response->getMdibVersion().get());
	}

    return t_description;
}

MdDescription SDCConsumer::getCachedMdDescription()
{
	if (m_mdib) {
		return m_mdib->getMdDescription();
	}
	return MdDescription();
}

MdState SDCConsumer::getMdState()
{
	if(nullptr == m_adapter) { // Todo: Temp workaround
		return MdState();
	}

    const MDM::GetMdState t_request;
    auto t_response(m_adapter->invoke(t_request, getSDCInstance()->getSSLConfig()->getClientContext()));

	if (nullptr == t_response) {
		log_error([] { return "GetMdState request failed!"; });
		onConnectionLost(); // Todo: Why? Unclear handling of connection!
		return MdState();
	}

    return ConvertFromCDM::convert(t_response->getMdState());
}

bool SDCConsumer::unregisterFutureInvocationListener(int p_transactionId) {
    std::lock_guard<std::mutex> t_lock(m_transactionMutex);
	return ml_fisMap.erase(p_transactionId) == 1;
}

bool SDCConsumer::registerStateEventHandler(SDCConsumerOperationInvokedHandler * p_handler)
{
	if(nullptr == m_adapter) {
		return false;
	}

    assert(p_handler != nullptr);

    std::lock_guard<std::mutex> t_lock(m_eventMutex);
	ml_eventHandlers[p_handler->getDescriptorHandle()] = p_handler;
 	p_handler->parentConsumer = this;
	if (m_adapter) {
		m_adapter->subscribeEvents();
	}
	return true;
}
bool SDCConsumer::unregisterStateEventHandler(SDCConsumerOperationInvokedHandler * p_handler)
{
	if(nullptr == m_adapter) {
		return false;
	}

	assert(p_handler != nullptr);

	std::lock_guard<std::mutex> t_lock(m_eventMutex);
    ml_eventHandlers.erase(p_handler->getDescriptorHandle());

	if (m_adapter && ml_eventHandlers.empty()) {
		m_adapter->unsubscribeEvents();
	}
    return true;
}

bool SDCConsumer::requestMdib()
{
	auto t_response(requestCDMMdib());
	if (t_response == nullptr) {
		return false;
	}

	std::lock_guard<std::mutex> t_lock(m_requestMutex);
	m_mdib.reset(new MdibContainer());
	m_mdib->setMdState(ConvertFromCDM::convert(t_response->getMdib().getMdState().get()));
	if (t_response->getMdib().getMdDescription().present()) {
		m_mdib->setMdDescription(ConvertFromCDM::convert(t_response->getMdib().getMdDescription().get()));
	}

	if (t_response->getMdibVersion().present()) {
		m_mdib->setMdibVersion(t_response->getMdibVersion().get());
	}
	return true;
}

std::unique_ptr<MDM::GetMdibResponse> SDCConsumer::requestCDMMdib()
{
	if(nullptr == m_adapter) { // Todo: Temp workaround
		return nullptr;
	}

    const MDM::GetMdib t_request;
    auto t_response(m_adapter->invoke(t_request, getSDCInstance()->getSSLConfig()->getClientContext()));
    return t_response;
}

std::string SDCConsumer::requestRawMdib()
{
	auto t_response(requestCDMMdib());
	if (t_response == nullptr) {
		log_error([] { return "MDIB request failed!"; });
		return "";
	}
	const xml_schema::Flags xercesFlags(xml_schema::Flags::dont_validate | xml_schema::Flags::no_xml_declaration | xml_schema::Flags::dont_initialize);
	std::ostringstream t_result;
	xml_schema::NamespaceInfomap tl_map;

	CDM::serializeMdibContainer(t_result, t_response->getMdib(), tl_map, OSELib::XML_ENCODING, xercesFlags);
	return t_result.str();

}

// TODO: delete commitStateImpl() use one template class, use traits for Metrices: https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Member_Detector

InvocationState SDCConsumer::commitState(const AlertSystemState & p_state, FutureInvocationState & p_fis) {
	return commitStateImpl<OSELib::SDC::SetAlertStateTraits>(p_state, p_fis);
}
InvocationState SDCConsumer::commitState(const AlertSignalState & p_state, FutureInvocationState & p_fis) {
	return commitStateImpl<OSELib::SDC::SetAlertStateTraits>(p_state, p_fis);
}
InvocationState SDCConsumer::commitState(const AlertConditionState & state, FutureInvocationState & p_fis) {
	return commitStateImpl<OSELib::SDC::SetAlertStateTraits>(state, p_fis);
}
InvocationState SDCConsumer::commitState(const LimitAlertConditionState & p_state, FutureInvocationState & p_fis) {
	return commitStateImpl<OSELib::SDC::SetAlertStateTraits>(p_state, p_fis);
}
InvocationState SDCConsumer::commitState(const EnumStringMetricState & p_state, FutureInvocationState & p_fis)
{
	if (!p_state.hasMetricValue()) {
		return InvocationState::Fail;
	}
	if (!p_state.getMetricValue().hasValue()) {
		return InvocationState::Fail;
	}
	return commitStateImpl<OSELib::SDC::SetStringTraits>(p_state, p_fis);
}
InvocationState SDCConsumer::commitState(const NumericMetricState & p_state, FutureInvocationState & p_fis)
{
	if (!p_state.hasMetricValue()) {
		return InvocationState::Fail;
	}
	if (!p_state.getMetricValue().hasValue()) {
		return InvocationState::Fail;
	}
	return commitStateImpl<OSELib::SDC::SetValueTraits>(p_state, p_fis);
}
InvocationState SDCConsumer::commitState(const StringMetricState & p_state, FutureInvocationState & p_fis)
{
	if (!p_state.hasMetricValue()) {
		return InvocationState::Fail;
	}
	if (!p_state.getMetricValue().hasValue()) {
		return InvocationState::Fail;
	}
	return commitStateImpl<OSELib::SDC::SetStringTraits>(p_state, p_fis);
}
InvocationState SDCConsumer::commitState(const LocationContextState & p_state, FutureInvocationState & p_fis) {
	return commitStateImpl<OSELib::SDC::SetContextStateTraits>(p_state, p_fis);
}
InvocationState SDCConsumer::commitState(const EnsembleContextState & p_state, FutureInvocationState & p_fis) {
	return commitStateImpl<OSELib::SDC::SetContextStateTraits>(p_state, p_fis);
}
InvocationState SDCConsumer::commitState(const OperatorContextState & p_state, FutureInvocationState & p_fis) {
	return commitStateImpl<OSELib::SDC::SetContextStateTraits>(p_state, p_fis);
}
InvocationState SDCConsumer::commitState(const PatientContextState & p_state, FutureInvocationState & p_fis) {
	return commitStateImpl<OSELib::SDC::SetContextStateTraits>(p_state, p_fis);
}
InvocationState SDCConsumer::commitState(const WorkflowContextState & p_state, FutureInvocationState & p_fis) {
	return commitStateImpl<OSELib::SDC::SetContextStateTraits>(p_state, p_fis);
}


InvocationState SDCConsumer::commitState(const AlertSystemState & p_state) {
	FutureInvocationState t_dummy;
	return commitState(p_state, t_dummy);
}
InvocationState SDCConsumer::commitState(const AlertSignalState & p_state) {
	FutureInvocationState t_dummy;
	return commitState(p_state, t_dummy);
}
InvocationState SDCConsumer::commitState(const AlertConditionState & p_state) {
	FutureInvocationState t_dummy;
	return commitState(p_state, t_dummy);
}
InvocationState SDCConsumer::commitState(const LimitAlertConditionState & p_state) {
	FutureInvocationState t_dummy;
	return commitState(p_state, t_dummy);
}
InvocationState SDCConsumer::commitState(const EnumStringMetricState & p_state) {
	FutureInvocationState t_dummy;
	return commitState(p_state, t_dummy);
}
InvocationState SDCConsumer::commitState(const NumericMetricState & p_state) {
	FutureInvocationState t_dummy;
	return commitState(p_state, t_dummy);
}
InvocationState SDCConsumer::commitState(const StringMetricState & p_state) {
	FutureInvocationState t_dummy;
	return commitState(p_state, t_dummy);
}
InvocationState SDCConsumer::commitState(const LocationContextState & p_state) {
	FutureInvocationState t_dummy;
	return commitState(p_state, t_dummy);
}
InvocationState SDCConsumer::commitState(const EnsembleContextState & p_state) {
	FutureInvocationState t_dummy;
	return commitState(p_state, t_dummy);
}
InvocationState SDCConsumer::commitState(const OperatorContextState & p_state) {
	FutureInvocationState t_dummy;
	return commitState(p_state, t_dummy);
}
InvocationState SDCConsumer::commitState(const PatientContextState & p_state) {
	FutureInvocationState t_dummy;
	return commitState(p_state, t_dummy);
}
InvocationState SDCConsumer::commitState(const WorkflowContextState & p_state) {
	FutureInvocationState t_dummy;
	return commitState(p_state, t_dummy);
}

template<class OperationTraits, class StateType>
InvocationState SDCConsumer::commitStateImpl(const StateType & p_state, FutureInvocationState & p_fis)
{
	if(nullptr == m_adapter) { // Todo: Temp workaround
		log_error([] { return "Commit failed: Adapter not initialized!"; });
		return InvocationState::Fail;
	}

	if (p_state.getDescriptorHandle().empty()) {
		log_error([] { return "Commit failed: descriptor handle is empty!"; });
		return InvocationState::Fail;
	}

	const MdDescription t_mddescription(getCachedMdDescription());

	typename StateType::DescriptorType t_descriptor;
	if (!t_mddescription.findDescriptor(p_state.getDescriptorHandle(), t_descriptor)) {
		log_error([] { return "Could not find descriptor handle in getMdDescriptionResponse. Resolving matching set operations failed!"; });
		return InvocationState::Fail;
	}


	// Check for operation that targets the descriptor for this state.
	// FIXME: Type needs to be considered here!
	auto t_operationHandle{t_mddescription.getFirstOperationHandleForOperationTarget(p_state.getDescriptorHandle())};
	if (t_operationHandle.empty()) {
		// No operation targeting this state was found.
		// check for operation that targets state
		t_operationHandle = t_mddescription.getFirstOperationHandleForOperationTarget(p_state.getDescriptorHandle()); // FIXME: duplicated code?
	}
	if (t_operationHandle.empty()) {
		log_error([&] { return "Commit failed: No set operation found to modify given state! State has descriptor handle " + p_state.getDescriptorHandle(); });
		return InvocationState::Fail;
	}

	const typename OperationTraits::Request t_request(createRequestMessage(p_state, t_operationHandle));
	auto t_response(m_adapter->invoke(t_request, getSDCInstance()->getSSLConfig()->getClientContext()));
	if (nullptr == t_response) {
		return InvocationState::Fail;
	}

	handleInvocationState(t_response->getInvocationInfo().getTransactionId(), p_fis);
	return ConvertFromCDM::convert(t_response->getInvocationInfo().getInvocationState());
}

void SDCConsumer::handleInvocationState(int p_transactionId, FutureInvocationState & p_fis)
{
	// Put user future state into map
	std::lock_guard<std::mutex> t_lock(m_transactionMutex);
	p_fis.m_transactionId = p_transactionId;
	ml_fisMap[p_fis.m_transactionId] = &p_fis;
	p_fis.m_consumer = this;
	// Dequeue possible intermediate events
    while (ml_transactionQueue.size() > 0) {
    	const auto t_ts(ml_transactionQueue.front());
    	ml_transactionQueue.pop_front();
	    if (ml_fisMap.find(t_ts.m_transactionId) != ml_fisMap.end()) {
	    	ml_fisMap[t_ts.m_transactionId]->setEvent(t_ts.m_invocationState);
	    }
    }
}

InvocationState SDCConsumer::activate(const std::string & p_handle) {
	FutureInvocationState t_dummy;
	return activate(p_handle, t_dummy);
}

InvocationState SDCConsumer::activate(const std::string & p_handle, FutureInvocationState & p_fis)
{
	if(nullptr == m_adapter) { // Todo: Temp workaround
		log_error([] { return "Commit failed: Adapter not initialized!"; });
		return InvocationState::Fail;
	}

    const auto t_mdd(getCachedMdDescription());

	const auto t_request(createRequestMessage(p_handle));
	auto t_response(m_adapter->invoke(t_request, getSDCInstance()->getSSLConfig()->getClientContext()));
	if (nullptr == t_response) {
		return InvocationState::Fail;
	}

	handleInvocationState(t_response->getInvocationInfo().getTransactionId(), p_fis);
	return ConvertFromCDM::convert(t_response->getInvocationInfo().getInvocationState());
}

//// specialization needed for API
template std::unique_ptr<AlertConditionState> SDCConsumer::requestState<AlertConditionState>(const std::string & p_handle);
template std::unique_ptr<AlertSignalState> SDCConsumer::requestState<AlertSignalState>(const std::string & p_handle);
template std::unique_ptr<AlertSystemState> SDCConsumer::requestState<AlertSystemState>(const std::string & p_handle);
template std::unique_ptr<ClockState> SDCConsumer::requestState<ClockState>(const std::string & p_handle);
template std::unique_ptr<EnsembleContextState> SDCConsumer::requestState<EnsembleContextState>(const std::string & p_handle);
template std::unique_ptr<EnumStringMetricState> SDCConsumer::requestState<EnumStringMetricState>(const std::string & p_handle);
template std::unique_ptr<LimitAlertConditionState> SDCConsumer::requestState<LimitAlertConditionState>(const std::string & p_handle);
template std::unique_ptr<LocationContextState> SDCConsumer::requestState<LocationContextState>(const std::string & p_handle);
template std::unique_ptr<NumericMetricState> SDCConsumer::requestState<NumericMetricState>(const std::string & p_handle);
template std::unique_ptr<OperatorContextState> SDCConsumer::requestState<OperatorContextState>(const std::string & p_handle);
template std::unique_ptr<PatientContextState> SDCConsumer::requestState<PatientContextState>(const std::string & p_handle);
template std::unique_ptr<StringMetricState> SDCConsumer::requestState<StringMetricState>(const std::string & p_handle);
template std::unique_ptr<WorkflowContextState> SDCConsumer::requestState<WorkflowContextState>(const std::string & p_handle);
template std::unique_ptr<RealTimeSampleArrayMetricState> SDCConsumer::requestState<RealTimeSampleArrayMetricState>(const std::string & p_handle);


// TODO: implement and test! missing states -> RealTimeSampleArrayMetricState, DistributionSampleArrayMetricState

template<class TStateType>
std::unique_ptr<TStateType> SDCConsumer::requestState(const std::string & p_handle)
{
	if(nullptr == m_adapter) {
		return nullptr;
	}

    MDM::GetMdState t_request;
    t_request.getHandleRef().push_back(p_handle);

    auto t_response(m_adapter->invoke(t_request, getSDCInstance()->getSSLConfig()->getClientContext()));
    if (nullptr == t_response) {
    	log_error([&] { return "requestState failed: invoke of adapter returned nullptr for handle "  + p_handle; });
    	return nullptr;
    }

	const CDM::MdState::StateSequence & t_resultStates(t_response->getMdState().getState());
	if (t_resultStates.empty()) {
		log_error([&] { return "requestState failed: Got no response object for handle "  + p_handle; });
		return nullptr;
	} else if (t_resultStates.size() > 1) {
		log_error([&] { return "requestState failed: Got too many response objects for handle " + p_handle + " ( " + std::to_string(t_resultStates.size()) + " )"; });
		return nullptr;
	}

	// take first element
	try {
		const typename TStateType::WrappedType & t_resultState(dynamic_cast<const typename TStateType::WrappedType &>(t_resultStates.front()));
		std::unique_ptr<TStateType> t_returnState(new TStateType(ConvertFromCDM::convert(t_resultState)));
		return std::move(t_returnState);
	} catch (...) {
		log_error([&] { return "requestState failed: Types mismatch of returned object for handle " + p_handle; });
		return nullptr;
	}
	return nullptr;
}

template<typename T> void SDCConsumer::onStateChanged(const T & p_state)
{
    std::lock_guard<std::mutex> t_lock(m_eventMutex);
    auto t_it = ml_eventHandlers.find(p_state.getDescriptorHandle());
    if (t_it != ml_eventHandlers.end()) {
    	if (SDCConsumerMDStateHandler<T> * t_handler = dynamic_cast<SDCConsumerMDStateHandler<T> *>(t_it->second)) {
    		t_handler->onStateChanged(p_state);
    	}
    }
}

//template<typename T> void SDCConsumer::onMultiStateChanged(const T & p_state) {
//    std::lock_guard<std::mutex> t_lock(m_eventMutex);
//	auto t_it = ml_eventHandlers.find(p_state.getHandle());
//	if (t_it != eventHandlers.end()) {
//		if (SDCConsumerMDStateHandler<T> * t_handler = dynamic_cast<SDCConsumerMDStateHandler<T> *>(t_it->second)) {
//			t_handler->onStateChanged(p_state);
//		}
//	}
//}

// metrices
template void SDCConsumer::onStateChanged(const EnumStringMetricState & p_state);
template void SDCConsumer::onStateChanged(const NumericMetricState & p_state);
template void SDCConsumer::onStateChanged(const StringMetricState & p_state);
template void SDCConsumer::onStateChanged(const RealTimeSampleArrayMetricState & p_state);
template void SDCConsumer::onStateChanged(const DistributionSampleArrayMetricState & p_state);
// alerts
template void SDCConsumer::onStateChanged(const AlertSystemState & p_state);
template void SDCConsumer::onStateChanged(const AlertSignalState & p_state);
template void SDCConsumer::onStateChanged(const AlertConditionState & p_state);
template void SDCConsumer::onStateChanged(const LimitAlertConditionState & p_state);
// Component
template void SDCConsumer::onStateChanged(const ScoState & p_state);
template void SDCConsumer::onStateChanged(const ClockState & p_state);
template void SDCConsumer::onStateChanged(const BatteryState & p_state);
template void SDCConsumer::onStateChanged(const MdsState & p_state);
template void SDCConsumer::onStateChanged(const VmdState & p_state);
// OperationState
template void SDCConsumer::onStateChanged(const SetValueOperationState & p_state);
template void SDCConsumer::onStateChanged(const SetComponentStateOperationState & p_state);
template void SDCConsumer::onStateChanged(const SetMetricStateOperationState & p_state);
template void SDCConsumer::onStateChanged(const SetContextStateOperationState & p_state);
template void SDCConsumer::onStateChanged(const ActivateOperationState & p_state);
template void SDCConsumer::onStateChanged(const SetStringOperationState & p_state);
template void SDCConsumer::onStateChanged(const SetAlertStateOperationState & p_state);

// TODO: change! context states are multi states
//template void SDCConsumer::onMultiStateChanged(const WorkflowContextState & p_state);
//template void SDCConsumer::onMultiStateChanged(const PatientContextState & p_state);
//template void SDCConsumer::onMultiStateChanged(const LocationContextState& p_state);
//template void SDCConsumer::onMultiStateChanged(const OperatorContextState & p_state);
//template void SDCConsumer::onMultiStateChanged(const MeansContextState & p_state);
//template void SDCConsumer::onMultiStateChanged(const EnsembleContextState & p_state);
// as well as states referenced by a descriptor
template void SDCConsumer::onStateChanged(const WorkflowContextState & p_state);
template void SDCConsumer::onStateChanged(const PatientContextState & p_state);
template void SDCConsumer::onStateChanged(const LocationContextState& p_state);
template void SDCConsumer::onStateChanged(const OperatorContextState & p_state);
template void SDCConsumer::onStateChanged(const MeansContextState & p_state);
template void SDCConsumer::onStateChanged(const EnsembleContextState & p_state);

void SDCConsumer::onOperationInvoked(const OperationInvocationContext & p_oic, InvocationState p_is)
{
    std::lock_guard<std::mutex> t_lockEvent(m_eventMutex);

    // If operation handle belongs to ActivateOperationDescriptor, use operation handle as target handle in case of operation invoked events!
    const MdDescription t_mdd(getCachedMdDescription());
    std::string t_targetHandle;
    const auto tl_mdss(t_mdd.collectAllMdsDescriptors());
    for (const auto & mds : tl_mdss) {
    	const auto t_mds_uniquePtr(ConvertToCDM::convert(mds));
		if (!t_mds_uniquePtr->getSco().present()) {
			continue;
		}
		for (const auto & t_operation : t_mds_uniquePtr->getSco().get().getOperation()) // TODO: Check on temporary return value in chaining
		{
			if (t_operation.getHandle() == p_oic.operationHandle && dynamic_cast<const CDM::ActivateOperationDescriptor *>(&t_operation) != nullptr) {
				t_targetHandle = p_oic.operationHandle;
				break;
			}
		}
		if (!t_targetHandle.empty())
			break;
    }

    // All other operation descriptor cases
    if (t_targetHandle.empty()) {
    	t_targetHandle = t_mdd.getOperationTargetForOperationHandle(p_oic.operationHandle);
    }
    const auto t_iter = ml_eventHandlers.find(t_targetHandle);
    if (t_iter != ml_eventHandlers.end()) {
    	t_iter->second->onOperationInvoked(p_oic, p_is);
    }

    // Notify user future invocation state events
    std::lock_guard<std::mutex> t_lockTransaction(m_transactionMutex);
    if (ml_fisMap.find(p_oic.transactionId) != ml_fisMap.end()) {
    	ml_fisMap[p_oic.transactionId]->setEvent(p_is);
    }
    // Queue to check intermediate events during commits
    ml_transactionQueue.push_back(TransactionState(p_oic.transactionId, p_is));
}

std::string SDCConsumer::getEndpointReference() const {
	return m_deviceDescription->getEPR();
}
std::shared_ptr<const OSELib::DPWS::DeviceDescription>  SDCConsumer::getDeviceDescription() const {
	return m_deviceDescription;
}

unsigned long long int SDCConsumer::getLastKnownMdibVersion() {
	std::lock_guard<std::mutex> t_lock(m_mdibVersionMutex);
	return m_lastKnownMDIBVersion;
}

void SDCConsumer::updateLastKnownMdibVersion(unsigned long long int p_newVersion) {
	std::lock_guard<std::mutex> t_lock(m_mdibVersionMutex);
	if (m_lastKnownMDIBVersion < p_newVersion) {
		m_lastKnownMDIBVersion = p_newVersion;
	}
	// FIXME: No return value?
}
