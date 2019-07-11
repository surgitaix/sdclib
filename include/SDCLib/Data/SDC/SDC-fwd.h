/*
 * SDC-fwd.h
 *
 *  Created on: 04.05.2015
 *      Author: roehser
 */

#ifndef SDCLIB_DATA_SDC_SDCFWD_H_
#define SDCLIB_DATA_SDC_SDCFWD_H_

#include "MDIB/MDIB-fwd.h"

namespace SDCLib {
namespace Data {
namespace SDC {

	class AsyncProviderInvoker;

	class FutureInvocationState;
	class SDCConsumer;
	class SDCConsumerConnectionLostHandler;
	class SDCConsumerOperationInvokedHandler;
	class SDCConsumerSubscriptionLostHandler;
	class SDCConsumerSystemContextStateChangedHandler;

	class SDCProvider;

	class SDCProviderStateHandler;

}
}
}


#endif /* SDCLIB_DATA_SDC_SDCFWD_H_ */
