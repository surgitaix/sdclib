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
 *  SetAlertStateOperationState.cpp
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

#include "SDCLib/Data/SDC/MDIB/SetAlertStateOperationState.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"


namespace SDCLib {
namespace Data {
namespace SDC {


SetAlertStateOperationState::SetAlertStateOperationState(
		HandleRef descriptorhandle
		,
		OperatingMode operatingmode
) : data(Defaults::SetAlertStateOperationStateInit(
		descriptorhandle
		,
		operatingmode
)) {}

SetAlertStateOperationState::operator CDM::SetAlertStateOperationState() const {
	return *data;
}

SetAlertStateOperationState::SetAlertStateOperationState(const CDM::SetAlertStateOperationState & object) : data(new CDM::SetAlertStateOperationState(object)) {

}

SetAlertStateOperationState::SetAlertStateOperationState(const SetAlertStateOperationState & object) : data(new CDM::SetAlertStateOperationState(*object.data)) {

}

SetAlertStateOperationState::~SetAlertStateOperationState() {

}

void SetAlertStateOperationState::copyFrom(const SetAlertStateOperationState & object) {
	data = std::shared_ptr<CDM::SetAlertStateOperationState>( new CDM::SetAlertStateOperationState(*object.data));
}

SetAlertStateOperationState & SetAlertStateOperationState:: operator=(const SetAlertStateOperationState & object) {
	copyFrom(object);
	return *this;
}


SetAlertStateOperationState & SetAlertStateOperationState::setStateVersion(const VersionCounter & value) {
	data->setStateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool SetAlertStateOperationState::getStateVersion(VersionCounter & out) const {
	if (data->getStateVersion().present()) {
		out = ConvertFromCDM::convert(data->getStateVersion().get());
		return true;
	}
	return false;
}

VersionCounter SetAlertStateOperationState::getStateVersion() const {
	return ConvertFromCDM::convert(data->getStateVersion().get());
}

bool SetAlertStateOperationState::hasStateVersion() const {
	return data->getStateVersion().present();
}

SetAlertStateOperationState & SetAlertStateOperationState::setDescriptorHandle(const HandleRef & value) {
	data->setDescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


HandleRef SetAlertStateOperationState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->getDescriptorHandle());
}

SetAlertStateOperationState & SetAlertStateOperationState::setDescriptorVersion(const ReferencedVersion & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool SetAlertStateOperationState::getDescriptorVersion(ReferencedVersion & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion SetAlertStateOperationState::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool SetAlertStateOperationState::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

SetAlertStateOperationState & SetAlertStateOperationState::setOperatingMode(const OperatingMode & value) {
	data->setOperatingMode(ConvertToCDM::convert(value));
	return *this;
}


OperatingMode SetAlertStateOperationState::getOperatingMode() const {
	return ConvertFromCDM::convert(data->getOperatingMode());
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

