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
 *  SetStringOperationDescriptor.h
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

#ifndef SETSTRINGOPERATIONDESCRIPTOR_H_
#define SETSTRINGOPERATIONDESCRIPTOR_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class SetStringOperationDescriptor {
private:
	SetStringOperationDescriptor(const CDM::SetStringOperationDescriptor & object);
	operator CDM::SetStringOperationDescriptor() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class OSCPProvider;
	friend class OSCPConsumer;
	friend class MdState;
public:
	SetStringOperationDescriptor(
		Handle handle
		, 
		HandleRef operationtarget
	); 
private:
	SetStringOperationDescriptor(){};
public:
	SetStringOperationDescriptor(const SetStringOperationDescriptor & object);
	virtual ~SetStringOperationDescriptor();
    
    void copyFrom(const SetStringOperationDescriptor & object);
    SetStringOperationDescriptor & operator=(const SetStringOperationDescriptor & object);
    
    typedef CDM::SetStringOperationDescriptor WrappedType;

	SetStringOperationDescriptor & setType(const CodedValue & value);
	CodedValue getType() const;
	bool getType(CodedValue & out) const;
	bool hasType() const;

	SetStringOperationDescriptor & setHandle(const Handle & value);
	Handle getHandle() const;

	SetStringOperationDescriptor & setDescriptorVersion(const VersionCounter & value);
	VersionCounter getDescriptorVersion() const;
	bool getDescriptorVersion(VersionCounter & out) const;
	bool hasDescriptorVersion() const;

	SetStringOperationDescriptor & setSafetyClassification(const SafetyClassification & value);
	SafetyClassification getSafetyClassification() const;
	bool getSafetyClassification(SafetyClassification & out) const;
	bool hasSafetyClassification() const;

	SetStringOperationDescriptor & setOperationTarget(const HandleRef & value);
	HandleRef getOperationTarget() const;

	SetStringOperationDescriptor & setMaxTimeToFinish(const xml_schema::Duration & value);
	xml_schema::Duration getMaxTimeToFinish() const;
	bool getMaxTimeToFinish(xml_schema::Duration & out) const;
	bool hasMaxTimeToFinish() const;

	SetStringOperationDescriptor & setInvocationEffectiveTimeout(const xml_schema::Duration & value);
	xml_schema::Duration getInvocationEffectiveTimeout() const;
	bool getInvocationEffectiveTimeout(xml_schema::Duration & out) const;
	bool hasInvocationEffectiveTimeout() const;

	SetStringOperationDescriptor & setRetriggerable(const xml_schema::Duration & value);
	xml_schema::Duration getRetriggerable() const;
	bool getRetriggerable(xml_schema::Duration & out) const;
	bool hasRetriggerable() const;

	SetStringOperationDescriptor & setAccessLevel(const AccessLevel & value);
	AccessLevel getAccessLevel() const;
	bool getAccessLevel(AccessLevel & out) const;
	bool hasAccessLevel() const;

	SetStringOperationDescriptor & setMaxLength(const unsigned long long & value);
	unsigned long long getMaxLength() const;
	bool getMaxLength(unsigned long long & out) const;
	bool hasMaxLength() const;

private:
	std::shared_ptr<CDM::SetStringOperationDescriptor> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* SETSTRINGOPERATIONDESCRIPTOR_H_ */
