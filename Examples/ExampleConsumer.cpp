
#include "OSCLib/OSCLibrary.h"
#include "OSCLib/Data/OSCP/OSCPConsumer.h"
#include "OSCLib/Data/OSCP/OSCPConsumerConnectionLostHandler.h"
#include "OSCLib/Data/OSCP/OSCPConsumerEventHandler.h"
#include "OSCLib/Data/OSCP/OSCPConsumerNumericMetricStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPConsumerAlertConditionStateHandler.h"
#include "OSCLib/Data/OSCP/MDIB/AlertConditionState.h"
#include "OSCLib/Data/OSCP/MDIB/HydraMDSDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricValue.h"
#include "OSCLib/Data/OSCP/FutureInvocationState.h"
#include "OSCLib/Util/DebugOut.h"

#include "OSELib/OSCP/ServiceManager.h"

using namespace OSCLib;
using namespace OSCLib::Data::OSCP;

const std::string deviceEPR("UDI-1234567890");

class ExampleConsumerEventHandler : public Data::OSCP::OSCPConsumerNumericMetricStateHandler {
public:
    ExampleConsumerEventHandler(const std::string & handle) : handle(handle) {
    }

    virtual ~ExampleConsumerEventHandler() {
    }

    void onStateChanged(const Data::OSCP::NumericMetricState & state) override {
        const double val(state.getObservedValue().getValue());
        Util::DebugOut(Util::DebugOut::Default, "ExampleConsumer") << "Consumer: Received value changed of " << handle << ": " << val << std::endl;
    }

    std::string getHandle() override {
        return handle;
    }

private:
    const std::string handle;
};

class ExampleConsumerAlertEventHandler : public Data::OSCP::OSCPConsumerAlertConditionStateHandler {
public:
	ExampleConsumerAlertEventHandler(const std::string & handle) :
		handle(handle)
	{
	}

    virtual ~ExampleConsumerAlertEventHandler() {

    }

    void onStateChanged(const Data::OSCP::AlertConditionState & state) override {
    	Util::DebugOut(Util::DebugOut::Default, "ExampleConsumer") << "Consumer: Received alert signal changed of " << handle << ", activation: "
        		<< Data::OSCP::EnumToString::convert(state.getActivationState()) << ", presence: " << state.getPresence() << std::endl;
    }

    std::string getHandle() override {
        return handle;
    }

private:
    const std::string handle;
};

void waitForUserInput() {
	std::string temp;
	Util::DebugOut(Util::DebugOut::Default, "") << "Press key to proceed.";
	std::cin >> temp;
}

int main() {
	Util::DebugOut(Util::DebugOut::Default, "ExampleConsumer") << "Startup";
    OSCLibrary::getInstance().startup();
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
	std::shared_ptr<ExampleConsumerEventHandler> eh(new ExampleConsumerEventHandler("handle_metric"));

	if (c != nullptr) {
		Data::OSCP::OSCPConsumer & consumer = *c;
	    std::unique_ptr<MyConnectionLostHandler> myHandler(new MyConnectionLostHandler(consumer));
	    consumer.setConnectionLostHandler(myHandler.get());

		consumer.registerStateEventHandler(eh.get());
        Util::DebugOut(Util::DebugOut::Default, "ExampleConsumer") << "Discovery succeeded.";

        NumericMetricState metricState;
        consumer.requestState("handle_metric", metricState);

        // Here, we increase max weight to switch condition presence => results in alert signal presence
        metricState.setObservedValue(NumericMetricValue().setValue(10));
        FutureInvocationState fis;
        consumer.commitState(metricState, fis);
        Util::DebugOut(Util::DebugOut::Default, "ExampleConsumer") << "Commit result: " << fis.waitReceived(InvocationState::FINISHED, 2000);

        waitForUserInput();
        consumer.unregisterStateEventHandler(eh.get());
		consumer.disconnect();
	} else {
		Util::DebugOut(Util::DebugOut::Default, "ExampleConsumer") << "Discovery failed.";
	}

    OSCLibrary::getInstance().shutdown();
    Util::DebugOut(Util::DebugOut::Default, "ExampleConsumer") << "Shutdown." << std::endl;
}
