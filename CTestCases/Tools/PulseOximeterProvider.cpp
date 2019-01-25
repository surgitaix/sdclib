/*
 * PulseOximeterProvider.cpp
 *
 *  Created on: Jan 14, 2019
 *      Author: rosenau
 */

#include "PulseOximeterProvider.h"

#include <OSCLib/Data/SDC/MDIB/SimpleTypesMapping.h>
#include <Poco/Thread.h>

const std::string DEFAULT_ENDPOINT_REFERENCE("PulseOximeter");
const int DEFAULT_PORT(6464);

PulseOximeterProvider::PulseOximeterProvider():
	sdcProvider(),
	//Metric state handler initialization
	satO2GetHandler(PULSE_OXIMETER_SAT_O2_GET_HANDLE),
	pulseRateGetHandler(PULSE_OXIMETER_PULSE_RATE_GET_HANDLE),
	//Alert state handler initialization
	satO2LimitAlert(PULSE_OXIMETER_SAT_O2_LIMIT_ALERT_HANDLE),
	//Battery state handler initialization
	batteryState(PULSE_OXIMETER_BATTERY_HANDLE),
	//AlertSystem state handler initialization
	pulseOximeterAlertSystemState(PULSE_OXIMETER_ALERT_SYSTEM_HANDLE),
	//Metric Descriptor initialization
	satO2Descriptor(PULSE_OXIMETER_SAT_O2_GET_HANDLE,
			CodedValue(DIMENSION_PERCENTAGE),
			MetricCategory::Msrmt,
			MetricAvailability::Cont,
			1.0), //Resolution of 1%
	pulseRateDescriptor(PULSE_OXIMETER_PULSE_RATE_GET_HANDLE,
			CodedValue(DIMENSION_BEATS_PER_MIN),
			MetricCategory::Msrmt,
			MetricAvailability::Cont,
			1.0), //Resolution of 1%
	batteryDescriptor(PULSE_OXIMETER_BATTERY_HANDLE),
	pulseOximeterAlertSystemDescriptor(PULSE_OXIMETER_ALERT_SYSTEM_HANDLE)
{
	//Mdib definition (bottom up)

	//Technical range satO2
	Range satO2Range;
	satO2Range.setLower(0);
	satO2Range.setUpper(100);
	satO2Range.setAbsoluteAccuracy(2);

	satO2Descriptor.addTechnicalRange(satO2Range);

	//Technical range pulse rate
	Range pulseRateRange;
	pulseRateRange.setLower(0);
	pulseRateRange.setUpper(250);
	pulseRateRange.setAbsoluteAccuracy(2);
	pulseRateRange.setRelativeAccuracy(2);

	pulseRateDescriptor.addTechnicalRange(pulseRateRange);

	//Channel
	ChannelDescriptor pulseChannel(PULSE_OXIMETER_PULS_CHAN_HANDLE);
	pulseChannel.setSafetyClassification(SafetyClassification::MedB)
				.addMetric(pulseRateDescriptor);
	ChannelDescriptor satO2Channel(PULSE_OXIMETER_PULS_SAT_O2_CHAN_HANDLE);
	satO2Channel.setSafetyClassification(SafetyClassification::MedB)
				.addMetric(satO2Descriptor);

	//VMD
	VmdDescriptor pulseOximeterVmd(PULSE_OXIMETER_VMD_HANDLE);
	pulseOximeterVmd.addChannel(pulseChannel);
	pulseOximeterVmd.addChannel(satO2Channel);

	//AlertSystem
	addAlertSystem(pulseOximeterVmd);

	//MDS
	MdsDescriptor pulseOximeterMds(PULSE_OXIMETER_MDS_HANDLE);
	pulseOximeterMds.addVmd(pulseOximeterVmd);

	MdDescription pulseOximeterMdDesction;
	pulseOximeterMdDesction.addMdsDescriptor(pulseOximeterMds);

	sdcProvider.setMdDescription(pulseOximeterMdDesction);
	sdcProvider.addMdStateHandler(&pulseRateGetHandler);
	sdcProvider.addMdStateHandler(&satO2GetHandler);
	sdcProvider.addMdStateHandler(&satO2LimitAlert);


	//Endpoint reference
	setEndPointReference(DEFAULT_ENDPOINT_REFERENCE);
	setPort(DEFAULT_PORT);
	Dev::DeviceCharacteristics devChar;
	devChar.addFriendlyName("en", "PulseOximeterProvider");
	sdcProvider.setDeviceCharacteristics(devChar);
}

PulseOximeterProvider::~PulseOximeterProvider() {
	shutdown();
}

void PulseOximeterProvider::setEndPointReference(std::string endPointReference) {
	sdcProvider.setEndpointReference(endPointReference);
}

void PulseOximeterProvider::setPort(int port) {
	//Network configuration
	MDPWSTransportLayerConfiguration providerConfig = MDPWSTransportLayerConfiguration();
	providerConfig.setPort(port);
	sdcProvider.setConfiguration(providerConfig);
}


void PulseOximeterProvider::startup() {
	//forwarding of the startup function
	sdcProvider.startup();
}

