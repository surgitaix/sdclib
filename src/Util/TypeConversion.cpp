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
 * TypeConversion.cpp
 *
 *  Created on: 04.03.2013
 *      Author: roehser
 */

#include "OSCLib/Util/TypeConversion.h"

namespace OSCLib {
namespace Util {

StringVector splitString(const std::string & input, char seperator) {

	std::string subString;
	std::istringstream isstream(input);
	StringVector output;

	while (!isstream.eof()) {
		getline(isstream, subString, seperator);
		if (subString.length() > 0) {
			output.push_back(subString);
		}
	}
	return output;
}

std::string joinString(const StringVector & input) {
	StringVector::const_iterator sIt;
	std::string result("");
	sIt = input.begin();
	while(sIt != input.end())
	{
		result.append(*sIt);
		++sIt;
		if(sIt != input.end())
			result.append(" ");
	}
	return result;
}

int stringToInt(const std::string & input) {
	int result = 0;
	std::istringstream isstream(input);
	isstream >> result;
	return result;
}


int hexStringToPositiveInt(const std::string & hexValue) {
	std::stringstream ss;
	ss << std::hex << hexValue;
	int value = -1;
	ss >> value;
	return value;
}

} /* namespace Util */
} /* namespace OSCLib */
