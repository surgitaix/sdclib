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
	data->setStateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool MeansContextState::getStateVersion(VersionCounter & out) const {
	if (data->getStateVersion().present()) {
		out = ConvertFromCDM::convert(data->getStateVersion().get());
		return true;
	}
	return false;
}

VersionCounter MeansContextState::getStateVersion() const {
	return ConvertFromCDM::convert(data->getStateVersion().get());
}

bool MeansContextState::hasStateVersion() const {
	return data->getStateVersion().present();
}

MeansContextState & MeansContextState::setDescriptorHandle(const HandleRef & value) {
	data->setDescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


HandleRef MeansContextState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->getDescriptorHandle());
}

MeansContextState & MeansContextState::setDescriptorVersion(const ReferencedVersion & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool MeansContextState::getDescriptorVersion(ReferencedVersion & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion MeansContextState::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool MeansContextState::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

MeansContextState & MeansContextState::setCategory(const CodedValue & value) {
	data->setCategory(ConvertToCDM::convert(value));
	return *this;
}

bool MeansContextState::getCategory(CodedValue & out) const {
	if (data->getCategory().present()) {
		out = ConvertFromCDM::convert(data->getCategory().get());
		return true;
	}
	return false;
}

CodedValue MeansContextState::getCategory() const {
	return ConvertFromCDM::convert(data->getCategory().get());
}

bool MeansContextState::hasCategory() const {
	return data->getCategory().present();
}

MeansContextState & MeansContextState::setHandle(const Handle & value) {
	data->setHandle(ConvertToCDM::convert(value));
	return *this;
}


Handle MeansContextState::getHandle() const {
	return ConvertFromCDM::convert(data->getHandle());
}

MeansContextState & MeansContextState::setContextAssociation(const ContextAssociation & value) {
	data->setContextAssociation(ConvertToCDM::convert(value));
	return *this;
}

bool MeansContextState::getContextAssociation(ContextAssociation & out) const {
	if (data->getContextAssociation().present()) {
		out = ConvertFromCDM::convert(data->getContextAssociation().get());
		return true;
	}
	return false;
}

ContextAssociation MeansContextState::getContextAssociation() const {
	return ConvertFromCDM::convert(data->getContextAssociation().get());
}

bool MeansContextState::hasContextAssociation() const {
	return data->getContextAssociation().present();
}

MeansContextState & MeansContextState::setBindingMdibVersion(const ReferencedVersion & value) {
	data->setBindingMdibVersion(ConvertToCDM::convert(value));
	return *this;
}

bool MeansContextState::getBindingMdibVersion(ReferencedVersion & out) const {
	if (data->getBindingMdibVersion().present()) {
		out = ConvertFromCDM::convert(data->getBindingMdibVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion MeansContextState::getBindingMdibVersion() const {
	return ConvertFromCDM::convert(data->getBindingMdibVersion().get());
}

bool MeansContextState::hasBindingMdibVersion() const {
	return data->getBindingMdibVersion().present();
}

MeansContextState & MeansContextState::setUnbindingMdibVersion(const ReferencedVersion & value) {
	data->setUnbindingMdibVersion(ConvertToCDM::convert(value));
	return *this;
}

bool MeansContextState::getUnbindingMdibVersion(ReferencedVersion & out) const {
	if (data->getUnbindingMdibVersion().present()) {
		out = ConvertFromCDM::convert(data->getUnbindingMdibVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion MeansContextState::getUnbindingMdibVersion() const {
	return ConvertFromCDM::convert(data->getUnbindingMdibVersion().get());
}

bool MeansContextState::hasUnbindingMdibVersion() const {
	return data->getUnbindingMdibVersion().present();
}

MeansContextState & MeansContextState::setBindingStartTime(const Timestamp & value) {
	data->setBindingStartTime(ConvertToCDM::convert(value));
	return *this;
}

bool MeansContextState::getBindingStartTime(Timestamp & out) const {
	if (data->getBindingStartTime().present()) {
		out = ConvertFromCDM::convert(data->getBindingStartTime().get());
		return true;
	}
	return false;
}

Timestamp MeansContextState::getBindingStartTime() const {
	return ConvertFromCDM::convert(data->getBindingStartTime().get());
}

bool MeansContextState::hasBindingStartTime() const {
	return data->getBindingStartTime().present();
}

MeansContextState & MeansContextState::setBindingEndTime(const Timestamp & value) {
	data->setBindingEndTime(ConvertToCDM::convert(value));
	return *this;
}

bool MeansContextState::getBindingEndTime(Timestamp & out) const {
	if (data->getBindingEndTime().present()) {
		out = ConvertFromCDM::convert(data->getBindingEndTime().get());
		return true;
	}
	return false;
}

Timestamp MeansContextState::getBindingEndTime() const {
	return ConvertFromCDM::convert(data->getBindingEndTime().get());
}

bool MeansContextState::hasBindingEndTime() const {
	return data->getBindingEndTime().present();
}

MeansContextState & MeansContextState::addValidator(const InstanceIdentifier & value) {
	data->getValidator().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<InstanceIdentifier> MeansContextState::getValidatorList() const {
	std::vector<InstanceIdentifier> result;
	result.reserve(data->getValidator().size());
	for (const auto & value: data->getValidator()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void MeansContextState::clearValidatorList() {
	data->getValidator().clear();
}

MeansContextState & MeansContextState::addIdentification(const InstanceIdentifier & value) {
	data->getIdentification().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<InstanceIdentifier> MeansContextState::getIdentificationList() const {
	std::vector<InstanceIdentifier> result;
	result.reserve(data->getIdentification().size());
	for (const auto & value: data->getIdentification()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void MeansContextState::clearIdentificationList() {
	data->getIdentification().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

