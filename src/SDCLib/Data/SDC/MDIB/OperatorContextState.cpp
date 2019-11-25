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
	data->setStateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool OperatorContextState::getStateVersion(VersionCounter & out) const {
	if (data->getStateVersion().present()) {
		out = ConvertFromCDM::convert(data->getStateVersion().get());
		return true;
	}
	return false;
}

VersionCounter OperatorContextState::getStateVersion() const {
	return ConvertFromCDM::convert(data->getStateVersion().get());
}

bool OperatorContextState::hasStateVersion() const {
	return data->getStateVersion().present();
}

OperatorContextState & OperatorContextState::setDescriptorHandle(const HandleRef & value) {
	data->setDescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


HandleRef OperatorContextState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->getDescriptorHandle());
}

OperatorContextState & OperatorContextState::setDescriptorVersion(const ReferencedVersion & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool OperatorContextState::getDescriptorVersion(ReferencedVersion & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion OperatorContextState::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool OperatorContextState::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

OperatorContextState & OperatorContextState::setCategory(const CodedValue & value) {
	data->setCategory(ConvertToCDM::convert(value));
	return *this;
}

bool OperatorContextState::getCategory(CodedValue & out) const {
	if (data->getCategory().present()) {
		out = ConvertFromCDM::convert(data->getCategory().get());
		return true;
	}
	return false;
}

CodedValue OperatorContextState::getCategory() const {
	return ConvertFromCDM::convert(data->getCategory().get());
}

bool OperatorContextState::hasCategory() const {
	return data->getCategory().present();
}

OperatorContextState & OperatorContextState::setHandle(const Handle & value) {
	data->setHandle(ConvertToCDM::convert(value));
	return *this;
}


Handle OperatorContextState::getHandle() const {
	return ConvertFromCDM::convert(data->getHandle());
}

OperatorContextState & OperatorContextState::setContextAssociation(const ContextAssociation & value) {
	data->setContextAssociation(ConvertToCDM::convert(value));
	return *this;
}

bool OperatorContextState::getContextAssociation(ContextAssociation & out) const {
	if (data->getContextAssociation().present()) {
		out = ConvertFromCDM::convert(data->getContextAssociation().get());
		return true;
	}
	return false;
}

ContextAssociation OperatorContextState::getContextAssociation() const {
	return ConvertFromCDM::convert(data->getContextAssociation().get());
}

bool OperatorContextState::hasContextAssociation() const {
	return data->getContextAssociation().present();
}

OperatorContextState & OperatorContextState::setBindingMdibVersion(const ReferencedVersion & value) {
	data->setBindingMdibVersion(ConvertToCDM::convert(value));
	return *this;
}

bool OperatorContextState::getBindingMdibVersion(ReferencedVersion & out) const {
	if (data->getBindingMdibVersion().present()) {
		out = ConvertFromCDM::convert(data->getBindingMdibVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion OperatorContextState::getBindingMdibVersion() const {
	return ConvertFromCDM::convert(data->getBindingMdibVersion().get());
}

bool OperatorContextState::hasBindingMdibVersion() const {
	return data->getBindingMdibVersion().present();
}

OperatorContextState & OperatorContextState::setUnbindingMdibVersion(const ReferencedVersion & value) {
	data->setUnbindingMdibVersion(ConvertToCDM::convert(value));
	return *this;
}

bool OperatorContextState::getUnbindingMdibVersion(ReferencedVersion & out) const {
	if (data->getUnbindingMdibVersion().present()) {
		out = ConvertFromCDM::convert(data->getUnbindingMdibVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion OperatorContextState::getUnbindingMdibVersion() const {
	return ConvertFromCDM::convert(data->getUnbindingMdibVersion().get());
}

bool OperatorContextState::hasUnbindingMdibVersion() const {
	return data->getUnbindingMdibVersion().present();
}

OperatorContextState & OperatorContextState::setBindingStartTime(const Timestamp & value) {
	data->setBindingStartTime(ConvertToCDM::convert(value));
	return *this;
}

bool OperatorContextState::getBindingStartTime(Timestamp & out) const {
	if (data->getBindingStartTime().present()) {
		out = ConvertFromCDM::convert(data->getBindingStartTime().get());
		return true;
	}
	return false;
}

Timestamp OperatorContextState::getBindingStartTime() const {
	return ConvertFromCDM::convert(data->getBindingStartTime().get());
}

bool OperatorContextState::hasBindingStartTime() const {
	return data->getBindingStartTime().present();
}

OperatorContextState & OperatorContextState::setBindingEndTime(const Timestamp & value) {
	data->setBindingEndTime(ConvertToCDM::convert(value));
	return *this;
}

bool OperatorContextState::getBindingEndTime(Timestamp & out) const {
	if (data->getBindingEndTime().present()) {
		out = ConvertFromCDM::convert(data->getBindingEndTime().get());
		return true;
	}
	return false;
}

Timestamp OperatorContextState::getBindingEndTime() const {
	return ConvertFromCDM::convert(data->getBindingEndTime().get());
}

bool OperatorContextState::hasBindingEndTime() const {
	return data->getBindingEndTime().present();
}

OperatorContextState & OperatorContextState::addValidator(const InstanceIdentifier & value) {
	data->getValidator().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<InstanceIdentifier> OperatorContextState::getValidatorList() const {
	std::vector<InstanceIdentifier> result;
	result.reserve(data->getValidator().size());
	for (const auto & value: data->getValidator()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void OperatorContextState::clearValidatorList() {
	data->getValidator().clear();
}

OperatorContextState & OperatorContextState::addIdentification(const InstanceIdentifier & value) {
	data->getIdentification().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<InstanceIdentifier> OperatorContextState::getIdentificationList() const {
	std::vector<InstanceIdentifier> result;
	result.reserve(data->getIdentification().size());
	for (const auto & value: data->getIdentification()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void OperatorContextState::clearIdentificationList() {
	data->getIdentification().clear();
}

OperatorContextState & OperatorContextState::setOperatorDetails(const BaseDemographics & value) {
	data->setOperatorDetails(ConvertToCDM::convert(value));
	return *this;
}

bool OperatorContextState::getOperatorDetails(BaseDemographics & out) const {
	if (data->getOperatorDetails().present()) {
		out = ConvertFromCDM::convert(data->getOperatorDetails().get());
		return true;
	}
	return false;
}

BaseDemographics OperatorContextState::getOperatorDetails() const {
	return ConvertFromCDM::convert(data->getOperatorDetails().get());
}

bool OperatorContextState::hasOperatorDetails() const {
	return data->getOperatorDetails().present();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

