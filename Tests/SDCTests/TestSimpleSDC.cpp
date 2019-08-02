/**
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  *
  */

/*
 * TestSimpleSDC.cpp
 *
 *  @Copyright (C) 2017, SurgiTAIX AG
 *  Author: besting, buerger, roehser
 *
 *	This unit test covers the basic functionality of the SDC library
 *
 *	1. 3 different kinds of Metrices (numeric, string, enum) are tested regarding
 *	- eventing
 *	- requesting
 *	- settability
 *	2. An alert system is implemented. Automatic alerting is evaluated:
 *	- the referenced alert state () is changed (attribute presence is changed)
 *	- one metric is increased over time (handle_cur). The value is evaluated by a state handler (LimitAlertConditionStateHandler) referencing the handle_alert_condition.
 *		If the value is out of bound an alert is triggered. The logic is implemented in the user code! Only the defined limits are taken from the descriptor.
 *
 */





#include "SDCLib/SDCInstance.h"
#include "SDCLib/Data/SDC/SDCConsumer.h"
#include "SDCLib/Data/SDC/FutureInvocationState.h"
#include "SDCLib/Data/SDC/SDCProvider.h"
#include "SDCLib/Data/SDC/SDCProviderMDStateHandler.h"
#include "SDCLib/Data/SDC/SDCProviderAlertConditionStateHandler.h"
#include "SDCLib/Data/SDC/SDCProviderActivateOperationHandler.h"
#include "SDCLib/Data/SDC/SDCProviderComponentStateHandler.h"
#include "SDCLib/Data/SDC/SDCConsumerMDStateHandler.h"
#include "SDCLib/Data/SDC/MDIB/ActivateOperationDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/AllowedValue.h"
#include "SDCLib/Data/SDC/MDIB/LimitAlertConditionDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/LimitAlertConditionState.h"
#include "SDCLib/Data/SDC/MDIB/AlertSignalDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/AlertSignalState.h"
#include "SDCLib/Data/SDC/MDIB/AlertSystemDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/AlertSystemState.h"
#include "SDCLib/Data/SDC/MDIB/ChannelDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ChannelState.h"
#include "SDCLib/Data/SDC/MDIB/CodedValue.h"
#include "SDCLib/Data/SDC/MDIB/EnumStringMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/EnumStringMetricState.h"
#include "SDCLib/Data/SDC/MDIB/MdsDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/MdsState.h"
#include "SDCLib/Data/SDC/MDIB/InstanceIdentifier.h"
#include "SDCLib/Data/SDC/MDIB/LocalizedText.h"
#include "SDCLib/Data/SDC/MDIB/LocationContextDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/LocationContextState.h"
#include "SDCLib/Data/SDC/MDIB/MdDescription.h"
#include "SDCLib/Data/SDC/MDIB/MetricQuality.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricState.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricValue.h"
#include "SDCLib/Data/SDC/MDIB/OperatorContextDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/PatientContextDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/PatientContextState.h"
#include "SDCLib/Data/SDC/MDIB/PatientDemographicsCoreData.h"
#include "SDCLib/Data/SDC/MDIB/Range.h"
#include "SDCLib/Data/SDC/MDIB/StringMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/StringMetricState.h"
#include "SDCLib/Data/SDC/MDIB/StringMetricValue.h"
#include "SDCLib/Data/SDC/MDIB/SystemContextDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/MetaData.h"
#include "SDCLib/Data/SDC/MDIB/VmdDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/VmdState.h"
#include "SDCLib/Data/SDC/MDIB/Udi.h"
#include "SDCLib/Data/SDC/MDIB/custom/OperationInvocationContext.h"
#include "SDCLib/Util/DebugOut.h"
#include "SDCLib/Util/Task.h"
#include "../AbstractSDCLibFixture.h"
#include "../UnitTest++/src/UnitTest++.h"

#include <memory>
#include <string>

#include "Poco/Event.h"

#include "OSELib/SDC/ServiceManager.h"

using namespace SDCLib;
using namespace SDCLib::Util;
using namespace SDCLib::Data::SDC;


// Some values to configure the test
const int LOOP_SLEEP = 200;
const int NUM_LOOPS_SLEEP = 2; // The number of loops to wait and let the provider run

const double WEIGHT_LOWER = 0.0;
const double WEIGHT_UPPER = 2.0;
const double WEIGHT_MAX = 2.5;
const double WEIGHT_INCR_PER_LOOP = 0.2;

namespace SDCLib {
namespace Tests {
namespace SimpleSDC {

//
// define handles and IDs
//

const std::string DEVICE_ENDPOINT_REFERENCE("EPR_1234");
const int DEFAULT_TIMEOUT(5000);

// Device's taxonomic description
const std::string MDS_HANDLE("sampleMDS");
const std::string VMD_DESCRIPTOR_HANDLE("vmd_descriptor");
const std::string CHANNEL_DESCRIPTOR_HANDLE("first_channel");

// Metrices
//
// all metrices are tested to be succesfully requested by the consumer from the provider
//
// 1. a provider side changing numeric metric representing a measured value
const std::string NUMERIC_METRIC_CURRENT_HANDLE("handle_cur");
// 2. a numeric metric representing a a limit for this changing value
// this value is set writable, thus the consumer is able to set it
const std::string NUMERIC_METRIC_MAX_HANDLE("handle_max");
// 3. a string metric which is also set by the consumer
const std::string STRING_METRIC_HANDLE("handle_str");
// 4. an enum metric is also tried to be set by the consumer with legal an illegal values
const std::string ENUM_METRIC_HANDLE("handle_enum");

// AlertSystem
//
// 1. a limit alert condition that consists of the bounds which must be kept by the handle_cur numeric metric state
// 		a LimitAlertConditionStateHandler with the same name checks compliance
const std::string ALERT_CONDITION_HANDLE("handle_alert_condition_limit");
// 2. an alert signal whose attribute presents is changed
const std::string ALERT_SIGNAL_HANDLE("handle_alert_signal");
// 3. an latching alert signal which latched state is checked
const std::string ALERT_SIGNAL_LATCHING_HANDLE("handle_alert_signal_latching");


// component state handler
const std::string ALERT_SYSTEM_HANDLE("handle_alert_system");
const std::string CMD_HANDLE("cmd_handle");


// context states
const std::string LOCATION_CONTEXT_HANDLE("location_context");
const std::string PATIENT_CONTEXT_HANDLE("patient_context");

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Consumer event handlers
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


class ExampleConsumerNumericHandler : public SDCConsumerMDStateHandler<NumericMetricState> {
public:
	ExampleConsumerNumericHandler(const std::string & descriptorHandle)
    : SDCConsumerMDStateHandler(descriptorHandle)
	{ }
    virtual ~ExampleConsumerNumericHandler() = default;

    void onStateChanged(const NumericMetricState & state) override {
        auto t_val = state.getMetricValue().getValue();
        DebugOut(DebugOut::Default, "SimpleSDC") << "Consumer: Received value changed of " << descriptorHandle << ": " << t_val << std::endl;
        m_weight = t_val;
        eventEMR.set();
    }

