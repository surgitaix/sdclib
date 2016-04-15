
#include "OSCLib/OSCLibrary.h"
#include "OSCLib/Data/OSCP/OSCPConsumer.h"
#include "OSCLib/Data/OSCP/OSCPConsumerAlertConditionStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPConsumerContextStateChangedHandler.h"
#include "OSCLib/Data/OSCP/OSCPConsumerNumericMetricStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPProvider.h"
#include "OSCLib/Data/OSCP/OSCPProviderAlertConditionStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPProviderAlertSystemStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPProviderComponentStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPProviderContextStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPProviderHydraMDSStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPProviderNumericMetricStateHandler.h"
#include "OSCLib/Data/OSCP/MDIB/AlertConditionDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AlertConditionState.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSystemDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/AlertSystemState.h"
#include "OSCLib/Data/OSCP/MDIB/ChannelDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/ComponentState.h"
#include "OSCLib/Data/OSCP/MDIB/HydraMDSDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/HydraMDSState.h"
#include "OSCLib/Data/OSCP/MDIB/LocalizedText.h"
#include "OSCLib/Data/OSCP/MDIB/LocationContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/LocationContextState.h"
#include "OSCLib/Data/OSCP/MDIB/MDDescription.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricValue.h"
#include "OSCLib/Data/OSCP/MDIB/OperationInvocationContext.h"
#include "OSCLib/Data/OSCP/MDIB/SystemContext.h"
#include "OSCLib/Data/OSCP/MDIB/SystemMetaData.h"
#include "OSCLib/Data/OSCP/MDIB/VMDDescriptor.h"
#include "OSCLib/Util/DebugOut.h"
#include "../AbstractOSCLibFixture.h"
#include "../UnitTest++/src/UnitTest++.h"

#include "OSELib/OSCP/ServiceManager.h"

#include "Poco/Event.h"
#include "Poco/Mutex.h"
#include "Poco/ScopedLock.h"

using namespace OSCLib;
using namespace OSCLib::Data::OSCP;

namespace OSCLib {
namespace Tests {
namespace PeriodicEvents {

const std::string TESTNAME("PeriodicEvents");

const std::string DEVICE_ENDPOINT_REFERENCE("EPR_PERIODIC_EVENT_TEST");
const std::string DEVICE_UDI("UDI_PERIODIC_EVENT_TEST");
const int DEFAULT_TIMEOUT(5000);

const std::string ALERT_CONDITION_HANDLE("handle_alert_condition");
const std::string ALERT_SYSTEM_HANDLE("handle_alert_system");
const std::string CHANNEL_DESCRIPTOR_HANDLE("channel_handle");
const std::string LOCATION_CONTEXT_DESCRIPTOR_HANDLE("location_context");
const std::string MDS_HANDLE("mds_handle");
const std::string METRIC_DUMMY_HANDLE("metric_dummy_handle");
const std::string VMD_DESCRIPTOR_HANDLE("vmd_handle");

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Consumer event handlers
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ConsumerAlertConditionHandler : public OSCPConsumerAlertConditionStateHandler {
public:
	ConsumerAlertConditionHandler() :
		handle(ALERT_CONDITION_HANDLE),
		counter(0)
	{
	}

    void onStateChanged(const AlertConditionState & ) override {
    	++counter;
		if (counter < 5) {
			Util::DebugOut(Util::DebugOut::Default, "SimpleOSCP") << "Consumer: Received alert condition change of " << handle << std::endl;
		} else {
			event.set();
		}
    }

    std::string getHandle() override {
        return handle;
    }

	Poco::Event & getEvent() {
		return event;
	}

private:
    const std::string handle;
    int counter;
    Poco::Event event;
};

class ConsumerContextEventHandler : public OSCPConsumerContextStateChangedHandler {
public:
	ConsumerContextEventHandler() :
		handle(LOCATION_CONTEXT_DESCRIPTOR_HANDLE),
		counter(0) {
	}

	virtual void onContextStateChanged(const std::vector<std::string> & handles) override {
        if (!handles.empty() && handles.front() == handle) {
        	++counter;
    		if (counter < 5) {
    	        Util::DebugOut(Util::DebugOut::Default, "SimpleOSCP") << "Consumer: Received context values changed!" << std::endl;
    		} else {
    			event.set();
    		}
        }
	}

	Poco::Event & getEvent() {
		return event;
	}

private:
	const std::string handle;
	int counter;
	Poco::Event event;

};

class ConsumerDummyHandler : public OSCPConsumerNumericMetricStateHandler {
public:
	ConsumerDummyHandler() :
		handle(METRIC_DUMMY_HANDLE),
		counter(0)
	{
	}

