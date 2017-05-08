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
 *  SetContextOperationDescriptor.h
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

#ifndef SETCONTEXTOPERATIONDESCRIPTOR_H_
#define SETCONTEXTOPERATIONDESCRIPTOR_H_

#include "OSCLib/Data/OSCP/MDIB/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class SetContextOperationDescriptor {
private:
	SetContextOperationDescriptor(const CDM::SetContextOperationDescriptor & object);
	operator CDM::SetContextOperationDescriptor() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	SetContextOperationDescriptor();
	SetContextOperationDescriptor(const SetContextOperationDescriptor & object);
	virtual ~SetContextOperationDescriptor();
    
    void copyFrom(const SetContextOperationDescriptor & object);
    SetContextOperationDescriptor & operator=(const SetContextOperationDescriptor & object);
    
    typedef CDM::SetContextOperationDescriptor WrappedType;

	SetContextOperationDescriptor & setType(const CodedValue & value);
	CodedValue getType() const;
	bool getType(CodedValue & out) const;
	bool hasType() const;

	SetContextOperationDescriptor & setHandle(const std::string & value);
	std::string getHandle() const;

	SetContextOperationDescriptor & setDescriptorVersion(const VersionCounter & value);
	VersionCounter getDescriptorVersion() const;
	bool getDescriptorVersion(VersionCounter & out) const;
	bool hasDescriptorVersion() const;

	SetContextOperationDescriptor & setOperationTarget(const std::string & value);
	std::string getOperationTarget() const;

	SetContextOperationDescriptor & addModifiableElement(const CodedValue & value);
	std::vector<CodedValue> getModifiableElements() const;
	void clearModifiableElements();
	
private:
	std::shared_ptr<CDM::SetContextOperationDescriptor> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* SETCONTEXTOPERATIONDESCRIPTOR_H_ */
