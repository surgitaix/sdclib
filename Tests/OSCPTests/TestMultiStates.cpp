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
 * TestMultiStates.cpp
 *
 *  @Copyright (C) 2018, SurgiTAIX AG
 *  Author: buerger
 *
 *	! Multistates are not implemented right now ! a state handler is mapped uniquely defined by its descriptor handle! (map as data type)
 *
 *  This unit test checks if the multi state implementation is working.
 *  Context states are implemented as multi states. They are utilized here for testing the libraries multi state logic.
 *  3 Tests:
 *  1. Context is handled like a metric (single state: only descriptor handle is referenced) (true)
 *  2. Descriptor handle is ambitious. Context state is referenced by handle attribute. (true)
 *  3. Descriptor handle is ambitious. Context state is referenced by the wrong handle attribute. (fail)
 *
 *
 */
#include "OSCLib/SDCLibrary.h"

#include "OSCLib/Data/OSCP/SDCConsumer.h"
#include "OSCLib/Data/OSCP/SDCConsumerMDStateHandler.h"
#include "OSCLib/Data/OSCP/SDCProvider.h"
#include "OSCLib/Data/OSCP/SDCProviderMDStateHandler.h"

// MDS and it's components
#include "OSCLib/Data/OSCP/MDIB/MdDescription.h"
#include "OSCLib/Data/OSCP/MDIB/MdsDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ChannelDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/VmdDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/MetaData.h"

// Mdib data types
#include "OSCLib/Data/OSCP/MDIB/SystemContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/LocationContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/LocationContextState.h"
#include "OSCLib/Data/OSCP/MDIB/LocationDetail.h"

#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/LocalizedText.h"
#include "OSCLib/Data/OSCP/MDIB/Measurement.h"
#include "OSCLib/Data/OSCP/MDIB/MetricQuality.h"
#include "OSCLib/Data/OSCP/MDIB/Range.h"

#include "OSCLib/Util/DebugOut.h"

// Testing framework
#include "../AbstractOSCLibFixture.h"
#include "../UnitTest++/src/UnitTest++.h"

#include "OSELib/OSCP/ServiceManager.h"

#include "Poco/Runnable.h"
#include "Poco/Mutex.h"
#include "Poco/ScopedLock.h"
#include "Poco/Thread.h"

using namespace OSCLib;
using namespace OSCLib::Util;
using namespace OSCLib::Data::SDC;

namespace OSCLib {
namespace Tests {
namespace multiStatesSDC {

const std::string deviceEPR("UDI_MULTISTATESTEST");



// a provider side multi state handler is defined just the same way as a single state handler.
// But pay attention: the optional handle attribute must be set!
class MultistateProviderStateHandler : public SDCProviderMDStateHandler<LocationContextState> {
public:

	MultistateProviderStateHandler(std::string descriptorHandle, std::string handle) : SDCProviderMDStateHandler(descriptorHandle), handle(handle) {
    }

    // Helper method
	LocationContextState createMultiState() {
    	LocationContextState locationContextState(descriptorHandle, handle);
    	locationContextState
        	.setLocationDetail(LocationDetail()
        			.setFloor("Floor1")
        			.setRoom("Room1"));
        return locationContextState;
    }

	// the initial state has to be defined.
	// It is called from within the framework
	LocationContextState getInitialState() override {
        return createMultiState();
    }

	// convenience function for changing the room value
    void updateMultiStateValue(std::string room) {
    	LocationContextState locationContextState = createMultiState();
    	locationContextState
        	.setLocationDetail(LocationDetail().setRoom(room));
        updateState(locationContextState);
    }

    // read-only state
    // do nothing when a consumer ask to change the value -> return Fail
    InvocationState onStateChangeRequest(const LocationContextState & state, const OperationInvocationContext & oic) override {
    	return InvocationState::Fail;
    }

public:
    std::string handle;
};



class SDCMultiStateTestProviders {
public:

