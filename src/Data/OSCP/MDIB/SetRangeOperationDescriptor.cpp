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
 *  SetRangeOperationDescriptor.cpp
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

#include "OSCLib/Data/OSCP/MDIB/SetRangeOperationDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/Range.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/VersionCounter.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

SetRangeOperationDescriptor::SetRangeOperationDescriptor() : data(Defaults::SetRangeOperationDescriptor()) {
}

SetRangeOperationDescriptor::operator CDM::SetRangeOperationDescriptor() const {
	return *data;
}

SetRangeOperationDescriptor::SetRangeOperationDescriptor(const CDM::SetRangeOperationDescriptor & object) : data(new CDM::SetRangeOperationDescriptor(object)) {

}

SetRangeOperationDescriptor::SetRangeOperationDescriptor(const SetRangeOperationDescriptor & object) : data(new CDM::SetRangeOperationDescriptor(*object.data)) {

}

SetRangeOperationDescriptor::~SetRangeOperationDescriptor() {

}

void SetRangeOperationDescriptor::copyFrom(const SetRangeOperationDescriptor & object) {
	*data = *object.data;
}

SetRangeOperationDescriptor & SetRangeOperationDescriptor:: operator=(const SetRangeOperationDescriptor & object) {
	copyFrom(object);
	return *this;
}


SetRangeOperationDescriptor & SetRangeOperationDescriptor::setType(const CodedValue & value) {
	data->Type(ConvertToCDM::convert(value));
	return *this;
}

bool SetRangeOperationDescriptor::getType(CodedValue & out) const {
	if (data->Type().present()) {
		out = ConvertFromCDM::convert(data->Type().get());
		return true;
	}
	return false;
}

CodedValue SetRangeOperationDescriptor::getType() const {
	return ConvertFromCDM::convert(data->Type().get());
}
	
bool SetRangeOperationDescriptor::hasType() const {
	return data->Type().present();
}
	
SetRangeOperationDescriptor & SetRangeOperationDescriptor::setHandle(const std::string & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}


std::string SetRangeOperationDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->Handle());
}
	
SetRangeOperationDescriptor & SetRangeOperationDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool SetRangeOperationDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter SetRangeOperationDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}
	
bool SetRangeOperationDescriptor::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}
	
SetRangeOperationDescriptor & SetRangeOperationDescriptor::setIntendedUse(const IntendedUse & value) {
	data->IntendedUse(ConvertToCDM::convert(value));
	return *this;
}

bool SetRangeOperationDescriptor::getIntendedUse(IntendedUse & out) const {
	if (data->IntendedUse().present()) {
		out = ConvertFromCDM::convert(data->IntendedUse().get());
		return true;
	}
	return false;
}

IntendedUse SetRangeOperationDescriptor::getIntendedUse() const {
	return ConvertFromCDM::convert(data->IntendedUse().get());
}
	
bool SetRangeOperationDescriptor::hasIntendedUse() const {
	return data->IntendedUse().present();
}
	
SetRangeOperationDescriptor & SetRangeOperationDescriptor::setOperationTarget(const std::string & value) {
	data->OperationTarget(ConvertToCDM::convert(value));
	return *this;
}


std::string SetRangeOperationDescriptor::getOperationTarget() const {
	return ConvertFromCDM::convert(data->OperationTarget());
}
	
SetRangeOperationDescriptor & SetRangeOperationDescriptor::addModifiableElement(const CodedValue & value) {
	data->ModifiableElement().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<CodedValue> SetRangeOperationDescriptor::getModifiableElements() const {
	std::vector<CodedValue> result;
	result.reserve(data->ModifiableElement().size());
	for (const auto & value: data->ModifiableElement()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void SetRangeOperationDescriptor::clearModifiableElements() {
	data->ModifiableElement().clear();
}

SetRangeOperationDescriptor & SetRangeOperationDescriptor::setAllowedMaxRange(const Range & value) {
	data->AllowedMaxRange(ConvertToCDM::convert(value));
	return *this;
}


Range SetRangeOperationDescriptor::getAllowedMaxRange() const {
	return ConvertFromCDM::convert(data->AllowedMaxRange());
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

