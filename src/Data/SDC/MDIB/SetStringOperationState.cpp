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
 *  SetStringOperationState.cpp
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

#include "OSCLib/Data/SDC/MDIB/SetStringOperationState.h"
#include "OSCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/SDC/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/SDC/MDIB/AllowedValues.h"

namespace OSCLib {
namespace Data {
namespace SDC {


SetStringOperationState::SetStringOperationState(
		HandleRef descriptorhandle
		, 
		OperatingMode operatingmode
) : data(Defaults::SetStringOperationStateInit(
		descriptorhandle
		,
		operatingmode
)) {}

SetStringOperationState::operator CDM::SetStringOperationState() const {
	return *data;
}

SetStringOperationState::SetStringOperationState(const CDM::SetStringOperationState & object) : data(new CDM::SetStringOperationState(object)) {

}

SetStringOperationState::SetStringOperationState(const SetStringOperationState & object) : data(new CDM::SetStringOperationState(*object.data)) {

}

SetStringOperationState::~SetStringOperationState() {

}

void SetStringOperationState::copyFrom(const SetStringOperationState & object) {
	data = std::shared_ptr<CDM::SetStringOperationState>( new CDM::SetStringOperationState(*object.data));
}

SetStringOperationState & SetStringOperationState:: operator=(const SetStringOperationState & object) {
	copyFrom(object);
	return *this;
}


SetStringOperationState & SetStringOperationState::setStateVersion(const VersionCounter & value) {
	data->StateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool SetStringOperationState::getStateVersion(VersionCounter & out) const {
	if (data->StateVersion().present()) {
		out = ConvertFromCDM::convert(data->StateVersion().get());
		return true;
	}
	return false;
}

VersionCounter SetStringOperationState::getStateVersion() const {
	return ConvertFromCDM::convert(data->StateVersion().get());
}
	
bool SetStringOperationState::hasStateVersion() const {
	return data->StateVersion().present();
}
	
SetStringOperationState & SetStringOperationState::setDescriptorHandle(const HandleRef & value) {
	data->DescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


HandleRef SetStringOperationState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->DescriptorHandle());
}
	
SetStringOperationState & SetStringOperationState::setDescriptorVersion(const ReferencedVersion & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool SetStringOperationState::getDescriptorVersion(ReferencedVersion & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion SetStringOperationState::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}
	
bool SetStringOperationState::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}
	
SetStringOperationState & SetStringOperationState::setOperatingMode(const OperatingMode & value) {
	data->OperatingMode(ConvertToCDM::convert(value));
	return *this;
}


OperatingMode SetStringOperationState::getOperatingMode() const {
	return ConvertFromCDM::convert(data->OperatingMode());
}
	
SetStringOperationState & SetStringOperationState::setAllowedValues(const AllowedValues & value) {
	data->AllowedValues(ConvertToCDM::convert(value));
	return *this;
}

bool SetStringOperationState::getAllowedValues(AllowedValues & out) const {
	if (data->AllowedValues().present()) {
		out = ConvertFromCDM::convert(data->AllowedValues().get());
		return true;
	}
	return false;
}

AllowedValues SetStringOperationState::getAllowedValues() const {
	return ConvertFromCDM::convert(data->AllowedValues().get());
}
	
bool SetStringOperationState::hasAllowedValues() const {
	return data->AllowedValues().present();
}
	

} /* namespace SDC */
} /* namespace Data */
} /* namespace OSCLib */