    void onStateChanged(const NumericMetricState & ) override {
        ++counter;
    	if (counter < 5) {
        	Util::DebugOut(Util::DebugOut::Default, "SimpleOSCP") << "Consumer: Received metric changed event of " << handle << std::endl;
        } else {
        	event.set();
        }
    }

    std::string getHandle() override {
        return handle;
    }

	Poco::Event & getEvent() {
		return event;
	}

private:
    const std::string handle;
    int counter;
    Poco::Event event;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Provider handlers
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AlertConditionStateHandler : public OSCPProviderAlertConditionStateHandler {
public:
	AlertConditionStateHandler() {
	}

    // Helper method
    AlertConditionState createState() {
        AlertConditionState result;
        result.setDescriptorHandle(ALERT_CONDITION_HANDLE);
        return result;
    }

	AlertConditionState getInitialClonedState() override {
    	AlertConditionState result = createState();
        return result;
    }

};

class AlertSystemStateHandler : public OSCPProviderAlertSystemStateHandler {
public:
	AlertSystemStateHandler() {
    }

    // Helper method
    AlertSystemState createState() {
        AlertSystemState result;
        // reference alert system descriptor's handle
        result
            .setActivationState(PausableActivation::ON)
            .setDescriptorHandle(ALERT_SYSTEM_HANDLE);
        return result;
    }

	AlertSystemState getInitialClonedState() override {
        AlertSystemState result = createState();
        return result;
    }

};

class ContextHandler : public OSCPProviderContextStateHandler {
public:
	ContextHandler() {
	}

    // Helper method
    LocationContextState createState() {
        LocationContextState result;
        result.setDescriptorHandle(LOCATION_CONTEXT_DESCRIPTOR_HANDLE);
        return result;
    }

	virtual std::vector<LocationContextState> getLocationContextStates() override {
		std::vector<LocationContextState> result;
        result.push_back(createState());
		return result;
	}

};

class ProviderNumericStateHandler : public OSCPProviderNumericMetricStateHandler {
public:
    ProviderNumericStateHandler() {
    }

    // Helper method
    NumericMetricState createState() {
        NumericMetricState result;
        result
            .setObservedValue(NumericMetricValue().setValue(0.0))
            .setComponentActivationState(ComponentActivation::ON)
            .setDescriptorHandle(METRIC_DUMMY_HANDLE);
        return result;
    }

