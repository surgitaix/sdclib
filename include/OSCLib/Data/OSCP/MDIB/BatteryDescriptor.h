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
 *  BatteryDescriptor.h
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

#ifndef BATTERYDESCRIPTOR_H_
#define BATTERYDESCRIPTOR_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class BatteryDescriptor {
private:
	BatteryDescriptor(const CDM::BatteryDescriptor & object);
	operator CDM::BatteryDescriptor() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	BatteryDescriptor();
	BatteryDescriptor(const BatteryDescriptor & object);
	virtual ~BatteryDescriptor();
    
    void copyFrom(const BatteryDescriptor & object);
    BatteryDescriptor & operator=(const BatteryDescriptor & object);
    
    typedef CDM::BatteryDescriptor WrappedType;

	BatteryDescriptor & setType(const CodedValue & value);
	CodedValue getType() const;
	bool getType(CodedValue & out) const;
	bool hasType() const;

	BatteryDescriptor & setHandle(const Handle & value);
	Handle getHandle() const;

	BatteryDescriptor & setDescriptorVersion(const VersionCounter & value);
	VersionCounter getDescriptorVersion() const;
	bool getDescriptorVersion(VersionCounter & out) const;
	bool hasDescriptorVersion() const;

	BatteryDescriptor & setSafetyClassification(const SafetyClassification & value);
	SafetyClassification getSafetyClassification() const;
	bool getSafetyClassification(SafetyClassification & out) const;
	bool hasSafetyClassification() const;

	BatteryDescriptor & addProductionSpecification(const ProductionSpecification & value);
	std::vector<ProductionSpecification> getProductionSpecificationList() const;
	void clearProductionSpecificationList();
	
	BatteryDescriptor & setCapacityFullCharge(const Measurement & value);
	Measurement getCapacityFullCharge() const;
	bool getCapacityFullCharge(Measurement & out) const;
	bool hasCapacityFullCharge() const;

	BatteryDescriptor & setCapacitySpecified(const Measurement & value);
	Measurement getCapacitySpecified() const;
	bool getCapacitySpecified(Measurement & out) const;
	bool hasCapacitySpecified() const;

	BatteryDescriptor & setVoltageSpecified(const Measurement & value);
	Measurement getVoltageSpecified() const;
	bool getVoltageSpecified(Measurement & out) const;
	bool hasVoltageSpecified() const;

private:
	std::shared_ptr<CDM::BatteryDescriptor> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* BATTERYDESCRIPTOR_H_ */
