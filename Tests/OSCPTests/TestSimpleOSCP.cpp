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
 * TestSimpleOSCP.cpp
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





#include "OSCLib/OSCLibrary.h"
#include "OSCLib/Data/OSCP/OSCPConsumer.h"
#include "OSCLib/Data/OSCP/FutureInvocationState.h"
#include "OSCLib/Data/OSCP/OSCPConsumerEventHandler.h"
#include "OSCLib/Data/OSCP/OSCPConsumerEnumStringMetricStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPConsumerNumericMetricStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPConsumerStringMetricStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPConsumerAlertSignalStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPConsumerSystemContextStateChangedHandler.h"
#include "OSCLib/Data/OSCP/OSCPProvider.h"
#include "OSCLib/Data/OSCP/OSCPProviderActivateOperationHandler.h"
#include "OSCLib/Data/OSCP/OSCPProviderLimitAlertConditionStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPProviderAlertSignalStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPProviderAlertSystemStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPProviderSystemContextStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPProviderEnumStringMetricStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPProviderMdsStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPProviderNumericMetricStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPProviderStringMetricStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPProviderChannelStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPProviderVmdStateHandler.h"
#include "OSCLib/Data/OSCP/MDIB/ActivateOperationDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AllowedValue.h"
#include "OSCLib/Data/OSCP/MDIB/LimitAlertConditionDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/LimitAlertConditionState.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSignalDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSignalState.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSystemDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSystemState.h"
#include "OSCLib/Data/OSCP/MDIB/ChannelDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ChannelState.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/EnumStringMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/EnumStringMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/MdsDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/MdsState.h"
#include "OSCLib/Data/OSCP/MDIB/InstanceIdentifier.h"
#include "OSCLib/Data/OSCP/MDIB/LocalizedText.h"
#include "OSCLib/Data/OSCP/MDIB/LocationContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/LocationContextState.h"
#include "OSCLib/Data/OSCP/MDIB/MdDescription.h"
#include "OSCLib/Data/OSCP/MDIB/MetricQuality.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricValue.h"
#include "OSCLib/Data/OSCP/MDIB/OperatorContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/PatientContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/PatientContextState.h"
#include "OSCLib/Data/OSCP/MDIB/PatientDemographicsCoreData.h"
#include "OSCLib/Data/OSCP/MDIB/Range.h"
#include "OSCLib/Data/OSCP/MDIB/StringMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/StringMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/StringMetricValue.h"
#include "OSCLib/Data/OSCP/MDIB/SystemContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/MetaData.h"
#include "OSCLib/Data/OSCP/MDIB/VmdDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/VmdState.h"
#include "OSCLib/Data/OSCP/MDIB/Udi.h"
#include "OSCLib/Data/OSCP/MDIB/custom/OperationInvocationContext.h"
#include "OSCLib/Util/DebugOut.h"
#include "OSCLib/Util/Task.h"
#include "../AbstractOSCLibFixture.h"
#include "../UnitTest++/src/UnitTest++.h"

#include <memory>

#include "Poco/Event.h"
#include "Poco/Mutex.h"
#include "Poco/ScopedLock.h"

#include "OSELib/OSCP/ServiceManager.h"

using namespace OSCLib;
using namespace OSCLib::Util;
using namespace OSCLib::Data::OSCP;

namespace OSCLib {
namespace Tests {
namespace SimpleOSCP {

//
// define handles and IDs
//

const std::string DEVICE_ENDPOINT_REFERENCE("EPR_1234");
const std::string DEVICE_UDI("UDI_1234");
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


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Consumer event handlers
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ExampleConsumerNumericHandler : public OSCPConsumerNumericMetricStateHandler {
public:
	ExampleConsumerNumericHandler(const std::string & handle) :
    	weight(0),
		handle(handle)
	{
	}

    virtual ~ExampleConsumerNumericHandler() {

    }

    void onStateChanged(const NumericMetricState & state) override {
        double val = state.getMetricValue().getValue();
        DebugOut(DebugOut::Default, "SimpleOSCP") << "Consumer: Received value changed of " << handle << ": " << val << std::endl;
    	Poco::Mutex::ScopedLock lock(mutex);
        weight = (float)val;
        eventEMR.set();
    }

    void onOperationInvoked(const OperationInvocationContext & oic, InvocationState is) override {
        DebugOut(DebugOut::Default, "SimpleOSCP") << "Consumer: Received operation invoked (ID, STATE) of " << handle << ": " << oic.transactionId << ", " << EnumToString::convert(is) << std::endl;
    }

    std::string getHandle() override {
        return handle;
    }

    float getWeight() {
    	Poco::Mutex::ScopedLock lock(mutex);
    	float result(weight);
        return result;
    }

	Poco::Event & getEventEMR() {
		return eventEMR;
	}

private:
    Poco::Mutex mutex;
    float weight;
    const std::string handle;
    Poco::Event eventEMR;
};

class ExampleConsumerEnumStringMetricHandler : public OSCPConsumerEnumStringMetricStateHandler {
public:
	ExampleConsumerEnumStringMetricHandler(const std::string & handle) :
		handle(handle)
	{
	}

