/*
 * SDCProviderComponentStateHandler.h
 *
 *  Created on: 23.01.18
 *      Author: buerger
 *
 *      Use this state hander for the component related states such as MdsState, VmdState, ClockState ...
 */

#ifndef SDCPROVIDERCOMPONENTSTATEHANDLER_H_
#define SDCPROVIDERCOMPONENTSTATEHANDLER_H_

#include "OSCLib/Data/SDC/SDCProviderStateHandler.h"

namespace SDCLib {
namespace Data {
namespace SDC {

template <class TState>
class SDCProviderComponentStateHandler : public SDCProviderStateHandler {
public:
	SDCProviderComponentStateHandler(std::string descriptorHandle) : SDCProviderStateHandler(descriptorHandle) {};
	virtual ~SDCProviderComponentStateHandler() =default;

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

#endif /* SDCPROVIDERCOMPONENTSTATEHANDLER_H_ */
