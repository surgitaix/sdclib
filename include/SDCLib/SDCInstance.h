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

#include "SDCLib/Prerequisites.h"
#include "config/config.h"

#include "SDCLib/Config/NetworkConfig.h"
#include "SDCLib/Config/SSLConfig.h"


#include "OSELib/DPWS/PingManager.h"

namespace SDCLib
{

    using SDCInstanceID = std::string;

    class SDCInstance
    {
    private:

        static std::atomic_uint s_IDcounter;
        SDCInstanceID m_ID = "INVALID_ID";

        mutable std::mutex m_mutex;

        std::atomic<bool> m_init = ATOMIC_VAR_INIT(false);

        Config::SDCConfig_shared_ptr m_SDCConfig = nullptr;

        std::unique_ptr<OSELib::DPWS::PingManager> _latestPingManager;

    public:

        explicit SDCInstance(bool p_init = true);
        explicit SDCInstance(Config::SDCConfig_shared_ptr p_config, bool p_init = true);
        explicit SDCInstance(SDCPort p_MDPWSPort, bool p_init);

        // Special Member Functions
        SDCInstance(const SDCInstance& p_obj) = delete;
        SDCInstance(SDCInstance&& p_obj) = delete;
        SDCInstance& operator=(const SDCInstance& p_obj) = delete;
        SDCInstance& operator=(SDCInstance&& p_obj) = delete;
        ~SDCInstance();

        SDCInstanceID getID() const { return m_ID; }

        bool init();
        bool isInit() const { return m_init; }

        // Convenience Helper to get Config and Subconfig parts
        Config::SDCConfig_shared_ptr getSDCConfig() const;
        Config::NetworkConfig_shared_ptr getNetworkConfig() const;
        Config::SSLConfig_shared_ptr getSSLConfig() const;


        bool bindToDefaultNetworkInterface(bool p_useAsMDPWS = true);
        bool bindToInterface(const std::string& ps_networkInterfaceName, bool p_useAsMDPWS = false);
        bool _networkInterfaceBoundTo(std::string ps_adapterName) const;

        // Configure own Params
        bool setDiscoveryConfigV4(std::string ps_IP_MC, SDCPort p_portMC, std::string ps_IP_Streaming, SDCPort p_portStreaming);
        bool setDiscoveryConfigV6(std::string ps_IP_MC, SDCPort p_portMC, std::string ps_IP_Streaming, SDCPort p_portStreaming);


        // SSL (optional) WIP!
        bool initSSL(Poco::Net::Context::VerificationMode p_modeClient = Poco::Net::Context::VERIFY_RELAXED, Poco::Net::Context::VerificationMode p_modeServer = Poco::Net::Context::VERIFY_RELAXED);

        // IP4 / IP6 - Forward to the Config
        bool getIP4enabled() const;
        bool getIP6enabled() const;
        void setIP4enabled(bool p_set);
        void setIP6enabled(bool p_set);
        bool setDiscoveryTime(std::chrono::milliseconds p_time);
        std::chrono::milliseconds getDiscoveryTime() const;


        void dumpPingManager(std::unique_ptr<OSELib::DPWS::PingManager> pingManager);


        /**
         * @brief checks if the given string matches the UUID pattern
         *
         * @param p_UUID the string to check
         * @return Matching the UUID requirements or not.
         *
         */
        static bool isUUID(const std::string& p_UUID);

        /**
		 * @brief Generates a time based UUID and prefixes it with "urn:uuid:"
		 *
		 */
		static std::string calcMSGID();
        /**
		 * @brief Generates a time based UUID (MAC Address seeded)
		 *
		 */
		static std::string calcUUID();
        /**
		 * @brief Generates a new UUIDv5 (SDC Namespace UUID seed)
		 *
		 * @param p_name Name from which to generate the UUID
		 * @param p_prefix If specified the UUID will be prefixed with "urn:uuid:" . (Default for Endpoint References)
		 *
		 */
		static std::string calcUUIDv5(std::string p_name, bool p_prefix);

    private:

        /**
         * @brief Get a free network port to listen.
         *
         * @return First argument true if second argument contains a valid port.
         */
        std::pair<bool, SDCPort> findFreePort() const;

        void _cleanup();

    };
}

#endif