    virtual ~ExampleConsumerEnumStringMetricHandler() {

    }

    void onStateChanged(const EnumStringMetricState & state) override {
    	const std::string val(state.getMetricValue().getValue());
        DebugOut(DebugOut::Default, "SimpleOSCP") << "Consumer: Received value changed of " << handle << ": " << val << std::endl;
        eventEMR.set();
    }

    void onOperationInvoked(const OperationInvocationContext & oic, InvocationState is) override {
        DebugOut(DebugOut::Default, "SimpleOSCP") << "Consumer: Received operation invoked (ID, STATE) of " << handle << ": " << oic.transactionId << ", " << EnumToString::convert(is) << std::endl;
    }

    std::string getHandle() override {
        return handle;
    }

	Poco::Event & getEventEMR() {
		return eventEMR;
	}

private:
    const std::string handle;
    Poco::Event eventEMR;
};

class ExampleConsumerStringMetricHandler : public OSCPConsumerStringMetricStateHandler {
public:
	ExampleConsumerStringMetricHandler(const std::string & handle) :
		handle(handle)
	{
	}

    virtual ~ExampleConsumerStringMetricHandler() {

    }

    void onStateChanged(const StringMetricState & state) override {
    	const std::string val(state.getMetricValue().getValue());
        DebugOut(DebugOut::Default, "SimpleOSCP") << "Consumer: Received value changed of " << handle << ": " << val << std::endl;
        eventEMR.set();
    }

    void onOperationInvoked(const OperationInvocationContext & oic, InvocationState is) override {
        DebugOut(DebugOut::Default, "SimpleOSCP") << "Consumer: Received operation invoked (ID, STATE) of " << handle << ": " << oic.transactionId << ", " << EnumToString::convert(is) << std::endl;
    }

    std::string getHandle() override {
        return handle;
    }

	Poco::Event & getEventEMR() {
		return eventEMR;
	}

private:
    const std::string handle;
    Poco::Event eventEMR;
};

class ExampleConsumerAlertSignalHandler : public OSCPConsumerAlertSignalStateHandler {
public:
	ExampleConsumerAlertSignalHandler(const std::string & handle) :
		handle(handle)
	{
	}

    virtual ~ExampleConsumerAlertSignalHandler() {

    }

    void onStateChanged(const AlertSignalState & state) override {
        DebugOut(DebugOut::Default, "SimpleOSCP") << "Consumer: Received alert signal changed of " << handle << ", presence = " << EnumToString::convert(state.getPresence()) << std::endl;
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
        DebugOut(DebugOut::Default, "SimpleOSCP") << "Consumer: Received operation invoked (ID, STATE) of " << handle << ": " << oic.transactionId << ", " << EnumToString::convert(is) << std::endl;
    }

    std::string getHandle() override {
        return handle;
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
    const std::string handle;
    Poco::Event eventEAROff;
    Poco::Event eventEAROn;
    Poco::Event eventEARLatch;
};

class ContextEventHandler : public OSCPConsumerSystemContextStateChangedHandler {
public:

	ContextEventHandler(const std::vector<std::string> & handles) : _handles(handles) {
	}

	virtual void onContextStateChanged(const std::vector<std::string> & handles) override {
        DebugOut(DebugOut::Default, "SimpleOSCP") << "Consumer: Received context values changed!" << std::endl;
        if (handles.size() > 0) {
        	if (std::find(_handles.begin(), _handles.end(), handles.front()) != _handles.end()) {
        		eventEMR.set();
        	}
        }
	}

	Poco::Event & getEventEMR() {
		return eventEMR;
	}

private:
	Poco::Event eventEMR;
	const std::vector<std::string> _handles;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Provider handlers
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


class ContextHandler : public OSCPProviderSystemContextStateHandler {
public:
	ContextHandler() {
	}

	virtual InvocationState onStateChangeRequest(
		const std::vector<EnsembleContextState> & ,
		const std::vector<LocationContextState> & lcStates,
		const std::vector<OperatorContextState> & ,
		const std::vector<PatientContextState> & pcStates,
		const std::vector<WorkflowContextState> & ,
		const OperationInvocationContext & ) override {

		if (lcStates.empty() && pcStates.empty()) {
			return InvocationState::Fail;
		}

		if ((lcStates.size() > 0 && lcStates[0].getDescriptorHandle() != "location_context")
			|| (pcStates.size() > 0 && pcStates[0].getDescriptorHandle() != "patient_context")) {
			return InvocationState::Fail;
		}

		DebugOut(DebugOut::Default, "SimpleOSCP") << "Provider: ContextHandler received state change request" << std::endl;
		if (lcStates.size() > 0) {
            updateState(lcStates[0]);
		}
		if (pcStates.size() > 0) {
            updateState(pcStates[0]);
        }
	    return InvocationState::Fin;
	}

