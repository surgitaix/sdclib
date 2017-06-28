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
 *  PatientContextState.h
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

#ifndef PATIENTCONTEXTSTATE_H_
#define PATIENTCONTEXTSTATE_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class PatientContextState {
private:
	PatientContextState(const CDM::PatientContextState & object);
	operator CDM::PatientContextState() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	PatientContextState();
	PatientContextState(const PatientContextState & object);
	virtual ~PatientContextState();
    
    void copyFrom(const PatientContextState & object);
    PatientContextState & operator=(const PatientContextState & object);
    
    typedef CDM::PatientContextState WrappedType;

	PatientContextState & setStateVersion(const VersionCounter & value);
	VersionCounter getStateVersion() const;

	PatientContextState & setDescriptorHandle(const HandleRef & value);
	HandleRef getDescriptorHandle() const;

	PatientContextState & setDescriptorVersion(const ReferencedVersion & value);
	ReferencedVersion getDescriptorVersion() const;

	PatientContextState & setCategory(const CodedValue & value);
	CodedValue getCategory() const;
	bool getCategory(CodedValue & out) const;
	bool hasCategory() const;

	PatientContextState & setHandle(const Handle & value);
	Handle getHandle() const;

	PatientContextState & setContextAssociation(const ContextAssociation & value);
	ContextAssociation getContextAssociation() const;

	PatientContextState & setBindingMdibVersion(const ReferencedVersion & value);
	ReferencedVersion getBindingMdibVersion() const;
	bool getBindingMdibVersion(ReferencedVersion & out) const;
	bool hasBindingMdibVersion() const;

	PatientContextState & setUnbindingMdibVersion(const ReferencedVersion & value);
	ReferencedVersion getUnbindingMdibVersion() const;

	PatientContextState & setBindingStartTime(const Timestamp & value);
	Timestamp getBindingStartTime() const;

	PatientContextState & setBindingEndTime(const Timestamp & value);
	Timestamp getBindingEndTime() const;

	PatientContextState & addValidator(const InstanceIdentifier & value);
	std::vector<InstanceIdentifier> getValidators() const;
	void clearValidators();
	
	PatientContextState & addIdentification(const InstanceIdentifier & value);
	std::vector<InstanceIdentifier> getIdentifications() const;
	void clearIdentifications();
	
	PatientContextState & setCoreData(const PatientDemographicsCoreData & value);
	PatientDemographicsCoreData getCoreData() const;
	bool getCoreData(PatientDemographicsCoreData & out) const;
	bool hasCoreData() const;

private:
	std::shared_ptr<CDM::PatientContextState> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* PATIENTCONTEXTSTATE_H_ */
