
#include "OSCLib/OSCLibrary.h"
#include "OSCLib/Data/OSCP/OSCPConstants.h"
#include "OSCLib/Data/OSCP/OSCPConsumer.h"
#include "OSCLib/Data/OSCP/OSCPConsumerEventHandler.h"
#include "OSCLib/Data/OSCP/OSCPConsumerNumericMetricStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPProvider.h"
#include "OSCLib/Data/OSCP/OSCPProviderNumericMetricStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPProviderComponentStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPProviderHydraMDSStateHandler.h"
#include "OSCLib/Data/OSCP/MDIB/ChannelDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/ComponentState.h"
#include "OSCLib/Data/OSCP/MDIB/HydraMDSDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/HydraMDSState.h"
#include "OSCLib/Data/OSCP/MDIB/MDDescription.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricValue.h"
#include "OSCLib/Data/OSCP/MDIB/OperationInvocationContext.h"
#include "OSCLib/Data/OSCP/MDIB/StringMetricValue.h"
#include "OSCLib/Data/OSCP/MDIB/SystemContext.h"
#include "OSCLib/Data/OSCP/MDIB/LocalizedText.h"
#include "OSCLib/Data/OSCP/MDIB/VMDDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayMetricState.h"
#include "OSCLib/Util/DebugOut.h"

#include "OSELib/OSCP/ServiceManager.h"

#include "Poco/Mutex.h"
#include "Poco/ScopedLock.h"
#include "Poco/Thread.h"
#include "Poco/Runnable.h"
#include "Poco/Net/NetException.h"

using namespace OSCLib;
using namespace OSCLib::Util;
using namespace OSCLib::Data::OSCP;

const std::string deviceEPR("UDI_12345");

const std::string MDS_HANDLE("mds_handle");
const std::string VMD_DESCRIPTOR_HANDLE("vmd_handle");
const std::string CHANNEL_DESCRIPTOR_HANDLE("channel_handle");

class MaxValueStateHandler : public OSCPProviderNumericMetricStateHandler {
public:

    MaxValueStateHandler() {
    }

    InvocationState onStateChangeRequest(const NumericMetricState & state, const OperationInvocationContext & oic) override {
        // Invocation has been fired as WAITING when entering this method
        DebugOut(DebugOut::Default, "SimpleOSCP") << "Provider: MaxValueStateHandler received state change request" << std::endl;

        notifyOperationInvoked(oic, InvocationState::STARTED);

        // we can update here, but if we return FINISHED, the framework will also update
        //updateState(state);

        // Usually, update the real device's state here.

        return InvocationState::FINISHED;  // Framework will update internal MDIB with the state's value and increase MDIB version
    }

    // Helper method
    NumericMetricState createState() {
        NumericMetricState result;
        result
            .setObservedValue(NumericMetricValue().setValue(2.0))
            .setComponentActivationState(ComponentActivation::ON)
            .setDescriptorHandle("handle_max")
            .setHandle("handle_max_state");
        return result;
    }

    NumericMetricState getInitialState() override {
        NumericMetricState result = createState();
        return result;
    }

    // Convenience value getter
    float getMaxWeight() {
        NumericMetricState result;
        // TODO: in real applications, check if findState returns true!
        getParentProvider().getMDState().findState("handle_max", result);
        // TODO: in real applications, check if state has an observed value and if the observed value has a value!
        return (float)result.getObservedValue().getValue();
    }

};

class CurValueStateHandler : public OSCPProviderNumericMetricStateHandler {
public:

    CurValueStateHandler() {
    }

    // onStateChangeRequest not implemented (state is read-only - MEASUREMENT)

    // Helper method
    NumericMetricState createState(float value) {
        NumericMetricState result;
        result
            .setObservedValue(NumericMetricValue().setValue(value))
            .setComponentActivationState(ComponentActivation::ON)
            .setDescriptorHandle("handle_cur");
        return result;
    }

    NumericMetricState getInitialState() override {
        return createState(0);
    }

    void setNumericValue(float value) {
        NumericMetricState currentWeightState = createState(value);
        // Call update function (this will update internal MDIB and increase MDIB version number)
        updateState(currentWeightState);
    }

};

