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
 * OperationHelpers.cpp
 *
 *  Created on: 26.04.2013
 *      Author: roehser
 */

#include "OSCLib/Data/OperationHelpers.h"
#include "OSCLib/Data/QName.h"

namespace OSCLib {
namespace Data {
namespace OperationHelpers {

std::string getDefaultInputAction(const std::string & name, const QName & portType)
{
	return portType.getNamespace() + "/" + portType.getLocal() + "/" + name;
}

std::string getDefaultOutputAction(const std::string & name, const QName & portType)
{
	return portType.getNamespace() + "/" + portType.getLocal() + "/" + name + "Response";
}

std::string getDefaultOutputActionForEventSource(const std::string & name, const QName & portType) {
	return portType.getNamespace() + "/" + portType.getLocal() + "/" + name;
}

std::string getDefaultInputActionForEventSource(const std::string & name, const QName & portType) {
	return portType.getNamespace() + "/" + portType.getLocal() + "/" + name + "Response";
}

}
} /* namespace Data */
} /* namespace OSCLib */
