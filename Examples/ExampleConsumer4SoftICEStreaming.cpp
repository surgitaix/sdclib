#include "OSCLib/OSCLibrary.h"
#include "OSCLib/Data/OSCP/OSCPConsumer.h"
#include "OSCLib/Data/OSCP/OSCPConsumerEventHandler.h"
#include "OSCLib/Data/OSCP/OSCPConsumerRealTimeSampleArrayMetricStateHandler.h"
#include "OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayValue.h"
#include "OSCLib/Data/OSCP/MDIB/RTValueType.h"
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

const std::string deviceEPR("DEMO-123");

class StreamConsumerEventHandler : public OSCPConsumerRealTimeSampleArrayMetricStateHandler {
public:
	StreamConsumerEventHandler(const std::string & handle) :
    	verifiedChunks(false),
		handle(handle)
    {
    }

    void onStateChanged(const RealTimeSampleArrayMetricState & state) override {
    	Poco::Mutex::ScopedLock lock(mutex);
        DebugOut(DebugOut::Default, "StreamOSCP") << "Received chunk! Handle: " << handle << std::endl;
        std::vector<double> values = state.getObservedValue().getSamples().getValues();

        // simple check if the data is valid:
        // assumption: sequence of values, increased by 1
        verifiedChunks = true;
        for (size_t i = 0; i < values.size(); i++) {
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


int main() {
	Util::DebugOut(Util::DebugOut::Default, "ExampleConsumer4SoftICEStreaming") << "Startup";
    OSCLibrary::getInstance().startup();

    // Consumer
	OSELib::OSCP::ServiceManager oscpsm;
	DebugOut(DebugOut::Default, "ExampleConsumer4SoftICEStreaming") << "Consumer discovery..." << std::endl;
	std::shared_ptr<OSCPConsumer> c(oscpsm.discoverEndpointReference("DEMO-123"));
	std::shared_ptr<StreamConsumerEventHandler> eventHandler = std::make_shared<StreamConsumerEventHandler>("handle_stream");

	if (c != nullptr) {
		DebugOut(DebugOut::Default, "ExampleConsumer4SoftICEStreaming") << "Provider found!" << std::endl;
		c->registerStateEventHandler(eventHandler.get());

		std::string temp;
		DebugOut(DebugOut::Default, "ExampleProvider4SoftICEStreaming") << "Press key to exit program.";
		std::cin >> temp;

		c->unregisterStateEventHandler(eventHandler.get());
		c->disconnect();
	} else {
		DebugOut(DebugOut::Default, "ExampleConsumer4SoftICEStreaming") << "Provider not found!" << std::endl;
	}



}
