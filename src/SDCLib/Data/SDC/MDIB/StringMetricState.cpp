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
 *  Author: besting, buerger, roehser
 */

/**
 * THIS FILE IS GENERATED AUTOMATICALLY! DO NOT MODIFY!
 *
 * YOUR CHANGES WILL BE OVERWRITTEN!
 *
 * USE THE DEFINITION FILES IN THE FOLDER "codegenerator" INSTEAD!
 */

#include "SDCLib/Data/SDC/MDIB/StringMetricState.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/StringMetricValue.h"
#include "SDCLib/Data/SDC/MDIB/CodedValue.h"
#include "SDCLib/Data/SDC/MDIB/PhysicalConnectorInfo.h"

namespace SDCLib {
namespace Data {
namespace SDC {


StringMetricState::StringMetricState(
		HandleRef descriptorhandle
) : data(Defaults::StringMetricStateInit(
		descriptorhandle
)) {}

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
	data = std::shared_ptr<CDM::StringMetricState>( new CDM::StringMetricState(*object.data));
}

StringMetricState & StringMetricState:: operator=(const StringMetricState & object) {
	copyFrom(object);
	return *this;
}


StringMetricState & StringMetricState::setStateVersion(const VersionCounter & value) {
	data->setStateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool StringMetricState::getStateVersion(VersionCounter & out) const {
	if (data->getStateVersion().present()) {
		out = ConvertFromCDM::convert(data->getStateVersion().get());
		return true;
	}
	return false;
}

VersionCounter StringMetricState::getStateVersion() const {
	return ConvertFromCDM::convert(data->getStateVersion().get());
}

bool StringMetricState::hasStateVersion() const {
	return data->getStateVersion().present();
}

StringMetricState & StringMetricState::setDescriptorHandle(const HandleRef & value) {
	data->setDescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


HandleRef StringMetricState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->getDescriptorHandle());
}

StringMetricState & StringMetricState::setDescriptorVersion(const ReferencedVersion & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool StringMetricState::getDescriptorVersion(ReferencedVersion & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion StringMetricState::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool StringMetricState::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

StringMetricState & StringMetricState::setPhysicalConnector(const PhysicalConnectorInfo & value) {
	data->setPhysicalConnector(ConvertToCDM::convert(value));
	return *this;
}

bool StringMetricState::getPhysicalConnector(PhysicalConnectorInfo & out) const {
	if (data->getPhysicalConnector().present()) {
		out = ConvertFromCDM::convert(data->getPhysicalConnector().get());
		return true;
	}
	return false;
}

PhysicalConnectorInfo StringMetricState::getPhysicalConnector() const {
	return ConvertFromCDM::convert(data->getPhysicalConnector().get());
}

bool StringMetricState::hasPhysicalConnector() const {
	return data->getPhysicalConnector().present();
}

StringMetricState & StringMetricState::setActivationState(const ComponentActivation & value) {
	data->setActivationState(ConvertToCDM::convert(value));
	return *this;
}

bool StringMetricState::getActivationState(ComponentActivation & out) const {
	if (data->getActivationState().present()) {
		out = ConvertFromCDM::convert(data->getActivationState().get());
		return true;
	}
	return false;
}

ComponentActivation StringMetricState::getActivationState() const {
	return ConvertFromCDM::convert(data->getActivationState().get());
}

bool StringMetricState::hasActivationState() const {
	return data->getActivationState().present();
}

StringMetricState & StringMetricState::setActiveDeterminationPeriod(const xml_schema::Duration & value) {
	data->setActiveDeterminationPeriod(ConvertToCDM::convert(value));
	return *this;
}

bool StringMetricState::getActiveDeterminationPeriod(xml_schema::Duration & out) const {
	if (data->getActiveDeterminationPeriod().present()) {
		out = ConvertFromCDM::convert(data->getActiveDeterminationPeriod().get());
		return true;
	}
	return false;
}

xml_schema::Duration StringMetricState::getActiveDeterminationPeriod() const {
	return ConvertFromCDM::convert(data->getActiveDeterminationPeriod().get());
}

bool StringMetricState::hasActiveDeterminationPeriod() const {
	return data->getActiveDeterminationPeriod().present();
}

StringMetricState & StringMetricState::setLifeTimePeriod(const xml_schema::Duration & value) {
	data->setLifeTimePeriod(ConvertToCDM::convert(value));
	return *this;
}

bool StringMetricState::getLifeTimePeriod(xml_schema::Duration & out) const {
	if (data->getLifeTimePeriod().present()) {
		out = ConvertFromCDM::convert(data->getLifeTimePeriod().get());
		return true;
	}
	return false;
}

xml_schema::Duration StringMetricState::getLifeTimePeriod() const {
	return ConvertFromCDM::convert(data->getLifeTimePeriod().get());
}

bool StringMetricState::hasLifeTimePeriod() const {
	return data->getLifeTimePeriod().present();
}

StringMetricState & StringMetricState::addBodySite(const CodedValue & value) {
	data->getBodySite().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<CodedValue> StringMetricState::getBodySiteList() const {
	std::vector<CodedValue> result;
	result.reserve(data->getBodySite().size());
	for (const auto & value: data->getBodySite()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void StringMetricState::clearBodySiteList() {
	data->getBodySite().clear();
}

StringMetricState & StringMetricState::setMetricValue(const StringMetricValue & value) {
	data->setMetricValue(ConvertToCDM::convert(value));
	return *this;
}

bool StringMetricState::getMetricValue(StringMetricValue & out) const {
	if (data->getMetricValue().present()) {
		out = ConvertFromCDM::convert(data->getMetricValue().get());
		return true;
	}
	return false;
}

StringMetricValue StringMetricState::getMetricValue() const {
	return ConvertFromCDM::convert(data->getMetricValue().get());
}

bool StringMetricState::hasMetricValue() const {
	return data->getMetricValue().present();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

