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

#include "OSCLib/Data/OSCP/MDIB/NumericMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/NumericMetricValue.h"
#include "OSCLib/Data/OSCP/MDIB/Range.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/PhysicalConnectorInfo.h"

namespace OSCLib {
namespace Data {
namespace OSCP {


NumericMetricState::NumericMetricState(
		HandleRef descriptorhandle
) : data(Defaults::NumericMetricStateInit(
		descriptorhandle
)) {}


// TODO: debugging -> remove
//NumericMetricState::NumericMetricState() : data(CDM::NumericMetricState("empty test string")){}

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
	data->StateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool NumericMetricState::getStateVersion(VersionCounter & out) const {
	if (data->StateVersion().present()) {
		out = ConvertFromCDM::convert(data->StateVersion().get());
		return true;
	}
	return false;
}

VersionCounter NumericMetricState::getStateVersion() const {
	return ConvertFromCDM::convert(data->StateVersion().get());
}
	
bool NumericMetricState::hasStateVersion() const {
	return data->StateVersion().present();
}
	
NumericMetricState & NumericMetricState::setDescriptorHandle(const HandleRef & value) {
	data->DescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


HandleRef NumericMetricState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->DescriptorHandle());
}
	
NumericMetricState & NumericMetricState::setDescriptorVersion(const ReferencedVersion & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool NumericMetricState::getDescriptorVersion(ReferencedVersion & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion NumericMetricState::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}
	
bool NumericMetricState::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}
	
NumericMetricState & NumericMetricState::setPhysicalConnector(const PhysicalConnectorInfo & value) {
	data->PhysicalConnector(ConvertToCDM::convert(value));
	return *this;
}

bool NumericMetricState::getPhysicalConnector(PhysicalConnectorInfo & out) const {
	if (data->PhysicalConnector().present()) {
		out = ConvertFromCDM::convert(data->PhysicalConnector().get());
		return true;
	}
	return false;
}

PhysicalConnectorInfo NumericMetricState::getPhysicalConnector() const {
	return ConvertFromCDM::convert(data->PhysicalConnector().get());
}
	
bool NumericMetricState::hasPhysicalConnector() const {
	return data->PhysicalConnector().present();
}
	
NumericMetricState & NumericMetricState::setActivationState(const ComponentActivation & value) {
	data->ActivationState(ConvertToCDM::convert(value));
	return *this;
}

bool NumericMetricState::getActivationState(ComponentActivation & out) const {
	if (data->ActivationState().present()) {
		out = ConvertFromCDM::convert(data->ActivationState().get());
		return true;
	}
	return false;
}

ComponentActivation NumericMetricState::getActivationState() const {
	return ConvertFromCDM::convert(data->ActivationState().get());
}
	
bool NumericMetricState::hasActivationState() const {
	return data->ActivationState().present();
}
	
NumericMetricState & NumericMetricState::setActiveDeterminationPeriod(const xml_schema::Duration & value) {
	data->ActiveDeterminationPeriod(ConvertToCDM::convert(value));
	return *this;
}

bool NumericMetricState::getActiveDeterminationPeriod(xml_schema::Duration & out) const {
	if (data->ActiveDeterminationPeriod().present()) {
		out = ConvertFromCDM::convert(data->ActiveDeterminationPeriod().get());
		return true;
	}
	return false;
}

xml_schema::Duration NumericMetricState::getActiveDeterminationPeriod() const {
	return ConvertFromCDM::convert(data->ActiveDeterminationPeriod().get());
}
	
bool NumericMetricState::hasActiveDeterminationPeriod() const {
	return data->ActiveDeterminationPeriod().present();
}
	
NumericMetricState & NumericMetricState::setLifeTimePeriod(const xml_schema::Duration & value) {
	data->LifeTimePeriod(ConvertToCDM::convert(value));
	return *this;
}

bool NumericMetricState::getLifeTimePeriod(xml_schema::Duration & out) const {
	if (data->LifeTimePeriod().present()) {
		out = ConvertFromCDM::convert(data->LifeTimePeriod().get());
		return true;
	}
	return false;
}

xml_schema::Duration NumericMetricState::getLifeTimePeriod() const {
	return ConvertFromCDM::convert(data->LifeTimePeriod().get());
}
	
bool NumericMetricState::hasLifeTimePeriod() const {
	return data->LifeTimePeriod().present();
}
	
NumericMetricState & NumericMetricState::addBodySite(const CodedValue & value) {
	data->BodySite().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<CodedValue> NumericMetricState::getBodySiteList() const {
	std::vector<CodedValue> result;
	result.reserve(data->BodySite().size());
	for (const auto & value: data->BodySite()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void NumericMetricState::clearBodySiteList() {
	data->BodySite().clear();
}

NumericMetricState & NumericMetricState::setMetricValue(const NumericMetricValue & value) {
	data->MetricValue(ConvertToCDM::convert(value));
	return *this;
}

bool NumericMetricState::getMetricValue(NumericMetricValue & out) const {
	if (data->MetricValue().present()) {
		out = ConvertFromCDM::convert(data->MetricValue().get());
		return true;
	}
	return false;
}

NumericMetricValue NumericMetricState::getMetricValue() const {
	return ConvertFromCDM::convert(data->MetricValue().get());
}
	
bool NumericMetricState::hasMetricValue() const {
	return data->MetricValue().present();
}
	
NumericMetricState & NumericMetricState::setActiveAveragingPeriod(const xml_schema::Duration & value) {
	data->ActiveAveragingPeriod(ConvertToCDM::convert(value));
	return *this;
}

bool NumericMetricState::getActiveAveragingPeriod(xml_schema::Duration & out) const {
	if (data->ActiveAveragingPeriod().present()) {
		out = ConvertFromCDM::convert(data->ActiveAveragingPeriod().get());
		return true;
	}
	return false;
}

xml_schema::Duration NumericMetricState::getActiveAveragingPeriod() const {
	return ConvertFromCDM::convert(data->ActiveAveragingPeriod().get());
}
	
bool NumericMetricState::hasActiveAveragingPeriod() const {
	return data->ActiveAveragingPeriod().present();
}
	
NumericMetricState & NumericMetricState::addPhysiologicalRange(const Range & value) {
	data->PhysiologicalRange().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<Range> NumericMetricState::getPhysiologicalRangeList() const {
	std::vector<Range> result;
	result.reserve(data->PhysiologicalRange().size());
	for (const auto & value: data->PhysiologicalRange()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void NumericMetricState::clearPhysiologicalRangeList() {
	data->PhysiologicalRange().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

