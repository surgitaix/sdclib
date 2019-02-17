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
 *  Author: besting, buerger, roehser
 */

/**
 * THIS FILE IS GENERATED AUTOMATICALLY! DO NOT MODIFY!
 *
 * YOUR CHANGES WILL BE OVERWRITTEN!
 *
 * USE THE DEFINITION FILES IN THE FOLDER "codegenerator" INSTEAD!
 */

#include "OSCLib/Data/SDC/MDIB/SetValueOperationDescriptor.h"
#include "OSCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/SDC/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/SDC/MDIB/CodedValue.h"

namespace SDCLib {
namespace Data {
namespace SDC {


SetValueOperationDescriptor::SetValueOperationDescriptor(
		Handle handle
		,
		HandleRef operationtarget
) : data(Defaults::SetValueOperationDescriptorInit(
		handle
		,
		operationtarget
)) {}

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
	data = std::shared_ptr<CDM::SetValueOperationDescriptor>( new CDM::SetValueOperationDescriptor(*object.data));
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

SetValueOperationDescriptor & SetValueOperationDescriptor::setHandle(const Handle & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}


Handle SetValueOperationDescriptor::getHandle() const {
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

SetValueOperationDescriptor & SetValueOperationDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->SafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool SetValueOperationDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->SafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->SafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification SetValueOperationDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->SafetyClassification().get());
}

bool SetValueOperationDescriptor::hasSafetyClassification() const {
	return data->SafetyClassification().present();
}

SetValueOperationDescriptor & SetValueOperationDescriptor::setOperationTarget(const HandleRef & value) {
	data->OperationTarget(ConvertToCDM::convert(value));
	return *this;
}


HandleRef SetValueOperationDescriptor::getOperationTarget() const {
	return ConvertFromCDM::convert(data->OperationTarget());
}

SetValueOperationDescriptor & SetValueOperationDescriptor::setMaxTimeToFinish(const xml_schema::Duration & value) {
	data->MaxTimeToFinish(ConvertToCDM::convert(value));
	return *this;
}

bool SetValueOperationDescriptor::getMaxTimeToFinish(xml_schema::Duration & out) const {
	if (data->MaxTimeToFinish().present()) {
		out = ConvertFromCDM::convert(data->MaxTimeToFinish().get());
		return true;
	}
	return false;
}

xml_schema::Duration SetValueOperationDescriptor::getMaxTimeToFinish() const {
	return ConvertFromCDM::convert(data->MaxTimeToFinish().get());
}

bool SetValueOperationDescriptor::hasMaxTimeToFinish() const {
	return data->MaxTimeToFinish().present();
}

SetValueOperationDescriptor & SetValueOperationDescriptor::setInvocationEffectiveTimeout(const xml_schema::Duration & value) {
	data->InvocationEffectiveTimeout(ConvertToCDM::convert(value));
	return *this;
}

bool SetValueOperationDescriptor::getInvocationEffectiveTimeout(xml_schema::Duration & out) const {
	if (data->InvocationEffectiveTimeout().present()) {
		out = ConvertFromCDM::convert(data->InvocationEffectiveTimeout().get());
		return true;
	}
	return false;
}

xml_schema::Duration SetValueOperationDescriptor::getInvocationEffectiveTimeout() const {
	return ConvertFromCDM::convert(data->InvocationEffectiveTimeout().get());
}

bool SetValueOperationDescriptor::hasInvocationEffectiveTimeout() const {
	return data->InvocationEffectiveTimeout().present();
}

SetValueOperationDescriptor & SetValueOperationDescriptor::setRetriggerable(const bool & value) {
	data->Retriggerable(ConvertToCDM::convert(value));
	return *this;
}

bool SetValueOperationDescriptor::getRetriggerable(bool & out) const {
	if (data->Retriggerable().present()) {
		out = ConvertFromCDM::convert(data->Retriggerable().get());
		return true;
	}
	return false;
}

bool SetValueOperationDescriptor::getRetriggerable() const {
	return ConvertFromCDM::convert(data->Retriggerable().get());
}

bool SetValueOperationDescriptor::hasRetriggerable() const {
	return data->Retriggerable().present();
}

SetValueOperationDescriptor & SetValueOperationDescriptor::setAccessLevel(const AccessLevel & value) {
	data->AccessLevel(ConvertToCDM::convert(value));
	return *this;
}

bool SetValueOperationDescriptor::getAccessLevel(AccessLevel & out) const {
	if (data->AccessLevel().present()) {
		out = ConvertFromCDM::convert(data->AccessLevel().get());
		return true;
	}
	return false;
}

AccessLevel SetValueOperationDescriptor::getAccessLevel() const {
	return ConvertFromCDM::convert(data->AccessLevel().get());
}

bool SetValueOperationDescriptor::hasAccessLevel() const {
	return data->AccessLevel().present();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

