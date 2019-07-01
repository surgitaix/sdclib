/*
 * PulseOximeterProvider.cpp
 *
 *  Created on: Jun 19, 2019
 *      Author: sebastian
 */

#define UNUSED(expr) do { (void)(expr); } while (0)

#include "PulseOximeterProvider.h"
#include "PulseOximeterHandleNames.h"
#include "SDCLib/Data/SDC/SDCProviderMDStateHandler.h"
#include "SDCLib/Data/SDC/MDIB/ChannelDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/CodedValue.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricState.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricValue.h"
#include "SDCLib/Data/SDC/MDIB/MetricQuality.h"
#include "SDCLib/Data/SDC/MDIB/Range.h"
#include "SDCLib/Data/SDC/MDIB/VmdDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/MdsDescriptor.h"


#include "SDCLib/Util/DebugOut.h"

const int DEFAULT_PORT(0);
const std::string DEFAULT_ENDPOINT_REFERENCE("PulseOximeter");

using namespace SDCLib;
using namespace SDCLib::Util;
using namespace SDCLib::Data::SDC;



	//MdStateHandler for O2 saturation
	class PulseOximeterSatO2GetHandler : public SDCProviderMDStateHandler<NumericMetricState>{
	public:
		PulseOximeterSatO2GetHandler(std::string descriptorHandle) : SDCProviderMDStateHandler(descriptorHandle) {
		}

		//Changing the value of a get service is prohibit.
		InvocationState onStateChangeRequest(const NumericMetricState &state, const OperationInvocationContext &oic) override {
			UNUSED(state);
			UNUSED(oic);
			Util::DebugOut(Util::DebugOut::Error, "PulseOximeterProvider") << "Changing the value of a get service is prohibit."
							<< std::endl << "Shutting down Consumer";
			return InvocationState::Fail;
		}


		NumericMetricState getInitialState() override{
			NumericMetricState nms = createState(0.00);
			return nms;
		}

		void setCurrentValue(double value) {
			NumericMetricState nms = createState(value);
			updateState(nms);
		}

	private:
		NumericMetricState createState(const double value) {
			NumericMetricState result(descriptorHandle);
			//Valid metric equaling value. The measurement is performed.
			result.setMetricValue(NumericMetricValue(MetricQuality(MeasurementValidity::Vld)).setValue(value))
				  .setActivationState(ComponentActivation::On);
			return result;
		}

	};

	//MdStateHandler for O2 saturation
	class PulseOximeterPulseRateGetHandler : public SDCProviderMDStateHandler<NumericMetricState>{
	public:
		PulseOximeterPulseRateGetHandler(std::string descriptorHandle) : SDCProviderMDStateHandler(descriptorHandle) {
		}

		//Changing the value of a get service is prohibit.
		InvocationState onStateChangeRequest(const NumericMetricState &state, const OperationInvocationContext &oic) override {
			UNUSED(state);
			UNUSED(oic);
			Util::DebugOut(Util::DebugOut::Error, "PulseOximeterProvider") << "Changing the value of a get service is prohibit."
							<< std::endl << "Shutting down Consumer";
			return InvocationState::Fail;
		}


		NumericMetricState getInitialState() override{
			NumericMetricState nms = createState(0.00);
			return nms;
		}

		void setCurrentValue(double value) {
			NumericMetricState nms = createState(value);
			updateState(nms);
		}

	private:
		NumericMetricState createState(const double value) {
			NumericMetricState result(descriptorHandle);
			//Valid metric equaling value. The measurement is performed.
			result.setMetricValue(NumericMetricValue(MetricQuality(MeasurementValidity::Vld)).setValue(value))
				  .setActivationState(ComponentActivation::On);
			return result;
		}

	};

	//MdStateHandler for setting Upper Pulse Rate Alarm Limit
	class PulseOximeterSetUpperAlarmLimitPulseRateHandler : public SDCProviderMDStateHandler<NumericMetricState>{
	public:
		PulseOximeterSetUpperAlarmLimitPulseRateHandler(std::string descriptorHandle) : SDCProviderMDStateHandler(descriptorHandle) {
		}

		//Changing the value of a get service is prohibit.
		InvocationState onStateChangeRequest(const NumericMetricState &state, const OperationInvocationContext &oic) override {
			double val = state.getMetricValue().getValue();
			Util::DebugOut(Util::DebugOut::Default, "PulseOximeterProvider") << "Trying to set upper pulse rate alarm limit " << val
							<< std::endl << "Shutting down Consumer";
			if(val >= 0 && val < 251)
			{
				setCurrentValue(val);
				return InvocationState::Fin;
			}
			else {
				Util::DebugOut(Util::DebugOut::Error, "PulseOximeterProvider") << "Setting the pulse rate alarm outside the values limit is prohibit" << std::endl;
				return InvocationState::Fail;
			}
		}


		NumericMetricState getInitialState() override{
			currentLimit = DEFAULT_UPPER_PULSE_RATE_ALARM_LIMIT;
			NumericMetricState nms = createState(currentLimit);
			return nms;
		}

		void setCurrentValue(double value) {
			if(value >= 0 && value < 251)
			{
				NumericMetricState nms = createState(value);
				updateState(nms);
			}
		}

	private:
		NumericMetricState createState(const double value) {
			NumericMetricState result(descriptorHandle);
			//Valid metric equaling value. The measurement is performed.
			result.setMetricValue(NumericMetricValue(MetricQuality(MeasurementValidity::Vld)).setValue(value))
				  .setActivationState(ComponentActivation::On);
			return result;
		}

		double currentLimit;
	};

	//MdStateHandler for setting lower pulse rate alarm limit
	class PulseOximeterSetLowerAlarmLimitPulseRateHandler : public SDCProviderMDStateHandler<NumericMetricState>{
	public:
		PulseOximeterSetLowerAlarmLimitPulseRateHandler(std::string descriptorHandle) : SDCProviderMDStateHandler(descriptorHandle) {
		}

		//Changing the value of a get service is prohibit.
		InvocationState onStateChangeRequest(const NumericMetricState &state, const OperationInvocationContext &oic) override {
			double val = state.getMetricValue().getValue();
			Util::DebugOut(Util::DebugOut::Default, "PulseOximeterProvider") << "Trying to set upper pulse rate alarm limit " << val
							<< std::endl << "Shutting down Consumer";
			if(val >= 0 && val < 251)
			{
				setCurrentValue(val);
				return InvocationState::Fin;
			}
			else {
				Util::DebugOut(Util::DebugOut::Error, "PulseOximeterProvider") << "Setting the pulse rate alarm outside the values limit is prohibit" << std::endl;
				return InvocationState::Fail;
			}
		}


		NumericMetricState getInitialState() override{
			currentLimit = DEFAULT_LOWER_PULSE_RATE_ALARM_LIMIT;
			NumericMetricState nms = createState(currentLimit);
			return nms;
		}

		void setCurrentValue(double value) {
			NumericMetricState nms = createState(value);
			updateState(nms);
		}

	private:
		NumericMetricState createState(const double value) {
			NumericMetricState result(descriptorHandle);
			//Valid metric equaling value. The measurement is performed.
			result.setMetricValue(NumericMetricValue(MetricQuality(MeasurementValidity::Vld)).setValue(value))
				  .setActivationState(ComponentActivation::On);
			return result;
		}

		double currentLimit;
	};


	class PulseOximeterSetLowerAlarmLimitSatO2Handler : public SDCProviderMDStateHandler<NumericMetricState>{
	public:
		PulseOximeterSetLowerAlarmLimitSatO2Handler(std::string descriptorHandle) : SDCProviderMDStateHandler(descriptorHandle) {
		}

		//Changing the value of a get service is prohibit.
		InvocationState onStateChangeRequest(const NumericMetricState &state, const OperationInvocationContext &oic) override {
			double val = state.getMetricValue().getValue();
			Util::DebugOut(Util::DebugOut::Default, "PulseOximeterProvider") << "Trying to set upper pulse rate alarm limit " << val
							<< std::endl << "Shutting down Consumer";
			if(val >= 0 && val < 100)
			{
				setCurrentValue(val);
				return InvocationState::Fin;
			}
			else {
				Util::DebugOut(Util::DebugOut::Error, "PulseOximeterProvider") << "Setting the pulse rate alarm outside the values limit is prohibit" << std::endl;
				return InvocationState::Fail;
			}
		}


		NumericMetricState getInitialState() override{
			currentLimit = DEFAULT_LOWER_SAT_O2_ALARM_LIMIT;
			NumericMetricState nms = createState(currentLimit);
			return nms;
		}

		void setCurrentValue(double value) {
			NumericMetricState nms = createState(value);
			updateState(nms);
		}

	private:
		NumericMetricState createState(const double value) {
			NumericMetricState result(descriptorHandle);
			//Valid metric equaling value. The measurement is performed.
			result.setMetricValue(NumericMetricValue(MetricQuality(MeasurementValidity::Vld)).setValue(value))
				  .setActivationState(ComponentActivation::On);
			return result;
		}

		double currentLimit;
	};


	class PulseOximeterSetUpperAlarmLimitSatO2Handler : public SDCProviderMDStateHandler<NumericMetricState>{
	public:
		PulseOximeterSetUpperAlarmLimitSatO2Handler(std::string descriptorHandle) : SDCProviderMDStateHandler(descriptorHandle) {
		}

		//Changing the value of a get service is prohibit.
		InvocationState onStateChangeRequest(const NumericMetricState &state, const OperationInvocationContext &oic) override {
			double val = state.getMetricValue().getValue();
			Util::DebugOut(Util::DebugOut::Default, "PulseOximeterProvider") << "Trying to set upper pulse rate alarm limit " << val
							<< std::endl << "Shutting down Consumer";
			if(val >= 0 && val < 100)
			{
				setCurrentValue(val);
				return InvocationState::Fin;
			}
			else {
				Util::DebugOut(Util::DebugOut::Error, "PulseOximeterProvider") << "Setting the pulse rate alarm outside the values limit is prohibit" << std::endl;
				return InvocationState::Fail;
			}
		}


		NumericMetricState getInitialState() override{
			currentLimit = DEFAULT_UPPER_SAT_O2_ALARM_LIMIT;
			NumericMetricState nms = createState(0.00);
			return nms;
		}

		void setCurrentValue(double value) {
			NumericMetricState nms = createState(value);
			updateState(nms);
		}

	private:
		NumericMetricState createState(const double value) {
			NumericMetricState result(descriptorHandle);
			//Valid metric equaling value. The measurement is performed.
			result.setMetricValue(NumericMetricValue(MetricQuality(MeasurementValidity::Vld)).setValue(value))
				  .setActivationState(ComponentActivation::On);
			return result;
		}

		double currentLimit;
	};


