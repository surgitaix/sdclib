/*
 * SDCParticipantMDStateForwarder.h
 *
 *  Created on: Apr 10, 2019
 *      Author: rosenau
 */

#ifndef EXAMPLES_ABSTRACTCONSUMERSIMULATOR_SDCPARTICIPANTMDSTATEFORWARDER_H_
#define EXAMPLES_ABSTRACTCONSUMERSIMULATOR_SDCPARTICIPANTMDSTATEFORWARDER_H_

#include <functional>

#include "SDCLib/Data/SDC/SDCConsumerMDStateHandler.h"
#include "SDCLib/Data/SDC/SDCProviderMDStateHandler.h"
#include "SDCLib/Data/SDC/MDIB/custom/OperationInvocationContext.h"
#include "SDCLib/Data/SDC/MDIB/StringMetricState.h"
#include "SDCLib/Data/SDC/MDIB/StringMetricValue.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricValue.h"
#include "SDCLib/Data/SDC/MDIB/MetricQuality.h"
#include "SDCLib/Data/SDC/SDCProviderActivateOperationHandler.h"
#include "SDCLib/Data/SDC/MDIB/RealTimeSampleArrayMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/RealTimeSampleArrayMetricState.h"
#include "SDCLib/Data/SDC/FutureInvocationState.h"
#include "AbstractConsumer.h"

#include "NamigConvention.h"

namespace SDCLib {
namespace Data {
namespace SDC {

namespace ACS {

template<typename TState>
class SDCParticipantMDStateForwarder : public SDCConsumerMDStateHandler<TState>, public SDCProviderMDStateHandler<TState> {
public:
	SDCParticipantMDStateForwarder(const std::string descriptorHandle) : SDCConsumerMDStateHandler<TState>(descriptorHandle), SDCProviderMDStateHandler<TState>(descriptorHandle) {}
	virtual ~SDCParticipantMDStateForwarder() = default;

	void onStateChanged(const TState & state) override {
		SDCProviderStateHandler::updateState(state);
	}

    InvocationState onStateChangeRequest(const TState & , const OperationInvocationContext & oic) override {
    	// extract information from the incoming operation
    	SDCProviderStateHandler::notifyOperationInvoked(oic, InvocationState::Start);
    	return InvocationState::Fail;
    }
};


class SDCParticipantNumericMetricStateForwarder : public SDCParticipantMDStateForwarder<NumericMetricState>
{
public:
	SDCParticipantNumericMetricStateForwarder(const std::string descriptorHandle) : SDCParticipantMDStateForwarder(descriptorHandle) {

	}
	NumericMetricState getInitialState() override
	{
		NumericMetricState numericMetricState(SDCProviderMDStateHandler::descriptorHandle);
		numericMetricState.setActivationState(ComponentActivation::On);
		numericMetricState.setMetricValue(NumericMetricValue(MetricQuality(MeasurementValidity::Vld)).setValue(0));
		return numericMetricState;
	}

	void onStateChanged(const NumericMetricState & state)  {
		double val = state.getMetricValue().getValue();
		std::cout << "Consumer: Received value changed of " << this->SDCProviderStateHandler::getDescriptorHandle() << ": " << val << std::endl;
		SDCProviderStateHandler::updateState(state);
	}
};

class SDCParticipantNumericMetricSetStateForwarder : public SDCParticipantMDStateForwarder<NumericMetricState>
{
public:
	SDCParticipantNumericMetricSetStateForwarder(const std::string descriptorHandle) : SDCParticipantMDStateForwarder(descriptorHandle) {

	}
	NumericMetricState getInitialState() override
	{
		NumericMetricState numericMetricState(SDCProviderMDStateHandler::descriptorHandle);
		numericMetricState.setActivationState(ComponentActivation::On);
		numericMetricState.setMetricValue(NumericMetricValue(MetricQuality(MeasurementValidity::Vld)).setValue(0));
		return numericMetricState;
	}
	InvocationState onStateChangeRequest(const NumericMetricState & state , const OperationInvocationContext & oic) override {
		// extract information from the incoming operation
		SDCProviderStateHandler::notifyOperationInvoked(oic, InvocationState::Start);
		FutureInvocationState fis;
		getParentConsumer().commitState(state, fis);
		auto providerUpdatedState = getParentConsumer().requestState<NumericMetricState>(state.getDescriptorHandle());
		if(state.getMetricValue().getValue() == providerUpdatedState->getMetricValue().getValue())
		{
			return InvocationState::Fin;
		}
		return InvocationState::Fail;
	}
};

class SDCParticipantRealTimeSampleArrayMetricStateForwarder : public SDCParticipantMDStateForwarder<RealTimeSampleArrayMetricState> {
public:
	SDCParticipantRealTimeSampleArrayMetricStateForwarder(const std::string descriptorHandle) : SDCParticipantMDStateForwarder(descriptorHandle) {}

