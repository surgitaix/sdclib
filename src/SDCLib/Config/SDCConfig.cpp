#include "SDCLib/Config/SDCConfig.h"

#include "SDCLib/Config/NetworkConfig.h"

using namespace SDCLib;
using namespace SDCLib::Config;

SDCConfig::SDCConfig()
 : m_networkConfig([]() { return std::make_shared<Config::NetworkConfig>(); } ())
{
}
SDCConfig::SDCConfig(NetworkConfig_shared_ptr p_portConfig)
 : m_networkConfig(p_portConfig)
{
    assert(m_networkConfig != nullptr);
}
SDCConfig::SDCConfig(NetworkConfig_shared_ptr p_portConfig, SSLConfig_shared_ptr p_SSLConfig)
 : m_networkConfig(p_portConfig)
 , m_SSLConfig(p_SSLConfig)
{
    assert(m_networkConfig != nullptr);
    assert(m_SSLConfig != nullptr);
}
SDCConfig_shared_ptr SDCConfig::randomMDPWSConfig(SDCConfig_shared_ptr p_config)
{
    assert(p_config);
    // Copy SDCConfig and shuffle the MDPWS Port of Network Part
    auto t_copy = std::make_shared<SDCConfig>(*p_config);
    if(!t_copy->getNetworkConfig()->_shuffleMDPWSPort()) {
        return nullptr;
    }
    return t_copy;
}
