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
 *  NumericMetricDescriptor.cpp
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

#include "OSCLib/Data/OSCP/MDIB/NumericMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/Duration.h"
#include "OSCLib/Data/OSCP/MDIB/Range.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/Duration.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/VersionCounter.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

NumericMetricDescriptor::NumericMetricDescriptor() : data(Defaults::NumericMetricDescriptor()) {
}

NumericMetricDescriptor::operator CDM::NumericMetricDescriptor() const {
	return *data;
}

NumericMetricDescriptor::NumericMetricDescriptor(const CDM::NumericMetricDescriptor & object) : data(new CDM::NumericMetricDescriptor(object)) {

}

NumericMetricDescriptor::NumericMetricDescriptor(const NumericMetricDescriptor & object) : data(new CDM::NumericMetricDescriptor(*object.data)) {

}

NumericMetricDescriptor::~NumericMetricDescriptor() {

}

void NumericMetricDescriptor::copyFrom(const NumericMetricDescriptor & object) {
	*data = *object.data;
}

NumericMetricDescriptor & NumericMetricDescriptor:: operator=(const NumericMetricDescriptor & object) {
	copyFrom(object);
	return *this;
}


NumericMetricDescriptor & NumericMetricDescriptor::setType(const CodedValue & value) {
	data->Type(ConvertToCDM::convert(value));
	return *this;
}

bool NumericMetricDescriptor::getType(CodedValue & out) const {
	if (data->Type().present()) {
		out = ConvertFromCDM::convert(data->Type().get());
		return true;
	}
	return false;
}

CodedValue NumericMetricDescriptor::getType() const {
	return ConvertFromCDM::convert(data->Type().get());
}
	
bool NumericMetricDescriptor::hasType() const {
	return data->Type().present();
}
	
NumericMetricDescriptor & NumericMetricDescriptor::setHandle(const std::string & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}


std::string NumericMetricDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->Handle());
}
	
NumericMetricDescriptor & NumericMetricDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool NumericMetricDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter NumericMetricDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}
	
bool NumericMetricDescriptor::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}
	
NumericMetricDescriptor & NumericMetricDescriptor::setUnit(const CodedValue & value) {
	data->Unit(ConvertToCDM::convert(value));
	return *this;
}


CodedValue NumericMetricDescriptor::getUnit() const {
	return ConvertFromCDM::convert(data->Unit());
}
	
NumericMetricDescriptor & NumericMetricDescriptor::setMetricCategory(const MetricCategory & value) {
	data->MetricCategory(ConvertToCDM::convert(value));
	return *this;
}


MetricCategory NumericMetricDescriptor::getMetricCategory() const {
	return ConvertFromCDM::convert(data->MetricCategory());
}
	
NumericMetricDescriptor & NumericMetricDescriptor::setAvailability(const MetricAvailability & value) {
	data->Availability(ConvertToCDM::convert(value));
	return *this;
}


MetricAvailability NumericMetricDescriptor::getAvailability() const {
	return ConvertFromCDM::convert(data->Availability());
}
	
NumericMetricDescriptor & NumericMetricDescriptor::setMaxDelayTime(const Duration & value) {
	data->MaxDelayTime(ConvertToCDM::convert(value));
	return *this;
}

bool NumericMetricDescriptor::getMaxDelayTime(Duration & out) const {
	if (data->MaxDelayTime().present()) {
		out = ConvertFromCDM::convert(data->MaxDelayTime().get());
		return true;
	}
	return false;
}

Duration NumericMetricDescriptor::getMaxDelayTime() const {
	return ConvertFromCDM::convert(data->MaxDelayTime().get());
}
	
bool NumericMetricDescriptor::hasMaxDelayTime() const {
	return data->MaxDelayTime().present();
}
	
NumericMetricDescriptor & NumericMetricDescriptor::addBodySite(const CodedValue & value) {
	data->BodySite().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<CodedValue> NumericMetricDescriptor::getBodySites() const {
	std::vector<CodedValue> result;
	result.reserve(data->BodySite().size());
	for (const auto & value: data->BodySite()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void NumericMetricDescriptor::clearBodySites() {
	data->BodySite().clear();
}

NumericMetricDescriptor & NumericMetricDescriptor::setResolution(const double & value) {
	data->Resolution(ConvertToCDM::convert(value));
	return *this;
}


double NumericMetricDescriptor::getResolution() const {
	return ConvertFromCDM::convert(data->Resolution());
}
	
NumericMetricDescriptor & NumericMetricDescriptor::setMeasurePeriod(const Duration & value) {
	data->MeasurePeriod(ConvertToCDM::convert(value));
	return *this;
}

bool NumericMetricDescriptor::getMeasurePeriod(Duration & out) const {
	if (data->MeasurePeriod().present()) {
		out = ConvertFromCDM::convert(data->MeasurePeriod().get());
		return true;
	}
	return false;
}

Duration NumericMetricDescriptor::getMeasurePeriod() const {
	return ConvertFromCDM::convert(data->MeasurePeriod().get());
}
	
bool NumericMetricDescriptor::hasMeasurePeriod() const {
	return data->MeasurePeriod().present();
}
	
NumericMetricDescriptor & NumericMetricDescriptor::setAveragingPeriod(const Duration & value) {
	data->AveragingPeriod(ConvertToCDM::convert(value));
	return *this;
}

bool NumericMetricDescriptor::getAveragingPeriod(Duration & out) const {
	if (data->AveragingPeriod().present()) {
		out = ConvertFromCDM::convert(data->AveragingPeriod().get());
		return true;
	}
	return false;
}

Duration NumericMetricDescriptor::getAveragingPeriod() const {
	return ConvertFromCDM::convert(data->AveragingPeriod().get());
}
	
bool NumericMetricDescriptor::hasAveragingPeriod() const {
	return data->AveragingPeriod().present();
}
	
NumericMetricDescriptor & NumericMetricDescriptor::addTechnicalRange(const Range & value) {
	data->TechnicalRange().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<Range> NumericMetricDescriptor::getTechnicalRanges() const {
	std::vector<Range> result;
	result.reserve(data->TechnicalRange().size());
	for (const auto & value: data->TechnicalRange()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void NumericMetricDescriptor::clearTechnicalRanges() {
	data->TechnicalRange().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

