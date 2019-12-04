/*
 * ExampleProvider.cpp
 *
 *  @Copyright (C) 2016, SurgiTAIX AG
 *  Author: buerger
 *
 *  This program sends a RealTimeSampleArrayMetricState (HANDLE_STREAM_METRIC) and a NumericMatricState (HANDLE_GET_METRIC) to the network. It changes the HANDLE_STREAM_METRIC
 *
 */



#include "SDCLib/Data/SDC/SDCProvider.h"

#include "SDCLib/SDCLibrary.h"
#include "SDCLib/SDCInstance.h"

#include "SDCLib/Data/SDC/SDCProviderStateHandler.h"
#include "SDCLib/Data/SDC/SDCProviderMDStateHandler.h"
#include "SDCLib/Data/SDC/MDIB/ChannelDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/CodedValue.h"
#include "SDCLib/Data/SDC/MDIB/SimpleTypesMapping.h"
#include "SDCLib/Data/SDC/MDIB/MdsDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/LocalizedText.h"
#include "SDCLib/Data/SDC/MDIB/MdDescription.h"
#include "SDCLib/Data/SDC/MDIB/MetricQuality.h"
#include "SDCLib/Data/SDC/MDIB/RealTimeSampleArrayMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/RealTimeSampleArrayMetricState.h"
#include "SDCLib/Data/SDC/MDIB/SampleArrayValue.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricState.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricValue.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/StringMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/StringMetricState.h"
#include "SDCLib/Data/SDC/MDIB/StringMetricValue.h"
#include "SDCLib/Data/SDC/MDIB/MetaData.h"
#include "SDCLib/Data/SDC/MDIB/VmdDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/custom/OperationInvocationContext.h"
#include "SDCLib/Dev/DeviceCharacteristics.h"

#include "SDCLib/Util/DebugOut.h"
#include "SDCLib/Util/Task.h"

using namespace SDCLib;
using namespace SDCLib::Util;
using namespace SDCLib::Data::SDC;


const std::string DEVICE_EPR("UDI-ExampleProvider");

const std::string VMD_DESCRIPTOR_HANDLE("holdingDevice_vmd");
const std::string CHANNEL_DESCRIPTOR_HANDLE("holdingDevice_channel");
const std::string MDS_DESCRIPTOR_HANDLE("holdingDevice_mds");

const std::string HANDLE_SET_METRIC("handle_set");
const std::string HANDLE_GET_METRIC("handle_get");
const std::string HANDLE_STREAM_METRIC("handle_stream");
const std::string HANDLE_STRING_METRIC("handle_string");


class NumericProviderStateHandlerGet : public SDCProviderMDStateHandler<NumericMetricState>
{
public:

	NumericProviderStateHandlerGet(std::string p_descriptorHandle)
	: SDCProviderMDStateHandler(p_descriptorHandle)
	{ }

	// Helper method
	NumericMetricState createState(double p_initialValue)
	{
		NumericMetricState t_newState{HANDLE_GET_METRIC};
		t_newState
			.setMetricValue(NumericMetricValue(MetricQuality(MeasurementValidity::Vld)).setValue(p_initialValue))
			.setActivationState(ComponentActivation::On);
		return t_newState;
	}

	// define how to react on a request for a state change. This handler should not be set, thus always return Fail.
	InvocationState onStateChangeRequest(const NumericMetricState&, const OperationInvocationContext& p_oic) override
	{
		// extract information from the incoming operation
		DebugOut(DebugOut::Default, "ExampleProvider") << "Operation invoked. Handle: " << p_oic.operationHandle << std::endl;
		return InvocationState::Fail;
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
};



class NumericProviderStateHandlerSet : public SDCProviderMDStateHandler<NumericMetricState>
{
public:

    NumericProviderStateHandlerSet(const std::string p_descriptorHandle)
	: SDCProviderMDStateHandler(p_descriptorHandle)
	{ }

    InvocationState onStateChangeRequest(const NumericMetricState & state, const OperationInvocationContext & oic) override
    {
    	// Invocation has been fired as WAITING when entering this method
    	notifyOperationInvoked(oic, InvocationState::Start);
    	// Do stuff
        DebugOut(DebugOut::Default, "ExampleProvider") << "Provider: handle_set received state change request. State's value: " << state.getMetricValue().getValue() << std::endl;
        // extract information from the incoming operation
        DebugOut(DebugOut::Default, "ExampleProvider") << "Operation invoked. Handle: " << oic.operationHandle << std::endl;
        // if success return Finished
        return InvocationState::Fin;  // Framework will update internal MDIB with the state's value and increase MDIB version
    }