	RealTimeSampleArrayMetricState getInitialState() override {
		RealTimeSampleArrayMetricState realTimeSampleArrayState(SDCProviderMDStateHandler::descriptorHandle);
		realTimeSampleArrayState.setActivationState(ComponentActivation::On);
		return realTimeSampleArrayState;
	}

};

class SDCParticipantStringMetricStateForwarder : public SDCParticipantMDStateForwarder<StringMetricState> {
public:
	SDCParticipantStringMetricStateForwarder(const std::string descriptorHandle) : SDCParticipantMDStateForwarder(descriptorHandle) {}

	StringMetricState getInitialState() override{
		StringMetricState stringMetricState(SDCProviderMDStateHandler::descriptorHandle);
		stringMetricState.setMetricValue(StringMetricValue(MetricQuality(MeasurementValidity::Vld)).setValue(""));
		return stringMetricState;
	}
};

class SDCParticipantStringMetricStateSetForwarder : public SDCParticipantMDStateForwarder<StringMetricState> {
public:
	SDCParticipantStringMetricStateSetForwarder(const std::string descriptorHandle) : SDCParticipantMDStateForwarder(descriptorHandle) {}

	StringMetricState getInitialState() override{
		StringMetricState stringMetricState(SDCProviderMDStateHandler::descriptorHandle);
		stringMetricState.setMetricValue(StringMetricValue(MetricQuality(MeasurementValidity::Vld)).setValue(""));
		return stringMetricState;
	}

	InvocationState onStateChangeRequest(const StringMetricState & state , const OperationInvocationContext & oic) override {
		// extract information from the incoming operation
		SDCProviderStateHandler::notifyOperationInvoked(oic, InvocationState::Start);
		FutureInvocationState fis;
		std::cout << "Setting " << SDCProviderMDStateHandler::descriptorHandle << " with " << state.getMetricValue().getValue() << std::endl;
		getParentConsumer().commitState(state, fis);
		auto providerUpdatedState = getParentConsumer().requestState<StringMetricState>(state.getDescriptorHandle());
		if(state.getMetricValue().getValue() == providerUpdatedState->getMetricValue().getValue())
		{
			return InvocationState::Fin;
		}
		return InvocationState::Fail;
	}
};

class SDCParticipantActivateForwarder : public SDCProviderActivateOperationHandler, public SDCConsumerOperationInvokedHandler {
public:
	SDCParticipantActivateForwarder(const std::string descriptorHandle) :
	SDCProviderActivateOperationHandler(descriptorHandle),
	SDCConsumerOperationInvokedHandler(descriptorHandle)
	{
	}

	InvocationState onActivateRequest(const OperationInvocationContext & oic) override {
		FutureInvocationState fis;
		SDCConsumerOperationInvokedHandler::getParentConsumer().activate(SDCConsumerOperationInvokedHandler::descriptorHandle, fis);
		std::cout << "Forwarding activate Request to DUT " << SDCConsumerOperationInvokedHandler::descriptorHandle << std::endl;
		//Todo once fis actually returns true or false use this to define the return value
		if(true)
		{
			return InvocationState::Fin;
		}
		return InvocationState::Fail;
	}
};

template<typename TState>
class SDCParticipantMDStateGetForwarder : public SDCProviderActivateOperationHandler, public SDCConsumerMDStateHandler<TState> {
public:
	SDCParticipantMDStateGetForwarder(const std::string descriptorHandle) :
		SDCProviderActivateOperationHandler(descriptorHandle + ACTIVATE_FOR_GET_OPERATION_ON_DUT_POSTFIX),
		SDCConsumerMDStateHandler<TState>(descriptorHandle + ACTIVATE_FOR_GET_OPERATION_ON_DUT_POSTFIX),
		activateDescriptorHandle(descriptorHandle + ACTIVATE_FOR_GET_OPERATION_ON_DUT_POSTFIX),
		targetDescriptorHandle(descriptorHandle)
	{

	}
	virtual ~SDCParticipantMDStateGetForwarder() = default;
	void onStateChanged(const TState & state) override {
	}

	InvocationState onActivateRequest(const OperationInvocationContext & oic) override {
		std::cout << "GetForwarder on " << targetDescriptorHandle << std::endl;
		auto p_State(SDCConsumerOperationInvokedHandler::getParentConsumer().template requestState< TState >(targetDescriptorHandle));
		if(p_State)
		{
			std::cout << "Updating State" << std::endl;
			SDCProviderActivateOperationHandler::getParentProvider().updateState(*p_State);
			return InvocationState::Fin;
		}
		else
		{
			std::cout << "Consumer could not find " << targetDescriptorHandle << " in MDIB" << std::endl;
		}
		return InvocationState::Fail;
	}
private:
	std::string activateDescriptorHandle;
	std::string targetDescriptorHandle;

};

class SDCParticipantGetMDIBCaller : public SDCProviderActivateOperationHandler, public SDCConsumerOperationInvokedHandler {
public:
	SDCParticipantGetMDIBCaller(const std::string descriptorHandle) :
		SDCProviderActivateOperationHandler(descriptorHandle + ACTIVATE_FOR_GET_OPERATION_ON_DUT_POSTFIX),
		SDCConsumerOperationInvokedHandler(descriptorHandle + ACTIVATE_FOR_GET_OPERATION_ON_DUT_POSTFIX),
		activateDescriptorHandle(descriptorHandle + ACTIVATE_FOR_GET_OPERATION_ON_DUT_POSTFIX),
		MDIBDescriptorHandle(descriptorHandle)
	{

	}
	virtual ~SDCParticipantGetMDIBCaller() = default;


