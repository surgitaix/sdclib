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
 *  @Copyright (C) 2014, SurgiTAIX AG
 *  Author: besting, roehser
 */

#include "OSCLib/OSCLibrary.h"
#include "OSCLib/Cli/Client.h"
#include "OSCLib/Comm/DPWS/DPWS11Constants.h"
#include "OSCLib/Comm/Binding.h"
#include "OSCLib/Comm/DPWS/DPWS11WaveformStreamActionHandler.h"
#include "OSCLib/Dev/Device.h"
#include "OSCLib/Data/OperationHelpers.h"
#include "OSCLib/Data/OSCP/FutureInvocationState.h"
#include "OSCLib/Data/OSCP/OSCPConstants.h"
#include "OSCLib/Data/OSCP/OSCPConsumer.h"
#include "OSCLib/Data/OSCP/OSCPConsumerConnectionLostHandler.h"
#include "OSCLib/Data/OSCP/OSCPConsumerContextStateChangedHandler.h"
#include "OSCLib/Data/OSCP/OSCPConsumerEventHandler.h"
#include "OSCLib/Data/OSCP/OSCPConsumerAlertConditionStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPConsumerAlertSignalStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPConsumerAlertSystemStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPConsumerLimitAlertConditionStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPConsumerEnumStringMetricStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPConsumerNumericMetricStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPConsumerRealTimeSampleArrayMetricStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPConsumerStringMetricStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPConsumerSubscriptionLostHandler.h"
#include "OSCLib/Data/OSCP/OSCPPingManager.h"
#include "OSCLib/Data/OSCP/OSCPSubscriptionManager.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSystemDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSystemState.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSignalDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSignalState.h"
#include "OSCLib/Data/OSCP/MDIB/AlertConditionDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AlertConditionState.h"
#include "OSCLib/Data/OSCP/MDIB/ClockState.h"
#include "OSCLib/Data/OSCP/MDIB/ComponentState.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/EnumStringMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/EnumStringMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/LimitAlertConditionState.h"
#include "OSCLib/Data/OSCP/MDIB/LimitAlertConditionDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/LocationContextState.h"
#include "OSCLib/Data/OSCP/MDIB/PatientContextState.h"
#include "OSCLib/Data/OSCP/MDIB/EnsembleContextState.h"
#include "OSCLib/Data/OSCP/MDIB/OperationState.h"
#include "OSCLib/Data/OSCP/MDIB/OperatorContextState.h"
#include "OSCLib/Data/OSCP/MDIB/WorkflowContextState.h"
#include "OSCLib/Data/OSCP/MDIB/LocationContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/PatientContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/EnsembleContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/OperatorContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/WorkflowContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/HydraMDSDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/MDDescription.h"
#include "OSCLib/Data/OSCP/MDIB/MDState.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricValue.h"
#include "OSCLib/Data/OSCP/MDIB/OperationInvocationContext.h"
#include "OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/StringMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/StringMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/StringMetricValue.h"
#include "OSCLib/Data/OSCP/Operations/OSCPOperationTraits.h"
#include "OSCLib/Util/DebugOut.h"
#include "OSCLib/Util/FromString.h"
#include "OSCLib/Util/ToString.h"
#include <vector>
#include <memory>

#include "osdm.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

CDM::SetAlertState createRequestMessage(const AlertConditionState & state, const std::string & operationHandle) {
	CDM::SetAlertState result(operationHandle, ConvertToCDM::convert(state));
	return result;
}

CDM::SetAlertState createRequestMessage(const AlertSignalState & state, const std::string & operationHandle) {
	CDM::SetAlertState result(operationHandle, ConvertToCDM::convert(state));
	return result;
}

CDM::SetAlertState createRequestMessage(const AlertSystemState & state, const std::string & operationHandle) {
	CDM::SetAlertState result(operationHandle, ConvertToCDM::convert(state));
	return result;
}

CDM::SetString createRequestMessage(const EnumStringMetricState & state, const std::string & operationHandle) {
	CDM::SetString result(operationHandle, state.getObservedValue().getValue());
	return result;
}

CDM::SetAlertState createRequestMessage(const LimitAlertConditionState & state, const std::string & operationHandle) {
	CDM::SetAlertState result(operationHandle, ConvertToCDM::convert(state));
	return result;
}

