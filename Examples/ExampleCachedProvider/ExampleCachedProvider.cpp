/*
 *  ExampleCachedProvider.cpp
 *
 *  @Copyright (C) 2017, SurgiTAIX AG
 *  Author: buerger, baumeister
 *
 *  The ExampleCachedProvider uses an .xml file ('cachedMdib.xml') to build up an SDCProvider device.
 *  It further shows how some of the the providers states ('') can be used to
 *
 */


#include <string>
#include <fstream>
#include <thread>

#include "SDCLib/SDCLibrary.h"
#include "SDCLib/Data/SDC/SDCProvider.h"
#include "SDCLib/Data/SDC/SDCProviderMDStateHandler.h"
#include "SDCLib/Data/SDC/MDIB/MetricQuality.h"
#include "SDCLib/Data/SDC/MDIB/RealTimeSampleArrayMetricState.h"
#include "SDCLib/Data/SDC/MDIB/SampleArrayValue.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricState.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricValue.h"
#include "SDCLib/Util/DebugOut.h"
#include "SDCLib/Util/Task.h"

using namespace SDCLib;
using namespace SDCLib::Util;
using namespace SDCLib::Data::SDC;

const std::string FILE_CACHED_MDIB{"cachedMdib.xml"};

const std::string DEVICE_EPR{"UDI-EXAMPLE_CACHED_PROVIDER"};

const std::string HANDLE_SET_METRIC{"handle_set"};
const std::string HANDLE_GET_METRIC{"handle_get"};
const std::string HANDLE_STREAM_METRIC{"handle_stream"};

class GetNumericMetricStateHandler : public SDCProviderMDStateHandler<NumericMetricState>
{
public:

	// The state handler take a string named as the descriptor for referencing
	GetNumericMetricStateHandler(const std::string p_descriptorHandle)
    : SDCProviderMDStateHandler(p_descriptorHandle)
    { }

	// Helper method
	NumericMetricState createState(double p_newValue)
	{
		NumericMetricState t_newState{getDescriptorHandle()};
		t_newState
			.setMetricValue(NumericMetricValue(MetricQuality(MeasurementValidity::Vld)).setValue(p_newValue))
			.setActivationState(ComponentActivation::On);
		return t_newState;
	}

	NumericMetricState getInitialState() override
	{
		return createState(42.0);
	}

	void setNumericValue(double p_newValue)
	{
		auto t_newState{createState(p_newValue)};
		updateState(t_newState);
	}

    // do nothing when a consumer ask to change the value -> return Fail
    InvocationState onStateChangeRequest(const NumericMetricState&, const OperationInvocationContext&) override
    {
    	return InvocationState::Fail;
    }
};



class SetNumericMetricStateHandler : public SDCProviderMDStateHandler<NumericMetricState>
{
public:
	// The state handler take a string named as the descriptor for referencing
    SetNumericMetricStateHandler(const std::string p_descriptorHandle)
    : SDCProviderMDStateHandler(p_descriptorHandle)
    { }

    InvocationState onStateChangeRequest(const NumericMetricState& p_changedState, const OperationInvocationContext& p_oic) override
    {
        // Invocation has been fired as WAITING when entering this method
        DebugOut(DebugOut::Default, "SimpleSDC") << "Provider: handle_set received state change request. State's value: " << p_changedState.getMetricValue().getValue() << std::endl;

        notifyOperationInvoked(p_oic, InvocationState::Start);

        return InvocationState::Fin;  // Framework will update internal MDIB with the state's value and increase MDIB version
    }

    // Helper method
    NumericMetricState createState()
    {
		NumericMetricState t_newState{getDescriptorHandle()};
		t_newState.setMetricValue(NumericMetricValue(MetricQuality(MeasurementValidity::Vld)).setValue(2.0))
			   .setActivationState(ComponentActivation::On);
        return t_newState;
    }

    NumericMetricState getInitialState() override
    {
    	return createState();
    }

    // Convenience value getter
    double getMaxWeight()
    {
        auto t_weightState{getParentProvider().getMdState().findState<NumericMetricState>(HANDLE_SET_METRIC)};

        // check if result is valid
        if ((nullptr == t_weightState) && (!t_weightState->hasMetricValue()))
        {
        	DebugOut(DebugOut::Default, "ExampleCachedProvider") << "Maximum weight metric state not found." << std::endl;
        	return 0;
        }
        // In real applications, check if state has an observed value and if the observed value has a value!
        return t_weightState->getMetricValue().getValue();
    }
};


// implements a measurement state of several measured values
class StreamProviderStateHandler : public SDCProviderMDStateHandler<RealTimeSampleArrayMetricState>
{
public:
	// The state handler take a string named as the descriptor for referencing
    StreamProviderStateHandler(std::string p_descriptorHandle)
    : SDCProviderMDStateHandler(p_descriptorHandle)
    { }

