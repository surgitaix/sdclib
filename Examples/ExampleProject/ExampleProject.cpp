
#include "SDCLib/SDCLibrary.h"
#include "OSELib/SDC/SDCConstants.h"
#include "SDCLib/Data/SDC/SDCConsumer.h"
#include "SDCLib/Data/SDC/SDCConsumerOperationInvokedHandler.h"
#include "SDCLib/Data/SDC/SDCConsumerMDStateHandler.h"
#include "SDCLib/Data/SDC/SDCProvider.h"
#include "SDCLib/Data/SDC/SDCProviderMDStateHandler.h"
#include "SDCLib/Data/SDC/SDCProviderComponentStateHandler.h"
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
#include "SDCLib/Data/SDC/MDIB/SystemContextDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/SystemContextState.h"
#include "SDCLib/Data/SDC/MDIB/LocalizedText.h"
#include "SDCLib/Data/SDC/MDIB/VmdDescriptor.h"
#include "SDCLib/Util/DebugOut.h"

#include "OSELib/SDC/ServiceManager.h"

#include "Poco/Mutex.h"
#include "Poco/ScopedLock.h"
#include "Poco/Thread.h"
#include "Poco/Runnable.h"
#include "Poco/Net/NetException.h"

using namespace SDCLib;
using namespace SDCLib::Util;
using namespace SDCLib::Data::SDC;

// Endpoint reference of the device -> unique ID
const std::string DEVICE_EPR("UDI-EXAMPLEPROJECT");

// descriptor handles
const std::string MDS_HANDLE("mds_handle");
const std::string VMD_DESCRIPTOR_HANDLE("vmd_handle");

const std::string CHANNEL_DESCRIPTOR_HANDLE("channel_handle");
const std::string HANDLE_MAX_WEIGHT_METRIC("handle_max");
const std::string HANDLE_CURRENT_WEIGHT_METRIC("handle_cur");


class MaxValueStateHandler : public SDCProviderMDStateHandler<NumericMetricState> {
public:

    MaxValueStateHandler(const std::string & descriptorHandle) : SDCProviderMDStateHandler(descriptorHandle){
    }

    // called when the consumer is requesting to set the MaxValueStateHandler
    InvocationState onStateChangeRequest(const NumericMetricState&, const OperationInvocationContext & oic) override {
        // Invocation has been fired as WAITING when entering this method
        DebugOut(DebugOut::Default, "ExampleProject") << "Provider: MaxValueStateHandler received state change request" << std::endl;

        notifyOperationInvoked(oic, InvocationState::Start);

        // we can update here, but if we return FINISHED, the framework will also update
        //updateState(state);

        return InvocationState::Fin;  // Framework will update internal MDIB with the state's value and increase MDIB version
    }

    // Helper method
    NumericMetricState createState() {
        NumericMetricState result(descriptorHandle);
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
        std::unique_ptr<NumericMetricState> pNMS(getParentProvider().getMdState().findState<NumericMetricState>(HANDLE_MAX_WEIGHT_METRIC));
        if ((pNMS != nullptr) && pNMS->hasMetricValue()) {
        	return (float) pNMS->getMetricValue().getValue();
        } else {
        	DebugOut(DebugOut::Default, "ExampleProject") << "No observed value" << std::endl;
        	return 0;
        }
    }
};




class CurValueStateHandler : public SDCProviderMDStateHandler<NumericMetricState> {
public:

    CurValueStateHandler(const std::string & descriptorHandler) : SDCProviderMDStateHandler(descriptorHandler){
    }

    // state is read-only - MEASUREMENT -> onStateChangeRequest() returns Fail
    InvocationState onStateChangeRequest(const NumericMetricState&, const OperationInvocationContext&) {
    	return InvocationState::Fail;
    }

