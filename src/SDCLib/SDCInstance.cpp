#include "SDCLib/SDCInstance.h"

#include "SDCLib/SDCLibrary.h"

#include "SDCLib/Config/SDCConfig.h"
#include "SDCLib/Config/NetworkConfig.h"

#include "OSELib/SDC/SDCConstants.h"
#include "OSELib/Helper/WithLogger.h"

#include <Poco/Net/ServerSocket.h>
#include <Poco/UUIDGenerator.h>
#include <Poco/SHA1Engine.h>


#include <iostream>

using namespace SDCLib;

std::atomic_uint SDCInstance::s_IDcounter{0};

SDCInstance::SDCInstance(bool p_init)
 : m_SDCConfig([]() { return std::make_shared<Config::SDCConfig>(); } ())
{
    if(p_init) {
        init();
    }
}
SDCInstance::SDCInstance(Config::SDCConfig_shared_ptr p_config, bool p_init)
 : m_SDCConfig(p_config)
{
    if(p_init) {
        init();
    }
}

SDCInstance::~SDCInstance()
{
    _cleanup();
}

void SDCInstance::_cleanup()
{
    // Nothing to cleanup
    if (!isInit()) {
        return;
    }
    // Lock
    std::lock_guard<std::mutex> t_lock(m_mutex);

    // ...Cleanup....

    m_latestPingManager.reset();
    // ....

}

bool SDCInstance::init()
{
    if (isInit()) {
        return false;
    }

    // Startup if not done yet
    if (!SDCLibrary::getInstance().isInitialized()) {
        SDCLibrary::getInstance().startup();
    }

    // Init Xerces
    xercesc::XMLPlatformUtils::Initialize();

    // Just a simple name
    m_ID = "SDCInstance-" + std::to_string(s_IDcounter++);

    // ...

    m_init = true;
    return true;
}

Config::SDCConfig_shared_ptr SDCInstance::getSDCConfig() const
{
    assert(m_SDCConfig != nullptr);
    return m_SDCConfig;
}
Config::NetworkConfig_shared_ptr SDCInstance::getNetworkConfig() const
{
    assert(m_SDCConfig != nullptr);
    return m_SDCConfig->getNetworkConfig();
}
Config::SSLConfig_shared_ptr SDCInstance::getSSLConfig() const
{
    assert(m_SDCConfig != nullptr);
    return m_SDCConfig->getSSLConfig();
}
bool SDCInstance::initSSL(const Poco::Net::Context::VerificationMode p_modeClient, const Poco::Net::Context::VerificationMode p_modeServer)
{
    assert(m_SDCConfig != nullptr);
    return m_SDCConfig->getSSLConfig()->init(p_modeClient, p_modeServer);
}

bool SDCInstance::bindToDefaultNetworkInterface(bool p_useAsMDPWS)
{
    if (!isInit()) {
        return false;
    }
    assert(m_SDCConfig != nullptr);
    return m_SDCConfig->getNetworkConfig()->bindToDefaultNetworkInterface(p_useAsMDPWS);
}
bool SDCInstance::bindToInterface(const std::string& ps_networkInterfaceName, bool p_useAsMDPWS)
{
    if (!isInit()) {
        return false;
    }
    assert(m_SDCConfig != nullptr);
    return m_SDCConfig->getNetworkConfig()->bindToInterface(ps_networkInterfaceName, p_useAsMDPWS);
}
bool SDCInstance::_networkInterfaceBoundTo(std::string ps_adapterName) const
{
    if (!isInit()) {
        return false;
    }
    assert(m_SDCConfig != nullptr);
    return m_SDCConfig->getNetworkConfig()->_networkInterfaceBoundTo(ps_adapterName);
}

void SDCInstance::dumpPingManager(std::unique_ptr<OSELib::DPWS::PingManager> p_pingManager)
{
    std::lock_guard<std::mutex> t_lock(m_mutex);
    m_latestPingManager = std::move(p_pingManager);
}

