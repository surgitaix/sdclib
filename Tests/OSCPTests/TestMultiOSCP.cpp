
#include "OSCLib/OSCLibrary.h"
#include "OSCLib/Data/OSCP/OSCPConsumer.h"
#include "OSCLib/Data/OSCP/OSCPProvider.h"
#include "OSCLib/Data/OSCP/MDIB/ChannelDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/MdsDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/LocalizedText.h"
#include "OSCLib/Data/OSCP/MDIB/MdDescription.h"
#include "OSCLib/Data/OSCP/MDIB/NumericMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/SystemContextDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/MetaData.h"
#include "OSCLib/Data/OSCP/MDIB/VmdDescriptor.h"
#include "OSCLib/Util/DebugOut.h"
#include "../AbstractOSCLibFixture.h"
#include "../UnitTest++/src/UnitTest++.h"

#include "OSELib/OSCP/ServiceManager.h"

#include "Poco/Mutex.h"
#include "Poco/ScopedLock.h"

using namespace OSCLib;
using namespace OSCLib::Util;
using namespace OSCLib::Data::OSCP;

namespace OSCLib {
namespace Tests {
namespace MultiOSCP {

class OSCPTestDeviceProvider {
public:

    OSCPTestDeviceProvider(const std::size_t number, const std::size_t metricCount) : oscpProvider(), epr(number), metrics(metricCount) {

    	oscpProvider.setEndpointReference(std::string("UDI_") + std::to_string(epr));

        // Location context
        SystemContextDescriptor sc;

        // Channel
        ChannelDescriptor testChannel;
        testChannel.setSafetyClassification(SafetyClassification::MedA);
        for (std::size_t i = 0; i < metrics; i++) {
        	NumericMetricDescriptor nmd;
    		nmd.setMetricCategory(MetricCategory::Msrmt)
               .setMetricAvailability(MetricAvailability::Cont)
               .setType(CodedValue()
            		   .addConceptDescription(LocalizedText().setRef("uri/to/file.txt").setLang("en"))
            		   .setCode("MDCX_CODE_ID_WEIGHT"))
    	       .setHandle("handle_cur" + std::to_string(i));
    		testChannel.addMetric(nmd);
        }

        // VMD
        VmdDescriptor testVmd;
        testVmd.addChannel(testChannel);

        // MDS
        MdsDescriptor mds;
        mds.setMetaData(
        		MetaData().addManufacturer(LocalizedText().setRef("SurgiTAIX AG"))
        		.setModelNumber("1")
        		.addModelName(LocalizedText().setRef("EndoTAIX"))
        		.addSerialNumber("1234"))
			.setSystemContext(sc)
			.setType(CodedValue()
			   .addConceptDescription(LocalizedText().setRef("uri/to/file.txt").setLang("en"))
			   .setCode("MDCX_CODE_ID_MDS"));

        mds.addVmd(testVmd);

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
    OSCPProvider oscpProvider;

    const std::size_t epr;
    const std::size_t metrics;
};

} /* namespace MultiOSCP */
} /* namespace Tests */
} /* namespace OSCLib */

struct FixtureMultiOSCP : Tests::AbstractOSCLibFixture {
	FixtureMultiOSCP() : AbstractOSCLibFixture("FixtureMultiOSCP", OSELib::LogLevel::NOTICE, 8000) {}
};

SUITE(OSCP) {
TEST_FIXTURE(FixtureMultiOSCP, multioscp)
{
	try
	{
		constexpr std::size_t providerCount(10);
		constexpr std::size_t metricCount(10);

		std::vector<std::shared_ptr<Tests::MultiOSCP::OSCPTestDeviceProvider>> providers;
		std::vector<std::string> providerEPRs;

		for (std::size_t i = 0; i < providerCount; i++) {
			std::shared_ptr<Tests::MultiOSCP::OSCPTestDeviceProvider> p(new Tests::MultiOSCP::OSCPTestDeviceProvider(i, metricCount));
			providers.push_back(p);
			p->startup();
			providerEPRs.emplace_back(p->getEndpointReference());
		}

        Poco::Thread::sleep(2000);

        DebugOut(DebugOut::Default, std::cout, "multioscp") << "Starting discovery test...";

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

        for (auto & nextConsumer : consumers) {
        	DebugOut(DebugOut::Default, std::cout, "multioscp") << "Found " << nextConsumer->getEndpointReference();
        }

        Poco::Thread::sleep(2000);

        for (auto & next : consumers) {
        	next->disconnect();
        }
        for (auto & next : providers) {
        	next->shutdown();
        }
    } catch (char const* exc) {
		DebugOut(DebugOut::Default, std::cerr, "multioscp") << exc;
	} catch (...) {
		DebugOut(DebugOut::Default, std::cerr, "multioscp") << "Unknown exception occurred!";
	}
	DebugOut::closeLogFile();
}
}
