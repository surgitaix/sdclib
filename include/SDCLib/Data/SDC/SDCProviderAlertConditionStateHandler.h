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

#ifndef SDCPROVIDERALERTCONDITIONSTATEHANDLER_H_
#define SDCPROVIDERALERTCONDITIONSTATEHANDLER_H_

#include "SDCLib/Data/SDC/SDCProviderMDStateHandler.h"
#include "SDCLib/Util/DebugOut.h"

namespace SDCLib {
namespace Data {
namespace SDC {

template <class TState>
class SDCProviderAlertConditionStateHandler : public SDCProviderMDStateHandler<TState> {
public:

	/**
	* @brief The constructor gets a handle as an argument referencing the regarding descriptor of the state
	*
	* @return The initial state
	*/
	SDCProviderAlertConditionStateHandler(std::string descriptorHandle) : SDCProviderMDStateHandler<TState>(descriptorHandle) {};
	virtual ~SDCProviderAlertConditionStateHandler() = default;

	virtual void sourceHasChanged(const std::string & sourceHandle) = 0;
	virtual void alertConditionHasChanged() { SDCLib::Util::DebugOut(SDCLib::Util::DebugOut::Default, "SDCProviderAlertConditionStateHandler") << "Soon to be pure virtual function alertConditionHasChanged called." << std::endl;};

};

} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

#endif /* SDCPROVIDERALERTCONDITIONSTATEHANDLER_H_ */
