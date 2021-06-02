
#include "SDCLib/SDCInstance.h"
#include "SDCLib/Data/SDC/SDCConsumer.h"

#include "SDCLib/Data/SDC/SDCConsumerMDStateHandler.h"

#include "SDCLib/Data/SDC/SDCProvider.h"
#include "SDCLib/Data/SDC/SDCProviderAlertConditionStateHandler.h"
#include "SDCLib/Data/SDC/SDCProviderComponentStateHandler.h"
#include "SDCLib/Data/SDC/SDCProviderMDStateHandler.h"
#include "SDCLib/Data/SDC/MDIB/AlertConditionDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/AlertConditionState.h"
#include "SDCLib/Data/SDC/MDIB/AlertSystemDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/AlertSystemState.h"
#include "SDCLib/Data/SDC/MDIB/ChannelDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ChannelState.h"
#include "SDCLib/Data/SDC/MDIB/CodedValue.h"
#include "SDCLib/Data/SDC/MDIB/MdsDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/MdsState.h"
#include "SDCLib/Data/SDC/MDIB/MetricQuality.h"
#include "SDCLib/Data/SDC/MDIB/LocalizedText.h"
#include "SDCLib/Data/SDC/MDIB/LocationContextDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/LocationContextState.h"
#include "SDCLib/Data/SDC/MDIB/MdDescription.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricState.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricValue.h"
#include "SDCLib/Data/SDC/MDIB/SystemContextDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/MetaData.h"
#include "SDCLib/Data/SDC/MDIB/VmdDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/VmdState.h"
#include "SDCLib/Util/DebugOut.h"
#include "../AbstractSDCLibFixture.h"
#include "../UnitTest++/src/UnitTest++.h"

#include "OSELib/SDC/ServiceManager.h"

using namespace SDCLib;
using namespace SDCLib::Data::SDC;

namespace SDCLib {
	namespace Tests {
		namespace PeriodicEvents {


			const std::string DEVICE_ENDPOINT_REFERENCE{ "EPR_PERIODIC_EVENT_TEST" };
			const std::string DEVICE_UDI{ "UDI_PERIODIC_EVENT_TEST" };
			const int DEFAULT_TIMEOUT{ 5000 };

			const std::string ALERT_CONDITION_HANDLE{ "handle_alert_condition" };
			const std::string ALERT_SYSTEM_HANDLE{ "handle_alert_system" };
			const std::string CHANNEL_DESCRIPTOR_HANDLE{ "channel_handle" };
			const std::string LOCATION_CONTEXT_DESCRIPTOR_HANDLE{ "location_context" };
			const std::string LOCATION_CONTEXT_HANDLE{ "location_context_state_handle" };
			const std::string MDS_HANDLE{ "mds_handle" };
			const std::string METRIC_DUMMY_HANDLE{ "metric_dummy_handle" };
			const std::string VMD_DESCRIPTOR_HANDLE{ "vmd_handle" };

			///////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// Consumer event handlers
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////


			class ConsumerAlertConditionHandler : public SDCConsumerMDStateHandler<AlertConditionState>
			{
			public:
				ConsumerAlertConditionHandler(const std::string p_descriptorHandle)
					: SDCConsumerMDStateHandler(p_descriptorHandle)
				{ }

				void onStateChanged(const AlertConditionState&) override
				{
					++m_counter;
					if (m_counter < 5)
					{
						Util::DebugOut(Util::DebugOut::Default, "PeriodicEvents") << "Consumer: Received alert condition change of " << getDescriptorHandle() << std::endl;
					}
					else
					{
						m_event.set();
					}
				}

				Poco::Event& getEvent()
				{
					return m_event;
				}

			private:
				std::atomic<int> m_counter{ 0 };
				Poco::Event m_event;
			};


			// FIXME: right?????
			class ConsumerContextEventHandler : public SDCConsumerMDStateHandler<LocationContextState>
			{
			public:
				ConsumerContextEventHandler(const std::string p_descriptorHandle)
					: SDCConsumerMDStateHandler<LocationContextState>(p_descriptorHandle)
				{ }

				virtual void onStateChanged(const LocationContextState&) override
				{
					++m_counter;
					if (m_counter < 5)
					{
						Util::DebugOut(Util::DebugOut::Default, "PeriodicEvents") << "Consumer: Received locationContextDescriptor context values changed! Handle: " << getDescriptorHandle() << std::endl;
					}
					else
					{
						m_event.set();
					}
				}

				Poco::Event& getEvent()
				{
					return m_event;
				}

