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
 *  Author: besting, buerger, roehser
 */

/**
 * THIS FILE IS GENERATED AUTOMATICALLY! DO NOT MODIFY!
 *
 * YOUR CHANGES WILL BE OVERWRITTEN!
 *
 * USE THE DEFINITION FILES IN THE FOLDER "codegenerator" INSTEAD!
 */

#include "SDCLib/Data/SDC/MDIB/SetAlertStateOperationDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/CodedValue.h"

namespace SDCLib {
namespace Data {
namespace SDC {


SetAlertStateOperationDescriptor::SetAlertStateOperationDescriptor(
		Handle handle
		,
		HandleRef operationtarget
) : data(Defaults::SetAlertStateOperationDescriptorInit(
		handle
		,
		operationtarget
))
{}

SetAlertStateOperationDescriptor::operator CDM::SetAlertStateOperationDescriptor() const {
	return *data;
}

SetAlertStateOperationDescriptor::SetAlertStateOperationDescriptor(const CDM::SetAlertStateOperationDescriptor & object)
: data(new CDM::SetAlertStateOperationDescriptor(object))
{ }

SetAlertStateOperationDescriptor::SetAlertStateOperationDescriptor(const SetAlertStateOperationDescriptor & object)
: data(std::make_shared<CDM::SetAlertStateOperationDescriptor>(*object.data))
{ }

void SetAlertStateOperationDescriptor::copyFrom(const SetAlertStateOperationDescriptor & object) {
	data = std::make_shared<CDM::SetAlertStateOperationDescriptor>(*object.data);
}

SetAlertStateOperationDescriptor & SetAlertStateOperationDescriptor:: operator=(const SetAlertStateOperationDescriptor& object) {
	copyFrom(object);
	return *this;
}


SetAlertStateOperationDescriptor & SetAlertStateOperationDescriptor::setType(const CodedValue & value) {
	data->setType(ConvertToCDM::convert(value));
	return *this;
}

bool SetAlertStateOperationDescriptor::getType(CodedValue & out) const {
	if (data->getType().present()) {
		out = ConvertFromCDM::convert(data->getType().get());
		return true;
	}
	return false;
}

CodedValue SetAlertStateOperationDescriptor::getType() const {
	return ConvertFromCDM::convert(data->getType().get());
}

bool SetAlertStateOperationDescriptor::hasType() const {
	return data->getType().present();
}

SetAlertStateOperationDescriptor & SetAlertStateOperationDescriptor::setHandle(const Handle & value) {
	data->setHandle(ConvertToCDM::convert(value));
	return *this;
}


Handle SetAlertStateOperationDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->getHandle());
}

SetAlertStateOperationDescriptor & SetAlertStateOperationDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool SetAlertStateOperationDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter SetAlertStateOperationDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool SetAlertStateOperationDescriptor::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

SetAlertStateOperationDescriptor & SetAlertStateOperationDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->setSafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool SetAlertStateOperationDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->getSafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->getSafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification SetAlertStateOperationDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->getSafetyClassification().get());
}

bool SetAlertStateOperationDescriptor::hasSafetyClassification() const {
	return data->getSafetyClassification().present();
}

SetAlertStateOperationDescriptor & SetAlertStateOperationDescriptor::setOperationTarget(const HandleRef & value) {
	data->setOperationTarget(ConvertToCDM::convert(value));
	return *this;
}


HandleRef SetAlertStateOperationDescriptor::getOperationTarget() const {
	return ConvertFromCDM::convert(data->getOperationTarget());
}

SetAlertStateOperationDescriptor & SetAlertStateOperationDescriptor::setMaxTimeToFinish(const xml_schema::Duration & value) {
	data->setMaxTimeToFinish(ConvertToCDM::convert(value));
	return *this;
}

bool SetAlertStateOperationDescriptor::getMaxTimeToFinish(xml_schema::Duration & out) const {
	if (data->getMaxTimeToFinish().present()) {
		out = ConvertFromCDM::convert(data->getMaxTimeToFinish().get());
		return true;
	}
	return false;
}

xml_schema::Duration SetAlertStateOperationDescriptor::getMaxTimeToFinish() const {
	return ConvertFromCDM::convert(data->getMaxTimeToFinish().get());
}

bool SetAlertStateOperationDescriptor::hasMaxTimeToFinish() const {
	return data->getMaxTimeToFinish().present();
}

SetAlertStateOperationDescriptor & SetAlertStateOperationDescriptor::setInvocationEffectiveTimeout(const xml_schema::Duration & value) {
	data->setInvocationEffectiveTimeout(ConvertToCDM::convert(value));
	return *this;
}

bool SetAlertStateOperationDescriptor::getInvocationEffectiveTimeout(xml_schema::Duration & out) const {
	if (data->getInvocationEffectiveTimeout().present()) {
		out = ConvertFromCDM::convert(data->getInvocationEffectiveTimeout().get());
		return true;
	}
	return false;
}

xml_schema::Duration SetAlertStateOperationDescriptor::getInvocationEffectiveTimeout() const {
	return ConvertFromCDM::convert(data->getInvocationEffectiveTimeout().get());
}

bool SetAlertStateOperationDescriptor::hasInvocationEffectiveTimeout() const {
	return data->getInvocationEffectiveTimeout().present();
}

SetAlertStateOperationDescriptor & SetAlertStateOperationDescriptor::setRetriggerable(const bool & value) {
	data->setRetriggerable(ConvertToCDM::convert(value));
	return *this;
}

bool SetAlertStateOperationDescriptor::getRetriggerable(bool & out) const {
	if (data->getRetriggerable().present()) {
		out = ConvertFromCDM::convert(data->getRetriggerable().get());
		return true;
	}
	return false;
}

bool SetAlertStateOperationDescriptor::getRetriggerable() const {
	return ConvertFromCDM::convert(data->getRetriggerable().get());
}

bool SetAlertStateOperationDescriptor::hasRetriggerable() const {
	return data->getRetriggerable().present();
}

SetAlertStateOperationDescriptor & SetAlertStateOperationDescriptor::setAccessLevel(const AccessLevel & value) {
	data->setAccessLevel(ConvertToCDM::convert(value));
	return *this;
}

bool SetAlertStateOperationDescriptor::getAccessLevel(AccessLevel & out) const {
	if (data->getAccessLevel().present()) {
		out = ConvertFromCDM::convert(data->getAccessLevel().get());
		return true;
	}
	return false;
}

AccessLevel SetAlertStateOperationDescriptor::getAccessLevel() const {
	return ConvertFromCDM::convert(data->getAccessLevel().get());
}

bool SetAlertStateOperationDescriptor::hasAccessLevel() const {
	return data->getAccessLevel().present();
}

SetAlertStateOperationDescriptor & SetAlertStateOperationDescriptor::addModifiableData(const std::string & value) {
	data->getModifiableData().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<std::string> SetAlertStateOperationDescriptor::getModifiableDataList() const {
	std::vector<std::string> result;
	result.reserve(data->getModifiableData().size());
	for (const auto & value: data->getModifiableData()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void SetAlertStateOperationDescriptor::clearModifiableDataList() {
	data->getModifiableData().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

