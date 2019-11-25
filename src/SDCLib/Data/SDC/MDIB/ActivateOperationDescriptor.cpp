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
 *  ActivateOperationDescriptor.cpp
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

#include "SDCLib/Data/SDC/MDIB/ActivateOperationDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/Argument.h"
#include "SDCLib/Data/SDC/MDIB/CodedValue.h"

namespace SDCLib {
namespace Data {
namespace SDC {


ActivateOperationDescriptor::ActivateOperationDescriptor(
		Handle handle
		,
		HandleRef operationtarget
) : data(Defaults::ActivateOperationDescriptorInit(
		handle
		,
		operationtarget
)) {}

ActivateOperationDescriptor::operator CDM::ActivateOperationDescriptor() const {
	return *data;
}

ActivateOperationDescriptor::ActivateOperationDescriptor(const CDM::ActivateOperationDescriptor & object) : data(new CDM::ActivateOperationDescriptor(object)) {

}

ActivateOperationDescriptor::ActivateOperationDescriptor(const ActivateOperationDescriptor & object) : data(new CDM::ActivateOperationDescriptor(*object.data)) {

}

ActivateOperationDescriptor::~ActivateOperationDescriptor() {

}

void ActivateOperationDescriptor::copyFrom(const ActivateOperationDescriptor & object) {
	data = std::shared_ptr<CDM::ActivateOperationDescriptor>( new CDM::ActivateOperationDescriptor(*object.data));
}

ActivateOperationDescriptor & ActivateOperationDescriptor:: operator=(const ActivateOperationDescriptor & object) {
	copyFrom(object);
	return *this;
}


ActivateOperationDescriptor & ActivateOperationDescriptor::setType(const CodedValue & value) {
	data->setType(ConvertToCDM::convert(value));
	return *this;
}

bool ActivateOperationDescriptor::getType(CodedValue & out) const {
	if (data->getType().present()) {
		out = ConvertFromCDM::convert(data->getType().get());
		return true;
	}
	return false;
}

CodedValue ActivateOperationDescriptor::getType() const {
	return ConvertFromCDM::convert(data->getType().get());
}

bool ActivateOperationDescriptor::hasType() const {
	return data->getType().present();
}

ActivateOperationDescriptor & ActivateOperationDescriptor::setHandle(const Handle & value) {
	data->setHandle(ConvertToCDM::convert(value));
	return *this;
}


Handle ActivateOperationDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->getHandle());
}

ActivateOperationDescriptor & ActivateOperationDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool ActivateOperationDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter ActivateOperationDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool ActivateOperationDescriptor::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

ActivateOperationDescriptor & ActivateOperationDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->setSafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool ActivateOperationDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->getSafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->getSafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification ActivateOperationDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->getSafetyClassification().get());
}

bool ActivateOperationDescriptor::hasSafetyClassification() const {
	return data->getSafetyClassification().present();
}

ActivateOperationDescriptor & ActivateOperationDescriptor::setOperationTarget(const HandleRef & value) {
	data->setOperationTarget(ConvertToCDM::convert(value));
	return *this;
}


HandleRef ActivateOperationDescriptor::getOperationTarget() const {
	return ConvertFromCDM::convert(data->getOperationTarget());
}

ActivateOperationDescriptor & ActivateOperationDescriptor::setMaxTimeToFinish(const xml_schema::Duration & value) {
	data->setMaxTimeToFinish(ConvertToCDM::convert(value));
	return *this;
}

bool ActivateOperationDescriptor::getMaxTimeToFinish(xml_schema::Duration & out) const {
	if (data->getMaxTimeToFinish().present()) {
		out = ConvertFromCDM::convert(data->getMaxTimeToFinish().get());
		return true;
	}
	return false;
}

xml_schema::Duration ActivateOperationDescriptor::getMaxTimeToFinish() const {
	return ConvertFromCDM::convert(data->getMaxTimeToFinish().get());
}

bool ActivateOperationDescriptor::hasMaxTimeToFinish() const {
	return data->getMaxTimeToFinish().present();
}

ActivateOperationDescriptor & ActivateOperationDescriptor::setInvocationEffectiveTimeout(const xml_schema::Duration & value) {
	data->setInvocationEffectiveTimeout(ConvertToCDM::convert(value));
	return *this;
}

bool ActivateOperationDescriptor::getInvocationEffectiveTimeout(xml_schema::Duration & out) const {
	if (data->getInvocationEffectiveTimeout().present()) {
		out = ConvertFromCDM::convert(data->getInvocationEffectiveTimeout().get());
		return true;
	}
	return false;
}

xml_schema::Duration ActivateOperationDescriptor::getInvocationEffectiveTimeout() const {
	return ConvertFromCDM::convert(data->getInvocationEffectiveTimeout().get());
}

bool ActivateOperationDescriptor::hasInvocationEffectiveTimeout() const {
	return data->getInvocationEffectiveTimeout().present();
}

ActivateOperationDescriptor & ActivateOperationDescriptor::setRetriggerable(const bool & value) {
	data->setRetriggerable(ConvertToCDM::convert(value));
	return *this;
}

bool ActivateOperationDescriptor::getRetriggerable(bool & out) const {
	if (data->getRetriggerable().present()) {
		out = ConvertFromCDM::convert(data->getRetriggerable().get());
		return true;
	}
	return false;
}

bool ActivateOperationDescriptor::getRetriggerable() const {
	return ConvertFromCDM::convert(data->getRetriggerable().get());
}

bool ActivateOperationDescriptor::hasRetriggerable() const {
	return data->getRetriggerable().present();
}

ActivateOperationDescriptor & ActivateOperationDescriptor::setAccessLevel(const AccessLevel & value) {
	data->setAccessLevel(ConvertToCDM::convert(value));
	return *this;
}

bool ActivateOperationDescriptor::getAccessLevel(AccessLevel & out) const {
	if (data->getAccessLevel().present()) {
		out = ConvertFromCDM::convert(data->getAccessLevel().get());
		return true;
	}
	return false;
}

AccessLevel ActivateOperationDescriptor::getAccessLevel() const {
	return ConvertFromCDM::convert(data->getAccessLevel().get());
}

bool ActivateOperationDescriptor::hasAccessLevel() const {
	return data->getAccessLevel().present();
}

ActivateOperationDescriptor & ActivateOperationDescriptor::addModifiableData(const std::string & value) {
	data->getModifiableData().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<std::string> ActivateOperationDescriptor::getModifiableDataList() const {
	std::vector<std::string> result;
	result.reserve(data->getModifiableData().size());
	for (const auto & value: data->getModifiableData()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void ActivateOperationDescriptor::clearModifiableDataList() {
	data->getModifiableData().clear();
}

ActivateOperationDescriptor & ActivateOperationDescriptor::addArgument(const Argument & value) {
	data->getArgument().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<Argument> ActivateOperationDescriptor::getArgumentList() const {
	std::vector<Argument> result;
	result.reserve(data->getArgument().size());
	for (const auto & value: data->getArgument()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void ActivateOperationDescriptor::clearArgumentList() {
	data->getArgument().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

