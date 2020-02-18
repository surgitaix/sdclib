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
const int LOOP_SLEEP{250};
const int NUM_LOOPS_SLEEP{10}; // The number of loops to wait and let the provider run

namespace SDCLib {
namespace Tests {
namespace StreamSDC {

const std::string deviceEPR{"UDI_STREAMINGTEST"};


class StreamConsumerEventHandler : public SDCConsumerMDStateHandler<RealTimeSampleArrayMetricState>
{
public:
	StreamConsumerEventHandler(const std::string p_descriptorHandle)
    : SDCConsumerMDStateHandler(p_descriptorHandle)
    { }

    void onStateChanged(const RealTimeSampleArrayMetricState& changedState) override
    {
        DebugOut(DebugOut::Default, "StreamSDC") << "Received chunk! Handle: " << getDescriptorHandle() << std::endl;
        auto t_sampleValues = changedState.getMetricValue().getSamples();
        m_chunksVerified = true;

        for (std::size_t i = 0; i < t_sampleValues.size(); ++i)
        {
            if (t_sampleValues[i] != static_cast<double>(i))
            {
            	m_chunksVerified = false;
            }
        }
    }

    bool chunksVerified() const
    {
    	return m_chunksVerified;
    }

private:
    std::atomic<bool> m_chunksVerified{false};
};


class StreamDistributionConsumerEventHandler : public SDCConsumerMDStateHandler<DistributionSampleArrayMetricState>
{
public:
	StreamDistributionConsumerEventHandler(const std::string p_descriptorHandle)
    :SDCConsumerMDStateHandler(p_descriptorHandle)
    { }

    void onStateChanged(const DistributionSampleArrayMetricState& changedState) override
    {
        DebugOut(DebugOut::Default, "StreamSDC") << "Received chunk of a distribution! Handle: " << getDescriptorHandle() << std::endl;
        auto t_sampleValues = changedState.getMetricValue().getSamples();
        m_chunksVerified = true;

        for (std::size_t i = 0; i < t_sampleValues.size(); ++i)
        {
            if (t_sampleValues[i] != static_cast<double>(i))
            {
            	m_chunksVerified = false;
            }
        }
    }

    bool chunksVerified() const
    {
    	return m_chunksVerified;
    }

private:
    std::atomic<bool> m_chunksVerified{false};
};



class StreamProviderStateHandler : public SDCProviderMDStateHandler<RealTimeSampleArrayMetricState>
{
public:

    StreamProviderStateHandler(const std::string p_descriptorHandle)
	: SDCProviderMDStateHandler(p_descriptorHandle)
	{ }

    // Helper method
    RealTimeSampleArrayMetricState createState()
    {
        RealTimeSampleArrayMetricState t_newState{getDescriptorHandle()};
        t_newState.setActivationState(ComponentActivation::On);

        return t_newState;
    }


    RealTimeSampleArrayMetricState getInitialState() override
    {
        return createState();
    }

    void updateStateValue(const SampleArrayValue& p_newValue)
    {
        auto t_newState{createState()};
        t_newState.setMetricValue(p_newValue);

        updateState(t_newState);
    }

    // do nothing when a consumer ask to change the value -> return Fail
    InvocationState onStateChangeRequest(const RealTimeSampleArrayMetricState&, const OperationInvocationContext&) override
    {
    	return InvocationState::Fail;
    }
};

class DistributionProviderStateHandler : public SDCProviderMDStateHandler<DistributionSampleArrayMetricState>
{
public:

	DistributionProviderStateHandler(const std::string p_descriptorHandle)
	: SDCProviderMDStateHandler(p_descriptorHandle)
	{ }

    // Helper method
    DistributionSampleArrayMetricState createState()
    {
    	DistributionSampleArrayMetricState t_newState{getDescriptorHandle()};
    	t_newState.setActivationState(ComponentActivation::On);

        return t_newState;
    }


    DistributionSampleArrayMetricState getInitialState() override
    {
        return createState();
    }

    void updateStateValue(const SampleArrayValue& p_newValue)
    {
    	auto t_newState{createState()};
    	t_newState.setMetricValue(p_newValue);

        updateState(t_newState);
    }

