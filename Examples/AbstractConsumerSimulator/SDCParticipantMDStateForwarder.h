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
#include "SDCLib/Data/SDC/SDCProviderActivateOperationHandler.h"
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

template<typename TState>
class SDCParticipantMDStateGetForwarder : public SDCProviderActivateOperationHandler, public SDCConsumerMDStateHandler<TState> {
	class AbstractConsumer;
public:
	SDCParticipantMDStateGetForwarder(const std::string descriptorHandle, const AbstractConsumer& observer) :
		SDCProviderActivateOperationHandler(descriptorHandle + ACTIVATE_FOR_GET_OPERATION_ON_DUT_POSTFIX),
		SDCConsumerMDStateHandler<TState>(descriptorHandle),
		activateDescriptorHandle(descriptorHandle + ACTIVATE_FOR_GET_OPERATION_ON_DUT_POSTFIX),
		consumerStateDescriptorHandle(descriptorHandle)
	{

	}
	virtual ~SDCParticipantMDStateGetForwarder() = default;
	void onStateChanged(const TState & state) override {
	}

	InvocationState onActivateRequest(const OperationInvocationContext & oic) override {
		auto p_State(SDCConsumerMDStateHandler<TState>::getParentConsumer().template requestState< TState >(consumerStateDescriptorHandle));
		if(p_State != nullptr)
		{
			SDCProviderActivateOperationHandler::getParentProvider().updateState(*p_State);
			return InvocationState::Fin;
		}
		return InvocationState::Fail;
	}
private:
	std::string activateDescriptorHandle;
	std::string consumerStateDescriptorHandle;
};

template<typename TState>
class SDCParticipantMDIBGetForwarder : public SDCProviderActivateOperationHandler, public SDCConsumerOperationInvokedHandler {
public:
	SDCParticipantMDIBGetForwarder(const std::string descriptorHandle) :
		SDCProviderActivateOperationHandler(descriptorHandle + ACTIVATE_FOR_GET_OPERATION_ON_DUT_POSTFIX),
		SDCConsumerOperationInvokedHandler(descriptorHandle),
		activateDescriptorHandle(descriptorHandle + ACTIVATE_FOR_GET_OPERATION_ON_DUT_POSTFIX),
		MDIBDescriptorHandle(descriptorHandle)
	{

	}
	virtual ~SDCParticipantMDIBGetForwarder() = default;
	void onStateChanged(const TState & state) override {
	}

	InvocationState onActivateRequest(const OperationInvocationContext & oic) override {
		std::string Mdib(SDCConsumerMDStateHandler<TState>::getParentConsumer().requestRawMdib());

		auto stringMetricStates = SDCProviderActivateOperationHandler::getParentProvider().getMdState().findStringMetricStates();
		for(auto strMetricState : stringMetricStates)
		{
			if(strMetricState.getDescriptorHandle() == MDIBDescriptorHandle)
			{
				StringMetricValue MdibStringMetricValue(MetricQuality(MeasurementValidity::Vld));
				MdibStringMetricValue.setValue(Mdib);
				strMetricState.setMetricValue(MdibStringMetricValue);
				SDCProviderActivateOperationHandler::getParentProvider().updateState(strMetricState);
				return InvocationState::Fin;
			}
		}
		return InvocationState::Fail;
	}
private:
	std::string activateDescriptorHandle;
	std::string MDIBDescriptorHandle;
};

class SDCParticipantTriggerFunctionActivateHandler : public SDCProviderActivateOperationHandler {
public:
	SDCParticipantTriggerFunctionActivateHandler(const std::string descriptorHandle, std::function<void()> callback) :
		SDCProviderActivateOperationHandler(descriptorHandle),
		callbackFunction(callback)
	{
	}

	InvocationState onActivateRequest(const OperationInvocationContext & oic) override {
		callbackFunction();
		return InvocationState::Fin;
	}

private:
	std::function<void()> callbackFunction;
};

class SDCParticipantTriggerStringFunctionActivateHandler : public SDCProviderMDStateHandler<StringMetricState> {
public:
	SDCParticipantTriggerStringFunctionActivateHandler(const std::string descriptorHandle, std::function<void(const std::string)> callback) :
		SDCProviderMDStateHandler<StringMetricState>(descriptorHandle),
		callbackFunction(callback)
		{
		}

	StringMetricState getInitialState() override
	{
		StringMetricState initialState(descriptorHandle);
		StringMetricValue initialStringValue(MetricQuality(MeasurementValidity::Vld))
		initialStringValue.setValue("");
		initialState.setMetricValue(initialStringValue);
		return initialState;
	}

	InvocationState onStateChangeRequest(const StringMetricState &state, const OperationInvocationContext & oic) override
	{
		std::string functionParameterString = "";
		if(state.getMetricValue().getValue(functionParameterString))
		{
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

} /* namespace ACS */
} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

#endif /* EXAMPLES_ABSTRACTCONSUMERSIMULATOR_SDCPARTICIPANTMDSTATEFORWARDER_H_ */
