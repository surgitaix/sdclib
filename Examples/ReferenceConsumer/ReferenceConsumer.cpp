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
 * ReferenceConsumer.cpp
 *
 *  @Copyright (C) 2018, SurgiTAIX AG
 *  Author: baumeister, rosenau
 *
 *  This example demonstrates how to set up a very simple SDCConsumer. It connects to the ExampleProvider defined with it's endpoint reference (EPR).
 *  A state handler is facilitated to utilize the eventing mechanism for a numeric metric state.
 *
 */

#include <chrono>
#include <atomic>

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
#include "SDCLib/Data/SDC/MDIB/AlertConditionState.h"
#include "SDCLib/Data/SDC/MDIB/AlertSignalState.h"
#include "SDCLib/Data/SDC/MDIB/StringMetricState.h"
#include "SDCLib/Data/SDC/MDIB/StringMetricValue.h"
#include "SDCLib/Data/SDC/MDIB/PatientContextState.h"
#include "SDCLib/Data/SDC/MDIB/LocationContextState.h"
#include "SDCLib/Data/SDC/MDIB/EnumStringMetricState.h"
#include "SDCLib/Data/SDC/FutureInvocationState.h"
#include "SDCLib/Util/DebugOut.h"
#include "SDCLib/Data/SDC/MDIB/ScoDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/VmdDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/SetStringOperationDescriptor.h"

#include "OSELib/SDC/ServiceManager.h"

using namespace SDCLib;
using namespace SDCLib::Util;
using namespace SDCLib::Data::SDC;

const std::string HANDLE_STATIC_GET_NM{"numeric.ch0.vmd0"};
const std::string HANDLE_DYNAMIC_GET_NM{"numeric.ch1.vmd0"};
const std::string HANDLE_SET_NM{"numeric.ch0.vmd1"};
const std::string HANDLE_STATIC_GET_STRM{"string.ch0.vmd0"};
const std::string HANDLE_SET_STRM{"string.ch0.vmd1"};
const std::string HANDLE_STATIC_GET_ESTRM{"enumstring.ch0.vmd0"};
const std::string HANDLE_DYNAMIC_GET_ESTRM{"enumstring2.ch0.vmd0"};
const std::string HANDLE_SET_ESTRM{"enumstring.ch0.vmd1"};

const std::string HANDLE_ALERTSIGNAL_MDS{"as0.mds0"};
const std::string HANDLE_ALERTSIGNAL_VMD{"as0.vmd0.mds0"};
const std::string HANDLE_ALERTCONDITION_MDS{"ac0.mds0"};
const std::string HANDLE_ALERTCONDITION_VMD{"ac0.vmd0.mds0"};

const std::string HANDLE_ACTIVATE_MDS{"actop.mds0_sco_0"};
const std::string HANDLE_ACTIVATE_VMD{"actop.vmd1_sco_0"};
const std::string HANDLE_STREAM{""};


class NumericMetricEventHandler : public SDCConsumerMDStateHandler<NumericMetricState>
{
private:
    std::atomic<double> m_currentWeight{0};
    std::atomic<int> m_timesValueChanged{0};

public:
    NumericMetricEventHandler(std::string p_descriptorHandle)
	: SDCConsumerMDStateHandler(p_descriptorHandle)
	{ }

    void onStateChanged(const NumericMetricState& p_changedState) override
    {
        auto t_newValue{p_changedState.getMetricValue().getValue()};
        DebugOut(DebugOut::Default, "ReferenceConsumer") << "Consumer: Received value changed of " << getDescriptorHandle() << ": " << t_newValue << std::endl;
        if(m_currentWeight != t_newValue)
        {
        	m_timesValueChanged++;
        }
        m_currentWeight = t_newValue;
    }

    void onOperationInvoked(const OperationInvocationContext& oic, InvocationState p_is) override
    {
        DebugOut(DebugOut::Default, "ReferenceConsumer") << "Consumer: Received operation invoked (numeric metric) (ID, STATE) of " << getDescriptorHandle() << ": " << oic.transactionId << ", " << Data::SDC::EnumToString::convert(p_is) << std::endl;
    }

    double getCurrentWeight() const
    {
        return m_currentWeight;
    }

