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
 *  SetMetricStateOperationState.cpp
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

#include "SDCLib/Data/SDC/MDIB/SetMetricStateOperationState.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"


namespace SDCLib {
namespace Data {
namespace SDC {


SetMetricStateOperationState::SetMetricStateOperationState(
		HandleRef descriptorhandle
		,
		OperatingMode operatingmode
) : data(Defaults::SetMetricStateOperationStateInit(
		descriptorhandle
		,
		operatingmode
)) {}

SetMetricStateOperationState::operator CDM::SetMetricStateOperationState() const {
	return *data;
}

SetMetricStateOperationState::SetMetricStateOperationState(const CDM::SetMetricStateOperationState & object) : data(new CDM::SetMetricStateOperationState(object)) {

}

SetMetricStateOperationState::SetMetricStateOperationState(const SetMetricStateOperationState & object) : data(new CDM::SetMetricStateOperationState(*object.data)) {

}

SetMetricStateOperationState::~SetMetricStateOperationState() {

}

void SetMetricStateOperationState::copyFrom(const SetMetricStateOperationState & object) {
	data = std::shared_ptr<CDM::SetMetricStateOperationState>( new CDM::SetMetricStateOperationState(*object.data));
}

SetMetricStateOperationState & SetMetricStateOperationState:: operator=(const SetMetricStateOperationState & object) {
	copyFrom(object);
	return *this;
}


SetMetricStateOperationState & SetMetricStateOperationState::setStateVersion(const VersionCounter & value) {
	data->setStateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool SetMetricStateOperationState::getStateVersion(VersionCounter & out) const {
	if (data->getStateVersion().present()) {
		out = ConvertFromCDM::convert(data->getStateVersion().get());
		return true;
	}
	return false;
}

VersionCounter SetMetricStateOperationState::getStateVersion() const {
	return ConvertFromCDM::convert(data->getStateVersion().get());
}

bool SetMetricStateOperationState::hasStateVersion() const {
	return data->getStateVersion().present();
}

SetMetricStateOperationState & SetMetricStateOperationState::setDescriptorHandle(const HandleRef & value) {
	data->setDescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


HandleRef SetMetricStateOperationState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->getDescriptorHandle());
}

SetMetricStateOperationState & SetMetricStateOperationState::setDescriptorVersion(const ReferencedVersion & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool SetMetricStateOperationState::getDescriptorVersion(ReferencedVersion & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion SetMetricStateOperationState::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool SetMetricStateOperationState::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

SetMetricStateOperationState & SetMetricStateOperationState::setOperatingMode(const OperatingMode & value) {
	data->setOperatingMode(ConvertToCDM::convert(value));
	return *this;
}


OperatingMode SetMetricStateOperationState::getOperatingMode() const {
	return ConvertFromCDM::convert(data->getOperatingMode());
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

