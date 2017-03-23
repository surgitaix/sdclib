/*
 * ExampleProvider4SoftICEStreaming.cpp
 *
 *  @Copyright (C) 2016, SurgiTAIX AG
 *  Author: buerger
 *
 *  This program sends a RealTimeSampleArrayMetricState ("handle_stream") and a NumericMatricState ("handle_get") to the network. It changes the "handle_stream"
 *
 */

#include "OSCLib/OSCLibrary.h"
#include "OSCLib/Data/OSCP/OSCPProvider.h"
#include "OSCLib/Data/OSCP/OSCPProviderRealTimeSampleArrayMetricStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPProviderNumericMetricStateHandler.h"
#include "OSCLib/Data/OSCP/MDIB/ChannelDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/Duration.h"
#include "OSCLib/Data/OSCP/MDIB/EnumMappings.h"
#include "OSCLib/Data/OSCP/MDIB/HydraMDSDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/LocalizedText.h"
#include "OSCLib/Data/OSCP/MDIB/Measure.h"
#include "OSCLib/Data/OSCP/MDIB/MDDescription.h"
#include "OSCLib/Data/OSCP/MDIB/Range.h"
#include "OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayValue.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricValue.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricDescriptor.h"

#include "OSCLib/Data/OSCP/MDIB/RTValueType.h"
#include "OSCLib/Data/OSCP/MDIB/Timestamp.h"
#include "OSCLib/Data/OSCP/MDIB/SystemContext.h"
#include "OSCLib/Data/OSCP/MDIB/SystemMetaData.h"
#include "OSCLib/Data/OSCP/MDIB/VMDDescriptor.h"
#include "OSCLib/Util/DebugOut.h"
#include "OSCLib/Util/Task.h"

#include "OSELib/OSCP/ServiceManager.h"

#include "Poco/Runnable.h"
#include "Poco/Mutex.h"
#include "Poco/ScopedLock.h"
#include "Poco/Thread.h"

using namespace OSCLib;
using namespace OSCLib::Util;
using namespace OSCLib::Data::OSCP;


const std::string deviceEPR("UDI-1234567890");


class GetNumericMetricStateHandler : public OSCPProviderNumericMetricStateHandler {
public:

	GetNumericMetricStateHandler(std::string descriptorHandle) : descriptorHandle(descriptorHandle) {
	}


	// Helper method
	NumericMetricState createState(double value) {
		NumericMetricState result;
		result
			.setObservedValue(NumericMetricValue().setValue(value))
			.setComponentActivationState(ComponentActivation::ON)
			.setDescriptorHandle("handle_get")
			.setHandle("handle_get_state");
		return result;
	}

	NumericMetricState getInitialState() override {
		NumericMetricState nms = createState(42.0);
		return nms;
	}

	void setNumericValue(double value) {
		NumericMetricState nms = createState(value);
		updateState(nms);
	}

private:
	std::string descriptorHandle;
};



class SetNumericMetricStateHandler : public OSCPProviderNumericMetricStateHandler {
public:

    SetNumericMetricStateHandler(const std::string descriptorHandle) : descriptorHandle(descriptorHandle) {
    }

    InvocationState onStateChangeRequest(const NumericMetricState & state, const OperationInvocationContext & oic) override {
        // Invocation has been fired as WAITING when entering this method
        DebugOut(DebugOut::Default, "SimpleOSCP") << "Provider: handle_set received state change request. State's value: " << state.getObservedValue().getValue() << std::endl;

        notifyOperationInvoked(oic, InvocationState::STARTED);

        return InvocationState::FINISHED;  // Framework will update internal MDIB with the state's value and increase MDIB version
    }

    // Helper method
    NumericMetricState createState() {
        NumericMetricState result;
        result
            .setObservedValue(NumericMetricValue().setValue(2.0))
            .setComponentActivationState(ComponentActivation::ON)
            .setDescriptorHandle("handle_set")
            .setHandle("handle_set_state");
        return result;
    }

    NumericMetricState getInitialState() override {
        NumericMetricState result = createState();
        return result;
    }

    // Convenience value getter
    float getMaxWeight() {
        NumericMetricState result;
        // TODO: in real applications, check if findState returns true!
        getParentProvider().getMDState().findState("handle_set", result);
        // TODO: in real applications, check if state has an observed value and if the observed value has a value!
        return (float)result.getObservedValue().getValue();
    }

private:
    const std::string descriptorHandle;
};



class StreamProviderStateHandler : public OSCPProviderRealTimeSampleArrayMetricStateHandler {
public:

    StreamProviderStateHandler(std::string descriptorHandle) : descriptorHandle(descriptorHandle) {
    }

    // Helper method
    RealTimeSampleArrayMetricState createState() {
        RealTimeSampleArrayMetricState realTimeSampleArrayState;
        realTimeSampleArrayState
            .setComponentActivationState(ComponentActivation::ON)
            .setDescriptorHandle(descriptorHandle)
            .setHandle(descriptorHandle + "_state");
        return realTimeSampleArrayState;
    }


    RealTimeSampleArrayMetricState getInitialState() override {
        return createState();
    }

