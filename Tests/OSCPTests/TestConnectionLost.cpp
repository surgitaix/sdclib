
#include "OSCLib/OSCLibrary.h"
#include "OSCLib/Data/OSCP/OSCPConsumer.h"
#include "OSCLib/Data/OSCP/OSCPConsumerConnectionLostHandler.h"
#include "OSCLib/Data/OSCP/OSCPProvider.h"
#include "OSCLib/Data/OSCP/MDIB/ChannelDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/MdsDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/LocalizedText.h"
#include "OSCLib/Data/OSCP/MDIB/MdDescription.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/SystemContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/LocationContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/MetaData.h"
#include "OSCLib/Data/OSCP/MDIB/VmdDescriptor.h"
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

class OSCPTestDeviceProvider {
public:

    OSCPTestDeviceProvider(const std::size_t number, const std::size_t metricCount) : oscpProvider(), epr(number), metrics(metricCount) {
    	oscpProvider.setEndpointReference(std::string("UDI_") + std::to_string(epr));

        // System context
        SystemContextDescriptor sc("MDC_SYS_CON");
        sc.setLocationContext(LocationContextDescriptor("MDC_LOC_CON"));

        // Channel
        ChannelDescriptor testChannel("MDC_CH");
        testChannel.setSafetyClassification(SafetyClassification::MedA);
        for (std::size_t i = 0; i < metrics; i++) {
        	NumericMetricDescriptor nmd("handle_cur" + std::to_string(i), CodedValue(CodeIdentifier("MDCX_CODE_ID_WEIGHT")), MetricCategory::Msrmt, MetricAvailability::Cont, 1.0);
    		testChannel.addMetric(nmd);
        }

        // VMD
        VmdDescriptor testVMD("MDC_VMD1");
        testVMD.addChannel(testChannel);

        // MDS
        MdsDescriptor mds("MDC_MDS");
        mds.setMetaData(
			MetaData()
				.addManufacturer(LocalizedText().setRef("SurgiTAIX AG"))
        		.setModelNumber("1")
        		.addModelName(LocalizedText().setRef("EndoTAIX"))
        		.addSerialNumber("1234"))
			.setSystemContext(sc)
			.setType(CodedValue(CodeIdentifier("MDCX_CODE_ID_MDS"))
					.setCodingSystem(xml_schema::Uri("OR.NET.Codings")));

        mds.addVmd(testVMD);

        // create and add description
        MdDescription mdDescription;
        mdDescription.addMdsDescriptor(mds);

        oscpProvider.setMdDescription(mdDescription);

    }

    void startup() {
    	oscpProvider.startup();
    }

    void shutdown() {
    	oscpProvider.shutdown();
    }

    const std::string getEndpointReference() const {
    	return oscpProvider.getEndpointReference();
    }


private:
    // Provider object
    OSCPProvider oscpProvider;

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

	    DebugOut(DebugOut::Default, std::cout, "connectionlostoscp") << "Waiting for the Providers to startup...";

		constexpr std::size_t providerCount(10);
		constexpr std::size_t metricCount(10);
		std::vector<std::shared_ptr<Tests::ConnectionLostOSCP::OSCPTestDeviceProvider>> providers;
		std::vector<std::string> providerEPRs;

		for (std::size_t i = 0; i < providerCount; i++) {
			std::shared_ptr<Tests::ConnectionLostOSCP::OSCPTestDeviceProvider> p(new Tests::ConnectionLostOSCP::OSCPTestDeviceProvider(i, metricCount));
			providers.push_back(p);
			p->startup();
			providerEPRs.emplace_back(p->getEndpointReference());
			Poco::Thread::sleep(1000);
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
				DebugOut(DebugOut::Default, std::cout, "connectionlostoscp") << "Missing epr: " << providerEPR << std::endl;
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
