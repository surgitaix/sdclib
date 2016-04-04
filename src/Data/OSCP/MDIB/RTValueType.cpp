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
 *  RTValueType.cpp
 *
 *  @Copyright (C) 2015, SurgiTAIX AG
 *  Author: besting, roehser
 */
 
/**
 * THIS FILE IS GENERATED AUTOMATICALLY! DO NOT MODIFY!
 *
 * YOUR CHANGES WILL BE OVERWRITTEN!
 * 
 * USE THE DEFINITION FILES IN THE FOLDER "codegenerator" INSTEAD!
 */

#include "OSCLib/Data/OSCP/MDIB/RTValueType.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"


namespace OSCLib {
namespace Data {
namespace OSCP {

RTValueType::RTValueType() : data(Defaults::RTValueType()) {
}

RTValueType::operator CDM::RTValueType() const {
	return *data;
}

RTValueType::RTValueType(const CDM::RTValueType & object) : data(new CDM::RTValueType(object)) {

}

RTValueType::RTValueType(const RTValueType & object) : data(new CDM::RTValueType(*object.data)) {

}

RTValueType::~RTValueType() {

}

void RTValueType::copyFrom(const RTValueType & object) {
	*data = *object.data;
}

RTValueType & RTValueType:: operator=(const RTValueType & object) {
	copyFrom(object);
	return *this;
}



} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

