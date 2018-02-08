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
 * OSCPConsumer.cpp
 *
 *  @Copyright (C) 2017, SurgiTAIX AG
 *  Author: buerger, besting, roehser
 */

#include <memory>
#include <vector>

#include "Poco/Net/NetException.h"

#include "osdm.hxx"

#include "OSCLib/OSCLibrary.h"
#include "OSCLib/Data/OSCP/FutureInvocationState.h"
#include "OSELib/OSCP/OSCPConstants.h"
#include "OSCLib/Data/OSCP/OSCPConsumer.h"
#include "OSCLib/Data/OSCP/OSCPConsumerConnectionLostHandler.h"
#include "OSCLib/Data/OSCP/SDCConsumerOperationInvokedHandler.h"
#include "OSCLib/Data/OSCP/OSCPConsumerSubscriptionLostHandler.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSystemDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSystemState.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSignalDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSignalState.h"
#include "OSCLib/Data/OSCP/MDIB/AlertConditionDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AlertConditionState.h"
#include "OSCLib/Data/OSCP/MDIB/ClockState.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/DistributionSampleArrayMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/EnumStringMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/EnumStringMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/LimitAlertConditionState.h"
#include "OSCLib/Data/OSCP/MDIB/LimitAlertConditionDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/LocationContextState.h"
#include "OSCLib/Data/OSCP/MDIB/PatientContextState.h"
#include "OSCLib/Data/OSCP/MDIB/EnsembleContextState.h"
#include "OSCLib/Data/OSCP/MDIB/OperatorContextState.h"
#include "OSCLib/Data/OSCP/MDIB/WorkflowContextState.h"
#include "OSCLib/Data/OSCP/MDIB/MeansContextState.h"
#include "OSCLib/Data/OSCP/MDIB/LocationContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/PatientContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/EnsembleContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/OperatorContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/WorkflowContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/MdsDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/MdDescription.h"
#include "OSCLib/Data/OSCP/MDIB/MdState.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricValue.h"
#include "OSCLib/Data/OSCP/MDIB/custom/OperationInvocationContext.h"
#include "OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/StringMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/StringMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/StringMetricValue.h"

#include "OSELib/DPWS/DPWS11Constants.h"
#include "OSELib/OSCP/OperationTraits.h"

#include "OSCLib/Data/OSCP/SDCConsumerMDStateHandler.h"


