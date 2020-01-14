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
 *  Author: besting, buerger, roehser
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

#include "SDCLib/Data/SDC/MDIB/SimpleTypesMapping.h"
#include "SDCLib/Data/SDC/SDC-fwd.h"
#include "DataModel/osdm-fwd.hxx"

namespace SDCLib {
namespace Data {
namespace SDC {

class ScoDescriptor
{
private:
	ScoDescriptor(const CDM::ScoDescriptor & object);
	operator CDM::ScoDescriptor() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class SDCProvider;
	friend class SDCConsumer;
	friend class MdState;
	friend class MdDescription;
public:
	ScoDescriptor(
		Handle handle
	);
private:
	ScoDescriptor(){};
public:
	ScoDescriptor(const ScoDescriptor& object);
	virtual ~ScoDescriptor() = default;

    void copyFrom(const ScoDescriptor& object);
    ScoDescriptor & operator=(const ScoDescriptor& object);

    typedef CDM::ScoDescriptor WrappedType;

	ScoDescriptor & setType(const CodedValue & value);
	CodedValue getType() const;
	bool getType(CodedValue & out) const;
	bool hasType() const;

	ScoDescriptor & setHandle(const Handle & value);
	Handle getHandle() const;

	ScoDescriptor & setDescriptorVersion(const VersionCounter & value);
	VersionCounter getDescriptorVersion() const;
	bool getDescriptorVersion(VersionCounter & out) const;
	bool hasDescriptorVersion() const;

	ScoDescriptor & setSafetyClassification(const SafetyClassification & value);
	SafetyClassification getSafetyClassification() const;
	bool getSafetyClassification(SafetyClassification & out) const;
	bool hasSafetyClassification() const;

	ScoDescriptor & addProductionSpecification(const ProductionSpecification & value);
	std::vector<ProductionSpecification> getProductionSpecificationList() const;
	void clearProductionSpecificationList();


	std::vector<ActivateOperationDescriptor> collectAllActivateOperationDescriptors() const;
	std::vector<SetAlertStateOperationDescriptor> collectAllSetAlertStateOperationDescriptors() const;
	std::vector<SetContextStateOperationDescriptor> collectAllSetContextOperationDescriptors() const;
	std::vector<SetStringOperationDescriptor> collectAllSetStringOperationDescriptors() const;
	std::vector<SetValueOperationDescriptor> collectAllSetValueOperationDescriptors() const;

private:
	template <class WrapperOperationDescriptorType>
	void collectOperationDescriptorImpl(std::vector<WrapperOperationDescriptorType> & out) const;
private:
	std::shared_ptr<CDM::ScoDescriptor> data = nullptr;
};

} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */
#endif /* SCODESCRIPTOR_H_ */