class AlwaysOnComponentStateHandler : public OSCPProviderComponentStateHandler {
public:
    AlwaysOnComponentStateHandler(const std::string & descriptorHandle) {
        this->descriptorHandle = descriptorHandle;
    }

    // Helper method
    ComponentState createState() {
        ComponentState result;
        result
            .setDescriptorHandle(descriptorHandle)
            .setComponentActivationState(ComponentActivation::ON);
        return result;
    }

    virtual ComponentState getInitialState() override {
        ComponentState state = createState();
        return state;
    }

private:
    std::string descriptorHandle;
};

class AlwaysOnHydraMDSStateHandler : public OSCPProviderHydraMDSStateHandler {
public:
    AlwaysOnHydraMDSStateHandler(const std::string & descriptorHandle) {
        this->descriptorHandle = descriptorHandle;
    }

    // Helper method
    HydraMDSState createState() {
        HydraMDSState result;
        result
            .setDescriptorHandle(descriptorHandle)
            .setComponentActivationState(ComponentActivation::ON);
        return result;
    }

    virtual HydraMDSState getInitialState() override {
        HydraMDSState state = createState();
        return state;
    }

private:
    std::string descriptorHandle;
};


// This example shows one elegant way of implementing the Provider
// Since the OSCPProvider class is final, it is recommended to implement the OSCPProvider as a member variable of a container class to expand the OSCPProvider in a clear and convinient fashion
class OSCPHoldingDeviceProvider {
public:

    OSCPHoldingDeviceProvider() :
    	oscpProvider(),
		currentWeight(0),
		channelState(CHANNEL_DESCRIPTOR_HANDLE),
    	hydraMDSState(MDS_HANDLE),
    	vmdState(VMD_DESCRIPTOR_HANDLE)
	{
    	oscpProvider.setEndpointReference(deviceEPR);
        // Define semantic meaning of weight unit "kg", which will be used for defining the
        // current weight and the max weight below.
        CodedValue unit;
        unit	.setCodeId("MDCX_CODE_ID_KG")
				.setCodingSystemId("OR.NET.Codings")
        		.addConceptDescription(LocalizedText().set("Weight in kg"));

    	//
        // Setup metric descriptors
        //

        // define properties of current weight metric
        currentWeightMetric
			.setMetricCategory(MetricCategory::MEASUREMENT)
        	.setAvailability(MetricAvailability::CONTINUOUS)
			.setUnit(unit)
			.setType(
				CodedValue()
				.setCodeId("MDCX_CODE_ID_WEIGHT")
				.addConceptDescription(LocalizedText().set("Current weight")))
	        .setHandle("handle_cur");

        // define properties of max weight metric
        maxWeightMetric
			.setMetricCategory(MetricCategory::SETTING)
        	.setAvailability(MetricAvailability::CONTINUOUS)
        	.setUnit(unit)
			.setType(
        		CodedValue()
				.addConceptDescription(LocalizedText().set("Maximum weight")))
        	.setHandle("handle_max");

        // Channel
        ChannelDescriptor holdingDeviceChannel;
        holdingDeviceChannel
			.setHandle(CHANNEL_DESCRIPTOR_HANDLE)
			.addMetric(currentWeightMetric)
        	.addMetric(maxWeightMetric)
			.setIntendedUse(IntendedUse::MEDICAL_A);

        // VMD
        VMDDescriptor holdingDeviceModule;
        holdingDeviceModule
			.setHandle(VMD_DESCRIPTOR_HANDLE)
			.addChannel(holdingDeviceChannel);

        // MDS
        HydraMDSDescriptor holdingDeviceSystem;
        holdingDeviceSystem
			.setHandle(MDS_HANDLE)
			.addVMD(holdingDeviceModule)
			.setType(
				CodedValue()
				.setCodingSystemId("OR.NET.Codings")
				.setCodeId("MDCX_CODE_ID_MDS"));


        // add descriptor to description
        // the description contains all the devices static information
        MDDescription holdingDeviceDescription;
        holdingDeviceDescription.addMDSDescriptor(holdingDeviceSystem);


        // set the providers description
        oscpProvider.setMDDescrition(holdingDeviceDescription);

        oscpProvider.createSetOperationForDescriptor(maxWeightMetric, holdingDeviceSystem);


		// State handler
        oscpProvider.addMDStateHandler(&maxValueState);
        oscpProvider.addMDStateHandler(&curValueState);
        oscpProvider.addMDStateHandler(&channelState);
        oscpProvider.addMDStateHandler(&hydraMDSState);
        oscpProvider.addMDStateHandler(&vmdState);


    }

