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

/*
 * Helpers.cpp
 *
 *  @Copyright (C) 2014, SurgiTAIX AG
 *  Author: besting, roehser
 */

#include "OSCLib/Util/Helpers.h"

namespace OSCLib {
namespace Util {

bool containedMessagesComplete(const std::string & s) {
	int envBeg = countSubstring(s, ":Envelope ");
	int envEnd = countSubstring(s, ":Envelope>");
	int httpinfoBeg = countSubstring(s, "<httpinfo>");
	int httpinfoEnd = countSubstring(s, "</httpinfo>");

	return (envBeg == envEnd) && (httpinfoBeg == httpinfoEnd);
}

int countSubstring(const std::string & str, const std::string & sub) {
    if (sub.length() == 0) return 0;
    int count = 0;
    for (size_t offset = str.find(sub); offset != std::string::npos;
	 offset = str.find(sub, offset + sub.length()))
    {
        ++count;
    }
    return count;
}

} /* namespace Util */
} /* namespace OSCLib */