PulseOximeterProvider::PulseOximeterProvider(std::shared_ptr<SDCLib::SDCInstance> p_SDCInstance) :
	sdcProvider(p_SDCInstance),
	//Metric state handler initialization
	satO2GetHandler(new PulseOximeterSatO2GetHandler(PULSE_OXIMETER_SAT_O2_GET_HANDLE)),
	pulseRateGetHandler(new PulseOximeterPulseRateGetHandler(PULSE_OXIMETER_PULSE_RATE_GET_HANDLE)),
	pulseRateLowerAlarmLimitSetHandler(new PulseOximeterSetLowerAlarmLimitPulseRateHandler
								  (PULSE_OXIMETER_SAT_O2_LOWER_ALARM_LIMIT_SET_HANDLE)),
	pulseRateUpperAlarmLimitSetHandler(new PulseOximeterSetUpperAlarmLimitPulseRateHandler
								  (PULSE_OXIMETER_SAT_O2_UPPER_ALARM_LIMIT_SET_HANDLE)),
	satO2UpperAlarmLimitSetHandler(new PulseOximeterSetUpperAlarmLimitSatO2Handler
								  (PULSE_OXIMETER_PULSE_RATE_UPPER_ALARM_LIMIT_SET_HANDLE)),
	satO2LowerAlarmLimitSetHandler(new PulseOximeterSetLowerAlarmLimitSatO2Handler
								  (PULSE_OXIMETER_PULSE_RATE_LOWER_ALARM_LIMIT_SET_HANDLE)),
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
	satO2LowerAlarmLimitDescriptor(PULSE_OXIMETER_SAT_O2_LOWER_ALARM_LIMIT_SET_HANDLE,
			CodedValue(DIMENSION_PERCENTAGE),
			MetricCategory::Set,
			MetricAvailability::Intr,
			1.0),
	satO2UpperAlarmLimitDescriptor(PULSE_OXIMETER_SAT_O2_UPPER_ALARM_LIMIT_SET_HANDLE,
			CodedValue(DIMENSION_PERCENTAGE),
			MetricCategory::Set,
			MetricAvailability::Intr,
			1.0),
	pulseRateLowerAlarmLimitDescriptor(PULSE_OXIMETER_PULSE_RATE_LOWER_ALARM_LIMIT_SET_HANDLE,
			CodedValue(DIMENSION_BEATS_PER_MIN),
			MetricCategory::Set,
			MetricAvailability::Intr,
			1.0),
	pulseRateUpperAlarmLimitDescriptor(PULSE_OXIMETER_PULSE_RATE_UPPER_ALARM_LIMIT_SET_HANDLE,
			CodedValue(DIMENSION_BEATS_PER_MIN),
			MetricCategory::Set,
			MetricAvailability::Intr,
			1.0)
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
	ChannelDescriptor pulseChannel(PULSE_OXIMETER_PULS_CHAN_HANDLE);
	pulseChannel.setSafetyClassification(SafetyClassification::MedB)
				.addMetric(pulseRateDescriptor)
				.addMetric(satO2Descriptor)
				.addMetric(satO2LowerAlarmLimitDescriptor)
				.addMetric(satO2UpperAlarmLimitDescriptor)
				.addMetric(pulseRateLowerAlarmLimitDescriptor)
				.addMetric(pulseRateUpperAlarmLimitDescriptor);


	//VMD
	VmdDescriptor pulseOximeterVmd(PULSE_OXIMETER_VMD_HANDLE);
	pulseOximeterVmd.addChannel(pulseChannel);

	//MDS
	MdsDescriptor pulseOximeterMds(PULSE_OXIMETER_MDS_HANDLE);
	pulseOximeterMds.addVmd(pulseOximeterVmd);

	MdDescription pulseOximeterMdDesction;
	pulseOximeterMdDesction.addMdsDescriptor(pulseOximeterMds);

	sdcProvider.setMdDescription(pulseOximeterMdDesction);
	sdcProvider.addMdStateHandler(pulseRateGetHandler.get());
	sdcProvider.addMdStateHandler(satO2GetHandler.get());
	sdcProvider.addMdStateHandler(satO2LowerAlarmLimitSetHandler.get());
	sdcProvider.addMdStateHandler(satO2UpperAlarmLimitSetHandler.get());
	sdcProvider.addMdStateHandler(pulseRateLowerAlarmLimitSetHandler.get());
	sdcProvider.addMdStateHandler(pulseRateUpperAlarmLimitSetHandler.get());


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

	}


	void PulseOximeterProvider::startup() {
		//forwarding of the startup function
		sdcProvider.startup();
	}

	void PulseOximeterProvider::shutdown() {
		//forwarding of the shutdown function
		sdcProvider.shutdown();
		serial->stop();
	}


	void PulseOximeterProvider::runImpl() {
		while (!isInterrupted()) {
			{
				int satO2 = serial->getSpo2();
				int pulseRate = serial->getPulseRate();
				satO2GetHandler->setCurrentValue(satO2);
				pulseRateGetHandler->setCurrentValue(pulseRate);
				DebugOut(DebugOut::Default, "ExampleProvider") << "satO2: value changed to " << satO2 << std::endl;
				DebugOut(DebugOut::Default, "ExampleProvider") << "PulseRate: value changed to " << pulseRate << std::endl;

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

	void PulseOximeterProvider::startMedicalDevice() {
	    try {

	    	serial = std::make_shared<Serial::SerialConnectionEventHandler>("/dev/ttyS0", 115200);

	    	serial->start();

			std::string hex = "7d81a1808080808080";

			int len = hex.length();
			std::string newString;
			for(int i=0; i< len; i+=2)
			{
			    std::string byte = hex.substr(i,2);
			    char chr = (char) (int)strtol(byte.c_str(), nullptr, 16);
			    newString.push_back(chr);
			}
			serial->send(newString.c_str(), newString.size());

			std::cout << "starting!" << std::endl;
	    } catch(std::system_error& e)
	    {
	        std::cout<< "Error: "<<e.what()<< std::endl;
	    }
	}