    double getTimesValueChanged() const
    {
    	return m_timesValueChanged;
    }
};


class StringMetricEventHandler : public SDCConsumerMDStateHandler<StringMetricState>
{
public:
	std::string currentValue{};
	StringMetricEventHandler(std::string p_descriptorHandle)
	: SDCConsumerMDStateHandler(p_descriptorHandle)
	{}

	void onStateChanged(const StringMetricState& p_changedState) override
	{
		currentValue = p_changedState.getMetricValue().getValue();
	}

	const std::string getCurrentString()
	{
		return currentValue;
	}

};


class EnumStringEventHandler : public SDCConsumerMDStateHandler<EnumStringMetricState>
{
public:
	EnumStringEventHandler(std::string p_descriptorHandle)
	: SDCConsumerMDStateHandler(p_descriptorHandle)
	{ }

	void onStateChanged(const EnumStringMetricState& p_changedState) override
	{
		currentValue = p_changedState.getMetricValue().getValue();
	}

	const std::string getCurrentString()
	{
		return currentValue;
	}
private:
	std::string currentValue{};
};


class AlertConditionEventHandler : public SDCConsumerMDStateHandler<AlertConditionState>
{
public:
	AlertConditionEventHandler(std::string p_descriptorHandle)
	: SDCConsumerMDStateHandler(p_descriptorHandle)
	{}

	void onStateChanged(const AlertConditionState& p_changedState) override
	{
		DebugOut(DebugOut::Default, "ReferenceConsumer") << EnumToString::convert(p_changedState.getActivationState()) << std::endl;
		if(p_changedState.hasPresence())
		{
			auto t_newValue = p_changedState.getPresence();
			if(m_presence != t_newValue)
			{
				m_timesValueChanged++;
			}
			m_presence = t_newValue;
		}
	}

	int getTimesValueChanged() const
	{
		DebugOut(DebugOut::Default, "ReferenceConsumer") << getDescriptorHandle() << " " << m_timesValueChanged << "\n";
		return m_timesValueChanged;
	}
private:
	bool m_presence{false};
	std::atomic<int> m_timesValueChanged{0};

};


class AlertSignalEventHandler : public SDCConsumerMDStateHandler<AlertSignalState>
{
public:
	AlertSignalEventHandler(std::string p_descriptorHandle)
	: SDCConsumerMDStateHandler(p_descriptorHandle)
	{}

	void onStateChanged(const AlertSignalState& p_changedState) override
	{
		if(p_changedState.hasPresence())
			DebugOut(DebugOut::Default, "ReferenceConsumer") << getDescriptorHandle() << " alert presence changed to: " << EnumToString::convert(p_changedState.getPresence()) << "\n";
		{
			auto t_newValue = p_changedState.getPresence();
			if(t_newValue != m_presence)
			{
				m_timesValueChanged++;
			}
			m_presence = t_newValue;
		}
	}

	int getTimesValueChanged() const
	{
		DebugOut(DebugOut::Default, "ReferenceConsumer") << getDescriptorHandle() << " " << m_timesValueChanged << "\n";
		return m_timesValueChanged;
	}
private:
	AlertSignalPresence m_presence{AlertSignalPresence::Off};
	std::atomic<int> m_timesValueChanged{0};
};


// state handler for array values, uses udp instead of tcp. Faster. Considered for real time applications
class StreamConsumerEventHandler : public SDCConsumerMDStateHandler<RealTimeSampleArrayMetricState>
{
public:
	StreamConsumerEventHandler(std::string p_descriptorHandle)
	: SDCConsumerMDStateHandler(p_descriptorHandle)
	{ }

	void onStateChanged(const RealTimeSampleArrayMetricState& p_changedState) override
	{
		std::vector<double> t_sampleValues = p_changedState.getMetricValue().getSamples();

		DebugOut(DebugOut::Default, "ReferenceConsumer") << "Received chunk! Handle: " << p_changedState.getDescriptorHandle() << std::endl;
		std::string out("Content: ");
		for (const auto t_value : t_sampleValues)
		{
			out.append(" " + std::to_string(t_value));
		}
		DebugOut(DebugOut::Default, "ReferenceConsumer") << out;
	}
};


