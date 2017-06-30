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
 *  SetAlertStateOperationDescriptor.cpp
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

#include "OSCLib/Data/OSCP/MDIB/SetAlertStateOperationDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

SetAlertStateOperationDescriptor::SetAlertStateOperationDescriptor() : data(Defaults::SetAlertStateOperationDescriptor()) {
}

SetAlertStateOperationDescriptor::operator CDM::SetAlertStateOperationDescriptor() const {
	return *data;
}

SetAlertStateOperationDescriptor::SetAlertStateOperationDescriptor(const CDM::SetAlertStateOperationDescriptor & object) : data(new CDM::SetAlertStateOperationDescriptor(object)) {

}

SetAlertStateOperationDescriptor::SetAlertStateOperationDescriptor(const SetAlertStateOperationDescriptor & object) : data(new CDM::SetAlertStateOperationDescriptor(*object.data)) {

}

SetAlertStateOperationDescriptor::~SetAlertStateOperationDescriptor() {

}

void SetAlertStateOperationDescriptor::copyFrom(const SetAlertStateOperationDescriptor & object) {
	*data = *object.data;
}

SetAlertStateOperationDescriptor & SetAlertStateOperationDescriptor:: operator=(const SetAlertStateOperationDescriptor & object) {
	copyFrom(object);
	return *this;
}


SetAlertStateOperationDescriptor & SetAlertStateOperationDescriptor::setType(const CodedValue & value) {
	data->Type(ConvertToCDM::convert(value));
	return *this;
}

bool SetAlertStateOperationDescriptor::getType(CodedValue & out) const {
	if (data->Type().present()) {
		out = ConvertFromCDM::convert(data->Type().get());
		return true;
	}
	return false;
}

CodedValue SetAlertStateOperationDescriptor::getType() const {
	return ConvertFromCDM::convert(data->Type().get());
}
	
bool SetAlertStateOperationDescriptor::hasType() const {
	return data->Type().present();
}
	
SetAlertStateOperationDescriptor & SetAlertStateOperationDescriptor::setHandle(const Handle & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}


Handle SetAlertStateOperationDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->Handle());
}
	
SetAlertStateOperationDescriptor & SetAlertStateOperationDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool SetAlertStateOperationDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter SetAlertStateOperationDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}
	
bool SetAlertStateOperationDescriptor::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}
	
SetAlertStateOperationDescriptor & SetAlertStateOperationDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->SafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool SetAlertStateOperationDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->SafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->SafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification SetAlertStateOperationDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->SafetyClassification().get());
}
	
bool SetAlertStateOperationDescriptor::hasSafetyClassification() const {
	return data->SafetyClassification().present();
}
	
SetAlertStateOperationDescriptor & SetAlertStateOperationDescriptor::setOperationTarget(const HandleRef & value) {
	data->OperationTarget(ConvertToCDM::convert(value));
	return *this;
}


HandleRef SetAlertStateOperationDescriptor::getOperationTarget() const {
	return ConvertFromCDM::convert(data->OperationTarget());
}
	
SetAlertStateOperationDescriptor & SetAlertStateOperationDescriptor::addModifiableElement(const std::string & value) {
	data->ModifiableElement().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<std::string> SetAlertStateOperationDescriptor::getModifiableElementLists() const {
	std::vector<std::string> result;
	result.reserve(data->ModifiableElement().size());
	for (const auto & value: data->ModifiableElement()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void SetAlertStateOperationDescriptor::clearModifiableElementLists() {
	data->ModifiableElement().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

