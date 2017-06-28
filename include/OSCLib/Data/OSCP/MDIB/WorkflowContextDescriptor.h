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
 *  WorkflowContextDescriptor.h
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

#ifndef WORKFLOWCONTEXTDESCRIPTOR_H_
#define WORKFLOWCONTEXTDESCRIPTOR_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class WorkflowContextDescriptor {
private:
	WorkflowContextDescriptor(const CDM::WorkflowContextDescriptor & object);
	operator CDM::WorkflowContextDescriptor() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	WorkflowContextDescriptor();
	WorkflowContextDescriptor(const WorkflowContextDescriptor & object);
	virtual ~WorkflowContextDescriptor();
    
    void copyFrom(const WorkflowContextDescriptor & object);
    WorkflowContextDescriptor & operator=(const WorkflowContextDescriptor & object);
    
    typedef CDM::WorkflowContextDescriptor WrappedType;

	WorkflowContextDescriptor & setType(const CodedValue & value);
	CodedValue getType() const;
	bool getType(CodedValue & out) const;
	bool hasType() const;

	WorkflowContextDescriptor & setHandle(const Handle & value);
	Handle getHandle() const;

	WorkflowContextDescriptor & setDescriptorVersion(const VersionCounter & value);
	VersionCounter getDescriptorVersion() const;
	bool getDescriptorVersion(VersionCounter & out) const;
	bool hasDescriptorVersion() const;

	WorkflowContextDescriptor & setSafetyClassification(const SafetyClassification & value);
	SafetyClassification getSafetyClassification() const;
	bool getSafetyClassification(SafetyClassification & out) const;
	bool hasSafetyClassification() const;

private:
	std::shared_ptr<CDM::WorkflowContextDescriptor> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* WORKFLOWCONTEXTDESCRIPTOR_H_ */
