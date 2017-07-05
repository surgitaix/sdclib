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
 *  RealTimeSampleArrayMetricDescriptor.cpp
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

#include "OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/Range.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

RealTimeSampleArrayMetricDescriptor::RealTimeSampleArrayMetricDescriptor() : data(Defaults::RealTimeSampleArrayMetricDescriptor()) {
}

RealTimeSampleArrayMetricDescriptor::operator CDM::RealTimeSampleArrayMetricDescriptor() const {
	return *data;
}

RealTimeSampleArrayMetricDescriptor::RealTimeSampleArrayMetricDescriptor(const CDM::RealTimeSampleArrayMetricDescriptor & object) : data(new CDM::RealTimeSampleArrayMetricDescriptor(object)) {

}

RealTimeSampleArrayMetricDescriptor::RealTimeSampleArrayMetricDescriptor(const RealTimeSampleArrayMetricDescriptor & object) : data(new CDM::RealTimeSampleArrayMetricDescriptor(*object.data)) {

}

RealTimeSampleArrayMetricDescriptor::~RealTimeSampleArrayMetricDescriptor() {

}

void RealTimeSampleArrayMetricDescriptor::copyFrom(const RealTimeSampleArrayMetricDescriptor & object) {
	*data = *object.data;
}

RealTimeSampleArrayMetricDescriptor & RealTimeSampleArrayMetricDescriptor:: operator=(const RealTimeSampleArrayMetricDescriptor & object) {
	copyFrom(object);
	return *this;
}


RealTimeSampleArrayMetricDescriptor & RealTimeSampleArrayMetricDescriptor::setType(const CodedValue & value) {
	data->Type(ConvertToCDM::convert(value));
	return *this;
}

bool RealTimeSampleArrayMetricDescriptor::getType(CodedValue & out) const {
	if (data->Type().present()) {
		out = ConvertFromCDM::convert(data->Type().get());
		return true;
	}
	return false;
}

CodedValue RealTimeSampleArrayMetricDescriptor::getType() const {
	return ConvertFromCDM::convert(data->Type().get());
}
	
bool RealTimeSampleArrayMetricDescriptor::hasType() const {
	return data->Type().present();
}
	
RealTimeSampleArrayMetricDescriptor & RealTimeSampleArrayMetricDescriptor::setHandle(const Handle & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}


Handle RealTimeSampleArrayMetricDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->Handle());
}
	
RealTimeSampleArrayMetricDescriptor & RealTimeSampleArrayMetricDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool RealTimeSampleArrayMetricDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter RealTimeSampleArrayMetricDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}
	
bool RealTimeSampleArrayMetricDescriptor::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}
	
RealTimeSampleArrayMetricDescriptor & RealTimeSampleArrayMetricDescriptor::setSafetyClassification(const SafetyClassification & value) {
	data->SafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool RealTimeSampleArrayMetricDescriptor::getSafetyClassification(SafetyClassification & out) const {
	if (data->SafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->SafetyClassification().get());
		return true;
	}
	return false;
}

SafetyClassification RealTimeSampleArrayMetricDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->SafetyClassification().get());
}
	
bool RealTimeSampleArrayMetricDescriptor::hasSafetyClassification() const {
	return data->SafetyClassification().present();
}
	
RealTimeSampleArrayMetricDescriptor & RealTimeSampleArrayMetricDescriptor::setUnit(const CodedValue & value) {
	data->Unit(ConvertToCDM::convert(value));
	return *this;
}


CodedValue RealTimeSampleArrayMetricDescriptor::getUnit() const {
	return ConvertFromCDM::convert(data->Unit());
}
	
RealTimeSampleArrayMetricDescriptor & RealTimeSampleArrayMetricDescriptor::setMetricCategory(const MetricCategory & value) {
	data->MetricCategory(ConvertToCDM::convert(value));
	return *this;
}


MetricCategory RealTimeSampleArrayMetricDescriptor::getMetricCategory() const {
	return ConvertFromCDM::convert(data->MetricCategory());
}
	
RealTimeSampleArrayMetricDescriptor & RealTimeSampleArrayMetricDescriptor::setDerivationMethod(const DerivationMethod & value) {
	data->DerivationMethod(ConvertToCDM::convert(value));
	return *this;
}


DerivationMethod RealTimeSampleArrayMetricDescriptor::getDerivationMethod() const {
	return ConvertFromCDM::convert(data->DerivationMethod());
}
	
RealTimeSampleArrayMetricDescriptor & RealTimeSampleArrayMetricDescriptor::setMetricAvailability(const MetricAvailability & value) {
	data->MetricAvailability(ConvertToCDM::convert(value));
	return *this;
}


MetricAvailability RealTimeSampleArrayMetricDescriptor::getMetricAvailability() const {
	return ConvertFromCDM::convert(data->MetricAvailability());
}
	
RealTimeSampleArrayMetricDescriptor & RealTimeSampleArrayMetricDescriptor::setMaxMeasurementTime(const xml_schema::Duration & value) {
	data->MaxMeasurementTime(ConvertToCDM::convert(value));
	return *this;
}

