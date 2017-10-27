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
 *  Author: besting, roehser
 */
 
/**
 * THIS FILE IS GENERATED AUTOMATICALLY! DO NOT MODIFY!
 *
 * YOUR CHANGES WILL BE OVERWRITTEN!
 * 
 * USE THE DEFINITION FILES IN THE FOLDER "codegenerator" INSTEAD!
 */

#include "OSCLib/Data/OSCP/MDIB/PatientContextState.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/PatientDemographicsCoreData.h"
#include "OSCLib/Data/OSCP/MDIB/InstanceIdentifier.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

PatientContextState::PatientContextState() : data(Defaults::PatientContextState()) {
}

PatientContextState::operator CDM::PatientContextState() const {
	return *data;
}

PatientContextState::PatientContextState(const CDM::PatientContextState & object) : data(new CDM::PatientContextState(object)) {

}

PatientContextState::PatientContextState(const PatientContextState & object) : data(new CDM::PatientContextState(*object.data)) {

}

PatientContextState::~PatientContextState() {

}

void PatientContextState::copyFrom(const PatientContextState & object) {
	*data = *object.data;
}

PatientContextState & PatientContextState:: operator=(const PatientContextState & object) {
	copyFrom(object);
	return *this;
}


PatientContextState & PatientContextState::setStateVersion(const VersionCounter & value) {
	data->StateVersion(ConvertToCDM::convert(value));
	return *this;
}

bool PatientContextState::getStateVersion(VersionCounter & out) const {
	if (data->StateVersion().present()) {
		out = ConvertFromCDM::convert(data->StateVersion().get());
		return true;
	}
	return false;
}

VersionCounter PatientContextState::getStateVersion() const {
	return ConvertFromCDM::convert(data->StateVersion().get());
}
	
bool PatientContextState::hasStateVersion() const {
	return data->StateVersion().present();
}
	
PatientContextState & PatientContextState::setDescriptorHandle(const HandleRef & value) {
	data->DescriptorHandle(ConvertToCDM::convert(value));
	return *this;
}


HandleRef PatientContextState::getDescriptorHandle() const {
	return ConvertFromCDM::convert(data->DescriptorHandle());
}
	
PatientContextState & PatientContextState::setDescriptorVersion(const ReferencedVersion & value) {
	data->DescriptorVersion(ConvertToCDM::convert(value));
	return *this;
}

