
#include "OSCLib/SDCInstance.h"
#include "OSCLib/Data/SDC/SDCConsumer.h"

#include "OSCLib/Data/SDC/SDCConsumerMDStateHandler.h"

#include "OSCLib/Data/SDC/SDCProvider.h"
#include "OSCLib/Data/SDC/SDCProviderAlertConditionStateHandler.h"
#include "OSCLib/Data/SDC/SDCProviderComponentStateHandler.h"
#include "OSCLib/Data/SDC/SDCProviderMDStateHandler.h"
#include "OSCLib/Data/SDC/MDIB/AlertConditionDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/AlertConditionState.h"
#include "OSCLib/Data/SDC/MDIB/AlertSystemDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/AlertSystemState.h"
#include "OSCLib/Data/SDC/MDIB/ChannelDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/ChannelState.h"
#include "OSCLib/Data/SDC/MDIB/CodedValue.h"
#include "OSCLib/Data/SDC/MDIB/MdsDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/MdsState.h"
#include "OSCLib/Data/SDC/MDIB/MetricQuality.h"
#include "OSCLib/Data/SDC/MDIB/LocalizedText.h"
#include "OSCLib/Data/SDC/MDIB/LocationContextDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/LocationContextState.h"
#include "OSCLib/Data/SDC/MDIB/MdDescription.h"
#include "OSCLib/Data/SDC/MDIB/NumericMetricDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/NumericMetricState.h"
#include "OSCLib/Data/SDC/MDIB/NumericMetricValue.h"
#include "OSCLib/Data/SDC/MDIB/SystemContextDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/MetaData.h"
#include "OSCLib/Data/SDC/MDIB/VmdDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/VmdState.h"
#include "OSCLib/Util/DebugOut.h"
#include "../AbstractOSCLibFixture.h"
#include "../UnitTest++/src/UnitTest++.h"

#include "OSELib/SDC/ServiceManager.h"

using namespace SDCLib;
using namespace SDCLib::Data::SDC;

namespace SDCLib {
namespace Tests {
namespace PeriodicEvents {


const std::string DEVICE_ENDPOINT_REFERENCE("EPR_PERIODIC_EVENT_TEST");
const std::string DEVICE_UDI("UDI_PERIODIC_EVENT_TEST");
const int DEFAULT_TIMEOUT(5000);

const std::string ALERT_CONDITION_HANDLE("handle_alert_condition");
const std::string ALERT_SYSTEM_HANDLE("handle_alert_system");
const std::string CHANNEL_DESCRIPTOR_HANDLE("channel_handle");
const std::string LOCATION_CONTEXT_DESCRIPTOR_HANDLE("location_context");
const std::string LOCATION_CONTEXT_HANDLE("location_context_state_handle");
const std::string MDS_HANDLE("mds_handle");
const std::string METRIC_DUMMY_HANDLE("metric_dummy_handle");
const std::string VMD_DESCRIPTOR_HANDLE("vmd_handle");

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Consumer event handlers
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


class ConsumerAlertConditionHandler : public SDCConsumerMDStateHandler<AlertConditionState> {
public:
	ConsumerAlertConditionHandler(const std::string descriptorHandle) : SDCConsumerMDStateHandler(descriptorHandle),
		counter(0)
	{
	}

    void onStateChanged(const AlertConditionState & ) override {
    	++counter;
		if (counter < 5) {
			Util::DebugOut(Util::DebugOut::Default, "PeriodicEvents") << "Consumer: Received alert condition change of " << descriptorHandle << std::endl;
		} else {
			event.set();
		}
    }

	Poco::Event & getEvent() {
		return event;
	}

private:
    int counter;
    Poco::Event event;
};


// FIXME: right?????
class ConsumerContextEventHandler : public SDCConsumerMDStateHandler<LocationContextState> {
public:
	ConsumerContextEventHandler(const std::string descriptorHandle) : SDCConsumerMDStateHandler<LocationContextState>(descriptorHandle),
		counter(0) {
	}

	virtual void onStateChanged(const LocationContextState & state) override {
		++counter;
		if (counter < 5) {
			Util::DebugOut(Util::DebugOut::Default, "PeriodicEvents") << "Consumer: Received locationContextDescriptor context values changed! Handle: " << getDescriptorHandle() <<std::endl;
		} else {
			event.set();
		}
	}

