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
 *  EnumStringMetricState.h
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

#ifndef ENUMSTRINGMETRICSTATE_H_
#define ENUMSTRINGMETRICSTATE_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class EnumStringMetricState {
private:
	EnumStringMetricState(const CDM::EnumStringMetricState & object);
	operator CDM::EnumStringMetricState() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	EnumStringMetricState();
	EnumStringMetricState(const EnumStringMetricState & object);
	virtual ~EnumStringMetricState();
    
    void copyFrom(const EnumStringMetricState & object);
    EnumStringMetricState & operator=(const EnumStringMetricState & object);
    
    typedef CDM::EnumStringMetricState WrappedType;
    typedef EnumStringMetricDescriptor DescriptorType;
    typedef OSCPProviderEnumStringMetricStateHandler ProviderHandlerType;
    typedef OSCPConsumerEnumStringMetricStateHandler ConsumerHandlerType;

	EnumStringMetricState & setStateVersion(const VersionCounter & value);
	VersionCounter getStateVersion() const;
	bool getStateVersion(VersionCounter & out) const;
	bool hasStateVersion() const;

	EnumStringMetricState & setDescriptorHandle(const HandleRef & value);
	HandleRef getDescriptorHandle() const;

	EnumStringMetricState & setDescriptorVersion(const ReferencedVersion & value);
	ReferencedVersion getDescriptorVersion() const;
	bool getDescriptorVersion(ReferencedVersion & out) const;
	bool hasDescriptorVersion() const;

	EnumStringMetricState & setPhysicalConnector(const PhysicalConnectorInfo & value);
	PhysicalConnectorInfo getPhysicalConnector() const;
	bool getPhysicalConnector(PhysicalConnectorInfo & out) const;
	bool hasPhysicalConnector() const;

	EnumStringMetricState & setActivationState(const ComponentActivation & value);
	ComponentActivation getActivationState() const;
	bool getActivationState(ComponentActivation & out) const;
	bool hasActivationState() const;

	EnumStringMetricState & setActiveDeterminationPeriod(const xml_schema::Duration & value);
	xml_schema::Duration getActiveDeterminationPeriod() const;
	bool getActiveDeterminationPeriod(xml_schema::Duration & out) const;
	bool hasActiveDeterminationPeriod() const;

	EnumStringMetricState & setLifeTimePeriod(const xml_schema::Duration & value);
	xml_schema::Duration getLifeTimePeriod() const;
	bool getLifeTimePeriod(xml_schema::Duration & out) const;
	bool hasLifeTimePeriod() const;

	EnumStringMetricState & addBodySite(const CodedValue & value);
	std::vector<CodedValue> getBodySiteLists() const;
	void clearBodySiteLists();
	
	EnumStringMetricState & setMetricValue(const StringMetricValue & value);
	StringMetricValue getMetricValue() const;
	bool getMetricValue(StringMetricValue & out) const;
	bool hasMetricValue() const;

private:
	std::shared_ptr<CDM::EnumStringMetricState> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* ENUMSTRINGMETRICSTATE_H_ */
