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
 *  Author: besting, roehser
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

#include "OSCLib/Data/OSCP/MDIB/custom/EnumMappings.h"
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
	EnumStringMetricDescriptor();
	EnumStringMetricDescriptor(const EnumStringMetricDescriptor & object);
	virtual ~EnumStringMetricDescriptor();
    
    void copyFrom(const EnumStringMetricDescriptor & object);
    EnumStringMetricDescriptor & operator=(const EnumStringMetricDescriptor & object);
    
    typedef CDM::EnumStringMetricDescriptor WrappedType;

	EnumStringMetricDescriptor & setType(const CodedValue & value);
	CodedValue getType() const;
	bool getType(CodedValue & out) const;
	bool hasType() const;

	EnumStringMetricDescriptor & setHandle(const std::string & value);
	std::string getHandle() const;

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

	EnumStringMetricDescriptor & setAvailability(const MetricAvailability & value);
	MetricAvailability getAvailability() const;

	EnumStringMetricDescriptor & setMaxDelayTime(const Duration & value);
	Duration getMaxDelayTime() const;
	bool getMaxDelayTime(Duration & out) const;
	bool hasMaxDelayTime() const;

	EnumStringMetricDescriptor & addBodySite(const CodedValue & value);
	std::vector<CodedValue> getBodySites() const;
	void clearBodySites();
	
	EnumStringMetricDescriptor & addAllowedValue(const AllowedValue & value);
	std::vector<AllowedValue> getAllowedValues() const;
	void clearAllowedValues();
	
private:
	std::shared_ptr<CDM::EnumStringMetricDescriptor> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* ENUMSTRINGMETRICDESCRIPTOR_H_ */