    void startup() {
    	oscpProvider.startup();
    }

    void shutdown() {
    	oscpProvider.shutdown();
    }

    void setCurrentWeight(float value) {
    	Poco::Mutex::ScopedLock lock(oscpProvider.getMutex());
    	currentWeight = value;
        curValueState.setNumericValue(value);
        DebugOut(DebugOut::Default, "ExampleProject") << "Changed value: " << currentWeight << std::endl;
    }

private:

    // OSCPProvider for communication to the network
    OSCPProvider oscpProvider;

    float currentWeight;

    // The current weight
    NumericMetricDescriptor currentWeightMetric;

    // Maximum weight
	NumericMetricDescriptor maxWeightMetric;

    MaxValueStateHandler maxValueState;
    CurValueStateHandler curValueState;

    AlwaysOnComponentStateHandler channelState;
    AlwaysOnHydraMDSStateHandler hydraMDSState;
    AlwaysOnComponentStateHandler vmdState;
};

class DummyValueProducer : public Poco::Runnable {
public:
	DummyValueProducer(OSCPHoldingDeviceProvider * provider) :
		isInterrupted(false),
		provider(provider),
		currentWeight(0)
	{
	}

    // Update weight periodically
    void run() {
    	DebugOut(DebugOut::Default, "ExampleProject") << "\nThread started." << std::endl;
        while (!isInterrupted) {
        	provider->setCurrentWeight(currentWeight);
        	currentWeight += 0.1f;
            Poco::Thread::sleep(1000);
        }
    }

	void start() {
		thread.start(*this);
	}

	void interrupt() {
		isInterrupted = true;
		thread.join();
	}

private:
	Poco::Thread thread;
	bool isInterrupted;
    OSCPHoldingDeviceProvider * provider;
    float currentWeight;
};

class ExampleConsumerEventHandler : public OSCPConsumerNumericMetricStateHandler {
public:
    ExampleConsumerEventHandler(const std::string & handle) :
    	currentWeight(0),
		handle(handle)
	{
    }

    void onStateChanged(const NumericMetricState & state) override {
        double val = state.getObservedValue().getValue();
        DebugOut(DebugOut::Default, "ExampleProject") << "Consumer: Received value changed of " << handle << ": " << val << std::endl;
        currentWeight = (float)val;
    }

    void onOperationInvoked(const OperationInvocationContext & oic, InvocationState is) override {
        DebugOut(DebugOut::Default, "ExampleProject") << "Consumer: Received operation invoked (ID, STATE) of " << handle << ": " << oic.transactionId << ", " << Data::OSCP::EnumToString::convert(is) << std::endl;
    }

    std::string getHandle() override {
        return handle;
    }

    float getCurrentWeight() {
        return currentWeight;
    }

private:
    float currentWeight;
    const std::string handle;
};


