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
 *  AbstractDeviceComponentState.cpp
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

#include "OSCLib/Data/OSCP/MDIB/AbstractDeviceComponentState.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/VersionCounter.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

AbstractDeviceComponentState::AbstractDeviceComponentState() : data(Defaults::AbstractDeviceComponentState()) {
}

AbstractDeviceComponentState::operator CDM::AbstractDeviceComponentState() const {
	return *data;
}

AbstractDeviceComponentState::AbstractDeviceComponentState(const CDM::AbstractDeviceComponentState & object) : data(new CDM::AbstractDeviceComponentState(object)) {

}

AbstractDeviceComponentState::AbstractDeviceComponentState(const AbstractDeviceComponentState & object) : data(new CDM::AbstractDeviceComponentState(*object.data)) {

}

AbstractDeviceComponentState::~AbstractDeviceComponentState() {

}

void AbstractDeviceComponentState::copyFrom(const AbstractDeviceComponentState & object) {
	*data = *object.data;
}

AbstractDeviceComponentState & AbstractDeviceComponentState:: operator=(const AbstractDeviceComponentState & object) {
	copyFrom(object);
	return *this;
}


AbstractDeviceComponentState & AbstractDeviceComponentState::setHandle(const std::string & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}

bool AbstractDeviceComponentState::getHandle(std::string & out) const {
	if (data->Handle().present()) {
		out = ConvertFromCDM::convert(data->Handle().get());
		return true;
	}
	return false;
}

std::string AbstractDeviceComponentState::getHandle() const {
	return ConvertFromCDM::convert(data->Handle().get());
}
	
bool AbstractDeviceComponentState::hasHandle() const {
	return data->Handle().present();
}
	
AbstractDeviceComponentState & AbstractDeviceComponentState::setDescriptorHandle(const std::string & value) {
	data->DescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


std::string AbstractDeviceComponentState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->DescriptorHandle());
}
	
AbstractDeviceComponentState & AbstractDeviceComponentState::setStateVersion(const VersionCounter & value) {
	data->StateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool AbstractDeviceComponentState::getStateVersion(VersionCounter & out) const {
	if (data->StateVersion().present()) {
		out = ConvertFromCDM::convert(data->StateVersion().get());
		return true;
	}
	return false;
}

VersionCounter AbstractDeviceComponentState::getStateVersion() const {
	return ConvertFromCDM::convert(data->StateVersion().get());
}
	
bool AbstractDeviceComponentState::hasStateVersion() const {
	return data->StateVersion().present();
}
	
AbstractDeviceComponentState & AbstractDeviceComponentState::setActivationState(const int & value) {
	data->ActivationState(ConvertToCDM::convert(value));
	return *this;
}

bool AbstractDeviceComponentState::getActivationState(int & out) const {
	if (data->ActivationState().present()) {
		out = ConvertFromCDM::convert(data->ActivationState().get());
		return true;
	}
	return false;
}

int AbstractDeviceComponentState::getActivationState() const {
	return ConvertFromCDM::convert(data->ActivationState().get());
}
	
bool AbstractDeviceComponentState::hasActivationState() const {
	return data->ActivationState().present();
}
	
AbstractDeviceComponentState & AbstractDeviceComponentState::setOperatingHours(const unsigned int & value) {
	data->OperatingHours(ConvertToCDM::convert(value));
	return *this;
}

bool AbstractDeviceComponentState::getOperatingHours(unsigned int & out) const {
	if (data->OperatingHours().present()) {
		out = ConvertFromCDM::convert(data->OperatingHours().get());
		return true;
	}
	return false;
}

unsigned int AbstractDeviceComponentState::getOperatingHours() const {
	return ConvertFromCDM::convert(data->OperatingHours().get());
}
	
bool AbstractDeviceComponentState::hasOperatingHours() const {
	return data->OperatingHours().present();
}
	
AbstractDeviceComponentState & AbstractDeviceComponentState::setOperatingCycles(const int & value) {
	data->OperatingCycles(ConvertToCDM::convert(value));
	return *this;
}

bool AbstractDeviceComponentState::getOperatingCycles(int & out) const {
	if (data->OperatingCycles().present()) {
		out = ConvertFromCDM::convert(data->OperatingCycles().get());
		return true;
	}
	return false;
}

int AbstractDeviceComponentState::getOperatingCycles() const {
	return ConvertFromCDM::convert(data->OperatingCycles().get());
}
	
bool AbstractDeviceComponentState::hasOperatingCycles() const {
	return data->OperatingCycles().present();
}
	
AbstractDeviceComponentState & AbstractDeviceComponentState::setCalibrationInfo(const CalibrationInfo & value) {
	data->CalibrationInfo(ConvertToCDM::convert(value));
	return *this;
}

bool AbstractDeviceComponentState::getCalibrationInfo(CalibrationInfo & out) const {
	if (data->CalibrationInfo().present()) {
		out = ConvertFromCDM::convert(data->CalibrationInfo().get());
		return true;
	}
	return false;
}

CalibrationInfo AbstractDeviceComponentState::getCalibrationInfo() const {
	return ConvertFromCDM::convert(data->CalibrationInfo().get());
}
	
bool AbstractDeviceComponentState::hasCalibrationInfo() const {
	return data->CalibrationInfo().present();
}
	
AbstractDeviceComponentState & AbstractDeviceComponentState::setNextCalibration(const CalibrationInfo & value) {
	data->NextCalibration(ConvertToCDM::convert(value));
	return *this;
}

bool AbstractDeviceComponentState::getNextCalibration(CalibrationInfo & out) const {
	if (data->NextCalibration().present()) {
		out = ConvertFromCDM::convert(data->NextCalibration().get());
		return true;
	}
	return false;
}

CalibrationInfo AbstractDeviceComponentState::getNextCalibration() const {
	return ConvertFromCDM::convert(data->NextCalibration().get());
}
	
bool AbstractDeviceComponentState::hasNextCalibration() const {
	return data->NextCalibration().present();
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

