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
 *  LimitAlertConditionState.cpp
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

#include "OSCLib/Data/OSCP/MDIB/LimitAlertConditionState.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/Range.h"
#include "OSCLib/Data/OSCP/MDIB/Timestamp.h"
#include "OSCLib/Data/OSCP/MDIB/VersionCounter.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

LimitAlertConditionState::LimitAlertConditionState() : data(Defaults::LimitAlertConditionState()) {
}

LimitAlertConditionState::operator CDM::LimitAlertConditionState() const {
	return *data;
}

LimitAlertConditionState::LimitAlertConditionState(const CDM::LimitAlertConditionState & object) : data(new CDM::LimitAlertConditionState(object)) {

}

LimitAlertConditionState::LimitAlertConditionState(const LimitAlertConditionState & object) : data(new CDM::LimitAlertConditionState(*object.data)) {

}

LimitAlertConditionState::~LimitAlertConditionState() {

}

void LimitAlertConditionState::copyFrom(const LimitAlertConditionState & object) {
	*data = *object.data;
}

LimitAlertConditionState & LimitAlertConditionState:: operator=(const LimitAlertConditionState & object) {
	copyFrom(object);
	return *this;
}


LimitAlertConditionState & LimitAlertConditionState::setHandle(const std::string & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}

bool LimitAlertConditionState::getHandle(std::string & out) const {
	if (data->Handle().present()) {
		out = ConvertFromCDM::convert(data->Handle().get());
		return true;
	}
	return false;
}

std::string LimitAlertConditionState::getHandle() const {
	return ConvertFromCDM::convert(data->Handle().get());
}
	
bool LimitAlertConditionState::hasHandle() const {
	return data->Handle().present();
}
	
LimitAlertConditionState & LimitAlertConditionState::setDescriptorHandle(const std::string & value) {
	data->DescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


std::string LimitAlertConditionState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->DescriptorHandle());
}
	
LimitAlertConditionState & LimitAlertConditionState::setStateVersion(const VersionCounter & value) {
	data->StateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool LimitAlertConditionState::getStateVersion(VersionCounter & out) const {
	if (data->StateVersion().present()) {
		out = ConvertFromCDM::convert(data->StateVersion().get());
		return true;
	}
	return false;
}

VersionCounter LimitAlertConditionState::getStateVersion() const {
	return ConvertFromCDM::convert(data->StateVersion().get());
}
	
bool LimitAlertConditionState::hasStateVersion() const {
	return data->StateVersion().present();
}
	
LimitAlertConditionState & LimitAlertConditionState::setActivationState(const PausableActivation & value) {
	data->ActivationState(ConvertToCDM::convert(value));
	return *this;
}


PausableActivation LimitAlertConditionState::getActivationState() const {
	return ConvertFromCDM::convert(data->ActivationState());
}
	
LimitAlertConditionState & LimitAlertConditionState::setRank(const int & value) {
	data->Rank(ConvertToCDM::convert(value));
	return *this;
}

bool LimitAlertConditionState::getRank(int & out) const {
	if (data->Rank().present()) {
		out = ConvertFromCDM::convert(data->Rank().get());
		return true;
	}
	return false;
}

int LimitAlertConditionState::getRank() const {
	return ConvertFromCDM::convert(data->Rank().get());
}
	
bool LimitAlertConditionState::hasRank() const {
	return data->Rank().present();
}
	
LimitAlertConditionState & LimitAlertConditionState::setPresence(const bool & value) {
	data->Presence(ConvertToCDM::convert(value));
	return *this;
}


bool LimitAlertConditionState::getPresence() const {
	return ConvertFromCDM::convert(data->Presence());
}
	
LimitAlertConditionState & LimitAlertConditionState::setObservationTime(const Timestamp & value) {
	data->ObservationTime(ConvertToCDM::convert(value));
	return *this;
}

bool LimitAlertConditionState::getObservationTime(Timestamp & out) const {
	if (data->ObservationTime().present()) {
		out = ConvertFromCDM::convert(data->ObservationTime().get());
		return true;
	}
	return false;
}

Timestamp LimitAlertConditionState::getObservationTime() const {
	return ConvertFromCDM::convert(data->ObservationTime().get());
}
	
bool LimitAlertConditionState::hasObservationTime() const {
	return data->ObservationTime().present();
}
	
LimitAlertConditionState & LimitAlertConditionState::setLimits(const Range & value) {
	data->Limits(ConvertToCDM::convert(value));
	return *this;
}

bool LimitAlertConditionState::getLimits(Range & out) const {
	if (data->Limits().present()) {
		out = ConvertFromCDM::convert(data->Limits().get());
		return true;
	}
	return false;
}

Range LimitAlertConditionState::getLimits() const {
	return ConvertFromCDM::convert(data->Limits().get());
}
	
bool LimitAlertConditionState::hasLimits() const {
	return data->Limits().present();
}
	
LimitAlertConditionState & LimitAlertConditionState::setMonitoredAlertLimits(const MonitoredAlertLimits & value) {
	data->MonitoredAlertLimits(ConvertToCDM::convert(value));
	return *this;
}


MonitoredAlertLimits LimitAlertConditionState::getMonitoredAlertLimits() const {
	return ConvertFromCDM::convert(data->MonitoredAlertLimits());
}
	
LimitAlertConditionState & LimitAlertConditionState::setAutoLimitActivationState(const PausableActivation & value) {
	data->AutoLimitActivationState(ConvertToCDM::convert(value));
	return *this;
}

bool LimitAlertConditionState::getAutoLimitActivationState(PausableActivation & out) const {
	if (data->AutoLimitActivationState().present()) {
		out = ConvertFromCDM::convert(data->AutoLimitActivationState().get());
		return true;
	}
	return false;
}

PausableActivation LimitAlertConditionState::getAutoLimitActivationState() const {
	return ConvertFromCDM::convert(data->AutoLimitActivationState().get());
}
	
bool LimitAlertConditionState::hasAutoLimitActivationState() const {
	return data->AutoLimitActivationState().present();
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

