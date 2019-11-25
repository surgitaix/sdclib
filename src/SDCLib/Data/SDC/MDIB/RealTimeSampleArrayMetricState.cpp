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
 *  RealTimeSampleArrayMetricState.cpp
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

#include "SDCLib/Data/SDC/MDIB/RealTimeSampleArrayMetricState.h"
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


RealTimeSampleArrayMetricState::RealTimeSampleArrayMetricState(
		HandleRef descriptorhandle
) : data(Defaults::RealTimeSampleArrayMetricStateInit(
		descriptorhandle
)) {}

RealTimeSampleArrayMetricState::operator CDM::RealTimeSampleArrayMetricState() const {
	return *data;
}

RealTimeSampleArrayMetricState::RealTimeSampleArrayMetricState(const CDM::RealTimeSampleArrayMetricState & object) : data(new CDM::RealTimeSampleArrayMetricState(object)) {

}

RealTimeSampleArrayMetricState::RealTimeSampleArrayMetricState(const RealTimeSampleArrayMetricState & object) : data(new CDM::RealTimeSampleArrayMetricState(*object.data)) {

}

RealTimeSampleArrayMetricState::~RealTimeSampleArrayMetricState() {

}

void RealTimeSampleArrayMetricState::copyFrom(const RealTimeSampleArrayMetricState & object) {
	data = std::shared_ptr<CDM::RealTimeSampleArrayMetricState>( new CDM::RealTimeSampleArrayMetricState(*object.data));
}

RealTimeSampleArrayMetricState & RealTimeSampleArrayMetricState:: operator=(const RealTimeSampleArrayMetricState & object) {
	copyFrom(object);
	return *this;
}


RealTimeSampleArrayMetricState & RealTimeSampleArrayMetricState::setStateVersion(const VersionCounter & value) {
	data->setStateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool RealTimeSampleArrayMetricState::getStateVersion(VersionCounter & out) const {
	if (data->getStateVersion().present()) {
		out = ConvertFromCDM::convert(data->getStateVersion().get());
		return true;
	}
	return false;
}

VersionCounter RealTimeSampleArrayMetricState::getStateVersion() const {
	return ConvertFromCDM::convert(data->getStateVersion().get());
}

bool RealTimeSampleArrayMetricState::hasStateVersion() const {
	return data->getStateVersion().present();
}

RealTimeSampleArrayMetricState & RealTimeSampleArrayMetricState::setDescriptorHandle(const HandleRef & value) {
	data->setDescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


HandleRef RealTimeSampleArrayMetricState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->getDescriptorHandle());
}

