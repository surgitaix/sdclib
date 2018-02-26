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
 *  DistributionSampleArrayMetricState.h
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

#ifndef DISTRIBUTIONSAMPLEARRAYMETRICSTATE_H_
#define DISTRIBUTIONSAMPLEARRAYMETRICSTATE_H_

#include "OSCLib/Data/SDC/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/SDC/SDC-fwd.h"
#include "osdm-fwd.hxx"

namespace SDCLib {
namespace Data {
namespace SDC {

class DistributionSampleArrayMetricState {
private:
	DistributionSampleArrayMetricState(const CDM::DistributionSampleArrayMetricState & object);
	operator CDM::DistributionSampleArrayMetricState() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class SDCProvider;
	friend class SDCConsumer;
	friend class MdState;
	friend class MdDescription;
public:
	DistributionSampleArrayMetricState(
		HandleRef descriptorhandle
	); 
private:
	DistributionSampleArrayMetricState(){};
public:
	DistributionSampleArrayMetricState(const DistributionSampleArrayMetricState & object);
	virtual ~DistributionSampleArrayMetricState();
    
    void copyFrom(const DistributionSampleArrayMetricState & object);
    DistributionSampleArrayMetricState & operator=(const DistributionSampleArrayMetricState & object);
    
    typedef CDM::DistributionSampleArrayMetricState WrappedType;

	DistributionSampleArrayMetricState & setStateVersion(const VersionCounter & value);
	VersionCounter getStateVersion() const;
	bool getStateVersion(VersionCounter & out) const;
	bool hasStateVersion() const;

	DistributionSampleArrayMetricState & setDescriptorHandle(const HandleRef & value);
	HandleRef getDescriptorHandle() const;

	DistributionSampleArrayMetricState & setDescriptorVersion(const ReferencedVersion & value);
	ReferencedVersion getDescriptorVersion() const;
	bool getDescriptorVersion(ReferencedVersion & out) const;
	bool hasDescriptorVersion() const;

	DistributionSampleArrayMetricState & setPhysicalConnector(const PhysicalConnectorInfo & value);
	PhysicalConnectorInfo getPhysicalConnector() const;
	bool getPhysicalConnector(PhysicalConnectorInfo & out) const;
	bool hasPhysicalConnector() const;

	DistributionSampleArrayMetricState & setActivationState(const ComponentActivation & value);
	ComponentActivation getActivationState() const;
	bool getActivationState(ComponentActivation & out) const;
	bool hasActivationState() const;

	DistributionSampleArrayMetricState & setActiveDeterminationPeriod(const xml_schema::Duration & value);
	xml_schema::Duration getActiveDeterminationPeriod() const;
	bool getActiveDeterminationPeriod(xml_schema::Duration & out) const;
	bool hasActiveDeterminationPeriod() const;

	DistributionSampleArrayMetricState & setLifeTimePeriod(const xml_schema::Duration & value);
	xml_schema::Duration getLifeTimePeriod() const;
	bool getLifeTimePeriod(xml_schema::Duration & out) const;
	bool hasLifeTimePeriod() const;

	DistributionSampleArrayMetricState & addBodySite(const CodedValue & value);
	std::vector<CodedValue> getBodySiteList() const;
	void clearBodySiteList();
	
	DistributionSampleArrayMetricState & setMetricValue(const SampleArrayValue & value);
	SampleArrayValue getMetricValue() const;
	bool getMetricValue(SampleArrayValue & out) const;
	bool hasMetricValue() const;

	DistributionSampleArrayMetricState & addPhysiologicalRange(const Range & value);
	std::vector<Range> getPhysiologicalRangeList() const;
	void clearPhysiologicalRangeList();
	
private:
	std::shared_ptr<CDM::DistributionSampleArrayMetricState> data;
};

} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */
#endif /* DISTRIBUTIONSAMPLEARRAYMETRICSTATE_H_ */
