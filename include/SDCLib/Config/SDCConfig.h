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
 *  @file SDCConfig.h
 *  @project SDCLib
 *  @date 02.07.2019
 *  @author baumeister
 *  @copyright (c) SurgiTAIX AG
 *
 */
#ifndef SDCLIB_CONFIG_SDCCONFIG_H
#define SDCLIB_CONFIG_SDCCONFIG_H

#include "Prerequisites.h"
#include "config/config.h"

namespace SDCLib
{
    namespace Config
    {
        class SDCConfig
        {
        private:

            NetworkConfig_shared_ptr m_networkConfig = nullptr;

            SSLConfig_shared_ptr m_SSLConfig = nullptr;

        public:

            // Special Member Functions
            SDCConfig();
            SDCConfig(NetworkConfig_shared_ptr p_networkConfig);
            SDCConfig(NetworkConfig_shared_ptr p_networkConfig, SSLConfig_shared_ptr p_SSLConfig);

            SDCConfig(const SDCConfig& p_obj) = default;
            SDCConfig(SDCConfig&& p_obj) = default;
            SDCConfig& operator=(const SDCConfig& p_obj) = default;
            SDCConfig& operator=(SDCConfig&& p_obj) = default;
            ~SDCConfig() = default;


            NetworkConfig_shared_ptr getNetworkConfig() const { return m_networkConfig; }

            // Copy with random MDPWS Port
            static SDCConfig_shared_ptr randomMDPWSConfig(SDCConfig_shared_ptr p_config);

        };
    }
}

#endif
