/*
 * test_ServiceParticipant_GetService_11073_10207_R0062.cpp
 *
 *  Created on: Jan 7, 2019
 *      Author: rosenau
 */
/*
 * Test against requirement R0062 from IEEE 11073-10207 A SERVICE PROVIDER SHALL provide a GET SERVICE.
 */

#include <iostream>

#include "osdm.hxx"

#include "OSCLib/SDCInstance.h"
#include "OSCLib/SDCLibrary.h"
#include "OSCLib/Data/SDC/SDCConsumer.h"
#include "OSCLib/Data/SDC/MDPWSTransportLayerConfiguration.h"
#include "OSELib/SDC/ServiceManager.h"
#include "OSELib/DPWS/DPWS11Constants.h"
#include "OSCLib/Data/SDC/MDIB/ConvertToCDM.h"

#include "Tools/HelperMethods.h"
#include "Tools/TestProvider.h"
#include "Tools/TestConsumer.h"


using namespace SDCLib;
using namespace SDCLib::Util;
using namespace SDCLib::Data::SDC;

const std::string DEVICE_EPR("TestProvider");


int main() {
	std::cout << "Test against requirement R0062 from IEEE 11073-10207 A SERVICE PROVIDER SHALL provide a GET SERVICE."
			  << std::endl;
	SDCLibrary::getInstance().startup(OSELib::LogLevel::Error);
	SDCLibrary::getInstance().setIP6enabled(false);
	SDCLibrary::getInstance().setIP4enabled(true);

	//Example Provider. Exchange for your provider.
	TestTools::TestProvider provider;
	provider.setPort(6466);
	provider.startup();
	provider.start();

	SDCLibrary::getInstance().setPortStart(12000);

	OSELib::SDC::ServiceManager oscpsm;
	MDPWSTransportLayerConfiguration config = MDPWSTransportLayerConfiguration();
	config.setPort(6467);

	TestTools::TestConsumer consumer;
	consumer.start();

	// Discovery
	std::unique_ptr<Data::SDC::SDCConsumer> c(oscpsm.discoverEndpointReference(DEVICE_EPR, config));
	if(c == nullptr) {
		std::cout << "ERROR";
	}
	consumer.setConsumer(std::move(c));

	if(TestTools::getStringRepresentationOfMDIB(consumer.getConsumer()->getMdib()) == TestTools::getStringRepresentationOfMDIB(provider.getMdib()))
	{
		std::cout << "Test passed";
	}
	else
		std::cout << "Test failed";

}