// IP4 / IP6 - Forward to the Config
bool SDCInstance::getIP4enabled() const
{
    assert(m_SDCConfig != nullptr);
    return m_SDCConfig->getNetworkConfig()->getIP4enabled();
}
bool SDCInstance::getIP6enabled() const
{
    assert(m_SDCConfig != nullptr);
    return m_SDCConfig->getNetworkConfig()->getIP6enabled();
}
void SDCInstance::setIP4enabled(bool p_set)
{
    assert(m_SDCConfig != nullptr);
    m_SDCConfig->getNetworkConfig()->setIP4enabled(p_set);
}
void SDCInstance::setIP6enabled(bool p_set)
{
    assert(m_SDCConfig != nullptr);
    m_SDCConfig->getNetworkConfig()->setIP6enabled(p_set);
}
bool SDCInstance::setDiscoveryTime(std::chrono::milliseconds p_time)
{
    // Dont change after it was Initialized
    if (isInit()) {
        return false;
    }
    assert(m_SDCConfig->getNetworkConfig() != nullptr);
    m_SDCConfig->getNetworkConfig()->setDiscoveryTime(p_time);

    return true;
}
std::chrono::milliseconds SDCInstance::getDiscoveryTime() const
{
    assert(m_SDCConfig != nullptr);
    return m_SDCConfig->getNetworkConfig()->getDiscoveryTime();
}

bool SDCInstance::isUUID(const std::string& p_UUID)
{
	// NOTE: Maybe this needs to be revised?

	Poco::UUID t_UUID;
	return t_UUID.tryParse(p_UUID);
}

std::string SDCInstance::calcUUID()
{
	Poco::SHA1Engine t_engineSHA1;
	auto t_UUID = Poco::UUIDGenerator::defaultGenerator().create();
	return std::string(t_UUID.toString());
}
std::string SDCInstance::calcUUIDv5(std::string p_name, bool p_prefix)
{
	assert(!p_name.empty());

	Poco::SHA1Engine t_engineSHA1;
	auto t_UUIDv5 = Poco::UUIDGenerator::defaultGenerator().createFromName(Poco::UUID(OSELib::SDC::UUID_SDC_BASE_NAMESPACE),
																			p_name,
																			t_engineSHA1,
																			Poco::UUID::Version::UUID_NAME_BASED_SHA1);
	return std::string((p_prefix) ? OSELib::SDC::UUID_SDC_PREFIX : std::string("")) + t_UUIDv5.toString();
}

std::string SDCInstance::calcMSGID()
{
	return std::string(OSELib::SDC::UUID_SDC_PREFIX + SDCInstance::calcUUID());
}

SDCLib::SDCInstance_shared_ptr SDCInstance::createSDCInstance(std::string p_networkInterface)
{
    // Init SDCInstance
    // Create a new SDCInstance (dont init yet) - give it a new port (just increment)
    auto t_SDCInstance = std::make_shared<SDCInstance>(false);

    // Init
    if(!t_SDCInstance->init()) {
    	OSELib::Helper::WithLogger(OSELib::Log::BASE).log_error([]{ return "Failed to init SDCInstance"; });
        return nullptr;
    }

    // Bind to network interface if specified
    if(!p_networkInterface.empty()) {
    	if(t_SDCInstance->bindToInterface(p_networkInterface, true)) {
    		return t_SDCInstance;
    	}
    	OSELib::Helper::WithLogger(OSELib::Log::BASE).log_error([&]{ return "Failed to bind SDCInstance to " + p_networkInterface + "!"; });
    	return nullptr;
    }

	// Bind it to interface that matches the internal criteria (usually the first enumerated)
	if(t_SDCInstance->bindToDefaultNetworkInterface()) {
		return t_SDCInstance;
	}

	// In any other case
	OSELib::Helper::WithLogger(OSELib::Log::BASE).log_error([]{ return "Failed to bind SDCInstance to default network interface!"; });
    return nullptr;
}
