/*
 * OSCPProviderNumericMetricStateHandler.h
 *
 *  Created on: 05.05.2015
 *      Author: roehser
 */

#ifndef SDCPROVIDERMETRICANDALERTSTATEHANDLER_H_
#define SDCPROVIDERMETRICANDALERTSTATEHANDLER_H_

#include "OSCLib/Data/OSCP/SDCProviderStateHandler.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

template <class TState>
class SDCProviderMetricAndAlertStateHandler : public SDCProviderStateHandler {
public:

	/**
	* @brief The constructor gets a handle as an argument referencing the regarding descriptor of the state
	*
	* @return The initial state
	*/
	SDCProviderMetricAndAlertStateHandler(std::string descriptorHandle) : SDCProviderStateHandler(descriptorHandle) {};
	virtual ~SDCProviderMetricAndAlertStateHandler(){};


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

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

#endif /* SDCPROVIDERMETRICANDALERTSTATEHANDLER_H_ */
