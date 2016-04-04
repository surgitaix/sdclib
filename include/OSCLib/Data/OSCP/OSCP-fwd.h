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
	template<class Traits>
	class CDMEventSink;
	template<class Traits>
	class CDMEventSource;
	struct ActivateTraits;
	struct EpisodicAlertReportTraits;
	struct EpisodicContextChangedReportTraits;
	struct EpisodicMetricReportTraits;
	struct GetContextStatesTraits;
	struct GetMDDescriptionTraits;
	struct GetMDIBTraits;
	struct GetMDStateTraits;
	struct OperationInvokedReportTraits;
	struct PeriodicAlertReportTraits;
	struct PeriodicContextChangedReportTraits;
	struct PeriodicMetricReportTraits;
	struct SetAlertStateTraits;
	struct SetContextStateTraits;
	struct SetStringTraits;
	struct SetValueTraits;
	struct WaveformStreamTraits;

	typedef CDMEventSink<EpisodicAlertReportTraits> CDMEAREventSink;
	typedef CDMEventSink<EpisodicMetricReportTraits> CDMEMREventSink;
	typedef CDMEventSink<EpisodicContextChangedReportTraits> CDMECREventSink;
	typedef CDMEventSink<PeriodicAlertReportTraits> CDMPAREventSink;
	typedef CDMEventSink<PeriodicContextChangedReportTraits> CDMPCREventSink;
	typedef CDMEventSink<PeriodicMetricReportTraits> CDMPMREventSink;
	typedef CDMEventSink<OperationInvokedReportTraits> CDMOIREventSink;

	typedef CDMEventSource<EpisodicAlertReportTraits> CDMEpisodicAlertEventSource;
	typedef CDMEventSource<EpisodicContextChangedReportTraits> CDMEpisodicContextChangedEventSource;
	typedef CDMEventSource<EpisodicMetricReportTraits> CDMEpisodicMetricEventSource;
	typedef CDMEventSource<OperationInvokedReportTraits> CDMOperationInvokedReportSource;
	typedef CDMEventSource<PeriodicAlertReportTraits> CDMPeriodicAlertEventSource;
	typedef CDMEventSource<PeriodicContextChangedReportTraits> CDMPeriodicContextChangedEventSource;
	typedef CDMEventSource<PeriodicMetricReportTraits> CDMPeriodicMetricEventSource;
	typedef CDMEventSource<WaveformStreamTraits> CDMWaveformStreamSource;

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
	class OSCPEventSink;
	class OSCPPingManager;
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
	class OSCPSubscriptionManager;
}
}
}


#endif /* OSCLIB_DATA_OSCP_OSCP_FWD_H_ */
