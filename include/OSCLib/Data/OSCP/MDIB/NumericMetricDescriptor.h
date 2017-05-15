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

#include "OSCLib/Data/OSCP/MDIB/custom/EnumMappings.h"
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

	NumericMetricDescriptor & setHandle(const std::string & value);
	std::string getHandle() const;

	NumericMetricDescriptor & setDescriptorVersion(const VersionCounter & value);
	VersionCounter getDescriptorVersion() const;
	bool getDescriptorVersion(VersionCounter & out) const;
	bool hasDescriptorVersion() const;

	NumericMetricDescriptor & setSafetyClassification(const std::string & value);
	std::string getSafetyClassification() const;
	bool getSafetyClassification(std::string & out) const;
	bool hasSafetyClassification() const;

	NumericMetricDescriptor & setUnit(const CodedValue & value);
	CodedValue getUnit() const;

	NumericMetricDescriptor & setMetricCategory(const MetricCategory & value);
	MetricCategory getMetricCategory() const;

	NumericMetricDescriptor & setAvailability(const MetricAvailability & value);
	MetricAvailability getAvailability() const;

	NumericMetricDescriptor & setMaxDelayTime(const Duration & value);
	Duration getMaxDelayTime() const;
	bool getMaxDelayTime(Duration & out) const;
	bool hasMaxDelayTime() const;

	NumericMetricDescriptor & addBodySite(const CodedValue & value);
	std::vector<CodedValue> getBodySites() const;
	void clearBodySites();
	
	NumericMetricDescriptor & setResolution(const double & value);
	double getResolution() const;

	NumericMetricDescriptor & setMeasurePeriod(const Duration & value);
	Duration getMeasurePeriod() const;
	bool getMeasurePeriod(Duration & out) const;
	bool hasMeasurePeriod() const;

	NumericMetricDescriptor & setAveragingPeriod(const Duration & value);
	Duration getAveragingPeriod() const;
	bool getAveragingPeriod(Duration & out) const;
	bool hasAveragingPeriod() const;

	NumericMetricDescriptor & addTechnicalRange(const Range & value);
	std::vector<Range> getTechnicalRanges() const;
	void clearTechnicalRanges();
	
private:
	std::shared_ptr<CDM::NumericMetricDescriptor> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* NUMERICMETRICDESCRIPTOR_H_ */
