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
 *  MeansContextState.cpp
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

#include "SDCLib/Data/SDC/MDIB/MeansContextState.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/InstanceIdentifier.h"
#include "SDCLib/Data/SDC/MDIB/CodedValue.h"

namespace SDCLib {
namespace Data {
namespace SDC {


MeansContextState::MeansContextState(
		HandleRef descriptorhandle
		,
		Handle handle
) : data(Defaults::MeansContextStateInit(
		descriptorhandle
		,
		handle
))
{}

MeansContextState::operator CDM::MeansContextState() const {
	return *data;
}

MeansContextState::MeansContextState(const CDM::MeansContextState & object)
: data(new CDM::MeansContextState(object))
{ }

MeansContextState::MeansContextState(const MeansContextState & object)
: data(std::make_shared<CDM::MeansContextState>(*object.data))
{ }

void MeansContextState::copyFrom(const MeansContextState & object) {
	data = std::make_shared<CDM::MeansContextState>(*object.data);
}

MeansContextState & MeansContextState:: operator=(const MeansContextState& object) {
	copyFrom(object);
	return *this;
}


MeansContextState & MeansContextState::setStateVersion(const VersionCounter & value) {
	data->StateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool MeansContextState::getStateVersion(VersionCounter & out) const {
	if (data->StateVersion().present()) {
		out = ConvertFromCDM::convert(data->StateVersion().get());
		return true;
	}
	return false;
}

VersionCounter MeansContextState::getStateVersion() const {
	return ConvertFromCDM::convert(data->StateVersion().get());
}

bool MeansContextState::hasStateVersion() const {
	return data->StateVersion().present();
}

MeansContextState & MeansContextState::setDescriptorHandle(const HandleRef & value) {
	data->DescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


HandleRef MeansContextState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->DescriptorHandle());
}

MeansContextState & MeansContextState::setDescriptorVersion(const ReferencedVersion & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool MeansContextState::getDescriptorVersion(ReferencedVersion & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion MeansContextState::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}

bool MeansContextState::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}

MeansContextState & MeansContextState::setCategory(const CodedValue & value) {
	data->Category(ConvertToCDM::convert(value));
	return *this;
}

bool MeansContextState::getCategory(CodedValue & out) const {
	if (data->Category().present()) {
		out = ConvertFromCDM::convert(data->Category().get());
		return true;
	}
	return false;
}

CodedValue MeansContextState::getCategory() const {
	return ConvertFromCDM::convert(data->Category().get());
}

bool MeansContextState::hasCategory() const {
	return data->Category().present();
}

MeansContextState & MeansContextState::setHandle(const Handle & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}


Handle MeansContextState::getHandle() const {
	return ConvertFromCDM::convert(data->Handle());
}

MeansContextState & MeansContextState::setContextAssociation(const ContextAssociation & value) {
	data->ContextAssociation(ConvertToCDM::convert(value));
	return *this;
}

bool MeansContextState::getContextAssociation(ContextAssociation & out) const {
	if (data->ContextAssociation().present()) {
		out = ConvertFromCDM::convert(data->ContextAssociation().get());
		return true;
	}
	return false;
}

ContextAssociation MeansContextState::getContextAssociation() const {
	return ConvertFromCDM::convert(data->ContextAssociation().get());
}

bool MeansContextState::hasContextAssociation() const {
	return data->ContextAssociation().present();
}

MeansContextState & MeansContextState::setBindingMdibVersion(const ReferencedVersion & value) {
	data->BindingMdibVersion(ConvertToCDM::convert(value));
	return *this;
}

bool MeansContextState::getBindingMdibVersion(ReferencedVersion & out) const {
	if (data->BindingMdibVersion().present()) {
		out = ConvertFromCDM::convert(data->BindingMdibVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion MeansContextState::getBindingMdibVersion() const {
	return ConvertFromCDM::convert(data->BindingMdibVersion().get());
}

bool MeansContextState::hasBindingMdibVersion() const {
	return data->BindingMdibVersion().present();
}

MeansContextState & MeansContextState::setUnbindingMdibVersion(const ReferencedVersion & value) {
	data->UnbindingMdibVersion(ConvertToCDM::convert(value));
	return *this;
}

bool MeansContextState::getUnbindingMdibVersion(ReferencedVersion & out) const {
	if (data->UnbindingMdibVersion().present()) {
		out = ConvertFromCDM::convert(data->UnbindingMdibVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion MeansContextState::getUnbindingMdibVersion() const {
	return ConvertFromCDM::convert(data->UnbindingMdibVersion().get());
}

bool MeansContextState::hasUnbindingMdibVersion() const {
	return data->UnbindingMdibVersion().present();
}

MeansContextState & MeansContextState::setBindingStartTime(const Timestamp & value) {
	data->BindingStartTime(ConvertToCDM::convert(value));
	return *this;
}

bool MeansContextState::getBindingStartTime(Timestamp & out) const {
	if (data->BindingStartTime().present()) {
		out = ConvertFromCDM::convert(data->BindingStartTime().get());
		return true;
	}
	return false;
}

Timestamp MeansContextState::getBindingStartTime() const {
	return ConvertFromCDM::convert(data->BindingStartTime().get());
}

bool MeansContextState::hasBindingStartTime() const {
	return data->BindingStartTime().present();
}

MeansContextState & MeansContextState::setBindingEndTime(const Timestamp & value) {
	data->BindingEndTime(ConvertToCDM::convert(value));
	return *this;
}

bool MeansContextState::getBindingEndTime(Timestamp & out) const {
	if (data->BindingEndTime().present()) {
		out = ConvertFromCDM::convert(data->BindingEndTime().get());
		return true;
	}
	return false;
}

Timestamp MeansContextState::getBindingEndTime() const {
	return ConvertFromCDM::convert(data->BindingEndTime().get());
}

bool MeansContextState::hasBindingEndTime() const {
	return data->BindingEndTime().present();
}

MeansContextState & MeansContextState::addValidator(const InstanceIdentifier & value) {
	data->Validator().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<InstanceIdentifier> MeansContextState::getValidatorList() const {
	std::vector<InstanceIdentifier> result;
	result.reserve(data->Validator().size());
	for (const auto & value: data->Validator()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void MeansContextState::clearValidatorList() {
	data->Validator().clear();
}

MeansContextState & MeansContextState::addIdentification(const InstanceIdentifier & value) {
	data->Identification().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<InstanceIdentifier> MeansContextState::getIdentificationList() const {
	std::vector<InstanceIdentifier> result;
	result.reserve(data->Identification().size());
	for (const auto & value: data->Identification()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void MeansContextState::clearIdentificationList() {
	data->Identification().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

