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
 *  SetValueOperationState.h
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

#ifndef SETVALUEOPERATIONSTATE_H_
#define SETVALUEOPERATIONSTATE_H_

#include "SDCLib/Data/SDC/MDIB/SimpleTypesMapping.h"
#include "SDCLib/Data/SDC/SDC-fwd.h"
#include "osdm-fwd.hxx"

namespace SDCLib {
namespace Data {
namespace SDC {

class SetValueOperationState {
private:
	SetValueOperationState(const CDM::SetValueOperationState & object);
	operator CDM::SetValueOperationState() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class SDCProvider;
	friend class SDCConsumer;
	friend class MdState;
	friend class MdDescription;
public:
	SetValueOperationState(
		HandleRef descriptorhandle
		,
		OperatingMode operatingmode
	);
private:
	SetValueOperationState(){};
public:
	SetValueOperationState(const SetValueOperationState & object);
	virtual ~SetValueOperationState();

    void copyFrom(const SetValueOperationState & object);
    SetValueOperationState & operator=(const SetValueOperationState & object);

    typedef CDM::SetValueOperationState WrappedType;

	SetValueOperationState & setStateVersion(const VersionCounter & value);
	VersionCounter getStateVersion() const;
	bool getStateVersion(VersionCounter & out) const;
	bool hasStateVersion() const;

	SetValueOperationState & setDescriptorHandle(const HandleRef & value);
	HandleRef getDescriptorHandle() const;

	SetValueOperationState & setDescriptorVersion(const ReferencedVersion & value);
	ReferencedVersion getDescriptorVersion() const;
	bool getDescriptorVersion(ReferencedVersion & out) const;
	bool hasDescriptorVersion() const;

	SetValueOperationState & setOperatingMode(const OperatingMode & value);
	OperatingMode getOperatingMode() const;

	SetValueOperationState & addAllowedRange(const Range & value);
	std::vector<Range> getAllowedRangeList() const;
	void clearAllowedRangeList();

private:
	std::shared_ptr<CDM::SetValueOperationState> data;
};

} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */
#endif /* SETVALUEOPERATIONSTATE_H_ */