			private:
				std::atomic<int> m_counter{ 0 };
				Poco::Event m_event;
			};

			class ConsumerDummyHandler : public SDCConsumerMDStateHandler<NumericMetricState>
			{
			public:
				ConsumerDummyHandler(const std::string p_descriptorHandle)
					: SDCConsumerMDStateHandler(p_descriptorHandle)
				{ }

				void onStateChanged(const NumericMetricState&) override
				{
					++m_counter;
					if (m_counter < 5)
					{
						Util::DebugOut(Util::DebugOut::Default, "PeriodicEvents") << "Consumer: Received metric changed event of " << getDescriptorHandle() << std::endl;
					}
					else
					{
						m_event.set();
					}
				}

				Poco::Event& getEvent()
				{
					return m_event;
				}

			private:
				std::atomic<int> m_counter{ 0 };
				Poco::Event m_event;
			};

			///////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// Provider handlers
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////

			class AlertConditionStateHandler : public SDCProviderAlertConditionStateHandler<AlertConditionState>
			{
			public:
				AlertConditionStateHandler(const std::string p_descriptorHandle)
					: SDCProviderAlertConditionStateHandler<AlertConditionState>(p_descriptorHandle)
				{ }

				AlertConditionState getInitialState() override
				{
					return { ALERT_CONDITION_HANDLE, AlertActivation::On };
				}

				// not allowed to change the state
				InvocationState onStateChangeRequest(const AlertConditionState&, const OperationInvocationContext&) override
				{
					return InvocationState::Fail;
				}

				// ignore
				void sourceHasChanged(const std::string&) override
				{
					return;
				}

			};


			class AlertSystemStateHandler : public  SDCProviderMDStateHandler<AlertSystemState>
			{
			public:
				AlertSystemStateHandler(const std::string p_descriptorHandle)
					: SDCProviderMDStateHandler<AlertSystemState>(p_descriptorHandle)
				{ }

				AlertSystemState getInitialState() override
				{
					return { ALERT_SYSTEM_HANDLE, AlertActivation::On };
				}

				InvocationState onStateChangeRequest(const AlertSystemState&, const OperationInvocationContext&) override
				{
					return InvocationState::Fail;
				}

			};

			class LocationContextHandler : public SDCProviderMDStateHandler<LocationContextState>
			{
			public:
				LocationContextHandler(const std::string p_descriptorHandle)
					: SDCProviderMDStateHandler<LocationContextState>(p_descriptorHandle)
				{ }

				LocationContextState getInitialState() override
				{
					return { LOCATION_CONTEXT_DESCRIPTOR_HANDLE, LOCATION_CONTEXT_HANDLE };
				}

				// not allowed
				InvocationState onStateChangeRequest(const LocationContextState&, const OperationInvocationContext&) override
				{
					return InvocationState::Fail;
				}
			};

			class ProviderNumericStateHandler : public SDCProviderMDStateHandler<NumericMetricState>
			{
			public:
				ProviderNumericStateHandler(const std::string p_descriptorHandle)
					: SDCProviderMDStateHandler<NumericMetricState>(p_descriptorHandle)
				{ }

				// Helper method
				NumericMetricState createState()
				{
					NumericMetricState t_newState{ METRIC_DUMMY_HANDLE };
					t_newState
						.setMetricValue(NumericMetricValue{ MetricQuality{MeasurementValidity::Vld} }.setValue(0.0))
						.setActivationState(ComponentActivation::On);
					return t_newState;
				}

				NumericMetricState getInitialState() override
				{
					return createState();
				}

				// not allowed
				InvocationState onStateChangeRequest(const NumericMetricState&, const OperationInvocationContext&) override
				{
					return InvocationState::Fail;
				}
			};


			class AlwaysOnMdsStateHandler : public SDCProviderComponentStateHandler<MdsState>
			{
			public:
				AlwaysOnMdsStateHandler(const std::string p_descriptorHandle)
					: SDCProviderComponentStateHandler<MdsState>(p_descriptorHandle)
				{ }

				// Helper method
				MdsState createState()
				{
					MdsState t_newState{ getDescriptorHandle() };
					t_newState.setActivationState(ComponentActivation::On);
					return t_newState;
				}

				MdsState getInitialState() override
				{
					return createState();
				}
			};


			class AlwaysOnVmdStateHandler : public SDCProviderComponentStateHandler<VmdState>
			{
			public:
				AlwaysOnVmdStateHandler(const std::string p_descriptorHandle)
					: SDCProviderComponentStateHandler<VmdState>(p_descriptorHandle)
				{ }

