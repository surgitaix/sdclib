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
	data->StateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool WorkflowContextState::getStateVersion(VersionCounter & out) const {
	if (data->StateVersion().present()) {
		out = ConvertFromCDM::convert(data->StateVersion().get());
		return true;
	}
	return false;
}

VersionCounter WorkflowContextState::getStateVersion() const {
	return ConvertFromCDM::convert(data->StateVersion().get());
}

bool WorkflowContextState::hasStateVersion() const {
	return data->StateVersion().present();
}

WorkflowContextState & WorkflowContextState::setDescriptorHandle(const HandleRef & value) {
	data->DescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


HandleRef WorkflowContextState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->DescriptorHandle());
}

WorkflowContextState & WorkflowContextState::setDescriptorVersion(const ReferencedVersion & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool WorkflowContextState::getDescriptorVersion(ReferencedVersion & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion WorkflowContextState::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}

bool WorkflowContextState::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}

WorkflowContextState & WorkflowContextState::setCategory(const CodedValue & value) {
	data->Category(ConvertToCDM::convert(value));
	return *this;
}

bool WorkflowContextState::getCategory(CodedValue & out) const {
	if (data->Category().present()) {
		out = ConvertFromCDM::convert(data->Category().get());
		return true;
	}
	return false;
}

CodedValue WorkflowContextState::getCategory() const {
	return ConvertFromCDM::convert(data->Category().get());
}

bool WorkflowContextState::hasCategory() const {
	return data->Category().present();
}

WorkflowContextState & WorkflowContextState::setHandle(const Handle & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}


Handle WorkflowContextState::getHandle() const {
	return ConvertFromCDM::convert(data->Handle());
}

WorkflowContextState & WorkflowContextState::setContextAssociation(const ContextAssociation & value) {
	data->ContextAssociation(ConvertToCDM::convert(value));
	return *this;
}

bool WorkflowContextState::getContextAssociation(ContextAssociation & out) const {
	if (data->ContextAssociation().present()) {
		out = ConvertFromCDM::convert(data->ContextAssociation().get());
		return true;
	}
	return false;
}

ContextAssociation WorkflowContextState::getContextAssociation() const {
	return ConvertFromCDM::convert(data->ContextAssociation().get());
}

bool WorkflowContextState::hasContextAssociation() const {
	return data->ContextAssociation().present();
}

WorkflowContextState & WorkflowContextState::setBindingMdibVersion(const ReferencedVersion & value) {
	data->BindingMdibVersion(ConvertToCDM::convert(value));
	return *this;
}

bool WorkflowContextState::getBindingMdibVersion(ReferencedVersion & out) const {
	if (data->BindingMdibVersion().present()) {
		out = ConvertFromCDM::convert(data->BindingMdibVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion WorkflowContextState::getBindingMdibVersion() const {
	return ConvertFromCDM::convert(data->BindingMdibVersion().get());
}

bool WorkflowContextState::hasBindingMdibVersion() const {
	return data->BindingMdibVersion().present();
}

WorkflowContextState & WorkflowContextState::setUnbindingMdibVersion(const ReferencedVersion & value) {
	data->UnbindingMdibVersion(ConvertToCDM::convert(value));
	return *this;
}

bool WorkflowContextState::getUnbindingMdibVersion(ReferencedVersion & out) const {
	if (data->UnbindingMdibVersion().present()) {
		out = ConvertFromCDM::convert(data->UnbindingMdibVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion WorkflowContextState::getUnbindingMdibVersion() const {
	return ConvertFromCDM::convert(data->UnbindingMdibVersion().get());
}

bool WorkflowContextState::hasUnbindingMdibVersion() const {
	return data->UnbindingMdibVersion().present();
}

WorkflowContextState & WorkflowContextState::setBindingStartTime(const Timestamp & value) {
	data->BindingStartTime(ConvertToCDM::convert(value));
	return *this;
}

bool WorkflowContextState::getBindingStartTime(Timestamp & out) const {
	if (data->BindingStartTime().present()) {
		out = ConvertFromCDM::convert(data->BindingStartTime().get());
		return true;
	}
	return false;
}

Timestamp WorkflowContextState::getBindingStartTime() const {
	return ConvertFromCDM::convert(data->BindingStartTime().get());
}

bool WorkflowContextState::hasBindingStartTime() const {
	return data->BindingStartTime().present();
}

WorkflowContextState & WorkflowContextState::setBindingEndTime(const Timestamp & value) {
	data->BindingEndTime(ConvertToCDM::convert(value));
	return *this;
}

bool WorkflowContextState::getBindingEndTime(Timestamp & out) const {
	if (data->BindingEndTime().present()) {
		out = ConvertFromCDM::convert(data->BindingEndTime().get());
		return true;
	}
	return false;
}

Timestamp WorkflowContextState::getBindingEndTime() const {
	return ConvertFromCDM::convert(data->BindingEndTime().get());
}

bool WorkflowContextState::hasBindingEndTime() const {
	return data->BindingEndTime().present();
}

WorkflowContextState & WorkflowContextState::addValidator(const InstanceIdentifier & value) {
	data->Validator().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<InstanceIdentifier> WorkflowContextState::getValidatorList() const {
	std::vector<InstanceIdentifier> result;
	result.reserve(data->Validator().size());
	for (const auto & value: data->Validator()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void WorkflowContextState::clearValidatorList() {
	data->Validator().clear();
}

WorkflowContextState & WorkflowContextState::addIdentification(const InstanceIdentifier & value) {
	data->Identification().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<InstanceIdentifier> WorkflowContextState::getIdentificationList() const {
	std::vector<InstanceIdentifier> result;
	result.reserve(data->Identification().size());
	for (const auto & value: data->Identification()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void WorkflowContextState::clearIdentificationList() {
	data->Identification().clear();
}

WorkflowContextState & WorkflowContextState::setWorkflowDetail(const WorkflowDetail & value) {
	data->WorkflowDetail(ConvertToCDM::convert(value));
	return *this;
}

bool WorkflowContextState::getWorkflowDetail(WorkflowDetail & out) const {
	if (data->WorkflowDetail().present()) {
		out = ConvertFromCDM::convert(data->WorkflowDetail().get());
		return true;
	}
	return false;
}

WorkflowDetail WorkflowContextState::getWorkflowDetail() const {
	return ConvertFromCDM::convert(data->WorkflowDetail().get());
}

bool WorkflowContextState::hasWorkflowDetail() const {
	return data->WorkflowDetail().present();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

