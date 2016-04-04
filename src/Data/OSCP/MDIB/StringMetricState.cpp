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
 *  Author: besting, roehser
 */
 
/**
 * THIS FILE IS GENERATED AUTOMATICALLY! DO NOT MODIFY!
 *
 * YOUR CHANGES WILL BE OVERWRITTEN!
 * 
 * USE THE DEFINITION FILES IN THE FOLDER "codegenerator" INSTEAD!
 */

#include "OSCLib/Data/OSCP/MDIB/StringMetricState.h"
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

StringMetricState::StringMetricState() : data(Defaults::StringMetricState()) {
}

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
	*data = *object.data;
}

StringMetricState & StringMetricState:: operator=(const StringMetricState & object) {
	copyFrom(object);
	return *this;
}


StringMetricState & StringMetricState::setHandle(const std::string & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}

bool StringMetricState::getHandle(std::string & out) const {
	if (data->Handle().present()) {
		out = ConvertFromCDM::convert(data->Handle().get());
		return true;
	}
	return false;
}

std::string StringMetricState::getHandle() const {
	return ConvertFromCDM::convert(data->Handle().get());
}
	
bool StringMetricState::hasHandle() const {
	return data->Handle().present();
}
	
StringMetricState & StringMetricState::setDescriptorHandle(const std::string & value) {
	data->DescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


std::string StringMetricState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->DescriptorHandle());
}
	
StringMetricState & StringMetricState::setStateVersion(const VersionCounter & value) {
	data->StateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool StringMetricState::getStateVersion(VersionCounter & out) const {
	if (data->StateVersion().present()) {
		out = ConvertFromCDM::convert(data->StateVersion().get());
		return true;
	}
	return false;
}

VersionCounter StringMetricState::getStateVersion() const {
	return ConvertFromCDM::convert(data->StateVersion().get());
}
	
bool StringMetricState::hasStateVersion() const {
	return data->StateVersion().present();
}
	
StringMetricState & StringMetricState::setComponentActivationState(const ComponentActivation & value) {
	data->ComponentActivationState(ConvertToCDM::convert(value));
	return *this;
}

bool StringMetricState::getComponentActivationState(ComponentActivation & out) const {
	if (data->ComponentActivationState().present()) {
		out = ConvertFromCDM::convert(data->ComponentActivationState().get());
		return true;
	}
	return false;
}

ComponentActivation StringMetricState::getComponentActivationState() const {
	return ConvertFromCDM::convert(data->ComponentActivationState().get());
}
	
bool StringMetricState::hasComponentActivationState() const {
	return data->ComponentActivationState().present();
}
	
StringMetricState & StringMetricState::setCalibrationInfo(const CalibrationInfo & value) {
	data->CalibrationInfo(ConvertToCDM::convert(value));
	return *this;
}

bool StringMetricState::getCalibrationInfo(CalibrationInfo & out) const {
	if (data->CalibrationInfo().present()) {
		out = ConvertFromCDM::convert(data->CalibrationInfo().get());
		return true;
	}
	return false;
}

CalibrationInfo StringMetricState::getCalibrationInfo() const {
	return ConvertFromCDM::convert(data->CalibrationInfo().get());
}
	
bool StringMetricState::hasCalibrationInfo() const {
	return data->CalibrationInfo().present();
}
	
StringMetricState & StringMetricState::setOperatingHours(const int & value) {
	data->OperatingHours(ConvertToCDM::convert(value));
	return *this;
}

bool StringMetricState::getOperatingHours(int & out) const {
	if (data->OperatingHours().present()) {
		out = ConvertFromCDM::convert(data->OperatingHours().get());
		return true;
	}
	return false;
}

int StringMetricState::getOperatingHours() const {
	return ConvertFromCDM::convert(data->OperatingHours().get());
}
	
bool StringMetricState::hasOperatingHours() const {
	return data->OperatingHours().present();
}
	
StringMetricState & StringMetricState::setOperatingCycles(const int & value) {
	data->OperatingCycles(ConvertToCDM::convert(value));
	return *this;
}

bool StringMetricState::getOperatingCycles(int & out) const {
	if (data->OperatingCycles().present()) {
		out = ConvertFromCDM::convert(data->OperatingCycles().get());
		return true;
	}
	return false;
}

int StringMetricState::getOperatingCycles() const {
	return ConvertFromCDM::convert(data->OperatingCycles().get());
}
	
bool StringMetricState::hasOperatingCycles() const {
	return data->OperatingCycles().present();
}
	
StringMetricState & StringMetricState::setObservedValue(const StringMetricValue & value) {
	data->ObservedValue(ConvertToCDM::convert(value));
	return *this;
}

bool StringMetricState::getObservedValue(StringMetricValue & out) const {
	if (data->ObservedValue().present()) {
		out = ConvertFromCDM::convert(data->ObservedValue().get());
		return true;
	}
	return false;
}

StringMetricValue StringMetricState::getObservedValue() const {
	return ConvertFromCDM::convert(data->ObservedValue().get());
}
	
bool StringMetricState::hasObservedValue() const {
	return data->ObservedValue().present();
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

