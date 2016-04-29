
#include "OSCLib/OSCLibrary.h"
#include "OSCLib/Data/OSCP/OSCPConsumer.h"
#include "OSCLib/Data/OSCP/OSCPConsumerConnectionLostHandler.h"
#include "OSCLib/Data/OSCP/OSCPProvider.h"
#include "OSCLib/Data/OSCP/MDIB/ChannelDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/HydraMDSDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/LocalizedText.h"
#include "OSCLib/Data/OSCP/MDIB/MDDescription.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/SystemContext.h"
#include "OSCLib/Data/OSCP/MDIB/SystemMetaData.h"
#include "OSCLib/Data/OSCP/MDIB/VMDDescriptor.h"
#include "OSCLib/Util/DebugOut.h"
#include "../AbstractOSCLibFixture.h"
#include "../UnitTest++/src/UnitTest++.h"

#include "OSELib/OSCP/ServiceManager.h"

#include "Poco/Mutex.h"
#include "Poco/ScopedLock.h"

#include <atomic>

using namespace OSCLib;
using namespace OSCLib::Util;
using namespace OSCLib::Data::OSCP;

namespace OSCLib {
namespace Tests {
namespace ConnectionLostOSCP {

class OSCPTestDeviceProvider : public OSCPProvider {
public:

    OSCPTestDeviceProvider(const std::size_t number, const std::size_t metricCount) : epr(number), metrics(metricCount) {
    	setEndpointReference(std::string("UDI_") + std::to_string(epr));

        // Location context
        SystemContext sc;

        // Channel
        ChannelDescriptor testChannel;
        testChannel.setIntendedUse(IntendedUse::MEDICAL_A);
        for (std::size_t i = 0; i < metrics; i++) {
        	NumericMetricDescriptor nmd;
    		nmd.setMetricCategory(MetricCategory::MEASUREMENT)
               .setAvailability(MetricAvailability::CONTINUOUS)
    		   .setType(
    				CodedValue()
    				.setCodeId("MDCX_CODE_ID_WEIGHT")
    				.addConceptDescription(LocalizedText().set("Current weight")))
    	       .setHandle("handle_cur" + std::to_string(i));
    		testChannel.addMetric(nmd);
        }

        // VMD
        VMDDescriptor testVMD;
        testVMD.addChannel(testChannel);

        // MDS
        HydraMDSDescriptor mds;
        mds
			.setMetaData(
					SystemMetaData()
					.addManufacturer(
						LocalizedText()
						.set("SurgiTAIX AG"))
					.addModelName(
						LocalizedText()
						.set("EndoTAIX"))
					.addModelNumber("1")
					.addSerialNumber("1234")
					)
			.setContext(sc)
			.setType(
                CodedValue()
                .setCodingSystemId("OR.NET.Codings")
        		.setCodeId("MDCX_CODE_ID_MDS"));

        mds.addVMD(testVMD);

        addHydraMDS(mds);
    }

private:
    const std::size_t epr;
    const std::size_t metrics;
};

} /* namespace MultiOSCP */
} /* namespace Tests */
} /* namespace OSCLib */

struct FixtureConnectionLostOSCP : Tests::AbstractOSCLibFixture {
	FixtureConnectionLostOSCP() : AbstractOSCLibFixture("FixtureConnectionLostOSCP", OSELib::LogLevel::NOTICE, 8150) {}
};

SUITE(OSCP) {
TEST_FIXTURE(FixtureConnectionLostOSCP, connectionlostoscp)
{
	try
	{
	    class MyConnectionLostHandler : public Data::OSCP::OSCPConsumerConnectionLostHandler {
	    public:
	    	MyConnectionLostHandler(Data::OSCP::OSCPConsumer & consumer) : consumer(consumer) {
	    	}
	    	void onConnectionLost() override {
	    		DebugOut logoutput(DebugOut::Default, std::cout, "connectionlostoscp");
	    		logoutput << "Connection lost, disconnecting... ";
	    		consumer.disconnect();
	    		logoutput << "disconnected." << std::endl;
	    		handlerVisited = true;
	    	}

	    	std::atomic<bool> handlerVisited;

	    private:
	    	Data::OSCP::OSCPConsumer & consumer;
	    };

		constexpr std::size_t providerCount(10);
		constexpr std::size_t metricCount(10);
		std::vector<std::shared_ptr<Tests::ConnectionLostOSCP::OSCPTestDeviceProvider>> providers;
		std::vector<std::string> providerEPRs;

		for (std::size_t i = 0; i < providerCount; i++) {
			std::shared_ptr<Tests::ConnectionLostOSCP::OSCPTestDeviceProvider> p(new Tests::ConnectionLostOSCP::OSCPTestDeviceProvider(i, metricCount));
			providers.push_back(p);
			p->startup();
			providerEPRs.emplace_back(p->getEndpointReference());
		}

        Poco::Thread::sleep(2000);

        DebugOut(DebugOut::Default, std::cout, "connectionlostoscp") << "Starting discovery test...";

        OSELib::OSCP::ServiceManager sm;
        std::vector<std::unique_ptr<OSCPConsumer>> consumers(sm.discoverOSCP());

        bool foundAll = true;
        for (const auto & providerEPR : providerEPRs) {
        	bool foundOne = false;
			for (const auto & consumer : consumers) {
				if (consumer->getEndpointReference() == providerEPR) {
					foundOne = true;
					break;
				}
			}
			if (!foundOne) {
				DebugOut(DebugOut::Default, std::cout, "multioscp") << "Missing epr: " << providerEPR << std::endl;
			}
			foundAll &= foundOne;
        }
        CHECK_EQUAL(true, foundAll);

        std::vector<std::shared_ptr<MyConnectionLostHandler>> connectionLostHanders;
        for (auto & nextConsumer : consumers) {
        	DebugOut(DebugOut::Default, std::cout, "connectionlostoscp") << "Found " << nextConsumer->getEndpointReference();

        	if (std::find(providerEPRs.begin(), providerEPRs.end(), nextConsumer->getEndpointReference()) == providerEPRs.end()) {
        		// not our own provider => skip
        		continue;
        	}

        	std::shared_ptr<MyConnectionLostHandler> myHandler(new MyConnectionLostHandler(*nextConsumer.get()));
        	nextConsumer->setConnectionLostHandler(myHandler.get());
        	connectionLostHanders.push_back(myHandler);
        }

        for (auto & next : providers) {
        	next->shutdown();
        }

        Poco::Thread::sleep(10000);

        for (const auto handler : connectionLostHanders) {
        	CHECK_EQUAL(true, handler->handlerVisited);
        }

    } catch (char const* exc) {
		DebugOut(DebugOut::Default, std::cerr, "connectionlostoscp") << exc;
	} catch (...) {
		DebugOut(DebugOut::Default, std::cerr, "connectionlostoscp") << "Unknown exception occurred!";
	}
	DebugOut::closeLogFile();
}
}
