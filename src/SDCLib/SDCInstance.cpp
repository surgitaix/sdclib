#include "SDCLib/SDCInstance.h"

#include "SDCLib/SDCLibrary.h"

#include "SDCLib/Config/SDCConfig.h"
#include "SDCLib/Config/NetworkConfig.h"

#include <Poco/Net/ServerSocket.h>


#include <iostream>

using namespace SDCLib;

std::atomic_uint SDCInstance::s_IDcounter = ATOMIC_VAR_INIT(0);

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
SDCInstance::SDCInstance(SDCPort, bool p_init)
 : m_SDCConfig([]() { return std::make_shared<Config::SDCConfig>(); } ())
{
    std::cout << "SDCInstance(SDCPort, bool) Constructor will be removed in future versions." << std::endl;
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

    _latestPingManager.reset();
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

void SDCInstance::dumpPingManager(std::unique_ptr<OSELib::DPWS::PingManager> pingManager)
{
    std::lock_guard<std::mutex> t_lock(m_mutex);
    _latestPingManager = std::move(pingManager);
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
