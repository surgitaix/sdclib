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
 *  StringMetricValue.h
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

#ifndef STRINGMETRICVALUE_H_
#define STRINGMETRICVALUE_H_

#include "OSCLib/Data/OSCP/MDIB/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class StringMetricValue {
private:
	StringMetricValue(const CDM::StringMetricValue & object);
	operator CDM::StringMetricValue() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	StringMetricValue();
	StringMetricValue(const StringMetricValue & object);
	virtual ~StringMetricValue();
    
    void copyFrom(const StringMetricValue & object);
    StringMetricValue & operator=(const StringMetricValue & object);
    
    typedef CDM::StringMetricValue WrappedType;

	StringMetricValue & setMetricQuality(const MetricQuality & value);
	MetricQuality getMetricQuality() const;

	StringMetricValue & setStart_Time(const Timestamp & value);
	Timestamp getStart_Time() const;
	bool getStart_Time(Timestamp & out) const;
	bool hasStart_Time() const;

	StringMetricValue & setStop_Time(const Timestamp & value);
	Timestamp getStop_Time() const;
	bool getStop_Time(Timestamp & out) const;
	bool hasStop_Time() const;

	StringMetricValue & setDeterminationTime(const Timestamp & value);
	Timestamp getDeterminationTime() const;
	bool getDeterminationTime(Timestamp & out) const;
	bool hasDeterminationTime() const;

	StringMetricValue & setValue(const std::string & value);
	std::string getValue() const;
	bool getValue(std::string & out) const;
	bool hasValue() const;

private:
	std::shared_ptr<CDM::StringMetricValue> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* STRINGMETRICVALUE_H_ */
