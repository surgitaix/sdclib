/*
 * PulseOximeterAlarmStates.h
 *
 *  Created on: Jul 12, 2019
 *      Author: rosenau
 */

#ifndef EXAMPLES_PULSEOXIMETERPROVIDER_PULSEOXIMETERALARMSTATES_H_
#define EXAMPLES_PULSEOXIMETERPROVIDER_PULSEOXIMETERALARMSTATES_H_

#include "SDCLib/Data/SDC/MDIB/LimitAlertConditionState.h"
#include "SDCLib/Data/SDC/MDIB/AlertConditionState.h"
#include "SDCLib/Data/SDC/SDCProviderAlertConditionStateHandler.h"
#include "SDCLib/Data/SDC/MDIB/Range.h"
#include "SDCLib/Util/DebugOut.h"

using namespace SDCLib;
using namespace SDCLib::Util;
using namespace SDCLib::Data::SDC;



	//MdStateHandler for setting Upper Pulse Rate Alarm Limit
	class PulseOximeterAlarmLimitPulseRateHandler : public SDCProviderAlertConditionStateHandler<LimitAlertConditionState>{
	public:
		PulseOximeterAlarmLimitPulseRateHandler(std::string p_descriptorHandle) : SDCProviderAlertConditionStateHandler(p_descriptorHandle) {
		}

		//Changing the Limits
		InvocationState onStateChangeRequest(const LimitAlertConditionState &state, const OperationInvocationContext &) override {
			auto maxLimits = getParentProvider().getMdDescription().findDescriptor<LimitAlertConditionDescriptor>(state.getDescriptorHandle())->getMaxLimits();
			Range incomingLimits;
			if(incomingLimits.getLower() >= maxLimits.getLower() &&
			   incomingLimits.getUpper() <= maxLimits.getUpper() &&
			   incomingLimits.getLower() <= incomingLimits.getUpper())
			{
				setLimitRange(incomingLimits);
				return InvocationState::Fin;
			}
			return InvocationState::Fail;

		}

		void sourceHasChanged(const std::string & p_sourceHandle)
		{
			auto sourceState{getParentProvider().getMdState().findState<NumericMetricState>(p_sourceHandle)};
			auto currentState(*getParentProvider().getMdState().findState<LimitAlertConditionState>(descriptorHandle));
			auto currentLimits = currentState.getLimits();
			auto currentValue = sourceState->getMetricValue().getValue();
			if(currentValue < currentLimits.getLower())
			{
				std::cout << "ALARM! " << p_sourceHandle << currentValue <<  std::endl;
			}
			else if(currentValue > currentLimits.getUpper())
			{
				std::cout << "ALARM! " << p_sourceHandle << currentValue << std::endl;
			}
		}


		LimitAlertConditionState getInitialState() override{
			Range limits;
			limits.setLower(DEFAULT_LOWER_PULSE_RATE_ALARM_LIMIT);
			limits.setUpper(DEFAULT_UPPER_PULSE_RATE_ALARM_LIMIT);
			limits.setAbsoluteAccuracy(DEFAULT_PULSE_RATE_ALARM_LIMIT_ABSOLUTE_ACCURACY);
			LimitAlertConditionState LimitAlertCS = createState(AlertActivation::Off, limits);
			return LimitAlertCS;
		}

		void setLimitRange(Range p_limits)
		{
			auto currentState{*getParentProvider().getMdState().findState<LimitAlertConditionState>(descriptorHandle)};
			currentState.setLimits(p_limits);
		}

		void setActivationState(AlertActivation p_activationState)
		{
			auto currentState{*getParentProvider().getMdState().findState<LimitAlertConditionState>(descriptorHandle)};
			currentState.setActivationState(p_activationState);
		}


	private:
		LimitAlertConditionState createState(AlertActivation p_activationState, Range p_limits) {
			LimitAlertConditionState LimitAlertCS{descriptorHandle, p_activationState, p_limits, AlertConditionMonitoredLimits::All};
			return LimitAlertCS;
		}

	};


	class PulseOximeterAlarmLimitSatO2Handler : public SDCProviderAlertConditionStateHandler<LimitAlertConditionState>{
	public:
		PulseOximeterAlarmLimitSatO2Handler(std::string p_descriptorHandle) : SDCProviderAlertConditionStateHandler(p_descriptorHandle) {
		}

		//Changing the Limits
		InvocationState onStateChangeRequest(const LimitAlertConditionState &p_state, const OperationInvocationContext &) override {
			auto maxLimits{getParentProvider().getMdDescription().findDescriptor<LimitAlertConditionDescriptor>(p_state.getDescriptorHandle())->getMaxLimits()};
			Range incomingLimits;
			if(incomingLimits.getLower() >= maxLimits.getLower() &&
			   incomingLimits.getUpper() <= maxLimits.getUpper() &&
			   incomingLimits.getLower() <= incomingLimits.getUpper())
			{
				setLimitRange(incomingLimits);
				return InvocationState::Fin;
			}
			return InvocationState::Fail;

		}

		void sourceHasChanged(const std::string & p_sourceHandle)
		{
			auto pSourceState{getParentProvider().getMdState().findState<NumericMetricState>(p_sourceHandle)};
			auto currentState{*getParentProvider().getMdState().findState<LimitAlertConditionState>(descriptorHandle)};
			auto currentLimits{currentState.getLimits()};
			auto currentValue{pSourceState->getMetricValue().getValue()};
			if(currentValue < currentLimits.getLower())
			{
				std::cout << "ALARM! " << p_sourceHandle << currentValue <<  std::endl;
			}
			else if(currentValue > currentLimits.getUpper())
			{
				std::cout << "ALARM! " << p_sourceHandle << currentValue << std::endl;
			}
		}


		LimitAlertConditionState getInitialState() override{
			Range limits;
			limits.setLower(DEFAULT_LOWER_SAT_O2_ALARM_LIMIT);
			limits.setUpper(DEFAULT_UPPER_SAT_O2_ALARM_LIMIT);
			limits.setAbsoluteAccuracy(DEFAULT_SAT_O2_ALARM_LIMIT_ABSOLUTE_ACCURACY);
			auto LimitAlertCS = createState(AlertActivation::Off, limits);
			return LimitAlertCS;
		}

		void setLimitRange(Range limits)
		{
			auto currentState(*getParentProvider().getMdState().findState<LimitAlertConditionState>(descriptorHandle));
			currentState.setLimits(limits);
		}

		void setActivationState(AlertActivation activationState)
		{
			auto currentState(*getParentProvider().getMdState().findState<LimitAlertConditionState>(descriptorHandle));
			currentState.setActivationState(activationState);
		}

	private:

		LimitAlertConditionState createState(AlertActivation p_activationState, Range p_limits) {
			LimitAlertConditionState LimitAlertCS(descriptorHandle, p_activationState, p_limits, AlertConditionMonitoredLimits::All);
			return LimitAlertCS;
		}

	};



	class PulseOximeterAlarmFingerOutHandler : public SDCProviderAlertConditionStateHandler<AlertConditionState>{
		public:
		PulseOximeterAlarmFingerOutHandler(std::string p_descriptorHandle) : SDCProviderAlertConditionStateHandler(p_descriptorHandle) {
			}

			//Changing the Limits
			InvocationState onStateChangeRequest(const AlertConditionState &, const OperationInvocationContext &) override {
				return InvocationState::Fail;

			}

			void sourceHasChanged(const std::string & )
			{

			}

			AlertConditionState getInitialState() override{
				auto AlertCS{createState(AlertActivation::Off)};
				return AlertCS;
			}

			void setActivationState(AlertActivation p_activationState)
			{
				auto currentState{*getParentProvider().getMdState().findState<AlertConditionState>(descriptorHandle)};
				currentState.setActivationState(p_activationState);
			}

		private:

			AlertConditionState createState(AlertActivation p_activationState) {
				AlertConditionState AlertCS{descriptorHandle, p_activationState};
				return AlertCS;
			}

		};



#endif /* EXAMPLES_PULSEOXIMETERPROVIDER_PULSEOXIMETERALARMSTATES_H_ */
