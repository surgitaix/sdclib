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
 *  StringMetricDescriptor.cpp
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

#include "OSCLib/Data/OSCP/MDIB/StringMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/Duration.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/VersionCounter.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

StringMetricDescriptor::StringMetricDescriptor() : data(Defaults::StringMetricDescriptor()) {
}

StringMetricDescriptor::operator CDM::StringMetricDescriptor() const {
	return *data;
}

StringMetricDescriptor::StringMetricDescriptor(const CDM::StringMetricDescriptor & object) : data(new CDM::StringMetricDescriptor(object)) {

}

StringMetricDescriptor::StringMetricDescriptor(const StringMetricDescriptor & object) : data(new CDM::StringMetricDescriptor(*object.data)) {

}

StringMetricDescriptor::~StringMetricDescriptor() {

}

void StringMetricDescriptor::copyFrom(const StringMetricDescriptor & object) {
	*data = *object.data;
}

StringMetricDescriptor & StringMetricDescriptor:: operator=(const StringMetricDescriptor & object) {
	copyFrom(object);
	return *this;
}


StringMetricDescriptor & StringMetricDescriptor::setType(const CodedValue & value) {
	data->Type(ConvertToCDM::convert(value));
	return *this;
}

bool StringMetricDescriptor::getType(CodedValue & out) const {
	if (data->Type().present()) {
		out = ConvertFromCDM::convert(data->Type().get());
		return true;
	}
	return false;
}

CodedValue StringMetricDescriptor::getType() const {
	return ConvertFromCDM::convert(data->Type().get());
}
	
bool StringMetricDescriptor::hasType() const {
	return data->Type().present();
}
	
StringMetricDescriptor & StringMetricDescriptor::setHandle(const std::string & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}


std::string StringMetricDescriptor::getHandle() const {
	return ConvertFromCDM::convert(data->Handle());
}
	
StringMetricDescriptor & StringMetricDescriptor::setDescriptorVersion(const VersionCounter & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool StringMetricDescriptor::getDescriptorVersion(VersionCounter & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

VersionCounter StringMetricDescriptor::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}
	
bool StringMetricDescriptor::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}
	
StringMetricDescriptor & StringMetricDescriptor::setSafetyClassification(const std::string & value) {
	data->SafetyClassification(ConvertToCDM::convert(value));
	return *this;
}

bool StringMetricDescriptor::getSafetyClassification(std::string & out) const {
	if (data->SafetyClassification().present()) {
		out = ConvertFromCDM::convert(data->SafetyClassification().get());
		return true;
	}
	return false;
}

std::string StringMetricDescriptor::getSafetyClassification() const {
	return ConvertFromCDM::convert(data->SafetyClassification().get());
}
	
bool StringMetricDescriptor::hasSafetyClassification() const {
	return data->SafetyClassification().present();
}
	
StringMetricDescriptor & StringMetricDescriptor::setUnit(const CodedValue & value) {
	data->Unit(ConvertToCDM::convert(value));
	return *this;
}


CodedValue StringMetricDescriptor::getUnit() const {
	return ConvertFromCDM::convert(data->Unit());
}
	
StringMetricDescriptor & StringMetricDescriptor::setMetricCategory(const MetricCategory & value) {
	data->MetricCategory(ConvertToCDM::convert(value));
	return *this;
}


MetricCategory StringMetricDescriptor::getMetricCategory() const {
	return ConvertFromCDM::convert(data->MetricCategory());
}
	
StringMetricDescriptor & StringMetricDescriptor::setAvailability(const MetricAvailability & value) {
	data->Availability(ConvertToCDM::convert(value));
	return *this;
}


MetricAvailability StringMetricDescriptor::getAvailability() const {
	return ConvertFromCDM::convert(data->Availability());
}
	
StringMetricDescriptor & StringMetricDescriptor::setMaxDelayTime(const Duration & value) {
	data->MaxDelayTime(ConvertToCDM::convert(value));
	return *this;
}

bool StringMetricDescriptor::getMaxDelayTime(Duration & out) const {
	if (data->MaxDelayTime().present()) {
		out = ConvertFromCDM::convert(data->MaxDelayTime().get());
		return true;
	}
	return false;
}

Duration StringMetricDescriptor::getMaxDelayTime() const {
	return ConvertFromCDM::convert(data->MaxDelayTime().get());
}
	
bool StringMetricDescriptor::hasMaxDelayTime() const {
	return data->MaxDelayTime().present();
}
	
StringMetricDescriptor & StringMetricDescriptor::addBodySite(const CodedValue & value) {
	data->BodySite().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<CodedValue> StringMetricDescriptor::getBodySites() const {
	std::vector<CodedValue> result;
	result.reserve(data->BodySite().size());
	for (const auto & value: data->BodySite()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void StringMetricDescriptor::clearBodySites() {
	data->BodySite().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

