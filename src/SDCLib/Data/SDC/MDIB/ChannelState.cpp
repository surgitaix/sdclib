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
 *  ChannelState.cpp
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

#include "SDCLib/Data/SDC/MDIB/ChannelState.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/CalibrationInfo.h"
#include "SDCLib/Data/SDC/MDIB/PhysicalConnectorInfo.h"

namespace SDCLib {
namespace Data {
namespace SDC {


ChannelState::ChannelState(
		HandleRef descriptorhandle
) : data(Defaults::ChannelStateInit(
		descriptorhandle
))
{}

ChannelState::operator CDM::ChannelState() const {
	return *data;
}

ChannelState::ChannelState(const CDM::ChannelState & object)
: data(new CDM::ChannelState(object))
{ }

ChannelState::ChannelState(const ChannelState & object)
: data(std::make_shared<CDM::ChannelState>(*object.data))
{ }

void ChannelState::copyFrom(const ChannelState & object) {
	data = std::make_shared<CDM::ChannelState>(*object.data);
}

ChannelState & ChannelState:: operator=(const ChannelState& object) {
	copyFrom(object);
	return *this;
}


ChannelState & ChannelState::setStateVersion(const VersionCounter & value) {
	data->setStateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool ChannelState::getStateVersion(VersionCounter & out) const {
	if (data->getStateVersion().present()) {
		out = ConvertFromCDM::convert(data->getStateVersion().get());
		return true;
	}
	return false;
}

VersionCounter ChannelState::getStateVersion() const {
	return ConvertFromCDM::convert(data->getStateVersion().get());
}

bool ChannelState::hasStateVersion() const {
	return data->getStateVersion().present();
}

ChannelState & ChannelState::setDescriptorHandle(const HandleRef & value) {
	data->setDescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


HandleRef ChannelState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->getDescriptorHandle());
}

ChannelState & ChannelState::setDescriptorVersion(const ReferencedVersion & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool ChannelState::getDescriptorVersion(ReferencedVersion & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion ChannelState::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool ChannelState::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

ChannelState & ChannelState::setCalibrationInfo(const CalibrationInfo & value) {
	data->setCalibrationInfo(ConvertToCDM::convert(value));
	return *this;
}

bool ChannelState::getCalibrationInfo(CalibrationInfo & out) const {
	if (data->getCalibrationInfo().present()) {
		out = ConvertFromCDM::convert(data->getCalibrationInfo().get());
		return true;
	}
	return false;
}

CalibrationInfo ChannelState::getCalibrationInfo() const {
	return ConvertFromCDM::convert(data->getCalibrationInfo().get());
}

bool ChannelState::hasCalibrationInfo() const {
	return data->getCalibrationInfo().present();
}

ChannelState & ChannelState::setNextCalibration(const CalibrationInfo & value) {
	data->setNextCalibration(ConvertToCDM::convert(value));
	return *this;
}

bool ChannelState::getNextCalibration(CalibrationInfo & out) const {
	if (data->getNextCalibration().present()) {
		out = ConvertFromCDM::convert(data->getNextCalibration().get());
		return true;
	}
	return false;
}

CalibrationInfo ChannelState::getNextCalibration() const {
	return ConvertFromCDM::convert(data->getNextCalibration().get());
}

bool ChannelState::hasNextCalibration() const {
	return data->getNextCalibration().present();
}

ChannelState & ChannelState::setPhysicalConnector(const PhysicalConnectorInfo & value) {
	data->setPhysicalConnector(ConvertToCDM::convert(value));
	return *this;
}

bool ChannelState::getPhysicalConnector(PhysicalConnectorInfo & out) const {
	if (data->getPhysicalConnector().present()) {
		out = ConvertFromCDM::convert(data->getPhysicalConnector().get());
		return true;
	}
	return false;
}

PhysicalConnectorInfo ChannelState::getPhysicalConnector() const {
	return ConvertFromCDM::convert(data->getPhysicalConnector().get());
}

bool ChannelState::hasPhysicalConnector() const {
	return data->getPhysicalConnector().present();
}

ChannelState & ChannelState::setActivationState(const ComponentActivation & value) {
	data->setActivationState(ConvertToCDM::convert(value));
	return *this;
}

bool ChannelState::getActivationState(ComponentActivation & out) const {
	if (data->getActivationState().present()) {
		out = ConvertFromCDM::convert(data->getActivationState().get());
		return true;
	}
	return false;
}

ComponentActivation ChannelState::getActivationState() const {
	return ConvertFromCDM::convert(data->getActivationState().get());
}

bool ChannelState::hasActivationState() const {
	return data->getActivationState().present();
}

ChannelState & ChannelState::setOperatingHours(const unsigned int & value) {
	data->setOperatingHours(ConvertToCDM::convert(value));
	return *this;
}

bool ChannelState::getOperatingHours(unsigned int & out) const {
	if (data->getOperatingHours().present()) {
		out = ConvertFromCDM::convert(data->getOperatingHours().get());
		return true;
	}
	return false;
}

unsigned int ChannelState::getOperatingHours() const {
	return ConvertFromCDM::convert(data->getOperatingHours().get());
}

bool ChannelState::hasOperatingHours() const {
	return data->getOperatingHours().present();
}

ChannelState & ChannelState::setOperatingCycles(const int & value) {
	data->setOperatingCycles(ConvertToCDM::convert(value));
	return *this;
}

bool ChannelState::getOperatingCycles(int & out) const {
	if (data->getOperatingCycles().present()) {
		out = ConvertFromCDM::convert(data->getOperatingCycles().get());
		return true;
	}
	return false;
}

int ChannelState::getOperatingCycles() const {
	return ConvertFromCDM::convert(data->getOperatingCycles().get());
}

bool ChannelState::hasOperatingCycles() const {
	return data->getOperatingCycles().present();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

