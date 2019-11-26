/*
 * test_PulseOximeterProvider.cpp
 *
 *  Created on: Jan 15, 2019
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
#include "Tools/PulseOximeterProvider.h"
using namespace SDCLib;
using namespace SDCLib::Util;
using namespace SDCLib::Data::SDC;

//Device endpoint reference change to your devices
const std::string DEVICE_EPR("PulseOximeter");


int main() {
	//Network configuration
	SDCLibrary::getInstance().startup(OSELib::LogLevel::Notice);
	SDCLibrary::getInstance().setIP6enabled(false);
	SDCLibrary::getInstance().setIP4enabled(true);

	//Sample Provider startup. Exchange for your provider under test.

    SDCLibrary2::getInstance().startup(OSELib::LogLevel::Debug);
    list<string> asdf;
    asdf.push_back("enp0s3");
    asdf.push_back("docker0");
    SDCInstancePtr sdcInstance2 = SDCLibrary2::getInstance().createBoundSDCInstance(asdf);

	PulseOximeterProvider provider;
	provider.setPort(6459);
	provider.startup();
	provider.start();

	std::string temp;
	DebugOut(DebugOut::Default, "PulseOximeterProvider") << "Press key to exit program.";
	std::cin >> temp;

	provider.shutdown();
	SDCLibrary::getInstance().shutdown();

    Util::DebugOut(Util::DebugOut::Default, "TestConsumer") << "Shutdown." << std::endl;
}

