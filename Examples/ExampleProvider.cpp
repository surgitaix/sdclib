/*
 * ExampleProvider.cpp
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
#include "OSCLib/Data/OSCP/OSCPProviderStringMetricStateHandler.h"
#include "OSCLib/Data/OSCP/MDIB/ChannelDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/MDIB/MdsDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/LocalizedText.h"
#include "OSCLib/Data/OSCP/MDIB/MdDescription.h"
#include "OSCLib/Data/OSCP/MDIB/Range.h"
#include "OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/SampleArrayValue.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricValue.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/StringMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/StringMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/StringMetricValue.h"
#include "OSCLib/Data/OSCP/MDIB/SystemContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/MetaData.h"
#include "OSCLib/Dev/DeviceCharacteristics.h"
#include "OSCLib/Data/OSCP/MDIB/VmdDescriptor.h"

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


const std::string DEVICE_EPR("UDI-1234567890");
const std::string VMD_DESCRIPTOR_HANDLE("holdingDevice_vmd");
const std::string CHANNEL_DESCRIPTOR_HANDLE("holdingDevice_channel");
const std::string MDS_DESCRIPTOR_HANDLE("holdingDevice_mds");

class NumericProviderStateHandlerGet : public OSCPProviderNumericMetricStateHandler {
public:

	NumericProviderStateHandlerGet(std::string descriptorHandle) : descriptorHandle(descriptorHandle) {
	}


	// Helper method
	NumericMetricState createState(double value) {
		NumericMetricState result;
		result
			.setMetricValue(NumericMetricValue().setValue(value))
			.setActivationState(ComponentActivation::On)
			.setDescriptorHandle("handle_get");
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



class NumericProviderStateHandlerSet : public OSCPProviderNumericMetricStateHandler {
public:

    NumericProviderStateHandlerSet(const std::string descriptorHandle) : descriptorHandle(descriptorHandle) {
    }

    InvocationState onStateChangeRequest(const NumericMetricState & state, const OperationInvocationContext & oic) override {
    	// Invocation has been fired as WAITING when entering this method
    	notifyOperationInvoked(oic, InvocationState::Start);
    	// Do stuff
        DebugOut(DebugOut::Default, "SimpleOSCP") << "Provider: handle_set received state change request. State's value: " << state.getMetricValue().getValue() << std::endl;
        // if success return Finished
        return InvocationState::Fin;  // Framework will update internal MDIB with the state's value and increase MDIB version
    }

    // Helper method
    NumericMetricState createState() {
        NumericMetricState result;
        result
            .setMetricValue(NumericMetricValue().setValue(2.0))
            .setActivationState(ComponentActivation::On)
            .setDescriptorHandle("handle_set");

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
        getParentProvider().getMdState().findState("handle_set", result);
        // TODO: in real applications, check if state has an observed value and if the observed value has a value!
        return (float)result.getMetricValue().getValue();
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
            .setActivationState(ComponentActivation::On)
            .setDescriptorHandle(descriptorHandle);

        return realTimeSampleArrayState;
    }


    RealTimeSampleArrayMetricState getInitialState() override {
        return createState();
    }


    void updateStateValue(const SampleArrayValue & sav) {
        RealTimeSampleArrayMetricState realTimeSampleArrayState = createState();
        realTimeSampleArrayState
            .setMetricValue(sav);
        updateState(realTimeSampleArrayState);
    }


private:
    std::string descriptorHandle;
};


class StringProviderStateHandler : public OSCPProviderStringMetricStateHandler {
public:
	StringProviderStateHandler(std::string descriptorHandle) : descriptorHandle(descriptorHandle) {

	}

	InvocationState onStateChangeRequest(const StringMetricState & state, const OperationInvocationContext & oic) override {
		notifyOperationInvoked(oic, InvocationState::Start);
		// Do something if a state change is requested
		DebugOut(DebugOut::Default, "ExampleProvider") << "String state of provider state changed to " << state.getMetricValue().getValue() << std::endl;
		// return Finished if successful
		return InvocationState::Fin;
	}


	// Helper method
	StringMetricState createState() {
		StringMetricState result;
		result
			.setDescriptorHandle("handle_string")
			.setMetricValue(StringMetricValue().setValue("StringMetricValueInit"));

	    return result;
	}

	StringMetricState getInitialState() override {
		StringMetricState result = createState();
	        return result;
	    }

private:
	std::string descriptorHandle;
};


class OSCPStreamProvider : public Util::Task {
public:

    OSCPStreamProvider() : oscpProvider(), streamProviderStateHandler("handle_stream"), stringProviderStateHandler("handle_string"), numericProviderStateHandlerGet("handle_get"), numericProviderStateHandlerSet("handle_set") {

		oscpProvider.setEndpointReference(DEVICE_EPR);
		Dev::DeviceCharacteristics devChar;
		devChar.addFriendlyName("en", "OSCLib ExampleProvider");
		oscpProvider.setDeviceCharacteristics(devChar);

		// Important:
        // each handle references its state
        streamMetricDescriptor.setHandle("handle_stream");
        setMetricDescriptor.setHandle("handle_set");
        getMetricDescriptor.setHandle("handle_get");
        stringMetricDescriptor.setHandle("handle_string");

        // metric stream metric (read-only)
        streamMetricDescriptor
        	.setMetricAvailability(MetricAvailability::Cont)
        	.setResolution(1.0)
        	.setType(CodedValue().setCode("MDCX_XXX"))
        	.setMetricCategory(MetricCategory::Msrmt)
        	.addTechnicalRange(Range().setLower(0).setUpper(2));

        setMetricDescriptor
        	.setMetricCategory(MetricCategory::Set)
        	.setMetricAvailability(MetricAvailability::Cont)
        	.setType(CodedValue().addConceptDescription(LocalizedText().setRef("uri/to/file.txt").setLang("en")));

        getMetricDescriptor
			.setMetricAvailability(MetricAvailability::Cont)
			.setType(CodedValue().addConceptDescription(LocalizedText().setRef("uri/to/file.txt").setLang("en")));

        stringMetricDescriptor
        	.setMetricAvailability(MetricAvailability::Cont)
        	.setType(CodedValue().addConceptDescription(LocalizedText().setRef("uri/to/file.txt").setLang("en")));

        // Channel
        ChannelDescriptor holdingDeviceParameters;
        holdingDeviceParameters
        	.setHandle(CHANNEL_DESCRIPTOR_HANDLE)
        	.setSafetyClassification(SafetyClassification::MedB)
			.addMetric(streamMetricDescriptor)
			.addMetric(setMetricDescriptor)
			.addMetric(getMetricDescriptor)
			.addMetric(stringMetricDescriptor);


        // VMD
        VmdDescriptor holdingDeviceModule;
        holdingDeviceModule
        	.setHandle(VMD_DESCRIPTOR_HANDLE)
        	.addChannel(holdingDeviceParameters);

        // MDS
        MdsDescriptor holdingDeviceSystem;
        holdingDeviceSystem
        	.setHandle(MDS_DESCRIPTOR_HANDLE)
        	//.setType(CodedValue().addConceptDescription(LocalizedText().setRef("uri/to/file.txt").setLang("en")))
        	.setMetaData(
        		MetaData().addManufacturer(LocalizedText().setRef("SurgiTAIX AG"))
        		.setModelNumber("1")
        		.addModelName(LocalizedText().setRef("EndoTAIX"))
        		.addSerialNumber("1234"))
        	.addVmd(holdingDeviceModule);


        oscpProvider.createSetOperationForDescriptor(setMetricDescriptor, holdingDeviceSystem);

        // create and add description
		MdDescription mdDescription;
		mdDescription.addMdsDescriptor(holdingDeviceSystem);

		oscpProvider.setMDDescription(mdDescription);

        // Add handler
		oscpProvider.addMdSateHandler(&streamProviderStateHandler);
		oscpProvider.addMdSateHandler(&numericProviderStateHandlerGet);
		oscpProvider.addMdSateHandler(&numericProviderStateHandlerSet);
		oscpProvider.addMdSateHandler(&stringProviderStateHandler);

    }

    void startup() {
    	oscpProvider.startup();
    }

    void shutdown() {
    	oscpProvider.shutdown();
    }

    void updateStateValue(const SampleArrayValue & sav) {
        streamProviderStateHandler.updateStateValue(sav); // updates handles and the parent provider
    }

private:

    OSCPProvider oscpProvider;
	RealTimeSampleArrayMetricDescriptor streamMetricDescriptor;
	NumericMetricDescriptor setMetricDescriptor;
	NumericMetricDescriptor getMetricDescriptor;
	StringMetricDescriptor stringMetricDescriptor;

    StreamProviderStateHandler streamProviderStateHandler;
    NumericProviderStateHandlerGet numericProviderStateHandlerGet;
    NumericProviderStateHandlerSet numericProviderStateHandlerSet;
    StringProviderStateHandler stringProviderStateHandler;

public:

    // Produce stream values
    // runImpl() gets called when starting the provider thread by the inherited function start()
    virtual void runImpl() override {

    	// RealTimeArray
		const std::size_t size(1000);
		RealTimeValueType samples;
		for (std::size_t i = 0; i < size; i++) {
			samples.push_back(i);
		}
		long index(0);

		while (!isInterrupted()) {
			{
                updateStateValue(SampleArrayValue().setSamples(samples));
			}
			DebugOut(DebugOut::Default, "ExampleProvider") << "Produced stream chunk of size " << size << ", index " << index << std::endl;

			// NumericMetricState
			numericProviderStateHandlerGet.setNumericValue(42.0);
//			DebugOut(DebugOut::Default, "ExampleProvider") << "NumericMetric: value changed to 42.0" << std::endl;
			Poco::Thread::sleep(1000);
			index += size;

		}
    }
};



int main()
{
	// Startup
	DebugOut(DebugOut::Default, "ExampleProvider") << "Startup" << std::endl;
    OSCLibrary::getInstance().startup(OSELib::LogLevel::DEBUG);
    OSCLibrary::getInstance().setIP6enabled(false);
    OSCLibrary::getInstance().setIP4enabled(true);

	OSELib::OSCP::ServiceManager oscpsm;
	OSCPStreamProvider provider;
	provider.startup();
	provider.start();

	std::string temp;
	DebugOut(DebugOut::Default, "ExampleProvider") << "Press key to exit program.";
	std::cin >> temp;

	// Shutdown
	DebugOut(DebugOut::Default, "ExampleProvider") << "Shutdown." << std::endl;
	provider.shutdown();
    OSCLibrary::getInstance().shutdown();
}
