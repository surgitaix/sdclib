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

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
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

	StringMetricDescriptor & setType(const CodedValue & value);
	CodedValue getType() const;
	bool getType(CodedValue & out) const;
	bool hasType() const;

	StringMetricDescriptor & setHandle(const Handle & value);
	Handle getHandle() const;

	StringMetricDescriptor & setDescriptorVersion(const VersionCounter & value);
	VersionCounter getDescriptorVersion() const;
	bool getDescriptorVersion(VersionCounter & out) const;
	bool hasDescriptorVersion() const;

	StringMetricDescriptor & setSafetyClassification(const SafetyClassification & value);
	SafetyClassification getSafetyClassification() const;
	bool getSafetyClassification(SafetyClassification & out) const;
	bool hasSafetyClassification() const;

	StringMetricDescriptor & setUnit(const CodedValue & value);
	CodedValue getUnit() const;

	StringMetricDescriptor & setMetricCategory(const MetricCategory & value);
	MetricCategory getMetricCategory() const;

	StringMetricDescriptor & setDerivationMethod(const DerivationMethod & value);
	DerivationMethod getDerivationMethod() const;

	StringMetricDescriptor & setMetricAvailability(const MetricAvailability & value);
	MetricAvailability getMetricAvailability() const;

	StringMetricDescriptor & setMaxMeasurementTime(const duration & value);
	duration getMaxMeasurementTime() const;
	bool getMaxMeasurementTime(duration & out) const;
	bool hasMaxMeasurementTime() const;

	StringMetricDescriptor & setMaxDelayTime(const duration & value);
	duration getMaxDelayTime() const;
	bool getMaxDelayTime(duration & out) const;
	bool hasMaxDelayTime() const;

	StringMetricDescriptor & setDeterminationPeriod(const duration & value);
	duration getDeterminationPeriod() const;
	bool getDeterminationPeriod(duration & out) const;
	bool hasDeterminationPeriod() const;

	StringMetricDescriptor & setLifeTimePeriod(const duration & value);
	duration getLifeTimePeriod() const;
	bool getLifeTimePeriod(duration & out) const;
	bool hasLifeTimePeriod() const;

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
