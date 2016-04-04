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
 *  ComponentState.cpp
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

#include "OSCLib/Data/OSCP/MDIB/ComponentState.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/CalibrationInfo.h"
#include "OSCLib/Data/OSCP/MDIB/VersionCounter.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

ComponentState::ComponentState() : data(Defaults::ComponentState()) {
}

ComponentState::operator CDM::ComponentState() const {
	return *data;
}

ComponentState::ComponentState(const CDM::ComponentState & object) : data(new CDM::ComponentState(object)) {

}

ComponentState::ComponentState(const ComponentState & object) : data(new CDM::ComponentState(*object.data)) {

}

ComponentState::~ComponentState() {

}

void ComponentState::copyFrom(const ComponentState & object) {
	*data = *object.data;
}

ComponentState & ComponentState:: operator=(const ComponentState & object) {
	copyFrom(object);
	return *this;
}


ComponentState & ComponentState::setHandle(const std::string & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}

bool ComponentState::getHandle(std::string & out) const {
	if (data->Handle().present()) {
		out = ConvertFromCDM::convert(data->Handle().get());
		return true;
	}
	return false;
}

std::string ComponentState::getHandle() const {
	return ConvertFromCDM::convert(data->Handle().get());
}
	
bool ComponentState::hasHandle() const {
	return data->Handle().present();
}
	
ComponentState & ComponentState::setDescriptorHandle(const std::string & value) {
	data->DescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


std::string ComponentState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->DescriptorHandle());
}
	
ComponentState & ComponentState::setStateVersion(const VersionCounter & value) {
	data->StateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool ComponentState::getStateVersion(VersionCounter & out) const {
	if (data->StateVersion().present()) {
		out = ConvertFromCDM::convert(data->StateVersion().get());
		return true;
	}
	return false;
}

VersionCounter ComponentState::getStateVersion() const {
	return ConvertFromCDM::convert(data->StateVersion().get());
}
	
bool ComponentState::hasStateVersion() const {
	return data->StateVersion().present();
}
	
ComponentState & ComponentState::setComponentActivationState(const ComponentActivation & value) {
	data->ComponentActivationState(ConvertToCDM::convert(value));
	return *this;
}

bool ComponentState::getComponentActivationState(ComponentActivation & out) const {
	if (data->ComponentActivationState().present()) {
		out = ConvertFromCDM::convert(data->ComponentActivationState().get());
		return true;
	}
	return false;
}

ComponentActivation ComponentState::getComponentActivationState() const {
	return ConvertFromCDM::convert(data->ComponentActivationState().get());
}
	
bool ComponentState::hasComponentActivationState() const {
	return data->ComponentActivationState().present();
}
	
ComponentState & ComponentState::setCalibrationInfo(const CalibrationInfo & value) {
	data->CalibrationInfo(ConvertToCDM::convert(value));
	return *this;
}

bool ComponentState::getCalibrationInfo(CalibrationInfo & out) const {
	if (data->CalibrationInfo().present()) {
		out = ConvertFromCDM::convert(data->CalibrationInfo().get());
		return true;
	}
	return false;
}

CalibrationInfo ComponentState::getCalibrationInfo() const {
	return ConvertFromCDM::convert(data->CalibrationInfo().get());
}
	
bool ComponentState::hasCalibrationInfo() const {
	return data->CalibrationInfo().present();
}
	
ComponentState & ComponentState::setOperatingHours(const int & value) {
	data->OperatingHours(ConvertToCDM::convert(value));
	return *this;
}

bool ComponentState::getOperatingHours(int & out) const {
	if (data->OperatingHours().present()) {
		out = ConvertFromCDM::convert(data->OperatingHours().get());
		return true;
	}
	return false;
}

int ComponentState::getOperatingHours() const {
	return ConvertFromCDM::convert(data->OperatingHours().get());
}
	
bool ComponentState::hasOperatingHours() const {
	return data->OperatingHours().present();
}
	
ComponentState & ComponentState::setOperatingCycles(const int & value) {
	data->OperatingCycles(ConvertToCDM::convert(value));
	return *this;
}

bool ComponentState::getOperatingCycles(int & out) const {
	if (data->OperatingCycles().present()) {
		out = ConvertFromCDM::convert(data->OperatingCycles().get());
		return true;
	}
	return false;
}

int ComponentState::getOperatingCycles() const {
	return ConvertFromCDM::convert(data->OperatingCycles().get());
}
	
bool ComponentState::hasOperatingCycles() const {
	return data->OperatingCycles().present();
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

