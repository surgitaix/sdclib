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
 *  Measurement.cpp
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

#include "OSCLib/Data/OSCP/MDIB/Measurement.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"

namespace OSCLib {
namespace Data {
namespace OSCP {


Measurement::Measurement(
		CodedValue measurementunit
		, 
		double measuredvalue
) : data(Defaults::MeasurementInit(
		measurementunit
		,
		measuredvalue
)) {}

Measurement::operator CDM::Measurement() const {
	return *data;
}

Measurement::Measurement(const CDM::Measurement & object) : data(new CDM::Measurement(object)) {

}

Measurement::Measurement(const Measurement & object) : data(new CDM::Measurement(*object.data)) {

}

Measurement::~Measurement() {

}

void Measurement::copyFrom(const Measurement & object) {
	data = std::shared_ptr<CDM::Measurement>( new CDM::Measurement(*object.data));
}

Measurement & Measurement:: operator=(const Measurement & object) {
	copyFrom(object);
	return *this;
}


Measurement & Measurement::setMeasurementUnit(const CodedValue & value) {
	data->MeasurementUnit(ConvertToCDM::convert(value));
	return *this;
}


CodedValue Measurement::getMeasurementUnit() const {
	return ConvertFromCDM::convert(data->MeasurementUnit());
}
	
Measurement & Measurement::setMeasuredValue(const double & value) {
	data->MeasuredValue(ConvertToCDM::convert(value));
	return *this;
}


double Measurement::getMeasuredValue() const {
	return ConvertFromCDM::convert(data->MeasuredValue());
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