    void onOperationInvoked(const OperationInvocationContext & oic, InvocationState is) override {
        DebugOut(DebugOut::Default, "SimpleSDC") << "Consumer: Received operation invoked (ID, STATE) of " << descriptorHandle << ": " << oic.transactionId << ", " << EnumToString::convert(is) << std::endl;
    }

    double getWeight() const { return m_weight; }

	Poco::Event & getEventEMR() {
		return eventEMR;
	}

private:
    std::atomic<double> m_weight = ATOMIC_VAR_INIT(0.0);
    Poco::Event eventEMR;
};

class ExampleConsumerEnumStringMetricHandler : public SDCConsumerMDStateHandler<EnumStringMetricState> {
public:
	ExampleConsumerEnumStringMetricHandler(const std::string & descriptorHandle) : SDCConsumerMDStateHandler(descriptorHandle)
	{
	}

    virtual ~ExampleConsumerEnumStringMetricHandler() {

    }

    void onStateChanged(const EnumStringMetricState & state) override {
    	const std::string val(state.getMetricValue().getValue());
        DebugOut(DebugOut::Default, "SimpleSDC") << "Consumer: Received value changed of " << descriptorHandle << ": " << val << std::endl;
        eventEMR.set();
    }

    void onOperationInvoked(const OperationInvocationContext & oic, InvocationState is) override {
        DebugOut(DebugOut::Default, "SimpleSDC") << "Consumer: Received operation invoked (ID, STATE) of " << descriptorHandle << ": " << oic.transactionId << ", " << EnumToString::convert(is) << std::endl;
    }

	Poco::Event & getEventEMR() {
		return eventEMR;
	}

private:
    Poco::Event eventEMR;
};

class ExampleConsumerStringMetricHandler : public SDCConsumerMDStateHandler<StringMetricState> {
public:
	ExampleConsumerStringMetricHandler(const std::string & descriptorHandle) : SDCConsumerMDStateHandler(descriptorHandle)
	{
	}

    virtual ~ExampleConsumerStringMetricHandler() {

    }

    void onStateChanged(const StringMetricState & state) override {
    	const std::string val(state.getMetricValue().getValue());
        DebugOut(DebugOut::Default, "SimpleSDC") << "Consumer: Received value changed of " << handle << ": " << val << std::endl;
        eventEMR.set();
    }

    void onOperationInvoked(const OperationInvocationContext & oic, InvocationState is) override {
        DebugOut(DebugOut::Default, "SimpleSDC") << "Consumer: Received operation invoked (ID, STATE) of " << handle << ": " << oic.transactionId << ", " << EnumToString::convert(is) << std::endl;
    }

	Poco::Event & getEventEMR() {
		return eventEMR;
	}

private:
    const std::string handle;
    Poco::Event eventEMR;
};

class ExampleConsumerAlertSignalHandler : public SDCConsumerMDStateHandler<AlertSignalState> {
public:
	ExampleConsumerAlertSignalHandler(const std::string & descriptorHandle) : SDCConsumerMDStateHandler(descriptorHandle)
	{
	}

    virtual ~ExampleConsumerAlertSignalHandler() {

    }

    void onStateChanged(const AlertSignalState & state) override {
        DebugOut(DebugOut::Default, "SimpleSDC") << "Consumer: Received alert signal changed of " << descriptorHandle << ", presence = " << EnumToString::convert(state.getPresence()) << std::endl;
        if (state.getPresence() == AlertSignalPresence::Off) {
        	eventEAROff.set();
        }
        if (state.getPresence() == AlertSignalPresence::On) {
        	eventEAROn.set();
        }
        if (state.getPresence() == AlertSignalPresence::Latch) {
        	eventEARLatch.set();
        }
    }

    void onOperationInvoked(const OperationInvocationContext & oic, InvocationState is) override {
        DebugOut(DebugOut::Default, "SimpleSDC") << "Consumer: Received operation invoked (ID, STATE) of " << descriptorHandle << ": " << oic.transactionId << ", " << EnumToString::convert(is) << std::endl;
    }

	Poco::Event & getEventEAROff() {
		return eventEAROff;
	}

	Poco::Event & getEventEAROn() {
		return eventEAROn;
	}

	Poco::Event & getEventEARLatch() {
		return eventEARLatch;
	}

private:
    Poco::Event eventEAROff;
    Poco::Event eventEAROn;
    Poco::Event eventEARLatch;
};

// context state handlers

class ExampleLocationContextEventHandler : public SDCConsumerMDStateHandler<LocationContextState> {
public:

	ExampleLocationContextEventHandler(std::string descriptorHandle) : SDCConsumerMDStateHandler(descriptorHandle) {
	}

	virtual void onStateChanged(const LocationContextState & state) override {
        DebugOut(DebugOut::Default, "SimpleSDC") << "Consumer: Received location context values changed for handle" << state.getHandle() << std::endl;
  		eventEMR.set();
	}

	Poco::Event & getEventEMR() {
		return eventEMR;
	}

private:
	Poco::Event eventEMR;
};


class ExamplePatientContextEventHandler : public SDCConsumerMDStateHandler<PatientContextState> {
public:

	ExamplePatientContextEventHandler(std::string descriptorHandle) : SDCConsumerMDStateHandler(descriptorHandle) {
	}

	virtual void onStateChanged(const PatientContextState & state) override {
        DebugOut(DebugOut::Default, "SimpleSDC") << "Consumer: Received patient context values changed for handle" << state.getHandle() << std::endl;
  		eventEMR.set();
	}

	Poco::Event & getEventEMR() {
		return eventEMR;
	}

private:
	Poco::Event eventEMR;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Provider handlers
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Context states are handled like metrices or alerts

// Note:
// quasi-multi states can be implemented like single states as well. Since they have the same descriptor handle
// each time a multi state (which has the same descritptor handle but differs in the handle attribute) changes,
// the state hander is called. The user has to destinguish!

class LocationContextStateHandler : public SDCProviderMDStateHandler<LocationContextState> {
public:
	LocationContextStateHandler(std::string descriptorHandle) : SDCProviderMDStateHandler(descriptorHandle) {}
	virtual InvocationState onStateChangeRequest(const LocationContextState & state,  const OperationInvocationContext&) override {
		if (state.getDescriptorHandle() !=  LOCATION_CONTEXT_HANDLE)
			return InvocationState::Fail;

		DebugOut(DebugOut::Default, "SimpleSDC") << "Provider: ContextHandler received state change request" << std::endl;
		return InvocationState::Fin;
	}

	virtual LocationContextState getInitialState() override {
		LocationContextState locationContextState(descriptorHandle, "multistate1");
		return locationContextState;
	}

};

class PatientContextStateHandler : public SDCProviderMDStateHandler<PatientContextState> {
public:
	PatientContextStateHandler(std::string descriptorHandle) : SDCProviderMDStateHandler(descriptorHandle) {}
	virtual InvocationState onStateChangeRequest(const PatientContextState & state,  const OperationInvocationContext&) override {
		if (state.getDescriptorHandle() !=  PATIENT_CONTEXT_HANDLE)
			return InvocationState::Fail;

		DebugOut(DebugOut::Default, "SimpleSDC") << "Provider: ContextHandler received state change request" << std::endl;
		return InvocationState::Fin;
	}

