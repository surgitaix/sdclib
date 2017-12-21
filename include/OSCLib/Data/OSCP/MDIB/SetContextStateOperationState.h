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
 *  SetContextStateOperationState.h
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

#ifndef SETCONTEXTSTATEOPERATIONSTATE_H_
#define SETCONTEXTSTATEOPERATIONSTATE_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class SetContextStateOperationState {
private:
	SetContextStateOperationState(const CDM::SetContextStateOperationState & object);
	operator CDM::SetContextStateOperationState() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class OSCPProvider;
	friend class OSCPConsumer;
	friend class MdState;
	friend class MdDescription;
public:
	SetContextStateOperationState(
		HandleRef descriptorhandle
		, 
		OperatingMode operatingmode
	); 
private:
	SetContextStateOperationState(){};
public:
	SetContextStateOperationState(const SetContextStateOperationState & object);
	virtual ~SetContextStateOperationState();
    
    void copyFrom(const SetContextStateOperationState & object);
    SetContextStateOperationState & operator=(const SetContextStateOperationState & object);
    
    typedef CDM::SetContextStateOperationState WrappedType;

	SetContextStateOperationState & setStateVersion(const VersionCounter & value);
	VersionCounter getStateVersion() const;
	bool getStateVersion(VersionCounter & out) const;
	bool hasStateVersion() const;

	SetContextStateOperationState & setDescriptorHandle(const HandleRef & value);
	HandleRef getDescriptorHandle() const;

	SetContextStateOperationState & setDescriptorVersion(const ReferencedVersion & value);
	ReferencedVersion getDescriptorVersion() const;
	bool getDescriptorVersion(ReferencedVersion & out) const;
	bool hasDescriptorVersion() const;

	SetContextStateOperationState & setOperatingMode(const OperatingMode & value);
	OperatingMode getOperatingMode() const;

private:
	std::shared_ptr<CDM::SetContextStateOperationState> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* SETCONTEXTSTATEOPERATIONSTATE_H_ */