void waitForUserInput() {
	std::string temp;
	Util::DebugOut(Util::DebugOut::Default, "ReferenceConsumerSSL") << "Press key to proceed.";
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


bool ends_with(const std::string & value, const std::string & ending)
{
    if (ending.size() > value.size())
	{
    	return false;
	}
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}


int main(int argc, char *argv[])
{
	DebugOut::DEBUG_LEVEL = DebugOut::Silent;

	bool useTLS = false;
	std::string endpointEnding{""};


	for(int i = 0; i < argc; i++)
	{
		if (std::string{argv[i]} == "-tls")
		{
			useTLS = true;
		}
		if (std::string{argv[i]} == "-epr")
		{
			if(i == argc-1)
			{
				std::cout << "please provide an endpoint";
				return -1;
			}
			else
			{
				endpointEnding = std::string{argv[i+1]};
			}
		}
	}



	Util::DebugOut(Util::DebugOut::Default, "ReferenceConsumerSSL") << "Startup";
    SDCLibrary::getInstance().startup(OSELib::LogLevel::None);

    // Create a new SDCInstance (no flag will auto init)
    auto t_SDCInstance = std::make_shared<SDCInstance>(true);
    // Some restriction
    t_SDCInstance->setIP6enabled(false);
    t_SDCInstance->setIP4enabled(true);
    // Bind it to interface that matches the internal criteria (usually the first enumerated)
    if(!t_SDCInstance->bindToDefaultNetworkInterface()) {
        DebugOut(DebugOut::Default, "ReferenceConsumer") << "Failed to bind to default network interface! Exit..." << std::endl;
        return -1;
    }


    if(useTLS) {
		// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		// <SSL> ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

		// Init SSL (Default Params should be fine)
		if(!t_SDCInstance->initSSL()) {
			DebugOut(DebugOut::Default, "ReferenceConsumer") << "Failed to init SSL!" << std::endl;
			return -1;
		}
		// Configure SSL
		auto t_SSLConfig = t_SDCInstance->getSSLConfig();
		t_SSLConfig->addCertificateAuthority("ca.pem");
		t_SSLConfig->useCertificate("sdccert.pem");
		t_SSLConfig->useKeyFiles(/*Public Key*/"", "userkey.pem", ""/* Password for Private Keyfile */);

		// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		// </SSL> +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    }

	// Discovery
	OSELib::SDC::ServiceManager t_serviceManager(t_SDCInstance);

	// Note: Calculate a UUIDv5 and apply prefix to it!

	auto t_availableConsumers = t_serviceManager.discover();
	if(t_availableConsumers.size() == 0)
	{
		std::cout << "No Endpoint found" << std::endl;
		return -1;
	}
	std::unique_ptr<SDCConsumer> t_consumer{};
	if(endpointEnding == "")
	{
		int i = 1;
		int selected = 0;
		std::cout << "Available EndpointReferences: \n";
		std::cout << "###############################################################################\n";
		for(auto&& consumer : t_availableConsumers)
		{
			std::cout << std::to_string(i) + ". " + consumer->getEndpointReference() << std::endl;
			i++;
		}
		DebugOut(DebugOut::Default, "ReferenceConsumer") << "Enter the Endpoint Reference of your choice" << std::endl;
		std::cin >> selected;
		t_consumer = std::move(t_availableConsumers[selected-1]);
		DebugOut(DebugOut::Default, "ReferenceConsumer") << t_consumer->getEndpointReference() << std::endl;
	}
	else
	{
		for(auto&& consumer : t_availableConsumers)
		{
			if(ends_with(consumer->getEndpointReference(), endpointEnding)) {
				t_consumer = std::move(consumer);
			}
		}
	}

	try
	{
		// Connected to Provider?
		if (t_consumer != nullptr)
		{
			std::cout << "### Test 1. ### passed \n";
			std::cout << "### Test 2. ### passed \n";
			std::cout << "### Test 3. ### passed \n";
			// Get notified on Lost Connection
			std::unique_ptr<MyConnectionLostHandler> myHandler(new MyConnectionLostHandler(*t_consumer));
			t_consumer->setConnectionLostHandler(myHandler.get());

			// Create StateEventHandler to "Consume" Events from Provider
			auto numeric_dynamic_get = std::make_shared<NumericMetricEventHandler>(HANDLE_DYNAMIC_GET_NM);
			auto enum_dynamic_get = std::make_shared<EnumStringEventHandler>(HANDLE_DYNAMIC_GET_ESTRM);
			auto alert_condition_mds = std::make_shared<AlertConditionEventHandler>(HANDLE_ALERTCONDITION_MDS);
			auto alert_condition_vmd = std::make_shared<AlertConditionEventHandler>(HANDLE_ALERTCONDITION_VMD);
			auto alert_signal_vmd = std::make_shared<AlertSignalEventHandler>(HANDLE_ALERTSIGNAL_VMD);
			auto alert_signal_mds = std::make_shared<AlertSignalEventHandler>(HANDLE_ALERTSIGNAL_MDS);
			auto stream = std::make_shared<StreamConsumerEventHandler>(HANDLE_STREAM);

			auto test7and8Evaluation = std::async(std::launch::async, [numeric_dynamic_get, alert_condition_mds,
																   alert_condition_vmd, alert_signal_vmd,
																   alert_signal_mds] {
				// Check that the metric (see above) changes within 30 seconds at least 5 times
				std::this_thread::sleep_for(std::chrono::seconds(30));
				numeric_dynamic_get->getTimesValueChanged() > 4 ? std::cout << "### Test 7. ### passed\n" : std::cout << "### Test 7. ### failed\n";

				// Check that the alert condition (see above)change within 30 seconds at least 5 times
				((alert_condition_mds->getTimesValueChanged() > 4) &&
				(alert_condition_vmd->getTimesValueChanged() > 4) &&
				(alert_signal_vmd->getTimesValueChanged() > 4) &&
				(alert_signal_mds->getTimesValueChanged() > 4)) ? std::cout << "### Test 8. ### passed\n" : std::cout << "### Test 8. ### failed\n";


			});

			// Register StateEventHandlers to get updates
			if (t_consumer->registerStateEventHandler(numeric_dynamic_get.get()) &&
				t_consumer->registerStateEventHandler(enum_dynamic_get.get()) &&
				t_consumer->registerStateEventHandler(alert_signal_vmd.get()) &&
				t_consumer->registerStateEventHandler(alert_signal_mds.get()) &&
				t_consumer->registerStateEventHandler(alert_condition_mds.get()) &&
				t_consumer->registerStateEventHandler(alert_condition_vmd.get()) &&
				t_consumer->registerStateEventHandler(stream.get()))
			{
				std::cout << "### Test 4. ### passed \n";
			}
			else
			{
				std::cout << "### Test 4. ### failed \n";
			}

			auto patientContext = t_consumer->getMdState().findPatientContextStates();
			auto locationContext = t_consumer->getMdState().findLocationContextStates();

			// Check that least one patient context exists
			patientContext.empty() ? std::cout << "### Test 5. ### failed\n" : std::cout << "### Test 5. ### passed\n";

			// Check that at least one location context exists
			locationContext.empty() ? std::cout << "### Test 6. ### failed\n" : std::cout << "### Test 6. ### passed\n";

			// Simple Test(1):
			// Search for the "Get"-State
			// If found: Print the current(!) value

			auto numeric_static_get{std::move(t_consumer->requestState<NumericMetricState>(HANDLE_STATIC_GET_NM))};


			if(numeric_static_get)
			{
				if(numeric_static_get->hasMetricValue())
				{
					Util::DebugOut(Util::DebugOut::Default, "ReferenceConsumer") << "Requested get metrics value: " << numeric_static_get->getMetricValue().getValue();
				}
			}

			auto string_static_get{std::move(t_consumer->requestState<StringMetricState>(HANDLE_STATIC_GET_STRM))};

			if(string_static_get)
			{
				if(string_static_get->hasMetricValue())
				{
					Util::DebugOut(Util::DebugOut::Default, "ReferenceConsumer") << "Requested get metrics value: " << string_static_get->getMetricValue().getValue();
				}
			}

			auto enum_static_get{std::move(t_consumer->requestState<EnumStringMetricState>(HANDLE_STATIC_GET_ESTRM))};

			if(enum_static_get)
			{
				if(enum_static_get->hasMetricValue())
				{
					Util::DebugOut(Util::DebugOut::Default, "ReferenceConsumer") << "Requested get metrics value: " << enum_static_get->getMetricValue().getValue();
				}
			}

			test7and8Evaluation.wait();

			// Search for the "Set"-State
			auto t_setMetricState{t_consumer->requestState<NumericMetricState>(HANDLE_SET_NM)};
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
				Util::DebugOut(Util::DebugOut::Default, "ReferenceConsumer") << "Commit result metric state: " << fis.waitReceived(InvocationState::Fin, 2000);
			}

			auto t_setEnumMetricState{t_consumer->requestState<EnumStringMetricState>(HANDLE_SET_ESTRM)};
			if (t_setEnumMetricState)
			{
				// If found check if settable
				for (const auto& vmd : t_consumer->getMdib().getMdDescription().collectAllVmdDescriptors())
				{
					if (vmd.hasSco())
					{
						const auto& setOperations = vmd.getSco().collectAllSetStringOperationDescriptors();
						for(const auto& operation : setOperations)
						{
							if(operation.getOperationTarget() == HANDLE_SET_ESTRM)
							{
								//t_newValue has to be in AllowedValues of the enum
								std::string t_newValue{"ON"};
								// Use the returned state, set the value and "commit" it
								t_setEnumMetricState->setMetricValue(StringMetricValue{MetricQuality{MeasurementValidity::Vld}}.setValue(t_newValue));
								// Now
								FutureInvocationState fis;
								t_consumer->commitState(*t_setEnumMetricState, fis);
								// Now wait for "InvocationState::Fin" (=> Success)
								Util::DebugOut(Util::DebugOut::Default, "ReferenceConsumer") << "Commit result metric state: " << fis.waitReceived(InvocationState::Fin, 2000) << "\n";
								break;
							}
						}
					}
				}
			}

			FutureInvocationState fis;
			t_consumer->activate(HANDLE_ACTIVATE_MDS, fis);
			if (fis.waitReceived(InvocationState::Fin, 2000))
			{
				std::cout << "### Test 9. activate MDS ### passed\n";
			}
			else
			{
				std::cout << "### Test 9. activate MDS ### failed\n";
			}
			FutureInvocationState fis1;
			t_consumer->activate(HANDLE_ACTIVATE_VMD, fis1);
			if (fis1.waitReceived(InvocationState::Fin, 2000))
			{
				std::cout << "### Test 9. activate VMD ### passed\n";
			}
			else
			{
				std::cout << "### Test 9. activate VMD ### failed\n";
			}

			// From here on the registered StateEventHandlers (SDCLib Threads / background) will provide information
			// on "state changes" until the user enters a key ("waitForUserInput") or exception is thrown.
			waitForUserInput();
			// Unregister and disconnect
			t_consumer->unregisterStateEventHandler(numeric_dynamic_get.get());
			t_consumer->unregisterStateEventHandler(enum_dynamic_get.get());
			t_consumer->unregisterStateEventHandler(alert_signal_mds.get());
			t_consumer->unregisterStateEventHandler(alert_signal_vmd.get());
			t_consumer->unregisterStateEventHandler(alert_condition_vmd.get());
			t_consumer->unregisterStateEventHandler(alert_condition_mds.get());
			t_consumer->unregisterStateEventHandler(stream.get());
			t_consumer->disconnect();
		}
		else
		{
			// Something went wrong -> Exit!

			std::cout << "### Test 1. ### failed \n";
			std::cout << "### Test 2. ### failed \n";
			Util::DebugOut(Util::DebugOut::Default, "ReferenceConsumer") << "Discovery failed. \n";
		}
	}
	catch (std::exception& e)
	{
		std::cout << "### Test 1. ### failed \n";
		std::cout << "### Test 2. ### failed \n";
		Util::DebugOut(Util::DebugOut::Default, "ReferenceConsumer") << "Exception: " << e.what() << std::endl;
	}

	Util::DebugOut(Util::DebugOut::Default, "ReferenceConsumer") << "Shutdown." << std::endl;
	return 0;
}
