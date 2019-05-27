
#include "SDCLib/SDCLibrary.h"
#include "SDCLib/Data/SDC/FutureInvocationState.h"
#include "SDCLib/Data/SDC/MDIB/custom/MdibContainer.h"
#include "SDCLib/Data/SDC/MDIB/MdsDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/AlertConditionDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/AlertConditionState.h"
#include "SDCLib/Data/SDC/MDIB/AlertSignalDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/AlertSignalState.h"
#include "SDCLib/Data/SDC/MDIB/AlertSystemDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/AlertSystemState.h"
#include "SDCLib/Data/SDC/MDIB/EnumStringMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/EnumStringMetricState.h"
#include "SDCLib/Data/SDC/MDIB/MdsDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/MdsState.h"
#include "SDCLib/Data/SDC/MDIB/MdDescription.h"
#include "SDCLib/Data/SDC/MDIB/MetricQuality.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricState.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricValue.h"
#include "SDCLib/Data/SDC/MDIB/StringMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/StringMetricState.h"
#include "SDCLib/Data/SDC/MDIB/StringMetricValue.h"
#include "SDCLib/Data/SDC/MDIB/RealTimeSampleArrayMetricState.h"
#include "OSELib/SDC/SDCConstants.h"
#include "SDCLib/Data/SDC/SDCConsumer.h"
#include "SDCLib/Data/SDC/SDCConsumerNumericMetricStateHandler.h"
#include "SDCLib/Data/SDC/SDCConsumerStringMetricStateHandler.h"
#include "SDCLib/Data/SDC/SDCProvider.h"
#include "SDCLib/Util/DebugOut.h"

#include "OSELib/SDC/ServiceManager.h"

#include "Poco/Thread.h"
#include "Poco/Timestamp.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeFormat.h"

using namespace SDCLib;
using namespace SDCLib::Util;
using namespace SDCLib::Data::SDC;

const std::string deviceEPR("urn:uuid:4242d68b-40ef-486a-a019-6b00d1424201");

class NumericEventHandler : public Data::SDC::SDCConsumerNumericMetricStateHandler {
public:
	NumericEventHandler(const std::string & handle) : handle(handle) {
		receivedEventsCounter = 0;
    }

    virtual ~NumericEventHandler() {
    }

    void onStateChanged(const Data::SDC::NumericMetricState & ) override {
        receivedEventsCounter++;
    }

    std::string getHandle() override {
        return handle;
    }

public:
    std::atomic_ulong receivedEventsCounter;
private:
    const std::string handle;
};

class StringEventHandler : public Data::SDC::SDCConsumerStringMetricStateHandler {
public:
	StringEventHandler(const std::string & handle) : handle(handle) {
		receivedEventsCounter = 0;
    }

    virtual ~StringEventHandler() {
    }

    void onStateChanged(const Data::SDC::StringMetricState & ) override {
        receivedEventsCounter++;
    }

    std::string getHandle() override {
        return handle;
    }

public:
    std::atomic_ulong receivedEventsCounter;
private:
    const std::string handle;
};

