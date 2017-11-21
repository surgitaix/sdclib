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
 *  Author: besting, buerger, roehser
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
	DistributionSampleArrayMetricDescriptor(
		Handle handle
		, 
		CodedValue unit
		, 
		MetricCategory metriccategory
		, 
		MetricAvailability metricavailability
		, 
		CodedValue domainunit
		, 
		Range distributionrange
		, 
		double resolution
	); 
	DistributionSampleArrayMetricDescriptor() = delete;
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
	bool getDerivationMethod(DerivationMethod & out) const;
	bool hasDerivationMethod() const;

	DistributionSampleArrayMetricDescriptor & setMetricAvailability(const MetricAvailability & value);
	MetricAvailability getMetricAvailability() const;

	DistributionSampleArrayMetricDescriptor & setMaxMeasurementTime(const xml_schema::Duration & value);
	xml_schema::Duration getMaxMeasurementTime() const;
	bool getMaxMeasurementTime(xml_schema::Duration & out) const;
	bool hasMaxMeasurementTime() const;

	DistributionSampleArrayMetricDescriptor & setMaxDelayTime(const xml_schema::Duration & value);
	xml_schema::Duration getMaxDelayTime() const;
	bool getMaxDelayTime(xml_schema::Duration & out) const;
	bool hasMaxDelayTime() const;

	DistributionSampleArrayMetricDescriptor & setDeterminationPeriod(const xml_schema::Duration & value);
	xml_schema::Duration getDeterminationPeriod() const;
	bool getDeterminationPeriod(xml_schema::Duration & out) const;
	bool hasDeterminationPeriod() const;

	DistributionSampleArrayMetricDescriptor & setLifeTimePeriod(const xml_schema::Duration & value);
	xml_schema::Duration getLifeTimePeriod() const;
	bool getLifeTimePeriod(xml_schema::Duration & out) const;
	bool hasLifeTimePeriod() const;

	DistributionSampleArrayMetricDescriptor & setActivationDuration(const xml_schema::Duration & value);
	xml_schema::Duration getActivationDuration() const;
	bool getActivationDuration(xml_schema::Duration & out) const;
	bool hasActivationDuration() const;

	DistributionSampleArrayMetricDescriptor & addBodySite(const CodedValue & value);
	std::vector<CodedValue> getBodySiteList() const;
	void clearBodySiteList();
	
	DistributionSampleArrayMetricDescriptor & setDomainUnit(const CodedValue & value);
	CodedValue getDomainUnit() const;

	DistributionSampleArrayMetricDescriptor & setDistributionRange(const Range & value);
	Range getDistributionRange() const;

	DistributionSampleArrayMetricDescriptor & setResolution(const double & value);
	double getResolution() const;

	DistributionSampleArrayMetricDescriptor & addTechnicalRange(const Range & value);
	std::vector<Range> getTechnicalRangeList() const;
	void clearTechnicalRangeList();
	
private:
	std::shared_ptr<CDM::DistributionSampleArrayMetricDescriptor> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* DISTRIBUTIONSAMPLEARRAYMETRICDESCRIPTOR_H_ */
