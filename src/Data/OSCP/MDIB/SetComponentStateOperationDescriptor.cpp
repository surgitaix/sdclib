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
 *  SetComponentStateOperationDescriptor.cpp
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

#include "OSCLib/Data/OSCP/MDIB/SetComponentStateOperationDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

SetComponentStateOperationDescriptor::SetComponentStateOperationDescriptor() : data(Defaults::SetComponentStateOperationDescriptor()) {
}

SetComponentStateOperationDescriptor::operator CDM::SetComponentStateOperationDescriptor() const {
	return *data;
}

SetComponentStateOperationDescriptor::SetComponentStateOperationDescriptor(const CDM::SetComponentStateOperationDescriptor & object) : data(new CDM::SetComponentStateOperationDescriptor(object)) {

}

SetComponentStateOperationDescriptor::SetComponentStateOperationDescriptor(const SetComponentStateOperationDescriptor & object) : data(new CDM::SetComponentStateOperationDescriptor(*object.data)) {

}

SetComponentStateOperationDescriptor::~SetComponentStateOperationDescriptor() {

}

void SetComponentStateOperationDescriptor::copyFrom(const SetComponentStateOperationDescriptor & object) {
	*data = *object.data;
}

SetComponentStateOperationDescriptor & SetComponentStateOperationDescriptor:: operator=(const SetComponentStateOperationDescriptor & object) {
	copyFrom(object);
	return *this;
}


SetComponentStateOperationDescriptor & SetComponentStateOperationDescriptor::setType(const CodedValue & value) {
	data->Type(ConvertToCDM::convert(value));
	return *this;
}

bool SetComponentStateOperationDescriptor::getType(CodedValue & out) const {
	if (data->Type().present()) {
		out = ConvertFromCDM::convert(data->Type().get());
		return true;
	}
	return false;
}

CodedValue SetComponentStateOperationDescriptor::getType() const {
	return ConvertFromCDM::convert(data->Type().get());
}
	
bool SetComponentStateOperationDescriptor::hasType() const {
	return data->Type().present();
}
	
SetComponentStateOperationDescriptor & SetComponentStateOperationDescriptor::setHandle(const Handle & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}


Handle SetComponentStateOperationDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->Handle());
}
	
SetComponentStateOperationDescriptor & SetComponentStateOperationDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool SetComponentStateOperationDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter SetComponentStateOperationDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}
	
bool SetComponentStateOperationDescriptor::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}
	
SetComponentStateOperationDescriptor & SetComponentStateOperationDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->SafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool SetComponentStateOperationDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->SafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->SafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification SetComponentStateOperationDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->SafetyClassification().get());
}
	
bool SetComponentStateOperationDescriptor::hasSafetyClassification() const {
	return data->SafetyClassification().present();
}
	
SetComponentStateOperationDescriptor & SetComponentStateOperationDescriptor::setOperationTarget(const HandleRef & value) {
	data->OperationTarget(ConvertToCDM::convert(value));
	return *this;
}


HandleRef SetComponentStateOperationDescriptor::getOperationTarget() const {
	return ConvertFromCDM::convert(data->OperationTarget());
}
	
SetComponentStateOperationDescriptor & SetComponentStateOperationDescriptor::addModifiableElement(const std::string & value) {
	data->ModifiableElement().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<std::string> SetComponentStateOperationDescriptor::getModifiableElementLists() const {
	std::vector<std::string> result;
	result.reserve(data->ModifiableElement().size());
	for (const auto & value: data->ModifiableElement()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void SetComponentStateOperationDescriptor::clearModifiableElementLists() {
	data->ModifiableElement().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

