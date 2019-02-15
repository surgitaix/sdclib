
#include "OSCLib/SDCLibrary.h"
#include "OSCLib/Data/SDC/SDCConsumer.h"
#include "OSCLib/Data/SDC/SDCConsumerConnectionLostHandler.h"
#include "OSCLib/Data/SDC/SDCProvider.h"
#include "OSCLib/Data/SDC/MDIB/ChannelDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/CodedValue.h"
#include "OSCLib/Data/SDC/MDIB/MdsDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/LocalizedText.h"
#include "OSCLib/Data/SDC/MDIB/MdDescription.h"
#include "OSCLib/Data/SDC/MDIB/NumericMetricDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/SystemContextDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/LocationContextDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/MetaData.h"
#include "OSCLib/Data/SDC/MDIB/VmdDescriptor.h"
#include "OSCLib/Util/DebugOut.h"
#include "../AbstractOSCLibFixture.h"
#include "../UnitTest++/src/UnitTest++.h"

#include "OSELib/SDC/ServiceManager.h"

#include "Poco/Mutex.h"
#include "Poco/ScopedLock.h"

#include <atomic>

using namespace SDCLib;
using namespace SDCLib::Util;
using namespace SDCLib::Data::SDC;

namespace SDCLib {
namespace Tests {
namespace ConnectionLostSDC {

class OSCPTestDeviceProvider {
public:

    OSCPTestDeviceProvider(SDCInstance_shared_ptr p_SDCInstance, const std::size_t number, const std::size_t metricCount) : sdcProvider(p_SDCInstance), epr(number), metrics(metricCount) {
    	sdcProvider.setEndpointReference(std::string("UDI_") + std::to_string(epr));

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

        sdcProvider.setMdDescription(mdDescription);

    }

    void startup() {
    	sdcProvider.startup();
    }

    void shutdown() {
    	sdcProvider.shutdown();
    }

    const std::string getEndpointReference() const {
    	return sdcProvider.getEndpointReference();
    }


private:
    // Provider object
    SDCProvider sdcProvider;

    const std::size_t epr;
    const std::size_t metrics;
};

} /* namespace MultiSDC */
} /* namespace Tests */
} /* namespace SDCLib */

struct FixtureConnectionLostSDC : Tests::AbstractOSCLibFixture {
	FixtureConnectionLostSDC() : AbstractOSCLibFixture("FixtureConnectionLostSDC", OSELib::LogLevel::Notice, 8150) {}
};

SUITE(OSCP) {
TEST_FIXTURE(FixtureConnectionLostSDC, connectionlostoscp)
{
	try
	{
	    class MyConnectionLostHandler : public Data::SDC::SDCConsumerConnectionLostHandler {
	    public:
	    	MyConnectionLostHandler(Data::SDC::SDCConsumer & consumer) : consumer(consumer) {
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
	    	Data::SDC::SDCConsumer & consumer;
	    };

	    DebugOut(DebugOut::Default, std::cout, "connectionlostoscp") << "Waiting for the Providers to startup...";

		CONSTEXPR_MACRO std::size_t providerCount(10);
		CONSTEXPR_MACRO std::size_t metricCount(10);
		std::vector<std::shared_ptr<Tests::ConnectionLostSDC::OSCPTestDeviceProvider>> providers;
		std::vector<std::string> providerEPRs;

        // Create a new SDCInstance (no flag will auto init)
        auto t_SDCInstance = std::make_shared<SDCInstance>();
        // Some restriction
        t_SDCInstance->setIP6enabled(false);
        t_SDCInstance->setIP4enabled(true);
        // Bind it to interface that matches the internal criteria (usually the first enumerated)
        if(!t_SDCInstance->bindToDefaultNetworkInterface()) {
            std::cout << "Failed to bind to default network interface! Exit..." << std::endl;
            return;
        }

		for (std::size_t i = 0; i < providerCount; i++) {
			std::shared_ptr<Tests::ConnectionLostSDC::OSCPTestDeviceProvider> p(new Tests::ConnectionLostSDC::OSCPTestDeviceProvider(t_SDCInstance, i, metricCount));
			providers.push_back(p);
			p->startup();
			providerEPRs.emplace_back(p->getEndpointReference());
			Poco::Thread::sleep(1000);
		}




        Poco::Thread::sleep(2000);

        DebugOut(DebugOut::Default, std::cout, "connectionlostoscp") << "Starting discovery test...";

        OSELib::SDC::ServiceManager sm(t_SDCInstance);
        std::vector<std::unique_ptr<SDCConsumer>> consumers(sm.discoverOSCP());

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
