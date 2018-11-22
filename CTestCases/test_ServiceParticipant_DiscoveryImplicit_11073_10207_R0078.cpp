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

using namespace SDCLib;
using namespace SDCLib::Util;
using namespace SDCLib::Data::SDC;


const std::string DEVICE_EPR("TestProvider");


class OSCPStreamProvider : public Util::Task {
public:

    OSCPStreamProvider() :
    	sdcProvider()
    	{

    	MDPWSTransportLayerConfiguration providerConfig = MDPWSTransportLayerConfiguration();
		providerConfig.setPort(6462);
		sdcProvider.setConfiguration(providerConfig);
		sdcProvider.setEndpointReference(DEVICE_EPR);


    }

    void startup() {
    	sdcProvider.startup();
    }

    void shutdown() {
    	sdcProvider.shutdown();
    }

private:

    SDCProvider sdcProvider;


public:
    virtual void runImpl() override {
		while (!isInterrupted()) {
			{
			}
			Poco::Thread::sleep(1000);
		}
    }
};


int main() {
	// Startup
	std::cout << "Test against requirement R0078 from IEEE 11073-10207 A BICEPS BINDING SHALL provide means for implicit discovery:";
	DebugOut(DebugOut::Default, "TestProvider") << "Startup";
	SDCLibrary::getInstance().startup(OSELib::LogLevel::Error);
	SDCLibrary::getInstance().setIP6enabled(false);
	SDCLibrary::getInstance().setIP4enabled(true);

	OSCPStreamProvider provider;
	provider.startup();
	provider.start();

	Util::DebugOut(Util::DebugOut::Default, "TestConsumer") << "Startup";
    SDCLibrary::getInstance().startup(OSELib::LogLevel::Error);
	SDCLibrary::getInstance().setPortStart(12000);

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


	// Discovery
	OSELib::SDC::ServiceManager oscpsm;
	// binding to a custom port
	MDPWSTransportLayerConfiguration config = MDPWSTransportLayerConfiguration();
	config.setPort(6463);

	auto consumers(oscpsm.discoverOSCP());
	std::unique_ptr<Data::SDC::SDCConsumer> c = nullptr;

	if(!consumers.empty())
		c = std::move(consumers.front());


	try {
		if (c != nullptr) {
			Data::SDC::SDCConsumer & consumer = *c;
			std::unique_ptr<MyConnectionLostHandler> myHandler(new MyConnectionLostHandler(consumer));
			consumer.setConnectionLostHandler(myHandler.get());
			Util::DebugOut(Util::DebugOut::Default, "TestConsumer") << "Discovery succeeded.";
			Util::DebugOut(Util::DebugOut::Default, "TestConsumer") << "Test passed";

			consumer.disconnect();
			provider.shutdown();
			SDCLibrary::getInstance().shutdown();


			} else {
			Util::DebugOut(Util::DebugOut::Default, "TestConsumer") << "Discovery failed.";
			Util::DebugOut(Util::DebugOut::Default, "TestConsumer") << "Test failed";

		}

	} catch (std::exception & e){
		Util::DebugOut(Util::DebugOut::Default, "TestConsumer") << "Exception: " << e.what() << std::endl;
		Util::DebugOut(Util::DebugOut::Default, "TestConsumer") << "Test failed";
	}
	SDCLibrary::getInstance().shutdown();
	Util::DebugOut(Util::DebugOut::Default, "TestConsumer") << "Shutdown." << std::endl;
}

