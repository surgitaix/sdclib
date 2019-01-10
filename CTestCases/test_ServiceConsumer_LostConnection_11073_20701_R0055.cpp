/*
 * test_ServiceConsumer_LostConnection_11073_20701_R0055.cpp
 *
 *  Created on: Dec 7, 2018
 *      Author: rosenau
 */
/*
 * Test against requirement R0080 from IEEE 11073-20701-R0055 An SDC Consumer MAY detect lost connections to an SDC SERVICE PROVIDER by requesting the
 * subscription state or trying to renew a subscription in case it did not receive any MESSAGE from the SDC SERVICE PROVIDER for a defined amount of time.
 */

#include "OSCLib/SDCInstance.h"
#include "OSCLib/SDCLibrary.h"

#include "OSCLib/Data/SDC/SDCProvider.h"
#include "OSCLib/Data/SDC/SDCConsumer.h"
#include "OSCLib/Data/SDC/SDCConsumerConnectionLostHandler.h"

#include "OSELib/SDC/ServiceManager.h"

#include "OSCLib/Util/DebugOut.h"

#include "Tools/TestProvider.h"

using namespace SDCLib;
using namespace SDCLib::Util;
using namespace SDCLib::Data::SDC;

const std::string DEVICE_EPR("TestProvider");

int main()
{
	std::cout << "Test against requirement R0080 from IEEE 11073-20701-R0055 An SDC Consumer MAY detect lost connections to an SDC SERVICE PROVIDER by requesting the "
			  << "subscription state or trying to renew a subscription in case it did not receive any MESSAGE from the SDC SERVICE PROVIDER for a defined amount of time."
			  << std::endl;

	//Network configuration
	SDCLibrary::getInstance().startup(OSELib::LogLevel::Trace);
	SDCLibrary::getInstance().setIP6enabled(false);
	SDCLibrary::getInstance().setIP4enabled(true);

	OSELib::SDC::ServiceManager oscpsm;

	//Sample Provider.
	TestTools::TestProvider provider;
	provider.startup();
	provider.start();

	MDPWSTransportLayerConfiguration consumerConfig = MDPWSTransportLayerConfiguration();
	consumerConfig.setPort(6461);
	class ConnectionLostHandler : public SDCConsumerConnectionLostHandler {
	public:
		void onConnectionLost() {
			Util::DebugOut(Util::DebugOut::Default, "TestConsumer") << "Test passed" << std::endl;
		}

	};
	ConnectionLostHandler connectionLostHandler;

	// Discovery
	std::unique_ptr<Data::SDC::SDCConsumer> c(oscpsm.discoverEndpointReference(DEVICE_EPR, consumerConfig));
	if(c != nullptr) {
		SDCConsumer &consumer = *c;
		consumer.setConnectionLostHandler(&connectionLostHandler);
		provider.~TestProvider();
		Poco::Thread::sleep(20000);
		consumer.disconnect();
	}

    SDCLibrary::getInstance().shutdown();


}



