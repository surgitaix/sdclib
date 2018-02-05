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
 * TestStreamOSCP.cpp
 *
 *  @Copyright (C) 2018, SurgiTAIX AG
 *  Author: buerger
 *
 *  This unit test checks the eventing mechanism for the udp based stream metrices: RealTimeSampleArrayMetric (time values) and DistributionSampleArrayMetric (other values)
 *
 */
#include "OSCLib/OSCLibrary.h"
#include "OSCLib/Data/OSCP/OSCPConsumer.h"
#include "OSCLib/Data/OSCP/SDCConsumerEventHandler.h"
#include "OSCLib/Data/OSCP/OSCPProvider.h"
#include "OSCLib/Data/OSCP/SDCProviderMDStateHandler.h"

#include "OSCLib/Data/OSCP/MDIB/ChannelDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/MDIB/MdsDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/LocalizedText.h"
#include "OSCLib/Data/OSCP/MDIB/MdDescription.h"
#include "OSCLib/Data/OSCP/MDIB/Measurement.h"
#include "OSCLib/Data/OSCP/MDIB/MetricQuality.h"
#include "OSCLib/Data/OSCP/MDIB/Range.h"
#include "OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/DistributionSampleArrayMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/DistributionSampleArrayMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/SampleArrayValue.h"

#include "OSCLib/Data/OSCP/MDIB/MetaData.h"
#include "OSCLib/Data/OSCP/MDIB/VmdDescriptor.h"
#include "OSCLib/Util/DebugOut.h"
#include "OSCLib/Util/Task.h"
#include "../AbstractOSCLibFixture.h"
#include "../UnitTest++/src/UnitTest++.h"

#include "OSELib/OSCP/ServiceManager.h"

#include "Poco/Runnable.h"
#include "Poco/Mutex.h"
#include "Poco/ScopedLock.h"
#include "Poco/Thread.h"

using namespace OSCLib;
using namespace OSCLib::Util;
using namespace OSCLib::Data::OSCP;

namespace OSCLib {
namespace Tests {
namespace StreamOSCP {

const std::string deviceEPR("UDI_STREAMINGTEST");


class StreamConsumerEventHandler : public SDCConsumerEventHandler<RealTimeSampleArrayMetricState> {
public:
	StreamConsumerEventHandler(const std::string & handle) :
		SDCConsumerEventHandler(handle),
    	verifiedChunks(false)
    {
    }