RealTimeSampleArrayMetricState & RealTimeSampleArrayMetricState::setDescriptorVersion(const ReferencedVersion & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool RealTimeSampleArrayMetricState::getDescriptorVersion(ReferencedVersion & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion RealTimeSampleArrayMetricState::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool RealTimeSampleArrayMetricState::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

RealTimeSampleArrayMetricState & RealTimeSampleArrayMetricState::setPhysicalConnector(const PhysicalConnectorInfo & value) {
	data->setPhysicalConnector(ConvertToCDM::convert(value));
	return *this;
}

bool RealTimeSampleArrayMetricState::getPhysicalConnector(PhysicalConnectorInfo & out) const {
	if (data->getPhysicalConnector().present()) {
		out = ConvertFromCDM::convert(data->getPhysicalConnector().get());
		return true;
	}
	return false;
}

PhysicalConnectorInfo RealTimeSampleArrayMetricState::getPhysicalConnector() const {
	return ConvertFromCDM::convert(data->getPhysicalConnector().get());
}

bool RealTimeSampleArrayMetricState::hasPhysicalConnector() const {
	return data->getPhysicalConnector().present();
}

RealTimeSampleArrayMetricState & RealTimeSampleArrayMetricState::setActivationState(const ComponentActivation & value) {
	data->setActivationState(ConvertToCDM::convert(value));
	return *this;
}

bool RealTimeSampleArrayMetricState::getActivationState(ComponentActivation & out) const {
	if (data->getActivationState().present()) {
		out = ConvertFromCDM::convert(data->getActivationState().get());
		return true;
	}
	return false;
}

ComponentActivation RealTimeSampleArrayMetricState::getActivationState() const {
	return ConvertFromCDM::convert(data->getActivationState().get());
}

bool RealTimeSampleArrayMetricState::hasActivationState() const {
	return data->getActivationState().present();
}

RealTimeSampleArrayMetricState & RealTimeSampleArrayMetricState::setActiveDeterminationPeriod(const xml_schema::Duration & value) {
	data->setActiveDeterminationPeriod(ConvertToCDM::convert(value));
	return *this;
}

bool RealTimeSampleArrayMetricState::getActiveDeterminationPeriod(xml_schema::Duration & out) const {
	if (data->getActiveDeterminationPeriod().present()) {
		out = ConvertFromCDM::convert(data->getActiveDeterminationPeriod().get());
		return true;
	}
	return false;
}

xml_schema::Duration RealTimeSampleArrayMetricState::getActiveDeterminationPeriod() const {
	return ConvertFromCDM::convert(data->getActiveDeterminationPeriod().get());
}

bool RealTimeSampleArrayMetricState::hasActiveDeterminationPeriod() const {
	return data->getActiveDeterminationPeriod().present();
}

RealTimeSampleArrayMetricState & RealTimeSampleArrayMetricState::setLifeTimePeriod(const xml_schema::Duration & value) {
	data->setLifeTimePeriod(ConvertToCDM::convert(value));
	return *this;
}

bool RealTimeSampleArrayMetricState::getLifeTimePeriod(xml_schema::Duration & out) const {
	if (data->getLifeTimePeriod().present()) {
		out = ConvertFromCDM::convert(data->getLifeTimePeriod().get());
		return true;
	}
	return false;
}

xml_schema::Duration RealTimeSampleArrayMetricState::getLifeTimePeriod() const {
	return ConvertFromCDM::convert(data->getLifeTimePeriod().get());
}

bool RealTimeSampleArrayMetricState::hasLifeTimePeriod() const {
	return data->getLifeTimePeriod().present();
}

RealTimeSampleArrayMetricState & RealTimeSampleArrayMetricState::addBodySite(const CodedValue & value) {
	data->getBodySite().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<CodedValue> RealTimeSampleArrayMetricState::getBodySiteList() const {
	std::vector<CodedValue> result;
	result.reserve(data->getBodySite().size());
	for (const auto & value: data->getBodySite()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void RealTimeSampleArrayMetricState::clearBodySiteList() {
	data->getBodySite().clear();
}

RealTimeSampleArrayMetricState & RealTimeSampleArrayMetricState::setMetricValue(const SampleArrayValue & value) {
	data->setMetricValue(ConvertToCDM::convert(value));
	return *this;
}

bool RealTimeSampleArrayMetricState::getMetricValue(SampleArrayValue & out) const {
	if (data->getMetricValue().present()) {
		out = ConvertFromCDM::convert(data->getMetricValue().get());
		return true;
	}
	return false;
}

SampleArrayValue RealTimeSampleArrayMetricState::getMetricValue() const {
	return ConvertFromCDM::convert(data->getMetricValue().get());
}

bool RealTimeSampleArrayMetricState::hasMetricValue() const {
	return data->getMetricValue().present();
}

RealTimeSampleArrayMetricState & RealTimeSampleArrayMetricState::addPhysiologicalRange(const Range & value) {
	data->getPhysiologicalRange().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<Range> RealTimeSampleArrayMetricState::getPhysiologicalRangeList() const {
	std::vector<Range> result;
	result.reserve(data->getPhysiologicalRange().size());
	for (const auto & value: data->getPhysiologicalRange()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void RealTimeSampleArrayMetricState::clearPhysiologicalRangeList() {
	data->getPhysiologicalRange().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

