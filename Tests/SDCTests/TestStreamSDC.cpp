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
 * TestStreamSDC.cpp
 *
 *  @Copyright (C) 2018, SurgiTAIX AG
 *  Author: buerger
 *
 *  This unit test checks the eventing mechanism for the udp based stream metrices: RealTimeSampleArrayMetric (time values) and DistributionSampleArrayMetric (other values)
 *  At the current state of the IEEE 11073 SDC BICEPS specification the DSAMS is transported via TCP, maybe this changes soon. Then SDCProvider::updateState has to be adapted accordingly
 *
 */

#include <atomic>
#include <thread>

#include "OSELib/SDC/ServiceManager.h"
#include "SDCLib/Data/SDC/SDCConsumer.h"
#include "SDCLib/Data/SDC/SDCConsumerMDStateHandler.h"
#include "SDCLib/Data/SDC/SDCProvider.h"
#include "SDCLib/Data/SDC/SDCProviderMDStateHandler.h"

#include "SDCLib/Data/SDC/MDIB/ChannelDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/CodedValue.h"

#include "SDCLib/Data/SDC/MDIB/MdsDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/LocalizedText.h"
#include "SDCLib/Data/SDC/MDIB/MdDescription.h"
#include "SDCLib/Data/SDC/MDIB/Measurement.h"
#include "SDCLib/Data/SDC/MDIB/MetricQuality.h"
#include "SDCLib/Data/SDC/MDIB/Range.h"
#include "SDCLib/Data/SDC/MDIB/RealTimeSampleArrayMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/RealTimeSampleArrayMetricState.h"
#include "SDCLib/Data/SDC/MDIB/DistributionSampleArrayMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/DistributionSampleArrayMetricState.h"
#include "SDCLib/Data/SDC/MDIB/SampleArrayValue.h"

#include "SDCLib/Data/SDC/MDIB/MetaData.h"
#include "SDCLib/Data/SDC/MDIB/VmdDescriptor.h"
#include "SDCLib/Util/DebugOut.h"
#include "SDCLib/Util/Task.h"


#include "../AbstractSDCLibFixture.h"
#include "../UnitTest++/src/UnitTest++.h"


using namespace SDCLib;
using namespace SDCLib::Util;
using namespace SDCLib::Data::SDC;


// Some values to configure the test
const int LOOP_SLEEP = 250;
const int NUM_LOOPS_SLEEP = 10; // The number of loops to wait and let the provider run

namespace SDCLib {
namespace Tests {
namespace StreamSDC {

const std::string deviceEPR("UDI_STREAMINGTEST");


class StreamConsumerEventHandler : public SDCConsumerMDStateHandler<RealTimeSampleArrayMetricState>
{
public:
	StreamConsumerEventHandler(const std::string & handle)
    : SDCConsumerMDStateHandler(handle)
    { }

    void onStateChanged(const RealTimeSampleArrayMetricState & state) override
    {
        DebugOut(DebugOut::Default, "StreamSDC") << "Received chunk! Handle: " << descriptorHandle << std::endl;
        auto tl_values = state.getMetricValue().getSamples();
        m_verifiedChunks = true;

        for (size_t i = 0; i < tl_values.size(); ++i) {
            if (tl_values[i] != static_cast<double>(i))
                m_verifiedChunks = false;
        }
    }

    bool getVerifiedChunks() const { return m_verifiedChunks; }

private:
    std::atomic<bool> m_verifiedChunks = ATOMIC_VAR_INIT(false);
};


class StreamDistributionConsumerEventHandler : public SDCConsumerMDStateHandler<DistributionSampleArrayMetricState>
{
public:
	StreamDistributionConsumerEventHandler(const std::string & handle)
    :SDCConsumerMDStateHandler(handle)
    { }

    void onStateChanged(const DistributionSampleArrayMetricState & state) override
    {
        DebugOut(DebugOut::Default, "StreamSDC") << "Received chunk of a distribution! Handle: " << descriptorHandle << std::endl;
        auto tl_values = state.getMetricValue().getSamples();
        m_verifiedChunks = true;

        for (size_t i = 0; i < tl_values.size(); ++i) {
            if (tl_values[i] != static_cast<double>(i))
                m_verifiedChunks = false;
        }
    }

    bool getVerifiedChunks() const { return m_verifiedChunks; }

private:
    std::atomic<bool> m_verifiedChunks = ATOMIC_VAR_INIT(false);
};



class StreamProviderStateHandler : public SDCProviderMDStateHandler<RealTimeSampleArrayMetricState> {
public:

    StreamProviderStateHandler(std::string p_descriptorHandle)
	: SDCProviderMDStateHandler(p_descriptorHandle)
	{ }

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

    void updateStateValue(const SampleArrayValue & rtsav) {
        RealTimeSampleArrayMetricState realTimeSampleArrayState = createState();
        realTimeSampleArrayState
            .setMetricValue(rtsav);
        updateState(realTimeSampleArrayState);
    }