    // Helper method
    NumericMetricState createState(float value) {
        NumericMetricState result(HANDLE_MAX_WEIGHT_METRIC);
        result
            .setMetricValue(NumericMetricValue(MetricQuality(MeasurementValidity::Inv)).setValue(value))
            .setActivationState(ComponentActivation::On)
            .setDescriptorHandle(descriptorHandle);
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


class MdsStateHandler : public SDCProviderComponentStateHandler<MdsState> {
public:
    MdsStateHandler(const std::string & descriptorHandle) : SDCProviderComponentStateHandler(descriptorHandle){
    }

    // Helper method
    MdsState createState() {
    	MdsState result(descriptorHandle);
        return result;
    }

    // implement this method from the stateHandler interface
    // each defined state needs an initial state
    virtual MdsState getInitialState() override {
    	MdsState state = createState();
        return state;
    }
};


// This example shows one way of implementing the Provider
// Since the SDCProvider class is final, it is recommended to implement the SDCProvider as a member variable of a container class to expand the SDCProvider in a clear and convinient fashion
class OSCPHoldingDeviceProvider {
public:

    OSCPHoldingDeviceProvider(SDCInstance_shared_ptr p_SDCInstance) :
    	sdcProvider(p_SDCInstance),
		currentWeight(0),
		maxValueState(HANDLE_MAX_WEIGHT_METRIC),
		curValueState(HANDLE_CURRENT_WEIGHT_METRIC),
    	mdsState(MDS_HANDLE)
	{
    	sdcProvider.setEndpointReference(DEVICE_EPR);
        // Define semantic meaning of weight unit "kg", which will be used for defining the
        // current weight and the max weight below.

    	// mandatory properties in constructor
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
        sdcProvider.createSetOperationForDescriptor(maxWeightMetric, holdingDeviceSystem);

        // add descriptor to description
        // the description contains all the devices static information
        MdDescription holdingDeviceDescription;
        holdingDeviceDescription.addMdsDescriptor(holdingDeviceSystem);


        // set the providers description
        sdcProvider.setMdDescription(holdingDeviceDescription);


		// State handler
        sdcProvider.addMdStateHandler(&maxValueState);
        sdcProvider.addMdStateHandler(&curValueState);
        sdcProvider.addMdStateHandler(&mdsState);


    }

    void startup() {
    	sdcProvider.startup();
    }

    void shutdown() {
    	sdcProvider.shutdown();
    }

    void setCurrentWeight(float value) {
    	Poco::Mutex::ScopedLock lock(m_mutex); // FIXME: changed from SDCProvider mutex to internal mutex
    	currentWeight = value;
        curValueState.setNumericValue(value);
        DebugOut(DebugOut::Default, "ExampleProject") << "Changed value: " << currentWeight << std::endl;
    }

private:

    Poco::Mutex m_mutex;
    // SDCProvider for communication to the network
    SDCProvider sdcProvider;

    float currentWeight;

    MaxValueStateHandler maxValueState;
    CurValueStateHandler curValueState;

    MdsStateHandler mdsState;
};


// The DummyValueProducer produces some some increasing values in a separate thread
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




// ExampleConsumerEventHandler extends SDCConsumerMDStateHandler, which is instanciated for NumericMetricState
// It's methods onStateChanged and onOperationInvoked are called from within this framework, each time the value is changed by the provider
// All event handlers have to be registered, please see below.
class ExampleConsumerEventHandler : public SDCConsumerMDStateHandler<NumericMetricState> {
public:
    ExampleConsumerEventHandler(const std::string & handle) : SDCConsumerMDStateHandler(handle),
    	currentWeight(0)
	{
    }

    // this method is called when a value changed in the provider
    void onStateChanged(const NumericMetricState & state) override {
        double val = state.getMetricValue().getValue();
        DebugOut(DebugOut::Default, "ExampleProject") << "Consumer: Received value changed of " << descriptorHandle << ": " << val << std::endl;
        currentWeight = (float)val;
    }

    // this method is called each time an operation (e.g. a set operation) is called by the provider
    // use to customize the handling of your code, e.g. log/ prompt a message, do validity checks, ect.
    void onOperationInvoked(const OperationInvocationContext & oic, InvocationState is) override {
        DebugOut(DebugOut::Default, "ExampleProject") << "Consumer: Received operation invoked (ID, STATE) of " << descriptorHandle << ": " << oic.transactionId << ", " << Data::SDC::EnumToString::convert(is) << std::endl;
    }

    float getCurrentWeight() {
        return currentWeight;
    }

private:
    float currentWeight;
};


int main()
{
	SDCLibrary::getInstance().startup(OSELib::LogLevel::Error);
	//SDCLibrary::getInstance().setPortStart(11000); // FIXME
	//SDCLibrary::getInstance().setDiscoveryTime(4000); // FIXME

    // Create a new SDCInstance (no flag will auto init)
    auto t_SDCInstanceConsumer = std::make_shared<SDCInstance>(Config::SDC_DEFAULT_PORT_CONSUMER, true);
    // Some restriction
    t_SDCInstanceConsumer->setIP6enabled(false);
    t_SDCInstanceConsumer->setIP4enabled(true);
    // Bind it to interface that matches the internal criteria (usually the first enumerated)
    if(!t_SDCInstanceConsumer->bindToDefaultNetworkInterface()) {
        std::cout << "Failed to bind to default network interface! Exit..." << std::endl;
        return -1;
    }

	OSELib::SDC::ServiceManager oscpsm(t_SDCInstanceConsumer);
	class MyHandler : public OSELib::SDC::HelloReceivedHandler {
	public:
		MyHandler() {
		}
		void helloReceived(const std::string & epr) override {
			DebugOut(DebugOut::Default, "ExampleProject") << "Hello received! EPR: " << epr;
		}
	};
	std::unique_ptr<MyHandler> myHandler(new MyHandler());
	oscpsm.setHelloReceivedHandler(myHandler.get());

    // Create a new SDCInstance (no flag will auto init)
    auto t_SDCInstanceProvider = std::make_shared<SDCInstance>(Config::SDC_DEFAULT_PORT_PROVIDER, true);
    // Some restriction
    t_SDCInstanceProvider->setIP6enabled(false);
    t_SDCInstanceProvider->setIP4enabled(true);
    // Bind it to interface that matches the internal criteria (usually the first enumerated)
    if(!t_SDCInstanceProvider->bindToDefaultNetworkInterface()) {
        std::cout << "Failed to bind to default network interface! Exit..." << std::endl;
        return -1;
    }

    // Provider
	OSCPHoldingDeviceProvider provider(t_SDCInstanceProvider);
	provider.startup();
	DummyValueProducer dummyValueProducer(&provider);
	dummyValueProducer.start();

	std::string temp;
	DebugOut(DebugOut::Default, "ExampleProject") << "Press key to proceed test (until then, provider will keep running indefinitely).";
	std::cin >> temp;

	// Discovery
	std::shared_ptr<SDCConsumer> c(oscpsm.discoverEndpointReference(DEVICE_EPR));
	// alternatively: search the whole network
//		std::vector<std::unique_ptr<SDCConsumer>> consumers(oscpsm.discoverOSCP());


	if (c != nullptr) {

		std::shared_ptr<ExampleConsumerEventHandler> eces1(new ExampleConsumerEventHandler(HANDLE_CURRENT_WEIGHT_METRIC));
		std::shared_ptr<ExampleConsumerEventHandler> eces2(new ExampleConsumerEventHandler(HANDLE_MAX_WEIGHT_METRIC));

		SDCConsumer & consumer = *c;
		DebugOut(DebugOut::Default, "ExampleProject") << "Discovery succeeded.";

		// MDIB test
		MdibContainer mdib = consumer.getMdib();

		// Register for metric event
		consumer.registerStateEventHandler(eces1.get());
		consumer.registerStateEventHandler(eces2.get());

		Poco::Thread::sleep(4000);

		// Get state test (current weight)
		std::unique_ptr<NumericMetricState> pCurrentWeightState(consumer.requestState<NumericMetricState>(HANDLE_CURRENT_WEIGHT_METRIC));
		double curWeight = pCurrentWeightState->getMetricValue().getValue();
		DebugOut(DebugOut::Default, "ExampleProject") << "Observed Weight " << curWeight;

		try {
			// Set state test (must fail due to read-only)
			InvocationState invocationStateFirst = consumer.commitState(*pCurrentWeightState);
			DebugOut(DebugOut::Default, "ExampleProject") << "InvocationState (1st commit): " << Data::SDC::EnumToString::convert(invocationStateFirst);
			if (InvocationState::Fail == invocationStateFirst) {
				DebugOut(DebugOut::Default, "ExampleProject") << "Committing state failed as expected.";
			} else {
				DebugOut(DebugOut::Default, "ExampleProject") << "Committing state succeeded. This is an error, because it should be read-only.";
			}
		} catch (const std::runtime_error & e) {
			DebugOut(DebugOut::Default, "ExampleProject") << "Exception";}
		// Get state test (maximum weight)
		std::unique_ptr<NumericMetricState> pMaxWeightState(consumer.requestState<NumericMetricState>(HANDLE_MAX_WEIGHT_METRIC));
		double maxWeight = pMaxWeightState->getMetricValue().getValue();
		DebugOut(DebugOut::Default, "ExampleProject") << "Max weight value: "<< maxWeight;

		// Set state test (must succeed)
		InvocationState invocationStateSecond  = consumer.commitState(*pMaxWeightState);
		DebugOut(DebugOut::Default, "ExampleProject") << "InvocationState (2nd commit): " << Data::SDC::EnumToString::convert(invocationStateSecond);

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
	SDCLibrary::getInstance().shutdown();

}
