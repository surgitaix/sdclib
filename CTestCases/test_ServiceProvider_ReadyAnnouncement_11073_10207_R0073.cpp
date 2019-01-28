/*
 * test_ServiceProvider_ReadyAnnouncement_11073_10207_R0073.cpp
 *
 *  Created on: Nov 7, 2018
 *      Author: rosenau
 *
 *      Test against requirement R0073 from IEEE 11073-10207 A SERVICE PROVIDER SHALL announce its presence if it is ready to exchange MESSAGEs with a SERVICE CONSUMER
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

#include "Tools/HelperMethods.h"
#include "Tools/TestProvider.h"

using namespace SDCLib;
using namespace SDCLib::Util;
using namespace SDCLib::Data::SDC;


const std::string DEVICE_EPR("TestProvider");

int main() {
	std::cout << "Test against requirement R0073 from IEEE 11073-10207 A SERVICE PROVIDER SHALL announce its presence if it is ready to exchange MESSAGEs with a SERVICE CONSUMER:";
	SDCLibrary::getInstance().startup(OSELib::LogLevel::None);
	SDCLibrary::getInstance().setIP6enabled(false);
	SDCLibrary::getInstance().setIP4enabled(true);
	SDCLibrary::getInstance().setPortStart(12000);

	OSELib::SDC::ServiceManager oscpsm;

	class MyHelloReceivedHandler : public OSELib::SDC::HelloReceivedHandler {
	public:
		MyHelloReceivedHandler() {};
		void helloReceived(const std::string &) override {
			Util::DebugOut(Util::DebugOut::Default, "TestConsumer") << "Hello received";
			Util::DebugOut(Util::DebugOut::Default, "TestConsumer") << "Test passed";
		}


	};
	std::unique_ptr<MyHelloReceivedHandler> helloReceivedTester(new MyHelloReceivedHandler);
	oscpsm.setHelloReceivedHandler(helloReceivedTester.get());

	TestTools::TestProvider provider;
	provider.setPort(TestTools::getFreePort());
	provider.startup();
	provider.start();

	provider.shutdown();
	SDCLibrary::getInstance().shutdown();
}


