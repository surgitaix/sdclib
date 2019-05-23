/*
 * ExampleCachedProvider.cpp
 *
 *  @Copyright (C) 2017, SurgiTAIX AG
 *  Author: buerger
 *
 *  The ExampleCachedProvider uses an .xml file ('cachedMdib.xml') to build up an SDCProvider device. It further shows how some of the the providers states ('') can be used to
 *
 */


#include <string>
#include <fstream>
#include <streambuf>

#include "SDCLib/SDCLibrary.h"
#include "SDCLib/Data/SDC/SDCProvider.h"
#include "SDCLib/Data/SDC/SDCProviderMDStateHandler.h"
#include "SDCLib/Data/SDC/MDIB/ChannelDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/CodedValue.h"
#include "SDCLib/Data/SDC/MDIB/SimpleTypesMapping.h"
#include "SDCLib/Data/SDC/MDIB/MdsDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/MetricQuality.h"
#include "SDCLib/Data/SDC/MDIB/LocalizedText.h"
#include "SDCLib/Data/SDC/MDIB/MdDescription.h"
#include "SDCLib/Data/SDC/MDIB/Range.h"
#include "SDCLib/Data/SDC/MDIB/RealTimeSampleArrayMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/RealTimeSampleArrayMetricState.h"
#include "SDCLib/Data/SDC/MDIB/SampleArrayValue.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricState.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricValue.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/SystemContextDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/MetaData.h"
#include "SDCLib/Data/SDC/MDIB/VmdDescriptor.h"
#include "SDCLib/Util/DebugOut.h"
#include "SDCLib/Util/Task.h"

#include "OSELib/SDC/ServiceManager.h"

#include "Poco/Runnable.h"
#include "Poco/Mutex.h"
#include "Poco/ScopedLock.h"
#include "Poco/Thread.h"

using namespace SDCLib;
using namespace SDCLib::Util;
using namespace SDCLib::Data::SDC;

const std::string ts_file("cachedMdib.xml");

const std::string DEVICE_EPR("UDI-EXAMPLEPROVIDER");

const std::string HANDLE_SET_METRIC("handle_set");
const std::string HANDLE_GET_METRIC("handle_get");
const std::string HANDLE_STREAM_METRIC("handle_stream");

class GetNumericMetricStateHandler : public SDCProviderMDStateHandler<NumericMetricState> {
public:

	// The state handler take a string named as the descriptor for referencing
	GetNumericMetricStateHandler(std::string descriptorHandle) : SDCProviderMDStateHandler(descriptorHandle) {
	}


	// Helper method
	NumericMetricState createState(double value) {
		NumericMetricState result(descriptorHandle);
		result
			.setMetricValue(NumericMetricValue(MetricQuality(MeasurementValidity::Vld)).setValue(value))
			.setActivationState(ComponentActivation::On);
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

    // do nothing when a consumer ask to change the value -> return Fail
    InvocationState onStateChangeRequest(const NumericMetricState&, const OperationInvocationContext&) override {
    	return InvocationState::Fail;
    }
};



class SetNumericMetricStateHandler : public SDCProviderMDStateHandler<NumericMetricState> {
public:
	// The state handler take a string named as the descriptor for referencing
    SetNumericMetricStateHandler(const std::string descriptorHandle) : SDCProviderMDStateHandler(descriptorHandle) {
    }

    InvocationState onStateChangeRequest(const NumericMetricState & state, const OperationInvocationContext & oic) override {
        // Invocation has been fired as WAITING when entering this method
        DebugOut(DebugOut::Default, "SimpleSDC") << "Provider: handle_set received state change request. State's value: " << state.getMetricValue().getValue() << std::endl;

        notifyOperationInvoked(oic, InvocationState::Start);

        return InvocationState::Fin;  // Framework will update internal MDIB with the state's value and increase MDIB version
    }

    // Helper method
    NumericMetricState createState() {
		NumericMetricState result(descriptorHandle);
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
        	DebugOut(DebugOut::Default, "ExampleCachedProvider") << "Maximum weight metric not found." << std::endl;
        	return 0;
        }

    }
};


// implements a measurement state of several measured values
class StreamProviderStateHandler : public SDCProviderMDStateHandler<RealTimeSampleArrayMetricState> {
public:
	// The state handler take a string named as the descriptor for referencing
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

    void updateStateValue(const SampleArrayValue & sav) {
        RealTimeSampleArrayMetricState realTimeSampleArrayState = createState();
        realTimeSampleArrayState
            .setMetricValue(sav);
        updateState(realTimeSampleArrayState);
    }

