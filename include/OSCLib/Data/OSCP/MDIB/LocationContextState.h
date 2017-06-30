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
 *  Author: besting, roehser
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
public:
	LocationContextState();
	LocationContextState(const LocationContextState & object);
	virtual ~LocationContextState();
    
    void copyFrom(const LocationContextState & object);
    LocationContextState & operator=(const LocationContextState & object);
    
    typedef CDM::LocationContextState WrappedType;
    typedef LocationContextDescriptor DescriptorType;

	LocationContextState & setStateVersion(const VersionCounter & value);
	VersionCounter getStateVersion() const;

	LocationContextState & setDescriptorHandle(const HandleRef & value);
	HandleRef getDescriptorHandle() const;

	LocationContextState & setDescriptorVersion(const ReferencedVersion & value);
	ReferencedVersion getDescriptorVersion() const;

	LocationContextState & setCategory(const CodedValue & value);
	CodedValue getCategory() const;
	bool getCategory(CodedValue & out) const;
	bool hasCategory() const;

	LocationContextState & setHandle(const Handle & value);
	Handle getHandle() const;

	LocationContextState & setContextAssociation(const ContextAssociation & value);
	ContextAssociation getContextAssociation() const;

	LocationContextState & setBindingMdibVersion(const ReferencedVersion & value);
	ReferencedVersion getBindingMdibVersion() const;
	bool getBindingMdibVersion(ReferencedVersion & out) const;
	bool hasBindingMdibVersion() const;

	LocationContextState & setUnbindingMdibVersion(const ReferencedVersion & value);
	ReferencedVersion getUnbindingMdibVersion() const;

	LocationContextState & setBindingStartTime(const Timestamp & value);
	Timestamp getBindingStartTime() const;

	LocationContextState & setBindingEndTime(const Timestamp & value);
	Timestamp getBindingEndTime() const;

	LocationContextState & addValidator(const InstanceIdentifier & value);
	std::vector<InstanceIdentifier> getValidatorLists() const;
	void clearValidatorLists();
	
	LocationContextState & addIdentification(const InstanceIdentifier & value);
	std::vector<InstanceIdentifier> getIdentificationLists() const;
	void clearIdentificationLists();
	
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
