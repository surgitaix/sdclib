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
 * RemoteOperation.h
 *
 *  @Copyright (C) 2014, SurgiTAIX AG
 *  Author: besting, roehser
 */

#ifndef REMOTEOPERATION_H_
#define REMOTEOPERATION_H_

#include "Operation.h"

namespace OSCLib {
namespace Data {

class RemoteOperation : public OSCLib::Data::Operation {
public:
	RemoteOperation();
	RemoteOperation(const std::string & name, const QName & portType);
	virtual ~RemoteOperation();

	Parameters invoke(Parameters & p);
};

}
}

#endif /* REMOTEOPERATION_H_ */
