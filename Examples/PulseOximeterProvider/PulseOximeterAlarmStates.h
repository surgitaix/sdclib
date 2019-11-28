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
		PulseOximeterAlarmLimitPulseRateHandler(std::string descriptorHandle) : SDCProviderAlertConditionStateHandler(descriptorHandle) {
		}

		//Changing the Limits
		InvocationState onStateChangeRequest(const LimitAlertConditionState &state, const OperationInvocationContext &oic) override {
			Range maxLimits = getParentProvider().getMdDescription().findDescriptor<LimitAlertConditionDescriptor>(state.getDescriptorHandle())->getMaxLimits();
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

		void sourceHasChanged(const std::string & sourceHandle)
		{
			std::unique_ptr<NumericMetricState> pSourceState(getParentProvider().getMdState().findState<NumericMetricState>(sourceHandle));
			LimitAlertConditionState currentState(*getParentProvider().getMdState().findState<LimitAlertConditionState>(descriptorHandle));
			Range currentLimits = currentState.getLimits();
			double currentValue = pSourceState->getMetricValue().getValue();
			if(currentValue < currentLimits.getLower())
			{
				std::cout << "ALARM! " << sourceHandle << currentValue <<  std::endl;
			}
			else if(currentValue > currentLimits.getUpper())
			{
				std::cout << "ALARM! " << sourceHandle << currentValue << std::endl;
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

		void setLimitRange(Range limits)
		{
			LimitAlertConditionState currentState(*getParentProvider().getMdState().findState<LimitAlertConditionState>(descriptorHandle));
			currentState.setLimits(limits);
		}

		void setActivationState(AlertActivation activationState)
		{
			LimitAlertConditionState currentState(*getParentProvider().getMdState().findState<LimitAlertConditionState>(descriptorHandle));
			currentState.setActivationState(activationState);
		}


	private:
		LimitAlertConditionState createState(AlertActivation activationState, Range limits) {
			LimitAlertConditionState LimitAlertCS(descriptorHandle, activationState, limits, AlertConditionMonitoredLimits::All);
			return LimitAlertCS;
		}

	};


	class PulseOximeterAlarmLimitSatO2Handler : public SDCProviderAlertConditionStateHandler<LimitAlertConditionState>{
	public:
		PulseOximeterAlarmLimitSatO2Handler(std::string descriptorHandle) : SDCProviderAlertConditionStateHandler(descriptorHandle) {
		}

		//Changing the Limits
		InvocationState onStateChangeRequest(const LimitAlertConditionState &state, const OperationInvocationContext &oic) override {
			Range maxLimits = getParentProvider().getMdDescription().findDescriptor<LimitAlertConditionDescriptor>(state.getDescriptorHandle())->getMaxLimits();
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

		void sourceHasChanged(const std::string & sourceHandle)
		{
			std::unique_ptr<NumericMetricState> pSourceState(getParentProvider().getMdState().findState<NumericMetricState>(sourceHandle));
			LimitAlertConditionState currentState(*getParentProvider().getMdState().findState<LimitAlertConditionState>(descriptorHandle));
			Range currentLimits = currentState.getLimits();
			double currentValue = pSourceState->getMetricValue().getValue();
			if(currentValue < currentLimits.getLower())
			{
				std::cout << "ALARM! " << sourceHandle << currentValue <<  std::endl;
			}
			else if(currentValue > currentLimits.getUpper())
			{
				std::cout << "ALARM! " << sourceHandle << currentValue << std::endl;
			}
		}


		LimitAlertConditionState getInitialState() override{
			Range limits;
			limits.setLower(DEFAULT_LOWER_SAT_O2_ALARM_LIMIT);
			limits.setUpper(DEFAULT_UPPER_SAT_O2_ALARM_LIMIT);
			limits.setAbsoluteAccuracy(DEFAULT_SAT_O2_ALARM_LIMIT_ABSOLUTE_ACCURACY);
			LimitAlertConditionState LimitAlertCS = createState(AlertActivation::Off, limits);
			return LimitAlertCS;
		}

		void setLimitRange(Range limits)
		{
			LimitAlertConditionState currentState(*getParentProvider().getMdState().findState<LimitAlertConditionState>(descriptorHandle));
			currentState.setLimits(limits);
		}

		void setActivationState(AlertActivation activationState)
		{
			LimitAlertConditionState currentState(*getParentProvider().getMdState().findState<LimitAlertConditionState>(descriptorHandle));
			currentState.setActivationState(activationState);
		}

	private:

		LimitAlertConditionState createState(AlertActivation activationState, Range limits) {
			LimitAlertConditionState LimitAlertCS(descriptorHandle, activationState, limits, AlertConditionMonitoredLimits::All);
			return LimitAlertCS;
		}

	};



	class PulseOximeterAlarmFingerOutHandler : public SDCProviderAlertConditionStateHandler<AlertConditionState>{
		public:
		PulseOximeterAlarmFingerOutHandler(std::string descriptorHandle) : SDCProviderAlertConditionStateHandler(descriptorHandle) {
			}

			//Changing the Limits
			InvocationState onStateChangeRequest(const AlertConditionState &state, const OperationInvocationContext &oic) override {
				return InvocationState::Fail;

			}

			void sourceHasChanged(const std::string & sourceHandle)
			{

			}

			AlertConditionState getInitialState() override{
				AlertConditionState AlertCS = createState(AlertActivation::Off);
				return AlertCS;
			}

			void setActivationState(AlertActivation activationState)
			{
				AlertConditionState currentState(*getParentProvider().getMdState().findState<AlertConditionState>(descriptorHandle));
				currentState.setActivationState(activationState);
			}

		private:

			AlertConditionState createState(AlertActivation activationState) {
				AlertConditionState AlertCS(descriptorHandle, activationState);
				return AlertCS;
			}

		};



#endif /* EXAMPLES_PULSEOXIMETERPROVIDER_PULSEOXIMETERALARMSTATES_H_ */
