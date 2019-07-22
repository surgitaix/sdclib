/*
 * SDCParticipantMDStateForwarder.h
 *
 *  Created on: Apr 10, 2019
 *      Author: rosenau
 */

#ifndef EXAMPLES_ABSTRACTCONSUMERSIMULATOR_SDCPARTICIPANTMDSTATEFORWARDER_H_
#define EXAMPLES_ABSTRACTCONSUMERSIMULATOR_SDCPARTICIPANTMDSTATEFORWARDER_H_

#include "SDCLib/Data/SDC/SDCConsumerMDStateHandler.h"
#include "SDCLib/Data/SDC/SDCProviderMDStateHandler.h"
#include "SDCLib/Data/SDC/MDIB/custom/OperationInvocationContext.h"
#include "SDCLib/Data/SDC/SDCProviderActivateOperationHandler.h"

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
public:
	SDCParticipantMDStateGetForwarder(const std::string descriptorHandle) :
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



} /* namespace ACS */
} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

#endif /* EXAMPLES_ABSTRACTCONSUMERSIMULATOR_SDCPARTICIPANTMDSTATEFORWARDER_H_ */
