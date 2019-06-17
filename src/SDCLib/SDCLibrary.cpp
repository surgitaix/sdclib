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
 *  @file SDCLibrary.cpp
 *  @project SDCLib
 *  @date 15.02.2019
 *  @author besting, buerger, baumeister
 *  @copyright (c) SurgiTAIX AG
 *
 */

#include "SDCLib/SDCLibrary.h"
#include "SDCLib/Data/SDC/SDCConsumer.h"
#include "SDCLib/Data/SDC/SDCProvider.h"


#include "OSELib/DPWS/PingManager.h"

#include <Poco/ConsoleChannel.h>
#include <Poco/FormattingChannel.h>
#include <Poco/PatternFormatter.h>
#include <Poco/ScopedLock.h>
#include <Poco/SimpleFileChannel.h>
#include <Poco/SplitterChannel.h>

#include <xercesc/util/PlatformUtils.hpp>

using namespace SDCLib;

SDCLibrary::SDCLibrary() :
	WithLogger(OSELib::Log::BASE),
	m_discoveryTimeMilSec(5000)
{
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
	createPortLists(14000, 1000);
}

SDCLibrary::~SDCLibrary() {
    shutdown();
}

SDCLibrary & SDCLibrary::getInstance() {
	static Poco::SingletonHolder<SDCLibrary> singletonHolder;
	return *singletonHolder.get();
}

void SDCLibrary::startup(OSELib::LogLevel debugLevel) {
	if (!initialized) {
		initialized = true;
		setDebugLevel(debugLevel);
		log_notice([&]{ return "SDCLib version " + Config::CURRENT_LIB_VERSION + " (C) " + Config::CURRENT_C_YEAR + " " + Config::STR_SURGITAIX; });
        xercesc::XMLPlatformUtils::Initialize();
	} else {
		log_error([&]{ return "SDCLib already initialized!"; });
	}
}

void SDCLibrary::shutdown() {
	if (initialized) {
        initialized = false;
        _latestPingManager.reset();
        xercesc::XMLPlatformUtils::Terminate();
	}
}

void SDCLibrary::setPortStart(unsigned int start, unsigned int range) {
	Poco::Mutex::ScopedLock lock(mutex);

	const auto end(start + range);
	log_information([&]{ return "Using ports: [" + std::to_string(start) + "," + std::to_string(end) + ")"; });

	createPortLists(start, range);
}

void SDCLibrary::createPortLists(unsigned int start, unsigned int range) {
	reservedPorts.clear();
	for (unsigned int i = start; i < start + range; i++) {
		reservedPorts.push_back(i);
	}
	availablePorts = reservedPorts;
}

unsigned int SDCLibrary::extractFreePort() {
	Poco::Mutex::ScopedLock lock(mutex);
	const unsigned int result(availablePorts.front());
	availablePorts.pop_front();
	return result;
}

void SDCLibrary::returnPortToPool(unsigned int port) {
	Poco::Mutex::ScopedLock lock(mutex);
	if (std::find(reservedPorts.begin(), reservedPorts.end(), port) != reservedPorts.end()) {
		availablePorts.push_back(port);
	}
}

void SDCLibrary::dumpPingManager(std::unique_ptr<OSELib::DPWS::PingManager> pingManager) {
	Poco::Mutex::ScopedLock lock(mutex);
	_latestPingManager = std::move(pingManager);
}

bool SDCLibrary::isInitialized() {
	return initialized;
}

void SDCLibrary::setIP4enabled(bool IP4enabled) {
	m_IP4enabled = IP4enabled;
}

void SDCLibrary::setIP6enabled(bool IP6enabled) {
	m_IP6enabled = IP6enabled;
}

bool SDCLibrary::getIP4enabled() {
	return m_IP4enabled;
}

bool SDCLibrary::getIP6enabled() {
	return m_IP6enabled;
}


void SDCLibrary::setDiscoveryTime(int discoveryTimeMilSec){
	m_discoveryTimeMilSec = discoveryTimeMilSec;
}

int SDCLibrary::getDiscoveryTime(){
	return m_discoveryTimeMilSec;
}
