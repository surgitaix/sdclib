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
 *  SetContextStateOperationDescriptor.h
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

#ifndef SETCONTEXTSTATEOPERATIONDESCRIPTOR_H_
#define SETCONTEXTSTATEOPERATIONDESCRIPTOR_H_

#include "SDCLib/Data/SDC/MDIB/SimpleTypesMapping.h"
#include "SDCLib/Data/SDC/SDC-fwd.h"
#include "DataModel/osdm-fwd.hxx"

namespace SDCLib {
namespace Data {
namespace SDC {

class SetContextStateOperationDescriptor
{
private:
	SetContextStateOperationDescriptor(const CDM::SetContextStateOperationDescriptor & object);
	operator CDM::SetContextStateOperationDescriptor() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class SDCProvider;
	friend class SDCConsumer;
	friend class MdState;
	friend class MdDescription;
public:
	SetContextStateOperationDescriptor(
		Handle handle
		,
		HandleRef operationtarget
	);
private:
	SetContextStateOperationDescriptor(){};
public:
	SetContextStateOperationDescriptor(const SetContextStateOperationDescriptor& object);
	virtual ~SetContextStateOperationDescriptor() = default;

    void copyFrom(const SetContextStateOperationDescriptor& object);
    SetContextStateOperationDescriptor & operator=(const SetContextStateOperationDescriptor& object);

    typedef CDM::SetContextStateOperationDescriptor WrappedType;

	SetContextStateOperationDescriptor & setType(const CodedValue & value);
	CodedValue getType() const;
	bool getType(CodedValue & out) const;
	bool hasType() const;

	SetContextStateOperationDescriptor & setHandle(const Handle & value);
	Handle getHandle() const;

	SetContextStateOperationDescriptor & setDescriptorVersion(const VersionCounter & value);
	VersionCounter getDescriptorVersion() const;
	bool getDescriptorVersion(VersionCounter & out) const;
	bool hasDescriptorVersion() const;

	SetContextStateOperationDescriptor & setSafetyClassification(const SafetyClassification & value);
	SafetyClassification getSafetyClassification() const;
	bool getSafetyClassification(SafetyClassification & out) const;
	bool hasSafetyClassification() const;

	SetContextStateOperationDescriptor & setOperationTarget(const HandleRef & value);
	HandleRef getOperationTarget() const;

	SetContextStateOperationDescriptor & setMaxTimeToFinish(const xml_schema::Duration & value);
	xml_schema::Duration getMaxTimeToFinish() const;
	bool getMaxTimeToFinish(xml_schema::Duration & out) const;
	bool hasMaxTimeToFinish() const;

	SetContextStateOperationDescriptor & setInvocationEffectiveTimeout(const xml_schema::Duration & value);
	xml_schema::Duration getInvocationEffectiveTimeout() const;
	bool getInvocationEffectiveTimeout(xml_schema::Duration & out) const;
	bool hasInvocationEffectiveTimeout() const;

	SetContextStateOperationDescriptor & setRetriggerable(const bool & value);
	bool getRetriggerable() const;
	bool getRetriggerable(bool & out) const;
	bool hasRetriggerable() const;

	SetContextStateOperationDescriptor & setAccessLevel(const AccessLevel & value);
	AccessLevel getAccessLevel() const;
	bool getAccessLevel(AccessLevel & out) const;
	bool hasAccessLevel() const;

	SetContextStateOperationDescriptor & addModifiableData(const std::string & value);
	std::vector<std::string> getModifiableDataList() const;
	void clearModifiableDataList();

private:
	std::shared_ptr<CDM::SetContextStateOperationDescriptor> data = nullptr;
};

} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */
#endif /* SETCONTEXTSTATEOPERATIONDESCRIPTOR_H_ */
