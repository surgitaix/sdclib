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
 *  Author: besting, roehser
 */
 
/**
 * THIS FILE IS GENERATED AUTOMATICALLY! DO NOT MODIFY!
 *
 * YOUR CHANGES WILL BE OVERWRITTEN!
 * 
 * USE THE DEFINITION FILES IN THE FOLDER "codegenerator" INSTEAD!
 */

#include "OSCLib/Data/OSCP/MDIB/AlertConditionDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/CauseInfo.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

AlertConditionDescriptor::AlertConditionDescriptor() : data(Defaults::AlertConditionDescriptor()) {
}

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
	*data = *object.data;
}

AlertConditionDescriptor & AlertConditionDescriptor:: operator=(const AlertConditionDescriptor & object) {
	copyFrom(object);
	return *this;
}


AlertConditionDescriptor & AlertConditionDescriptor::setType(const CodedValue & value) {
	data->Type(ConvertToCDM::convert(value));
	return *this;
}

bool AlertConditionDescriptor::getType(CodedValue & out) const {
	if (data->Type().present()) {
		out = ConvertFromCDM::convert(data->Type().get());
		return true;
	}
	return false;
}

CodedValue AlertConditionDescriptor::getType() const {
	return ConvertFromCDM::convert(data->Type().get());
}
	
bool AlertConditionDescriptor::hasType() const {
	return data->Type().present();
}
	
AlertConditionDescriptor & AlertConditionDescriptor::setHandle(const Handle & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}


Handle AlertConditionDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->Handle());
}
	
AlertConditionDescriptor & AlertConditionDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool AlertConditionDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter AlertConditionDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}
	
bool AlertConditionDescriptor::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}
	
AlertConditionDescriptor & AlertConditionDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->SafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool AlertConditionDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->SafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->SafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification AlertConditionDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->SafetyClassification().get());
}
	
bool AlertConditionDescriptor::hasSafetyClassification() const {
	return data->SafetyClassification().present();
}
	
AlertConditionDescriptor & AlertConditionDescriptor::setKind(const AlertConditionKind & value) {
	data->Kind(ConvertToCDM::convert(value));
	return *this;
}


AlertConditionKind AlertConditionDescriptor::getKind() const {
	return ConvertFromCDM::convert(data->Kind());
}
	
AlertConditionDescriptor & AlertConditionDescriptor::setPriority(const AlertConditionPriority & value) {
	data->Priority(ConvertToCDM::convert(value));
	return *this;
}


AlertConditionPriority AlertConditionDescriptor::getPriority() const {
	return ConvertFromCDM::convert(data->Priority());
}
	
AlertConditionDescriptor & AlertConditionDescriptor::setDefaultConditionGenerationDelay(const xml_schema::Duration & value) {
	data->DefaultConditionGenerationDelay(ConvertToCDM::convert(value));
	return *this;
}

bool AlertConditionDescriptor::getDefaultConditionGenerationDelay(xml_schema::Duration & out) const {
	if (data->DefaultConditionGenerationDelay().present()) {
		out = ConvertFromCDM::convert(data->DefaultConditionGenerationDelay().get());
		return true;
	}
	return false;
}

xml_schema::Duration AlertConditionDescriptor::getDefaultConditionGenerationDelay() const {
	return ConvertFromCDM::convert(data->DefaultConditionGenerationDelay().get());
}
	
bool AlertConditionDescriptor::hasDefaultConditionGenerationDelay() const {
	return data->DefaultConditionGenerationDelay().present();
}
	
AlertConditionDescriptor & AlertConditionDescriptor::setCanEscalate(const CanEscalate & value) {
	data->CanEscalate(ConvertToCDM::convert(value));
	return *this;
}

bool AlertConditionDescriptor::getCanEscalate(CanEscalate & out) const {
	if (data->CanEscalate().present()) {
		out = ConvertFromCDM::convert(data->CanEscalate().get());
		return true;
	}
	return false;
}

CanEscalate AlertConditionDescriptor::getCanEscalate() const {
	return ConvertFromCDM::convert(data->CanEscalate().get());
}
	
bool AlertConditionDescriptor::hasCanEscalate() const {
	return data->CanEscalate().present();
}
	
AlertConditionDescriptor & AlertConditionDescriptor::setCanDeescalate(const CanDeescalate & value) {
	data->CanDeescalate(ConvertToCDM::convert(value));
	return *this;
}

bool AlertConditionDescriptor::getCanDeescalate(CanDeescalate & out) const {
	if (data->CanDeescalate().present()) {
		out = ConvertFromCDM::convert(data->CanDeescalate().get());
		return true;
	}
	return false;
}

CanDeescalate AlertConditionDescriptor::getCanDeescalate() const {
	return ConvertFromCDM::convert(data->CanDeescalate().get());
}
	
bool AlertConditionDescriptor::hasCanDeescalate() const {
	return data->CanDeescalate().present();
}
	
AlertConditionDescriptor & AlertConditionDescriptor::addSource(const HandleRef & value) {
	data->Source().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<HandleRef> AlertConditionDescriptor::getSourceList() const {
	std::vector<HandleRef> result;
	result.reserve(data->Source().size());
	for (const auto & value: data->Source()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void AlertConditionDescriptor::clearSourceList() {
	data->Source().clear();
}

AlertConditionDescriptor & AlertConditionDescriptor::addCauseInfo(const CauseInfo & value) {
	data->CauseInfo().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<CauseInfo> AlertConditionDescriptor::getCauseInfoList() const {
	std::vector<CauseInfo> result;
	result.reserve(data->CauseInfo().size());
	for (const auto & value: data->CauseInfo()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void AlertConditionDescriptor::clearCauseInfoList() {
	data->CauseInfo().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