CDM::SetValue createRequestMessage(const NumericMetricState & state, const std::string & operationHandle) {
	CDM::SetValue result(operationHandle, state.getObservedValue().getValue());
	return result;
}

CDM::SetString createRequestMessage(const StringMetricState & state, const std::string & operationHandle) {
	CDM::SetString result(operationHandle, state.getObservedValue().getValue());
	return result;
}

CDM::Activate createRequestMessage(const std::string & operationHandle) {
	CDM::Activate result(operationHandle);
	return result;
}

CDM::SetContextState createRequestMessage(const LocationContextState & state, const std::string & operationHandle) {
	CDM::SetContextState result(operationHandle);
	result.ProposedContextState().push_back(ConvertToCDM::convert(state));
	return result;
}


CDM::SetContextState createRequestMessage(const PatientContextState & state, const std::string & operationHandle) {
	CDM::SetContextState result(operationHandle);
	result.ProposedContextState().push_back(ConvertToCDM::convert(state));
	return result;
}

CDM::SetContextState createRequestMessage(const EnsembleContextState & state, const std::string & operationHandle) {
	CDM::SetContextState result(operationHandle);
	result.ProposedContextState().push_back(ConvertToCDM::convert(state));
	return result;
}

CDM::SetContextState createRequestMessage(const OperatorContextState & state, const std::string & operationHandle) {
	CDM::SetContextState result(operationHandle);
	result.ProposedContextState().push_back(ConvertToCDM::convert(state));
	return result;
}

CDM::SetContextState createRequestMessage(const WorkflowContextState & state, const std::string & operationHandle) {
	CDM::SetContextState result(operationHandle);
	result.ProposedContextState().push_back(ConvertToCDM::convert(state));
	return result;
}

OSCPConsumer::OSCPConsumer() :
		client(nullptr),
		pingMan(nullptr),
		subMan(nullptr),
		connectionLostHandler(nullptr),
		contextStateChangedHandler(nullptr),
		subscriptionLostHandler(nullptr),
		lastKnownMDIBVersion(0),
		connected(true)
{
}

OSCPConsumer::OSCPConsumer(std::shared_ptr<Cli::Client> client) :
		client(client),
		pingMan(nullptr),
		subMan(nullptr),
		connectionLostHandler(nullptr),
		contextStateChangedHandler(nullptr),
		subscriptionLostHandler(nullptr),
		lastKnownMDIBVersion(0),
		connected(true)
{
	std::shared_ptr<Comm::DPWS::DPWS11WaveformStreamActionHandler> wsah(new Comm::DPWS::DPWS11WaveformStreamActionHandler(*this));
    this->client->addDPWSActionHandler(ACTION_ORNET_STREAM, wsah); 
	initializePingManager();
	initializeCDMEventSinks();
}

OSCPConsumer::~OSCPConsumer() {
    for (auto & fis : fisMap) {
    	fis.second->consumer = nullptr;
    }
    if (OSCLibrary::getInstance()->isInitialized() && isValid())
    {
        disconnect();
        Util::DebugOut(Util::DebugOut::Error, "OSCPConsumer") << "OSCPConsumer deleted before disconnected!";
    }
}

void OSCPConsumer::disconnect() {
	{
		Poco::Mutex::ScopedLock lock(pingManMutex);
		if (pingMan) {
			pingMan->detachConsumer();
			OSCLibrary::getInstance()->scheduleTaskForShutdown(pingMan);
			pingMan.reset();
		}
	}
    if (client) {
        client->setClosing(true);
        removeCDMEventSinks();
        client->close();
    }
    OSCLibrary::getInstance()->unRegisterConsumer(this);
}

bool OSCPConsumer::isValid() {
    return client != nullptr && !client->isClosed() && OSCLibrary::getInstance()->getNetInterface()->isValidUnicastCallback(client.get());
}

std::string OSCPConsumer::getProviderXAddr() const {
    return client->getRemoteDevice()->getDefaultTransportAddr(OSCLib::Comm::DPWS::DPWS11);
}

void OSCPConsumer::setConnectionLostHandler(OSCPConsumerConnectionLostHandler * handler) {
    connectionLostHandler = handler;
}

void OSCPConsumer::setContextStateChangedHandler(OSCPConsumerContextStateChangedHandler * handler) {
    initializeCDMEventSinks();
    Poco::Mutex::ScopedLock lock(eventMutex);
	contextStateChangedHandler = handler;
}