    void onStateChanged(const RealTimeSampleArrayMetricState & state) override {
    	Poco::Mutex::ScopedLock lock(mutex);
        DebugOut(DebugOut::Default, "StreamOSCP") << "Received chunk! Handle: " << descriptorHandle << std::endl;
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


class StreamDistributionConsumerEventHandler : public SDCConsumerEventHandler<DistributionSampleArrayMetricState> {
public:
	StreamDistributionConsumerEventHandler(const std::string & handle) :
		SDCConsumerEventHandler(handle),
    	verifiedChunks(false)
    {
    }

    void onStateChanged(const DistributionSampleArrayMetricState & state) override {
    	Poco::Mutex::ScopedLock lock(mutex);
        DebugOut(DebugOut::Default, "StreamOSCP") << "Received chunk of a distribution! Handle: " << descriptorHandle << std::endl;
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
    InvocationState onStateChangeRequest(const RealTimeSampleArrayMetricState & state, const OperationInvocationContext & oic) override {
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
    InvocationState onStateChangeRequest(const DistributionSampleArrayMetricState & state, const OperationInvocationContext & oic) override {
    	return InvocationState::Fail;
    }
};





class OSCPStreamHoldingDeviceProvider : public Util::Task {
public:

    OSCPStreamHoldingDeviceProvider() :
    	oscpProvider(),
    	streamEventHandler("handle_plethysmogram_stream"),
    	streamEventHandlerAlt("handle_plethysmogram_stream_alt"),
    	distributionEventHandler("handle_distribution_stream")
	{

		oscpProvider.setEndpointReference(OSCLib::Tests::StreamOSCP::deviceEPR);


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

		oscpProvider.setMdDescription(mdDescription);

        // Add handler
        oscpProvider.addMdSateHandler(&streamEventHandler);
        oscpProvider.addMdSateHandler(&streamEventHandlerAlt);
        oscpProvider.addMdSateHandler(&distributionEventHandler);
    }

    void startup() {
    	oscpProvider.startup();
    }

    void shutdown() {
    	oscpProvider.shutdown();
    }

    void updateStateValue(const SampleArrayValue & rtsav) {
        streamEventHandler.updateStateValue(rtsav); // updates handles and the parent provider
        streamEventHandlerAlt.updateStateValue(rtsav);
        distributionEventHandler.updateStateValue(rtsav);
    }

private:

    OSCPProvider oscpProvider;

    StreamProviderStateHandler streamEventHandler;
    StreamProviderStateHandler streamEventHandlerAlt;
    DistributionProviderStateHandler distributionEventHandler;


public:
    
    // Produce stream values
    // runImpl() gets called when starting the provider thread by the inherited function start()
    virtual void runImpl() override {
    	DebugOut(DebugOut::Default, "StreamOSCP") << "\nPoducer thread started." << std::endl;
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
			DebugOut(DebugOut::Default, "StreamOSCP") << "Produced stream chunk of size " << size << ", index " << index << std::endl;
			Poco::Thread::sleep(1000);
			index += size;
		}
    }
};

}
}
}

struct FixtureStreamOSCP : Tests::AbstractOSCLibFixture {
	FixtureStreamOSCP() : AbstractOSCLibFixture("FixtureStreamOSCP", OSELib::LogLevel::NOTICE, 10000) {}
};

SUITE(OSCP) {
TEST_FIXTURE(FixtureStreamOSCP, streamoscp)
{
	DebugOut::openLogFile("TestStream.log.txt", true);
	try
	{
        // Provider
		Tests::StreamOSCP::OSCPStreamHoldingDeviceProvider provider;
		DebugOut(DebugOut::Default, "StreamOSCP") << "Provider init.." << std::endl;
		provider.startup();

        // Consumer
        OSELib::OSCP::ServiceManager oscpsm;
        DebugOut(DebugOut::Default, "StreamOSCP") << "Consumer discovery..." << std::endl;
        std::shared_ptr<OSCPConsumer> c(oscpsm.discoverEndpointReference(OSCLib::Tests::StreamOSCP::deviceEPR));
        std::shared_ptr<Tests::StreamOSCP::StreamConsumerEventHandler> eventHandler = std::make_shared<Tests::StreamOSCP::StreamConsumerEventHandler>("handle_plethysmogram_stream");
        std::shared_ptr<Tests::StreamOSCP::StreamConsumerEventHandler> eventHandlerAlt = std::make_shared<Tests::StreamOSCP::StreamConsumerEventHandler>("handle_plethysmogram_stream_alt");
        std::shared_ptr<Tests::StreamOSCP::StreamDistributionConsumerEventHandler> eventHandlerDistribution= std::make_shared<Tests::StreamOSCP::StreamDistributionConsumerEventHandler>("handle_distribution_stream");

        // Discovery test
        CHECK_EQUAL(true, c != nullptr);

        if (c != nullptr) {
            c->registerStateEventHandler(eventHandler.get());
            c->registerStateEventHandler(eventHandlerAlt.get());
            c->registerStateEventHandler(eventHandlerDistribution.get());

            provider.start();// starts provider in a thread and calls the overwritten function runImpl()

			// Metric event reception test
            Poco::Thread::sleep(10000);
            CHECK_EQUAL(true, eventHandler->getVerifiedChunks());
            CHECK_EQUAL(true, eventHandlerAlt->getVerifiedChunks());
            CHECK_EQUAL(true, eventHandlerDistribution->getVerifiedChunks());
            
            provider.interrupt();
            c->unregisterStateEventHandler(eventHandler.get());
            c->unregisterStateEventHandler(eventHandlerAlt.get());
            c->unregisterStateEventHandler(eventHandlerDistribution.get());
            c->disconnect();
        }

        Poco::Thread::sleep(2000);
        provider.shutdown();
	}
	catch (char const* exc)
	{
		DebugOut(DebugOut::Default, std::cerr, "streamoscp") << exc;
	}    
	catch (...)
	{
		DebugOut(DebugOut::Default, std::cerr, "streamoscp") << "Unknown exception occurred!";
	}
	DebugOut::closeLogFile();
}
}
