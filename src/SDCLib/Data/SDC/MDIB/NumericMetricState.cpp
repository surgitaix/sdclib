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
 *  NumericMetricState.cpp
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

#include "SDCLib/Data/SDC/MDIB/NumericMetricState.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/NumericMetricValue.h"
#include "SDCLib/Data/SDC/MDIB/Range.h"
#include "SDCLib/Data/SDC/MDIB/CodedValue.h"
#include "SDCLib/Data/SDC/MDIB/PhysicalConnectorInfo.h"

namespace SDCLib {
namespace Data {
namespace SDC {


NumericMetricState::NumericMetricState(
		HandleRef descriptorhandle
) : data(Defaults::NumericMetricStateInit(
		descriptorhandle
)) {}

NumericMetricState::operator CDM::NumericMetricState() const {
	return *data;
}

NumericMetricState::NumericMetricState(const CDM::NumericMetricState & object) : data(new CDM::NumericMetricState(object)) {

}

NumericMetricState::NumericMetricState(const NumericMetricState & object) : data(new CDM::NumericMetricState(*object.data)) {

}

NumericMetricState::~NumericMetricState() {

}

void NumericMetricState::copyFrom(const NumericMetricState & object) {
	data = std::shared_ptr<CDM::NumericMetricState>( new CDM::NumericMetricState(*object.data));
}

NumericMetricState & NumericMetricState:: operator=(const NumericMetricState & object) {
	copyFrom(object);
	return *this;
}


NumericMetricState & NumericMetricState::setStateVersion(const VersionCounter & value) {
	data->setStateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool NumericMetricState::getStateVersion(VersionCounter & out) const {
	if (data->getStateVersion().present()) {
		out = ConvertFromCDM::convert(data->getStateVersion().get());
		return true;
	}
	return false;
}

VersionCounter NumericMetricState::getStateVersion() const {
	return ConvertFromCDM::convert(data->getStateVersion().get());
}

bool NumericMetricState::hasStateVersion() const {
	return data->getStateVersion().present();
}

NumericMetricState & NumericMetricState::setDescriptorHandle(const HandleRef & value) {
	data->setDescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


HandleRef NumericMetricState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->getDescriptorHandle());
}

NumericMetricState & NumericMetricState::setDescriptorVersion(const ReferencedVersion & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool NumericMetricState::getDescriptorVersion(ReferencedVersion & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion NumericMetricState::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool NumericMetricState::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

NumericMetricState & NumericMetricState::setPhysicalConnector(const PhysicalConnectorInfo & value) {
	data->setPhysicalConnector(ConvertToCDM::convert(value));
	return *this;
}

bool NumericMetricState::getPhysicalConnector(PhysicalConnectorInfo & out) const {
	if (data->getPhysicalConnector().present()) {
		out = ConvertFromCDM::convert(data->getPhysicalConnector().get());
		return true;
	}
	return false;
}

PhysicalConnectorInfo NumericMetricState::getPhysicalConnector() const {
	return ConvertFromCDM::convert(data->getPhysicalConnector().get());
}

bool NumericMetricState::hasPhysicalConnector() const {
	return data->getPhysicalConnector().present();
}

NumericMetricState & NumericMetricState::setActivationState(const ComponentActivation & value) {
	data->setActivationState(ConvertToCDM::convert(value));
	return *this;
}

bool NumericMetricState::getActivationState(ComponentActivation & out) const {
	if (data->getActivationState().present()) {
		out = ConvertFromCDM::convert(data->getActivationState().get());
		return true;
	}
	return false;
}

ComponentActivation NumericMetricState::getActivationState() const {
	return ConvertFromCDM::convert(data->getActivationState().get());
}

bool NumericMetricState::hasActivationState() const {
	return data->getActivationState().present();
}

NumericMetricState & NumericMetricState::setActiveDeterminationPeriod(const xml_schema::Duration & value) {
	data->setActiveDeterminationPeriod(ConvertToCDM::convert(value));
	return *this;
}

bool NumericMetricState::getActiveDeterminationPeriod(xml_schema::Duration & out) const {
	if (data->getActiveDeterminationPeriod().present()) {
		out = ConvertFromCDM::convert(data->getActiveDeterminationPeriod().get());
		return true;
	}
	return false;
}

xml_schema::Duration NumericMetricState::getActiveDeterminationPeriod() const {
	return ConvertFromCDM::convert(data->getActiveDeterminationPeriod().get());
}

bool NumericMetricState::hasActiveDeterminationPeriod() const {
	return data->getActiveDeterminationPeriod().present();
}

NumericMetricState & NumericMetricState::setLifeTimePeriod(const xml_schema::Duration & value) {
	data->setLifeTimePeriod(ConvertToCDM::convert(value));
	return *this;
}

bool NumericMetricState::getLifeTimePeriod(xml_schema::Duration & out) const {
	if (data->getLifeTimePeriod().present()) {
		out = ConvertFromCDM::convert(data->getLifeTimePeriod().get());
		return true;
	}
	return false;
}

xml_schema::Duration NumericMetricState::getLifeTimePeriod() const {
	return ConvertFromCDM::convert(data->getLifeTimePeriod().get());
}

bool NumericMetricState::hasLifeTimePeriod() const {
	return data->getLifeTimePeriod().present();
}

NumericMetricState & NumericMetricState::addBodySite(const CodedValue & value) {
	data->getBodySite().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<CodedValue> NumericMetricState::getBodySiteList() const {
	std::vector<CodedValue> result;
	result.reserve(data->getBodySite().size());
	for (const auto & value: data->getBodySite()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void NumericMetricState::clearBodySiteList() {
	data->getBodySite().clear();
}

NumericMetricState & NumericMetricState::setMetricValue(const NumericMetricValue & value) {
	data->setMetricValue(ConvertToCDM::convert(value));
	return *this;
}

bool NumericMetricState::getMetricValue(NumericMetricValue & out) const {
	if (data->getMetricValue().present()) {
		out = ConvertFromCDM::convert(data->getMetricValue().get());
		return true;
	}
	return false;
}

NumericMetricValue NumericMetricState::getMetricValue() const {
	return ConvertFromCDM::convert(data->getMetricValue().get());
}

bool NumericMetricState::hasMetricValue() const {
	return data->getMetricValue().present();
}

NumericMetricState & NumericMetricState::setActiveAveragingPeriod(const xml_schema::Duration & value) {
	data->setActiveAveragingPeriod(ConvertToCDM::convert(value));
	return *this;
}

bool NumericMetricState::getActiveAveragingPeriod(xml_schema::Duration & out) const {
	if (data->getActiveAveragingPeriod().present()) {
		out = ConvertFromCDM::convert(data->getActiveAveragingPeriod().get());
		return true;
	}
	return false;
}

xml_schema::Duration NumericMetricState::getActiveAveragingPeriod() const {
	return ConvertFromCDM::convert(data->getActiveAveragingPeriod().get());
}

bool NumericMetricState::hasActiveAveragingPeriod() const {
	return data->getActiveAveragingPeriod().present();
}

NumericMetricState & NumericMetricState::addPhysiologicalRange(const Range & value) {
	data->getPhysiologicalRange().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<Range> NumericMetricState::getPhysiologicalRangeList() const {
	std::vector<Range> result;
	result.reserve(data->getPhysiologicalRange().size());
	for (const auto & value: data->getPhysiologicalRange()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void NumericMetricState::clearPhysiologicalRangeList() {
	data->getPhysiologicalRange().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