	virtual PatientContextState getInitialState() override {
		PatientContextState patientContextState(descriptorHandle, "multistate1");
		return patientContextState;
	}

};


class MaxValueStateHandler : public SDCProviderMDStateHandler<NumericMetricState>
{
public:

    MaxValueStateHandler(std::string descriptorHandle)
	: SDCProviderMDStateHandler(descriptorHandle)
	{ }

    InvocationState onStateChangeRequest(const NumericMetricState & state, const OperationInvocationContext & oic) override {
        // Invocation has been fired as WAITING when entering this method
    	DebugOut(DebugOut::Default, "SimpleSDC") << "Provider: MaxValueStateHandler received state change request" << std::endl;

    	notifyOperationInvoked(oic, InvocationState::Start);

        // we can update here, but if we return Fin, the framework will also update
        updateState(state);

        // Usually, update the real device's state here.

        // Framework will update internal MDIB with the state's value and increase MDIB version
        return InvocationState::Fin;
    }

    // Helper method
    NumericMetricState createState() {
        auto t_result = NumericMetricState(descriptorHandle);
        t_result.setMetricValue(NumericMetricValue(MetricQuality(MeasurementValidity::Vld)).setValue(2.0))
                .setActivationState(ComponentActivation::On);
        return t_result;
    }

    NumericMetricState getInitialState() override {
        return createState();
    }

    // Convenience value getter
    double getMaxWeight() {
    	std::unique_ptr<NumericMetricState> result(getParentProvider().getMdState().findState<NumericMetricState>(NUMERIC_METRIC_MAX_HANDLE));
        // check if result is valid
        if (result != nullptr) {
        	// In real applications, check if state has an observed value and if the observed value has a value!
        	return result->getMetricValue().getValue();
        }
        DebugOut(DebugOut::Default, "SimpleSDC") << "Maximum weight metric not found." << std::endl;
        return 0;
    }
};





class CurValueStateHandler : public SDCProviderMDStateHandler<NumericMetricState>
{
public:

    CurValueStateHandler(std::string descriptorHandle)
	: SDCProviderMDStateHandler(descriptorHandle)
	{ }

	// define how to react on a request for a state change. This handler should not be set, thus always return Fail.
	InvocationState onStateChangeRequest(const NumericMetricState&, const OperationInvocationContext&) override {
		return InvocationState::Fail;
	}
    // Helper method
    NumericMetricState createState(double value) {
        auto t_result = NumericMetricState(descriptorHandle);
        t_result
            .setMetricValue(NumericMetricValue(MetricQuality(MeasurementValidity::Vld)).setValue(value))
            .setActivationState(ComponentActivation::On)
            .setDescriptorHandle(NUMERIC_METRIC_CURRENT_HANDLE)
            .setLifeTimePeriod(xml_schema::Duration(0,0,0,0,0,0,1));
        return t_result;
    }

    NumericMetricState getInitialState() override {
        return createState(0);
    }

    void setNumericValue(double value) {
        NumericMetricState currentWeightState = createState(value);
        // Call update function (this will update internal MDIB and increase MDIB version number)
        updateState(currentWeightState);
    }
};

class EnumStringMetricStateHandler : public SDCProviderMDStateHandler<EnumStringMetricState> {
public:

	EnumStringMetricStateHandler(std::string descriptorHandle) : SDCProviderMDStateHandler(descriptorHandle) {
    }

    InvocationState onStateChangeRequest(const EnumStringMetricState&, const OperationInvocationContext & oic) override {
        // Invocation has been fired as WAITING when entering this method
    	DebugOut(DebugOut::Default, "SimpleSDC") << "Provider: EnumStringMetricStateHandler received state change request" << std::endl;
    	notifyOperationInvoked(oic, InvocationState::Start);

        // we can update here, but if we return Fin, the framework will also notify
        //updateState(currentStringState);

        // Usually, update the real device's state here.

        return InvocationState::Fin;  // Framework will update internal MDIB with the state's value and increase MDIB version
    }

    // Helper method
    EnumStringMetricState createState(const std::string & value) {
        EnumStringMetricState result(descriptorHandle);
        result
            .setMetricValue(StringMetricValue(MetricQuality(MeasurementValidity::Vld)).setValue(value))
            .setActivationState(ComponentActivation::On);
        return result;
    }

    EnumStringMetricState getInitialState() override {
        return createState("hello");
    }

};

class StrValueStateHandler : public SDCProviderMDStateHandler<StringMetricState> {
public:

    StrValueStateHandler(std::string descriptorHandle) : SDCProviderMDStateHandler(descriptorHandle) {
    }

    InvocationState onStateChangeRequest(const StringMetricState&, const OperationInvocationContext & oic) override {
        // Invocation has been fired as WAITING when entering this method
    	DebugOut(DebugOut::Default, "SimpleSDC") << "Provider: StrValueStateHandler received state change request" << std::endl;
    	notifyOperationInvoked(oic, InvocationState::Start);

        // we can update here, but if we return Fin, the framework will also notify
        //updateState(currentStringState);

        // Usually, update the real device's state here.

        return InvocationState::Fin;  // Framework will update internal MDIB with the state's value and increase MDIB version
    }

    // Helper method
    StringMetricState createState(const std::string & value) {
        StringMetricState result(STRING_METRIC_HANDLE);
        result
            .setMetricValue(StringMetricValue(MetricQuality(MeasurementValidity::Vld)).setValue(value))
            .setActivationState(ComponentActivation::On);
        return result;
    }

    StringMetricState getInitialState() override {
        return createState("Test");
    }

    // Convenience setter
    void setStringValue(const std::string & value) {
        StringMetricState currentState = createState(value);
        updateState(currentState);
    }

};

class AlertSignalStateHandler : public SDCProviderMDStateHandler<AlertSignalState> {
public:

	AlertSignalStateHandler(std::string descriptorHandle) : SDCProviderMDStateHandler(descriptorHandle) {
    }

    InvocationState onStateChangeRequest(const AlertSignalState & state, const OperationInvocationContext & oic) override {
        // Invocation has been fired as WAITING when entering this method
    	DebugOut(DebugOut::Default, "SimpleSDC") << "Provider: AlertSignalStateHandler received state change: " << EnumToString::convert(state.getPresence()) << std::endl;

    	notifyOperationInvoked(oic, InvocationState::Start);

    	// Update the real device's state here (update device alarms)! Check state's presence and alertSignalState's presence values!

    	// we can update here, but if we return Fin, the framework will also notify
    	//updateState(state);

        return InvocationState::Fin;  // Framework will update internal MDIB with the state's value and increase MDIB version
    }

    // Helper method
    AlertSignalState createState() {
        AlertSignalState result(ALERT_SIGNAL_HANDLE, AlertActivation::On); // Reference alert signal descriptor's handle // Component is working
        result
            .setPresence(AlertSignalPresence::Off);  // No alarm signal
        return result;
    }

    AlertSignalState getInitialState() override {
        return createState();
    }

};

class LatchingAlertSignalStateHandler : public SDCProviderMDStateHandler<AlertSignalState> {
public:

