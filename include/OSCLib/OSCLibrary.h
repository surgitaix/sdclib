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
 *  @file OSCLibrary.h
 *  @project OSCLib
 *  @date 24.08.2011
 *  @author besting
 *  @copyright (c) SurgiTAIX AG
 *
 */

#ifndef OSCLIB_H_
#define OSCLIB_H_

#include "Util/DebugOut.h"
#include "Util/Task.h"

#include <xercesc/dom/DOMImplementationLS.hpp>

#include <atomic>
#include <list>
#include <memory>
#include <set>
#include <string>

#include "Poco/Mutex.h"
#include "Poco/Thread.h"
#include "Poco/Runnable.h"
#include "Poco/NotificationQueue.h"

namespace CDM {
	class FromString;
}

namespace OSCLib {

    class ShutdownTask;

namespace Data {
namespace OSCP {
    class OSCPConsumer;
    class OSCPProvider;
    class OSCPServiceManager;
}
}

namespace Comm {
	class CommunicationManager;
	class NetworkInterface;
}

namespace Dev {
	class Device;
}

class ReaderThread;
class WriterThread;

class OSCLibrary {
	friend class Dev::Device;
    friend class Data::OSCP::OSCPConsumer;
    friend class Data::OSCP::OSCPProvider;
    friend class Data::OSCP::OSCPServiceManager;
    friend class CDM::FromString;
public:

	OSCLibrary();
	virtual ~OSCLibrary();

    void scheduleTaskForShutdown(std::shared_ptr<OSCLib::Util::Task> task);

	static OSCLibrary * getInstance();

	/**
	 * Startup framework.
	 *
	 * @param debugLevel The debug output level (0: no output, 1: errors, 2: errors and messages)
	 */
	void startup(Util::DebugOut::LogLevel debugLevel = Util::DebugOut::Default);

	/**
	 * Shutdown framework.
	 *
	 */
	void shutdown();

	/**
	 * Bind active sockets to a specific interface.
	 *
	 * @param bindInt The interface address
	 */
	void setBindInterface(const std::string & bindInt);

	std::string getBindInterface();

	/**
	 * Set the next global free port number used for bindings which are automatically created.
	 *
	 * @param portStart The next free port number to use
	 */
	void setPortStart(int portStart);

	/**
	 * Get the next global free port number used for bindings which are automatically created.
	 * Increases current number by one.
	 * 	 *
	 * @return The next free port number to use
	 */
	int extractNextPort();

	void readMessages();

    Comm::NetworkInterface * getNetInterface();

	bool isInitialized() {
		return initialized;
	}

    void bindToAll();

private:

	void registerDevice(Dev::Device * device);
	void unRegisterDevice(Dev::Device * device);
    void registerConsumer(Data::OSCP::OSCPConsumer * consumer);
    void unRegisterConsumer(Data::OSCP::OSCPConsumer * consumer);
    void registerProvider(Data::OSCP::OSCPProvider * provider);
    void unRegisterProvider(Data::OSCP::OSCPProvider * provider);
    void cleanUpOSCP();

	Comm::NetworkInterface * netInterface;
	ReaderThread * reader;
	static OSCLibrary * instance;
	std::list<Comm::CommunicationManager *> managersShuttingDown;
    std::set<Data::OSCP::OSCPConsumer *> consumers;
    std::set<Data::OSCP::OSCPProvider *> providers;

    std::set<Dev::Device *> deviceSet;
	std::string bindInt;
	std::atomic<int> portStart;
	bool initialized;

	Poco::Mutex mutex;

	xercesc::XMLGrammarPool * pool;
    std::shared_ptr<ShutdownTask> shutdownTask;
    Poco::NotificationQueue shutdownQueue;
};

class ReaderThread : public Util::Task {
public:
	ReaderThread();

	void runImpl();
};

} /* namespace OSCLib */
#endif /* OSCLIB_H_ */
