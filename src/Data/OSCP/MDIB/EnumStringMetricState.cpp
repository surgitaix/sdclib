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
 *  EnumStringMetricState.cpp
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

#include "OSCLib/Data/OSCP/MDIB/EnumStringMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/StringMetricValue.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

EnumStringMetricState::EnumStringMetricState() : data(Defaults::EnumStringMetricState()) {
}

EnumStringMetricState::operator CDM::EnumStringMetricState() const {
	return *data;
}

EnumStringMetricState::EnumStringMetricState(const CDM::EnumStringMetricState & object) : data(new CDM::EnumStringMetricState(object)) {

}

EnumStringMetricState::EnumStringMetricState(const EnumStringMetricState & object) : data(new CDM::EnumStringMetricState(*object.data)) {

}

EnumStringMetricState::~EnumStringMetricState() {

}

void EnumStringMetricState::copyFrom(const EnumStringMetricState & object) {
	*data = *object.data;
}

EnumStringMetricState & EnumStringMetricState:: operator=(const EnumStringMetricState & object) {
	copyFrom(object);
	return *this;
}


EnumStringMetricState & EnumStringMetricState::setStateVersion(const VersionCounter & value) {
	data->StateVersion(ConvertToCDM::convert(value));
	return *this;
}


VersionCounter EnumStringMetricState::getStateVersion() const {
	return ConvertFromCDM::convert(data->StateVersion());
}
	
EnumStringMetricState & EnumStringMetricState::setDescriptorHandle(const HandleRef & value) {
	data->DescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


HandleRef EnumStringMetricState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->DescriptorHandle());
}
	
EnumStringMetricState & EnumStringMetricState::setDescriptorVersion(const ReferencedVersion & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}


ReferencedVersion EnumStringMetricState::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion());
}
	
EnumStringMetricState & EnumStringMetricState::setActivationState(const ComponentActivation & value) {
	data->ActivationState(ConvertToCDM::convert(value));
	return *this;
}


ComponentActivation EnumStringMetricState::getActivationState() const {
	return ConvertFromCDM::convert(data->ActivationState());
}
	
EnumStringMetricState & EnumStringMetricState::setActiveDeterminationPeriod(const duration & value) {
	data->ActiveDeterminationPeriod(ConvertToCDM::convert(value));
	return *this;
}


duration EnumStringMetricState::getActiveDeterminationPeriod() const {
	return ConvertFromCDM::convert(data->ActiveDeterminationPeriod());
}
	
EnumStringMetricState & EnumStringMetricState::setLifeTimePeriod(const duration & value) {
	data->LifeTimePeriod(ConvertToCDM::convert(value));
	return *this;
}

bool EnumStringMetricState::getLifeTimePeriod(duration & out) const {
	if (data->LifeTimePeriod().present()) {
		out = ConvertFromCDM::convert(data->LifeTimePeriod().get());
		return true;
	}
	return false;
}

duration EnumStringMetricState::getLifeTimePeriod() const {
	return ConvertFromCDM::convert(data->LifeTimePeriod().get());
}
	
bool EnumStringMetricState::hasLifeTimePeriod() const {
	return data->LifeTimePeriod().present();
}
	
EnumStringMetricState & EnumStringMetricState::addBodySite(const CodedValue & value) {
	data->BodySite().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<CodedValue> EnumStringMetricState::getBodySites() const {
	std::vector<CodedValue> result;
	result.reserve(data->BodySite().size());
	for (const auto & value: data->BodySite()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void EnumStringMetricState::clearBodySites() {
	data->BodySite().clear();
}

EnumStringMetricState & EnumStringMetricState::setMetricValue(const StringMetricValue & value) {
	data->MetricValue(ConvertToCDM::convert(value));
	return *this;
}

bool EnumStringMetricState::getMetricValue(StringMetricValue & out) const {
	if (data->MetricValue().present()) {
		out = ConvertFromCDM::convert(data->MetricValue().get());
		return true;
	}
	return false;
}

StringMetricValue EnumStringMetricState::getMetricValue() const {
	return ConvertFromCDM::convert(data->MetricValue().get());
}
	
bool EnumStringMetricState::hasMetricValue() const {
	return data->MetricValue().present();
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

