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
 *  Author: besting, roehser
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
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class RealTimeSampleArrayMetricState {
private:
	RealTimeSampleArrayMetricState(const CDM::RealTimeSampleArrayMetricState & object);
	operator CDM::RealTimeSampleArrayMetricState() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	RealTimeSampleArrayMetricState();
	RealTimeSampleArrayMetricState(const RealTimeSampleArrayMetricState & object);
	virtual ~RealTimeSampleArrayMetricState();
    
    void copyFrom(const RealTimeSampleArrayMetricState & object);
    RealTimeSampleArrayMetricState & operator=(const RealTimeSampleArrayMetricState & object);
    
    typedef CDM::RealTimeSampleArrayMetricState WrappedType;

	RealTimeSampleArrayMetricState & setStateVersion(const VersionCounter & value);
	VersionCounter getStateVersion() const;

	RealTimeSampleArrayMetricState & setDescriptorHandle(const HandleRef & value);
	HandleRef getDescriptorHandle() const;

	RealTimeSampleArrayMetricState & setDescriptorVersion(const ReferencedVersion & value);
	ReferencedVersion getDescriptorVersion() const;

	RealTimeSampleArrayMetricState & setActivationState(const ComponentActivation & value);
	ComponentActivation getActivationState() const;

	RealTimeSampleArrayMetricState & setActiveDeterminationPeriod(const duration & value);
	duration getActiveDeterminationPeriod() const;

	RealTimeSampleArrayMetricState & setLifeTimePeriod(const duration & value);
	duration getLifeTimePeriod() const;
	bool getLifeTimePeriod(duration & out) const;
	bool hasLifeTimePeriod() const;

	RealTimeSampleArrayMetricState & addBodySite(const CodedValue & value);
	std::vector<CodedValue> getBodySites() const;
	void clearBodySites();
	
	RealTimeSampleArrayMetricState & setMetricValue(const SampleArrayValue & value);
	SampleArrayValue getMetricValue() const;
	bool getMetricValue(SampleArrayValue & out) const;
	bool hasMetricValue() const;

	RealTimeSampleArrayMetricState & addPhysiologicalRange(const Range & value);
	std::vector<Range> getPhysiologicalRanges() const;
	void clearPhysiologicalRanges();
	
private:
	std::shared_ptr<CDM::RealTimeSampleArrayMetricState> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* REALTIMESAMPLEARRAYMETRICSTATE_H_ */
