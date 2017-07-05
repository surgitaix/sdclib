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
 *  MetricQualityType.h
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

#ifndef METRICQUALITYTYPE_H_
#define METRICQUALITYTYPE_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class MetricQualityType {
private:
	MetricQualityType(const CDM::MetricQualityType & object);
	operator CDM::MetricQualityType() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	MetricQualityType();
	MetricQualityType(const MetricQualityType & object);
	virtual ~MetricQualityType();
    
    void copyFrom(const MetricQualityType & object);
    MetricQualityType & operator=(const MetricQualityType & object);
    
    typedef CDM::MetricQualityType WrappedType;

	MetricQualityType & setValidity(const MeasurementValidity & value);
	MeasurementValidity getValidity() const;

	MetricQualityType & setMode(const GenerationMode & value);
	GenerationMode getMode() const;

	MetricQualityType & setQi(const QualityIndicator & value);
	QualityIndicator getQi() const;

private:
	std::shared_ptr<CDM::MetricQualityType> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* METRICQUALITYTYPE_H_ */
