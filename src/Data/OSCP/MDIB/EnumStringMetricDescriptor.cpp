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
 *  EnumStringMetricDescriptor.cpp
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

#include "OSCLib/Data/OSCP/MDIB/EnumStringMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

EnumStringMetricDescriptor::EnumStringMetricDescriptor() : data(Defaults::EnumStringMetricDescriptor()) {
}

EnumStringMetricDescriptor::operator CDM::EnumStringMetricDescriptor() const {
	return *data;
}

EnumStringMetricDescriptor::EnumStringMetricDescriptor(const CDM::EnumStringMetricDescriptor & object) : data(new CDM::EnumStringMetricDescriptor(object)) {

}

EnumStringMetricDescriptor::EnumStringMetricDescriptor(const EnumStringMetricDescriptor & object) : data(new CDM::EnumStringMetricDescriptor(*object.data)) {

}

EnumStringMetricDescriptor::~EnumStringMetricDescriptor() {

}

void EnumStringMetricDescriptor::copyFrom(const EnumStringMetricDescriptor & object) {
	*data = *object.data;
}

EnumStringMetricDescriptor & EnumStringMetricDescriptor:: operator=(const EnumStringMetricDescriptor & object) {
	copyFrom(object);
	return *this;
}


EnumStringMetricDescriptor & EnumStringMetricDescriptor::setType(const CodedValue & value) {
	data->Type(ConvertToCDM::convert(value));
	return *this;
}

bool EnumStringMetricDescriptor::getType(CodedValue & out) const {
	if (data->Type().present()) {
		out = ConvertFromCDM::convert(data->Type().get());
		return true;
	}
	return false;
}

CodedValue EnumStringMetricDescriptor::getType() const {
	return ConvertFromCDM::convert(data->Type().get());
}
	
bool EnumStringMetricDescriptor::hasType() const {
	return data->Type().present();
}
	
EnumStringMetricDescriptor & EnumStringMetricDescriptor::setHandle(const Handle & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}


Handle EnumStringMetricDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->Handle());
}
	
EnumStringMetricDescriptor & EnumStringMetricDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool EnumStringMetricDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter EnumStringMetricDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}
	
bool EnumStringMetricDescriptor::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}
	
EnumStringMetricDescriptor & EnumStringMetricDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->SafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool EnumStringMetricDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->SafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->SafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification EnumStringMetricDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->SafetyClassification().get());
}
	
bool EnumStringMetricDescriptor::hasSafetyClassification() const {
	return data->SafetyClassification().present();
}
	
EnumStringMetricDescriptor & EnumStringMetricDescriptor::setUnit(const CodedValue & value) {
	data->Unit(ConvertToCDM::convert(value));
	return *this;
}


CodedValue EnumStringMetricDescriptor::getUnit() const {
	return ConvertFromCDM::convert(data->Unit());
}
	
EnumStringMetricDescriptor & EnumStringMetricDescriptor::setMetricCategory(const MetricCategory & value) {
	data->MetricCategory(ConvertToCDM::convert(value));
	return *this;
}


MetricCategory EnumStringMetricDescriptor::getMetricCategory() const {
	return ConvertFromCDM::convert(data->MetricCategory());
}
	
EnumStringMetricDescriptor & EnumStringMetricDescriptor::setDerivationMethod(const DerivationMethod & value) {
	data->DerivationMethod(ConvertToCDM::convert(value));
	return *this;
}

bool EnumStringMetricDescriptor::getDerivationMethod(DerivationMethod & out) const {
	if (data->DerivationMethod().present()) {
		out = ConvertFromCDM::convert(data->DerivationMethod().get());
		return true;
	}
	return false;
}

DerivationMethod EnumStringMetricDescriptor::getDerivationMethod() const {
	return ConvertFromCDM::convert(data->DerivationMethod().get());
}
	
bool EnumStringMetricDescriptor::hasDerivationMethod() const {
	return data->DerivationMethod().present();
}
	
EnumStringMetricDescriptor & EnumStringMetricDescriptor::setMetricAvailability(const MetricAvailability & value) {
	data->MetricAvailability(ConvertToCDM::convert(value));
	return *this;
}


