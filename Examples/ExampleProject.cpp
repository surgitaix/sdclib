
#include "OSCLib/OSCLibrary.h"
#include "OSELib/OSCP/OSCPConstants.h"
#include "OSCLib/Data/OSCP/OSCPConsumer.h"
#include "OSCLib/Data/OSCP/OSCPConsumerEventHandler.h"
#include "OSCLib/Data/OSCP/OSCPConsumerNumericMetricStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPProvider.h"
#include "OSCLib/Data/OSCP/OSCPProviderNumericMetricStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPProviderMdsStateHandler.h"
#include "OSCLib/Data/OSCP/MDIB/ChannelDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/MdsDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/MdsState.h"
#include "OSCLib/Data/OSCP/MDIB/MdDescription.h"
#include "OSCLib/Data/OSCP/MDIB/MetricQuality.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricValue.h"
#include "OSCLib/Data/OSCP/MDIB/custom/OperationInvocationContext.h"
#include "OSCLib/Data/OSCP/MDIB/StringMetricValue.h"
#include "OSCLib/Data/OSCP/MDIB/SystemContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/SystemContextState.h"
#include "OSCLib/Data/OSCP/MDIB/LocalizedText.h"
#include "OSCLib/Data/OSCP/MDIB/VmdDescriptor.h"
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

// Endpoint reference of the device -> unique ID
const std::string deviceEPR("UDI-1234567890");

// handles of the de
const std::string MDS_HANDLE("mds_handle");
const std::string VMD_DESCRIPTOR_HANDLE("vmd_handle");

const std::string CHANNEL_DESCRIPTOR_HANDLE("channel_handle");
const std::string HANDLE_MAX_WEIGHT_METRIC("handle_max");
const std::string HANDLE_CURRENT_WEIGHT_METRIC("handle_cur");


class MaxValueStateHandler : public OSCPProviderNumericMetricStateHandler {
public:

    MaxValueStateHandler() {
    }

    // called when the consumer is requesting to set the MaxValueStateHandler
    InvocationState onStateChangeRequest(const NumericMetricState & state, const OperationInvocationContext & oic) override {
        // Invocation has been fired as WAITING when entering this method
        DebugOut(DebugOut::Default, "ExampleProject") << "Provider: MaxValueStateHandler received state change request" << std::endl;

        notifyOperationInvoked(oic, InvocationState::Start);

        // we can update here, but if we return FINISHED, the framework will also update
        //updateState(state);

        return InvocationState::Fin;  // Framework will update internal MDIB with the state's value and increase MDIB version
    }

    // Helper method
    NumericMetricState createState() {
        NumericMetricState result(HANDLE_MAX_WEIGHT_METRIC);
        result
            .setMetricValue(NumericMetricValue(MetricQuality(MeasurementValidity::Vld)).setValue(2.0))
            .setActivationState(ComponentActivation::On);
        return result;
    }

    // implement this method from the stateHandler interface
    // each defined state needs an initial state
    NumericMetricState getInitialState() override {
        NumericMetricState result = createState();
        return result;
    }

    // Convenience value getter
    float getMaxWeight() {
        NumericMetricState result(HANDLE_MAX_WEIGHT_METRIC);
        if (getParentProvider().getMdState().findState(HANDLE_MAX_WEIGHT_METRIC, result) && result.hasMetricValue()) {
        	return (float)result.getMetricValue().getValue();
        } else {
        	DebugOut(DebugOut::Default, "ExampleProject") << "No observed value" << std::endl;
        	return 0;
        }
    }

};

class CurValueStateHandler : public OSCPProviderNumericMetricStateHandler {
public:

    CurValueStateHandler() {
    }

    // onStateChangeRequest not implemented (state is read-only - MEASUREMENT)

    // Helper method
    NumericMetricState createState(float value) {
        NumericMetricState result(HANDLE_MAX_WEIGHT_METRIC);
        result
            .setMetricValue(NumericMetricValue(MetricQuality(MeasurementValidity::Inv)).setValue(value))
            .setActivationState(ComponentActivation::On)
            .setDescriptorHandle(HANDLE_CURRENT_WEIGHT_METRIC);
        return result;
    }

    // implement this method from the stateHandler interface
    // each defined state needs an initial state
    NumericMetricState getInitialState() override {
        return createState(0);
    }

    void setNumericValue(float value) {
        NumericMetricState currentWeightState = createState(value);
        // Call update function (this will update internal MDIB and increase MDIB version number)
        updateState(currentWeightState);
    }

};


class MDSStateHandler : public OSCPProviderMdsStateHandler {
public:
    MDSStateHandler(const std::string & descriptorHandle) {
        this->descriptorHandle = descriptorHandle;
    }

    // Helper method
    MdsState createState() {
    	MdsState result(this->descriptorHandle);
        return result;
    }

    // implement this method from the stateHandler interface
    // each defined state needs an initial state
    virtual MdsState getInitialState() override {
    	MdsState state = createState();
        return state;
    }

private:
    std::string descriptorHandle;
};


// This example shows one way of implementing the Provider
// Since the OSCPProvider class is final, it is recommended to implement the OSCPProvider as a member variable of a container class to expand the OSCPProvider in a clear and convinient fashion
class OSCPHoldingDeviceProvider {
public:

    OSCPHoldingDeviceProvider() :
    	oscpProvider(),
		currentWeight(0),
    	mdsState(MDS_HANDLE)
//    	vmdState(VMD_DESCRIPTOR_HANDLE)
	{
    	oscpProvider.setEndpointReference(deviceEPR);
        // Define semantic meaning of weight unit "kg", which will be used for defining the
        // current weight and the max weight below.

    	// mandatory properties in costructor
        CodedValue unit("MDCX_CODE_ID_KG");
        // additional properties using method chaining
        unit	.setCodingSystem("OR.NET.Codings")
        		.addConceptDescription(LocalizedText().setRef("uri/to/file.txt").setLang("en"));

    	//
        // Setup metric descriptors
        //

        // The current weight: mandatory properties
        NumericMetricDescriptor currentWeightMetric(HANDLE_CURRENT_WEIGHT_METRIC,
        		unit,
        		MetricCategory::Msrmt,
        		MetricAvailability::Cont,
        		1.0);

        // Maximum weight: mandatory properties
    	NumericMetricDescriptor maxWeightMetric(HANDLE_MAX_WEIGHT_METRIC,
        		unit,
        		MetricCategory::Set,
        		MetricAvailability::Cont,
        		1.0);

        // Channel
        ChannelDescriptor holdingDeviceChannel(CHANNEL_DESCRIPTOR_HANDLE);
        holdingDeviceChannel
			.addMetric(currentWeightMetric)
        	.addMetric(maxWeightMetric)
        	.setSafetyClassification(SafetyClassification::MedA);

        // VMD
        VmdDescriptor holdingDeviceModule(VMD_DESCRIPTOR_HANDLE);
        holdingDeviceModule
			.addChannel(holdingDeviceChannel);

        // MDS
        MdsDescriptor holdingDeviceSystem(MDS_HANDLE);
        holdingDeviceSystem
			.addVmd(holdingDeviceModule)
			.setType(
				CodedValue("MDCX_CODE_ID_MDS")
					.setCodingSystem("OR.NET.Codings"));

        // the set operations have to be defined before adding the MdDescription
        oscpProvider.createSetOperationForDescriptor(maxWeightMetric, holdingDeviceSystem);

        // add descriptor to description
        // the description contains all the devices static information
        MdDescription holdingDeviceDescription;
        holdingDeviceDescription.addMdsDescriptor(holdingDeviceSystem);


        // set the providers description
        oscpProvider.setMdDescription(holdingDeviceDescription);


		// State handler
        oscpProvider.addMdSateHandler(&maxValueState);
        oscpProvider.addMdSateHandler(&curValueState);
//        oscpProvider.addMDStateHandler(&channelState);
        oscpProvider.addMdSateHandler(&mdsState);
//        oscpProvider.addMDStateHandler(&vmdState);


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

    MaxValueStateHandler maxValueState;
    CurValueStateHandler curValueState;

    MDSStateHandler mdsState;
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
        double val = state.getMetricValue().getValue();
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
	OSCLibrary::getInstance().startup(OSELib::LogLevel::TRACE);
	OSCLibrary::getInstance().setIP6enabled(false);
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
	oscpsm.setHelloReceivedHandler(myHandler.get());
	// Provider
	OSCPHoldingDeviceProvider provider;
	provider.startup();
	DummyValueProducer dummyValueProducer(&provider);
	dummyValueProducer.start();

	std::string temp;
	DebugOut(DebugOut::Default, "ExampleProject") << "Press key to proceed test (until then, provider will keep running indefinitely).";
	std::cin >> temp;

	// Discovery
	std::shared_ptr<OSCPConsumer> c(oscpsm.discoverEndpointReference(deviceEPR));
	// alternatively: search the whole network
//		std::vector<std::unique_ptr<OSCPConsumer>> consumers(oscpsm.discoverOSCP());




	std::shared_ptr<ExampleConsumerEventHandler> eces1(new ExampleConsumerEventHandler(HANDLE_CURRENT_WEIGHT_METRIC));
	std::shared_ptr<ExampleConsumerEventHandler> eces2(new ExampleConsumerEventHandler(HANDLE_MAX_WEIGHT_METRIC));


	if (c != nullptr) {
		OSCPConsumer & consumer = *c;
		DebugOut(DebugOut::Default, "ExampleProject") << "Discovery succeeded.";

		// MDIB test
		MdibContainer mdib = consumer.getMdib();

		// Register for metric event
		consumer.registerStateEventHandler(eces1.get());
		consumer.registerStateEventHandler(eces2.get());

		Poco::Thread::sleep(4000);

		// Get state test (current weight)
		NumericMetricState currentWeightState(HANDLE_CURRENT_WEIGHT_METRIC);
		consumer.requestState(HANDLE_CURRENT_WEIGHT_METRIC, currentWeightState);
		double curWeight = currentWeightState.getMetricValue().getValue();
		DebugOut(DebugOut::Default, "ExampleProject") << "Observed Weight " << curWeight;

		try {
			// Set state test (must fail due to read-only)
			InvocationState invocationStateFirst = consumer.commitState(currentWeightState);
			DebugOut(DebugOut::Default, "ExampleProject") << "InvocationState (1st commit): " << Data::OSCP::EnumToString::convert(invocationStateFirst);
			if (InvocationState::Fail == invocationStateFirst) {
				DebugOut(DebugOut::Default, "ExampleProject") << "Committing state failed as expected.";
			} else {
				DebugOut(DebugOut::Default, "ExampleProject") << "Committing state succeeded. This is an error, because it should be read-only.";
			}
		} catch (const std::runtime_error & e) {
			DebugOut(DebugOut::Default, "ExampleProject") << "Exeption";}
		// Get state test (maximum weight)
		NumericMetricState maxWeightState(HANDLE_MAX_WEIGHT_METRIC);
		consumer.requestState(HANDLE_MAX_WEIGHT_METRIC, maxWeightState);
		double maxWeight = maxWeightState.getMetricValue().getValue();
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

	DebugOut(DebugOut::Default, "ExampleProject") << "Shutdown." << std::endl;
	OSCLibrary::getInstance().shutdown();

}