    void updateStateValue(const RealTimeSampleArrayValue & rtsav) {
        RealTimeSampleArrayMetricState realTimeSampleArrayState = createState();
        realTimeSampleArrayState
            .setObservedValue(rtsav);
        updateState(realTimeSampleArrayState);
    }


private:
    std::string descriptorHandle;
};

class OSCPStreamProvider : public Util::Task {
public:

    OSCPStreamProvider() : oscpProvider(), streamHandler("handle_stream"), getNumericHandler("handle_get"), setNumericHandler("handle_set") {

		oscpProvider.setEndpointReference(deviceEPR);

        // handle references of their states
        streamMetricDescriptor.setHandle("handle_stream");

        // metric stream metric (read-only)
        streamMetricDescriptor
			.setSamplePeriod(
					Duration()
					.setseconds(0.001)
					)
			.setResolution(1.0)
			.addTechnicalRange(Range()
					.setUpper(2)
					.setLower(0))
			.setMetricCategory(MetricCategory::MEASUREMENT)
			.setAvailability(MetricAvailability::CONTINUOUS)
			.setType(CodedValue()
                    .setCodeId("MDCX_XXX"));

        setMetricDescriptor
        	.setHandle("handle_set")
        	.setMetricCategory(MetricCategory::SETTING)
        	.setAvailability(MetricAvailability::CONTINUOUS)
        	.setType(CodedValue().addConceptDescription(LocalizedText().set("Maximum weight")));






        // Channel
        ChannelDescriptor holdingDeviceParameters;
        holdingDeviceParameters
			.addMetric(streamMetricDescriptor)
			.addMetric(setMetricDescriptor)
			.setIntendedUse(IntendedUse::INFORMATIONAL);

        // VMD
        VMDDescriptor holdingDeviceModule;
        holdingDeviceModule.addChannel(holdingDeviceParameters);

        // MDS
        HydraMDSDescriptor holdingDeviceSystem;
        holdingDeviceSystem
			.setMetaData(
				SystemMetaData()
				.addManufacturer(
					LocalizedText()
					.set("SurgiTAIX AG"))
				.addModelName(
					LocalizedText()
					.set("ChipOx"))
				.addModelNumber("1")
				.addSerialNumber("1234")
				)
            .setType(CodedValue()
                .setCodeId("MDC_DEV_ANALY_SAT_O2_MDS"))
			.addVMD(holdingDeviceModule);

        oscpProvider.createSetOperationForDescriptor(setMetricDescriptor, holdingDeviceSystem);

        // create and add description
		MDDescription mdDescription;
		mdDescription.addMDSDescriptor(holdingDeviceSystem);

		oscpProvider.setMDDescription(mdDescription);

        // Add handler
		oscpProvider.addMDStateHandler(&streamHandler);
		oscpProvider.addMDStateHandler(&getNumericHandler);
		oscpProvider.addMDStateHandler(&setNumericHandler);
    }

    void startup() {
    	oscpProvider.startup();
    }

    void shutdown() {
    	oscpProvider.shutdown();
    }

    void updateStateValue(const RealTimeSampleArrayValue & rtsav) {
        streamHandler.updateStateValue(rtsav); // updates handles and the parent provider
    }

private:

    OSCPProvider oscpProvider;
	RealTimeSampleArrayMetricDescriptor streamMetricDescriptor;
	NumericMetricDescriptor setMetricDescriptor;
    StreamProviderStateHandler streamHandler;
    GetNumericMetricStateHandler getNumericHandler;
    SetNumericMetricStateHandler setNumericHandler;

public:

    // Produce stream values
    // runImpl() gets called when starting the provider thread by the inherited function start()
    virtual void runImpl() override {

    	// RealTimeArray
		const std::size_t size(1000);
		std::vector<double> samples;
		for (std::size_t i = 0; i < size; i++) {
			samples.push_back(i);
		}
		long index(0);
		while (!isInterrupted()) {
			{
                updateStateValue(
						RealTimeSampleArrayValue()
						.setSamples(
							RTValueType()
							.setValues(samples))
						);

			}
//			DebugOut(DebugOut::Default, "ExampleProvider4SoftICEStreaming") << "Produced stream chunk of size " << size << ", index " << index << std::endl;

			// NumericMetricState
			getNumericHandler.setNumericValue(42.0);
//			DebugOut(DebugOut::Default, "ExampleProvider4SoftICEStreaming") << "NumericMetric: value changed to 42.0" << std::endl;
			Poco::Thread::sleep(1000);
			index += size;

		}
    }
};



int main()
{
	// Startup
	DebugOut(DebugOut::Default, "ExampleProvider4SoftICEStreaming") << "Startup" << std::endl;
    OSCLibrary::getInstance().startup(OSELib::LogLevel::DEBUG);
    OSCLibrary::getInstance().setIP6enabled(false);
    OSCLibrary::getInstance().setIP4enabled(true);

	OSELib::OSCP::ServiceManager oscpsm;
	OSCPStreamProvider provider;
	provider.startup();
	provider.start();

	std::string temp;
	DebugOut(DebugOut::Default, "ExampleProvider4SoftICEStreaming") << "Press key to exit program.";
	std::cin >> temp;

	// Shutdown
	DebugOut(DebugOut::Default, "ExampleProvider4SoftICEStreaming") << "Shutdown." << std::endl;
	provider.shutdown();
    OSCLibrary::getInstance().shutdown();
}
