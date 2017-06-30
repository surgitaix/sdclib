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
 *  Author: besting, roehser
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

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class OperatorContextState {
private:
	OperatorContextState(const CDM::OperatorContextState & object);
	operator CDM::OperatorContextState() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	OperatorContextState();
	OperatorContextState(const OperatorContextState & object);
	virtual ~OperatorContextState();
    
    void copyFrom(const OperatorContextState & object);
    OperatorContextState & operator=(const OperatorContextState & object);
    
    typedef CDM::OperatorContextState WrappedType;
    typedef OperatorContextDescriptor DescriptorType;

	OperatorContextState & setStateVersion(const VersionCounter & value);
	VersionCounter getStateVersion() const;

	OperatorContextState & setDescriptorHandle(const HandleRef & value);
	HandleRef getDescriptorHandle() const;

	OperatorContextState & setDescriptorVersion(const ReferencedVersion & value);
	ReferencedVersion getDescriptorVersion() const;

	OperatorContextState & setCategory(const CodedValue & value);
	CodedValue getCategory() const;
	bool getCategory(CodedValue & out) const;
	bool hasCategory() const;

	OperatorContextState & setHandle(const Handle & value);
	Handle getHandle() const;

	OperatorContextState & setContextAssociation(const ContextAssociation & value);
	ContextAssociation getContextAssociation() const;

	OperatorContextState & setBindingMdibVersion(const ReferencedVersion & value);
	ReferencedVersion getBindingMdibVersion() const;
	bool getBindingMdibVersion(ReferencedVersion & out) const;
	bool hasBindingMdibVersion() const;

	OperatorContextState & setUnbindingMdibVersion(const ReferencedVersion & value);
	ReferencedVersion getUnbindingMdibVersion() const;

	OperatorContextState & setBindingStartTime(const Timestamp & value);
	Timestamp getBindingStartTime() const;

	OperatorContextState & setBindingEndTime(const Timestamp & value);
	Timestamp getBindingEndTime() const;

	OperatorContextState & addValidator(const InstanceIdentifier & value);
	std::vector<InstanceIdentifier> getValidatorLists() const;
	void clearValidatorLists();
	
	OperatorContextState & addIdentification(const InstanceIdentifier & value);
	std::vector<InstanceIdentifier> getIdentificationLists() const;
	void clearIdentificationLists();
	
	OperatorContextState & setOperatorDetails(const BaseDemographics & value);
	BaseDemographics getOperatorDetails() const;

private:
	std::shared_ptr<CDM::OperatorContextState> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* OPERATORCONTEXTSTATE_H_ */
