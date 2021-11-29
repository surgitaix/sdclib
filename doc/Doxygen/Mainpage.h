/**
@mainpage %SDCLib documentation

Welcome to the SDCLibrary documentation pages. Use the menu on the left to navigate to a section, or select
one of the page links below.

@li @ref intro <b>OR.NET</b>: A short introduction to the %SDCLib
@li @ref sdcpage <b>OR.NET</b>: API for the Open Surgical Communication Protocol

@version 4.6.0
@author Besting, Baumeister
@copyright (C) 2021 SurgiTAIX AG

@page introductionpage Introduction

@tableofcontents

@section intro Introduction
The SDCLibrary (%SDCLib) is a lightweight, easy-to-use, easy-to-port, resource-friendly and fast
webservice library for medical devices. It implements the Open Surgical Communication Protocol (SDC) on top of
DPWS 1.1. %SDCLib supports the WS-Discovery, WS-Addressing, WS-Transfer, WS-Eventing and WS-MetadataExchange specification and is based on
SOAP 1.2 and WSDL 1.1 standards.

@section setup Setting up the development environment

The %SDCLib is mostly platform independent. There are only few parts that are implemented for a specific operating system.
These parts rely on preprocessor directives. Additionally different libraries have to be linked for different operating systems.
The neccessary steps are described in the README.md. You can find further information in the doc/ folder.

The %SDCLib relies on XSD (http://www.codesynthesis.com), XercesC and Poco. Being a major dependency Poco has been included in the dependecy folder and will be built along with the SDCLib.

@subsection linuxspecificcmake CMake on Linux

We recommend using the SDCLib with CMake on Linux. We try to support Windows too, but cannot guarantee for platform dependent bugs.
The following guideline will focus on setting up the SDCLib on Linux systems.

Essential requirements
  
<ul>
  <li>C++ 11 Compiler Support</li>
  <li>CMake (> 3.5.0), pthread</li>
  <li>Supported Compilers:</li>
  <ol>
  <li>GCC ( 4.8.1 ) full C++11 support</li>
  <li>Clang ( 3.3 ) full C++11 support</li>
  <li>MSVC++ ( 18.0 ) partial C++11 support (19.0 or higher recommended)</li>
  </ol>
</ul>

@subsubsection linuxdependenciesxsd Installing XSD and XERCES

Install XSD and xerces-c binaries and includes, on debian or ubuntu you can use the commands
<ul>
  <li>sudo apt-get install xsdcxx</li>
  <li>sudo apt-get install libxerces-c-dev</li>
  <li>sudo apt-get install libssl-dev</li>
</ul>


@subsection integrating Integrating compiled binaries in your project

After building the SDCLib you can perform
<ul>
  <li>make install</li>
</ul>
This will copy all required files into the folder specified under CMAKE_INSTALL_PREFIX (Header and compiled binaries).
You can set the include and library path to this folder and use the built SDCLib in your project without CMake.

@page sdcpage Open Surgical Communication Protocol

@tableofcontents

@section sdcstartup Framework startup and shutdown
Each Participant is based on an individual SDCInstance. To start a provider create it, bind it to an interface and pass it to the provider on creation:
@code
// Include common library headers
#include <SDCLib/SDCInstance.h>
#include <SDCLib/Data/SDC/SDCProvider.h>

#include <iostream>

using namespace SDCLib;
using namespace SDCLib::Data::SDC;

int main()
{
    // Create a new SDCInstance (no flag will auto init)
    auto t_SDCInstance = std::make_shared<SDCInstance>(true);
    // Configure (optional)
    t_SDCInstance->setIP6enabled(false);
    t_SDCInstance->setIP4enabled(true);
    // Bind it to interface that matches the internal criteria (usually the first enumerated)
    if(!t_SDCInstance->bindToDefaultNetworkInterface()) {
        std::cout << "Failed to bind to default network interface! Exit..." << std::endl;
        return -1;
    }
    // Create the SDCProvider
    SDCProvider provider(t_SDCInstance);
    provider.startup();

    // ... Do some work here, let the provider run etc.
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    // Clean shutdown of the SDCProvider
    provider.shutdown();
    return 0;
}
@endcode

@section sdcoverview Overview

The API for the SDC Protocol (SDC-API) is set on top of DPWS. It was created by the OR.NET data model working group and is based on the DIN EN ISO 11073-10201 information model. The resulting OR.NET data model is called CDM (Communication Data Model).

There are two main instances used for communication:

<ul>
  <li><b>SDCLib::Data::SDC::SDCProvider</b>: describes the device, and converts SDC-conform requests into (proprietary) device commands</li>
  <li><b>SDCLib::Data::SDC::SDCConsumer</b>: a client tool used to establish communication with an SDCProvider</li>
</ul>

<p>Both instances implement a base set of methods defined by a common interface. This interface allows transparent access to the medical device information base (MDIB) which can be regarded as the database that contains the values defined by the CDM.</b> 
<p>In order to integrate a medical device (or a medical information service) into an SDC Network (i.e. writing an <b>SDC-Connector</b>), you'll first have to implement an instance of SDCProvider. The following sections describe this process using a simple example of implementing an SDC-Connector for the EndoTAIX holding device system, a camera holding device for endoscopy.</p>
Working examples similar to this one can be found in the "Examples" folder, especially in <b>ExampleProject.cpp</b>. The unit tests <b>TestSimpleSDC.cpp</b> and <b>TestStreamSDC.cpp</b> might also help to illustrate the SDC API.

@subsection sdc_mbid The MDIB structure

The MDIB structure is used to exchange information between the SDCProvider and SDCConsumer instances. The class structure behind it can be used to describe a medical device or a medical service statically and dynamically. The following (simplified) structure is used for the MDIB:

<ul>
  <li><b>MDIB</b>: the information base holding all static and dynamic sub-structures. Class-name: SDCLib::Data::SDC::MDIBContainer</li>
    <ul>
      <li><b>Medical Device Description</b>: Describes the static part. Class-name: SDCLib::Data::SDC::MDDescription</li>
        <ul>
          <li><b>Medical Device System</b>: Describes the complete device or service. Class-name: SDCLib::Data::SDC::MdsDescriptor</li>
            <ul>
              <li><b>Virtual Medical Device</b>: Describes a subsystem (e.g. a hardware- or software-modul). Class-name: SDCLib::Data::SDC::VMDDescriptor</li>
                <ul>
                  <li><b>Channel</b>: Describes a group of metrics. Class-name: SDCLib::Data::SDC::ChannelDescriptor</li>
                    <ul>
                      <li><b>Metric</b>: Describes a primitive or complex data object (e.g. heart rate measurement). Sub-classes of: SDCLib::Data::SDC::AbstractMetricDescriptor</li>
                      <li><b>Context</b>: Describes a specifix context (e.g. location of patient demographics). Sub-classes of: SDCLib::Data::SDC::AbstractContextDescriptor</li>
                    </ul>  
                </ul> 
            </ul>
        </ul>
      <li><b>Medical Devices States</b>: Containes the dynamic part. Class-name: SDCLib::Data::SDC::MdState</li>
        <ul>
          <li><b>Metric State</b>: Describes the state of a references metric (e.g. current heart rate value). Sub-classes of: SDCLib::Data::SDC::AbstractMetricState</li> (e.g. NumericMetricState, StringMetricState, etc.)
          <li><b>Context State</b>: Describes the state of a specific context (e.g. patient demographics data). Sub-classes of: SDCLib::Data::SDC::AbstractContextState</li></li> 
        </ul>  
    </ul>
</ul>

Alert systems can be inserted at the level of the Mds, the VMD or channel. They will be described later in detail.

@section sdc_provider The EndoTAIX SDC Provider example

This section provides a simplified example for an SDCProvider instance for the EndoTAIX holding device system. The <b>SDCHoldingDeviceProvider</b> class extends the <b>SDCLib::Data::SDC::SDCProvider</b> class. However, it is not required to subclass SDCProvider. Instead, you can also use an instance as a member variable in another class.
<p>Using <b>SDCrovider::addMdStateHandler</b> is a comfortable way to provide separate handlers for each state. This has the advantage, that code concerning devices's data will be encapsulated elsewhere. This will keep our class (SDCHoldingDeviceProvider) short.</p>

<P>In this example, the provider contains two metrics, which describe their purpose and properties:
One for current weight (currentWeightMetric, read-only), which is measured using a force-torque-sensor attached to the arm. The other one defines the maximum weight limit (maxWeightMetric, read-write). Each metric also needs a corresponding <b>metric state</b> which contains the actual value.</p>
Each metric state will be represented by a separate handler, which subclasses <b>SDCProviderMdStateHandler</b>.

@subsection sdc_provider_basics_descriptive Implementation - The descriptive part

The implementation of the provider's descriptive part can be structured as followed.

@code
class SDCHoldingDeviceProvider : public SDCProvider {
public:
    SDCHoldingDeviceProvider() { ... }

    virtual ~SDCHoldingDeviceProvider() { }

  ...

private:
    // The current weight
    NumericMetricDescriptor currentWeightMetric;
  
    // Maximum weight
    NumericMetricDescriptor maxWeightMetric;
  
  ...
}
@endcode

First, the descriptors have to be filled with proper definitions for our example device. For convenience, we do this in the constructor of our SDCHoldingDeviceProvider. However this is not a strict requirement.

The most important thing about initializing the metrics is that each metric needs a unique string identifier called "handle", which we define here. You are totally free to chose the handles, as long as they are unique within your device. It is also valid to generate them randomly.

@code
SDCHoldingDeviceProvider() {
  // Note: When setting this is converted to UUIDv5 and a prefix is applied:
  // urn:uuid:<UUIDv5("EPR_12345")>
  setEndpointReference(SDCInstance::calcUUIDv5("EPR_12345"));
  // Or use
  setEndpointReferenceByName("EPR_12345"); // This will do automatic conversion

  // Define semantic meaning of weight unit "kg", which will be used for defining the
  // current weight and the max weight below.
  CodedValue unit;
  unit.setCodeId("MDCX_CODE_ID_KG")
    .setCodingSystemId("OR.NET.Codings")
    .addConceptDescription(LocalizedText().set("Weight in kg"));

  // Setup metric descriptors
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

  // Define properties of max weight metric
  maxWeightMetric
    .setMetricCategory(MetricCategory::SETTING)
    .setAvailability(MetricAvailability::CONTINUOUS)
    .setUnit(unit)
    .setType(
      CodedValue()
        .addConceptDescription(LocalizedText().set("Maximum weight")))
    .setHandle("handle_max");

  ...
}

@endcode

<p>The above code shows the usage of <b>method chaining</b>, which eases the definitions of descriptors.</p>

<p>The description (containing the Mds) will be constructed <b>bottom-up</b>. It describes the structure of our device and uses the definitions of our metrics:
Each metric must be added to a channel instance, the channel instance to the virtual medical device instance and that one finally to the medical device system instance.</p>

<p><b>Important:</b> To make the maximum value state writeable (<b>onStateChangeRequest</b> implemented), a set operation descriptor must be added using <b>createSetOperationForDescriptor</b>!</p>

@code
SDCHoldingDeviceProvider(...) {

  ...

  // Channel
  ChannelDescriptor holdingDeviceChannel;
  holdingDeviceChannel
    // Add metrics to channel
    .addMetric(currentWeightMetric)
    .addMetric(maxWeightMetric)
	.setIntendedUse(IntendedUse::MEDICAL_A);

  // VMD
  VMDDescriptor holdingDeviceModule;
  holdingDeviceModule.addChannel(holdingDeviceChannel);

  // Mds
  MdsDescriptor holdingDeviceSystem;
  holdingDeviceSystem
    .setHandle(MDS_HANDLE)
    .setMetaData(
      SystemMetaData()
        .setUDI("UDI_12345")
        .addManufacturer(
          LocalizedText()
          .set("SurgiTAIX AG"))
        .addModelName(
          LocalizedText()
          .set("EndoTAIX"))
        .addModelNumber("1")
        .addSerialNumber("1234")
      )
    // Add VMD to Mds
    .addVMD(holdingDeviceModule)
    .setType(
      CodedValue()
        .setCodingSystemId("OR.NET.Codings")
  	    .setCodeId("MDCX_CODE_ID_MDS"));

  // Create SET operation for max value
  createSetOperationForDescriptor(maxWeightMetric, holdingDeviceSystem);
  
  // Add MDS to provider
  addMds(holdingDeviceSystem);

}
@endcode

@subsection sdc_provider_basics_dynamic Implementation - The dynamic part

<p>For the dynamic part, we have to implement handlers of a subtype of <b>SDCProviderMdStateHandler</b> (e.g. <b>SDCProviderNumericMetricStateHandler</b>) where each handler takes care of a single state, as already mentioned before. It defines the initial state at startup.
The handler may then call the <b>updateState</b> method at any time to tell the framework about a state (value) change (e.g. if the real devices state changes). The internal MDIB will then be updated.</p>
<p>If the state is writable (SETTING), the handler has to provide at least a type-specific implementation of <b>onStateChangeRequest</b> for a specific type (e.g. NumericMetricState or StringMetricState) which processes incoming change requests for our metric state.</p>
Each state must refer to the descriptor's state handle. If multiple states refer to the same descriptor, each state must furthermore have its own state handle. Otherwise this is optional.

@code
// READ-ONLY state handler
class CurValueStateHandler : public SDCProviderMDStateHandler<NumericMetricState>
{
public:

    CurValueStateHandler(std::string descriptorHandle)
	: SDCProviderMDStateHandler(descriptorHandle)
	{ }

	// define how to react on a request for a state change. This handler should not be set, thus always return Fail.
	InvocationState onStateChangeRequest(const NumericMetricState&, const OperationInvocationContext&) override {
		return InvocationState::Fail;
	}
    // Helper method
    NumericMetricState createState(double value) {
        auto t_result = NumericMetricState(descriptorHandle);
        t_result
            .setMetricValue(NumericMetricValue(MetricQuality(MeasurementValidity::Vld)).setValue(value))
            .setActivationState(ComponentActivation::On)
            .setDescriptorHandle(NUMERIC_METRIC_CURRENT_HANDLE)
            .setLifeTimePeriod(xml_schema::Duration(0,0,0,0,0,0,1));
        return t_result;
    }

    NumericMetricState getInitialState() override {
        return createState(0);
    }

    void setNumericValue(double value) {
        NumericMetricState currentWeightState = createState(value);
        // Call update function (this will update internal MDIB and increase MDIB version number)
        updateState(currentWeightState);
    }
};

@endcode

The handler for the max value state:

@code
// READ-WRITE state handler
class MaxValueStateHandler : public SDCProviderMDStateHandler<NumericMetricState>
{
public:

    MaxValueStateHandler(std::string descriptorHandle)
	: SDCProviderMDStateHandler(descriptorHandle)
	{ }

    InvocationState onStateChangeRequest(const NumericMetricState & state, const OperationInvocationContext & oic) override {
        // Invocation has been fired as WAITING when entering this method
    	DebugOut(DebugOut::Default, "SimpleSDC") << "Provider: MaxValueStateHandler received state change request" << std::endl;

    	notifyOperationInvoked(oic, InvocationState::Start);

        // we can update here, but if we return Fin, the framework will also update
        updateState(state);

        // Usually, update the real device's state here.

        // Framework will update internal MDIB with the state's value and increase MDIB version
        return InvocationState::Fin;
    }

    // Helper method
    NumericMetricState createState() {
        auto t_result = NumericMetricState(descriptorHandle);
        t_result
            .setMetricValue(NumericMetricValue(MetricQuality(MeasurementValidity::Vld)).setValue(2.0))
            .setActivationState(ComponentActivation::On);
        return t_result;
    }

    NumericMetricState getInitialState() override {
        return createState();
    }

    // Convenience value getter
    double getMaxWeight() {
    	std::unique_ptr<NumericMetricState> result(getParentProvider().getMdState().findState<NumericMetricState>(NUMERIC_METRIC_MAX_HANDLE));
        // check if result is valid
        if (result != nullptr) {
        	// In real applications, check if state has an observed value and if the observed value has a value!
        	return result->getMetricValue().getValue();
        }
        DebugOut(DebugOut::Default, "SimpleSDC") << "Maximum weight metric not found." << std::endl;
        return 0;
    }
};
@endcode

We extend the constructor's code to add the handlers, which we define as members of the holding device provider class.

@code
class SDCHoldingDeviceProvider : public SDCProvider {
public:
  SDCHoldingDeviceProvider(...) {
  
    ...
  
    // Add state handler's
    addMdStateHandler(&maxValueState);
    addMdStateHandler(&curValueState);
  
  }

private:
  // Current weight
  NumericMetricDescriptor currentWeightMetric;
  // State handler
  CurValueStateHandler curValueState;
  
  // Maximum weight
  NumericMetricDescriptor maxWeightMetric;
  // State handler
  MaxValueStateHandler maxValueState;

}
@endcode

@subsection sdc_provider_start Implementation - Start the provider

Starting the provider can be done by calling the method <b>startup</b>. The periodic update thread can be launched by calling <b>start</b>.
 The provider can be stopped by calling </b>shutdown</b>:
@code
  //...
  
  SDCHoldingDeviceProvider provider(t_SDCInstance);
  // Start provider
  provider.startup();  
  provider.start();
  ...

  provider.shutdown();
}

@endcode

@section sdc_consumer The EndoTAIX SDC Consumer example

<p>An SDCConsumer instance is always connected to exactly one SDCProvider instance. SDCConsumer instances can be retrieved via the ServiceManager by using its connection and discovery methods.</p>

@subsection sdc_consumer_servicemanager Discovery using the ServiceManager

<p>An SDCConsumer instance cannot be instantiated directly. The only component that can produce these instances is the ServiceManager (<b>OSELib::SDC::ServiceManager</b>).
The ServiceManager is resposibe for the discovery of SDCProvider instances. An SDCInstance is passed to the ServiceManager. The config is used as a "template" (configured IPv4/IPv6), bound Network Interface etc. for the discovered Consumers. We will now discover the provider using the ServiceManager:</p>

@code

// ... SDCInstance (Create, init and bind as shown above)
// ServiceManager
OSELib::SDC::ServiceManager t_serviceManager(t_SDCInstance);
// Consumer - Calculate UUIDv5 AND apply the prefix "urn:uuid:" when searching
auto t_consumer(t_serviceManager.discoverEndpointReference(SDCInstance::calcUUIDv5("EPR_1234", true)));
if (t_consumer != nullptr) {
  ...
}
@endcode

It's also possible to directly connect using a known transport address:

@code
SDCServiceManager sdcsm;
auto t_consumer = sdcsm.connect("http://192.168.1.32:1234/UDI_1234");
if (t_consumer != nullptr) {
  ...
}
@endcode

You can also issue a global discover into the network:

@code

// ... SDCInstance (Create, initand bind as shown above)

// ServiceManager
OSELib::SDC::ServiceManager sm(t_SDCInstance);
auto tl_consumers{sm.discover()};
// List EPR (Endpoint Reference) of all found Consumers
for (const auto & t_consumer : tl_consumers) {
    std::cout << "Found: " << t_consumer->getEndpointReference() << std::endl;
}

// ...

@endcode

Discovery can also be done asynchronously. A full Example:

@code
// Include common library headers
#include <SDCLib/SDCInstance.h>
#include <OSELib/SDC/ServiceManager.h>
#include <SDCLib/Data/SDC/SDCConsumer.h>

#include <iostream>

using namespace SDCLib;
using namespace SDCLib::Data::SDC;

const auto t_discoveryTime = std::chrono::milliseconds{5000};

void discover(OSELib::SDC::ServiceManager& p_SDCServiceManager)
{
    std::cout << "Starting Discovery...";
    int t_waitLoops = t_discoveryTime.count() / 100 + 5;
    auto t_asyncResults = p_SDCServiceManager.async_discover();
    for (auto i = 0; i < t_waitLoops; ++i) {
        std::cout << "." << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(t_discoveryTime / t_waitLoops));
    }

    auto t_results = t_asyncResults.get();
    std::cout << "\nDISCOVERED: ";
    if (t_results.empty()) { std::cout << "None.\n"; return; }
    else { std::cout << t_results.size() << ":" << std::endl; }
    for (auto& t_consumer :  t_results) {
        if(t_consumer == nullptr) {
            continue;
        }
        std::cout << " - " << t_consumer->getEndpointReference() << std::endl;
    }
}
int main()
{
    // Create a new SDCInstance (no flag will auto init)
    auto t_SDCInstance = std::make_shared<SDCInstance>(true);
    // Configure (optional)
    t_SDCInstance->setIP6enabled(false);
    t_SDCInstance->setIP4enabled(true);
    // Bind it to interface that matches the internal criteria (usually the first enumerated)
    if(!t_SDCInstance->bindToDefaultNetworkInterface()) {
        std::cout << "Failed to bind to default network interface! Exit..." << std::endl;
        return -1;
    }

    OSELib::SDC::ServiceManager t_SDCServiceManager(t_SDCInstance);
    discover(t_SDCServiceManager);
    return 0;
}
@endcode


@subsection sdc_consumer_events Using the consumer - reception of events
// NOTE: This subsection needs to be revised!
  
If we like to process events (in this case, the ones containing states for the current weight metric), we'll have to provide an event handler of a subtype of
<b>SDCConsumerEventHandler</b> (e.g. <b>SDCConsumerNumericMetricStateHandler</b>), implement the <b>onStateChanged</b> (if the metric is writable!) and override the <b>getHandle</b> method. The <b>onStateChanged</b> method will be entered whenever the framework or the user code notify about a metric change (updateState).
Optionally, the method <b>onOperationInvoked</b> can be overwritten to receive detailed notification about invocation states.

@code
class ExampleConsumerEventHandler : public SDCConsumerNumericMetricStateHandler
{
public:

  ExampleConsumerEventHandler(const std::string & handle) {
    currentWeight = 0;
    this->handle = handle;
  }

  virtual ~ExampleConsumerEventHandler() = default;

  // Overrides base
  void onStateChanged(const NumericMetricState & state) override {
    double val = state.getObservedValue().getValue();
    cout << "Received current weight value changed: " << val << endl;
    Poco::Mutex::ScopedLock lock(mutex);  // Pay attention to concurrency
    double val = state.getObservedValue().getValue();
    this->currentWeight = val;
  }
  
  // Overrides base
  void onOperationInvoked(const OperationInvocationContext & oic, InvocationState is) override {
    cout << "Received operation invoked (ID, STATE): " << oic.transactionId << ", " << EnumToString::convert(is) << endl;
  }  

  // Overrides base
  std::string getHandle() override {
    return handle;
  }

  double getWeight() {
    Poco::Mutex::ScopedLock lock(mutex);  // Pay attention to concurrency
    return this->weight;
  }

private:
  Poco::Mutex mutex;
  double weight;
  std::string handle;

};
@endcode

You can then register for the events using the following code:

@code
ExampleConsumerEventHandler * handler1 = new ExampleConsumerEventHandler("handle_cur");
ExampleConsumerEventHandler * handler2 = new ExampleConsumerEventHandler("handle_max");
consumer.registerStateEventHandler(handler1);
consumer.registerStateEventHandler(handler2);

@endcode

@subsection sdc_consumer_request_commit Using the consumer - Request and commit states
// NOTE: This subsection needs to be revised!
  
The currentweight metric state can also be requested directly using <b>requestState</b>:

@code
NumericMetricState currentWeightState;
if(consumer.requestState("handle_cur", currentWeightState)) {
    // Note: the following pre-check is very important - if the observed value is missing, the code will result in undefined behavior!
    if(currentWeightState.hasObservedValue()) {
        std::cout << "Current weight value is: " << currentWeightState.getObservedValue().getValue() << std::endl;
    }
}
@endcode

<p><b>Important:</b> The handle provided to the function can either be the descriptor's handle or the state's handle (if there is any). In cases when multiple states refer to the same descriptor, the state's handle must be used! the same thing applies to commiting states (see below).</p> 

@subsubsection sdc_consumer_request_commit_async Handling async commits

<p>Committing states takes place <b>asynchronously</b>, which means the method always returns at once, independently from how long the actual change process takes to complete on the Provider's side. The default return value for a change process that has preliminary been accepted, is InvocationState::Wait.</p>
However, in some cases like the currentweight metric, the invocation state will indicate a failure because this metric is read-only:

@code
NumericMetricState currentWeightStateResult;
auto is = consumer.commitState(currentWeightState);
// is == InvocationState::Fail
@endcode

<p>Please note that in this case the framework itself makes this determination and returns this value in the response. If for example InvocationState::Fail is returned by the provider handler's user code,
it can only be detected by evaluating the results later, because the immediate return value will still be InvocationState::Wait (remember that the user code on the provider's side will be executed asynchronously).</p>
There are two possibilities of how to handle results of asynchronously committed states:

<ul>
  <li>Synchronously wait for received invocation state(s) by using a <b>FutureInvocationState</b> object provided to the <b>commit</b> function. Then call <b>waitReceived</b> after the commit.</li>
  <li>Handle operation invoked reports and episodic metric / alert / context reports in a user-defined subclass of subtypes of SDCConsumerEventHandler (<b>onOperationInvoked</b> and <b>onStateChanged</b>) like shown before. The <b>FutureInvocationState</b> object can be used to get the right transaction ID which must somehow be taken into account by the handler.</li>
</ul>

So in each case, a <b>FutureInvocationState</b> object is needed, either to use its methods to actively wait for an event to occur or to get the transaction ID and compare it with events received elsewhere.
The first case is very easy to implement:

@code
NumericMetricState maxWeightState;
maxWeightState.setDescriptorHandle("handle_max");
maxWeightState.setObservedValue(NumericMetricValue(3.0));
FutureInvocationState fis;
if (consumer.commitState(maxWeightState, fis) == InvocationState::Wait) {
  std::cout << "Commit in progress..." << std::endl;
  // Wait FINISHED to be signaled in the next 1000 milliseconds
  if (fis.waitReceived(InvocationState::FINISHED, 1000)) {
  	std::cout << "Commit succeeded within expected time!" << std::endl;
  }
}
@endcode

The second case would be more complicated because the chronology of messages sent from the server is not deterministic. Operation invoked reports can be received by the consumer event handler before the commit function actually returns. At this point, the transaction ID (created by the provider) is not yet known on the
consumer's side. One way to address this problem would be to maintain a history of received events in the consumer event handler.

@subsection sdc_consumer_close Disconnecting the consumer

If the consumer is not needed any more, it should be disconnected (it MUST be disconnected before deletion). Handlers may be unregistered before that (if not, on the provider side the event subscription will time out):

@code
consumer.unregisterStateEventHandler(handler1);
consumer.unregisterStateEventHandler(handler2);
consumer.disconnect();
// shared_ptr will delete consumer when leaving scope
@endcode

@section sdc_alarm_system The alarm system

<p>The structures and methods of the alarm system can be used to implement alarm situations using mostly <b>conditions</b> and <b>signals</b>. Descriptors and states exist for each of the latter. This section describes an extension of the previous example to produce and consume an alarm, if the current weight value exceeds the maximum value. A real implementation of this example can be found in the unit test <b>TestSimpleSDC.cpp</b><p>
<p>An alert condition holds the information about an actual alarm situation, while an alert signal's purpose is to define, how exactly the condition should be reported. In general, multiple signals can reference the same condition. We start again with the descriptive part.</p>

@subsection sdc_alarm_system_provide The Provider

We'd like to create an alert for the <b>limit condition</b> when the current weight value exceeds the maximum value and extend the holding device's provider with the following code.

@code
class SDCHoldingDeviceProvider : public SDCProvider
{
public:
  SDCHoldingDeviceProvider() {
  
    ...

    // Setup alert system
    AlertSystemDescriptor alertSystem;
    alertSystem
        .addAlertSignal(alertSignal)
        .addAlertCondition(alertCondition)
        .setHandle("handle_alert_system");

    // Add to channel (VMD or Mds is also possible)
    holdingDeviceChannel.setAlertSystem(alertSystem);
    ...

    // Create SET operation descriptor
    createSetOperationForDescriptor(alertSignal, holdingDeviceSystem);
  
    // Setup alert descriptors

    // Alert condition
    alertCondition
        .addSource("handle_cur")
        .setType(
            CodedValue()
            .setCodeId("MDCX_CODE_ID_ALERT_WEIGHT_CONDITION")
            .setCodingSystemId("OR.NET.Codings"))
        .setKind(AlertConditionKind::TECHNICAL)
        .setPriority(AlertConditionPriority::MEDIUM)
        .setHandle("handle_alert_condition");

    // Create signal for condition
    alertSignal
        .setConditionSignaled("handle_alert_condition")
        .setManifestation(AlertSignalManifestation::VISIBLE)
        .setLatching(false)
        .setHandle("handle_alert_signal");
        
    // Add alert state handlers
    addMDStateHandler(&alertCondHandler);
    addMDStateHandler(&alertSigHandler);
    addMDStateHandler(&alertSysHandler);
  }
  
private:
  ...
  
  // Alert descriptors
  AlertSignalDescriptor alertSignal;
  AlertConditionDescriptor alertCondition;
  
  // Alert states
  LimitAlertConditionStateHandler alertCondHandler;  // See implementation details below
  AlertSignalStateHandler alertSigHandler;  // See implementation details below
  AlertSystemStateHandler alertSysHandler;  // See implementation details below
}
@endcode

The <b>LimitAlertConditionStateHandler</b> and <b>AlertSignalStateHandler</b> classes extend the SDCProviderAlertConditionStateHandler and the SDCProviderAlertSignalStateHandler, resp.
The method <b>sourceHasChanged</b> will be called whenever the referenced source state changed (e.g. updateState was called). The behavior of the method call to <b>setAlertConditionPresence</b> will be explained later.

@code
class LimitAlertConditionStateHandler : public SDCProviderAlertConditionStateHandler<LimitAlertConditionState> {
public:

    LimitAlertConditionStateHandler(std::string descriptorHandle)
    : SDCProviderAlertConditionStateHandler(descriptorHandle)
    { }

    InvocationState onStateChangeRequest(const LimitAlertConditionState & state, const OperationInvocationContext & ) override {

        // Invocation has been fired as WAITING when entering this method
        std::unique_ptr<LimitAlertConditionState> pCurrentState(getParentProvider().getMdState().findState<LimitAlertConditionState>(state.getDescriptorHandle()));
        if(!pCurrentState) {
            return InvocationState::Fail;
        }

        DebugOut(DebugOut::Default, "SimpleSDC") << "Provider: LimitAlertConditionStateHandler received state change, presence = " << state.getPresence() << std::endl;
        if (state.getPresence() != pCurrentState->getPresence()) {
            DebugOut(DebugOut::Default, "SimpleSDC") << "Provider: LimitAlertConditionStateHandler detected presence change to: " << state.getPresence() << std::endl;
            // do something...
        }

        //we can update here, but if we return Fin, the framework will also notify
        //updateState(*pCurrentState);

        return InvocationState::Fin;  // Framework will update internal MDIB with the state's value and increase MDIB version
    }

    // this function monitors the observered metric which is defined by the Source attribute of the corresponding LimitAlertConditionDescriptor
    void sourceHasChanged(const std::string & sourceHandle) override {
        DebugOut(DebugOut::Default, "SimpleSDC") << "Provider: LimitAlertConditionStateHandler monitored source state changed." << std::endl;

        // Check limit and trigger alarm condition, if needed (this method will then take care of handling all signal states)
        std::unique_ptr<NumericMetricState> pSourceState(getParentProvider().getMdState().findState<NumericMetricState>(sourceHandle));

        std::unique_ptr<LimitAlertConditionState> pLimitAlertConditionState(getParentProvider().getMdState().findState<LimitAlertConditionState>(ALERT_CONDITION_HANDLE));
        if (pSourceState->getDescriptorHandle() != sourceHandle) {
            return;
        }
        if (!pSourceState->hasMetricValue()) {
            return;
        }
        const auto sourceValue(pSourceState->getMetricValue());
        if (!sourceValue.hasValue()) {
            return;
        }
        const auto limits(pLimitAlertConditionState->getLimits());
        if (!limits.hasUpper()) {
            return;
        }
        if (!limits.hasLower()) {
            return;
        }
        const bool triggerAlarm(sourceValue.getValue() > limits.getUpper() || sourceValue.getValue() < limits.getLower());
        setAlertConditionPresence(pLimitAlertConditionState->getDescriptorHandle(), triggerAlarm, OperationInvocationContext::none());
    }

    // Can be used to switch condition on and off (e.g. propagate input from real device). Currently not used in this test.
    void setPresence(bool presence) {
        // We do not need to update our state here, this will be done in onStateChangeRequest (will be called by the method we invoke next)
        setAlertConditionPresence(getDescriptorHandle(), presence, OperationInvocationContext::none());
    }

    // Helper method
    LimitAlertConditionState createState() {
        LimitAlertConditionState result(ALERT_CONDITION_HANDLE, AlertActivation::On, Range().setLower(0.0).setUpper(2.0), AlertConditionMonitoredLimits::All); // Reference alert signal descriptor's handle
        result
            .setPresence(false);
        return result;
    }

    LimitAlertConditionState getInitialState() override {
        return createState();
    }

};
@endcode

Changing the condition's presence will trigger all alert signals which are referenced. The implementation of the signal's state handler follows next.

@code
class AlertSignalStateHandler : public SDCProviderMDStateHandler<AlertSignalState>
{
public:

    AlertSignalStateHandler(std::string descriptorHandle)
    : SDCProviderMDStateHandler(descriptorHandle)
    { }

    InvocationState onStateChangeRequest(const AlertSignalState & state, const OperationInvocationContext & oic) override {
        // Invocation has been fired as WAITING when entering this method
        DebugOut(DebugOut::Default, "SimpleSDC") << "Provider: AlertSignalStateHandler received state change: " << EnumToString::convert(state.getPresence()) << std::endl;

        notifyOperationInvoked(oic, InvocationState::Start);

        // Update the real device's state here (update device alarms)! Check state's presence and alertSignalState's presence values!

        // we can update here, but if we return Fin, the framework will also notify
        //updateState(state);
        return InvocationState::Fin;  // Framework will update internal MDIB with the state's value and increase MDIB version
    }

    // Helper method
    AlertSignalState createState() {
        AlertSignalState result(ALERT_SIGNAL_HANDLE, AlertActivation::On); // Reference alert signal descriptor's handle // Component is working
        result
            .setPresence(AlertSignalPresence::Off);  // No alarm signal
        return result;
    }

    AlertSignalState getInitialState() override {
        return createState();
    }

};
@endcode

Finally, the alarm system's state handler.

@code
class AlertSystemStateHandler : public SDCProviderMDStateHandler<AlertSystemState>
{
public:

    AlertSystemStateHandler(std::string descriptorHandle)
    : SDCProviderMDStateHandler(descriptorHandle)
    { }

    AlertSystemState getInitialState() override {
        AlertSystemState alertSystemState(descriptorHandle, AlertActivation::On);  // reference alert system descriptor's handle // Alert is activated
        return alertSystemState;
    }

    // define how to react on a request for a state change. This handler should not be set, thus always return Fail.
    InvocationState onStateChangeRequest(const AlertSystemState&, const OperationInvocationContext&) override {
        return InvocationState::Fail;
    }
};
@endcode

Calling the method <b>setAlertConditionPresence</b> will handle all alert signals which reference a condition automatically. Depending on the condition's presence parameter (true or false), alert signals will be handled as follows.

<ol>
  <li>True: the alert signal's presence state will be set ON (no matter what the previous value was).</li>
  <li>False: if an alert signal's presence state is currently set to ON, it will be set to LATCHED.</li>
</ol>

<p>However, it will never be set OFF or ACK (automatically). The logic behind this will be left to the user code.</p>

@subsection sdc_alarm_system_consumer The Consumer
// NOTE: This subsection needs to be revised!
  
The consumer can be extended by a new state handler, to handle alert state events fired by the provider. Like the <b>ExampleConsumerEventHandler</b> described before, a similar subclass of <b>SDCConsumerMDStateHandler</b> will be used. The new handler will be called <b>ExampleConsumerAlertSignalHandler</b>.

@code
class ExampleConsumerAlertSignalHandler : public SDCConsumerMDStateHandler<AlertSignalState>
{
public:
    ExampleConsumerAlertSignalHandler(const std::string & descriptorHandle)
    : SDCConsumerMDStateHandler(descriptorHandle)
    { }

    void onStateChanged(const AlertSignalState & state) override {
        DebugOut(DebugOut::Default, "SimpleSDC") << "Consumer: Received alert signal changed of " << descriptorHandle << ", presence = " << EnumToString::convert(state.getPresence()) << std::endl;
  
        // ...
    }
    void onOperationInvoked(const OperationInvocationContext & oic, InvocationState is) override {
        DebugOut(DebugOut::Default, "SimpleSDC") << "Consumer: Received operation invoked (ID, STATE) of " << descriptorHandle << ": " << oic.transactionId << ", " << EnumToString::convert(is) << std::endl;
    }
    // ...
};
@endcode

<p>An instance of the handler can be added to the consumer using the Consumer's method <b>registerStateEventHandler</b>. Events will be fired when using the method <b>setAlertConditionPresence</b> on the provider's side.</p>
Using the following code shows how to change an alert signal's activation state (in this case, switch the alarm OFF).

@code
// First request state (this way, we do not have to populate the structure manually)
auto t_state = consumer.requestState<AlertSignalState>("handle_alert_signal");
if (t_state != nullptr) {
  // Switch alert signal off
  t_state->setPresence(AlertSignalPresence::Off);
  FutureInvocationState fis;
  if(t_consumer->commitState(*t_state, fis) == InvocationState::Wait) {
      if(fis.waitReceived(InvocationState::FINISHED, 1000)) {
        std::cout << "Success! Alarm has been switched off." << endl;
      }
  }
}
@endcode

@section sdc_code_snippets Useful code snippets and recipes

@subsection sdc_streaming Streaming

NOTE: See TestStreamSDC for a complete example! - This section is outdated!
  
  
In order to provide streaming, the first thing to do is to define one or more streaming metrics members inside an SDCProvider instance.
<ul>
  <li>Create a member <b>RealTimeSampleArrayMetricDescriptor</b> and configure it in the constructor similar as shown before (define a unique handle for the descriptor).</li>
  <li>Create a provider state handler subclassing <b>SDCProviderRealTimeSampleArrayMetricStateHandler</b> (see example below).</li>
</ul>

@code
class StreamProviderStateHandler : public SDCProviderRealTimeSampleArrayMetricStateHandler {
public:

  StreamProviderStateHandler(std::string descriptorHandle) : descriptorHandle(descriptorHandle) {
  }

  virtual ~StreamProviderStateHandler() { }

  // Helper method
  RealTimeSampleArrayMetricState createState() {
    RealTimeSampleArrayMetricState realTimeSampleArrayState;
    realTimeSampleArrayState
      .setComponentActivationState(ComponentActivation::ON)
      .setDescriptorHandle(descriptorHandle)
      .setHandle(descriptorHandle + "_state");
    return realTimeSampleArrayState;
  }

  RealTimeSampleArrayMetricState getInitialState() override {
    return createState();
  }

  // Called by user code (see next code example)
  void updateStateValue(const RealTimeSampleArrayValue & rtsav) {
    RealTimeSampleArrayMetricState realTimeSampleArrayState = createState();
    realTimeSampleArrayState
      .setObservedValue(rtsav);
    updateState(realTimeSampleArrayState);
  }

private:
    std::string descriptorHandle;
};
@endcode

Produce next block of stream values using this code:

@code
RTValueType values;
std::vector<double> samples;
for (int i = 0; i < size; i++) {
   samples.push_back(i);
}
values.setValues(samples);
RealTimeSampleArrayValue value;
value.setSamples(values);
// Produce next stream chunk
stateHandler.updateStateValue(value);
@endcode

<p>The stream values are sent in blocks to all registered consumers whenever <b>updateState</b> is called.</p>

In order to consume streaming, you can subclass <b>SDCConsumerRealTimeSampleArrayMetricStateHandler</b>. You will then receive a block of next values instead.

@code
class StreamConsumerEventHandler : public SDCConsumerRealTimeSampleArrayMetricStateHandler {

  ...

  void onStateChanged(const RealTimeSampleArrayMetricState & state) {
    std::vector<double> values = state.getObservedValue().getSamples().getValues();
    
    ...
  }
  
  std::string getHandle() {
    ...
  }  
  
}
@endcode

@subsection sdc_activation Custom commands using activations
// NOTE: This subsection needs to be revised!
  
<p>Whenever a (parameterless) function should be called that is not connected directly to a state, a custom activate operation can be defined. For example, this can be used for relative value increases or for simple switches like ON / OFF.</p>

Definition of the handler on the provider's side:

@code
class CommandHandler : public SDCProviderActivateOperationHandler
{
public:

    CommandHandler()
    { }

    InvocationState onActivateRequest(const MDIBContainer & , const OperationInvocationContext & )
    {
        std::cout << "Provider: Received command!" << endl;
  
        // TODO: if needed, make changes in the MDIB (e.g. increase max value) using updateState
  
        return InvocationState::FINISHED;
    }

    std::string getHandle() const {
        return "handle_cmd";
    }

};
@endcode

The following code must be used in the provider to register the operation descriptor using an operation handle and target:

@code
ActivateOperationDescriptor aod;
aod.setHandle("handle_cmd").setOperationTarget("handle_max");
// Add the operation descriptor
addActivateOperationForDescriptor(aod, holdingDeviceSystem);
@endcode

Then at last, the command handler itself must be registered:

@code
CommandHandler cmdHandler;  // Use this as private member in the provider
...
addMDStateHandler(&cmdHandler);
@endcode

To send an activate request, use the following code:

@code
FutureInvocationState fis;
consumer->activate("handle_cmd", fis)
if (fis.waitReceived(InvocationState::FINISHED, 1000)) {
  cout << "Consumer: Activation succeeded!" << endl;
}
@endcode

@subsection sdc_contexts Using contexts
// NOTE: This subsection needs to be revised!
  
To handle incoming commits on the provider's side, there can be only one handler which processes all incoming commits.

@code
class ContextHandler : public SDCProviderContextStateHandler {
public:

  ContextHandler() {
  }
   
  virtual ~ContextHandler() { }

  // Get inital states
  virtual std::vector<LocationContextState> getLocationContextStates() override {
    LocationContextState locationState;
    // This device magically knows its location
    locationState
      .setHandle("location_context_state")
      .setDescriptorHandle("location_context")
      .addIdentification(
        InstanceIdentifier()
          .setroot("MyHospital")
          .setextension("Room 23")
        );
    std::vector<LocationContextState> result;
    result.push_back(locationState);
    return result;
  }

   // TODO: other initial states...
  
  virtual InvocationState onStateChangeRequest(const std::vector<EnsembleContextState> & ecStates,
    const std::vector<LocationContextState> & lcStates,
    const std::vector<OperatorContextState> & ocStates,
    const std::vector<PatientContextState> & pcStates,
    const std::vector<WorkflowContextState> & wcStates,
    const OperationInvocationContext & oic) override {
    
    notifyOperationInvoked(oic, InvocationState::STARTED);
    // TODO: check handles and return InvocationState::Fail;
		
    cout << "Provider: ContextHandler received state change request" << endl;
	
    // TODO: Iterate lcStates, call updateState on the given states
	
    return InvocationState::FINISHED;
  }

}
@endcode

For the descriptive part, we need context descriptors for each state and must add them to the MDS:

@code
LocationContextDescriptor location;  // Use this as private member in the provider
...
location.setHandle("location_context");  // Init like this in constructor
...
holdingDeviceSystem  // Use in getMDDescription
    .setContext(
        SystemContext().setLocationContext(location)
    )
@endcode

Multiple contexts can be added using method chaning, e.g.:

@code
holdingDeviceSystem
  .setContext(
     SystemContext()
       .setLocationContext(...)
       .setPatientContext(...)
       .setWorkflowContext(...)
       .setEnsembleContext(...)
       .setOperatorContext(...)
  )
@endcode

The context handler must be registered in the provider:

@code
ContextHandler contextHandler;  // Use this as private member in the provider
...
addMDStateHandler(&contextHandler);  // Use in constructor
@endcode

On the consumer's side, requesting and committing context states is no more different than handling any other state, the same rules and methods (<b>requestState</b> and <b>commitState</b>) apply. To receive events, subclass <b>SDCConsumerContextStateChangedHandler</b> and override <b>onContextStateChanged</b>.

@subsection sdc_stringenums Using string enums
// NOTE: This subsection needs to be revised!
  
On the provider side, please use the following steps (similar to the ones of conventional metrics):

<ul>
    <li>Create a handler by subclassing <b>SDCProviderEnumStringMetricStateHandler</b> and override <b>onStateChangeRequest</b> and <b>getInitialState</b>. Initialize the handler's internal state (of type <b>EnumStringMetricState</b> in the constructor. Set a descriptor handle and optionally, a state handle (remember that you MUST set a state handle in cases when multiple states refer to the same descriptor!).</li>
    <li>Create a member variable of the handler in the provider and add the handler using <b>addMDStateHandler</b></li>.
    <li>In provider constructor, add the metric descriptor to a channel (using <b>addMetric</b>). Then add a SET operation using <b>createSetOperationForDescriptor</b></li>, if the state shoulb be writable (consumer can commit)!
</ul>

On the consumer side:

<ul>
    <li>Use <b>requestState</b> and <b>commitState</b> to request and commit string enum states (as usual).</li>
    <li>Subclass <b>SDCConsumerEnumStringMetricStateHandler</b> and override <b>onStateChanged</b> method for the type <b>EnumStringMetricState</b>, if events need to be received. Then register the handler in the consumer (<b>registerStateEventHandler</b>). Don't forget to unregister!    
</ul>

**/
