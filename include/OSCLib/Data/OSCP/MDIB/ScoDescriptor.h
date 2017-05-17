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
 *  ScoDescriptor.h
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

#ifndef SCODESCRIPTOR_H_
#define SCODESCRIPTOR_H_

#include "OSCLib/Data/OSCP/MDIB/custom/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class ScoDescriptor {
private:
	ScoDescriptor(const CDM::ScoDescriptor & object);
	operator CDM::ScoDescriptor() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	ScoDescriptor();
	ScoDescriptor(const ScoDescriptor & object);
	virtual ~ScoDescriptor();
    
    void copyFrom(const ScoDescriptor & object);
    ScoDescriptor & operator=(const ScoDescriptor & object);
    
    typedef CDM::ScoDescriptor WrappedType;

	ScoDescriptor & setType(const CodedValue & value);
	CodedValue getType() const;
	bool getType(CodedValue & out) const;
	bool hasType() const;

	ScoDescriptor & setHandle(const std::string & value);
	std::string getHandle() const;

	ScoDescriptor & setDescriptorVersion(const VersionCounter & value);
	VersionCounter getDescriptorVersion() const;
	bool getDescriptorVersion(VersionCounter & out) const;
	bool hasDescriptorVersion() const;

	ScoDescriptor & setSafetyClassification(const SafetyClassification & value);
	SafetyClassification getSafetyClassification() const;
	bool getSafetyClassification(SafetyClassification & out) const;
	bool hasSafetyClassification() const;

	ScoDescriptor & addOperation(const AbstractOperationDescriptor & value);
	std::vector<AbstractOperationDescriptor> getOperations() const;
	void clearOperations();
	

	std::vector<ActivateOperationDescriptor> collectAllActivateOperationDescriptors() const;
	std::vector<SetAlertStateOperationDescriptor> collectAllSetAlertStateOperationDescriptors() const;
	std::vector<SetContextOperationDescriptor> collectAllSetContextOperationDescriptors() const;
	std::vector<SetRangeOperationDescriptor> collectAllSetRangeOperationDescriptors() const;
	std::vector<SetStringOperationDescriptor> collectAllSetStringOperationDescriptors() const;
	std::vector<SetValueOperationDescriptor> collectAllSetValueOperationDescriptors() const;

private:
	template <class WrapperOperationDescriptorType>
	void collectOperationDescriptorImpl(std::vector<WrapperOperationDescriptorType> & out) const;
private:
	std::shared_ptr<CDM::ScoDescriptor> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* SCODESCRIPTOR_H_ */
