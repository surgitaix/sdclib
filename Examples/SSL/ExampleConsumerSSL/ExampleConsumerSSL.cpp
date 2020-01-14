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

const std::string DEVICE_EPR{"UDI-ExampleProvider"};
const std::string HANDLE_SET_METRIC{"handle_set"};
const std::string HANDLE_GET_METRIC{"handle_get"};
const std::string HANDLE_STREAM_METRIC{"handle_stream"};

class ExampleConsumerEventHandler : public SDCConsumerMDStateHandler<NumericMetricState>
{
private:
    double currentWeight{0};

public:
    ExampleConsumerEventHandler(std::string p_descriptorHandle)
	: SDCConsumerMDStateHandler(p_descriptorHandle)
	{ }

    void onStateChanged(const NumericMetricState& p_changedState) override
    {
        auto t_newValue{p_changedState.getMetricValue().getValue()};
        DebugOut(DebugOut::Default, "ExampleConsumer") << "Consumer: Received value changed of " << getDescriptorHandle() << ": " << t_newValue << std::endl;
        currentWeight = t_newValue;
    }

    void onOperationInvoked(const OperationInvocationContext& oic, InvocationState p_is) override
    {
        DebugOut(DebugOut::Default, "ExampleConsumer") << "Consumer: Received operation invoked (numeric metric) (ID, STATE) of " << getDescriptorHandle() << ": " << oic.transactionId << ", " << Data::SDC::EnumToString::convert(p_is) << std::endl;
    }

    double getCurrentWeight() const
    {
        return currentWeight;
    }
};


// state handler for array values, uses udp instead of tcp. Faster. Considered for real time applications
class StreamConsumerStateHandler : public SDCConsumerMDStateHandler<RealTimeSampleArrayMetricState>
{
public:
	StreamConsumerStateHandler(std::string p_descriptorHandle)
	: SDCConsumerMDStateHandler(p_descriptorHandle)
	{ }

	void onStateChanged(const RealTimeSampleArrayMetricState& p_changedState) override
	{
		std::vector<double> t_sampleValues = p_changedState.getMetricValue().getSamples();

		DebugOut(DebugOut::Default, "ExampleConsumer") << "Received chunk! Handle: " << p_changedState.getDescriptorHandle() << std::endl;
		std::string out("Content: ");
		for (const auto t_value : t_sampleValues)
		{
			out.append(" " + std::to_string(t_value));
		}
		DebugOut(DebugOut::Default, "ExampleConsumer") << out;
	}
};



void waitForUserInput() {
	std::string temp;
	Util::DebugOut(Util::DebugOut::Default, "ExampleConsumerSSL") << "Press key to proceed.";
	std::cin >> temp;
}

class MyConnectionLostHandler : public Data::SDC::SDCConsumerConnectionLostHandler
{
public:
	MyConnectionLostHandler(Data::SDC::SDCConsumer& p_consumer)
	: m_consumer(p_consumer)
	{ }
	void onConnectionLost() override
	{
		std::cerr << "Connection lost, disconnecting... ";
		m_consumer.disconnect();
		std::cerr << "Disconnected. Press key to proceed." << std::endl;
	}
private:
	Data::SDC::SDCConsumer& m_consumer;
};


int main()
{
	Util::DebugOut(Util::DebugOut::Default, "ExampleConsumerSSL") << "Startup";
    SDCLibrary::getInstance().startup(OSELib::LogLevel::Warning);

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
    // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // <SSL> ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    // Init SSL (Default Params should be fine)
    if(!t_SDCInstance->initSSL()) {
        std::cout << "Failed to init SSL!" << std::endl;
        return -1;
    }
    // Configure SSL
    auto t_SSLConfig = t_SDCInstance->getSSLConfig();
    t_SSLConfig->addCertificateAuthority("rootCA.pem");
    t_SSLConfig->useCertificate("leaf.pem");
    t_SSLConfig->useKeyFiles(/*Public Key*/"", "leafkey.pem", ""/* Password for Private Keyfile */);

    // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // </SSL> +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	// Discovery
	OSELib::SDC::ServiceManager t_serviceManager(t_SDCInstance);

	// Note: Calculate a UUIDv5 and apply prefix to it!
	auto t_consumer{t_serviceManager.discoverEndpointReference(SDCInstance::calcUUIDv5(DEVICE_EPR, true))};

	try
	{
		// Connected to Provider?
		if (t_consumer != nullptr)
		{
			// Get notified on Lost Connection
			std::unique_ptr<MyConnectionLostHandler> myHandler(new MyConnectionLostHandler(*t_consumer));
			t_consumer->setConnectionLostHandler(myHandler.get());

			// Create StateEventHandler to "Consume" Events from Provider
			auto eh_get = std::make_shared<ExampleConsumerEventHandler>(HANDLE_GET_METRIC);
			auto eh_set = std::make_shared<ExampleConsumerEventHandler>(HANDLE_SET_METRIC);
			auto eh_stream = std::make_shared<StreamConsumerStateHandler>(HANDLE_STREAM_METRIC);

			// Register StateEventHandlers to get updates
			t_consumer->registerStateEventHandler(eh_get.get());
			t_consumer->registerStateEventHandler(eh_set.get());
			t_consumer->registerStateEventHandler(eh_stream.get());

			// Simple Test(1):
			// Search for the "Get"-State
			auto t_getMetricState{t_consumer->requestState<NumericMetricState>(HANDLE_GET_METRIC)};
			// If found: Print the current(!) value
			if(t_getMetricState)
			{
				Util::DebugOut(Util::DebugOut::Default, "ExampleConsumer") << "Requested get metrics value: " << t_getMetricState->getMetricValue().getValue();
			}

			// Simple Test(2):
			// Search for the "Set"-State
			auto t_setMetricState{t_consumer->requestState<NumericMetricState>(HANDLE_SET_METRIC)};
			// If found: Set it to a given value
			if(t_setMetricState)
			{
				double t_newValue{10.0};
				// Use the returned state, set the value and "commit" it
				t_setMetricState->setMetricValue(NumericMetricValue{MetricQuality{MeasurementValidity::Vld}}.setValue(t_newValue));
				// Now
				FutureInvocationState fis;
				t_consumer->commitState(*t_setMetricState, fis);
				// Now wait for "InvocationState::Fin" (=> Success)
				Util::DebugOut(Util::DebugOut::Default, "ExampleConsumer") << "Commit result metric state: " << fis.waitReceived(InvocationState::Fin, 2000);
			}

			// From here on the registered StateEventHandlers (SDCLib Threads / background) will provide information
			// on "state changes" until the user enters a key ("waitForUserInput") or exception is thrown.
			waitForUserInput();
			// Unregister and disconnect
			t_consumer->unregisterStateEventHandler(eh_get.get());
			t_consumer->unregisterStateEventHandler(eh_set.get());
			t_consumer->unregisterStateEventHandler(eh_stream.get());
			t_consumer->disconnect();
		}
		else
		{
			// Something went wrong -> Exit!
			Util::DebugOut(Util::DebugOut::Default, "ExampleConsumer") << "Discovery failed.";
		}
	}
	catch (std::exception& e)
	{
		Util::DebugOut(Util::DebugOut::Default, "ExampleConsumer") << "Exception: " << e.what() << std::endl;
	}

	Util::DebugOut(Util::DebugOut::Default, "ExampleConsumer") << "Shutdown." << std::endl;
	return 0;
}
