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
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/Timestamp.h"
#include "OSCLib/Data/OSCP/MDIB/TimeZone.h"
#include "OSCLib/Data/OSCP/MDIB/VersionCounter.h"

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


ClockState & ClockState::setHandle(const std::string & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}

bool ClockState::getHandle(std::string & out) const {
	if (data->Handle().present()) {
		out = ConvertFromCDM::convert(data->Handle().get());
		return true;
	}
	return false;
}

std::string ClockState::getHandle() const {
	return ConvertFromCDM::convert(data->Handle().get());
}
	
bool ClockState::hasHandle() const {
	return data->Handle().present();
}
	
ClockState & ClockState::setDescriptorHandle(const std::string & value) {
	data->DescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


std::string ClockState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->DescriptorHandle());
}
	
ClockState & ClockState::setStateVersion(const VersionCounter & value) {
	data->StateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool ClockState::getStateVersion(VersionCounter & out) const {
	if (data->StateVersion().present()) {
		out = ConvertFromCDM::convert(data->StateVersion().get());
		return true;
	}
	return false;
}

VersionCounter ClockState::getStateVersion() const {
	return ConvertFromCDM::convert(data->StateVersion().get());
}
	
bool ClockState::hasStateVersion() const {
	return data->StateVersion().present();
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

bool ClockState::getDateAndTime(Timestamp & out) const {
	if (data->DateAndTime().present()) {
		out = ConvertFromCDM::convert(data->DateAndTime().get());
		return true;
	}
	return false;
}

Timestamp ClockState::getDateAndTime() const {
	return ConvertFromCDM::convert(data->DateAndTime().get());
}
	
bool ClockState::hasDateAndTime() const {
	return data->DateAndTime().present();
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

bool ClockState::getReferenceSource(std::string & out) const {
	if (data->ReferenceSource().present()) {
		out = ConvertFromCDM::convert(data->ReferenceSource().get());
		return true;
	}
	return false;
}

std::string ClockState::getReferenceSource() const {
	return ConvertFromCDM::convert(data->ReferenceSource().get());
}
	
bool ClockState::hasReferenceSource() const {
	return data->ReferenceSource().present();
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

bool ClockState::getLastSet(Timestamp & out) const {
	if (data->LastSet().present()) {
		out = ConvertFromCDM::convert(data->LastSet().get());
		return true;
	}
	return false;
}

Timestamp ClockState::getLastSet() const {
	return ConvertFromCDM::convert(data->LastSet().get());
}
	
bool ClockState::hasLastSet() const {
	return data->LastSet().present();
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