void OSCPConsumer::setSubscriptionLostHandler(OSCPConsumerSubscriptionLostHandler * handler) {
    subscriptionLostHandler = handler;
}

void OSCPConsumer::onConnectionLost() {
	if (subMan)
		subMan->setError(true);
    if (connectionLostHandler != nullptr) {
        connectionLostHandler->onConnectionLost();
    }
}

void OSCPConsumer::onContextStateChanged(const std::vector<std::string> & handles) {
	if (contextStateChangedHandler != nullptr) {
		contextStateChangedHandler->onContextStateChanged(handles);
	}
}

void OSCPConsumer::onSubscriptionLost() {
    if (subscriptionLostHandler != nullptr) {
        subscriptionLostHandler->onSubscriptionLost();
    }
}

MDIBContainer OSCPConsumer::getMDIB() {
	if (!requestMDIB()) {
		onConnectionLost();
	}
    return *mdib;
}

MDDescription OSCPConsumer::getMDDescription() {
    const CDM::GetMDDescription request;
    std::unique_ptr<const CDM::GetMDDescriptionResponse> response(invokeImpl<GetMDDescriptionTraits>(request));

	if (response == nullptr) {
		onConnectionLost();
		Util::DebugOut(Util::DebugOut::Error, "OSCPConsumer") << "GetMDDescription request failed!";
		return MDDescription();
	}
	const MDDescription description(ConvertFromCDM::convert(response->StaticDescription()));

	// refresh cashed version
	mdib->setMDDescription(description);
	mdib->setMDIBVersion(response->MDIBVersion());

    return description;
}

MDDescription OSCPConsumer::getCachedMDDescription() {
	if (mdib) {
		return mdib->getMDDescription();
	} else {
		return MDDescription();
	}
}

MDState OSCPConsumer::getMDState() {
    const CDM::GetMDState request;
    std::unique_ptr<const CDM::GetMDStateResponse> response(invokeImpl<GetMDStateTraits>(request));

	if (response == nullptr) {
		onConnectionLost();
		Util::DebugOut(Util::DebugOut::Error, "OSCPConsumer") << "GetMDState request failed!";
		return MDState();
	}

    return ConvertFromCDM::convert(response->MDState());
}

void OSCPConsumer::initializePingManager() {
    Poco::Mutex::ScopedLock lock(pingManMutex);
    pingMan.reset(new OSCPPingManager(*this));
    if (isValid()) {
        pingMan->start();
    }
}

void OSCPConsumer::initializeCDMEventSinks() {
    Poco::Mutex::ScopedLock lock(subManMutex);
    if (subMan == nullptr) {
        subMan.reset(new OSCPSubscriptionManager(*this));
        if (isValid()) {
        	subMan->init();
            subMan->start();
        }
    }
}

void OSCPConsumer::removeCDMEventSinks() {
	Poco::Mutex::ScopedLock lock(subManMutex);
    if (subMan != nullptr) {
    	subMan->remove();
    	subMan->detachConsumer();
        OSCLibrary::getInstance()->scheduleTaskForShutdown(subMan);
        subMan.reset();
    }
}

bool OSCPConsumer::unregisterFutureInvocationListener(int transactionId) {
	Poco::Mutex::ScopedLock lock(transactionMutex);
	return fisMap.erase(transactionId) == 1;
}

bool OSCPConsumer::registerStateEventHandler(OSCPConsumerEventHandler * handler) {
    initializeCDMEventSinks();

    if (!subMan || !subMan->isInitialized()) {
        Util::DebugOut(Util::DebugOut::Error, "OSCPConsumer") << "Event registration failed due to prior missing event subscription!";
        return false;
    }

    if (dynamic_cast<OSCPConsumerRealTimeSampleArrayMetricStateHandler *>(handler) != nullptr) {
        client->enableStreaming();
    }

    Poco::Mutex::ScopedLock lock(eventMutex);
	eventHandlers[handler->getHandle()] = handler;
	return true;
}

bool OSCPConsumer::unregisterStateEventHandler(OSCPConsumerEventHandler * handler) {
    if (!isValid()) {
        return false;
    }
    bool cleanSinks(false);
    {
        Poco::Mutex::ScopedLock lock(eventMutex);
        eventHandlers.erase(handler->getHandle());
        cleanSinks = eventHandlers.empty();
    }
    if (cleanSinks) {
        removeCDMEventSinks();
    }
    return true;
}

