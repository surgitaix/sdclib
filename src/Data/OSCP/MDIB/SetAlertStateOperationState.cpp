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
 *  Author: besting, roehser
 */
 
/**
 * THIS FILE IS GENERATED AUTOMATICALLY! DO NOT MODIFY!
 *
 * YOUR CHANGES WILL BE OVERWRITTEN!
 * 
 * USE THE DEFINITION FILES IN THE FOLDER "codegenerator" INSTEAD!
 */

#include "OSCLib/Data/OSCP/MDIB/SetAlertStateOperationState.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/ReferencedVersion.h"
#include "OSCLib/Data/OSCP/MDIB/VersionCounter.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

SetAlertStateOperationState::SetAlertStateOperationState() : data(Defaults::SetAlertStateOperationState()) {
}

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
	*data = *object.data;
}

SetAlertStateOperationState & SetAlertStateOperationState:: operator=(const SetAlertStateOperationState & object) {
	copyFrom(object);
	return *this;
}


SetAlertStateOperationState & SetAlertStateOperationState::setDescriptorVersion(const ReferencedVersion & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool SetAlertStateOperationState::getDescriptorVersion(ReferencedVersion & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion SetAlertStateOperationState::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}
	
bool SetAlertStateOperationState::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}
	
SetAlertStateOperationState & SetAlertStateOperationState::setDescriptorHandle(const std::string & value) {
	data->DescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


std::string SetAlertStateOperationState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->DescriptorHandle());
}
	
SetAlertStateOperationState & SetAlertStateOperationState::setStateVersion(const VersionCounter & value) {
	data->StateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool SetAlertStateOperationState::getStateVersion(VersionCounter & out) const {
	if (data->StateVersion().present()) {
		out = ConvertFromCDM::convert(data->StateVersion().get());
		return true;
	}
	return false;
}

VersionCounter SetAlertStateOperationState::getStateVersion() const {
	return ConvertFromCDM::convert(data->StateVersion().get());
}
	
bool SetAlertStateOperationState::hasStateVersion() const {
	return data->StateVersion().present();
}
	
SetAlertStateOperationState & SetAlertStateOperationState::setOperatingMode(const OperatingMode & value) {
	data->OperatingMode(ConvertToCDM::convert(value));
	return *this;
}


OperatingMode SetAlertStateOperationState::getOperatingMode() const {
	return ConvertFromCDM::convert(data->OperatingMode());
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