	Poco::Event & getEvent() {
		return event;
	}

private:
	int counter;
	Poco::Event event;
};

class ConsumerDummyHandler : public SDCConsumerMDStateHandler<NumericMetricState> {
public:
	ConsumerDummyHandler(const std::string descriptorHandle) : SDCConsumerMDStateHandler(descriptorHandle),
		counter(0)
	{
	}

    void onStateChanged(const NumericMetricState & ) override {
        ++counter;
    	if (counter < 5) {
        	Util::DebugOut(Util::DebugOut::Default, "PeriodicEvents") << "Consumer: Received metric changed event of " << getDescriptorHandle() << std::endl;
        } else {
        	event.set();
        }
    }

	Poco::Event & getEvent() {
		return event;
	}

private:
    int counter;
    Poco::Event event;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Provider handlers
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AlertConditionStateHandler : public SDCProviderAlertConditionStateHandler<AlertConditionState> {
public:
	AlertConditionStateHandler(const std::string descriptorHandle) : SDCProviderAlertConditionStateHandler<AlertConditionState>(descriptorHandle) {
	}

    // Helper method
    AlertConditionState createState() {
        AlertConditionState result(ALERT_CONDITION_HANDLE, AlertActivation::On);
        return result;
    }

	AlertConditionState getInitialState() override {
    	AlertConditionState result = createState();
        return result;
    }

	// not allowed to change the state
	InvocationState onStateChangeRequest(const AlertConditionState & state, const OperationInvocationContext & oic) override {
		return InvocationState::Fail;
	}

	// ignore
	void sourceHasChanged(const std::string & sourceHandle) override {
		return;
	}

};


class AlertSystemStateHandler : public  SDCProviderMDStateHandler<AlertSystemState> {
public:
	AlertSystemStateHandler(const std::string descriptorHandle) : SDCProviderMDStateHandler<AlertSystemState>(descriptorHandle) {
    }

    // Helper method
    AlertSystemState createState() {
    	// reference alert system descriptor's handle
    	AlertSystemState result(ALERT_SYSTEM_HANDLE, AlertActivation::On);
        return result;
    }

	AlertSystemState getInitialState() override {
        AlertSystemState result = createState();
        return result;
    }

	InvocationState onStateChangeRequest(const AlertSystemState & state, const OperationInvocationContext & oic) override {
		return InvocationState::Fail;
	}

};

class LocationContextHandler : public SDCProviderMDStateHandler<LocationContextState> {
public:
	LocationContextHandler(const std::string descriptorHandle) : SDCProviderMDStateHandler<LocationContextState>(descriptorHandle) {
	}

    // Helper method
    LocationContextState createState() {
        LocationContextState result(LOCATION_CONTEXT_DESCRIPTOR_HANDLE, LOCATION_CONTEXT_HANDLE);
        return result;
    }

    LocationContextState getInitialState() override	{
    	return createState();
    }

    // not allowed
    InvocationState onStateChangeRequest(const LocationContextState & state, const OperationInvocationContext & oic) {
    	return InvocationState::Fail;
    }
};

class ProviderNumericStateHandler : public SDCProviderMDStateHandler<NumericMetricState> {
public:
    ProviderNumericStateHandler(const std::string descriptorHandle) : SDCProviderMDStateHandler<NumericMetricState>(descriptorHandle) {
    }

    // Helper method
    NumericMetricState createState() {
        NumericMetricState result(METRIC_DUMMY_HANDLE);
        result
            .setMetricValue(NumericMetricValue(MetricQuality(MeasurementValidity::Vld)).setValue(0.0))
            .setActivationState(ComponentActivation::On);
        return result;
    }

    NumericMetricState getInitialState() override {
        NumericMetricState result = createState();
        return result;
    }

    // not allowed
    InvocationState onStateChangeRequest(const NumericMetricState & state, const OperationInvocationContext & oic) {
    	return InvocationState::Fail;
    }
};


class AlwaysOnMdsStateHandler : public SDCProviderComponentStateHandler<MdsState> {
public:
	AlwaysOnMdsStateHandler(const std::string & descriptorHandle) : SDCProviderComponentStateHandler<MdsState>(descriptorHandle) {
	}

    // Helper method
    MdsState createState() {
        MdsState result(descriptorHandle);
        result
            .setActivationState(ComponentActivation::On);
        return result;
    }

	virtual MdsState getInitialState() override {
        MdsState state = createState();
        return state;
	}
};


class AlwaysOnVmdStateHandler : public SDCProviderComponentStateHandler<VmdState> {
public:
	AlwaysOnVmdStateHandler(const std::string & descriptorHandle) : SDCProviderComponentStateHandler<VmdState>(descriptorHandle) {
	}

