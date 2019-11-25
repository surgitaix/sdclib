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
 *  SetContextStateOperationState.cpp
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

#include "SDCLib/Data/SDC/MDIB/SetContextStateOperationState.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"


namespace SDCLib {
namespace Data {
namespace SDC {


SetContextStateOperationState::SetContextStateOperationState(
		HandleRef descriptorhandle
		,
		OperatingMode operatingmode
) : data(Defaults::SetContextStateOperationStateInit(
		descriptorhandle
		,
		operatingmode
)) {}

SetContextStateOperationState::operator CDM::SetContextStateOperationState() const {
	return *data;
}

SetContextStateOperationState::SetContextStateOperationState(const CDM::SetContextStateOperationState & object) : data(new CDM::SetContextStateOperationState(object)) {

}

SetContextStateOperationState::SetContextStateOperationState(const SetContextStateOperationState & object) : data(new CDM::SetContextStateOperationState(*object.data)) {

}

SetContextStateOperationState::~SetContextStateOperationState() {

}

void SetContextStateOperationState::copyFrom(const SetContextStateOperationState & object) {
	data = std::shared_ptr<CDM::SetContextStateOperationState>( new CDM::SetContextStateOperationState(*object.data));
}

SetContextStateOperationState & SetContextStateOperationState:: operator=(const SetContextStateOperationState & object) {
	copyFrom(object);
	return *this;
}


SetContextStateOperationState & SetContextStateOperationState::setStateVersion(const VersionCounter & value) {
	data->setStateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool SetContextStateOperationState::getStateVersion(VersionCounter & out) const {
	if (data->getStateVersion().present()) {
		out = ConvertFromCDM::convert(data->getStateVersion().get());
		return true;
	}
	return false;
}

VersionCounter SetContextStateOperationState::getStateVersion() const {
	return ConvertFromCDM::convert(data->getStateVersion().get());
}

bool SetContextStateOperationState::hasStateVersion() const {
	return data->getStateVersion().present();
}

SetContextStateOperationState & SetContextStateOperationState::setDescriptorHandle(const HandleRef & value) {
	data->setDescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


HandleRef SetContextStateOperationState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->getDescriptorHandle());
}

SetContextStateOperationState & SetContextStateOperationState::setDescriptorVersion(const ReferencedVersion & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool SetContextStateOperationState::getDescriptorVersion(ReferencedVersion & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion SetContextStateOperationState::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool SetContextStateOperationState::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

SetContextStateOperationState & SetContextStateOperationState::setOperatingMode(const OperatingMode & value) {
	data->setOperatingMode(ConvertToCDM::convert(value));
	return *this;
}


OperatingMode SetContextStateOperationState::getOperatingMode() const {
	return ConvertFromCDM::convert(data->getOperatingMode());
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

