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

#include "OSCLib/Data/OSCP/MDIB/PersonReference.h"
#include "OSCLib/Data/OSCP/MDIB/LocationReference.h"
#include "OSCLib/Data/OSCP/MDIB/InstanceIdentifier.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/ClinicalInfo.h"
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

WorkflowContextState & WorkflowContextState::setPatient(const PersonReference & value) {
	data->Patient(ConvertToCDM::convert(value));
	return *this;
}


PersonReference WorkflowContextState::getPatient() const {
	return ConvertFromCDM::convert(data->Patient());
}
	
WorkflowContextState & WorkflowContextState::setAssignedLocation(const LocationReference & value) {
	data->AssignedLocation(ConvertToCDM::convert(value));
	return *this;
}

bool WorkflowContextState::getAssignedLocation(LocationReference & out) const {
	if (data->AssignedLocation().present()) {
		out = ConvertFromCDM::convert(data->AssignedLocation().get());
		return true;
	}
	return false;
}

LocationReference WorkflowContextState::getAssignedLocation() const {
	return ConvertFromCDM::convert(data->AssignedLocation().get());
}
	
bool WorkflowContextState::hasAssignedLocation() const {
	return data->AssignedLocation().present();
}
	
WorkflowContextState & WorkflowContextState::setVisitNumber(const InstanceIdentifier & value) {
	data->VisitNumber(ConvertToCDM::convert(value));
	return *this;
}

bool WorkflowContextState::getVisitNumber(InstanceIdentifier & out) const {
	if (data->VisitNumber().present()) {
		out = ConvertFromCDM::convert(data->VisitNumber().get());
		return true;
	}
	return false;
}

InstanceIdentifier WorkflowContextState::getVisitNumber() const {
	return ConvertFromCDM::convert(data->VisitNumber().get());
}
	
bool WorkflowContextState::hasVisitNumber() const {
	return data->VisitNumber().present();
}
	
WorkflowContextState & WorkflowContextState::setReferringPhysician(const PersonReference & value) {
	data->ReferringPhysician(ConvertToCDM::convert(value));
	return *this;
}

bool WorkflowContextState::getReferringPhysician(PersonReference & out) const {
	if (data->ReferringPhysician().present()) {
		out = ConvertFromCDM::convert(data->ReferringPhysician().get());
		return true;
	}
	return false;
}

PersonReference WorkflowContextState::getReferringPhysician() const {
	return ConvertFromCDM::convert(data->ReferringPhysician().get());
}
	
bool WorkflowContextState::hasReferringPhysician() const {
	return data->ReferringPhysician().present();
}
	
WorkflowContextState & WorkflowContextState::setRequestingPhysician(const PersonReference & value) {
	data->RequestingPhysician(ConvertToCDM::convert(value));
	return *this;
}

bool WorkflowContextState::getRequestingPhysician(PersonReference & out) const {
	if (data->RequestingPhysician().present()) {
		out = ConvertFromCDM::convert(data->RequestingPhysician().get());
		return true;
	}
	return false;
}

PersonReference WorkflowContextState::getRequestingPhysician() const {
	return ConvertFromCDM::convert(data->RequestingPhysician().get());
}
	
bool WorkflowContextState::hasRequestingPhysician() const {
	return data->RequestingPhysician().present();
}
	
WorkflowContextState & WorkflowContextState::setPlacerOrderNumber(const InstanceIdentifier & value) {
	data->PlacerOrderNumber(ConvertToCDM::convert(value));
	return *this;
}


InstanceIdentifier WorkflowContextState::getPlacerOrderNumber() const {
	return ConvertFromCDM::convert(data->PlacerOrderNumber());
}
	
WorkflowContextState & WorkflowContextState::setFillerOrderNumber(const InstanceIdentifier & value) {
	data->FillerOrderNumber(ConvertToCDM::convert(value));
	return *this;
}

bool WorkflowContextState::getFillerOrderNumber(InstanceIdentifier & out) const {
	if (data->FillerOrderNumber().present()) {
		out = ConvertFromCDM::convert(data->FillerOrderNumber().get());
		return true;
	}
	return false;
}

InstanceIdentifier WorkflowContextState::getFillerOrderNumber() const {
	return ConvertFromCDM::convert(data->FillerOrderNumber().get());
}
	
bool WorkflowContextState::hasFillerOrderNumber() const {
	return data->FillerOrderNumber().present();
}
	
WorkflowContextState & WorkflowContextState::addDangerCode(const CodedValue & value) {
	data->DangerCode().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<CodedValue> WorkflowContextState::getDangerCodeLists() const {
	std::vector<CodedValue> result;
	result.reserve(data->DangerCode().size());
	for (const auto & value: data->DangerCode()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void WorkflowContextState::clearDangerCodeLists() {
	data->DangerCode().clear();
}

WorkflowContextState & WorkflowContextState::addRelevantClinicalInfo(const ClinicalInfo & value) {
	data->RelevantClinicalInfo().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<ClinicalInfo> WorkflowContextState::getRelevantClinicalInfoLists() const {
	std::vector<ClinicalInfo> result;
	result.reserve(data->RelevantClinicalInfo().size());
	for (const auto & value: data->RelevantClinicalInfo()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void WorkflowContextState::clearRelevantClinicalInfoLists() {
	data->RelevantClinicalInfo().clear();
}

WorkflowContextState & WorkflowContextState::addResultingClinicalInfo(const ClinicalInfo & value) {
	data->ResultingClinicalInfo().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<ClinicalInfo> WorkflowContextState::getResultingClinicalInfoLists() const {
	std::vector<ClinicalInfo> result;
	result.reserve(data->ResultingClinicalInfo().size());
	for (const auto & value: data->ResultingClinicalInfo()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void WorkflowContextState::clearResultingClinicalInfoLists() {
	data->ResultingClinicalInfo().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