    // Helper method
    VmdState createState() {
        VmdState result(descriptorHandle);
        result
            .setActivationState(ComponentActivation::On);
        return result;
    }

	virtual VmdState getInitialState() override {
		VmdState state = createState();
        return state;
	}
};

class AlwaysOnChannelStateHandler : public SDCProviderComponentStateHandler<ChannelState>  {
public:
	AlwaysOnChannelStateHandler(const std::string & descriptorHandle) : SDCProviderComponentStateHandler<ChannelState>(descriptorHandle)  {
	}

    // Helper method
    ChannelState createState() {
    	ChannelState result(descriptorHandle);
        result
            .setActivationState(ComponentActivation::On);
        return result;
    }

	virtual ChannelState getInitialState() override {
		ChannelState state = createState();
        return state;
	}
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Provider
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

class OSCPDeviceProvider {
public:
	// the mandatory fields of the states and descriptors MUST be initialized in the constructor initializer list,
	// the state handlers are recommended to be initialized in the constructor initializer list
	OSCPDeviceProvider(SDCInstance_shared_ptr p_SDCInstance) :
		sdcProvider(p_SDCInstance),

		alertCondition(ALERT_CONDITION_HANDLE, AlertConditionKind::Tec, AlertConditionPriority::Me),
		dummyMetricDescriptor(METRIC_DUMMY_HANDLE, CodedValue(CodeIdentifier("codedvalue_dummy_handle")), MetricCategory::Msrmt, MetricAvailability::Cont, 1.0),
		locationContextDescriptor(LOCATION_CONTEXT_DESCRIPTOR_HANDLE),

		locationContextState(LOCATION_CONTEXT_DESCRIPTOR_HANDLE),
		alertConditionState(ALERT_CONDITION_HANDLE),
		alertSystemState(ALERT_SYSTEM_HANDLE),

		channelState(CHANNEL_DESCRIPTOR_HANDLE),
		dummyState(METRIC_DUMMY_HANDLE),
		mdsState(MDS_HANDLE),
		vmdState(VMD_DESCRIPTOR_HANDLE)
	{
		sdcProvider.setEndpointReference(DEVICE_ENDPOINT_REFERENCE);

    	// Alerts
        AlertSystemDescriptor alertSystem(ALERT_SYSTEM_HANDLE);
        alertSystem
			.addAlertCondition(alertCondition);

    	// Channel
        ChannelDescriptor deviceChannel(CHANNEL_DESCRIPTOR_HANDLE);
        deviceChannel
			.addMetric(dummyMetricDescriptor)
			.setSafetyClassification(SafetyClassification::MedA);

        // VMD
        VmdDescriptor deviceModule(VMD_DESCRIPTOR_HANDLE);
        deviceModule
			.addChannel(deviceChannel);

        // MDS
        MdsDescriptor deviceSystem(MDS_HANDLE);
        deviceSystem
			.setMetaData(MetaData()
				.addManufacturer(LocalizedText().setRef("SurgiTAIX AG"))
				.setModelNumber("1")
				.addModelName(LocalizedText().setRef("EndoTAIX"))
				.addSerialNumber("1234"))
			.setSystemContext(
				SystemContextDescriptor("systemcontext_handle")
					.setLocationContext(locationContextDescriptor))
			.addVmd(deviceModule)
			.setAlertSystem(alertSystem);

        // create and add description
		MdDescription mdDescription;
		mdDescription.addMdsDescriptor(deviceSystem);

		sdcProvider.setMdDescription(mdDescription);

        // State handlers
        sdcProvider.addMdStateHandler(&alertSystemState);
        sdcProvider.addMdStateHandler(&alertConditionState);
        sdcProvider.addMdStateHandler(&channelState);
        sdcProvider.addMdStateHandler(&locationContextState);
        sdcProvider.addMdStateHandler(&dummyState);
        sdcProvider.addMdStateHandler(&mdsState);
        sdcProvider.addMdStateHandler(&vmdState);
	}

	void startup() {
		sdcProvider.startup();
	}

	void shutdown() {
		sdcProvider.shutdown();
	}

	void addHandleForPeriodicEvent(const std::string & handle) {
		sdcProvider.addHandleForPeriodicEvent(handle);
	}

	void setPeriodicEventInterval(const int seconds, const int milliseconds) {
		sdcProvider.setPeriodicEventInterval(seconds, milliseconds);
	}

private:
	// Provider
	SDCProvider sdcProvider;