	LatchingAlertSignalStateHandler(std::string descriptorHandle) : SDCProviderMDStateHandler(descriptorHandle) {
    }

    InvocationState onStateChangeRequest(const AlertSignalState & state, const OperationInvocationContext & oic) override {
        // Invocation has been fired as WAITING when entering this method
    	DebugOut(DebugOut::Default, "SimpleSDC") << "Provider: LatchingAlertSignalStateHandler received state change: " << EnumToString::convert(state.getPresence()) << std::endl;

    	notifyOperationInvoked(oic, InvocationState::Start);

    	// Update the real device's state here (update device alarms)! Check state's presence and alertSignalState's presence values!

    	// we can update here, but if we return Fin, the framework will also notify
    	//updateState(alertSignalState);

        return InvocationState::Fin;  // Framework will update internal MDIB with the state's value and increase MDIB version
    }

    // Helper method
    AlertSignalState createState() {
        AlertSignalState result(ALERT_SIGNAL_LATCHING_HANDLE, AlertActivation::On); // Reference alert signal descriptor's handle // Component is working
        result
            .setPresence(AlertSignalPresence::Off);  // No alarm signal
        return result;
    }

    AlertSignalState getInitialState() override {
        return createState();
    }

};

class LimitAlertConditionStateHandler : public SDCProviderAlertConditionStateHandler<LimitAlertConditionState> {
public:

	LimitAlertConditionStateHandler(std::string descriptorHandle)
	: SDCProviderAlertConditionStateHandler(descriptorHandle)
	{ }

    InvocationState onStateChangeRequest(const LimitAlertConditionState & state, const OperationInvocationContext & ) override {

        // Invocation has been fired as WAITING when entering this method
    	std::unique_ptr<LimitAlertConditionState> pCurrentState(getParentProvider().getMdState().findState<LimitAlertConditionState>(state.getDescriptorHandle()));
        if(!pCurrentState) {
            return InvocationState::Fail;
        }

    	DebugOut(DebugOut::Default, "SimpleSDC") << "Provider: LimitAlertConditionStateHandler received state change, presence = " << state.getPresence() << std::endl;
        if (state.getPresence() != pCurrentState->getPresence()) {
    		DebugOut(DebugOut::Default, "SimpleSDC") << "Provider: LimitAlertConditionStateHandler detected presence change to: " << state.getPresence() << std::endl;
    		// do something...
    	}

    	//we can update here, but if we return Fin, the framework will also notify
    	//updateState(*pCurrentState);

    	return InvocationState::Fin;  // Framework will update internal MDIB with the state's value and increase MDIB version
    }

    // this function monitors the observered metric which is defined by the Source attribute of the corresponding LimitAlertConditionDescriptor
    void sourceHasChanged(const std::string & sourceHandle) override {
    	DebugOut(DebugOut::Default, "SimpleSDC") << "Provider: LimitAlertConditionStateHandler monitored source state changed." << std::endl;

    	// Check limit and trigger alarm condition, if needed (this method will then take care of handling all signal states)
        std::unique_ptr<NumericMetricState> pSourceState(getParentProvider().getMdState().findState<NumericMetricState>(sourceHandle));

        std::unique_ptr<LimitAlertConditionState> pLimitAlertConditionState(getParentProvider().getMdState().findState<LimitAlertConditionState>(ALERT_CONDITION_HANDLE));
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
    	const auto limits(pLimitAlertConditionState->getLimits());
    	if (!limits.hasUpper()) {
    		return;
    	}
    	if (!limits.hasLower()) {
    		return;
    	}
    	const bool triggerAlarm(sourceValue.getValue() > limits.getUpper() || sourceValue.getValue() < limits.getLower());
   		setAlertConditionPresence(pLimitAlertConditionState->getDescriptorHandle(), triggerAlarm, OperationInvocationContext::none());
    }

	// Can be used to switch condition on and off (e.g. propagate input from real device). Currently not used in this test.
	void setPresence(bool presence) {
		// We do not need to update our state here, this will be done in onStateChangeRequest (will be called by the method we invoke next)
		setAlertConditionPresence(getDescriptorHandle(), presence, OperationInvocationContext::none());
	}

    // Helper method
    LimitAlertConditionState createState() {
        LimitAlertConditionState result(ALERT_CONDITION_HANDLE, AlertActivation::On, Range().setLower(0.0).setUpper(2.0), AlertConditionMonitoredLimits::All); // Reference alert signal descriptor's handle
        result
            .setPresence(false);
        return result;
    }

    LimitAlertConditionState getInitialState() override {
        return createState();
    }

};


class AlertSystemStateHandler : public SDCProviderMDStateHandler<AlertSystemState> {
public:

	AlertSystemStateHandler(std::string descriptorHandle)
	: SDCProviderMDStateHandler(descriptorHandle)
	{ }

	AlertSystemState getInitialState() override {
        AlertSystemState alertSystemState(descriptorHandle, AlertActivation::On);  // reference alert system descriptor's handle // Alert is activated
        return alertSystemState;
    }

	// define how to react on a request for a state change. This handler should not be set, thus always return Fail.
	InvocationState onStateChangeRequest(const AlertSystemState&, const OperationInvocationContext&) override {
		return InvocationState::Fail;
	}
};


// use this state handler for remote function calls
class CommandHandler : public SDCProviderActivateOperationHandler {
public:

	CommandHandler(std::string descriptorHandle) : SDCProviderActivateOperationHandler(descriptorHandle) {
    }

	InvocationState onActivateRequest(const OperationInvocationContext&) override {
		DebugOut(DebugOut::Default, "SimpleSDC") << "Provider: Received command!" << std::endl;
		return InvocationState::Fin;
	}
};

class AlwaysOnChannelStateHandler : public SDCProviderComponentStateHandler<ChannelState> {
public:
	AlwaysOnChannelStateHandler(const std::string & descriptorHandle) : SDCProviderComponentStateHandler(descriptorHandle){
    }

    // Helper method
    ChannelState createState() {
    	auto t_result = ChannelState(descriptorHandle);
        t_result
            .setActivationState(ComponentActivation::On);
        return t_result;
    }

    virtual ChannelState getInitialState() override {
    	ChannelState state = createState();
        return state;
    }
};


class AlwaysOnVmdStateHandler : public SDCProviderComponentStateHandler<VmdState> {
public:
	AlwaysOnVmdStateHandler(const std::string & descriptorHandle) : SDCProviderComponentStateHandler(descriptorHandle){
    }

    // Helper method
    VmdState createState() {
    	auto t_result = VmdState(descriptorHandle);
        t_result
            .setActivationState(ComponentActivation::On);
        return t_result;
    }

    virtual VmdState getInitialState() override {
    	VmdState state = createState();
        return state;
    }
};



class AlwaysOnMdsStateHandler : public SDCProviderComponentStateHandler<MdsState> {
public:
    AlwaysOnMdsStateHandler(const std::string & descriptorHandle) : SDCProviderComponentStateHandler(descriptorHandle){
    }

    // Helper method
    MdsState createState() {
        auto t_result = MdsState(descriptorHandle);
        t_result
            .setActivationState(ComponentActivation::On);
        return t_result;
    }

