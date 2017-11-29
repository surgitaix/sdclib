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
 *  ContainmentTreeEntry.cpp
 *
 *  @Copyright (C) 2015, SurgiTAIX AG
 *  Author: besting, buerger, roehser
 */
 
/**
 * THIS FILE IS GENERATED AUTOMATICALLY! DO NOT MODIFY!
 *
 * YOUR CHANGES WILL BE OVERWRITTEN!
 * 
 * USE THE DEFINITION FILES IN THE FOLDER "codegenerator" INSTEAD!
 */

#include "OSCLib/Data/OSCP/MDIB/ContainmentTreeEntry.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"

namespace OSCLib {
namespace Data {
namespace OSCP {


ContainmentTreeEntry::ContainmentTreeEntry(
) : data(Defaults::ContainmentTreeEntryInit(
)) {}

ContainmentTreeEntry::operator CDM::ContainmentTreeEntry() const {
	return *data;
}

ContainmentTreeEntry::ContainmentTreeEntry(const CDM::ContainmentTreeEntry & object) : data(new CDM::ContainmentTreeEntry(object)) {

}

ContainmentTreeEntry::ContainmentTreeEntry(const ContainmentTreeEntry & object) : data(new CDM::ContainmentTreeEntry(*object.data)) {

}

ContainmentTreeEntry::~ContainmentTreeEntry() {

}

void ContainmentTreeEntry::copyFrom(const ContainmentTreeEntry & object) {
	data = std::shared_ptr<CDM::ContainmentTreeEntry>( new CDM::ContainmentTreeEntry(*object.data));
}

ContainmentTreeEntry & ContainmentTreeEntry:: operator=(const ContainmentTreeEntry & object) {
	copyFrom(object);
	return *this;
}


ContainmentTreeEntry & ContainmentTreeEntry::setType(const CodedValue & value) {
	data->Type(ConvertToCDM::convert(value));
	return *this;
}

bool ContainmentTreeEntry::getType(CodedValue & out) const {
	if (data->Type().present()) {
		out = ConvertFromCDM::convert(data->Type().get());
		return true;
	}
	return false;
}

CodedValue ContainmentTreeEntry::getType() const {
	return ConvertFromCDM::convert(data->Type().get());
}
	
bool ContainmentTreeEntry::hasType() const {
	return data->Type().present();
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