bool OSCPConsumer::requestMDIB() {
	std::unique_ptr<const CDM::GetMDIBResponse> response(requestCDMMDIB());
	if (response == nullptr) {
		return false;
	}

	Poco::Mutex::ScopedLock lock(requestMutex);
	mdib.reset(new MDIBContainer());
	mdib->setMDState(ConvertFromCDM::convert(response->MDIB().MDState()));
	mdib->setMDDescription(ConvertFromCDM::convert(response->MDIB().MDDescription()));
	mdib->setMDIBVersion(response->MDIBVersion());
	return true;
}

std::unique_ptr<CDM::GetMDIBResponse> OSCPConsumer::requestCDMMDIB() {
    const CDM::GetMDIB request;
    std::unique_ptr<CDM::GetMDIBResponse> response(invokeImpl<GetMDIBTraits>(request));
    return response;
}

std::string OSCPConsumer::requestRawMDIB() {
	std::unique_ptr<const CDM::GetMDIBResponse> response(requestCDMMDIB());
	if (response == nullptr) {
		Util::DebugOut(Util::DebugOut::Error, "OSCPConsumer") << "MDIB request failed!";
		return "";
	} else {
		return CDM::ToString::convert(response->MDIB());
	}
}

InvocationState OSCPConsumer::commitState(const EnumStringMetricState & state, FutureInvocationState & fis) {
	if (!state.hasObservedValue()) {
		return InvocationState::FAILED;
	}
	if (!state.getObservedValue().hasValue()) {
		return InvocationState::FAILED;
	}
	return commitStateImpl<SetStringTraits>(state, fis);
}

InvocationState OSCPConsumer::commitState(const NumericMetricState & state, FutureInvocationState & fis) {
	if (!state.hasObservedValue()) {
		return InvocationState::FAILED;
	}
	if (!state.getObservedValue().hasValue()) {
		return InvocationState::FAILED;
	}
	return commitStateImpl<SetValueTraits>(state, fis);
}

InvocationState OSCPConsumer::commitState(const StringMetricState & state, FutureInvocationState & fis) {
	if (!state.hasObservedValue()) {
		return InvocationState::FAILED;
	}
	if (!state.getObservedValue().hasValue()) {
		return InvocationState::FAILED;
	}
	return commitStateImpl<SetStringTraits>(state, fis);
}

InvocationState OSCPConsumer::commitState(const LocationContextState & state, FutureInvocationState & fis) {
	return commitStateImpl<SetContextStateTraits>(state, fis);
}

InvocationState OSCPConsumer::commitState(const EnsembleContextState & state, FutureInvocationState & fis) {
	return commitStateImpl<SetContextStateTraits>(state, fis);
}

InvocationState OSCPConsumer::commitState(const OperatorContextState & state, FutureInvocationState & fis) {
	return commitStateImpl<SetContextStateTraits>(state, fis);
}

InvocationState OSCPConsumer::commitState(const PatientContextState & state, FutureInvocationState & fis) {
	return commitStateImpl<SetContextStateTraits>(state, fis);
}

InvocationState OSCPConsumer::commitState(const WorkflowContextState & state, FutureInvocationState & fis) {
	return commitStateImpl<SetContextStateTraits>(state, fis);
}

InvocationState OSCPConsumer::commitState(const AlertSystemState & state, FutureInvocationState & fis) {
	return commitStateImpl<SetAlertStateTraits>(state, fis);
}

InvocationState OSCPConsumer::commitState(const AlertSignalState & state, FutureInvocationState & fis) {
	return commitStateImpl<SetAlertStateTraits>(state, fis);
}

InvocationState OSCPConsumer::commitState(const AlertConditionState & state, FutureInvocationState & fis) {
	return commitStateImpl<SetAlertStateTraits>(state, fis);
}

