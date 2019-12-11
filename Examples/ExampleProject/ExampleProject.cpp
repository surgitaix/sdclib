
#include "SDCLib/SDCLibrary.h"
#include "SDCLib/SDCInstance.h"
#include "OSELib/SDC/SDCConstants.h"
#include "SDCLib/Data/SDC/SDCConsumer.h"
#include "SDCLib/Data/SDC/SDCConsumerMDStateHandler.h"
#include "SDCLib/Data/SDC/SDCProvider.h"
#include "SDCLib/Data/SDC/SDCProviderMDStateHandler.h"
#include "SDCLib/Data/SDC/SDCProviderComponentStateHandler.h"
#include "SDCLib/Data/SDC/FutureInvocationState.h"
#include "SDCLib/Data/SDC/MDIB/ChannelDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/CodedValue.h"
#include "SDCLib/Data/SDC/MDIB/MdsDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/MdsState.h"
#include "SDCLib/Data/SDC/MDIB/MdDescription.h"
#include "SDCLib/Data/SDC/MDIB/MetricQuality.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricState.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricValue.h"
#include "SDCLib/Data/SDC/MDIB/custom/OperationInvocationContext.h"
#include "SDCLib/Data/SDC/MDIB/StringMetricValue.h"
#include "SDCLib/Data/SDC/MDIB/LocalizedText.h"
#include "SDCLib/Data/SDC/MDIB/VmdDescriptor.h"
#include "SDCLib/Util/DebugOut.h"

#include "OSELib/SDC/ServiceManager.h"


#include <Poco/Thread.h>
#include <Poco/Runnable.h>


using namespace SDCLib;
using namespace SDCLib::Util;
using namespace SDCLib::Data::SDC;

// Endpoint reference of the device -> unique ID
const std::string DEVICE_EPR{"UDI-EXAMPLEPROJECT"};

// descriptor handles
const std::string MDS_HANDLE{"mds_handle"};
const std::string VMD_DESCRIPTOR_HANDLE{"vmd_handle"};

const std::string CHANNEL_DESCRIPTOR_HANDLE{"channel_handle"};
const std::string HANDLE_MAX_WEIGHT_METRIC{"handle_max"};
const std::string HANDLE_CURRENT_WEIGHT_METRIC{"handle_cur"};

const int WAIT_TIMEOUT_MS{2000};


class MaxValueStateHandler : public SDCProviderMDStateHandler<NumericMetricState>
{
public:

    MaxValueStateHandler(const std::string p_descriptorHandle)
	: SDCProviderMDStateHandler(p_descriptorHandle)
	{ }

    // called when the consumer is requesting to set the MaxValueStateHandler
    InvocationState onStateChangeRequest(const NumericMetricState&, const OperationInvocationContext& p_oic) override
    {
        // Invocation has been fired as WAITING when entering this method
        DebugOut(DebugOut::Default, "ExampleProject") << "Provider: MaxValueStateHandler received state change request";

        notifyOperationInvoked(p_oic, InvocationState::Start);

        // we can update here, but if we return FINISHED, the framework will also update
        //updateState(state);

        return InvocationState::Fin;  // Framework will update internal MDIB with the state's value and increase MDIB version
    }

    // Helper method
    NumericMetricState createState(double p_initialValue)
    {
        NumericMetricState t_newState{getDescriptorHandle()};
        t_newState
            .setMetricValue(NumericMetricValue{MetricQuality{MeasurementValidity::Vld}}.setValue(p_initialValue))
            .setActivationState(ComponentActivation::On);
        return t_newState;
    }

    // implement this method from the stateHandler interface
    // each defined state needs an initial state
    NumericMetricState getInitialState() override
    {
    	return createState(2.0);
    }

