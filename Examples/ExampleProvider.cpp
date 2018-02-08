/*
 * ExampleProvider.cpp
 *
 *  @Copyright (C) 2016, SurgiTAIX AG
 *  Author: buerger
 *
 *  This program sends a RealTimeSampleArrayMetricState (HANDLE_STREAM_METRIC) and a NumericMatricState (HANDLE_GET_METRIC) to the network. It changes the HANDLE_STREAM_METRIC
 *
 */

#include "OSCLib/SDCLibrary.h"
#include "OSCLib/Data/OSCP/SDCProvider.h"

#include "OSCLib/Data/OSCP/SDCProviderComponentStateHandler.h"
#include "OSCLib/Data/OSCP/SDCProviderStateHandler.h"
#include "OSCLib/Data/OSCP/SDCProviderMDStateHandler.h"
#include "OSCLib/Data/OSCP/MDIB/MdsState.h"
#include "OSCLib/Data/OSCP/MDIB/ChannelDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/MDIB/MdsDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/LocalizedText.h"
#include "OSCLib/Data/OSCP/MDIB/MdDescription.h"
#include "OSCLib/Data/OSCP/MDIB/MetricQuality.h"
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

#include "BICEPS_MessageModel-fwd.hxx"

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


const std::string DEVICE_EPR("UDI-EXAMPLEPROVIDER");

const std::string VMD_DESCRIPTOR_HANDLE("holdingDevice_vmd");
const std::string CHANNEL_DESCRIPTOR_HANDLE("holdingDevice_channel");
const std::string MDS_DESCRIPTOR_HANDLE("holdingDevice_mds");

const std::string HANDLE_SET_METRIC("handle_set");
const std::string HANDLE_GET_METRIC("handle_get");
const std::string HANDLE_STREAM_METRIC("handle_stream");
const std::string HANDLE_STRING_METRIC("handle_string");


class NumericProviderStateHandlerGet : public SDCProviderMDStateHandler<NumericMetricState> {
public:

	NumericProviderStateHandlerGet(std::string descriptorHandle) : SDCProviderMDStateHandler(descriptorHandle) {
	}


	// Helper method
	NumericMetricState createState(double value) {
		NumericMetricState result(HANDLE_GET_METRIC);
		result
			.setMetricValue(NumericMetricValue(MetricQuality(MeasurementValidity::Vld)).setValue(value))
			.setActivationState(ComponentActivation::On);
		return result;
	}

	// define how to react on a request for a state change. This handler should not be set, thus always return Fail.
	InvocationState onStateChangeRequest(const NumericMetricState & state, const OperationInvocationContext & oic) override {
		return InvocationState::Fail;
	}


	NumericMetricState getInitialState() override {
		NumericMetricState nms = createState(42.0);
		return nms;
	}

	void setNumericValue(double value) {
		NumericMetricState nms = createState(value);
		updateState(nms);
	}
};



class NumericProviderStateHandlerSet : public SDCProviderMDStateHandler<NumericMetricState> {
public:

    NumericProviderStateHandlerSet(const std::string descriptorHandle) : SDCProviderMDStateHandler(descriptorHandle) {
    }

    InvocationState onStateChangeRequest(const NumericMetricState & state, const OperationInvocationContext & oic) override {
    	// Invocation has been fired as WAITING when entering this method
    	notifyOperationInvoked(oic, InvocationState::Start);
    	// Do stuff
        DebugOut(DebugOut::Default, "ExampleProvider") << "Provider: handle_set received state change request. State's value: " << state.getMetricValue().getValue() << std::endl;
        // if success return Finished
        return InvocationState::Fin;  // Framework will update internal MDIB with the state's value and increase MDIB version
    }

