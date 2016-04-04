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
 *  @file AbstractBinding.cpp
 *  @project OSCLib
 *  @date 14.07.2011
 *  @author Besting
 *  @copyright (c) SurgiTAIX AG
 *
 */

#include "OSCLib/Comm/AbstractBinding.h"

namespace OSCLib {
namespace Comm {

AbstractBinding::AbstractBinding(): type(AbstractBinding::TCP_HTTP)
{
}

AbstractBinding::AbstractBinding(BindingType bType): type(bType)
{

}

AbstractBinding::AbstractBinding(const AbstractBinding & source) : type(source.getType())
{
}

AbstractBinding::~AbstractBinding()
{
}

AbstractBinding::BindingType AbstractBinding::getType() const
{
	return type;
}


void AbstractBinding::setType(BindingType newType)
{
	this->type = newType;
}

} /* namespace Comm */
} /* namespace OSCLib */
