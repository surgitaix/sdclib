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
 *  Author: besting, buerger, roehser
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

#include "OSCLib/Data/SDC/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/SDC/SDC-fwd.h"
#include "osdm-fwd.hxx"

namespace SDCLib {
namespace Data {
namespace SDC {

class StringMetricValue {
private:
	StringMetricValue(const CDM::StringMetricValue & object);
	operator CDM::StringMetricValue() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class SDCProvider;
	friend class SDCConsumer;
	friend class MdState;
	friend class MdDescription;
public:
	StringMetricValue(
		MetricQuality metricquality
	);
private:
	StringMetricValue(){};
public:
	StringMetricValue(const StringMetricValue & object);
	virtual ~StringMetricValue();

    void copyFrom(const StringMetricValue & object);
    StringMetricValue & operator=(const StringMetricValue & object);

    typedef CDM::StringMetricValue WrappedType;

	StringMetricValue & setMetricQuality(const MetricQuality & value);
	MetricQuality getMetricQuality() const;

	StringMetricValue & setStartTime(const Timestamp & value);
	Timestamp getStartTime() const;
	bool getStartTime(Timestamp & out) const;
	bool hasStartTime() const;

	StringMetricValue & setStopTime(const Timestamp & value);
	Timestamp getStopTime() const;
	bool getStopTime(Timestamp & out) const;
	bool hasStopTime() const;

	StringMetricValue & setDeterminationTime(const Timestamp & value);
	Timestamp getDeterminationTime() const;
	bool getDeterminationTime(Timestamp & out) const;
	bool hasDeterminationTime() const;

	StringMetricValue & addAnnotation(const Annotation & value);
	std::vector<Annotation> getAnnotationList() const;
	void clearAnnotationList();

	StringMetricValue & setValue(const std::string & value);
	std::string getValue() const;
	bool getValue(std::string & out) const;
	bool hasValue() const;

private:
	std::shared_ptr<CDM::StringMetricValue> data;
};

} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */
#endif /* STRINGMETRICVALUE_H_ */
