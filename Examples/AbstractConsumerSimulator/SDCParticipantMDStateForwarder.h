/*
 * SDCParticipantMDStateForwarder.h
 *
 *  Created on: Apr 10, 2019
 *      Author: rosenau
 */

#ifndef EXAMPLES_ABSTRACTCONSUMERSIMULATOR_SDCPARTICIPANTMDSTATEFORWARDER_H_
#define EXAMPLES_ABSTRACTCONSUMERSIMULATOR_SDCPARTICIPANTMDSTATEFORWARDER_H_

#include "OSCLib/Data/SDC/SDCConsumerMDStateHandler.h"
#include "OSCLib/Data/SDC/SDCProviderMDStateHandler.h"
#include "OSCLib/Data/SDC/MDIB/custom/OperationInvocationContext.h"

namespace SDCLib {
namespace Data {
namespace SDC {

namespace ACS {

template<typename TState>
class SDCParticipantMDStateForwarder : public SDCConsumerMDStateHandler<TState>, public SDCProviderMDStateHandler<TState> {
public:
	SDCParticipantMDStateForwarder(const std::string descriptorHandle) : SDCConsumerMDStateHandler<TState>(descriptorHandle), SDCProviderMDStateHandler<TState>(descriptorHandle) {}
	virtual ~SDCParticipantMDStateForwarder() {}

	void onStateChanged(const TState & state) override {
		SDCProviderStateHandler::updateState(state);
	}

    InvocationState onStateChangeRequest(const TState & , const OperationInvocationContext & oic) override {
    	// extract information from the incoming operation
    	SDCProviderStateHandler::notifyOperationInvoked(oic, InvocationState::Start);
    	return InvocationState::Fin;
    }

};

} /* namespace ACS */
} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

#endif /* EXAMPLES_ABSTRACTCONSUMERSIMULATOR_SDCPARTICIPANTMDSTATEFORWARDER_H_ */