InvocationState OSCPConsumer::commitState(const LimitAlertConditionState & state, FutureInvocationState & fis) {
	return commitStateImpl<SetAlertStateTraits>(state, fis);
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
		Util::DebugOut(Util::DebugOut::Error, "OSCPConsumer") << "Commit failed: descriptor handle is empty!";
		return InvocationState::FAILED;
	}

	const MDDescription mddescription(getCachedMDDescription());

	typename StateType::DescriptorType descriptor;
	if (!mddescription.findDescriptor(state.getDescriptorHandle(), descriptor)) {
		Util::DebugOut(Util::DebugOut::Error, "OSCPConsumer") << "Could not find descriptor handle in getMDDescriptionResponse. Resolving matching set operations failed.!";
		return InvocationState::FAILED;
	}

	// Check for operation that targets the descriptor for this state.
	std::string operationHandle(mddescription.getFirstOperationHandleForOperationTarget(state.getDescriptorHandle()));
	if (operationHandle.empty() && state.hasHandle()) {
		// No operation targeting this state was found.
		// check for operation that targets state
		operationHandle = mddescription.getFirstOperationHandleForOperationTarget(state.getHandle());
	}
	if (operationHandle.empty()) {
		Util::DebugOut(Util::DebugOut::Error, "OSCPConsumer") << "Commit failed: No set operation found to modify given state!";
		Util::DebugOut(Util::DebugOut::Error, "OSCPConsumer") << "State has descriptor handle " << state.getDescriptorHandle() << std::endl;
		return InvocationState::FAILED;
	}

	const typename OperationTraits::Request request(createRequestMessage(state, operationHandle));
	std::unique_ptr<const typename OperationTraits::Response> response(invokeImpl<OperationTraits>(request));
	if (response == nullptr) {
		return InvocationState::FAILED;
	} else {
		handleInvocationState(response->TransactionId(), fis);
		return ConvertFromCDM::convert(response->InvocationState());
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

    const MDDescription mdd(getCachedMDDescription());

	const CDM::Activate request(createRequestMessage(handle));
	std::unique_ptr<const CDM::ActivateResponse> response(invokeImpl<ActivateTraits>(request));
	if (response == nullptr) {
		return InvocationState::FAILED;
	} else {
		handleInvocationState(response->TransactionId(), fis);
		return ConvertFromCDM::convert(response->InvocationState());
	}
}

template<class OperationTraits>
std::unique_ptr<typename OperationTraits::Response> OSCPConsumer::invokeImpl(const typename OperationTraits::Request & request) {
	Parameter message("CDMRequest", Parameter::Type::CDM);
	message.setValue(CDM::ToString::convert(request));
	Parameters p;
	p.push_back(message);

	Poco::Mutex::ScopedLock lock(requestMutex);
	Parameters output;
	bool success = client->invokeSync(OperationTraits::RequestAction(), p, &output, 10000);
	if (success) {
		const std::string bodyContent(output[output.size() - 1].getValue());
		if (bodyContent.length() > 0) {
			std::unique_ptr<typename OperationTraits::Response> response(CDM::FromString::validateAndConvert<typename OperationTraits::Response>(bodyContent));
			if (response != nullptr) {
				updateLastKnownMDIBVersion(response->MDIBVersion());
			}
			return response;
		}
	}
	return nullptr;
}

bool OSCPConsumer::requestState(const std::string & handle, AlertConditionState & outState) {
	return requestStateImpl(handle, outState);
}

bool OSCPConsumer::requestState(const std::string & handle, AlertSignalState & outState) {
	return requestStateImpl(handle, outState);
}

bool OSCPConsumer::requestState(const std::string & handle, AlertSystemState & outState) {
	return requestStateImpl(handle, outState);
}

bool OSCPConsumer::requestState(const std::string & handle, ClockState & outState) {
	return requestStateImpl(handle, outState);
}

bool OSCPConsumer::requestState(const std::string & handle, ComponentState & outState) {
	return requestStateImpl(handle, outState);
}

bool OSCPConsumer::requestState(const std::string & handle, EnsembleContextState & outState) {
	return requestStateImpl(handle, outState);
}

bool OSCPConsumer::requestState(const std::string & handle, EnumStringMetricState & outState) {
	return requestStateImpl(handle, outState);
}

bool OSCPConsumer::requestState(const std::string & handle, LimitAlertConditionState & outState) {
	return requestStateImpl(handle, outState);
}

bool OSCPConsumer::requestState(const std::string & handle, LocationContextState & outState) {
	return requestStateImpl(handle, outState);
}

bool OSCPConsumer::requestState(const std::string & handle, NumericMetricState & outState) {
	return requestStateImpl(handle, outState);
}

bool OSCPConsumer::requestState(const std::string & handle, OperationState & outState) {
	return requestStateImpl(handle, outState);
}

bool OSCPConsumer::requestState(const std::string & handle, OperatorContextState & outState) {
	return requestStateImpl(handle, outState);
}

bool OSCPConsumer::requestState(const std::string & handle, PatientContextState & outState) {
	return requestStateImpl(handle, outState);
}

