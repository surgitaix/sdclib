#include "OSCLib/SDCInstance.h"

#include "OSCLib/SDCLibrary.h"


#include <iostream>

using namespace SDCLib;

unsigned SDCInstance::s_IDcounter = 1;

SDCInstance::SDCInstance(bool p_init)
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

    // Clear the ports
    m_reservedPorts.clear();
    m_availablePorts.clear();


    _latestPingManager.reset();
    // ....

}

bool SDCInstance::init()
{
    if (isInit()) {
        return false;
    }

    // Create the Portlist
    createPortLists(m_portStart, m_portRange);

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

bool SDCInstance::bindToDefaultNetworkInterface()
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
            if(bindToInterface(t_interface.adapterName())) {
                return true;
            }
        }
    }
    return false;
}
bool SDCInstance::bindToInterface(const std::string& ps_networkInterfaceName)
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
                catch (...) { }
            }
            else { setIP4enabled(false); }


            // IPv6? Else disable!
            if (t_interface.supportsIPv6()) {
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

            std::cout << "\nSDCInstance bound to: " << t_if->m_name << " (" << t_if->m_IPv4 << ", " << t_if->m_IPv6 << ").\n";
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

    // Only for IPv4!
    if (p_IP.family() != Poco::Net::IPAddress::IPv4) {
        return false;
    }

    // Multicast?
    if (p_IP == Poco::Net::IPAddress(m_MULTICAST_IPv4)) {
        return true;
    }

    // Unicast
    for (auto& t_if : ml_networkInterfaces) {
        auto t_subnetMask = t_if->m_if.subnetMask();
        auto t_networkInterface = t_if->m_IPv4;

        // First Convert both (address & mask)
        t_networkInterface.mask(t_subnetMask);
        p_IP.mask(t_subnetMask);
        // Compare - Found one?
        if (t_networkInterface == p_IP) {
            return true;
        }
    }
    // No match
    return false;
}

bool SDCInstance::setPortConfig(SDCPort p_start, SDCPort p_range)
{
    if(isInit()) {
        return false;
    }

    assert(p_start != 0);
    assert(p_range != 0);

    m_portStart = p_start;
    m_portRange = p_range;
    return true;
}
void SDCInstance::createPortLists(SDCPort p_start, SDCPort p_range)
{
    // No well-known ports allowed!
    assert(p_start > 1024);
    assert(p_range != 0);

    // Lock
    std::lock_guard<std::mutex> t_lock(m_mutex);

    m_reservedPorts.clear();

    // Make sure the loop wont run over
    std::size_t t_start = p_start;
    std::size_t t_range = p_range;

    auto t_end = t_start + t_range;
    assert(t_end < std::numeric_limits<unsigned short>::max());

    for (auto i = t_start; i < t_end; ++i) {
        m_reservedPorts.emplace_back(static_cast<SDCPort>(i));
    }
    m_availablePorts = m_reservedPorts;
}
bool SDCInstance::extractFreePort(SDCPort& p_port)
{
    // Lock
    std::lock_guard<std::mutex> t_lock(m_mutex);

    // No ports available!
    if (m_availablePorts.empty()) {
        return false;
    }

    // Grab the value
    p_port = m_availablePorts.front();

    // Remove it from the collection
    m_availablePorts.pop_front();
    return true;
}
void SDCInstance::returnPortToPool(SDCPort p_port)
{
    // Lock
    std::lock_guard<std::mutex> t_lock(m_mutex);
    auto t_resultReserved = std::find(m_reservedPorts.begin(), m_reservedPorts.end(), p_port);
    auto t_resultAvailable = std::find(m_availablePorts.begin(), m_availablePorts.end(), p_port);

    // 2 Requirements: Inside reserved list, but not already returned! - Quick fix
    // Performance issue, maybe add a "returned" flag to the reservedPorts - list...(use of "using" keyword etc.) -> One lookup only
    if ((t_resultReserved != m_reservedPorts.end()) && (t_resultAvailable == m_availablePorts.end())) {
        m_availablePorts.push_back(p_port);
    }
}


// Forward to SDCLibrary
bool SDCInstance::getIP4enabled() const
{
    return m_IP4enabled;
}
bool SDCInstance::setIP4enabled(bool p_set)
{
    // Set it
    m_IP4enabled = p_set;
    return true;
}
bool SDCInstance::getIP6enabled() const
{
    return m_IP6enabled;
}
bool SDCInstance::setIP6enabled(bool p_set)
{
    // Set it
    m_IP6enabled = p_set;
    return true;
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
