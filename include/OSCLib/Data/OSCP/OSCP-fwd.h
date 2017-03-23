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
	class OSCPConsumer;
	class OSCPConsumerConnectionLostHandler;
	class OSCPConsumerContextStateChangedHandler;
	class OSCPConsumerEventHandler;
	class OSCPConsumerEnumStringMetricStateHandler;
	class OSCPConsumerNumericMetricStateHandler;
	class OSCPConsumerStringMetricStateHandler;
	class OSCPConsumerRealTimeSampleArrayMetricStateHandler;
	class OSCPConsumerAlertSystemStateHandler;
	class OSCPConsumerAlertSignalStateHandler;
	class OSCPConsumerAlertConditionStateHandler;
	class OSCPConsumerLimitAlertConditionStateHandler;
	class OSCPConsumerSubscriptionLostHandler;

	class OSCPProvider;
	class OSCPProviderMDStateHandler;
	class OSCPProviderAlertConditionStateHandler;
	class OSCPProviderAlertSignalStateHandler;
	class OSCPProviderAlertSystemStateHandler;
	class OSCPProviderClockStateHandler;
	class OSCPProviderComponentStateHandler;
	class OSCPProviderHydraMDSStateHandler;
	class OSCPProviderEnumStringMetricStateHandler;
	class OSCPProviderLimitAlertConditionStateHandler;
	class OSCPProviderNumericMetricStateHandler;
	class OSCPProviderRealTimeSampleArrayMetricStateHandler;
	class OSCPProviderStringMetricStateHandler;
}
}
}


#endif /* OSCLIB_DATA_OSCP_OSCP_FWD_H_ */