    // do nothing when a consumer ask to change the value -> return Fail
    InvocationState onStateChangeRequest(const DistributionSampleArrayMetricState&, const OperationInvocationContext&) override
    {
    	return InvocationState::Fail;
    }
};



class SDCStreamHoldingDeviceProvider : public Util::Task
{
public:

    SDCStreamHoldingDeviceProvider(SDCInstance_shared_ptr p_SDCInstance)
	: m_sdcProvider(p_SDCInstance)
	{
    	m_sdcProvider.setEndpointReferenceByName(SDCLib::Tests::StreamSDC::deviceEPR);

		// Current weight stream metric (read-only)
		// Metric references the handler
		RealTimeSampleArrayMetricDescriptor currentMetric{"handle_plethysmogram_stream",
				CodedValue{CodeIdentifier{"MDCX_VOLTAGE"}}.addConceptDescription(LocalizedText{"Concept Description on MDCX_VOLTAGE."}.setLang("en")),
				MetricCategory::Msrmt,
				MetricAvailability::Cont,
				1,
				xml_schema::Duration{0,0,0,0,0,0,1}};


	    // alternative current matrix
		// Metric references the handler
		RealTimeSampleArrayMetricDescriptor currentMetricAlt{"handle_plethysmogram_stream_alt",
				CodedValue(CodeIdentifier{"MDCS_VOLTAGE"}).addConceptDescription(LocalizedText{"Concept Description on MDCS_VOLTAGE."}.setLang("en")),
				MetricCategory::Msrmt,
				MetricAvailability::Cont,
				1,
				xml_schema::Duration{0,0,0,0,0,0,1}};


		// set up a distribution metric
		// Declares a sample array that represents linear value distributions in the form of arrays containing scaled sample values.
		// In contrast to real-time sample arrays, distribution sample arrays provide observed spatial values, not time points.
		// An example for a distribution sample array metric might be a fourier-transformed electroencephalogram to derive frequency distribution.
		DistributionSampleArrayMetricDescriptor distributionMetric{"handle_FFT_stream",
				CodedValue(CodeIdentifier{"MDCX_FFT_VOLTAGE_SQUARED"}),
				MetricCategory::Msrmt,
				MetricAvailability::Cont,
				CodedValue{CodeIdentifier{"MDCX_FREQUENCY"}},
				Range{}.setUpper(3.1415).setLower(-3.1415),
				1};


        // alternative current matrix: non-mandatory information
        currentMetricAlt.addTechnicalRange(Range{}.setLower(0).setUpper(2));


        // Channel
        ChannelDescriptor holdingDeviceParameters{"handle_channel"};
        holdingDeviceParameters
			.addMetric(currentMetric)
            .addMetric(currentMetricAlt)
            .addMetric(distributionMetric)
			.setSafetyClassification(SafetyClassification::Inf);

        // VMD
        VmdDescriptor holdingDeviceModule{"handle_vmd"};
        holdingDeviceModule.addChannel(holdingDeviceParameters);

        // MDS
        MdsDescriptor holdingDeviceSystem{"handle_mds"};
        holdingDeviceSystem
			.setMetaData(
				MetaData()
					.addManufacturer(LocalizedText{"SurgiTAIX AG"})
	        		.setModelNumber("1")
	        		.addModelName(LocalizedText{"EndoTAIX"})
	        		.addSerialNumber("1234"))
            .setType(CodedValue{CodeIdentifier{"MDC_DEV_ANALY_SAT_O2_MDS"}})
			.addVmd(holdingDeviceModule);

        // create and add description
		MdDescription mdDescription;
		mdDescription.addMdsDescriptor(holdingDeviceSystem);

		m_sdcProvider.setMdDescription(mdDescription);

        // Add handler
		m_sdcProvider.addMdStateHandler(&m_streamEventHandler);
		m_sdcProvider.addMdStateHandler(&m_streamEventHandlerAlt);
		m_sdcProvider.addMdStateHandler(&m_distributionEventHandler);
    }

    void startup()
    {
    	m_sdcProvider.startup();
    }

    void updateStateValue(const SampleArrayValue& p_newValue)
    {
    	m_streamEventHandler.updateStateValue(p_newValue); // updates handles and the parent provider
    	m_streamEventHandlerAlt.updateStateValue(p_newValue);
    	m_distributionEventHandler.updateStateValue(p_newValue);
    }

private:

    SDCProvider m_sdcProvider;

    StreamProviderStateHandler m_streamEventHandler{"handle_plethysmogram_stream"};
    StreamProviderStateHandler m_streamEventHandlerAlt{"handle_plethysmogram_stream_alt"};
    DistributionProviderStateHandler m_distributionEventHandler{"handle_distribution_stream"};


public:

    // Produce stream values
    // runImpl() gets called when starting the provider thread by the inherited function start()
    void runImpl() override
    {
    	DebugOut(DebugOut::Default, "StreamSDC") << "\nPoducer thread started." << std::endl;

		const auto t_chunkSizePerSample{1000};
		std::vector<double> samples;
		for (auto i = 0; i < t_chunkSizePerSample; ++i)
		{
			samples.push_back(i);
		}
		auto t_sampleIndex{0};
		while (!isInterrupted())
		{
			{
                updateStateValue(SampleArrayValue{MetricQuality{MeasurementValidity::Vld}}.setSamples(samples));
			}
			DebugOut(DebugOut::Default, "StreamSDC") << "Produced stream chunk of size " << t_chunkSizePerSample << ", index " << t_sampleIndex << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(LOOP_SLEEP));
			t_sampleIndex += t_chunkSizePerSample;
		}
    }
};

}
}
}

struct FixtureStreamSDC : Tests::AbstractSDCLibFixture
{
	FixtureStreamSDC()
	: AbstractSDCLibFixture("FixtureStreamSDC", OSELib::LogLevel::Notice)
	{ }
};

SUITE(SDC)
{
TEST_FIXTURE(FixtureStreamSDC, StreamSDC)
{
	DebugOut::openLogFile("TestStream.log.txt", true);
	try
	{
        auto t_SDCInstance{createSDCInstance()};

        // Provider
		Tests::StreamSDC::SDCStreamHoldingDeviceProvider t_provider{t_SDCInstance};
		DebugOut(DebugOut::Default, std::cout, m_details.testName) << "Provider init.." << std::endl;
		t_provider.startup();

        // Consumer
        OSELib::SDC::ServiceManager t_serviceManager{t_SDCInstance};
        DebugOut(DebugOut::Default, std::cout, m_details.testName) << "Consumer discovery..." << std::endl;

        auto t_consumer{t_serviceManager.discoverEndpointReference(SDCLib::SDCInstance::calcUUIDv5(SDCLib::Tests::StreamSDC::deviceEPR, true))};

        auto eventHandler = std::make_shared<Tests::StreamSDC::StreamConsumerEventHandler>("handle_plethysmogram_stream");
        auto eventHandlerAlt = std::make_shared<Tests::StreamSDC::StreamConsumerEventHandler>("handle_plethysmogram_stream_alt");
        auto eventHandlerDistribution = std::make_shared<Tests::StreamSDC::StreamDistributionConsumerEventHandler>("handle_distribution_stream");

        // Discovery test
        CHECK_EQUAL(true, t_consumer != nullptr);

        if (t_consumer != nullptr)
        {
            t_consumer->registerStateEventHandler(eventHandler.get());
            t_consumer->registerStateEventHandler(eventHandlerAlt.get());
            t_consumer->registerStateEventHandler(eventHandlerDistribution.get());

            t_provider.start(); // starts provider in a thread and calls the overwritten function runImpl()

			// Metric event reception test
            std::this_thread::sleep_for(std::chrono::milliseconds(LOOP_SLEEP*NUM_LOOPS_SLEEP));
            CHECK_EQUAL(true, eventHandler->chunksVerified());
            CHECK_EQUAL(true, eventHandlerAlt->chunksVerified());
            CHECK_EQUAL(true, eventHandlerDistribution->chunksVerified());

            t_consumer->unregisterStateEventHandler(eventHandler.get());
            t_consumer->unregisterStateEventHandler(eventHandlerAlt.get());
            t_consumer->unregisterStateEventHandler(eventHandlerDistribution.get());

            t_consumer->disconnect();

            t_provider.interrupt();// TODO: Better solution?
        }
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
