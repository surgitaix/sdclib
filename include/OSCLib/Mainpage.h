/**
@mainpage %OSCLib documentation

Welcome to the Open Surgical Communication Library documentation pages. Use the menu on the left to navigate to a section, or select
one of the page links below.

@li @ref intro <b>OR.NET</b>: A short introduction to the %OSCLib
@li @ref oscppage <b>OR.NET</b>: API for the Open Surgical Communication Protocol
@li @ref startedpage Using the %OSCLib's DPWS layer <b>(not OR.NET)</b>
@li @ref advancedpage Advanced DPWS topics <b>(not OR.NET)</b>

@version 0.95 beta
@author Besting
@copyright (C) 2015 SurgiTAIX AG

@page introductionpage Introduction

@tableofcontents

@section intro Introduction
The Open Surgical Communication Library (%OSCLib) is a lightweight, easy-to-use, easy-to-port, resource-friendly and fast
webservice library for medical devices. It implements the Open Surgical Communication Protocol (OSCP) on top of
DPWS 1.1. %OSCLib supports the WS-Discovery, WS-Addressing, WS-Transfer, WS-Eventing and WS-MetadataExchange specification and is based on
SOAP 1.2 and WSDL 1.1 standards.

@section setup Setting up the development environment

The %OSCLib is mostly platform independent. There are only few parts that are implemented for a specific operating system.
These parts rely on preprocessor directives. Additionally different libraries have to be linked for different operating systems.
The neccessary steps are described below.

The %OSCLib relies on XSD including XERCES (http://www.codesynthesis.com). Also, POCO libs are a major dependency but these have been included as source files.

@subsection linuxspecificcmake CMAKE on linux (Ubuntu or Debian recommended)

We provide a cmake build script, which builds a shared library you can include in your own projects as well as several example
applications which are ready to run. Follow the steps outlined in this section to build %OSCLib on linux.

@subsubsection linuxdependenciesxsd Installing XSD and XERCES

Install XSD and xerces-c binaries and includes, on debian or ubuntu you can use the commands

<ul>
  <li>sudo apt-get install xsdcxx</li>
  <li>sudo apt-get install libxerces-c-dev</li>
</ul>

@subsubsection buildcmake Building OSCLib using cmake

<p>Before running cmake, edit the CMakeList.txt file. You might have to edit paths defined the CMakesList.txt, if dependecies are not installed on the system using <i>make install</i> or 
<i>apt-get install</i>.</p>
Run the following commands from within the project root folder:
<ul>
  <li>mkdir cmake</li>
  <li>cd cmake</li>
  <li>cmake ../</li>
  <li>make</li>
</ul>

The library should now compile and link. If you'd like to configure a debug build, use

<ul>
  <li>cmake -Ddebug=ON</li>
</ul>

@subsection buildjavawrappers Building Java wrappers

@subsubsection buildosclibjava Building OSCLib with Java wrapper code

The SWIG Java wrapper code (C++) must first be included into the build.

<ul>
  <li>First, check if the JVM path is set correctly in the CMakesList.txt (jni.h and jni_md.h are needed for the build).</li>
</ul>

Then configure cmake and run make using

<ul>
  <li>cmake -Djava=ON</li>
  <li>make</li>
</ul>

The resulting shared library can now be included into a precompiled JAR (see next section).

@subsubsection createjavawrappers Creating system-dependend Java JAR library

<p>The JAR file you're about to update already includes pure Java source code which interfaces with the wrapped SWIG C-code now included into the build. 
All native libraries (.dll or .so) must be added to the JAR file manually.</p>
<p>The native libraries are<p>

<ol>
  <li>%OSCLib shared library including SWIG code (libOSCLib.so or OSCLib.dll)</li>
  <li>Additional dependencies, if needed (XERCES)</li>
</ol>

<p>Whether you'll need to include additional dependencies into the JAR or not, depends on how you installed them. If they can be found on the system, they may be omitted.</p>
<p>You can use a precompiled <b>OSCLib.jar</b> archive file, and you'll need an <b>archiver tool</b> to add additional library and index files to the JAR. 
The index file lists all the paths to the library files inside the JAR so that they can be loaded by the JVM.</p>
Follow these steps to update your OSCLib.jar:

<ul>
  <li>Copy %OSCLib shared library (e.g. libOSCLib.so) into a folder (e.g. named <b>libs</b>).</li>
  <li>If needed, copy other dependencies. Usually this is only <b>xerces-c</b>, if not available by system path.</li>
  <li>Create the file <b>nativelibs.txt</b>. Add all library paths, line-by-line (e.g. /libs/libOSCLib.so).</li>
  <li>Add the library folder (e.g. <b>libs</b>) into the OSCLib.jar.</li>
  <li>Add the file <b>nativelibs.txt</b> into the OSCLib.jar root location.</li>
</ul>

You can now use the OSCLib.jar in your java project.

@subsection linuxspecificide Linux specific IDE settings

<ol>
  <li>When you setup your Preprocessor, make sure that the symbol "_LINUX" is defined. The included POCO sources need "POCO_NO_AUTOMATIC_LIBS", "Foundation_EXPORTS" and "Net_EXPORTS" to be set.</li>
  <li>Add %OSCLib include path.</li>
  <li>Optionally XERCES include paths (depending on your system configuration).</li>
  <li>Add %OSCLib library path.</li>
  <li>Optionally XERCES library paths (depending on your system configuration).</li>
  <li>Link %OSCLib, xerces-c and pthread libraries.</li>
</ol>

@subsection windowsspecificide Windows specific IDE settings (Visual Studio [2008, 2010, 2012, 2013])

We provide a Visual Studio 2012 / 2013 solution (see below). CMAKE for windows should also work, but has not been tested thoroughly. If you need to setup your own build system, here are some hints:

<ul>
  <li>XSD (including xerces) bring build scripts or precompiled binaries for several Visual Studio versions. Just use the appropriate one for your version.</li>
  <li>When you setup your Preprocessor, make sure that the symbol "_WIN32" is defined. The included POCO sources need "POCO_NO_AUTOMATIC_LIBS", "Foundation_EXPORTS" and "Net_EXPORTS" to be set.</li>
</ul>

You need to add the following includes to your search path:
- [xerces]/include
- [osclib]/include

You need to link the following binaries:
- ws2_32.lib
- iphlpapi.lib
- xerces-c_3.lib

@page oscppage Open Surgical Communication Protocol

@tableofcontents

@section oscpstartup Framework startup and shutdown
On both consumer and provider side, the library needs to be initialized before use:
@code
// Include common library headers
#include "OSCL.h"
// Start framework
OSCLibrary::getInstance()->startup();
// Optional (override ip autobinding): choose a network adapter by providing an IP address for new socket connections
OSCLibrary::getInstance()->setBindInterface("192.168.1.1");
// Optional (override default port start): choose a global port start number used for bindings
OSCLibrary::getInstance()->setPortStart("2011");
// Do something

OSCLibrary::getInstance()->shutdown();
@endcode

Please make sure to explicitly shutdown the library and all high level object such as consumers and providers. When calling the <b>OSCLibrary::getInstance()->shutdown()</b> all internal memory of the library is freed completely and immediately.
@code
int main() {
  // Startup library and init consumer and provider
  OSCLibrary::getInstance()->startup();
  OSCPConsumer c;
  CustomOSCPProvider p;  // Subclasses OSCPProvider
  
  // do something with p
  // do something with c
  
  // Shutdown provider
  p.shutdown();
  // Disconnect consumer
  c.disconnect();
  // Shutdown library
  OSCLibrary::getInstance()->shutdown();
}
@endcode

@section oscpoverview Overview

The API for the Open Surgical Communication Protocol (OSCP-API) is set on top of DPWS. It was created by the OR.NET data model working group and is based on the DIN EN ISO 11073-10201 information model. The resulting OR.NET data model is called CDM (Communication Data Model).

There are two main instances used for communication:

<ul>
  <li><b>OSCLib::Data::OSCP::OSCPProvider</b>: describes the device, and converts OSCP-conform requests into (proprietary) device commands</li>
  <li><b>OSCLib::Data::OSCP::OSCPConsumer</b>: a client tool used to establish communication with an OSCPProvider</li>
</ul>

<p>Both instances implement a base set of methods defined by a common interface. This interface allows transparent access to the medical device information base (MDIB) which can be regarded as the database that contains the values defined by the CDM.</b> 
<p>In order to integrate a medical device (or a medical information service) into an OSCP Network (i.e. writing an <b>OSCP-Connector</b>), you'll first have to implement an instance of OSCPProvider. The following sections describe this process using a simple example of implementing an OSCP-Connector for the EndoTAIX holding device system, a camera holding device for endoscopy.</p>
Working examples similar to this one can be found in the "Examples" folder, especially in <b>ExampleProject.cpp</b>. The unit tests <b>TestSimpleOSCP.cpp</b> and <b>TestStreamOSCP.cpp</b> might also help to illustrate the OSCP API.

@subsection oscp_mbid The MDIB structure

The MDIB structure is used to exchange information between the OSCPProvider and OSCPConsumer instances. The class structure behind it can be used to describe a medical device or a medical service statically and dynamically. The following (simplified) structure is used for the MDIB:

<ul>
  <li><b>MDIB</b>: the information base holding all static and dynamic sub-structures. Class-name: OSCLib::Data::OSCP::MDIBContainer</li>
    <ul>
      <li><b>Medical Device Description</b>: Describes the static part. Class-name: OSCLib::Data::OSCP::MDDescription</li>
        <ul>
          <li><b>Hydra Medical Device System</b>: Describes the complete device or service. Class-name: OSCLib::Data::OSCP::HydraMDSDescriptor</li>
            <ul>
              <li><b>Virtual Medical Device</b>: Describes a subsystem (e.g. a hardware- or software-modul). Class-name: OSCLib::Data::OSCP::VMDDescriptor</li>
                <ul>
                  <li><b>Channel</b>: Describes a group of metrics. Class-name: OSCLib::Data::OSCP::ChannelDescriptor</li>
                    <ul>
                      <li><b>Metric</b>: Describes a primitive or complex data object (e.g. heart rate measurement). Sub-classes of: OSCLib::Data::OSCP::AbstractMetricDescriptor</li>
                      <li><b>Context</b>: Describes a specifix context (e.g. location of patient demographics). Sub-classes of: OSCLib::Data::OSCP::AbstractContextDescriptor</li>
                    </ul>  
                </ul> 
            </ul>
        </ul>
      <li><b>Medical Devices States</b>: Containes the dynamic part. Class-name: OSCLib::Data::OSCP::MDState</li>
        <ul>
          <li><b>Metric State</b>: Describes the state of a references metric (e.g. current heart rate value). Sub-classes of: OSCLib::Data::OSCP::AbstractMetricState</li> (e.g. NumericMetricState, StringMetricState, etc.)
          <li><b>Context State</b>: Describes the state of a specific context (e.g. patient demographics data). Sub-classes of: OSCLib::Data::OSCP::AbstractContextState</li></li> 
        </ul>  
    </ul>
</ul>

Alert systems can be inserted at the level of the hydra MDS, the VMD or channel. They will be described later in detail.

@section oscp_provider The EndoTAIX OSCP Provider example

This section provides a simplified example for an OSCPProvider instance for the EndoTAIX holding device system. The <b>OSCPHoldingDeviceProvider</b> class extends the <b>OSCLib::Data::OSCP::OSCPProvider</b> class, which requires overriding a method for creating the MDIB's description part and adding <b>handlers</b> for states:

<ol>
  <li>Implementing a method for creating the MDIB's description part <b>getMDDescription</b>: describes the device (statically). <b>MUST</b> be overridden!</li>
  <li>Implementing handlers for states, i.e. subclassing <b>OSCPProviderMDStateHandler</b> and adding the resulting handler with <b>addMDStateHandler</b>!</li>
</ol>

<p>Using <b>OSCProvider::addMDStateHandler</b> is a comfortable way to provide separate handlers for each state. This has the advantage, that code concerning devices's data will be encapsulated elsewhere. This will keep our class (OSCPHoldingDeviceProvider) short.</p>

<P>In this example, the provider contains two metrics, which describe their purpose and properties:
One for current weight (currentWeightMetric, read-only), which is measured using a force-torque-sensor attached to the arm. The other one defines the maximum weight limit (maxWeightMetric, read-write). Each metric also needs a corresponding <b>metric state</b> which contains the actual value.</p>
Each metric state will be encapsulated in a separate handler, which subclasses <b>OSCPProviderMDStateHandler</b>.

@subsection oscp_provider_basics_descriptive Implementation - The descriptive part

The implementation of the provider's descriptive part can be structured as followed.

@code
class OSCPHoldingDeviceProvider : public OSCPProvider {
public:
  OSCPHoldingDeviceProvider() { ... }

  MDDescription getMDDescription() override { ... }

  ...

private:
  // The current weight
  NumericMetricDescriptor currentWeightMetric;
  
  // Maximum weight
  NumericMetricDescriptor maxWeightMetric;
  
  ...
}
@endcode

First, the descriptors have to be filled with proper definitions for our example device. For convenience, we do this in the constructor of our OSCPHoldingDeviceProvider. However this is not a strict requirement.

The most important thing about initializing the metrics is that each metric needs a unique string identifier called "handle", which we define here. You are totally free to chose the handles, as long as they are unique within your device. It is also valid to generate them randomly.

@code
OSCPHoldingDeviceProvider() {
  setEndpointReference("EPR_12345");

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

<p>The implementation of <b>getMDDescription</b> constructs the description (containing the hydra MDS) <b>bottom-up</b>, which statically describes the structure of our device and uses the definitions of our metrics:
Each metric must be added to a channel instance, the channel instance to the virtual medical device instance and that one finally to the medical device system instance.</p>

<p><b>Important:</b> To make the maximum value state writeable (<b>onStateChangeRequest</b> implemented), a set operation descriptor must be added using <b>createSetOperationForDescriptor</b>!</p>

@code
MDDescription getMDDescription() override {

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

  // Hydra MDS
  HydraMDSDescriptor holdingDeviceSystem;
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
    // Add VMD to MDS
    .addVMD(holdingDeviceModule)
    .setType(
      CodedValue()
        .setCodingSystemId("OR.NET.Codings")
  	    .setCodeId("MDCX_CODE_ID_MDS"));

  // Create SET operation for max value
  createSetOperationForDescriptor(maxWeightMetric, holdingDeviceSystem);
  
}
@endcode

@subsection oscp_provider_basics_dynamic Implementation - The dynamic part

For the dynamic part, we have to implement handlers of a subtype of <b>OSCPProviderMDStateHandler</b> (e.g. <b>OSCPProviderNumericMetricStateHandler</b>) where each handler takes care of a single state, as already mentioned before.
<p>If the state is writable (SETTING), the handler has to provide at least a type-specific implementation of <b>onStateChangeRequest</b> for a specific subtype of <b>AbstractState</b> (e.g. NumericMetricState or StringMetricState) which processes incoming change requests for our metric state.</p>
Each state must refer to the descriptor's state handle. If multiple states refer to the same descriptor, each state must furthermore have its own state handle. Otherwise this is optional.
<p>The method <b>getState</b> returns the current state (subclass of <b>AbstractState</b>). Inside the constructor, we initialize our state object. We will implement two handlers. Firstly, one for the current value and secondly, one for the maximum value.</p>

@code
class CurValueStateHandler : public OSCPProviderNumericMetricStateHandler {
public:

  CurValueStateHandler() {
    currentWeightState
      .setObservedValue(NumericMetricValue().setValue(0.0))  // Initial value
      .setComponentActivationState(ComponentActivation::ON)
      .setDescriptorHandle("handle_cur");  // Reference the metric's handle
  }
  
  // Note: no implementation of onStateChangeRequest (state is read-only)

  NumericMetricState getState() const override {
    Poco::Mutex::ScopedLock lock(getMutex());  // Pay attention to concurrency (only use provider's mutex)
    NumericMetricState result(currentWeightState);
    return result;
  }

  // This method should be called providing the real value from the device as parameter!
  void setNumericValue(double value) {
    Poco::Mutex::ScopedLock lock(getMutex());  // Pay attention to concurrency (only use provider's mutex)
    currentWeightState.setObservedValue(NumericMetricValue().setValue(value));
    // Notify all consumers which registered on the handle that the state has just changed
    notifyMDIBObjectChanged(&currentWeightState);
  }

private:
  NumericMetricState currentWeightState;
};
@endcode

The handler for the max value state:

@code
class MaxValueStateHandler : public OSCPProviderMDStateHandler {
public:

  MaxValueStateHandler() {
    maxWeightState
      .setObservedValue(NumericMetricValue().setValue(2.0))  // Initial value
      .setComponentActivationState(ComponentActivation::ON)
      .setDescriptorHandle("handle_max");  // Reference the metric's handle  
  }

  // Overrides base
  InvocationState onStateChangeRequest(const NumericMetricState & state, const OperationInvocationContext & oic) override {
    // Invocation has been fired as WAITING when entering this method

    cout << "Provider: MaxValueStateHandler received state change request" << endl;

    // Notify that the operation is about to start...
    notifyOperationInvoked(oic, InvocationState::STARTED);
    // Save the actual value in our state
    {
      Poco::Mutex::ScopedLock lock(getMutex());  // Pay attention to concurrency (only use handler's mutex)
      maxWeightState.copyFrom(state);
    }
    // we can notify here, but if we return FINISHED, the framework will also notify
    //notifyMDIBObjectChanged(maxWeightState);

    // Usually, update the real device's state here...
    // ...

    return InvocationState::FINISHED;
  }

  // Overrides base
  NumericMetricState getState() const override {
    Poco::Mutex::ScopedLock lock(getMutex());  // Pay attention to concurrency (only use handler's mutex)
    NumericMetricState result(maxWeightState);
    return result;
  }

private:
  NumericMetricState maxWeightState;
};
@endcode

We extend the constructor's code to add the handlers, which we define as members of the holding device provider class.

@code
class OSCPHoldingDeviceProvider : public OSCPProvider {
public:
  OSCPHoldingDeviceProvider() {
  
    ...
  
    // Add state handler's
    addMDStateHandler(&maxValueState);
    addMDStateHandler(&curValueState);
  
  }

private:
  // Current weight
  NumericMetricDescriptor currentWeightMetric;
  // State handler
  CurValueStateHandler curValueState;
  
  // Maximum weight
  NumericMetricDescriptor maxWeightMetric;
  // State handler
  MaxValueStateHandler

}
@endcode

@subsection oscp_provider_start Implementation - Start the provider

Starting the provider can be done by calling the method <b>startup</b>. The periodic update thread can be launched by calling <b>start</b>.
 The provider can be stopped by calling </b>shutdown</b>:
@code
// Start framework
OSCLibrary::getInstance()->startup();

// The OSCP Provider instance
{ 
  OSCPHoldingDeviceProvider provider;
  // Start provider
  provider.startup();  
  ...

  provider.shutdown();
}

@endcode

@section oscp_consumer The EndoTAIX OSCP Consumer example

<p>An OSCPConsumer instance is always connected to exactly one OSCPProvider instance. OSCPConsumer instances can be retrieved via the ServiceManager by using its connection and discovery methods.</p>

@subsection oscp_consumer_servicemanager Discovery using the ServiceManager

<p>An OSCPConsumer instance cannot be instantiated directly. The only component that can produce these instances is the ServiceManager (<b>OSCLib::Data::OSCP::OSCPServiceManager</b>).
The ServiceManager is resposibe for the discovery of OSCPProvider instances. 
We will now discover the provider using the ServiceManager:

@code
OSCPServiceManager oscpsm;
shared_ptr<OSCPConsumer> consumer = oscpsm.discoverEndpointReference("EPR_1234");
if (consumer != 0) {
  ...
}
@endcode

It's also possible to directly connect using a known transport address:

@code
OSCPServiceManager oscpsm;
shared_ptr<OSCPConsumer> consumer = oscpsm.connect("http://192.168.1.32:1234/UDI_1234");
@endcode

The actual address can be retrieved by calling <b>OSCPConsumer.getProviderXAddr</b>.

@subsection oscp_consumer_events Using the consumer - reception of events

If we like to process events (in this case, the ones containing states for the current weight metric), we'll have to provide an event handler of a subtype of
<b>OSCPConsumerEventHandler</b> (e.g. <b>OSCPConsumerNumericMetricStateHandler</b>), implement the <b>onStateChanged</b> (if the metric is writable!) and override the <b>getHandle</b> method. The <b>onStateChanged</b> method will be entererd whenever the framework or the user code notify about a metric change (notifyMDIBObjectChanged).
Optionally, the method <b>onOperationInvoked</b> can be overwritten to receive detailed notification about invocation states.

@code
class ExampleConsumerEventHandler : public OSCPConsumerNumericMetricStateHandler
{
public:

  ExampleConsumerEventHandler(const std::string & handle) {
    currentWeight = 0;
    this->handle = handle;
  }

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

@subsection oscp_consumer_request_commit Using the consumer - Request and commit states

The currentweight metric state can also be requested directly using <b>requestState</b>:

@code
NumericMetricState currentWeightState;
if (consumer.requestState("handle_cur", currentWeightState)) {
  // Note: the following pre-check is very important - if the observed value is missing, the code will result in undefined behaviour!
  if (currentWeightState.hasObservedValue()) {
    cout << "Current weight value is: " << currentWeightState.getObservedValue().getValue() << endl;
  }
}
@endcode

<p><b>Important:</b> The handle provided to the function can either be the descriptor's handle or the state's handle (if there is any). In cases when multiple states refer to the same descriptor, the state's handle must be used! the same thing applies to commiting states (see below).</p> 

@subsubsection oscp_consumer_request_commit_async Handling async commits

<p>Committing states takes place <b>asynchronously</b>, which means the method always returns at once, independently from how long the actual change process takes to complete on the Provider's side. The default return value for a change process that has preliminary been accepted, is InvocationState::WAITING.</p>
However, in some cases like the currentweight metric, the invocation state will indicate a failure because this metric is read-only:

@code
NumericMetricState currentWeightStateResult;
InvocationState::Value is = consumer.commitState(currentWeightState);
// is == InvocationState::FAILED
@endcode

<p>Please note that in this case the framework itself makes this determination and returns this value in the response. If for example InvocationState::FAILED is returned by the provider handler's user code,
it can only be detected by evaluating the results later, because the immediate return value will still be InvocationState::WAITING (remember that the user code on the provider's side will be executed asynchronously).</p>
There are two possibilities of how to handle results of asynchronously committed states:

<ul>
  <li>Synchronously wait for received invocation state(s) by using a <b>FutureInvocationState</b> object provided to the <b>commit</b> function. Then call <b>waitReceived</b> after the commit.</li>
  <li>Handle operation invoked reports and episodic metric / alert / context reports in a user-defined subclass of subtypes of OSCPConsumerEventHandler (<b>onOperationInvoked</b> and <b>onStateChanged</b>) like shown before. The <b>FutureInvocationState</b> object can be used to get the right transaction ID which must somehow be taken into account by the handler.</li>
</ul>

So in each case, a <b>FutureInvocationState</b> object is needed, either to use its methods to actively wait for an event to occur or to get the transaction ID and compare it with events received elsewhere.
The first case is very easy to implement:

@code
NumericMetricState maxWeightState;
maxWeightState.setDescriptorHandle("handle_max");
maxWeightState.setObservedValue(NumericMetricValue(3.0));
FutureInvocationState fis;
if (consumer.commitState(maxWeightState, fis) == InvocationState::WAITING) {
  cout << "Commit in progress..." << endl;
  // Wait FINISHED to be signaled in the next 1000 milliseconds
  if (fis.waitReceived(InvocationState::FINISHED, 1000)) {
  	cout << "Commit succeeded within expected time!" << endl;
  }
}
@endcode

The second case would be more complicated because the chronology of messages sent from the server is not deterministic. Operation invoked reports can be received by the consumer event handler before the commit function actually returns. At this point, the transaction ID (created by the provider) is not yet known on the
consumer's side. One way to address this problem would be to maintain a history of received events in the consumer event handler.

@subsection oscp_consumer_close Using the consumer - Cut the cable

If the consumer is not needed any more, it should be disconnected (it MUST be disconnected before deletion). Handlers may be unregistered before that (if not, on the provider side the event subscription will time out):

@code
consumer.unregisterStateEventHandler(handler1);
consumer.unregisterStateEventHandler(handler2);
consumer.disconnect();
// shared_ptr will delete consumer when leaving scope
@endcode

@section oscp_alarm_system The alarm system

<p>The structures and methods of the alarm system can be used to implement alarm situations using mostly <b>conditions</b> and <b>signals</b>. Descriptors and states exist for each of the latter. This section describes an extension of the previous example to produce and consume an alarm, if the current weight value exceeds the maximum value. A real implementation of this example can be found in the unit test <b>TestSimpleOSCP.cpp</b><p>
<p>An alert condition holds the information about an actual alarm situation, while an alert signal's purpose is to define, how exactly the condition should be reported. In general, multiple signals can reference the same condition. We start again with the descriptive part.</p>

@subsection oscp_alarm_system_provide The provider

We'd like to create an alert for the condition when the current weight value exceeds the maximum value and extend the holding device's provider with the following code. 

@code
class OSCPHoldingDeviceProvider : public OSCPProvider {
public:
  OSCPHoldingDeviceProvider() {
  
    ...
  
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
  
  MDDescription getMDDescription() override {
  
    ...
  
    // Setup alert system
    AlertSystemDescriptor alertSystem;
    alertSystem
        .addAlertSignal(alertSignal)
        .addAlertCondition(alertCondition)
        .setHandle("handle_alert_system"); 
      
    // Add to channel (VMD or MDS is also possible)
    holdingDeviceChannel.setAlertSystem(alertSystem);
    ...
    
    // Create SET operation descriptor
    createSetOperationForDescriptor(alertSignal, holdingDeviceSystem);
    
  }

private:
  ...
  
  // Alert descriptors
  AlertSignalDescriptor alertSignal;
  AlertConditionDescriptor alertCondition;
  
  // Alert states
  AlertConditionStateHandler alertCondHandler;  // See implementation details below
  AlertSignalStateHandler alertSigHandler;  // See implementation details below
  AlertSystemStateHandler alertSysHandler;  // See implementation details below
}
@endcode

The <b>AlertConditionStateHandler</b> and <b>AlertSignalStateHandler</b> classes extend the OSCPProviderAlertConditionStateHandler and the OSCPProviderAlertSignalStateHandler, resp. The behaviour of the method call to <b>setAlertConditionPresence</b> will be explained later.

@code
class AlertConditionStateHandler : public OSCPProviderAlertConditionStateHandler {
public:

  AlertConditionStateHandler() {
    // Init state
    alertConditionState
        .setDescriptorHandle("handle_alert_condition")  // Reference alert signal descriptor's handle
        .setActivationState(PausableActivation::ON)  // Component is working
        .setPresence(false);  // No condition detected
  }

  InvocationState onStateChangeRequest(const AlertConditionState & state, const OperationInvocationContext &) {
    cout << "AlertConditionStateHandler received state change, presence = " << state.getPresence() << endl;
    if (state.getPresence() != alertConditionState.getPresence()) {
      // Do something, if necessary...
    }
    
    Poco::Mutex::ScopedLock lock(getMutex());  // Pay attention to concurrency (only use handler's mutex)
    alertConditionState.copyFrom(state);
    return InvocationState::FINISHED;
  }

  // Can be used to switch condition on and off (e.g. propagate input from real device). Currently not used in this example.
  void setPresence(bool presence) {
    // We do not need to update our state here, this will be done in onStateChangeRequest 
    // (will be called by the method we invoke next)
    setAlertConditionPresence(getState().getDescriptorHandle(), presence, OperationInvocationContext::none());
  }

  AlertConditionState getState() const {
    Poco::Mutex::ScopedLock lock(getMutex());  // Pay attention to concurrency (only use handler's mutex)
    AlertConditionState result(alertConditionState);
    return result;
  }

private:
  AlertConditionState alertConditionState;
};
@endcode

Changing the condition's presence will trigger all alert signals which are referenced. The implementation of the signal's state handler follows next.

@code
class AlertSignalStateHandler : public OSCPProviderMDStateHandler {
public:

  AlertSignalStateHandler() {
    // Init state
    alertSignalState
        .setDescriptorHandle("handle_alert_signal")  // Reference alert signal descriptor's handle
        .setActivationState(PausableActivation::ON)  // Component is working
        .setPresence(SignalPresence::Off);  // No alarm signal
  }

  InvocationState::Value onStateChangeRequest(const AlertSignalState & state) {
    // Invocation has been fired as WAITING when entering this method

    cout << "Provider: AlertSignalStateHandler received state change: " << EnumToString::convert(state.getPresence()) << endl;
   
    // Update the real device's state here (update device alarms)! Check [state]'s presence and [alertSignalState]'s presence values!
    // ...

    Poco::Mutex::ScopedLock lock(getMutex());  // Pay attention to concurrency (only use handler's mutex)
    alertSignalState.copyFrom(state);

    return InvocationState::FINISHED;
  }

  AbstractState getState() const {
    Poco::Mutex::ScopedLock lock(getMutex());  // Pay attention to concurrency (only use handler's mutex)
    AlertSignalState result(alertSignalState);
    return result;
  }
  
private:
  AlertSignalState alertSignalState;  
@endcode

Finally, the alarm system's state handler.

@code
class AlertSystemStateHandler : public OSCPProviderAlertSystemStateHandler {
public:

  AlertSystemStateHandler() {
    // reference alert system descriptor's handle
    alertSystemState
      .setActivationState(PausableActivation::ON)
      .setDescriptorHandle("handle_alert_system");
  }

  AlertSystemState getState() const {
    Poco::Mutex::ScopedLock lock(getMutex());  // Pay attention to concurrency (only use handler's mutex)
    AlertSystemState result(alertSystemState);
    return result;
  }

private:
  AlertSystemState alertSystemState;
};
@endcode

The numeric state handler's implementation described in one of the previous sections can now be extended with code that actually sets the alarm conditions presence flag, if the condition arises (current value exceeds max value).

@code
class CurValueStateHandler : public OSCPProviderMDStateHandler {
public:

  ...

  // This method should be called providing the real value and the limit (defined by the max value's state handler)!
  void setNumericValue(double value, double maxLimit) {
    Poco::Mutex::ScopedLock lock(getMutex());  // Pay attention to concurrency (only use handler's mutex)
    currentWeightState.setObservedValue(NumericMetricValue().setValue(value));
    // Notify about the change
    notifyMDIBObjectChanged(currentWeightState);
    
    // Check limit and trigger alarm condition, if needed (the method will then take care of handling all signal states)
    if (value > maxLimit)
      setAlertConditionPresence("handle_alert_condition", true, OperationInvocationContext::none());
    else
      setAlertConditionPresence("handle_alert_condition", false, OperationInvocationContext::none());
  }

private:
NumericMetricState currentWeightState;  
}
@endcode

Calling the method <b>setAlertConditionPresence</b> will handle all alert signals which reference a condition automatically. Depending on the condition's presence parameter (true or false), alert signals will be handled as follows.

<ol>
  <li>True: the alert signal's presence state will be set ON (no matter what the previous value was).</li>
  <li>False: if an alert signal's presence state is currently set to ON, it will be set to LATCHED.</li>
</ol>

<p>However, it will never be set OFF or ACK (automatically). The logic behind this will be left to the user code.</p>

@subsection oscp_alarm_system_consumer The consumer

The consumer can be extended by a new state handler, to handle alert state events fired by the provider. Like the <b>ExampleConsumerEventHandler</b> described before, a similar subclass of <b>OSCPConsumerAlertSignalStateHandler</b> will be used. The new handler will be called <b>ExampleConsumerAlertEventHandler</b>.

@code
class ExampleConsumerAlertEventHandler : public OSCPConsumerAlertSignalStateHandler {
public:
  ExampleConsumerAlertEventHandler(const string & handle) :
    handle(handle) {
  }

  virtual ~ExampleConsumerAlertEventHandler() {
  }

  void onStateChanged(const AlertSignalState & state) override {
    cout << "Consumer: Received alert signal changed of " << handle << ", presence = " << EnumToString::convert(state.getPresence()) << endl;
  }
  
  void onOperationInvoked(const OperationInvocationContext & oic, InvocationState is) {
    // Implement, if needed...
  }

  string getHandle() {
    return handle;
  }

private:
  Poco::Mutex mutex;
  string handle;
};
@endcode

<p>An instance of the handler can be added to the consumer using the Consumer's method <b>registerStateEventHandler</b>. Events will be fired when using the method <b>setAlertConditionPresence</b> on the provider's side.</p>
Using the following code shows how to change an alert signal's activation state (in this case, switch the alarm OFF).

@code
AlertSignalState alertSignal;
// First request state (this way, we do not have to populate the structure manually)
if (consumer.requestState("handle_alert_signal", alertSignal)) {
  // Switch alert signal off
  alertSignal.setPresence(SignalPresence::Off);
  FutureInvocationState fis;
  if (consumer.commitState(alertSignal) == InvocationState::WAITING && fis.waitReceived(InvocationState::FINISHED, 1000)) {
    cout << "Success! Alarm has been switched off." << endl;
  }
}
@endcode

@section oscp_code_snippets Useful code snippets and recipes

@subsection oscp_streaming Streaming
In order to provide streaming, the first thing to do is to define one or more streaming metrics members inside an OSCPProvider instance.
<ul>
    <li>Create a member <b>RealTimeSampleArrayMetricDescriptor</b> and configure it in the method <b>getMDDescription</b> similar as shown before (define a unique handle for the descriptor).</li>
    <li>Create a provider state handler subclassing <b>OSCPProviderRealTimeSampleArrayMetricStateHandler</b>.</li>
    <li>Create a state member of the type <b>RealTimeSampleArrayMetricState</b> in the handler (remember to set the descriptor handle).</li>
    <li>Update the sample values using <b>RealTimeSampleArrayMetricState.setObservedValue</b> (see example below).</li>
</ul>

Use the following (or similar) code to produce the next block of stream sample values:
@code
RTValueType values;
std::vector<double> samples;
for (int i = 0; i < size; i++) {
   samples.push_back(i);
}
values.setValues(samples);
RealTimeSampleArrayValue value;
value.setSamples(values);
outputStreamState.setObservedValue(value);
notifyMDIBObjectChanged(outputStreamState);
@endcode

<p>The stream values are sent in blocks to all registered consumers whenever <b>notifyMDIBObjectChanged</b> is called.</p>

In order to consume streaming, you can subclass <b>OSCPConsumerRealTimeSampleArrayMetricStateHandler</b>. You will then receive a block of next values instead.

@code
class StreamConsumerEventHandler : public OSCPConsumerRealTimeSampleArrayMetricStateHandler {

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

@subsection oscp_activation Custom commands using activations

<p>Whenever a (parameterless) function should be called that is not connected directly to a state, a custom activate operation can be defined. For example, this can be used for relative value increases or for simple switches like ON / OFF.</p>

Definition of the handler on the provider's side:

@code
class CommandHandler : public OSCPProviderActivateOperationHandler {
public:

  CommandHandler() {
  }

  InvocationState onActivateRequest(const MDIBContainer & , const OperationInvocationContext & ) {
    cout << "Provider: Received command!" << endl;
    
    // TODO: if needed, make changes in the MDIB (e.g. increase max value), then notify using notifyMDIBObjectChanged
    
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

@subsection oscp_contexts Using contexts

To handle incoming commits on the provider's side, there can be only one handler which processes all incoming commits.

@code
class ContextHandler : public OSCPProviderContextStateHandler {
public:

   ContextHandler() {
     // Example state:
     locationState
         .setHandle("location_context_state")
         .setDescriptorHandle("location_context")
         .addIdentification(
            InstanceIdentifier()
              .setroot("MyHospital")
              .setextension("Room 23")
     );   
     // Init more states here, if needed...
   }
   
  virtual std::vector<LocationContextState> getLocationContextStates() override {
    Poco::Mutex::ScopedLock lock(getMutex());  // Pay attention to concurrency (only use handler's mutex)
    std::vector<LocationContextState> result;
    result.push_back(locationState);
    return result;
  }   
  
virtual InvocationState onStateChangeRequest(const std::vector<EnsembleContextState> & ecStates,
    const std::vector<LocationContextState> & lcStates,
    const std::vector<OperatorContextState> & ocStates,
    const std::vector<PatientContextState> & pcStates,
    const std::vector<WorkflowContextState> & wcStates,
    const OperationInvocationContext & oic) override {
    
    notifyOperationInvoked(oic, InvocationState::STARTED);
    // TODO: check handles and return InvocationState::FAILED;
		
    cout << "Provider: ContextHandler received state change request" << endl;
    Poco::Mutex::ScopedLock lock(getMutex());  // Pay attention to concurrency (only use handler's mutex)
	
    // TODO: Iterate lcStates, copy the right state using locationState.copyFrom(...)
	
    // TODO: Notify consumers, use notifyMDIBObjectChanged(...);
    return InvocationState::FINISHED;
}  

private:
  LocationContextState locationState;
  ...

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

On the consumer's side, requesting and committing context states is no more different than handling any other state, the same rules and methods (<b>requestState</b> and <b>commitState</b>) apply. To receive events, subclass <b>OSCPConsumerContextStateChangedHandler</b> and override <b>onContextStateChanged</b>.

@subsection oscp_stringenums Using string enums

On the provider side, please use the following steps (similar to the ones of conventional metrics):

<ul>
    <li>Create a handler by subclassing <b>OSCPProviderEnumStringMetricStateHandler</b> and override <b>onStateChangeRequest</b> and <b>getState</b>. Initialize the handler's internal state (of type <b>EnumStringMetricState</b> in the constructor. Set a descriptor handle and optionally, a state handle (remember that you MUST set a state handle in cases when multiple states refer to the same descriptor!).</li>    
    <li>Create a member variable of the handler in the provider and add the handler using <b>addMDStateHandler</b></li>.
    <li>Create a member variable for an enum descriptor (type <b>EnumStringMetricDescriptor</b> and initialize if in the constructor. Use <b>addAllowedValue</b>. Use <b>setHandle</b> to set the descriptor handle (must equal to the the one used in the handler).</li>
    <li>In <b>getMDDescription</b>, add the metric descriptor to a channel (using <b>addMetric</b>). Then add a SET operation using <b>createSetOperationForDescriptor</b></li>, if the state shoulb be writable (can commit)!
</ul>

On the consumer side:

<ul>
    <li>Use <b>requestState</b> and <b>commitState</b> to request and commit string enum states (as usual).</li>
    <li>Subclass <b>OSCPConsumerEnumStringMetricStateHandler</b> and override <b>onStateChanged</b> method for the type <b>EnumStringMetricState</b>, if events need to be received. Then register the handler in the consumer (<b>registerStateEventHandler</b>). Don't forget to unregister!    
</ul>

@page startedpage Using the OSCLib's DPWS layer

@tableofcontents

<p>The Devices Profile for Web Services (DPWS) specifies a standard for web-services targeting resource-constrained devices. It combines several WS-*
specifications in combination with own extensions. The %OSCLib may be used as a library for the DPWS 1.1 (aka 2009) version since it implements
the most part of it, but only as much as needed for the OSCB-protocol (e.g. WS-Security is not implemented). In this section, framework basics and
DPWS functions will be described.</p>

@section started Getting started

@subsection autobinding Autobinding to a network interface

The library tries to bind itself to a network interface. Usually it takes the first interface that it finds and which is not the loopback adapter.
You can override this by calling the <b>OSCLibrary::setBindInterface</b> method after starting the framework, as shown below.
Also, the library defines a global port start number (default is 9000) which will be used and increased for all bindings, which are created
automatically, if needed. This number can be changed using <b>OSCLibrary::setPortStart</b>.

@subsection startup Framework startup and shutdown
On both client and server side, the library needs to be initialized before use:
@code
// Include common library headers
#include "OSCL.h"
// Start framework
OSCLibrary::getInstance()->startup();
// Optional (override ip autobinding): choose a network adapter by providing an IP address for new socket connections
OSCLibrary::getInstance()->setBindInterface("192.168.1.1");
// Optional (override default port start): choose a global port start number used for bindings
OSCLibrary::getInstance()->setPortStart("2011");
// Do something

OSCLibrary::getInstance()->shutdown();
@endcode

Please make sure to explicitly shutdown the library and all high level objects such as consumers and providers. When calling the <b>OSCLibrary::getInstance()->shutdown()</b> all internal memory of the library is freed completely and immediately.

@subsection createdevice Create the first device
Low level DPWS objects like devices and services can be created (server side), or a client can be used to communicate 
with a remote device or service (client side). With the framework started the next step would be to create a device:

@code
// Create device, remember to delete it later
Device* device = new Device();
// Add custom endpoint reference
device->setEPRAddress("urn:uuid:1234");
// Add types and scopes
device->addType(QName("MedicalDevice", "http://www.surgitaix.com/example"));
device->addScope("http://www.surgitaix.com/example");

// ...

delete device;
@endcode

The <b>Device</b>-class can also be subclassed. By default the device is being configured to support the DPWS 1.1 protocol,
thus being discoverable.
Types and scopes can be used to search for the device.
Finally, the device needs a specific binding, that defines the network configuration for the DPWS 1.1 protocol. Defining
such a binding is optional: if it's missing, the library automatically creates one based on global settings for ip binding and
port start (<b>OSCLibrary::setBindInterface</b> and <b>OSCLibrary::setPortStart</b>).

@code
// Optional: create binding for device (remember to delete it later)
Binding * deviceBinding = new Binding("192.168.1.1", 1234, "ExampleDevice");
device->addBinding(DPWS11, deviceBinding);
@endcode

If defined in such way, the binding must specify a valid network adapter IP address, port number and an optional path.
The default binding type is HTTP/TCP, but UDP is also possible (however not recommended) by adding:

@code
// Warning: ALL communication is routed using UDP which is NOT reliable!
deviceBinding->setType(Binding::UDP);
@endcode

In HTTP/TCP case the device is now reachable over a simple HTTP browser request at http://192.168.1.1:1234/ExampleDevice
as soon as it has been started. The device responses to such a request with an XML device snapshot response conform
with http://schemas.xmlsoap.org/ws/2004/09/transfer/GetResponse.
A device snapshot should of course contain further device characteristics, that can be added as shown next.

@code
DeviceCharacteristics * dc = device->getDeviceCharacteristics();
dc->setManufacturer("SurgiTAIX");
dc->setManufacturerUrl("www.surgitaix.com");
dc->addModelName("en-US", "Example Model");
dc->setModelNumber("1");
dc->setModelUrl("http://www.surgitaix.com/example");
dc->addFriendlyName("en-US", "Example device");
dc->setFirmwareVersion("1.0");
dc->setSerialNumber("123");
@endcode

By default, these values are added to any Device created so that adding characteristics may be omitted to get started.
Device characteristics are included in any metadata request. Finally the device has to be started (and stopped at the end):

@code
// Start device (starts services if available)
device->start();

// ...

// Stop device (before it runs out of scope)
device->stop();
@endcode

@subsection createservice Create and host a service
At this point the device does not yet host any service that provides some particular functions that can be called remotely.
Defining such a service is very similar to a device.

@code
// Create a service, remember to delete it later
Service* service = new Service();
// Add service ID
service->setServiceId("ExampleServiceId1");
// Optional: create binding for service (must differ from device's one!)
Binding* serviceBinding = new Binding("192.168.1.1", 1235, "ExampleService");
service->addBinding(DPWS11, serviceBinding);
@endcode

For the service to be useful, it has to offer at least one operation that can be called remotely. This can be done
by subclassing <b>Operation</b>.

@code
class ExampleOperation : public Operation
{
  ...
}
@endcode

The first thing is to define a name and a port type of the operation (constructor). Here, we want to create a simple
operation that returns the sum of two integer numbers. We need two input parameters and one output parameter.

@code
ExampleOperation()
{
  // The operation's name
  setName("GetSum");
  // The port type
  QName portType("ExampleServicePort", "http://www.surgitaix.com/example");
  setPortType(portType);
  // Input parameters
  Parameter p1("InValue1", Parameter::INT);
  Parameter p2("InValue2", Parameter::INT);
  addInputParameter(p1);
  addInputParameter(p2);
  // Output parameter
  Parameter p3("OutValue", Parameter::INT);
  addOutputParameter(p3);
}
@endcode

The operation's invoke method defines what to do when the operation method is called:

@code
Parameters invoke(Parameters& p)
{
  // Convert input parameters to int (no range check here!)
  int i1 = atoi(p[0].getValue().c_str());
  int i2 = atoi(p[1].getValue().c_str());
  // Sum up
  int r = i1 + i2;
  // Convert int result back to string
  Parameter result;
  stringstream s;
  s << r;
  result.setValue(s.str());
  Parameters returnParams;
  // Insert and return result
  returnParams.push_back(result);
  return returnParams;
}
@endcode

The <b>ExampleOperation</b> class is complete. An instance can now be added to the service:

@code
// Add operation to service, remember to delete operation later
ExampleOperation* op = new ExampleOperation();
service->addOperation(op);
@endcode

At last, the service has to be added to the device and started.
@li Note: The default behavior of starting a device includes starting all services automatically. Starting each service
separately as shown next, may be replaced by simply starting the device once in the end.

@code
// Add service to device
device->addService(service);
service->start();
@endcode

If needed, a WSDL description is generated on-the-fly. It can be retrieved with a simple browser request at
http://192.168.1.1:1235/ExampleService/description.wsdl. The client uses the description to build up a remote service reference.

@section client Using the client

@subsection client_search Searching

Once the device, service and operation have been created on the server-side, a client can be used on the client-side
to discover the device and service and invoke an operation. Defining search parameters of the client depends on the following:

@li If the endpoint reference of the device is known and all services (thus all operations) should be accessible, using <b>client.setDeviceEPRAdrSearchParam</b> is recommended.
@li If the endpoint reference of the device is known and only a particular service should be accessible who's service ID is known, using <b>setServiceIDSearchParam</b> in addition is recommended.
@li If multiple services of multiple devices should be accessible, instead of defining the endpoint reference and/or the service ID you may start a search without parameters. However it is strongly recommended to narrow down the results by defining certain types and scopes using <b>client.addDeviceTypeSearchParam</b>, <b>client.addDeviceScopeSearchParam</b> or <b>client.addServiceTypeSearchParam</b>

We start with the EPR method:

@code
Client client;
// Define the device's endpoint reference to resolve its transport address
client.setDeviceEPRAdrSearchParam("urn:uuid:1234");

// Resolve the device and all of its services
bool found = client.searchSync();

if (found)
{
  ...
}

// Always close the client (before it runs out of scope)
client.close();
@endcode

Say you don't know the device's EPR, then some code like this would be useful:

@code
Client client;
// Look for the service ID instead of the devices EPR
client.setServiceIDSearchParam("ExampleServiceId1");

// Add some more search criteria to narrow down responses (all have to match)
client.addDeviceScopeSearchParam("http://www.surgitaix.com/example");
client.addDeviceTypeSearchParam(QName("MedicalDevice", "http://www.surgitaix.com/example"));
client.addServiceTypeSearchParam(QName("ExampleServicePort", "http://www.surgitaix.com/example"));

// Send out a probe to find the device and only one of its services
bool found = client.searchSync();

if (found)
{
  ...
}

// Always close the client (before it runs out of scope)
client.close();
@endcode

Another possibility is to search for anything and then inspect the results afterwards. It makes more sense to search asynchronously
in this case. The next example also shows how to create a new client using a remote device reference of another client which might be advisable in cases
where a huge number of devices (and services) are expected to be found. A client which operates only on one remote device may be faster.

@code
Client client;
// Search asynchronously and give it some time (10 seconds)
client.search();
Sleep(10000);

// See what we've got so far
if (client.serviceFound())
{
  vector<Service*> services = client.getRemoteServices();
  // Find the right one
  Service* targetService = 0;
  for (int i = 0; i < services->size(); i++)
  {
    ...
  }

  // Do something with the client, e.g. invoke
  ...

  client.close();
}
else
{
  // Nothing found, maybe print out some error?
  ...

  client.close();
}
@endcode

@subsection client_invoke Invoking

As searching, there are two methods of invoking a remote operation, synchronous and asynchronous. Both are very similar, we start with the synchronous one and
continue our example of adding two numbers.

@code
// Define port type and input parameters (all strings)
QName portType("ExampleServicePort", "http://www.surgitaix.com/example");
Parameters inParams;
inParams.push_back(Parameter("InValue1", Parameter::INT, "1"));
inParams.push_back(Parameter("InValue2", Parameter::INT, "2"));
Parameters outParams;
// Invoke method (1 + 2)
bool invoked = invokeSync(portType, "GetSum", inParams, &outParams);
if (invoked)
{
  // Print out "3"
  cout << outParams[0].getValue() << endl;
}
@endcode

The asynchronous case:

@code
// Define port type and input parameters (all strings)
QName portType("ExampleServicePort", "http://www.surgitaix.com/example");
Parameters inParams;
inParams.push_back(Parameter("InValue1", Parameter::INT, "1"));
inParams.push_back(Parameter("InValue2", Parameter::INT, "2"));
// Invoke asynchronously, then poll for results
invoke(portType, "GetSum", inParams);
// Poll for results, use a timeout of 5 seconds.
timeout = 5000;
while ((timeout-=100) > 0 && !client.invokeReturned()) { Sleep(100); }
if (timeout > 0)
{
  // Get output parameters (all strings!)
  const Parameters& outParams = client.getInvokeResult();
  // Print out "3"
  cout << outParams[0].getValue() << endl;
}
@endcode

@section stopping Stopping devices, services and clients
Please make sure to shutdown devices and clients in any case:
@li Calling the <b>stop()</b> method of a device is essential before it is actually deleted. Since a device is not automatically stopped
on delete, a missing call to this function results in undefined behaviour of the library. Stopping a device implicates stopping any
of its hosted service.
@li A client must release its connection-related resources before being deleted. This can be done by calling the
<b>close()</b> method, as shown before.

@page advancedpage Advanced DPWS topics

@tableofcontents

@section customclients Custom clients

Waiting and polling might not be the most elegant way of handling asynchronous search and invoke results. Subclassing the client class and overriding
virtual functions can be done as shown next.

@code
class CustomClient : public Client
{
public:

  CustomClient()
  {
    addDeviceScopeSearchParam("http://www.surgitaix.com/example");
    setServiceIDSearchParam("ExampleServiceId");
    search();
  }

  // Called when search is complete (invokes a function)
  void searchComplete()
  {
    QName portType("ExampleServicePort", "http://www.surgitaix.com/example");
    Parameters params;
    params.push_back(Parameter("InValue1", Parameter::INT, "1"));
    params.push_back(Parameter("InValue2", Parameter::INT, "2"));
    invoke(portType, "GetSum", params);
  }

  // Called when invoke returned (prints the result of invoke)
  void invokeResponse()
  {
    const Parameters& out = getInvokeResult();
    cout << out[0].getValue() << endl;
  }

};
@endcode

@section structures Building structures

So far, only primitive data types have been introduced. They can be added to a parameter list to define input and
output parameters of a service operation (i.e. parameter name and type). A similar list must be used during method invocation on the client side,
with each parameter entry holding a concrete value (besides a name and a type). Building more complex structures is easily possible,
since each parameter entry itself can contain other parameters, thus becoming a container. Suppose the following structure should be mapped
to a service operation:

@code
typedef struct
{
  string lastName;
  string firstName;
  int age;
  float weight;
} Person
@endcode

Definition with OSCLib:

@code
// The container
Parameter person("Person");
//Equivalent: Parameter person("Person", Parameter::COMPLEX);
//Equivalent: Parameter person("Person", Parameter::ANY);
// Add types
person["lastName"].setType(Parameter::STRING);
person["firstName"].setType(Parameter::STRING);
person["age"].setType(Parameter::INT);
person["weight"].setType(Parameter::FLOAT);
// Add container to list
addInputParameter(person);
@endcode

The index operator of the <b>Parameter</b> class can be used to <b>create</b> or <b>access</b> elements of arbitrary depth using dots
as separators. For example, it allows to create a complex container inside another complex container. The next code example shows how to create a
parameter container which contains:
@li Two primitive data types
@li One complex type
@li Another complex type inside the first complex type

In pseudo code:

@code
typedef struct
{
  int id;
  long date;

  typedef struct
  {
    string lastName;
    string firstName;
    int age;
    float weight;

    typedef struct
    {
      string street;
      string city;
      int zip;
    } Address

  } Person

} File
@endcode

Definition with OSCLib:

@code
// File
Parameter file("File");
file["id"].setType(Parameter::INT);
file["date"].setType(Parameter::LONG);
// Person
file["Person.lastName"].setType(Parameter::STRING);
file["Person.firstName"].setType(Parameter::STRING);
file["Person.age"].setType(Parameter::INT);
file["Person.weight"].setType(Parameter::FLOAT);
// Address
file["Person.Address.street"].setType(Parameter::STRING);
file["Person.Address.city"].setType(Parameter::STRING);
file["Person.Address.zip"].setType(Parameter::INT);
// Add container as input parameter
addInputParameter(file);
@endcode

It's also possible to spare the \"file\" parameter and directly add the parameters \"id\" and \"date\" as separate input parameters.
The parameter list would then contain three elements, two primitive and one complex element (containing another complex element). At last, setting
a concrete value of a parameter (needed for invocation) can be done like this:

@code
Parameter file("File");
file["Person.Address.zip"].setType(Parameter::INT).setValue("12345");
@endcode

The \"setType\" part my be omitted when defining input values to call an operation, so the simpler statement suffices:

@code
Parameter file("File");
file["Person.Address.zip"].setValue("12345");
@endcode

@subsection structure_properties Structure properties

OSCLib allows the definition of complex type names (i.e. user defined types). In the generated WSDL, \"complexType\"-tags will be used, which are then referenced by \"element\"-tags. Other properties, like compositors, can be defined, too.

@li <b>Sequence:</b> Child parameter MUST all appear in the order they are declared.
@li <b>Choice:</b> Only one of the child parameter CAN appear.
@li <b>All:</b> The child parameters CAN appear in ANY order.

The default compositor type is <b>sequence</b>. In code this means:

@code
// Person
file["Person"].setCompositor(Parameter::COMPOSITOR_SEQUENCE);  // Default
...
@endcode

The next section defines how to define cardinalities, which plays an important role with respect to these properties.

@subsection structure_cardinalities Cardinalities

Since WSDL allows the definition of how many times an element can appear, OSCLib also supports setting the cardinality for
a certain parameter type in terms of a minimum and maximum number. To continue the example above, suppose a person can have
multiple addresses:

@code
// Address
file["Person.Address"].setMinOccurs(1).setMaxOccurs(10);
...
@endcode

An address may now occur from 1 to 10 times. The default count for the minimum and maximum number is 1. Setting the value to
\"unbounded\" can be done by passing a -1. <b>Creating</b> or <b>accessing</b> multiple elements is possible by using
parantheses inside the index path:

@code
// Main address (required)
file["Person.Address.street"].setType(Parameter::STRING);
file["Person.Address.city"].setType(Parameter::STRING);
file["Person.Address.zip"].setType(Parameter::INT);
// 1st alternate address
file["Person.Address(0).street"].setType(Parameter::STRING);
file["Person.Address(0).city"].setType(Parameter::STRING);
file["Person.Address(0).zip"].setType(Parameter::INT);
// 2nd alternate address
file["Person.Address(1).street"].setType(Parameter::STRING);
file["Person.Address(1).city"].setType(Parameter::STRING);
file["Person.Address(1).zip"].setType(Parameter::INT);
@endcode

To save some writing, consider using references like this:

@code
Parameter& altAdrs = file["Person.Address(1)"];
altAdrs["street"].setType(Parameter::STRING);
altAdrs["city"].setType(Parameter::STRING);
altAdrs["zip"].setType(Parameter::INT);
@endcode

@section complextypenames Complex type names
Until now, even in complex cases, a single simple parameter name have been used. That is possible, because OSCLib automatically generates a type name for a complex parameter, if needed.
For example, in case of the complex parameter <b>Person</b>, the complex type name is <b>PersonType</b>, in the WSDL type schema.
@code
<wsdl:definitions...
<wsdl:types>
<xs:schema xmlns:xs="http://www.w3.org/2001/XMLSchema">
  <xs:complexType name="PersonType">
    <xs:sequence>
      <xs:element name="lastName" type="xs:string"/>
      <xs:element name="firstName" type="xs:string"/>
      <xs:element name="age" type="xs:int"/>
      <xs:element name="weight" type="xs:float"/>
      <xs:element name="Address" type="AddressType"/>
    </xs:sequence>
  </xs:complexType>
  <xs:element name="Person" type="PersonType"/>
  ...
</xs:schema>
...
@endcode
However, the parameter's type name can also be set explicitly, using <b>Parameter.setCustomTypeName(const std::string & customType)</b>. Furthermore, the use of <b>Parameter.setCustomType(const QName & customType)</b> accepts a <b>qualified name</b> as input
instead of a string which makes it possible to provide a <b>namespace</b> for the type. Note that the parameter name itself can also be qualified (see next section).

@section qualifiednames Qualified names
As previously indicated, qualified names can be used to provide a namespace. Namespaces can be used in both <b>parameter names</b> and <b>parameter type names</b>. The parameter class provides a number of constructors for each case.
@code
Parameter(const std::string & name);
Parameter(const QName & name);
Parameter(const std::string & name, Type type);
Parameter(const QName & name, Type type);
Parameter(const std::string & name, Type type, const std::string & value);
Parameter(const QName & name, Type type, const std::string & value);
Parameter(const std::string & name, const QName & customType);
Parameter(const QName & name, const QName & customType);
@endcode

Consider the following definition using the last constructor, which defines two namespaces for the parameter's name and custom type:
@code
Parameter person(QName("Person", "http://mynamespace/1"), QName("MyPersonType", "http://mynamespace/2"));
@endcode

The generated WSDL would look like this:
@code
<wsdl:definitions...
<wsdl:types>
<xs:schema xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:i2="http://mynamespace/2">
  <xs:complexType name="MyPersonType">
    <xs:sequence>
    ...
    </xs:sequence>
  </xs:complexType>
  <xs:element name="Person" type="i2:MyPersonType"/>
  ...
</xs:schema>
<wsdl:message xmlns:i1="http://mynamespace/1">
  <wsdl:part name="parameters" element="i1:Person"/>
</wsdl:message>
...
@endcode

@section qualifiedinvoke Invoking with qualified names
Namespaces do not only play an important role in the generated WSDL on the service side. Please note, that qualified names in paramters must also be used in the process of
invoking operations using the client, once they are defined.

@section soapactions Custom SOAP actions

<i>Coming soon:</i> To ease handling of invoking operations, the library automatically generates SOAP actions by using information from port types and operation names.
However, a custom SOAP action may be defined in both the definition of an operation and the invoking process.

@section eventing DPWS Eventing

<i>Coming soon:</i> See code snippets below.

@subsection eventing_source Defining an event source

The following example shows the definition of an event source which can fire an event and receive a solicit response send back
from an event sink.

@code
class NotificationEventSource : public EventSource
{
public:

  NotificationEventSource()
  {
    // The event's name
    setName("SendNotification");

    // The port type
    QName pType("NotificationPort", "http://www.surgitaix.com/example");
    setPortType(pType);

    // The output parameter (notification)
    Parameter p1("NotificationValue", Parameter::STRING);
    addOutputParameter(p1);

    // The input parameter (solicit response)
    Parameter p2("ResponseValue", Parameter::STRING);
    addInputParameter(p2);
  }

  void responseReceived(Parameters& p)
  {
    // Get the value of the solicit response
    string response = p[0].getValue();
    // ...
  }

};
@endcode

A service must be defined to use the event source.

@code
Service* service = new Service();
// Create HTTP binding for service
Binding serviceBinding* = new Binding("192.168.1.1", 1235, "EventingService");
service->addBinding(DPWS11, serviceBinding);
service->setServiceId("EventingServiceId");

// Create and add the event source defined before
NotificationEventSource* source = new NotificationEventSource();
service->addEvent(source);
// ...
@endcode

@subsection eventing_sink Defining an event sink

The following example shows the definition of an event sink which can receive an event and then return parameters for a solicit response to
send back to the event source.

@code
class NotificationEventSink : public EventSink
{
public:

  NotificationEventSink()
  {
  }

  Parameters eventReceived(Parameters& p)
  {
    // Get the notification value of the event
    string value = p[0].getValue();
    // ...

    // Set parameter for the solicit response
    Parameters returnParams;
    returnParams.push_back(Parameter("ResponseValue", Parameter::STRING, "Response Test"));
    return returnParams;
  }

};
@endcode

@subsection eventing_client Setting up the client

The following example shows the definition of client that encapsulates the event sink and subscribes for events of the service
that contains the event source.

@code
class NotificationEventClient : public Client
{
public:

  NotificationEventClient(AbstractBinding* b = 0) : Client(b)
  {
    // Search the eventing service defined before
    setServiceIDSearchParam("EventingServiceId");
    sinkBinding = 0;
    search();
  }

  ~NotificationEventClient()
  {
    delete sinkBinding;
  }

  void searchComplete()
  {
    // Eventing service found, subscribe
    QName pType("NotificationPort", DEFAULT_NAMESPACE);
    sinkBinding = new Binding("192.168.1.1", 1236);
    // Subscribe (subscription expires after 60 seconds)
    subscribe(pType, "SendNotification", 60000, &sink, sinkBinding);
  }

  void subscribeResponse()
  {
    // Subscription response received, everything O.K.
    // ...
  }

private:
  NotificationEventSink sink;
  Binding* sinkBinding;

};
@endcode

@subsection eventing_fire Fire an event

An event source of a running eventing service can fire an event at any time. The event sink of a client subscribed to the eventing service can
receive the event and eventually send back a solicit response.

@code
Parameters params;
params.push_back(Parameter("NotificationValue").setValue("Event Test"));
// Send notification, get the number of sinks it has been send to
int count = source.fire(params);
@endcode

@section examples Useful code examples

Cool things you can do with OSCLib.

@subsection network_scan Continuously scanning the network

The following example of a class keeps scanning the network for DPWS 1.1 devices and services. It maintains a simple
map of devices (endpoint reference -> friendly name) and provides a method of retrieving a snapshop copy of that map. The class
makes also use of OSCLib's thread API (<b>DefaultRunnable</b> and <b>DefaultCritical</b>).

@code
class NetworkMonitor : public Client, public DefaultRunnable
{
public:

  NetworkMonitor(AbstractBinding* b = 0) : Client(b)
  {
  }

  // Scan network every 10 seconds in a separate thread
  void run()
  {
    while (!interrupted)
    {
      cout << "Searching network..." << endl;
      search();
      sleep(10000);
    }
  }

  // Get a copy of the simple device list
  map<string, LocalizedString> getDeviceList()
  {
    criticalSection.enter();
    map<string, LocalizedString> temp = deviceList;
    criticalSection.exit();
    return temp;
  }

  // Called if a device is found, store EPR and friendly name in a map
  void deviceVisited(Device* device)
  {
    string epr = device->getEndpointReference()->getAddress();
    LocalizedString friendlyName = *(device->getDeviceCharacteristics()->getFriendlyNames());
    criticalSection.enter();
    deviceList[epr] = friendlyName;
    criticalSection.exit();
    cout << "Device found: EPR = " << epr << ", friendly name = " << friendlyName.begin()->second << endl;
  }

  // Called if a service is found, just print out some parameters
  void serviceVisited(Service* service)
  {
    string eprDevice = service->getParentDevice()->getEndpointReference()->getAddress();
    string eprService = service->getEndpointReference()->getAddress();
    cout << "Service found: EPR = " << eprService << ", ID = " << service->getServiceId() << ", parent device's EPR = " << eprDevice << endl;
  }

private:

  DefaultCritical criticalSection;

  // The map contains the endpoint reference and friendly names of each device
  map<string, LocalizedString> deviceList;

};
@endcode

Start the network monitor client with the following code:

@code
NetworkMonitor monitor;
monitor.start();
...
// Interrupt monitor
monitor.interrupt();
@endcode

To retrieve the device list simply call <b>getDeviceList()</b>.

**/
