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
 *  SetAlertStateOperationDescriptor.h
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

#ifndef SETALERTSTATEOPERATIONDESCRIPTOR_H_
#define SETALERTSTATEOPERATIONDESCRIPTOR_H_

#include "OSCLib/Data/OSCP/MDIB/custom/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class SetAlertStateOperationDescriptor {
private:
	SetAlertStateOperationDescriptor(const CDM::SetAlertStateOperationDescriptor & object);
	operator CDM::SetAlertStateOperationDescriptor() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	SetAlertStateOperationDescriptor();
	SetAlertStateOperationDescriptor(const SetAlertStateOperationDescriptor & object);
	virtual ~SetAlertStateOperationDescriptor();
    
    void copyFrom(const SetAlertStateOperationDescriptor & object);
    SetAlertStateOperationDescriptor & operator=(const SetAlertStateOperationDescriptor & object);
    
    typedef CDM::SetAlertStateOperationDescriptor WrappedType;

	SetAlertStateOperationDescriptor & setType(const CodedValue & value);
	CodedValue getType() const;
	bool getType(CodedValue & out) const;
	bool hasType() const;

	SetAlertStateOperationDescriptor & setHandle(const std::string & value);
	std::string getHandle() const;

	SetAlertStateOperationDescriptor & setDescriptorVersion(const VersionCounter & value);
	VersionCounter getDescriptorVersion() const;
	bool getDescriptorVersion(VersionCounter & out) const;
	bool hasDescriptorVersion() const;

	SetAlertStateOperationDescriptor & setOperationTarget(const std::string & value);
	std::string getOperationTarget() const;

	SetAlertStateOperationDescriptor & addModifiableElement(const CodedValue & value);
	std::vector<CodedValue> getModifiableElements() const;
	void clearModifiableElements();
	
private:
	std::shared_ptr<CDM::SetAlertStateOperationDescriptor> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* SETALERTSTATEOPERATIONDESCRIPTOR_H_ */
