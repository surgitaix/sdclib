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
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/NumericMetricValue.h"
#include "OSCLib/Data/OSCP/MDIB/Range.h"
#include "OSCLib/Data/OSCP/MDIB/CalibrationInfo.h"
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
	
NumericMetricState & NumericMetricState::setComponentActivationState(const ComponentActivation & value) {
	data->ComponentActivationState(ConvertToCDM::convert(value));
	return *this;
}

bool NumericMetricState::getComponentActivationState(ComponentActivation & out) const {
	if (data->ComponentActivationState().present()) {
		out = ConvertFromCDM::convert(data->ComponentActivationState().get());
		return true;
	}
	return false;
}

ComponentActivation NumericMetricState::getComponentActivationState() const {
	return ConvertFromCDM::convert(data->ComponentActivationState().get());
}
	
bool NumericMetricState::hasComponentActivationState() const {
	return data->ComponentActivationState().present();
}
	
NumericMetricState & NumericMetricState::setCalibrationInfo(const CalibrationInfo & value) {
	data->CalibrationInfo(ConvertToCDM::convert(value));
	return *this;
}

bool NumericMetricState::getCalibrationInfo(CalibrationInfo & out) const {
	if (data->CalibrationInfo().present()) {
		out = ConvertFromCDM::convert(data->CalibrationInfo().get());
		return true;
	}
	return false;
}

CalibrationInfo NumericMetricState::getCalibrationInfo() const {
	return ConvertFromCDM::convert(data->CalibrationInfo().get());
}
	
bool NumericMetricState::hasCalibrationInfo() const {
	return data->CalibrationInfo().present();
}
	
NumericMetricState & NumericMetricState::setOperatingHours(const int & value) {
	data->OperatingHours(ConvertToCDM::convert(value));
	return *this;
}

bool NumericMetricState::getOperatingHours(int & out) const {
	if (data->OperatingHours().present()) {
		out = ConvertFromCDM::convert(data->OperatingHours().get());
		return true;
	}
	return false;
}

int NumericMetricState::getOperatingHours() const {
	return ConvertFromCDM::convert(data->OperatingHours().get());
}
	
bool NumericMetricState::hasOperatingHours() const {
	return data->OperatingHours().present();
}
	
NumericMetricState & NumericMetricState::setOperatingCycles(const int & value) {
	data->OperatingCycles(ConvertToCDM::convert(value));
	return *this;
}

bool NumericMetricState::getOperatingCycles(int & out) const {
	if (data->OperatingCycles().present()) {
		out = ConvertFromCDM::convert(data->OperatingCycles().get());
		return true;
	}
	return false;
}

int NumericMetricState::getOperatingCycles() const {
	return ConvertFromCDM::convert(data->OperatingCycles().get());
}
	
bool NumericMetricState::hasOperatingCycles() const {
	return data->OperatingCycles().present();
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