    // Convenience value getter
    double getMaxWeight()
    {
        auto t_numericMetricState{getParentProvider().getMdState().findState<NumericMetricState>(HANDLE_MAX_WEIGHT_METRIC)};
        if ((t_numericMetricState != nullptr) && t_numericMetricState->hasMetricValue())
        {
        	return t_numericMetricState->getMetricValue().getValue();
        }
        DebugOut(DebugOut::Default, "ExampleProject") << "No observed value" << std::endl;
        return 0;
    }
};




class CurValueStateHandler : public SDCProviderMDStateHandler<NumericMetricState>
{
public:

    CurValueStateHandler(const std::string p_descriptorHandler)
	: SDCProviderMDStateHandler(p_descriptorHandler)
	{ }

    // state is read-only - MEASUREMENT -> onStateChangeRequest() returns Fail
    InvocationState onStateChangeRequest(const NumericMetricState&, const OperationInvocationContext&)
    {
    	return InvocationState::Fail;
    }

    // Helper method
    NumericMetricState createState(double p_initialValue)
    {
        NumericMetricState t_newState{getDescriptorHandle()};
        t_newState
            .setMetricValue(NumericMetricValue{MetricQuality{MeasurementValidity::Inv}}.setValue(p_initialValue))
            .setActivationState(ComponentActivation::On);
        return t_newState;
    }

    // implement this method from the stateHandler interface
    // each defined state needs an initial state
    NumericMetricState getInitialState() override
    {
        return createState(0);
    }

    void setNumericValue(double p_newValue)
    {
        auto t_currentWeightState{createState(p_newValue)};
        // Call update function (this will update internal MDIB and increase MDIB version number)
        updateState(t_currentWeightState);
    }

};


class MdsStateHandler : public SDCProviderComponentStateHandler<MdsState>
{
public:
    MdsStateHandler(const std::string p_descriptorHandle)
    : SDCProviderComponentStateHandler(p_descriptorHandle)
	{ }

    // implement this method from the stateHandler interface
    // each defined state needs an initial state
    MdsState getInitialState() override
    {
    	return {getDescriptorHandle()};
    }
};


// This example shows one way of implementing the Provider
// Since the SDCProvider class is final, it is recommended to implement the SDCProvider as a member variable of a container class to expand the SDCProvider in a clear and convinient fashion
class SDCHoldingDeviceProvider
{
public:

    SDCHoldingDeviceProvider(SDCInstance_shared_ptr p_SDCInstance)
	: m_sdcProvider(p_SDCInstance)
	{
    	m_sdcProvider.setEndpointReferenceByName(DEVICE_EPR);
        // Define semantic meaning of weight unit "kg", which will be used for defining the
        // current weight and the max weight below.

    	// mandatory properties in constructor
        CodedValue unit{"MDCX_CODE_ID_KG"};
        // additional properties using method chaining
        unit.setCodingSystem("OR.NET.Codings")
        	.addConceptDescription(LocalizedText{"Unit in KG"}.setRef("uri/to/file.txt").setLang("en"));

    	//
        // Setup metric descriptors
        //

        // The current weight: mandatory properties
        NumericMetricDescriptor currentWeightMetric{HANDLE_CURRENT_WEIGHT_METRIC,
        		unit,
        		MetricCategory::Msrmt,
        		MetricAvailability::Cont,
        		1.0};

        // Maximum weight: mandatory properties
    	NumericMetricDescriptor maxWeightMetric{HANDLE_MAX_WEIGHT_METRIC,
        		unit,
        		MetricCategory::Set,
        		MetricAvailability::Cont,
        		1.0};

        // Channel
        ChannelDescriptor holdingDeviceChannel{CHANNEL_DESCRIPTOR_HANDLE};
        holdingDeviceChannel
			.addMetric(currentWeightMetric)
        	.addMetric(maxWeightMetric)
        	.setSafetyClassification(SafetyClassification::MedA);

        // VMD
        VmdDescriptor holdingDeviceModule{VMD_DESCRIPTOR_HANDLE};
        holdingDeviceModule
			.addChannel(holdingDeviceChannel);

        // MDS
        MdsDescriptor holdingDeviceSystem{MDS_HANDLE};
        holdingDeviceSystem
			.addVmd(holdingDeviceModule)
			.setType(CodedValue{"MDCX_CODE_ID_MDS"}.setCodingSystem("OR.NET.Codings"));

        // the set operations have to be defined before adding the MdDescription
        m_sdcProvider.createSetOperationForDescriptor(maxWeightMetric, holdingDeviceSystem);

        // add descriptor to description
        // the description contains all the devices static information
        MdDescription holdingDeviceDescription;
        holdingDeviceDescription.addMdsDescriptor(holdingDeviceSystem);


        // set the providers description
        m_sdcProvider.setMdDescription(holdingDeviceDescription);

        // set DPWS metadata, e.g. for the displayed friendly name
		Dev::DeviceCharacteristics devChar;
		devChar.addFriendlyName("en", "SDCLib C ExampleProvider");
		devChar.setManufacturer("SurgiTAIX AG");
		devChar.addModelName("en", "sdcDeviceNo1");
		m_sdcProvider.setDeviceCharacteristics(devChar);

		// State handler
		m_sdcProvider.addMdStateHandler(&m_maxValueState);
		m_sdcProvider.addMdStateHandler(&m_curValueState);
		m_sdcProvider.addMdStateHandler(&m_mdsState);
    }

