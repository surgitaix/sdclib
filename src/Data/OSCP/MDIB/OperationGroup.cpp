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
 *  OperationGroup.cpp
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

#include "OSCLib/Data/OSCP/MDIB/OperationGroup.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"

namespace OSCLib {
namespace Data {
namespace SDC {

OperationGroup::OperationGroup(
		CodedValue type
) : data(Defaults::OperationGroupInit(
		type
)) {}

OperationGroup::operator CDM::OperationGroup() const {
	return *data;
}

OperationGroup::OperationGroup(const CDM::OperationGroup & object) : data(new CDM::OperationGroup(object)) {

}

OperationGroup::OperationGroup(const OperationGroup & object) : data(new CDM::OperationGroup(*object.data)) {

}

OperationGroup::~OperationGroup() {

}

void OperationGroup::copyFrom(const OperationGroup & object) {
	data = std::shared_ptr<CDM::OperationGroup>( new CDM::OperationGroup(*object.data));
}

OperationGroup & OperationGroup:: operator=(const OperationGroup & object) {
	copyFrom(object);
	return *this;
}


OperationGroup & OperationGroup::setType(const CodedValue & value) {
	data->Type(ConvertToCDM::convert(value));
	return *this;
}


CodedValue OperationGroup::getType() const {
	return ConvertFromCDM::convert(data->Type());
}
	
OperationGroup & OperationGroup::setOperatingMode(const OperatingMode & value) {
	data->OperatingMode(ConvertToCDM::convert(value));
	return *this;
}

bool OperationGroup::getOperatingMode(OperatingMode & out) const {
	if (data->OperatingMode().present()) {
		out = ConvertFromCDM::convert(data->OperatingMode().get());
		return true;
	}
	return false;
}

OperatingMode OperationGroup::getOperatingMode() const {
	return ConvertFromCDM::convert(data->OperatingMode().get());
}
	
bool OperationGroup::hasOperatingMode() const {
	return data->OperatingMode().present();
}
	
OperationGroup & OperationGroup::setOperations(const OperationRef & value) {
	data->Operations(ConvertToCDM::convert1(value));
	return *this;
}

bool OperationGroup::getOperations(OperationRef & out) const {
	if (data->Operations().present()) {
		out = ConvertFromCDM::convert(data->Operations().get());
		return true;
	}
	return false;
}

OperationRef OperationGroup::getOperations() const {
	return ConvertFromCDM::convert(data->Operations().get());
}
	
bool OperationGroup::hasOperations() const {
	return data->Operations().present();
}
	

} /* namespace SDC */
} /* namespace Data */
} /* namespace OSCLib */

