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
 *  NumericMetricState.h
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

#ifndef NUMERICMETRICSTATE_H_
#define NUMERICMETRICSTATE_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class NumericMetricState {
private:
	NumericMetricState(const CDM::NumericMetricState & object);
	operator CDM::NumericMetricState() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	NumericMetricState();
	NumericMetricState(const NumericMetricState & object);
	virtual ~NumericMetricState();
    
    void copyFrom(const NumericMetricState & object);
    NumericMetricState & operator=(const NumericMetricState & object);
    
    typedef CDM::NumericMetricState WrappedType;

	NumericMetricState & setStateVersion(const VersionCounter & value);
	VersionCounter getStateVersion() const;

	NumericMetricState & setDescriptorHandle(const HandleRef & value);
	HandleRef getDescriptorHandle() const;

	NumericMetricState & setDescriptorVersion(const ReferencedVersion & value);
	ReferencedVersion getDescriptorVersion() const;

	NumericMetricState & setActivationState(const ComponentActivation & value);
	ComponentActivation getActivationState() const;

	NumericMetricState & setActiveDeterminationPeriod(const duration & value);
	duration getActiveDeterminationPeriod() const;

	NumericMetricState & setLifeTimePeriod(const duration & value);
	duration getLifeTimePeriod() const;
	bool getLifeTimePeriod(duration & out) const;
	bool hasLifeTimePeriod() const;

	NumericMetricState & addBodySite(const CodedValue & value);
	std::vector<CodedValue> getBodySites() const;
	void clearBodySites();
	
	NumericMetricState & setMetricValue(const NumericMetricValue & value);
	NumericMetricValue getMetricValue() const;
	bool getMetricValue(NumericMetricValue & out) const;
	bool hasMetricValue() const;

	NumericMetricState & setActiveAveragingPeriod(const duration & value);
	duration getActiveAveragingPeriod() const;
	bool getActiveAveragingPeriod(duration & out) const;
	bool hasActiveAveragingPeriod() const;

	NumericMetricState & addPhysiologicalRange(const Range & value);
	std::vector<Range> getPhysiologicalRanges() const;
	void clearPhysiologicalRanges();
	
private:
	std::shared_ptr<CDM::NumericMetricState> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* NUMERICMETRICSTATE_H_ */
