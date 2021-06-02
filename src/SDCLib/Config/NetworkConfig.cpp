#include "SDCLib/Config/NetworkConfig.h"


#include <Poco/Net/ServerSocket.h>

#include <assert.h>

using namespace SDCLib;
using namespace SDCLib::Config;

NetworkConfig::NetworkConfig()
    : OSELib::Helper::WithLogger(OSELib::Log::BASE)
{
    // TODO: PortList
}


NetworkConfig::NetworkConfig(const NetworkConfig& p_obj)
    : OSELib::Helper::WithLogger(OSELib::Log::BASE)
{
    m_networkInterfaces = p_obj.m_networkInterfaces;
    m_MDPWSInterface = p_obj.m_MDPWSInterface;
    m_MDPWSPort = p_obj.m_MDPWSPort;


    m_IP4enabled = p_obj.getIP4enabled();
    m_IP6enabled = p_obj.getIP6enabled();
    m_discoveryTime = p_obj.getDiscoveryTime();


    m_MULTICAST_IPv4 = p_obj.m_MULTICAST_IPv4;
    m_MULTICAST_IPv6 = p_obj.m_MULTICAST_IPv6;
    m_STREAMING_IPv4 = p_obj.m_STREAMING_IPv4;
    m_STREAMING_IPv6 = p_obj.m_STREAMING_IPv6;
    m_PORT_MULTICASTv4 = p_obj.m_PORT_MULTICASTv4;
    m_PORT_MULTICASTv6 = p_obj.m_PORT_MULTICASTv6;
    m_PORT_STREAMINGv4 = p_obj.m_PORT_STREAMINGv4;
    m_PORT_STREAMINGv6 = p_obj.m_PORT_STREAMINGv6;
}


