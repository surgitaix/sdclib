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
 *  @file SDCLibrary2.h
 *  @project SDCLib
 *  @date 24.08.2011
 *  @author besting
 *  @copyright (c) SurgiTAIX AG
 *
 */

#ifndef SDCLIBRARAY_H_
#define SDCLIBRARAY_H_

#include <list>
#include <memory>
#include <set>
#include <string>


#include <Poco/Mutex.h>
#include <Poco/Net/NetworkInterface.h>

#include "SDCLib/Prerequisites.h"
#include "OSELib/fwd.h"
#include "OSELib/Helper/WithLogger.h"


namespace SDCLib {

class SDCLibrary2 final : public OSELib::WithLogger {
public:
	SDCLibrary2();
	~SDCLibrary2();

	static SDCLibrary2 & getInstance();

	/**
	 * @brief Startup framework.
	 *
	 * @param debugLevel The debug output level.
	 */
	void startup(OSELib::LogLevel debugLevel = OSELib::LogLevel::Error);

	/**
	 * Shutdown framework.
	 *
	 */
	void shutdown();


	/**
	 * @brief Returns true if the SDCLibrary singleton is initialized
	 *
	 * @return initialization status of the framework
	 */
	bool isInitialized() { return initialized; }


	void dumpPingManager(std::unique_ptr<OSELib::DPWS::PingManager> pingManager);


//
// public members
//
	/**
	 * @brief Returns a SDCInstance, which is used the interface binding and port management of the framework.
	 * 			The default SDCInstance binds to all available network interfaces except loopback.
	 *
	 * @return Pointer to SDCInstance that binds the SDCConsumer and SDCProvider to all available network interfaces
	 */
	SDCInstance_shared_ptr createDefaultSDCInstance();

	/**
	 * @brief Returns a SDCInstance, which is used the interface binding and port management of the framework.
	 * 			The interface to be bound to is specified by its name given as a string (e.g. "enp0s3", "wlan0"...)
	 *
	 * @return Pointer to SDCInstance that binds the SDCConsumer and SDCProvider the specified adapter's name
	 */

	SDCInstance_shared_ptr createBoundSDCInstance(std::string interfaceName);

	/**
	 * @brief Returns a SDCInstance, which is used the interface binding and port management of the framework.
	 * 			The interfaces to be bound to are specified by a list of names given as a strings (e.g. "enp0s3", "wlan0"...)
	 *
	 * @return Pointer to SDCInstance that binds the SDCConsumer and SDCProvider the specified adapters' names
	 */
	SDCInstance_shared_ptr createBoundSDCInstance(std::list<std::string> interfacesNamesList);

	/**
	 * @brief Checks if an unbound interface is still available. Interfaces are not returned to this singleton,
	 * 			but part of the configuration.
	 *
	 * @return Returns true if an interface is still available
	 */
	bool isInterfaceAvailable();

private:

	bool initialized;

	Poco::Mutex mutex;
	// contains all available network interfaces
	std::list<Poco::Net::NetworkInterface> m_availableNetworkInterfacesList;

	std::unique_ptr<OSELib::DPWS::PingManager> _latestPingManager;

	// declaring copy-methods prevents from initializing multiple copies of singleton
    SDCLibrary2(const SDCLibrary2& p_obj) = delete;
    // even do not allow to move the singleton. It is only used on top of the framework
    SDCLibrary2(SDCLibrary2&& p_obj) = delete;
    SDCLibrary2& operator=(const SDCLibrary2& p_obj) = delete;
    SDCLibrary2& operator=(SDCLibrary2&& p_obj) = delete;


};

} /* namespace SDCLib */
#endif /* OSCLIB_H_ */
