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
 *  SetComponentStateOperationState.h
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

#ifndef SETCOMPONENTSTATEOPERATIONSTATE_H_
#define SETCOMPONENTSTATEOPERATIONSTATE_H_

#include "OSCLib/Data/SDC/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/SDC/SDC-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace SDC {

class SetComponentStateOperationState {
private:
	SetComponentStateOperationState(const CDM::SetComponentStateOperationState & object);
	operator CDM::SetComponentStateOperationState() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class SDCProvider;
	friend class SDCConsumer;
	friend class MdState;
	friend class MdDescription;
public:
	SetComponentStateOperationState(
		HandleRef descriptorhandle
		, 
		OperatingMode operatingmode
	); 
private:
	SetComponentStateOperationState(){};
public:
	SetComponentStateOperationState(const SetComponentStateOperationState & object);
	virtual ~SetComponentStateOperationState();
    
    void copyFrom(const SetComponentStateOperationState & object);
    SetComponentStateOperationState & operator=(const SetComponentStateOperationState & object);
    
    typedef CDM::SetComponentStateOperationState WrappedType;

	SetComponentStateOperationState & setStateVersion(const VersionCounter & value);
	VersionCounter getStateVersion() const;
	bool getStateVersion(VersionCounter & out) const;
	bool hasStateVersion() const;

	SetComponentStateOperationState & setDescriptorHandle(const HandleRef & value);
	HandleRef getDescriptorHandle() const;

	SetComponentStateOperationState & setDescriptorVersion(const ReferencedVersion & value);
	ReferencedVersion getDescriptorVersion() const;
	bool getDescriptorVersion(ReferencedVersion & out) const;
	bool hasDescriptorVersion() const;

	SetComponentStateOperationState & setOperatingMode(const OperatingMode & value);
	OperatingMode getOperatingMode() const;

private:
	std::shared_ptr<CDM::SetComponentStateOperationState> data;
};

} /* namespace SDC */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* SETCOMPONENTSTATEOPERATIONSTATE_H_ */
