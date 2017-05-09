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
 *  MetricQuality.h
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

#ifndef METRICQUALITY_H_
#define METRICQUALITY_H_

#include "OSCLib/Data/OSCP/MDIB/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class MetricQuality {
private:
	MetricQuality(const CDM::MetricQuality & object);
	operator CDM::MetricQuality() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	MetricQuality();
	MetricQuality(const MetricQuality & object);
	virtual ~MetricQuality();
    
    void copyFrom(const MetricQuality & object);
    MetricQuality & operator=(const MetricQuality & object);
    
    typedef CDM::MetricQuality WrappedType;

	MetricQuality & setValidity(const MeasurementValidity & value);
	MeasurementValidity getValidity() const;

	MetricQuality & setMode(const GenerationMode & value);
	GenerationMode getMode() const;
	bool getMode(GenerationMode & out) const;
	bool hasMode() const;

	MetricQuality & setQi(const double & value);
	double getQi() const;
	bool getQi(double & out) const;
	bool hasQi() const;

private:
	std::shared_ptr<CDM::MetricQuality> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* METRICQUALITY_H_ */
