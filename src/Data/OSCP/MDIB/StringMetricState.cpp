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
 *  StringMetricState.cpp
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

#include "OSCLib/Data/OSCP/MDIB/StringMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/StringMetricValue.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

StringMetricState::StringMetricState() : data(Defaults::StringMetricState()) {
}

StringMetricState::operator CDM::StringMetricState() const {
	return *data;
}

StringMetricState::StringMetricState(const CDM::StringMetricState & object) : data(new CDM::StringMetricState(object)) {

}

StringMetricState::StringMetricState(const StringMetricState & object) : data(new CDM::StringMetricState(*object.data)) {

}

StringMetricState::~StringMetricState() {

}

void StringMetricState::copyFrom(const StringMetricState & object) {
	*data = *object.data;
}

StringMetricState & StringMetricState:: operator=(const StringMetricState & object) {
	copyFrom(object);
	return *this;
}


StringMetricState & StringMetricState::setStateVersion(const VersionCounter & value) {
	data->StateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool StringMetricState::getStateVersion(VersionCounter & out) const {
	if (data->StateVersion().present()) {
		out = ConvertFromCDM::convert(data->StateVersion().get());
		return true;
	}
	return false;
}

VersionCounter StringMetricState::getStateVersion() const {
	return ConvertFromCDM::convert(data->StateVersion().get());
}
	
bool StringMetricState::hasStateVersion() const {
	return data->StateVersion().present();
}
	
StringMetricState & StringMetricState::setDescriptorHandle(const HandleRef & value) {
	data->DescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


HandleRef StringMetricState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->DescriptorHandle());
}
	
StringMetricState & StringMetricState::setDescriptorVersion(const ReferencedVersion & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool StringMetricState::getDescriptorVersion(ReferencedVersion & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion StringMetricState::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}
	
bool StringMetricState::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}
	
StringMetricState & StringMetricState::setActivationState(const ComponentActivation & value) {
	data->ActivationState(ConvertToCDM::convert(value));
	return *this;
}

bool StringMetricState::getActivationState(ComponentActivation & out) const {
	if (data->ActivationState().present()) {
		out = ConvertFromCDM::convert(data->ActivationState().get());
		return true;
	}
	return false;
}

ComponentActivation StringMetricState::getActivationState() const {
	return ConvertFromCDM::convert(data->ActivationState().get());
}
	
bool StringMetricState::hasActivationState() const {
	return data->ActivationState().present();
}
	
StringMetricState & StringMetricState::setActiveDeterminationPeriod(const xml_schema::Duration & value) {
	data->ActiveDeterminationPeriod(ConvertToCDM::convert(value));
	return *this;
}

bool StringMetricState::getActiveDeterminationPeriod(xml_schema::Duration & out) const {
	if (data->ActiveDeterminationPeriod().present()) {
		out = ConvertFromCDM::convert(data->ActiveDeterminationPeriod().get());
		return true;
	}
	return false;
}

xml_schema::Duration StringMetricState::getActiveDeterminationPeriod() const {
	return ConvertFromCDM::convert(data->ActiveDeterminationPeriod().get());
}
	
bool StringMetricState::hasActiveDeterminationPeriod() const {
	return data->ActiveDeterminationPeriod().present();
}
	
StringMetricState & StringMetricState::setLifeTimePeriod(const xml_schema::Duration & value) {
	data->LifeTimePeriod(ConvertToCDM::convert(value));
	return *this;
}

bool StringMetricState::getLifeTimePeriod(xml_schema::Duration & out) const {
	if (data->LifeTimePeriod().present()) {
		out = ConvertFromCDM::convert(data->LifeTimePeriod().get());
		return true;
	}
	return false;
}

xml_schema::Duration StringMetricState::getLifeTimePeriod() const {
	return ConvertFromCDM::convert(data->LifeTimePeriod().get());
}
	
bool StringMetricState::hasLifeTimePeriod() const {
	return data->LifeTimePeriod().present();
}
	
StringMetricState & StringMetricState::addBodySite(const CodedValue & value) {
	data->BodySite().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<CodedValue> StringMetricState::getBodySiteLists() const {
	std::vector<CodedValue> result;
	result.reserve(data->BodySite().size());
	for (const auto & value: data->BodySite()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void StringMetricState::clearBodySiteLists() {
	data->BodySite().clear();
}

StringMetricState & StringMetricState::setMetricValue(const StringMetricValue & value) {
	data->MetricValue(ConvertToCDM::convert(value));
	return *this;
}

bool StringMetricState::getMetricValue(StringMetricValue & out) const {
	if (data->MetricValue().present()) {
		out = ConvertFromCDM::convert(data->MetricValue().get());
		return true;
	}
	return false;
}

StringMetricValue StringMetricState::getMetricValue() const {
	return ConvertFromCDM::convert(data->MetricValue().get());
}
	
bool StringMetricState::hasMetricValue() const {
	return data->MetricValue().present();
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

