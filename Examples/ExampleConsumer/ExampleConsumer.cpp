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
#include "SDCLib/Data/SDC/MDIB/MetricQuality.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricState.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricValue.h"
#include "SDCLib/Data/SDC/MDIB/RealTimeSampleArrayMetricState.h"
#include "SDCLib/Data/SDC/MDIB/SampleArrayValue.h"
#include "SDCLib/Data/SDC/MDIB/custom/OperationInvocationContext.h"
#include "SDCLib/Data/SDC/FutureInvocationState.h"
#include "SDCLib/Util/DebugOut.h"

#include "OSELib/SDC/ServiceManager.h"

using namespace SDCLib;
using namespace SDCLib::Util;
using namespace SDCLib::Data::SDC;

//SDCLib/C
const std::string deviceEPR("UDI-ExampleProvider");
const std::string HANDLE_SET_METRIC("handle_set");
const std::string HANDLE_GET_METRIC("handle_get");
const std::string HANDLE_STREAM_METRIC("handle_stream");




class ExampleConsumerEventHandler : public SDCConsumerMDStateHandler<NumericMetricState>
{
private:
    double currentWeight = 0;

public:
    ExampleConsumerEventHandler(const std::string & handle)
	: SDCConsumerMDStateHandler(handle)
	{ }

    void onStateChanged(const NumericMetricState & state) override {
        double t_value = state.getMetricValue().getValue();
        DebugOut(DebugOut::Default, "ExampleConsumer") << "Consumer: Received value changed of " << this->getDescriptorHandle() << ": " << t_value << std::endl;
        currentWeight = t_value;
    }

    void onOperationInvoked(const OperationInvocationContext & oic, InvocationState is) override {
        DebugOut(DebugOut::Default, "ExampleConsumer") << "Consumer: Received operation invoked (numeric metric) (ID, STATE) of " << this->getDescriptorHandle() << ": " << oic.transactionId << ", " << Data::SDC::EnumToString::convert(is) << std::endl;
    }

    double getCurrentWeight() {
        return currentWeight;
    }
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
	Util::DebugOut(Util::DebugOut::Default, "") << "Press key to proceed.";
	std::cin.get();
}




int main()
{
	Util::DebugOut(Util::DebugOut::Default, "ExampleConsumer") << "Startup";
    SDCLibrary::getInstance().startup(OSELib::LogLevel::Warning);

    class MyConnectionLostHandler : public Data::SDC::SDCConsumerConnectionLostHandler {
    public:
    	MyConnectionLostHandler(Data::SDC::SDCConsumer & consumer) : consumer(consumer) {
    	}
    	void onConnectionLost() override {
    		std::cerr << "Connection lost, disconnecting... ";
    		consumer.disconnect();
    		std::cerr << "Disconnected. Press key to proceed." << std::endl;
    	}
    private:
    	Data::SDC::SDCConsumer & consumer;
    };

    // Create a new SDCInstance (no flag will auto init)
    auto t_SDCInstance = std::make_shared<SDCInstance>(true);
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

	// Note: Calculate a UUIDv5 and apply prefix to it!
	auto t_consumer(t_serviceManager.discoverEndpointReference(SDCInstance::calcUUIDv5(deviceEPR, true)));

	// state handler
	auto eh_get = std::make_shared<ExampleConsumerEventHandler>(HANDLE_GET_METRIC);
	auto eh_set = std::make_shared<ExampleConsumerEventHandler>(HANDLE_SET_METRIC);
	auto eh_stream = std::make_shared<StreamConsumerStateHandler>(HANDLE_STREAM_METRIC);

	try {
		if (t_consumer != nullptr) {
			std::unique_ptr<MyConnectionLostHandler> myHandler(new MyConnectionLostHandler(*t_consumer));
			t_consumer->setConnectionLostHandler(myHandler.get());

			t_consumer->registerStateEventHandler(eh_get.get());
			t_consumer->registerStateEventHandler(eh_set.get());
			t_consumer->registerStateEventHandler(eh_stream.get());

			Util::DebugOut(Util::DebugOut::Default, "ExampleConsumer") << "Discovery succeeded." << std::endl << std::endl << "Waiting 5 sec. for the subscriptions to beeing finished";

			// wait for the subscriptions to be completed
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));

			auto t_getMetricState(t_consumer->requestState<NumericMetricState>(HANDLE_GET_METRIC));
			if(t_getMetricState) {
				Util::DebugOut(Util::DebugOut::Default, "ExampleConsumer") << "Requested get metrics value: " << t_getMetricState->getMetricValue().getValue();
			}

			// set numeric metric
			auto t_setMetricState(t_consumer->requestState<NumericMetricState>(HANDLE_SET_METRIC));
			if(t_setMetricState) {
				t_setMetricState->setMetricValue(NumericMetricValue(MetricQuality(MeasurementValidity::Vld)).setValue(10));
				FutureInvocationState fis;
				t_consumer->commitState(*t_setMetricState, fis);
				Util::DebugOut(Util::DebugOut::Default, "ExampleConsumer") << "Commit result metric state: " << fis.waitReceived(InvocationState::Fin, 10000);
			}
			waitForUserInput();
			t_consumer->unregisterStateEventHandler(eh_get.get());
			t_consumer->unregisterStateEventHandler(eh_set.get());
			t_consumer->unregisterStateEventHandler(eh_stream.get());
			t_consumer->disconnect();
		} else {
			Util::DebugOut(Util::DebugOut::Default, "ExampleConsumer") << "Discovery failed.";
		}

	} catch (std::exception & e){
		Util::DebugOut(Util::DebugOut::Default, "ExampleConsumer") << "Exception: " << e.what() << std::endl;
	}
    SDCLibrary::getInstance().shutdown();
    Util::DebugOut(Util::DebugOut::Default, "ExampleConsumer") << "Shutdown." << std::endl;
}
