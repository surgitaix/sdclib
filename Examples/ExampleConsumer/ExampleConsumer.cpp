/**
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  *
  */

/*
 * ExampleConsumer.cpp
 *
 *  @Copyright (C) 2018, SurgiTAIX AG
 *  Author: buerger
 *
 *  This example demonstrates how to set up a very simple SDCConsumer. It connects to the ExampleProvider defined with it's endpoint reference (EPR).
 *  A state handler is facilitated to utilize the eventing mechanism for a numeric metric state.
 *
 */



#include "SDCLib/SDCLibrary.h"
#include "SDCLib/Data/SDC/SDCConsumer.h"
#include "SDCLib/Data/SDC/SDCConsumerConnectionLostHandler.h"
#include "SDCLib/Data/SDC/SDCConsumerMDStateHandler.h"
#include "SDCLib/Data/SDC/MDIB/MdsDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/MetricQuality.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricState.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricValue.h"
#include "SDCLib/Data/SDC/MDIB/RealTimeSampleArrayMetricState.h"
#include "SDCLib/Data/SDC/MDIB/SampleArrayValue.h"
#include "SDCLib/Data/SDC/MDIB/LocationContextState.h"
#include "SDCLib/Data/SDC/MDIB/LocationDetail.h"
#include "SDCLib/Data/SDC/MDIB/AlertSignalState.h"
#include "SDCLib/Data/SDC/MDIB/custom/OperationInvocationContext.h"
#include "SDCLib/Data/SDC/FutureInvocationState.h"
#include "SDCLib/Util/DebugOut.h"

#include "OSELib/SDC/ServiceManager.h"

#include "OSELib/TCP/TCPClientEventHandler.h"

using namespace SDCLib;
using namespace SDCLib::Util;
using namespace SDCLib::Data::SDC;

//SDCLib/C
const std::string deviceEPR("UDI-1234567890");
const std::string HANDLE_SET_METRIC("handle_set");
const std::string HANDLE_GET_METRIC("handle_get");
const std::string HANDLE_STREAM_METRIC("handle_stream");




class ExampleConsumerEventHandler : public SDCConsumerMDStateHandler<NumericMetricState> {
public:
    ExampleConsumerEventHandler(const std::string & handle) : SDCConsumerMDStateHandler(handle),
    	currentWeight(0)
	{
    }


    void onStateChanged(const NumericMetricState & state) override {
        double val = state.getMetricValue().getValue();
        DebugOut(DebugOut::Default, "ExampleConsumer") << "Consumer: Received value changed of " << this->getDescriptorHandle() << ": " << val << std::endl;
        currentWeight = (float)val;
    }

    void onOperationInvoked(const OperationInvocationContext & oic, InvocationState is) override {
        DebugOut(DebugOut::Default, "ExampleConsumer") << "Consumer: Received operation invoked (numeric metric) (ID, STATE) of " << this->getDescriptorHandle() << ": " << oic.transactionId << ", " << Data::SDC::EnumToString::convert(is) << std::endl;
    }

    float getCurrentWeight() {
        return currentWeight;
    }

private:
    float currentWeight;
};


// state handler for array values, uses udp instead of tcp. Faster. Considered for real time applications
class StreamConsumerStateHandler : public SDCConsumerMDStateHandler<RealTimeSampleArrayMetricState> {
public:
	StreamConsumerStateHandler(std::string descriptorHandle) : SDCConsumerMDStateHandler(descriptorHandle) {}

	void onStateChanged(const RealTimeSampleArrayMetricState & state) override {
		std::vector<double> values = state.getMetricValue().getSamples();

		// simple check if the data is valid:
		// assumption: sequence of values, increased by 1

		std::string out("Content: ");
		DebugOut(DebugOut::Default, "ExampleConsumer") << "Received chunk! Handle: " << state.getDescriptorHandle() << std::endl;
		for (size_t i = 0; i < values.size(); i++) {
			out.append(" " + std::to_string(values[i]));
		}
		DebugOut(DebugOut::Default, "ExampleConsumer") << out;
	}
};




