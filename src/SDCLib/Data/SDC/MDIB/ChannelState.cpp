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
)) {}

ChannelState::operator CDM::ChannelState() const {
	return *data;
}

ChannelState::ChannelState(const CDM::ChannelState & object) : data(new CDM::ChannelState(object)) {

}

ChannelState::ChannelState(const ChannelState & object) : data(new CDM::ChannelState(*object.data)) {

}

ChannelState::~ChannelState() {

}

void ChannelState::copyFrom(const ChannelState & object) {
	data = std::shared_ptr<CDM::ChannelState>( new CDM::ChannelState(*object.data));
}

ChannelState & ChannelState:: operator=(const ChannelState & object) {
	copyFrom(object);
	return *this;
}


ChannelState & ChannelState::setStateVersion(const VersionCounter & value) {
	data->StateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool ChannelState::getStateVersion(VersionCounter & out) const {
	if (data->StateVersion().present()) {
		out = ConvertFromCDM::convert(data->StateVersion().get());
		return true;
	}
	return false;
}

VersionCounter ChannelState::getStateVersion() const {
	return ConvertFromCDM::convert(data->StateVersion().get());
}

bool ChannelState::hasStateVersion() const {
	return data->StateVersion().present();
}

ChannelState & ChannelState::setDescriptorHandle(const HandleRef & value) {
	data->DescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


HandleRef ChannelState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->DescriptorHandle());
}

ChannelState & ChannelState::setDescriptorVersion(const ReferencedVersion & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool ChannelState::getDescriptorVersion(ReferencedVersion & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion ChannelState::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}

bool ChannelState::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}

ChannelState & ChannelState::setCalibrationInfo(const CalibrationInfo & value) {
	data->CalibrationInfo(ConvertToCDM::convert(value));
	return *this;
}

bool ChannelState::getCalibrationInfo(CalibrationInfo & out) const {
	if (data->CalibrationInfo().present()) {
		out = ConvertFromCDM::convert(data->CalibrationInfo().get());
		return true;
	}
	return false;
}

CalibrationInfo ChannelState::getCalibrationInfo() const {
	return ConvertFromCDM::convert(data->CalibrationInfo().get());
}

bool ChannelState::hasCalibrationInfo() const {
	return data->CalibrationInfo().present();
}

ChannelState & ChannelState::setNextCalibration(const CalibrationInfo & value) {
	data->NextCalibration(ConvertToCDM::convert(value));
	return *this;
}

bool ChannelState::getNextCalibration(CalibrationInfo & out) const {
	if (data->NextCalibration().present()) {
		out = ConvertFromCDM::convert(data->NextCalibration().get());
		return true;
	}
	return false;
}

CalibrationInfo ChannelState::getNextCalibration() const {
	return ConvertFromCDM::convert(data->NextCalibration().get());
}

bool ChannelState::hasNextCalibration() const {
	return data->NextCalibration().present();
}

ChannelState & ChannelState::setPhysicalConnector(const PhysicalConnectorInfo & value) {
	data->PhysicalConnector(ConvertToCDM::convert(value));
	return *this;
}

bool ChannelState::getPhysicalConnector(PhysicalConnectorInfo & out) const {
	if (data->PhysicalConnector().present()) {
		out = ConvertFromCDM::convert(data->PhysicalConnector().get());
		return true;
	}
	return false;
}

PhysicalConnectorInfo ChannelState::getPhysicalConnector() const {
	return ConvertFromCDM::convert(data->PhysicalConnector().get());
}

bool ChannelState::hasPhysicalConnector() const {
	return data->PhysicalConnector().present();
}

ChannelState & ChannelState::setActivationState(const ComponentActivation & value) {
	data->ActivationState(ConvertToCDM::convert(value));
	return *this;
}

bool ChannelState::getActivationState(ComponentActivation & out) const {
	if (data->ActivationState().present()) {
		out = ConvertFromCDM::convert(data->ActivationState().get());
		return true;
	}
	return false;
}

ComponentActivation ChannelState::getActivationState() const {
	return ConvertFromCDM::convert(data->ActivationState().get());
}

bool ChannelState::hasActivationState() const {
	return data->ActivationState().present();
}

ChannelState & ChannelState::setOperatingHours(const unsigned int & value) {
	data->OperatingHours(ConvertToCDM::convert(value));
	return *this;
}

bool ChannelState::getOperatingHours(unsigned int & out) const {
	if (data->OperatingHours().present()) {
		out = ConvertFromCDM::convert(data->OperatingHours().get());
		return true;
	}
	return false;
}

unsigned int ChannelState::getOperatingHours() const {
	return ConvertFromCDM::convert(data->OperatingHours().get());
}

bool ChannelState::hasOperatingHours() const {
	return data->OperatingHours().present();
}

ChannelState & ChannelState::setOperatingCycles(const int & value) {
	data->OperatingCycles(ConvertToCDM::convert(value));
	return *this;
}

bool ChannelState::getOperatingCycles(int & out) const {
	if (data->OperatingCycles().present()) {
		out = ConvertFromCDM::convert(data->OperatingCycles().get());
		return true;
	}
	return false;
}

int ChannelState::getOperatingCycles() const {
	return ConvertFromCDM::convert(data->OperatingCycles().get());
}

bool ChannelState::hasOperatingCycles() const {
	return data->OperatingCycles().present();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