    virtual MdsState getInitialState() override {
        MdsState state = createState();
        return state;
    }
};



///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Provider
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

class SDCHoldingDeviceProvider : public Util::Task {
public:
    SDCHoldingDeviceProvider(SDCInstance_shared_ptr p_SDCInstance)
    :
    	m_sdcProvider(p_SDCInstance),
    	locationContextStateHandler(LOCATION_CONTEXT_HANDLE),
    	patientContextStateHandler(PATIENT_CONTEXT_HANDLE),
    	curValueState(NUMERIC_METRIC_CURRENT_HANDLE),
    	maxValueState(NUMERIC_METRIC_MAX_HANDLE),
    	enumState(ENUM_METRIC_HANDLE),
    	strValueState(STRING_METRIC_HANDLE),
    	alertSigHandler(ALERT_SIGNAL_HANDLE),
    	latchingAlertSigHandler(ALERT_SIGNAL_LATCHING_HANDLE),
    	limitAlertConditionHandler(ALERT_CONDITION_HANDLE),
    	alertSysHandler(ALERT_SYSTEM_HANDLE),
    	cmdHandler(CMD_HANDLE),
    	channelStateHandler(CHANNEL_DESCRIPTOR_HANDLE),
    	mdsStateHandler(MDS_HANDLE),
    	vmdStateHandler(VMD_DESCRIPTOR_HANDLE)
	{
    	m_sdcProvider.setEndpointReferenceByName(DEVICE_ENDPOINT_REFERENCE);

        // Define semantic meaning of weight unit "kg", which will be used for defining the
        // current weight and the max weight below.
        CodedValue unit(CodeIdentifier("MDCX_CODE_ID_KG"));
        unit	.setCodingSystem("OR.NET.Codings")
				.addConceptDescription(LocalizedText().setRef("uri/to/file.txt").setLang("en"));


    	//
        // Setup metric descriptors
        //

        // define properties of current weight metric
        NumericMetricDescriptor currentWeightMetric(NUMERIC_METRIC_CURRENT_HANDLE,
        		unit,
        		MetricCategory::Msrmt,
        		MetricAvailability::Cont,
        		2);

        // add additional information: averaging period of the measurement
        currentWeightMetric.setAveragingPeriod(xml_schema::Duration(0,0,0,0,0,1,0));

        //  define properties of enum metric
        EnumStringMetricDescriptor testEnumMetric(ENUM_METRIC_HANDLE,
        		CodedValue("MDCX_CODE_ID_ENUM")
        			.setCodingSystem("OR.NET.Codings")
        			.addConceptDescription(LocalizedText().setRef("uri/to/file.txt").setLang("en")),
        		MetricCategory::Set,
        		MetricAvailability::Cont);

        testEnumMetric
			.addAllowedValue(AllowedValue("hello"))
			.addAllowedValue(AllowedValue("hallo"))
			.addAllowedValue(AllowedValue("bon jour"));


        // define properties of max weight metric
        NumericMetricDescriptor maxWeightMetric(NUMERIC_METRIC_MAX_HANDLE,
        		unit,
        		MetricCategory::Set,
        		MetricAvailability::Cont,
        		1);

        // define properties of test string metric
        StringMetricDescriptor testStringMetric(STRING_METRIC_HANDLE,
        		CodedValue("MDCX_CODE_ID_STRING"),
        		MetricCategory::Set,
        		MetricAvailability::Cont);


        //
        // Contexts
        //

        // Location context
        LocationContextDescriptor location("location_context");
        PatientContextDescriptor patient("patient_context");


        //
		// Setup alert system
		//

        // alert condition that is monitoring the handle_cur
        LimitAlertConditionDescriptor limitAlertCondition(ALERT_CONDITION_HANDLE,
        		AlertConditionKind::Tec,
        		AlertConditionPriority::Me,
        		Range()
        			.setLower(WEIGHT_LOWER)
        			.setUpper(WEIGHT_UPPER)
        		);

        limitAlertCondition.setType(CodedValue("MDCX_CODE_ID_ALERT_WEIGHT_CONDITION").setCodingSystem("OR.NET.Codings")).addSource(NUMERIC_METRIC_CURRENT_HANDLE);

        // create signal for condition
        AlertSignalDescriptor alertSignal(ALERT_SIGNAL_HANDLE, AlertSignalManifestation::Vis, false);
        alertSignal
        	.setConditionSignaled(ALERT_CONDITION_HANDLE);

        AlertSignalDescriptor latchingAlertSignal(ALERT_SIGNAL_LATCHING_HANDLE, AlertSignalManifestation::Vis, true);
        latchingAlertSignal
			.setConditionSignaled(ALERT_CONDITION_HANDLE);

        // Alerts
        AlertSystemDescriptor alertSystem(ALERT_SYSTEM_HANDLE);
        alertSystem
			.addAlertSignal(alertSignal)
			.addAlertSignal(latchingAlertSignal)
			.addLimitAlertCondition(limitAlertCondition);


        //
        // assemble everything following the taxonomic structure of the device
        //

        // Channel
        ChannelDescriptor holdingDeviceChannel(CHANNEL_DESCRIPTOR_HANDLE);
        holdingDeviceChannel
			.addMetric(currentWeightMetric)
			.addMetric(testEnumMetric)
        	.addMetric(maxWeightMetric)
        	.addMetric(testStringMetric)
			.setSafetyClassification(SafetyClassification::MedA);

        // VMD
        VmdDescriptor holdingDeviceModule(VMD_DESCRIPTOR_HANDLE);
        holdingDeviceModule
        	.setAlertSystem(alertSystem)
			.setHandle(VMD_DESCRIPTOR_HANDLE)
			.addChannel(holdingDeviceChannel);

        // MDS
        MdsDescriptor holdingDeviceSystem(MDS_HANDLE);
        holdingDeviceSystem
        	.setMetaData(
        		MetaData().addManufacturer(LocalizedText().setRef("SurgiTAIX AG"))
        		.setModelNumber("1")
        		.addModelName(LocalizedText().setRef("EndoTAIX"))
        		.addSerialNumber("1234-5678"))
			.setSystemContext(
				SystemContextDescriptor("MDC_SYS_CON")
			    .setPatientContext(
			    		patient)
				.setLocationContext(
						location)
				)
			.addVmd(holdingDeviceModule)
			.setType(
                CodedValue("MDCX_CODE_ID_MDS")
                .setCodingSystem("OR.NET.Codings"));

        m_sdcProvider.createSetOperationForDescriptor(alertSignal, holdingDeviceSystem);
        m_sdcProvider.createSetOperationForDescriptor(maxWeightMetric, holdingDeviceSystem);
        m_sdcProvider.createSetOperationForDescriptor(testEnumMetric, holdingDeviceSystem);
        m_sdcProvider.createSetOperationForDescriptor(testStringMetric, holdingDeviceSystem);
        m_sdcProvider.createSetOperationForDescriptor(location, holdingDeviceSystem);
        m_sdcProvider.createSetOperationForDescriptor(patient, holdingDeviceSystem);

        ActivateOperationDescriptor aod(CMD_HANDLE, NUMERIC_METRIC_MAX_HANDLE);
        aod.setRetriggerable(true);

		m_sdcProvider.addActivateOperationForDescriptor(aod, holdingDeviceSystem);

		// create and add description
		MdDescription mdDescription;
		mdDescription.addMdsDescriptor(holdingDeviceSystem);

		m_sdcProvider.setMdDescription(mdDescription);

        // State handlers

		m_sdcProvider.addMdStateHandler(&locationContextStateHandler);
		m_sdcProvider.addMdStateHandler(&patientContextStateHandler);
		m_sdcProvider.addMdStateHandler(&curValueState);
		m_sdcProvider.addMdStateHandler(&enumState);
		m_sdcProvider.addMdStateHandler(&maxValueState);
		m_sdcProvider.addMdStateHandler(&strValueState);
		m_sdcProvider.addMdStateHandler(&limitAlertConditionHandler);
		m_sdcProvider.addMdStateHandler(&alertSigHandler);
		m_sdcProvider.addMdStateHandler(&latchingAlertSigHandler);
		m_sdcProvider.addMdStateHandler(&alertSysHandler);
		m_sdcProvider.addMdStateHandler(&cmdHandler);
		m_sdcProvider.addMdStateHandler(&channelStateHandler);
		m_sdcProvider.addMdStateHandler(&mdsStateHandler);
		m_sdcProvider.addMdStateHandler(&vmdStateHandler);
	}

