/*
 * PulseOximeterProvider.cpp
 *
 *  Created on: Jun 19, 2019
 *      Author: rosenau
 */

#include "PulseOximeterProvider.h"
#include "PulseOximeterHandleNames.h"
#include "SDCLib/Data/SDC/SDCProviderMDStateHandler.h"
#include "SDCLib/Data/SDC/MDIB/ChannelDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/CodedValue.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricState.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricValue.h"
#include "SDCLib/Data/SDC/MDIB/EnumStringMetricState.h"
#include "SDCLib/Data/SDC/MDIB/StringMetricValue.h"
#include "SDCLib/Data/SDC/MDIB/MetricQuality.h"
#include "SDCLib/Data/SDC/MDIB/Range.h"
#include "SDCLib/Data/SDC/MDIB/VmdDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/MdsDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/LimitAlertConditionState.h"
#include "SDCLib/Data/SDC/SDCProviderAlertConditionStateHandler.h"
#include "SDCLib/Data/SDC/MDIB/AlertConditionState.h"
#include "SDCLib/Data/SDC/MDIB/CauseInfo.h"
#include "SDCLib/Data/SDC/MDIB/LocalizedText.h"
#include "SDCLib/Data/SDC/MDIB/AlertSignalDescriptor.h"

#include <SDCLib/Data/SDC/MDIB/SimpleTypesMapping.h>

#include <PulseOximeterMetricStates.h>
#include <PulseOximeterAlarmStates.h>


#include "SDCLib/Util/DebugOut.h"

const int DEFAULT_PORT{0};
const std::string DEFAULT_ENDPOINT_REFERENCE{"PulseOximeter"};


