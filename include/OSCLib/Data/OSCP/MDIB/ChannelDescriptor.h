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
 *  ChannelDescriptor.h
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

#ifndef CHANNELDESCRIPTOR_H_
#define CHANNELDESCRIPTOR_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class ChannelDescriptor {
private:
	ChannelDescriptor(const CDM::ChannelDescriptor & object);
	operator CDM::ChannelDescriptor() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	ChannelDescriptor();
	ChannelDescriptor(const ChannelDescriptor & object);
	virtual ~ChannelDescriptor();
    
    void copyFrom(const ChannelDescriptor & object);
    ChannelDescriptor & operator=(const ChannelDescriptor & object);
    
    typedef CDM::ChannelDescriptor WrappedType;

	ChannelDescriptor & setType(const CodedValue & value);
	CodedValue getType() const;
	bool getType(CodedValue & out) const;
	bool hasType() const;

	ChannelDescriptor & setHandle(const Handle & value);
	Handle getHandle() const;

	ChannelDescriptor & setDescriptorVersion(const VersionCounter & value);
	VersionCounter getDescriptorVersion() const;
	bool getDescriptorVersion(VersionCounter & out) const;
	bool hasDescriptorVersion() const;

	ChannelDescriptor & setSafetyClassification(const SafetyClassification & value);
	SafetyClassification getSafetyClassification() const;
	bool getSafetyClassification(SafetyClassification & out) const;
	bool hasSafetyClassification() const;

	ChannelDescriptor & setSpecType(const CodedValue & value);
	CodedValue getSpecType() const;

	ChannelDescriptor & setProductionSpec(const std::string & value);
	std::string getProductionSpec() const;

	ChannelDescriptor & setComponentId(const InstanceIdentifier & value);
	InstanceIdentifier getComponentId() const;
	bool getComponentId(InstanceIdentifier & out) const;
	bool hasComponentId() const;

	ChannelDescriptor & setAlertSystem(const AlertSystemDescriptor & value);
	AlertSystemDescriptor getAlertSystem() const;
	bool getAlertSystem(AlertSystemDescriptor & out) const;
	bool hasAlertSystem() const;

	ChannelDescriptor & addMetric(const AbstractMetricDescriptor & value);
	std::vector<AbstractMetricDescriptor> getMetrics() const;
	void clearMetrics();
	
private:
	std::shared_ptr<CDM::ChannelDescriptor> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* CHANNELDESCRIPTOR_H_ */
