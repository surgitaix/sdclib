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
 *  SystemContextDescriptor.h
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

#ifndef SYSTEMCONTEXTDESCRIPTOR_H_
#define SYSTEMCONTEXTDESCRIPTOR_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class SystemContextDescriptor {
private:
	SystemContextDescriptor(const CDM::SystemContextDescriptor & object);
	operator CDM::SystemContextDescriptor() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class SDCProvider;
	friend class SDCConsumer;
	friend class MdState;
	friend class MdDescription;
public:
	SystemContextDescriptor(
		Handle handle
	); 
private:
	SystemContextDescriptor(){};
public:
	SystemContextDescriptor(const SystemContextDescriptor & object);
	virtual ~SystemContextDescriptor();
    
    void copyFrom(const SystemContextDescriptor & object);
    SystemContextDescriptor & operator=(const SystemContextDescriptor & object);
    
    typedef CDM::SystemContextDescriptor WrappedType;

	SystemContextDescriptor & setType(const CodedValue & value);
	CodedValue getType() const;
	bool getType(CodedValue & out) const;
	bool hasType() const;

	SystemContextDescriptor & setHandle(const Handle & value);
	Handle getHandle() const;

	SystemContextDescriptor & setDescriptorVersion(const VersionCounter & value);
	VersionCounter getDescriptorVersion() const;
	bool getDescriptorVersion(VersionCounter & out) const;
	bool hasDescriptorVersion() const;

	SystemContextDescriptor & setSafetyClassification(const SafetyClassification & value);
	SafetyClassification getSafetyClassification() const;
	bool getSafetyClassification(SafetyClassification & out) const;
	bool hasSafetyClassification() const;

	SystemContextDescriptor & setPatientContext(const PatientContextDescriptor & value);
	PatientContextDescriptor getPatientContext() const;
	bool getPatientContext(PatientContextDescriptor & out) const;
	bool hasPatientContext() const;

	SystemContextDescriptor & setLocationContext(const LocationContextDescriptor & value);
	LocationContextDescriptor getLocationContext() const;
	bool getLocationContext(LocationContextDescriptor & out) const;
	bool hasLocationContext() const;

	SystemContextDescriptor & addEnsembleContext(const EnsembleContextDescriptor & value);
	std::vector<EnsembleContextDescriptor> getEnsembleContextList() const;
	void clearEnsembleContextList();
	
	SystemContextDescriptor & addOperatorContext(const OperatorContextDescriptor & value);
	std::vector<OperatorContextDescriptor> getOperatorContextList() const;
	void clearOperatorContextList();
	
	SystemContextDescriptor & addWorkflowContext(const WorkflowContextDescriptor & value);
	std::vector<WorkflowContextDescriptor> getWorkflowContextList() const;
	void clearWorkflowContextList();
	
	SystemContextDescriptor & addMeansContext(const MeansContextDescriptor & value);
	std::vector<MeansContextDescriptor> getMeansContextList() const;
	void clearMeansContextList();
	
private:
	std::shared_ptr<CDM::SystemContextDescriptor> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* SYSTEMCONTEXTDESCRIPTOR_H_ */
