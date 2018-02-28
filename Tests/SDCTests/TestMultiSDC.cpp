
#include "OSCLib/SDCLibrary.h"
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

    OSCPTestDeviceProvider(const std::size_t number, const std::size_t metricCount) : oscpProvider(), epr(number), metrics(metricCount) {

    	oscpProvider.setEndpointReference(std::string("UDI_") + std::to_string(epr));

        // Location context
        SystemContextDescriptor sc("systemcontext_handle_" + number);

        // Channel
        ChannelDescriptor testChannel("channel_handle" + number);
        testChannel.setSafetyClassification(SafetyClassification::MedA);
        for (std::size_t i = 0; i < metrics; i++) {
        	NumericMetricDescriptor nmd("handle_cur" + std::to_string(i), CodedValue(CodeIdentifier("MDCX_CODE_ID_WEIGHT")), MetricCategory::Msrmt, MetricAvailability::Cont, 1.0);
    		testChannel.addMetric(nmd);
        }

        // VMD
        VmdDescriptor testVmd("vmd_handle_" + number);
        testVmd.addChannel(testChannel);

        // MDS
        MdsDescriptor mds("mds_handle_" + number);
        mds.setMetaData(
        		MetaData().addManufacturer(LocalizedText().setRef("SurgiTAIX AG"))
        		.setModelNumber("1")
        		.addModelName(LocalizedText().setRef("EndoTAIX"))
        		.addSerialNumber("1234"))
			.setSystemContext(sc)
			.setType(CodedValue(CodeIdentifier("MDCX_CODE_ID_MDS"))
			   .addConceptDescription(LocalizedText().setRef("uri/to/file.txt").setLang("en")));
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
    SDCProvider oscpProvider;

    const std::size_t epr;
    const std::size_t metrics;
};

} /* namespace MultiSDC */
} /* namespace Tests */
} /* namespace SDCLib */

struct FixtureMultiOSCP : Tests::AbstractOSCLibFixture {
	FixtureMultiOSCP() : AbstractOSCLibFixture("FixtureMultiOSCP", OSELib::LogLevel::Notice, 8000) {}
};

SUITE(OSCP) {
TEST_FIXTURE(FixtureMultiOSCP, multioscp)
{
	try
	{
		CONSTEXPR_MACRO std::size_t providerCount(10);
		CONSTEXPR_MACRO std::size_t metricCount(10);

		std::vector<std::shared_ptr<Tests::MultiSDC::OSCPTestDeviceProvider>> providers;
		std::vector<std::string> providerEPRs;

		for (std::size_t i = 0; i < providerCount; i++) {
			std::shared_ptr<Tests::MultiSDC::OSCPTestDeviceProvider> p(new Tests::MultiSDC::OSCPTestDeviceProvider(i, metricCount));
			providers.push_back(p);
			p->startup();
			providerEPRs.emplace_back(p->getEndpointReference());
		}

        Poco::Thread::sleep(2000);

        DebugOut(DebugOut::Default, std::cout, "multioscp") << "Starting discovery test...";

        OSELib::SDC::ServiceManager sm;
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
