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
 *  SetValueOperationDescriptor.cpp
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

#include "OSCLib/Data/OSCP/MDIB/SetValueOperationDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/VersionCounter.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

SetValueOperationDescriptor::SetValueOperationDescriptor() : data(Defaults::SetValueOperationDescriptor()) {
}

SetValueOperationDescriptor::operator CDM::SetValueOperationDescriptor() const {
	return *data;
}

SetValueOperationDescriptor::SetValueOperationDescriptor(const CDM::SetValueOperationDescriptor & object) : data(new CDM::SetValueOperationDescriptor(object)) {

}

SetValueOperationDescriptor::SetValueOperationDescriptor(const SetValueOperationDescriptor & object) : data(new CDM::SetValueOperationDescriptor(*object.data)) {

}

SetValueOperationDescriptor::~SetValueOperationDescriptor() {

}

void SetValueOperationDescriptor::copyFrom(const SetValueOperationDescriptor & object) {
	*data = *object.data;
}

SetValueOperationDescriptor & SetValueOperationDescriptor:: operator=(const SetValueOperationDescriptor & object) {
	copyFrom(object);
	return *this;
}


SetValueOperationDescriptor & SetValueOperationDescriptor::setType(const CodedValue & value) {
	data->Type(ConvertToCDM::convert(value));
	return *this;
}

bool SetValueOperationDescriptor::getType(CodedValue & out) const {
	if (data->Type().present()) {
		out = ConvertFromCDM::convert(data->Type().get());
		return true;
	}
	return false;
}

CodedValue SetValueOperationDescriptor::getType() const {
	return ConvertFromCDM::convert(data->Type().get());
}
	
bool SetValueOperationDescriptor::hasType() const {
	return data->Type().present();
}
	
SetValueOperationDescriptor & SetValueOperationDescriptor::setHandle(const std::string & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}


std::string SetValueOperationDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->Handle());
}
	
SetValueOperationDescriptor & SetValueOperationDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool SetValueOperationDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter SetValueOperationDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}
	
bool SetValueOperationDescriptor::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}
	
SetValueOperationDescriptor & SetValueOperationDescriptor::setIntendedUse(const IntendedUse & value) {
	data->IntendedUse(ConvertToCDM::convert(value));
	return *this;
}

bool SetValueOperationDescriptor::getIntendedUse(IntendedUse & out) const {
	if (data->IntendedUse().present()) {
		out = ConvertFromCDM::convert(data->IntendedUse().get());
		return true;
	}
	return false;
}

IntendedUse SetValueOperationDescriptor::getIntendedUse() const {
	return ConvertFromCDM::convert(data->IntendedUse().get());
}
	
bool SetValueOperationDescriptor::hasIntendedUse() const {
	return data->IntendedUse().present();
}
	
SetValueOperationDescriptor & SetValueOperationDescriptor::setOperationTarget(const std::string & value) {
	data->OperationTarget(ConvertToCDM::convert(value));
	return *this;
}


std::string SetValueOperationDescriptor::getOperationTarget() const {
	return ConvertFromCDM::convert(data->OperationTarget());
}
	
SetValueOperationDescriptor & SetValueOperationDescriptor::addModifiableElement(const CodedValue & value) {
	data->ModifiableElement().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<CodedValue> SetValueOperationDescriptor::getModifiableElements() const {
	std::vector<CodedValue> result;
	result.reserve(data->ModifiableElement().size());
	for (const auto & value: data->ModifiableElement()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void SetValueOperationDescriptor::clearModifiableElements() {
	data->ModifiableElement().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

