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
   *  @Copyright (C) 2021, SurgiTAIX AG
   *  Author: baumeister, rosenau
   *
   * ReferenceConsumer Implementation
   *
   * This consumer executes the following steps and prints whether each step was successful
   * 1. discovery of device with specific endpoint
   * 2. connect to device with specific endpoint
   * 3. read mdib of provider
   * 4. subscribe metrics, alerts, waveforms
   * 5. check that least one patient context exists
   * 6. check that at least one location context exists
   * 7. check that the metric (see above) changes within 30 seconds at least 5 times
   * 8. check that the alert condition (see above)change within 30 seconds at least 5 times
   * 9. execute operations (Activate, SetString, SetValue) as specified and check that result is “finished”
   *
   */
#include "SDCLib/SDCLibrary.h"
#include "SDCLib/Data/SDC/SDCConsumer.h"
#include "SDCLib/Data/SDC/SDCConsumerConnectionLostHandler.h"
#include "SDCLib/Data/SDC/SDCConsumerMDStateHandler.h"
#include "SDCLib/Data/SDC/MDIB/MdsDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ScoDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/VmdDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/SetStringOperationDescriptor.h"
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
#include "OSELib/SDC/ServiceManager.h"

#include <chrono>
#include <atomic>
#include <string>


const std::string HANDLE_STATIC_GET_NM{ "numeric.ch0.vmd0" };
const std::string HANDLE_DYNAMIC_GET_NM{ "numeric.ch1.vmd0" };
const std::string HANDLE_SET_NM{ "numeric.ch0.vmd1" };
const std::string HANDLE_STATIC_GET_STRM{ "string.ch0.vmd0" };
const std::string HANDLE_SET_STRM{ "string.ch0.vmd1" };
const std::string HANDLE_STATIC_GET_ESTRM{ "enumstring.ch0.vmd0" };
const std::string HANDLE_DYNAMIC_GET_ESTRM{ "enumstring2.ch0.vmd0" };
const std::string HANDLE_SET_ESTRM{ "enumstring.ch0.vmd1" };

const std::string HANDLE_ALERTSIGNAL_MDS{ "as0.mds0" };
const std::string HANDLE_ALERTSIGNAL_VMD{ "as0.vmd0.mds0" };
const std::string HANDLE_ALERTCONDITION_MDS{ "ac0.mds0" };
const std::string HANDLE_ALERTCONDITION_VMD{ "ac0.vmd0.mds0" };

const std::string HANDLE_ACTIVATE_MDS{ "actop.mds0_sco_0" };
const std::string HANDLE_ACTIVATE_VMD{ "actop.vmd1_sco_0" };
const std::string HANDLE_STREAM{ "" };  // TODO?

const std::string TEST_PASSED{ "PASSED" };
const std::string TEST_FAILED{ "FAILED" };

using namespace SDCLib;
using namespace SDCLib::Util;
using namespace SDCLib::Data::SDC;

class NumericMetricEventHandler : public SDCConsumerMDStateHandler<NumericMetricState>
{
private:
	std::atomic<double> m_currentValue{ 0 };
	std::atomic<std::size_t> m_numValueChanged{ 0 };

public:
	NumericMetricEventHandler(std::string p_descriptorHandle)
		: SDCConsumerMDStateHandler(p_descriptorHandle)
	{
	}

	void onStateChanged(const NumericMetricState& p_changedState) override
	{
		if (!p_changedState.getMetricValue().hasValue())
		{
			return;
		}

		const auto newValue{ p_changedState.getMetricValue().getValue() };

		DebugOut(DebugOut::Default, "ReferenceConsumer") << getDescriptorHandle() << " numeric metric changed to: " << newValue;

		if (m_currentValue != newValue)
		{
			m_numValueChanged++;
		}
		m_currentValue = newValue;
	}

	void onOperationInvoked(const OperationInvocationContext& oic, InvocationState p_is) override
	{
		DebugOut(DebugOut::Default, "ReferenceConsumer")
			<< getDescriptorHandle() << " operation invoked (numeric metric) (ID, STATE): " << oic.transactionId << ", "
			<< Data::SDC::EnumToString::convert(p_is) << std::endl;
	}
	std::size_t getNumValueChanged() const noexcept
	{
		return m_numValueChanged;
	}
};


