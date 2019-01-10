/*
 * test_ServiceProvider_AbsenceAnnouncement_11073_10207_R0074.cpp
 *
 *  Created on: Nov 7, 2018
 *      Author: rosenau
 *
 *      Test against requirement R0074 from IEEE 11073-10207 A SERVICE PROVIDER SHOULD announce its upcoming absence if it is switching to a mode where it is not ready to exchange MESSAGEs with a SERVICE CONSUMER temporarily.
 */

#include "OSCLib/SDCInstance.h"


#include "OSCLib/SDCInstance.h"


#include "OSCLib/SDCLibrary.h"
#include "OSCLib/Data/SDC/SDCProvider.h"

#include "OSCLib/Data/SDC/MDPWSTransportLayerConfiguration.h"

#include "OSELib/SDC/ServiceManager.h"

#include "OSCLib/Util/DebugOut.h"
#include "OSCLib/Util/Task.h"


#include "Poco/Runnable.h"
#include "Poco/Mutex.h"
#include "Poco/ScopedLock.h"
#include "Poco/Thread.h"
#include "Poco/Net/IPAddress.h"

#include "Tools/TestProvider.h"

using namespace SDCLib;
using namespace SDCLib::Util;
using namespace SDCLib::Data::SDC;


const std::string DEVICE_EPR("TestProvider");


int main() {
	std::cout << "Test against requirement R0074 from IEEE 11073-10207 A SERVICE PROVIDER SHOULD announce its upcoming absence if it is switching to a mode where it is not ready to exchange MESSAGEs with a SERVICE CONSUMER temporarily:";
	SDCLibrary::getInstance().startup(OSELib::LogLevel::None);
	SDCLibrary::getInstance().setIP6enabled(false);
	SDCLibrary::getInstance().setIP4enabled(true);
	SDCLibrary::getInstance().setPortStart(12000);

	OSELib::SDC::ServiceManager oscpsm;

	TestTools::TestProvider provider;
	provider.setPort(6470);
	provider.startup();
	provider.start();

	provider.shutdown();
	SDCLibrary::getInstance().shutdown();

	SDCLibrary::getInstance().shutdown();
	std::cout << "Test failed";
}