int main() {
	DebugOut(DebugOut::Default, "ClientForUniRostockDevices") << std::endl << "Startup" << std::endl;
    SDCLibrary::getInstance().startup();
	SDCLibrary::getInstance().setPortStart(11111);

	// Discovery
	OSELib::SDC::ServiceManager t_serviceManager;
	std::unique_ptr<Data::SDC::SDCConsumer> c(t_serviceManager.discoverEndpointReference(deviceEPR));

	if (c != nullptr) {
		Data::SDC::SDCConsumer & consumer = *c;
        Util::DebugOut(Util::DebugOut::Default, "ClientForUniRostockDevices") << "Discovery succeeded.";

        // used handles
    	const std::string handle_m1_get_and_episodic("handle_m1");
    	const std::string handle_m2_get_and_periodic("handle_m2");
    	const std::string handle_sm1_get_and_episodic_and_periodic("handle_sm1");
    	const std::string handle_channel1_vmd0("c1vmd0");
    	const std::string handle_setString_operation("handle_op_sm1");

    	// "magic" test values
    	const double numeric_initial_value(0.0);
    	const double numeric_some_value(1234.5);
    	const std::string string_initial_value("initial_string");
    	const std::string string_some_value("some value");

    	// handler definitions
		NumericEventHandler episodicHandler(handle_m1_get_and_episodic);
		NumericEventHandler periodicHandler(handle_m2_get_and_periodic);
		StringEventHandler combinedHandler(handle_sm1_get_and_episodic_and_periodic);
		consumer.registerStateEventHandler(&episodicHandler);
		consumer.registerStateEventHandler(&periodicHandler);
		consumer.registerStateEventHandler(&combinedHandler);

		{
			std::ostringstream additionalResults;
			{
        		// TODO MDIBVersion in GetMDIBResponse/MDIB node is missing so the messages fails validation.
//				Util::DebugOut(Util::DebugOut::Default, "ClientForUniRostockDevices") << "Testing getMDIB:";
//				const auto mdib = consumer.getMdib();
//				Util::DebugOut(Util::DebugOut::Default, "ClientForUniRostockDevices") << "Done.";
			}
			Util::DebugOut(Util::DebugOut::Default, "ClientForUniRostockDevices") << " ";
			{
				Util::DebugOut(Util::DebugOut::Default, "ClientForUniRostockDevices") << "Testing getMdState():";
				const auto mdstate = consumer.getMdState();
				if (!mdstate.findNumericMetricStates().empty()
					&& !mdstate.findStringMetricStates().empty()) {
					Util::DebugOut(Util::DebugOut::Default, "ClientForUniRostockDevices") << "Success.";
				} else {
					Util::DebugOut(Util::DebugOut::Default, "ClientForUniRostockDevices") << "Fail.";
				}

				additionalResults << "Testing getMdState():" << std::endl;
				additionalResults << "Found " << mdstate.findEnumStringMetricStates().size() << " EnumStringMetricStates." << std::endl;
				additionalResults << "Found " << mdstate.findNumericMetricStates().size() << " NumericMetricStates." << std::endl;
				additionalResults << "Found " << mdstate.findStringMetricStates().size() << " StringMetricStates." << std::endl;
			}
			Util::DebugOut(Util::DebugOut::Default, "ClientForUniRostockDevices") << " ";
			Util::DebugOut(Util::DebugOut::Default, "ClientForUniRostockDevices") << " ";
			{
				Util::DebugOut(Util::DebugOut::Default, "ClientForUniRostockDevices") << "Testing getMDState(some_handle) for numeric metric:";
				std::unique_ptr<NumericMetricState> pNMS(consumer.requestState<NumericMetricState>(handle_m1_get_and_episodic));
				if ((pNMS != nullptr)
						&& pNMS->hasMetricValue()
						&& (pNMS->getMetricValue().getValue() == numeric_initial_value
								|| pNMS->getMetricValue().getValue() == numeric_some_value)) {
					Util::DebugOut(Util::DebugOut::Default, "ClientForUniRostockDevices") << "Success.";
				} else {
					Util::DebugOut(Util::DebugOut::Default, "ClientForUniRostockDevices") << "Fail.";
				}
			}
			// todo: reimplement for all OpertionStates
//			Util::DebugOut(Util::DebugOut::Default, "ClientForUniRostockDevices") << " ";
//			{
//				Util::DebugOut(Util::DebugOut::Default, "ClientForUniRostockDevices") << "Testing getMDState(some_handle) for operation state:";
//				OperationState os;
//				if (consumer.requestState(handle_setString_operation, os)
//						&& os.getOperatingMode() == OperatingMode::En) {
//					Util::DebugOut(Util::DebugOut::Default, "ClientForUniRostockDevices") << "Success.";
//				} else {
//					Util::DebugOut(Util::DebugOut::Default, "ClientForUniRostockDevices") << "Fail.";
//				}
//			}
			Util::DebugOut(Util::DebugOut::Default, "ClientForUniRostockDevices") << " ";
			{
				Util::DebugOut(Util::DebugOut::Default, "ClientForUniRostockDevices") << "Testing getMDState(some_handle) for string metric:";
				std::unique_ptr<StringMetricState> pSMS(consumer.requestState<StringMetricState>(handle_sm1_get_and_episodic_and_periodic));
				if ((pSMS != nullptr)
						&& pSMS->hasMetricValue()
						&& (pSMS->getMetricValue().getValue() == string_initial_value
								|| pSMS->getMetricValue().getValue() == string_some_value)) {
					Util::DebugOut(Util::DebugOut::Default, "ClientForUniRostockDevices") << "Success.";
				} else {
					Util::DebugOut(Util::DebugOut::Default, "ClientForUniRostockDevices") << "Fail.";
				}
			}
			Util::DebugOut(Util::DebugOut::Default, "ClientForUniRostockDevices") << " ";
			{
				Util::DebugOut(Util::DebugOut::Default, "ClientForUniRostockDevices") << "Testing getMdDescription():";
				const auto mddescription = consumer.getMdDescription();
				if (!mddescription.collectAllMdsDescriptors().empty()
						&& !mddescription.collectAllNumericMetricDescriptors().empty()
						&& !mddescription.collectAllStringMetricDescriptors().empty()) {
					Util::DebugOut(Util::DebugOut::Default, "ClientForUniRostockDevices") << "Success.";
				} else {
					Util::DebugOut(Util::DebugOut::Default, "ClientForUniRostockDevices") << "Fail.";
				}

				additionalResults << "Testing getMdDescription():" << std::endl;
				additionalResults << "Found " << mddescription.collectAllEnumStringMetricDescriptors().size() << " EnumStringMetricDescriptors." << std::endl;
				additionalResults << "Found " << mddescription.collectAllMdsDescriptors().size() << " HydraMDSDescriptors." << std::endl;
				additionalResults << "Found " << mddescription.collectAllNumericMetricDescriptors().size() << " NumericMetricDescriptors." << std::endl;
				additionalResults << "Found " << mddescription.collectAllStringMetricDescriptors().size() << " StringMetricDescriptors." << std::endl;
			}
			Util::DebugOut(Util::DebugOut::Default, "ClientForUniRostockDevices") << " ";
			{
				Util::DebugOut(Util::DebugOut::Default, "ClientForUniRostockDevices") << "Testing setValue():";
				additionalResults << "Testing setValue():" << std::endl;
				NumericMetricState nms(handle_m1_get_and_episodic);
				nms	.setDescriptorHandle(handle_m1_get_and_episodic)
					.setMetricValue(NumericMetricValue(MetricQuality(MeasurementValidity::Vld)).setValue(numeric_some_value));
				FutureInvocationState fut;
				if (consumer.commitState(nms, fut) == InvocationState::Wait) {
					additionalResults << "Request accepted." << std::endl;
				} else {
					additionalResults << "Request rejected." << std::endl;
				}
				if (fut.waitReceived(InvocationState::Fin, 1000)) {
					Util::DebugOut(Util::DebugOut::Default, "ClientForUniRostockDevices") << "Success.";
					additionalResults << "Request successful." << std::endl;
				} else {
					Util::DebugOut(Util::DebugOut::Default, "ClientForUniRostockDevices") << "Fail.";
					additionalResults << "Request failed." << std::endl;
				}
			}
			Util::DebugOut(Util::DebugOut::Default, "ClientForUniRostockDevices") << " ";
			{
				Util::DebugOut(Util::DebugOut::Default, "ClientForUniRostockDevices") << "Testing setString():";
				additionalResults << "Testing setString():" << std::endl;
				StringMetricState sms(handle_sm1_get_and_episodic_and_periodic);
				sms	.setDescriptorHandle(handle_sm1_get_and_episodic_and_periodic)
					.setMetricValue(StringMetricValue(MetricQuality(MeasurementValidity::Vld)).setValue(string_some_value));
				FutureInvocationState fut;
				if (consumer.commitState(sms, fut) == InvocationState::Wait) {
					additionalResults << "Request accepted." << std::endl;
				} else {
					additionalResults << "Request rejected." << std::endl;
				}
				if (fut.waitReceived(InvocationState::Fin, 1000)) {
					Util::DebugOut(Util::DebugOut::Default, "ClientForUniRostockDevices") << "Success.";
					additionalResults << "Request successful." << std::endl;
				} else {
					Util::DebugOut(Util::DebugOut::Default, "ClientForUniRostockDevices") << "Fail.";
					additionalResults << "Request failed." << std::endl;
				}
			}
			Util::DebugOut(Util::DebugOut::Default, "ClientForUniRostockDevices") << " ";
			{
				Util::DebugOut(Util::DebugOut::Default, "ClientForUniRostockDevices") << "Testing episodic eventing for numeric metrics by triggering setValue():";

				const unsigned int before(episodicHandler.receivedEventsCounter);

				Poco::Thread::sleep(1000);
				NumericMetricState nms(handle_m1_get_and_episodic);
				nms	.setDescriptorHandle(handle_m1_get_and_episodic)
					.setMetricValue(NumericMetricValue(MetricQuality(MeasurementValidity::Vld)).setValue(numeric_initial_value));
				FutureInvocationState fut;
				consumer.commitState(nms, fut);
				fut.waitReceived(InvocationState::Fin, 1000);
				Poco::Thread::sleep(1000);

				const unsigned int after(episodicHandler.receivedEventsCounter);

				if (after - before > 0) {
					Util::DebugOut(Util::DebugOut::Default, "ClientForUniRostockDevices") << "Success.";
				} else {
					Util::DebugOut(Util::DebugOut::Default, "ClientForUniRostockDevices") << "Fail.";
				}
			}
			Util::DebugOut(Util::DebugOut::Default, "ClientForUniRostockDevices") << " ";
			{
				Util::DebugOut(Util::DebugOut::Default, "ClientForUniRostockDevices") << "Testing periodic eventing by waiting for changed event counter:";

				const unsigned int before(periodicHandler.receivedEventsCounter);
				Poco::Thread::sleep(5500);
				const unsigned int after(periodicHandler.receivedEventsCounter);

				if (after - before > 0) {
					Util::DebugOut(Util::DebugOut::Default, "ClientForUniRostockDevices") << "Success.";
				} else {
					Util::DebugOut(Util::DebugOut::Default, "ClientForUniRostockDevices") << "Fail.";
				}
			}
			Util::DebugOut(Util::DebugOut::Default, "ClientForUniRostockDevices") << " ";
			{
				Util::DebugOut(Util::DebugOut::Default, "ClientForUniRostockDevices") << "Testing episodic and periodic eventing for string metrics by triggering setValue() and waiting:";

				const unsigned int before(combinedHandler.receivedEventsCounter);

				Poco::Thread::sleep(1000);
				StringMetricState sms(handle_sm1_get_and_episodic_and_periodic);
				sms	.setDescriptorHandle(handle_sm1_get_and_episodic_and_periodic)
					.setMetricValue(StringMetricValue(MetricQuality(MeasurementValidity::Vld)).setValue(string_some_value));
				FutureInvocationState fut;
				consumer.commitState(sms, fut);
				fut.waitReceived(InvocationState::Fin, 1000);
				Poco::Thread::sleep(5000);

				const unsigned int after(combinedHandler.receivedEventsCounter);

				if (after - before >= 2) {
					Util::DebugOut(Util::DebugOut::Default, "ClientForUniRostockDevices") << "Success.";
				} else {
					Util::DebugOut(Util::DebugOut::Default, "ClientForUniRostockDevices") << "Fail.";
				}
			}
			Util::DebugOut(Util::DebugOut::Default, "ClientForUniRostockDevices") << " ";
			{
				additionalResults << "Checking number of received events:" << std::endl;
				if (episodicHandler.receivedEventsCounter > 0) {
					additionalResults << "Handler for " << episodicHandler.getHandle() << " has " << episodicHandler.receivedEventsCounter << " events." << std::endl;
				} else {
					additionalResults << "Events for " << episodicHandler.getHandle() << " failed." << std::endl;
				}
				if (periodicHandler.receivedEventsCounter > 0) {
					additionalResults << "Handler for " << periodicHandler.getHandle() << " has " << periodicHandler.receivedEventsCounter << " events." << std::endl;
				} else {
					additionalResults << "Events for " << periodicHandler.getHandle() << " failed." << std::endl;
				}
				if (combinedHandler.receivedEventsCounter > 0) {
					additionalResults << "Handler for " << combinedHandler.getHandle() << " has " << combinedHandler.receivedEventsCounter << " events." << std::endl;
				} else {
					additionalResults << "Events for " << combinedHandler.getHandle() << " failed." << std::endl;
				}
			}

			Util::DebugOut(Util::DebugOut::Default, "ClientForUniRostockDevices") << std::endl << std::endl << "Additional information for results above: " << std::endl << additionalResults.str();
		}

		consumer.unregisterStateEventHandler(&episodicHandler);
		consumer.unregisterStateEventHandler(&periodicHandler);
		consumer.disconnect();
	} else {
		Util::DebugOut(Util::DebugOut::Default, "ClientForUniRostockDevices") << "Discovery failed.";
	}

    SDCLibrary::getInstance().shutdown();
	DebugOut(DebugOut::Default, "ClientForUniRostockDevices") << "Shutdown" << std::endl;
}