bool RealTimeSampleArrayMetricDescriptor::getMaxMeasurementTime(xml_schema::Duration & out) const {
	if (data->MaxMeasurementTime().present()) {
		out = ConvertFromCDM::convert(data->MaxMeasurementTime().get());
		return true;
	}
	return false;
}

xml_schema::Duration RealTimeSampleArrayMetricDescriptor::getMaxMeasurementTime() const {
	return ConvertFromCDM::convert(data->MaxMeasurementTime().get());
}
	
bool RealTimeSampleArrayMetricDescriptor::hasMaxMeasurementTime() const {
	return data->MaxMeasurementTime().present();
}
	
RealTimeSampleArrayMetricDescriptor & RealTimeSampleArrayMetricDescriptor::setMaxDelayTime(const xml_schema::Duration & value) {
	data->MaxDelayTime(ConvertToCDM::convert(value));
	return *this;
}

bool RealTimeSampleArrayMetricDescriptor::getMaxDelayTime(xml_schema::Duration & out) const {
	if (data->MaxDelayTime().present()) {
		out = ConvertFromCDM::convert(data->MaxDelayTime().get());
		return true;
	}
	return false;
}

xml_schema::Duration RealTimeSampleArrayMetricDescriptor::getMaxDelayTime() const {
	return ConvertFromCDM::convert(data->MaxDelayTime().get());
}
	
bool RealTimeSampleArrayMetricDescriptor::hasMaxDelayTime() const {
	return data->MaxDelayTime().present();
}
	
RealTimeSampleArrayMetricDescriptor & RealTimeSampleArrayMetricDescriptor::setDeterminationPeriod(const xml_schema::Duration & value) {
	data->DeterminationPeriod(ConvertToCDM::convert(value));
	return *this;
}

bool RealTimeSampleArrayMetricDescriptor::getDeterminationPeriod(xml_schema::Duration & out) const {
	if (data->DeterminationPeriod().present()) {
		out = ConvertFromCDM::convert(data->DeterminationPeriod().get());
		return true;
	}
	return false;
}

xml_schema::Duration RealTimeSampleArrayMetricDescriptor::getDeterminationPeriod() const {
	return ConvertFromCDM::convert(data->DeterminationPeriod().get());
}
	
bool RealTimeSampleArrayMetricDescriptor::hasDeterminationPeriod() const {
	return data->DeterminationPeriod().present();
}
	
RealTimeSampleArrayMetricDescriptor & RealTimeSampleArrayMetricDescriptor::setLifeTimePeriod(const xml_schema::Duration & value) {
	data->LifeTimePeriod(ConvertToCDM::convert(value));
	return *this;
}

bool RealTimeSampleArrayMetricDescriptor::getLifeTimePeriod(xml_schema::Duration & out) const {
	if (data->LifeTimePeriod().present()) {
		out = ConvertFromCDM::convert(data->LifeTimePeriod().get());
		return true;
	}
	return false;
}

xml_schema::Duration RealTimeSampleArrayMetricDescriptor::getLifeTimePeriod() const {
	return ConvertFromCDM::convert(data->LifeTimePeriod().get());
}
	
bool RealTimeSampleArrayMetricDescriptor::hasLifeTimePeriod() const {
	return data->LifeTimePeriod().present();
}
	
RealTimeSampleArrayMetricDescriptor & RealTimeSampleArrayMetricDescriptor::addBodySite(const CodedValue & value) {
	data->BodySite().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<CodedValue> RealTimeSampleArrayMetricDescriptor::getBodySiteLists() const {
	std::vector<CodedValue> result;
	result.reserve(data->BodySite().size());
	for (const auto & value: data->BodySite()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void RealTimeSampleArrayMetricDescriptor::clearBodySiteLists() {
	data->BodySite().clear();
}

RealTimeSampleArrayMetricDescriptor & RealTimeSampleArrayMetricDescriptor::setResolution(const double & value) {
	data->Resolution(ConvertToCDM::convert(value));
	return *this;
}


double RealTimeSampleArrayMetricDescriptor::getResolution() const {
	return ConvertFromCDM::convert(data->Resolution());
}
	
RealTimeSampleArrayMetricDescriptor & RealTimeSampleArrayMetricDescriptor::setSamplePeriod(const xml_schema::Duration & value) {
	data->SamplePeriod(ConvertToCDM::convert(value));
	return *this;
}


xml_schema::Duration RealTimeSampleArrayMetricDescriptor::getSamplePeriod() const {
	return ConvertFromCDM::convert(data->SamplePeriod());
}
	
RealTimeSampleArrayMetricDescriptor & RealTimeSampleArrayMetricDescriptor::addTechnicalRange(const Range & value) {
	data->TechnicalRange().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<Range> RealTimeSampleArrayMetricDescriptor::getTechnicalRangeLists() const {
	std::vector<Range> result;
	result.reserve(data->TechnicalRange().size());
	for (const auto & value: data->TechnicalRange()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void RealTimeSampleArrayMetricDescriptor::clearTechnicalRangeLists() {
	data->TechnicalRange().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

