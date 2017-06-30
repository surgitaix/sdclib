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
 *  SetMetricStateOperationDescriptor.cpp
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

#include "OSCLib/Data/OSCP/MDIB/SetMetricStateOperationDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

SetMetricStateOperationDescriptor::SetMetricStateOperationDescriptor() : data(Defaults::SetMetricStateOperationDescriptor()) {
}

SetMetricStateOperationDescriptor::operator CDM::SetMetricStateOperationDescriptor() const {
	return *data;
}

SetMetricStateOperationDescriptor::SetMetricStateOperationDescriptor(const CDM::SetMetricStateOperationDescriptor & object) : data(new CDM::SetMetricStateOperationDescriptor(object)) {

}

SetMetricStateOperationDescriptor::SetMetricStateOperationDescriptor(const SetMetricStateOperationDescriptor & object) : data(new CDM::SetMetricStateOperationDescriptor(*object.data)) {

}

SetMetricStateOperationDescriptor::~SetMetricStateOperationDescriptor() {

}

void SetMetricStateOperationDescriptor::copyFrom(const SetMetricStateOperationDescriptor & object) {
	*data = *object.data;
}

SetMetricStateOperationDescriptor & SetMetricStateOperationDescriptor:: operator=(const SetMetricStateOperationDescriptor & object) {
	copyFrom(object);
	return *this;
}


SetMetricStateOperationDescriptor & SetMetricStateOperationDescriptor::setType(const CodedValue & value) {
	data->Type(ConvertToCDM::convert(value));
	return *this;
}

bool SetMetricStateOperationDescriptor::getType(CodedValue & out) const {
	if (data->Type().present()) {
		out = ConvertFromCDM::convert(data->Type().get());
		return true;
	}
	return false;
}

CodedValue SetMetricStateOperationDescriptor::getType() const {
	return ConvertFromCDM::convert(data->Type().get());
}
	
bool SetMetricStateOperationDescriptor::hasType() const {
	return data->Type().present();
}
	
SetMetricStateOperationDescriptor & SetMetricStateOperationDescriptor::setHandle(const Handle & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}


Handle SetMetricStateOperationDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->Handle());
}
	
SetMetricStateOperationDescriptor & SetMetricStateOperationDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool SetMetricStateOperationDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter SetMetricStateOperationDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}
	
bool SetMetricStateOperationDescriptor::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}
	
SetMetricStateOperationDescriptor & SetMetricStateOperationDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->SafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool SetMetricStateOperationDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->SafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->SafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification SetMetricStateOperationDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->SafetyClassification().get());
}
	
bool SetMetricStateOperationDescriptor::hasSafetyClassification() const {
	return data->SafetyClassification().present();
}
	
SetMetricStateOperationDescriptor & SetMetricStateOperationDescriptor::setOperationTarget(const HandleRef & value) {
	data->OperationTarget(ConvertToCDM::convert(value));
	return *this;
}


HandleRef SetMetricStateOperationDescriptor::getOperationTarget() const {
	return ConvertFromCDM::convert(data->OperationTarget());
}
	
SetMetricStateOperationDescriptor & SetMetricStateOperationDescriptor::addModifiableElement(const std::string & value) {
	data->ModifiableElement().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<std::string> SetMetricStateOperationDescriptor::getModifiableElementLists() const {
	std::vector<std::string> result;
	result.reserve(data->ModifiableElement().size());
	for (const auto & value: data->ModifiableElement()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void SetMetricStateOperationDescriptor::clearModifiableElementLists() {
	data->ModifiableElement().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