    MdDescription getMdDescription() {
    	return m_sdcProvider.getMdDescription();
    }

    void startup() {
    	m_sdcProvider.startup();
    }

    void shutdown() {
    	m_sdcProvider.shutdown();
    }

    // Update weight periodically
    virtual void runImpl() override {
    	auto nextWeight = m_currentWeight + WEIGHT_INCR_PER_LOOP;
    	if (nextWeight > WEIGHT_MAX) {
    		nextWeight = 0.0;
    	}
		setCurrentWeight(nextWeight);
		std::this_thread::sleep_for(std::chrono::milliseconds(LOOP_SLEEP));
    }

    void setCurrentWeight(double p_value)
    {
        m_currentWeight = p_value;
        curValueState.setNumericValue(p_value);
        DebugOut(DebugOut::Default, "SimpleSDC") << "Changed value: " << m_currentWeight << std::endl;
        strValueState.setStringValue(std::string("Test ") + std::to_string(p_value));
    }

private:

    // Provider object
    SDCProvider m_sdcProvider;

    double m_currentWeight = 0;

    // State (handlers)
    LocationContextStateHandler locationContextStateHandler;
    PatientContextStateHandler patientContextStateHandler;

    CurValueStateHandler curValueState;
    MaxValueStateHandler maxValueState;
    EnumStringMetricStateHandler enumState;
    StrValueStateHandler strValueState;

