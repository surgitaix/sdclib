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
 *  SystemContext.h
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

#ifndef SYSTEMCONTEXT_H_
#define SYSTEMCONTEXT_H_

#include "OSCLib/Data/OSCP/MDIB/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class SystemContext {
private:
	SystemContext(const CDM::SystemContext & object);
	operator CDM::SystemContext() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	SystemContext();
	SystemContext(const SystemContext & object);
	virtual ~SystemContext();
    
    void copyFrom(const SystemContext & object);
    SystemContext & operator=(const SystemContext & object);
    
    typedef CDM::SystemContext WrappedType;

	SystemContext & setEnsembleContext(const EnsembleContextDescriptor & value);
	EnsembleContextDescriptor getEnsembleContext() const;
	bool getEnsembleContext(EnsembleContextDescriptor & out) const;
	bool hasEnsembleContext() const;

	SystemContext & setLocationContext(const LocationContextDescriptor & value);
	LocationContextDescriptor getLocationContext() const;
	bool getLocationContext(LocationContextDescriptor & out) const;
	bool hasLocationContext() const;

	SystemContext & setOperatorContext(const OperatorContextDescriptor & value);
	OperatorContextDescriptor getOperatorContext() const;
	bool getOperatorContext(OperatorContextDescriptor & out) const;
	bool hasOperatorContext() const;

	SystemContext & setPatientContext(const PatientContextDescriptor & value);
	PatientContextDescriptor getPatientContext() const;
	bool getPatientContext(PatientContextDescriptor & out) const;
	bool hasPatientContext() const;

	SystemContext & setWorkflowContext(const WorkflowContextDescriptor & value);
	WorkflowContextDescriptor getWorkflowContext() const;
	bool getWorkflowContext(WorkflowContextDescriptor & out) const;
	bool hasWorkflowContext() const;

private:
	std::shared_ptr<CDM::SystemContext> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* SYSTEMCONTEXT_H_ */
