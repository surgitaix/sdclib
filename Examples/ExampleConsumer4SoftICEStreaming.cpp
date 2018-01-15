#include "OSCLib/OSCLibrary.h"
#include "OSCLib/Data/OSCP/OSCPConsumer.h"
#include "OSCLib/Data/OSCP/SDCConsumerOperationInvokedHandler.h"
#include "OSCLib/Data/OSCP/OSCPConsumerRealTimeSampleArrayMetricStateHandler.h"
#include "OSCLib/Data/OSCP/OSCPConsumerNumericMetricStateHandler.h"
#include "OSCLib/Data/OSCP/MDIB/MetricQuality.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricValue.h"
#include "OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/SampleArrayValue.h"
#include "OSCLib/Util/DebugOut.h"
#include "OSCLib/Util/Task.h"


#include "OSELib/OSCP/ServiceManager.h"

#include "Poco/Runnable.h"
#include "Poco/Mutex.h"
#include "Poco/ScopedLock.h"
#include "Poco/Thread.h"

using namespace OSCLib;
using namespace OSCLib::Util;
using namespace OSCLib::Data::OSCP;

const std::string deviceEPR("UDI-1234567890");

const std::string streamHandle("handle_stream");


class StreamConsumerEventHandler : public OSCPConsumerRealTimeSampleArrayMetricStateHandler {
public:
	StreamConsumerEventHandler(const std::string & handle) :
    	verifiedChunks(false),
		handle(handle)
    {
    }

    void onStateChanged(const RealTimeSampleArrayMetricState & state) override {
    	Poco::Mutex::ScopedLock lock(mutex);
        std::vector<double> values = state.getMetricValue().getSamples();


        // simple check if the data is valid:
        // assumption: sequence of values, increased by 1
        verifiedChunks = true;
        for (size_t i = 0; i < values.size(); i++) {
//        	DebugOut(DebugOut::Default, "StreamOSCP") << values[i];
            if (values[i] != double(i))
                verifiedChunks = false;
        }
        DebugOut(DebugOut::Default, "StreamOSCP") << "Received chunk! Handle: " << handle << ". Validity: " << verifiedChunks << std::endl;
    }

    std::string getHandle() override {
        return handle;
    }

    bool getVerifiedChunks() {
    	Poco::Mutex::ScopedLock lock(mutex);
        return verifiedChunks;
    }

private:
    Poco::Mutex mutex;
    bool verifiedChunks;
    const std::string handle;
};


class NumericConsumerEventHandler : public OSCPConsumerNumericMetricStateHandler {

public:
	NumericConsumerEventHandler(const std::string & handle) : handle(handle) {
	}

	void onStateChanged(const NumericMetricState & state) override {
		DebugOut(DebugOut::Default, "ExampleConsumer4SoftICEStreaming") << "Recieved Value: " << state.getMetricValue().getValue() << std::endl;
	}

	std::string getHandle() override {
	        return handle;
	    }
private:
	const std::string handle;

};




int main() {
	Util::DebugOut(Util::DebugOut::Default, "ExampleConsumer4SoftICEStreaming") << "Startup";
    OSCLibrary::getInstance().startup(OSELib::LogLevel::DEBUG);
    OSCLibrary::getInstance().setIP4enabled(true);
    OSCLibrary::getInstance().setIP6enabled(false);

    // Consumer is build via discovery
	OSELib::OSCP::ServiceManager oscpsm;
	DebugOut(DebugOut::Default, "ExampleConsumer4SoftICEStreaming") << "Consumer discovery..." << std::endl;

	// testing against SoftICE
	std::shared_ptr<OSCPConsumer> c(oscpsm.discoverEndpointReference(deviceEPR));
	std::shared_ptr<StreamConsumerEventHandler> streamEventHandler = std::make_shared<StreamConsumerEventHandler>(streamHandle);
	std::shared_ptr<NumericConsumerEventHandler> getNumericEventHandler = std::make_shared<NumericConsumerEventHandler>("handle_metric");
	std::shared_ptr<NumericConsumerEventHandler> setNumericEventHandler = std::make_shared<NumericConsumerEventHandler>("handle_set");

	if (c != nullptr) {
		DebugOut(DebugOut::Default, "ExampleConsumer4SoftICEStreaming") << "Provider found!" << std::endl;
		c->registerStateEventHandler(streamEventHandler.get());
		c->registerStateEventHandler(getNumericEventHandler.get());
		c->registerStateEventHandler(setNumericEventHandler.get());

//		set the providers value for the NMS: handle_set
		NumericMetricState nms("handle_set");
		nms.setMetricValue(NumericMetricValue(MetricQuality(MeasurementValidity::Vld)).setValue(84.0));
		Poco::Thread::sleep(1000);
		c->commitState(nms);

		std::string temp;
		DebugOut(DebugOut::Default, "ExampleProvider4SoftICEStreaming") << "Press key to exit program.";
		std::cin >> temp;

		c->unregisterStateEventHandler(streamEventHandler.get());
		c->unregisterStateEventHandler(getNumericEventHandler.get());
		c->unregisterStateEventHandler(setNumericEventHandler.get());
		c->disconnect();
	} else {
		DebugOut(DebugOut::Default, "ExampleConsumer4SoftICEStreaming") << "Provider not found!" << std::endl;
	}

}