    AlertSignalStateHandler alertSigHandler;
    LatchingAlertSignalStateHandler latchingAlertSigHandler;
    LimitAlertConditionStateHandler limitAlertConditionHandler;
    AlertSystemStateHandler alertSysHandler;
    CommandHandler cmdHandler;
    AlwaysOnChannelStateHandler channelStateHandler;
    AlwaysOnMdsStateHandler mdsStateHandler;
    AlwaysOnVmdStateHandler vmdStateHandler;
};

}
}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Test
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct FixtureSimpleSDC : Tests::AbstractSDCLibFixture {
	FixtureSimpleSDC() : AbstractSDCLibFixture("FixtureSimpleSDC", OSELib::LogLevel::Error) {}
};

SUITE(SDC) {
TEST_FIXTURE(FixtureSimpleSDC, SimpleSDC)
{
	DebugOut::openLogFile("Test.log.txt", true);
	try
	{
        auto t_SDCInstance = createSDCInstance();

        // Provider
        Tests::SimpleSDC::SDCHoldingDeviceProvider provider(t_SDCInstance);
        provider.startup();
        provider.start();

        // MdDescription test
        MdDescription mdDescription =  provider.getMdDescription();
        // add and remove a test MDS
        MdsDescriptor mds_test("MDC_MDS_HANDLE");
        mdDescription.addMdsDescriptor(mds_test);
        CHECK_EQUAL(true, mdDescription.removeMdsDescriptor(mds_test));
        DebugOut(DebugOut::Default, std::cout, m_details.testName) << "Discover EPR...";

        // Consumer
        OSELib::SDC::ServiceManager t_serviceManager(t_SDCInstance);
        auto t_consumer(t_serviceManager.discoverEndpointReference(SDCLib::SDCInstance::calcUUIDv5(Tests::SimpleSDC::DEVICE_ENDPOINT_REFERENCE, true)));

        // create state handlers
        Tests::SimpleSDC::ExampleConsumerNumericHandler eces1(Tests::SimpleSDC::NUMERIC_METRIC_CURRENT_HANDLE);
        Tests::SimpleSDC::ExampleConsumerNumericHandler eces2(Tests::SimpleSDC::NUMERIC_METRIC_MAX_HANDLE);
        Tests::SimpleSDC::ExampleConsumerStringMetricHandler eces3(Tests::SimpleSDC::STRING_METRIC_HANDLE);
        Tests::SimpleSDC::ExampleConsumerEnumStringMetricHandler eces4(Tests::SimpleSDC::ENUM_METRIC_HANDLE);
        Tests::SimpleSDC::ExampleConsumerAlertSignalHandler alertSignalsink(Tests::SimpleSDC::ALERT_SIGNAL_HANDLE);
        Tests::SimpleSDC::ExampleConsumerAlertSignalHandler latchingAlertSignalsink(Tests::SimpleSDC::ALERT_SIGNAL_LATCHING_HANDLE);
        Tests::SimpleSDC::ExampleLocationContextEventHandler locationEventHandler(Tests::SimpleSDC::LOCATION_CONTEXT_HANDLE);
        Tests::SimpleSDC::ExamplePatientContextEventHandler  patientEventHandler(Tests::SimpleSDC::PATIENT_CONTEXT_HANDLE);


        // Discovery test
        CHECK_EQUAL(true, t_consumer != nullptr);

		if (t_consumer != nullptr) {
            // MDIB test
            MdibContainer mdib(t_consumer->getMdib());

            { // test access to system metadata of mds implemented by provider above
            	std::unique_ptr<MdsDescriptor> pMdsDescriptor(mdib.getMdDescription().findDescriptor<MdsDescriptor>(Tests::SimpleSDC::MDS_HANDLE));
            	if (pMdsDescriptor != nullptr) {
            		if (pMdsDescriptor->hasMetaData()) {
            			const MetaData metadata(pMdsDescriptor->getMetaData());

            			if (!metadata.getUdiList().empty()) {
							const std::string serialNumber(metadata.getSerialNumberList().at(0));
							CHECK_EQUAL("1234-5678",serialNumber);
            			}

            		}
            	}
            }

            { // test presence of system context descriptors
            	std::unique_ptr<MdsDescriptor> pMdsDescriptor(mdib.getMdDescription().findDescriptor<MdsDescriptor>(Tests::SimpleSDC::MDS_HANDLE));
            	if (pMdsDescriptor != nullptr) {
            		SystemContextDescriptor sc(pMdsDescriptor->getSystemContext());
            		CHECK_EQUAL(true, sc.hasPatientContext());
            		CHECK_EQUAL(true, sc.getOperatorContextList().empty());
            	}
            }
            {	// lookup descriptors that should exist for the provider implemented above
            	std::unique_ptr<NumericMetricDescriptor> pNumericMetricDescriptor(mdib.getMdDescription().findDescriptor<NumericMetricDescriptor>(Tests::SimpleSDC::NUMERIC_METRIC_CURRENT_HANDLE));
            	if (pNumericMetricDescriptor != nullptr) {
				CHECK_EQUAL("en", pNumericMetricDescriptor->getUnit().getConceptDescriptionList()[0].getLang());
				}
				std::unique_ptr<StringMetricDescriptor> pStringMetricDescriptor(mdib.getMdDescription().findDescriptor<StringMetricDescriptor>(Tests::SimpleSDC::STRING_METRIC_HANDLE));
				CHECK_EQUAL(true, pStringMetricDescriptor != nullptr);
				CHECK_EQUAL(Tests::SimpleSDC::STRING_METRIC_HANDLE, pStringMetricDescriptor->getHandle());
            }

            // Register for consumer events
            CHECK_EQUAL(true, t_consumer->registerStateEventHandler(&eces1));
            CHECK_EQUAL(true, t_consumer->registerStateEventHandler(&eces2));
            CHECK_EQUAL(true, t_consumer->registerStateEventHandler(&eces3));
            CHECK_EQUAL(true, t_consumer->registerStateEventHandler(&eces4));
            // Register for alert signal events
            CHECK_EQUAL(true, t_consumer->registerStateEventHandler(&alertSignalsink));
            CHECK_EQUAL(true, t_consumer->registerStateEventHandler(&latchingAlertSignalsink));
            // Register for context changed events
            CHECK_EQUAL(true, t_consumer->registerStateEventHandler(&locationEventHandler));
            CHECK_EQUAL(true, t_consumer->registerStateEventHandler(&patientEventHandler));

            DebugOut(DebugOut::Default, std::cout, m_details.testName) << "Waiting...";
            // Note: Min 1 Loop sleep
            std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(LOOP_SLEEP*1.1)));

            {	// Ensure that requests for wrong handles fail.
                DebugOut(DebugOut::Default, m_details.testName) << "Numeric test..." << std::endl;
                DebugOut(DebugOut::Default, m_details.testName) << "SHOULD FAIL: " << std::endl;
				NumericMetricState tempState(" ");
				std::unique_ptr<NumericMetricState> pTempNMS(t_consumer->requestState<NumericMetricState>("unknown"));
            	CHECK_EQUAL(false, pTempNMS != nullptr);
            }
            {	// Request state of current weight
                std::unique_ptr<NumericMetricState> pTempNMS(t_consumer->requestState<NumericMetricState>(Tests::SimpleSDC::NUMERIC_METRIC_CURRENT_HANDLE));
				CHECK_EQUAL(true, pTempNMS != nullptr);
				CHECK_EQUAL(true, pTempNMS->hasMetricValue());
				if (pTempNMS->hasMetricValue()) {
					const double curWeight(pTempNMS->getMetricValue().getValue());
					CHECK_EQUAL(true, curWeight > WEIGHT_INCR_PER_LOOP*0.5);
				}
            }
            {	// Ensure that (read-only) metrics without matching SetOperation cannot be set.
                DebugOut(DebugOut::Default, m_details.testName) << "SHOULD FAIL: " << std::endl;
                std::unique_ptr<NumericMetricState> pTempNMS(t_consumer->requestState<NumericMetricState>(Tests::SimpleSDC::NUMERIC_METRIC_CURRENT_HANDLE));
            	CHECK_EQUAL(true, pTempNMS != nullptr);
                CHECK_EQUAL(true, InvocationState::Fail == t_consumer->commitState(*pTempNMS));
            }
            {	// Get state of maximum weight
                std::unique_ptr<NumericMetricState> pTempNMS(t_consumer->requestState<NumericMetricState>(Tests::SimpleSDC::NUMERIC_METRIC_MAX_HANDLE));
				CHECK_EQUAL(true, pTempNMS != nullptr);
				double maxWeight = pTempNMS->getMetricValue().getValue();
				CHECK_EQUAL(2.0, maxWeight);
            }
            {	// Get state of test enum
                std::unique_ptr<EnumStringMetricState> pTempESMS(t_consumer->requestState<EnumStringMetricState>(Tests::SimpleSDC::ENUM_METRIC_HANDLE));
				CHECK_EQUAL(true, pTempESMS != nullptr);
				const std::string enumValue(pTempESMS->getMetricValue().getValue());
				CHECK_EQUAL("hello", enumValue);
            }
            {	// Set state of test enum with allowed enum value
                std::unique_ptr<EnumStringMetricState> pTempESMS(t_consumer->requestState<EnumStringMetricState>(Tests::SimpleSDC::ENUM_METRIC_HANDLE));
            	CHECK_EQUAL(true, pTempESMS != nullptr);

            	pTempESMS->setMetricValue(pTempESMS->getMetricValue().setValue("bon jour"));
				FutureInvocationState fis;
				CHECK_EQUAL(true, InvocationState::Wait == t_consumer->commitState(*pTempESMS, fis));
				CHECK_EQUAL(true, fis.waitReceived(InvocationState::Fin, Tests::SimpleSDC::DEFAULT_TIMEOUT));
            }
            {	// Set state of test enum with illegal enum value
                std::unique_ptr<EnumStringMetricState> pTempESMS(t_consumer->requestState<EnumStringMetricState>(Tests::SimpleSDC::ENUM_METRIC_HANDLE));
            	CHECK_EQUAL(true, pTempESMS != nullptr);

				const std::string enumValue(pTempESMS->getMetricValue().getValue());
				CHECK_EQUAL("bon jour", enumValue);

				pTempESMS->setMetricValue(pTempESMS->getMetricValue().setValue("bye"));
				FutureInvocationState fis;
				t_consumer->commitState(*pTempESMS, fis);
				CHECK_EQUAL(true, fis.waitReceived(InvocationState::Fail, Tests::SimpleSDC::DEFAULT_TIMEOUT));
            }

            // Wait here and let the current value exceed max value. This will trigger alert condition presence which in turn
            // will trigger an alert signal presence (Off -> On -> Latch)!
            auto t_waitTime0 = LOOP_SLEEP * (WEIGHT_UPPER / WEIGHT_INCR_PER_LOOP)*NUM_LOOPS_SLEEP;
			std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(t_waitTime0)));

			{	// Set state test for a numeric metric state (must succeed, use state handle instead of descriptor handle)
                std::unique_ptr<NumericMetricState> pTempNMS(t_consumer->requestState<NumericMetricState>(Tests::SimpleSDC::NUMERIC_METRIC_MAX_HANDLE));
				CHECK_EQUAL(true, pTempNMS != nullptr);

				// Here, we increase max weight to switch condition presence => results in alert signal presence
				pTempNMS->setMetricValue(pTempNMS->getMetricValue().setValue(10));
				FutureInvocationState fis;
				CHECK_EQUAL(true, InvocationState::Wait == t_consumer->commitState(*pTempNMS, fis));
				CHECK_EQUAL(true, fis.waitReceived(InvocationState::Fin, Tests::SimpleSDC::DEFAULT_TIMEOUT));
			}