    // Helper method
    RealTimeSampleArrayMetricState createState()
    {
        RealTimeSampleArrayMetricState t_newState{getDescriptorHandle()};
        t_newState.setActivationState(ComponentActivation::On);
        return t_newState;
    }


    RealTimeSampleArrayMetricState getInitialState() override
    {
    	return createState();
    }

    void updateStateValue(const SampleArrayValue& p_newValue)
    {
        auto t_newState{createState()};
        t_newState.setMetricValue(p_newValue);

        updateState(t_newState);
    }

    // do nothing when a consumer ask to change the value -> return Fail
    InvocationState onStateChangeRequest(const RealTimeSampleArrayMetricState&, const OperationInvocationContext&) override
    {
    	return InvocationState::Fail;
    }
};

class SDCStreamProvider : public Util::Task
{
public:

    SDCStreamProvider(SDCInstance_shared_ptr p_SDCInstance, std::ifstream& p_stream)
    : m_sdcProvider(p_SDCInstance)
    {
        assert(p_stream.is_open());

        m_sdcProvider.setEndpointReferenceByName(DEVICE_EPR);

		std::stringstream buffer;
		buffer << p_stream.rdbuf();
		std::string mdDesciption_xml = buffer.str();
        p_stream.close();

		DebugOut(DebugOut::Default, "ExampleCachedProvider") << mdDesciption_xml;

		// set DPWS metadata, e.g. for the displayed friendly name
		Dev::DeviceCharacteristics devChar;
		devChar.addFriendlyName("en", "SDCLib ExampleProvider");
		m_sdcProvider.setDeviceCharacteristics(devChar);

		m_sdcProvider.setMdDescription(mdDesciption_xml);

        // Add handler
		m_sdcProvider.addMdStateHandler(&m_streamHandler);
		m_sdcProvider.addMdStateHandler(&m_getNumericHandler);
		m_sdcProvider.addMdStateHandler(&m_setNumericHandler);
    }

    void startup()
    {
    	m_sdcProvider.startup();
    }

    void updateStateValue(const SampleArrayValue& p_newValue)
    {
    	m_streamHandler.updateStateValue(p_newValue); // updates handles and the parent provider
    }

private:

    // API provider class
    SDCProvider m_sdcProvider;

    // State Handlers
    // each state handler ist named the same way as regarding descriptor
    StreamProviderStateHandler m_streamHandler{HANDLE_STREAM_METRIC};
    GetNumericMetricStateHandler m_getNumericHandler{HANDLE_GET_METRIC};
    SetNumericMetricStateHandler m_setNumericHandler{HANDLE_SET_METRIC};

public:

    // Produce stream values
    // runImpl() gets called when starting the provider thread by the inherited function start()
    void runImpl() override
    {
    	// Streaming init
		const auto t_chunkSize{1000};
		std::vector<double> t_samples;
        std::iota(t_samples.begin(), t_samples.end(), 0);

		auto t_sampleIndex{0};

		while (!isInterrupted())
		{
			{
                updateStateValue(SampleArrayValue{MetricQuality{MeasurementValidity::Vld}}.setSamples(RealTimeValueType{t_samples}));
			}
			DebugOut(DebugOut::Default, "ExampleCachedProvider") << "Produced stream chunk of size " << t_chunkSize << ", index " << t_sampleIndex << std::endl;

			// generate NumericMetricState
			m_getNumericHandler.setNumericValue(42.0);
			DebugOut(DebugOut::Default, "ExampleCachedProvider") << "NumericMetric: value changed to 42.0" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            t_sampleIndex += t_chunkSize;
		}
    }
};



int main()
{
    // Load cached Mdib from file system
    // Mdib is specified in xml
    std::ifstream t_mdibFilestream(FILE_CACHED_MDIB);
    // Found?
    if(!t_mdibFilestream.is_open()) {
        DebugOut(DebugOut::Default, "ExampleCachedProvider") << "Could not open " << FILE_CACHED_MDIB << "\n";
        return -1;
    }

	// Startup
	DebugOut(DebugOut::Default, "ExampleCachedProvider") << "Startup" << std::endl;
    SDCLibrary::getInstance().startup(OSELib::LogLevel::Debug);

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

	SDCStreamProvider t_provider(t_SDCInstance, t_mdibFilestream);
	t_provider.startup();
	t_provider.start();

	DebugOut(DebugOut::Default, "ExampleCachedProvider") << "Press key to exit program.";
	std::cin.get();

	// Shutdown
	DebugOut(DebugOut::Default, "ExampleCachedProvider") << "Shutdown." << std::endl;

    return 0;
}
