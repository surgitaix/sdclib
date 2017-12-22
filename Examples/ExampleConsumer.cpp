
#include "OSCLib/OSCLibrary.h"
#include "OSCLib/Data/OSCP/OSCPConsumer.h"
#include "OSCLib/Data/OSCP/OSCPConsumerConnectionLostHandler.h"
#include "OSCLib/Data/OSCP/OSCPConsumerEventHandler.h"
#include "OSCLib/Data/OSCP/OSCPConsumerNumericMetricStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPConsumerAlertConditionStateHandler.h"
#include "OSCLib/Data/OSCP/MDIB/AlertConditionState.h"
#include "OSCLib/Data/OSCP/MDIB/MdsDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/MetricQuality.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricValue.h"
#include "OSCLib/Data/OSCP/MDIB/custom/OperationInvocationContext.h"
#include "OSCLib/Data/OSCP/FutureInvocationState.h"
#include "OSCLib/Util/DebugOut.h"

#include "OSELib/OSCP/ServiceManager.h"

using namespace OSCLib;
using namespace OSCLib::Data::OSCP;

const std::string deviceEPR("UDI-EXAMPLEPROVIDER");

const std::string HANDLE_SET_METRIC("handle_set");
const std::string HANDLE_GET_METRIC("handle_get");
const std::string HANDLE_STREAM_METRIC("handle_stream");
const std::string HANDLE_STRING_METRIC("handle_string");


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




void waitForUserInput() {
	std::string temp;
	Util::DebugOut(Util::DebugOut::Default, "") << "Press key to proceed.";
	std::cin >> temp;
}




int main() {
	Util::DebugOut(Util::DebugOut::Default, "ExampleConsumer") << "Startup";
    OSCLibrary::getInstance().startup(OSELib::LogLevel::ERROR);
	OSCLibrary::getInstance().setPortStart(12000);

    class MyConnectionLostHandler : public Data::OSCP::OSCPConsumerConnectionLostHandler {
    public:
    	MyConnectionLostHandler(Data::OSCP::OSCPConsumer & consumer) : consumer(consumer) {
    	}
    	void onConnectionLost() override {
    		std::cerr << "Connection lost, disconnecting... ";
    		consumer.disconnect();
    		std::cerr << "disconnected." << std::endl;
    	}
    private:
    	Data::OSCP::OSCPConsumer & consumer;
    };

	// Discovery
	OSELib::OSCP::ServiceManager oscpsm;
	std::unique_ptr<Data::OSCP::OSCPConsumer> c(oscpsm.discoverEndpointReference(deviceEPR));
	std::shared_ptr<ExampleConsumerEventHandler> eh_get(new ExampleConsumerEventHandler(HANDLE_GET_METRIC));
	std::shared_ptr<ExampleConsumerEventHandler> eh_set(new ExampleConsumerEventHandler(HANDLE_SET_METRIC));

	if (c != nullptr) {
		Data::OSCP::OSCPConsumer & consumer = *c;
	    std::unique_ptr<MyConnectionLostHandler> myHandler(new MyConnectionLostHandler(consumer));
	    consumer.setConnectionLostHandler(myHandler.get());

	    consumer.registerStateEventHandler(eh_get.get());
	    consumer.registerStateEventHandler(eh_set.get());
        Util::DebugOut(Util::DebugOut::Default, "ExampleConsumer") << "Discovery succeeded.";

        std::unique_ptr<NumericMetricState> pMetricState(consumer.requestState<NumericMetricState>(HANDLE_SET_METRIC));

        pMetricState->setMetricValue(NumericMetricValue(MetricQuality(MeasurementValidity::Vld)).setValue(10));
        FutureInvocationState fis;
        consumer.commitState(*pMetricState, fis);
        Util::DebugOut(Util::DebugOut::Default, "ExampleConsumer") << "Commit result: " << fis.waitReceived(InvocationState::Fin, 10000);

        waitForUserInput();
        consumer.unregisterStateEventHandler(eh_get.get());
        consumer.unregisterStateEventHandler(eh_set.get());
		consumer.disconnect();
	} else {
		Util::DebugOut(Util::DebugOut::Default, "ExampleConsumer") << "Discovery failed.";
	}

    OSCLibrary::getInstance().shutdown();
    Util::DebugOut(Util::DebugOut::Default, "ExampleConsumer") << "Shutdown." << std::endl;
}
