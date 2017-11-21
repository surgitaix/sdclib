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
 *  EnumStringMetricDescriptor.h
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

#ifndef ENUMSTRINGMETRICDESCRIPTOR_H_
#define ENUMSTRINGMETRICDESCRIPTOR_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class EnumStringMetricDescriptor {
private:
	EnumStringMetricDescriptor(const CDM::EnumStringMetricDescriptor & object);
	operator CDM::EnumStringMetricDescriptor() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	EnumStringMetricDescriptor(
		Handle handle
		, 
		CodedValue unit
		, 
		MetricCategory metriccategory
		, 
		MetricAvailability metricavailability
	); 
	EnumStringMetricDescriptor() = delete;
	EnumStringMetricDescriptor(const EnumStringMetricDescriptor & object);
	virtual ~EnumStringMetricDescriptor();
    
    void copyFrom(const EnumStringMetricDescriptor & object);
    EnumStringMetricDescriptor & operator=(const EnumStringMetricDescriptor & object);
    
    typedef CDM::EnumStringMetricDescriptor WrappedType;

	EnumStringMetricDescriptor & setType(const CodedValue & value);
	CodedValue getType() const;
	bool getType(CodedValue & out) const;
	bool hasType() const;

	EnumStringMetricDescriptor & setHandle(const Handle & value);
	Handle getHandle() const;

	EnumStringMetricDescriptor & setDescriptorVersion(const VersionCounter & value);
	VersionCounter getDescriptorVersion() const;
	bool getDescriptorVersion(VersionCounter & out) const;
	bool hasDescriptorVersion() const;

	EnumStringMetricDescriptor & setSafetyClassification(const SafetyClassification & value);
	SafetyClassification getSafetyClassification() const;
	bool getSafetyClassification(SafetyClassification & out) const;
	bool hasSafetyClassification() const;

	EnumStringMetricDescriptor & setUnit(const CodedValue & value);
	CodedValue getUnit() const;

	EnumStringMetricDescriptor & setMetricCategory(const MetricCategory & value);
	MetricCategory getMetricCategory() const;

	EnumStringMetricDescriptor & setDerivationMethod(const DerivationMethod & value);
	DerivationMethod getDerivationMethod() const;
	bool getDerivationMethod(DerivationMethod & out) const;
	bool hasDerivationMethod() const;

	EnumStringMetricDescriptor & setMetricAvailability(const MetricAvailability & value);
	MetricAvailability getMetricAvailability() const;

	EnumStringMetricDescriptor & setMaxMeasurementTime(const xml_schema::Duration & value);
	xml_schema::Duration getMaxMeasurementTime() const;
	bool getMaxMeasurementTime(xml_schema::Duration & out) const;
	bool hasMaxMeasurementTime() const;

	EnumStringMetricDescriptor & setMaxDelayTime(const xml_schema::Duration & value);
	xml_schema::Duration getMaxDelayTime() const;
	bool getMaxDelayTime(xml_schema::Duration & out) const;
	bool hasMaxDelayTime() const;

	EnumStringMetricDescriptor & setDeterminationPeriod(const xml_schema::Duration & value);
	xml_schema::Duration getDeterminationPeriod() const;
	bool getDeterminationPeriod(xml_schema::Duration & out) const;
	bool hasDeterminationPeriod() const;

	EnumStringMetricDescriptor & setLifeTimePeriod(const xml_schema::Duration & value);
	xml_schema::Duration getLifeTimePeriod() const;
	bool getLifeTimePeriod(xml_schema::Duration & out) const;
	bool hasLifeTimePeriod() const;

	EnumStringMetricDescriptor & setActivationDuration(const xml_schema::Duration & value);
	xml_schema::Duration getActivationDuration() const;
	bool getActivationDuration(xml_schema::Duration & out) const;
	bool hasActivationDuration() const;

	EnumStringMetricDescriptor & addBodySite(const CodedValue & value);
	std::vector<CodedValue> getBodySiteList() const;
	void clearBodySiteList();
	
private:
	std::shared_ptr<CDM::EnumStringMetricDescriptor> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* ENUMSTRINGMETRICDESCRIPTOR_H_ */
