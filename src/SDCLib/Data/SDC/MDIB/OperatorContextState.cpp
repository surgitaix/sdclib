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
 *  OperatorContextState.cpp
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

#include "SDCLib/Data/SDC/MDIB/OperatorContextState.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/BaseDemographics.h"
#include "SDCLib/Data/SDC/MDIB/InstanceIdentifier.h"
#include "SDCLib/Data/SDC/MDIB/CodedValue.h"

namespace SDCLib {
namespace Data {
namespace SDC {


OperatorContextState::OperatorContextState(
		HandleRef descriptorhandle
		,
		Handle handle
) : data(Defaults::OperatorContextStateInit(
		descriptorhandle
		,
		handle
)) {}

OperatorContextState::operator CDM::OperatorContextState() const {
	return *data;
}

OperatorContextState::OperatorContextState(const CDM::OperatorContextState & object) : data(new CDM::OperatorContextState(object)) {

}

OperatorContextState::OperatorContextState(const OperatorContextState & object) : data(new CDM::OperatorContextState(*object.data)) {

}

OperatorContextState::~OperatorContextState() {

}

void OperatorContextState::copyFrom(const OperatorContextState & object) {
	data = std::shared_ptr<CDM::OperatorContextState>( new CDM::OperatorContextState(*object.data));
}

OperatorContextState & OperatorContextState:: operator=(const OperatorContextState & object) {
	copyFrom(object);
	return *this;
}


OperatorContextState & OperatorContextState::setStateVersion(const VersionCounter & value) {
	data->StateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool OperatorContextState::getStateVersion(VersionCounter & out) const {
	if (data->StateVersion().present()) {
		out = ConvertFromCDM::convert(data->StateVersion().get());
		return true;
	}
	return false;
}

VersionCounter OperatorContextState::getStateVersion() const {
	return ConvertFromCDM::convert(data->StateVersion().get());
}

bool OperatorContextState::hasStateVersion() const {
	return data->StateVersion().present();
}

OperatorContextState & OperatorContextState::setDescriptorHandle(const HandleRef & value) {
	data->DescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


HandleRef OperatorContextState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->DescriptorHandle());
}

OperatorContextState & OperatorContextState::setDescriptorVersion(const ReferencedVersion & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool OperatorContextState::getDescriptorVersion(ReferencedVersion & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion OperatorContextState::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}

bool OperatorContextState::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}

OperatorContextState & OperatorContextState::setCategory(const CodedValue & value) {
	data->Category(ConvertToCDM::convert(value));
	return *this;
}

bool OperatorContextState::getCategory(CodedValue & out) const {
	if (data->Category().present()) {
		out = ConvertFromCDM::convert(data->Category().get());
		return true;
	}
	return false;
}

CodedValue OperatorContextState::getCategory() const {
	return ConvertFromCDM::convert(data->Category().get());
}

bool OperatorContextState::hasCategory() const {
	return data->Category().present();
}

OperatorContextState & OperatorContextState::setHandle(const Handle & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}


Handle OperatorContextState::getHandle() const {
	return ConvertFromCDM::convert(data->Handle());
}

OperatorContextState & OperatorContextState::setContextAssociation(const ContextAssociation & value) {
	data->ContextAssociation(ConvertToCDM::convert(value));
	return *this;
}

bool OperatorContextState::getContextAssociation(ContextAssociation & out) const {
	if (data->ContextAssociation().present()) {
		out = ConvertFromCDM::convert(data->ContextAssociation().get());
		return true;
	}
	return false;
}

ContextAssociation OperatorContextState::getContextAssociation() const {
	return ConvertFromCDM::convert(data->ContextAssociation().get());
}

bool OperatorContextState::hasContextAssociation() const {
	return data->ContextAssociation().present();
}

OperatorContextState & OperatorContextState::setBindingMdibVersion(const ReferencedVersion & value) {
	data->BindingMdibVersion(ConvertToCDM::convert(value));
	return *this;
}

bool OperatorContextState::getBindingMdibVersion(ReferencedVersion & out) const {
	if (data->BindingMdibVersion().present()) {
		out = ConvertFromCDM::convert(data->BindingMdibVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion OperatorContextState::getBindingMdibVersion() const {
	return ConvertFromCDM::convert(data->BindingMdibVersion().get());
}

bool OperatorContextState::hasBindingMdibVersion() const {
	return data->BindingMdibVersion().present();
}

OperatorContextState & OperatorContextState::setUnbindingMdibVersion(const ReferencedVersion & value) {
	data->UnbindingMdibVersion(ConvertToCDM::convert(value));
	return *this;
}

bool OperatorContextState::getUnbindingMdibVersion(ReferencedVersion & out) const {
	if (data->UnbindingMdibVersion().present()) {
		out = ConvertFromCDM::convert(data->UnbindingMdibVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion OperatorContextState::getUnbindingMdibVersion() const {
	return ConvertFromCDM::convert(data->UnbindingMdibVersion().get());
}

bool OperatorContextState::hasUnbindingMdibVersion() const {
	return data->UnbindingMdibVersion().present();
}

OperatorContextState & OperatorContextState::setBindingStartTime(const Timestamp & value) {
	data->BindingStartTime(ConvertToCDM::convert(value));
	return *this;
}

bool OperatorContextState::getBindingStartTime(Timestamp & out) const {
	if (data->BindingStartTime().present()) {
		out = ConvertFromCDM::convert(data->BindingStartTime().get());
		return true;
	}
	return false;
}

Timestamp OperatorContextState::getBindingStartTime() const {
	return ConvertFromCDM::convert(data->BindingStartTime().get());
}

bool OperatorContextState::hasBindingStartTime() const {
	return data->BindingStartTime().present();
}

OperatorContextState & OperatorContextState::setBindingEndTime(const Timestamp & value) {
	data->BindingEndTime(ConvertToCDM::convert(value));
	return *this;
}

bool OperatorContextState::getBindingEndTime(Timestamp & out) const {
	if (data->BindingEndTime().present()) {
		out = ConvertFromCDM::convert(data->BindingEndTime().get());
		return true;
	}
	return false;
}

Timestamp OperatorContextState::getBindingEndTime() const {
	return ConvertFromCDM::convert(data->BindingEndTime().get());
}

bool OperatorContextState::hasBindingEndTime() const {
	return data->BindingEndTime().present();
}

OperatorContextState & OperatorContextState::addValidator(const InstanceIdentifier & value) {
	data->Validator().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<InstanceIdentifier> OperatorContextState::getValidatorList() const {
	std::vector<InstanceIdentifier> result;
	result.reserve(data->Validator().size());
	for (const auto & value: data->Validator()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void OperatorContextState::clearValidatorList() {
	data->Validator().clear();
}

OperatorContextState & OperatorContextState::addIdentification(const InstanceIdentifier & value) {
	data->Identification().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<InstanceIdentifier> OperatorContextState::getIdentificationList() const {
	std::vector<InstanceIdentifier> result;
	result.reserve(data->Identification().size());
	for (const auto & value: data->Identification()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void OperatorContextState::clearIdentificationList() {
	data->Identification().clear();
}

OperatorContextState & OperatorContextState::setOperatorDetails(const BaseDemographics & value) {
	data->OperatorDetails(ConvertToCDM::convert(value));
	return *this;
}

bool OperatorContextState::getOperatorDetails(BaseDemographics & out) const {
	if (data->OperatorDetails().present()) {
		out = ConvertFromCDM::convert(data->OperatorDetails().get());
		return true;
	}
	return false;
}

BaseDemographics OperatorContextState::getOperatorDetails() const {
	return ConvertFromCDM::convert(data->OperatorDetails().get());
}

bool OperatorContextState::hasOperatorDetails() const {
	return data->OperatorDetails().present();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

