
#include "OSCLib/SDCInstance.h"
#include "OSCLib/Data/SDC/SDCConsumer.h"
#include "OSCLib/Data/SDC/SDCProvider.h"
#include "OSCLib/Data/SDC/MDIB/ChannelDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/CodedValue.h"
#include "OSCLib/Data/SDC/MDIB/MdsDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/LocalizedText.h"
#include "OSCLib/Data/SDC/MDIB/MdDescription.h"
#include "OSCLib/Data/SDC/MDIB/NumericMetricDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/SystemContextDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/MetaData.h"
#include "OSCLib/Data/SDC/MDIB/VmdDescriptor.h"
#include "OSCLib/Util/DebugOut.h"
#include "../AbstractOSCLibFixture.h"
#include "../UnitTest++/src/UnitTest++.h"

#include "OSELib/SDC/ServiceManager.h"

#include "Poco/Mutex.h"
#include "Poco/ScopedLock.h"

using namespace SDCLib;
using namespace SDCLib::Util;
using namespace SDCLib::Data::SDC;

namespace SDCLib {
namespace Tests {
namespace MultiSDC {

class OSCPTestDeviceProvider {
public:

    OSCPTestDeviceProvider(SDCInstance_shared_ptr p_SDCInstance, const std::size_t number, const std::size_t metricCount)
    : sdcProvider(p_SDCInstance)
    , m_eprID(number)
    , metrics(metricCount)
    {

        sdcProvider.setEndpointReference(std::string("UDI_") + std::to_string(m_eprID));

        Dev::DeviceCharacteristics devChar;
		devChar.addFriendlyName("en", "Test TestMultiSDC " + std::to_string(m_eprID));
		sdcProvider.setDeviceCharacteristics(devChar);

        // Channel
        ChannelDescriptor testChannel(std::string("channel_handle") + std::to_string(m_eprID));
        testChannel.setSafetyClassification(SafetyClassification::MedA);
        for (std::size_t i = 0; i < metrics; i++) {
        	NumericMetricDescriptor nmd("handle_cur" + std::to_string(i), CodedValue(CodeIdentifier("MDCX_CODE_ID_WEIGHT")), MetricCategory::Msrmt, MetricAvailability::Cont, 1.0);
    		testChannel.addMetric(nmd);
        }

        // VMD
        VmdDescriptor t_vmd(std::string("vmd_handle_") + std::to_string(m_eprID));
        t_vmd.addChannel(testChannel);

        // MDS
        MdsDescriptor t_Mds(std::string("mds_handle_") + std::to_string(m_eprID));
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
    SDCProvider sdcProvider;

    const std::size_t m_eprID;
    const std::size_t metrics;
};

} /* namespace MultiSDC */
} /* namespace Tests */
} /* namespace SDCLib */

struct FixtureMultiOSCP : Tests::AbstractOSCLibFixture {
	FixtureMultiOSCP() : AbstractOSCLibFixture("FixtureMultiOSCP", OSELib::LogLevel::Notice, SDCLib::Config::SDC_ALLOWED_PORT_START + 40) {}
};


SUITE(OSCP) {
TEST_FIXTURE(FixtureMultiOSCP, MultiSDC)
{
	try
	{
        auto t_SDCInstance = getSDCInstance();

		CONSTEXPR_MACRO std::size_t providerCount(10);
		CONSTEXPR_MACRO std::size_t metricCount(10);

		std::vector<std::shared_ptr<Tests::MultiSDC::OSCPTestDeviceProvider>> providers;
		std::vector<std::string> providerEPRs;

        DebugOut(DebugOut::Default, std::cout, m_details.testName) << "Waiting for the Providers to startup...";
		for (std::size_t i = 0; i < providerCount; i++) {
			std::shared_ptr<Tests::MultiSDC::OSCPTestDeviceProvider> p(new Tests::MultiSDC::OSCPTestDeviceProvider(t_SDCInstance, i, metricCount));
			providers.push_back(p);
            providerEPRs.push_back(p->getEndpointReference());
			p->startup();
            Poco::Thread::sleep(500);
		}
        // Wait for startup...
        Poco::Thread::sleep(5000);

        DebugOut(DebugOut::Default, std::cout, m_details.testName) << "Starting discovery test...";

        OSELib::SDC::ServiceManager sm(t_SDCInstance);
        auto tl_consumers(sm.discoverOSCP());

        bool foundAll = true;
        for (const auto & providerEPR : providerEPRs) {
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

        for (auto & nextConsumer : tl_consumers) {
            DebugOut(DebugOut::Default, std::cout, m_details.testName) << "Found " << nextConsumer->getEndpointReference();
        }

        DebugOut(DebugOut::Default, std::cout, m_details.testName) << "Waiting...";

        for (auto & next : tl_consumers) {
        	next->disconnect();
        }
        for (auto & next : providers) {
        	next->shutdown();
        }
        Poco::Thread::sleep(2000);
    } catch (char const* exc) {
		DebugOut(DebugOut::Default, std::cerr, m_details.testName) << exc;
	} catch (...) {
		DebugOut(DebugOut::Default, std::cerr, m_details.testName) << "Unknown exception occurred!";
	}
	DebugOut::closeLogFile();
}
}
