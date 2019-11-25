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
 *  AlertConditionDescriptor.cpp
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

#include "SDCLib/Data/SDC/MDIB/AlertConditionDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/CauseInfo.h"
#include "SDCLib/Data/SDC/MDIB/CodedValue.h"

namespace SDCLib {
namespace Data {
namespace SDC {


AlertConditionDescriptor::AlertConditionDescriptor(
		Handle handle
		,
		AlertConditionKind kind
		,
		AlertConditionPriority priority
) : data(Defaults::AlertConditionDescriptorInit(
		handle
		,
		kind
		,
		priority
)) {}

AlertConditionDescriptor::operator CDM::AlertConditionDescriptor() const {
	return *data;
}

AlertConditionDescriptor::AlertConditionDescriptor(const CDM::AlertConditionDescriptor & object) : data(new CDM::AlertConditionDescriptor(object)) {

}

AlertConditionDescriptor::AlertConditionDescriptor(const AlertConditionDescriptor & object) : data(new CDM::AlertConditionDescriptor(*object.data)) {

}

AlertConditionDescriptor::~AlertConditionDescriptor() {

}

void AlertConditionDescriptor::copyFrom(const AlertConditionDescriptor & object) {
	data = std::shared_ptr<CDM::AlertConditionDescriptor>( new CDM::AlertConditionDescriptor(*object.data));
}

AlertConditionDescriptor & AlertConditionDescriptor:: operator=(const AlertConditionDescriptor & object) {
	copyFrom(object);
	return *this;
}


AlertConditionDescriptor & AlertConditionDescriptor::setType(const CodedValue & value) {
	data->setType(ConvertToCDM::convert(value));
	return *this;
}

bool AlertConditionDescriptor::getType(CodedValue & out) const {
	if (data->getType().present()) {
		out = ConvertFromCDM::convert(data->getType().get());
		return true;
	}
	return false;
}

CodedValue AlertConditionDescriptor::getType() const {
	return ConvertFromCDM::convert(data->getType().get());
}

bool AlertConditionDescriptor::hasType() const {
	return data->getType().present();
}

AlertConditionDescriptor & AlertConditionDescriptor::setHandle(const Handle & value) {
	data->setHandle(ConvertToCDM::convert(value));
	return *this;
}


Handle AlertConditionDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->getHandle());
}

AlertConditionDescriptor & AlertConditionDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool AlertConditionDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter AlertConditionDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool AlertConditionDescriptor::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

AlertConditionDescriptor & AlertConditionDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->setSafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool AlertConditionDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->getSafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->getSafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification AlertConditionDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->getSafetyClassification().get());
}

bool AlertConditionDescriptor::hasSafetyClassification() const {
	return data->getSafetyClassification().present();
}

AlertConditionDescriptor & AlertConditionDescriptor::setKind(const AlertConditionKind & value) {
	data->setKind(ConvertToCDM::convert(value));
	return *this;
}


AlertConditionKind AlertConditionDescriptor::getKind() const {
	return ConvertFromCDM::convert(data->getKind());
}

AlertConditionDescriptor & AlertConditionDescriptor::setPriority(const AlertConditionPriority & value) {
	data->setPriority(ConvertToCDM::convert(value));
	return *this;
}


AlertConditionPriority AlertConditionDescriptor::getPriority() const {
	return ConvertFromCDM::convert(data->getPriority());
}

AlertConditionDescriptor & AlertConditionDescriptor::setDefaultConditionGenerationDelay(const xml_schema::Duration & value) {
	data->setDefaultConditionGenerationDelay(ConvertToCDM::convert(value));
	return *this;
}

bool AlertConditionDescriptor::getDefaultConditionGenerationDelay(xml_schema::Duration & out) const {
	if (data->getDefaultConditionGenerationDelay().present()) {
		out = ConvertFromCDM::convert(data->getDefaultConditionGenerationDelay().get());
		return true;
	}
	return false;
}

xml_schema::Duration AlertConditionDescriptor::getDefaultConditionGenerationDelay() const {
	return ConvertFromCDM::convert(data->getDefaultConditionGenerationDelay().get());
}

bool AlertConditionDescriptor::hasDefaultConditionGenerationDelay() const {
	return data->getDefaultConditionGenerationDelay().present();
}

AlertConditionDescriptor & AlertConditionDescriptor::setCanEscalate(const CanEscalate & value) {
	data->setCanEscalate(ConvertToCDM::convert(value));
	return *this;
}

bool AlertConditionDescriptor::getCanEscalate(CanEscalate & out) const {
	if (data->getCanEscalate().present()) {
		out = ConvertFromCDM::convert(data->getCanEscalate().get());
		return true;
	}
	return false;
}

CanEscalate AlertConditionDescriptor::getCanEscalate() const {
	return ConvertFromCDM::convert(data->getCanEscalate().get());
}

bool AlertConditionDescriptor::hasCanEscalate() const {
	return data->getCanEscalate().present();
}

AlertConditionDescriptor & AlertConditionDescriptor::setCanDeescalate(const CanDeescalate & value) {
	data->setCanDeescalate(ConvertToCDM::convert(value));
	return *this;
}

bool AlertConditionDescriptor::getCanDeescalate(CanDeescalate & out) const {
	if (data->getCanDeescalate().present()) {
		out = ConvertFromCDM::convert(data->getCanDeescalate().get());
		return true;
	}
	return false;
}

CanDeescalate AlertConditionDescriptor::getCanDeescalate() const {
	return ConvertFromCDM::convert(data->getCanDeescalate().get());
}

bool AlertConditionDescriptor::hasCanDeescalate() const {
	return data->getCanDeescalate().present();
}

AlertConditionDescriptor & AlertConditionDescriptor::addSource(const HandleRef & value) {
	data->getSource().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<HandleRef> AlertConditionDescriptor::getSourceList() const {
	std::vector<HandleRef> result;
	result.reserve(data->getSource().size());
	for (const auto & value: data->getSource()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void AlertConditionDescriptor::clearSourceList() {
	data->getSource().clear();
}

AlertConditionDescriptor & AlertConditionDescriptor::addCauseInfo(const CauseInfo & value) {
	data->getCauseInfo().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<CauseInfo> AlertConditionDescriptor::getCauseInfoList() const {
	std::vector<CauseInfo> result;
	result.reserve(data->getCauseInfo().size());
	for (const auto & value: data->getCauseInfo()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void AlertConditionDescriptor::clearCauseInfoList() {
	data->getCauseInfo().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

