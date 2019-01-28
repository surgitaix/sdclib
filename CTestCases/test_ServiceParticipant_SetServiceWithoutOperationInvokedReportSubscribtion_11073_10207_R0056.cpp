/*
 * test_ServiceParticipant_SetServiceWithoutOperationInvokedReportSubscription_11073_10207_R0056.cpp
 *
 *  Created on: Dec 3, 2018
 *      Author: rosenau
 */

#include <iostream>

#include "OSCLib/SDCInstance.h"

#include "OSCLib/SDCLibrary.h"
#include "OSCLib/Data/SDC/SDCProvider.h"
#include "OSCLib/Data/SDC/SDCConsumer.h"
#include "OSELib/SDC/ServiceManager.h"

#include "OSCLib/Data/SDC/MDIB/ChannelDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/VmdDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/MdsDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/MdDescription.h"
#include "OSCLib/Data/SDC/MDIB/CodedValue.h"

#include "OSCLib/Data/SDC/MDIB/NumericMetricState.h"
#include "OSCLib/Data/SDC/MDIB/NumericMetricValue.h"
#include "OSCLib/Data/SDC/MDIB/NumericMetricDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/MetricQuality.h"
#include "OSCLib/Data/SDC/SDCProviderMDStateHandler.h"
#include "OSCLib/Data/SDC/SDCConsumerMDStateHandler.h"
#include "OSCLib/Data/SDC/SDCConsumerOperationInvokedHandler.h"

#include "OSCLib/Data/SDC/FutureInvocationState.h"


#include "OSCLib/Data/SDC/MDIB/custom/OperationInvocationContext.h"

#include "OSCLib/Util/Task.h"

#include "OSCLib/Data/SDC/SDCConsumerConnectionLostHandler.h"
#include "OSCLib/Data/SDC/MDPWSTransportLayerConfiguration.h"

#include "OSCLib/Util/DebugOut.h"

#include "Tools/HelperMethods.h"

#include "Tools/TestProvider.h"

#include "Tools/TestConsumer.h"

const std::string DEVICE_EPR("TestProvider");


using namespace SDCLib;
using namespace SDCLib::Util;
using namespace SDCLib::Data::SDC;



int main() {
	std::cout << "Test against requirement R0056  A SERVICE CONSUMER SHALL subscribe to msg:OperationInvokedReport"
			  << " before invoking request-response SERVICE OPERATIONs of the SET SERVICE" << std::endl;

	SDCLibrary::getInstance().startup(OSELib::LogLevel::Error);
	SDCLibrary::getInstance().setIP6enabled(false);
	SDCLibrary::getInstance().setIP4enabled(true);

	TestTools::TestProvider provider;
	provider.setPort(TestTools::getFreePort());
	provider.startup();
	provider.start();

	//Discovery
	OSELib::SDC::ServiceManager oscpsm;
	// binding to a custom port
	MDPWSTransportLayerConfiguration config = MDPWSTransportLayerConfiguration();
	config.setPort(TestTools::getFreePort());

	TestTools::TestConsumer consumer;
	consumer.start();

	std::unique_ptr<Data::SDC::SDCConsumer> c(oscpsm.discoverEndpointReference(DEVICE_EPR, config));

	if (c != nullptr) {
		consumer.setConsumer(std::move(c));

		consumer.registerNumericMetricStateSetHandler();
		consumer.setNumericMetricStateValue(2.0);
		Poco::Thread::sleep(2000);
		consumer.unregisterNumericMetricStateSetHandler();

		consumer.disconnect();
	}

	provider.shutdown();
	SDCLibrary::getInstance().shutdown();
}
