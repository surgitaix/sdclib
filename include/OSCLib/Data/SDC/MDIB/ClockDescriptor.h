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
 *  ClockDescriptor.h
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

#ifndef CLOCKDESCRIPTOR_H_
#define CLOCKDESCRIPTOR_H_

#include "OSCLib/Data/SDC/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/SDC/SDC-fwd.h"
#include "osdm-fwd.hxx"

namespace SDCLib {
namespace Data {
namespace SDC {

class ClockDescriptor {
private:
	ClockDescriptor(const CDM::ClockDescriptor & object);
	operator CDM::ClockDescriptor() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class SDCProvider;
	friend class SDCConsumer;
	friend class MdState;
	friend class MdDescription;
public:
	ClockDescriptor(
		Handle handle
	); 
private:
	ClockDescriptor(){};
public:
	ClockDescriptor(const ClockDescriptor & object);
	virtual ~ClockDescriptor();
    
    void copyFrom(const ClockDescriptor & object);
    ClockDescriptor & operator=(const ClockDescriptor & object);
    
    typedef CDM::ClockDescriptor WrappedType;

	ClockDescriptor & setType(const CodedValue & value);
	CodedValue getType() const;
	bool getType(CodedValue & out) const;
	bool hasType() const;

	ClockDescriptor & setHandle(const Handle & value);
	Handle getHandle() const;

	ClockDescriptor & setDescriptorVersion(const VersionCounter & value);
	VersionCounter getDescriptorVersion() const;
	bool getDescriptorVersion(VersionCounter & out) const;
	bool hasDescriptorVersion() const;

	ClockDescriptor & setSafetyClassification(const SafetyClassification & value);
	SafetyClassification getSafetyClassification() const;
	bool getSafetyClassification(SafetyClassification & out) const;
	bool hasSafetyClassification() const;

	ClockDescriptor & addProductionSpecification(const ProductionSpecification & value);
	std::vector<ProductionSpecification> getProductionSpecificationList() const;
	void clearProductionSpecificationList();
	
	ClockDescriptor & setResolution(const xml_schema::Duration & value);
	xml_schema::Duration getResolution() const;
	bool getResolution(xml_schema::Duration & out) const;
	bool hasResolution() const;

	ClockDescriptor & addTimeProtocol(const CodedValue & value);
	std::vector<CodedValue> getTimeProtocolList() const;
	void clearTimeProtocolList();
	
private:
	std::shared_ptr<CDM::ClockDescriptor> data;
};

} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */
#endif /* CLOCKDESCRIPTOR_H_ */
