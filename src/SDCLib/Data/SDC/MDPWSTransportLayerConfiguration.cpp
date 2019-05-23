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
 *  @file MDPWSTransportLayerConfiguration.cpp
 *  @project SDCLib
 *  @date 14.02.2019
 *  @author buerger, baumeister
 *  @copyright (c) SurgiTAIX AG
 *
 */

#include "SDCLib/Data/SDC/MDPWSTransportLayerConfiguration.h"

#include "SDCLib/SDCInstance.h"

#include <iostream>

using namespace SDCLib::Data::SDC;

// default configuration
MDPWSTransportLayerConfiguration::MDPWSTransportLayerConfiguration(SDCLib::SDCInstance_shared_ptr p_SDCInstance)
  : m_SDCInstance(p_SDCInstance)
{
    assert(m_SDCInstance != nullptr);

    Poco::Net::IPAddress t_IP = Poco::Net::IPAddress(Poco::Net::AddressFamily::IPv4);
    if (m_SDCInstance->isBound()) {
        t_IP = m_SDCInstance->getNetworkInterfaces()[0]->m_IPv4;
    }
    // Socket: Address + Port
    m_httpBindAddress = t_IP;
    // Extract a free port - DEBUG //FIXME
   if (!m_SDCInstance->extractFreePort(m_port)) {
       std::cout << "MDPWSTransportLayerConfiguration::Constructor: FAILED EXTRACTING FREE PORT!" << std::endl;
   }

}

MDPWSTransportLayerConfiguration::~MDPWSTransportLayerConfiguration()
{
    if (!customPortFlag) {
        m_SDCInstance->returnPortToPool(m_port);
    }
}

void MDPWSTransportLayerConfiguration::setBindAddress(Poco::Net::IPAddress bindAddress)
{
    m_httpBindAddress = bindAddress;
}

void MDPWSTransportLayerConfiguration::setPort(SDCLib::SDCPort port)
{
	m_port = port;
	// return the standard port to the pool
    if (!customPortFlag) {
        m_SDCInstance->returnPortToPool(m_port);
		customPortFlag = true;
	}
}
