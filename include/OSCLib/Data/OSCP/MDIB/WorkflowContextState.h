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

#include "OSCLib/Data/OSCP/MDIB/EnumMappings.h"
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
    typedef WorkflowContextDescriptor DescriptorType;

	WorkflowContextState & setHandle(const std::string & value);
	std::string getHandle() const;
	bool getHandle(std::string & out) const;
	bool hasHandle() const;

	WorkflowContextState & setDescriptorHandle(const std::string & value);
	std::string getDescriptorHandle() const;

	WorkflowContextState & setStateVersion(const VersionCounter & value);
	VersionCounter getStateVersion() const;
	bool getStateVersion(VersionCounter & out) const;
	bool hasStateVersion() const;

	WorkflowContextState & setContextAssociation(const ContextAssociation & value);
	ContextAssociation getContextAssociation() const;
	bool getContextAssociation(ContextAssociation & out) const;
	bool hasContextAssociation() const;

	WorkflowContextState & setBindingMDIBVersion(const ReferencedVersion & value);
	ReferencedVersion getBindingMDIBVersion() const;

	WorkflowContextState & setUnbindingMDIBVersion(const ReferencedVersion & value);
	ReferencedVersion getUnbindingMDIBVersion() const;
	bool getUnbindingMDIBVersion(ReferencedVersion & out) const;
	bool hasUnbindingMDIBVersion() const;

	WorkflowContextState & setBindingStartTime(const Timestamp & value);
	Timestamp getBindingStartTime() const;
	bool getBindingStartTime(Timestamp & out) const;
	bool hasBindingStartTime() const;

	WorkflowContextState & setBindingEndTime(const Timestamp & value);
	Timestamp getBindingEndTime() const;
	bool getBindingEndTime(Timestamp & out) const;
	bool hasBindingEndTime() const;

	WorkflowContextState & addValidator(const InstanceIdentifier & value);
	std::vector<InstanceIdentifier> getValidators() const;
	void clearValidators();
	
	WorkflowContextState & addIdentification(const InstanceIdentifier & value);
	std::vector<InstanceIdentifier> getIdentifications() const;
	void clearIdentifications();
	
	WorkflowContextState & setOrderDetail(const Order & value);
	Order getOrderDetail() const;
	bool getOrderDetail(Order & out) const;
	bool hasOrderDetail() const;

private:
	std::shared_ptr<CDM::WorkflowContextState> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* WORKFLOWCONTEXTSTATE_H_ */
