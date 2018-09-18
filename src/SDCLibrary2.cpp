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
 *  @file SDCLibrary2.cpp
 *  @project SDCLib
 *  @date 17.09.2018
 *  @author buerger
 *  @copyright (c) SurgiTAIX AG
 *
 */


#include "OSCLib/SDCLibrary2.h"
#include "OSCLib/SDCInstance.h"
#include "config/config.h"

#include "Poco/ConsoleChannel.h"
#include "Poco/FormattingChannel.h"
#include "Poco/Notification.h"
#include "Poco/PatternFormatter.h"
#include "Poco/ScopedLock.h"
#include "Poco/SimpleFileChannel.h"
#include "Poco/SingletonHolder.h"
#include "Poco/SplitterChannel.h"




#include <xercesc/util/PlatformUtils.hpp>


#include "OSELib/DPWS/PingManager.h"

namespace SDCLib {

const std::string CURRENT_LIB_VERSION("3.0.1");

SDCLibrary2::SDCLibrary2() :
	WithLogger(OSELib::Log::BASE),
	initialized(false)
{


	// set up the librarie's logger
	Poco::AutoPtr<Poco::ConsoleChannel> consoleChannel(new Poco::ConsoleChannel);
	Poco::AutoPtr<Poco::SimpleFileChannel> fileChannel(new Poco::SimpleFileChannel);
	Poco::AutoPtr<Poco::SplitterChannel> splitterChannel(new Poco::SplitterChannel);
	fileChannel->setProperty("path", "sdclib.log");
	fileChannel->setProperty("rotation", "10 M");
	splitterChannel->addChannel(consoleChannel);
	splitterChannel->addChannel(fileChannel);

	Poco::AutoPtr<Poco::PatternFormatter> patternFormatter(new Poco::PatternFormatter);
	patternFormatter->setProperty("pattern", "%q %H:%M:%S.%i %s:\n  %t");
	Poco::AutoPtr<Poco::FormattingChannel> formattingChannel(new Poco::FormattingChannel(patternFormatter, splitterChannel));

	getLogger().setChannel(formattingChannel);

	// default ports chosen regarding to unlikely used ports:
	// https://en.wikipedia.org/wiki/List_of_TCP_and_UDP_port_numbers
}

SDCLibrary2::~SDCLibrary2() {
    shutdown();
}


SDCLibrary2 & SDCLibrary2::getInstance() {
	static Poco::SingletonHolder<SDCLibrary2> singletonHolder;
	return *singletonHolder.get();
}

void SDCLibrary2::startup(OSELib::LogLevel debugLevel) {
	if (!initialized) {
		initialized = true;
		setDebugLevel(debugLevel);
		log_notice([&]{ return "SDCLib version " + CURRENT_LIB_VERSION + " (C) 2018 SurgiTAIX AG"; });

		// init parser
        xercesc::XMLPlatformUtils::Initialize();

        // init interfaces management
        // TODO: implement IPv6
        for (const auto & nextIf : Poco::Net::NetworkInterface::list()) {
        	if (nextIf.supportsIPv4()
				&& nextIf.address().isUnicast()
				&& !nextIf.address().isLoopback()) {
        			m_availableNetworkInterfacesList.push_back(nextIf);
        	}
        }
	} else {
		log_error([&]{ return "SDCLib already initialized!"; });
	}
}

void SDCLibrary2::shutdown() {
	if (initialized) {
        initialized = false;
        _latestPingManager.reset();
        xercesc::XMLPlatformUtils::Terminate();
	}
}


void SDCLibrary2::dumpPingManager(std::unique_ptr<OSELib::DPWS::PingManager> pingManager) {
	Poco::Mutex::ScopedLock lock(mutex);
	_latestPingManager = std::move(pingManager);
}

bool SDCLibrary2::isInitialized() {
	return initialized;
}

// "Factory" methods
SDCInstancePtr SDCLibrary2::createDefaultSDCInstance() {
	Poco::Mutex::ScopedLock lock(mutex);
	SDCInstancePtr t_sdcInstance = shared_ptr<SDCInstance>(new SDCInstance(SDCLib::Config::SDC_PORT_START, SDCLib::Config::SDC_PORT_RANGE, m_availableNetworkInterfacesList));
	// empty list since all network interfaces are assigned to the SDCInstance
	m_availableNetworkInterfacesList.clear();
	return move(t_sdcInstance);
}


SDCInstancePtr SDCLibrary2::bindToInterface(string interfaceName) {
	Poco::Mutex::ScopedLock lock(mutex);
	list<Poco::Net::NetworkInterface> t_networkInterfacesList;

	for (list<Poco::Net::NetworkInterface>::iterator itr = m_availableNetworkInterfacesList.begin(); itr != m_availableNetworkInterfacesList.end(); )
	{
		if (itr->adapterName() == interfaceName) {
			t_networkInterfacesList.push_back(*itr);
			m_availableNetworkInterfacesList.erase(itr);
			break;
		}	else {
			++itr;
		}

	}
	SDCInstancePtr t_sdcInstance = shared_ptr<SDCInstance>(new SDCInstance(SDCLib::Config::SDC_PORT_START, SDCLib::Config::SDC_PORT_RANGE, t_networkInterfacesList));
	return move(t_sdcInstance);
}

SDCInstancePtr SDCLibrary2::bindToMultipleInterfaces(list<string> interfacesNamesList) {
	Poco::Mutex::ScopedLock lock(mutex);
	list<Poco::Net::NetworkInterface> t_networkInterfacesList;

	for (string netInterfaceName: interfacesNamesList) {
		for (list<Poco::Net::NetworkInterface>::iterator itr = m_availableNetworkInterfacesList.begin(); itr != m_availableNetworkInterfacesList.end(); )
		{
			if (itr->adapterName() == netInterfaceName) {
				t_networkInterfacesList.push_back(*itr);
				m_availableNetworkInterfacesList.erase(itr);
				break;
			}	else {
				++itr;
			}
		}
	}
	SDCInstancePtr t_sdcInstance = shared_ptr<SDCInstance>(new SDCInstance(SDCLib::Config::SDC_PORT_START, SDCLib::Config::SDC_PORT_RANGE, t_networkInterfacesList));
	return move(t_sdcInstance);
}



} /* namespace SDCLib */
