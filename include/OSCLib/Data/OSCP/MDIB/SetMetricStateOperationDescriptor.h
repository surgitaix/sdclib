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
 *  SetMetricStateOperationDescriptor.h
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

#ifndef SETMETRICSTATEOPERATIONDESCRIPTOR_H_
#define SETMETRICSTATEOPERATIONDESCRIPTOR_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class SetMetricStateOperationDescriptor {
private:
	SetMetricStateOperationDescriptor(const CDM::SetMetricStateOperationDescriptor & object);
	operator CDM::SetMetricStateOperationDescriptor() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	SetMetricStateOperationDescriptor();
	SetMetricStateOperationDescriptor(const SetMetricStateOperationDescriptor & object);
	virtual ~SetMetricStateOperationDescriptor();
    
    void copyFrom(const SetMetricStateOperationDescriptor & object);
    SetMetricStateOperationDescriptor & operator=(const SetMetricStateOperationDescriptor & object);
    
    typedef CDM::SetMetricStateOperationDescriptor WrappedType;

	SetMetricStateOperationDescriptor & setType(const CodedValue & value);
	CodedValue getType() const;
	bool getType(CodedValue & out) const;
	bool hasType() const;

	SetMetricStateOperationDescriptor & setHandle(const Handle & value);
	Handle getHandle() const;

	SetMetricStateOperationDescriptor & setDescriptorVersion(const VersionCounter & value);
	VersionCounter getDescriptorVersion() const;
	bool getDescriptorVersion(VersionCounter & out) const;
	bool hasDescriptorVersion() const;

	SetMetricStateOperationDescriptor & setSafetyClassification(const SafetyClassification & value);
	SafetyClassification getSafetyClassification() const;
	bool getSafetyClassification(SafetyClassification & out) const;
	bool hasSafetyClassification() const;

	SetMetricStateOperationDescriptor & setOperationTarget(const HandleRef & value);
	HandleRef getOperationTarget() const;

	SetMetricStateOperationDescriptor & addModifiableElement(const std::string & value);
	std::vector<std::string> getModifiableElements() const;
	void clearModifiableElements();
	
private:
	std::shared_ptr<CDM::SetMetricStateOperationDescriptor> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* SETMETRICSTATEOPERATIONDESCRIPTOR_H_ */
