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
 *  SampleArrayValue.h
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

#ifndef SAMPLEARRAYVALUE_H_
#define SAMPLEARRAYVALUE_H_

#include "OSCLib/Data/OSCP/MDIB/custom/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class SampleArrayValue {
private:
	SampleArrayValue(const CDM::SampleArrayValue & object);
	operator CDM::SampleArrayValue() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	SampleArrayValue();
	SampleArrayValue(const SampleArrayValue & object);
	virtual ~SampleArrayValue();
    
    void copyFrom(const SampleArrayValue & object);
    SampleArrayValue & operator=(const SampleArrayValue & object);
    
    typedef CDM::SampleArrayValue WrappedType;

	SampleArrayValue & setMetricQuality(const MetricQuality & value);
	MetricQuality getMetricQuality() const;

	SampleArrayValue & setStart_Time(const Timestamp & value);
	Timestamp getStart_Time() const;
	bool getStart_Time(Timestamp & out) const;
	bool hasStart_Time() const;

	SampleArrayValue & setStop_Time(const Timestamp & value);
	Timestamp getStop_Time() const;
	bool getStop_Time(Timestamp & out) const;
	bool hasStop_Time() const;

	SampleArrayValue & setDeterminationTime(const Timestamp & value);
	Timestamp getDeterminationTime() const;
	bool getDeterminationTime(Timestamp & out) const;
	bool hasDeterminationTime() const;

	SampleArrayValue & setSamples(const RealTimeValueType & value);
	RealTimeValueType getSamples() const;
	bool getSamples(RealTimeValueType & out) const;
	bool hasSamples() const;

	SampleArrayValue & addApplyAnnotation(const ApplyAnnotation & value);
	std::vector<ApplyAnnotation> getApplyAnnotations() const;
	void clearApplyAnnotations();
	
private:
	std::shared_ptr<CDM::SampleArrayValue> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* SAMPLEARRAYVALUE_H_ */