    // Helper method
    NumericMetricState createState() {
        NumericMetricState result(HANDLE_SET_METRIC);
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
        std::unique_ptr<NumericMetricState> result(getParentProvider().getMdState().findState<NumericMetricState>(HANDLE_SET_METRIC));

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


class StreamProviderStateHandler : public SDCProviderMDStateHandler<RealTimeSampleArrayMetricState> {
public:

    StreamProviderStateHandler(std::string descriptorHandle) : SDCProviderMDStateHandler(descriptorHandle) {
    }

    // Helper method
    RealTimeSampleArrayMetricState createState() {
        RealTimeSampleArrayMetricState realTimeSampleArrayState(descriptorHandle);
        realTimeSampleArrayState
            .setActivationState(ComponentActivation::On);
        return realTimeSampleArrayState;
    }


    RealTimeSampleArrayMetricState getInitialState() override {
        return createState();
    }

    // disallow set operation for this state
    InvocationState onStateChangeRequest(const RealTimeSampleArrayMetricState & state, const OperationInvocationContext & oic) override {
    	return InvocationState::Fail;
    }


    // convenient update method
    void updateStateValue(const SampleArrayValue & sav) {
        RealTimeSampleArrayMetricState realTimeSampleArrayState = createState();
        realTimeSampleArrayState
            .setMetricValue(sav);
        updateState(realTimeSampleArrayState);
    }
};

class StringProviderStateHandler : public SDCProviderMDStateHandler<StringMetricState> {
public:
	StringProviderStateHandler(std::string descriptorHandle) : SDCProviderMDStateHandler(descriptorHandle) {

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
		StringMetricState result(HANDLE_STRING_METRIC);
		result
			.setMetricValue(StringMetricValue(MetricQuality(MeasurementValidity::Vld)).setValue("StringMetricValueInit"));

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

    OSCPStreamProvider() :
    	oscpProvider(),
    	streamProviderStateHandler(HANDLE_STREAM_METRIC),
    	stringProviderStateHandler(HANDLE_STRING_METRIC),
    	numericProviderStateHandlerGet(HANDLE_GET_METRIC),
    	numericProviderStateHandlerSet(HANDLE_SET_METRIC),
    	streamMetricDescriptor(HANDLE_STREAM_METRIC,
    		    		CodedValue("MDCX_EXAMPLE_STREAM"),
    		    		MetricCategory::Msrmt,
    		    		MetricAvailability::Cont,
    		    		1,
    		    		xml_schema::Duration(0,0,0,0,0,0,1)),
		setMetricDescriptor(HANDLE_SET_METRIC,
						CodedValue("MDCX_EXAMPLE_SET"),
						MetricCategory::Set,
						MetricAvailability::Cont,
						1.0),
		getMetricDescriptor(HANDLE_GET_METRIC,
						CodedValue("MDCX_EXAMPLE_GET"),
						MetricCategory::Set,
						MetricAvailability::Cont,
						1),
		stringMetricDescriptor(HANDLE_STRING_METRIC,
						CodedValue("MDCX_EXAMPLE_STRING"),
						MetricCategory::Set,
						MetricAvailability::Cont)
    	{

		oscpProvider.setEndpointReference(DEVICE_EPR);
		Dev::DeviceCharacteristics devChar;
		devChar.addFriendlyName("en", "OSCLib ExampleProvider");
		oscpProvider.setDeviceCharacteristics(devChar);

        // Channel
        ChannelDescriptor holdingDeviceParameters(CHANNEL_DESCRIPTOR_HANDLE);
        holdingDeviceParameters
        	.setSafetyClassification(SafetyClassification::MedB)
			.addMetric(streamMetricDescriptor)
			.addMetric(setMetricDescriptor)
			.addMetric(getMetricDescriptor)
			.addMetric(stringMetricDescriptor);


        // VMD
        VmdDescriptor holdingDeviceModule(VMD_DESCRIPTOR_HANDLE);
        holdingDeviceModule
        	.addChannel(holdingDeviceParameters);

        // MDS
        MdsDescriptor holdingDeviceSystem(MDS_DESCRIPTOR_HANDLE);
        holdingDeviceSystem
        	.setType(CodedValue("MDC_DEV_DOCU_POSE_MDS")
        			.addConceptDescription(LocalizedText().setRef("uri/to/file.txt").setLang("en")))
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

		oscpProvider.setMdDescription(mdDescription);

        // Add handler
		oscpProvider.addMdSateHandler(&numericProviderStateHandlerGet);
		oscpProvider.addMdSateHandler(&streamProviderStateHandler);

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

    SDCProvider oscpProvider;

    StreamProviderStateHandler streamProviderStateHandler;
    StringProviderStateHandler stringProviderStateHandler;
    NumericProviderStateHandlerGet numericProviderStateHandlerGet;
    NumericProviderStateHandlerSet numericProviderStateHandlerSet;


    RealTimeSampleArrayMetricDescriptor streamMetricDescriptor;
    NumericMetricDescriptor setMetricDescriptor;
    NumericMetricDescriptor getMetricDescriptor;
    StringMetricDescriptor  stringMetricDescriptor;


public:

    // Produce stream values
    // runImpl() gets called when starting the provider thread by the inherited function start()
    virtual void runImpl() override {

    	// RealTimeArray
		const std::size_t size(10);
		RealTimeValueType samples;
		for (std::size_t i = 0; i < size; i++) {
			samples.push_back(i);
		}
		long index(0);

		while (!isInterrupted()) {
			{
                updateStateValue(SampleArrayValue(MetricQuality(MeasurementValidity::Vld)).setSamples(samples));
			}
			DebugOut(DebugOut::Default, "ExampleProvider") << "Produced stream chunk of size " << size << ", index " << index << std::endl;

			// Update the NumericMetricState's value using the state handler's method
			numericProviderStateHandlerGet.setNumericValue(index/size);
			DebugOut(DebugOut::Default, "ExampleProvider") << "NumericMetric: value changed to " << index/size << std::endl;
			Poco::Thread::sleep(1000);
			index += size;

		}
    }
};



int main()
{
	// Startup
	DebugOut(DebugOut::Default, "ExampleProvider") << "Startup" << std::endl;
    SDCLibrary::getInstance().startup(OSELib::LogLevel::ERROR);
    SDCLibrary::getInstance().setIP6enabled(false);
    SDCLibrary::getInstance().setIP4enabled(true);

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
    SDCLibrary::getInstance().shutdown();
}
