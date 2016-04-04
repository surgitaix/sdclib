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
 *  AlertConditionState.cpp
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

#include "OSCLib/Data/OSCP/MDIB/AlertConditionState.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/Timestamp.h"
#include "OSCLib/Data/OSCP/MDIB/VersionCounter.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

AlertConditionState::AlertConditionState() : data(Defaults::AlertConditionState()) {
}

AlertConditionState::operator CDM::AlertConditionState() const {
	return *data;
}

AlertConditionState::AlertConditionState(const CDM::AlertConditionState & object) : data(new CDM::AlertConditionState(object)) {

}

AlertConditionState::AlertConditionState(const AlertConditionState & object) : data(new CDM::AlertConditionState(*object.data)) {

}

AlertConditionState::~AlertConditionState() {

}

void AlertConditionState::copyFrom(const AlertConditionState & object) {
	*data = *object.data;
}

AlertConditionState & AlertConditionState:: operator=(const AlertConditionState & object) {
	copyFrom(object);
	return *this;
}


AlertConditionState & AlertConditionState::setHandle(const std::string & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}

bool AlertConditionState::getHandle(std::string & out) const {
	if (data->Handle().present()) {
		out = ConvertFromCDM::convert(data->Handle().get());
		return true;
	}
	return false;
}

std::string AlertConditionState::getHandle() const {
	return ConvertFromCDM::convert(data->Handle().get());
}
	
bool AlertConditionState::hasHandle() const {
	return data->Handle().present();
}
	
AlertConditionState & AlertConditionState::setDescriptorHandle(const std::string & value) {
	data->DescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


std::string AlertConditionState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->DescriptorHandle());
}
	
AlertConditionState & AlertConditionState::setStateVersion(const VersionCounter & value) {
	data->StateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool AlertConditionState::getStateVersion(VersionCounter & out) const {
	if (data->StateVersion().present()) {
		out = ConvertFromCDM::convert(data->StateVersion().get());
		return true;
	}
	return false;
}

VersionCounter AlertConditionState::getStateVersion() const {
	return ConvertFromCDM::convert(data->StateVersion().get());
}
	
bool AlertConditionState::hasStateVersion() const {
	return data->StateVersion().present();
}
	
AlertConditionState & AlertConditionState::setActivationState(const PausableActivation & value) {
	data->ActivationState(ConvertToCDM::convert(value));
	return *this;
}


PausableActivation AlertConditionState::getActivationState() const {
	return ConvertFromCDM::convert(data->ActivationState());
}
	
AlertConditionState & AlertConditionState::setRank(const int & value) {
	data->Rank(ConvertToCDM::convert(value));
	return *this;
}

bool AlertConditionState::getRank(int & out) const {
	if (data->Rank().present()) {
		out = ConvertFromCDM::convert(data->Rank().get());
		return true;
	}
	return false;
}

int AlertConditionState::getRank() const {
	return ConvertFromCDM::convert(data->Rank().get());
}
	
bool AlertConditionState::hasRank() const {
	return data->Rank().present();
}
	
AlertConditionState & AlertConditionState::setPresence(const bool & value) {
	data->Presence(ConvertToCDM::convert(value));
	return *this;
}


bool AlertConditionState::getPresence() const {
	return ConvertFromCDM::convert(data->Presence());
}
	
AlertConditionState & AlertConditionState::setObservationTime(const Timestamp & value) {
	data->ObservationTime(ConvertToCDM::convert(value));
	return *this;
}

bool AlertConditionState::getObservationTime(Timestamp & out) const {
	if (data->ObservationTime().present()) {
		out = ConvertFromCDM::convert(data->ObservationTime().get());
		return true;
	}
	return false;
}

Timestamp AlertConditionState::getObservationTime() const {
	return ConvertFromCDM::convert(data->ObservationTime().get());
}
	
bool AlertConditionState::hasObservationTime() const {
	return data->ObservationTime().present();
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

