#include "OSCLib/SDCInstance.h"

using namespace SDCLib;

SDCInstance::SDCInstance(unsigned int portStart, unsigned int portRange, const list<Poco::Net::NetworkInterface> networkInterfacesList) :
			WithLogger(OSELib::Log::BASE),
			m_init(false)
{
	for (const auto interface : networkInterfacesList) {
		m_networkInterfacesList.push_back(interface);
	}

    // Create the Portlist
    createPortList(portStart, portRange);
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

}

void SDCInstance::sealAndInit()
{

    if (isInit()) {
        return;
    }
    // ...
    std::lock_guard<std::mutex> t_lock(m_mutex);
    m_init = true;
}


list<Poco::Net::NetworkInterface> SDCInstance::getNetworkInterfacesList() {
	return m_networkInterfacesList;
}

void SDCInstance::createPortList(unsigned int start, unsigned int range)
{
    // No well-known ports allowed!
    if (!(start > 1024)) {
    	log_error([&] { return "Established ports (> 1024) are not allowed."; });
    	return;
    };

    // Lock
    std::lock_guard<std::mutex> t_lock(m_mutex);

    m_reservedPorts.clear();
    for (auto i = start; i < start + range; ++i) {
        m_reservedPorts.push_back(i);
    }
    m_availablePorts = m_reservedPorts;
}



//bool SDCInstance::bindToDefaultNetworkInterface()
//{
//    if (!isInit()) {
//        return false;
//    }
//    // NOTE: Temporary Hack qnd
//    // Bind to the first that is not the loopback device
//    auto tl_interfaces = Poco::Net::NetworkInterface::list(true, true);
//    for (auto t_interface : tl_interfaces) {
//        if (t_interface.isLoopback()) {
//            continue;
//        }
//        return bindToInterface(t_interface.adapterName());
//    }
//    return false;
//}
//bool SDCInstance::bindToInterface(const std::string& ps_networkInterfaceName)
//{
//    if (!isInit()) {
//        return false;
//    }
//
//    assert(!ps_networkInterfaceName.empty());
//
//
//    // Is there an Interface with the given name running?
//    // Qnd for now...
//    auto tl_interfaces = Poco::Net::NetworkInterface::list(true, true);
//    for (auto t_interface : tl_interfaces) {
//
//        if (t_interface.adapterName() == ps_networkInterfaceName) {
//            // Lock
//            std::lock_guard<std::mutex> t_lock(m_mutex);
//            // Grab the address
//            m_bindAddress = t_interface.address();
//            m_networkInterfaceName = ps_networkInterfaceName;
//            m_init = true;
//
//            //std::cout << "SDCInstance bound to: " << ms_networkInterfaceName << " (" << m_bindAddress << ").\n";
//            return true;
//        }
//    }
//    return false;
//}
//

bool SDCInstance::setPorts(list<unsigned int> portList) {
	if (isInit()) {
		return false;
	}

	for (const auto port : portList) {
		m_availablePorts.clear();
		m_availablePorts.push_back(port);
	}
	return true;
}

//unsigned int SDCInstance::extractFreePort()
//{
//    // Lock
//    std::lock_guard<std::mutex> t_lock(m_mutex);
//
//    // Grab the value
//    const unsigned int t_result = m_availablePorts.front();
//
//    // Remove it from the collection
//    m_availablePorts.pop_front();
//
//    // Return it
//    return t_result;
//}
//void SDCInstance::returnPortToPool(unsigned int p_port)
//{
//    // Lock
//    std::lock_guard<std::mutex> t_lock(m_mutex);
//    auto t_resultReserved = std::find(m_reservedPorts.begin(), m_reservedPorts.end(), p_port);
//    auto t_resultAvailable = std::find(m_availablePorts.begin(), m_availablePorts.end(), p_port);
//
//    // 2 Requirements: Inside reserved list, but not already returned! - Quick fix
//    // Performance issue, maybe add a "returned" flag to the reservedPorts - list...(use of "using" keyword etc.) -> One lookup only
//    if ((t_resultReserved != m_reservedPorts.end()) && (t_resultAvailable == m_availablePorts.end())) {
//        m_availablePorts.push_back(p_port);
//    }
//}
//
//
//// Forward to SDCLibrary
//bool SDCInstance::getIP4enabled() const
//{
//    // Just forward it
//    return SDCLibrary::getInstance().getIP4enabled();
//}
//void SDCInstance::setIP4enabled(bool p_set) const
//{
//    // Just forward it
//    SDCLibrary::getInstance().setIP4enabled(p_set);
//}
//bool SDCInstance::getIP6enabled() const
//{
//    // Just forward it
//    return SDCLibrary::getInstance().getIP6enabled();
//}
//void SDCInstance::setIP6enabled(bool p_set) const
//{
//    // Just forward it
//    SDCLibrary::getInstance().setIP6enabled(p_set);
//}
//// DiscoveryTime
//int SDCInstance::getDiscoveryTime() const
//{
//    // Just forward it
//    return SDCLibrary::getInstance().getDiscoveryTime();
//}
//
//bool SDCInstance::setDiscoveryTime(int p_discoveryTimeMilSec) const
//{
//    // Dont change after initialization?
//    if (isInit()) {
//        return false;
//    }
//
//
//    // Just forward it
//    SDCLibrary::getInstance().setDiscoveryTime(p_discoveryTimeMilSec);
//    return true;
//}

//void SDCInstance::dumpPingManager(std::unique_ptr<OSELib::DPWS::PingManager> pingManager)
//{
//    std::lock_guard<std::mutex> t_lock(m_mutex);
//    _latestPingManager = std::move(pingManager);
//}
