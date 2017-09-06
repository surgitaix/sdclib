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
 *  SetStringOperationDescriptor.cpp
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

#include "OSCLib/Data/OSCP/MDIB/SetStringOperationDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

SetStringOperationDescriptor::SetStringOperationDescriptor() : data(Defaults::SetStringOperationDescriptor()) {
}

SetStringOperationDescriptor::operator CDM::SetStringOperationDescriptor() const {
	return *data;
}

SetStringOperationDescriptor::SetStringOperationDescriptor(const CDM::SetStringOperationDescriptor & object) : data(new CDM::SetStringOperationDescriptor(object)) {

}

SetStringOperationDescriptor::SetStringOperationDescriptor(const SetStringOperationDescriptor & object) : data(new CDM::SetStringOperationDescriptor(*object.data)) {

}

SetStringOperationDescriptor::~SetStringOperationDescriptor() {

}

void SetStringOperationDescriptor::copyFrom(const SetStringOperationDescriptor & object) {
	*data = *object.data;
}

SetStringOperationDescriptor & SetStringOperationDescriptor:: operator=(const SetStringOperationDescriptor & object) {
	copyFrom(object);
	return *this;
}


SetStringOperationDescriptor & SetStringOperationDescriptor::setType(const CodedValue & value) {
	data->Type(ConvertToCDM::convert(value));
	return *this;
}

bool SetStringOperationDescriptor::getType(CodedValue & out) const {
	if (data->Type().present()) {
		out = ConvertFromCDM::convert(data->Type().get());
		return true;
	}
	return false;
}

CodedValue SetStringOperationDescriptor::getType() const {
	return ConvertFromCDM::convert(data->Type().get());
}
	
bool SetStringOperationDescriptor::hasType() const {
	return data->Type().present();
}
	
SetStringOperationDescriptor & SetStringOperationDescriptor::setHandle(const Handle & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}


Handle SetStringOperationDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->Handle());
}
	
SetStringOperationDescriptor & SetStringOperationDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool SetStringOperationDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter SetStringOperationDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}
	
bool SetStringOperationDescriptor::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}
	
SetStringOperationDescriptor & SetStringOperationDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->SafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool SetStringOperationDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->SafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->SafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification SetStringOperationDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->SafetyClassification().get());
}
	
bool SetStringOperationDescriptor::hasSafetyClassification() const {
	return data->SafetyClassification().present();
}
	
SetStringOperationDescriptor & SetStringOperationDescriptor::setOperationTarget(const HandleRef & value) {
	data->OperationTarget(ConvertToCDM::convert(value));
	return *this;
}


HandleRef SetStringOperationDescriptor::getOperationTarget() const {
	return ConvertFromCDM::convert(data->OperationTarget());
}
	
SetStringOperationDescriptor & SetStringOperationDescriptor::setMaxLength(const unsigned long & value) {
	data->MaxLength(ConvertToCDM::convert(value));
	return *this;
}

bool SetStringOperationDescriptor::getMaxLength(unsigned long & out) const {
	if (data->MaxLength().present()) {
		out = ConvertFromCDM::convert(data->MaxLength().get());
		return true;
	}
	return false;
}

unsigned long SetStringOperationDescriptor::getMaxLength() const {
	return ConvertFromCDM::convert(data->MaxLength().get());
}
	
bool SetStringOperationDescriptor::hasMaxLength() const {
	return data->MaxLength().present();
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

