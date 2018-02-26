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
 *  @file SDCLibrary.h
 *  @project OSCLib
 *  @date 24.08.2011
 *  @author besting
 *  @copyright (c) SurgiTAIX AG
 *
 */

#ifndef OSCLIB_H_
#define OSCLIB_H_

#include <atomic>
#include <list>
#include <memory>
#include <set>
#include <string>

#include "Poco/Mutex.h"
#include "Poco/Thread.h"
#include "Poco/Runnable.h"
#include "Poco/NotificationQueue.h"

#include "OSELib/fwd.h"
#include "OSELib/Helper/WithLogger.h"

namespace OSCLib {



class SDCLibrary final : public OSELib::WithLogger {
public:

	SDCLibrary();
	~SDCLibrary();

	static SDCLibrary & getInstance();

	/**
	 * Startup framework.
	 *
	 * @param debugLevel The debug output level.
	 */
	void startup(OSELib::LogLevel debugLevel = OSELib::LogLevel::ERROR);

	/**
	 * Shutdown framework.
	 *
	 */
	void shutdown();

	/**
	 * Set the next global free port number used for bindings which are automatically created.
	 *
	 * @param portStart The next free port number to use
	 */
	void setPortStart(unsigned int portStart, unsigned int portRange = 1000);

	/**
	 * Get the next global free port number used for bindings which are automatically created.
	 * Increases current number by one.
	 * 	 *
	 * @return The next free port number to use
	 */
	unsigned int extractFreePort();
	void returnPortToPool(unsigned int port);

	bool isInitialized();

	void dumpPingManager(std::unique_ptr<OSELib::DPWS::PingManager> pingManager);

	void setIP4enabled(bool IP4enabled);
	void setIP6enabled(bool IP6enabled);
	bool getIP4enabled();
	bool getIP6enabled();
	int getNumberOfReattemptsWithAnotherPort() const;
	void setNumberOfReattemptsWithAnotherPort(const int numberOfReattemptsWithAnotherPort);


    /**
    * @brief Set the time the service manager waits for the device discovery
    *
    * @param discoveryTimeSec The time in seconds to wait while discovery
    */
	void setDiscoveryTime(int discoveryTimeSec);

    /**
    * @brief Get the time the service manager waits for the device discovery
    *
    * @return The time in seconds to wait for discovery
    */
	int getDiscoveryTime();
private:

	bool m_IP4enabled;
	bool m_IP6enabled;
	bool initialized;
	int m_numberOfReattemptsWithAnotherPort;
	int m_discoveryTimeSec;

	void createPortLists(unsigned int portStart, unsigned int portRange = 1000);
	std::deque<unsigned int> reservedPorts;
	std::deque<unsigned int> availablePorts;

	Poco::Mutex mutex;
	std::unique_ptr<OSELib::DPWS::PingManager> _latestPingManager;

	// declaring copy-methods prevents from initializing multiple copies of singleton
	SDCLibrary(SDCLibrary const&);
	void operator=(SDCLibrary const&);
};

} /* namespace OSCLib */
#endif /* OSCLIB_H_ */
