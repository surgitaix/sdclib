#ifdef WIN32
#define NOMINMAX
#endif

#include "SDCLib/SDCInstance.h"

#include "SDCLib/SDCLibrary.h"

#include <iostream>

using namespace SDCLib;

std::atomic_uint SDCInstance::s_IDcounter = ATOMIC_VAR_INIT(0);

SDCInstance::SDCInstance(SDCPort p_MDPWSPort, bool p_init)
 : m_MDPWSPort(p_MDPWSPort)
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

    // Just a simple name
    m_ID = "SDCInstance-" + std::to_string(s_IDcounter++);

    // ...

    m_init = true;
    return true;
}

bool SDCInstance::bindToDefaultNetworkInterface(bool p_useAsMDPWS)
{
    if (!isInit()) {
        return false;
    }
    // NOTE: Temporary Hack qnd
    // Bind to the first that is not the loopback device and matches our criteria
    auto tl_interfaces = Poco::Net::NetworkInterface::list(true, true);
    for (auto t_interface : tl_interfaces) {
        if (t_interface.isLoopback()) { continue; }
        if (!t_interface.address().isUnicast()) { continue; }

        // Must at least support one of the following
        if (!t_interface.supportsIPv4() && !t_interface.supportsIPv6()) { continue; }

        // Matching the criteria?
        if((m_IP4enabled && t_interface.supportsIPv4()) || (m_IP6enabled && t_interface.supportsIPv6())) {
            // Try to bind (else try the next one)
            if(bindToNetworkInterface(t_interface.adapterName(), p_useAsMDPWS)) {
                return true;
            }
        }
    }
    return false;
}
bool SDCInstance::bindToNetworkInterface(const std::string& ps_networkInterfaceName, bool p_useAsMDPWS)
{
    if (!isInit()) {
        return false;
    }

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
				//both IPv4 and IPv6 are enabled by default, so disabled means it was configured by the application in that way, so we should respect this here
            if ((!t_interface.supportsIPv4() && !getIP6enabled()) || (!t_interface.supportsIPv6() && !getIP4enabled())) {
                continue;	//the adapter might be listed multiple times (under Windows) so we need to search on.
            }
            // Lock
            std::lock_guard<std::mutex> t_lock(m_mutex);

            // Create the struct
            auto t_if = std::make_shared<NetInterface>(t_interface);

            // Grab the address

            // IPv4? Else disable!
            if (t_interface.supportsIPv4() && getIP4enabled()) {
                IPAddress t_IPv4;
                try {
                    t_interface.firstAddress(t_IPv4, Poco::Net::IPAddress::IPv4);
                    t_if->m_IPv4 = t_IPv4;
                }
                catch (...) { }
            }
            else { setIP4enabled(false); }


            // IPv6? Else disable!
            if (t_interface.supportsIPv6() && getIP6enabled()) {
                IPAddress t_IPv6;
                try {
                    t_interface.firstAddress(t_IPv6, Poco::Net::IPAddress::IPv6);
                    t_if->m_IPv6 = t_IPv6;
                }
                catch (...) { }
            }
            else { setIP6enabled(false); }

            // Add
            ml_networkInterfaces.push_back(t_if);

            std::cout << "\nSDCInstance bound to: " << t_if->m_name;

            // Print additional information
            std::cout << " (";
            auto t_count = 0;
            if(t_interface.supportsIPv4()) { std::cout << "IPv4: " << t_if->m_IPv4; t_count++; }
            if(t_interface.supportsIPv6()) { if(t_count > 0) { std::cout <<","; }
                std::cout << "IPv6: " << t_if->m_IPv6;
            }

            std::cout << ").\n";
            // This is the primary MDPWS Interface (only if none has been set yet!)
            if(p_useAsMDPWS && (m_MDPWSInterface == nullptr)) {

                m_MDPWSInterface = t_if;

                // Check on the port
                if(m_MDPWSPort == 0) {
                    std::cout << "WARNING! NO MDPWS PORT SPECIFIED. TAKING RANDOM PORT..." << std::endl;
                    auto t_result = findFreePort();
                    if(t_result.first) {
                        m_MDPWSPort = t_result.second;
                    }
                    else {
                        throw std::runtime_error("NO FREE PORTS FOUND!");
                    }
                }
                std::cout << "MDPWS Interface set: " << t_if->m_name << " on Port " << m_MDPWSPort << std::endl;
            }
            else {
                // Not set yet! - Emit a Warning
                if(m_MDPWSInterface == nullptr) {
                    std::cout << "Warning: No Primary MDPWS Binding Interface set yet!" << std::endl;
                }
            }
            return true;
        }
    }
    return false;
}
bool SDCInstance::_networkInterfaceBoundTo(std::string ps_adapterName) const
{
    if (!isInit()) {
        return false;
    }
    assert(!ps_adapterName.empty());

    for (auto t_if : ml_networkInterfaces) {
        if (t_if->m_name == ps_adapterName) {
            return true;
        }
    }
    return false;
}
bool SDCInstance::isBound() const
{
    if (!isInit()) {
        return false;
    }
    return !ml_networkInterfaces.empty();
}

