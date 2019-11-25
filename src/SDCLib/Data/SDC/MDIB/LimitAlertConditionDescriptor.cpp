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
 *  LimitAlertConditionDescriptor.cpp
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

#include "SDCLib/Data/SDC/MDIB/LimitAlertConditionDescriptor.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/Range.h"
#include "SDCLib/Data/SDC/MDIB/CauseInfo.h"
#include "SDCLib/Data/SDC/MDIB/CodedValue.h"

namespace SDCLib {
namespace Data {
namespace SDC {


LimitAlertConditionDescriptor::LimitAlertConditionDescriptor(
		Handle handle
		,
		AlertConditionKind kind
		,
		AlertConditionPriority priority
		,
		Range maxlimits
) : data(Defaults::LimitAlertConditionDescriptorInit(
		handle
		,
		kind
		,
		priority
		,
		maxlimits
)) {}

LimitAlertConditionDescriptor::operator CDM::LimitAlertConditionDescriptor() const {
	return *data;
}

LimitAlertConditionDescriptor::LimitAlertConditionDescriptor(const CDM::LimitAlertConditionDescriptor & object) : data(new CDM::LimitAlertConditionDescriptor(object)) {

}

LimitAlertConditionDescriptor::LimitAlertConditionDescriptor(const LimitAlertConditionDescriptor & object) : data(new CDM::LimitAlertConditionDescriptor(*object.data)) {

}

LimitAlertConditionDescriptor::~LimitAlertConditionDescriptor() {

}

void LimitAlertConditionDescriptor::copyFrom(const LimitAlertConditionDescriptor & object) {
	data = std::shared_ptr<CDM::LimitAlertConditionDescriptor>( new CDM::LimitAlertConditionDescriptor(*object.data));
}

LimitAlertConditionDescriptor & LimitAlertConditionDescriptor:: operator=(const LimitAlertConditionDescriptor & object) {
	copyFrom(object);
	return *this;
}


LimitAlertConditionDescriptor & LimitAlertConditionDescriptor::setType(const CodedValue & value) {
	data->setType(ConvertToCDM::convert(value));
	return *this;
}

bool LimitAlertConditionDescriptor::getType(CodedValue & out) const {
	if (data->getType().present()) {
		out = ConvertFromCDM::convert(data->getType().get());
		return true;
	}
	return false;
}

CodedValue LimitAlertConditionDescriptor::getType() const {
	return ConvertFromCDM::convert(data->getType().get());
}

bool LimitAlertConditionDescriptor::hasType() const {
	return data->getType().present();
}

LimitAlertConditionDescriptor & LimitAlertConditionDescriptor::setHandle(const Handle & value) {
	data->setHandle(ConvertToCDM::convert(value));
	return *this;
}


Handle LimitAlertConditionDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->getHandle());
}

LimitAlertConditionDescriptor & LimitAlertConditionDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool LimitAlertConditionDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter LimitAlertConditionDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool LimitAlertConditionDescriptor::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

LimitAlertConditionDescriptor & LimitAlertConditionDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->setSafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool LimitAlertConditionDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->getSafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->getSafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification LimitAlertConditionDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->getSafetyClassification().get());
}

bool LimitAlertConditionDescriptor::hasSafetyClassification() const {
	return data->getSafetyClassification().present();
}

LimitAlertConditionDescriptor & LimitAlertConditionDescriptor::setKind(const AlertConditionKind & value) {
	data->setKind(ConvertToCDM::convert(value));
	return *this;
}


AlertConditionKind LimitAlertConditionDescriptor::getKind() const {
	return ConvertFromCDM::convert(data->getKind());
}

LimitAlertConditionDescriptor & LimitAlertConditionDescriptor::setPriority(const AlertConditionPriority & value) {
	data->setPriority(ConvertToCDM::convert(value));
	return *this;
}


AlertConditionPriority LimitAlertConditionDescriptor::getPriority() const {
	return ConvertFromCDM::convert(data->getPriority());
}

LimitAlertConditionDescriptor & LimitAlertConditionDescriptor::setDefaultConditionGenerationDelay(const xml_schema::Duration & value) {
	data->setDefaultConditionGenerationDelay(ConvertToCDM::convert(value));
	return *this;
}

