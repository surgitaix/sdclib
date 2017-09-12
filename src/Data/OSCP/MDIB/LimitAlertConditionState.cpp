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
	
LimitAlertConditionState & LimitAlertConditionState::setDescriptorHandle(const HandleRef & value) {
	data->DescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


HandleRef LimitAlertConditionState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->DescriptorHandle());
}
	
LimitAlertConditionState & LimitAlertConditionState::setDescriptorVersion(const ReferencedVersion & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool LimitAlertConditionState::getDescriptorVersion(ReferencedVersion & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion LimitAlertConditionState::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}
	
bool LimitAlertConditionState::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}
	
LimitAlertConditionState & LimitAlertConditionState::setActivationState(const AlertActivation & value) {
	data->ActivationState(ConvertToCDM::convert(value));
	return *this;
}


AlertActivation LimitAlertConditionState::getActivationState() const {
	return ConvertFromCDM::convert(data->ActivationState());
}
	
LimitAlertConditionState & LimitAlertConditionState::setActualConditionGenerationDelay(const xml_schema::Duration & value) {
	data->ActualConditionGenerationDelay(ConvertToCDM::convert(value));
	return *this;
}

bool LimitAlertConditionState::getActualConditionGenerationDelay(xml_schema::Duration & out) const {
	if (data->ActualConditionGenerationDelay().present()) {
		out = ConvertFromCDM::convert(data->ActualConditionGenerationDelay().get());
		return true;
	}
	return false;
}

xml_schema::Duration LimitAlertConditionState::getActualConditionGenerationDelay() const {
	return ConvertFromCDM::convert(data->ActualConditionGenerationDelay().get());
}
	
bool LimitAlertConditionState::hasActualConditionGenerationDelay() const {
	return data->ActualConditionGenerationDelay().present();
}
	
LimitAlertConditionState & LimitAlertConditionState::setActualPriority(const AlertConditionPriority & value) {
	data->ActualPriority(ConvertToCDM::convert(value));
	return *this;
}

bool LimitAlertConditionState::getActualPriority(AlertConditionPriority & out) const {
	if (data->ActualPriority().present()) {
		out = ConvertFromCDM::convert(data->ActualPriority().get());
		return true;
	}
	return false;
}

AlertConditionPriority LimitAlertConditionState::getActualPriority() const {
	return ConvertFromCDM::convert(data->ActualPriority().get());
}
	
bool LimitAlertConditionState::hasActualPriority() const {
	return data->ActualPriority().present();
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
	
LimitAlertConditionState & LimitAlertConditionState::setDeterminationTime(const Timestamp & value) {
	data->DeterminationTime(ConvertToCDM::convert(value));
	return *this;
}

bool LimitAlertConditionState::getDeterminationTime(Timestamp & out) const {
	if (data->DeterminationTime().present()) {
		out = ConvertFromCDM::convert(data->DeterminationTime().get());
		return true;
	}
	return false;
}

Timestamp LimitAlertConditionState::getDeterminationTime() const {
	return ConvertFromCDM::convert(data->DeterminationTime().get());
}
	
bool LimitAlertConditionState::hasDeterminationTime() const {
	return data->DeterminationTime().present();
}
	
LimitAlertConditionState & LimitAlertConditionState::setLimits(const Range & value) {
	data->Limits(ConvertToCDM::convert(value));
	return *this;
}


Range LimitAlertConditionState::getLimits() const {
	return ConvertFromCDM::convert(data->Limits());
}
	
LimitAlertConditionState & LimitAlertConditionState::setMonitoredAlertLimits(const AlertConditionMonitoredLimits & value) {
	data->MonitoredAlertLimits(ConvertToCDM::convert(value));
	return *this;
}


AlertConditionMonitoredLimits LimitAlertConditionState::getMonitoredAlertLimits() const {
	return ConvertFromCDM::convert(data->MonitoredAlertLimits());
}
	
LimitAlertConditionState & LimitAlertConditionState::setAutoLimitActivationState(const AlertActivation & value) {
	data->AutoLimitActivationState(ConvertToCDM::convert(value));
	return *this;
}

bool LimitAlertConditionState::getAutoLimitActivationState(AlertActivation & out) const {
	if (data->AutoLimitActivationState().present()) {
		out = ConvertFromCDM::convert(data->AutoLimitActivationState().get());
		return true;
	}
	return false;
}

AlertActivation LimitAlertConditionState::getAutoLimitActivationState() const {
	return ConvertFromCDM::convert(data->AutoLimitActivationState().get());
}
	
bool LimitAlertConditionState::hasAutoLimitActivationState() const {
	return data->AutoLimitActivationState().present();
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

