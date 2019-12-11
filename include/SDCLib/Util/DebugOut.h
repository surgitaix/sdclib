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
 *  @file DebugOut.h
 *  @project SDCLib
 *  @date 12.07.2012
 *  @author besting
 *  @copyright (c) SurgiTAIX AG
 *
 */

#ifndef SDCLIB_UTIL_DEBUGSTREAM_H_
#define SDCLIB_UTIL_DEBUGSTREAM_H_

#include <mutex>
#include <iostream>
#include <fstream>
#include <sstream>

namespace SDCLib
{
	namespace Util
	{
		/**
		 * Class for managing debug output.
		 */
		class DebugOut
		{
		public:

			enum LogLevel // TODO: Change to enum 'class' -> Will probably break some code...
			{
				Silent,
				Default,
				Error,
				Info,
				Full,
				Verbose
			};

			static LogLevel DEBUG_LEVEL;

			DebugOut(LogLevel level, std::ostream& s, const std::string& prefix = "");
			DebugOut(std::ostream& s, const std::string& prefix = "");
			DebugOut(LogLevel level, const std::string& prefix = "");
			virtual ~DebugOut();

			static bool openLogFile(const std::string& filename, bool truncateFile = false);
			static void closeLogFile();

			void flush();

			DebugOut& operator<<(std::ostream& (*pf)(std::ostream&)); // TODO: ???

			template<typename T>
			DebugOut& operator<<(T & item)
			{
				const T & constItem(item);
				return operator <<(constItem);
			}

			template<typename T>
			DebugOut& operator<<(const T& item)
			{
				if(m_showMessage)
				{
					m_logBuffer << item;
				}
				return *this;
			}

		private:

			void outputOnCreate();
			void outputOnDestroy();

			std::ostringstream m_logBuffer;
			std::ostream& m_stream;

			const LogLevel m_level;
			const std::string m_prefix;
			bool m_showMessage;

			static std::mutex m_globalOutputLock;
			static std::ofstream* m_fileOut; // TODO: smart pointer?
			static bool isLogFileGood(); // TODO: Mixing member functions and variables?
		};

	} /* namespace Util */
} /* namespace SDCLib */
#endif /* SDCLIB_UTIL_DEBUGSTREAM_H_ */