    // do nothing when a consumer ask to change the value -> return Fail
    InvocationState onStateChangeRequest(const RealTimeSampleArrayMetricState&, const OperationInvocationContext&) override {
    	return InvocationState::Fail;
    }
};

class DistributionProviderStateHandler : public SDCProviderMDStateHandler<DistributionSampleArrayMetricState> {
public:

	DistributionProviderStateHandler(std::string p_descriptorHandle)
	: SDCProviderMDStateHandler(p_descriptorHandle)
	{ }

    // Helper method
    DistributionSampleArrayMetricState createState() {
    	DistributionSampleArrayMetricState distributionSampleArrayState(descriptorHandle);
    	distributionSampleArrayState
        	.setActivationState(ComponentActivation::On);
        return distributionSampleArrayState;
    }


    DistributionSampleArrayMetricState getInitialState() override {
        return createState();
    }

    void updateStateValue(const SampleArrayValue & rtsav) {
    	DistributionSampleArrayMetricState distributionSampleArrayState = createState();
    	distributionSampleArrayState
            .setMetricValue(rtsav);
        updateState(distributionSampleArrayState);
    }

    // do nothing when a consumer ask to change the value -> return Fail
    InvocationState onStateChangeRequest(const DistributionSampleArrayMetricState&, const OperationInvocationContext&) override {
    	return InvocationState::Fail;
    }
};



class SDCStreamHoldingDeviceProvider : public Util::Task {
public:

    SDCStreamHoldingDeviceProvider(SDCInstance_shared_ptr p_SDCInstance) :
        sdcProvider(p_SDCInstance),
    	streamEventHandler("handle_plethysmogram_stream"),
    	streamEventHandlerAlt("handle_plethysmogram_stream_alt"),
    	distributionEventHandler("handle_distribution_stream")
	{

		sdcProvider.setEndpointReferenceByName(SDCLib::Tests::StreamSDC::deviceEPR);


		// Current weight stream metric (read-only)
		// Metric references the handler
		RealTimeSampleArrayMetricDescriptor currentMetric("handle_plethysmogram_stream",
				CodedValue(CodeIdentifier("MDCX_VOLTAGE")).addConceptDescription(LocalizedText("Concept Description on MDCX_VOLTAGE.").setLang("en")),
				MetricCategory::Msrmt,
				MetricAvailability::Cont,
				1,
				xml_schema::Duration(0,0,0,0,0,0,1));


	    // alternative current matrix
		// Metric references the handler
		RealTimeSampleArrayMetricDescriptor currentMetricAlt("handle_plethysmogram_stream_alt",
				CodedValue(CodeIdentifier("MDCS_VOLTAGE")).addConceptDescription(LocalizedText("Concept Description on MDCS_VOLTAGE.").setLang("en")),
				MetricCategory::Msrmt,
				MetricAvailability::Cont,
				1,
				xml_schema::Duration(0,0,0,0,0,0,1));


		// set up a distribution metric
		// Declares a sample array that represents linear value distributions in the form of arrays containing scaled sample values.
		// In contrast to real-time sample arrays, distribution sample arrays provide observed spatial values, not time points.
		// An example for a distribution sample array metric might be a fourier-transformed electroencephalogram to derive frequency distribution.
		DistributionSampleArrayMetricDescriptor distributionMetric("handle_FFT_stream",
				CodedValue(CodeIdentifier("MDCX_FFT_VOLTAGE_SQUARED")),
				MetricCategory::Msrmt,
				MetricAvailability::Cont,
				CodedValue(CodeIdentifier("MDCX_FREQUENCY")),
				Range().setUpper(3.1415).setLower(-3.1415),
				1);


        // alternative current matrix: non-mandatory information
        currentMetricAlt.addTechnicalRange(Range().setLower(0).setUpper(2));


        // Channel
        ChannelDescriptor holdingDeviceParameters("handle_channel");
        holdingDeviceParameters
			.addMetric(currentMetric)
            .addMetric(currentMetricAlt)
            .addMetric(distributionMetric)
			.setSafetyClassification(SafetyClassification::Inf);

        // VMD
        VmdDescriptor holdingDeviceModule("handle_vmd");
        holdingDeviceModule.addChannel(holdingDeviceParameters);

        // MDS
        MdsDescriptor holdingDeviceSystem("handle_mds");
        holdingDeviceSystem
			.setMetaData(
				MetaData()
					.addManufacturer(LocalizedText("SurgiTAIX AG"))
	        		.setModelNumber("1")
	        		.addModelName(LocalizedText("EndoTAIX"))
	        		.addSerialNumber("1234"))
            .setType(CodedValue(CodeIdentifier("MDC_DEV_ANALY_SAT_O2_MDS")))
			.addVmd(holdingDeviceModule);

        // create and add description
		MdDescription mdDescription;
		mdDescription.addMdsDescriptor(holdingDeviceSystem);

		sdcProvider.setMdDescription(mdDescription);

        // Add handler
        sdcProvider.addMdStateHandler(&streamEventHandler);
        sdcProvider.addMdStateHandler(&streamEventHandlerAlt);
        sdcProvider.addMdStateHandler(&distributionEventHandler);
    }