void PulseOximeterProvider::shutdown() {
	//forwarding of the shutdown function
	sdcProvider.shutdown();
}


void PulseOximeterProvider::runImpl() {
	while (!isInterrupted()) {
		{
			int satO2 = std::rand() % 20 + 80; //80-100
			int pulseRate = std::rand() % 100 + 40; // 40-140
			satO2GetHandler.setCurrentValue(satO2);
			pulseRateGetHandler.setCurrentValue(pulseRate);
			DebugOut(DebugOut::Default, "ExampleProvider") << "satO2: value changed to " << satO2 << std::endl;
			DebugOut(DebugOut::Default, "ExampleProvider") << "PulseRate: value changed to " << pulseRate << std::endl;

		}
		Poco::Thread::sleep(1000);
	}
}

MdibContainer PulseOximeterProvider::getMdib() {
	return sdcProvider.getMdib();
}

MdDescription PulseOximeterProvider::getMdDscription()
{
	return sdcProvider.getMdDescription();
}

MdState PulseOximeterProvider::getMdState()
{
	return sdcProvider.getMdState();
}

void PulseOximeterProvider::addAlertSystem(VmdDescriptor & vmdDesc)
{
	addPulseRateLimitAlertCondition(pulseOximeterAlertSystemDescriptor);
	addSatO2LimitAlertCondition(pulseOximeterAlertSystemDescriptor);
	vmdDesc.setAlertSystem(pulseOximeterAlertSystemDescriptor);
}

void PulseOximeterProvider::addPulseRateLimitAlertCondition(AlertSystemDescriptor &alertSystemDesc)
{
	Range pulseRateAlertRange;
	pulseRateAlertRange.setLower(60);
	pulseRateAlertRange.setUpper(120);
	LimitAlertConditionState pulseRateLimitAlert(PULSE_OXIMETER_PULSE_RATE_LIMIT_ALERT_HANDLE,
			AlertActivation::Off,
			pulseRateAlertRange,
			AlertConditionMonitoredLimits::All);

	Range maxPulseRateAlertRange;
	maxPulseRateAlertRange.setLower(0);
	maxPulseRateAlertRange.setUpper(250);
	LimitAlertConditionDescriptor pulseRateLimitAlertDescriptor(PULSE_OXIMETER_PULSE_RATE_LIMIT_ALERT_HANDLE,
		AlertConditionKind::Phy,
		AlertConditionPriority::Me,
		maxPulseRateAlertRange);
	pulseRateLimitAlertDescriptor.addSource(PULSE_OXIMETER_PULSE_RATE_GET_HANDLE);
	CauseInfo pulseLimitCauseInfo;
	LocalizedText pulseCauseInfoDescriptor;
	pulseCauseInfoDescriptor.setLang("en");
	pulseCauseInfoDescriptor.setRef("Pulse rate is out of defined limit range");
	pulseLimitCauseInfo.addDescription(pulseCauseInfoDescriptor);
	pulseRateLimitAlertDescriptor.getCauseInfoList().push_back(pulseLimitCauseInfo);
	alertSystemDesc.addLimitAlertCondition(pulseRateLimitAlertDescriptor);

	AlertSignalDescriptor pulseRateLimitSignal(PULSE_OXIMETER_PULSE_RATE_LIMIT_ALERT_SIGNAL_HANDLE,
		AlertSignalManifestation::Vis,
		true);
	pulseRateLimitSignal.setConditionSignaled(PULSE_OXIMETER_PULSE_RATE_LIMIT_ALERT_HANDLE);
	alertSystemDesc.addAlertSignal(pulseRateLimitSignal);
}

void PulseOximeterProvider::addSatO2LimitAlertCondition(AlertSystemDescriptor &alertSystemDesc)
{
	AlertConditionDescriptor satO2LimitAlertDescriptor(PULSE_OXIMETER_SAT_O2_LIMIT_ALERT_HANDLE,
		AlertConditionKind::Phy,
		AlertConditionPriority::Hi
	);
	satO2LimitAlertDescriptor.addSource(PULSE_OXIMETER_SAT_O2_GET_HANDLE);

	CauseInfo satO2LimitCauseInfo;
	LocalizedText satO2InfoDescriptor;
	satO2InfoDescriptor.setLang("en");
	satO2InfoDescriptor.setRef("SatO2 dropped significantly");
	satO2LimitCauseInfo.addDescription(satO2InfoDescriptor);
	satO2LimitAlertDescriptor.getCauseInfoList().push_back(satO2LimitCauseInfo);
	alertSystemDesc.addAlertCondition(satO2LimitAlertDescriptor);

	AlertSignalDescriptor satO2LimitSignal(PULSE_OXIMETER_SAT_O2_LIMIT_ALERT_SIGNAL_HANDLE,
		AlertSignalManifestation::Vis,
		true);
	satO2LimitSignal.setConditionSignaled(PULSE_OXIMETER_SAT_O2_LIMIT_ALERT_SIGNAL_HANDLE);
	alertSystemDesc.addAlertSignal(satO2LimitSignal);
}
