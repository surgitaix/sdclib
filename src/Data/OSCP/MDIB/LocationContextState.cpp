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
 *  LocationContextState.cpp
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

#include "OSCLib/Data/OSCP/MDIB/LocationContextState.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/InstanceIdentifier.h"
#include "OSCLib/Data/OSCP/MDIB/ReferencedVersion.h"
#include "OSCLib/Data/OSCP/MDIB/Timestamp.h"
#include "OSCLib/Data/OSCP/MDIB/InstanceIdentifier.h"
#include "OSCLib/Data/OSCP/MDIB/ReferencedVersion.h"
#include "OSCLib/Data/OSCP/MDIB/ReferencedVersion.h"
#include "OSCLib/Data/OSCP/MDIB/VersionCounter.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

LocationContextState::LocationContextState() : data(Defaults::LocationContextState()) {
}

LocationContextState::operator CDM::LocationContextState() const {
	return *data;
}

LocationContextState::LocationContextState(const CDM::LocationContextState & object) : data(new CDM::LocationContextState(object)) {

}

LocationContextState::LocationContextState(const LocationContextState & object) : data(new CDM::LocationContextState(*object.data)) {

}

LocationContextState::~LocationContextState() {

}

void LocationContextState::copyFrom(const LocationContextState & object) {
	*data = *object.data;
}

LocationContextState & LocationContextState:: operator=(const LocationContextState & object) {
	copyFrom(object);
	return *this;
}


LocationContextState & LocationContextState::setDescriptorVersion(const ReferencedVersion & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool LocationContextState::getDescriptorVersion(ReferencedVersion & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion LocationContextState::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}
	
bool LocationContextState::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}
	
LocationContextState & LocationContextState::setDescriptorHandle(const std::string & value) {
	data->DescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


std::string LocationContextState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->DescriptorHandle());
}
	
LocationContextState & LocationContextState::setStateVersion(const VersionCounter & value) {
	data->StateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool LocationContextState::getStateVersion(VersionCounter & out) const {
	if (data->StateVersion().present()) {
		out = ConvertFromCDM::convert(data->StateVersion().get());
		return true;
	}
	return false;
}

VersionCounter LocationContextState::getStateVersion() const {
	return ConvertFromCDM::convert(data->StateVersion().get());
}
	
bool LocationContextState::hasStateVersion() const {
	return data->StateVersion().present();
}
	
LocationContextState & LocationContextState::setContextAssociation(const ContextAssociation & value) {
	data->ContextAssociation(ConvertToCDM::convert(value));
	return *this;
}

bool LocationContextState::getContextAssociation(ContextAssociation & out) const {
	if (data->ContextAssociation().present()) {
		out = ConvertFromCDM::convert(data->ContextAssociation().get());
		return true;
	}
	return false;
}

ContextAssociation LocationContextState::getContextAssociation() const {
	return ConvertFromCDM::convert(data->ContextAssociation().get());
}
	
bool LocationContextState::hasContextAssociation() const {
	return data->ContextAssociation().present();
}
	
LocationContextState & LocationContextState::setBindingMDIBVersion(const ReferencedVersion & value) {
	data->BindingMDIBVersion(ConvertToCDM::convert(value));
	return *this;
}


ReferencedVersion LocationContextState::getBindingMDIBVersion() const {
	return ConvertFromCDM::convert(data->BindingMDIBVersion());
}
	
LocationContextState & LocationContextState::setUnbindingMDIBVersion(const ReferencedVersion & value) {
	data->UnbindingMDIBVersion(ConvertToCDM::convert(value));
	return *this;
}

bool LocationContextState::getUnbindingMDIBVersion(ReferencedVersion & out) const {
	if (data->UnbindingMDIBVersion().present()) {
		out = ConvertFromCDM::convert(data->UnbindingMDIBVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion LocationContextState::getUnbindingMDIBVersion() const {
	return ConvertFromCDM::convert(data->UnbindingMDIBVersion().get());
}
	
bool LocationContextState::hasUnbindingMDIBVersion() const {
	return data->UnbindingMDIBVersion().present();
}
	
LocationContextState & LocationContextState::setBindingStartTime(const Timestamp & value) {
	data->BindingStartTime(ConvertToCDM::convert(value));
	return *this;
}

bool LocationContextState::getBindingStartTime(Timestamp & out) const {
	if (data->BindingStartTime().present()) {
		out = ConvertFromCDM::convert(data->BindingStartTime().get());
		return true;
	}
	return false;
}

Timestamp LocationContextState::getBindingStartTime() const {
	return ConvertFromCDM::convert(data->BindingStartTime().get());
}
	
bool LocationContextState::hasBindingStartTime() const {
	return data->BindingStartTime().present();
}
	
LocationContextState & LocationContextState::setBindingEndTime(const Timestamp & value) {
	data->BindingEndTime(ConvertToCDM::convert(value));
	return *this;
}

bool LocationContextState::getBindingEndTime(Timestamp & out) const {
	if (data->BindingEndTime().present()) {
		out = ConvertFromCDM::convert(data->BindingEndTime().get());
		return true;
	}
	return false;
}

Timestamp LocationContextState::getBindingEndTime() const {
	return ConvertFromCDM::convert(data->BindingEndTime().get());
}
	
bool LocationContextState::hasBindingEndTime() const {
	return data->BindingEndTime().present();
}
	
LocationContextState & LocationContextState::addValidator(const InstanceIdentifier & value) {
	data->Validator().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<InstanceIdentifier> LocationContextState::getValidators() const {
	std::vector<InstanceIdentifier> result;
	result.reserve(data->Validator().size());
	for (const auto & value: data->Validator()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void LocationContextState::clearValidators() {
	data->Validator().clear();
}

LocationContextState & LocationContextState::addIdentification(const InstanceIdentifier & value) {
	data->Identification().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<InstanceIdentifier> LocationContextState::getIdentifications() const {
	std::vector<InstanceIdentifier> result;
	result.reserve(data->Identification().size());
	for (const auto & value: data->Identification()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void LocationContextState::clearIdentifications() {
	data->Identification().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