    NumericMetricState getInitialClonedState() override {
        NumericMetricState result = createState();
        return result;
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

	virtual ComponentState getInitialClonedState() override {
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

	virtual HydraMDSState getInitialClonedState() override {
        HydraMDSState state = createState();
        return state;
	}

private:
    std::string descriptorHandle;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Provider
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

class OSCPDeviceProvider : public OSCPProvider {
public:
	OSCPDeviceProvider() :
		channelState(CHANNEL_DESCRIPTOR_HANDLE),
		hydraMDSState(MDS_HANDLE),
		vmdState(VMD_DESCRIPTOR_HANDLE)
	{
    	setEndpointReference(DEVICE_ENDPOINT_REFERENCE);

        alertCondition
			.addSource(METRIC_DUMMY_HANDLE)
			.setKind(AlertConditionKind::TECHNICAL)
			.setPriority(AlertConditionPriority::MEDIUM)
			.setHandle(ALERT_CONDITION_HANDLE);

        dummyMetricDescriptor
			.setMetricCategory(MetricCategory::MEASUREMENT)
        	.setAvailability(MetricAvailability::CONTINUOUS)
	        .setHandle(METRIC_DUMMY_HANDLE);

        location.setHandle(LOCATION_CONTEXT_DESCRIPTOR_HANDLE);

        // State handlers
		addMDStateHandler(&alertSystemState);
		addMDStateHandler(&alertConditionState);
        addMDStateHandler(&channelState);
        addMDStateHandler(&contextStates);
		addMDStateHandler(&dummyState);
        addMDStateHandler(&hydraMDSState);
        addMDStateHandler(&vmdState);
    }

    MDDescription getMDDescription() override {

    	// Alerts
        AlertSystemDescriptor alertSystem;
        alertSystem
			.addAlertCondition(alertCondition)
			.setHandle(ALERT_SYSTEM_HANDLE);

    	// Channel
        ChannelDescriptor deviceChannel;
        deviceChannel
			.setHandle(CHANNEL_DESCRIPTOR_HANDLE)
			.addMetric(dummyMetricDescriptor)
			.setIntendedUse(IntendedUse::MEDICAL_A);

        // VMD
        VMDDescriptor deviceModule;
        deviceModule
			.setHandle(VMD_DESCRIPTOR_HANDLE)
			.addChannel(deviceChannel);

        // MDS
        HydraMDSDescriptor deviceSystem;
        deviceSystem
			.setHandle(MDS_HANDLE)
			.setMetaData(
				SystemMetaData()
				.setUDI(DEVICE_UDI)
				.addManufacturer(
					LocalizedText()
					.set("SurgiTAIX AG"))
				.addModelName(
					LocalizedText()
					.set("EndoTAIX"))
				.addModelNumber("1")
				.addSerialNumber("1234")
				)
			.setContext(
				SystemContext()
				.setLocationContext(location)
				)
			.addVMD(deviceModule)
			.setAlertSystem(alertSystem);

        MDDescription mdd;
        mdd.addHydraMDSDescriptor(deviceSystem);

        return mdd;
    }

private:
    // alert descriptors
	AlertConditionDescriptor alertCondition;
    // metric descriptors
    NumericMetricDescriptor dummyMetricDescriptor;
    // context descriptors
    LocationContextDescriptor location;

    // State (handlers)
    ContextHandler contextStates;
    AlertConditionStateHandler alertConditionState;
    AlertSystemStateHandler alertSystemState;
    AlwaysOnComponentStateHandler channelState;
    ProviderNumericStateHandler dummyState;
    AlwaysOnHydraMDSStateHandler hydraMDSState;
    AlwaysOnComponentStateHandler vmdState;
};

}
}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Test
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct FixturePeriodicEvents : Tests::AbstractOSCLibFixture {
	FixturePeriodicEvents() : AbstractOSCLibFixture("FixturePeriodicEvents", OSELib::LogLevel::NOTICE, 9100) {}
};

SUITE(OSCP) {
TEST_FIXTURE(FixturePeriodicEvents, periodicevents)
{
	try
	{
        // Provider
        Tests::PeriodicEvents::OSCPDeviceProvider provider;
        provider.startup();    

        // enable periodic event for metric
        provider.addHandleForPeriodicEvent(Tests::PeriodicEvents::ALERT_CONDITION_HANDLE);
        provider.addHandleForPeriodicEvent(Tests::PeriodicEvents::LOCATION_CONTEXT_DESCRIPTOR_HANDLE);
        provider.addHandleForPeriodicEvent(Tests::PeriodicEvents::METRIC_DUMMY_HANDLE);
        // and set custom periodic event interval to 0.5s
        provider.setPeriodicEventInterval(0, 500);

        // Consumer
        OSELib::OSCP::ServiceManager oscpsm;
        std::shared_ptr<OSCPConsumer> consumer(oscpsm.discoverEndpointReference(Tests::PeriodicEvents::DEVICE_ENDPOINT_REFERENCE));

        // Make test fail if discovery fails
        CHECK_EQUAL(true, consumer != nullptr);

		if (consumer != nullptr) {
            // Register for metric events
	        Tests::PeriodicEvents::ConsumerDummyHandler dummyMetricHandler;
	        Tests::PeriodicEvents::ConsumerAlertConditionHandler alertConditionHandler;
            CHECK_EQUAL(true, consumer->registerStateEventHandler(&alertConditionHandler));
            CHECK_EQUAL(true, consumer->registerStateEventHandler(&dummyMetricHandler));
            Tests::PeriodicEvents::ConsumerContextEventHandler contextStateHandler;
            consumer->setContextStateChangedHandler(&contextStateHandler);

            // Run for some time to receive incoming metric events.
			Poco::Thread::sleep(4000);

			// verify results
            CHECK_EQUAL(true, alertConditionHandler.getEvent().tryWait(Tests::PeriodicEvents::DEFAULT_TIMEOUT));
            CHECK_EQUAL(true, contextStateHandler.getEvent().tryWait(Tests::PeriodicEvents::DEFAULT_TIMEOUT));
            CHECK_EQUAL(true, dummyMetricHandler.getEvent().tryWait(Tests::PeriodicEvents::DEFAULT_TIMEOUT));

            // shutdown consumer
            CHECK_EQUAL(true, consumer->unregisterStateEventHandler(&alertConditionHandler));
            CHECK_EQUAL(true, consumer->unregisterStateEventHandler(&dummyMetricHandler));
            consumer->setContextStateChangedHandler(nullptr);
            consumer->disconnect();
		}

        provider.shutdown();
    } catch (char const* exc) {
    	Util::DebugOut(Util::DebugOut::Default, std::cerr, Tests::PeriodicEvents::TESTNAME) << exc;
	} catch (...) {
		Util::DebugOut(Util::DebugOut::Default, std::cerr, Tests::PeriodicEvents::TESTNAME) << "Unknown exception occurred!";
	}
}
}
