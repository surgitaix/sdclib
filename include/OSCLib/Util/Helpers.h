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

#ifndef HELPERS_H_
#define HELPERS_H_

#include <string>

namespace OSCLib {
namespace Util {

bool containedMessagesComplete(const std::string & ss);
int countSubstring(const std::string & str, const std::string & sub);

} /* namespace Util */
} /* namespace OSCLib */
#endif /* HELPERS_H_ */
