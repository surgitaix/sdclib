/*
 * test_ServiceParticipant_RemoteInvocationOfDisabledOperation.cpp
 *
 *  Created on: Jan 23, 2019
 *      Author: rosenau
 */

#include "OSCLib/SDCLibrary.h"

#include "OSCLib/Data/SDC/SDCConsumer.h"
#include "OSELib/SDC/ServiceManager.h"

#include "Tools/HelperMethods.h"
#include "Tools/TestProvider.h"
#include "Tools/TestConsumer.h"

using namespace SDCLib;
using namespace SDCLib::Data::SDC;

const std::string DEVICE_EPR("TestProvider");

int main() {
	std::cout << "Test against requirement R0027 from IEEE 11073-10207 A SERVICE PROVIDER SHALL ensure that a disabled operation is not accessible for remote invocation:" << std::endl;
	SDCLibrary::getInstance().startup(OSELib::LogLevel::Error);
	SDCLibrary::getInstance().setIP6enabled(false);
	SDCLibrary::getInstance().setIP4enabled(true);
	SDCLibrary::getInstance().setPortStart(12000);

	TestTools::TestProvider provider;
	provider.setPort(TestTools::getFreePort());
	provider.startup();
	provider.start();

	TestTools::TestConsumer consumer;
	consumer.start();

	//Discovery
	OSELib::SDC::ServiceManager oscpsm;
	// binding to a custom port
	MDPWSTransportLayerConfiguration config = MDPWSTransportLayerConfiguration();
	config.setPort(TestTools::getFreePort());

	std::unique_ptr<Data::SDC::SDCConsumer> c(oscpsm.discoverEndpointReference(DEVICE_EPR, config));

	if(c != nullptr) {
		consumer.setConsumer(std::move(c));
		consumer.registerNumericMetricStateSetHandler();
	}

}


