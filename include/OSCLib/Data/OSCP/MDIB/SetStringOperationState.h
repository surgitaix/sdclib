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
 *  SetStringOperationState.h
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

#ifndef SETSTRINGOPERATIONSTATE_H_
#define SETSTRINGOPERATIONSTATE_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class SetStringOperationState {
private:
	SetStringOperationState(const CDM::SetStringOperationState & object);
	operator CDM::SetStringOperationState() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class OSCPProvider;
	friend class OSCPConsumer;
public:
	SetStringOperationState(
		HandleRef descriptorhandle
		, 
		OperatingMode operatingmode
	); 
private:
	SetStringOperationState(){};
public:
	SetStringOperationState(const SetStringOperationState & object);
	virtual ~SetStringOperationState();
    
    void copyFrom(const SetStringOperationState & object);
    SetStringOperationState & operator=(const SetStringOperationState & object);
    
    typedef CDM::SetStringOperationState WrappedType;

	SetStringOperationState & setStateVersion(const VersionCounter & value);
	VersionCounter getStateVersion() const;
	bool getStateVersion(VersionCounter & out) const;
	bool hasStateVersion() const;

	SetStringOperationState & setDescriptorHandle(const HandleRef & value);
	HandleRef getDescriptorHandle() const;

	SetStringOperationState & setDescriptorVersion(const ReferencedVersion & value);
	ReferencedVersion getDescriptorVersion() const;
	bool getDescriptorVersion(ReferencedVersion & out) const;
	bool hasDescriptorVersion() const;

	SetStringOperationState & setOperatingMode(const OperatingMode & value);
	OperatingMode getOperatingMode() const;

	SetStringOperationState & setAllowedValues(const AllowedValues & value);
	AllowedValues getAllowedValues() const;
	bool getAllowedValues(AllowedValues & out) const;
	bool hasAllowedValues() const;

private:
	std::shared_ptr<CDM::SetStringOperationState> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* SETSTRINGOPERATIONSTATE_H_ */
