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
 *  RealTimeValueType.cpp
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

#include "OSCLib/Data/OSCP/MDIB/RealTimeValueType.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"


namespace OSCLib {
namespace Data {
namespace OSCP {

RealTimeValueType::RealTimeValueType() : data(Defaults::RealTimeValueType()) {
}

RealTimeValueType::operator CDM::RealTimeValueType() const {
	return *data;
}

RealTimeValueType::RealTimeValueType(const CDM::RealTimeValueType & object) : data(new CDM::RealTimeValueType(object)) {

}

RealTimeValueType::RealTimeValueType(const RealTimeValueType & object) : data(new CDM::RealTimeValueType(*object.data)) {

}

RealTimeValueType::~RealTimeValueType() {

}

void RealTimeValueType::copyFrom(const RealTimeValueType & object) {
	*data = *object.data;
}

RealTimeValueType & RealTimeValueType:: operator=(const RealTimeValueType & object) {
	copyFrom(object);
	return *this;
}



} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

