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
 *  ClockState.cpp
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

#include "SDCLib/Data/SDC/MDIB/ClockState.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/CodedValue.h"
#include "SDCLib/Data/SDC/MDIB/CalibrationInfo.h"
#include "SDCLib/Data/SDC/MDIB/PhysicalConnectorInfo.h"

namespace SDCLib {
namespace Data {
namespace SDC {


ClockState::ClockState(
		HandleRef descriptorhandle
		,
		bool remotesync
) : data(Defaults::ClockStateInit(
		descriptorhandle
		,
		remotesync
))
{}

ClockState::operator CDM::ClockState() const {
	return *data;
}

ClockState::ClockState(const CDM::ClockState & object)
: data(new CDM::ClockState(object))
{ }

ClockState::ClockState(const ClockState & object)
: data(std::make_shared<CDM::ClockState>(*object.data))
{ }

void ClockState::copyFrom(const ClockState & object) {
	data = std::make_shared<CDM::ClockState>(*object.data);
}

ClockState & ClockState:: operator=(const ClockState& object) {
	copyFrom(object);
	return *this;
}


ClockState & ClockState::setStateVersion(const VersionCounter & value) {
	data->setStateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool ClockState::getStateVersion(VersionCounter & out) const {
	if (data->getStateVersion().present()) {
		out = ConvertFromCDM::convert(data->getStateVersion().get());
		return true;
	}
	return false;
}

VersionCounter ClockState::getStateVersion() const {
	return ConvertFromCDM::convert(data->getStateVersion().get());
}

bool ClockState::hasStateVersion() const {
	return data->getStateVersion().present();
}

ClockState & ClockState::setDescriptorHandle(const HandleRef & value) {
	data->setDescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


HandleRef ClockState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->getDescriptorHandle());
}

ClockState & ClockState::setDescriptorVersion(const ReferencedVersion & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool ClockState::getDescriptorVersion(ReferencedVersion & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion ClockState::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool ClockState::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

ClockState & ClockState::setCalibrationInfo(const CalibrationInfo & value) {
	data->setCalibrationInfo(ConvertToCDM::convert(value));
	return *this;
}

bool ClockState::getCalibrationInfo(CalibrationInfo & out) const {
	if (data->getCalibrationInfo().present()) {
		out = ConvertFromCDM::convert(data->getCalibrationInfo().get());
		return true;
	}
	return false;
}

CalibrationInfo ClockState::getCalibrationInfo() const {
	return ConvertFromCDM::convert(data->getCalibrationInfo().get());
}

bool ClockState::hasCalibrationInfo() const {
	return data->getCalibrationInfo().present();
}

ClockState & ClockState::setNextCalibration(const CalibrationInfo & value) {
	data->setNextCalibration(ConvertToCDM::convert(value));
	return *this;
}

bool ClockState::getNextCalibration(CalibrationInfo & out) const {
	if (data->getNextCalibration().present()) {
		out = ConvertFromCDM::convert(data->getNextCalibration().get());
		return true;
	}
	return false;
}

CalibrationInfo ClockState::getNextCalibration() const {
	return ConvertFromCDM::convert(data->getNextCalibration().get());
}

bool ClockState::hasNextCalibration() const {
	return data->getNextCalibration().present();
}

ClockState & ClockState::setPhysicalConnector(const PhysicalConnectorInfo & value) {
	data->setPhysicalConnector(ConvertToCDM::convert(value));
	return *this;
}

bool ClockState::getPhysicalConnector(PhysicalConnectorInfo & out) const {
	if (data->getPhysicalConnector().present()) {
		out = ConvertFromCDM::convert(data->getPhysicalConnector().get());
		return true;
	}
	return false;
}

PhysicalConnectorInfo ClockState::getPhysicalConnector() const {
	return ConvertFromCDM::convert(data->getPhysicalConnector().get());
}

bool ClockState::hasPhysicalConnector() const {
	return data->getPhysicalConnector().present();
}

ClockState & ClockState::setActivationState(const ComponentActivation & value) {
	data->setActivationState(ConvertToCDM::convert(value));
	return *this;
}

bool ClockState::getActivationState(ComponentActivation & out) const {
	if (data->getActivationState().present()) {
		out = ConvertFromCDM::convert(data->getActivationState().get());
		return true;
	}
	return false;
}

ComponentActivation ClockState::getActivationState() const {
	return ConvertFromCDM::convert(data->getActivationState().get());
}

bool ClockState::hasActivationState() const {
	return data->getActivationState().present();
}

ClockState & ClockState::setOperatingHours(const unsigned int & value) {
	data->setOperatingHours(ConvertToCDM::convert(value));
	return *this;
}

bool ClockState::getOperatingHours(unsigned int & out) const {
	if (data->getOperatingHours().present()) {
		out = ConvertFromCDM::convert(data->getOperatingHours().get());
		return true;
	}
	return false;
}

unsigned int ClockState::getOperatingHours() const {
	return ConvertFromCDM::convert(data->getOperatingHours().get());
}

bool ClockState::hasOperatingHours() const {
	return data->getOperatingHours().present();
}

ClockState & ClockState::setOperatingCycles(const int & value) {
	data->setOperatingCycles(ConvertToCDM::convert(value));
	return *this;
}

bool ClockState::getOperatingCycles(int & out) const {
	if (data->getOperatingCycles().present()) {
		out = ConvertFromCDM::convert(data->getOperatingCycles().get());
		return true;
	}
	return false;
}

int ClockState::getOperatingCycles() const {
	return ConvertFromCDM::convert(data->getOperatingCycles().get());
}

bool ClockState::hasOperatingCycles() const {
	return data->getOperatingCycles().present();
}

ClockState & ClockState::setActiveSyncProtocol(const CodedValue & value) {
	data->setActiveSyncProtocol(ConvertToCDM::convert(value));
	return *this;
}

bool ClockState::getActiveSyncProtocol(CodedValue & out) const {
	if (data->getActiveSyncProtocol().present()) {
		out = ConvertFromCDM::convert(data->getActiveSyncProtocol().get());
		return true;
	}
	return false;
}

CodedValue ClockState::getActiveSyncProtocol() const {
	return ConvertFromCDM::convert(data->getActiveSyncProtocol().get());
}

bool ClockState::hasActiveSyncProtocol() const {
	return data->getActiveSyncProtocol().present();
}

ClockState & ClockState::setDateAndTime(const Timestamp & value) {
	data->setDateAndTime(ConvertToCDM::convert(value));
	return *this;
}

bool ClockState::getDateAndTime(Timestamp & out) const {
	if (data->getDateAndTime().present()) {
		out = ConvertFromCDM::convert(data->getDateAndTime().get());
		return true;
	}
	return false;
}

Timestamp ClockState::getDateAndTime() const {
	return ConvertFromCDM::convert(data->getDateAndTime().get());
}

bool ClockState::hasDateAndTime() const {
	return data->getDateAndTime().present();
}

ClockState & ClockState::setRemoteSync(const bool & value) {
	data->setRemoteSync(ConvertToCDM::convert(value));
	return *this;
}


bool ClockState::getRemoteSync() const {
	return ConvertFromCDM::convert(data->getRemoteSync());
}

ClockState & ClockState::setAccuracy(const double & value) {
	data->setAccuracy(ConvertToCDM::convert(value));
	return *this;
}

bool ClockState::getAccuracy(double & out) const {
	if (data->getAccuracy().present()) {
		out = ConvertFromCDM::convert(data->getAccuracy().get());
		return true;
	}
	return false;
}

double ClockState::getAccuracy() const {
	return ConvertFromCDM::convert(data->getAccuracy().get());
}

bool ClockState::hasAccuracy() const {
	return data->getAccuracy().present();
}

ClockState & ClockState::setLastSet(const Timestamp & value) {
	data->setLastSet(ConvertToCDM::convert(value));
	return *this;
}

bool ClockState::getLastSet(Timestamp & out) const {
	if (data->getLastSet().present()) {
		out = ConvertFromCDM::convert(data->getLastSet().get());
		return true;
	}
	return false;
}

Timestamp ClockState::getLastSet() const {
	return ConvertFromCDM::convert(data->getLastSet().get());
}

bool ClockState::hasLastSet() const {
	return data->getLastSet().present();
}

ClockState & ClockState::setTimeZone(const TimeZone & value) {
	data->setTimeZone(ConvertToCDM::convert(value));
	return *this;
}

bool ClockState::getTimeZone(TimeZone & out) const {
	if (data->getTimeZone().present()) {
		out = ConvertFromCDM::convert(data->getTimeZone().get());
		return true;
	}
	return false;
}

TimeZone ClockState::getTimeZone() const {
	return ConvertFromCDM::convert(data->getTimeZone().get());
}

bool ClockState::hasTimeZone() const {
	return data->getTimeZone().present();
}

ClockState & ClockState::setCriticalUse(const bool & value) {
	data->setCriticalUse(ConvertToCDM::convert(value));
	return *this;
}

bool ClockState::getCriticalUse(bool & out) const {
	if (data->getCriticalUse().present()) {
		out = ConvertFromCDM::convert(data->getCriticalUse().get());
		return true;
	}
	return false;
}

bool ClockState::getCriticalUse() const {
	return ConvertFromCDM::convert(data->getCriticalUse().get());
}

bool ClockState::hasCriticalUse() const {
	return data->getCriticalUse().present();
}

ClockState & ClockState::addReferenceSource(const std::string & value) {
	data->getReferenceSource().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<std::string> ClockState::getReferenceSourceList() const {
	std::vector<std::string> result;
	result.reserve(data->getReferenceSource().size());
	for (const auto & value: data->getReferenceSource()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void ClockState::clearReferenceSourceList() {
	data->getReferenceSource().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

