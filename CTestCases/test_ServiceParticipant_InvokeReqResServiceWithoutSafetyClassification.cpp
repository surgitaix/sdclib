/*
 * test_ServiceParticipant_InvokeReqResServiceWithoutSafetyClassification.cpp
 *
 *  Created on: Feb 12, 2019
 *      Author: rosenau
 */

#include <iostream>
#include "OSCLib/SDCLibrary.h"
#include "OSCLib/Data/SDC/MDIB/ChannelDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/MdDescription.h"
#include "OSCLib/Data/SDC/MDIB/MdState.h"
#include "OSCLib/Data/SDC/MDIB/Mdib.h"
#include "OSCLib/Data/SDC/MDIB/VmdDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/MdsDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/CodedValue.h"
#include "OSCLib/Data/SDC/MDIB/NumericMetricDescriptor.h"


#include "OSCLib/Data/SDC/SDCConsumer.h"
#include "OSCLib/Data/SDC/SDCProvider.h"

#include "Tools/HelperMethods.h"
#include "Tools/TestProviderHandleNames.h"
#include "Tools/StateHandler/NumericMetricStateGetHandler.h"
#include "Tools/StateHandler/NumericMetricStateSetHandler.h"
#include "Tools/TestConsumer.h"

#include "OSELib/SDC/ServiceManager.h"

using namespace SDCLib;
using namespace SDCLib::Data::SDC;

class ProviderWithoutSafetyClassification : public Util::Task {
public:
	ProviderWithoutSafetyClassification():
		sdcProvider(),
		nmsSetHandler(TestTools::HANDLE_SET_NUMERIC_METRIC),
		nmsGetHandler(TestTools::HANDLE_GET_NUMERIC_METRIC),
		nmsSetDescriptor(TestTools::HANDLE_SET_NUMERIC_METRIC,
				CodedValue("MDCX_EXAMPLE_SET"),
				MetricCategory::Set,
				MetricAvailability::Cont,
				1.0),
		nmsGetDescriptor(TestTools::HANDLE_GET_NUMERIC_METRIC,
				CodedValue("MDCX_EXAMPLE_GET"),
				MetricCategory::Set,
				MetricAvailability::Cont,
				1)
		{

		//Channel
		ChannelDescriptor deviceParameters("d");
		deviceParameters.addMetric(nmsSetDescriptor)
						.addMetric(nmsGetDescriptor);

		//VMD
		VmdDescriptor deviceModule(TestTools::VMD_DESCRIPTOR_HANDLE);
		deviceModule.addChannel(deviceParameters);

		//MDS
		MdsDescriptor deviceSystem(TestTools::MDS_DESCRIPTOR_HANDLE);
		deviceSystem.addVmd(deviceModule);

		sdcProvider.createSetOperationForDescriptor(nmsSetDescriptor, deviceSystem);

		MdDescription mdDescription;
		mdDescription.addMdsDescriptor(deviceSystem);

		sdcProvider.setMdDescription(mdDescription);

		sdcProvider.addMdStateHandler(&nmsSetHandler);
		sdcProvider.addMdStateHandler(&nmsGetHandler);

		sdcProvider.addHandleForPeriodicEvent(TestTools::HANDLE_SET_NUMERIC_METRIC);

		sdcProvider.setEndpointReference(TestTools::DEFAULT_TEST_DEVICE_EPR);
	}

	~ProviderWithoutSafetyClassification() {
		shutdown();
	}

	void setPort(int port) {
		//Network configuration
		MDPWSTransportLayerConfiguration providerConfig = MDPWSTransportLayerConfiguration();
		providerConfig.setPort(port);
		sdcProvider.setConfiguration(providerConfig);
	}

	void startup() {
		sdcProvider.startup();
	}

	void shutdown() {
		sdcProvider.shutdown();
	}

	void runImpl() {
		while (!isInterrupted()) {
			{
			}
			Poco::Thread::sleep(1000);
		}
	}

	MdibContainer getMdib() {
		return sdcProvider.getMdib();
	}

	MdDescription getMdDscription()
	{
		return sdcProvider.getMdDescription();
	}

	MdState getMdState()
	{
		return sdcProvider.getMdState();
	}

private:
		SDCProvider sdcProvider;

		TestTools::NumericMetricStateSetHandler nmsSetHandler;
		TestTools::NumericMetricStateGetHandler nmsGetHandler;
	    NumericMetricDescriptor nmsSetDescriptor;
		NumericMetricDescriptor nmsGetDescriptor;



};


int main() {
	std::cout << "Test against requirement 11073-20701-R0029: An SDC SERVICE CONSUMER SHALL "
			  << "not invoke a REQUEST-RESPONSE SERVICE OPERATION associated with a "
			  << "pm:AbstractOperationDescriptor that does not contain specific "
			  << "pm:AbstractOperationDescriptor/@SafetyClassification."
			  << std::endl;

	SDCLibrary::getInstance().startup(OSELib::LogLevel::Error);
	SDCLibrary::getInstance().setIP6enabled(false);
	SDCLibrary::getInstance().setIP4enabled(true);

	ProviderWithoutSafetyClassification provider;
	provider.setPort(TestTools::getFreePort());
	provider.startup();
	provider.start();

	//Discovery
	TestTools::TestConsumer consumer;
	consumer.start();

	OSELib::SDC::ServiceManager oscpsm;
	// binding to a custom port
	MDPWSTransportLayerConfiguration config = MDPWSTransportLayerConfiguration();
	config.setPort(TestTools::getFreePort());
	std::unique_ptr<Data::SDC::SDCConsumer> c(oscpsm.discoverEndpointReference(TestTools::DEFAULT_TEST_DEVICE_EPR, config));

	if (c != nullptr) {
		consumer.setConsumer(std::move(c));

		consumer.registerNumericMetricStateSetHandler();
		int testValue = 2;
		consumer.setNumericMetricStateValue(testValue);
		std::cout << TestTools::getStringRepresentationOfMDIB(provider.getMdib());
		if (testValue == provider.getMdState().findState<NumericMetricState>(TestTools::HANDLE_SET_NUMERIC_METRIC)->getMetricValue().getValue()) {
			std::cout << std::endl << "SetNumericMetricValue as RequestResponse example was successful, even though no safety information was provided." << std::endl;
			std::cout << "Test failed";
		}
		else {
			std::cout << "Test passed";
		}
		Poco::Thread::sleep(2000);
		consumer.unregisterNumericMetricStateSetHandler();

		consumer.disconnect();
	}

	provider.shutdown();
	SDCLibrary::getInstance().shutdown();


}

