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
 *  RealTimeSampleArrayMetricState.h
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

#ifndef REALTIMESAMPLEARRAYMETRICSTATE_H_
#define REALTIMESAMPLEARRAYMETRICSTATE_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/SDC-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace SDC {

class RealTimeSampleArrayMetricState {
private:
	RealTimeSampleArrayMetricState(const CDM::RealTimeSampleArrayMetricState & object);
	operator CDM::RealTimeSampleArrayMetricState() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class SDCProvider;
	friend class SDCConsumer;
	friend class MdState;
	friend class MdDescription;
public:
	RealTimeSampleArrayMetricState(
		HandleRef descriptorhandle
	); 
private:
	RealTimeSampleArrayMetricState(){};
public:
	RealTimeSampleArrayMetricState(const RealTimeSampleArrayMetricState & object);
	virtual ~RealTimeSampleArrayMetricState();
    
    void copyFrom(const RealTimeSampleArrayMetricState & object);
    RealTimeSampleArrayMetricState & operator=(const RealTimeSampleArrayMetricState & object);
    
    typedef CDM::RealTimeSampleArrayMetricState WrappedType;
    typedef RealTimeSampleArrayMetricDescriptor DescriptorType;

	RealTimeSampleArrayMetricState & setStateVersion(const VersionCounter & value);
	VersionCounter getStateVersion() const;
	bool getStateVersion(VersionCounter & out) const;
	bool hasStateVersion() const;

	RealTimeSampleArrayMetricState & setDescriptorHandle(const HandleRef & value);
	HandleRef getDescriptorHandle() const;

	RealTimeSampleArrayMetricState & setDescriptorVersion(const ReferencedVersion & value);
	ReferencedVersion getDescriptorVersion() const;
	bool getDescriptorVersion(ReferencedVersion & out) const;
	bool hasDescriptorVersion() const;

	RealTimeSampleArrayMetricState & setPhysicalConnector(const PhysicalConnectorInfo & value);
	PhysicalConnectorInfo getPhysicalConnector() const;
	bool getPhysicalConnector(PhysicalConnectorInfo & out) const;
	bool hasPhysicalConnector() const;

	RealTimeSampleArrayMetricState & setActivationState(const ComponentActivation & value);
	ComponentActivation getActivationState() const;
	bool getActivationState(ComponentActivation & out) const;
	bool hasActivationState() const;

	RealTimeSampleArrayMetricState & setActiveDeterminationPeriod(const xml_schema::Duration & value);
	xml_schema::Duration getActiveDeterminationPeriod() const;
	bool getActiveDeterminationPeriod(xml_schema::Duration & out) const;
	bool hasActiveDeterminationPeriod() const;

	RealTimeSampleArrayMetricState & setLifeTimePeriod(const xml_schema::Duration & value);
	xml_schema::Duration getLifeTimePeriod() const;
	bool getLifeTimePeriod(xml_schema::Duration & out) const;
	bool hasLifeTimePeriod() const;

	RealTimeSampleArrayMetricState & addBodySite(const CodedValue & value);
	std::vector<CodedValue> getBodySiteList() const;
	void clearBodySiteList();
	
	RealTimeSampleArrayMetricState & setMetricValue(const SampleArrayValue & value);
	SampleArrayValue getMetricValue() const;
	bool getMetricValue(SampleArrayValue & out) const;
	bool hasMetricValue() const;

	RealTimeSampleArrayMetricState & addPhysiologicalRange(const Range & value);
	std::vector<Range> getPhysiologicalRangeList() const;
	void clearPhysiologicalRangeList();
	
private:
	std::shared_ptr<CDM::RealTimeSampleArrayMetricState> data;
};

} /* namespace SDC */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* REALTIMESAMPLEARRAYMETRICSTATE_H_ */
