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
 *  Author: besting, roehser
 */
 
/**
 * THIS FILE IS GENERATED AUTOMATICALLY! DO NOT MODIFY!
 *
 * YOUR CHANGES WILL BE OVERWRITTEN!
 * 
 * USE THE DEFINITION FILES IN THE FOLDER "codegenerator" INSTEAD!
 */

#include "OSCLib/Data/OSCP/MDIB/ClockState.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/CalibrationInfo.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

ClockState::ClockState() : data(Defaults::ClockState()) {
}

ClockState::operator CDM::ClockState() const {
	return *data;
}

ClockState::ClockState(const CDM::ClockState & object) : data(new CDM::ClockState(object)) {

}

ClockState::ClockState(const ClockState & object) : data(new CDM::ClockState(*object.data)) {

}

ClockState::~ClockState() {

}

void ClockState::copyFrom(const ClockState & object) {
	*data = *object.data;
}

ClockState & ClockState:: operator=(const ClockState & object) {
	copyFrom(object);
	return *this;
}


ClockState & ClockState::setStateVersion(const VersionCounter & value) {
	data->StateVersion(ConvertToCDM::convert(value));
	return *this;
}


VersionCounter ClockState::getStateVersion() const {
	return ConvertFromCDM::convert(data->StateVersion());
}
	
ClockState & ClockState::setDescriptorHandle(const HandleRef & value) {
	data->DescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


HandleRef ClockState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->DescriptorHandle());
}
	
ClockState & ClockState::setDescriptorVersion(const ReferencedVersion & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}


ReferencedVersion ClockState::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion());
}
	
ClockState & ClockState::setCalibrationInfo(const CalibrationInfo & value) {
	data->CalibrationInfo(ConvertToCDM::convert(value));
	return *this;
}

bool ClockState::getCalibrationInfo(CalibrationInfo & out) const {
	if (data->CalibrationInfo().present()) {
		out = ConvertFromCDM::convert(data->CalibrationInfo().get());
		return true;
	}
	return false;
}

CalibrationInfo ClockState::getCalibrationInfo() const {
	return ConvertFromCDM::convert(data->CalibrationInfo().get());
}
	
bool ClockState::hasCalibrationInfo() const {
	return data->CalibrationInfo().present();
}
	
ClockState & ClockState::setNextCalibration(const CalibrationInfo & value) {
	data->NextCalibration(ConvertToCDM::convert(value));
	return *this;
}

bool ClockState::getNextCalibration(CalibrationInfo & out) const {
	if (data->NextCalibration().present()) {
		out = ConvertFromCDM::convert(data->NextCalibration().get());
		return true;
	}
	return false;
}

CalibrationInfo ClockState::getNextCalibration() const {
	return ConvertFromCDM::convert(data->NextCalibration().get());
}
	
bool ClockState::hasNextCalibration() const {
	return data->NextCalibration().present();
}
	
ClockState & ClockState::setActivationState(const ComponentActivation & value) {
	data->ActivationState(ConvertToCDM::convert(value));
	return *this;
}


ComponentActivation ClockState::getActivationState() const {
	return ConvertFromCDM::convert(data->ActivationState());
}
	
ClockState & ClockState::setOperatingHours(const unsigned int & value) {
	data->OperatingHours(ConvertToCDM::convert(value));
	return *this;
}


unsigned int ClockState::getOperatingHours() const {
	return ConvertFromCDM::convert(data->OperatingHours());
}
	
ClockState & ClockState::setOperatingCycles(const int & value) {
	data->OperatingCycles(ConvertToCDM::convert(value));
	return *this;
}


int ClockState::getOperatingCycles() const {
	return ConvertFromCDM::convert(data->OperatingCycles());
}
	
ClockState & ClockState::setActiveSyncProtocol(const CodedValue & value) {
	data->ActiveSyncProtocol(ConvertToCDM::convert(value));
	return *this;
}

bool ClockState::getActiveSyncProtocol(CodedValue & out) const {
	if (data->ActiveSyncProtocol().present()) {
		out = ConvertFromCDM::convert(data->ActiveSyncProtocol().get());
		return true;
	}
	return false;
}

CodedValue ClockState::getActiveSyncProtocol() const {
	return ConvertFromCDM::convert(data->ActiveSyncProtocol().get());
}
	
bool ClockState::hasActiveSyncProtocol() const {
	return data->ActiveSyncProtocol().present();
}
	
ClockState & ClockState::setDateAndTime(const Timestamp & value) {
	data->DateAndTime(ConvertToCDM::convert(value));
	return *this;
}


Timestamp ClockState::getDateAndTime() const {
	return ConvertFromCDM::convert(data->DateAndTime());
}
	
ClockState & ClockState::setRemoteSync(const bool & value) {
	data->RemoteSync(ConvertToCDM::convert(value));
	return *this;
}


bool ClockState::getRemoteSync() const {
	return ConvertFromCDM::convert(data->RemoteSync());
}
	
ClockState & ClockState::setReferenceSource(const std::string & value) {
	data->ReferenceSource(ConvertToCDM::convert(value));
	return *this;
}


std::string ClockState::getReferenceSource() const {
	return ConvertFromCDM::convert(data->ReferenceSource());
}
	
ClockState & ClockState::setAccuracy(const double & value) {
	data->Accuracy(ConvertToCDM::convert(value));
	return *this;
}

bool ClockState::getAccuracy(double & out) const {
	if (data->Accuracy().present()) {
		out = ConvertFromCDM::convert(data->Accuracy().get());
		return true;
	}
	return false;
}

double ClockState::getAccuracy() const {
	return ConvertFromCDM::convert(data->Accuracy().get());
}
	
bool ClockState::hasAccuracy() const {
	return data->Accuracy().present();
}
	
ClockState & ClockState::setLastSet(const Timestamp & value) {
	data->LastSet(ConvertToCDM::convert(value));
	return *this;
}


Timestamp ClockState::getLastSet() const {
	return ConvertFromCDM::convert(data->LastSet());
}
	
ClockState & ClockState::setTimeZone(const TimeZone & value) {
	data->TimeZone(ConvertToCDM::convert(value));
	return *this;
}

bool ClockState::getTimeZone(TimeZone & out) const {
	if (data->TimeZone().present()) {
		out = ConvertFromCDM::convert(data->TimeZone().get());
		return true;
	}
	return false;
}

TimeZone ClockState::getTimeZone() const {
	return ConvertFromCDM::convert(data->TimeZone().get());
}
	
bool ClockState::hasTimeZone() const {
	return data->TimeZone().present();
}
	
ClockState & ClockState::setCriticalUse(const bool & value) {
	data->CriticalUse(ConvertToCDM::convert(value));
	return *this;
}

bool ClockState::getCriticalUse(bool & out) const {
	if (data->CriticalUse().present()) {
		out = ConvertFromCDM::convert(data->CriticalUse().get());
		return true;
	}
	return false;
}

bool ClockState::getCriticalUse() const {
	return ConvertFromCDM::convert(data->CriticalUse().get());
}
	
bool ClockState::hasCriticalUse() const {
	return data->CriticalUse().present();
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