    void startup()
    {
    	m_sdcProvider.startup();
    }

    void setCurrentWeight(double p_newWeight)
    {
    	std::lock_guard<std::mutex> t_lock{m_mutex}; // FIXME: changed from SDCProvider mutex to internal mutex
    	m_currentWeight = p_newWeight;
    	m_curValueState.setNumericValue(p_newWeight);
        DebugOut(DebugOut::Default, "ExampleProject") << "Changed value: " << m_currentWeight << std::endl;
    }

private:

    std::mutex m_mutex;
    // SDCProvider for communication to the network
    SDCProvider m_sdcProvider;

    std::atomic<double> m_currentWeight{0};

    MaxValueStateHandler m_maxValueState{HANDLE_MAX_WEIGHT_METRIC};
    CurValueStateHandler m_curValueState{HANDLE_CURRENT_WEIGHT_METRIC};

    MdsStateHandler m_mdsState{MDS_HANDLE};
};


// The DummyValueProducer produces some some increasing values in a separate thread
class DummyValueProducer : public Poco::Runnable
{
private:
	std::atomic<bool> m_isInterrupted{false};
    SDCHoldingDeviceProvider* m_provider{nullptr};
    std::atomic<double> m_currentWeight{0};
    Poco::Thread m_thread;

public:
	DummyValueProducer(SDCHoldingDeviceProvider* p_provider)
	: m_provider(p_provider)
	{ }

    // Update weight periodically
    void run()
    {
    	DebugOut(DebugOut::Default, "ExampleProject") << "Thread started." << std::endl;
        while (!m_isInterrupted)
        {
        	m_provider->setCurrentWeight(m_currentWeight);
        	m_currentWeight = m_currentWeight + 0.1;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }

	void start()
	{
		m_thread.start(*this);
	}

	void interrupt()
	{
		m_isInterrupted = true;
		m_thread.join();
	}
};




// ExampleConsumerEventHandler extends SDCConsumerMDStateHandler, which is instanciated for NumericMetricState
// It's methods onStateChanged and onOperationInvoked are called from within this framework, each time the value is changed by the provider
// All event handlers have to be registered, please see below.
class ExampleConsumerEventHandler : public SDCConsumerMDStateHandler<NumericMetricState>
{
private:
    std::atomic<double> m_currentWeight{0};

public:
    ExampleConsumerEventHandler(const std::string p_descriptorHandle)
	: SDCConsumerMDStateHandler(p_descriptorHandle)
	{ }

    // this method is called when a value changed in the provider
    void onStateChanged(const NumericMetricState& p_changedState) override
    {
    	m_currentWeight = p_changedState.getMetricValue().getValue();
        DebugOut(DebugOut::Default, "ExampleProject") << "Consumer: Received value changed of " << getDescriptorHandle() << ": " << m_currentWeight << std::endl;
    }

