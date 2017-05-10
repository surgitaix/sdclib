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
 *  Author: besting, roehser
 */
 
/**
 * THIS FILE IS GENERATED AUTOMATICALLY! DO NOT MODIFY!
 *
 * YOUR CHANGES WILL BE OVERWRITTEN!
 * 
 * USE THE DEFINITION FILES IN THE FOLDER "codegenerator" INSTEAD!
 */

#include "OSCLib/Data/OSCP/MDIB/NumericMetricState.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/NumericMetricValue.h"
#include "OSCLib/Data/OSCP/MDIB/Range.h"
#include "OSCLib/Data/OSCP/MDIB/Duration.h"
#include "OSCLib/Data/OSCP/MDIB/VersionCounter.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

NumericMetricState::NumericMetricState() : data(Defaults::NumericMetricState()) {
}

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
	*data = *object.data;
}

NumericMetricState & NumericMetricState:: operator=(const NumericMetricState & object) {
	copyFrom(object);
	return *this;
}


NumericMetricState & NumericMetricState::setHandle(const std::string & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}

bool NumericMetricState::getHandle(std::string & out) const {
	if (data->Handle().present()) {
		out = ConvertFromCDM::convert(data->Handle().get());
		return true;
	}
	return false;
}

std::string NumericMetricState::getHandle() const {
	return ConvertFromCDM::convert(data->Handle().get());
}
	
bool NumericMetricState::hasHandle() const {
	return data->Handle().present();
}
	
NumericMetricState & NumericMetricState::setDescriptorHandle(const std::string & value) {
	data->DescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


std::string NumericMetricState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->DescriptorHandle());
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
	
NumericMetricState & NumericMetricState::setActivationState(const ComponentActivation & value) {
	data->ActivationState(ConvertToCDM::convert(value));
	return *this;
}


ComponentActivation NumericMetricState::getActivationState() const {
	return ConvertFromCDM::convert(data->ActivationState());
}
	
NumericMetricState & NumericMetricState::setLifeTimePeriod(const Duration & value) {
	data->LifeTimePeriod(ConvertToCDM::convert(value));
	return *this;
}

bool NumericMetricState::getLifeTimePeriod(Duration & out) const {
	if (data->LifeTimePeriod().present()) {
		out = ConvertFromCDM::convert(data->LifeTimePeriod().get());
		return true;
	}
	return false;
}

Duration NumericMetricState::getLifeTimePeriod() const {
	return ConvertFromCDM::convert(data->LifeTimePeriod().get());
}
	
bool NumericMetricState::hasLifeTimePeriod() const {
	return data->LifeTimePeriod().present();
}
	
NumericMetricState & NumericMetricState::setActiveDeterminationPeriod(const Duration & value) {
	data->ActiveDeterminationPeriod(ConvertToCDM::convert(value));
	return *this;
}

bool NumericMetricState::getActiveDeterminationPeriod(Duration & out) const {
	if (data->ActiveDeterminationPeriod().present()) {
		out = ConvertFromCDM::convert(data->ActiveDeterminationPeriod().get());
		return true;
	}
	return false;
}

Duration NumericMetricState::getActiveDeterminationPeriod() const {
	return ConvertFromCDM::convert(data->ActiveDeterminationPeriod().get());
}
	
bool NumericMetricState::hasActiveDeterminationPeriod() const {
	return data->ActiveDeterminationPeriod().present();
}
	
NumericMetricState & NumericMetricState::setObservedValue(const NumericMetricValue & value) {
	data->ObservedValue(ConvertToCDM::convert(value));
	return *this;
}

bool NumericMetricState::getObservedValue(NumericMetricValue & out) const {
	if (data->ObservedValue().present()) {
		out = ConvertFromCDM::convert(data->ObservedValue().get());
		return true;
	}
	return false;
}

NumericMetricValue NumericMetricState::getObservedValue() const {
	return ConvertFromCDM::convert(data->ObservedValue().get());
}
	
bool NumericMetricState::hasObservedValue() const {
	return data->ObservedValue().present();
}
	
NumericMetricState & NumericMetricState::addPhysiologicalRange(const Range & value) {
	data->PhysiologicalRange().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<Range> NumericMetricState::getPhysiologicalRanges() const {
	std::vector<Range> result;
	result.reserve(data->PhysiologicalRange().size());
	for (const auto & value: data->PhysiologicalRange()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void NumericMetricState::clearPhysiologicalRanges() {
	data->PhysiologicalRange().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

