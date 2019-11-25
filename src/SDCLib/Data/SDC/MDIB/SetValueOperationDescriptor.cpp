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

#include "SDCLib/Data/SDC/MDIB/SetValueOperationDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/CodedValue.h"

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
	data->setType(ConvertToCDM::convert(value));
	return *this;
}

bool SetValueOperationDescriptor::getType(CodedValue & out) const {
	if (data->getType().present()) {
		out = ConvertFromCDM::convert(data->getType().get());
		return true;
	}
	return false;
}

CodedValue SetValueOperationDescriptor::getType() const {
	return ConvertFromCDM::convert(data->getType().get());
}

bool SetValueOperationDescriptor::hasType() const {
	return data->getType().present();
}

SetValueOperationDescriptor & SetValueOperationDescriptor::setHandle(const Handle & value) {
	data->setHandle(ConvertToCDM::convert(value));
	return *this;
}


Handle SetValueOperationDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->getHandle());
}

SetValueOperationDescriptor & SetValueOperationDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool SetValueOperationDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter SetValueOperationDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool SetValueOperationDescriptor::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

SetValueOperationDescriptor & SetValueOperationDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->setSafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool SetValueOperationDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->getSafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->getSafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification SetValueOperationDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->getSafetyClassification().get());
}

bool SetValueOperationDescriptor::hasSafetyClassification() const {
	return data->getSafetyClassification().present();
}

SetValueOperationDescriptor & SetValueOperationDescriptor::setOperationTarget(const HandleRef & value) {
	data->setOperationTarget(ConvertToCDM::convert(value));
	return *this;
}


HandleRef SetValueOperationDescriptor::getOperationTarget() const {
	return ConvertFromCDM::convert(data->getOperationTarget());
}

SetValueOperationDescriptor & SetValueOperationDescriptor::setMaxTimeToFinish(const xml_schema::Duration & value) {
	data->setMaxTimeToFinish(ConvertToCDM::convert(value));
	return *this;
}

bool SetValueOperationDescriptor::getMaxTimeToFinish(xml_schema::Duration & out) const {
	if (data->getMaxTimeToFinish().present()) {
		out = ConvertFromCDM::convert(data->getMaxTimeToFinish().get());
		return true;
	}
	return false;
}

xml_schema::Duration SetValueOperationDescriptor::getMaxTimeToFinish() const {
	return ConvertFromCDM::convert(data->getMaxTimeToFinish().get());
}

bool SetValueOperationDescriptor::hasMaxTimeToFinish() const {
	return data->getMaxTimeToFinish().present();
}

SetValueOperationDescriptor & SetValueOperationDescriptor::setInvocationEffectiveTimeout(const xml_schema::Duration & value) {
	data->setInvocationEffectiveTimeout(ConvertToCDM::convert(value));
	return *this;
}

bool SetValueOperationDescriptor::getInvocationEffectiveTimeout(xml_schema::Duration & out) const {
	if (data->getInvocationEffectiveTimeout().present()) {
		out = ConvertFromCDM::convert(data->getInvocationEffectiveTimeout().get());
		return true;
	}
	return false;
}

xml_schema::Duration SetValueOperationDescriptor::getInvocationEffectiveTimeout() const {
	return ConvertFromCDM::convert(data->getInvocationEffectiveTimeout().get());
}

bool SetValueOperationDescriptor::hasInvocationEffectiveTimeout() const {
	return data->getInvocationEffectiveTimeout().present();
}

SetValueOperationDescriptor & SetValueOperationDescriptor::setRetriggerable(const bool & value) {
	data->setRetriggerable(ConvertToCDM::convert(value));
	return *this;
}

bool SetValueOperationDescriptor::getRetriggerable(bool & out) const {
	if (data->getRetriggerable().present()) {
		out = ConvertFromCDM::convert(data->getRetriggerable().get());
		return true;
	}
	return false;
}

bool SetValueOperationDescriptor::getRetriggerable() const {
	return ConvertFromCDM::convert(data->getRetriggerable().get());
}

bool SetValueOperationDescriptor::hasRetriggerable() const {
	return data->getRetriggerable().present();
}

SetValueOperationDescriptor & SetValueOperationDescriptor::setAccessLevel(const AccessLevel & value) {
	data->setAccessLevel(ConvertToCDM::convert(value));
	return *this;
}

bool SetValueOperationDescriptor::getAccessLevel(AccessLevel & out) const {
	if (data->getAccessLevel().present()) {
		out = ConvertFromCDM::convert(data->getAccessLevel().get());
		return true;
	}
	return false;
}

AccessLevel SetValueOperationDescriptor::getAccessLevel() const {
	return ConvertFromCDM::convert(data->getAccessLevel().get());
}

bool SetValueOperationDescriptor::hasAccessLevel() const {
	return data->getAccessLevel().present();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

