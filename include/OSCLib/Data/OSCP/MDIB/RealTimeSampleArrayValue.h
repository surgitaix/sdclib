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
 *  RealTimeSampleArrayValue.h
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

#ifndef REALTIMESAMPLEARRAYVALUE_H_
#define REALTIMESAMPLEARRAYVALUE_H_

#include "OSCLib/Data/OSCP/MDIB/custom/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class RealTimeSampleArrayValue {
private:
	RealTimeSampleArrayValue(const CDM::RealTimeSampleArrayValue & object);
	operator CDM::RealTimeSampleArrayValue() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	RealTimeSampleArrayValue();
	RealTimeSampleArrayValue(const RealTimeSampleArrayValue & object);
	virtual ~RealTimeSampleArrayValue();
    
    void copyFrom(const RealTimeSampleArrayValue & object);
    RealTimeSampleArrayValue & operator=(const RealTimeSampleArrayValue & object);
    
    typedef CDM::RealTimeSampleArrayValue WrappedType;

	RealTimeSampleArrayValue & setMetricQuality(const MetricQuality & value);
	MetricQuality getMetricQuality() const;

	RealTimeSampleArrayValue & setStart_Time(const Timestamp & value);
	Timestamp getStart_Time() const;
	bool getStart_Time(Timestamp & out) const;
	bool hasStart_Time() const;

	RealTimeSampleArrayValue & setStop_Time(const Timestamp & value);
	Timestamp getStop_Time() const;
	bool getStop_Time(Timestamp & out) const;
	bool hasStop_Time() const;

	RealTimeSampleArrayValue & setDeterminationTime(const Timestamp & value);
	Timestamp getDeterminationTime() const;
	bool getDeterminationTime(Timestamp & out) const;
	bool hasDeterminationTime() const;

	RealTimeSampleArrayValue & setSamples(const RTValueType & value);
	RTValueType getSamples() const;
	bool getSamples(RTValueType & out) const;
	bool hasSamples() const;

	RealTimeSampleArrayValue & addAnnotation(const Annotation & value);
	std::vector<Annotation> getAnnotations() const;
	void clearAnnotations();
	
private:
	std::shared_ptr<CDM::RealTimeSampleArrayValue> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* REALTIMESAMPLEARRAYVALUE_H_ */
