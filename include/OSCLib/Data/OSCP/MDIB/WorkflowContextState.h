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
 *  WorkflowContextState.h
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

#ifndef WORKFLOWCONTEXTSTATE_H_
#define WORKFLOWCONTEXTSTATE_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class WorkflowContextState {
private:
	WorkflowContextState(const CDM::WorkflowContextState & object);
	operator CDM::WorkflowContextState() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	WorkflowContextState();
	WorkflowContextState(const WorkflowContextState & object);
	virtual ~WorkflowContextState();
    
    void copyFrom(const WorkflowContextState & object);
    WorkflowContextState & operator=(const WorkflowContextState & object);
    
    typedef CDM::WorkflowContextState WrappedType;

	WorkflowContextState & setStateVersion(const VersionCounter & value);
	VersionCounter getStateVersion() const;

	WorkflowContextState & setDescriptorHandle(const HandleRef & value);
	HandleRef getDescriptorHandle() const;

	WorkflowContextState & setDescriptorVersion(const ReferencedVersion & value);
	ReferencedVersion getDescriptorVersion() const;

	WorkflowContextState & setCategory(const CodedValue & value);
	CodedValue getCategory() const;
	bool getCategory(CodedValue & out) const;
	bool hasCategory() const;

	WorkflowContextState & setHandle(const Handle & value);
	Handle getHandle() const;

	WorkflowContextState & setContextAssociation(const ContextAssociation & value);
	ContextAssociation getContextAssociation() const;

	WorkflowContextState & setBindingMdibVersion(const ReferencedVersion & value);
	ReferencedVersion getBindingMdibVersion() const;
	bool getBindingMdibVersion(ReferencedVersion & out) const;
	bool hasBindingMdibVersion() const;

	WorkflowContextState & setUnbindingMdibVersion(const ReferencedVersion & value);
	ReferencedVersion getUnbindingMdibVersion() const;

	WorkflowContextState & setBindingStartTime(const Timestamp & value);
	Timestamp getBindingStartTime() const;

	WorkflowContextState & setBindingEndTime(const Timestamp & value);
	Timestamp getBindingEndTime() const;

	WorkflowContextState & addValidator(const InstanceIdentifier & value);
	std::vector<InstanceIdentifier> getValidators() const;
	void clearValidators();
	
	WorkflowContextState & addIdentification(const InstanceIdentifier & value);
	std::vector<InstanceIdentifier> getIdentifications() const;
	void clearIdentifications();
	
	WorkflowContextState & setPatient(const PersonReference & value);
	PersonReference getPatient() const;

	WorkflowContextState & setAssignedLocation(const LocationReference & value);
	LocationReference getAssignedLocation() const;
	bool getAssignedLocation(LocationReference & out) const;
	bool hasAssignedLocation() const;

	WorkflowContextState & setVisitNumber(const InstanceIdentifier & value);
	InstanceIdentifier getVisitNumber() const;
	bool getVisitNumber(InstanceIdentifier & out) const;
	bool hasVisitNumber() const;

	WorkflowContextState & setReferringPhysician(const PersonReference & value);
	PersonReference getReferringPhysician() const;
	bool getReferringPhysician(PersonReference & out) const;
	bool hasReferringPhysician() const;

	WorkflowContextState & setRequestingPhysician(const PersonReference & value);
	PersonReference getRequestingPhysician() const;
	bool getRequestingPhysician(PersonReference & out) const;
	bool hasRequestingPhysician() const;

	WorkflowContextState & setPlacerOrderNumber(const InstanceIdentifier & value);
	InstanceIdentifier getPlacerOrderNumber() const;

	WorkflowContextState & setFillerOrderNumber(const InstanceIdentifier & value);
	InstanceIdentifier getFillerOrderNumber() const;
	bool getFillerOrderNumber(InstanceIdentifier & out) const;
	bool hasFillerOrderNumber() const;

	WorkflowContextState & addDangerCode(const CodedValue & value);
	std::vector<CodedValue> getDangerCodes() const;
	void clearDangerCodes();
	
	WorkflowContextState & addRelevantClinicalInfo(const ClinicalInfo & value);
	std::vector<ClinicalInfo> getRelevantClinicalInfos() const;
	void clearRelevantClinicalInfos();
	
	WorkflowContextState & addResultingClinicalInfo(const ClinicalInfo & value);
	std::vector<ClinicalInfo> getResultingClinicalInfos() const;
	void clearResultingClinicalInfos();
	
private:
	std::shared_ptr<CDM::WorkflowContextState> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* WORKFLOWCONTEXTSTATE_H_ */
