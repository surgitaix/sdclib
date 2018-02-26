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
 *  @project OSCLib
 *  @date 12.07.2012
 *  @author besting
 *  @copyright (c) SurgiTAIX AG
 *
 */

#ifndef DEBUGSTREAM_H_
#define DEBUGSTREAM_H_

#include "Poco/Mutex.h"

#include <iostream>
#include <fstream>
#include <sstream>

namespace SDCLib {
namespace Util {

/**
 * Class for managing debug output.
 */
class DebugOut {
public:

	enum LogLevel {
		Silent,
		Default,
		Error,
		Info,
		Full,
		Verbose
	};

	static LogLevel DEBUG_LEVEL;

	DebugOut(LogLevel level, std::ostream & s, const std::string & prefix = "");
	DebugOut(std::ostream & s, const std::string & prefix = "");
	DebugOut(LogLevel level, const std::string & prefix = "");
	virtual ~DebugOut();

    static bool openLogFile(const std::string & filename, bool truncateFile = false);
    static void closeLogFile();

    void flush();

    DebugOut & operator<<(std::ostream & (*pf)(std::ostream&));

    template<typename T>
    DebugOut & operator<<(T & item) {
    	const T & constItem(item);
		return operator <<(constItem);
    }

    template<typename T>
    DebugOut & operator<<(const T & item) {
    	if (showMessage) {
    		logBuffer << item;
    	}
		return *this;
    }

private:

    void outputOnCreate();
    void outputOnDestroy();

    std::ostringstream logBuffer;
    std::ostream & stream;

	const LogLevel level;
	const std::string prefix;
	bool showMessage;

    static Poco::Mutex globalOutputLock;
	static std::ofstream * fileOut;
	static bool isLogFileGood();
};

} /* namespace Util */
} /* namespace SDCLib */
#endif /* DEBUGSTREAM_H_ */