PulseOximeterProvider::PulseOximeterProvider(std::shared_ptr<SDCLib::SDCInstance> p_SDCInstance, const std::string& p_port) :
	sdcProvider(p_SDCInstance),
	COMport(p_port),
	//Metric state handler initialization
	fingerOutStatusHandler{std::make_shared<PulseOximeterFingerOutGetHandler>(PULSE_OXIMETER_FINGER_STATUS_GET_HANDLE)},
	satO2GetHandler{std::make_shared<PulseOximeterSatO2GetHandler>(PULSE_OXIMETER_SAT_O2_GET_HANDLE)},
	pulseRateGetHandler{std::make_shared<PulseOximeterPulseRateGetHandler>(PULSE_OXIMETER_PULSE_RATE_GET_HANDLE)},
	pulseRateAlarmLimitHandler{std::make_shared<PulseOximeterAlarmLimitPulseRateHandler>
								  (PULSE_OXIMETER_PULSE_RATE_LIMIT_ALERT_HANDLE)},
	satO2AlarmLimitHandler{std::make_shared<PulseOximeterAlarmLimitSatO2Handler>
								  (PULSE_OXIMETER_SAT_O2_LIMIT_ALERT_HANDLE)},
	//Metric Descriptor initialization
	satO2Descriptor{PULSE_OXIMETER_SAT_O2_GET_HANDLE,
			CodedValue(DIMENSION_PERCENTAGE),
			MetricCategory::Msrmt,
			MetricAvailability::Cont,
			1.0}, //Resolution of 1%
	pulseRateDescriptor{PULSE_OXIMETER_PULSE_RATE_GET_HANDLE,
			CodedValue(DIMENSION_BEATS_PER_MIN),
			MetricCategory::Msrmt,
			MetricAvailability::Cont,
			1.0}, //Resolution of 1%
	pulseOximeterAlertSystemDescriptor{PULSE_OXIMETER_ALERT_SYSTEM_HANDLE}
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
	pulseRateRange.setLower(30);
	pulseRateRange.setUpper(250);
	pulseRateRange.setAbsoluteAccuracy(2);
	pulseRateRange.setRelativeAccuracy(2);

	pulseRateDescriptor.addTechnicalRange(pulseRateRange);

	//Channel
	ChannelDescriptor pulseChannel{PULSE_OXIMETER_PULS_CHAN_HANDLE};
	pulseChannel.setSafetyClassification(SafetyClassification::MedB)
				.addMetric(pulseRateDescriptor)
				.addMetric(satO2Descriptor);


	//VMD
	VmdDescriptor pulseOximeterVmd{PULSE_OXIMETER_VMD_HANDLE};
	pulseOximeterVmd.addChannel(pulseChannel);

	//AlertSystem
	addAlertSystem(pulseOximeterVmd);

	//MDS
	MdsDescriptor pulseOximeterMds{PULSE_OXIMETER_MDS_HANDLE};
	pulseOximeterMds.addVmd(pulseOximeterVmd);

	MdDescription pulseOximeterMdDesction;
	pulseOximeterMdDesction.addMdsDescriptor(pulseOximeterMds);

	sdcProvider.setMdDescription(pulseOximeterMdDesction);
	sdcProvider.addMdStateHandler(pulseRateGetHandler.get());
	sdcProvider.addMdStateHandler(satO2AlarmLimitHandler.get());
	sdcProvider.addMdStateHandler(satO2GetHandler.get());
	sdcProvider.addMdStateHandler(pulseRateAlarmLimitHandler.get());
	sdcProvider.addMdStateHandler(fingerOutStatusHandler.get());


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

	void PulseOximeterProvider::setPort(int ) {
		//Network configuration

	}


	void PulseOximeterProvider::startup() {
		//forwarding of the startup function
		sdcProvider.startup();
	}

	void PulseOximeterProvider::shutdown() {
		//forwarding of the shutdown function
		interrupt();
		sdcProvider.shutdown();
		serial->stop();
	}


	void PulseOximeterProvider::runImpl() {
		while (!isInterrupted()) {
			{
				auto satO2 = serial->getSpo2();
				auto pulseRate = serial->getPulseRate();
				auto fingerIsOut = serial->fingerIsOut();
				fingerOutStatusHandler->setCurrentStatus(fingerIsOut);
				satO2GetHandler->setCurrentValue(satO2);
				pulseRateGetHandler->setCurrentValue(pulseRate);
				DebugOut(DebugOut::Default, "PulseOximeterProvider") << "satO2: value changed to " << satO2 << std::endl;
				DebugOut(DebugOut::Default, "PulseOximeterProvider") << "PulseRate: value changed to " << pulseRate << std::endl;

			}
			Poco::Thread::sleep(1000);
		}
	}

	MdibContainer PulseOximeterProvider::getMdib() {
		return sdcProvider.getMdib();
	}

	MdDescription PulseOximeterProvider::getMdDescription()
	{
		return sdcProvider.getMdDescription();
	}

	MdState PulseOximeterProvider::getMdState()
	{
		return sdcProvider.getMdState();
	}

	void PulseOximeterProvider::addSatO2LimitAlertCondition(AlertSystemDescriptor &p_alertSystemDesc)
	{
		Range satO2MaxLimits;
		satO2MaxLimits.setUpper(100);
		satO2MaxLimits.setLower(0);
		satO2MaxLimits.setAbsoluteAccuracy(1);

		LimitAlertConditionDescriptor satO2AlarmLimitDescriptor{PULSE_OXIMETER_SAT_O2_LIMIT_ALERT_HANDLE,
				AlertConditionKind::Phy,
				AlertConditionPriority::Me,
				satO2MaxLimits};
		satO2AlarmLimitDescriptor.addSource(PULSE_OXIMETER_SAT_O2_GET_HANDLE);

		CauseInfo satO2LimitCauseInfo;
		LocalizedText satO2InfoDescriptor;
		satO2InfoDescriptor.setLang("en");
		satO2InfoDescriptor.setText("O2 saturation outside of limit");
		satO2LimitCauseInfo.addDescription(satO2InfoDescriptor);
		satO2AlarmLimitDescriptor.getCauseInfoList().push_back(satO2LimitCauseInfo);
		p_alertSystemDesc.addLimitAlertCondition(satO2AlarmLimitDescriptor);

		AlertSignalDescriptor satO2LimitSignal{PULSE_OXIMETER_SAT_O2_LIMIT_ALERT_SIGNAL_HANDLE,
				AlertSignalManifestation::Vis,
				true};
		satO2LimitSignal.setConditionSignaled(PULSE_OXIMETER_SAT_O2_LIMIT_ALERT_HANDLE);
		p_alertSystemDesc.addAlertSignal(satO2LimitSignal);
	}

	void PulseOximeterProvider::addPulseRateLimitAlertCondition(AlertSystemDescriptor &p_alertSystemDesc)
	{
		Range pulseRateMaxLimits;
		pulseRateMaxLimits.setUpper(100);
		pulseRateMaxLimits.setLower(0);
		pulseRateMaxLimits.setAbsoluteAccuracy(1);

		LimitAlertConditionDescriptor pulseRateAlarmLimitDescriptor{PULSE_OXIMETER_PULSE_RATE_LIMIT_ALERT_HANDLE,
				AlertConditionKind::Phy,
				AlertConditionPriority::Me,
				pulseRateMaxLimits};
		pulseRateAlarmLimitDescriptor.addSource(PULSE_OXIMETER_PULSE_RATE_GET_HANDLE);

		CauseInfo pulseRateLimitCauseInfo;
		LocalizedText pulseRateInfoDescriptor;
		pulseRateInfoDescriptor.setLang("en");
		pulseRateInfoDescriptor.setText("Pulse Rate outside of limit");
		pulseRateLimitCauseInfo.addDescription(pulseRateInfoDescriptor);
		pulseRateAlarmLimitDescriptor.getCauseInfoList().push_back(pulseRateLimitCauseInfo);
		p_alertSystemDesc.addLimitAlertCondition(pulseRateAlarmLimitDescriptor);

		AlertSignalDescriptor pulseRateLimitSignal{PULSE_OXIMETER_PULSE_RATE_LIMIT_ALERT_SIGNAL_HANDLE,
				AlertSignalManifestation::Vis,
				true};
		pulseRateLimitSignal.setConditionSignaled(PULSE_OXIMETER_PULSE_RATE_LIMIT_ALERT_HANDLE);
		p_alertSystemDesc.addAlertSignal(pulseRateLimitSignal);
	}

	void PulseOximeterProvider::addFingerOutAlertCondition(AlertSystemDescriptor &p_alertSystemDesc)
	{

		AlertConditionDescriptor fingerOutAlarmDescriptor{PULSE_OXIMETER_FINGER_OUT_ALERT_HANDLE,
				AlertConditionKind::Phy,
				AlertConditionPriority::None};
		fingerOutAlarmDescriptor.addSource(PULSE_OXIMETER_FINGER_STATUS_GET_HANDLE);

		CauseInfo fingerOutCauseInfo;
		LocalizedText fingerOutInfoDescriptor;
		fingerOutInfoDescriptor.setLang("en");
		fingerOutInfoDescriptor.setText("Patient Finger is Out");
		fingerOutCauseInfo.addDescription(fingerOutInfoDescriptor);
		fingerOutAlarmDescriptor.getCauseInfoList().push_back(fingerOutCauseInfo);
		p_alertSystemDesc.addAlertCondition(fingerOutAlarmDescriptor);

		AlertSignalDescriptor fingerOutAlarmSignal{PULSE_OXIMETER_FINGER_OUT_ALERT_SIGNAL_HANDLE,
				AlertSignalManifestation::Vis,
				true};
		fingerOutAlarmSignal.setConditionSignaled(PULSE_OXIMETER_FINGER_OUT_ALERT_HANDLE);
		p_alertSystemDesc.addAlertSignal(fingerOutAlarmSignal);
	}




	void PulseOximeterProvider::addAlertSystem(VmdDescriptor &p_vmdDesc)
	{
		addPulseRateLimitAlertCondition(pulseOximeterAlertSystemDescriptor);
		addSatO2LimitAlertCondition(pulseOximeterAlertSystemDescriptor);
		p_vmdDesc.setAlertSystem(pulseOximeterAlertSystemDescriptor);
	}


	void PulseOximeterProvider::startMedicalDevice() {
	    try {

	    	serial = std::make_shared<Serial::SerialConnectionEventHandler>(COMport, 115200);

	    	serial->start();

			std::string hex{"7d81a1808080808080"};

			int len = hex.length();
			std::string newString;
			for(int i=0; i < len; i+=2)
			{
			    std::string byte = hex.substr(i,2);
			    char chr = static_cast<char>(static_cast<int>(strtol(byte.c_str(), nullptr, 16)));
			    newString.push_back(chr);
			}
			serial->send(newString.c_str(), newString.size());

			std::cout << "starting!" << std::endl;
	    }
	    catch(std::system_error & e)
	    {
	        std::cout<< "Error: "<< e.what()<< std::endl;
	    }
	}
