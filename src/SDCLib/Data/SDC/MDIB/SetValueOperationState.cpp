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
 *  SetValueOperationState.cpp
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

#include "SDCLib/Data/SDC/MDIB/SetValueOperationState.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/Range.h"

namespace SDCLib {
namespace Data {
namespace SDC {


SetValueOperationState::SetValueOperationState(
		HandleRef descriptorhandle
		,
		OperatingMode operatingmode
) : data(Defaults::SetValueOperationStateInit(
		descriptorhandle
		,
		operatingmode
)) {}

SetValueOperationState::operator CDM::SetValueOperationState() const {
	return *data;
}

SetValueOperationState::SetValueOperationState(const CDM::SetValueOperationState & object) : data(new CDM::SetValueOperationState(object)) {

}

SetValueOperationState::SetValueOperationState(const SetValueOperationState & object) : data(new CDM::SetValueOperationState(*object.data)) {

}

SetValueOperationState::~SetValueOperationState() {

}

void SetValueOperationState::copyFrom(const SetValueOperationState & object) {
	data = std::shared_ptr<CDM::SetValueOperationState>( new CDM::SetValueOperationState(*object.data));
}

SetValueOperationState & SetValueOperationState:: operator=(const SetValueOperationState & object) {
	copyFrom(object);
	return *this;
}


SetValueOperationState & SetValueOperationState::setStateVersion(const VersionCounter & value) {
	data->setStateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool SetValueOperationState::getStateVersion(VersionCounter & out) const {
	if (data->getStateVersion().present()) {
		out = ConvertFromCDM::convert(data->getStateVersion().get());
		return true;
	}
	return false;
}

VersionCounter SetValueOperationState::getStateVersion() const {
	return ConvertFromCDM::convert(data->getStateVersion().get());
}

bool SetValueOperationState::hasStateVersion() const {
	return data->getStateVersion().present();
}

SetValueOperationState & SetValueOperationState::setDescriptorHandle(const HandleRef & value) {
	data->setDescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


HandleRef SetValueOperationState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->getDescriptorHandle());
}

SetValueOperationState & SetValueOperationState::setDescriptorVersion(const ReferencedVersion & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool SetValueOperationState::getDescriptorVersion(ReferencedVersion & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion SetValueOperationState::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool SetValueOperationState::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

SetValueOperationState & SetValueOperationState::setOperatingMode(const OperatingMode & value) {
	data->setOperatingMode(ConvertToCDM::convert(value));
	return *this;
}


OperatingMode SetValueOperationState::getOperatingMode() const {
	return ConvertFromCDM::convert(data->getOperatingMode());
}

SetValueOperationState & SetValueOperationState::addAllowedRange(const Range & value) {
	data->getAllowedRange().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<Range> SetValueOperationState::getAllowedRangeList() const {
	std::vector<Range> result;
	result.reserve(data->getAllowedRange().size());
	for (const auto & value: data->getAllowedRange()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void SetValueOperationState::clearAllowedRangeList() {
	data->getAllowedRange().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

