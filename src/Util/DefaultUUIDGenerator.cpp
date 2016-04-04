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
 *  @file UUIDGenerator.cpp
 *  @project OSCLib
 *  @date 21.06.2012
 *  @author besting
 *  @copyright (c) SurgiTAIX AG
 *
 */

#include "OSCLib/Util/DefaultUUIDGenerator.h"

#include "Poco/UUID.h"
#include "Poco/UUIDGenerator.h"

namespace OSCLib {
namespace Util {

DefaultUUIDGenerator::DefaultUUIDGenerator()
{
}

DefaultUUIDGenerator::~DefaultUUIDGenerator()
{
}

std::string DefaultUUIDGenerator::getUUID()
{
	Poco::UUIDGenerator * ugen = new Poco::UUIDGenerator();
	Poco::UUID uuid = ugen->createRandom();
	std::string result = uuid.toString();
	delete ugen;
	return result;
}

} /* namespace Util */
} /* namespace OSCLib */
