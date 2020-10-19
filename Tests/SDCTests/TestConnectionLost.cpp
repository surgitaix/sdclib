
#include <thread>
#include <atomic>

#include "SDCLib/SDCInstance.h"
#include "SDCLib/Data/SDC/SDCConsumer.h"
#include "SDCLib/Data/SDC/SDCConsumerConnectionLostHandler.h"
#include "SDCLib/Data/SDC/SDCProvider.h"
#include "SDCLib/Data/SDC/MDIB/ChannelDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/CodedValue.h"
#include "SDCLib/Data/SDC/MDIB/MdsDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/LocalizedText.h"
#include "SDCLib/Data/SDC/MDIB/MdDescription.h"
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
namespace ConnectionLostSDC {

const std::string VMD_DESCRIPTOR_HANDLE{"ConnectionLost_vmd"};
const std::string CHANNEL_DESCRIPTOR_HANDLE{"ConnectionLost_channel"};
const std::string MDS_DESCRIPTOR_HANDLE{"ConnectionLost_mds"};

const std::string HANDLE_GET_METRIC{"handle_get"};


class SDCTestDeviceProvider
{
public:

    SDCTestDeviceProvider(SDCInstance_shared_ptr p_SDCInstance, const std::size_t p_eprID)
        : m_sdcProvider(p_SDCInstance)
        , m_eprID(p_eprID)
        , m_getMetricDescriptor(HANDLE_GET_METRIC,
				CodedValue{"MDCX_EXAMPLE_GET"},
				MetricCategory::Set,
				MetricAvailability::Cont,
				1)
        {

    	m_sdcProvider.setEndpointReferenceByName(std::string{"UDI_"} + std::to_string(m_eprID));

		Dev::DeviceCharacteristics devChar;
		devChar.addFriendlyName("en", "Test ConnectionLost " + std::to_string(m_eprID));
		m_sdcProvider.setDeviceCharacteristics(devChar);

        // Channel
        ChannelDescriptor t_channel{CHANNEL_DESCRIPTOR_HANDLE};
        t_channel
            .setSafetyClassification(SafetyClassification::MedB)
            .addMetric(m_getMetricDescriptor);


        // VMD
        VmdDescriptor t_vmd{VMD_DESCRIPTOR_HANDLE};
        t_vmd.addChannel(t_channel);

        // MDS
        MdsDescriptor t_Mds{MDS_DESCRIPTOR_HANDLE};
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

    std::string getEndpointReference() const
    {
    	return m_sdcProvider.getEndpointReference();
    }


private:
    // Provider object
    SDCProvider m_sdcProvider;
    const std::size_t m_eprID{};

    NumericMetricDescriptor m_getMetricDescriptor;

};

} /* namespace MultiSDC */
} /* namespace Tests */
} /* namespace SDCLib */

struct FixtureConnectionLostSDC : Tests::AbstractSDCLibFixture
{
	FixtureConnectionLostSDC()
	: AbstractSDCLibFixture("FixtureConnectionLostSDC", OSELib::LogLevel::Notice)
	{ }
};

class MyConnectionLostHandler : public Data::SDC::SDCConsumerConnectionLostHandler
{
public:
    MyConnectionLostHandler(Data::SDC::SDCConsumer& p_consumer)
        : m_consumer(p_consumer)
    {
        // Set this as the current ConnectionLostHandler
        m_consumer.setConnectionLostHandler(this);
    }
    ~MyConnectionLostHandler()
    {
        // Unset the Handler
        m_consumer.setConnectionLostHandler(nullptr);
    }

    void onConnectionLost() override
    {
        DebugOut logoutput(DebugOut::Default, std::cout, "ConnectionLost");
        logoutput << "Connection lost, disconnecting... ";
        m_consumer.disconnect();
        logoutput << "disconnected." << std::endl;
        m_handlerVisited = true;
    }

