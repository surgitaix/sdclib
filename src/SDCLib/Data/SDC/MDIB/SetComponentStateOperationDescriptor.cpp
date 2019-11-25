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
 *  Author: besting, buerger, roehser
 */

/**
 * THIS FILE IS GENERATED AUTOMATICALLY! DO NOT MODIFY!
 *
 * YOUR CHANGES WILL BE OVERWRITTEN!
 *
 * USE THE DEFINITION FILES IN THE FOLDER "codegenerator" INSTEAD!
 */

#include "SDCLib/Data/SDC/MDIB/SetComponentStateOperationDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/CodedValue.h"

namespace SDCLib {
namespace Data {
namespace SDC {


SetComponentStateOperationDescriptor::SetComponentStateOperationDescriptor(
		Handle handle
		,
		HandleRef operationtarget
) : data(Defaults::SetComponentStateOperationDescriptorInit(
		handle
		,
		operationtarget
)) {}

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
	data = std::shared_ptr<CDM::SetComponentStateOperationDescriptor>( new CDM::SetComponentStateOperationDescriptor(*object.data));
}

SetComponentStateOperationDescriptor & SetComponentStateOperationDescriptor:: operator=(const SetComponentStateOperationDescriptor & object) {
	copyFrom(object);
	return *this;
}


SetComponentStateOperationDescriptor & SetComponentStateOperationDescriptor::setType(const CodedValue & value) {
	data->setType(ConvertToCDM::convert(value));
	return *this;
}

bool SetComponentStateOperationDescriptor::getType(CodedValue & out) const {
	if (data->getType().present()) {
		out = ConvertFromCDM::convert(data->getType().get());
		return true;
	}
	return false;
}

CodedValue SetComponentStateOperationDescriptor::getType() const {
	return ConvertFromCDM::convert(data->getType().get());
}

bool SetComponentStateOperationDescriptor::hasType() const {
	return data->getType().present();
}

SetComponentStateOperationDescriptor & SetComponentStateOperationDescriptor::setHandle(const Handle & value) {
	data->setHandle(ConvertToCDM::convert(value));
	return *this;
}


Handle SetComponentStateOperationDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->getHandle());
}

SetComponentStateOperationDescriptor & SetComponentStateOperationDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool SetComponentStateOperationDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter SetComponentStateOperationDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool SetComponentStateOperationDescriptor::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

SetComponentStateOperationDescriptor & SetComponentStateOperationDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->setSafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool SetComponentStateOperationDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->getSafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->getSafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification SetComponentStateOperationDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->getSafetyClassification().get());
}

bool SetComponentStateOperationDescriptor::hasSafetyClassification() const {
	return data->getSafetyClassification().present();
}

SetComponentStateOperationDescriptor & SetComponentStateOperationDescriptor::setOperationTarget(const HandleRef & value) {
	data->setOperationTarget(ConvertToCDM::convert(value));
	return *this;
}


HandleRef SetComponentStateOperationDescriptor::getOperationTarget() const {
	return ConvertFromCDM::convert(data->getOperationTarget());
}

SetComponentStateOperationDescriptor & SetComponentStateOperationDescriptor::setMaxTimeToFinish(const xml_schema::Duration & value) {
	data->setMaxTimeToFinish(ConvertToCDM::convert(value));
	return *this;
}

bool SetComponentStateOperationDescriptor::getMaxTimeToFinish(xml_schema::Duration & out) const {
	if (data->getMaxTimeToFinish().present()) {
		out = ConvertFromCDM::convert(data->getMaxTimeToFinish().get());
		return true;
	}
	return false;
}

xml_schema::Duration SetComponentStateOperationDescriptor::getMaxTimeToFinish() const {
	return ConvertFromCDM::convert(data->getMaxTimeToFinish().get());
}

bool SetComponentStateOperationDescriptor::hasMaxTimeToFinish() const {
	return data->getMaxTimeToFinish().present();
}

SetComponentStateOperationDescriptor & SetComponentStateOperationDescriptor::setInvocationEffectiveTimeout(const xml_schema::Duration & value) {
	data->setInvocationEffectiveTimeout(ConvertToCDM::convert(value));
	return *this;
}

bool SetComponentStateOperationDescriptor::getInvocationEffectiveTimeout(xml_schema::Duration & out) const {
	if (data->getInvocationEffectiveTimeout().present()) {
		out = ConvertFromCDM::convert(data->getInvocationEffectiveTimeout().get());
		return true;
	}
	return false;
}

xml_schema::Duration SetComponentStateOperationDescriptor::getInvocationEffectiveTimeout() const {
	return ConvertFromCDM::convert(data->getInvocationEffectiveTimeout().get());
}

bool SetComponentStateOperationDescriptor::hasInvocationEffectiveTimeout() const {
	return data->getInvocationEffectiveTimeout().present();
}

SetComponentStateOperationDescriptor & SetComponentStateOperationDescriptor::setRetriggerable(const bool & value) {
	data->setRetriggerable(ConvertToCDM::convert(value));
	return *this;
}

bool SetComponentStateOperationDescriptor::getRetriggerable(bool & out) const {
	if (data->getRetriggerable().present()) {
		out = ConvertFromCDM::convert(data->getRetriggerable().get());
		return true;
	}
	return false;
}

bool SetComponentStateOperationDescriptor::getRetriggerable() const {
	return ConvertFromCDM::convert(data->getRetriggerable().get());
}

bool SetComponentStateOperationDescriptor::hasRetriggerable() const {
	return data->getRetriggerable().present();
}

SetComponentStateOperationDescriptor & SetComponentStateOperationDescriptor::setAccessLevel(const AccessLevel & value) {
	data->setAccessLevel(ConvertToCDM::convert(value));
	return *this;
}

bool SetComponentStateOperationDescriptor::getAccessLevel(AccessLevel & out) const {
	if (data->getAccessLevel().present()) {
		out = ConvertFromCDM::convert(data->getAccessLevel().get());
		return true;
	}
	return false;
}

AccessLevel SetComponentStateOperationDescriptor::getAccessLevel() const {
	return ConvertFromCDM::convert(data->getAccessLevel().get());
}

bool SetComponentStateOperationDescriptor::hasAccessLevel() const {
	return data->getAccessLevel().present();
}

SetComponentStateOperationDescriptor & SetComponentStateOperationDescriptor::addModifiableData(const std::string & value) {
	data->getModifiableData().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<std::string> SetComponentStateOperationDescriptor::getModifiableDataList() const {
	std::vector<std::string> result;
	result.reserve(data->getModifiableData().size());
	for (const auto & value: data->getModifiableData()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void SetComponentStateOperationDescriptor::clearModifiableDataList() {
	data->getModifiableData().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

