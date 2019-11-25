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
 *  WorkflowContextState.cpp
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

#include "SDCLib/Data/SDC/MDIB/WorkflowContextState.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/WorkflowDetail.h"
#include "SDCLib/Data/SDC/MDIB/InstanceIdentifier.h"
#include "SDCLib/Data/SDC/MDIB/CodedValue.h"

namespace SDCLib {
namespace Data {
namespace SDC {


WorkflowContextState::WorkflowContextState(
		HandleRef descriptorhandle
		,
		Handle handle
) : data(Defaults::WorkflowContextStateInit(
		descriptorhandle
		,
		handle
)) {}

WorkflowContextState::operator CDM::WorkflowContextState() const {
	return *data;
}

WorkflowContextState::WorkflowContextState(const CDM::WorkflowContextState & object) : data(new CDM::WorkflowContextState(object)) {

}

WorkflowContextState::WorkflowContextState(const WorkflowContextState & object) : data(new CDM::WorkflowContextState(*object.data)) {

}

WorkflowContextState::~WorkflowContextState() {

}

void WorkflowContextState::copyFrom(const WorkflowContextState & object) {
	data = std::shared_ptr<CDM::WorkflowContextState>( new CDM::WorkflowContextState(*object.data));
}

WorkflowContextState & WorkflowContextState:: operator=(const WorkflowContextState & object) {
	copyFrom(object);
	return *this;
}


WorkflowContextState & WorkflowContextState::setStateVersion(const VersionCounter & value) {
	data->setStateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool WorkflowContextState::getStateVersion(VersionCounter & out) const {
	if (data->getStateVersion().present()) {
		out = ConvertFromCDM::convert(data->getStateVersion().get());
		return true;
	}
	return false;
}

VersionCounter WorkflowContextState::getStateVersion() const {
	return ConvertFromCDM::convert(data->getStateVersion().get());
}

bool WorkflowContextState::hasStateVersion() const {
	return data->getStateVersion().present();
}

WorkflowContextState & WorkflowContextState::setDescriptorHandle(const HandleRef & value) {
	data->setDescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


HandleRef WorkflowContextState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->getDescriptorHandle());
}

WorkflowContextState & WorkflowContextState::setDescriptorVersion(const ReferencedVersion & value) {
	data->setDescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool WorkflowContextState::getDescriptorVersion(ReferencedVersion & out) const {
	if (data->getDescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->getDescriptorVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion WorkflowContextState::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->getDescriptorVersion().get());
}

bool WorkflowContextState::hasDescriptorVersion() const {
	return data->getDescriptorVersion().present();
}

WorkflowContextState & WorkflowContextState::setCategory(const CodedValue & value) {
	data->setCategory(ConvertToCDM::convert(value));
	return *this;
}

bool WorkflowContextState::getCategory(CodedValue & out) const {
	if (data->getCategory().present()) {
		out = ConvertFromCDM::convert(data->getCategory().get());
		return true;
	}
	return false;
}

CodedValue WorkflowContextState::getCategory() const {
	return ConvertFromCDM::convert(data->getCategory().get());
}

bool WorkflowContextState::hasCategory() const {
	return data->getCategory().present();
}

WorkflowContextState & WorkflowContextState::setHandle(const Handle & value) {
	data->setHandle(ConvertToCDM::convert(value));
	return *this;
}


Handle WorkflowContextState::getHandle() const {
	return ConvertFromCDM::convert(data->getHandle());
}

WorkflowContextState & WorkflowContextState::setContextAssociation(const ContextAssociation & value) {
	data->setContextAssociation(ConvertToCDM::convert(value));
	return *this;
}

bool WorkflowContextState::getContextAssociation(ContextAssociation & out) const {
	if (data->getContextAssociation().present()) {
		out = ConvertFromCDM::convert(data->getContextAssociation().get());
		return true;
	}
	return false;
}

ContextAssociation WorkflowContextState::getContextAssociation() const {
	return ConvertFromCDM::convert(data->getContextAssociation().get());
}

bool WorkflowContextState::hasContextAssociation() const {
	return data->getContextAssociation().present();
}

WorkflowContextState & WorkflowContextState::setBindingMdibVersion(const ReferencedVersion & value) {
	data->setBindingMdibVersion(ConvertToCDM::convert(value));
	return *this;
}

bool WorkflowContextState::getBindingMdibVersion(ReferencedVersion & out) const {
	if (data->getBindingMdibVersion().present()) {
		out = ConvertFromCDM::convert(data->getBindingMdibVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion WorkflowContextState::getBindingMdibVersion() const {
	return ConvertFromCDM::convert(data->getBindingMdibVersion().get());
}

bool WorkflowContextState::hasBindingMdibVersion() const {
	return data->getBindingMdibVersion().present();
}

WorkflowContextState & WorkflowContextState::setUnbindingMdibVersion(const ReferencedVersion & value) {
	data->setUnbindingMdibVersion(ConvertToCDM::convert(value));
	return *this;
}

bool WorkflowContextState::getUnbindingMdibVersion(ReferencedVersion & out) const {
	if (data->getUnbindingMdibVersion().present()) {
		out = ConvertFromCDM::convert(data->getUnbindingMdibVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion WorkflowContextState::getUnbindingMdibVersion() const {
	return ConvertFromCDM::convert(data->getUnbindingMdibVersion().get());
}

bool WorkflowContextState::hasUnbindingMdibVersion() const {
	return data->getUnbindingMdibVersion().present();
}

WorkflowContextState & WorkflowContextState::setBindingStartTime(const Timestamp & value) {
	data->setBindingStartTime(ConvertToCDM::convert(value));
	return *this;
}

bool WorkflowContextState::getBindingStartTime(Timestamp & out) const {
	if (data->getBindingStartTime().present()) {
		out = ConvertFromCDM::convert(data->getBindingStartTime().get());
		return true;
	}
	return false;
}

Timestamp WorkflowContextState::getBindingStartTime() const {
	return ConvertFromCDM::convert(data->getBindingStartTime().get());
}

bool WorkflowContextState::hasBindingStartTime() const {
	return data->getBindingStartTime().present();
}

WorkflowContextState & WorkflowContextState::setBindingEndTime(const Timestamp & value) {
	data->setBindingEndTime(ConvertToCDM::convert(value));
	return *this;
}

bool WorkflowContextState::getBindingEndTime(Timestamp & out) const {
	if (data->getBindingEndTime().present()) {
		out = ConvertFromCDM::convert(data->getBindingEndTime().get());
		return true;
	}
	return false;
}

Timestamp WorkflowContextState::getBindingEndTime() const {
	return ConvertFromCDM::convert(data->getBindingEndTime().get());
}

bool WorkflowContextState::hasBindingEndTime() const {
	return data->getBindingEndTime().present();
}

WorkflowContextState & WorkflowContextState::addValidator(const InstanceIdentifier & value) {
	data->getValidator().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<InstanceIdentifier> WorkflowContextState::getValidatorList() const {
	std::vector<InstanceIdentifier> result;
	result.reserve(data->getValidator().size());
	for (const auto & value: data->getValidator()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void WorkflowContextState::clearValidatorList() {
	data->getValidator().clear();
}

WorkflowContextState & WorkflowContextState::addIdentification(const InstanceIdentifier & value) {
	data->getIdentification().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<InstanceIdentifier> WorkflowContextState::getIdentificationList() const {
	std::vector<InstanceIdentifier> result;
	result.reserve(data->getIdentification().size());
	for (const auto & value: data->getIdentification()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void WorkflowContextState::clearIdentificationList() {
	data->getIdentification().clear();
}

WorkflowContextState & WorkflowContextState::setWorkflowDetail(const WorkflowDetail & value) {
	data->setWorkflowDetail(ConvertToCDM::convert(value));
	return *this;
}

bool WorkflowContextState::getWorkflowDetail(WorkflowDetail & out) const {
	if (data->getWorkflowDetail().present()) {
		out = ConvertFromCDM::convert(data->getWorkflowDetail().get());
		return true;
	}
	return false;
}

WorkflowDetail WorkflowContextState::getWorkflowDetail() const {
	return ConvertFromCDM::convert(data->getWorkflowDetail().get());
}

bool WorkflowContextState::hasWorkflowDetail() const {
	return data->getWorkflowDetail().present();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