    std::atomic<bool> m_handlerVisited{ false };

private:
    Data::SDC::SDCConsumer& m_consumer;
};

SUITE(SDC)
{
TEST_FIXTURE(FixtureConnectionLostSDC, ConnectionLost)
{
	try
	{
	    DebugOut(DebugOut::Default, std::cout, m_details.testName) << "Waiting for the Providers to startup...";

		const auto t_providerCount{10};
		std::vector<std::shared_ptr<Tests::ConnectionLostSDC::SDCTestDeviceProvider>> t_testProviders;
		std::vector<std::string> t_testProviderEPRs;

		for (auto i = 0; i < t_providerCount; ++i)
		{
			auto p = std::make_shared<Tests::ConnectionLostSDC::SDCTestDeviceProvider>(createSDCInstance(), i);
			t_testProviders.push_back(p);
			t_testProviderEPRs.push_back(p->getEndpointReference());
            // Startup
            p->startup();
		}

        DebugOut(DebugOut::Default, std::cout, m_details.testName) << "Starting discovery test [Timeout: " << SDCLib::Config::SDC_DISCOVERY_TIMEOUT_MS << " ms] ...";

        OSELib::SDC::ServiceManager sm{createSDCInstance()};
        auto t_discoverdConsumers = sm.discover();

        // Found all the providers?
        bool t_allFound{true};
        for (const auto& t_epr : t_testProviderEPRs)
        {
        	bool t_oneFound{false};
			for (const auto& t_consumer : t_discoverdConsumers)
			{
				if (t_consumer->getEndpointReference() == t_epr)
				{
					t_oneFound = true;
					break;
				}
			}
			if (!t_oneFound)
			{
				DebugOut(DebugOut::Default, std::cout, m_details.testName) << "Missing epr: " << t_epr << std::endl;
			}
			t_allFound &= t_oneFound;
        }
        CHECK_EQUAL(true, t_allFound);

        std::vector<std::shared_ptr<MyConnectionLostHandler>> t_connectionLostHanders;
        for (const auto& t_nextConsumer : t_discoverdConsumers)
        {
            DebugOut(DebugOut::Default, std::cout, m_details.testName) << "Found " << t_nextConsumer->getEndpointReference();
            if (std::find(t_testProviderEPRs.begin(), t_testProviderEPRs.end(), t_nextConsumer->getEndpointReference()) == t_testProviderEPRs.end())
            {
        		// not our own provider => skip
        		continue;
        	}
            auto myHandler = std::make_shared<MyConnectionLostHandler>(*t_nextConsumer);
        	t_connectionLostHanders.push_back(myHandler);
        }
        DebugOut(DebugOut::Default, std::cout, m_details.testName) << "Shutting down all Providers...\n";
        t_testProviders.clear();

        // Wait long enough for all to get a call...

        // Long enough that all ConnectionLost Handlers have the time to get triggered...
        const auto t_waitTime{SDCLib::Config::SDC_CONNECTION_TIMEOUT_MS * 2};
        DebugOut(DebugOut::Default, std::cout, m_details.testName) << "Waiting " << t_waitTime << " ms for connectionLostHanders...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<std::size_t>(t_waitTime)));

        DebugOut(DebugOut::Default, std::cout, m_details.testName) << "Checking connectionLostHandlers...\n";

        for (auto& t_handler : t_connectionLostHanders)
        {
            CHECK_EQUAL(true, t_handler->m_handlerVisited);
        }
        t_connectionLostHanders.clear();
	}
	catch (...)
	{
		DebugOut(DebugOut::Default, std::cout, m_details.testName) << "Unknown exception occurred!";
	}
	DebugOut(DebugOut::Default, std::cout, m_details.testName) << "CloseLogFile...\n";
    DebugOut(DebugOut::Default, std::cout, m_details.testName) << "\nFinished Test!\n";
	DebugOut::closeLogFile();
}
}
