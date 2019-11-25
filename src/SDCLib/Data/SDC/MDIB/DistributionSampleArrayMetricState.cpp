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
 *  DistributionSampleArrayMetricState.cpp
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

#include "SDCLib/Data/SDC/MDIB/DistributionSampleArrayMetricState.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/SampleArrayValue.h"
#include "SDCLib/Data/SDC/MDIB/Range.h"
#include "SDCLib/Data/SDC/MDIB/CodedValue.h"
#include "SDCLib/Data/SDC/MDIB/PhysicalConnectorInfo.h"

namespace SDCLib {
namespace Data {
namespace SDC {


DistributionSampleArrayMetricState::DistributionSampleArrayMetricState(
		HandleRef descriptorhandle
) : data(Defaults::DistributionSampleArrayMetricStateInit(
		descriptorhandle
)) {}

DistributionSampleArrayMetricState::operator CDM::DistributionSampleArrayMetricState() const {
	return *data;
}

DistributionSampleArrayMetricState::DistributionSampleArrayMetricState(const CDM::DistributionSampleArrayMetricState & object) : data(new CDM::DistributionSampleArrayMetricState(object)) {

}

DistributionSampleArrayMetricState::DistributionSampleArrayMetricState(const DistributionSampleArrayMetricState & object) : data(new CDM::DistributionSampleArrayMetricState(*object.data)) {

}

DistributionSampleArrayMetricState::~DistributionSampleArrayMetricState() {

}

void DistributionSampleArrayMetricState::copyFrom(const DistributionSampleArrayMetricState & object) {
	data = std::shared_ptr<CDM::DistributionSampleArrayMetricState>( new CDM::DistributionSampleArrayMetricState(*object.data));
}

DistributionSampleArrayMetricState & DistributionSampleArrayMetricState:: operator=(const DistributionSampleArrayMetricState & object) {
	copyFrom(object);
	return *this;
}


DistributionSampleArrayMetricState & DistributionSampleArrayMetricState::setStateVersion(const VersionCounter & value) {
	data->setStateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool DistributionSampleArrayMetricState::getStateVersion(VersionCounter & out) const {
	if (data->getStateVersion().present()) {
		out = ConvertFromCDM::convert(data->getStateVersion().get());
		return true;
	}
	return false;
}

VersionCounter DistributionSampleArrayMetricState::getStateVersion() const {
	return ConvertFromCDM::convert(data->getStateVersion().get());
}

bool DistributionSampleArrayMetricState::hasStateVersion() const {
	return data->getStateVersion().present();
}

DistributionSampleArrayMetricState & DistributionSampleArrayMetricState::setDescriptorHandle(const HandleRef & value) {
	data->setDescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


HandleRef DistributionSampleArrayMetricState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->getDescriptorHandle());
}

DistributionSampleArrayMetricState & DistributionSampleArrayMetricState::setDescriptorVersion(const ReferencedVersion & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool DistributionSampleArrayMetricState::getDescriptorVersion(ReferencedVersion & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion DistributionSampleArrayMetricState::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool DistributionSampleArrayMetricState::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

DistributionSampleArrayMetricState & DistributionSampleArrayMetricState::setPhysicalConnector(const PhysicalConnectorInfo & value) {
	data->setPhysicalConnector(ConvertToCDM::convert(value));
	return *this;
}

bool DistributionSampleArrayMetricState::getPhysicalConnector(PhysicalConnectorInfo & out) const {
	if (data->getPhysicalConnector().present()) {
		out = ConvertFromCDM::convert(data->getPhysicalConnector().get());
		return true;
	}
	return false;
}

PhysicalConnectorInfo DistributionSampleArrayMetricState::getPhysicalConnector() const {
	return ConvertFromCDM::convert(data->getPhysicalConnector().get());
}

bool DistributionSampleArrayMetricState::hasPhysicalConnector() const {
	return data->getPhysicalConnector().present();
}

DistributionSampleArrayMetricState & DistributionSampleArrayMetricState::setActivationState(const ComponentActivation & value) {
	data->setActivationState(ConvertToCDM::convert(value));
	return *this;
}

bool DistributionSampleArrayMetricState::getActivationState(ComponentActivation & out) const {
	if (data->getActivationState().present()) {
		out = ConvertFromCDM::convert(data->getActivationState().get());
		return true;
	}
	return false;
}

ComponentActivation DistributionSampleArrayMetricState::getActivationState() const {
	return ConvertFromCDM::convert(data->getActivationState().get());
}

bool DistributionSampleArrayMetricState::hasActivationState() const {
	return data->getActivationState().present();
}

DistributionSampleArrayMetricState & DistributionSampleArrayMetricState::setActiveDeterminationPeriod(const xml_schema::Duration & value) {
	data->setActiveDeterminationPeriod(ConvertToCDM::convert(value));
	return *this;
}

bool DistributionSampleArrayMetricState::getActiveDeterminationPeriod(xml_schema::Duration & out) const {
	if (data->getActiveDeterminationPeriod().present()) {
		out = ConvertFromCDM::convert(data->getActiveDeterminationPeriod().get());
		return true;
	}
	return false;
}

xml_schema::Duration DistributionSampleArrayMetricState::getActiveDeterminationPeriod() const {
	return ConvertFromCDM::convert(data->getActiveDeterminationPeriod().get());
}

bool DistributionSampleArrayMetricState::hasActiveDeterminationPeriod() const {
	return data->getActiveDeterminationPeriod().present();
}

DistributionSampleArrayMetricState & DistributionSampleArrayMetricState::setLifeTimePeriod(const xml_schema::Duration & value) {
	data->setLifeTimePeriod(ConvertToCDM::convert(value));
	return *this;
}

bool DistributionSampleArrayMetricState::getLifeTimePeriod(xml_schema::Duration & out) const {
	if (data->getLifeTimePeriod().present()) {
		out = ConvertFromCDM::convert(data->getLifeTimePeriod().get());
		return true;
	}
	return false;
}

xml_schema::Duration DistributionSampleArrayMetricState::getLifeTimePeriod() const {
	return ConvertFromCDM::convert(data->getLifeTimePeriod().get());
}

bool DistributionSampleArrayMetricState::hasLifeTimePeriod() const {
	return data->getLifeTimePeriod().present();
}

DistributionSampleArrayMetricState & DistributionSampleArrayMetricState::addBodySite(const CodedValue & value) {
	data->getBodySite().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<CodedValue> DistributionSampleArrayMetricState::getBodySiteList() const {
	std::vector<CodedValue> result;
	result.reserve(data->getBodySite().size());
	for (const auto & value: data->getBodySite()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void DistributionSampleArrayMetricState::clearBodySiteList() {
	data->getBodySite().clear();
}

DistributionSampleArrayMetricState & DistributionSampleArrayMetricState::setMetricValue(const SampleArrayValue & value) {
	data->setMetricValue(ConvertToCDM::convert(value));
	return *this;
}

bool DistributionSampleArrayMetricState::getMetricValue(SampleArrayValue & out) const {
	if (data->getMetricValue().present()) {
		out = ConvertFromCDM::convert(data->getMetricValue().get());
		return true;
	}
	return false;
}

SampleArrayValue DistributionSampleArrayMetricState::getMetricValue() const {
	return ConvertFromCDM::convert(data->getMetricValue().get());
}

bool DistributionSampleArrayMetricState::hasMetricValue() const {
	return data->getMetricValue().present();
}

DistributionSampleArrayMetricState & DistributionSampleArrayMetricState::addPhysiologicalRange(const Range & value) {
	data->getPhysiologicalRange().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<Range> DistributionSampleArrayMetricState::getPhysiologicalRangeList() const {
	std::vector<Range> result;
	result.reserve(data->getPhysiologicalRange().size());
	for (const auto & value: data->getPhysiologicalRange()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void DistributionSampleArrayMetricState::clearPhysiologicalRangeList() {
	data->getPhysiologicalRange().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