    // Helper method
    NumericMetricState createState()
	{
        NumericMetricState t_newState{HANDLE_SET_METRIC};
        t_newState
            .setMetricValue(NumericMetricValue(MetricQuality(MeasurementValidity::Vld)).setValue(2.0))
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
		auto t_maxWeightState{getParentProvider().getMdState().findState<NumericMetricState>(HANDLE_SET_METRIC)};
		// check if result is valid
		if ((nullptr == t_maxWeightState) && (!t_maxWeightState->hasMetricValue())) {
			DebugOut(DebugOut::Default, "ExampleProvider") << "Maximum weight metric not found." << std::endl;
			return 0;
		}
		// In real applications, check if state has an observed value!
		return t_maxWeightState->getMetricValue().getValue();
	}
};


class StreamProviderStateHandler : public SDCProviderMDStateHandler<RealTimeSampleArrayMetricState>
{
public:

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

    // disallow set operation for this state
    InvocationState onStateChangeRequest(const RealTimeSampleArrayMetricState&, const OperationInvocationContext& p_oic) override
    {
    	// extract information from the incoming operation
    	DebugOut(DebugOut::Default, "ExampleProvider") << "Operation invoked. Handle: " << p_oic.operationHandle << std::endl;
    	return InvocationState::Fail;
    }

    // convenient update method
    void updateStateValue(const SampleArrayValue& p_newValue)
	{
        auto t_newState{createState()};
        t_newState.setMetricValue(p_newValue);

        updateState(t_newState);
    }
};

class StringProviderStateHandler : public SDCProviderMDStateHandler<StringMetricState>
{
public:
	StringProviderStateHandler(std::string p_descriptorHandle)
	: SDCProviderMDStateHandler(p_descriptorHandle)
	{ }

	InvocationState onStateChangeRequest(const StringMetricState& p_changedState, const OperationInvocationContext& p_oic) override
	{
		notifyOperationInvoked(p_oic, InvocationState::Start);
		// Do something if a state change is requested
		DebugOut(DebugOut::Default, "ExampleProvider") << "String state of provider state changed to " << p_changedState.getMetricValue().getValue() << std::endl;
		// return Finished if successful
		return InvocationState::Fin;
	}

	// Helper method
	StringMetricState createState()
	{
		StringMetricState t_newState{HANDLE_STRING_METRIC};
		t_newState.setMetricValue(StringMetricValue(MetricQuality(MeasurementValidity::Vld)).setValue("StringMetricValueInit"));
	    return t_newState;
	}

	StringMetricState getInitialState() override
	{
		return createState();
	}
};


class SDCStreamProvider : public Util::Task
{
public:

    SDCStreamProvider(SDCInstance_shared_ptr p_SDCInstance)
	: m_sdcProvider(p_SDCInstance)
	, m_streamMetricDescriptor{HANDLE_STREAM_METRIC,
    		    		CodedValue{"MDCX_EXAMPLE_STREAM"},
    		    		MetricCategory::Msrmt,
    		    		MetricAvailability::Cont,
    		    		1,
    		    		xml_schema::Duration{0,0,0,0,0,0,1}}
    , m_setMetricDescriptor{HANDLE_SET_METRIC,
						CodedValue{"MDCX_EXAMPLE_SET"},
						MetricCategory::Set,
						MetricAvailability::Cont,
						1.0}
    , m_getMetricDescriptor{HANDLE_GET_METRIC,
				CodedValue{"MDCX_EXAMPLE_GET"},
				MetricCategory::Set,
				MetricAvailability::Cont,
				1}
    , m_stringMetricDescriptor{HANDLE_STRING_METRIC,
						CodedValue{"MDCX_EXAMPLE_STRING"},
						MetricCategory::Set,
						MetricAvailability::Cont}
    {

		m_sdcProvider.setEndpointReferenceByName(DEVICE_EPR);

		// set DPWS metadata, e.g. for the displayed friendly name
		Dev::DeviceCharacteristics devChar;
		devChar.addFriendlyName("en", "SDCLib C ExampleProvider");
		devChar.setManufacturer("SurgiTAIX AG");
		devChar.addModelName("en", "sdcDeviceNo1");
		m_sdcProvider.setDeviceCharacteristics(devChar);

        // Channel
        ChannelDescriptor holdingDeviceParameters{CHANNEL_DESCRIPTOR_HANDLE};
        holdingDeviceParameters
        	.setSafetyClassification(SafetyClassification::MedB)
			.addMetric(m_streamMetricDescriptor)
			.addMetric(m_setMetricDescriptor)
			.addMetric(m_getMetricDescriptor)
			.addMetric(m_stringMetricDescriptor);


        // VMD
        VmdDescriptor holdingDeviceModule{VMD_DESCRIPTOR_HANDLE};
        holdingDeviceModule.addChannel(holdingDeviceParameters);

        // MDS
        MdsDescriptor holdingDeviceSystem{MDS_DESCRIPTOR_HANDLE};
        holdingDeviceSystem
        	.setType(CodedValue{"MDC_DEV_DOCU_POSE_MDS"}.addConceptDescription(LocalizedText{"DOCU POSE"}.setLang("en")))
        	.setMetaData(
                MetaData().addManufacturer(LocalizedText{SDCLib::Config::STR_SURGITAIX})
                .setModelNumber("1")
                .addModelName(LocalizedText{"EndoTAIX"})
                .addSerialNumber(SDCLib::Config::CURRENT_C_YEAR))
        	.addVmd(holdingDeviceModule);


        m_sdcProvider.createSetOperationForDescriptor(m_setMetricDescriptor, holdingDeviceSystem);

        // create and add description
		MdDescription mdDescription;
		mdDescription.addMdsDescriptor(holdingDeviceSystem);

		m_sdcProvider.setMdDescription(mdDescription);

        // Add handler
		m_sdcProvider.addMdStateHandler(&m_numericProviderStateHandlerGet);
		m_sdcProvider.addMdStateHandler(&m_streamProviderStateHandler);

		m_sdcProvider.addMdStateHandler(&m_numericProviderStateHandlerSet);
		m_sdcProvider.addMdStateHandler(&m_stringProviderStateHandler);

    }

