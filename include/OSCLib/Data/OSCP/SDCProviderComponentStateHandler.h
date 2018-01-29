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

#include "OSCLib/Data/OSCP/SDCProviderStateHandler.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

template <class TState>
class SDCProviderComponentStateHandler : public SDCProviderStateHandler {
public:
	SDCProviderComponentStateHandler(std::string descriptorHandle) : SDCProviderStateHandler(descriptorHandle) {};
	virtual ~SDCProviderComponentStateHandler() {};

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

#endif /* SDCPROVIDERCOMPONENTSTATEHANDLER_H_ */