MetricAvailability EnumStringMetricDescriptor::getMetricAvailability() const {
	return ConvertFromCDM::convert(data->MetricAvailability());
}
	
EnumStringMetricDescriptor & EnumStringMetricDescriptor::setMaxMeasurementTime(const xml_schema::Duration & value) {
	data->MaxMeasurementTime(ConvertToCDM::convert(value));
	return *this;
}

bool EnumStringMetricDescriptor::getMaxMeasurementTime(xml_schema::Duration & out) const {
	if (data->MaxMeasurementTime().present()) {
		out = ConvertFromCDM::convert(data->MaxMeasurementTime().get());
		return true;
	}
	return false;
}

xml_schema::Duration EnumStringMetricDescriptor::getMaxMeasurementTime() const {
	return ConvertFromCDM::convert(data->MaxMeasurementTime().get());
}
	
bool EnumStringMetricDescriptor::hasMaxMeasurementTime() const {
	return data->MaxMeasurementTime().present();
}
	
EnumStringMetricDescriptor & EnumStringMetricDescriptor::setMaxDelayTime(const xml_schema::Duration & value) {
	data->MaxDelayTime(ConvertToCDM::convert(value));
	return *this;
}

bool EnumStringMetricDescriptor::getMaxDelayTime(xml_schema::Duration & out) const {
	if (data->MaxDelayTime().present()) {
		out = ConvertFromCDM::convert(data->MaxDelayTime().get());
		return true;
	}
	return false;
}

xml_schema::Duration EnumStringMetricDescriptor::getMaxDelayTime() const {
	return ConvertFromCDM::convert(data->MaxDelayTime().get());
}
	
bool EnumStringMetricDescriptor::hasMaxDelayTime() const {
	return data->MaxDelayTime().present();
}
	
EnumStringMetricDescriptor & EnumStringMetricDescriptor::setDeterminationPeriod(const xml_schema::Duration & value) {
	data->DeterminationPeriod(ConvertToCDM::convert(value));
	return *this;
}

bool EnumStringMetricDescriptor::getDeterminationPeriod(xml_schema::Duration & out) const {
	if (data->DeterminationPeriod().present()) {
		out = ConvertFromCDM::convert(data->DeterminationPeriod().get());
		return true;
	}
	return false;
}

xml_schema::Duration EnumStringMetricDescriptor::getDeterminationPeriod() const {
	return ConvertFromCDM::convert(data->DeterminationPeriod().get());
}
	
bool EnumStringMetricDescriptor::hasDeterminationPeriod() const {
	return data->DeterminationPeriod().present();
}
	
EnumStringMetricDescriptor & EnumStringMetricDescriptor::setLifeTimePeriod(const xml_schema::Duration & value) {
	data->LifeTimePeriod(ConvertToCDM::convert(value));
	return *this;
}

bool EnumStringMetricDescriptor::getLifeTimePeriod(xml_schema::Duration & out) const {
	if (data->LifeTimePeriod().present()) {
		out = ConvertFromCDM::convert(data->LifeTimePeriod().get());
		return true;
	}
	return false;
}

xml_schema::Duration EnumStringMetricDescriptor::getLifeTimePeriod() const {
	return ConvertFromCDM::convert(data->LifeTimePeriod().get());
}
	
bool EnumStringMetricDescriptor::hasLifeTimePeriod() const {
	return data->LifeTimePeriod().present();
}
	
EnumStringMetricDescriptor & EnumStringMetricDescriptor::addBodySite(const CodedValue & value) {
	data->BodySite().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<CodedValue> EnumStringMetricDescriptor::getBodySiteLists() const {
	std::vector<CodedValue> result;
	result.reserve(data->BodySite().size());
	for (const auto & value: data->BodySite()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void EnumStringMetricDescriptor::clearBodySiteLists() {
	data->BodySite().clear();
}

EnumStringMetricDescriptor & EnumStringMetricDescriptor::addAllowedValue(const AllowedValue & value) {
	data->AllowedValue().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<AllowedValue> EnumStringMetricDescriptor::getAllowedValueLists() const {
	std::vector<AllowedValue> result;
	result.reserve(data->AllowedValue().size());
	for (const auto & value: data->AllowedValue()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void EnumStringMetricDescriptor::clearAllowedValueLists() {
	data->AllowedValue().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

