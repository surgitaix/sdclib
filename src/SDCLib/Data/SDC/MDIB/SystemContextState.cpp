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

#include "SDCLib/Data/SDC/MDIB/SystemContextState.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/CalibrationInfo.h"
#include "SDCLib/Data/SDC/MDIB/PhysicalConnectorInfo.h"

namespace SDCLib {
namespace Data {
namespace SDC {


SystemContextState::SystemContextState(
		HandleRef descriptorhandle
) : data(Defaults::SystemContextStateInit(
		descriptorhandle
))
{}

SystemContextState::operator CDM::SystemContextState() const {
	return *data;
}

SystemContextState::SystemContextState(const CDM::SystemContextState & object)
: data(new CDM::SystemContextState(object))
{ }

SystemContextState::SystemContextState(const SystemContextState & object)
: data(std::make_shared<CDM::SystemContextState>(*object.data))
{ }

void SystemContextState::copyFrom(const SystemContextState & object) {
	data = std::make_shared<CDM::SystemContextState>(*object.data);
}

SystemContextState & SystemContextState:: operator=(const SystemContextState& object) {
	copyFrom(object);
	return *this;
}


SystemContextState & SystemContextState::setStateVersion(const VersionCounter & value) {
	data->setStateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool SystemContextState::getStateVersion(VersionCounter & out) const {
	if (data->getStateVersion().present()) {
		out = ConvertFromCDM::convert(data->getStateVersion().get());
		return true;
	}
	return false;
}

VersionCounter SystemContextState::getStateVersion() const {
	return ConvertFromCDM::convert(data->getStateVersion().get());
}

bool SystemContextState::hasStateVersion() const {
	return data->getStateVersion().present();
}

SystemContextState & SystemContextState::setDescriptorHandle(const HandleRef & value) {
	data->setDescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


HandleRef SystemContextState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->getDescriptorHandle());
}

SystemContextState & SystemContextState::setDescriptorVersion(const ReferencedVersion & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool SystemContextState::getDescriptorVersion(ReferencedVersion & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion SystemContextState::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool SystemContextState::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

SystemContextState & SystemContextState::setCalibrationInfo(const CalibrationInfo & value) {
	data->setCalibrationInfo(ConvertToCDM::convert(value));
	return *this;
}

bool SystemContextState::getCalibrationInfo(CalibrationInfo & out) const {
	if (data->getCalibrationInfo().present()) {
		out = ConvertFromCDM::convert(data->getCalibrationInfo().get());
		return true;
	}
	return false;
}

CalibrationInfo SystemContextState::getCalibrationInfo() const {
	return ConvertFromCDM::convert(data->getCalibrationInfo().get());
}

bool SystemContextState::hasCalibrationInfo() const {
	return data->getCalibrationInfo().present();
}

SystemContextState & SystemContextState::setNextCalibration(const CalibrationInfo & value) {
	data->setNextCalibration(ConvertToCDM::convert(value));
	return *this;
}

bool SystemContextState::getNextCalibration(CalibrationInfo & out) const {
	if (data->getNextCalibration().present()) {
		out = ConvertFromCDM::convert(data->getNextCalibration().get());
		return true;
	}
	return false;
}

CalibrationInfo SystemContextState::getNextCalibration() const {
	return ConvertFromCDM::convert(data->getNextCalibration().get());
}

bool SystemContextState::hasNextCalibration() const {
	return data->getNextCalibration().present();
}

SystemContextState & SystemContextState::setPhysicalConnector(const PhysicalConnectorInfo & value) {
	data->setPhysicalConnector(ConvertToCDM::convert(value));
	return *this;
}

bool SystemContextState::getPhysicalConnector(PhysicalConnectorInfo & out) const {
	if (data->getPhysicalConnector().present()) {
		out = ConvertFromCDM::convert(data->getPhysicalConnector().get());
		return true;
	}
	return false;
}

PhysicalConnectorInfo SystemContextState::getPhysicalConnector() const {
	return ConvertFromCDM::convert(data->getPhysicalConnector().get());
}

bool SystemContextState::hasPhysicalConnector() const {
	return data->getPhysicalConnector().present();
}

SystemContextState & SystemContextState::setActivationState(const ComponentActivation & value) {
	data->setActivationState(ConvertToCDM::convert(value));
	return *this;
}

bool SystemContextState::getActivationState(ComponentActivation & out) const {
	if (data->getActivationState().present()) {
		out = ConvertFromCDM::convert(data->getActivationState().get());
		return true;
	}
	return false;
}

ComponentActivation SystemContextState::getActivationState() const {
	return ConvertFromCDM::convert(data->getActivationState().get());
}

bool SystemContextState::hasActivationState() const {
	return data->getActivationState().present();
}

SystemContextState & SystemContextState::setOperatingHours(const unsigned int & value) {
	data->setOperatingHours(ConvertToCDM::convert(value));
	return *this;
}

bool SystemContextState::getOperatingHours(unsigned int & out) const {
	if (data->getOperatingHours().present()) {
		out = ConvertFromCDM::convert(data->getOperatingHours().get());
		return true;
	}
	return false;
}

unsigned int SystemContextState::getOperatingHours() const {
	return ConvertFromCDM::convert(data->getOperatingHours().get());
}

bool SystemContextState::hasOperatingHours() const {
	return data->getOperatingHours().present();
}

SystemContextState & SystemContextState::setOperatingCycles(const int & value) {
	data->setOperatingCycles(ConvertToCDM::convert(value));
	return *this;
}

bool SystemContextState::getOperatingCycles(int & out) const {
	if (data->getOperatingCycles().present()) {
		out = ConvertFromCDM::convert(data->getOperatingCycles().get());
		return true;
	}
	return false;
}

int SystemContextState::getOperatingCycles() const {
	return ConvertFromCDM::convert(data->getOperatingCycles().get());
}

bool SystemContextState::hasOperatingCycles() const {
	return data->getOperatingCycles().present();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

