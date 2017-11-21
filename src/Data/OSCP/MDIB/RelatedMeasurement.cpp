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
 *  RelatedMeasurement.cpp
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

#include "OSCLib/Data/OSCP/MDIB/RelatedMeasurement.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/Measurement.h"

namespace OSCLib {
namespace Data {
namespace OSCP {


RelatedMeasurement::RelatedMeasurement(
		Measurement value
) : data(Defaults::RelatedMeasurementInit(
		value
)) {}

RelatedMeasurement::operator CDM::RelatedMeasurement() const {
	return *data;
}

RelatedMeasurement::RelatedMeasurement(const CDM::RelatedMeasurement & object) : data(new CDM::RelatedMeasurement(object)) {

}

RelatedMeasurement::RelatedMeasurement(const RelatedMeasurement & object) : data(new CDM::RelatedMeasurement(*object.data)) {

}

RelatedMeasurement::~RelatedMeasurement() {

}

void RelatedMeasurement::copyFrom(const RelatedMeasurement & object) {
	*data = *object.data;
}

RelatedMeasurement & RelatedMeasurement:: operator=(const RelatedMeasurement & object) {
	copyFrom(object);
	return *this;
}


RelatedMeasurement & RelatedMeasurement::setValue(const Measurement & value) {
	data->Value(ConvertToCDM::convert(value));
	return *this;
}


Measurement RelatedMeasurement::getValue() const {
	return ConvertFromCDM::convert(data->Value());
}
	
RelatedMeasurement & RelatedMeasurement::setValidity(const MeasurementValidity & value) {
	data->Validity(ConvertToCDM::convert(value));
	return *this;
}

bool RelatedMeasurement::getValidity(MeasurementValidity & out) const {
	if (data->Validity().present()) {
		out = ConvertFromCDM::convert(data->Validity().get());
		return true;
	}
	return false;
}

MeasurementValidity RelatedMeasurement::getValidity() const {
	return ConvertFromCDM::convert(data->Validity().get());
}
	
bool RelatedMeasurement::hasValidity() const {
	return data->Validity().present();
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

