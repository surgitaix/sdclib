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
 *  MdsDescriptor.h
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

#ifndef MDSDESCRIPTOR_H_
#define MDSDESCRIPTOR_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/SDC-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class MdsDescriptor {
private:
	MdsDescriptor(const CDM::MdsDescriptor & object);
	operator CDM::MdsDescriptor() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class SDCProvider;
	friend class SDCConsumer;
	friend class MdState;
	friend class MdDescription;
public:
	MdsDescriptor(
		Handle handle
	); 
private:
	MdsDescriptor(){};
public:
	MdsDescriptor(const MdsDescriptor & object);
	virtual ~MdsDescriptor();
    
    void copyFrom(const MdsDescriptor & object);
    MdsDescriptor & operator=(const MdsDescriptor & object);
    
    typedef CDM::MdsDescriptor WrappedType;

	MdsDescriptor & setType(const CodedValue & value);
	CodedValue getType() const;
	bool getType(CodedValue & out) const;
	bool hasType() const;

	MdsDescriptor & setHandle(const Handle & value);
	Handle getHandle() const;

	MdsDescriptor & setDescriptorVersion(const VersionCounter & value);
	VersionCounter getDescriptorVersion() const;
	bool getDescriptorVersion(VersionCounter & out) const;
	bool hasDescriptorVersion() const;

	MdsDescriptor & setSafetyClassification(const SafetyClassification & value);
	SafetyClassification getSafetyClassification() const;
	bool getSafetyClassification(SafetyClassification & out) const;
	bool hasSafetyClassification() const;

	MdsDescriptor & addProductionSpecification(const ProductionSpecification & value);
	std::vector<ProductionSpecification> getProductionSpecificationList() const;
	void clearProductionSpecificationList();
	
	MdsDescriptor & setAlertSystem(const AlertSystemDescriptor & value);
	AlertSystemDescriptor getAlertSystem() const;
	bool getAlertSystem(AlertSystemDescriptor & out) const;
	bool hasAlertSystem() const;

	MdsDescriptor & setSco(const ScoDescriptor & value);
	ScoDescriptor getSco() const;
	bool getSco(ScoDescriptor & out) const;
	bool hasSco() const;

	MdsDescriptor & setMetaData(const MetaData & value);
	MetaData getMetaData() const;
	bool getMetaData(MetaData & out) const;
	bool hasMetaData() const;

	MdsDescriptor & setSystemContext(const SystemContextDescriptor & value);
	SystemContextDescriptor getSystemContext() const;
	bool getSystemContext(SystemContextDescriptor & out) const;
	bool hasSystemContext() const;

	MdsDescriptor & setClock(const ClockDescriptor & value);
	ClockDescriptor getClock() const;
	bool getClock(ClockDescriptor & out) const;
	bool hasClock() const;

	MdsDescriptor & setApprovedJurisdictions(const ApprovedJurisdictions & value);
	ApprovedJurisdictions getApprovedJurisdictions() const;
	bool getApprovedJurisdictions(ApprovedJurisdictions & out) const;
	bool hasApprovedJurisdictions() const;

	MdsDescriptor & addBattery(const BatteryDescriptor & value);
	std::vector<BatteryDescriptor> getBatteryList() const;
	void clearBatteryList();
	
	MdsDescriptor & addVmd(const VmdDescriptor & value);
	std::vector<VmdDescriptor> getVmdList() const;
	void clearVmdList();
	
private:
	std::shared_ptr<CDM::MdsDescriptor> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* MDSDESCRIPTOR_H_ */
