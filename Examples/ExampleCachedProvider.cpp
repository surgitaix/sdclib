/*
 * ExampleCachedProvider.cpp
 *
 *  @Copyright (C) 2017, SurgiTAIX AG
 *  Author: buerger
 *
 *  The ExampleCachedProvider uses an .xml file ('cachedMdib.xml') to build up an OSCP-provider device. It further shows how some of the the providers states ('') can be used to
 *
 */


#include <string>
#include <fstream>
#include <streambuf>

#include "OSCLib/OSCLibrary.h"
#include "OSCLib/Data/OSCP/OSCPProvider.h"
#include "OSCLib/Data/OSCP/SDCProviderMetricAndAlertStateHandler.h"
#include "OSCLib/Data/OSCP/MDIB/ChannelDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/MDIB/MdsDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/MetricQuality.h"
#include "OSCLib/Data/OSCP/MDIB/LocalizedText.h"
#include "OSCLib/Data/OSCP/MDIB/MdDescription.h"
#include "OSCLib/Data/OSCP/MDIB/Range.h"
#include "OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/SampleArrayValue.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricValue.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/SystemContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/MetaData.h"
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


const std::string DEVICE_EPR("UDI-EXAMPLEPROVIDER");

const std::string HANDLE_SET_METRIC("handle_set");
const std::string HANDLE_GET_METRIC("handle_get");
const std::string HANDLE_STREAM_METRIC("handle_stream");


class GetNumericMetricStateHandler : public SDCProviderMetricAndAlertStateHandler<NumericMetricState> {
public:

	// The state handler take a string named as the descriptor for referencing
	GetNumericMetricStateHandler(std::string descriptorHandle) : SDCProviderMetricAndAlertStateHandler(descriptorHandle) {
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
    InvocationState onStateChangeRequest(const NumericMetricState & state, const OperationInvocationContext & oic) override {
    	return InvocationState::Fail;
    }
};



class SetNumericMetricStateHandler : public SDCProviderMetricAndAlertStateHandler<NumericMetricState> {
public:
	// The state handler take a string named as the descriptor for referencing
    SetNumericMetricStateHandler(const std::string descriptorHandle) : SDCProviderMetricAndAlertStateHandler(descriptorHandle) {
    }

    InvocationState onStateChangeRequest(const NumericMetricState & state, const OperationInvocationContext & oic) override {
        // Invocation has been fired as WAITING when entering this method
        DebugOut(DebugOut::Default, "SimpleOSCP") << "Provider: handle_set received state change request. State's value: " << state.getMetricValue().getValue() << std::endl;

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
class StreamProviderStateHandler : public SDCProviderMetricAndAlertStateHandler<RealTimeSampleArrayMetricState> {
public:
	// The state handler take a string named as the descriptor for referencing
    StreamProviderStateHandler(std::string descriptorHandle) : SDCProviderMetricAndAlertStateHandler(descriptorHandle) {
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
    InvocationState onStateChangeRequest(const RealTimeSampleArrayMetricState & state, const OperationInvocationContext & oic) override {
    	return InvocationState::Fail;
    }
};

class OSCPStreamProvider : public Util::Task {
public:

    OSCPStreamProvider() : oscpProvider(), streamHandler(HANDLE_STREAM_METRIC), getNumericHandler(HANDLE_GET_METRIC), setNumericHandler(HANDLE_SET_METRIC) {

		oscpProvider.setEndpointReference(DEVICE_EPR);

		// Load cached Mdib from file system
		// Mdib is specified in xml
		std::ifstream t("Examples/cachedMdib.xml");
		std::stringstream buffer;
		buffer << t.rdbuf();
		std::string mdDesciption_xml = buffer.str();

		DebugOut(DebugOut::Default, "ExampleCachedProvider") << mdDesciption_xml;

		oscpProvider.setMdDescription(mdDesciption_xml);

        // Add handler
		oscpProvider.addMdSateHandler(&streamHandler);
		oscpProvider.addMdSateHandler(&getNumericHandler);
		oscpProvider.addMdSateHandler(&setNumericHandler);
    }

    void startup() {
    	oscpProvider.startup();
    }

    void shutdown() {
    	oscpProvider.shutdown();
    }

    void updateStateValue(const SampleArrayValue & sav) {
        streamHandler.updateStateValue(sav); // updates handles and the parent provider
    }

private:

    // API provider class
    OSCPProvider oscpProvider;

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
			DebugOut(DebugOut::Default, "ExampleProvider4SoftICEStreaming") << "Produced stream chunk of size " << size << ", index " << index << std::endl;

			// generate NumericMetricState
			getNumericHandler.setNumericValue(42.0);
			DebugOut(DebugOut::Default, "ExampleProvider4SoftICEStreaming") << "NumericMetric: value changed to 42.0" << std::endl;
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