    // do nothing when a consumer ask to change the value -> return Fail
    InvocationState onStateChangeRequest(const RealTimeSampleArrayMetricState&, const OperationInvocationContext&) override {
    	return InvocationState::Fail;
    }
};

class OSCPStreamProvider : public Util::Task {
public:

    OSCPStreamProvider(SDCInstance_shared_ptr p_SDCInstance, std::ifstream& p_stream) : sdcProvider(p_SDCInstance), streamHandler(HANDLE_STREAM_METRIC), getNumericHandler(HANDLE_GET_METRIC), setNumericHandler(HANDLE_SET_METRIC) {

        assert(p_stream.is_open());

		sdcProvider.setEndpointReference(DEVICE_EPR);


		std::stringstream buffer;
		buffer << p_stream.rdbuf();
		std::string mdDesciption_xml = buffer.str();
        p_stream.close();

		DebugOut(DebugOut::Default, "ExampleCachedProvider") << mdDesciption_xml;

		// set DPWS metadata, e.g. for the displayed friendly name
		Dev::DeviceCharacteristics devChar;
		devChar.addFriendlyName("en", "SDCLib ExampleProvider");
		sdcProvider.setDeviceCharacteristics(devChar);

		sdcProvider.setMdDescription(mdDesciption_xml);

        // Add handler
		sdcProvider.addMdStateHandler(&streamHandler);
		sdcProvider.addMdStateHandler(&getNumericHandler);
		sdcProvider.addMdStateHandler(&setNumericHandler);
    }

    void startup() {
    	sdcProvider.startup();
    }

    void shutdown() {
    	sdcProvider.shutdown();
    }

    void updateStateValue(const SampleArrayValue & sav) {
        streamHandler.updateStateValue(sav); // updates handles and the parent provider
    }

private:

    // API provider class
    SDCProvider sdcProvider;

    // State Handlers
    // each state handler ist named the same way as regarding descriptor
    StreamProviderStateHandler streamHandler;
    GetNumericMetricStateHandler getNumericHandler;
    SetNumericMetricStateHandler setNumericHandler;

public:

    // Produce stream values
    // runImpl() gets called when starting the provider thread by the inherited function start()
    virtual void runImpl() override {

    	// Streaming init
		const std::size_t size(1000);
		std::vector<double> samples;
		for (std::size_t i = 0; i < size; i++) {
			samples.push_back(i);
		}
		long index(0);

		while (!isInterrupted()) {
			{
                updateStateValue(SampleArrayValue(MetricQuality(MeasurementValidity::Vld)).setSamples(RealTimeValueType(samples)));
			}
			DebugOut(DebugOut::Default, "ExampleCachedProvider") << "Produced stream chunk of size " << size << ", index " << index << std::endl;

			// generate NumericMetricState
			getNumericHandler.setNumericValue(42.0);
			DebugOut(DebugOut::Default, "ExampleCachedProvider") << "NumericMetric: value changed to 42.0" << std::endl;
			Poco::Thread::sleep(1000);
			index += size;
		}
    }
};



int main()
{
    // Load cached Mdib from file system
    // Mdib is specified in xml
    std::ifstream t_stream(ts_file);
    // Found?
    if(!t_stream.is_open()) {
        DebugOut(DebugOut::Default, "ExampleCachedProvider") << "Could not open " << ts_file << "\n";
        return -1;
    }

	// Startup
	DebugOut(DebugOut::Default, "ExampleCachedProvider") << "Startup" << std::endl;
    SDCLibrary::getInstance().startup(OSELib::LogLevel::Debug);

	// Create a new SDCInstance (no flag will auto init)
    auto t_SDCInstance = std::make_shared<SDCInstance>(Config::SDC_DEFAULT_PORT_PROVIDER, true);
    // Some restriction
    t_SDCInstance->setIP6enabled(false);
    t_SDCInstance->setIP4enabled(true);
    // Bind it to interface that matches the internal criteria (usually the first enumerated)
    if(!t_SDCInstance->bindToDefaultNetworkInterface()) {
        std::cout << "Failed to bind to default network interface! Exit..." << std::endl;
        return -1;
    }

    OSELib::SDC::ServiceManager oscpsm(t_SDCInstance);
	OSCPStreamProvider provider(t_SDCInstance, t_stream);
	provider.startup();
	provider.start();

	std::string temp;
	DebugOut(DebugOut::Default, "ExampleCachedProvider") << "Press key to exit program.";
	std::cin >> temp;

	// Shutdown
	DebugOut(DebugOut::Default, "ExampleCachedProvider") << "Shutdown." << std::endl;
	provider.shutdown();
    SDCLibrary::getInstance().shutdown();
}