namespace OSCLib {
namespace Data {
namespace OSCP {

MDM::SetAlertState createRequestMessage(const AlertConditionState & state, const std::string & operationHandle) {
	MDM::SetAlertState result(operationHandle, ConvertToCDM::convert(state));
	return result;
}

MDM::SetAlertState createRequestMessage(const AlertSignalState & state, const std::string & operationHandle) {
	MDM::SetAlertState result(operationHandle, ConvertToCDM::convert(state));
	return result;
}

MDM::SetAlertState createRequestMessage(const AlertSystemState & state, const std::string & operationHandle) {
	MDM::SetAlertState result(operationHandle, ConvertToCDM::convert(state));
	return result;
}

MDM::SetString createRequestMessage(const EnumStringMetricState & state, const std::string & operationHandle) {
	MDM::SetString result(operationHandle, state.getMetricValue().getValue());
	return result;
}

MDM::SetAlertState createRequestMessage(const LimitAlertConditionState & state, const std::string & operationHandle) {
	MDM::SetAlertState result(operationHandle, ConvertToCDM::convert(state));
	return result;
}

MDM::SetValue createRequestMessage(const NumericMetricState & state, const std::string & operationHandle) {
	MDM::SetValue result(operationHandle, state.getMetricValue().getValue());
	return result;
}

MDM::SetString createRequestMessage(const StringMetricState & state, const std::string & operationHandle) {
	MDM::SetString result(operationHandle, state.getMetricValue().getValue());
	return result;
}

MDM::Activate createRequestMessage(const std::string & operationHandle) {
	MDM::Activate result(operationHandle);
	return result;
}

MDM::SetContextState createRequestMessage(const LocationContextState & state, const std::string & operationHandle) {
	MDM::SetContextState result(operationHandle);
	result.ProposedContextState().push_back(ConvertToCDM::convert(state));
	return result;
}


MDM::SetContextState createRequestMessage(const PatientContextState & state, const std::string & operationHandle) {
	MDM::SetContextState result(operationHandle);
	result.ProposedContextState().push_back(ConvertToCDM::convert(state));
	return result;
}

MDM::SetContextState createRequestMessage(const EnsembleContextState & state, const std::string & operationHandle) {
	MDM::SetContextState result(operationHandle);
	result.ProposedContextState().push_back(ConvertToCDM::convert(state));
	return result;
}

MDM::SetContextState createRequestMessage(const OperatorContextState & state, const std::string & operationHandle) {
	MDM::SetContextState result(operationHandle);
	result.ProposedContextState().push_back(ConvertToCDM::convert(state));
	return result;
}

MDM::SetContextState createRequestMessage(const WorkflowContextState & state, const std::string & operationHandle) {
	MDM::SetContextState result(operationHandle);
	result.ProposedContextState().push_back(ConvertToCDM::convert(state));
	return result;
}

OSCPConsumer::OSCPConsumer(const OSELib::DPWS::DeviceDescription & deviceDescription) :
		WithLogger(OSELib::Log::OSCPCONSUMER),
		connectionLostHandler(nullptr),
		contextStateChangedHandler(nullptr),
		subscriptionLostHandler(nullptr),
		lastKnownMDIBVersion(0),
		_deviceDescription(deviceDescription)
{
	connected = false;
	for (int i = 0; i < OSCLibrary::getInstance().getNumberOfReattemptsWithAnotherPort(); i++) {
		const int port(OSCLibrary::getInstance().extractFreePort());
		try {
			_adapter = std::unique_ptr<OSELibConsumerAdapter>(new OSELibConsumerAdapter(*this, port, _deviceDescription));
			_adapter->start();
			connected = true;
			break;
		} catch (const Poco::Net::NetException & e) {
			log_error([&] { return "Exception: " + std::string(e.what()) + " Retrying with other port."; });
			OSCLibrary::getInstance().returnPortToPool(port);
		} catch (const std::runtime_error & e) {
			log_error([&] {return "Exception: " + std::string(e.what()); });
		}
	}
	if (!connected) {
		log_error([&] { return "Connecting to " + deviceDescription.getEPR() + " failed after " + std::to_string(OSCLibrary::getInstance().getNumberOfReattemptsWithAnotherPort()) + " attempts."; });
	}

}

OSCPConsumer::~OSCPConsumer() {

    for (auto & fis : fisMap) {
    	fis.second->consumer = nullptr;
    }
    if (OSCLibrary::getInstance().isInitialized() && _adapter)
    {
        log_error([] { return "OSCPConsumer deleted before disconnected!"; });
    	disconnect();
    }
}

void OSCPConsumer::disconnect() {
	if (_adapter) {
		_adapter->stop();
		_adapter.reset();
	}
}

void OSCPConsumer::setConnectionLostHandler(OSCPConsumerConnectionLostHandler * handler) {
    connectionLostHandler = handler;
}

void OSCPConsumer::setContextStateChangedHandler(OSCPConsumerSystemContextStateChangedHandler * handler) {
    Poco::Mutex::ScopedLock lock(eventMutex);
	contextStateChangedHandler = handler;
	if (_adapter) {
		_adapter->subscribeEvents();
	}
}

void OSCPConsumer::setSubscriptionLostHandler(OSCPConsumerSubscriptionLostHandler * handler) {
    subscriptionLostHandler = handler;
}

void OSCPConsumer::onConnectionLost() {
    if (connectionLostHandler != nullptr) {
        connectionLostHandler->onConnectionLost();
    }
}

void OSCPConsumer::onSubscriptionLost() {
    if (subscriptionLostHandler != nullptr) {
        subscriptionLostHandler->onSubscriptionLost();
    }
}

MdibContainer OSCPConsumer::getMdib() {
	if (!requestMdib()) {
		onConnectionLost();
	}
    return *mdib;
}

MdDescription OSCPConsumer::getMdDescription() {
    const MDM::GetMdDescription request;
    auto response(_adapter->invoke(request));

	if (response == nullptr) {
        log_error([] { return "GetMdDescription request failed!"; });
		onConnectionLost();
		return MdDescription();
	}

	const MdDescription description(ConvertFromCDM::convert(response->MdDescription()));

	// refresh cashed version
	mdib->setMdDescription(description);
	if (response->MdibVersion().present()) {
		mdib->setMdibVersion(response->MdibVersion().get());
	}

    return description;
}

MdDescription OSCPConsumer::getCachedMdDescription() {
	if (mdib) {
		return mdib->getMdDescription();
	} else {
		return MdDescription();
	}
}

MdState OSCPConsumer::getMdState() {
    const MDM::GetMdState request;
    std::unique_ptr<const MDM::GetMdStateResponse> response(_adapter->invoke(request));

	if (response == nullptr) {
		log_error([] { return "GetMdState request failed!"; });
		onConnectionLost();
		return MdState();
	}

    return ConvertFromCDM::convert(response->MdState());
}

bool OSCPConsumer::unregisterFutureInvocationListener(int transactionId) {
	Poco::Mutex::ScopedLock lock(transactionMutex);
	return fisMap.erase(transactionId) == 1;
}

bool OSCPConsumer::registerStateEventHandler(SDCConsumerOperationInvokedHandler * handler) {
    Poco::Mutex::ScopedLock lock(eventMutex);
	eventHandlers[handler->getDescriptorHandle()] = handler;
	if (_adapter) {
		_adapter->subscribeEvents();
	}
	return true;
}

bool OSCPConsumer::unregisterStateEventHandler(SDCConsumerOperationInvokedHandler * handler) {
	Poco::Mutex::ScopedLock lock(eventMutex);
	eventHandlers.erase(handler->getDescriptorHandle());

	if (_adapter && eventHandlers.empty() && contextStateChangedHandler == nullptr) {
		_adapter->unsubscribeEvents();
	}

    return true;
}

bool OSCPConsumer::requestMdib() {
	std::unique_ptr<const MDM::GetMdibResponse> response(requestCDMMdib());
	if (response == nullptr) {
		return false;
	}

	Poco::Mutex::ScopedLock lock(requestMutex);
	mdib.reset(new MdibContainer());
	mdib->setMdState(ConvertFromCDM::convert(response->Mdib().MdState().get()));
	if (response->Mdib().MdDescription().present()) {
		mdib->setMdDescription(ConvertFromCDM::convert(response->Mdib().MdDescription().get()));
	}

	if (response->MdibVersion().present()) {
		mdib->setMdibVersion(response->MdibVersion().get());
	}

	return true;
}

std::unique_ptr<MDM::GetMdibResponse> OSCPConsumer::requestCDMMdib() {
    const MDM::GetMdib request;
    auto response(_adapter->invoke(request));
    return response;
}

std::string OSCPConsumer::requestRawMdib() {
	std::unique_ptr<const MDM::GetMdibResponse> response(requestCDMMdib());
	if (response == nullptr) {
		log_error([] { return "MDIB request failed!"; });
		return "";
	} else {
		const xml_schema::Flags xercesFlags(xml_schema::Flags::dont_validate | xml_schema::Flags::no_xml_declaration | xml_schema::Flags::dont_initialize);
		std::ostringstream result;
		xml_schema::NamespaceInfomap map;

		CDM::MdibContainer(result, response->Mdib(), map, OSELib::XML_ENCODING, xercesFlags);
		return result.str();
	}
}

// TODO: delete commitStateImpl() use one template class, use traits for Metrices: https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Member_Detector
InvocationState OSCPConsumer::commitState(const EnumStringMetricState & state, FutureInvocationState & fis) {
	if (!state.hasMetricValue()) {
		return InvocationState::Fail;
	}
	if (!state.getMetricValue().hasValue()) {
		return InvocationState::Fail;
	}
	return commitStateImpl<OSELib::OSCP::SetStringTraits>(state, fis);
}

InvocationState OSCPConsumer::commitState(const NumericMetricState & state, FutureInvocationState & fis) {
	if (!state.hasMetricValue()) {
		return InvocationState::Fail;
	}
	if (!state.getMetricValue().hasValue()) {
		return InvocationState::Fail;
	}
	return commitStateImpl<OSELib::OSCP::SetValueTraits>(state, fis);
}

InvocationState OSCPConsumer::commitState(const StringMetricState & state, FutureInvocationState & fis) {
	if (!state.hasMetricValue()) {
		return InvocationState::Fail;
	}
	if (!state.getMetricValue().hasValue()) {
		return InvocationState::Fail;
	}
	return commitStateImpl<OSELib::OSCP::SetStringTraits>(state, fis);
}

InvocationState OSCPConsumer::commitState(const LocationContextState & state, FutureInvocationState & fis) {
	return commitStateImpl<OSELib::OSCP::SetContextStateTraits>(state, fis);
}

InvocationState OSCPConsumer::commitState(const EnsembleContextState & state, FutureInvocationState & fis) {
	return commitStateImpl<OSELib::OSCP::SetContextStateTraits>(state, fis);
}

InvocationState OSCPConsumer::commitState(const OperatorContextState & state, FutureInvocationState & fis) {
	return commitStateImpl<OSELib::OSCP::SetContextStateTraits>(state, fis);
}

InvocationState OSCPConsumer::commitState(const PatientContextState & state, FutureInvocationState & fis) {
	return commitStateImpl<OSELib::OSCP::SetContextStateTraits>(state, fis);
}

InvocationState OSCPConsumer::commitState(const WorkflowContextState & state, FutureInvocationState & fis) {
	return commitStateImpl<OSELib::OSCP::SetContextStateTraits>(state, fis);
}

InvocationState OSCPConsumer::commitState(const AlertSystemState & state, FutureInvocationState & fis) {
	return commitStateImpl<OSELib::OSCP::SetAlertStateTraits>(state, fis);
}

InvocationState OSCPConsumer::commitState(const AlertSignalState & state, FutureInvocationState & fis) {
	return commitStateImpl<OSELib::OSCP::SetAlertStateTraits>(state, fis);
}

InvocationState OSCPConsumer::commitState(const AlertConditionState & state, FutureInvocationState & fis) {
	return commitStateImpl<OSELib::OSCP::SetAlertStateTraits>(state, fis);
}

InvocationState OSCPConsumer::commitState(const LimitAlertConditionState & state, FutureInvocationState & fis) {
	return commitStateImpl<OSELib::OSCP::SetAlertStateTraits>(state, fis);
}

InvocationState OSCPConsumer::commitState(const AlertSystemState & state) {
	FutureInvocationState dummy;
	return commitState(state, dummy);
}

InvocationState OSCPConsumer::commitState(const AlertSignalState & state) {
	FutureInvocationState dummy;
	return commitState(state, dummy);
}

InvocationState OSCPConsumer::commitState(const AlertConditionState & state) {
	FutureInvocationState dummy;
	return commitState(state, dummy);
}

InvocationState OSCPConsumer::commitState(const LimitAlertConditionState & state) {
	FutureInvocationState dummy;
	return commitState(state, dummy);
}

InvocationState OSCPConsumer::commitState(const EnumStringMetricState & state) {
	FutureInvocationState dummy;
	return commitState(state, dummy);
}

InvocationState OSCPConsumer::commitState(const NumericMetricState & state) {
	FutureInvocationState dummy;
	return commitState(state, dummy);
}

InvocationState OSCPConsumer::commitState(const StringMetricState & state) {
	FutureInvocationState dummy;
	return commitState(state, dummy);
}

InvocationState OSCPConsumer::commitState(const LocationContextState & state) {
	FutureInvocationState dummy;
	return commitState(state, dummy);
}

InvocationState OSCPConsumer::commitState(const EnsembleContextState & state) {
	FutureInvocationState dummy;
	return commitState(state, dummy);
}

InvocationState OSCPConsumer::commitState(const OperatorContextState & state) {
	FutureInvocationState dummy;
	return commitState(state, dummy);
}

InvocationState OSCPConsumer::commitState(const PatientContextState & state) {
	FutureInvocationState dummy;
	return commitState(state, dummy);
}

InvocationState OSCPConsumer::commitState(const WorkflowContextState & state) {
	FutureInvocationState dummy;
	return commitState(state, dummy);
}

template<class OperationTraits, class StateType>
InvocationState OSCPConsumer::commitStateImpl(const StateType & state, FutureInvocationState & fis) {

	if (state.getDescriptorHandle().empty()) {
		log_error([] { return "Commit failed: descriptor handle is empty!"; });
		return InvocationState::Fail;
	}

	const MdDescription mddescription(getCachedMdDescription());

	typename StateType::DescriptorType descriptor;
	if (!mddescription.findDescriptor(state.getDescriptorHandle(), descriptor)) {
		log_error([] { return "Could not find descriptor handle in getMdDescriptionResponse. Resolving matching set operations failed!"; });
		return InvocationState::Fail;
	}


	// Check for operation that targets the descriptor for this state.
	std::string operationHandle(mddescription.getFirstOperationHandleForOperationTarget(state.getDescriptorHandle()));



	if (operationHandle.empty()) {
		// No operation targeting this state was found.
		// check for operation that targets state
		operationHandle = mddescription.getFirstOperationHandleForOperationTarget(state.getDescriptorHandle());
	}
	if (operationHandle.empty()) {
		log_error([&] { return "Commit failed: No set operation found to modify given state! State has descriptor handle " + state.getDescriptorHandle(); });
		return InvocationState::Fail;
	}

	const typename OperationTraits::Request request(createRequestMessage(state, operationHandle));
	std::unique_ptr<const typename OperationTraits::Response> response(_adapter->invoke(request));
	if (response == nullptr) {
		return InvocationState::Fail;
	} else {
		handleInvocationState(response->InvocationInfo().TransactionId(), fis);
		return ConvertFromCDM::convert(response->InvocationInfo().InvocationState());
	}
}

void OSCPConsumer::handleInvocationState(int transactionId, FutureInvocationState & fis) {
	// Put user future state into map
	Poco::Mutex::ScopedLock lock(transactionMutex);
	fis.transactionId = transactionId;
	fisMap[fis.transactionId] = &fis;
	fis.consumer = this;
	// Dequeue possible intermediate events
    while (transactionQueue.size() > 0) {
    	const TransactionState ts(transactionQueue.front());
    	transactionQueue.pop_front();
	    if (fisMap.find(ts.transactionId) != fisMap.end()) {
	    	fisMap[ts.transactionId]->setEvent(ts.invocationState);
	    }
    }
}

InvocationState OSCPConsumer::activate(const std::string & handle) {
	FutureInvocationState dummy;
	return activate(handle, dummy);
}

InvocationState OSCPConsumer::activate(const std::string & handle, FutureInvocationState & fis) {

    const MdDescription mdd(getCachedMdDescription());

	const MDM::Activate request(createRequestMessage(handle));
	std::unique_ptr<const MDM::ActivateResponse> response(_adapter->invoke(request));
	if (response == nullptr) {
		return InvocationState::Fail;
	} else {
		handleInvocationState(response->InvocationInfo().TransactionId(), fis);
		return ConvertFromCDM::convert(response->InvocationInfo().InvocationState());
	}
}

//// specialization needed for API
template std::unique_ptr<AlertConditionState> OSCPConsumer::requestState<AlertConditionState>(const std::string & handle);
template std::unique_ptr<AlertSignalState> OSCPConsumer::requestState<AlertSignalState>(const std::string & handle);
template std::unique_ptr<AlertSystemState> OSCPConsumer::requestState<AlertSystemState>(const std::string & handle);
template std::unique_ptr<ClockState> OSCPConsumer::requestState<ClockState>(const std::string & handle);
template std::unique_ptr<EnsembleContextState> OSCPConsumer::requestState<EnsembleContextState>(const std::string & handle);
template std::unique_ptr<EnumStringMetricState> OSCPConsumer::requestState<EnumStringMetricState>(const std::string & handle);
template std::unique_ptr<LimitAlertConditionState> OSCPConsumer::requestState<LimitAlertConditionState>(const std::string & handle);
template std::unique_ptr<LocationContextState> OSCPConsumer::requestState<LocationContextState>(const std::string & handle);
template std::unique_ptr<NumericMetricState> OSCPConsumer::requestState<NumericMetricState>(const std::string & handle);
template std::unique_ptr<OperatorContextState> OSCPConsumer::requestState<OperatorContextState>(const std::string & handle);
template std::unique_ptr<PatientContextState> OSCPConsumer::requestState<PatientContextState>(const std::string & handle);
template std::unique_ptr<StringMetricState> OSCPConsumer::requestState<StringMetricState>(const std::string & handle);
template std::unique_ptr<WorkflowContextState> OSCPConsumer::requestState<WorkflowContextState>(const std::string & handle);


// TODO: implement and test! missing states -> RealTimeSampleArrayMetricState, DistributionSampleArrayMetricState

template<class TStateType>
std::unique_ptr<TStateType> OSCPConsumer::requestState(const std::string & handle) {

    MDM::GetMdState request;
    request.HandleRef().push_back(handle);

    auto response (_adapter->invoke(request));
    if (response == nullptr) {
    	log_error([&] { return "requestState failed: invoke of adapter returned nullptr for handle "  + handle; });
    	return nullptr;
    }

	const CDM::MdState::StateSequence & resultStates(response->MdState().State());
	if (resultStates.empty()) {
		log_error([&] { return "requestState failed: Got no response object for handle "  + handle; });
		return nullptr;
	} else if (resultStates.size() > 1) {
		log_error([&] { return "requestState failed: Got too many response objects for handle " + handle + std::to_string(resultStates.size()); });
		return nullptr;
	}

	// take first element
	try {
		const typename TStateType::WrappedType & resultState(dynamic_cast<const typename TStateType::WrappedType &>(resultStates.front()));
		std::unique_ptr<TStateType> pReturnState(new TStateType(ConvertFromCDM::convert(resultState)));
		return std::move(pReturnState);
	} catch (...) {
		log_error([&] { return "requestState failed: Types mismatch of returned object for handle " + handle; });
		return nullptr;
	}
	return nullptr;
}

template<typename T> void OSCPConsumer::onStateChanged(const T & state) {
    Poco::Mutex::ScopedLock lock(eventMutex);
    std::map<std::string, SDCConsumerOperationInvokedHandler *>::iterator it = eventHandlers.find(state.getDescriptorHandle());
    if (it != eventHandlers.end()) {
    	if (SDCConsumerMDStateHandler<T> * handler = dynamic_cast<SDCConsumerMDStateHandler<T> *>(it->second)) {
        	handler->onStateChanged(state);
    	}
    }
}

//template<typename T> void OSCPConsumer::onMultiStateChanged(const T & state) {
//    Poco::Mutex::ScopedLock lock(eventMutex);
//	std::map<std::string, SDCConsumerOperationInvokedHandler *>::iterator it = eventHandlers.find(state.getHandle());
//	if (it != eventHandlers.end()) {
//		if (SDCConsumerMDStateHandler<T> * handler = dynamic_cast<SDCConsumerMDStateHandler<T> *>(it->second)) {
//			handler->onStateChanged(state);
//		}
//	}
//}

// metrices
template void OSCPConsumer::onStateChanged(const EnumStringMetricState & state);
template void OSCPConsumer::onStateChanged(const NumericMetricState & state);
template void OSCPConsumer::onStateChanged(const StringMetricState & state);
template void OSCPConsumer::onStateChanged(const RealTimeSampleArrayMetricState & state);
template void OSCPConsumer::onStateChanged(const DistributionSampleArrayMetricState & state);
// alerts
template void OSCPConsumer::onStateChanged(const AlertSystemState & state);
template void OSCPConsumer::onStateChanged(const AlertSignalState & state);
template void OSCPConsumer::onStateChanged(const AlertConditionState & state);
template void OSCPConsumer::onStateChanged(const LimitAlertConditionState & state);
// TODO: change! context states are multi states
//template void OSCPConsumer::onMultiStateChanged(const WorkflowContextState & state);
//template void OSCPConsumer::onMultiStateChanged(const PatientContextState & state);
//template void OSCPConsumer::onMultiStateChanged(const LocationContextState& state);
//template void OSCPConsumer::onMultiStateChanged(const OperatorContextState & state);
//template void OSCPConsumer::onMultiStateChanged(const MeansContextState & state);
//template void OSCPConsumer::onMultiStateChanged(const EnsembleContextState & state);
// as well as states referenced by a descriptor
template void OSCPConsumer::onStateChanged(const WorkflowContextState & state);
template void OSCPConsumer::onStateChanged(const PatientContextState & state);
template void OSCPConsumer::onStateChanged(const LocationContextState& state);
template void OSCPConsumer::onStateChanged(const OperatorContextState & state);
template void OSCPConsumer::onStateChanged(const MeansContextState & state);
template void OSCPConsumer::onStateChanged(const EnsembleContextState & state);

void OSCPConsumer::onOperationInvoked(const OperationInvocationContext & oic, InvocationState is) {
    Poco::Mutex::ScopedLock lock(eventMutex);


    // If operation handle belongs to ActivateOperationDescriptor, use operation handle as target handle in case of operation invoked events!
    const MdDescription mdd(getCachedMdDescription());
    std::string targetHandle;
    const std::vector<MdsDescriptor> mdss(mdd.collectAllMdsDescriptors());
    for (const auto & mds : mdss) {
    	const std::unique_ptr<CDM::MdsDescriptor> mds_uniquePtr(ConvertToCDM::convert(mds));
		if (!mds_uniquePtr->Sco().present()) {
			continue;
		}
		for (const auto & operation : mds_uniquePtr->Sco().get().Operation()) {
			if (operation.Handle() == oic.operationHandle && dynamic_cast<const CDM::ActivateOperationDescriptor *>(&operation) != nullptr) {
				targetHandle = oic.operationHandle;
				break;
			}
		}
		if (!targetHandle.empty())
			break;
    }

    // All other operation descriptor cases
    if (targetHandle.empty())
    	targetHandle = mdd.getOperationTargetForOperationHandle(oic.operationHandle);
    std::map<std::string, SDCConsumerOperationInvokedHandler *>::iterator it = eventHandlers.find(targetHandle);
    if (it != eventHandlers.end()) {
        it->second->onOperationInvoked(oic, is);
    }

    // Notify user future invocation state events
    Poco::Mutex::ScopedLock transactionLock(transactionMutex);
    if (fisMap.find(oic.transactionId) != fisMap.end()) {
    	fisMap[oic.transactionId]->setEvent(is);
    }
    // Queue to check intermediate events during commits
    transactionQueue.push_back(TransactionState(oic.transactionId, is));
}

std::string OSCPConsumer::getEndpointReference() {
	return _deviceDescription.getEPR();
}

unsigned long long int OSCPConsumer::getLastKnownMdibVersion() {
	Poco::Mutex::ScopedLock lock(mdibVersionMutex);
	unsigned long long int result = lastKnownMDIBVersion;
	return result;
}

void OSCPConsumer::updateLastKnownMdibVersion(unsigned long long int newVersion) {
	Poco::Mutex::ScopedLock lock(mdibVersionMutex);
	if (lastKnownMDIBVersion < newVersion) {
		lastKnownMDIBVersion = newVersion;
	}
}

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
