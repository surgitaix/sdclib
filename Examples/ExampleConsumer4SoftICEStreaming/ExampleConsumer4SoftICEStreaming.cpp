/**
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  *
  */

/*
 * SDCConsumerEventHandler.cpp
 *
 *  @Copyright (C) 2018, SurgiTAIX AG
 *  Author: buerger
 *
 *  This example demonstrates how to set up a simple SDCConsumer. Conceptually it connects to the ExampleProvider of SoftICE (https://bitbucket.org/surgitaix/softice/),
 *  the Java SDC Library which is defined by it's endpoint reference (EPR).
 *  Two state handler classes are defined to utilize the eventing mechanism for a numeric metric state.
 *
 */

#include "SDCLib/SDCLibrary.h"
#include "SDCLib/Data/SDC/SDCConsumer.h"
#include "SDCLib/Data/SDC/SDCConsumerMDStateHandler.h"
#include "SDCLib/Data/SDC/MDIB/MetricQuality.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricState.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricValue.h"
#include "SDCLib/Data/SDC/MDIB/RealTimeSampleArrayMetricState.h"
#include "SDCLib/Data/SDC/MDIB/SampleArrayValue.h"
#include "SDCLib/Util/DebugOut.h"
#include "SDCLib/Util/Task.h"


#include "OSELib/SDC/ServiceManager.h"

#include "Poco/Runnable.h"
#include "Poco/Mutex.h"
#include "Poco/ScopedLock.h"
#include "Poco/Thread.h"

using namespace SDCLib;
using namespace SDCLib::Util;
using namespace SDCLib::Data::SDC;

const std::string deviceEPR("UDI-1234567890");

const std::string streamHandle("handle_stream");


// Example for a minimum implementation of a consumer state handler
class NumericConsumerEventHandler : public  SDCConsumerMDStateHandler<NumericMetricState> {
public:
	NumericConsumerEventHandler(const std::string & handle) :  SDCConsumerMDStateHandler(handle)
	{
	}

	// this abstract method implements the eventing mechanism
	// called from within the framework if a value is changed by the provider
	void onStateChanged(const NumericMetricState & state) override {
		DebugOut(DebugOut::Default, "ExampleConsumer4SoftICEStreaming") << "Recieved Value: " << state.getMetricValue().getValue() << std::endl;
	}
};


class StreamConsumerEventHandler : public SDCConsumerMDStateHandler<RealTimeSampleArrayMetricState> {
public:
	StreamConsumerEventHandler(const std::string & handle) : SDCConsumerMDStateHandler(handle),
    	verifiedChunks(false)
    {
    }

	// this abstract method implements the eventing mechanism
	// called from within the framework if a value is changed by the provider
    void onStateChanged(const RealTimeSampleArrayMetricState & state) override {
    	Poco::Mutex::ScopedLock lock(mutex);
        std::vector<double> values = state.getMetricValue().getSamples();


        // simple check if the data is valid:
        // assumption: sequence of values, increased by 1
        verifiedChunks = true;
        for (size_t i = 0; i < values.size(); i++) {
//        	DebugOut(DebugOut::Default, "StreamSDC") << values[i];
            if (values[i] != double(i))
                verifiedChunks = false;
        }
        DebugOut(DebugOut::Default, "StreamSDC") << "Received chunk! Handle: " << descriptorHandle << ". Validity: " << verifiedChunks << std::endl;
    }

    bool getVerifiedChunks() {
    	Poco::Mutex::ScopedLock lock(mutex);
        return verifiedChunks;
    }

private:
    Poco::Mutex mutex;
    bool verifiedChunks;
};




int main() {
	Util::DebugOut(Util::DebugOut::Default, "ExampleConsumer4SoftICEStreaming") << "Startup";
    SDCLibrary::getInstance().startup(OSELib::LogLevel::Debug);

    // Create a new SDCInstance (no flag will auto init)
    auto t_SDCInstance = std::make_shared<SDCInstance>(Config::SDC_DEFAULT_PORT_CONSUMER, true);
    // Some restriction
    t_SDCInstance->setIP6enabled(false);
    t_SDCInstance->setIP4enabled(true);
    // Bind it to interface that matches the internal criteria (usually the first enumerated)
    if(!t_SDCInstance->bindToDefaultNetworkInterface()) {
        std::cout << "Failed to bind to default network interface! Exit..." << std::endl;
        return -1;
    }

    // Consumer is build via discovery
	OSELib::SDC::ServiceManager oscpsm(t_SDCInstance);
	DebugOut(DebugOut::Default, "ExampleConsumer4SoftICEStreaming") << "Consumer discovery..." << std::endl;

	// testing against SoftICE
	std::shared_ptr<SDCConsumer> c(oscpsm.discoverEndpointReference(deviceEPR));
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
