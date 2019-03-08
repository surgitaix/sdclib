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
#include "OSCLib/SDCInstance.h"
#include "OSCLib/Data/SDC/SDCConsumer.h"
#include "OSCLib/Data/SDC/SDCConsumerMDStateHandler.h"
#include "OSCLib/Data/SDC/SDCProvider.h"
#include "OSCLib/Data/SDC/SDCProviderMDStateHandler.h"

#include "OSCLib/Data/SDC/MDIB/ChannelDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/CodedValue.h"

#include "OSCLib/Data/SDC/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/SDC/MDIB/MdsDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/LocalizedText.h"
#include "OSCLib/Data/SDC/MDIB/MdDescription.h"
#include "OSCLib/Data/SDC/MDIB/Measurement.h"
#include "OSCLib/Data/SDC/MDIB/MetricQuality.h"
#include "OSCLib/Data/SDC/MDIB/Range.h"
#include "OSCLib/Data/SDC/MDIB/RealTimeSampleArrayMetricDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/RealTimeSampleArrayMetricState.h"
#include "OSCLib/Data/SDC/MDIB/DistributionSampleArrayMetricDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/DistributionSampleArrayMetricState.h"
#include "OSCLib/Data/SDC/MDIB/SampleArrayValue.h"

#include "OSCLib/Data/SDC/MDIB/MetaData.h"
#include "OSCLib/Data/SDC/MDIB/VmdDescriptor.h"
#include "OSCLib/Util/DebugOut.h"
#include "OSCLib/Util/Task.h"
#include "../AbstractOSCLibFixture.h"
#include "../UnitTest++/src/UnitTest++.h"

#include "OSELib/SDC/ServiceManager.h"

#include "Poco/Runnable.h"
#include "Poco/Mutex.h"
#include "Poco/ScopedLock.h"
#include "Poco/Thread.h"

using namespace SDCLib;
using namespace SDCLib::Util;
using namespace SDCLib::Data::SDC;

namespace SDCLib {
namespace Tests {
namespace StreamSDC {

const std::string deviceEPR("UDI_STREAMINGTEST");


class StreamConsumerEventHandler : public SDCConsumerMDStateHandler<RealTimeSampleArrayMetricState> {
public:
	StreamConsumerEventHandler(const std::string & handle) :
		SDCConsumerMDStateHandler(handle),
    	verifiedChunks(false)
    {
    }

    void onStateChanged(const RealTimeSampleArrayMetricState & state) override {
    	Poco::Mutex::ScopedLock lock(mutex);
        DebugOut(DebugOut::Default, "StreamSDC") << "Received chunk! Handle: " << descriptorHandle << std::endl;
        std::vector<double> values = state.getMetricValue().getSamples();
        verifiedChunks = true;

        for (size_t i = 0; i < values.size(); i++) {
            if (values[i] != double(i))
                verifiedChunks = false;
        }
    }

    bool getVerifiedChunks() {
    	Poco::Mutex::ScopedLock lock(mutex);
        return verifiedChunks;
    }

private:
    Poco::Mutex mutex;
    bool verifiedChunks;
};


class StreamDistributionConsumerEventHandler : public SDCConsumerMDStateHandler<DistributionSampleArrayMetricState> {
public:
	StreamDistributionConsumerEventHandler(const std::string & handle) :
		SDCConsumerMDStateHandler(handle),
    	verifiedChunks(false)
    {
    }

    void onStateChanged(const DistributionSampleArrayMetricState & state) override {
    	Poco::Mutex::ScopedLock lock(mutex);
        DebugOut(DebugOut::Default, "StreamSDC") << "Received chunk of a distribution! Handle: " << descriptorHandle << std::endl;
        std::vector<double> values = state.getMetricValue().getSamples();
        verifiedChunks = true;

        for (size_t i = 0; i < values.size(); i++) {
            if (values[i] != double(i))
                verifiedChunks = false;
        }
    }

    bool getVerifiedChunks() {
    	Poco::Mutex::ScopedLock lock(mutex);
        return verifiedChunks;
    }

private:
    Poco::Mutex mutex;
    bool verifiedChunks;
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

	DistributionProviderStateHandler(std::string descriptorHandle) : SDCProviderMDStateHandler(descriptorHandle) {
    }

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





class OSCPStreamHoldingDeviceProvider : public Util::Task {
public:

