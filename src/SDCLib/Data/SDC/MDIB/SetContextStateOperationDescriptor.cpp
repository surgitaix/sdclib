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
 *  Author: besting, buerger, roehser
 */

/**
 * THIS FILE IS GENERATED AUTOMATICALLY! DO NOT MODIFY!
 *
 * YOUR CHANGES WILL BE OVERWRITTEN!
 *
 * USE THE DEFINITION FILES IN THE FOLDER "codegenerator" INSTEAD!
 */

#include "SDCLib/Data/SDC/MDIB/SetContextStateOperationDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/CodedValue.h"

namespace SDCLib {
namespace Data {
namespace SDC {


SetContextStateOperationDescriptor::SetContextStateOperationDescriptor(
		Handle handle
		,
		HandleRef operationtarget
) : data(Defaults::SetContextStateOperationDescriptorInit(
		handle
		,
		operationtarget
))
{}

SetContextStateOperationDescriptor::operator CDM::SetContextStateOperationDescriptor() const {
	return *data;
}

SetContextStateOperationDescriptor::SetContextStateOperationDescriptor(const CDM::SetContextStateOperationDescriptor & object)
: data(new CDM::SetContextStateOperationDescriptor(object))
{ }

SetContextStateOperationDescriptor::SetContextStateOperationDescriptor(const SetContextStateOperationDescriptor & object)
: data(std::make_shared<CDM::SetContextStateOperationDescriptor>(*object.data))
{ }

void SetContextStateOperationDescriptor::copyFrom(const SetContextStateOperationDescriptor & object) {
	data = std::make_shared<CDM::SetContextStateOperationDescriptor>(*object.data);
}

SetContextStateOperationDescriptor & SetContextStateOperationDescriptor:: operator=(const SetContextStateOperationDescriptor& object) {
	copyFrom(object);
	return *this;
}


SetContextStateOperationDescriptor & SetContextStateOperationDescriptor::setType(const CodedValue & value) {
	data->setType(ConvertToCDM::convert(value));
	return *this;
}

bool SetContextStateOperationDescriptor::getType(CodedValue & out) const {
	if (data->getType().present()) {
		out = ConvertFromCDM::convert(data->getType().get());
		return true;
	}
	return false;
}

CodedValue SetContextStateOperationDescriptor::getType() const {
	return ConvertFromCDM::convert(data->getType().get());
}

bool SetContextStateOperationDescriptor::hasType() const {
	return data->getType().present();
}

SetContextStateOperationDescriptor & SetContextStateOperationDescriptor::setHandle(const Handle & value) {
	data->setHandle(ConvertToCDM::convert(value));
	return *this;
}


Handle SetContextStateOperationDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->getHandle());
}

SetContextStateOperationDescriptor & SetContextStateOperationDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool SetContextStateOperationDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter SetContextStateOperationDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool SetContextStateOperationDescriptor::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

SetContextStateOperationDescriptor & SetContextStateOperationDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->setSafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool SetContextStateOperationDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->getSafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->getSafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification SetContextStateOperationDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->getSafetyClassification().get());
}

bool SetContextStateOperationDescriptor::hasSafetyClassification() const {
	return data->getSafetyClassification().present();
}

SetContextStateOperationDescriptor & SetContextStateOperationDescriptor::setOperationTarget(const HandleRef & value) {
	data->setOperationTarget(ConvertToCDM::convert(value));
	return *this;
}


HandleRef SetContextStateOperationDescriptor::getOperationTarget() const {
	return ConvertFromCDM::convert(data->getOperationTarget());
}

SetContextStateOperationDescriptor & SetContextStateOperationDescriptor::setMaxTimeToFinish(const xml_schema::Duration & value) {
	data->setMaxTimeToFinish(ConvertToCDM::convert(value));
	return *this;
}

bool SetContextStateOperationDescriptor::getMaxTimeToFinish(xml_schema::Duration & out) const {
	if (data->getMaxTimeToFinish().present()) {
		out = ConvertFromCDM::convert(data->getMaxTimeToFinish().get());
		return true;
	}
	return false;
}

xml_schema::Duration SetContextStateOperationDescriptor::getMaxTimeToFinish() const {
	return ConvertFromCDM::convert(data->getMaxTimeToFinish().get());
}

bool SetContextStateOperationDescriptor::hasMaxTimeToFinish() const {
	return data->getMaxTimeToFinish().present();
}

SetContextStateOperationDescriptor & SetContextStateOperationDescriptor::setInvocationEffectiveTimeout(const xml_schema::Duration & value) {
	data->setInvocationEffectiveTimeout(ConvertToCDM::convert(value));
	return *this;
}

bool SetContextStateOperationDescriptor::getInvocationEffectiveTimeout(xml_schema::Duration & out) const {
	if (data->getInvocationEffectiveTimeout().present()) {
		out = ConvertFromCDM::convert(data->getInvocationEffectiveTimeout().get());
		return true;
	}
	return false;
}

xml_schema::Duration SetContextStateOperationDescriptor::getInvocationEffectiveTimeout() const {
	return ConvertFromCDM::convert(data->getInvocationEffectiveTimeout().get());
}

bool SetContextStateOperationDescriptor::hasInvocationEffectiveTimeout() const {
	return data->getInvocationEffectiveTimeout().present();
}

SetContextStateOperationDescriptor & SetContextStateOperationDescriptor::setRetriggerable(const bool & value) {
	data->setRetriggerable(ConvertToCDM::convert(value));
	return *this;
}

bool SetContextStateOperationDescriptor::getRetriggerable(bool & out) const {
	if (data->getRetriggerable().present()) {
		out = ConvertFromCDM::convert(data->getRetriggerable().get());
		return true;
	}
	return false;
}

bool SetContextStateOperationDescriptor::getRetriggerable() const {
	return ConvertFromCDM::convert(data->getRetriggerable().get());
}

bool SetContextStateOperationDescriptor::hasRetriggerable() const {
	return data->getRetriggerable().present();
}

SetContextStateOperationDescriptor & SetContextStateOperationDescriptor::setAccessLevel(const AccessLevel & value) {
	data->setAccessLevel(ConvertToCDM::convert(value));
	return *this;
}

bool SetContextStateOperationDescriptor::getAccessLevel(AccessLevel & out) const {
	if (data->getAccessLevel().present()) {
		out = ConvertFromCDM::convert(data->getAccessLevel().get());
		return true;
	}
	return false;
}

AccessLevel SetContextStateOperationDescriptor::getAccessLevel() const {
	return ConvertFromCDM::convert(data->getAccessLevel().get());
}

bool SetContextStateOperationDescriptor::hasAccessLevel() const {
	return data->getAccessLevel().present();
}

SetContextStateOperationDescriptor & SetContextStateOperationDescriptor::addModifiableData(const std::string & value) {
	data->getModifiableData().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<std::string> SetContextStateOperationDescriptor::getModifiableDataList() const {
	std::vector<std::string> result;
	result.reserve(data->getModifiableData().size());
	for (const auto & value: data->getModifiableData()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void SetContextStateOperationDescriptor::clearModifiableDataList() {
	data->getModifiableData().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

