
#include "OSCLib/SDCInstance.h"
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

const std::string VMD_DESCRIPTOR_HANDLE("ConnectionLost_vmd");
const std::string CHANNEL_DESCRIPTOR_HANDLE("ConnectionLost_channel");
const std::string MDS_DESCRIPTOR_HANDLE("ConnectionLost_mds");

const std::string HANDLE_GET_METRIC("handle_get");


class OSCPTestDeviceProvider {
public:

    OSCPTestDeviceProvider(SDCInstance_shared_ptr p_SDCInstance, const std::size_t number)
        : sdcProvider(p_SDCInstance)
        , m_eprID(number)
        , getMetricDescriptor(HANDLE_GET_METRIC,
				CodedValue("MDCX_EXAMPLE_GET"),
				MetricCategory::Set,
				MetricAvailability::Cont,
				1)
        {

        sdcProvider.setEndpointReference(std::string("UDI_") + std::to_string(m_eprID));

		Dev::DeviceCharacteristics devChar;
		devChar.addFriendlyName("en", "Test ConnectionLost " + std::to_string(m_eprID));
		sdcProvider.setDeviceCharacteristics(devChar);

        // Channel
        ChannelDescriptor t_channel(CHANNEL_DESCRIPTOR_HANDLE);
        t_channel
            .setSafetyClassification(SafetyClassification::MedB)
            .addMetric(getMetricDescriptor);


        // VMD
        VmdDescriptor t_vmd(VMD_DESCRIPTOR_HANDLE);
        t_vmd.addChannel(t_channel);


        // MDS
        MdsDescriptor t_Mds(MDS_DESCRIPTOR_HANDLE);
        t_Mds.setType(CodedValue("MDC_DEV_DOCU_POSE_MDS")
            .addConceptDescription(LocalizedText().setRef("uri/to/file.txt").setLang("en")))
            .setMetaData(
                MetaData().addManufacturer(LocalizedText().setRef(SDCLib::Config::STR_SURGITAIX))
                          .setModelNumber("1")
                          .addModelName(LocalizedText().setRef("EndoTAIX"))
                          .addSerialNumber(SDCLib::Config::CURRENT_C_YEAR))
            .addVmd(t_vmd);


        // create and add description
		MdDescription mdDescription;
		mdDescription.addMdsDescriptor(t_Mds);

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
    const std::size_t m_eprID;

    NumericMetricDescriptor getMetricDescriptor;

};

} /* namespace MultiSDC */
} /* namespace Tests */
} /* namespace SDCLib */

struct FixtureConnectionLostSDC : Tests::AbstractOSCLibFixture {
	FixtureConnectionLostSDC() : AbstractOSCLibFixture("FixtureConnectionLostSDC", OSELib::LogLevel::Notice, SDCLib::Config::SDC_ALLOWED_PORT_START) {}
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

            std::atomic<bool> handlerVisited = ATOMIC_VAR_INIT(false);

	    private:
	    	Data::SDC::SDCConsumer & consumer;
	    };

	    DebugOut(DebugOut::Default, std::cout, m_details.testName) << "Waiting for the Providers to startup...";

		CONSTEXPR_MACRO std::size_t t_providerCount{10};
		std::vector<std::shared_ptr<Tests::ConnectionLostSDC::OSCPTestDeviceProvider>> providers;
		std::vector<std::string> t_providerEPRs;

        auto t_SDCInstance = getSDCInstance();

		for (std::size_t i = 0; i < t_providerCount; ++i) {
			auto p = std::make_shared<Tests::ConnectionLostSDC::OSCPTestDeviceProvider>(t_SDCInstance, i);
			providers.push_back(p);
			t_providerEPRs.push_back(p->getEndpointReference());
            // Startup
            p->startup();
            Poco::Thread::sleep(1000);
		}
		// Wait for startup...
        Poco::Thread::sleep(5000);


        DebugOut(DebugOut::Default, std::cout, m_details.testName) << "Starting discovery test...";

        OSELib::SDC::ServiceManager sm(t_SDCInstance);
        auto tl_consumers{sm.discoverOSCP()};

        // Found all the providers?
        bool foundAll = true;
        for (const auto & providerEPR : t_providerEPRs) {
        	bool foundOne = false;
			for (const auto & consumer : tl_consumers) {
				if (consumer->getEndpointReference() == providerEPR) {
					foundOne = true;
					break;
				}
			}
			if (!foundOne) {
				DebugOut(DebugOut::Default, std::cout, m_details.testName) << "Missing epr: " << providerEPR << std::endl;
			}
			foundAll &= foundOne;
        }
        CHECK_EQUAL(true, foundAll);

        std::vector<std::shared_ptr<MyConnectionLostHandler>> connectionLostHanders;
        for (auto& nextConsumer : tl_consumers) {
            DebugOut(DebugOut::Default, std::cout, m_details.testName) << "Found " << nextConsumer->getEndpointReference();

            if (std::find(t_providerEPRs.begin(), t_providerEPRs.end(), nextConsumer->getEndpointReference()) == t_providerEPRs.end()) {
        		// not our own provider => skip
        		continue;
        	}

            auto myHandler = std::make_shared<MyConnectionLostHandler>(*nextConsumer.get());
        	nextConsumer->setConnectionLostHandler(myHandler.get());
        	connectionLostHanders.push_back(myHandler);
        }

        DebugOut(DebugOut::Default, std::cout, m_details.testName) << "Shutting down all Providers...\n";
        for (auto next : providers) {
        	next->shutdown();
        }

        // Wait long enough for all to get a call... FIXME: Sometimes this test fails. Just because the timings arent correct.
        DebugOut(DebugOut::Default, std::cout, m_details.testName) << "Waiting for connectionLostHanders...\n";
        Poco::Thread::sleep(8000);

        DebugOut(DebugOut::Default, std::cout, m_details.testName) << "Checking connectionLostHandlers...\n";

        for (auto & handler : connectionLostHanders) {
        	CHECK_EQUAL(true, handler->handlerVisited);
        }
	}
	catch (...) {
		DebugOut(DebugOut::Default, std::cout, m_details.testName) << "Unknown exception occurred!";
	}
	DebugOut(DebugOut::Default, std::cout, m_details.testName) << "CloseLogFile...\n";
	DebugOut::closeLogFile();
    DebugOut(DebugOut::Default, std::cout, m_details.testName) << "\nFinished Test!\n";
}
}
