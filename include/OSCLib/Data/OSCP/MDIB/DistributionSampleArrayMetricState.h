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
 *  Author: besting, roehser
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

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class DistributionSampleArrayMetricState {
private:
	DistributionSampleArrayMetricState(const CDM::DistributionSampleArrayMetricState & object);
	operator CDM::DistributionSampleArrayMetricState() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	DistributionSampleArrayMetricState();
	DistributionSampleArrayMetricState(const DistributionSampleArrayMetricState & object);
	virtual ~DistributionSampleArrayMetricState();
    
    void copyFrom(const DistributionSampleArrayMetricState & object);
    DistributionSampleArrayMetricState & operator=(const DistributionSampleArrayMetricState & object);
    
    typedef CDM::DistributionSampleArrayMetricState WrappedType;

	DistributionSampleArrayMetricState & setStateVersion(const VersionCounter & value);
	VersionCounter getStateVersion() const;

	DistributionSampleArrayMetricState & setDescriptorHandle(const HandleRef & value);
	HandleRef getDescriptorHandle() const;

	DistributionSampleArrayMetricState & setDescriptorVersion(const ReferencedVersion & value);
	ReferencedVersion getDescriptorVersion() const;

	DistributionSampleArrayMetricState & setActivationState(const ComponentActivation & value);
	ComponentActivation getActivationState() const;

	DistributionSampleArrayMetricState & setActiveDeterminationPeriod(const duration & value);
	duration getActiveDeterminationPeriod() const;

	DistributionSampleArrayMetricState & setLifeTimePeriod(const duration & value);
	duration getLifeTimePeriod() const;
	bool getLifeTimePeriod(duration & out) const;
	bool hasLifeTimePeriod() const;

	DistributionSampleArrayMetricState & addBodySite(const CodedValue & value);
	std::vector<CodedValue> getBodySites() const;
	void clearBodySites();
	
	DistributionSampleArrayMetricState & setMetricValue(const SampleArrayValue & value);
	SampleArrayValue getMetricValue() const;
	bool getMetricValue(SampleArrayValue & out) const;
	bool hasMetricValue() const;

	DistributionSampleArrayMetricState & addPhysiologicalRange(const Range & value);
	std::vector<Range> getPhysiologicalRanges() const;
	void clearPhysiologicalRanges();
	
private:
	std::shared_ptr<CDM::DistributionSampleArrayMetricState> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* DISTRIBUTIONSAMPLEARRAYMETRICSTATE_H_ */
