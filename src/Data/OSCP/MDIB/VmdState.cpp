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
 *  VmdState.cpp
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

#include "OSCLib/Data/OSCP/MDIB/VmdState.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/CalibrationInfo.h"
#include "OSCLib/Data/OSCP/MDIB/CalibrationInfo.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

VmdState::VmdState() : data(Defaults::VmdState()) {
}

VmdState::operator CDM::VmdState() const {
	return *data;
}

VmdState::VmdState(const CDM::VmdState & object) : data(new CDM::VmdState(object)) {

}

VmdState::VmdState(const VmdState & object) : data(new CDM::VmdState(*object.data)) {

}

VmdState::~VmdState() {

}

void VmdState::copyFrom(const VmdState & object) {
	*data = *object.data;
}

VmdState & VmdState:: operator=(const VmdState & object) {
	copyFrom(object);
	return *this;
}


VmdState & VmdState::setStateVersion(const VersionCounter & value) {
	data->StateVersion(ConvertToCDM::convert(value));
	return *this;
}


VersionCounter VmdState::getStateVersion() const {
	return ConvertFromCDM::convert(data->StateVersion());
}
	
VmdState & VmdState::setDescriptorHandle(const HandleRef & value) {
	data->DescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


HandleRef VmdState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->DescriptorHandle());
}
	
VmdState & VmdState::setDescriptorVersion(const ReferencedVersion & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}


ReferencedVersion VmdState::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion());
}
	
VmdState & VmdState::setCalibrationInfo(const CalibrationInfo & value) {
	data->CalibrationInfo(ConvertToCDM::convert(value));
	return *this;
}

bool VmdState::getCalibrationInfo(CalibrationInfo & out) const {
	if (data->CalibrationInfo().present()) {
		out = ConvertFromCDM::convert(data->CalibrationInfo().get());
		return true;
	}
	return false;
}

CalibrationInfo VmdState::getCalibrationInfo() const {
	return ConvertFromCDM::convert(data->CalibrationInfo().get());
}
	
bool VmdState::hasCalibrationInfo() const {
	return data->CalibrationInfo().present();
}
	
VmdState & VmdState::setNextCalibration(const CalibrationInfo & value) {
	data->NextCalibration(ConvertToCDM::convert(value));
	return *this;
}

bool VmdState::getNextCalibration(CalibrationInfo & out) const {
	if (data->NextCalibration().present()) {
		out = ConvertFromCDM::convert(data->NextCalibration().get());
		return true;
	}
	return false;
}

CalibrationInfo VmdState::getNextCalibration() const {
	return ConvertFromCDM::convert(data->NextCalibration().get());
}
	
bool VmdState::hasNextCalibration() const {
	return data->NextCalibration().present();
}
	
VmdState & VmdState::setActivationState(const ComponentActivation & value) {
	data->ActivationState(ConvertToCDM::convert(value));
	return *this;
}


ComponentActivation VmdState::getActivationState() const {
	return ConvertFromCDM::convert(data->ActivationState());
}
	
VmdState & VmdState::setOperatingHours(const unsigned int & value) {
	data->OperatingHours(ConvertToCDM::convert(value));
	return *this;
}


unsigned int VmdState::getOperatingHours() const {
	return ConvertFromCDM::convert(data->OperatingHours());
}
	
VmdState & VmdState::setOperatingCycles(const int & value) {
	data->OperatingCycles(ConvertToCDM::convert(value));
	return *this;
}


int VmdState::getOperatingCycles() const {
	return ConvertFromCDM::convert(data->OperatingCycles());
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

