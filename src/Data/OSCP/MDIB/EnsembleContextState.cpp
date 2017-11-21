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
 *  EnsembleContextState.cpp
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

#include "OSCLib/Data/OSCP/MDIB/EnsembleContextState.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/InstanceIdentifier.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"

namespace OSCLib {
namespace Data {
namespace OSCP {


EnsembleContextState::EnsembleContextState(
		HandleRef descriptorhandle
		, 
		Handle handle
) : data(Defaults::EnsembleContextStateInit(
		descriptorhandle
		,
		handle
)) {}

EnsembleContextState::operator CDM::EnsembleContextState() const {
	return *data;
}

EnsembleContextState::EnsembleContextState(const CDM::EnsembleContextState & object) : data(new CDM::EnsembleContextState(object)) {

}

EnsembleContextState::EnsembleContextState(const EnsembleContextState & object) : data(new CDM::EnsembleContextState(*object.data)) {

}

EnsembleContextState::~EnsembleContextState() {

}

void EnsembleContextState::copyFrom(const EnsembleContextState & object) {
	*data = *object.data;
}

EnsembleContextState & EnsembleContextState:: operator=(const EnsembleContextState & object) {
	copyFrom(object);
	return *this;
}


EnsembleContextState & EnsembleContextState::setStateVersion(const VersionCounter & value) {
	data->StateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool EnsembleContextState::getStateVersion(VersionCounter & out) const {
	if (data->StateVersion().present()) {
		out = ConvertFromCDM::convert(data->StateVersion().get());
		return true;
	}
	return false;
}

VersionCounter EnsembleContextState::getStateVersion() const {
	return ConvertFromCDM::convert(data->StateVersion().get());
}
	
bool EnsembleContextState::hasStateVersion() const {
	return data->StateVersion().present();
}
	
EnsembleContextState & EnsembleContextState::setDescriptorHandle(const HandleRef & value) {
	data->DescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


HandleRef EnsembleContextState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->DescriptorHandle());
}
	
EnsembleContextState & EnsembleContextState::setDescriptorVersion(const ReferencedVersion & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool EnsembleContextState::getDescriptorVersion(ReferencedVersion & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion EnsembleContextState::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}
	
bool EnsembleContextState::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}
	
EnsembleContextState & EnsembleContextState::setCategory(const CodedValue & value) {
	data->Category(ConvertToCDM::convert(value));
	return *this;
}

bool EnsembleContextState::getCategory(CodedValue & out) const {
	if (data->Category().present()) {
		out = ConvertFromCDM::convert(data->Category().get());
		return true;
	}
	return false;
}

CodedValue EnsembleContextState::getCategory() const {
	return ConvertFromCDM::convert(data->Category().get());
}
	
bool EnsembleContextState::hasCategory() const {
	return data->Category().present();
}
	
EnsembleContextState & EnsembleContextState::setHandle(const Handle & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}


Handle EnsembleContextState::getHandle() const {
	return ConvertFromCDM::convert(data->Handle());
}
	
EnsembleContextState & EnsembleContextState::setContextAssociation(const ContextAssociation & value) {
	data->ContextAssociation(ConvertToCDM::convert(value));
	return *this;
}

bool EnsembleContextState::getContextAssociation(ContextAssociation & out) const {
	if (data->ContextAssociation().present()) {
		out = ConvertFromCDM::convert(data->ContextAssociation().get());
		return true;
	}
	return false;
}

ContextAssociation EnsembleContextState::getContextAssociation() const {
	return ConvertFromCDM::convert(data->ContextAssociation().get());
}
	
bool EnsembleContextState::hasContextAssociation() const {
	return data->ContextAssociation().present();
}
	
EnsembleContextState & EnsembleContextState::setBindingMdibVersion(const ReferencedVersion & value) {
	data->BindingMdibVersion(ConvertToCDM::convert(value));
	return *this;
}

bool EnsembleContextState::getBindingMdibVersion(ReferencedVersion & out) const {
	if (data->BindingMdibVersion().present()) {
		out = ConvertFromCDM::convert(data->BindingMdibVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion EnsembleContextState::getBindingMdibVersion() const {
	return ConvertFromCDM::convert(data->BindingMdibVersion().get());
}
	
bool EnsembleContextState::hasBindingMdibVersion() const {
	return data->BindingMdibVersion().present();
}
	
EnsembleContextState & EnsembleContextState::setUnbindingMdibVersion(const ReferencedVersion & value) {
	data->UnbindingMdibVersion(ConvertToCDM::convert(value));
	return *this;
}

bool EnsembleContextState::getUnbindingMdibVersion(ReferencedVersion & out) const {
	if (data->UnbindingMdibVersion().present()) {
		out = ConvertFromCDM::convert(data->UnbindingMdibVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion EnsembleContextState::getUnbindingMdibVersion() const {
	return ConvertFromCDM::convert(data->UnbindingMdibVersion().get());
}
	
bool EnsembleContextState::hasUnbindingMdibVersion() const {
	return data->UnbindingMdibVersion().present();
}
	
EnsembleContextState & EnsembleContextState::setBindingStartTime(const Timestamp & value) {
	data->BindingStartTime(ConvertToCDM::convert(value));
	return *this;
}

bool EnsembleContextState::getBindingStartTime(Timestamp & out) const {
	if (data->BindingStartTime().present()) {
		out = ConvertFromCDM::convert(data->BindingStartTime().get());
		return true;
	}
	return false;
}

Timestamp EnsembleContextState::getBindingStartTime() const {
	return ConvertFromCDM::convert(data->BindingStartTime().get());
}
	
bool EnsembleContextState::hasBindingStartTime() const {
	return data->BindingStartTime().present();
}
	
EnsembleContextState & EnsembleContextState::setBindingEndTime(const Timestamp & value) {
	data->BindingEndTime(ConvertToCDM::convert(value));
	return *this;
}

bool EnsembleContextState::getBindingEndTime(Timestamp & out) const {
	if (data->BindingEndTime().present()) {
		out = ConvertFromCDM::convert(data->BindingEndTime().get());
		return true;
	}
	return false;
}

Timestamp EnsembleContextState::getBindingEndTime() const {
	return ConvertFromCDM::convert(data->BindingEndTime().get());
}
	
bool EnsembleContextState::hasBindingEndTime() const {
	return data->BindingEndTime().present();
}
	
EnsembleContextState & EnsembleContextState::addValidator(const InstanceIdentifier & value) {
	data->Validator().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<InstanceIdentifier> EnsembleContextState::getValidatorList() const {
	std::vector<InstanceIdentifier> result;
	result.reserve(data->Validator().size());
	for (const auto & value: data->Validator()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void EnsembleContextState::clearValidatorList() {
	data->Validator().clear();
}

EnsembleContextState & EnsembleContextState::addIdentification(const InstanceIdentifier & value) {
	data->Identification().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<InstanceIdentifier> EnsembleContextState::getIdentificationList() const {
	std::vector<InstanceIdentifier> result;
	result.reserve(data->Identification().size());
	for (const auto & value: data->Identification()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void EnsembleContextState::clearIdentificationList() {
	data->Identification().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

