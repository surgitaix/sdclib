/*
 * PulseOximeterAlarmStates.h
 *
 *  Created on: Jul 12, 2019
 *      Author: rosenau
 */

#ifndef EXAMPLES_PULSEOXIMETERPROVIDER_PULSEOXIMETERMETRICSTATES_H_
#define EXAMPLES_PULSEOXIMETERPROVIDER_PULSEOXIMETERMETRICSTATES_H_

#include "SDCLib/Data/SDC/MDIB/EnumStringMetricState.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricState.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricValue.h"
#include "SDCLib/Data/SDC/SDCProviderMDStateHandler.h"
#include "SDCLib/Data/SDC/MDIB/MetricQuality.h"
#include "SDCLib/Data/SDC/MDIB/StringMetricValue.h"
#include "SDCLib/Util/DebugOut.h"

using namespace SDCLib;
using namespace SDCLib::Util;
using namespace SDCLib::Data::SDC;


	class PulseOximeterFingerOutGetHandler : public SDCProviderMDStateHandler<EnumStringMetricState> {
	public:
		PulseOximeterFingerOutGetHandler(std::string p_descriptorHandle) : SDCProviderMDStateHandler(p_descriptorHandle){
		}

		InvocationState onStateChangeRequest(const EnumStringMetricState &, const OperationInvocationContext &) override {
			return InvocationState::Fail;
		}

		EnumStringMetricState getInitialState() override{
			auto EnumStringMS{createState("Finger out")};
			return EnumStringMS;
		}

		void setCurrentStatus(bool p_fingerIsOut)
		{
			if(p_fingerIsOut)
			{
				auto EnumStringMS{createState("Finger out")};
				updateState(EnumStringMS);
			}
			else
			{
				auto EnumStringMS{createState("Finger out")};
				updateState(EnumStringMS);
			}
		}

	private:
		EnumStringMetricState createState(const std::string & p_statusMessage)
		{
			EnumStringMetricState result{descriptorHandle};
			result.setMetricValue(StringMetricValue(MetricQuality(MeasurementValidity::Vld)).setValue(p_statusMessage));
			return result;
		}

	};

	//MdStateHandler for O2 saturation
	class PulseOximeterSatO2GetHandler : public SDCProviderMDStateHandler<NumericMetricState>{
	public:
		PulseOximeterSatO2GetHandler(std::string p_descriptorHandle) : SDCProviderMDStateHandler(p_descriptorHandle) {
		}

		//Changing the value of a get service is prohibit.
		InvocationState onStateChangeRequest(const NumericMetricState &, const OperationInvocationContext &) override {
			Util::DebugOut(Util::DebugOut::Error, "PulseOximeterProvider") << "Changing the value of a get service is prohibit."
							<< std::endl << "Shutting down Consumer";
			return InvocationState::Fail;
		}


		NumericMetricState getInitialState() override{
			auto nms{createState(0.00)};
			return nms;
		}

		void setCurrentValue(double p_value) {
			auto nms{createState(p_value)};
			updateState(nms);
		}

	private:
		NumericMetricState createState(const double p_value) {
			NumericMetricState result{descriptorHandle};
			//Valid metric equaling value. The measurement is performed.
			result.setMetricValue(NumericMetricValue(MetricQuality(MeasurementValidity::Vld)).setValue(p_value))
				  .setActivationState(ComponentActivation::On);
			return result;
		}

	};

	//MdStateHandler for O2 saturation
	class PulseOximeterPulseRateGetHandler : public SDCProviderMDStateHandler<NumericMetricState>{
	public:
		PulseOximeterPulseRateGetHandler(std::string p_descriptorHandle) : SDCProviderMDStateHandler(p_descriptorHandle) {
		}

		//Changing the value of a get service is prohibit.
		InvocationState onStateChangeRequest(const NumericMetricState &, const OperationInvocationContext &) override {
			Util::DebugOut(Util::DebugOut::Error, "PulseOximeterProvider") << "Changing the value of a get service is prohibit."
							<< std::endl << "Shutting down Consumer";
			return InvocationState::Fail;
		}


		NumericMetricState getInitialState() override{
			auto nms{createState(0.00)};
			return nms;
		}

		void setCurrentValue(double p_value) {
			auto nms{createState(p_value)};
			updateState(nms);
		}

	private:
		NumericMetricState createState(const double p_value) {
			NumericMetricState result{descriptorHandle};
			//Valid metric equaling value. The measurement is performed.
			result.setMetricValue(NumericMetricValue(MetricQuality(MeasurementValidity::Vld)).setValue(p_value))
				  .setActivationState(ComponentActivation::On);
			return result;
		}

	};

#endif