    void startup()
    {
    	m_sdcProvider.startup();
    }

    void updateStateValue(const SampleArrayValue& p_newValue)
    {
    	m_streamProviderStateHandler.updateStateValue(p_newValue); // updates handles and the parent provider
    }

private:

    SDCProvider m_sdcProvider;

    StreamProviderStateHandler m_streamProviderStateHandler{HANDLE_STREAM_METRIC};
    StringProviderStateHandler m_stringProviderStateHandler{HANDLE_STRING_METRIC};
    NumericProviderStateHandlerGet m_numericProviderStateHandlerGet{HANDLE_GET_METRIC};
    NumericProviderStateHandlerSet m_numericProviderStateHandlerSet{HANDLE_SET_METRIC};

    RealTimeSampleArrayMetricDescriptor m_streamMetricDescriptor;
    NumericMetricDescriptor m_setMetricDescriptor;
    NumericMetricDescriptor m_getMetricDescriptor;
    StringMetricDescriptor  m_stringMetricDescriptor;


public:

    // Produce stream values
    // runImpl() gets called when starting the provider thread by the inherited function start()
    void runImpl() override
    {

    	// RealTimeArray
		RealTimeValueType t_sampleValues(10);
		// Fill with values from [0,samples.size()]
		std::iota(t_sampleValues.begin(), t_sampleValues.end(), 0);

		std::size_t t_sampleIndex{0};

		while (!isInterrupted())
		{
			{
                updateStateValue(SampleArrayValue(MetricQuality(MeasurementValidity::Vld)).setSamples(t_sampleValues));
                DebugOut(DebugOut::Default, "ExampleProvider") << "Produced stream chunk of size " << t_sampleValues.size() << ", index " << t_sampleIndex << std::endl;
			}

			// Update the NumericMetricState's value using the state handler's method
			m_numericProviderStateHandlerGet.setNumericValue(t_sampleIndex/t_sampleValues.size());
			DebugOut(DebugOut::Default, "ExampleProvider") << "NumericMetric: value changed to " << t_sampleIndex/t_sampleValues.size() << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			t_sampleIndex += t_sampleValues.size();
		}
    }
};


int main()
{
	// Startup
	DebugOut(DebugOut::Default, "ExampleProvider") << "Startup" << std::endl;
    SDCLibrary::getInstance().startup(OSELib::LogLevel::Debug);

    // Create a new SDCInstance (no flag will auto init)
    auto t_SDCInstance = std::make_shared<SDCInstance>(true);

    // Some restriction
    t_SDCInstance->setIP6enabled(false);
    t_SDCInstance->setIP4enabled(true);
    // Bind it to interface that matches the internal criteria (usually the first enumerated)
    if(!t_SDCInstance->bindToDefaultNetworkInterface()) {
    	DebugOut(DebugOut::Default, "ExampleProvider") << "Failed to bind to default network interface! Exit..." << std::endl;
        return -1;
    }

	SDCStreamProvider provider{t_SDCInstance};
	provider.startup();
	provider.start();

	DebugOut(DebugOut::Default, "ExampleProvider") << "Press key to exit program.";
	std::cin.get();

	// Shutdown
	DebugOut(DebugOut::Default, "ExampleProvider") << "Shutdown." << std::endl;

    return 0;
}
