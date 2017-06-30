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
 *  EnsembleContextState.h
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

#ifndef ENSEMBLECONTEXTSTATE_H_
#define ENSEMBLECONTEXTSTATE_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class EnsembleContextState {
private:
	EnsembleContextState(const CDM::EnsembleContextState & object);
	operator CDM::EnsembleContextState() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	EnsembleContextState();
	EnsembleContextState(const EnsembleContextState & object);
	virtual ~EnsembleContextState();
    
    void copyFrom(const EnsembleContextState & object);
    EnsembleContextState & operator=(const EnsembleContextState & object);
    
    typedef CDM::EnsembleContextState WrappedType;
    typedef EnsembleContextDescriptor DescriptorType;

	EnsembleContextState & setStateVersion(const VersionCounter & value);
	VersionCounter getStateVersion() const;

	EnsembleContextState & setDescriptorHandle(const HandleRef & value);
	HandleRef getDescriptorHandle() const;

	EnsembleContextState & setDescriptorVersion(const ReferencedVersion & value);
	ReferencedVersion getDescriptorVersion() const;

	EnsembleContextState & setCategory(const CodedValue & value);
	CodedValue getCategory() const;
	bool getCategory(CodedValue & out) const;
	bool hasCategory() const;

	EnsembleContextState & setHandle(const Handle & value);
	Handle getHandle() const;

	EnsembleContextState & setContextAssociation(const ContextAssociation & value);
	ContextAssociation getContextAssociation() const;

	EnsembleContextState & setBindingMdibVersion(const ReferencedVersion & value);
	ReferencedVersion getBindingMdibVersion() const;
	bool getBindingMdibVersion(ReferencedVersion & out) const;
	bool hasBindingMdibVersion() const;

	EnsembleContextState & setUnbindingMdibVersion(const ReferencedVersion & value);
	ReferencedVersion getUnbindingMdibVersion() const;

	EnsembleContextState & setBindingStartTime(const Timestamp & value);
	Timestamp getBindingStartTime() const;

	EnsembleContextState & setBindingEndTime(const Timestamp & value);
	Timestamp getBindingEndTime() const;

	EnsembleContextState & addValidator(const InstanceIdentifier & value);
	std::vector<InstanceIdentifier> getValidatorLists() const;
	void clearValidatorLists();
	
	EnsembleContextState & addIdentification(const InstanceIdentifier & value);
	std::vector<InstanceIdentifier> getIdentificationLists() const;
	void clearIdentificationLists();
	
private:
	std::shared_ptr<CDM::EnsembleContextState> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* ENSEMBLECONTEXTSTATE_H_ */
