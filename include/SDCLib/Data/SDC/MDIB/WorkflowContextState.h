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
 *  Author: besting, buerger, roehser
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

#include "SDCLib/Data/SDC/MDIB/SimpleTypesMapping.h"
#include "SDCLib/Data/SDC/SDC-fwd.h"
#include "DataModel/osdm-fwd.hxx"

namespace SDCLib {
namespace Data {
namespace SDC {

class WorkflowContextState {
private:
	WorkflowContextState(const CDM::WorkflowContextState & object);
	operator CDM::WorkflowContextState() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class SDCProvider;
	friend class SDCConsumer;
	friend class MdState;
	friend class MdDescription;
public:
	WorkflowContextState(
		HandleRef descriptorhandle
		,
		Handle handle
	);
private:
	WorkflowContextState(){};
public:
	WorkflowContextState(const WorkflowContextState & object);
	virtual ~WorkflowContextState();

    void copyFrom(const WorkflowContextState & object);
    WorkflowContextState & operator=(const WorkflowContextState & object);

    typedef CDM::WorkflowContextState WrappedType;
    typedef WorkflowContextDescriptor DescriptorType;

	WorkflowContextState & setStateVersion(const VersionCounter & value);
	VersionCounter getStateVersion() const;
	bool getStateVersion(VersionCounter & out) const;
	bool hasStateVersion() const;

	WorkflowContextState & setDescriptorHandle(const HandleRef & value);
	HandleRef getDescriptorHandle() const;

	WorkflowContextState & setDescriptorVersion(const ReferencedVersion & value);
	ReferencedVersion getDescriptorVersion() const;
	bool getDescriptorVersion(ReferencedVersion & out) const;
	bool hasDescriptorVersion() const;

	WorkflowContextState & setCategory(const CodedValue & value);
	CodedValue getCategory() const;
	bool getCategory(CodedValue & out) const;
	bool hasCategory() const;

	WorkflowContextState & setHandle(const Handle & value);
	Handle getHandle() const;

	WorkflowContextState & setContextAssociation(const ContextAssociation & value);
	ContextAssociation getContextAssociation() const;
	bool getContextAssociation(ContextAssociation & out) const;
	bool hasContextAssociation() const;

	WorkflowContextState & setBindingMdibVersion(const ReferencedVersion & value);
	ReferencedVersion getBindingMdibVersion() const;
	bool getBindingMdibVersion(ReferencedVersion & out) const;
	bool hasBindingMdibVersion() const;

	WorkflowContextState & setUnbindingMdibVersion(const ReferencedVersion & value);
	ReferencedVersion getUnbindingMdibVersion() const;
	bool getUnbindingMdibVersion(ReferencedVersion & out) const;
	bool hasUnbindingMdibVersion() const;

	WorkflowContextState & setBindingStartTime(const Timestamp & value);
	Timestamp getBindingStartTime() const;
	bool getBindingStartTime(Timestamp & out) const;
	bool hasBindingStartTime() const;

	WorkflowContextState & setBindingEndTime(const Timestamp & value);
	Timestamp getBindingEndTime() const;
	bool getBindingEndTime(Timestamp & out) const;
	bool hasBindingEndTime() const;

	WorkflowContextState & addValidator(const InstanceIdentifier & value);
	std::vector<InstanceIdentifier> getValidatorList() const;
	void clearValidatorList();

	WorkflowContextState & addIdentification(const InstanceIdentifier & value);
	std::vector<InstanceIdentifier> getIdentificationList() const;
	void clearIdentificationList();

	WorkflowContextState & setWorkflowDetail(const WorkflowDetail & value);
	WorkflowDetail getWorkflowDetail() const;
	bool getWorkflowDetail(WorkflowDetail & out) const;
	bool hasWorkflowDetail() const;

private:
	std::shared_ptr<CDM::WorkflowContextState> data;
};

} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */
#endif /* WORKFLOWCONTEXTSTATE_H_ */