bool SDCInstance::setDiscoveryConfigV4(std::string ps_IP_MC, SDCPort p_portMC, std::string ps_IP_Streaming, SDCPort p_portStreaming)
{
    assert(!ps_IP_MC.empty());
    assert(p_portMC != 0);
    assert(!ps_IP_Streaming.empty());
    assert(p_portStreaming != 0);

    // Quick check if the passed values are valid
    Poco::Net::IPAddress t_MC, t_STR;
    if (!Poco::Net::IPAddress::tryParse(ps_IP_MC, t_MC) || !Poco::Net::IPAddress::tryParse(ps_IP_Streaming, t_STR)) {
        return false;
    }
    // AddressFamily
    if ((t_MC.family() != Poco::Net::AddressFamily::IPv4) || (t_STR.family() != Poco::Net::AddressFamily::IPv4)) {
        return false;
    }

    // Set
    m_MULTICAST_IPv4 = ps_IP_MC;
    m_PORT_MULTICASTv4 = p_portMC;
    m_STREAMING_IPv4 = ps_IP_Streaming;
    m_PORT_STREAMINGv4 = p_portStreaming;
    return true;
}
bool SDCInstance::setDiscoveryConfigV6(std::string ps_IP_MC, SDCPort p_portMC, std::string ps_IP_Streaming, SDCPort p_portStreaming)
{
    assert(!ps_IP_MC.empty());
    assert(p_portMC != 0);
    assert(!ps_IP_Streaming.empty());
    assert(p_portStreaming != 0);

    // Quick check if the passed values are valid
    Poco::Net::IPAddress t_MC, t_STR;
    if (!Poco::Net::IPAddress::tryParse(ps_IP_MC, t_MC) || !Poco::Net::IPAddress::tryParse(ps_IP_Streaming, t_STR)) {
        return false;
    }
    // AddressFamily
    if ((t_MC.family() != Poco::Net::AddressFamily::IPv6) || (t_STR.family() != Poco::Net::AddressFamily::IPv6)) {
        return false;
    }

    // Set
    m_MULTICAST_IPv6 = ps_IP_MC;
    m_PORT_MULTICASTv6 = p_portMC;
    m_STREAMING_IPv6 = ps_IP_Streaming;
    m_PORT_STREAMINGv6 = p_portStreaming;
    return true;
}

bool SDCInstance::belongsToSDCInstance(Poco::Net::IPAddress p_IP) const
{
    if (!isInit()) {
        return false;
    }

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
std::chrono::milliseconds SDCInstance::getDiscoveryTime() const
{
    return m_discoveryTime;
}
bool SDCInstance::setDiscoveryTime(std::chrono::milliseconds p_time)
{
    assert(p_time != std::chrono::milliseconds::zero());

    // Dont change after initialization?
    if (isInit()) {
        return false;
    }
    // Set it
    m_discoveryTime = p_time;
    return true;
}
void SDCInstance::dumpPingManager(std::unique_ptr<OSELib::DPWS::PingManager> pingManager)
{
    std::lock_guard<std::mutex> t_lock(m_mutex);
    _latestPingManager = std::move(pingManager);
}
std::pair<bool, SDCPort> SDCInstance::findFreePort() const
{
    // TODO: Currently just random...
    auto t_reserved = 1024;
    // Seed
    std::srand(std::chrono::system_clock::now().time_since_epoch().count());
    auto t_mod = std::numeric_limits<SDCPort>::max() - t_reserved;
    return {true, std::rand()%t_mod + t_reserved};
}
