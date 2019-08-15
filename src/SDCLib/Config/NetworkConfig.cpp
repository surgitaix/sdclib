#include "SDCLib/Config/NetworkConfig.h"


#include <Poco/Net/ServerSocket.h>

#include <iostream>

using namespace SDCLib;
using namespace SDCLib::Config;


NetworkConfig::NetworkConfig()
: OSELib::WithLogger(OSELib::Log::BASE)
{
    // TODO: PortList
}

bool NetworkConfig::bindToDefaultNetworkInterface(bool p_useAsMDPWS)
{
    assert(!isBound());

    // NOTE: Temporary Hack qnd
    // Bind to the first that is not the loopback device and matches our criteria
    auto tl_interfaces = Poco::Net::NetworkInterface::list(true, true);
    for (auto t_interface : tl_interfaces) {
        if (t_interface.isLoopback()) { continue; }
        if (!t_interface.address().isUnicast()) { continue; }

        // Must at least support one of the following
        if (!t_interface.supportsIPv4() && !t_interface.supportsIPv6()) { continue; }

        // Matching the criteria?
        if((getIP4enabled() && t_interface.supportsIPv4()) || (getIP6enabled() && t_interface.supportsIPv6())) {
            // Try to bind (else try the next one)
            if(bindToInterface(t_interface.adapterName(), p_useAsMDPWS)) {
                return true;
            }
        }
    }
    return false;
}
bool NetworkConfig::bindToInterface(const std::string& ps_networkInterfaceName, bool p_useAsMDPWS)
{
    assert(!ps_networkInterfaceName.empty());

    // Is there an Interface with the given name running?
    // Qnd for now...
    auto tl_interfaces = Poco::Net::NetworkInterface::list(true, true);
    for (const auto & t_interface : tl_interfaces) {

        // We got a match! - qnd: just take the first one
        if (t_interface.adapterName() == ps_networkInterfaceName) {

            // Already bound to it?
            if (_networkInterfaceBoundTo(ps_networkInterfaceName)) {
                return false;
            }

            // Must at least support one of the following
            if (!t_interface.supportsIPv4() && !t_interface.supportsIPv6()) {
                return false;
            }
            // Lock
            std::lock_guard<std::mutex> t_lock(m_mutex);

            // Create the struct
            auto t_if = std::make_shared<NetInterface>(t_interface);

            // Grab the address

            // IPv4? Else disable!
            if (t_interface.supportsIPv4()) {
                IPAddress t_IPv4;
                try {
                    t_interface.firstAddress(t_IPv4, Poco::Net::IPAddress::IPv4);
                    t_if->m_IPv4 = t_IPv4;
                }
                catch (...) { setIP4enabled(false); }
            }
            else { setIP4enabled(false); }


            // IPv6? Else disable!
            if (t_interface.supportsIPv6()) {
                IPAddress t_IPv6;
                try {
                    t_interface.firstAddress(t_IPv6, Poco::Net::IPAddress::IPv6);
                    t_if->m_IPv6 = t_IPv6;
                }
                catch (...) { setIP6enabled(false); }
            }
            else { setIP6enabled(false); }

            // Add
            ml_networkInterfaces.push_back(t_if);
            // This is the primary MDPWS Interface (only if none has been set yet!)
            if(p_useAsMDPWS && (m_MDPWSInterface == nullptr)) {

                m_MDPWSInterface = t_if;

                // Check on the port
                auto t_result = findFreePort();
                if(t_result.first) {
                    m_MDPWSPort = t_result.second;
                }
                else {
                    throw std::runtime_error("NO FREE PORTS FOUND!");
                }

                log_debug([&] { return "SDCInstance bound to: " +  m_MDPWSInterface->m_name +  " ("
                		+ (m_MDPWSInterface->m_if.supportsIPv4() ? "IPv4: " + m_MDPWSInterface->m_IPv4.toString() : "")
						+ ((m_MDPWSInterface->m_if.supportsIPv4() && m_MDPWSInterface->m_if.supportsIPv6()) ? "|" : "")
						+ (m_MDPWSInterface->m_if.supportsIPv6() ? "IPv6: "+  m_MDPWSInterface->m_IPv6.toString() : "")
                		+ ").\n";
                });
            }
            else {
                // Not set yet! - Emit a Warning
                if(m_MDPWSInterface == nullptr) {
                	log_warning([] { return "Warning: No Primary MDPWS Binding Interface set yet!"; });
                }
            }
            return true;
        }
    }
    return false;
}
bool NetworkConfig::_networkInterfaceBoundTo(std::string ps_adapterName) const
{
    assert(!ps_adapterName.empty());

    for (auto t_if : ml_networkInterfaces) {
        if (t_if->m_name == ps_adapterName) {
            return true;
        }
    }
    return false;
}
bool NetworkConfig::isBound() const
{
    return !ml_networkInterfaces.empty();
}

bool NetworkConfig::belongsTo(Poco::Net::IPAddress p_IP) const
{
    // Unicast
    for (const auto& t_if : ml_networkInterfaces)
    {
        // Default to IPv4
        auto t_networkInterfaceIP = t_if->m_IPv4;
        // IPv6?
        if(t_if->m_if.supportsIPv6() && (p_IP.family() == Poco::Net::AddressFamily::IPv6)) {
            t_networkInterfaceIP = t_if->m_IPv6;
        }
        /*auto t_subnetMask = t_if->m_if.subnetMask();
        t_networkInterfaceIP.mask(t_subnetMask);
        p_IP.mask(t_subnetMask);*/
        // Compare - Found one?
        if (t_networkInterfaceIP == p_IP) {
            return true;
        }
    }
    // No match
    return false;
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
    Poco::Net::SocketAddress socketAddress(0);
    Poco::Net::ServerSocket socket(socketAddress);
    unsigned short portNumber = socket.address().port();
    socket.close();
    return {true, portNumber};
}
bool NetworkConfig::_shuffleMDPWSPort()
{
    std::size_t t_tries = 0;
    std::size_t t_triesMax = 10000;

    auto t_newPort = m_MDPWSPort;
    while (t_newPort == m_MDPWSPort) {
        auto t_result = findFreePort();
        // Found one -> Set it
        if(t_result.first) {
            t_newPort = t_result.second;
        }
        // Dont loop forever!
        if(t_tries++ >= t_triesMax) {
            return false;
        }
    }
    // Set it
    m_MDPWSPort = t_newPort;
    return true;
}
