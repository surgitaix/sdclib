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
 *  OperatorContextState.h
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

#ifndef OPERATORCONTEXTSTATE_H_
#define OPERATORCONTEXTSTATE_H_

#include "OSCLib/Data/OSCP/MDIB/custom/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class OperatorContextState {
private:
	OperatorContextState(const CDM::OperatorContextState & object);
	operator CDM::OperatorContextState() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	OperatorContextState();
	OperatorContextState(const OperatorContextState & object);
	virtual ~OperatorContextState();
    
    void copyFrom(const OperatorContextState & object);
    OperatorContextState & operator=(const OperatorContextState & object);
    
    typedef CDM::OperatorContextState WrappedType;
    typedef OperatorContextDescriptor DescriptorType;

	OperatorContextState & setHandle(const std::string & value);
	std::string getHandle() const;
	bool getHandle(std::string & out) const;
	bool hasHandle() const;

	OperatorContextState & setDescriptorHandle(const std::string & value);
	std::string getDescriptorHandle() const;

	OperatorContextState & setStateVersion(const VersionCounter & value);
	VersionCounter getStateVersion() const;
	bool getStateVersion(VersionCounter & out) const;
	bool hasStateVersion() const;

	OperatorContextState & setContextAssociation(const ContextAssociation & value);
	ContextAssociation getContextAssociation() const;
	bool getContextAssociation(ContextAssociation & out) const;
	bool hasContextAssociation() const;

	OperatorContextState & setBindingMDIBVersion(const ReferencedVersion & value);
	ReferencedVersion getBindingMDIBVersion() const;

	OperatorContextState & setUnbindingMDIBVersion(const ReferencedVersion & value);
	ReferencedVersion getUnbindingMDIBVersion() const;
	bool getUnbindingMDIBVersion(ReferencedVersion & out) const;
	bool hasUnbindingMDIBVersion() const;

	OperatorContextState & setBindingStartTime(const Timestamp & value);
	Timestamp getBindingStartTime() const;
	bool getBindingStartTime(Timestamp & out) const;
	bool hasBindingStartTime() const;

	OperatorContextState & setBindingEndTime(const Timestamp & value);
	Timestamp getBindingEndTime() const;
	bool getBindingEndTime(Timestamp & out) const;
	bool hasBindingEndTime() const;

	OperatorContextState & addValidator(const InstanceIdentifier & value);
	std::vector<InstanceIdentifier> getValidators() const;
	void clearValidators();
	
	OperatorContextState & addIdentification(const InstanceIdentifier & value);
	std::vector<InstanceIdentifier> getIdentifications() const;
	void clearIdentifications();
	
private:
	std::shared_ptr<CDM::OperatorContextState> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* OPERATORCONTEXTSTATE_H_ */
