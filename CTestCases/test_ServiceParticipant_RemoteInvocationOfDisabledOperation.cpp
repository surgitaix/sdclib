/*
 * test_ServiceParticipant_RemoteInvocationOfDisabledOperation.cpp
 *
 *  Created on: Jan 23, 2019
 *      Author: rosenau
 */

#include "OSCLib/SDCLibrary.h"
#include "Tools/TestProvider.h"
#include "Tools/TestConsumer.h"

using namespace SDCLib::Data::SDC;

int main() {
	std::cout << "Test against requirement R0027 from IEEE 11073-10207 A SERVICE PROVIDER SHALL ensure that a disabled operation is not accessible for remote invocation:" << std::endl;
	SDCLibrary::getInstance().startup(OSELib::LogLevel::Error);
	SDCLibrary::getInstance().setIP6enabled(false);
	SDCLibrary::getInstance().setIP4enabled(true);
	SDCLibrary::getInstance().setPortStart(12000);

	TestTools::TestProvider provider;
	provider.setPort(6470);
	provider.startup();
	provider.start();

	TestTools::TestConsumer consumer;
	consumer.start();

	//Discovery
	OSELib::SDC::ServiceManager oscpsm;
	// binding to a custom port
	MDPWSTransportLayerConfiguration config = MDPWSTransportLayerConfiguration();
	config.setPort(6471);

	std::unique_ptr<Data::SDC::SDCConsumer> c(oscpsm.discoverEndpointReference(TestTools::DEFAULT_TEST_DEVICE_EPR, config));

	if(c != nullptr) {
		consumer.setConsumer(std::move(c));
		consumer.registerNumericMetricStateSetHandler();

	}

}