class StringMetricEventHandler : public SDCConsumerMDStateHandler<StringMetricState>
{
private:
	std::string currentValue{};

public:
	StringMetricEventHandler(std::string p_descriptorHandle)
		: SDCConsumerMDStateHandler(p_descriptorHandle)
	{
	}

	void onStateChanged(const StringMetricState& p_changedState) override
	{
		if (!p_changedState.getMetricValue().hasValue())
		{
			return;
		}
		currentValue = p_changedState.getMetricValue().getValue();
	}
};


class EnumStringEventHandler : public SDCConsumerMDStateHandler<EnumStringMetricState>
{
private:
	std::string currentValue{};

public:
	EnumStringEventHandler(std::string p_descriptorHandle)
		: SDCConsumerMDStateHandler(p_descriptorHandle)
	{
	}

	void onStateChanged(const EnumStringMetricState& p_changedState) override
	{
		if (!p_changedState.getMetricValue().hasValue())
		{
			return;
		}
		currentValue = p_changedState.getMetricValue().getValue();
	}
};


class AlertConditionEventHandler : public SDCConsumerMDStateHandler<AlertConditionState>
{
private:
	bool m_currentPresence{ false };
	std::atomic<std::size_t> m_numPresenceChanged{ 0 };

public:
	AlertConditionEventHandler(std::string p_descriptorHandle)
		: SDCConsumerMDStateHandler(p_descriptorHandle)
	{
	}

	void onStateChanged(const AlertConditionState& p_changedState) override
	{
		if (!p_changedState.hasPresence())
		{
			return;
		}

		const auto newPresence{ p_changedState.getPresence() };

		DebugOut(DebugOut::Default, "ReferenceConsumer")
			<< getDescriptorHandle() << " alert condition changed to: " << (newPresence ? "true" : "false");

		if (m_currentPresence != newPresence)
		{
			m_numPresenceChanged++;
		}
		m_currentPresence = newPresence;
	}

	std::size_t getNumValueChanged() const noexcept
	{
		return m_numPresenceChanged;
	}
};


class AlertSignalEventHandler : public SDCConsumerMDStateHandler<AlertSignalState>
{
private:
	AlertSignalPresence m_currentPresence{ AlertSignalPresence::Off };
	std::atomic<int> m_numPresenceChanged{ 0 };

public:
	AlertSignalEventHandler(std::string p_descriptorHandle)
		: SDCConsumerMDStateHandler(p_descriptorHandle)
	{
	}

	void onStateChanged(const AlertSignalState& p_changedState) override
	{
		if (!p_changedState.hasPresence())
		{
			return;
		}

		const auto newPresence{ p_changedState.getPresence() };

		DebugOut(DebugOut::Default, "ReferenceConsumer")
			<< getDescriptorHandle() << " alert presence changed to: " << EnumToString::convert(newPresence);

		if (newPresence != m_currentPresence)
		{
			m_numPresenceChanged++;
		}
		m_currentPresence = newPresence;
	}

	std::size_t getNumValueChanged() const noexcept
	{
		return m_numPresenceChanged;
	}
};


// state handler for array values, uses udp instead of tcp. Faster. Considered for real time applications
class StreamConsumerEventHandler : public SDCConsumerMDStateHandler<RealTimeSampleArrayMetricState>
{
public:
	StreamConsumerEventHandler(std::string p_descriptorHandle)
		: SDCConsumerMDStateHandler(p_descriptorHandle)
	{
	}

	void onStateChanged(const RealTimeSampleArrayMetricState& p_changedState) override
	{
		if (!p_changedState.getMetricValue().hasSamples())
		{
			return;
		}
		const auto& sampleValues{ p_changedState.getMetricValue().getSamples() };

		DebugOut(DebugOut::Default, "ReferenceConsumer") << "Received chunk! Handle: " << p_changedState.getDescriptorHandle() << std::endl;
		std::string out("Content: ");
		for (const auto& sample : sampleValues)
		{
			out.append(" " + std::to_string(sample));
		}
		DebugOut(DebugOut::Default, "ReferenceConsumer") << out;
	}
};


void waitForUserInput()
{
	std::string temp;
	Util::DebugOut(Util::DebugOut::Default, "ReferenceConsumerSSL") << "Press key to proceed.";
	std::cin >> temp;
}

