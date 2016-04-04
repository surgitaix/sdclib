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
 *  Measure.cpp
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

#include "OSCLib/Data/OSCP/MDIB/Measure.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

Measure::Measure() : data(Defaults::Measure()) {
}

Measure::operator CDM::Measure() const {
	return *data;
}

Measure::Measure(const CDM::Measure & object) : data(new CDM::Measure(object)) {

}

Measure::Measure(const Measure & object) : data(new CDM::Measure(*object.data)) {

}

Measure::~Measure() {

}

void Measure::copyFrom(const Measure & object) {
	*data = *object.data;
}

Measure & Measure:: operator=(const Measure & object) {
	copyFrom(object);
	return *this;
}


Measure & Measure::setMeasurementUnit(const CodedValue & value) {
	data->MeasurementUnit(ConvertToCDM::convert(value));
	return *this;
}


CodedValue Measure::getMeasurementUnit() const {
	return ConvertFromCDM::convert(data->MeasurementUnit());
}
	
Measure & Measure::setMeasuredValue(const double & value) {
	data->MeasuredValue(ConvertToCDM::convert(value));
	return *this;
}

bool Measure::getMeasuredValue(double & out) const {
	if (data->MeasuredValue().present()) {
		out = ConvertFromCDM::convert(data->MeasuredValue().get());
		return true;
	}
	return false;
}

double Measure::getMeasuredValue() const {
	return ConvertFromCDM::convert(data->MeasuredValue().get());
}
	
bool Measure::hasMeasuredValue() const {
	return data->MeasuredValue().present();
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

