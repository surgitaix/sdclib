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
 *  Author: besting, buerger, roehser
 */

/**
 * THIS FILE IS GENERATED AUTOMATICALLY! DO NOT MODIFY!
 *
 * YOUR CHANGES WILL BE OVERWRITTEN!
 *
 * USE THE DEFINITION FILES IN THE FOLDER "codegenerator" INSTEAD!
 */

#include "SDCLib/Data/SDC/MDIB/EnumStringMetricState.h"
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


EnumStringMetricState::EnumStringMetricState(
		HandleRef descriptorhandle
) : data(Defaults::EnumStringMetricStateInit(
		descriptorhandle
))
{}

EnumStringMetricState::operator CDM::EnumStringMetricState() const {
	return *data;
}

EnumStringMetricState::EnumStringMetricState(const CDM::EnumStringMetricState & object)
: data(new CDM::EnumStringMetricState(object))
{ }

EnumStringMetricState::EnumStringMetricState(const EnumStringMetricState & object)
: data(std::make_shared<CDM::EnumStringMetricState>(*object.data))
{ }

void EnumStringMetricState::copyFrom(const EnumStringMetricState & object) {
	data = std::make_shared<CDM::EnumStringMetricState>(*object.data);
}

EnumStringMetricState & EnumStringMetricState:: operator=(const EnumStringMetricState& object) {
	copyFrom(object);
	return *this;
}


EnumStringMetricState & EnumStringMetricState::setStateVersion(const VersionCounter & value) {
	data->setStateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool EnumStringMetricState::getStateVersion(VersionCounter & out) const {
	if (data->getStateVersion().present()) {
		out = ConvertFromCDM::convert(data->getStateVersion().get());
		return true;
	}
	return false;
}

VersionCounter EnumStringMetricState::getStateVersion() const {
	return ConvertFromCDM::convert(data->getStateVersion().get());
}

bool EnumStringMetricState::hasStateVersion() const {
	return data->getStateVersion().present();
}

EnumStringMetricState & EnumStringMetricState::setDescriptorHandle(const HandleRef & value) {
	data->setDescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


HandleRef EnumStringMetricState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->getDescriptorHandle());
}

EnumStringMetricState & EnumStringMetricState::setDescriptorVersion(const ReferencedVersion & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool EnumStringMetricState::getDescriptorVersion(ReferencedVersion & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion EnumStringMetricState::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool EnumStringMetricState::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

EnumStringMetricState & EnumStringMetricState::setPhysicalConnector(const PhysicalConnectorInfo & value) {
	data->setPhysicalConnector(ConvertToCDM::convert(value));
	return *this;
}

bool EnumStringMetricState::getPhysicalConnector(PhysicalConnectorInfo & out) const {
	if (data->getPhysicalConnector().present()) {
		out = ConvertFromCDM::convert(data->getPhysicalConnector().get());
		return true;
	}
	return false;
}

PhysicalConnectorInfo EnumStringMetricState::getPhysicalConnector() const {
	return ConvertFromCDM::convert(data->getPhysicalConnector().get());
}

bool EnumStringMetricState::hasPhysicalConnector() const {
	return data->getPhysicalConnector().present();
}

EnumStringMetricState & EnumStringMetricState::setActivationState(const ComponentActivation & value) {
	data->setActivationState(ConvertToCDM::convert(value));
	return *this;
}

bool EnumStringMetricState::getActivationState(ComponentActivation & out) const {
	if (data->getActivationState().present()) {
		out = ConvertFromCDM::convert(data->getActivationState().get());
		return true;
	}
	return false;
}

ComponentActivation EnumStringMetricState::getActivationState() const {
	return ConvertFromCDM::convert(data->getActivationState().get());
}

bool EnumStringMetricState::hasActivationState() const {
	return data->getActivationState().present();
}

EnumStringMetricState & EnumStringMetricState::setActiveDeterminationPeriod(const xml_schema::Duration & value) {
	data->setActiveDeterminationPeriod(ConvertToCDM::convert(value));
	return *this;
}

bool EnumStringMetricState::getActiveDeterminationPeriod(xml_schema::Duration & out) const {
	if (data->getActiveDeterminationPeriod().present()) {
		out = ConvertFromCDM::convert(data->getActiveDeterminationPeriod().get());
		return true;
	}
	return false;
}

xml_schema::Duration EnumStringMetricState::getActiveDeterminationPeriod() const {
	return ConvertFromCDM::convert(data->getActiveDeterminationPeriod().get());
}

bool EnumStringMetricState::hasActiveDeterminationPeriod() const {
	return data->getActiveDeterminationPeriod().present();
}

EnumStringMetricState & EnumStringMetricState::setLifeTimePeriod(const xml_schema::Duration & value) {
	data->setLifeTimePeriod(ConvertToCDM::convert(value));
	return *this;
}

bool EnumStringMetricState::getLifeTimePeriod(xml_schema::Duration & out) const {
	if (data->getLifeTimePeriod().present()) {
		out = ConvertFromCDM::convert(data->getLifeTimePeriod().get());
		return true;
	}
	return false;
}

xml_schema::Duration EnumStringMetricState::getLifeTimePeriod() const {
	return ConvertFromCDM::convert(data->getLifeTimePeriod().get());
}

bool EnumStringMetricState::hasLifeTimePeriod() const {
	return data->getLifeTimePeriod().present();
}

EnumStringMetricState & EnumStringMetricState::addBodySite(const CodedValue & value) {
	data->getBodySite().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<CodedValue> EnumStringMetricState::getBodySiteList() const {
	std::vector<CodedValue> result;
	result.reserve(data->getBodySite().size());
	for (const auto & value: data->getBodySite()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void EnumStringMetricState::clearBodySiteList() {
	data->getBodySite().clear();
}

EnumStringMetricState & EnumStringMetricState::setMetricValue(const StringMetricValue & value) {
	data->setMetricValue(ConvertToCDM::convert(value));
	return *this;
}

bool EnumStringMetricState::getMetricValue(StringMetricValue & out) const {
	if (data->getMetricValue().present()) {
		out = ConvertFromCDM::convert(data->getMetricValue().get());
		return true;
	}
	return false;
}

StringMetricValue EnumStringMetricState::getMetricValue() const {
	return ConvertFromCDM::convert(data->getMetricValue().get());
}

bool EnumStringMetricState::hasMetricValue() const {
	return data->getMetricValue().present();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

