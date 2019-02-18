/*
 * test_ServiceParticipant_DiscoveryExplicit_11073_10207_R0080.cpp
 *
 *  Created on: Oct 30, 2018
 *      Author: rosenau
 */
/*
 * Test against requirement R0080 from IEEE 11073-10207 A BICEPS BINDING SHALL provide means for explicit discovery
 */

#include "OSCLib/SDCInstance.h"
#include "OSCLib/SDCLibrary.h"
#include "OSCLib/Data/SDC/SDCConsumer.h"
#include "OSCLib/Data/SDC/MDPWSTransportLayerConfiguration.h"
#include "OSELib/SDC/ServiceManager.h"

#include "OSCLib/Util/DebugOut.h"
#include "OSCLib/Util/Task.h"

#include "Tools/HelperMethods.h"
#include "Tools/TestProvider.h"
#include "Tools/TestConsumer.h"

using namespace SDCLib;
using namespace SDCLib::Util;
using namespace SDCLib::Data::SDC;

const std::string DEVICE_EPR("TestProvider");


int main() {
	// Startup
	std::cout << "Test against requirement R0080 from IEEE 11073-10207: A BICEPS BINDING SHALL provide means "
			  << "for explicit discovery:"
			  << std::endl;
	//Network configuration
	SDCLibrary::getInstance().startup(OSELib::LogLevel::Error);
	SDCLibrary::getInstance().setIP6enabled(false);
	SDCLibrary::getInstance().setIP4enabled(true);

	//Provider setup
	TestTools::TestProvider provider;
	provider.setPort(TestTools::getFreePort());
	provider.startup();
	provider.start();

	SDCLibrary::getInstance().setPortStart(12000);

	// Discovery
	TestTools::TestConsumer consumer;
	consumer.start();

	OSELib::SDC::ServiceManager oscpsm;
	MDPWSTransportLayerConfiguration config = MDPWSTransportLayerConfiguration();
	config.setPort(TestTools::getFreePort());

	std::unique_ptr<Data::SDC::SDCConsumer> c(oscpsm.discoverEndpointReference(DEVICE_EPR, config));
	try {
		if (c != nullptr) {
			consumer.setConsumer(std::move(c));
			Util::DebugOut(Util::DebugOut::Default, "TestConsumer") << "Discovery succeeded." << std::endl;
			Util::DebugOut(Util::DebugOut::Default, "TestConsumer") << "Test passed" << std::endl;


			consumer.disconnect();
		    SDCLibrary::getInstance().shutdown();
			} else {
			Util::DebugOut(Util::DebugOut::Default, "TestConsumer") << "Discovery failed: Provider was not found." << std::endl;
			Util::DebugOut(Util::DebugOut::Default, "TestConsumer") << "Test failed" << std::endl;

		}

	} catch (std::exception & e){
		Util::DebugOut(Util::DebugOut::Default, "TestConsumer") << "Exception: " << e.what() << std::endl;
		Util::DebugOut(Util::DebugOut::Default, "TestConsumer") << "Test failed" << std::endl;
	}
	provider.shutdown();
    SDCLibrary::getInstance().shutdown();
    Util::DebugOut(Util::DebugOut::Default, "TestConsumer") << "Shutdown." << std::endl;
}

