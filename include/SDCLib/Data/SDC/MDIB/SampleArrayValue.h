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
 *  Author: besting, buerger, roehser
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

#include "SDCLib/Data/SDC/MDIB/SimpleTypesMapping.h"
#include "SDCLib/Data/SDC/SDC-fwd.h"
#include "osdm-fwd.hxx"

namespace SDCLib {
namespace Data {
namespace SDC {

class SampleArrayValue {
private:
	SampleArrayValue(const CDM::SampleArrayValue & object);
	operator CDM::SampleArrayValue() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
	friend class SDCProvider;
	friend class SDCConsumer;
	friend class MdState;
	friend class MdDescription;
public:
	SampleArrayValue(
		MetricQuality metricquality
	);
private:
	SampleArrayValue(){};
public:
	SampleArrayValue(const SampleArrayValue & object);
	virtual ~SampleArrayValue();

    void copyFrom(const SampleArrayValue & object);
    SampleArrayValue & operator=(const SampleArrayValue & object);

    typedef CDM::SampleArrayValue WrappedType;

	SampleArrayValue & setMetricQuality(const MetricQuality & value);
	MetricQuality getMetricQuality() const;

	SampleArrayValue & setStartTime(const Timestamp & value);
	Timestamp getStartTime() const;
	bool getStartTime(Timestamp & out) const;
	bool hasStartTime() const;

	SampleArrayValue & setStopTime(const Timestamp & value);
	Timestamp getStopTime() const;
	bool getStopTime(Timestamp & out) const;
	bool hasStopTime() const;

	SampleArrayValue & setDeterminationTime(const Timestamp & value);
	Timestamp getDeterminationTime() const;
	bool getDeterminationTime(Timestamp & out) const;
	bool hasDeterminationTime() const;

	SampleArrayValue & addAnnotation(const Annotation & value);
	std::vector<Annotation> getAnnotationList() const;
	void clearAnnotationList();

	SampleArrayValue & setSamples(const RealTimeValueType & value);
	RealTimeValueType getSamples() const;
	bool getSamples(RealTimeValueType & out) const;
	bool hasSamples() const;

	SampleArrayValue & addApplyAnnotation(const ApplyAnnotation & value);
	std::vector<ApplyAnnotation> getApplyAnnotationList() const;
	void clearApplyAnnotationList();

private:
	std::shared_ptr<CDM::SampleArrayValue> data;
};

} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */
#endif /* SAMPLEARRAYVALUE_H_ */
