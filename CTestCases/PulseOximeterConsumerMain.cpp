/*
 * test_PulseOximeterConsumer.cpp
 *
 *  Created on: Jan 16, 2019
 *      Author: rosenau
 */

#include "OSCLib/SDCInstance.h"
#include "OSCLib/SDCLibrary.h"
#include "OSCLib/SDCLibrary2.h"
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
#include "Tools/PulseOximeterConsumer.h"
using namespace SDCLib;
using namespace SDCLib::Util;
using namespace SDCLib::Data::SDC;

//Device endpoint reference change to your devices
const std::string DEVICE_EPR("PulseOximeter");


int main() {
	//Network configuration
	Util::DebugOut(Util::DebugOut::Default, "PulseOximeterConsumer") << "Startup";
    SDCLibrary::getInstance().startup(OSELib::LogLevel::Warning);
	SDCLibrary::getInstance().setPortStart(12000);

	//Discovery
	OSELib::SDC::ServiceManager oscpsm;

	//binding to custom port
	MDPWSTransportLayerConfiguration config = MDPWSTransportLayerConfiguration();
	config.setPort(6465);

	PulseOximeterConsumer consumer;
	consumer.start();

	std::unique_ptr<Data::SDC::SDCConsumer> c(oscpsm.discoverEndpointReference(DEVICE_EPR, config));
	SDCLibrary::getInstance().shutdown();
	if(c != nullptr) {
		consumer.setConsumer(std::move(c));
		consumer.registerPulseRateHandler();
		consumer.registerSatO2Handler();
		consumer.registerPulseRateAlertHandler();
		consumer.registerPulseRateAlertSignalHandler();
		consumer.registerSatO2AlertHandler();
		consumer.registerSatO2AlertSignalHandler();
		consumer.registerOximeterAlertSystemHandler();
	}


	std::string temp;
	DebugOut(DebugOut::Default, "PulseOximeterConsumer") << "Press key to exit program.";
	std::cin >> temp;

	consumer.shutdown();

    Util::DebugOut(Util::DebugOut::Default, "TestConsumer") << "Shutdown." << std::endl;
}