    OSCPStreamHoldingDeviceProvider(SDCInstance_shared_ptr p_SDCInstance) :
    	sdcProvider(p_SDCInstance),
    	streamEventHandler("handle_plethysmogram_stream"),
    	streamEventHandlerAlt("handle_plethysmogram_stream_alt"),
    	distributionEventHandler("handle_distribution_stream")
	{

		sdcProvider.setEndpointReference(SDCLib::Tests::StreamSDC::deviceEPR);


		// Currentweight stream metric (read-only)
		// Metric references the handler
		RealTimeSampleArrayMetricDescriptor currentMetric("handle_plethysmogram_stream",
				CodedValue(CodeIdentifier("MDCX_VOLTAGE")).addConceptDescription(LocalizedText().setRef("uri/to/file.txt").setLang("en")),
				MetricCategory::Msrmt,
				MetricAvailability::Cont,
				1,
				xml_schema::Duration(0,0,0,0,0,0,1));


	    // alternative current matrix
		// Metric references the handler
		RealTimeSampleArrayMetricDescriptor currentMetricAlt("handle_plethysmogram_stream_alt",
				CodedValue(CodeIdentifier("MDCS_VOLTAGE")).addConceptDescription(LocalizedText().setRef("uri/to/file.txt").setLang("en")),
				MetricCategory::Msrmt,
				MetricAvailability::Cont,
				1,
				xml_schema::Duration(0,0,0,0,0,0,1));


		// set up a distibution metric
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
					.addManufacturer(LocalizedText().setRef("SurgiTAIX AG"))
	        		.setModelNumber("1")
	        		.addModelName(LocalizedText().setRef("EndoTAIX"))
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
        samples.reserve(size);
		for (std::size_t i = 0; i < samples.size(); i++) {
			samples[i] = static_cast<double>(i);
		}
		long index(0);
		while (!isInterrupted()) {
			{
                updateStateValue(
						SampleArrayValue(MetricQuality(MeasurementValidity::Vld))
						.setSamples(samples));

			}
			DebugOut(DebugOut::Default, "StreamSDC") << "Produced stream chunk of size " << size << ", index " << index << std::endl;
			Poco::Thread::sleep(1000);
			index += size;
		}
    }
};

}
}
}

struct FixtureStreamSDC : Tests::AbstractOSCLibFixture {
	FixtureStreamSDC() : AbstractOSCLibFixture("FixtureStreamSDC", OSELib::LogLevel::Notice, SDCLib::Config::SDC_ALLOWED_PORT_START + 120) {}
};

SUITE(OSCP) {
TEST_FIXTURE(FixtureStreamSDC, streamsdc)
{
	DebugOut::openLogFile("TestStream.log.txt", true);
	try
	{
        auto t_SDCInstance = getSDCInstance();
        // Provider
		Tests::StreamSDC::OSCPStreamHoldingDeviceProvider provider(t_SDCInstance);
		DebugOut(DebugOut::Default, m_details.testName) << "Provider init.." << std::endl;
		provider.startup();

        // Consumer
        OSELib::SDC::ServiceManager oscpsm(t_SDCInstance);
        DebugOut(DebugOut::Default, m_details.testName) << "Consumer discovery..." << std::endl;
        std::shared_ptr<SDCConsumer> c(oscpsm.discoverEndpointReference(SDCLib::Tests::StreamSDC::deviceEPR));
        std::shared_ptr<Tests::StreamSDC::StreamConsumerEventHandler> eventHandler = std::make_shared<Tests::StreamSDC::StreamConsumerEventHandler>("handle_plethysmogram_stream");
        std::shared_ptr<Tests::StreamSDC::StreamConsumerEventHandler> eventHandlerAlt = std::make_shared<Tests::StreamSDC::StreamConsumerEventHandler>("handle_plethysmogram_stream_alt");
        std::shared_ptr<Tests::StreamSDC::StreamDistributionConsumerEventHandler> eventHandlerDistribution= std::make_shared<Tests::StreamSDC::StreamDistributionConsumerEventHandler>("handle_distribution_stream");

        // Discovery test
        CHECK_EQUAL(true, c != nullptr);

        if (c != nullptr) {
            c->registerStateEventHandler(eventHandler.get());
            c->registerStateEventHandler(eventHandlerAlt.get());
            c->registerStateEventHandler(eventHandlerDistribution.get());

            provider.start();// starts provider in a thread and calls the overwritten function runImpl()

			// Metric event reception test
			DebugOut(DebugOut::Default, m_details.testName) << "Waiting..." << std::endl;
            Poco::Thread::sleep(4000);
            CHECK_EQUAL(true, eventHandler->getVerifiedChunks());
            CHECK_EQUAL(true, eventHandlerAlt->getVerifiedChunks());
            CHECK_EQUAL(true, eventHandlerDistribution->getVerifiedChunks());

            provider.interrupt();
            c->unregisterStateEventHandler(eventHandler.get());
            c->unregisterStateEventHandler(eventHandlerAlt.get());
            c->unregisterStateEventHandler(eventHandlerDistribution.get());
            c->disconnect();
        }
        provider.shutdown();
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
