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
 *  SetComponentStateOperationState.cpp
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

#include "SDCLib/Data/SDC/MDIB/SetComponentStateOperationState.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"


namespace SDCLib {
namespace Data {
namespace SDC {


SetComponentStateOperationState::SetComponentStateOperationState(
		HandleRef descriptorhandle
		,
		OperatingMode operatingmode
) : data(Defaults::SetComponentStateOperationStateInit(
		descriptorhandle
		,
		operatingmode
))
{}

SetComponentStateOperationState::operator CDM::SetComponentStateOperationState() const {
	return *data;
}

SetComponentStateOperationState::SetComponentStateOperationState(const CDM::SetComponentStateOperationState & object)
: data(new CDM::SetComponentStateOperationState(object))
{ }

SetComponentStateOperationState::SetComponentStateOperationState(const SetComponentStateOperationState & object)
: data(std::make_shared<CDM::SetComponentStateOperationState>(*object.data))
{ }

void SetComponentStateOperationState::copyFrom(const SetComponentStateOperationState & object) {
	data = std::make_shared<CDM::SetComponentStateOperationState>(*object.data);
}

SetComponentStateOperationState & SetComponentStateOperationState:: operator=(const SetComponentStateOperationState& object) {
	copyFrom(object);
	return *this;
}


SetComponentStateOperationState & SetComponentStateOperationState::setStateVersion(const VersionCounter & value) {
	data->setStateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool SetComponentStateOperationState::getStateVersion(VersionCounter & out) const {
	if (data->getStateVersion().present()) {
		out = ConvertFromCDM::convert(data->getStateVersion().get());
		return true;
	}
	return false;
}

VersionCounter SetComponentStateOperationState::getStateVersion() const {
	return ConvertFromCDM::convert(data->getStateVersion().get());
}

bool SetComponentStateOperationState::hasStateVersion() const {
	return data->getStateVersion().present();
}

SetComponentStateOperationState & SetComponentStateOperationState::setDescriptorHandle(const HandleRef & value) {
	data->setDescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


HandleRef SetComponentStateOperationState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->getDescriptorHandle());
}

SetComponentStateOperationState & SetComponentStateOperationState::setDescriptorVersion(const ReferencedVersion & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool SetComponentStateOperationState::getDescriptorVersion(ReferencedVersion & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion SetComponentStateOperationState::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool SetComponentStateOperationState::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

SetComponentStateOperationState & SetComponentStateOperationState::setOperatingMode(const OperatingMode & value) {
	data->setOperatingMode(ConvertToCDM::convert(value));
	return *this;
}


OperatingMode SetComponentStateOperationState::getOperatingMode() const {
	return ConvertFromCDM::convert(data->getOperatingMode());
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

