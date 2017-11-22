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
 *  LocationContextState.h
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

#ifndef LOCATIONCONTEXTSTATE_H_
#define LOCATIONCONTEXTSTATE_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class LocationContextState {
private:
	LocationContextState(const CDM::LocationContextState & object);
	operator CDM::LocationContextState() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class OSCPProvider;
	friend class OSCPConsumer;
public:
	LocationContextState(
		HandleRef descriptorhandle
		, 
		Handle handle
	); 
private:
	LocationContextState(){};
public:
	LocationContextState(const LocationContextState & object);
	virtual ~LocationContextState();
    
    void copyFrom(const LocationContextState & object);
    LocationContextState & operator=(const LocationContextState & object);
    
    typedef CDM::LocationContextState WrappedType;
    typedef LocationContextDescriptor DescriptorType;

	LocationContextState & setStateVersion(const VersionCounter & value);
	VersionCounter getStateVersion() const;
	bool getStateVersion(VersionCounter & out) const;
	bool hasStateVersion() const;

	LocationContextState & setDescriptorHandle(const HandleRef & value);
	HandleRef getDescriptorHandle() const;

	LocationContextState & setDescriptorVersion(const ReferencedVersion & value);
	ReferencedVersion getDescriptorVersion() const;
	bool getDescriptorVersion(ReferencedVersion & out) const;
	bool hasDescriptorVersion() const;

	LocationContextState & setCategory(const CodedValue & value);
	CodedValue getCategory() const;
	bool getCategory(CodedValue & out) const;
	bool hasCategory() const;

	LocationContextState & setHandle(const Handle & value);
	Handle getHandle() const;

	LocationContextState & setContextAssociation(const ContextAssociation & value);
	ContextAssociation getContextAssociation() const;
	bool getContextAssociation(ContextAssociation & out) const;
	bool hasContextAssociation() const;

	LocationContextState & setBindingMdibVersion(const ReferencedVersion & value);
	ReferencedVersion getBindingMdibVersion() const;
	bool getBindingMdibVersion(ReferencedVersion & out) const;
	bool hasBindingMdibVersion() const;

	LocationContextState & setUnbindingMdibVersion(const ReferencedVersion & value);
	ReferencedVersion getUnbindingMdibVersion() const;
	bool getUnbindingMdibVersion(ReferencedVersion & out) const;
	bool hasUnbindingMdibVersion() const;

	LocationContextState & setBindingStartTime(const Timestamp & value);
	Timestamp getBindingStartTime() const;
	bool getBindingStartTime(Timestamp & out) const;
	bool hasBindingStartTime() const;

	LocationContextState & setBindingEndTime(const Timestamp & value);
	Timestamp getBindingEndTime() const;
	bool getBindingEndTime(Timestamp & out) const;
	bool hasBindingEndTime() const;

	LocationContextState & addValidator(const InstanceIdentifier & value);
	std::vector<InstanceIdentifier> getValidatorList() const;
	void clearValidatorList();
	
	LocationContextState & addIdentification(const InstanceIdentifier & value);
	std::vector<InstanceIdentifier> getIdentificationList() const;
	void clearIdentificationList();
	
	LocationContextState & setLocationDetail(const LocationDetail & value);
	LocationDetail getLocationDetail() const;
	bool getLocationDetail(LocationDetail & out) const;
	bool hasLocationDetail() const;

private:
	std::shared_ptr<CDM::LocationContextState> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* LOCATIONCONTEXTSTATE_H_ */
