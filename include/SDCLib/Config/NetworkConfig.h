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
 *  @file NetworkConfig.h
 *  @project SDCLib
 *  @date 02.07.2019
 *  @author baumeister
 *  @copyright (c) SurgiTAIX AG
 *
 */
#ifndef SDCLIB_CONFIG_NETWORKCONFIG_H
#define SDCLIB_CONFIG_NETWORKCONFIG_H

#include "SDCLib/Prerequisites.h"
#include "config/config.h"

#include "OSELib/DPWS/DPWS11Constants.h"
#include "OSELib/Helper/WithLogger.h"

#include <Poco/Net/NetworkInterface.h>
#include <Poco/Net/SocketDefs.h>

namespace SDCLib
{
    namespace Config
    {
        const Poco::Net::IPAddress SUBNET_CLASS_A = Poco::Net::IPAddress("255.0.0.0");
        const Poco::Net::IPAddress SUBNET_CLASS_B = Poco::Net::IPAddress("255.255.0.0");
        const Poco::Net::IPAddress SUBNET_CLASS_C = Poco::Net::IPAddress("255.255.255.0");

        using IPAddress = Poco::Net::IPAddress;
        using IPAddressList = std::vector<IPAddress>;

        class NetInterface
		{
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


        class NetworkConfig : public OSELib::Helper::WithLogger
        {
            friend SDCConfig;

        private:

            mutable std::mutex m_mutex;

            NI_List ml_networkInterfaces;
            NetInterface_shared_ptr m_MDPWSInterface = nullptr;
            SDCPort m_MDPWSPort = 0;

            std::atomic<bool> m_IP4enabled = ATOMIC_VAR_INIT(Config::SDC_IP_V4_ENABLED);
            std::atomic<bool> m_IP6enabled = ATOMIC_VAR_INIT(Config::SDC_IP_V6_ENABLED);

            // Discovery
            std::atomic<std::chrono::milliseconds> m_discoveryTime = ATOMIC_VAR_INIT(std::chrono::milliseconds(Config::SDC_DISCOVERY_TIMEOUT_MS));

            // Network settings
            std::string m_MULTICAST_IPv4 = OSELib::UDP_MULTICAST_DISCOVERY_IP_V4;
            std::string m_MULTICAST_IPv6 = OSELib::UDP_MULTICAST_DISCOVERY_IP_V6;
            std::string m_STREAMING_IPv4 = OSELib::UDP_MULTICAST_STREAMING_IP_V4;
            std::string m_STREAMING_IPv6 = OSELib::UDP_MULTICAST_STREAMING_IP_V6;

            SDCPort m_PORT_MULTICASTv4 = OSELib::UPD_MULTICAST_DISCOVERY_PORT;
            SDCPort m_PORT_MULTICASTv6 = OSELib::UPD_MULTICAST_DISCOVERY_PORT;
            SDCPort m_PORT_STREAMINGv4 = OSELib::UPD_MULTICAST_STREAMING_PORT;
            SDCPort m_PORT_STREAMINGv6 = OSELib::UPD_MULTICAST_STREAMING_PORT;

            // TODO: PortList

        public:

            // Special Member Functions
            NetworkConfig();
            NetworkConfig(const NetworkConfig& p_obj) = delete;
            NetworkConfig(NetworkConfig&& p_obj) = delete;
            NetworkConfig& operator=(const NetworkConfig& p_obj) = delete;
            NetworkConfig& operator=(NetworkConfig&& p_obj) = delete;
            ~NetworkConfig() = default;

            // IP4 / IP6
            bool getIP4enabled() const { return m_IP4enabled; }
            bool getIP6enabled() const { return m_IP6enabled; }
            void setIP4enabled(bool p_set) { m_IP4enabled = p_set; }
            void setIP6enabled(bool p_set) { m_IP6enabled = p_set; }

            bool bindToDefaultNetworkInterface(bool p_useAsMDPWS = true);
            bool bindToInterface(const std::string& ps_networkInterfaceName, bool p_useAsMDPWS = false);
            NI_List getNetworkInterfaces() const { return ml_networkInterfaces; }
            bool _networkInterfaceBoundTo(std::string ps_adapterName) const;
            bool isBound() const;

            // Note: Can be nullptr!
            NetInterface_shared_ptr getMDPWSInterface() { return m_MDPWSInterface; }
            // Listening Port of the HTTP Server
            SDCPort getMDPWSPort() { return m_MDPWSPort; }

            // Note: Only works with IPv4 IPAddresses!
            bool belongsTo(Poco::Net::IPAddress p_IP) const;

            // Internal usage
            std::string _getMulticastIPv4() const { return m_MULTICAST_IPv4; }
            std::string _getMulticastIPv6() const { return m_MULTICAST_IPv6; }
            std::string _getStreamingIPv4() const { return m_STREAMING_IPv4; }
            std::string _getStreamingIPv6() const { return m_STREAMING_IPv6; }
            SDCPort _getMulticastPortv4() const { return m_PORT_MULTICASTv4; }
            SDCPort _getMulticastPortv6() const { return m_PORT_MULTICASTv6; }
            SDCPort _getStreamingPortv4() const { return m_PORT_STREAMINGv4; }
            SDCPort _getStreamingPortv6() const { return m_PORT_STREAMINGv6; }


            // Discovery Time
            /**
            * @brief Set the time the service manager waits for the device discovery
            *
            * @param discoveryTimeSec The time in milliseconds to wait while discovery
            */
            void setDiscoveryTime(std::chrono::milliseconds p_time);
            /**
            * @brief Get the time the service manager waits for the device discovery
            *
            * @return The time in milliseconds to wait for discovery
            */
            std::chrono::milliseconds getDiscoveryTime() const;

        private:

            // Internal usage by friend class only
            bool _shuffleMDPWSPort();

            /**
            * @brief Get a free network port to listen.
            *
            * @return First argument true if second argument contains a valid port.
            */
            std::pair<bool, SDCPort> findFreePort() const;

            void _cleanup();

        };
    }
}

#endif