bool NetworkConfig::bindToDefaultNetworkInterface(bool p_useAsMDPWS)
{
    assert(!isBound());

    // NOTE: Temporary Hack qnd
    // Bind to the first that is not the loopback device and matches our criteria
    auto tl_interfaces = Poco::Net::NetworkInterface::list(true, true);
    for(auto t_interface : tl_interfaces)
    {
        if(t_interface.isLoopback())
        {
            continue;
        }
        if(!t_interface.address().isUnicast())
        {
            continue;
        }

        // Must at least support one of the following
        if(!t_interface.supportsIPv4() && !t_interface.supportsIPv6())
        {
            continue;
        }

        // Matching the criteria?
        if((getIP4enabled() && t_interface.supportsIPv4()) || (getIP6enabled() && t_interface.supportsIPv6()))
        {
            // Try to bind (else try the next one)
            if(bindToInterface(t_interface.adapterName(), p_useAsMDPWS))
            {
                return true;
            }
        }
    }
    return false;
}
bool NetworkConfig::bindToInterface(const std::string& p_networkInterfaceName, bool p_useAsMDPWS)
{
    assert(!p_networkInterfaceName.empty());

    // Already bound to it?
    if(_networkInterfaceBoundTo(p_networkInterfaceName))
    {
        return false;
    }

    // Is there an Interface with the given name running?
    // Qnd for now...
    auto tl_interfaces = Poco::Net::NetworkInterface::list(true, true);
    for(const auto& t_interface : tl_interfaces)
    {
        // We got a match! - qnd: just take the first one
        if(t_interface.adapterName() == p_networkInterfaceName)
        {
            // Must at least support one of the following
            if(!t_interface.supportsIPv4() && !t_interface.supportsIPv6())
            {
                continue;
            }

            // Lock
            std::lock_guard<std::mutex> t_lock(m_mutex);
            auto t_validIP = false;

            // Create the struct
            auto t_if = std::make_shared<NetInterface>(t_interface);

            // Grab the address
            // IPv4?
            if(t_interface.supportsIPv4() && getIP4enabled())
            {
                IPAddress t_IPv4;
                try
                {
                    t_interface.firstAddress(t_IPv4, Poco::Net::IPAddress::IPv4);
                    t_if->m_IPv4 = t_IPv4;
                    t_validIP = true;
                }
                catch(...)
                {
                }
            }

            // IPv6?
            if(t_interface.supportsIPv6() && getIP6enabled())
            {
                IPAddress t_IPv6;
                try
                {
                    t_interface.firstAddress(t_IPv6, Poco::Net::IPAddress::IPv6);
                    t_if->m_IPv6 = t_IPv6;
                    t_validIP = true;
                }
                catch(...)
                {
                    // Could not get a valid address -> try next interface
                    continue;
                }
            }

            // Do we have a valid Interface (at least one valid IP)
            if(!t_validIP)
            {
                continue;
            }

            // Add
            m_networkInterfaces.push_back(t_if);

            // This is the primary MDPWS Interface (only if none has been set yet!)
            if(p_useAsMDPWS && (m_MDPWSInterface == nullptr))
            {
                m_MDPWSInterface = t_if;

                // This is the only interface so far -> Disable IPv4 / IPv6
                if(m_networkInterfaces.size() == 1)
                {
                    // IPv4
                    if((getIP4enabled()) && (!m_MDPWSInterface->m_if.supportsIPv4()))
                    {
                        log_notice([]() { return "MDPWSInterface does not support IPv4. Disabling..."; });
                        setIP4enabled(false);
                    }
                    // IPv6
                    if((getIP6enabled()) && (!m_MDPWSInterface->m_if.supportsIPv6()))
                    {
                        log_notice([]() { return "MDPWSInterface does not support IPv6. Disabling..."; });
                        setIP6enabled(false);
                    }
                }

                // Check on the port
                auto t_result = findFreePort();
                if(t_result.first)
                {
                    m_MDPWSPort = t_result.second;
                }
                else
                {
                    throw std::runtime_error("NO FREE PORTS FOUND!");
                }

                log_notice([&] {
                    return "SDCInstance bound to: " + m_MDPWSInterface->m_name + " ("
                           + (getIP4enabled() ? "IPv4: " + m_MDPWSInterface->m_IPv4.toString() : "")
                           + ((getIP4enabled() && getIP6enabled()) ? "|" : "")
                           + (getIP6enabled() ? "IPv6: " + m_MDPWSInterface->m_IPv6.toString() : "") + ").\n";
                });
            }
            else
            {
                // Not set yet! - Emit a Warning
                if(m_MDPWSInterface == nullptr)
                {
                    log_warning([] { return "Warning: No Primary MDPWS Binding Interface set yet!"; });
                }
            }
            return true;
        }
    }
    return false;
}
bool NetworkConfig::_networkInterfaceBoundTo(std::string p_adapterName) const
{
    assert(!p_adapterName.empty());

    for(auto interface : m_networkInterfaces)
    {
        if(interface->m_name == p_adapterName)
        {
            return true;
        }
    }
    return false;
}
bool NetworkConfig::isBound() const
{
    return !m_networkInterfaces.empty();
}

// DiscoveryTime
std::chrono::milliseconds NetworkConfig::getDiscoveryTime() const
{
    return m_discoveryTime;
}
void NetworkConfig::setDiscoveryTime(std::chrono::milliseconds p_time)
{
    assert(p_time != std::chrono::milliseconds::zero());
    // Set it
    m_discoveryTime = p_time;
}
std::pair<bool, SDCPort> NetworkConfig::findFreePort() const
{
    // TODO: Rework for Portrange
    // TODO: Consider Exceptions instead of pair!
    Poco::Net::SocketAddress socketAddress{0};
    Poco::Net::ServerSocket socket{socketAddress};
    auto portNumber = socket.address().port();
    socket.close();
    return {true, portNumber};
}
bool NetworkConfig::_shuffleMDPWSPort()
{
    std::size_t tries = 0;
    std::size_t triesMax = 10000;

    auto newPort = m_MDPWSPort;
    while(newPort == m_MDPWSPort)
    {
        auto result = findFreePort();
        // Found one -> Set it
        if(result.first)
        {
            newPort = result.second;
        }
        // Dont loop forever!
        if(tries++ >= triesMax)
        {
            return false;
        }
    }
    // Set it
    m_MDPWSPort = newPort;
    return true;
}