				// Helper method
				VmdState createState()
				{
					VmdState t_newState{ getDescriptorHandle() };
					t_newState.setActivationState(ComponentActivation::On);
					return t_newState;
				}

				VmdState getInitialState() override
				{
					return createState();
				}
			};

			class AlwaysOnChannelStateHandler : public SDCProviderComponentStateHandler<ChannelState>
			{
			public:
				AlwaysOnChannelStateHandler(const std::string p_descriptorHandle)
					: SDCProviderComponentStateHandler<ChannelState>(p_descriptorHandle)
				{ }

				// Helper method
				ChannelState createState()
				{
					ChannelState t_newState{ getDescriptorHandle() };
					t_newState.setActivationState(ComponentActivation::On);
					return t_newState;
				}

				ChannelState getInitialState() override
				{
					return createState();
				}
			};

			///////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// Provider
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////

			class SDCDeviceProvider
			{
			public:
				// the mandatory fields of the states and descriptors MUST be initialized in the constructor initializer list,
				// the state handlers are recommended to be initialized in the constructor initializer list
				SDCDeviceProvider(SDCInstance_shared_ptr p_SDCInstance)
					: m_sdcProvider(p_SDCInstance)
				{
					m_sdcProvider.setEndpointReferenceByName(DEVICE_ENDPOINT_REFERENCE);

					// Alerts
					AlertSystemDescriptor alertSystem{ ALERT_SYSTEM_HANDLE };
					alertSystem
						.addAlertCondition(m_alertCondition);

					// Channel
					ChannelDescriptor deviceChannel{ CHANNEL_DESCRIPTOR_HANDLE };
					deviceChannel
						.addMetric(m_dummyMetricDescriptor)
						.setSafetyClassification(SafetyClassification::MedA);

					// VMD
					VmdDescriptor deviceModule{ VMD_DESCRIPTOR_HANDLE };
					deviceModule
						.addChannel(deviceChannel);

					// MDS
					MdsDescriptor deviceSystem{ MDS_HANDLE };
					deviceSystem
						.setMetaData(MetaData{}
							.addManufacturer(LocalizedText{ "SurgiTAIX AG" })
							.setModelNumber("1")
							.addModelName(LocalizedText{ "EndoTAIX" })
							.addSerialNumber("1234"))
						.setSystemContext(
							SystemContextDescriptor{ "systemcontext_handle" }
							.setLocationContext(m_locationContextDescriptor))
						.addVmd(deviceModule)
						.setAlertSystem(alertSystem);

					// create and add description
					MdDescription mdDescription;
					mdDescription.addMdsDescriptor(deviceSystem);

					m_sdcProvider.setMdDescription(mdDescription);

					// State handlers
					m_sdcProvider.addMdStateHandler(&m_alertSystemState);
					m_sdcProvider.addMdStateHandler(&m_alertConditionState);
					m_sdcProvider.addMdStateHandler(&m_channelState);
					m_sdcProvider.addMdStateHandler(&m_locationContextState);
					m_sdcProvider.addMdStateHandler(&m_dummyState);
					m_sdcProvider.addMdStateHandler(&m_mdsState);
					m_sdcProvider.addMdStateHandler(&m_vmdState);
				}

				void startup()
				{
					m_sdcProvider.startup();
				}

				void addHandleForPeriodicEvent(const std::string& p_handle)
				{
					m_sdcProvider.addHandleForPeriodicEvent(p_handle);
				}

				void setPeriodicEventInterval(std::chrono::milliseconds p_milliseconds)
				{
					m_sdcProvider.setPeriodicEventInterval(p_milliseconds);
				}

			private:
				// Provider
				SDCProvider m_sdcProvider;

				// alert descriptors
				AlertConditionDescriptor m_alertCondition{ ALERT_CONDITION_HANDLE, AlertConditionKind::Tec, AlertConditionPriority::Me };
				// metric descriptors
				NumericMetricDescriptor m_dummyMetricDescriptor{ METRIC_DUMMY_HANDLE, CodedValue(CodeIdentifier("codedvalue_dummy_handle")), MetricCategory::Msrmt, MetricAvailability::Cont, 1.0 };
				// context descriptors
				LocationContextDescriptor m_locationContextDescriptor{ LOCATION_CONTEXT_DESCRIPTOR_HANDLE };

				// State handler
				LocationContextHandler m_locationContextState{ LOCATION_CONTEXT_DESCRIPTOR_HANDLE };
				AlertConditionStateHandler m_alertConditionState{ ALERT_CONDITION_HANDLE };
				AlertSystemStateHandler m_alertSystemState{ ALERT_SYSTEM_HANDLE };

