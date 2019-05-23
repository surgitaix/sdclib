/*
 * SDCProviderMetricAndAlertStateHandler.h
 *
 *  Created on: 24.01.2018
 *      Author: buerger
 *
 *      Use this state handler for all metrices and alerts. References regarding descriptor.
 *		Use the inhereted update state method for internally updating the mdib's state.
 *		Use onStateChangeRequest to define the behavior when a consumer requests the change of a state.
 *
 */

#ifndef SDCPROVIDERMDSTATEHANDLER_H_
#define SDCPROVIDERMDSTATEHANDLER_H_

#include "SDCLib/Data/SDC/SDCProviderStateHandler.h"

namespace SDCLib {
namespace Data {
namespace SDC {

template <class TState>
class SDCProviderMDStateHandler : public SDCProviderStateHandler {
public:

	/**
	* @brief The constructor gets a handle as an argument referencing the regarding descriptor of the state
	*
	* @return The initial state
	*/
	SDCProviderMDStateHandler(std::string descriptorHandle) : SDCProviderStateHandler(descriptorHandle) {};
	virtual ~SDCProviderMDStateHandler() = default;


	/**
	* @brief it is necessary to define what to do if a consumer asks for changing a state.
	* 			Thus this method has to be implemented for each handler.
	* 			The internal state WILL ONLY BE updated if
	* 			InvocationState::Fin
	* 			is returned!
	* 			Note that internally
	* 			Have a look at the ExampleProvider for one simple way the usage is intended.
	*
	* @return The initial state
	*/
	virtual InvocationState onStateChangeRequest(const TState & state, const OperationInvocationContext & oic) = 0;

    /**
    * @brief the initial state has to be defined. It is needed to be called from within the framework.
    *
    * @return The initial state
    */
    virtual TState getInitialState() = 0;
};

} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

#endif /* SDCPROVIDERMDSTATEHANDLER_H_ */
