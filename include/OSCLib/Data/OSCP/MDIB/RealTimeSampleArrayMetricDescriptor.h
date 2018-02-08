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
 *  RealTimeSampleArrayMetricDescriptor.h
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

#ifndef REALTIMESAMPLEARRAYMETRICDESCRIPTOR_H_
#define REALTIMESAMPLEARRAYMETRICDESCRIPTOR_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class RealTimeSampleArrayMetricDescriptor {
private:
	RealTimeSampleArrayMetricDescriptor(const CDM::RealTimeSampleArrayMetricDescriptor & object);
	operator CDM::RealTimeSampleArrayMetricDescriptor() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class SDCProvider;
	friend class SDCConsumer;
	friend class MdState;
	friend class MdDescription;
public:
	RealTimeSampleArrayMetricDescriptor(
		Handle handle
		, 
		CodedValue unit
		, 
		MetricCategory metriccategory
		, 
		MetricAvailability metricavailability
		, 
		double resolution
		, 
		xml_schema::Duration sampleperiod
	); 
private:
	RealTimeSampleArrayMetricDescriptor(){};
public:
	RealTimeSampleArrayMetricDescriptor(const RealTimeSampleArrayMetricDescriptor & object);
	virtual ~RealTimeSampleArrayMetricDescriptor();
    
    void copyFrom(const RealTimeSampleArrayMetricDescriptor & object);
    RealTimeSampleArrayMetricDescriptor & operator=(const RealTimeSampleArrayMetricDescriptor & object);
    
    typedef CDM::RealTimeSampleArrayMetricDescriptor WrappedType;
    typedef RealTimeSampleArrayMetricState StateType;

	RealTimeSampleArrayMetricDescriptor & setType(const CodedValue & value);
	CodedValue getType() const;
	bool getType(CodedValue & out) const;
	bool hasType() const;

	RealTimeSampleArrayMetricDescriptor & setHandle(const Handle & value);
	Handle getHandle() const;

	RealTimeSampleArrayMetricDescriptor & setDescriptorVersion(const VersionCounter & value);
	VersionCounter getDescriptorVersion() const;
	bool getDescriptorVersion(VersionCounter & out) const;
	bool hasDescriptorVersion() const;

	RealTimeSampleArrayMetricDescriptor & setSafetyClassification(const SafetyClassification & value);
	SafetyClassification getSafetyClassification() const;
	bool getSafetyClassification(SafetyClassification & out) const;
	bool hasSafetyClassification() const;

	RealTimeSampleArrayMetricDescriptor & setUnit(const CodedValue & value);
	CodedValue getUnit() const;

	RealTimeSampleArrayMetricDescriptor & setMetricCategory(const MetricCategory & value);
	MetricCategory getMetricCategory() const;

	RealTimeSampleArrayMetricDescriptor & setDerivationMethod(const DerivationMethod & value);
	DerivationMethod getDerivationMethod() const;
	bool getDerivationMethod(DerivationMethod & out) const;
	bool hasDerivationMethod() const;

	RealTimeSampleArrayMetricDescriptor & setMetricAvailability(const MetricAvailability & value);
	MetricAvailability getMetricAvailability() const;

	RealTimeSampleArrayMetricDescriptor & setMaxMeasurementTime(const xml_schema::Duration & value);
	xml_schema::Duration getMaxMeasurementTime() const;
	bool getMaxMeasurementTime(xml_schema::Duration & out) const;
	bool hasMaxMeasurementTime() const;

	RealTimeSampleArrayMetricDescriptor & setMaxDelayTime(const xml_schema::Duration & value);
	xml_schema::Duration getMaxDelayTime() const;
	bool getMaxDelayTime(xml_schema::Duration & out) const;
	bool hasMaxDelayTime() const;

	RealTimeSampleArrayMetricDescriptor & setDeterminationPeriod(const xml_schema::Duration & value);
	xml_schema::Duration getDeterminationPeriod() const;
	bool getDeterminationPeriod(xml_schema::Duration & out) const;
	bool hasDeterminationPeriod() const;

	RealTimeSampleArrayMetricDescriptor & setLifeTimePeriod(const xml_schema::Duration & value);
	xml_schema::Duration getLifeTimePeriod() const;
	bool getLifeTimePeriod(xml_schema::Duration & out) const;
	bool hasLifeTimePeriod() const;

	RealTimeSampleArrayMetricDescriptor & setActivationDuration(const xml_schema::Duration & value);
	xml_schema::Duration getActivationDuration() const;
	bool getActivationDuration(xml_schema::Duration & out) const;
	bool hasActivationDuration() const;

	RealTimeSampleArrayMetricDescriptor & addBodySite(const CodedValue & value);
	std::vector<CodedValue> getBodySiteList() const;
	void clearBodySiteList();
	
	RealTimeSampleArrayMetricDescriptor & addRelation(const Relation & value);
	std::vector<Relation> getRelationList() const;
	void clearRelationList();
	
	RealTimeSampleArrayMetricDescriptor & setResolution(const double & value);
	double getResolution() const;

	RealTimeSampleArrayMetricDescriptor & setSamplePeriod(const xml_schema::Duration & value);
	xml_schema::Duration getSamplePeriod() const;

	RealTimeSampleArrayMetricDescriptor & addTechnicalRange(const Range & value);
	std::vector<Range> getTechnicalRangeList() const;
	void clearTechnicalRangeList();
	
private:
	std::shared_ptr<CDM::RealTimeSampleArrayMetricDescriptor> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* REALTIMESAMPLEARRAYMETRICDESCRIPTOR_H_ */
