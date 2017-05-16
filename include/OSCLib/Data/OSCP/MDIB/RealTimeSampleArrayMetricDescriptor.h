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
 *  Author: besting, roehser
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

#include "OSCLib/Data/OSCP/MDIB/custom/EnumMappings.h"
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
public:
	RealTimeSampleArrayMetricDescriptor();
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

	RealTimeSampleArrayMetricDescriptor & setHandle(const std::string & value);
	std::string getHandle() const;

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

	RealTimeSampleArrayMetricDescriptor & setAvailability(const MetricAvailability & value);
	MetricAvailability getAvailability() const;

	RealTimeSampleArrayMetricDescriptor & setMaxDelayTime(const Duration & value);
	Duration getMaxDelayTime() const;
	bool getMaxDelayTime(Duration & out) const;
	bool hasMaxDelayTime() const;

	RealTimeSampleArrayMetricDescriptor & addBodySite(const CodedValue & value);
	std::vector<CodedValue> getBodySites() const;
	void clearBodySites();
	
	RealTimeSampleArrayMetricDescriptor & setSamplePeriod(const Duration & value);
	Duration getSamplePeriod() const;

	RealTimeSampleArrayMetricDescriptor & setResolution(const double & value);
	double getResolution() const;

	RealTimeSampleArrayMetricDescriptor & addTechnicalRange(const Range & value);
	std::vector<Range> getTechnicalRanges() const;
	void clearTechnicalRanges();
	
private:
	std::shared_ptr<CDM::RealTimeSampleArrayMetricDescriptor> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* REALTIMESAMPLEARRAYMETRICDESCRIPTOR_H_ */
