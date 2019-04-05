/*
 * test_MultiProvider.cpp

 *
 *  Created on: Feb 20, 2019
 *      Author: sebastian
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
#include "Tools/HelperMethods.h"
//Sample Provider. Exchange for your provider under test.
#include "Tools/TestProvider.h"
using namespace SDCLib;
using namespace SDCLib::Util;
using namespace SDCLib::Data::SDC;

//Device endpoint reference change to your devices

int main() {
	//Network configuration
	SDCLibrary::getInstance().startup(OSELib::LogLevel::Trace);
	SDCLibrary::getInstance().setIP6enabled(false);
	SDCLibrary::getInstance().setIP4enabled(true);

	//Sample Provider startup. Exchange for your provider under test.

//    SDCLibrary2::getInstance().startup(OSELib::LogLevel::Error);
//    list<string> asdf;
//    asdf.push_back("enp0s3");
//    asdf.push_back("docker0");
//    SDCInstancePtr sdcInstance2 = SDCLibrary2::getInstance().createBoundSDCInstance(asdf);

	TestTools::TestProvider provider123;
	provider123.setPort(TestTools::getFreePort());
	provider123.setEndPointReference("123");
	provider123.startup();
	provider123.start();

	TestTools::TestProvider provider456;
	provider456.setPort(TestTools::getFreePort());
	provider456.setEndPointReference("456");
	provider456.startup();
	provider456.start();

	TestTools::TestProvider provider789;
	provider789.setPort(TestTools::getFreePort());
	provider789.setEndPointReference("789");
	provider789.startup();
	provider789.start();

	std::string temp;
	DebugOut(DebugOut::Default, "PulseOximeterProvider") << "Press key to exit program.";
	std::cin >> temp;

	provider123.shutdown();
	provider456.shutdown();
	provider789.shutdown();
	SDCLibrary::getInstance().shutdown();

    Util::DebugOut(Util::DebugOut::Default, "TestConsumer") << "Shutdown." << std::endl;

}

