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
 *  SystemContextState.cpp
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

#include "OSCLib/Data/SDC/MDIB/SystemContextState.h"
#include "OSCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/SDC/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/SDC/MDIB/CalibrationInfo.h"
#include "OSCLib/Data/SDC/MDIB/PhysicalConnectorInfo.h"

namespace SDCLib {
namespace Data {
namespace SDC {


SystemContextState::SystemContextState(
		HandleRef descriptorhandle
) : data(Defaults::SystemContextStateInit(
		descriptorhandle
)) {}

SystemContextState::operator CDM::SystemContextState() const {
	return *data;
}

SystemContextState::SystemContextState(const CDM::SystemContextState & object) : data(new CDM::SystemContextState(object)) {

}

SystemContextState::SystemContextState(const SystemContextState & object) : data(new CDM::SystemContextState(*object.data)) {

}

SystemContextState::~SystemContextState() {

}

void SystemContextState::copyFrom(const SystemContextState & object) {
	data = std::shared_ptr<CDM::SystemContextState>( new CDM::SystemContextState(*object.data));
}

SystemContextState & SystemContextState:: operator=(const SystemContextState & object) {
	copyFrom(object);
	return *this;
}


SystemContextState & SystemContextState::setStateVersion(const VersionCounter & value) {
	data->StateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool SystemContextState::getStateVersion(VersionCounter & out) const {
	if (data->StateVersion().present()) {
		out = ConvertFromCDM::convert(data->StateVersion().get());
		return true;
	}
	return false;
}

VersionCounter SystemContextState::getStateVersion() const {
	return ConvertFromCDM::convert(data->StateVersion().get());
}

bool SystemContextState::hasStateVersion() const {
	return data->StateVersion().present();
}

SystemContextState & SystemContextState::setDescriptorHandle(const HandleRef & value) {
	data->DescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


HandleRef SystemContextState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->DescriptorHandle());
}

SystemContextState & SystemContextState::setDescriptorVersion(const ReferencedVersion & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool SystemContextState::getDescriptorVersion(ReferencedVersion & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion SystemContextState::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}

bool SystemContextState::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}

SystemContextState & SystemContextState::setCalibrationInfo(const CalibrationInfo & value) {
	data->CalibrationInfo(ConvertToCDM::convert(value));
	return *this;
}

bool SystemContextState::getCalibrationInfo(CalibrationInfo & out) const {
	if (data->CalibrationInfo().present()) {
		out = ConvertFromCDM::convert(data->CalibrationInfo().get());
		return true;
	}
	return false;
}

CalibrationInfo SystemContextState::getCalibrationInfo() const {
	return ConvertFromCDM::convert(data->CalibrationInfo().get());
}

bool SystemContextState::hasCalibrationInfo() const {
	return data->CalibrationInfo().present();
}

SystemContextState & SystemContextState::setNextCalibration(const CalibrationInfo & value) {
	data->NextCalibration(ConvertToCDM::convert(value));
	return *this;
}

bool SystemContextState::getNextCalibration(CalibrationInfo & out) const {
	if (data->NextCalibration().present()) {
		out = ConvertFromCDM::convert(data->NextCalibration().get());
		return true;
	}
	return false;
}

CalibrationInfo SystemContextState::getNextCalibration() const {
	return ConvertFromCDM::convert(data->NextCalibration().get());
}

bool SystemContextState::hasNextCalibration() const {
	return data->NextCalibration().present();
}

SystemContextState & SystemContextState::setPhysicalConnector(const PhysicalConnectorInfo & value) {
	data->PhysicalConnector(ConvertToCDM::convert(value));
	return *this;
}

bool SystemContextState::getPhysicalConnector(PhysicalConnectorInfo & out) const {
	if (data->PhysicalConnector().present()) {
		out = ConvertFromCDM::convert(data->PhysicalConnector().get());
		return true;
	}
	return false;
}

PhysicalConnectorInfo SystemContextState::getPhysicalConnector() const {
	return ConvertFromCDM::convert(data->PhysicalConnector().get());
}

bool SystemContextState::hasPhysicalConnector() const {
	return data->PhysicalConnector().present();
}

SystemContextState & SystemContextState::setActivationState(const ComponentActivation & value) {
	data->ActivationState(ConvertToCDM::convert(value));
	return *this;
}

bool SystemContextState::getActivationState(ComponentActivation & out) const {
	if (data->ActivationState().present()) {
		out = ConvertFromCDM::convert(data->ActivationState().get());
		return true;
	}
	return false;
}

ComponentActivation SystemContextState::getActivationState() const {
	return ConvertFromCDM::convert(data->ActivationState().get());
}

bool SystemContextState::hasActivationState() const {
	return data->ActivationState().present();
}

SystemContextState & SystemContextState::setOperatingHours(const unsigned int & value) {
	data->OperatingHours(ConvertToCDM::convert(value));
	return *this;
}

bool SystemContextState::getOperatingHours(unsigned int & out) const {
	if (data->OperatingHours().present()) {
		out = ConvertFromCDM::convert(data->OperatingHours().get());
		return true;
	}
	return false;
}

unsigned int SystemContextState::getOperatingHours() const {
	return ConvertFromCDM::convert(data->OperatingHours().get());
}

bool SystemContextState::hasOperatingHours() const {
	return data->OperatingHours().present();
}

SystemContextState & SystemContextState::setOperatingCycles(const int & value) {
	data->OperatingCycles(ConvertToCDM::convert(value));
	return *this;
}

bool SystemContextState::getOperatingCycles(int & out) const {
	if (data->OperatingCycles().present()) {
		out = ConvertFromCDM::convert(data->OperatingCycles().get());
		return true;
	}
	return false;
}

int SystemContextState::getOperatingCycles() const {
	return ConvertFromCDM::convert(data->OperatingCycles().get());
}

bool SystemContextState::hasOperatingCycles() const {
	return data->OperatingCycles().present();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

