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
 *  SCODescriptor.h
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

#include "OSCLib/Data/OSCP/MDIB/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class SCODescriptor {
private:
	SCODescriptor(const CDM::SCODescriptor & object);
	operator CDM::SCODescriptor() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	SCODescriptor();
	SCODescriptor(const SCODescriptor & object);
	virtual ~SCODescriptor();
    
    void copyFrom(const SCODescriptor & object);
    SCODescriptor & operator=(const SCODescriptor & object);
    
    typedef CDM::SCODescriptor WrappedType;

	SCODescriptor & setType(const CodedValue & value);
	CodedValue getType() const;
	bool getType(CodedValue & out) const;
	bool hasType() const;

	SCODescriptor & setHandle(const std::string & value);
	std::string getHandle() const;

	SCODescriptor & setDescriptorVersion(const VersionCounter & value);
	VersionCounter getDescriptorVersion() const;
	bool getDescriptorVersion(VersionCounter & out) const;
	bool hasDescriptorVersion() const;

	SCODescriptor & setIntendedUse(const IntendedUse & value);
	IntendedUse getIntendedUse() const;
	bool getIntendedUse(IntendedUse & out) const;
	bool hasIntendedUse() const;

	SCODescriptor & addProductionSpecification(const ProductionSpecification & value);
	std::vector<ProductionSpecification> getProductionSpecifications() const;
	void clearProductionSpecifications();
	

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
	std::shared_ptr<CDM::SCODescriptor> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* SCODESCRIPTOR_H_ */