    // this method is called each time an operation (e.g. a set operation) is called by the provider
    // use to customize the handling of your code, e.g. log/ prompt a message, do validity checks, ect.
    void onOperationInvoked(const OperationInvocationContext& oic, InvocationState is) override
    {
        DebugOut(DebugOut::Default, "ExampleProject") << "Consumer: Received operation invoked (ID, STATE) of " << getDescriptorHandle() << ": " << oic.transactionId << ", " << Data::SDC::EnumToString::convert(is);
    }

    double getCurrentWeight() const
    {
        return m_currentWeight;
    }
};


class MyHandler : public OSELib::SDC::HelloReceivedHandler
{
public:

	void helloReceived(const std::string& p_newEPR) override
	{
		DebugOut(DebugOut::Default, "ExampleProject") << "Hello received! EPR: " << p_newEPR << std::endl;
	}
};

int main()
{
	SDCLibrary::getInstance().startup(OSELib::LogLevel::Error);

    // Create a new SDCInstance (no flag will auto init)
    auto t_SDCInstanceConsumer = std::make_shared<SDCInstance>(true);
    // Some restriction
    t_SDCInstanceConsumer->setIP6enabled(false);
    t_SDCInstanceConsumer->setIP4enabled(true);
    // Bind it to interface that matches the internal criteria (usually the first enumerated)
    if(!t_SDCInstanceConsumer->bindToDefaultNetworkInterface())
    {
        std::cout << "Failed to bind to default network interface! Exit..." << std::endl;
        return -1;
    }

	OSELib::SDC::ServiceManager t_serviceManager{t_SDCInstanceConsumer};

	std::unique_ptr<MyHandler> myHandler(new MyHandler());
	t_serviceManager.setHelloReceivedHandler(myHandler.get());

    // Create a new SDCInstance (no flag will auto init)
    auto t_SDCInstanceProvider = std::make_shared<SDCInstance>(true);
    // Some restriction
    t_SDCInstanceProvider->setIP6enabled(false);
    t_SDCInstanceProvider->setIP4enabled(true);

    // Bind it to interface that matches the internal criteria (usually the first enumerated)
    if(!t_SDCInstanceProvider->bindToDefaultNetworkInterface())
    {
        std::cout << "Failed to bind to default network interface! Exit..." << std::endl;
        return -1;
    }

    // Provider
	SDCHoldingDeviceProvider provider{t_SDCInstanceProvider};
	provider.startup();
	DummyValueProducer dummyValueProducer{&provider};
	dummyValueProducer.start();

	DebugOut(DebugOut::Default, "ExampleProject") << "Press key to proceed test (until then, provider will keep running indefinitely).";
	std::cin.get();

	// Note: Calculate a UUIDv5 and apply prefix to it!
	auto t_consumer{t_serviceManager.discoverEndpointReference(SDCInstance::calcUUIDv5(DEVICE_EPR, true))};
	// alternatively: search the whole network
	// std::vector<std::unique_ptr<SDCConsumer>> consumers(t_serviceManager.discover());

	if (t_consumer != nullptr)
	{
		SDCConsumer& consumer = *t_consumer;

		// Register for metric event
		auto eces1 = std::make_shared<ExampleConsumerEventHandler>(HANDLE_CURRENT_WEIGHT_METRIC);
		auto eces2 = std::make_shared<ExampleConsumerEventHandler>(HANDLE_MAX_WEIGHT_METRIC);
		consumer.registerStateEventHandler(eces1.get());
		consumer.registerStateEventHandler(eces2.get());

		// wait for the subscriptions to be completed
		Util::DebugOut(Util::DebugOut::Default, "ExampleProject") << "Discovery succeeded.\n\nWaiting 2 sec. for the subscriptions to beeing finished" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));

