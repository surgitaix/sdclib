/*
 * test_ServiceProvider_LostConnection_11073_20701_R0054.cpp
 *
 *  Created on: Dec 7, 2018
 *      Author: rosenau
 */

#include "OSCLib/SDCInstance.h"
#include "OSCLib/SDCLibrary.h"

#include "OSCLib/Data/SDC/SDCProvider.h"
#include "OSCLib/Data/SDC/SDCConsumer.h"

#include "OSELib/SDC/ServiceManager.h"

#include "OSCLib/Util/DebugOut.h"

#include "Tools/HelperMethods.h"

using namespace SDCLib;
using namespace SDCLib::Util;
using namespace SDCLib::Data::SDC;

const std::string DEVICE_EPR("TestProvider");

int main()
{
	std::cout << "Test against requirement 11073-20701-R0054: An SDC SERVICE PROVIDER MAY detect "
			  << "lost connections to an SDC SERVICE CONSUMER by defining a short "
			  << "expiration time for subscriptions.";
	SDCLibrary::getInstance().startup(OSELib::LogLevel::Error);
	SDCLibrary::getInstance().setIP6enabled(false);
	SDCLibrary::getInstance().setIP4enabled(true);

	// Discovery
	OSELib::SDC::ServiceManager oscpsm;
	// binding to a custom port
	MDPWSTransportLayerConfiguration providerConfig = MDPWSTransportLayerConfiguration();
	providerConfig.setPort(TestTools::getFreePort());

	SDCProvider sdcProvider;
	sdcProvider.setConfiguration(providerConfig);
	sdcProvider.setEndpointReference(DEVICE_EPR);
	sdcProvider.startup();

	MDPWSTransportLayerConfiguration consumerConfig = MDPWSTransportLayerConfiguration();
	consumerConfig.setPort(TestTools::getFreePort());

	std::unique_ptr<Data::SDC::SDCConsumer> c(oscpsm.discoverEndpointReference(DEVICE_EPR, consumerConfig));
	if(c != nullptr) {
		SDCConsumer &consumer = *c;
		Util::DebugOut(Util::DebugOut::Default, "TestConsumer") << "Connection established..."
				<< std::endl << "Shutting down Consumer";
		consumer.disconnect();
	}
	Poco::Thread::sleep(5000);
	sdcProvider.shutdown();
    SDCLibrary::getInstance().shutdown();

    std::cout << "Test failed";


}

