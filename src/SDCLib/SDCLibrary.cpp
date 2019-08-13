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


#include "OSELib/DPWS/PingManager.h"

#include <Poco/ConsoleChannel.h>
#include <Poco/FormattingChannel.h>
#include <Poco/PatternFormatter.h>
#include <Poco/ScopedLock.h>
#include <Poco/SimpleFileChannel.h>
#include <Poco/SplitterChannel.h>
#include <Poco/SingletonHolder.h>

#include <xercesc/util/PlatformUtils.hpp>

using namespace SDCLib;

SDCLibrary::SDCLibrary()
: WithLogger(OSELib::Log::BASE)
{
	Poco::AutoPtr<Poco::ConsoleChannel> t_consoleChannel(new Poco::ConsoleChannel);
	Poco::AutoPtr<Poco::SimpleFileChannel> t_fileChannel(new Poco::SimpleFileChannel);
	Poco::AutoPtr<Poco::SplitterChannel> t_splitterChannel(new Poco::SplitterChannel);
	t_fileChannel->setProperty("path", "sdclib.log");
	t_fileChannel->setProperty("rotation", "10 M");
	t_splitterChannel->addChannel(t_consoleChannel);
	t_splitterChannel->addChannel(t_fileChannel);

	Poco::AutoPtr<Poco::PatternFormatter> t_patternFormatter(new Poco::PatternFormatter);
	t_patternFormatter->setProperty("pattern", "%q %H:%M:%S.%i %s:\n  %t");
	Poco::AutoPtr<Poco::FormattingChannel> t_formattingChannel(new Poco::FormattingChannel(t_patternFormatter, t_splitterChannel));

	getLogger().setChannel(t_formattingChannel);
}

SDCLibrary::~SDCLibrary()
{
    shutdown();
}

SDCLibrary & SDCLibrary::getInstance() {
	static Poco::SingletonHolder<SDCLibrary> t_singletonHolder;
	return *t_singletonHolder.get();
}

void SDCLibrary::startup(OSELib::LogLevel debugLevel) {
	if (!m_initialized) {
		m_initialized = true;
		setDebugLevel(debugLevel);
		log_notice([&]{ return "SDCLib version " + Config::CURRENT_LIB_VERSION + " (C) " + Config::CURRENT_C_YEAR + " " + Config::STR_SURGITAIX; });
        xercesc::XMLPlatformUtils::Initialize();
	} else {
		log_error([&]{ return "SDCLib already initialized!"; });
	}
}

void SDCLibrary::shutdown()
{
    if(m_initialized) {
        m_initialized = false;
        m_latestPingManager.reset();
    }
}

void SDCLibrary::dumpPingManager(std::unique_ptr<OSELib::DPWS::PingManager> pingManager) {
	std::lock_guard<std::mutex> t_lock(m_mutex);
	m_latestPingManager = std::move(pingManager);
}

bool SDCLibrary::isInitialized() {
	return m_initialized;
}