		// Get state test (current weight)
		auto t_currentWeightState{consumer.requestState<NumericMetricState>(HANDLE_CURRENT_WEIGHT_METRIC)};
		if(nullptr == t_currentWeightState)
		{
			DebugOut(DebugOut::Default, "ExampleProject") << "Weight State not found!";
			return -1;
		}
		if(!t_currentWeightState->hasMetricValue())
		{
			DebugOut(DebugOut::Default, "ExampleProject") << "Weight State has no MetricValue!";
			return -1;
		}
		auto curWeight{t_currentWeightState->getMetricValue().getValue()};
		DebugOut(DebugOut::Default, "ExampleProject") << "Observed Weight " << curWeight;

		try
		{
			// Set state test (must fail due to read-only)
			InvocationState invocationStateFirst = consumer.commitState(*t_currentWeightState);
			DebugOut(DebugOut::Default, "ExampleProject") << "InvocationState (1st commit): " << Data::SDC::EnumToString::convert(invocationStateFirst);
			if (InvocationState::Fail == invocationStateFirst)
			{
				DebugOut(DebugOut::Default, "ExampleProject") << "Committing state failed as expected.";
			}
			else
			{
				DebugOut(DebugOut::Default, "ExampleProject") << "Committing state succeeded. This is an error, because it should be read-only.";
			}
		}
		catch (const std::runtime_error & e)
		{
			DebugOut(DebugOut::Default, "ExampleProject") << "Exception";
		}
		// Get state test (maximum weight)
		auto t_maxWeightState{consumer.requestState<NumericMetricState>(HANDLE_MAX_WEIGHT_METRIC)};
		if(nullptr == t_maxWeightState)
		{
			DebugOut(DebugOut::Default, "ExampleProject") << "Max weight value state not found!";
			return -1;
		}
		if(!t_maxWeightState->hasMetricValue())
		{
			DebugOut(DebugOut::Default, "ExampleProject") << "Max weight state has no MetricValue!";
			return -1;
		}
		auto maxWeight{t_maxWeightState->getMetricValue().getValue()};
		DebugOut(DebugOut::Default, "ExampleProject") << "Max weight value: "<< maxWeight;

		// Set state test (must succeed)
		// Expected States: Wait -> Start -> Fin as implemented in MaxValueStateHandler

		bool t_stateFinReached{false};
		FutureInvocationState t_fis;
		auto invocationStateSecond = consumer.commitState(*t_maxWeightState, t_fis);
		if(invocationStateSecond == InvocationState::Wait)
		{
			DebugOut(DebugOut::Default, "ExampleProject") << "InvocationState (2nd commit): Wait";
			if(t_fis.waitReceived(InvocationState::Start, WAIT_TIMEOUT_MS))
			{
				DebugOut(DebugOut::Default, "ExampleProject") << "InvocationState (2nd commit): Start";
				if(t_fis.waitReceived(InvocationState::Fin, WAIT_TIMEOUT_MS))
				{
					t_stateFinReached = true;
					DebugOut(DebugOut::Default, "ExampleProject") << "InvocationState (2nd commit): Fin";
				}
			}
		}

		// Something went wrong
		if(t_stateFinReached)
		{
			DebugOut(DebugOut::Default, "ExampleProject") << "Committing state succeeded as expected.\n";
		}
		else
		{
			DebugOut(DebugOut::Default, "ExampleProject") << "InvocationState (2nd commit): FAILED TO REACH \"FIN STATE\"!\n";
		}

		// Cleanup
		consumer.unregisterStateEventHandler(eces1.get());
		consumer.unregisterStateEventHandler(eces2.get());
		consumer.disconnect();
	}
	else
	{
		DebugOut(DebugOut::Default, "ExampleProject") << "Discovery failed." << std::endl;
		return -1;
	}

	DebugOut(DebugOut::Default, "\nExampleProject") << "Shutdown.\n" << std::endl;
	t_serviceManager.setHelloReceivedHandler(nullptr);
	dummyValueProducer.interrupt();

	return 0;
}
