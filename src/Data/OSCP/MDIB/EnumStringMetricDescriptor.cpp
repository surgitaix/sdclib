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

#include "OSCLib/Data/OSCP/MDIB/EnumNomenRef.h"
#include "OSCLib/Data/OSCP/MDIB/StringMetricDescriptor.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/Duration.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/VersionCounter.h"

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
	
EnumStringMetricDescriptor & EnumStringMetricDescriptor::setHandle(const std::string & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}


std::string EnumStringMetricDescriptor::getHandle() const {
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
	
EnumStringMetricDescriptor & EnumStringMetricDescriptor::setIntendedUse(const IntendedUse & value) {
	data->IntendedUse(ConvertToCDM::convert(value));
	return *this;
}

bool EnumStringMetricDescriptor::getIntendedUse(IntendedUse & out) const {
	if (data->IntendedUse().present()) {
		out = ConvertFromCDM::convert(data->IntendedUse().get());
		return true;
	}
	return false;
}

IntendedUse EnumStringMetricDescriptor::getIntendedUse() const {
	return ConvertFromCDM::convert(data->IntendedUse().get());
}
	
bool EnumStringMetricDescriptor::hasIntendedUse() const {
	return data->IntendedUse().present();
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
	
EnumStringMetricDescriptor & EnumStringMetricDescriptor::setAvailability(const MetricAvailability & value) {
	data->Availability(ConvertToCDM::convert(value));
	return *this;
}


MetricAvailability EnumStringMetricDescriptor::getAvailability() const {
	return ConvertFromCDM::convert(data->Availability());
}
	
EnumStringMetricDescriptor & EnumStringMetricDescriptor::setMaxDelayTime(const Duration & value) {
	data->MaxDelayTime(ConvertToCDM::convert(value));
	return *this;
}

bool EnumStringMetricDescriptor::getMaxDelayTime(Duration & out) const {
	if (data->MaxDelayTime().present()) {
		out = ConvertFromCDM::convert(data->MaxDelayTime().get());
		return true;
	}
	return false;
}

Duration EnumStringMetricDescriptor::getMaxDelayTime() const {
	return ConvertFromCDM::convert(data->MaxDelayTime().get());
}
	
bool EnumStringMetricDescriptor::hasMaxDelayTime() const {
	return data->MaxDelayTime().present();
}
	
EnumStringMetricDescriptor & EnumStringMetricDescriptor::addBodySite(const CodedValue & value) {
	data->BodySite().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<CodedValue> EnumStringMetricDescriptor::getBodySites() const {
	std::vector<CodedValue> result;
	result.reserve(data->BodySite().size());
	for (const auto & value: data->BodySite()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void EnumStringMetricDescriptor::clearBodySites() {
	data->BodySite().clear();
}

EnumStringMetricDescriptor & EnumStringMetricDescriptor::addAllowedValue(const std::string & value) {
	data->AllowedValue().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<std::string> EnumStringMetricDescriptor::getAllowedValues() const {
	std::vector<std::string> result;
	result.reserve(data->AllowedValue().size());
	for (const auto & value: data->AllowedValue()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void EnumStringMetricDescriptor::clearAllowedValues() {
	data->AllowedValue().clear();
}

EnumStringMetricDescriptor & EnumStringMetricDescriptor::addEnumCodes(const EnumNomenRef & value) {
	data->EnumCodes().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<EnumNomenRef> EnumStringMetricDescriptor::getEnumCodes() const {
	std::vector<EnumNomenRef> result;
	result.reserve(data->EnumCodes().size());
	for (const auto & value: data->EnumCodes()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void EnumStringMetricDescriptor::clearEnumCodes() {
	data->EnumCodes().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

