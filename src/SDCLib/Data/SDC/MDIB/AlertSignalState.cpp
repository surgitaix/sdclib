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
 *  Author: besting, buerger, roehser
 */

/**
 * THIS FILE IS GENERATED AUTOMATICALLY! DO NOT MODIFY!
 *
 * YOUR CHANGES WILL BE OVERWRITTEN!
 *
 * USE THE DEFINITION FILES IN THE FOLDER "codegenerator" INSTEAD!
 */

#include "SDCLib/Data/SDC/MDIB/AlertSignalState.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"


namespace SDCLib {
namespace Data {
namespace SDC {


AlertSignalState::AlertSignalState(
		HandleRef descriptorhandle
		,
		AlertActivation activationstate
) : data(Defaults::AlertSignalStateInit(
		descriptorhandle
		,
		activationstate
)) {}

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
	data = std::shared_ptr<CDM::AlertSignalState>( new CDM::AlertSignalState(*object.data));
}

AlertSignalState & AlertSignalState:: operator=(const AlertSignalState & object) {
	copyFrom(object);
	return *this;
}


AlertSignalState & AlertSignalState::setStateVersion(const VersionCounter & value) {
	data->setStateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSignalState::getStateVersion(VersionCounter & out) const {
	if (data->getStateVersion().present()) {
		out = ConvertFromCDM::convert(data->getStateVersion().get());
		return true;
	}
	return false;
}

VersionCounter AlertSignalState::getStateVersion() const {
	return ConvertFromCDM::convert(data->getStateVersion().get());
}

bool AlertSignalState::hasStateVersion() const {
	return data->getStateVersion().present();
}

AlertSignalState & AlertSignalState::setDescriptorHandle(const HandleRef & value) {
	data->setDescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


HandleRef AlertSignalState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->getDescriptorHandle());
}

AlertSignalState & AlertSignalState::setDescriptorVersion(const ReferencedVersion & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSignalState::getDescriptorVersion(ReferencedVersion & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion AlertSignalState::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool AlertSignalState::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

AlertSignalState & AlertSignalState::setActivationState(const AlertActivation & value) {
	data->setActivationState(ConvertToCDM::convert(value));
	return *this;
}


AlertActivation AlertSignalState::getActivationState() const {
	return ConvertFromCDM::convert(data->getActivationState());
}

AlertSignalState & AlertSignalState::setActualSignalGenerationDelay(const xml_schema::Duration & value) {
	data->setActualSignalGenerationDelay(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSignalState::getActualSignalGenerationDelay(xml_schema::Duration & out) const {
	if (data->getActualSignalGenerationDelay().present()) {
		out = ConvertFromCDM::convert(data->getActualSignalGenerationDelay().get());
		return true;
	}
	return false;
}

xml_schema::Duration AlertSignalState::getActualSignalGenerationDelay() const {
	return ConvertFromCDM::convert(data->getActualSignalGenerationDelay().get());
}

bool AlertSignalState::hasActualSignalGenerationDelay() const {
	return data->getActualSignalGenerationDelay().present();
}

AlertSignalState & AlertSignalState::setPresence(const AlertSignalPresence & value) {
	data->setPresence(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSignalState::getPresence(AlertSignalPresence & out) const {
	if (data->getPresence().present()) {
		out = ConvertFromCDM::convert(data->getPresence().get());
		return true;
	}
	return false;
}

AlertSignalPresence AlertSignalState::getPresence() const {
	return ConvertFromCDM::convert(data->getPresence().get());
}

bool AlertSignalState::hasPresence() const {
	return data->getPresence().present();
}

AlertSignalState & AlertSignalState::setLocation(const AlertSignalPrimaryLocation & value) {
	data->setLocation(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSignalState::getLocation(AlertSignalPrimaryLocation & out) const {
	if (data->getLocation().present()) {
		out = ConvertFromCDM::convert(data->getLocation().get());
		return true;
	}
	return false;
}

AlertSignalPrimaryLocation AlertSignalState::getLocation() const {
	return ConvertFromCDM::convert(data->getLocation().get());
}

bool AlertSignalState::hasLocation() const {
	return data->getLocation().present();
}

AlertSignalState & AlertSignalState::setSlot(const unsigned int & value) {
	data->setSlot(ConvertToCDM::convert(value));
	return *this;
}

bool AlertSignalState::getSlot(unsigned int & out) const {
	if (data->getSlot().present()) {
		out = ConvertFromCDM::convert(data->getSlot().get());
		return true;
	}
	return false;
}

unsigned int AlertSignalState::getSlot() const {
	return ConvertFromCDM::convert(data->getSlot().get());
}

bool AlertSignalState::hasSlot() const {
	return data->getSlot().present();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

