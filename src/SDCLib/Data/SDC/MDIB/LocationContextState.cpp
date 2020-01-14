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

#include "SDCLib/Data/SDC/MDIB/LocationContextState.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/LocationDetail.h"
#include "SDCLib/Data/SDC/MDIB/InstanceIdentifier.h"
#include "SDCLib/Data/SDC/MDIB/CodedValue.h"

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
))
{}

LocationContextState::operator CDM::LocationContextState() const {
	return *data;
}

LocationContextState::LocationContextState(const CDM::LocationContextState & object)
: data(new CDM::LocationContextState(object))
{ }

LocationContextState::LocationContextState(const LocationContextState & object)
: data(std::make_shared<CDM::LocationContextState>(*object.data))
{ }

void LocationContextState::copyFrom(const LocationContextState & object) {
	data = std::make_shared<CDM::LocationContextState>(*object.data);
}

LocationContextState & LocationContextState:: operator=(const LocationContextState& object) {
	copyFrom(object);
	return *this;
}


LocationContextState & LocationContextState::setStateVersion(const VersionCounter & value) {
	data->setStateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool LocationContextState::getStateVersion(VersionCounter & out) const {
	if (data->getStateVersion().present()) {
		out = ConvertFromCDM::convert(data->getStateVersion().get());
		return true;
	}
	return false;
}

VersionCounter LocationContextState::getStateVersion() const {
	return ConvertFromCDM::convert(data->getStateVersion().get());
}

bool LocationContextState::hasStateVersion() const {
	return data->getStateVersion().present();
}

LocationContextState & LocationContextState::setDescriptorHandle(const HandleRef & value) {
	data->setDescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


HandleRef LocationContextState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->getDescriptorHandle());
}

LocationContextState & LocationContextState::setDescriptorVersion(const ReferencedVersion & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool LocationContextState::getDescriptorVersion(ReferencedVersion & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion LocationContextState::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool LocationContextState::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

LocationContextState & LocationContextState::setCategory(const CodedValue & value) {
	data->setCategory(ConvertToCDM::convert(value));
	return *this;
}

bool LocationContextState::getCategory(CodedValue & out) const {
	if (data->getCategory().present()) {
		out = ConvertFromCDM::convert(data->getCategory().get());
		return true;
	}
	return false;
}

CodedValue LocationContextState::getCategory() const {
	return ConvertFromCDM::convert(data->getCategory().get());
}

bool LocationContextState::hasCategory() const {
	return data->getCategory().present();
}

LocationContextState & LocationContextState::setHandle(const Handle & value) {
	data->setHandle(ConvertToCDM::convert(value));
	return *this;
}


Handle LocationContextState::getHandle() const {
	return ConvertFromCDM::convert(data->getHandle());
}

LocationContextState & LocationContextState::setContextAssociation(const ContextAssociation & value) {
	data->setContextAssociation(ConvertToCDM::convert(value));
	return *this;
}

bool LocationContextState::getContextAssociation(ContextAssociation & out) const {
	if (data->getContextAssociation().present()) {
		out = ConvertFromCDM::convert(data->getContextAssociation().get());
		return true;
	}
	return false;
}

ContextAssociation LocationContextState::getContextAssociation() const {
	return ConvertFromCDM::convert(data->getContextAssociation().get());
}

bool LocationContextState::hasContextAssociation() const {
	return data->getContextAssociation().present();
}

LocationContextState & LocationContextState::setBindingMdibVersion(const ReferencedVersion & value) {
	data->setBindingMdibVersion(ConvertToCDM::convert(value));
	return *this;
}

bool LocationContextState::getBindingMdibVersion(ReferencedVersion & out) const {
	if (data->getBindingMdibVersion().present()) {
		out = ConvertFromCDM::convert(data->getBindingMdibVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion LocationContextState::getBindingMdibVersion() const {
	return ConvertFromCDM::convert(data->getBindingMdibVersion().get());
}

bool LocationContextState::hasBindingMdibVersion() const {
	return data->getBindingMdibVersion().present();
}

LocationContextState & LocationContextState::setUnbindingMdibVersion(const ReferencedVersion & value) {
	data->setUnbindingMdibVersion(ConvertToCDM::convert(value));
	return *this;
}

bool LocationContextState::getUnbindingMdibVersion(ReferencedVersion & out) const {
	if (data->getUnbindingMdibVersion().present()) {
		out = ConvertFromCDM::convert(data->getUnbindingMdibVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion LocationContextState::getUnbindingMdibVersion() const {
	return ConvertFromCDM::convert(data->getUnbindingMdibVersion().get());
}

bool LocationContextState::hasUnbindingMdibVersion() const {
	return data->getUnbindingMdibVersion().present();
}

LocationContextState & LocationContextState::setBindingStartTime(const Timestamp & value) {
	data->setBindingStartTime(ConvertToCDM::convert(value));
	return *this;
}

bool LocationContextState::getBindingStartTime(Timestamp & out) const {
	if (data->getBindingStartTime().present()) {
		out = ConvertFromCDM::convert(data->getBindingStartTime().get());
		return true;
	}
	return false;
}

Timestamp LocationContextState::getBindingStartTime() const {
	return ConvertFromCDM::convert(data->getBindingStartTime().get());
}

bool LocationContextState::hasBindingStartTime() const {
	return data->getBindingStartTime().present();
}

LocationContextState & LocationContextState::setBindingEndTime(const Timestamp & value) {
	data->setBindingEndTime(ConvertToCDM::convert(value));
	return *this;
}

bool LocationContextState::getBindingEndTime(Timestamp & out) const {
	if (data->getBindingEndTime().present()) {
		out = ConvertFromCDM::convert(data->getBindingEndTime().get());
		return true;
	}
	return false;
}

Timestamp LocationContextState::getBindingEndTime() const {
	return ConvertFromCDM::convert(data->getBindingEndTime().get());
}

bool LocationContextState::hasBindingEndTime() const {
	return data->getBindingEndTime().present();
}

LocationContextState & LocationContextState::addValidator(const InstanceIdentifier & value) {
	data->getValidator().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<InstanceIdentifier> LocationContextState::getValidatorList() const {
	std::vector<InstanceIdentifier> result;
	result.reserve(data->getValidator().size());
	for (const auto & value: data->getValidator()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void LocationContextState::clearValidatorList() {
	data->getValidator().clear();
}

LocationContextState & LocationContextState::addIdentification(const InstanceIdentifier & value) {
	data->getIdentification().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<InstanceIdentifier> LocationContextState::getIdentificationList() const {
	std::vector<InstanceIdentifier> result;
	result.reserve(data->getIdentification().size());
	for (const auto & value: data->getIdentification()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void LocationContextState::clearIdentificationList() {
	data->getIdentification().clear();
}

LocationContextState & LocationContextState::setLocationDetail(const LocationDetail & value) {
	data->setLocationDetail(ConvertToCDM::convert(value));
	return *this;
}

bool LocationContextState::getLocationDetail(LocationDetail & out) const {
	if (data->getLocationDetail().present()) {
		out = ConvertFromCDM::convert(data->getLocationDetail().get());
		return true;
	}
	return false;
}

LocationDetail LocationContextState::getLocationDetail() const {
	return ConvertFromCDM::convert(data->getLocationDetail().get());
}

bool LocationContextState::hasLocationDetail() const {
	return data->getLocationDetail().present();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

