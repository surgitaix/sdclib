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
#include "OSCLib/Data/SDC/SDCProvider.h"
#include "OSCLib/Data/SDC/SDCConsumer.h"
#include "OSCLib/Data/SDC/SDCConsumerConnectionLostHandler.h"
#include "OSCLib/Data/SDC/MDPWSTransportLayerConfiguration.h"
#include "OSELib/SDC/ServiceManager.h"

#include "OSCLib/Util/DebugOut.h"
#include "OSCLib/Util/Task.h"


#include "Poco/Runnable.h"
#include "Poco/Mutex.h"
#include "Poco/ScopedLock.h"
#include "Poco/Thread.h"
#include "Poco/Net/IPAddress.h"

//Sample Provider. Exchange for your provider under test.
#include "Tools/TestProvider.h"

using namespace SDCLib;
using namespace SDCLib::Util;
using namespace SDCLib::Data::SDC;

//Device endpoint reference change to your devices
const std::string DEVICE_EPR("Test_Provider");


int main() {
	// Startup
	std::cout << "Test against requirement R0080 from IEEE 11073-10207 A BICEPS BINDING SHALL provide means for explicit discovery:"
			  << std::endl;
	//Network configuration
	SDCLibrary::getInstance().startup(OSELib::LogLevel::Error);
	SDCLibrary::getInstance().setIP6enabled(false);
	SDCLibrary::getInstance().setIP4enabled(true);

	//Sample Provider startup. Exchange for your provider under test.
	TestTools::TestProvider provider;
	provider.startup();
	provider.start();

	SDCLibrary::getInstance().setPortStart(12000);

	//Handler of SDCConsumer to disconnect on connection loss
    class MyConnectionLostHandler : public Data::SDC::SDCConsumerConnectionLostHandler {
    public:
    	MyConnectionLostHandler(Data::SDC::SDCConsumer & consumer) : consumer(consumer) {
    	}
    	void onConnectionLost() override {
    		std::cerr << "Connection lost, disconnecting... ";
    		consumer.disconnect();
    		std::cerr << "disconnected." << std::endl;
    	}
    private:
    	Data::SDC::SDCConsumer & consumer;
    };


	OSELib::SDC::ServiceManager oscpsm;
	MDPWSTransportLayerConfiguration config = MDPWSTransportLayerConfiguration();
	config.setPort(6467);

	// Discovery
	std::unique_ptr<Data::SDC::SDCConsumer> c(oscpsm.discoverEndpointReference(DEVICE_EPR, config));

	try {
		if (c != nullptr) {
			Data::SDC::SDCConsumer & consumer = *c;
			std::unique_ptr<MyConnectionLostHandler> myHandler(new MyConnectionLostHandler(consumer));
			consumer.setConnectionLostHandler(myHandler.get());
			Util::DebugOut(Util::DebugOut::Default, "TestConsumer") << "Discovery succeeded." << std::endl;
			Util::DebugOut(Util::DebugOut::Default, "TestConsumer") << "Test passed" << std::endl;


			consumer.disconnect();
			provider.shutdown();
		    SDCLibrary::getInstance().shutdown();
			} else {
			Util::DebugOut(Util::DebugOut::Default, "TestConsumer") << "Discovery failed." << std::endl;
			Util::DebugOut(Util::DebugOut::Default, "TestConsumer") << "Test failed" << std::endl;

		}

	} catch (std::exception & e){
		Util::DebugOut(Util::DebugOut::Default, "TestConsumer") << "Exception: " << e.what() << std::endl;
		Util::DebugOut(Util::DebugOut::Default, "TestConsumer") << "Test failed" << std::endl;
	}
    SDCLibrary::getInstance().shutdown();
    Util::DebugOut(Util::DebugOut::Default, "TestConsumer") << "Shutdown." << std::endl;
}

