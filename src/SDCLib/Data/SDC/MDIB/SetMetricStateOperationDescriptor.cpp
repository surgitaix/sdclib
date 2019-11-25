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
 *  Author: besting, buerger, roehser
 */

/**
 * THIS FILE IS GENERATED AUTOMATICALLY! DO NOT MODIFY!
 *
 * YOUR CHANGES WILL BE OVERWRITTEN!
 *
 * USE THE DEFINITION FILES IN THE FOLDER "codegenerator" INSTEAD!
 */

#include "SDCLib/Data/SDC/MDIB/SetMetricStateOperationDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/CodedValue.h"

namespace SDCLib {
namespace Data {
namespace SDC {


SetMetricStateOperationDescriptor::SetMetricStateOperationDescriptor(
		Handle handle
		,
		HandleRef operationtarget
) : data(Defaults::SetMetricStateOperationDescriptorInit(
		handle
		,
		operationtarget
)) {}

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
	data = std::shared_ptr<CDM::SetMetricStateOperationDescriptor>( new CDM::SetMetricStateOperationDescriptor(*object.data));
}

SetMetricStateOperationDescriptor & SetMetricStateOperationDescriptor:: operator=(const SetMetricStateOperationDescriptor & object) {
	copyFrom(object);
	return *this;
}


SetMetricStateOperationDescriptor & SetMetricStateOperationDescriptor::setType(const CodedValue & value) {
	data->setType(ConvertToCDM::convert(value));
	return *this;
}

bool SetMetricStateOperationDescriptor::getType(CodedValue & out) const {
	if (data->getType().present()) {
		out = ConvertFromCDM::convert(data->getType().get());
		return true;
	}
	return false;
}

CodedValue SetMetricStateOperationDescriptor::getType() const {
	return ConvertFromCDM::convert(data->getType().get());
}

bool SetMetricStateOperationDescriptor::hasType() const {
	return data->getType().present();
}

SetMetricStateOperationDescriptor & SetMetricStateOperationDescriptor::setHandle(const Handle & value) {
	data->setHandle(ConvertToCDM::convert(value));
	return *this;
}


Handle SetMetricStateOperationDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->getHandle());
}

SetMetricStateOperationDescriptor & SetMetricStateOperationDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool SetMetricStateOperationDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter SetMetricStateOperationDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool SetMetricStateOperationDescriptor::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

SetMetricStateOperationDescriptor & SetMetricStateOperationDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->setSafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool SetMetricStateOperationDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->getSafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->getSafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification SetMetricStateOperationDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->getSafetyClassification().get());
}

bool SetMetricStateOperationDescriptor::hasSafetyClassification() const {
	return data->getSafetyClassification().present();
}

SetMetricStateOperationDescriptor & SetMetricStateOperationDescriptor::setOperationTarget(const HandleRef & value) {
	data->setOperationTarget(ConvertToCDM::convert(value));
	return *this;
}


HandleRef SetMetricStateOperationDescriptor::getOperationTarget() const {
	return ConvertFromCDM::convert(data->getOperationTarget());
}

SetMetricStateOperationDescriptor & SetMetricStateOperationDescriptor::setMaxTimeToFinish(const xml_schema::Duration & value) {
	data->setMaxTimeToFinish(ConvertToCDM::convert(value));
	return *this;
}

bool SetMetricStateOperationDescriptor::getMaxTimeToFinish(xml_schema::Duration & out) const {
	if (data->getMaxTimeToFinish().present()) {
		out = ConvertFromCDM::convert(data->getMaxTimeToFinish().get());
		return true;
	}
	return false;
}

xml_schema::Duration SetMetricStateOperationDescriptor::getMaxTimeToFinish() const {
	return ConvertFromCDM::convert(data->getMaxTimeToFinish().get());
}

bool SetMetricStateOperationDescriptor::hasMaxTimeToFinish() const {
	return data->getMaxTimeToFinish().present();
}

SetMetricStateOperationDescriptor & SetMetricStateOperationDescriptor::setInvocationEffectiveTimeout(const xml_schema::Duration & value) {
	data->setInvocationEffectiveTimeout(ConvertToCDM::convert(value));
	return *this;
}

bool SetMetricStateOperationDescriptor::getInvocationEffectiveTimeout(xml_schema::Duration & out) const {
	if (data->getInvocationEffectiveTimeout().present()) {
		out = ConvertFromCDM::convert(data->getInvocationEffectiveTimeout().get());
		return true;
	}
	return false;
}

xml_schema::Duration SetMetricStateOperationDescriptor::getInvocationEffectiveTimeout() const {
	return ConvertFromCDM::convert(data->getInvocationEffectiveTimeout().get());
}

bool SetMetricStateOperationDescriptor::hasInvocationEffectiveTimeout() const {
	return data->getInvocationEffectiveTimeout().present();
}

SetMetricStateOperationDescriptor & SetMetricStateOperationDescriptor::setRetriggerable(const bool & value) {
	data->setRetriggerable(ConvertToCDM::convert(value));
	return *this;
}

bool SetMetricStateOperationDescriptor::getRetriggerable(bool & out) const {
	if (data->getRetriggerable().present()) {
		out = ConvertFromCDM::convert(data->getRetriggerable().get());
		return true;
	}
	return false;
}

bool SetMetricStateOperationDescriptor::getRetriggerable() const {
	return ConvertFromCDM::convert(data->getRetriggerable().get());
}

bool SetMetricStateOperationDescriptor::hasRetriggerable() const {
	return data->getRetriggerable().present();
}

SetMetricStateOperationDescriptor & SetMetricStateOperationDescriptor::setAccessLevel(const AccessLevel & value) {
	data->setAccessLevel(ConvertToCDM::convert(value));
	return *this;
}

bool SetMetricStateOperationDescriptor::getAccessLevel(AccessLevel & out) const {
	if (data->getAccessLevel().present()) {
		out = ConvertFromCDM::convert(data->getAccessLevel().get());
		return true;
	}
	return false;
}

AccessLevel SetMetricStateOperationDescriptor::getAccessLevel() const {
	return ConvertFromCDM::convert(data->getAccessLevel().get());
}

bool SetMetricStateOperationDescriptor::hasAccessLevel() const {
	return data->getAccessLevel().present();
}

SetMetricStateOperationDescriptor & SetMetricStateOperationDescriptor::addModifiableData(const std::string & value) {
	data->getModifiableData().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<std::string> SetMetricStateOperationDescriptor::getModifiableDataList() const {
	std::vector<std::string> result;
	result.reserve(data->getModifiableData().size());
	for (const auto & value: data->getModifiableData()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void SetMetricStateOperationDescriptor::clearModifiableDataList() {
	data->getModifiableData().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

