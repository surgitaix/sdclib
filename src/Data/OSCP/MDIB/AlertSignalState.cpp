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
 *  AlertSignalState.cpp
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

#include "OSCLib/Data/OSCP/MDIB/AlertSignalState.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/VersionCounter.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

AlertSignalState::AlertSignalState() : data(Defaults::AlertSignalState()) {
}

AlertSignalState::operator CDM::AlertSignalState() const {
	return *data;
}

AlertSignalState::AlertSignalState(const CDM::AlertSignalState & object) : data(new CDM::AlertSignalState(object)) {

}

AlertSignalState::AlertSignalState(const AlertSignalState & object) : data(new CDM::AlertSignalState(*object.data)) {

}

AlertSignalState::~AlertSignalState() {

}

void AlertSignalState::copyFrom(const AlertSignalState & object) {
	*data = *object.data;
}

AlertSignalState & AlertSignalState:: operator=(const AlertSignalState & object) {
	copyFrom(object);
	return *this;
}


AlertSignalState & AlertSignalState::setHandle(const std::string & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSignalState::getHandle(std::string & out) const {
	if (data->Handle().present()) {
		out = ConvertFromCDM::convert(data->Handle().get());
		return true;
	}
	return false;
}

std::string AlertSignalState::getHandle() const {
	return ConvertFromCDM::convert(data->Handle().get());
}
	
bool AlertSignalState::hasHandle() const {
	return data->Handle().present();
}
	
AlertSignalState & AlertSignalState::setDescriptorHandle(const std::string & value) {
	data->DescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


std::string AlertSignalState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->DescriptorHandle());
}
	
AlertSignalState & AlertSignalState::setStateVersion(const VersionCounter & value) {
	data->StateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSignalState::getStateVersion(VersionCounter & out) const {
	if (data->StateVersion().present()) {
		out = ConvertFromCDM::convert(data->StateVersion().get());
		return true;
	}
	return false;
}

VersionCounter AlertSignalState::getStateVersion() const {
	return ConvertFromCDM::convert(data->StateVersion().get());
}
	
bool AlertSignalState::hasStateVersion() const {
	return data->StateVersion().present();
}
	
AlertSignalState & AlertSignalState::setActivationState(const AlertActivation & value) {
	data->ActivationState(ConvertToCDM::convert(value));
	return *this;
}


AlertActivation AlertSignalState::getActivationState() const {
	return ConvertFromCDM::convert(data->ActivationState());
}
	
AlertSignalState & AlertSignalState::setLocation(const AlertSignalPrimaryLocation & value) {
	data->Location(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSignalState::getLocation(AlertSignalPrimaryLocation & out) const {
	if (data->Location().present()) {
		out = ConvertFromCDM::convert(data->Location().get());
		return true;
	}
	return false;
}

AlertSignalPrimaryLocation AlertSignalState::getLocation() const {
	return ConvertFromCDM::convert(data->Location().get());
}
	
bool AlertSignalState::hasLocation() const {
	return data->Location().present();
}
	
AlertSignalState & AlertSignalState::setSlot(const int & value) {
	data->Slot(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSignalState::getSlot(int & out) const {
	if (data->Slot().present()) {
		out = ConvertFromCDM::convert(data->Slot().get());
		return true;
	}
	return false;
}

int AlertSignalState::getSlot() const {
	return ConvertFromCDM::convert(data->Slot().get());
}
	
bool AlertSignalState::hasSlot() const {
	return data->Slot().present();
}
	
AlertSignalState & AlertSignalState::setPresence(const AlertSignalPresence & value) {
	data->Presence(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSignalState::getPresence(AlertSignalPresence & out) const {
	if (data->Presence().present()) {
		out = ConvertFromCDM::convert(data->Presence().get());
		return true;
	}
	return false;
}

AlertSignalPresence AlertSignalState::getPresence() const {
	return ConvertFromCDM::convert(data->Presence().get());
}
	
bool AlertSignalState::hasPresence() const {
	return data->Presence().present();
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

