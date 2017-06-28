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
 *  Author: besting, roehser
 */
 
/**
 * THIS FILE IS GENERATED AUTOMATICALLY! DO NOT MODIFY!
 *
 * YOUR CHANGES WILL BE OVERWRITTEN!
 * 
 * USE THE DEFINITION FILES IN THE FOLDER "codegenerator" INSTEAD!
 */

#include "OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/SampleArrayValue.h"
#include "OSCLib/Data/OSCP/MDIB/Range.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

RealTimeSampleArrayMetricState::RealTimeSampleArrayMetricState() : data(Defaults::RealTimeSampleArrayMetricState()) {
}

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
	*data = *object.data;
}

RealTimeSampleArrayMetricState & RealTimeSampleArrayMetricState:: operator=(const RealTimeSampleArrayMetricState & object) {
	copyFrom(object);
	return *this;
}


RealTimeSampleArrayMetricState & RealTimeSampleArrayMetricState::setStateVersion(const VersionCounter & value) {
	data->StateVersion(ConvertToCDM::convert(value));
	return *this;
}


VersionCounter RealTimeSampleArrayMetricState::getStateVersion() const {
	return ConvertFromCDM::convert(data->StateVersion());
}
	
RealTimeSampleArrayMetricState & RealTimeSampleArrayMetricState::setDescriptorHandle(const HandleRef & value) {
	data->DescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


HandleRef RealTimeSampleArrayMetricState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->DescriptorHandle());
}
	
RealTimeSampleArrayMetricState & RealTimeSampleArrayMetricState::setDescriptorVersion(const ReferencedVersion & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}


ReferencedVersion RealTimeSampleArrayMetricState::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion());
}
	
RealTimeSampleArrayMetricState & RealTimeSampleArrayMetricState::setActivationState(const ComponentActivation & value) {
	data->ActivationState(ConvertToCDM::convert(value));
	return *this;
}


ComponentActivation RealTimeSampleArrayMetricState::getActivationState() const {
	return ConvertFromCDM::convert(data->ActivationState());
}
	
RealTimeSampleArrayMetricState & RealTimeSampleArrayMetricState::setActiveDeterminationPeriod(const duration & value) {
	data->ActiveDeterminationPeriod(ConvertToCDM::convert(value));
	return *this;
}


duration RealTimeSampleArrayMetricState::getActiveDeterminationPeriod() const {
	return ConvertFromCDM::convert(data->ActiveDeterminationPeriod());
}
	
RealTimeSampleArrayMetricState & RealTimeSampleArrayMetricState::setLifeTimePeriod(const duration & value) {
	data->LifeTimePeriod(ConvertToCDM::convert(value));
	return *this;
}

bool RealTimeSampleArrayMetricState::getLifeTimePeriod(duration & out) const {
	if (data->LifeTimePeriod().present()) {
		out = ConvertFromCDM::convert(data->LifeTimePeriod().get());
		return true;
	}
	return false;
}

duration RealTimeSampleArrayMetricState::getLifeTimePeriod() const {
	return ConvertFromCDM::convert(data->LifeTimePeriod().get());
}
	
bool RealTimeSampleArrayMetricState::hasLifeTimePeriod() const {
	return data->LifeTimePeriod().present();
}
	
RealTimeSampleArrayMetricState & RealTimeSampleArrayMetricState::addBodySite(const CodedValue & value) {
	data->BodySite().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<CodedValue> RealTimeSampleArrayMetricState::getBodySites() const {
	std::vector<CodedValue> result;
	result.reserve(data->BodySite().size());
	for (const auto & value: data->BodySite()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void RealTimeSampleArrayMetricState::clearBodySites() {
	data->BodySite().clear();
}

RealTimeSampleArrayMetricState & RealTimeSampleArrayMetricState::setMetricValue(const SampleArrayValue & value) {
	data->MetricValue(ConvertToCDM::convert(value));
	return *this;
}

bool RealTimeSampleArrayMetricState::getMetricValue(SampleArrayValue & out) const {
	if (data->MetricValue().present()) {
		out = ConvertFromCDM::convert(data->MetricValue().get());
		return true;
	}
	return false;
}

SampleArrayValue RealTimeSampleArrayMetricState::getMetricValue() const {
	return ConvertFromCDM::convert(data->MetricValue().get());
}
	
bool RealTimeSampleArrayMetricState::hasMetricValue() const {
	return data->MetricValue().present();
}
	
RealTimeSampleArrayMetricState & RealTimeSampleArrayMetricState::addPhysiologicalRange(const Range & value) {
	data->PhysiologicalRange().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<Range> RealTimeSampleArrayMetricState::getPhysiologicalRanges() const {
	std::vector<Range> result;
	result.reserve(data->PhysiologicalRange().size());
	for (const auto & value: data->PhysiologicalRange()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void RealTimeSampleArrayMetricState::clearPhysiologicalRanges() {
	data->PhysiologicalRange().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

