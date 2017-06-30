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
 *  NumericMetricDescriptor.h
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

#ifndef NUMERICMETRICDESCRIPTOR_H_
#define NUMERICMETRICDESCRIPTOR_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class NumericMetricDescriptor {
private:
	NumericMetricDescriptor(const CDM::NumericMetricDescriptor & object);
	operator CDM::NumericMetricDescriptor() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	NumericMetricDescriptor();
	NumericMetricDescriptor(const NumericMetricDescriptor & object);
	virtual ~NumericMetricDescriptor();
    
    void copyFrom(const NumericMetricDescriptor & object);
    NumericMetricDescriptor & operator=(const NumericMetricDescriptor & object);
    
    typedef CDM::NumericMetricDescriptor WrappedType;
    typedef NumericMetricState StateType;

	NumericMetricDescriptor & setType(const CodedValue & value);
	CodedValue getType() const;
	bool getType(CodedValue & out) const;
	bool hasType() const;

	NumericMetricDescriptor & setHandle(const Handle & value);
	Handle getHandle() const;

	NumericMetricDescriptor & setDescriptorVersion(const VersionCounter & value);
	VersionCounter getDescriptorVersion() const;
	bool getDescriptorVersion(VersionCounter & out) const;
	bool hasDescriptorVersion() const;

	NumericMetricDescriptor & setSafetyClassification(const SafetyClassification & value);
	SafetyClassification getSafetyClassification() const;
	bool getSafetyClassification(SafetyClassification & out) const;
	bool hasSafetyClassification() const;

	NumericMetricDescriptor & setUnit(const CodedValue & value);
	CodedValue getUnit() const;

	NumericMetricDescriptor & setMetricCategory(const MetricCategory & value);
	MetricCategory getMetricCategory() const;

	NumericMetricDescriptor & setDerivationMethod(const DerivationMethod & value);
	DerivationMethod getDerivationMethod() const;

	NumericMetricDescriptor & setMetricAvailability(const MetricAvailability & value);
	MetricAvailability getMetricAvailability() const;

	NumericMetricDescriptor & setMaxMeasurementTime(const xml_schema::Duration & value);
	xml_schema::Duration getMaxMeasurementTime() const;
	bool getMaxMeasurementTime(xml_schema::Duration & out) const;
	bool hasMaxMeasurementTime() const;

	NumericMetricDescriptor & setMaxDelayTime(const xml_schema::Duration & value);
	xml_schema::Duration getMaxDelayTime() const;
	bool getMaxDelayTime(xml_schema::Duration & out) const;
	bool hasMaxDelayTime() const;

	NumericMetricDescriptor & setDeterminationPeriod(const xml_schema::Duration & value);
	xml_schema::Duration getDeterminationPeriod() const;
	bool getDeterminationPeriod(xml_schema::Duration & out) const;
	bool hasDeterminationPeriod() const;

	NumericMetricDescriptor & setLifeTimePeriod(const xml_schema::Duration & value);
	xml_schema::Duration getLifeTimePeriod() const;
	bool getLifeTimePeriod(xml_schema::Duration & out) const;
	bool hasLifeTimePeriod() const;

	NumericMetricDescriptor & addBodySite(const CodedValue & value);
	std::vector<CodedValue> getBodySiteLists() const;
	void clearBodySiteLists();
	
	NumericMetricDescriptor & setResolution(const double & value);
	double getResolution() const;

	NumericMetricDescriptor & setAveragingPeriod(const xml_schema::Duration & value);
	xml_schema::Duration getAveragingPeriod() const;

	NumericMetricDescriptor & addTechnicalRange(const Range & value);
	std::vector<Range> getTechnicalRangeLists() const;
	void clearTechnicalRangeLists();
	
private:
	std::shared_ptr<CDM::NumericMetricDescriptor> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* NUMERICMETRICDESCRIPTOR_H_ */
