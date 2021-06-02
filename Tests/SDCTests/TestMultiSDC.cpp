
#include "SDCLib/SDCInstance.h"
#include "SDCLib/Data/SDC/SDCConsumer.h"
#include "SDCLib/Data/SDC/SDCProvider.h"
#include "SDCLib/Data/SDC/MDIB/ChannelDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/CodedValue.h"
#include "SDCLib/Data/SDC/MDIB/MdsDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/LocalizedText.h"
#include "SDCLib/Data/SDC/MDIB/NumericMetricDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/MetaData.h"
#include "SDCLib/Data/SDC/MDIB/VmdDescriptor.h"
#include "SDCLib/Util/DebugOut.h"
#include "../AbstractSDCLibFixture.h"
#include "../UnitTest++/src/UnitTest++.h"

#include "OSELib/SDC/ServiceManager.h"

using namespace SDCLib;
using namespace SDCLib::Util;
using namespace SDCLib::Data::SDC;

namespace SDCLib {
namespace Tests {
namespace MultiSDC {

class SDCTestDeviceProvider
{
public:

    SDCTestDeviceProvider(SDCInstance_shared_ptr p_SDCInstance, const std::size_t p_eprID, const std::size_t p_metricCount)
    : m_sdcProvider(p_SDCInstance)
    , m_eprID(p_eprID)
    , m_metricCount(p_metricCount)
    {

    	m_sdcProvider.setEndpointReferenceByName(std::string{"UDI_"} + std::to_string(m_eprID));

        Dev::DeviceCharacteristics devChar;
		devChar.addFriendlyName("en", "Test TestMultiSDC " + std::to_string(m_eprID));
		m_sdcProvider.setDeviceCharacteristics(devChar);

        // Channel
        ChannelDescriptor testChannel{std::string{"channel_handle"} + std::to_string(m_eprID)};
        testChannel.setSafetyClassification(SafetyClassification::MedA);
        for (std::size_t i = 0; i < m_metricCount; ++i)
        {
        	NumericMetricDescriptor t_numericMetric{"handle_cur" + std::to_string(i),
        			CodedValue(CodeIdentifier{"MDCX_CODE_ID_WEIGHT"}),
					MetricCategory::Msrmt,
					MetricAvailability::Cont,
					1.0};
    		testChannel.addMetric(t_numericMetric);
        }

        // VMD
        VmdDescriptor t_vmd{std::string{"vmd_handle_"} + std::to_string(m_eprID)};
        t_vmd.addChannel(testChannel);

        // MDS
        MdsDescriptor t_Mds{std::string{"mds_handle_"} + std::to_string(m_eprID)};
        t_Mds.setType(CodedValue{"MDC_DEV_DOCU_POSE_MDS"}
            .addConceptDescription(LocalizedText{"DOCU POSE"}.setLang("en")))
            .setMetaData(
                MetaData().addManufacturer(LocalizedText{SDCLib::Config::STR_SURGITAIX})
                          .setModelNumber("1")
                          .addModelName(LocalizedText{"EndoTAIX"})
                          .addSerialNumber(SDCLib::Config::CURRENT_C_YEAR))
            .addVmd(t_vmd);

        // create and add description
		MdDescription mdDescription;
		mdDescription.addMdsDescriptor(t_Mds);

		m_sdcProvider.setMdDescription(mdDescription);
    }

    void startup()
    {
    	m_sdcProvider.startup();
    }

    const std::string getEndpointReference() const
    {
    	return m_sdcProvider.getEndpointReference();
    }

private:

    SDCProvider m_sdcProvider;

    const std::size_t m_eprID{};
    const std::size_t m_metricCount{};
};

}
}
}

struct FixtureMultiSDC : Tests::AbstractSDCLibFixture
{
	FixtureMultiSDC()
	: AbstractSDCLibFixture("FixtureMultiSDC", OSELib::LogLevel::Notice)
	{ }
};


SUITE(SDC)
{
TEST_FIXTURE(FixtureMultiSDC, MultiSDC)
{
	try
	{
		// Specify number of providers and metrics per provider to spin up
		const std::size_t providerCount{10};
		const std::size_t metricCount{10};

		std::vector<std::shared_ptr<Tests::MultiSDC::SDCTestDeviceProvider>> t_testProviders;
		std::vector<std::string> t_testProviderEPRs;

        DebugOut(DebugOut::Default, std::cout, m_details.testName) << "Waiting for the Providers to startup...";
		for (std::size_t i = 0; i < providerCount; ++i)
		{
			auto t_provider = std::make_shared<Tests::MultiSDC::SDCTestDeviceProvider>(createSDCInstance(), i, metricCount);
			t_testProviders.push_back(t_provider);
			t_testProviderEPRs.push_back(t_provider->getEndpointReference());
            t_provider->startup();
		}

        DebugOut(DebugOut::Default, std::cout, m_details.testName) << "Starting discovery test...";

        OSELib::SDC::ServiceManager sm{createSDCInstance()};
        auto t_discoveredConsumers{sm.discoverAndConnect()};

        // Search for Providers by EPR
        bool t_allFound{true};
        for (const auto& providerEPR : t_testProviderEPRs)
        {
        	bool t_oneFound{false};
			for (const auto& consumer : t_discoveredConsumers)
			{
				if (consumer->getEndpointReference() == providerEPR)
				{
					t_oneFound = true;
					break;
				}
			}
			if (!t_oneFound)
			{
				DebugOut(DebugOut::Default, std::cout, m_details.testName) << "Missing epr: " << providerEPR << std::endl;
			}
			t_allFound &= t_oneFound;
        }
        CHECK_EQUAL(true, t_allFound);

        for (const auto& t_consumer : t_discoveredConsumers)
        {
            DebugOut(DebugOut::Default, std::cout, m_details.testName) << "Found " << t_consumer->getEndpointReference();
        }
        DebugOut(DebugOut::Default, std::cout, m_details.testName) << "Waiting...";

        for (auto & t_consumer : t_discoveredConsumers)
        {
        	t_consumer->disconnect();
        }
        // Delete all Consumer
        t_discoveredConsumers.clear();

        // Delete all Provider
        t_testProviders.clear();

    }
	catch (char const* exc)
	{
		DebugOut(DebugOut::Default, std::cerr, m_details.testName) << exc;
	}
	catch (...)
	{
		DebugOut(DebugOut::Default, std::cerr, m_details.testName) << "Unknown exception occurred!";
	}
	DebugOut::closeLogFile();
}
}