    // Get initial states
	virtual std::vector<LocationContextState> getLocationContextStates() override {
        LocationContextState locationState("location_context_state", "location_context");
        // This device magically knows its location
        locationState
            .addIdentification(
            InstanceIdentifier()
            	.setRoot("MyHospital")
            	.setExtension("Room 23"));
		std::vector<LocationContextState> result;
		result.push_back(locationState);
		return result;
	}

    // Get inital states
    virtual std::vector<PatientContextState> getPatientContextStates() override {
        PatientContextState patientState("patient_context_state", "patient_context");
        patientState
            .addIdentification(
            InstanceIdentifier()
				.setRoot("max")
				.setExtension("mustermann"));
        std::vector<PatientContextState> result;
		result.push_back(patientState);
		return result;
	}
};

class MaxValueStateHandler : public OSCPProviderNumericMetricStateHandler {
public:

    MaxValueStateHandler() {
    }

    InvocationState onStateChangeRequest(const NumericMetricState & state, const OperationInvocationContext & oic) override {
        // Invocation has been fired as WAITING when entering this method
    	DebugOut(DebugOut::Default, "SimpleOSCP") << "Provider: MaxValueStateHandler received state change request" << std::endl;

    	notifyOperationInvoked(oic, InvocationState::Start);

        // we can update here, but if we return Fin, the framework will also update
        updateState(state);

        // Usually, update the real device's state here.

        return InvocationState::Fin;  // Framework will update internal MDIB with the state's value and increase MDIB version
    }

    // Helper method
    NumericMetricState createState() {
        NumericMetricState result(NUMERIC_METRIC_MAX_HANDLE);
        result
            .setMetricValue(NumericMetricValue(MetricQuality(MeasurementValidity::Vld)).setValue(2.0))
            .setActivationState(ComponentActivation::On);
        return result;
    }

    NumericMetricState getInitialState() override {
        NumericMetricState result = createState();
        return result;
    }

    // Convenience value getter
    float getMaxWeight() {
    	std::unique_ptr<NumericMetricState> result(getParentProvider().getMdState().findState<NumericMetricState>(NUMERIC_METRIC_MAX_HANDLE));
        // check if result is valid
        if (result != nullptr) {
        	// In real applications, check if state has an observed value and if the observed value has a value!
        	return (float)result->getMetricValue().getValue();
        } else {
        	DebugOut(DebugOut::Default, "ExampleProvider") << "Maximum weight metric not found." << std::endl;
        	return 0;
        }
    }
};





class CurValueStateHandler : public OSCPProviderNumericMetricStateHandler {
public:

    CurValueStateHandler() {
    }

    // onStateChangeRequest not implemented (state is read-only - MEASUREMENT)

    // Helper method
    NumericMetricState createState(float value) {
        NumericMetricState result(NUMERIC_METRIC_CURRENT_HANDLE);
        result
            .setMetricValue(NumericMetricValue(MetricQuality(MeasurementValidity::Vld)).setValue(value))
            .setActivationState(ComponentActivation::On)
            .setDescriptorHandle(NUMERIC_METRIC_CURRENT_HANDLE)
            .setLifeTimePeriod(xml_schema::Duration(0,0,0,0,0,0,1));
        return result;
    }

    NumericMetricState getInitialState() override {
        return createState(0);
    }

    void setNumericValue(float value) {
        NumericMetricState currentWeightState = createState(value);
        // Call update function (this will update internal MDIB and increase MDIB version number)
        updateState(currentWeightState);
    }

};

class EnumStringMetricStateHandler : public OSCPProviderEnumStringMetricStateHandler {
public:

	EnumStringMetricStateHandler() {
    }

    InvocationState onStateChangeRequest(const EnumStringMetricState & state, const OperationInvocationContext & oic) override {
        // Invocation has been fired as WAITING when entering this method
    	DebugOut(DebugOut::Default, "SimpleOSCP") << "Provider: EnumStringMetricStateHandler received state change request" << std::endl;
    	notifyOperationInvoked(oic, InvocationState::Start);

        // we can update here, but if we return Fin, the framework will also notify
        //updateState(currentStringState);

        // Usually, update the real device's state here.

        return InvocationState::Fin;  // Framework will update internal MDIB with the state's value and increase MDIB version
    }

    // Helper method
    EnumStringMetricState createState(const std::string & value) {
        EnumStringMetricState result(ENUM_METRIC_HANDLE);
        result
            .setMetricValue(StringMetricValue(MetricQuality(MeasurementValidity::Vld)).setValue(value))
            .setActivationState(ComponentActivation::On);
        return result;
    }

    EnumStringMetricState getInitialState() override {
        return createState("hello");
    }

};

class StrValueStateHandler : public OSCPProviderStringMetricStateHandler {
public:

    StrValueStateHandler() {
    }

