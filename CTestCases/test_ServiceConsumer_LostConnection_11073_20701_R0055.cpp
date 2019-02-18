/*
 * test_ServiceConsumer_LostConnection_11073_20701_R0055.cpp
 *
 *  Created on: Dec 7, 2018
 *      Author: rosenau
 */
/*
 * Test against requirement R0080 from IEEE 11073-20701-R0055 An SDC Consumer MAY detect lost connections to an SDC SERVICE PROVIDER by requesting the
 * subscription state or trying to renew a subscription in case it did not receive any MESSAGE from the SDC SERVICE PROVIDER for a defined amount of time.
 * This test will only work under linux, as windows does not provide fork()!
 */


#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "OSCLib/SDCInstance.h"
#include "OSCLib/SDCLibrary.h"
#include "OSCLib/Data/SDC/SDCProvider.h"
#include "OSCLib/Data/SDC/SDCConsumer.h"
#include "OSCLib/Data/SDC/SDCConsumerConnectionLostHandler.h"
#include "OSELib/SDC/ServiceManager.h"

#include "OSCLib/Util/DebugOut.h"

#include "Tools/HelperMethods.h"
#include "Tools/TestProvider.h"
#include "Tools/TestConsumer.h"

using namespace SDCLib;
using namespace SDCLib::Util;
using namespace SDCLib::Data::SDC;

const std::string DEVICE_EPR("TestProvider");


int main(void) {
	std::cout << "Test against requirement R0080 from IEEE 11073-20701-R0055 An SDC Consumer MAY detect "
			  << "lost connections to an SDC SERVICE PROVIDER by requesting the "
			  << "subscription state or trying to renew a subscription in case it did not receive "
			  << "any MESSAGE from the SDC SERVICE PROVIDER for a defined amount of time."
			  << std::endl;

	//Network configuration
	SDCLibrary::getInstance().startup(OSELib::LogLevel::Error);
	SDCLibrary::getInstance().setIP6enabled(false);
	SDCLibrary::getInstance().setIP4enabled(true);

	OSELib::SDC::ServiceManager oscpsm;

	//Creating separated processes to be able to make the provider crash. To ensure the provider is setup for discovery a shared variable is used:
	//shared_setup = 0 -> provider is not setup, shared_setup = 1 -> provider is setup.
	int * shared_setup = (int*) mmap(NULL, sizeof(int), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    *shared_setup = 0;
	pid_t providerProcessId = fork();
	//Child process setting up provider
    if(providerProcessId==0) {
    	//Sample provider setup
    	TestTools::TestProvider provider;
        provider.setPort(TestTools::getFreePort());
        provider.startup();
        provider.start();
        *shared_setup = 1;
        pause();
    }
    //Parent Process
    else if(providerProcessId > 0) {
    	//Wait for provider being setup
    	while(*shared_setup != 1) {
    		sleep(1);
    	}
    	Util::DebugOut(Util::DebugOut::Default, "LostConnection") << "Provider is setup" << std::endl;

    	//ConnectionLostHandler defining the behavior onConnectionLost.
		class ConnectionLostHandler : public SDCConsumerConnectionLostHandler {
		public:
			void onConnectionLost() {
				Util::DebugOut(Util::DebugOut::Default, "LostConnection") << "Test passed" << std::endl;
			}

		};

		// Discovery
		TestTools::TestConsumer consumer;
		consumer.start();

		MDPWSTransportLayerConfiguration consumerConfig = MDPWSTransportLayerConfiguration();
		consumerConfig.setPort(TestTools::getFreePort());
		std::unique_ptr<Data::SDC::SDCConsumer> c(oscpsm.discoverEndpointReference(DEVICE_EPR, consumerConfig));
		if(c != nullptr) {
	    	Util::DebugOut(Util::DebugOut::Default, "LostConnection") << "Established Connection" << std::endl;
			consumer.setConsumer(std::move(c));
			ConnectionLostHandler connectionLostHandler;
			consumer.setConnectionLostHandler(&connectionLostHandler);

			//Simulating provider crash by killing the process.
			kill(providerProcessId, SIGKILL);
	    	Util::DebugOut(Util::DebugOut::Default, "LostConnection") << "Killing Provider" << std::endl;

	    	//After killing the Provider it takes about 5seconds until the lostConnection is detected.
	    	//This value should be exchanged for a defined limit.
			Poco::Thread::sleep(5000);
			consumer.disconnect();
		}
		SDCLibrary::getInstance().shutdown();
		munmap(shared_setup, sizeof *shared_setup);
    }
	else
	{
		//fork failed
		std::cout << "fork() failed!" << std::endl;
	}
}



