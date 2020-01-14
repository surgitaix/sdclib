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
 *  Author: besting, buerger, roehser
 */

/**
 * THIS FILE IS GENERATED AUTOMATICALLY! DO NOT MODIFY!
 *
 * YOUR CHANGES WILL BE OVERWRITTEN!
 *
 * USE THE DEFINITION FILES IN THE FOLDER "codegenerator" INSTEAD!
 */

#include "SDCLib/Data/SDC/MDIB/VmdState.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/OperatingJurisdiction.h"
#include "SDCLib/Data/SDC/MDIB/CalibrationInfo.h"
#include "SDCLib/Data/SDC/MDIB/PhysicalConnectorInfo.h"

namespace SDCLib {
namespace Data {
namespace SDC {


VmdState::VmdState(
		HandleRef descriptorhandle
) : data(Defaults::VmdStateInit(
		descriptorhandle
))
{}

VmdState::operator CDM::VmdState() const {
	return *data;
}

VmdState::VmdState(const CDM::VmdState & object)
: data(new CDM::VmdState(object))
{ }

VmdState::VmdState(const VmdState & object)
: data(std::make_shared<CDM::VmdState>(*object.data))
{ }

void VmdState::copyFrom(const VmdState & object) {
	data = std::make_shared<CDM::VmdState>(*object.data);
}

VmdState & VmdState:: operator=(const VmdState& object) {
	copyFrom(object);
	return *this;
}


VmdState & VmdState::setStateVersion(const VersionCounter & value) {
	data->setStateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool VmdState::getStateVersion(VersionCounter & out) const {
	if (data->getStateVersion().present()) {
		out = ConvertFromCDM::convert(data->getStateVersion().get());
		return true;
	}
	return false;
}

VersionCounter VmdState::getStateVersion() const {
	return ConvertFromCDM::convert(data->getStateVersion().get());
}

bool VmdState::hasStateVersion() const {
	return data->getStateVersion().present();
}

VmdState & VmdState::setDescriptorHandle(const HandleRef & value) {
	data->setDescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


HandleRef VmdState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->getDescriptorHandle());
}

VmdState & VmdState::setDescriptorVersion(const ReferencedVersion & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool VmdState::getDescriptorVersion(ReferencedVersion & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion VmdState::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool VmdState::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

VmdState & VmdState::setCalibrationInfo(const CalibrationInfo & value) {
	data->setCalibrationInfo(ConvertToCDM::convert(value));
	return *this;
}

bool VmdState::getCalibrationInfo(CalibrationInfo & out) const {
	if (data->getCalibrationInfo().present()) {
		out = ConvertFromCDM::convert(data->getCalibrationInfo().get());
		return true;
	}
	return false;
}

CalibrationInfo VmdState::getCalibrationInfo() const {
	return ConvertFromCDM::convert(data->getCalibrationInfo().get());
}

bool VmdState::hasCalibrationInfo() const {
	return data->getCalibrationInfo().present();
}

VmdState & VmdState::setNextCalibration(const CalibrationInfo & value) {
	data->setNextCalibration(ConvertToCDM::convert(value));
	return *this;
}

bool VmdState::getNextCalibration(CalibrationInfo & out) const {
	if (data->getNextCalibration().present()) {
		out = ConvertFromCDM::convert(data->getNextCalibration().get());
		return true;
	}
	return false;
}

CalibrationInfo VmdState::getNextCalibration() const {
	return ConvertFromCDM::convert(data->getNextCalibration().get());
}

bool VmdState::hasNextCalibration() const {
	return data->getNextCalibration().present();
}

VmdState & VmdState::setPhysicalConnector(const PhysicalConnectorInfo & value) {
	data->setPhysicalConnector(ConvertToCDM::convert(value));
	return *this;
}

bool VmdState::getPhysicalConnector(PhysicalConnectorInfo & out) const {
	if (data->getPhysicalConnector().present()) {
		out = ConvertFromCDM::convert(data->getPhysicalConnector().get());
		return true;
	}
	return false;
}

PhysicalConnectorInfo VmdState::getPhysicalConnector() const {
	return ConvertFromCDM::convert(data->getPhysicalConnector().get());
}

bool VmdState::hasPhysicalConnector() const {
	return data->getPhysicalConnector().present();
}

VmdState & VmdState::setActivationState(const ComponentActivation & value) {
	data->setActivationState(ConvertToCDM::convert(value));
	return *this;
}

bool VmdState::getActivationState(ComponentActivation & out) const {
	if (data->getActivationState().present()) {
		out = ConvertFromCDM::convert(data->getActivationState().get());
		return true;
	}
	return false;
}

ComponentActivation VmdState::getActivationState() const {
	return ConvertFromCDM::convert(data->getActivationState().get());
}

bool VmdState::hasActivationState() const {
	return data->getActivationState().present();
}

VmdState & VmdState::setOperatingHours(const unsigned int & value) {
	data->setOperatingHours(ConvertToCDM::convert(value));
	return *this;
}

bool VmdState::getOperatingHours(unsigned int & out) const {
	if (data->getOperatingHours().present()) {
		out = ConvertFromCDM::convert(data->getOperatingHours().get());
		return true;
	}
	return false;
}

unsigned int VmdState::getOperatingHours() const {
	return ConvertFromCDM::convert(data->getOperatingHours().get());
}

bool VmdState::hasOperatingHours() const {
	return data->getOperatingHours().present();
}

VmdState & VmdState::setOperatingCycles(const int & value) {
	data->setOperatingCycles(ConvertToCDM::convert(value));
	return *this;
}

bool VmdState::getOperatingCycles(int & out) const {
	if (data->getOperatingCycles().present()) {
		out = ConvertFromCDM::convert(data->getOperatingCycles().get());
		return true;
	}
	return false;
}

int VmdState::getOperatingCycles() const {
	return ConvertFromCDM::convert(data->getOperatingCycles().get());
}

bool VmdState::hasOperatingCycles() const {
	return data->getOperatingCycles().present();
}

VmdState & VmdState::setOperatingJurisdiction(const OperatingJurisdiction & value) {
	data->setOperatingJurisdiction(ConvertToCDM::convert(value));
	return *this;
}

bool VmdState::getOperatingJurisdiction(OperatingJurisdiction & out) const {
	if (data->getOperatingJurisdiction().present()) {
		out = ConvertFromCDM::convert(data->getOperatingJurisdiction().get());
		return true;
	}
	return false;
}

OperatingJurisdiction VmdState::getOperatingJurisdiction() const {
	return ConvertFromCDM::convert(data->getOperatingJurisdiction().get());
}

bool VmdState::hasOperatingJurisdiction() const {
	return data->getOperatingJurisdiction().present();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

