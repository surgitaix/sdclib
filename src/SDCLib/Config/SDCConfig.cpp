#include "SDCLib/Config/SDCConfig.h"

#include "SDCLib/Config/NetworkConfig.h"
#include "SDCLib/Config/SSLConfig.h"

#include <assert.h>

using namespace SDCLib;
using namespace SDCLib::Config;

SDCConfig::SDCConfig()
 : m_networkConfig(std::make_shared<Config::NetworkConfig>())
 , m_SSLConfig(std::make_shared<Config::SSLConfig>())
{
}
SDCConfig::SDCConfig(NetworkConfig_shared_ptr p_portConfig)
 : m_networkConfig(p_portConfig)
 , m_SSLConfig([]() { return std::make_shared<Config::SSLConfig>(); } ())
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


SDCConfig::SDCConfig(const SDCConfig& p_obj)
{
	m_networkConfig = std::make_shared<Config::NetworkConfig>(*p_obj.getNetworkConfig());
	m_SSLConfig = std::make_shared<Config::SSLConfig>(*p_obj.getSSLConfig());
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
