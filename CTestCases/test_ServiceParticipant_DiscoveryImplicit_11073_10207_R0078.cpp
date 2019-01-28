/*
 * test_ServiceParticipant_DiscoveryExplicit_11073_10207_R0078.cpp
 *
 *  Created on: Oct 30, 2018
 *      Author: rosenau
 */
/*
 * Test against requirement R0078 from IEEE 11073-10207 A BICEPS BINDING SHALL provide means for implicit discovery
 */

#include "OSCLib/SDCInstance.h"


#include "OSCLib/SDCLibrary.h"
#include "OSCLib/Data/SDC/SDCProvider.h"

#include "OSCLib/Data/SDC/SDCProviderComponentStateHandler.h"
#include "OSCLib/Data/SDC/SDCProviderStateHandler.h"
#include "OSCLib/Data/SDC/SDCProviderMDStateHandler.h"
#include "OSCLib/Data/SDC/SDCConsumer.h"
#include "OSCLib/Data/SDC/SDCConsumerConnectionLostHandler.h"
#include "OSCLib/Data/SDC/SDCConsumerMDStateHandler.h"
#include "OSCLib/Data/SDC/MDPWSTransportLayerConfiguration.h"


#include "OSELib/SDC/ServiceManager.h"

#include "BICEPS_MessageModel-fwd.hxx"

#include "OSCLib/Util/DebugOut.h"
#include "OSCLib/Util/Task.h"


#include "Poco/Runnable.h"
#include "Poco/Mutex.h"
#include "Poco/ScopedLock.h"
#include "Poco/Thread.h"
#include "Poco/Net/IPAddress.h"

#include "Tools/HelperMethods.h"

//Sample Provider. Exchange for your provider under test.
#include "Tools/TestProvider.h"

//Sample Consumer. Exchange for you consumer under test.
#include "Tools/TestConsumer.h"

using namespace SDCLib;
using namespace SDCLib::Util;
using namespace SDCLib::Data::SDC;

//Device endpoint reference change to your devices
const std::string DEVICE_EPR("TestProvider");

int main() {
	// Startup
	std::cout << "Test against requirement R0078 from IEEE 11073-10207 A BICEPS BINDING SHALL provide means for implicit discovery:"
			  << std::endl;
	//Network configuration
	SDCLibrary::getInstance().startup(OSELib::LogLevel::Error);
	SDCLibrary::getInstance().setIP6enabled(false);
	SDCLibrary::getInstance().setIP4enabled(true);

	//Sample Provider startup. Exchange for your provider under test.
	TestTools::TestProvider provider;
	provider.setPort(TestTools::getFreePort());
	provider.startup();
	provider.start();

	SDCLibrary::getInstance().setPortStart(12000);

	OSELib::SDC::ServiceManager oscpsm;
	MDPWSTransportLayerConfiguration config = MDPWSTransportLayerConfiguration();
	config.setPort(TestTools::getFreePort());

	TestTools::TestConsumer consumer;
	consumer.start();

	// Discovery
	auto consumers(oscpsm.discoverOSCP());
	std::unique_ptr<Data::SDC::SDCConsumer> c = nullptr;

	if(!consumers.empty())
		c = std::move(consumers.front());


	try {
		if (c != nullptr) {
			consumer.setConsumer(std::move(c));
			Util::DebugOut(Util::DebugOut::Default, "TestConsumer") << "Discovery succeeded." << std::endl;
			Util::DebugOut(Util::DebugOut::Default, "TestConsumer") << "Test passed" << std::endl;

			consumer.disconnect();
			provider.shutdown();
			SDCLibrary::getInstance().shutdown();


			} else {
			Util::DebugOut(Util::DebugOut::Default, "TestConsumer") << "Discovery failed." << std::endl;
			Util::DebugOut(Util::DebugOut::Default, "TestConsumer") << "Test failed";

		}

	} catch (std::exception & e){
		Util::DebugOut(Util::DebugOut::Default, "TestConsumer") << "Exception: " << e.what() << std::endl;
		Util::DebugOut(Util::DebugOut::Default, "TestConsumer") << "Test failed" << std::endl;
	}
	SDCLibrary::getInstance().shutdown();
	Util::DebugOut(Util::DebugOut::Default, "TestConsumer") << "Shutdown." << std::endl;
}

