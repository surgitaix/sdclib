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
 *  DistributionSampleArrayMetricDescriptor.h
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

#ifndef DISTRIBUTIONSAMPLEARRAYMETRICDESCRIPTOR_H_
#define DISTRIBUTIONSAMPLEARRAYMETRICDESCRIPTOR_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class DistributionSampleArrayMetricDescriptor {
private:
	DistributionSampleArrayMetricDescriptor(const CDM::DistributionSampleArrayMetricDescriptor & object);
	operator CDM::DistributionSampleArrayMetricDescriptor() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	DistributionSampleArrayMetricDescriptor();
	DistributionSampleArrayMetricDescriptor(const DistributionSampleArrayMetricDescriptor & object);
	virtual ~DistributionSampleArrayMetricDescriptor();
    
    void copyFrom(const DistributionSampleArrayMetricDescriptor & object);
    DistributionSampleArrayMetricDescriptor & operator=(const DistributionSampleArrayMetricDescriptor & object);
    
    typedef CDM::DistributionSampleArrayMetricDescriptor WrappedType;

	DistributionSampleArrayMetricDescriptor & setType(const CodedValue & value);
	CodedValue getType() const;
	bool getType(CodedValue & out) const;
	bool hasType() const;

	DistributionSampleArrayMetricDescriptor & setHandle(const Handle & value);
	Handle getHandle() const;

	DistributionSampleArrayMetricDescriptor & setDescriptorVersion(const VersionCounter & value);
	VersionCounter getDescriptorVersion() const;
	bool getDescriptorVersion(VersionCounter & out) const;
	bool hasDescriptorVersion() const;

	DistributionSampleArrayMetricDescriptor & setSafetyClassification(const SafetyClassification & value);
	SafetyClassification getSafetyClassification() const;
	bool getSafetyClassification(SafetyClassification & out) const;
	bool hasSafetyClassification() const;

	DistributionSampleArrayMetricDescriptor & setUnit(const CodedValue & value);
	CodedValue getUnit() const;

	DistributionSampleArrayMetricDescriptor & setMetricCategory(const MetricCategory & value);
	MetricCategory getMetricCategory() const;

	DistributionSampleArrayMetricDescriptor & setDerivationMethod(const DerivationMethod & value);
	DerivationMethod getDerivationMethod() const;

	DistributionSampleArrayMetricDescriptor & setMetricAvailability(const MetricAvailability & value);
	MetricAvailability getMetricAvailability() const;

	DistributionSampleArrayMetricDescriptor & setMaxMeasurementTime(const duration & value);
	duration getMaxMeasurementTime() const;
	bool getMaxMeasurementTime(duration & out) const;
	bool hasMaxMeasurementTime() const;

	DistributionSampleArrayMetricDescriptor & setMaxDelayTime(const duration & value);
	duration getMaxDelayTime() const;
	bool getMaxDelayTime(duration & out) const;
	bool hasMaxDelayTime() const;

	DistributionSampleArrayMetricDescriptor & setDeterminationPeriod(const duration & value);
	duration getDeterminationPeriod() const;
	bool getDeterminationPeriod(duration & out) const;
	bool hasDeterminationPeriod() const;

	DistributionSampleArrayMetricDescriptor & setLifeTimePeriod(const duration & value);
	duration getLifeTimePeriod() const;
	bool getLifeTimePeriod(duration & out) const;
	bool hasLifeTimePeriod() const;

	DistributionSampleArrayMetricDescriptor & addBodySite(const CodedValue & value);
	std::vector<CodedValue> getBodySites() const;
	void clearBodySites();
	
	DistributionSampleArrayMetricDescriptor & setDomainUnit(const CodedValue & value);
	CodedValue getDomainUnit() const;

	DistributionSampleArrayMetricDescriptor & setDistributionRange(const Range & value);
	Range getDistributionRange() const;

	DistributionSampleArrayMetricDescriptor & setResolution(const decimal & value);
	decimal getResolution() const;

	DistributionSampleArrayMetricDescriptor & addTechnicalRange(const Range & value);
	std::vector<Range> getTechnicalRanges() const;
	void clearTechnicalRanges();
	
private:
	std::shared_ptr<CDM::DistributionSampleArrayMetricDescriptor> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* DISTRIBUTIONSAMPLEARRAYMETRICDESCRIPTOR_H_ */
