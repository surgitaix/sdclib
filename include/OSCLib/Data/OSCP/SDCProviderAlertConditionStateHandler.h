/*
 * SDCProviderAlertConditionStateHandler.h
 *
 *  Created on: 26.01.2018
 *      Author: buerger
 *
 *      This state handler extends alert state handlers. The sourceHasChanged method is called each time when a referenced state changes.
 *      Use it e.g. to check for defined boundaries.
 *
 *
 */

#ifndef SDCPROVIDERMETRICANDALERTSTATEHANDLER_H_
#define SDCPROVIDERMETRICANDALERTSTATEHANDLER_H_

#include "OSCLib/Data/OSCP/SDCProviderStateHandler.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

template <class TState>
class SDCProviderAlertConditionStateHandler : public SDCProviderMetricAndAlertStateHandler<TState> {
public:

	/**
	* @brief The constructor gets a handle as an argument referencing the regarding descriptor of the state
	*
	* @return The initial state
	*/
	SDCProviderAlertConditionStateHandler(std::string descriptorHandle) : SDCProviderMetricAndAlertStateHandler(descriptorHandle) {};
	virtual ~SDCProviderAlertConditionStateHandler(){};

	virtual sourceHasChanged(const std::string sourceHandle) = 0;

};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

#endif /* SDCPROVIDERMETRICANDALERTSTATEHANDLER_H_ */
