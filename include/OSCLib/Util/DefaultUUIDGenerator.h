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
 * DefaultUUIDGenerator.h
 *
 *  Created on: 20.02.2013
 *      Author: roehser
 */

#ifndef DEFAULTUUIDGENERATOR_H_
#define DEFAULTUUIDGENERATOR_H_

#include <string>

namespace OSCLib {
namespace Util {

class DefaultUUIDGenerator {
public:
	DefaultUUIDGenerator();
	virtual ~DefaultUUIDGenerator();

	static std::string getUUID();
};

} /* namespace Util */
} /* namespace OSCLib */

#endif /* DEFAULTUUIDGENERATOR_H_ */