bool LimitAlertConditionDescriptor::getDefaultConditionGenerationDelay(xml_schema::Duration & out) const {
	if (data->getDefaultConditionGenerationDelay().present()) {
		out = ConvertFromCDM::convert(data->getDefaultConditionGenerationDelay().get());
		return true;
	}
	return false;
}

xml_schema::Duration LimitAlertConditionDescriptor::getDefaultConditionGenerationDelay() const {
	return ConvertFromCDM::convert(data->getDefaultConditionGenerationDelay().get());
}

bool LimitAlertConditionDescriptor::hasDefaultConditionGenerationDelay() const {
	return data->getDefaultConditionGenerationDelay().present();
}

LimitAlertConditionDescriptor & LimitAlertConditionDescriptor::setCanEscalate(const CanEscalate & value) {
	data->setCanEscalate(ConvertToCDM::convert(value));
	return *this;
}

bool LimitAlertConditionDescriptor::getCanEscalate(CanEscalate & out) const {
	if (data->getCanEscalate().present()) {
		out = ConvertFromCDM::convert(data->getCanEscalate().get());
		return true;
	}
	return false;
}

CanEscalate LimitAlertConditionDescriptor::getCanEscalate() const {
	return ConvertFromCDM::convert(data->getCanEscalate().get());
}

bool LimitAlertConditionDescriptor::hasCanEscalate() const {
	return data->getCanEscalate().present();
}

LimitAlertConditionDescriptor & LimitAlertConditionDescriptor::setCanDeescalate(const CanDeescalate & value) {
	data->setCanDeescalate(ConvertToCDM::convert(value));
	return *this;
}

bool LimitAlertConditionDescriptor::getCanDeescalate(CanDeescalate & out) const {
	if (data->getCanDeescalate().present()) {
		out = ConvertFromCDM::convert(data->getCanDeescalate().get());
		return true;
	}
	return false;
}

CanDeescalate LimitAlertConditionDescriptor::getCanDeescalate() const {
	return ConvertFromCDM::convert(data->getCanDeescalate().get());
}

bool LimitAlertConditionDescriptor::hasCanDeescalate() const {
	return data->getCanDeescalate().present();
}

LimitAlertConditionDescriptor & LimitAlertConditionDescriptor::addSource(const HandleRef & value) {
	data->getSource().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<HandleRef> LimitAlertConditionDescriptor::getSourceList() const {
	std::vector<HandleRef> result;
	result.reserve(data->getSource().size());
	for (const auto & value: data->getSource()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void LimitAlertConditionDescriptor::clearSourceList() {
	data->getSource().clear();
}

LimitAlertConditionDescriptor & LimitAlertConditionDescriptor::addCauseInfo(const CauseInfo & value) {
	data->getCauseInfo().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<CauseInfo> LimitAlertConditionDescriptor::getCauseInfoList() const {
	std::vector<CauseInfo> result;
	result.reserve(data->getCauseInfo().size());
	for (const auto & value: data->getCauseInfo()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void LimitAlertConditionDescriptor::clearCauseInfoList() {
	data->getCauseInfo().clear();
}

LimitAlertConditionDescriptor & LimitAlertConditionDescriptor::setMaxLimits(const Range & value) {
	data->setMaxLimits(ConvertToCDM::convert(value));
	return *this;
}


Range LimitAlertConditionDescriptor::getMaxLimits() const {
	return ConvertFromCDM::convert(data->getMaxLimits());
}

LimitAlertConditionDescriptor & LimitAlertConditionDescriptor::setAutoLimitSupported(const bool & value) {
	data->setAutoLimitSupported(ConvertToCDM::convert(value));
	return *this;
}

bool LimitAlertConditionDescriptor::getAutoLimitSupported(bool & out) const {
	if (data->getAutoLimitSupported().present()) {
		out = ConvertFromCDM::convert(data->getAutoLimitSupported().get());
		return true;
	}
	return false;
}

bool LimitAlertConditionDescriptor::getAutoLimitSupported() const {
	return ConvertFromCDM::convert(data->getAutoLimitSupported().get());
}

bool LimitAlertConditionDescriptor::hasAutoLimitSupported() const {
	return data->getAutoLimitSupported().present();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

