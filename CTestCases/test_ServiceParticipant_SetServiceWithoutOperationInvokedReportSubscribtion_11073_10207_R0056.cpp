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

#include "Tools/TestProvider.h"

const std::string DEVICE_EPR("TestProvider");
const std::string HANDLE_SET_NUMERICMETRIC("handle_set_numericmetric");


using namespace SDCLib;
using namespace SDCLib::Util;
using namespace SDCLib::Data::SDC;


class SettableConsumerNumericMetricStateHandler : public SDCConsumerMDStateHandler<NumericMetricState>
{
public:
	SettableConsumerNumericMetricStateHandler(std::string descriptionHandler) : SDCConsumerMDStateHandler(descriptionHandler) {
	}

	void onStateChanged(const NumericMetricState &state) override{
		Util::DebugOut(Util::DebugOut::Default, "PeriodicEvents") << "Received periodic state of " << descriptorHandle << " " <<  state.getMetricValue().getValue() << std::endl;
	}

};


int main() {
	std::cout << "Test against requirement R0056  A SERVICE CONSUMER SHALL subscribe to msg:OperationInvokedReport"
			  << " before invoking request-response SERVICE OPERATIONs of the SET SERVICE" << std::endl;

	SDCLibrary::getInstance().startup(OSELib::LogLevel::Notice);
	SDCLibrary::getInstance().setIP6enabled(false);
	SDCLibrary::getInstance().setIP4enabled(true);

	TestTools::TestProvider provider;
	provider.startup();
	provider.start();

	class MyConnectionLostHandler : public Data::SDC::SDCConsumerConnectionLostHandler {
	public:
	 	MyConnectionLostHandler(Data::SDC::SDCConsumer & consumer) : consumer(consumer) {
	  	}
	  	void onConnectionLost() override {
	   		std::cerr << "Connection lost, disconnecting... ";
	 		consumer.disconnect();
	   		std::cerr << "disconnected." << std::endl;
	   	}
	private:
	   	Data::SDC::SDCConsumer & consumer;
	};

	//Discovery
	OSELib::SDC::ServiceManager oscpsm;
	// binding to a custom port
	MDPWSTransportLayerConfiguration config = MDPWSTransportLayerConfiguration();
	config.setPort(6467);

	std::unique_ptr<Data::SDC::SDCConsumer> c(oscpsm.discoverEndpointReference(DEVICE_EPR, config));

	std::shared_ptr<SettableConsumerNumericMetricStateHandler> setHandler(new SettableConsumerNumericMetricStateHandler(HANDLE_SET_NUMERICMETRIC));


	if (c != nullptr) {
		Data::SDC::SDCConsumer & consumer = *c;
		std::unique_ptr<MyConnectionLostHandler> myHandler(new MyConnectionLostHandler(consumer));
		consumer.setConnectionLostHandler(myHandler.get());

		SettableConsumerNumericMetricStateHandler settableNumicMetricStateHandler(HANDLE_SET_NUMERICMETRIC);

		consumer.registerStateEventHandler(setHandler.get());

		std::unique_ptr<NumericMetricState> setNumericMetricState(consumer.requestState<NumericMetricState>(HANDLE_SET_NUMERICMETRIC));
		setNumericMetricState->setMetricValue(NumericMetricValue(MetricQuality(MeasurementValidity::Vld)).setValue(1.0));
		FutureInvocationState fis;
		consumer.commitState(*setNumericMetricState, fis);
		Util::DebugOut(Util::DebugOut::Default, "Consumer") << "Commit result: " << fis.waitReceived(InvocationState::Fin, 10000);


		Poco::Thread::sleep(2000);
		consumer.unregisterStateEventHandler(setHandler.get());

		consumer.disconnect();
	}

	provider.shutdown();
	SDCLibrary::getInstance().shutdown();
}
