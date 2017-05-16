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
 *  AllowedValueType.cpp
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

#include "OSCLib/Data/OSCP/MDIB/AllowedValueType.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

AllowedValueType::AllowedValueType() : data(Defaults::AllowedValueType()) {
}

AllowedValueType::operator CDM::AllowedValueType() const {
	return *data;
}

AllowedValueType::AllowedValueType(const CDM::AllowedValueType & object) : data(new CDM::AllowedValueType(object)) {

}

AllowedValueType::AllowedValueType(const AllowedValueType & object) : data(new CDM::AllowedValueType(*object.data)) {

}

AllowedValueType::~AllowedValueType() {

}

void AllowedValueType::copyFrom(const AllowedValueType & object) {
	*data = *object.data;
}

AllowedValueType & AllowedValueType:: operator=(const AllowedValueType & object) {
	copyFrom(object);
	return *this;
}


AllowedValueType & AllowedValueType::setValue(const std::string & value) {
	data->Value(ConvertToCDM::convert(value));
	return *this;
}


std::string AllowedValueType::getValue() const {
	return ConvertFromCDM::convert(data->Value());
}
	
AllowedValueType & AllowedValueType::setType(const CodedValue & value) {
	data->Type(ConvertToCDM::convert(value));
	return *this;
}


CodedValue AllowedValueType::getType() const {
	return ConvertFromCDM::convert(data->Type());
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

