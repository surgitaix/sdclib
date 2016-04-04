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
 * RemoteOperation.cpp
 *
 *  @Copyright (C) 2014, SurgiTAIX AG
 *  Author: besting, roehser
 */

#include "OSCLib/Data/RemoteOperation.h"

#include <stdexcept>

namespace OSCLib {
namespace Data {

RemoteOperation::RemoteOperation() {

}

RemoteOperation::RemoteOperation(const std::string & name, const QName & portType) : Operation(name, portType) {

}

RemoteOperation::~RemoteOperation() {

}

Parameters RemoteOperation::invoke(Parameters & ) {
	throw std::runtime_error("This operation object is intended to be a placeholder for a remote operation. Therefore it is not a operation of a hosted service and calling its invoke operation is forbidden.");
}

}
}
