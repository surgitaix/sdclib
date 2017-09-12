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
 *  ActivateOperationDescriptor.h
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

#ifndef ACTIVATEOPERATIONDESCRIPTOR_H_
#define ACTIVATEOPERATIONDESCRIPTOR_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class ActivateOperationDescriptor {
private:
	ActivateOperationDescriptor(const CDM::ActivateOperationDescriptor & object);
	operator CDM::ActivateOperationDescriptor() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	ActivateOperationDescriptor();
	ActivateOperationDescriptor(const ActivateOperationDescriptor & object);
	virtual ~ActivateOperationDescriptor();
    
    void copyFrom(const ActivateOperationDescriptor & object);
    ActivateOperationDescriptor & operator=(const ActivateOperationDescriptor & object);
    
    typedef CDM::ActivateOperationDescriptor WrappedType;

	ActivateOperationDescriptor & setType(const CodedValue & value);
	CodedValue getType() const;
	bool getType(CodedValue & out) const;
	bool hasType() const;

	ActivateOperationDescriptor & setHandle(const Handle & value);
	Handle getHandle() const;

	ActivateOperationDescriptor & setDescriptorVersion(const VersionCounter & value);
	VersionCounter getDescriptorVersion() const;
	bool getDescriptorVersion(VersionCounter & out) const;
	bool hasDescriptorVersion() const;

	ActivateOperationDescriptor & setSafetyClassification(const SafetyClassification & value);
	SafetyClassification getSafetyClassification() const;
	bool getSafetyClassification(SafetyClassification & out) const;
	bool hasSafetyClassification() const;

	ActivateOperationDescriptor & setOperationTarget(const HandleRef & value);
	HandleRef getOperationTarget() const;

	ActivateOperationDescriptor & setMaxTimeToFinish(const xml_schema::Duration & value);
	xml_schema::Duration getMaxTimeToFinish() const;
	bool getMaxTimeToFinish(xml_schema::Duration & out) const;
	bool hasMaxTimeToFinish() const;

	ActivateOperationDescriptor & setInvocationEffectiveTimeout(const xml_schema::Duration & value);
	xml_schema::Duration getInvocationEffectiveTimeout() const;
	bool getInvocationEffectiveTimeout(xml_schema::Duration & out) const;
	bool hasInvocationEffectiveTimeout() const;

	ActivateOperationDescriptor & setRetriggerable(const xml_schema::Duration & value);
	xml_schema::Duration getRetriggerable() const;
	bool getRetriggerable(xml_schema::Duration & out) const;
	bool hasRetriggerable() const;

	ActivateOperationDescriptor & addModifiableElement(const std::string & value);
	std::vector<std::string> getModifiableElementLists() const;
	void clearModifiableElementLists();
	
	ActivateOperationDescriptor & addArgument(const Argument & value);
	std::vector<Argument> getArgumentLists() const;
	void clearArgumentLists();
	
private:
	std::shared_ptr<CDM::ActivateOperationDescriptor> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* ACTIVATEOPERATIONDESCRIPTOR_H_ */
