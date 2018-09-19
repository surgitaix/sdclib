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
 *  @date 17.09.2018
 *  @author baumeister, buerger
 *  @copyright (c) SurgiTAIX AG
 *
 */
#ifndef SDCLIB_SDCINSTANCE_H
#define SDCLIB_SDCINSTANCE_H

#include "Prerequisites.h"

#include "Poco/Net/NetworkInterface.h"

#include "config/config.h"
#include "OSELib/Helper/WithLogger.h"

#include <mutex>
#include <list>
#include <deque>

using namespace std;

namespace SDCLib
{
    class SDCInstance : public OSELib::WithLogger
    {
    private:

    	friend class SDCLibrary2;

    	// each adapter thread needs writing access to this class,
    	// thus synchronization mechanisms need to be implemented
        mutable mutex m_mutex;

        list<Poco::Net::NetworkInterface> m_networkInterfacesList;

        bool m_init = false;
        unsigned int m_discoveryTime; // in ms

        bool ip4enabled;
        bool ip6enabled;

        std::deque<unsigned int> m_reservedPorts;
        std::deque<unsigned int> m_availablePorts;

    public:
        SDCInstance& operator=(const SDCInstance& p_obj) = delete;
        SDCInstance& operator=(SDCInstance&& p_obj) = delete;
        ~SDCInstance();


        /**
		* @brief Returns the initialization status. The Library needs to be initialized before
		* 		being handed over to the framework. After initializations the defined ports are fixed
		* 		and cannot be changed afterwards.
		*
		* @return initialization status
		*/
        bool isInit() const { return m_init; }

        /**
		* @brief Get the list of interfaces assigned to this SDCInstance.
		*
		* @return list of all assigend interfaces
		*/
        list<Poco::Net::NetworkInterface> getNetworkInterfacesList();




        // Port Management
        /**
    	* @brief Defines the ports to be used for the interfaces. The ports are taken out in the order of the list
    	* 			If an interface is shut down, the formerly bound port is returned.
    	*
    	* @param A list of all ports to be used.
    	* @return returns true if successful
    	*/
        bool setPorts(list<unsigned int> portList);

        /**
         * @brief Get the next free port number used for the bindings.
         *
         * @return The next free port number to use
         */
        unsigned int getFreePort() const;

        /**
		 * @brief If an interface is shut down, the formerly bound port is returned.
		 *
		 * @param The freed port
		 */
        void returnPortToPool(unsigned int p_port);

        // IP4 / IP6
        /**
		 * @brief Returns true if IP v4 is activated for the interfaces
		 *
		 * @return Status of the IP v4 activation
		 */
        bool getIP4enabled() const;

        /**
		 * @brief Returns true if IP v6 is activated for the interfaces
		 *
		 * @return Status of the IP v6 activation
		 */
        bool getIP6enabled() const;

        /**
		 * @brief Set the status of the IP v4 activation for all regarding interfaces
		 *
		 * @param Status of the IP v4 activation
		 */
        void setIP4enabled(bool ipv4Status);

        /**
		 * @brief Set the status of the IP v6 activation for all regarding interfaces
		 *
		 * @param Status of the IP v6 activation
		 */
        void setIP6enabled(bool ipv6Status);

        // Discovery Time
        /**
		 * @brief Sets the time the ServiceManager is searching the network for discovery
		 *
		 * @param The discovery time in ms
		 */
        bool setDiscoveryTime(int discoveryTimeMilSec);

        /**
		 * @brief Gets the time the ServiceManager is searching the network for discovery
		 *
		 * @return The discovery time in ms
		 */
        int getDiscoveryTime() const;

		/**
		 * @brief Seals the SDCInstance and initialized the class. This have to be done before handing the class over to
		 * 			SDCConsumer or SDCProvider. The classes settings (ports, interfaces) cannot be changed afterwards.
		 */
        void sealAndInit();

    private:
        // do not allow the user to initialize SDCInstance objects.
        // Only the SDCLibrary (friend) is allowed to init these since it manages the network interfaces
        SDCInstance(unsigned int portStart, unsigned int portRange, const list<Poco::Net::NetworkInterface> networkInterfacesList);
        // limit copy functionality to friend classes (SDCLibrary), since each class uniquely represents one or more network interfaces
        SDCInstance(const SDCInstance& p_obj);

        void createPortList(unsigned int portStart, unsigned int portRange);




        void _cleanup();

    };
}

#endif
