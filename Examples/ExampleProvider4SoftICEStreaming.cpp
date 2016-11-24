/*
 * ExampleProvider4SoftICEStreaming.cpp
 *
 *  @Copyright (C) 2016, SurgiTAIX AG
 *  Author: buerger
 */

#include "OSCLib/OSCLibrary.h"
#include "OSCLib/Data/OSCP/OSCPProvider.h"
#include "OSCLib/Data/OSCP/OSCPProviderRealTimeSampleArrayMetricStateHandler.h"
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

const std::string deviceEPR("DEMO-123");



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

    OSCPStreamProvider() : oscpProvider(), streamHandler("handle_stream") {

		oscpProvider.setEndpointReference(deviceEPR);

        // Handles and handle references of their states
        currentMetric.setHandle("handle_stream");

        // metric stream metric (read-only)
        currentMetric
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
                    .setCodeId("MDCX_PLETHYSMOGRAM"));


        // Channel
        ChannelDescriptor holdingDeviceParameters;
        holdingDeviceParameters
			.addMetric(currentMetric)
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

        // create and add description
		MDDescription mdDescription;
		mdDescription.addMDSDescriptor(holdingDeviceSystem);

		oscpProvider.setMDDescrition(mdDescription);

        // Add handler
        oscpProvider.addMDStateHandler(&streamHandler);
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
	RealTimeSampleArrayMetricDescriptor currentMetric;
    StreamProviderStateHandler streamHandler;

public:

    // Produce stream values
    // runImpl() gets called when starting the provider thread by the inherited function start()
    virtual void runImpl() override {
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
			DebugOut(DebugOut::Default, "ExampleProvider4SoftICEStreaming") << "Produced stream chunk of size " << size << ", index " << index << std::endl;
			Poco::Thread::sleep(1000);
			index += size;
		}
    }
};



int main()
{
	// Startup
	DebugOut(DebugOut::Default, "ExampleProvider4SoftICEStreaming") << "Startup";
    OSCLibrary::getInstance().startup();

	OSELib::OSCP::ServiceManager oscpsm;

	// Provider
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
