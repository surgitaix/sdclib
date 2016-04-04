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
 *  OperationState.h
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

#ifndef OPERATIONSTATE_H_
#define OPERATIONSTATE_H_

#include "OSCLib/Data/OSCP/MDIB/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class OperationState {
private:
	OperationState(const CDM::OperationState & object);
	operator CDM::OperationState() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	OperationState();
	OperationState(const OperationState & object);
	virtual ~OperationState();
    
    void copyFrom(const OperationState & object);
    OperationState & operator=(const OperationState & object);
    
    typedef CDM::OperationState WrappedType;

	OperationState & setHandle(const std::string & value);
	std::string getHandle() const;
	bool getHandle(std::string & out) const;
	bool hasHandle() const;

	OperationState & setDescriptorHandle(const std::string & value);
	std::string getDescriptorHandle() const;

	OperationState & setStateVersion(const VersionCounter & value);
	VersionCounter getStateVersion() const;
	bool getStateVersion(VersionCounter & out) const;
	bool hasStateVersion() const;

	OperationState & setOperatingMode(const OperatingMode & value);
	OperatingMode getOperatingMode() const;

private:
	std::shared_ptr<CDM::OperationState> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* OPERATIONSTATE_H_ */
