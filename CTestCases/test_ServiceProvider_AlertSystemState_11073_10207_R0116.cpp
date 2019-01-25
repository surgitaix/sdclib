/*
 * test_ServiceProvider_AlertSystemState_11073_10207_R0116.cpp
 *
 *  Created on: Dec 3, 2018
 *      Author: rosenau
 */

#include <iostream>

#include "OSCLib/SDCInstance.h"

#include "OSCLib/SDCLibrary.h"
#include "Tools/TestProvider.h"
#include "OSELib/SDC/ServiceManager.h"

#include "OSCLib/Util/Task.h"

#include "OSCLib/Data/SDC/MDPWSTransportLayerConfiguration.h"

#include "OSCLib/Util/DebugOut.h"
#include "Tools/HelperMethods.h"

using namespace SDCLib;
using namespace SDCLib::Data;
using namespace SDCLib::Data::SDC;



int main()
{
	std::cout << "Test against requirement R0116 from IEEE 11073-10207";
	SDCLibrary::getInstance().startup(OSELib::LogLevel::Error);
	SDCLibrary::getInstance().setIP6enabled(false);
	SDCLibrary::getInstance().setIP4enabled(true);
	SDCLibrary::getInstance().setPortStart(12000);

	TestTools::TestProvider provider;
	provider.setPort(6478);
	provider.startup();
	provider.start();

	provider.setNumericMetricValue(20);
	//std::cout << TestTools::getStringRepresentationOfMDIB(provider.getMdib());

	provider.shutdown();
	SDCLibrary::getInstance().shutdown();
	Util::DebugOut(Util::DebugOut::Default, "TestConsumer") << "Shutdown." << std::endl;

	std::cout << "Test failed";
}
