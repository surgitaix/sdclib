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
 *  EnsembleContextState.h
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

#ifndef ENSEMBLECONTEXTSTATE_H_
#define ENSEMBLECONTEXTSTATE_H_

#include "OSCLib/Data/OSCP/MDIB/custom/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class EnsembleContextState {
private:
	EnsembleContextState(const CDM::EnsembleContextState & object);
	operator CDM::EnsembleContextState() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	EnsembleContextState();
	EnsembleContextState(const EnsembleContextState & object);
	virtual ~EnsembleContextState();
    
    void copyFrom(const EnsembleContextState & object);
    EnsembleContextState & operator=(const EnsembleContextState & object);
    
    typedef CDM::EnsembleContextState WrappedType;
    typedef EnsembleContextDescriptor DescriptorType;

	EnsembleContextState & setHandle(const std::string & value);
	std::string getHandle() const;
	bool getHandle(std::string & out) const;
	bool hasHandle() const;

	EnsembleContextState & setDescriptorHandle(const std::string & value);
	std::string getDescriptorHandle() const;

	EnsembleContextState & setStateVersion(const VersionCounter & value);
	VersionCounter getStateVersion() const;
	bool getStateVersion(VersionCounter & out) const;
	bool hasStateVersion() const;

	EnsembleContextState & setContextAssociation(const ContextAssociation & value);
	ContextAssociation getContextAssociation() const;
	bool getContextAssociation(ContextAssociation & out) const;
	bool hasContextAssociation() const;

	EnsembleContextState & setBindingMDIBVersion(const ReferencedVersion & value);
	ReferencedVersion getBindingMDIBVersion() const;

	EnsembleContextState & setUnbindingMDIBVersion(const ReferencedVersion & value);
	ReferencedVersion getUnbindingMDIBVersion() const;
	bool getUnbindingMDIBVersion(ReferencedVersion & out) const;
	bool hasUnbindingMDIBVersion() const;

	EnsembleContextState & setBindingStartTime(const Timestamp & value);
	Timestamp getBindingStartTime() const;
	bool getBindingStartTime(Timestamp & out) const;
	bool hasBindingStartTime() const;

	EnsembleContextState & setBindingEndTime(const Timestamp & value);
	Timestamp getBindingEndTime() const;
	bool getBindingEndTime(Timestamp & out) const;
	bool hasBindingEndTime() const;

	EnsembleContextState & addValidator(const InstanceIdentifier & value);
	std::vector<InstanceIdentifier> getValidators() const;
	void clearValidators();
	
	EnsembleContextState & addIdentification(const InstanceIdentifier & value);
	std::vector<InstanceIdentifier> getIdentifications() const;
	void clearIdentifications();
	
private:
	std::shared_ptr<CDM::EnsembleContextState> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* ENSEMBLECONTEXTSTATE_H_ */