void waitForUserInput() {
	std::string temp;
	Util::DebugOut(Util::DebugOut::Default, "") << "Press key to proceed.";
	std::cin >> temp;
}




int main() {
	Util::DebugOut(Util::DebugOut::Default, "ExampleConsumer") << "Startup";
    SDCLibrary::getInstance().startup(OSELib::LogLevel::None);
	SDCLibrary::getInstance().setPortStart(12000);


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

    // Create a new SDCInstance (no flag will auto init)
    auto t_SDCInstance = std::make_shared<SDCInstance>(Config::SDC_DEFAULT_MDPWS_PORT, true);
    // Some restriction
    t_SDCInstance->setIP6enabled(false);
    t_SDCInstance->setIP4enabled(true);
    // Bind it to interface that matches the internal criteria (usually the first enumerated)
    if(!t_SDCInstance->bindToDefaultNetworkInterface()) {
        std::cout << "Failed to bind to default network interface! Exit..." << std::endl;
        return -1;
    }

	// Discovery
	OSELib::SDC::ServiceManager t_serviceManager(t_SDCInstance);


	std::unique_ptr<Data::SDC::SDCConsumer> c(t_serviceManager.discoverEndpointReference(deviceEPR));
//	auto c(t_serviceManager.discover());

	// state handler
	auto eh_get = std::make_shared<ExampleConsumerEventHandler>(HANDLE_GET_METRIC);
	auto eh_set = std::make_shared<ExampleConsumerEventHandler>(HANDLE_SET_METRIC);
	auto eh_stream = std::make_shared<StreamConsumerStateHandler>(HANDLE_STREAM_METRIC);

	try {
		if (c != nullptr) {
//		if (c[0] != nullptr) {
//			Data::SDC::SDCConsumer & consumer = *c[0];
			Data::SDC::SDCConsumer & consumer = *c;
			std::unique_ptr<MyConnectionLostHandler> myHandler(new MyConnectionLostHandler(consumer));
			consumer.setConnectionLostHandler(myHandler.get());

			consumer.registerStateEventHandler(eh_get.get());
			consumer.registerStateEventHandler(eh_set.get());
			consumer.registerStateEventHandler(eh_stream.get());

			Util::DebugOut(Util::DebugOut::Default, "ExampleConsumer") << "Discovery succeeded." << std::endl << std::endl << "Waiting 5 sec. for the subscriptions to beeing finished";

			// wait for the subscriptions to be completed
			Poco::Thread::sleep(5000);

			std::unique_ptr<NumericMetricState> pGetMetricState(consumer.requestState<NumericMetricState>(HANDLE_GET_METRIC));
			Util::DebugOut(Util::DebugOut::Default, "ExampleConsumer") << "Requested get metrics value: " << pGetMetricState->getMetricValue().getValue();

			// set numeric metric
			std::unique_ptr<NumericMetricState> pMetricState(consumer.requestState<NumericMetricState>(HANDLE_SET_METRIC));
			pMetricState->setMetricValue(NumericMetricValue(MetricQuality(MeasurementValidity::Vld)).setValue(10));

			FutureInvocationState fis;
			consumer.commitState(*pMetricState, fis);
			Util::DebugOut(Util::DebugOut::Default, "ExampleConsumer") << "Commit result metric state: " << fis.waitReceived(InvocationState::Fin, 10000);

			waitForUserInput();
			consumer.unregisterStateEventHandler(eh_get.get());
			consumer.unregisterStateEventHandler(eh_set.get());
			consumer.unregisterStateEventHandler(eh_stream.get());
			consumer.disconnect();
		} else {
			Util::DebugOut(Util::DebugOut::Default, "ExampleConsumer") << "Discovery failed.";
		}

	} catch (std::exception & e){
		Util::DebugOut(Util::DebugOut::Default, "ExampleConsumer") << "Exception: " << e.what() << std::endl;
	}
    SDCLibrary::getInstance().shutdown();
    Util::DebugOut(Util::DebugOut::Default, "ExampleConsumer") << "Shutdown." << std::endl;
}
