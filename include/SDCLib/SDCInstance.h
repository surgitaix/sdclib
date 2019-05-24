/**
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  *
  */

/**
 *  @file SDCInstance.h
 *  @project SDCLib
 *  @date 14.02.2019
 *  @author baumeister
 *  @copyright (c) SurgiTAIX AG
 *
 */
#ifndef SDCLIB_SDCINSTANCE_H
#define SDCLIB_SDCINSTANCE_H

#include "Prerequisites.h"
#include "config/config.h"

#include "OSELib/DPWS/DPWS11Constants.h"
#include "OSELib/DPWS/PingManager.h"

#include <Poco/Net/NetworkInterface.h>
#include <Poco/Net/SocketDefs.h>


namespace SDCLib
{
    const Poco::Net::IPAddress SUBNET_CLASS_A = Poco::Net::IPAddress("255.0.0.0");
    const Poco::Net::IPAddress SUBNET_CLASS_B = Poco::Net::IPAddress("255.255.0.0");
    const Poco::Net::IPAddress SUBNET_CLASS_C = Poco::Net::IPAddress("255.255.255.0");

    using IPAddress = Poco::Net::IPAddress;
    using IPAddressList = std::vector<IPAddress>;

    using SDCInstanceID = std::string;

    class NetInterface {
    public:
        std::string m_name;
        IPAddress m_IPv4;
        IPAddress m_IPv6;
        Poco::Net::NetworkInterface m_if;

        bool SO_REUSEADDR_FLAG = true;
        bool SO_REUSEPORT_FLAG = false;


        NetInterface (const Poco::Net::NetworkInterface& p_if)
          : m_if(p_if) {
              m_name = m_if.adapterName();

        }
      };

    using NetInterface_shared_ptr = std::shared_ptr<NetInterface>;
    using NI_List = std::vector<NetInterface_shared_ptr>;

    class SDCInstance
    {
    private:

        static std::atomic_uint s_IDcounter;
        SDCInstanceID m_ID;

        mutable std::mutex m_mutex;

        std::atomic<bool> m_init = ATOMIC_VAR_INIT(false);
        NI_List ml_networkInterfaces;
        NetInterface_shared_ptr m_MDPWSInterface = nullptr;
        SDCPort m_MDPWSPort = Config::SDC_DEFAULT_MDPWS_PORT;

        std::atomic<bool> m_IP4enabled = ATOMIC_VAR_INIT(true);
        std::atomic<bool> m_IP6enabled = ATOMIC_VAR_INIT(true);

        std::chrono::milliseconds m_discoveryTime = std::chrono::milliseconds(Config::SDC_DISCOVERY_TIMEOUT_MS);

        std::unique_ptr<OSELib::DPWS::PingManager> _latestPingManager;


        // Network settings
        std::string m_MULTICAST_IPv4 = OSELib::UDP_MULTICAST_DISCOVERY_IP_V4;
        std::string m_MULTICAST_IPv6 = OSELib::UDP_MULTICAST_DISCOVERY_IP_V6;
        std::string m_STREAMING_IPv4 = OSELib::UDP_MULTICAST_STREAMING_IP_V4;
        std::string m_STREAMING_IPv6 = OSELib::UDP_MULTICAST_STREAMING_IP_V6;

        SDCPort m_PORT_MULTICASTv4 = OSELib::UPD_MULTICAST_DISCOVERY_PORT;
        SDCPort m_PORT_MULTICASTv6 = OSELib::UPD_MULTICAST_DISCOVERY_PORT;
        SDCPort m_PORT_STREAMINGv4 = OSELib::UPD_MULTICAST_STREAMING_PORT;
        SDCPort m_PORT_STREAMINGv6 = OSELib::UPD_MULTICAST_STREAMING_PORT;

    public:

        SDCInstance(SDCPort p_MDPWSPort = Config::SDC_DEFAULT_MDPWS_PORT, bool p_init = true);

        // Special Member Functions
        SDCInstance(const SDCInstance& p_obj) = delete;
        SDCInstance(SDCInstance&& p_obj) = delete;
        SDCInstance& operator=(const SDCInstance& p_obj) = delete;
        SDCInstance& operator=(SDCInstance&& p_obj) = delete;
        ~SDCInstance();

        SDCInstanceID getID() const { return m_ID; }

        bool init();
        bool isInit() const { return m_init; }

        bool bindToDefaultNetworkInterface(bool p_useAsMDPWS = true);
        bool bindToNetworkInterface(const std::string& ps_networkInterfaceName, bool p_useAsMDPWS = false);
        NI_List getNetworkInterfaces() const { return ml_networkInterfaces; }
        size_t getNumNetworkInterfaces() const { return ml_networkInterfaces.size(); }
        bool _networkInterfaceBoundTo(std::string ps_adapterName) const;
        bool isBound() const;

        // Note: Can be nullptr!
        NetInterface_shared_ptr getMDPWSInterface() { return m_MDPWSInterface; }
        // Listening Port of the HTTP Server
        SDCPort getMDPWSPort() { return m_MDPWSPort; }

        // Internal usage
        std::string _getMulticastIPv4() const { return m_MULTICAST_IPv4; }
        std::string _getMulticastIPv6() const { return m_MULTICAST_IPv6; }
        std::string _getStreamingIPv4() const { return m_STREAMING_IPv4; }
        std::string _getStreamingIPv6() const { return m_STREAMING_IPv6; }
        SDCPort _getMulticastPortv4() const { return m_PORT_MULTICASTv4; }
        SDCPort _getMulticastPortv6() const { return m_PORT_MULTICASTv6; }
        SDCPort _getStreamingPortv4() const { return m_PORT_STREAMINGv4; }
        SDCPort _getStreamingPortv6() const { return m_PORT_STREAMINGv6; }

        // Configure own Params
        bool setDiscoveryConfigV4(std::string ps_IP_MC, SDCPort p_portMC, std::string ps_IP_Streaming, SDCPort p_portStreaming);
        bool setDiscoveryConfigV6(std::string ps_IP_MC, SDCPort p_portMC, std::string ps_IP_Streaming, SDCPort p_portStreaming);

        // Note: Only works with IPv4 IPAddresses!
        bool belongsToSDCInstance(Poco::Net::IPAddress p_IP) const;

        // IP4 / IP6
        bool getIP4enabled() const { return m_IP4enabled; }
        bool getIP6enabled() const { return m_IP6enabled; }
        void setIP4enabled(bool p_set) { m_IP4enabled = p_set; }
        void setIP6enabled(bool p_set) { m_IP6enabled = p_set; }

        // Discovery Time
        /**
         * @brief Set the time the service manager waits for the device discovery
         *
         * @param discoveryTimeSec The time in milliseconds to wait while discovery
         */
        bool setDiscoveryTime(std::chrono::milliseconds p_time);
        /**
         * @brief Get the time the service manager waits for the device discovery
         *
         * @return The time in milliseconds to wait for discovery
         */
        std::chrono::milliseconds getDiscoveryTime() const;

        void dumpPingManager(std::unique_ptr<OSELib::DPWS::PingManager> pingManager);

    private:

        std::pair<bool, SDCPort> findFreePort() const;

        void _cleanup();

    };
}

#endif
