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
 *  EnumNomenRef.cpp
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

#include "OSCLib/Data/OSCP/MDIB/EnumNomenRef.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/SampleIndex.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

EnumNomenRef::EnumNomenRef() : data(Defaults::EnumNomenRef()) {
}

EnumNomenRef::operator CDM::EnumNomenRef() const {
	return *data;
}

EnumNomenRef::EnumNomenRef(const CDM::EnumNomenRef & object) : data(new CDM::EnumNomenRef(object)) {

}

EnumNomenRef::EnumNomenRef(const EnumNomenRef & object) : data(new CDM::EnumNomenRef(*object.data)) {

}

EnumNomenRef::~EnumNomenRef() {

}

void EnumNomenRef::copyFrom(const EnumNomenRef & object) {
	*data = *object.data;
}

EnumNomenRef & EnumNomenRef:: operator=(const EnumNomenRef & object) {
	copyFrom(object);
	return *this;
}


EnumNomenRef & EnumNomenRef::setCode(const CodedValue & value) {
	data->Code(ConvertToCDM::convert(value));
	return *this;
}


CodedValue EnumNomenRef::getCode() const {
	return ConvertFromCDM::convert(data->Code());
}
	
EnumNomenRef & EnumNomenRef::setEnumIndex(const SampleIndex & value) {
	data->EnumIndex(ConvertToCDM::convert(value));
	return *this;
}

bool EnumNomenRef::getEnumIndex(SampleIndex & out) const {
	if (data->EnumIndex().present()) {
		out = ConvertFromCDM::convert(data->EnumIndex().get());
		return true;
	}
	return false;
}

SampleIndex EnumNomenRef::getEnumIndex() const {
	return ConvertFromCDM::convert(data->EnumIndex().get());
}
	
bool EnumNomenRef::hasEnumIndex() const {
	return data->EnumIndex().present();
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

