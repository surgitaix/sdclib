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

#include "SDCLib/Util/DebugOut.h"


using namespace SDCLib;
using namespace SDCLib::Util;

/**
 * Specify global debug level:
 * 0: no output
 * 1: errors
 * 2: errors and messages
 */
DebugOut::LogLevel DebugOut::DEBUG_LEVEL = DebugOut::LogLevel::Info;
std::ofstream* DebugOut::m_fileOut = nullptr;
std::mutex DebugOut::m_globalOutputLock;

DebugOut::DebugOut(LogLevel logLevel, std::ostream& s, const std::string& prefix)
: m_stream(s),
 m_level(logLevel),
 m_prefix(prefix),
 m_showMessage(logLevel <= DEBUG_LEVEL)
{
	outputOnCreate();
}

DebugOut::DebugOut(LogLevel logLevel, const std::string& prefix)
:	m_stream(logLevel != LogLevel::Error ? std::cout : std::cerr),
	m_level(logLevel),
	m_prefix(prefix),
	m_showMessage(logLevel <= DEBUG_LEVEL)
{
	outputOnCreate();
}

DebugOut::DebugOut(std::ostream& s, const std::string& prefix)
:	m_stream(s),
	m_level(LogLevel::Info),
	m_prefix(prefix),
	m_showMessage(m_level <= DEBUG_LEVEL) // TODO: CAREFUL: showMessage must be placed AFTER level in header! -> Design!
{
	outputOnCreate();
}

DebugOut::~DebugOut()
{
	outputOnDestroy();
	flush();
	// closeLogFile(); // TODO: RAII ?
}

void DebugOut::flush()
{
	if (!m_showMessage)
	{
		m_logBuffer.clear();
		return;
	}

	std::lock_guard<std::mutex> t_globalLock{m_globalOutputLock};

	const std::string t_output{m_logBuffer.str()};

	{ // LOCK
		static std::mutex mutex; // TODO: What is going on her? static std::mutex in non static member function?
		std::lock_guard<std::mutex> t_lock{mutex};

		if (m_showMessage)
		{
			m_stream << t_output << std::flush;
		}

		if (m_showMessage && isLogFileGood())
		{
			(*m_fileOut) << t_output << std::flush;
		}
	} // UNLOCK

	m_logBuffer.clear();
}

bool DebugOut::openLogFile(const std::string& filename, bool truncateFile)
{
	std::lock_guard<std::mutex> t_lock(m_globalOutputLock);
	if (nullptr == m_fileOut)
	{
		m_fileOut = new std::ofstream();
	}

	try
	{
		if (truncateFile)
		{
			m_fileOut->open(filename.c_str(), m_fileOut->trunc);
		}
		else
		{
			m_fileOut->open(filename.c_str(), m_fileOut->app);
		}
	}
	catch (...)
	{
		return false;
	}
	return isLogFileGood();
}

void DebugOut::closeLogFile()
{
    std::lock_guard<std::mutex> t_lock(m_globalOutputLock);

	if (m_fileOut != nullptr)
	{
		m_fileOut->close();
		delete m_fileOut;
		m_fileOut = nullptr;
	}
}

DebugOut& DebugOut::operator<<(std::ostream& (*pf)(std::ostream&))
{
	if (m_showMessage)
	{
		m_logBuffer << pf;
	}

	return *this;
}

void DebugOut::outputOnCreate()
{
	std::string outString{"\n"};
	switch(m_level)
	{
		case DebugOut::LogLevel::Default: break; // TODO: WHAT TO OUTPUT HERE?
		case DebugOut::LogLevel::Error: outString += "ERR  "; break;
		case DebugOut::LogLevel::Full: 	outString += "FULL "; break;
		case DebugOut::LogLevel::Info: 	outString += "INF  "; break;
		case DebugOut::LogLevel::Silent: break;
		case DebugOut::LogLevel::Verbose: break;
		default:
			// "SHOULD" NEVER HAPPEN -> IMPLEMENTATION ERROR -> How to handle that?
			break;
	}

	if (m_prefix.size() > 0)
	{
		outString += m_prefix;
		outString += ": ";
	}
	operator <<(outString);
}

void DebugOut::outputOnDestroy()
{
	operator <<(std::flush);
}

bool DebugOut::isLogFileGood()
{
   	if (m_fileOut != nullptr)
   	{
   		return m_fileOut->is_open();
   	}
   	return false;
}
