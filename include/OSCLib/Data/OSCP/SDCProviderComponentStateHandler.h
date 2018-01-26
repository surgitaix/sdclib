/*
 * OSCPProviderNumericMetricStateHandler.h
 *
 *  Created on: 05.05.2015
 *      Author: roehser
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
	virtual ~SDCProviderComponentStateHandler();

    virtual TState getInitialState() = 0;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

#endif /* SDCPROVIDERCOMPONENTSTATEHANDLER_H_ */
