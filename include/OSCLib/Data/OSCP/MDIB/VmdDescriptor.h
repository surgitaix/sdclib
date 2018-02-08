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
 *  VmdDescriptor.h
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

#ifndef VMDDESCRIPTOR_H_
#define VMDDESCRIPTOR_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/SDC-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class VmdDescriptor {
private:
	VmdDescriptor(const CDM::VmdDescriptor & object);
	operator CDM::VmdDescriptor() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class SDCProvider;
	friend class SDCConsumer;
	friend class MdState;
	friend class MdDescription;
public:
	VmdDescriptor(
		Handle handle
	); 
private:
	VmdDescriptor(){};
public:
	VmdDescriptor(const VmdDescriptor & object);
	virtual ~VmdDescriptor();
    
    void copyFrom(const VmdDescriptor & object);
    VmdDescriptor & operator=(const VmdDescriptor & object);
    
    typedef CDM::VmdDescriptor WrappedType;

	VmdDescriptor & setType(const CodedValue & value);
	CodedValue getType() const;
	bool getType(CodedValue & out) const;
	bool hasType() const;

	VmdDescriptor & setHandle(const Handle & value);
	Handle getHandle() const;

	VmdDescriptor & setDescriptorVersion(const VersionCounter & value);
	VersionCounter getDescriptorVersion() const;
	bool getDescriptorVersion(VersionCounter & out) const;
	bool hasDescriptorVersion() const;

	VmdDescriptor & setSafetyClassification(const SafetyClassification & value);
	SafetyClassification getSafetyClassification() const;
	bool getSafetyClassification(SafetyClassification & out) const;
	bool hasSafetyClassification() const;

	VmdDescriptor & addProductionSpecification(const ProductionSpecification & value);
	std::vector<ProductionSpecification> getProductionSpecificationList() const;
	void clearProductionSpecificationList();
	
	VmdDescriptor & setAlertSystem(const AlertSystemDescriptor & value);
	AlertSystemDescriptor getAlertSystem() const;
	bool getAlertSystem(AlertSystemDescriptor & out) const;
	bool hasAlertSystem() const;

	VmdDescriptor & setSco(const ScoDescriptor & value);
	ScoDescriptor getSco() const;
	bool getSco(ScoDescriptor & out) const;
	bool hasSco() const;

	VmdDescriptor & setApprovedJurisdictions(const ApprovedJurisdictions & value);
	ApprovedJurisdictions getApprovedJurisdictions() const;
	bool getApprovedJurisdictions(ApprovedJurisdictions & out) const;
	bool hasApprovedJurisdictions() const;

	VmdDescriptor & addChannel(const ChannelDescriptor & value);
	std::vector<ChannelDescriptor> getChannelList() const;
	void clearChannelList();
	
private:
	std::shared_ptr<CDM::VmdDescriptor> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* VMDDESCRIPTOR_H_ */