				AlwaysOnMdsStateHandler m_mdsState{ MDS_HANDLE };
				AlwaysOnVmdStateHandler m_vmdState{ VMD_DESCRIPTOR_HANDLE };
				AlwaysOnChannelStateHandler m_channelState{ CHANNEL_DESCRIPTOR_HANDLE };
				ProviderNumericStateHandler m_dummyState{ METRIC_DUMMY_HANDLE };
			};

		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Test
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct FixturePeriodicEvents : Tests::AbstractSDCLibFixture // FIXME: Why struct?
{
	FixturePeriodicEvents()
		: AbstractSDCLibFixture("FixturePeriodicEvents", OSELib::LogLevel::Error)
	{ }
};

SUITE(SDC) {
	TEST_FIXTURE(FixturePeriodicEvents, PeriodicEvents)
	{
		try
		{
			auto t_SDCInstance{ createSDCInstance() };

			// Provider
			Tests::PeriodicEvents::SDCDeviceProvider t_provider{ t_SDCInstance };
			t_provider.startup();

			// enable periodic event for metrics
			t_provider.addHandleForPeriodicEvent(Tests::PeriodicEvents::ALERT_CONDITION_HANDLE);
			t_provider.addHandleForPeriodicEvent(Tests::PeriodicEvents::LOCATION_CONTEXT_DESCRIPTOR_HANDLE);
			t_provider.addHandleForPeriodicEvent(Tests::PeriodicEvents::METRIC_DUMMY_HANDLE);
			// and set custom periodic event interval to 0.5s
			t_provider.setPeriodicEventInterval(std::chrono::milliseconds(500));

			// Consumer
			OSELib::SDC::ServiceManager t_serviceManager(t_SDCInstance);
			auto consumer(t_serviceManager.resolveEndpointReference(SDCInstance::calcUUIDv5(Tests::PeriodicEvents::DEVICE_ENDPOINT_REFERENCE, true)));

			// Make test fail if discovery fails
			CHECK_EQUAL(true, consumer != nullptr);

			if (consumer != nullptr)
			{
				// Register for metric events
				Tests::PeriodicEvents::ConsumerDummyHandler dummyMetricHandler(Tests::PeriodicEvents::METRIC_DUMMY_HANDLE);
				Tests::PeriodicEvents::ConsumerAlertConditionHandler alertConditionHandler(Tests::PeriodicEvents::ALERT_CONDITION_HANDLE);
				Tests::PeriodicEvents::ConsumerContextEventHandler locationContextStateHandler(Tests::PeriodicEvents::LOCATION_CONTEXT_DESCRIPTOR_HANDLE);

				CHECK_EQUAL(true, consumer->registerStateEventHandler(&alertConditionHandler));
				CHECK_EQUAL(true, consumer->registerStateEventHandler(&dummyMetricHandler));
				CHECK_EQUAL(true, consumer->registerStateEventHandler(&locationContextStateHandler));

				// Run for some time to receive incoming metric events.
				std::this_thread::sleep_for(std::chrono::milliseconds(2000));

				// verify results
				CHECK_EQUAL(true, dummyMetricHandler.getEvent().tryWait(Tests::PeriodicEvents::DEFAULT_TIMEOUT));
				CHECK_EQUAL(true, alertConditionHandler.getEvent().tryWait(Tests::PeriodicEvents::DEFAULT_TIMEOUT));
				CHECK_EQUAL(true, locationContextStateHandler.getEvent().tryWait(Tests::PeriodicEvents::DEFAULT_TIMEOUT));

				// shutdown consumer
				CHECK_EQUAL(true, consumer->unregisterStateEventHandler(&alertConditionHandler));
				CHECK_EQUAL(true, consumer->unregisterStateEventHandler(&dummyMetricHandler));
				CHECK_EQUAL(true, consumer->unregisterStateEventHandler(&locationContextStateHandler));
				consumer->disconnect();
			}
		}
		catch (char const* exc)
		{
			Util::DebugOut(Util::DebugOut::Default, std::cerr, m_details.testName) << exc;
		}
		catch (Poco::SystemException* e)
		{
			Util::DebugOut(Util::DebugOut::Default, std::cerr, m_details.testName) << e->message();
		}
		catch (...)
		{
			Util::DebugOut(Util::DebugOut::Default, std::cerr, m_details.testName) << "Unknown exception occurred!";
		}
	}
}
