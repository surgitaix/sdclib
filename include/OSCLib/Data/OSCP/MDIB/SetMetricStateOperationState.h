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
 *  SetMetricStateOperationState.h
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

#ifndef SETMETRICSTATEOPERATIONSTATE_H_
#define SETMETRICSTATEOPERATIONSTATE_H_

#include "OSCLib/Data/OSCP/MDIB/custom/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class SetMetricStateOperationState {
private:
	SetMetricStateOperationState(const CDM::SetMetricStateOperationState & object);
	operator CDM::SetMetricStateOperationState() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	SetMetricStateOperationState();
	SetMetricStateOperationState(const SetMetricStateOperationState & object);
	virtual ~SetMetricStateOperationState();
    
    void copyFrom(const SetMetricStateOperationState & object);
    SetMetricStateOperationState & operator=(const SetMetricStateOperationState & object);
    
    typedef CDM::SetMetricStateOperationState WrappedType;

	SetMetricStateOperationState & setDescriptorVersion(const ReferencedVersion & value);
	ReferencedVersion getDescriptorVersion() const;
	bool getDescriptorVersion(ReferencedVersion & out) const;
	bool hasDescriptorVersion() const;

	SetMetricStateOperationState & setDescriptorHandle(const std::string & value);
	std::string getDescriptorHandle() const;

	SetMetricStateOperationState & setStateVersion(const VersionCounter & value);
	VersionCounter getStateVersion() const;
	bool getStateVersion(VersionCounter & out) const;
	bool hasStateVersion() const;

	SetMetricStateOperationState & setOperatingMode(const OperatingMode & value);
	OperatingMode getOperatingMode() const;

private:
	std::shared_ptr<CDM::SetMetricStateOperationState> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* SETMETRICSTATEOPERATIONSTATE_H_ */
