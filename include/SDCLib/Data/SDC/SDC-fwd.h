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
	class SDCConsumerSystemContextStateChangedHandler;
	class SDCConsumerOperationInvokedHandler;
	class SDCConsumerEnumStringMetricStateHandler;
	class SDCConsumerNumericMetricStateHandler;
	class SDCConsumerStringMetricStateHandler;
	class SDCConsumerRealTimeSampleArrayMetricStateHandler;
	class SDCConsumerAlertSystemStateHandler;
	class SDCConsumerAlertSignalStateHandler;
	class SDCConsumerAlertConditionStateHandler;
	class SDCConsumerLimitAlertConditionStateHandler;
	class SDCConsumerSubscriptionLostHandler;

	class SDCProvider;
	class SDCProviderMdStateHandler;
	class SDCProviderAlertSignalStateHandler;
	class SDCProviderAlertSystemStateHandler;
	class SDCProviderClockStateHandler;
	class SDCProviderMdsStateHandler;
	class SDCProviderEnumStringMetricStateHandler;
	class SDCProviderLimitAlertConditionStateHandler;
	class SDCProviderNumericMetricStateHandler;
	class SDCProviderRealTimeSampleArrayMetricStateHandler;
	class SDCProviderStringMetricStateHandler;

	class SDCProviderStateHandler;

}
}
}


#endif /* SDCLIB_DATA_SDC_SDCFWD_H_ */
