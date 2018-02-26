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
 *  OperatorContextState.h
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

#ifndef OPERATORCONTEXTSTATE_H_
#define OPERATORCONTEXTSTATE_H_

#include "OSCLib/Data/SDC/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/SDC/SDC-fwd.h"
#include "osdm-fwd.hxx"

namespace SDCLib {
namespace Data {
namespace SDC {

class OperatorContextState {
private:
	OperatorContextState(const CDM::OperatorContextState & object);
	operator CDM::OperatorContextState() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class SDCProvider;
	friend class SDCConsumer;
	friend class MdState;
	friend class MdDescription;
public:
	OperatorContextState(
		HandleRef descriptorhandle
		, 
		Handle handle
	); 
private:
	OperatorContextState(){};
public:
	OperatorContextState(const OperatorContextState & object);
	virtual ~OperatorContextState();
    
    void copyFrom(const OperatorContextState & object);
    OperatorContextState & operator=(const OperatorContextState & object);
    
    typedef CDM::OperatorContextState WrappedType;
    typedef OperatorContextDescriptor DescriptorType;

	OperatorContextState & setStateVersion(const VersionCounter & value);
	VersionCounter getStateVersion() const;
	bool getStateVersion(VersionCounter & out) const;
	bool hasStateVersion() const;

	OperatorContextState & setDescriptorHandle(const HandleRef & value);
	HandleRef getDescriptorHandle() const;

	OperatorContextState & setDescriptorVersion(const ReferencedVersion & value);
	ReferencedVersion getDescriptorVersion() const;
	bool getDescriptorVersion(ReferencedVersion & out) const;
	bool hasDescriptorVersion() const;

	OperatorContextState & setCategory(const CodedValue & value);
	CodedValue getCategory() const;
	bool getCategory(CodedValue & out) const;
	bool hasCategory() const;

	OperatorContextState & setHandle(const Handle & value);
	Handle getHandle() const;

	OperatorContextState & setContextAssociation(const ContextAssociation & value);
	ContextAssociation getContextAssociation() const;
	bool getContextAssociation(ContextAssociation & out) const;
	bool hasContextAssociation() const;

	OperatorContextState & setBindingMdibVersion(const ReferencedVersion & value);
	ReferencedVersion getBindingMdibVersion() const;
	bool getBindingMdibVersion(ReferencedVersion & out) const;
	bool hasBindingMdibVersion() const;

	OperatorContextState & setUnbindingMdibVersion(const ReferencedVersion & value);
	ReferencedVersion getUnbindingMdibVersion() const;
	bool getUnbindingMdibVersion(ReferencedVersion & out) const;
	bool hasUnbindingMdibVersion() const;

	OperatorContextState & setBindingStartTime(const Timestamp & value);
	Timestamp getBindingStartTime() const;
	bool getBindingStartTime(Timestamp & out) const;
	bool hasBindingStartTime() const;

	OperatorContextState & setBindingEndTime(const Timestamp & value);
	Timestamp getBindingEndTime() const;
	bool getBindingEndTime(Timestamp & out) const;
	bool hasBindingEndTime() const;

	OperatorContextState & addValidator(const InstanceIdentifier & value);
	std::vector<InstanceIdentifier> getValidatorList() const;
	void clearValidatorList();
	
	OperatorContextState & addIdentification(const InstanceIdentifier & value);
	std::vector<InstanceIdentifier> getIdentificationList() const;
	void clearIdentificationList();
	
	OperatorContextState & setOperatorDetails(const BaseDemographics & value);
	BaseDemographics getOperatorDetails() const;
	bool getOperatorDetails(BaseDemographics & out) const;
	bool hasOperatorDetails() const;

private:
	std::shared_ptr<CDM::OperatorContextState> data;
};

} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */
#endif /* OPERATORCONTEXTSTATE_H_ */