    SDCMultiStateTestProviders() :
    	oscpProvider(),
    	multistateProviderStateHandler1_1("locationStateLikeSingleState_handle", "does_not_matter"),
    	// this medical device has two states: one that contains information about the current room and one that contains information about the next room (at the same Floor)
    	multistateProviderStateHandler2_1("locationContextAbitious_handle", "actualRoom_handle"),
    	multistateProviderStateHandler2_2("locationContextAbitious_handle", "nextRoom_handle")
	{

		oscpProvider.setEndpointReference(OSCLib::Tests::multiStatesSDC::deviceEPR);


		LocationContextDescriptor locationContextDescriptor1("locationStateLikeSingleState_handle");
		LocationContextDescriptor locationContextDescriptor2("locationContextAbitious_handle");



        // Channel
        ChannelDescriptor holdingDeviceParameters("handle_channel");

        // VMD
        VmdDescriptor holdingDeviceModule("handle_vmd");
        holdingDeviceModule.addChannel(holdingDeviceParameters);

        // MDS
        MdsDescriptor holdingDeviceSystem("handle_mds");
        holdingDeviceSystem
			.setSystemContext(
					SystemContextDescriptor("MDC_SYS_CON")
					.setLocationContext(locationContextDescriptor1)
					.setLocationContext(locationContextDescriptor2))
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
        oscpProvider.addMdSateHandler(&multistateProviderStateHandler1_1);
        oscpProvider.addMdSateHandler(&multistateProviderStateHandler2_1);
        oscpProvider.addMdSateHandler(&multistateProviderStateHandler2_2);
    }

    void startup() {
    	oscpProvider.startup();
    }

    void shutdown() {
    	oscpProvider.shutdown();
    }

    void updateStateValue(std::string room) {
    	multistateProviderStateHandler1_1.updateMultiStateValue(room);
    	multistateProviderStateHandler2_1.updateMultiStateValue(room);
    	multistateProviderStateHandler2_2.updateMultiStateValue(std::string(room + "1"));
    }

private:

    SDCProvider oscpProvider;

    // Test case 1
    MultistateProviderStateHandler multistateProviderStateHandler1_1;
    // Test case 2 & 3 (three only needs a consumer state handle referencing some non existing room)
    MultistateProviderStateHandler multistateProviderStateHandler2_1;
    MultistateProviderStateHandler multistateProviderStateHandler2_2;


};


}
}
}

struct FixtureMultiStatesTest: Tests::AbstractOSCLibFixture {
	FixtureMultiStatesTest() : AbstractOSCLibFixture("FixtureMultiStateTest", OSELib::LogLevel::NOTICE, 10000) {}
};

SUITE(OSCP) {
TEST_FIXTURE(FixtureMultiStatesTest, multistates)
{
	DebugOut::openLogFile("TestMultiState.log", true);
	try
	{
        // Provider
		Tests::multiStatesSDC::SDCMultiStateTestProviders provider;
		DebugOut(DebugOut::Default, "MultiStateSDC") << "Provider init.." << std::endl;
		provider.startup();

        // Consumer
        OSELib::SDC::ServiceManager oscpsm;
        DebugOut(DebugOut::Default, "MultiStateSDC") << "Consumer discovery..." << std::endl;
        std::shared_ptr<SDCConsumer> c(oscpsm.discoverEndpointReference(OSCLib::Tests::multiStatesSDC::deviceEPR));
//        std::shared_ptr<Tests::multiStatesSDC::  > eventHandler = std::make_shared<Tests::StreamSDC::StreamConsumerEventHandler>("handle_plethysmogram_stream");
//        std::shared_ptr<Tests::StreamSDC::StreamConsumerEventHandler> eventHandlerAlt = std::make_shared<Tests::StreamSDC::StreamConsumerEventHandler>("handle_plethysmogram_stream_alt");
//        std::shared_ptr<Tests::StreamSDC::StreamDistributionConsumerEventHandler> eventHandlerDistribution= std::make_shared<Tests::StreamSDC::StreamDistributionConsumerEventHandler>("handle_distribution_stream");

        // Discovery test
        CHECK_EQUAL(true, c != nullptr);

        if (c != nullptr) {
//            c->registerStateEventHandler(eventHandler.get());
//            c->registerStateEventHandler(eventHandlerAlt.get());
//            c->registerStateEventHandler(eventHandlerDistribution.get());
//
//            provider.start();// starts provider in a thread and calls the overwritten function runImpl()
//
//			// Metric event reception test
//            Poco::Thread::sleep(10000);
//            CHECK_EQUAL(true, eventHandler->getVerifiedChunks());
//            CHECK_EQUAL(true, eventHandlerAlt->getVerifiedChunks());
//            CHECK_EQUAL(true, eventHandlerDistribution->getVerifiedChunks());
//
//            provider.interrupt();
//            c->unregisterStateEventHandler(eventHandler.get());
//            c->unregisterStateEventHandler(eventHandlerAlt.get());
//            c->unregisterStateEventHandler(eventHandlerDistribution.get());
            c->disconnect();
        }

        Poco::Thread::sleep(2000);
        provider.shutdown();
	}
	catch (char const* exc)
	{
		DebugOut(DebugOut::Default, std::cerr, "MultiStateSDC") << exc;
	}
	catch (...)
	{
		DebugOut(DebugOut::Default, std::cerr, "MultiStateSDC") << "Unknown exception occurred!";
	}
	DebugOut::closeLogFile();
}
}
