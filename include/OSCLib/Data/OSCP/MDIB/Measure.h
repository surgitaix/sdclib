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
 *  Measure.h
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

#ifndef MEASURE_H_
#define MEASURE_H_

#include "OSCLib/Data/OSCP/MDIB/EnumMappings.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class Measure {
private:
	Measure(const CDM::Measure & object);
	operator CDM::Measure() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	Measure();
	Measure(const Measure & object);
	virtual ~Measure();
    
    void copyFrom(const Measure & object);
    Measure & operator=(const Measure & object);
    
    typedef CDM::Measure WrappedType;

	Measure & setMeasurementUnit(const CodedValue & value);
	CodedValue getMeasurementUnit() const;

	Measure & setMeasuredValue(const double & value);
	double getMeasuredValue() const;
	bool getMeasuredValue(double & out) const;
	bool hasMeasuredValue() const;

private:
	std::shared_ptr<CDM::Measure> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* MEASURE_H_ */