            {	// Set state test for a string metric state (must succeed)
                DebugOut(DebugOut::Default, m_details.testName) << "String test...";
                std::unique_ptr<StringMetricState> pTempNMS(t_consumer->requestState<StringMetricState>(Tests::SimpleSDC::STRING_METRIC_HANDLE));
				CHECK_EQUAL(true, pTempNMS != nullptr);

				pTempNMS->setMetricValue(pTempNMS->getMetricValue().setValue("Test2"));
				FutureInvocationState fis;
				CHECK_EQUAL(true, InvocationState::Wait == t_consumer->commitState(*pTempNMS, fis));
                CHECK_EQUAL(true, fis.waitReceived(InvocationState::Fin, Tests::SimpleSDC::DEFAULT_TIMEOUT));
            }

            {	// Activate test
                DebugOut(DebugOut::Default, m_details.testName) << "Activate test...";
                FutureInvocationState fis;
				CHECK_EQUAL(true, InvocationState::Wait == t_consumer->activate(Tests::SimpleSDC::CMD_HANDLE, fis));
				CHECK_EQUAL(true, fis.waitReceived(InvocationState::Fin, Tests::SimpleSDC::DEFAULT_TIMEOUT));
            }

            {	// Location context test
                DebugOut(DebugOut::Default, m_details.testName) << "Location context test...";
                // todo: check here if working!
                LocationContextState lcs(Tests::SimpleSDC::LOCATION_CONTEXT_HANDLE, "location_context_state");
                lcs.setContextAssociation(ContextAssociation::Assoc);
                lcs.addIdentification(InstanceIdentifier().setRoot("hello").setExtension("world"));
                FutureInvocationState fis;
                locationEventHandler.getEventEMR().reset();
                CHECK_EQUAL(true, InvocationState::Wait == t_consumer->commitState(lcs, fis));
				CHECK_EQUAL(true, locationEventHandler.getEventEMR().tryWait(3000));
				CHECK_EQUAL(true, fis.waitReceived(InvocationState::Fin, Tests::SimpleSDC::DEFAULT_TIMEOUT));
				DebugOut(DebugOut::Default, m_details.testName) << "Location context test done...";
            }
            {	// Patient context test
                DebugOut(DebugOut::Default, m_details.testName) << "Patient context test...";
				PatientContextState pcs(Tests::SimpleSDC::PATIENT_CONTEXT_HANDLE, "patient_context_state");
				pcs.setContextAssociation(ContextAssociation::Assoc);
				pcs.addIdentification(InstanceIdentifier().setRoot("hello").setExtension("world"));
				pcs.setCoreData(PatientDemographicsCoreData()
						.setGivenname("Max")
						.setBirthname("")
						.setFamilyname("Mustermann"));
						// FIXME: DateOfBirth does not work yet -> schema validation fail because union is not rightly implemented
						//.setDateOfBirth("08.05.1945"));
				FutureInvocationState fis;
				patientEventHandler.getEventEMR().reset();
				CHECK_EQUAL(true, InvocationState::Wait == t_consumer->commitState(pcs, fis));

				CHECK_EQUAL(true, patientEventHandler.getEventEMR().tryWait(3000));

				CHECK_EQUAL(true, fis.waitReceived(InvocationState::Fin, Tests::SimpleSDC::DEFAULT_TIMEOUT));
				DebugOut(DebugOut::Default, m_details.testName) << "Patient context test done...";
			}
            // Run for some time to receive and display incoming metric events.
            auto t_waitTime1 = LOOP_SLEEP * (WEIGHT_UPPER / WEIGHT_INCR_PER_LOOP)*NUM_LOOPS_SLEEP;
			std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(t_waitTime1)));

			// Stop dummy events created by provider
			provider.interrupt();

			{	// Switch alert signal state off
                std::unique_ptr<AlertSignalState> pTempASS(t_consumer->requestState<AlertSignalState>(Tests::SimpleSDC::ALERT_SIGNAL_HANDLE));
				CHECK_EQUAL(true, pTempASS != nullptr);


				pTempASS->setPresence(AlertSignalPresence::Off);
				FutureInvocationState fis;
				CHECK_EQUAL(true, InvocationState::Wait == t_consumer->commitState(*pTempASS, fis));
				CHECK_EQUAL(true, fis.waitReceived(InvocationState::Fin, Tests::SimpleSDC::DEFAULT_TIMEOUT));
			}

            auto t_waitTime2 = LOOP_SLEEP * (WEIGHT_UPPER / WEIGHT_INCR_PER_LOOP)*NUM_LOOPS_SLEEP;
			std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(t_waitTime2)));

            CHECK_EQUAL(true, eces1.getWeight() > 0);

            CHECK_EQUAL(true, eces1.getEventEMR().tryWait(Tests::SimpleSDC::DEFAULT_TIMEOUT));
            CHECK_EQUAL(true, eces2.getEventEMR().tryWait(Tests::SimpleSDC::DEFAULT_TIMEOUT));
            CHECK_EQUAL(true, eces3.getEventEMR().tryWait(Tests::SimpleSDC::DEFAULT_TIMEOUT));
            CHECK_EQUAL(true, eces4.getEventEMR().tryWait(Tests::SimpleSDC::DEFAULT_TIMEOUT));

            CHECK_EQUAL(true, alertSignalsink.getEventEAROff().tryWait(Tests::SimpleSDC::DEFAULT_TIMEOUT));
            CHECK_EQUAL(true, alertSignalsink.getEventEAROn().tryWait(Tests::SimpleSDC::DEFAULT_TIMEOUT));
            CHECK_EQUAL(true, latchingAlertSignalsink.getEventEARLatch().tryWait(Tests::SimpleSDC::DEFAULT_TIMEOUT));



            CHECK_EQUAL(true, t_consumer->unregisterStateEventHandler(&eces1));
            CHECK_EQUAL(true, t_consumer->unregisterStateEventHandler(&eces2));
            CHECK_EQUAL(true, t_consumer->unregisterStateEventHandler(&eces3));
            CHECK_EQUAL(true, t_consumer->unregisterStateEventHandler(&eces4));
            CHECK_EQUAL(true, t_consumer->unregisterStateEventHandler(&alertSignalsink));
            CHECK_EQUAL(true, t_consumer->unregisterStateEventHandler(&latchingAlertSignalsink));

            t_consumer->setContextStateChangedHandler(nullptr);

            DebugOut(DebugOut::Default, m_details.testName) << "Finished...";

            t_consumer->disconnect();
        }
        provider.shutdown();
    } catch (char const* exc) {
		DebugOut(DebugOut::Default, std::cerr, m_details.testName) << exc;
	} catch (...) {
		DebugOut(DebugOut::Default, std::cerr, m_details.testName) << "Unknown exception occurred!";
	}
	DebugOut::closeLogFile();
}
}
