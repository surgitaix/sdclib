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

#include "SDCLib/Data/SDC/MDIB/EnsembleContextState.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/InstanceIdentifier.h"
#include "SDCLib/Data/SDC/MDIB/CodedValue.h"

namespace SDCLib {
namespace Data {
namespace SDC {


EnsembleContextState::EnsembleContextState(
		HandleRef descriptorhandle
		,
		Handle handle
) : data(Defaults::EnsembleContextStateInit(
		descriptorhandle
		,
		handle
))
{}

EnsembleContextState::operator CDM::EnsembleContextState() const {
	return *data;
}

EnsembleContextState::EnsembleContextState(const CDM::EnsembleContextState & object)
: data(new CDM::EnsembleContextState(object))
{ }

EnsembleContextState::EnsembleContextState(const EnsembleContextState & object)
: data(std::make_shared<CDM::EnsembleContextState>(*object.data))
{ }

void EnsembleContextState::copyFrom(const EnsembleContextState & object) {
	data = std::make_shared<CDM::EnsembleContextState>(*object.data);
}

EnsembleContextState & EnsembleContextState:: operator=(const EnsembleContextState& object) {
	copyFrom(object);
	return *this;
}


EnsembleContextState & EnsembleContextState::setStateVersion(const VersionCounter & value) {
	data->setStateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool EnsembleContextState::getStateVersion(VersionCounter & out) const {
	if (data->getStateVersion().present()) {
		out = ConvertFromCDM::convert(data->getStateVersion().get());
		return true;
	}
	return false;
}

VersionCounter EnsembleContextState::getStateVersion() const {
	return ConvertFromCDM::convert(data->getStateVersion().get());
}

bool EnsembleContextState::hasStateVersion() const {
	return data->getStateVersion().present();
}

EnsembleContextState & EnsembleContextState::setDescriptorHandle(const HandleRef & value) {
	data->setDescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


HandleRef EnsembleContextState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->getDescriptorHandle());
}

EnsembleContextState & EnsembleContextState::setDescriptorVersion(const ReferencedVersion & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool EnsembleContextState::getDescriptorVersion(ReferencedVersion & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion EnsembleContextState::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool EnsembleContextState::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

EnsembleContextState & EnsembleContextState::setCategory(const CodedValue & value) {
	data->setCategory(ConvertToCDM::convert(value));
	return *this;
}

bool EnsembleContextState::getCategory(CodedValue & out) const {
	if (data->getCategory().present()) {
		out = ConvertFromCDM::convert(data->getCategory().get());
		return true;
	}
	return false;
}

CodedValue EnsembleContextState::getCategory() const {
	return ConvertFromCDM::convert(data->getCategory().get());
}

bool EnsembleContextState::hasCategory() const {
	return data->getCategory().present();
}

EnsembleContextState & EnsembleContextState::setHandle(const Handle & value) {
	data->setHandle(ConvertToCDM::convert(value));
	return *this;
}


Handle EnsembleContextState::getHandle() const {
	return ConvertFromCDM::convert(data->getHandle());
}

EnsembleContextState & EnsembleContextState::setContextAssociation(const ContextAssociation & value) {
	data->setContextAssociation(ConvertToCDM::convert(value));
	return *this;
}

bool EnsembleContextState::getContextAssociation(ContextAssociation & out) const {
	if (data->getContextAssociation().present()) {
		out = ConvertFromCDM::convert(data->getContextAssociation().get());
		return true;
	}
	return false;
}

ContextAssociation EnsembleContextState::getContextAssociation() const {
	return ConvertFromCDM::convert(data->getContextAssociation().get());
}

bool EnsembleContextState::hasContextAssociation() const {
	return data->getContextAssociation().present();
}

EnsembleContextState & EnsembleContextState::setBindingMdibVersion(const ReferencedVersion & value) {
	data->setBindingMdibVersion(ConvertToCDM::convert(value));
	return *this;
}

bool EnsembleContextState::getBindingMdibVersion(ReferencedVersion & out) const {
	if (data->getBindingMdibVersion().present()) {
		out = ConvertFromCDM::convert(data->getBindingMdibVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion EnsembleContextState::getBindingMdibVersion() const {
	return ConvertFromCDM::convert(data->getBindingMdibVersion().get());
}

bool EnsembleContextState::hasBindingMdibVersion() const {
	return data->getBindingMdibVersion().present();
}

EnsembleContextState & EnsembleContextState::setUnbindingMdibVersion(const ReferencedVersion & value) {
	data->setUnbindingMdibVersion(ConvertToCDM::convert(value));
	return *this;
}

bool EnsembleContextState::getUnbindingMdibVersion(ReferencedVersion & out) const {
	if (data->getUnbindingMdibVersion().present()) {
		out = ConvertFromCDM::convert(data->getUnbindingMdibVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion EnsembleContextState::getUnbindingMdibVersion() const {
	return ConvertFromCDM::convert(data->getUnbindingMdibVersion().get());
}

bool EnsembleContextState::hasUnbindingMdibVersion() const {
	return data->getUnbindingMdibVersion().present();
}

EnsembleContextState & EnsembleContextState::setBindingStartTime(const Timestamp & value) {
	data->setBindingStartTime(ConvertToCDM::convert(value));
	return *this;
}

bool EnsembleContextState::getBindingStartTime(Timestamp & out) const {
	if (data->getBindingStartTime().present()) {
		out = ConvertFromCDM::convert(data->getBindingStartTime().get());
		return true;
	}
	return false;
}

Timestamp EnsembleContextState::getBindingStartTime() const {
	return ConvertFromCDM::convert(data->getBindingStartTime().get());
}

bool EnsembleContextState::hasBindingStartTime() const {
	return data->getBindingStartTime().present();
}

EnsembleContextState & EnsembleContextState::setBindingEndTime(const Timestamp & value) {
	data->setBindingEndTime(ConvertToCDM::convert(value));
	return *this;
}

bool EnsembleContextState::getBindingEndTime(Timestamp & out) const {
	if (data->getBindingEndTime().present()) {
		out = ConvertFromCDM::convert(data->getBindingEndTime().get());
		return true;
	}
	return false;
}

Timestamp EnsembleContextState::getBindingEndTime() const {
	return ConvertFromCDM::convert(data->getBindingEndTime().get());
}

bool EnsembleContextState::hasBindingEndTime() const {
	return data->getBindingEndTime().present();
}

EnsembleContextState & EnsembleContextState::addValidator(const InstanceIdentifier & value) {
	data->getValidator().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<InstanceIdentifier> EnsembleContextState::getValidatorList() const {
	std::vector<InstanceIdentifier> result;
	result.reserve(data->getValidator().size());
	for (const auto & value: data->getValidator()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void EnsembleContextState::clearValidatorList() {
	data->getValidator().clear();
}

EnsembleContextState & EnsembleContextState::addIdentification(const InstanceIdentifier & value) {
	data->getIdentification().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<InstanceIdentifier> EnsembleContextState::getIdentificationList() const {
	std::vector<InstanceIdentifier> result;
	result.reserve(data->getIdentification().size());
	for (const auto & value: data->getIdentification()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void EnsembleContextState::clearIdentificationList() {
	data->getIdentification().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