bool OSCPConsumer::requestState(const std::string & handle, StringMetricState & outState) {
	return requestStateImpl(handle, outState);
}

bool OSCPConsumer::requestState(const std::string & handle, WorkflowContextState & outState) {
	return requestStateImpl(handle, outState);
}

template<class OutStateType>
bool OSCPConsumer::requestStateImpl(const std::string & handle, OutStateType & outState) {

    CDM::GetMDState request;
    request.HandleRef().push_back(handle);

    std::unique_ptr<const CDM::GetMDStateResponse> response(invokeImpl<GetMDStateTraits>(request));
    if (response == nullptr) {
    	return false;
    }

	const CDM::MDState::StateSequence & resultStates(response->MDState().State());
	if (resultStates.empty()) {
		Util::DebugOut(Util::DebugOut::Error, "OSCPConsumer") << "requestState failed: Got no response object for handle " << handle << std::endl;
		return false;
	} else if (resultStates.size() > 1) {
		Util::DebugOut(Util::DebugOut::Error, "OSCPConsumer") << "requestState failed: Got too many response objects for handle " << handle << resultStates.size() << std::endl;
		return false;
	}

	// take first element
	try {
		const typename OutStateType::WrappedType & resultState(dynamic_cast<const typename OutStateType::WrappedType &>(resultStates.front()));
		const OutStateType castedType(ConvertFromCDM::convert(resultState));
		outState.copyFrom(castedType);
		return true;
	} catch (...) {
		Util::DebugOut(Util::DebugOut::Error, "OSCPConsumer") << "requestState failed: Types mismatch of returned object for handle " << handle << std::endl;
		return false;
	}

	return true;
}

template<typename T> void OSCPConsumer::onStateChanged(const T & state) {
    Poco::Mutex::ScopedLock lock(eventMutex);
    std::map<std::string, OSCPConsumerEventHandler *>::iterator it = eventHandlers.find(state.getDescriptorHandle());
    if (it != eventHandlers.end()) {
    	if (typename T::ConsumerHandlerType * handler = dynamic_cast<typename T::ConsumerHandlerType *>(it->second)) {
        	handler->onStateChanged(state);
    	}
    }
}

template void OSCPConsumer::onStateChanged(const EnumStringMetricState & state);
template void OSCPConsumer::onStateChanged(const NumericMetricState & state);
template void OSCPConsumer::onStateChanged(const StringMetricState & state);
template void OSCPConsumer::onStateChanged(const RealTimeSampleArrayMetricState & state);
template void OSCPConsumer::onStateChanged(const AlertSystemState & state);
template void OSCPConsumer::onStateChanged(const AlertSignalState & state);
template void OSCPConsumer::onStateChanged(const AlertConditionState & state);
template void OSCPConsumer::onStateChanged(const LimitAlertConditionState & state);

void OSCPConsumer::onOperationInvoked(const OperationInvocationContext & oic, InvocationState is) {
    Poco::Mutex::ScopedLock lock(eventMutex);
    // If operation handle belongs to ActivateOperationDescriptor, use operation handle as target handle in case of operation invoked events!

    const MDDescription mdd(getCachedMDDescription());
    std::string targetHandle;
    const std::vector<HydraMDSDescriptor> mdss(mdd.collectAllHydraMDSDescriptors());
    for (const auto & mds : mdss) {
    	const std::unique_ptr<CDM::HydraMDSDescriptor> hydraMDS(ConvertToCDM::convert(mds));
		if (!hydraMDS->SCO().present()) {
			continue;
		}
		for (const auto & operation : hydraMDS->SCO().get().Operation()) {
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
    std::map<std::string, OSCPConsumerEventHandler *>::iterator it = eventHandlers.find(targetHandle);
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
	return client->getRemoteDevice()->getEndpointReference().getAddress();
}

unsigned long long int OSCPConsumer::getLastKnownMDIBVersion() {
	Poco::Mutex::ScopedLock lock(mdibVersionMutex);
	unsigned long long int result = lastKnownMDIBVersion;
	return result;
}

void OSCPConsumer::updateLastKnownMDIBVersion(unsigned long long int newVersion) {
	Poco::Mutex::ScopedLock lock(mdibVersionMutex);
	if (lastKnownMDIBVersion < newVersion) {
		lastKnownMDIBVersion = newVersion;
	}
}

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
