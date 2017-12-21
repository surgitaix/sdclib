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
 *  MeansContextState.h
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

#ifndef MEANSCONTEXTSTATE_H_
#define MEANSCONTEXTSTATE_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class MeansContextState {
private:
	MeansContextState(const CDM::MeansContextState & object);
	operator CDM::MeansContextState() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class OSCPProvider;
	friend class OSCPConsumer;
	friend class MdState;
	friend class MdDescription;
public:
	MeansContextState(
		HandleRef descriptorhandle
		, 
		Handle handle
	); 
private:
	MeansContextState(){};
public:
	MeansContextState(const MeansContextState & object);
	virtual ~MeansContextState();
    
    void copyFrom(const MeansContextState & object);
    MeansContextState & operator=(const MeansContextState & object);
    
    typedef CDM::MeansContextState WrappedType;

	MeansContextState & setStateVersion(const VersionCounter & value);
	VersionCounter getStateVersion() const;
	bool getStateVersion(VersionCounter & out) const;
	bool hasStateVersion() const;

	MeansContextState & setDescriptorHandle(const HandleRef & value);
	HandleRef getDescriptorHandle() const;

	MeansContextState & setDescriptorVersion(const ReferencedVersion & value);
	ReferencedVersion getDescriptorVersion() const;
	bool getDescriptorVersion(ReferencedVersion & out) const;
	bool hasDescriptorVersion() const;

	MeansContextState & setCategory(const CodedValue & value);
	CodedValue getCategory() const;
	bool getCategory(CodedValue & out) const;
	bool hasCategory() const;

	MeansContextState & setHandle(const Handle & value);
	Handle getHandle() const;

	MeansContextState & setContextAssociation(const ContextAssociation & value);
	ContextAssociation getContextAssociation() const;
	bool getContextAssociation(ContextAssociation & out) const;
	bool hasContextAssociation() const;

	MeansContextState & setBindingMdibVersion(const ReferencedVersion & value);
	ReferencedVersion getBindingMdibVersion() const;
	bool getBindingMdibVersion(ReferencedVersion & out) const;
	bool hasBindingMdibVersion() const;

	MeansContextState & setUnbindingMdibVersion(const ReferencedVersion & value);
	ReferencedVersion getUnbindingMdibVersion() const;
	bool getUnbindingMdibVersion(ReferencedVersion & out) const;
	bool hasUnbindingMdibVersion() const;

	MeansContextState & setBindingStartTime(const Timestamp & value);
	Timestamp getBindingStartTime() const;
	bool getBindingStartTime(Timestamp & out) const;
	bool hasBindingStartTime() const;

	MeansContextState & setBindingEndTime(const Timestamp & value);
	Timestamp getBindingEndTime() const;
	bool getBindingEndTime(Timestamp & out) const;
	bool hasBindingEndTime() const;

	MeansContextState & addValidator(const InstanceIdentifier & value);
	std::vector<InstanceIdentifier> getValidatorList() const;
	void clearValidatorList();
	
	MeansContextState & addIdentification(const InstanceIdentifier & value);
	std::vector<InstanceIdentifier> getIdentificationList() const;
	void clearIdentificationList();
	
private:
	std::shared_ptr<CDM::MeansContextState> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* MEANSCONTEXTSTATE_H_ */