class MyConnectionLostHandler : public Data::SDC::SDCConsumerConnectionLostHandler
{
private:
	Data::SDC::SDCConsumer& m_consumer;

public:
	MyConnectionLostHandler(Data::SDC::SDCConsumer& p_consumer)
		: m_consumer(p_consumer)
	{
	}
	void onConnectionLost() override
	{
		std::cout << "Connection lost, disconnecting... " << std::endl;
		m_consumer.disconnect();
		std::cout << "Disconnected. Press key to proceed." << std::endl;
		throw std::runtime_error("Connection Lost");
	}
};


bool ends_with(const std::string& value, const std::string& ending)
{
	if (ending.size() > value.size())
	{
		return false;
	}
	return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

struct StateHandlerContainer
{
	std::shared_ptr<NumericMetricEventHandler> numeric_dynamic_get{ std::make_shared<NumericMetricEventHandler>(HANDLE_DYNAMIC_GET_NM) };
	std::shared_ptr<EnumStringEventHandler> enum_dynamic_get{ std::make_shared<EnumStringEventHandler>(HANDLE_DYNAMIC_GET_ESTRM) };
	std::shared_ptr<AlertConditionEventHandler> alert_condition_mds{
		std::make_shared<AlertConditionEventHandler>(HANDLE_ALERTCONDITION_MDS) };
	std::shared_ptr<AlertSignalEventHandler> alert_signal_mds{ std::make_shared<AlertSignalEventHandler>(HANDLE_ALERTSIGNAL_MDS) };
	std::shared_ptr<StreamConsumerEventHandler> stream{ std::make_shared<StreamConsumerEventHandler>(HANDLE_STREAM) };
};

/*
 * This consumer executes the following steps and prints whether each step was successful
 * 1. discovery of device with specific endpoint
 * 2. connect to device with specific endpoint
 * 3. read mdib of provider
 * 4. subscribe metrics, alerts, waveforms
 * 5. check that least one patient context exists
 * 6. check that at least one location context exists
 * 7. check that the metric (see above) changes within 30 seconds at least 5 times
 * 8. check that the alert condition (see above)change within 30 seconds at least 5 times
 * 9. execute operations (Activate, SetString, SetValue) as specified and check that result is “finished”
 */
class Test1
{
private:
	bool m_testPassed{ false };
	std::string m_targetEPR;

public:
	Test1(OSELib::SDC::ServiceManager& p_serviceManager, const std::string& p_targetEPR, bool p_compareEndingOnly)
	{
		testImpl(p_serviceManager, p_targetEPR, p_compareEndingOnly);
	}

	std::string getTargetEPR() const
	{
		return m_targetEPR;
	}

	bool hasPassed() const
	{
		return m_testPassed;
	}

private:
	void testImpl(OSELib::SDC::ServiceManager& p_serviceManager, const std::string& p_targetEPR, bool p_compareEndingOnly)
	{
		// Discover and check if targetEPR is found
		// Discover
		std::cout << "\nDiscover..." << std::flush;
		auto discoveredEndpoints{ p_serviceManager.discover() };
		if (discoveredEndpoints.size() == 0)
		{
			throw std::runtime_error("### Test 1. Test Condition failed. No Endpoints found!");
		}

		std::cout << "\nDiscovered Endpoints:" << std::endl;
		for (const auto& epr : discoveredEndpoints)
		{
			std::cout << "- " << epr.endpointAddress << std::endl;
		}

		if (compareResults(discoveredEndpoints, p_targetEPR, p_compareEndingOnly))
		{
			m_testPassed = true;
			return;
		}

		throw std::runtime_error("### Test 1. Test Condition failed. No matching Endpoints found!");
	}

	bool compareResults(const OSELib::SDC::ServiceManager::DiscoverResults& p_results,
		const std::string& p_targetEPR,
		bool p_compareEndingOnly)
	{
		for (const auto& epr : p_results)
		{
			if (compareEPR(epr.endpointAddress, p_targetEPR, p_compareEndingOnly))
			{
				m_targetEPR = epr.endpointAddress;
				return true;
			}
		}
		return false;
	}

	bool compareEPR(const std::string& p_epr1, const std::string& p_epr2, const bool p_compareEndingOnly)
	{
		return p_compareEndingOnly ? ends_with(p_epr1, p_epr2) : (p_epr1 == p_epr2);
	}
};
class Test2
{
private:
	std::unique_ptr<SDCLib::Data::SDC::SDCConsumer> m_resolvedConsumer{ nullptr };
	bool m_testPassed{ false };

public:
	Test2(OSELib::SDC::ServiceManager& p_serviceManager, const std::string& p_targetEndpoint)
	{
		testImpl(p_serviceManager, p_targetEndpoint);
	}

	bool hasPassed() const
	{
		return m_testPassed;
	}

	SDCLib::Data::SDC::SDCConsumer& resolvedConsumer()
	{
		if (!m_resolvedConsumer)
		{
			throw std::runtime_error("SDCLib::Data::SDC::SDCConsumer nullptr");
		}
		return *m_resolvedConsumer;
	}

private:
	void testImpl(OSELib::SDC::ServiceManager& p_serviceManager, const std::string& p_targetEndpoint)
	{
		std::cout << "Resolving Endpoint: '" << p_targetEndpoint << "'" << std::endl;
		auto resolvedConsumer{ p_serviceManager.resolveEndpointReference(p_targetEndpoint) };
		if (!resolvedConsumer)
		{
			throw std::runtime_error("### Test 2. Test Condition failed. Could not resolve EPR: " + p_targetEndpoint);
		}

		m_resolvedConsumer = (std::move(resolvedConsumer));
		m_testPassed = true;
	}
};
class Test3
{
private:
	bool m_testPassed{ false };

public:
	Test3(SDCLib::Data::SDC::SDCConsumer& p_consumer)
	{
		testImpl(p_consumer);
	}

	bool hasPassed() const
	{
		return m_testPassed;
	}

private:
	void testImpl(SDCLib::Data::SDC::SDCConsumer& p_consumer)
	{
		auto mdib = p_consumer.getMdib();

		// TBD: Some basic checks to make sure this mdib is not "empty"
		if (mdib.getMdDescription().getMdsList().empty())
		{
			return;
		}

		// Other checks?

		m_testPassed = true;
	}
};
class Test4
{
private:
	bool m_testPassed{ false };

public:
	Test4(SDCLib::Data::SDC::SDCConsumer& p_consumer, std::shared_ptr<StateHandlerContainer> p_stateHandlerContainer)
	{
		testImpl(p_consumer, p_stateHandlerContainer);
	}

	bool hasPassed() const
	{
		return m_testPassed;
	}

private:
	void testImpl(SDCLib::Data::SDC::SDCConsumer& p_consumer, std::shared_ptr<StateHandlerContainer> p_stateHandlerContainer)
	{
		if (p_consumer.registerStateEventHandler(p_stateHandlerContainer->numeric_dynamic_get.get())
			&& p_consumer.registerStateEventHandler(p_stateHandlerContainer->enum_dynamic_get.get())
			&& p_consumer.registerStateEventHandler(p_stateHandlerContainer->alert_signal_mds.get())
			&& p_consumer.registerStateEventHandler(p_stateHandlerContainer->alert_condition_mds.get())
			&& p_consumer.registerStateEventHandler(p_stateHandlerContainer->stream.get()))
		{
			m_testPassed = true;
		}
		else
		{
			std::cout << "### Test 4. Test Condition failed. Failed to register all StateEventHandler!" << std::endl;
		}
	}
};
class Test5
{
private:
	SDCLib::Data::SDC::SDCConsumer& m_consumer;
	bool m_testPassed{ false };

public:
	Test5(SDCLib::Data::SDC::SDCConsumer& p_consumer)
		: m_consumer(p_consumer)
	{
		testImpl();
	}

	bool hasPassed() const
	{
		return m_testPassed;
	}

private:
	void testImpl()
	{
		auto patientContext{ m_consumer.getMdState().findPatientContextStates() };

		// Check that least one patient context exists
		if (patientContext.empty())
		{
			std::cout << "### Test 5. Test Condition failed. No PatientContext found!" << std::endl;
		}
		else
		{
			m_testPassed = true;
		}
	}
};
class Test6
{
private:
	SDCLib::Data::SDC::SDCConsumer& m_consumer;
	bool m_testPassed{ false };

public:
	Test6(SDCLib::Data::SDC::SDCConsumer& p_consumer)
		: m_consumer(p_consumer)
	{
		testImpl();
	}

	bool hasPassed() const
	{
		return m_testPassed;
	}

private:
	void testImpl()
	{
		auto locationContext{ m_consumer.getMdState().findLocationContextStates() };

		// Check that least one location context exists
		if (locationContext.empty())
		{
			std::cout << "### Test 6. Test Condition failed. No LocationContext found!" << std::endl;
		}
		else
		{
			m_testPassed = true;
		}
	}
};
class Test7
{
	/*
	 * Test 7
	 * check that the metric (see above) changes within 30 seconds at least 5 times
	 */
private:
	const std::chrono::seconds WAIT_BEFORE_CHECK_CONDITION{ 30 };
	const std::size_t NUM_CHANGES_TO_PASS_TEST{ 5 };

	std::future<bool> m_testResult;

	bool m_testPassed{ false };

public:
	Test7(std::shared_ptr<NumericMetricEventHandler> p_numericHandler)
	{
		testImpl(p_numericHandler);
	}

	bool hasPassed()
	{
		if (m_testResult.valid())
		{
			m_testPassed = m_testResult.get();
		}
		return m_testPassed;
	}

	void wait_until(const std::chrono::milliseconds p_wait)
	{
		m_testResult.wait_for(p_wait);
	}
	void wait()
	{
		m_testResult.wait();
	}

private:
	void testImpl(std::shared_ptr<NumericMetricEventHandler> p_numericHandler)
	{
		m_testResult = std::async(std::launch::async, [=] {
			// Wait the specified amount of time before checking the conditions
			std::this_thread::sleep_for(WAIT_BEFORE_CHECK_CONDITION);

			if (p_numericHandler->getNumValueChanged() < NUM_CHANGES_TO_PASS_TEST)
			{
				std::cout << "### Test 7. NumericMetric - test condition failed. NumChanges: " << p_numericHandler->getNumValueChanged()
					<< std::endl;
				return false;
			}

			return true;
			});
	}
};
class Test8
{
private:
	const std::chrono::seconds WAIT_BEFORE_CHECK_CONDITION{ 30 };
	const std::size_t NUM_CHANGES_TO_PASS_TEST{ 5 };

	bool m_testPassed{ false };
	std::future<bool> m_testResult;

public:
	Test8(std::shared_ptr<StateHandlerContainer> p_allStateHandler)
	{
		testImpl(p_allStateHandler);
	}

	bool hasPassed()
	{
		if (m_testResult.valid())
		{
			m_testPassed = m_testResult.get();
		}
		return m_testPassed;
	}

	void wait_until(const std::chrono::milliseconds p_wait)
	{
		m_testResult.wait_for(p_wait);
	}
	void wait()
	{
		m_testResult.wait();
	}

private:
	void testImpl(std::shared_ptr<StateHandlerContainer> p_allStateHandler)
	{
		m_testResult = std::async(std::launch::async, [=] {
			// Wait the specified amount of time before checking the conditions
			std::this_thread::sleep_for(WAIT_BEFORE_CHECK_CONDITION);

			// AlertCondition - Mds
			if (p_allStateHandler->alert_condition_mds->getNumValueChanged() < NUM_CHANGES_TO_PASS_TEST)
			{
				std::cout << "### Test 8. AlertCondition - Mds test condition failed. NumChanges: "
					<< p_allStateHandler->alert_condition_mds->getNumValueChanged() << std::endl;
				return false;
			}

			// AlertSignal - Mds
			if (p_allStateHandler->alert_signal_mds->getNumValueChanged() < NUM_CHANGES_TO_PASS_TEST)
			{
				std::cout << "### Test 8. AlertSignal - Mds test condition failed. NumChanges: "
					<< p_allStateHandler->alert_signal_mds->getNumValueChanged() << std::endl;
				return false;
			}

			return true;
			});
	}
};
class Test9
{
private:
	SDCLib::Data::SDC::SDCConsumer& m_consumer;
	bool m_testPassed{ false };

	const int ACTIVATE_TIMEOUT_MS{ 2000 };

public:
	Test9(SDCLib::Data::SDC::SDCConsumer& p_consumer)
		: m_consumer(p_consumer)
	{
		testImpl();
	}

	bool hasPassed()
	{
		return m_testPassed;
	}

private:
	void testImpl()
	{
		if (!activateMds())
		{
			std::cout << "### Test 9. activate MDS ### failed\n";
			return;
		}
		if (!activateVmd())
		{
			std::cout << "### Test 9. activate VMD ### failed\n";
			return;
		}

		if (!testSetValue())
		{
			std::cout << "### Test 9. setValue ### failed\n";
			return;
		}

		if (!testSetString())
		{
			std::cout << "### Test 9. SetString ### failed\n";
			return;
		}

		if (!testSetEnumString())
		{
			std::cout << "### Test 9. SetEnumString ### failed\n";
			return;
		}

		// ...

		m_testPassed = true;
	}

	bool activateMds()
	{
		std::cout << "### Test 9. skipped activate MDS ### " << std::endl;
		return true;
		//return activate(HANDLE_ACTIVATE_MDS);
	}

	bool activateVmd()
	{
		return activate(HANDLE_ACTIVATE_VMD);
	}

	bool activate(const std::string& p_handle)
	{
		FutureInvocationState fis;
		m_consumer.activate(p_handle, fis);
		return fis.waitReceived(InvocationState::Fin, ACTIVATE_TIMEOUT_MS);
	}

	// numeric.ch0.vmd1
	bool testSetValue()
	{
		// Search for the "Set"-State
		auto setMetricState{ m_consumer.requestState<NumericMetricState>(HANDLE_SET_NM) };
		// If found: Set it to a given value
		if (!setMetricState)
		{
			std::cout << "### Test 9. failed. SetValue could not request NumericMetricState. ###\n";
			return false;
		}
		const auto newValue{ 10.0 };
		// Use the returned state, set the value and "commit" it
		setMetricState->setMetricValue(NumericMetricValue{ MetricQuality{MeasurementValidity::Vld} }.setValue(newValue));
		// Now
		FutureInvocationState fis;
		m_consumer.commitState(*setMetricState, fis);
		// Now wait for "InvocationState::Fin" (=> Success)
		Util::DebugOut(Util::DebugOut::Default, "ReferenceConsumer")
			<< "Commit result metric state: " << fis.waitReceived(InvocationState::Fin, 2000);
		return true;
	}
	// string.ch0.vmd1
	bool testSetString()
	{
		auto setEnumMetricState{ m_consumer.requestState<StringMetricState>(HANDLE_SET_STRM) };
		if (!setEnumMetricState)
		{
			return false;
		}

		// If found check if settable
		for (const auto& vmd : m_consumer.getMdib().getMdDescription().collectAllVmdDescriptors())
		{
			if (!vmd.hasSco())
			{
				continue;
			}

			const auto& setOperations = vmd.getSco().collectAllSetStringOperationDescriptors();
			for (const auto& operation : setOperations)
			{
				if (operation.getOperationTarget() != HANDLE_SET_ESTRM)
				{
					continue;
				}
				//newValue has to be in AllowedValues of the enum
				const std::string newValue{ "ON" };
				// Use the returned state, set the value and "commit" it
				setEnumMetricState->setMetricValue(StringMetricValue{ MetricQuality{MeasurementValidity::Vld} }.setValue(newValue));
				// Now
				FutureInvocationState fis;
				m_consumer.commitState(*setEnumMetricState, fis);
				// Now wait for "InvocationState::Fin" (=> Success)
				Util::DebugOut(Util::DebugOut::Default, "ReferenceConsumer")
					<< "Commit result string metric state: " << fis.waitReceived(InvocationState::Fin, 2000) << "\n";
				return true;
			}
		}

		return false;
	}
	// enumstring.ch0.vmd1
	bool testSetEnumString()
	{
		auto setEnumMetricState{ m_consumer.requestState<EnumStringMetricState>(HANDLE_SET_ESTRM) };
		if (!setEnumMetricState)
		{
			return false;
		}

		// If found check if settable
		for (const auto& vmd : m_consumer.getMdib().getMdDescription().collectAllVmdDescriptors())
		{
			if (!vmd.hasSco())
			{
				continue;
			}

			const auto& setOperations = vmd.getSco().collectAllSetStringOperationDescriptors();
			for (const auto& operation : setOperations)
			{
				if (operation.getOperationTarget() != HANDLE_SET_ESTRM)
				{
					continue;
				}
				//newValue has to be in AllowedValues of the enum
				const std::string newValue{ "ON" };
				// Use the returned state, set the value and "commit" it
				setEnumMetricState->setMetricValue(StringMetricValue{ MetricQuality{MeasurementValidity::Vld} }.setValue(newValue));
				// Now
				FutureInvocationState fis;
				m_consumer.commitState(*setEnumMetricState, fis);
				// Now wait for "InvocationState::Fin" (=> Success)
				Util::DebugOut(Util::DebugOut::Default, "ReferenceConsumer")
					<< "Commit result enum string metric state: " << fis.waitReceived(InvocationState::Fin, 2000) << "\n";
				return true;
			}
		}
		return false;
	}
};


void printHelp()
{
	std::cout << "ReferenceConsumer usage." << std::endl;
	std::cout << "-epr <EPR>\tResolve given Endpoint." << std::endl;
	std::cout << "-eprew <EPR>\tResolve Endpoint that ends with given sequence." << std::endl;
	std::cout << "-b <NETWORK INTERFACE>\tBind to given network interface. If omitted most appropriate is chosen." << std::endl;
	std::cout << "-tls Enable TLS Encryption to load predefined certificate files." << std::endl;

	std::cout << "-h\tPrint this help text." << std::endl;
}
int main(/*int argc, char* argv[]*/)
{
	DebugOut::DEBUG_LEVEL = DebugOut::Info;

	bool useTLS{ false };
	std::string targetEndpoint{ "urn:uuid:9eb4fd10-a6b0-4659-b31b-934505bffc7b" };
	std::string bindToInterface;
	bool compareEPREndingOnly{ false };

	/*
	for (int i = 0; i < argc; i++)
	{
		if (std::string{ argv[i] } == "-tls")
		{
			useTLS = true;
		}
		if (std::string{ argv[i] } == "-epr")
		{
			if (i == argc - 1)
			{
				std::cout << "please provide an endpoint";
				return -1;
			}
			else
			{
				targetEndpoint = std::string{ argv[i + 1] };
			}
		}
		if (std::string{ argv[i] } == "-eprew")
		{
			if (i == argc - 1)
			{
				std::cout << "please provide an endpoint";
				return -1;
			}
			else
			{
				targetEndpoint = std::string{ argv[i + 1] };
				compareEPREndingOnly = true;
			}
		}

		if (std::string{ argv[i] } == "-b")
		{
			bindToInterface = std::string{ argv[i + 1] };
		}

		if (std::string{ argv[i] } == "-h")
		{
			printHelp();
			return 0;
		}
	}
	*/

	if (targetEndpoint.empty())
	{
		std::cout << "Either provide -epr <ENDPOINT> or -eprew <ENDPOINT_ENDS_WITH>" << std::endl;
		return -1;
	}


	Util::DebugOut(Util::DebugOut::Default, "ReferenceConsumerSSL") << "Startup";
	SDCLibrary::getInstance().startup(OSELib::LogLevel::Warning);

	// Create a new SDCInstance (no flag will auto init)
	auto consumerSDCInstance{ std::make_shared<SDCInstance>(true) };
	// Some restriction
	consumerSDCInstance->setIP6enabled(false);
	consumerSDCInstance->setIP4enabled(true);


	// Bind it to interface that matches the internal criteria (usually the first enumerated)

	if (bindToInterface.empty())
	{
		std::cout << "\nSearching a network interface to bind to ..." << std::endl;
		if (!consumerSDCInstance->bindToInterface("{5576B12E-A7F6-4BB0-9B85-3A2CFE11F53E}", true))
		{
			DebugOut(DebugOut::Default, "ReferenceConsumer") << "Failed to bind to default network interface! Exit..." << std::endl;
			return -1;
		}
	}
	else
	{
		std::cout << "\nTrying to bind to interface: " << bindToInterface << std::endl;
		if (!consumerSDCInstance->bindToInterface("{5576B12E-A7F6-4BB0-9B85-3A2CFE11F53E}", true))
		{
			DebugOut(DebugOut::Default, "ReferenceConsumer")
				<< "Failed to bind to network interface'" << bindToInterface << "'! Exit..." << std::endl;
			return -1;
		}
	}


	if (useTLS)
	{
		// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		// <SSL> ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

		// Init SSL (Default Params should be fine)
		if (!consumerSDCInstance->initSSL())
		{
			DebugOut(DebugOut::Default, "ReferenceConsumer") << "Failed to init SSL!" << std::endl;
			return -1;
		}
		// Configure SSL
		auto consumerSSLConfig{ consumerSDCInstance->getSSLConfig() };
		consumerSSLConfig->addCertificateAuthority("ca.pem");
		consumerSSLConfig->useCertificate("sdccert.pem");
		consumerSSLConfig->useKeyFiles(/*Public Key*/ "", "userkey.pem", "" /* Password for Private Keyfile */);

		// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		// </SSL> +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	}

	OSELib::SDC::ServiceManager serviceManager(consumerSDCInstance);

	try
	{
		auto stateHandlerContainer{ std::make_shared<StateHandlerContainer>() };

		Test1 test1{ serviceManager, targetEndpoint, compareEPREndingOnly };
		Test2 test2{ serviceManager, test1.getTargetEPR() };
		Test3 test3{ test2.resolvedConsumer() };
		Test4 test4{ test2.resolvedConsumer(), stateHandlerContainer };
		Test5 test5{ test2.resolvedConsumer() };
		Test6 test6{ test2.resolvedConsumer() };
		Test7 test7{ stateHandlerContainer->numeric_dynamic_get };
		Test8 test8{ stateHandlerContainer };
		Test9 test9{ test2.resolvedConsumer() };

		// Get notified on Lost Connection
		std::unique_ptr<MyConnectionLostHandler> myHandler(new MyConnectionLostHandler(test2.resolvedConsumer()));
		test2.resolvedConsumer().setConnectionLostHandler(myHandler.get());

		// Wait for async results
		test7.wait();
		test8.wait();

		std::cout << "\n" << std::endl;

		std::cout << "### Test 1. ### " << (test1.hasPassed() ? TEST_PASSED : TEST_FAILED) << std::endl;
		std::cout << "### Test 2. ### " << (test2.hasPassed() ? TEST_PASSED : TEST_FAILED) << std::endl;
		std::cout << "### Test 3. ### " << (test3.hasPassed() ? TEST_PASSED : TEST_FAILED) << std::endl;
		std::cout << "### Test 4. ### " << (test4.hasPassed() ? TEST_PASSED : TEST_FAILED) << std::endl;
		std::cout << "### Test 5. ### " << (test5.hasPassed() ? TEST_PASSED : TEST_FAILED) << std::endl;
		std::cout << "### Test 6. ### " << (test6.hasPassed() ? TEST_PASSED : TEST_FAILED) << std::endl;
		std::cout << "### Test 7. ### " << (test7.hasPassed() ? TEST_PASSED : TEST_FAILED) << std::endl;
		std::cout << "### Test 8. ### " << (test8.hasPassed() ? TEST_PASSED : TEST_FAILED) << std::endl;
		std::cout << "### Test 9. ### " << (test9.hasPassed() ? TEST_PASSED : TEST_FAILED) << std::endl;


		// From here on the registered StateEventHandlers (SDCLib Threads / background) will provide information
		// on "state changes" until the user enters a key ("waitForUserInput") or exception is thrown.
		//waitForUserInput();
		// Unregister and disconnect
		test2.resolvedConsumer().unregisterStateEventHandler(stateHandlerContainer->numeric_dynamic_get.get());
		test2.resolvedConsumer().unregisterStateEventHandler(stateHandlerContainer->enum_dynamic_get.get());
		test2.resolvedConsumer().unregisterStateEventHandler(stateHandlerContainer->alert_signal_mds.get());
		test2.resolvedConsumer().unregisterStateEventHandler(stateHandlerContainer->alert_condition_mds.get());
		test2.resolvedConsumer().disconnect();
	}
	catch (std::exception& e)
	{
		Util::DebugOut(Util::DebugOut::Default, "ReferenceConsumer") << "Exception: " << e.what() << std::endl;
		return -1;
	}

	Util::DebugOut(Util::DebugOut::Default, "ReferenceConsumer") << "Shutdown." << std::endl;
	return 0;
}
