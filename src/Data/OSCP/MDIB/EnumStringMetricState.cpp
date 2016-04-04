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
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/StringMetricValue.h"
#include "OSCLib/Data/OSCP/MDIB/CalibrationInfo.h"
#include "OSCLib/Data/OSCP/MDIB/VersionCounter.h"

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


EnumStringMetricState & EnumStringMetricState::setHandle(const std::string & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}

bool EnumStringMetricState::getHandle(std::string & out) const {
	if (data->Handle().present()) {
		out = ConvertFromCDM::convert(data->Handle().get());
		return true;
	}
	return false;
}

std::string EnumStringMetricState::getHandle() const {
	return ConvertFromCDM::convert(data->Handle().get());
}
	
bool EnumStringMetricState::hasHandle() const {
	return data->Handle().present();
}
	
EnumStringMetricState & EnumStringMetricState::setDescriptorHandle(const std::string & value) {
	data->DescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


std::string EnumStringMetricState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->DescriptorHandle());
}
	
EnumStringMetricState & EnumStringMetricState::setStateVersion(const VersionCounter & value) {
	data->StateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool EnumStringMetricState::getStateVersion(VersionCounter & out) const {
	if (data->StateVersion().present()) {
		out = ConvertFromCDM::convert(data->StateVersion().get());
		return true;
	}
	return false;
}

VersionCounter EnumStringMetricState::getStateVersion() const {
	return ConvertFromCDM::convert(data->StateVersion().get());
}
	
bool EnumStringMetricState::hasStateVersion() const {
	return data->StateVersion().present();
}
	
EnumStringMetricState & EnumStringMetricState::setComponentActivationState(const ComponentActivation & value) {
	data->ComponentActivationState(ConvertToCDM::convert(value));
	return *this;
}

bool EnumStringMetricState::getComponentActivationState(ComponentActivation & out) const {
	if (data->ComponentActivationState().present()) {
		out = ConvertFromCDM::convert(data->ComponentActivationState().get());
		return true;
	}
	return false;
}

ComponentActivation EnumStringMetricState::getComponentActivationState() const {
	return ConvertFromCDM::convert(data->ComponentActivationState().get());
}
	
bool EnumStringMetricState::hasComponentActivationState() const {
	return data->ComponentActivationState().present();
}
	
EnumStringMetricState & EnumStringMetricState::setCalibrationInfo(const CalibrationInfo & value) {
	data->CalibrationInfo(ConvertToCDM::convert(value));
	return *this;
}

bool EnumStringMetricState::getCalibrationInfo(CalibrationInfo & out) const {
	if (data->CalibrationInfo().present()) {
		out = ConvertFromCDM::convert(data->CalibrationInfo().get());
		return true;
	}
	return false;
}

CalibrationInfo EnumStringMetricState::getCalibrationInfo() const {
	return ConvertFromCDM::convert(data->CalibrationInfo().get());
}
	
bool EnumStringMetricState::hasCalibrationInfo() const {
	return data->CalibrationInfo().present();
}
	
EnumStringMetricState & EnumStringMetricState::setOperatingHours(const int & value) {
	data->OperatingHours(ConvertToCDM::convert(value));
	return *this;
}

bool EnumStringMetricState::getOperatingHours(int & out) const {
	if (data->OperatingHours().present()) {
		out = ConvertFromCDM::convert(data->OperatingHours().get());
		return true;
	}
	return false;
}

int EnumStringMetricState::getOperatingHours() const {
	return ConvertFromCDM::convert(data->OperatingHours().get());
}
	
bool EnumStringMetricState::hasOperatingHours() const {
	return data->OperatingHours().present();
}
	
EnumStringMetricState & EnumStringMetricState::setOperatingCycles(const int & value) {
	data->OperatingCycles(ConvertToCDM::convert(value));
	return *this;
}

bool EnumStringMetricState::getOperatingCycles(int & out) const {
	if (data->OperatingCycles().present()) {
		out = ConvertFromCDM::convert(data->OperatingCycles().get());
		return true;
	}
	return false;
}

int EnumStringMetricState::getOperatingCycles() const {
	return ConvertFromCDM::convert(data->OperatingCycles().get());
}
	
bool EnumStringMetricState::hasOperatingCycles() const {
	return data->OperatingCycles().present();
}
	
EnumStringMetricState & EnumStringMetricState::setObservedValue(const StringMetricValue & value) {
	data->ObservedValue(ConvertToCDM::convert(value));
	return *this;
}

bool EnumStringMetricState::getObservedValue(StringMetricValue & out) const {
	if (data->ObservedValue().present()) {
		out = ConvertFromCDM::convert(data->ObservedValue().get());
		return true;
	}
	return false;
}

StringMetricValue EnumStringMetricState::getObservedValue() const {
	return ConvertFromCDM::convert(data->ObservedValue().get());
}
	
bool EnumStringMetricState::hasObservedValue() const {
	return data->ObservedValue().present();
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