bool PatientContextState::getDescriptorVersion(ReferencedVersion & out) const {
	if (data->DescriptorVersion().present()) {
		out = ConvertFromCDM::convert(data->DescriptorVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion PatientContextState::getDescriptorVersion() const {
	return ConvertFromCDM::convert(data->DescriptorVersion().get());
}
	
bool PatientContextState::hasDescriptorVersion() const {
	return data->DescriptorVersion().present();
}
	
PatientContextState & PatientContextState::setCategory(const CodedValue & value) {
	data->Category(ConvertToCDM::convert(value));
	return *this;
}

bool PatientContextState::getCategory(CodedValue & out) const {
	if (data->Category().present()) {
		out = ConvertFromCDM::convert(data->Category().get());
		return true;
	}
	return false;
}

CodedValue PatientContextState::getCategory() const {
	return ConvertFromCDM::convert(data->Category().get());
}
	
bool PatientContextState::hasCategory() const {
	return data->Category().present();
}
	
PatientContextState & PatientContextState::setHandle(const Handle & value) {
	data->Handle(ConvertToCDM::convert(value));
	return *this;
}


Handle PatientContextState::getHandle() const {
	return ConvertFromCDM::convert(data->Handle());
}
	
PatientContextState & PatientContextState::setContextAssociation(const ContextAssociation & value) {
	data->ContextAssociation(ConvertToCDM::convert(value));
	return *this;
}

bool PatientContextState::getContextAssociation(ContextAssociation & out) const {
	if (data->ContextAssociation().present()) {
		out = ConvertFromCDM::convert(data->ContextAssociation().get());
		return true;
	}
	return false;
}

ContextAssociation PatientContextState::getContextAssociation() const {
	return ConvertFromCDM::convert(data->ContextAssociation().get());
}
	
bool PatientContextState::hasContextAssociation() const {
	return data->ContextAssociation().present();
}
	
PatientContextState & PatientContextState::setBindingMdibVersion(const ReferencedVersion & value) {
	data->BindingMdibVersion(ConvertToCDM::convert(value));
	return *this;
}

bool PatientContextState::getBindingMdibVersion(ReferencedVersion & out) const {
	if (data->BindingMdibVersion().present()) {
		out = ConvertFromCDM::convert(data->BindingMdibVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion PatientContextState::getBindingMdibVersion() const {
	return ConvertFromCDM::convert(data->BindingMdibVersion().get());
}
	
bool PatientContextState::hasBindingMdibVersion() const {
	return data->BindingMdibVersion().present();
}
	
PatientContextState & PatientContextState::setUnbindingMdibVersion(const ReferencedVersion & value) {
	data->UnbindingMdibVersion(ConvertToCDM::convert(value));
	return *this;
}

bool PatientContextState::getUnbindingMdibVersion(ReferencedVersion & out) const {
	if (data->UnbindingMdibVersion().present()) {
		out = ConvertFromCDM::convert(data->UnbindingMdibVersion().get());
		return true;
	}
	return false;
}

ReferencedVersion PatientContextState::getUnbindingMdibVersion() const {
	return ConvertFromCDM::convert(data->UnbindingMdibVersion().get());
}
	
bool PatientContextState::hasUnbindingMdibVersion() const {
	return data->UnbindingMdibVersion().present();
}
	
PatientContextState & PatientContextState::setBindingStartTime(const Timestamp & value) {
	data->BindingStartTime(ConvertToCDM::convert(value));
	return *this;
}

bool PatientContextState::getBindingStartTime(Timestamp & out) const {
	if (data->BindingStartTime().present()) {
		out = ConvertFromCDM::convert(data->BindingStartTime().get());
		return true;
	}
	return false;
}

Timestamp PatientContextState::getBindingStartTime() const {
	return ConvertFromCDM::convert(data->BindingStartTime().get());
}
	
bool PatientContextState::hasBindingStartTime() const {
	return data->BindingStartTime().present();
}
	
PatientContextState & PatientContextState::setBindingEndTime(const Timestamp & value) {
	data->BindingEndTime(ConvertToCDM::convert(value));
	return *this;
}

bool PatientContextState::getBindingEndTime(Timestamp & out) const {
	if (data->BindingEndTime().present()) {
		out = ConvertFromCDM::convert(data->BindingEndTime().get());
		return true;
	}
	return false;
}

Timestamp PatientContextState::getBindingEndTime() const {
	return ConvertFromCDM::convert(data->BindingEndTime().get());
}
	
bool PatientContextState::hasBindingEndTime() const {
	return data->BindingEndTime().present();
}
	
PatientContextState & PatientContextState::addValidator(const InstanceIdentifier & value) {
	data->Validator().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<InstanceIdentifier> PatientContextState::getValidatorList() const {
	std::vector<InstanceIdentifier> result;
	result.reserve(data->Validator().size());
	for (const auto & value: data->Validator()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void PatientContextState::clearValidatorList() {
	data->Validator().clear();
}

PatientContextState & PatientContextState::addIdentification(const InstanceIdentifier & value) {
	data->Identification().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<InstanceIdentifier> PatientContextState::getIdentificationList() const {
	std::vector<InstanceIdentifier> result;
	result.reserve(data->Identification().size());
	for (const auto & value: data->Identification()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void PatientContextState::clearIdentificationList() {
	data->Identification().clear();
}

PatientContextState & PatientContextState::setCoreData(const PatientDemographicsCoreData & value) {
	data->CoreData(ConvertToCDM::convert(value));
	return *this;
}

bool PatientContextState::getCoreData(PatientDemographicsCoreData & out) const {
	if (data->CoreData().present()) {
		out = ConvertFromCDM::convert(data->CoreData().get());
		return true;
	}
	return false;
}

PatientDemographicsCoreData PatientContextState::getCoreData() const {
	return ConvertFromCDM::convert(data->CoreData().get());
}
	
bool PatientContextState::hasCoreData() const {
	return data->CoreData().present();
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

