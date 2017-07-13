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
 *  Author: besting, roehser
 */
 
/**
 * THIS FILE IS GENERATED AUTOMATICALLY! DO NOT MODIFY!
 *
 * YOUR CHANGES WILL BE OVERWRITTEN!
 * 
 * USE THE DEFINITION FILES IN THE FOLDER "codegenerator" INSTEAD!
 */

#include "OSCLib/Data/OSCP/MDIB/WorkflowContextState.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/InstanceIdentifier.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

WorkflowContextState::WorkflowContextState() : data(Defaults::WorkflowContextState()) {
}

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
	*data = *object.data;
}

WorkflowContextState & WorkflowContextState:: operator=(const WorkflowContextState & object) {
	copyFrom(object);
	return *this;
}


WorkflowContextState & WorkflowContextState::setStateVersion(const VersionCounter & value) {
	data->StateVersion(ConvertToCDM::convert(value));
	return *this;
}


VersionCounter WorkflowContextState::getStateVersion() const {
	return ConvertFromCDM::convert(data->StateVersion());
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


ReferencedVersion WorkflowContextState::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion());
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


ContextAssociation WorkflowContextState::getContextAssociation() const {
	return ConvertFromCDM::convert(data->ContextAssociation());
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


ReferencedVersion WorkflowContextState::getUnbindingMdibVersion() const {
	return ConvertFromCDM::convert(data->UnbindingMdibVersion());
}
	
WorkflowContextState & WorkflowContextState::setBindingStartTime(const Timestamp & value) {
	data->BindingStartTime(ConvertToCDM::convert(value));
	return *this;
}


Timestamp WorkflowContextState::getBindingStartTime() const {
	return ConvertFromCDM::convert(data->BindingStartTime());
}
	
WorkflowContextState & WorkflowContextState::setBindingEndTime(const Timestamp & value) {
	data->BindingEndTime(ConvertToCDM::convert(value));
	return *this;
}


Timestamp WorkflowContextState::getBindingEndTime() const {
	return ConvertFromCDM::convert(data->BindingEndTime());
}
	
WorkflowContextState & WorkflowContextState::addValidator(const InstanceIdentifier & value) {
	data->Validator().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<InstanceIdentifier> WorkflowContextState::getValidatorLists() const {
	std::vector<InstanceIdentifier> result;
	result.reserve(data->Validator().size());
	for (const auto & value: data->Validator()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void WorkflowContextState::clearValidatorLists() {
	data->Validator().clear();
}

WorkflowContextState & WorkflowContextState::addIdentification(const InstanceIdentifier & value) {
	data->Identification().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<InstanceIdentifier> WorkflowContextState::getIdentificationLists() const {
	std::vector<InstanceIdentifier> result;
	result.reserve(data->Identification().size());
	for (const auto & value: data->Identification()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void WorkflowContextState::clearIdentificationLists() {
	data->Identification().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

