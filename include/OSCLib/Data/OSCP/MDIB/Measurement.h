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
 *  Measurement.h
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

#ifndef MEASUREMENT_H_
#define MEASUREMENT_H_

#include "OSCLib/Data/OSCP/MDIB/SimpleTypesMapping.h"
#include "OSCLib/Data/OSCP/OSCP-fwd.h"
#include "osdm-fwd.hxx"

namespace OSCLib {
namespace Data {
namespace OSCP {

class Measurement {
private:
	Measurement(const CDM::Measurement & object);
	operator CDM::Measurement() const;
	friend class ConvertFromCDM;
	friend class ConvertToCDM;
public:
	Measurement();
	Measurement(const Measurement & object);
	virtual ~Measurement();
    
    void copyFrom(const Measurement & object);
    Measurement & operator=(const Measurement & object);
    
    typedef CDM::Measurement WrappedType;

	Measurement & setMeasurementUnit(const CodedValue & value);
	CodedValue getMeasurementUnit() const;

	Measurement & setMeasuredValue(const double & value);
	double getMeasuredValue() const;

private:
	std::shared_ptr<CDM::Measurement> data;
};

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */
#endif /* MEASUREMENT_H_ */