	InvocationState onActivateRequest(const OperationInvocationContext & oic) override {
		std::string Mdib(SDCConsumerOperationInvokedHandler::getParentConsumer().requestRawMdib());
		auto stringMetricStates = SDCProviderActivateOperationHandler::getParentProvider().getMdState().findStringMetricStates();
		for(auto strMetricState : stringMetricStates)
		{
			std::cout << strMetricState.getDescriptorHandle() << std::endl;
			std::cout << MDIBDescriptorHandle << std::endl;
			if(strMetricState.getDescriptorHandle() == MDIBDescriptorHandle)
			{
				StringMetricState stringState(MDIBDescriptorHandle);
				StringMetricValue stringValue(MetricQuality(MeasurementValidity::Vld));
				stringValue.setValue(Mdib);
				stringState.setMetricValue(stringValue);
				parentProvider->updateState(stringState);
				return InvocationState::Fin;
			}
		}
		return InvocationState::Fail;
	}
private:
	std::string activateDescriptorHandle;
	std::string MDIBDescriptorHandle;
};

/**
 * @brief Activate state handle in the SDC context internally calling the function_ptr from the constructor as callback.
 */

class SDCParticipantActivateFunctionCaller : public SDCProviderActivateOperationHandler {
public:
	SDCParticipantActivateFunctionCaller(const std::string descriptorHandle, std::function<void()> callback) :
		SDCProviderActivateOperationHandler(descriptorHandle),
		callbackFunction(callback)
	{
	}

	SDCParticipantActivateFunctionCaller(const std::string descriptorHandle, std::function<bool()> callback) :
		SDCProviderActivateOperationHandler(descriptorHandle),
		boolCallbackFunction(callback)
	{
	}

	InvocationState onActivateRequest(const OperationInvocationContext & oic) override {
		if(callbackFunction)
			callbackFunction();
		else if(boolCallbackFunction)
		{
			if(!boolCallbackFunction())
			{
				return InvocationState::Fail;
			}
		}
		return InvocationState::Fin;
	}

private:
	std::function<void()> callbackFunction;
	std::function<bool()> boolCallbackFunction;
};

/**
 * @brief Set string metric state handler in the SDC context internally calling the function_ptr provided from the constructor as callback with the
 * set string.
 */
class SDCParticipantStringFunctionCaller : public SDCProviderMDStateHandler<StringMetricState> {
public:
	SDCParticipantStringFunctionCaller(const std::string descriptorHandle, std::function<void(const std::string)> callback) :
		SDCProviderMDStateHandler<StringMetricState>(descriptorHandle),
		callbackFunction(callback)
		{
		}

	StringMetricState getInitialState() override
	{
		StringMetricState initialState(descriptorHandle);
		StringMetricValue initialStringValue(MetricQuality(MeasurementValidity::Vld));
		initialStringValue.setValue("");
		initialState.setMetricValue(initialStringValue);
		return initialState;
	}

	InvocationState onStateChangeRequest(const StringMetricState &state, const OperationInvocationContext & oic) override
	{
		std::string functionParameterString = "";
		if(state.getMetricValue().getValue(functionParameterString))
		{
			std::cout << descriptorHandle << " called with " << functionParameterString << std::endl;
			if(functionParameterString == "")
			{
				return InvocationState::Fail;
			}
			callbackFunction(functionParameterString);
			return InvocationState::Fin;
		}
		return InvocationState::Fail;
	}

private:
	std::function<void(const std::string)> callbackFunction;
};

class SDCProviderStringMetricHandler : public SDCProviderMDStateHandler<StringMetricState> {
public:
	SDCProviderStringMetricHandler(const std::string descripotrHanlde) : SDCProviderMDStateHandler<StringMetricState>(descripotrHanlde){}

	StringMetricState getInitialState() override
	{
		StringMetricState initialState(descriptorHandle);
		StringMetricValue initialStringValue(MetricQuality(MeasurementValidity::Vld));
		initialStringValue.setValue("");
		initialState.setMetricValue(initialStringValue);
		return initialState;
	}

	InvocationState onStateChangeRequest(const StringMetricState &state, const OperationInvocationContext &oic) override
	{
		return InvocationState::Fail;
	}

	void updateStateValue(const std::string &str)
	{
		StringMetricState stringState(descriptorHandle);
		StringMetricValue stringValue(MetricQuality(MeasurementValidity::Vld));
		stringValue.setValue(str);
		stringState.setMetricValue(stringValue);
		parentProvider->updateState(stringState);
	}
};

} /* namespace ACS */
} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

#endif /* EXAMPLES_ABSTRACTCONSUMERSIMULATOR_SDCPARTICIPANTMDSTATEFORWARDER_H_ */