    // alert descriptors
	AlertConditionDescriptor alertCondition;
    // metric descriptors
    NumericMetricDescriptor dummyMetricDescriptor;
    // context descriptors
    LocationContextDescriptor locationContextDescriptor;

    // State handler
    LocationContextHandler locationContextState;
    AlertConditionStateHandler alertConditionState;
    AlertSystemStateHandler alertSystemState;

    AlwaysOnChannelStateHandler channelState;
    ProviderNumericStateHandler dummyState;
    AlwaysOnMdsStateHandler mdsState;
    AlwaysOnVmdStateHandler vmdState;
};

}
}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Test
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct FixturePeriodicEvents : Tests::AbstractOSCLibFixture {
	FixturePeriodicEvents() : AbstractOSCLibFixture("FixturePeriodicEvents", OSELib::LogLevel::Error, SDCLib::Config::SDC_ALLOWED_PORT_START + 80) {}
};

SUITE(OSCP) {
TEST_FIXTURE(FixturePeriodicEvents, periodicevents)
{
	try
	{
        auto t_SDCInstance = getSDCInstance();

        // Provider
        Tests::PeriodicEvents::OSCPDeviceProvider provider(t_SDCInstance);
        provider.startup();

        // enable periodic event for metrices
        provider.addHandleForPeriodicEvent(Tests::PeriodicEvents::ALERT_CONDITION_HANDLE);
        provider.addHandleForPeriodicEvent(Tests::PeriodicEvents::LOCATION_CONTEXT_DESCRIPTOR_HANDLE);
        provider.addHandleForPeriodicEvent(Tests::PeriodicEvents::METRIC_DUMMY_HANDLE);
        // and set custom periodic event interval to 0.5s
        provider.setPeriodicEventInterval(0, 500);

        // Consumer
        OSELib::SDC::ServiceManager oscpsm(t_SDCInstance);
        std::shared_ptr<SDCConsumer> consumer(oscpsm.discoverEndpointReference(Tests::PeriodicEvents::DEVICE_ENDPOINT_REFERENCE));

        // Make test fail if discovery fails
        CHECK_EQUAL(true, consumer != nullptr);

		if (consumer != nullptr) {
            // Register for metric events
	        Tests::PeriodicEvents::ConsumerDummyHandler dummyMetricHandler(Tests::PeriodicEvents::METRIC_DUMMY_HANDLE);
	        Tests::PeriodicEvents::ConsumerAlertConditionHandler alertConditionHandler(Tests::PeriodicEvents::ALERT_CONDITION_HANDLE);
	        Tests::PeriodicEvents::ConsumerContextEventHandler locationContextStateHandler(Tests::PeriodicEvents::LOCATION_CONTEXT_DESCRIPTOR_HANDLE);

            CHECK_EQUAL(true, consumer->registerStateEventHandler(&alertConditionHandler));
            CHECK_EQUAL(true, consumer->registerStateEventHandler(&dummyMetricHandler));
            CHECK_EQUAL(true, consumer->registerStateEventHandler(&locationContextStateHandler));

            // Run for some time to receive incoming metric events.
			Poco::Thread::sleep(2000);


			// TODO: fails
			// verify results
			CHECK_EQUAL(true, dummyMetricHandler.getEvent().tryWait(Tests::PeriodicEvents::DEFAULT_TIMEOUT));
			CHECK_EQUAL(true, alertConditionHandler.getEvent().tryWait(Tests::PeriodicEvents::DEFAULT_TIMEOUT));
            CHECK_EQUAL(true, locationContextStateHandler.getEvent().tryWait(Tests::PeriodicEvents::DEFAULT_TIMEOUT));


            // shutdown consumer
            CHECK_EQUAL(true, consumer->unregisterStateEventHandler(&alertConditionHandler));
            CHECK_EQUAL(true, consumer->unregisterStateEventHandler(&dummyMetricHandler));
            CHECK_EQUAL(true, consumer->unregisterStateEventHandler(&locationContextStateHandler));
            consumer->setContextStateChangedHandler(nullptr);
            consumer->disconnect();
		}

        provider.shutdown();
    } catch (char const* exc) {
        Util::DebugOut(Util::DebugOut::Default, std::cerr, m_details.testName) << exc;
    }catch (Poco::SystemException *e){
        Util::DebugOut(Util::DebugOut::Default, std::cerr, m_details.testName) << e->message();
	} catch (...) {
        Util::DebugOut(Util::DebugOut::Default, std::cerr, m_details.testName) << "Unknown exception occurred!";
	}
}
}