int main()
{

	DebugOut(DebugOut::Default, "ExampleProject") << "1";
	try {
		OSCLibrary::getInstance().startup();
		DebugOut(DebugOut::Default, "ExampleProject") << "2";
		OSCLibrary::getInstance().setPortStart(11000);

		OSELib::OSCP::ServiceManager oscpsm;
		class MyHandler : public OSELib::OSCP::HelloReceivedHandler {
		public:
			MyHandler() {
			}
			void helloReceived(const std::string & epr) override {
				DebugOut(DebugOut::Default, "ExampleProject") << "Hello received! EPR: " << epr;
			}
		};
		std::unique_ptr<MyHandler> myHandler(new MyHandler());
		DebugOut(DebugOut::Default, "ExampleProject") << "3";
		oscpsm.setHelloReceivedHandler(myHandler.get());
		// Provider
		OSCPHoldingDeviceProvider provider;
		provider.startup();
		DebugOut(DebugOut::Default, "ExampleProject") << "4";
		DummyValueProducer dummyValueProducer(&provider);
		dummyValueProducer.start();
		DebugOut(DebugOut::Default, "ExampleProject") << "5";

		int temp;
		DebugOut(DebugOut::Default, "ExampleProject") << "Press key to proceed test (until then, provider will keep running indefinitely).";
		std::cin >> temp;

		// Discovery
		std::shared_ptr<OSCPConsumer> c(oscpsm.discoverEndpointReference(deviceEPR));
		DebugOut(DebugOut::Default, "ExampleProject") << "6";
		std::shared_ptr<ExampleConsumerEventHandler> eces1(new ExampleConsumerEventHandler("handle_cur"));
		std::shared_ptr<ExampleConsumerEventHandler> eces2(new ExampleConsumerEventHandler("handle_max"));
		DebugOut(DebugOut::Default, "ExampleProject") << "7";


		if (c != nullptr) {
			OSCPConsumer & consumer = *c;
			DebugOut(DebugOut::Default, "ExampleProject") << "Discovery succeeded.";

			// MDIB test
			MDIBContainer mdib = consumer.getMDIB();

			// Register for metric event
			consumer.registerStateEventHandler(eces1.get());
			consumer.registerStateEventHandler(eces2.get());

			Poco::Thread::sleep(4000);

			// Get state test (current weight)
			NumericMetricState currentWeightState;
			consumer.requestState("handle_cur", currentWeightState);
			double curWeight = currentWeightState.getObservedValue().getValue();
			DebugOut(DebugOut::Default, "ExampleProject") << "Observed Weight " << curWeight;

			// Set state test (must fail due to read-only)
			InvocationState invocationStateFirst = consumer.commitState(currentWeightState);
			DebugOut(DebugOut::Default, "ExampleProject") << "InvocationState (1st commit): " << Data::OSCP::EnumToString::convert(invocationStateFirst);
			if (InvocationState::FAILED == invocationStateFirst) {
				DebugOut(DebugOut::Default, "ExampleProject") << "Committing state failed as expected.";
			} else {
				DebugOut(DebugOut::Default, "ExampleProject") << "Committing state succeeded. This is an error, because it should be read-only.";
			}

			// Get state test (maximum weight)
			NumericMetricState maxWeightState;
			consumer.requestState("handle_max", maxWeightState);
			double maxWeight = maxWeightState.getObservedValue().getValue();
			DebugOut(DebugOut::Default, "ExampleProject") << "Max weight value: "<< maxWeight;

			// Set state test (must succeed)
			InvocationState invocationStateSecond  = consumer.commitState(maxWeightState);
			DebugOut(DebugOut::Default, "ExampleProject") << "InvocationState (2nd commit): " << Data::OSCP::EnumToString::convert(invocationStateSecond);

			Poco::Thread::sleep(1000);
			consumer.unregisterStateEventHandler(eces1.get());
			consumer.unregisterStateEventHandler(eces2.get());
			Poco::Thread::sleep(4000);

			consumer.disconnect();
		} else {
			DebugOut(DebugOut::Default, "ExampleProject") << "Discovery failed.";
		}

		oscpsm.setHelloReceivedHandler(nullptr);

		dummyValueProducer.interrupt();
		provider.shutdown();
		Poco::Thread::sleep(2000);

		OSCLibrary::getInstance().shutdown();
	} catch (Poco::Net::NetException & e) {
		DebugOut(DebugOut::Default, "ExampleProject") << "what:" << e.what() << std::endl;
		DebugOut(DebugOut::Default, "ExampleProject") << "className:" << e.className() << std::endl;
		DebugOut(DebugOut::Default, "ExampleProject") << "code:" << e.code() << std::endl;
		DebugOut(DebugOut::Default, "ExampleProject") << "displayText:" << e.displayText() << std::endl;
		DebugOut(DebugOut::Default, "ExampleProject") << "message:" << e.message() << std::endl;
		DebugOut(DebugOut::Default, "ExampleProject") << "name:" << e.name() << std::endl;
	}
	DebugOut(DebugOut::Default, "ExampleProject") << "Shutdown." << std::endl;
}
