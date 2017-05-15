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
 *  SetRangeOperationDescriptor.h
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

#ifndef SETRANGEOPERATIONDESCRIPTOR_H_
#define SETRANGEOPERATIONDESCRIPTOR_H_

#include "OSCLib/Data/OSCP/MDIB/custom/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class SetRangeOperationDescriptor {
private:
	SetRangeOperationDescriptor(const CDM::SetRangeOperationDescriptor & object);
	operator CDM::SetRangeOperationDescriptor() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	SetRangeOperationDescriptor();
	SetRangeOperationDescriptor(const SetRangeOperationDescriptor & object);
	virtual ~SetRangeOperationDescriptor();
    
    void copyFrom(const SetRangeOperationDescriptor & object);
    SetRangeOperationDescriptor & operator=(const SetRangeOperationDescriptor & object);
    
    typedef CDM::SetRangeOperationDescriptor WrappedType;

	SetRangeOperationDescriptor & setType(const CodedValue & value);
	CodedValue getType() const;
	bool getType(CodedValue & out) const;
	bool hasType() const;

	SetRangeOperationDescriptor & setHandle(const std::string & value);
	std::string getHandle() const;

	SetRangeOperationDescriptor & setDescriptorVersion(const VersionCounter & value);
	VersionCounter getDescriptorVersion() const;
	bool getDescriptorVersion(VersionCounter & out) const;
	bool hasDescriptorVersion() const;

	SetRangeOperationDescriptor & setSafetyClassification(const std::string & value);
	std::string getSafetyClassification() const;
	bool getSafetyClassification(std::string & out) const;
	bool hasSafetyClassification() const;

	SetRangeOperationDescriptor & setOperationTarget(const std::string & value);
	std::string getOperationTarget() const;

	SetRangeOperationDescriptor & addModifiableElement(const CodedValue & value);
	std::vector<CodedValue> getModifiableElements() const;
	void clearModifiableElements();
	
	SetRangeOperationDescriptor & setAllowedMaxRange(const Range & value);
	Range getAllowedMaxRange() const;

private:
	std::shared_ptr<CDM::SetRangeOperationDescriptor> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* SETRANGEOPERATIONDESCRIPTOR_H_ */
