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
 *  StringMetricDescriptor.h
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

#ifndef STRINGMETRICDESCRIPTOR_H_
#define STRINGMETRICDESCRIPTOR_H_

#include "OSCLib/Data/OSCP/MDIB/custom/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class StringMetricDescriptor {
private:
	StringMetricDescriptor(const CDM::StringMetricDescriptor & object);
	operator CDM::StringMetricDescriptor() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	StringMetricDescriptor();
	StringMetricDescriptor(const StringMetricDescriptor & object);
	virtual ~StringMetricDescriptor();
    
    void copyFrom(const StringMetricDescriptor & object);
    StringMetricDescriptor & operator=(const StringMetricDescriptor & object);
    
    typedef CDM::StringMetricDescriptor WrappedType;
    typedef StringMetricState StateType;

	StringMetricDescriptor & setType(const CodedValue & value);
	CodedValue getType() const;
	bool getType(CodedValue & out) const;
	bool hasType() const;

	StringMetricDescriptor & setHandle(const std::string & value);
	std::string getHandle() const;

	StringMetricDescriptor & setDescriptorVersion(const VersionCounter & value);
	VersionCounter getDescriptorVersion() const;
	bool getDescriptorVersion(VersionCounter & out) const;
	bool hasDescriptorVersion() const;

	StringMetricDescriptor & setSafetyClassification(const std::string & value);
	std::string getSafetyClassification() const;
	bool getSafetyClassification(std::string & out) const;
	bool hasSafetyClassification() const;

	StringMetricDescriptor & setUnit(const CodedValue & value);
	CodedValue getUnit() const;

	StringMetricDescriptor & setMetricCategory(const MetricCategory & value);
	MetricCategory getMetricCategory() const;

	StringMetricDescriptor & setAvailability(const MetricAvailability & value);
	MetricAvailability getAvailability() const;

	StringMetricDescriptor & setMaxDelayTime(const Duration & value);
	Duration getMaxDelayTime() const;
	bool getMaxDelayTime(Duration & out) const;
	bool hasMaxDelayTime() const;

	StringMetricDescriptor & addBodySite(const CodedValue & value);
	std::vector<CodedValue> getBodySites() const;
	void clearBodySites();
	
private:
	std::shared_ptr<CDM::StringMetricDescriptor> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* STRINGMETRICDESCRIPTOR_H_ */
