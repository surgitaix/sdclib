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
 *  SetComponentStateOperationDescriptor.h
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

#ifndef SETCOMPONENTSTATEOPERATIONDESCRIPTOR_H_
#define SETCOMPONENTSTATEOPERATIONDESCRIPTOR_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class SetComponentStateOperationDescriptor {
private:
	SetComponentStateOperationDescriptor(const CDM::SetComponentStateOperationDescriptor & object);
	operator CDM::SetComponentStateOperationDescriptor() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class SDCProvider;
	friend class SDCConsumer;
	friend class MdState;
	friend class MdDescription;
public:
	SetComponentStateOperationDescriptor(
		Handle handle
		, 
		HandleRef operationtarget
	); 
private:
	SetComponentStateOperationDescriptor(){};
public:
	SetComponentStateOperationDescriptor(const SetComponentStateOperationDescriptor & object);
	virtual ~SetComponentStateOperationDescriptor();
    
    void copyFrom(const SetComponentStateOperationDescriptor & object);
    SetComponentStateOperationDescriptor & operator=(const SetComponentStateOperationDescriptor & object);
    
    typedef CDM::SetComponentStateOperationDescriptor WrappedType;

	SetComponentStateOperationDescriptor & setType(const CodedValue & value);
	CodedValue getType() const;
	bool getType(CodedValue & out) const;
	bool hasType() const;

	SetComponentStateOperationDescriptor & setHandle(const Handle & value);
	Handle getHandle() const;

	SetComponentStateOperationDescriptor & setDescriptorVersion(const VersionCounter & value);
	VersionCounter getDescriptorVersion() const;
	bool getDescriptorVersion(VersionCounter & out) const;
	bool hasDescriptorVersion() const;

	SetComponentStateOperationDescriptor & setSafetyClassification(const SafetyClassification & value);
	SafetyClassification getSafetyClassification() const;
	bool getSafetyClassification(SafetyClassification & out) const;
	bool hasSafetyClassification() const;

	SetComponentStateOperationDescriptor & setOperationTarget(const HandleRef & value);
	HandleRef getOperationTarget() const;

	SetComponentStateOperationDescriptor & setMaxTimeToFinish(const xml_schema::Duration & value);
	xml_schema::Duration getMaxTimeToFinish() const;
	bool getMaxTimeToFinish(xml_schema::Duration & out) const;
	bool hasMaxTimeToFinish() const;

	SetComponentStateOperationDescriptor & setInvocationEffectiveTimeout(const xml_schema::Duration & value);
	xml_schema::Duration getInvocationEffectiveTimeout() const;
	bool getInvocationEffectiveTimeout(xml_schema::Duration & out) const;
	bool hasInvocationEffectiveTimeout() const;

	SetComponentStateOperationDescriptor & setRetriggerable(const xml_schema::Duration & value);
	xml_schema::Duration getRetriggerable() const;
	bool getRetriggerable(xml_schema::Duration & out) const;
	bool hasRetriggerable() const;

	SetComponentStateOperationDescriptor & setAccessLevel(const AccessLevel & value);
	AccessLevel getAccessLevel() const;
	bool getAccessLevel(AccessLevel & out) const;
	bool hasAccessLevel() const;

	SetComponentStateOperationDescriptor & addModifiableData(const std::string & value);
	std::vector<std::string> getModifiableDataList() const;
	void clearModifiableDataList();
	
private:
	std::shared_ptr<CDM::SetComponentStateOperationDescriptor> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* SETCOMPONENTSTATEOPERATIONDESCRIPTOR_H_ */
