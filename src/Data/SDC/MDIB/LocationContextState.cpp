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
 *  Author: besting, buerger, roehser
 */
 
/**
 * THIS FILE IS GENERATED AUTOMATICALLY! DO NOT MODIFY!
 *
 * YOUR CHANGES WILL BE OVERWRITTEN!
 * 
 * USE THE DEFINITION FILES IN THE FOLDER "codegenerator" INSTEAD!
 */

#include "OSCLib/Data/SDC/MDIB/LocationContextState.h"
#include "OSCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/SDC/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/SDC/MDIB/LocationDetail.h"
#include "OSCLib/Data/SDC/MDIB/InstanceIdentifier.h"
#include "OSCLib/Data/SDC/MDIB/CodedValue.h"

namespace SDCLib {
namespace Data {
namespace SDC {


LocationContextState::LocationContextState(
		HandleRef descriptorhandle
		, 
		Handle handle
) : data(Defaults::LocationContextStateInit(
		descriptorhandle
		,
		handle
)) {}

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
	data = std::shared_ptr<CDM::LocationContextState>( new CDM::LocationContextState(*object.data));
}

LocationContextState & LocationContextState:: operator=(const LocationContextState & object) {
	copyFrom(object);
	return *this;
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
	
LocationContextState & LocationContextState::setDescriptorHandle(const HandleRef & value) {
	data->DescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


HandleRef LocationContextState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->DescriptorHandle());
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
	
LocationContextState & LocationContextState::setCategory(const CodedValue & value) {
	data->Category(ConvertToCDM::convert(value));
	return *this;
}

bool LocationContextState::getCategory(CodedValue & out) const {
	if (data->Category().present()) {
		out = ConvertFromCDM::convert(data->Category().get());
		return true;
	}
	return false;
}

CodedValue LocationContextState::getCategory() const {
	return ConvertFromCDM::convert(data->Category().get());
}
	
bool LocationContextState::hasCategory() const {
	return data->Category().present();
}
	
LocationContextState & LocationContextState::setHandle(const Handle & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}


Handle LocationContextState::getHandle() const {
	return ConvertFromCDM::convert(data->Handle());
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
	
LocationContextState & LocationContextState::setBindingMdibVersion(const ReferencedVersion & value) {
	data->BindingMdibVersion(ConvertToCDM::convert(value));
	return *this;
}

bool LocationContextState::getBindingMdibVersion(ReferencedVersion & out) const {
	if (data->BindingMdibVersion().present()) {
		out = ConvertFromCDM::convert(data->BindingMdibVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion LocationContextState::getBindingMdibVersion() const {
	return ConvertFromCDM::convert(data->BindingMdibVersion().get());
}
	
bool LocationContextState::hasBindingMdibVersion() const {
	return data->BindingMdibVersion().present();
}
	
LocationContextState & LocationContextState::setUnbindingMdibVersion(const ReferencedVersion & value) {
	data->UnbindingMdibVersion(ConvertToCDM::convert(value));
	return *this;
}

bool LocationContextState::getUnbindingMdibVersion(ReferencedVersion & out) const {
	if (data->UnbindingMdibVersion().present()) {
		out = ConvertFromCDM::convert(data->UnbindingMdibVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion LocationContextState::getUnbindingMdibVersion() const {
	return ConvertFromCDM::convert(data->UnbindingMdibVersion().get());
}
	
bool LocationContextState::hasUnbindingMdibVersion() const {
	return data->UnbindingMdibVersion().present();
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

std::vector<InstanceIdentifier> LocationContextState::getValidatorList() const {
	std::vector<InstanceIdentifier> result;
	result.reserve(data->Validator().size());
	for (const auto & value: data->Validator()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void LocationContextState::clearValidatorList() {
	data->Validator().clear();
}

LocationContextState & LocationContextState::addIdentification(const InstanceIdentifier & value) {
	data->Identification().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<InstanceIdentifier> LocationContextState::getIdentificationList() const {
	std::vector<InstanceIdentifier> result;
	result.reserve(data->Identification().size());
	for (const auto & value: data->Identification()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void LocationContextState::clearIdentificationList() {
	data->Identification().clear();
}

LocationContextState & LocationContextState::setLocationDetail(const LocationDetail & value) {
	data->LocationDetail(ConvertToCDM::convert(value));
	return *this;
}

bool LocationContextState::getLocationDetail(LocationDetail & out) const {
	if (data->LocationDetail().present()) {
		out = ConvertFromCDM::convert(data->LocationDetail().get());
		return true;
	}
	return false;
}

LocationDetail LocationContextState::getLocationDetail() const {
	return ConvertFromCDM::convert(data->LocationDetail().get());
}
	
bool LocationContextState::hasLocationDetail() const {
	return data->LocationDetail().present();
}
	

} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

