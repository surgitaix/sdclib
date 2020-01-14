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
 *  PatientContextState.cpp
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

#include "SDCLib/Data/SDC/MDIB/PatientContextState.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/PatientDemographicsCoreData.h"
#include "SDCLib/Data/SDC/MDIB/InstanceIdentifier.h"
#include "SDCLib/Data/SDC/MDIB/CodedValue.h"

namespace SDCLib {
namespace Data {
namespace SDC {


PatientContextState::PatientContextState(
		HandleRef descriptorhandle
		,
		Handle handle
) : data(Defaults::PatientContextStateInit(
		descriptorhandle
		,
		handle
))
{}

PatientContextState::operator CDM::PatientContextState() const {
	return *data;
}

PatientContextState::PatientContextState(const CDM::PatientContextState & object)
: data(new CDM::PatientContextState(object))
{ }

PatientContextState::PatientContextState(const PatientContextState & object)
: data(std::make_shared<CDM::PatientContextState>(*object.data))
{ }

void PatientContextState::copyFrom(const PatientContextState & object) {
	data = std::make_shared<CDM::PatientContextState>(*object.data);
}

PatientContextState & PatientContextState:: operator=(const PatientContextState& object) {
	copyFrom(object);
	return *this;
}


PatientContextState & PatientContextState::setStateVersion(const VersionCounter & value) {
	data->setStateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool PatientContextState::getStateVersion(VersionCounter & out) const {
	if (data->getStateVersion().present()) {
		out = ConvertFromCDM::convert(data->getStateVersion().get());
		return true;
	}
	return false;
}

VersionCounter PatientContextState::getStateVersion() const {
	return ConvertFromCDM::convert(data->getStateVersion().get());
}

bool PatientContextState::hasStateVersion() const {
	return data->getStateVersion().present();
}

PatientContextState & PatientContextState::setDescriptorHandle(const HandleRef & value) {
	data->setDescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


HandleRef PatientContextState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->getDescriptorHandle());
}

PatientContextState & PatientContextState::setDescriptorVersion(const ReferencedVersion & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool PatientContextState::getDescriptorVersion(ReferencedVersion & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion PatientContextState::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool PatientContextState::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

PatientContextState & PatientContextState::setCategory(const CodedValue & value) {
	data->setCategory(ConvertToCDM::convert(value));
	return *this;
}

bool PatientContextState::getCategory(CodedValue & out) const {
	if (data->getCategory().present()) {
		out = ConvertFromCDM::convert(data->getCategory().get());
		return true;
	}
	return false;
}

CodedValue PatientContextState::getCategory() const {
	return ConvertFromCDM::convert(data->getCategory().get());
}

bool PatientContextState::hasCategory() const {
	return data->getCategory().present();
}

PatientContextState & PatientContextState::setHandle(const Handle & value) {
	data->setHandle(ConvertToCDM::convert(value));
	return *this;
}


Handle PatientContextState::getHandle() const {
	return ConvertFromCDM::convert(data->getHandle());
}

PatientContextState & PatientContextState::setContextAssociation(const ContextAssociation & value) {
	data->setContextAssociation(ConvertToCDM::convert(value));
	return *this;
}

bool PatientContextState::getContextAssociation(ContextAssociation & out) const {
	if (data->getContextAssociation().present()) {
		out = ConvertFromCDM::convert(data->getContextAssociation().get());
		return true;
	}
	return false;
}

ContextAssociation PatientContextState::getContextAssociation() const {
	return ConvertFromCDM::convert(data->getContextAssociation().get());
}

bool PatientContextState::hasContextAssociation() const {
	return data->getContextAssociation().present();
}

PatientContextState & PatientContextState::setBindingMdibVersion(const ReferencedVersion & value) {
	data->setBindingMdibVersion(ConvertToCDM::convert(value));
	return *this;
}

bool PatientContextState::getBindingMdibVersion(ReferencedVersion & out) const {
	if (data->getBindingMdibVersion().present()) {
		out = ConvertFromCDM::convert(data->getBindingMdibVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion PatientContextState::getBindingMdibVersion() const {
	return ConvertFromCDM::convert(data->getBindingMdibVersion().get());
}

bool PatientContextState::hasBindingMdibVersion() const {
	return data->getBindingMdibVersion().present();
}

PatientContextState & PatientContextState::setUnbindingMdibVersion(const ReferencedVersion & value) {
	data->setUnbindingMdibVersion(ConvertToCDM::convert(value));
	return *this;
}

bool PatientContextState::getUnbindingMdibVersion(ReferencedVersion & out) const {
	if (data->getUnbindingMdibVersion().present()) {
		out = ConvertFromCDM::convert(data->getUnbindingMdibVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion PatientContextState::getUnbindingMdibVersion() const {
	return ConvertFromCDM::convert(data->getUnbindingMdibVersion().get());
}

bool PatientContextState::hasUnbindingMdibVersion() const {
	return data->getUnbindingMdibVersion().present();
}

PatientContextState & PatientContextState::setBindingStartTime(const Timestamp & value) {
	data->setBindingStartTime(ConvertToCDM::convert(value));
	return *this;
}

bool PatientContextState::getBindingStartTime(Timestamp & out) const {
	if (data->getBindingStartTime().present()) {
		out = ConvertFromCDM::convert(data->getBindingStartTime().get());
		return true;
	}
	return false;
}

Timestamp PatientContextState::getBindingStartTime() const {
	return ConvertFromCDM::convert(data->getBindingStartTime().get());
}

bool PatientContextState::hasBindingStartTime() const {
	return data->getBindingStartTime().present();
}

PatientContextState & PatientContextState::setBindingEndTime(const Timestamp & value) {
	data->setBindingEndTime(ConvertToCDM::convert(value));
	return *this;
}

bool PatientContextState::getBindingEndTime(Timestamp & out) const {
	if (data->getBindingEndTime().present()) {
		out = ConvertFromCDM::convert(data->getBindingEndTime().get());
		return true;
	}
	return false;
}

Timestamp PatientContextState::getBindingEndTime() const {
	return ConvertFromCDM::convert(data->getBindingEndTime().get());
}

bool PatientContextState::hasBindingEndTime() const {
	return data->getBindingEndTime().present();
}

PatientContextState & PatientContextState::addValidator(const InstanceIdentifier & value) {
	data->getValidator().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<InstanceIdentifier> PatientContextState::getValidatorList() const {
	std::vector<InstanceIdentifier> result;
	result.reserve(data->getValidator().size());
	for (const auto & value: data->getValidator()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void PatientContextState::clearValidatorList() {
	data->getValidator().clear();
}

PatientContextState & PatientContextState::addIdentification(const InstanceIdentifier & value) {
	data->getIdentification().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<InstanceIdentifier> PatientContextState::getIdentificationList() const {
	std::vector<InstanceIdentifier> result;
	result.reserve(data->getIdentification().size());
	for (const auto & value: data->getIdentification()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void PatientContextState::clearIdentificationList() {
	data->getIdentification().clear();
}

PatientContextState & PatientContextState::setCoreData(const PatientDemographicsCoreData & value) {
	data->setCoreData(ConvertToCDM::convert(value));
	return *this;
}

bool PatientContextState::getCoreData(PatientDemographicsCoreData & out) const {
	if (data->getCoreData().present()) {
		out = ConvertFromCDM::convert(data->getCoreData().get());
		return true;
	}
	return false;
}

PatientDemographicsCoreData PatientContextState::getCoreData() const {
	return ConvertFromCDM::convert(data->getCoreData().get());
}

bool PatientContextState::hasCoreData() const {
	return data->getCoreData().present();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

