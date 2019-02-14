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
 *  @file DebugOut.cpp
 *  @project SDCLib
 *  @date 12.07.2012
 *  @author besting
 *  @copyright (c) SurgiTAIX AG
 *
 */

#include "OSCLib/Util/DebugOut.h"

#include "Poco/Mutex.h"
#include "Poco/ScopedLock.h"

namespace SDCLib {
namespace Util {

/**
 * Specify global debug level:
 * 0: no output
 * 1: errors
 * 2: errors and messages
 */
DebugOut::LogLevel DebugOut::DEBUG_LEVEL = DebugOut::Info;
std::ofstream * DebugOut::fileOut = nullptr;
Poco::Mutex DebugOut::globalOutputLock;

DebugOut::DebugOut(LogLevel logLevel, std::ostream & s, const std::string & prefix) :
		stream(s),
		level(logLevel),
		prefix(prefix),
		showMessage(level <= DEBUG_LEVEL)
{
	outputOnCreate();
}

DebugOut::DebugOut(LogLevel logLevel, const std::string & prefix) :
		stream(logLevel != Error ? std::cout : std::cerr),
		level(logLevel),
		prefix(prefix),
		showMessage(level <= DEBUG_LEVEL)
{
	outputOnCreate();
}

DebugOut::DebugOut(std::ostream & s, const std::string & prefix) :
		stream(s),
		level(Info),
		prefix(prefix),
		showMessage(level <= DEBUG_LEVEL)
{
	outputOnCreate();
}

DebugOut::~DebugOut() {
	outputOnDestroy();
	flush();
}

void DebugOut::flush() {
	if (!showMessage) {
		logBuffer.clear();
		return;
	}

	Poco::Mutex::ScopedLock lock(globalOutputLock);

	const std::string output(logBuffer.str());
	{
		static Poco::Mutex mutex;
		Poco::Mutex::ScopedLock lock(mutex);

		if (showMessage) {
			stream << output << std::flush;
		}

		if (showMessage && isLogFileGood()) {
			(*fileOut) << output << std::flush;
		}
	}
	logBuffer.clear();
}

bool DebugOut::openLogFile(const std::string & filename, bool truncateFile) {
	Poco::Mutex::ScopedLock lock(globalOutputLock);
	if (DebugOut::fileOut == nullptr) {
		fileOut = new std::ofstream();
	}

	try {
		if (truncateFile) {
			fileOut->open(filename.c_str(), fileOut->trunc);
		} else {
			fileOut->open(filename.c_str(), fileOut->app);
		}
	}
	catch (...) {
		return false;
	}
	return isLogFileGood();
}

void DebugOut::closeLogFile() {
	Poco::Mutex::ScopedLock lock(globalOutputLock);
	if (DebugOut::fileOut != nullptr) {
		DebugOut::fileOut->close();
		delete fileOut;
		fileOut = nullptr;
	}
}

DebugOut & DebugOut::operator<<(std::ostream & (*pf)(std::ostream&)) {
	if (showMessage)
		logBuffer << pf;

	return *this;
}

void DebugOut::outputOnCreate() {
	std::string outString("\n");
	switch(level) {
		case DebugOut::Default: break;
		case DebugOut::Error: outString += "ERR  "; break;
		case DebugOut::Full: outString += "FULL "; break;
		case DebugOut::Info: outString += "INF  "; break;
		case DebugOut::Silent: break;
		case DebugOut::Verbose: break;
	}
	if (prefix.size() > 0) {
		outString += prefix;
		outString += ": ";
	}
	operator <<(outString);
}

void DebugOut::outputOnDestroy() {
	operator <<(std::flush);
}

bool DebugOut::isLogFileGood() {
   	if (DebugOut::fileOut != nullptr) {
   		return DebugOut::fileOut->is_open();
   	}

   	return false;
}

} /* namespace Util */
} /* namespace SDCLib */