    void startup() {
    	sdcProvider.startup();
    }

    void shutdown() {
    	sdcProvider.shutdown();
    }

    void updateStateValue(const SampleArrayValue & rtsav) {
        streamEventHandler.updateStateValue(rtsav); // updates handles and the parent provider
        streamEventHandlerAlt.updateStateValue(rtsav);
        distributionEventHandler.updateStateValue(rtsav);
    }

private:

    SDCProvider sdcProvider;

    StreamProviderStateHandler streamEventHandler;
    StreamProviderStateHandler streamEventHandlerAlt;
    DistributionProviderStateHandler distributionEventHandler;


public:

    // Produce stream values
    // runImpl() gets called when starting the provider thread by the inherited function start()
    virtual void runImpl() override {
    	DebugOut(DebugOut::Default, "StreamSDC") << "\nPoducer thread started." << std::endl;
		const std::size_t size(1000);
		std::vector<double> samples;
		for (std::size_t i = 0; i < size; i++) {
			samples.push_back(i);
		}
		long index(0);
		while (!isInterrupted()) {
			{
                updateStateValue(
						SampleArrayValue(MetricQuality(MeasurementValidity::Vld))
						.setSamples(samples));

			}
			DebugOut(DebugOut::Default, "StreamSDC") << "Produced stream chunk of size " << size << ", index " << index << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(LOOP_SLEEP));
			index += size;
		}
    }
};

}
}
}

struct FixtureStreamSDC : Tests::AbstractSDCLibFixture {
	FixtureStreamSDC() : AbstractSDCLibFixture("FixtureStreamSDC", OSELib::LogLevel::Notice) {}
};

SUITE(SDC) {
TEST_FIXTURE(FixtureStreamSDC, StreamSDC)
{
	DebugOut::openLogFile("TestStream.log.txt", true);
	try
	{
        auto t_SDCInstance = createSDCInstance();

        // Provider
		Tests::StreamSDC::SDCStreamHoldingDeviceProvider t_provider(t_SDCInstance);
		DebugOut(DebugOut::Default, std::cout, m_details.testName) << "Provider init.." << std::endl;
		t_provider.startup();

        // Consumer
        OSELib::SDC::ServiceManager t_serviceManager(t_SDCInstance);
        DebugOut(DebugOut::Default, std::cout, m_details.testName) << "Consumer discovery..." << std::endl;
        auto t_consumer(t_serviceManager.discoverEndpointReference(SDCLib::SDCInstance::calcUUIDv5(SDCLib::Tests::StreamSDC::deviceEPR, true)));
        auto eventHandler = std::make_shared<Tests::StreamSDC::StreamConsumerEventHandler>("handle_plethysmogram_stream");
        auto eventHandlerAlt = std::make_shared<Tests::StreamSDC::StreamConsumerEventHandler>("handle_plethysmogram_stream_alt");
        auto eventHandlerDistribution = std::make_shared<Tests::StreamSDC::StreamDistributionConsumerEventHandler>("handle_distribution_stream");

        // Discovery test
        CHECK_EQUAL(true, t_consumer != nullptr);

        if (t_consumer != nullptr) {
            t_consumer->registerStateEventHandler(eventHandler.get());
            t_consumer->registerStateEventHandler(eventHandlerAlt.get());
            t_consumer->registerStateEventHandler(eventHandlerDistribution.get());

            t_provider.start(); // starts provider in a thread and calls the overwritten function runImpl()

			// Metric event reception test
            std::this_thread::sleep_for(std::chrono::milliseconds(LOOP_SLEEP*NUM_LOOPS_SLEEP));
            CHECK_EQUAL(true, eventHandler->getVerifiedChunks());
            CHECK_EQUAL(true, eventHandlerAlt->getVerifiedChunks());
            CHECK_EQUAL(true, eventHandlerDistribution->getVerifiedChunks());


            t_consumer->unregisterStateEventHandler(eventHandler.get());
            t_consumer->unregisterStateEventHandler(eventHandlerAlt.get());
            t_consumer->unregisterStateEventHandler(eventHandlerDistribution.get());
            t_consumer->disconnect();
            t_provider.interrupt();
        }
        t_provider.shutdown();
	}
	catch (char const* exc)
	{
		DebugOut(DebugOut::Default, std::cerr, m_details.testName) << exc;
	}
	catch (...)
	{
		DebugOut(DebugOut::Default, std::cerr, m_details.testName) << "Unknown exception occurred!";
	}
	DebugOut::closeLogFile();
}
}