    InvocationState onStateChangeRequest(const StringMetricState & state, const OperationInvocationContext & oic) override {
        // Invocation has been fired as WAITING when entering this method
    	DebugOut(DebugOut::Default, "SimpleOSCP") << "Provider: StrValueStateHandler received state change request" << std::endl;
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

class AlertSignalStateHandler : public OSCPProviderAlertSignalStateHandler {
public:

	AlertSignalStateHandler() {
    }

    InvocationState onStateChangeRequest(const AlertSignalState & state, const OperationInvocationContext & oic) override {
        // Invocation has been fired as WAITING when entering this method
    	DebugOut(DebugOut::Default, "SimpleOSCP") << "Provider: AlertSignalStateHandler received state change: " << EnumToString::convert(state.getPresence()) << std::endl;

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

class LatchingAlertSignalStateHandler : public OSCPProviderAlertSignalStateHandler {
public:

	LatchingAlertSignalStateHandler() {
    }

    InvocationState onStateChangeRequest(const AlertSignalState & state, const OperationInvocationContext & oic) override {
        // Invocation has been fired as WAITING when entering this method
    	DebugOut(DebugOut::Default, "SimpleOSCP") << "Provider: LatchingAlertSignalStateHandler received state change: " << EnumToString::convert(state.getPresence()) << std::endl;

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

class LimitAlertConditionStateHandler : public OSCPProviderLimitAlertConditionStateHandler {
public:

	LimitAlertConditionStateHandler() 
	{
	}

    InvocationState onStateChangeRequest(const LimitAlertConditionState & state, const OperationInvocationContext & ) override {
        // Invocation has been fired as WAITING when entering this method
    	std::unique_ptr<LimitAlertConditionState> pCurrentState(getParentProvider().getMdState().findState<LimitAlertConditionState>(state.getDescriptorHandle()));

    	DebugOut(DebugOut::Default, "SimpleOSCP") << "Provider: LimitAlertConditionStateHandler received state change, presence = " << state.getPresence() << std::endl;
        if (state.getPresence() != pCurrentState->getPresence()) {
    		DebugOut(DebugOut::Default, "SimpleOSCP") << "Provider: LimitAlertConditionStateHandler detected presence change to: " << state.getPresence() << std::endl;
    		// do something...
    	}

    	//we can update here, but if we return Fin, the framework will also notify
    	//updateState(*pCurrentState);

    	return InvocationState::Fin;  // Framework will update internal MDIB with the state's value and increase MDIB version
    }

    // this function monitors the observered metric which is defined by the Source attribute of the corresponding LimitAlertConditionDescriptor
    void sourceHasChanged(const std::string & sourceHandle) override {
    	DebugOut(DebugOut::Default, "SimpleOSCP") << "Provider: LimitAlertConditionStateHandler monitored source state changed." << std::endl;

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

class AlertSystemStateHandler : public OSCPProviderAlertSystemStateHandler {
public:

	AlertSystemStateHandler() {
    }

	AlertSystemState getInitialState() override {
        AlertSystemState alertSystemState("handle_alert_system", AlertActivation::On);  // reference alert system descriptor's handle // Alert is activated
        return alertSystemState;
    }

};

class CommandHandler : public OSCPProviderActivateOperationHandler {
public:

	CommandHandler() {
    }

	InvocationState onActivateRequest(const MdibContainer & , const OperationInvocationContext & ) override {
		DebugOut(DebugOut::Default, "SimpleOSCP") << "Provider: Received command!" << std::endl;
		return InvocationState::Fin;
	}

	std::string getDescriptorHandle() override {
		return "handle_cmd";
	}
};

class AlwaysOnChannelStateHandler : public OSCPProviderChannelStateHandler {
public:
	AlwaysOnChannelStateHandler(const std::string & descriptorHandle) {
        this->descriptorHandle = descriptorHandle;
    }

    // Helper method
    ChannelState createState() {
    	ChannelState result(descriptorHandle);
        result
            .setActivationState(ComponentActivation::On);
        return result;
    }

    virtual ChannelState getInitialState() override {
    	ChannelState state = createState();
        return state;
    }

private:
    std::string descriptorHandle;
};


class AlwaysOnVmdStateHandler : public OSCPProviderVmdStateHandler {
public:
	AlwaysOnVmdStateHandler(const std::string & descriptorHandle) {
        this->descriptorHandle = descriptorHandle;
    }

    // Helper method
    VmdState createState() {
    	VmdState result(descriptorHandle);
        result
            .setActivationState(ComponentActivation::On);
        return result;
    }

    virtual VmdState getInitialState() override {
    	VmdState state = createState();
        return state;
    }

private:
    std::string descriptorHandle;
};





class AlwaysOnMdsStateHandler : public OSCPProviderMdsStateHandler {
public:
    AlwaysOnMdsStateHandler(const std::string & descriptorHandle) {
        this->descriptorHandle = descriptorHandle;
    }

    // Helper method
    MdsState createState() {
        MdsState result(descriptorHandle);
        result
            .setActivationState(ComponentActivation::On);
        return result;
    }

    virtual MdsState getInitialState() override {
        MdsState state = createState();
        return state;
    }

private:
    std::string descriptorHandle;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Provider
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

class OSCPHoldingDeviceProvider : public Util::Task {
public:
    OSCPHoldingDeviceProvider() :
    	currentWeight(0),
    	oscpProvider(),
		curValueState(),
		maxValueState(),
		channelState(CHANNEL_DESCRIPTOR_HANDLE),
		MdsState(MDS_HANDLE),
		vmdState(VMD_DESCRIPTOR_HANDLE)
	{
    	oscpProvider.setEndpointReference(DEVICE_ENDPOINT_REFERENCE);



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
        			.setLower(0)
        			.setUpper(2.0)
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
        AlertSystemDescriptor alertSystem("handle_alert_system");
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

        oscpProvider.createSetOperationForDescriptor(alertSignal, holdingDeviceSystem);
        oscpProvider.createSetOperationForDescriptor(maxWeightMetric, holdingDeviceSystem);
        oscpProvider.createSetOperationForDescriptor(testEnumMetric, holdingDeviceSystem);
        oscpProvider.createSetOperationForDescriptor(testStringMetric, holdingDeviceSystem);
        oscpProvider.createSetOperationForDescriptor(location, holdingDeviceSystem);
        oscpProvider.createSetOperationForDescriptor(patient, holdingDeviceSystem);

        ActivateOperationDescriptor aod("handle_cmd", NUMERIC_METRIC_MAX_HANDLE);

		oscpProvider.addActivateOperationForDescriptor(aod, holdingDeviceSystem);

		// create and add description
		MdDescription mdDescription;
		mdDescription.addMdsDescriptor(holdingDeviceSystem);

		oscpProvider.setMdDescription(mdDescription);

        // State handlers

		oscpProvider.addMdSateHandler(&contextStates);
		oscpProvider.addMdSateHandler(&curValueState);
		oscpProvider.addMdSateHandler(&enumState);
		oscpProvider.addMdSateHandler(&maxValueState);
		oscpProvider.addMdSateHandler(&strValueState);
		oscpProvider.addMdSateHandler(&limitAlertConditionHandler);
		oscpProvider.addMdSateHandler(&alertSigHandler);
		oscpProvider.addMdSateHandler(&latchingAlertSigHandler);
		oscpProvider.addMdSateHandler(&alertSysHandler);
		oscpProvider.addMdSateHandler(&cmdHandler);
		oscpProvider.addMdSateHandler(&channelState);
		oscpProvider.addMdSateHandler(&MdsState);
		oscpProvider.addMdSateHandler(&vmdState);
	}

    MdDescription getMdDescription() {
    	return oscpProvider.getMdDescription();
    }

    void startup() {
    	oscpProvider.startup();
    }

    void shutdown() {
    	oscpProvider.shutdown();
    }

    // Update weight periodically
    virtual void runImpl() override {
    	float nextWeight = currentWeight + 0.2f;
    	if (nextWeight > 2.5f) {
    		nextWeight = 0.1;
    	}
		setCurrentWeight(nextWeight);
		Poco::Thread::sleep(1000);
    }

    void setCurrentWeight(float value) {
        Poco::Mutex::ScopedLock lock(oscpProvider.getMutex());
        currentWeight = value;
        curValueState.setNumericValue(value);
        DebugOut(DebugOut::Default, "SimpleOSCP") << "Changed value: " << currentWeight << std::endl;
        strValueState.setStringValue("Test " + std::to_string(value));
    }

private:
    float currentWeight;

    // Provider object
    OSCPProvider oscpProvider;

    // State (handlers)
    ContextHandler contextStates;
    CurValueStateHandler curValueState;
    MaxValueStateHandler maxValueState;
    EnumStringMetricStateHandler enumState;
    StrValueStateHandler strValueState;
    LimitAlertConditionStateHandler limitAlertConditionHandler;
    AlertSignalStateHandler alertSigHandler;
    LatchingAlertSignalStateHandler latchingAlertSigHandler;
    AlertSystemStateHandler alertSysHandler;
    CommandHandler cmdHandler;
    AlwaysOnChannelStateHandler channelState;
    AlwaysOnMdsStateHandler MdsState;
    AlwaysOnVmdStateHandler vmdState;
};

}
}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Test
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct FixtureSimpleOSCP : Tests::AbstractOSCLibFixture {
	FixtureSimpleOSCP() : AbstractOSCLibFixture("FixtureSimpleOSCP", OSELib::LogLevel::ERROR, 9000) {}
};

SUITE(OSCP) {
TEST_FIXTURE(FixtureSimpleOSCP, simpleoscp)
{
	DebugOut::openLogFile("Test.log.txt", true);
	try
	{
        // Provider
        Tests::SimpleOSCP::OSCPHoldingDeviceProvider provider;
        provider.startup();
        provider.start();

        // MdDescription test
        MdDescription mdDescription =  provider.getMdDescription();
        // add and remove a test MDS
        MdsDescriptor mds_test("MDC_MDS_HANDLE");
        mdDescription.addMdsDescriptor(mds_test);

        CHECK_EQUAL(true, mdDescription.removeMdsDescriptor(mds_test));

        Poco::Thread::sleep(2000);
        // Consumer
        OSELib::OSCP::ServiceManager oscpsm;
        std::shared_ptr<OSCPConsumer> c(oscpsm.discoverEndpointReference(Tests::SimpleOSCP::DEVICE_ENDPOINT_REFERENCE));


        Tests::SimpleOSCP::ExampleConsumerNumericHandler eces1(Tests::SimpleOSCP::NUMERIC_METRIC_CURRENT_HANDLE);
        Tests::SimpleOSCP::ExampleConsumerNumericHandler eces2(Tests::SimpleOSCP::NUMERIC_METRIC_MAX_HANDLE);
        Tests::SimpleOSCP::ExampleConsumerStringMetricHandler eces3(Tests::SimpleOSCP::STRING_METRIC_HANDLE);
        Tests::SimpleOSCP::ExampleConsumerEnumStringMetricHandler eces4(Tests::SimpleOSCP::ENUM_METRIC_HANDLE);
        Tests::SimpleOSCP::ExampleConsumerAlertSignalHandler alertSignalsink(Tests::SimpleOSCP::ALERT_SIGNAL_HANDLE);
        Tests::SimpleOSCP::ExampleConsumerAlertSignalHandler latchingAlertSignalsink(Tests::SimpleOSCP::ALERT_SIGNAL_LATCHING_HANDLE);
        Tests::SimpleOSCP::ContextEventHandler ceh({"location_context_state", "patient_context_state"});


        // Discovery test
        CHECK_EQUAL(true, c != nullptr);

		if (c != nullptr) {
			OSCPConsumer & consumer = *c;
            // MDIB test
            MdibContainer mdib(consumer.getMdib());

            { // test access to system metadata of mds implemented by provider above
            	std::unique_ptr<MdsDescriptor> pMdsDescriptor(mdib.getMdDescription().findDescriptor<MdsDescriptor>(Tests::SimpleOSCP::MDS_HANDLE));
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
            	std::unique_ptr<MdsDescriptor> pMdsDescriptor(mdib.getMdDescription().findDescriptor<MdsDescriptor>(Tests::SimpleOSCP::MDS_HANDLE));
            	if (pMdsDescriptor != nullptr) {
            		SystemContextDescriptor sc(pMdsDescriptor->getSystemContext());
            		CHECK_EQUAL(true, sc.hasPatientContext());
            		CHECK_EQUAL(true, sc.getOperatorContextList().empty());
            	}
            }
            {	// lookup descriptors that should exist for the provider implemented above
            	std::unique_ptr<NumericMetricDescriptor> pNumericMetricDescriptor(mdib.getMdDescription().findDescriptor<NumericMetricDescriptor>(Tests::SimpleOSCP::NUMERIC_METRIC_CURRENT_HANDLE));
            	if (pNumericMetricDescriptor != nullptr) {
				CHECK_EQUAL("en", pNumericMetricDescriptor->getUnit().getConceptDescriptionList()[0].getLang());
				}
				std::unique_ptr<StringMetricDescriptor> pStringMetricDescriptor(mdib.getMdDescription().findDescriptor<StringMetricDescriptor>(Tests::SimpleOSCP::STRING_METRIC_HANDLE));
				CHECK_EQUAL(true, pStringMetricDescriptor != nullptr);
				CHECK_EQUAL(Tests::SimpleOSCP::STRING_METRIC_HANDLE, pStringMetricDescriptor->getHandle());
            }

            // Register for consumer events
            CHECK_EQUAL(true, consumer.registerStateEventHandler(&eces1));
            CHECK_EQUAL(true, consumer.registerStateEventHandler(&eces2));
            CHECK_EQUAL(true, consumer.registerStateEventHandler(&eces3));
            CHECK_EQUAL(true, consumer.registerStateEventHandler(&eces4));
            // Register for alert signal events
            CHECK_EQUAL(true, consumer.registerStateEventHandler(&alertSignalsink));
            CHECK_EQUAL(true, consumer.registerStateEventHandler(&latchingAlertSignalsink));
            // Register for context changed events
            consumer.setContextStateChangedHandler(&ceh);

            Poco::Thread::sleep(2000);

            {	// Ensure that requests for wrong handles fail.
            	DebugOut(DebugOut::Default, "SimpleOSCP") << "Numeric test..." << std::endl;
				DebugOut(DebugOut::Default, "SimpleOSCP") << "SHOULD FAIL: " << std::endl;
				NumericMetricState tempState(" ");
				std::unique_ptr<NumericMetricState> pTempNMS(consumer.requestState<NumericMetricState>("unknown"));
            	CHECK_EQUAL(false, pTempNMS != nullptr);
            }
            {	// Request state of current weight
				std::unique_ptr<NumericMetricState> pTempNMS(consumer.requestState<NumericMetricState>(Tests::SimpleOSCP::NUMERIC_METRIC_CURRENT_HANDLE));
				CHECK_EQUAL(true, pTempNMS != nullptr);
				CHECK_EQUAL(true, pTempNMS->hasMetricValue());
				if (pTempNMS->hasMetricValue()) {
					const double curWeight(pTempNMS->getMetricValue().getValue());
					CHECK_EQUAL(true, curWeight > 0.1);
				}
            }
            {	// Ensure that (read-only) metrics without matching SetOperation cannot be set.
            	DebugOut(DebugOut::Default, "SimpleOSCP") << "SHOULD FAIL: " << std::endl;
            	std::unique_ptr<NumericMetricState> pTempNMS(consumer.requestState<NumericMetricState>(Tests::SimpleOSCP::NUMERIC_METRIC_CURRENT_HANDLE));
            	CHECK_EQUAL(true, pTempNMS != nullptr);
            	CHECK_EQUAL(true, InvocationState::Fail == consumer.commitState(*pTempNMS));
            }
            {	// Get state of maximum weight
            	std::unique_ptr<NumericMetricState> pTempNMS(consumer.requestState<NumericMetricState>(Tests::SimpleOSCP::NUMERIC_METRIC_MAX_HANDLE));
				CHECK_EQUAL(true, pTempNMS != nullptr);
				double maxWeight = pTempNMS->getMetricValue().getValue();
				CHECK_EQUAL(2.0, maxWeight);
            }
            {	// Get state of test enum
            	std::unique_ptr<EnumStringMetricState> pTempESMS(consumer.requestState<EnumStringMetricState>(Tests::SimpleOSCP::ENUM_METRIC_HANDLE));
				CHECK_EQUAL(true, pTempESMS != nullptr);
				const std::string enumValue(pTempESMS->getMetricValue().getValue());
				CHECK_EQUAL("hello", enumValue);
            }
            {	// Set state of test enum with allowed enum value
            	std::unique_ptr<EnumStringMetricState> pTempESMS(consumer.requestState<EnumStringMetricState>(Tests::SimpleOSCP::ENUM_METRIC_HANDLE));
            	CHECK_EQUAL(true, pTempESMS != nullptr);

            	pTempESMS->setMetricValue(pTempESMS->getMetricValue().setValue("bon jour"));
				FutureInvocationState fis;
				CHECK_EQUAL(true, InvocationState::Wait == consumer.commitState(*pTempESMS, fis));
				CHECK_EQUAL(true, fis.waitReceived(InvocationState::Fin, Tests::SimpleOSCP::DEFAULT_TIMEOUT));
            }
            {	// Set state of test enum with illegal enum value
            	std::unique_ptr<EnumStringMetricState> pTempESMS(consumer.requestState<EnumStringMetricState>(Tests::SimpleOSCP::ENUM_METRIC_HANDLE));
            	CHECK_EQUAL(true, pTempESMS != nullptr);

				const std::string enumValue(pTempESMS->getMetricValue().getValue());
				CHECK_EQUAL("bon jour", enumValue);

				pTempESMS->setMetricValue(pTempESMS->getMetricValue().setValue("bye"));
				FutureInvocationState fis;
				consumer.commitState(*pTempESMS, fis);
				CHECK_EQUAL(true, fis.waitReceived(InvocationState::Fail, Tests::SimpleOSCP::DEFAULT_TIMEOUT));
            }

            // Wait here and let the current value exceed max value. This will trigger alert condition presence which in turn
            // will trigger an alert signal presence (Off -> On -> Latch)!
            Poco::Thread::sleep(8000);

			{	// Set state test for a numeric metric state (must succeed, use state handle instead of descriptor handle)
            	std::unique_ptr<NumericMetricState> pTempNMS(consumer.requestState<NumericMetricState>(Tests::SimpleOSCP::NUMERIC_METRIC_MAX_HANDLE));
				CHECK_EQUAL(true, pTempNMS != nullptr);

				// Here, we increase max weight to switch condition presence => results in alert signal presence
				pTempNMS->setMetricValue(pTempNMS->getMetricValue().setValue(10));
				FutureInvocationState fis;
				CHECK_EQUAL(true, InvocationState::Wait == consumer.commitState(*pTempNMS, fis));
				CHECK_EQUAL(true, fis.waitReceived(InvocationState::Fin, Tests::SimpleOSCP::DEFAULT_TIMEOUT));
			}

            {	// Set state test for a string metric state (must succeed)
                DebugOut(DebugOut::Default, "SimpleOSCP") << "String test...";
            	std::unique_ptr<StringMetricState> pTempNMS(consumer.requestState<StringMetricState>(Tests::SimpleOSCP::STRING_METRIC_HANDLE));
				CHECK_EQUAL(true, pTempNMS != nullptr);

				pTempNMS->setMetricValue(pTempNMS->getMetricValue().setValue("Test2"));
				FutureInvocationState fis;
				CHECK_EQUAL(true, InvocationState::Wait == consumer.commitState(*pTempNMS, fis));
				CHECK_EQUAL(true, fis.waitReceived(InvocationState::Fin, Tests::SimpleOSCP::DEFAULT_TIMEOUT));
            }

            {	// Activate test
                DebugOut(DebugOut::Default, "SimpleOSCP") << "Activate test...";
                FutureInvocationState fis;
				CHECK_EQUAL(true, InvocationState::Wait == c->activate("handle_cmd", fis));
				CHECK_EQUAL(true, fis.waitReceived(InvocationState::Fin, Tests::SimpleOSCP::DEFAULT_TIMEOUT));
            }

            {	// Location context test
                DebugOut(DebugOut::Default, "SimpleOSCP") << "Location context test...";
                LocationContextState lcs("location_context", "location_context_state");
                lcs.setContextAssociation(ContextAssociation::Assoc);
                lcs.addIdentification(InstanceIdentifier().setRoot("hello").setExtension("world"));
                FutureInvocationState fis;
                ceh.getEventEMR().reset();
                CHECK_EQUAL(true, InvocationState::Wait == consumer.commitState(lcs, fis));
				CHECK_EQUAL(true, ceh.getEventEMR().tryWait(3000));
				CHECK_EQUAL(true, fis.waitReceived(InvocationState::Fin, Tests::SimpleOSCP::DEFAULT_TIMEOUT));
				DebugOut(DebugOut::Default, "SimpleOSCP") << "Location context test done...";
            }
            {	// Patient context test
            	DebugOut(DebugOut::Default, "SimpleOSCP") << "Patient context test...";
				PatientContextState pcs("patient_context", "patient_context_state");
				pcs.setContextAssociation(ContextAssociation::Assoc);
				pcs.addIdentification(InstanceIdentifier().setRoot("hello").setExtension("world"));
				pcs.setCoreData(PatientDemographicsCoreData()
						.setGivenname("Max")
						.setBirthname("")
						.setFamilyname("Mustermann"));
						// FIXME: DateOfBirth does not work yet -> schema validation fail because union is not rightly implemented
						//.setDateOfBirth("08.05.1945"));
				FutureInvocationState fis;
				ceh.getEventEMR().reset();
				CHECK_EQUAL(true, InvocationState::Wait == consumer.commitState(pcs, fis));

				CHECK_EQUAL(true, ceh.getEventEMR().tryWait(3000));

				CHECK_EQUAL(true, fis.waitReceived(InvocationState::Fin, Tests::SimpleOSCP::DEFAULT_TIMEOUT));
				DebugOut(DebugOut::Default, "SimpleOSCP") << "Patient context test done...";
			}
            // Run for some time to receive and display incoming metric events.
			Poco::Thread::sleep(5000);

			// Stop dummy events created by provider
			provider.interrupt();

			{	// Switch alert signal state off
            	std::unique_ptr<AlertSignalState> pTempASS(consumer.requestState<AlertSignalState>(Tests::SimpleOSCP::ALERT_SIGNAL_HANDLE));
				CHECK_EQUAL(true, pTempASS != nullptr);


				pTempASS->setPresence(AlertSignalPresence::Off);
				FutureInvocationState fis;
				CHECK_EQUAL(true, InvocationState::Wait == consumer.commitState(*pTempASS, fis));
				CHECK_EQUAL(true, fis.waitReceived(InvocationState::Fin, Tests::SimpleOSCP::DEFAULT_TIMEOUT));
			}

            Poco::Thread::sleep(5000);

            CHECK_EQUAL(true, eces1.getWeight() > 0);

            CHECK_EQUAL(true, eces1.getEventEMR().tryWait(Tests::SimpleOSCP::DEFAULT_TIMEOUT));
            CHECK_EQUAL(true, eces2.getEventEMR().tryWait(Tests::SimpleOSCP::DEFAULT_TIMEOUT));
            CHECK_EQUAL(true, eces3.getEventEMR().tryWait(Tests::SimpleOSCP::DEFAULT_TIMEOUT));
            CHECK_EQUAL(true, eces4.getEventEMR().tryWait(Tests::SimpleOSCP::DEFAULT_TIMEOUT));

            CHECK_EQUAL(true, alertSignalsink.getEventEAROff().tryWait(Tests::SimpleOSCP::DEFAULT_TIMEOUT));
            CHECK_EQUAL(true, alertSignalsink.getEventEAROn().tryWait(Tests::SimpleOSCP::DEFAULT_TIMEOUT));
            CHECK_EQUAL(true, latchingAlertSignalsink.getEventEARLatch().tryWait(Tests::SimpleOSCP::DEFAULT_TIMEOUT));

            CHECK_EQUAL(true, consumer.unregisterStateEventHandler(&eces1));
            CHECK_EQUAL(true, consumer.unregisterStateEventHandler(&eces2));
            CHECK_EQUAL(true, consumer.unregisterStateEventHandler(&eces3));
            CHECK_EQUAL(true, consumer.unregisterStateEventHandler(&eces4));
            CHECK_EQUAL(true, consumer.unregisterStateEventHandler(&alertSignalsink));
            CHECK_EQUAL(true, consumer.unregisterStateEventHandler(&latchingAlertSignalsink));
            
            consumer.setContextStateChangedHandler(nullptr);

            DebugOut(DebugOut::Default, "SimpleOSCP") << "Finished...";
            
            consumer.disconnect();
		}

        Poco::Thread::sleep(2000);
        provider.shutdown();
    } catch (char const* exc) {
		DebugOut(DebugOut::Default, std::cerr, "simpleoscp") << exc;
	} catch (...) {
		DebugOut(DebugOut::Default, std::cerr, "simpleoscp") << "Unknown exception occurred!";
	}
	DebugOut::closeLogFile();
}
}
