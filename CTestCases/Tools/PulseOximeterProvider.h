/*
 * PulseOximeterProvider.h
 *
 *  Created on: Jan 14, 2019
 *      Author: rosenau
 */
/*
 * Representation of a Pulse Oximeter as Provider.
 */


#ifndef EXAMPLES_PULSEOXIMETERPROVIDER_H_
#define EXAMPLES_PULSEOXIMETERPROVIDER_H_

#define UNUSED(expr) do { (void)(expr); } while (0)

#include "OSCLib/Data/SDC/SDCProvider.h"
#include "OSCLib/Data/SDC/SDCProviderMDStateHandler.h"
#include "OSCLib/Data/SDC/SDCProviderAlertConditionStateHandler.h"
#include "OSCLib/Data/SDC/MDIB/MdsState.h"
#include "OSCLib/Data/SDC/MDIB/ChannelDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/CodedValue.h"
#include "OSCLib/Data/SDC/MDIB/MdsDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/MdDescription.h"
#include "OSCLib/Data/SDC/MDIB/MetricQuality.h"
#include "OSCLib/Data/SDC/MDIB/Range.h"
#include "OSCLib/Data/SDC/MDIB/NumericMetricState.h"
#include "OSCLib/Data/SDC/MDIB/NumericMetricValue.h"
#include "OSCLib/Data/SDC/MDIB/NumericMetricDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/VmdDescriptor.h"
#include "OSCLib/Data/SDC/MDPWSTransportLayerConfiguration.h"
#include "OSCLib/Data/SDC/MDIB/BatteryState.h"
#include "OSCLib/Data/SDC/MDIB/BatteryDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/LimitAlertConditionDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/LimitAlertConditionState.h"
#include "OSCLib/Data/SDC/MDIB/AlertConditionDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/AlertConditionState.h"
#include "OSCLib/Data/SDC/MDIB/CauseInfo.h"
#include "OSCLib/Data/SDC/MDIB/LocalizedText.h"
#include "OSCLib/Data/SDC/MDIB/AlertSystemState.h"
#include "OSCLib/Data/SDC/MDIB/AlertSystemDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/AlertSignalDescriptor.h"

#include "OSCLib/Data/SDC/MDIB/custom/MdibContainer.h"

#include "BICEPS_MessageModel-fwd.hxx"

#include "OSCLib/Util/Task.h"
#include "OSCLib/Util/DebugOut.h"

#include "PulseOximeterHandleNames.h"


using namespace SDCLib;
using namespace SDCLib::Util;
using namespace SDCLib::Data::SDC;

class PulseOximeterProvider : public Util::Task{

	//MdStateHandler to get manage the accessible values of the pulse oximeter

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
			NumericMetricState result(PULSE_OXIMETER_SAT_O2_GET_HANDLE);
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
			NumericMetricState result(PULSE_OXIMETER_PULSE_RATE_GET_HANDLE);
			//Valid metric equaling value. The measurement is performed.
			result.setMetricValue(NumericMetricValue(MetricQuality(MeasurementValidity::Vld)).setValue(value))
				  .setActivationState(ComponentActivation::On);
			return result;
		}

	};

	//Alert system handle
	class PulseOximeterAlertSystemState : public SDCProviderAlertConditionStateHandler<AlertSystemState> {
	public:
		PulseOximeterAlertSystemState(const std::string descriptorHandle) : SDCProviderAlertConditionStateHandler(descriptorHandle){

		}

		void sourceHasChanged(const std::string &sourceHandle) override {
			UNUSED(sourceHandle);
		}

		InvocationState onStateChangeRequest(const AlertSystemState &state, const OperationInvocationContext &oic) override {
			UNUSED(state);
			UNUSED(oic);
			return InvocationState::Fin;
		}

		AlertSystemState getInitialState() override {
			AlertSystemState result(PULSE_OXIMETER_ALERT_SYSTEM_HANDLE , AlertActivation::Off);
			return result;
		}

		void setAlert(const AlertActivation & alertActivation) {
			AlertSystemState newAlertSystemState(PULSE_OXIMETER_ALERT_SYSTEM_HANDLE, alertActivation);
			updateState(newAlertSystemState);
		}
	};

	//SatO2 alert handle sets alarm on deviation of current value from previous value by
	class SatO2AlertStateHandle : public SDCProviderAlertConditionStateHandler<AlertConditionState>
	{
	public:
		SatO2AlertStateHandle(std::string descriptorHandle) : SDCProviderAlertConditionStateHandler(descriptorHandle) {

		}

		void sourceHasChanged(const std::string &sourceHandle) override {
			std::unique_ptr<NumericMetricState> pSourceState(getParentProvider().getMdState().findState<NumericMetricState>(sourceHandle));
			if (pSourceState->getDescriptorHandle() != sourceHandle) {
			   	return;
			}
			if (!pSourceState->hasMetricValue()) {
				return;
			}
			const auto sourceValue(pSourceState->getMetricValue());
			if (!sourceValue.hasValue()) {
				return;
			}

			if(lastValue < sourceValue.getValue()) {
				lastValue = sourceValue.getValue();
				return;
			}
			else {
				if (lastValue - sourceValue.getValue() <= maxDiff) {
					lastValue = sourceValue.getValue();
					return;
				}
				else {
					setAlert(AlertActivation::On);
				}
			}
		}

		InvocationState onStateChangeRequest(const AlertConditionState &state, const OperationInvocationContext &oic) override {
			UNUSED(state);
			UNUSED(oic);
			return InvocationState::Fin;
		}

		AlertConditionState getInitialState() override {
			AlertConditionState result(PULSE_OXIMETER_SAT_O2_LIMIT_ALERT_HANDLE, AlertActivation::Off);
			return result;
		}

		void setAlert(const AlertActivation & alertActivation) {
			AlertConditionState result(PULSE_OXIMETER_SAT_O2_LIMIT_ALERT_HANDLE, alertActivation);
			updateState(result);
		}

		void setMaxDiff(const int &newMaxDiff) {
			maxDiff = newMaxDiff;
		}

		int getMaxDiff() {
			return maxDiff;
		}

	private:
		int maxDiff = 4;
		double lastValue = -1;
	};


public:
	PulseOximeterProvider();
	virtual ~PulseOximeterProvider();

	void setPort(int port);
	void setEndPointReference(std::string endPointReference);

	void startup();
	void shutdown();

	virtual void runImpl() override;

	MdibContainer getMdib();
	MdDescription getMdDscription();
	MdState getMdState();


private:

	void addAlertSystem(VmdDescriptor & vmdDesc);
	void addPulseRateLimitAlertCondition(AlertSystemDescriptor &alertSystemDesc);
	void addSatO2LimitAlertCondition(AlertSystemDescriptor &alertSystemDesc);


	SDCProvider sdcProvider;
	PulseOximeterSatO2GetHandler satO2GetHandler;
	PulseOximeterPulseRateGetHandler pulseRateGetHandler;
	SatO2AlertStateHandle satO2LimitAlert;
	BatteryState batteryState;
	PulseOximeterAlertSystemState pulseOximeterAlertSystemState;
	NumericMetricDescriptor satO2Descriptor;
	NumericMetricDescriptor pulseRateDescriptor;
	BatteryDescriptor batteryDescriptor;
	AlertSystemDescriptor pulseOximeterAlertSystemDescriptor;
};

#endif /* EXAMPLES_PULSEOXIMETERPROVIDER_H_ */
