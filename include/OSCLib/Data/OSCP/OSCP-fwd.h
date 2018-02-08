/*
 * OSCP-fwd.h
 *
 *  Created on: 04.05.2015
 *      Author: roehser
 */

#ifndef OSCLIB_DATA_OSCP_OSCP_FWD_H_
#define OSCLIB_DATA_OSCP_OSCP_FWD_H_

#include "MDIB/MDIB-fwd.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

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

//	class SDCConsumerMDStateHandler;
//	class SDCConsumerOperationInvokedHandler;

	class SDCProvider;
	class SDCProviderMdStateHandler;
	//class SDCProviderAlertConditionStateHandler;
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
//	class SDCProviderActivateOperationHandler;
//	class SDCProviderAlertConditionStateHandler;
//	class SDCProviderComponentStateHandler;
//	class SDCProviderMetricAndAlertStateHandler;
}
}
}


#endif /* OSCLIB_DATA_OSCP_OSCP_FWD_H_ */
