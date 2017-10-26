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
 *  SetContextStateOperationDescriptor.cpp
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

#include "OSCLib/Data/OSCP/MDIB/SetContextStateOperationDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

SetContextStateOperationDescriptor::SetContextStateOperationDescriptor() : data(Defaults::SetContextStateOperationDescriptor()) {
}

SetContextStateOperationDescriptor::operator CDM::SetContextStateOperationDescriptor() const {
	return *data;
}

SetContextStateOperationDescriptor::SetContextStateOperationDescriptor(const CDM::SetContextStateOperationDescriptor & object) : data(new CDM::SetContextStateOperationDescriptor(object)) {

}

SetContextStateOperationDescriptor::SetContextStateOperationDescriptor(const SetContextStateOperationDescriptor & object) : data(new CDM::SetContextStateOperationDescriptor(*object.data)) {

}

SetContextStateOperationDescriptor::~SetContextStateOperationDescriptor() {

}

void SetContextStateOperationDescriptor::copyFrom(const SetContextStateOperationDescriptor & object) {
	*data = *object.data;
}

SetContextStateOperationDescriptor & SetContextStateOperationDescriptor:: operator=(const SetContextStateOperationDescriptor & object) {
	copyFrom(object);
	return *this;
}


SetContextStateOperationDescriptor & SetContextStateOperationDescriptor::setType(const CodedValue & value) {
	data->Type(ConvertToCDM::convert(value));
	return *this;
}

bool SetContextStateOperationDescriptor::getType(CodedValue & out) const {
	if (data->Type().present()) {
		out = ConvertFromCDM::convert(data->Type().get());
		return true;
	}
	return false;
}

CodedValue SetContextStateOperationDescriptor::getType() const {
	return ConvertFromCDM::convert(data->Type().get());
}
	
bool SetContextStateOperationDescriptor::hasType() const {
	return data->Type().present();
}
	
SetContextStateOperationDescriptor & SetContextStateOperationDescriptor::setHandle(const Handle & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}


Handle SetContextStateOperationDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->Handle());
}
	
SetContextStateOperationDescriptor & SetContextStateOperationDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool SetContextStateOperationDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter SetContextStateOperationDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}
	
bool SetContextStateOperationDescriptor::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}
	
SetContextStateOperationDescriptor & SetContextStateOperationDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->SafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool SetContextStateOperationDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->SafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->SafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification SetContextStateOperationDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->SafetyClassification().get());
}
	
bool SetContextStateOperationDescriptor::hasSafetyClassification() const {
	return data->SafetyClassification().present();
}
	
SetContextStateOperationDescriptor & SetContextStateOperationDescriptor::setOperationTarget(const HandleRef & value) {
	data->OperationTarget(ConvertToCDM::convert(value));
	return *this;
}


HandleRef SetContextStateOperationDescriptor::getOperationTarget() const {
	return ConvertFromCDM::convert(data->OperationTarget());
}
	
SetContextStateOperationDescriptor & SetContextStateOperationDescriptor::setMaxTimeToFinish(const xml_schema::Duration & value) {
	data->MaxTimeToFinish(ConvertToCDM::convert(value));
	return *this;
}

bool SetContextStateOperationDescriptor::getMaxTimeToFinish(xml_schema::Duration & out) const {
	if (data->MaxTimeToFinish().present()) {
		out = ConvertFromCDM::convert(data->MaxTimeToFinish().get());
		return true;
	}
	return false;
}

xml_schema::Duration SetContextStateOperationDescriptor::getMaxTimeToFinish() const {
	return ConvertFromCDM::convert(data->MaxTimeToFinish().get());
}
	
bool SetContextStateOperationDescriptor::hasMaxTimeToFinish() const {
	return data->MaxTimeToFinish().present();
}
	
SetContextStateOperationDescriptor & SetContextStateOperationDescriptor::setInvocationEffectiveTimeout(const xml_schema::Duration & value) {
	data->InvocationEffectiveTimeout(ConvertToCDM::convert(value));
	return *this;
}

bool SetContextStateOperationDescriptor::getInvocationEffectiveTimeout(xml_schema::Duration & out) const {
	if (data->InvocationEffectiveTimeout().present()) {
		out = ConvertFromCDM::convert(data->InvocationEffectiveTimeout().get());
		return true;
	}
	return false;
}

xml_schema::Duration SetContextStateOperationDescriptor::getInvocationEffectiveTimeout() const {
	return ConvertFromCDM::convert(data->InvocationEffectiveTimeout().get());
}
	
bool SetContextStateOperationDescriptor::hasInvocationEffectiveTimeout() const {
	return data->InvocationEffectiveTimeout().present();
}
	
SetContextStateOperationDescriptor & SetContextStateOperationDescriptor::setRetriggerable(const xml_schema::Duration & value) {
	data->Retriggerable(ConvertToCDM::convert(value));
	return *this;
}

bool SetContextStateOperationDescriptor::getRetriggerable(xml_schema::Duration & out) const {
	if (data->Retriggerable().present()) {
		out = ConvertFromCDM::convert(data->Retriggerable().get());
		return true;
	}
	return false;
}

xml_schema::Duration SetContextStateOperationDescriptor::getRetriggerable() const {
	return ConvertFromCDM::convert(data->Retriggerable().get());
}
	
bool SetContextStateOperationDescriptor::hasRetriggerable() const {
	return data->Retriggerable().present();
}
	
SetContextStateOperationDescriptor & SetContextStateOperationDescriptor::setAccessLevel(const AccessLevel & value) {
	data->AccessLevel(ConvertToCDM::convert(value));
	return *this;
}

bool SetContextStateOperationDescriptor::getAccessLevel(AccessLevel & out) const {
	if (data->AccessLevel().present()) {
		out = ConvertFromCDM::convert(data->AccessLevel().get());
		return true;
	}
	return false;
}

AccessLevel SetContextStateOperationDescriptor::getAccessLevel() const {
	return ConvertFromCDM::convert(data->AccessLevel().get());
}
	
bool SetContextStateOperationDescriptor::hasAccessLevel() const {
	return data->AccessLevel().present();
}
	
SetContextStateOperationDescriptor & SetContextStateOperationDescriptor::addModifiableData(const std::string & value) {
	data->ModifiableData().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<std::string> SetContextStateOperationDescriptor::getModifiableDataList() const {
	std::vector<std::string> result;
	result.reserve(data->ModifiableData().size());
	for (const auto & value: data->ModifiableData()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void SetContextStateOperationDescriptor::clearModifiableDataList() {
	data->ModifiableData().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

