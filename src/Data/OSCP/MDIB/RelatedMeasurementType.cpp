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
 *  RelatedMeasurementType.cpp
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

#include "OSCLib/Data/OSCP/MDIB/RelatedMeasurementType.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/Measurement.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

RelatedMeasurementType::RelatedMeasurementType() : data(Defaults::RelatedMeasurementType()) {
}

RelatedMeasurementType::operator CDM::RelatedMeasurementType() const {
	return *data;
}

RelatedMeasurementType::RelatedMeasurementType(const CDM::RelatedMeasurementType & object) : data(new CDM::RelatedMeasurementType(object)) {

}

RelatedMeasurementType::RelatedMeasurementType(const RelatedMeasurementType & object) : data(new CDM::RelatedMeasurementType(*object.data)) {

}

RelatedMeasurementType::~RelatedMeasurementType() {

}

void RelatedMeasurementType::copyFrom(const RelatedMeasurementType & object) {
	*data = *object.data;
}

RelatedMeasurementType & RelatedMeasurementType:: operator=(const RelatedMeasurementType & object) {
	copyFrom(object);
	return *this;
}


RelatedMeasurementType & RelatedMeasurementType::setValue(const Measurement & value) {
	data->Value(ConvertToCDM::convert(value));
	return *this;
}


Measurement RelatedMeasurementType::getValue() const {
	return ConvertFromCDM::convert(data->Value());
}
	
RelatedMeasurementType & RelatedMeasurementType::setValidity(const MeasurementValidity & value) {
	data->Validity(ConvertToCDM::convert(value));
	return *this;
}


MeasurementValidity RelatedMeasurementType::getValidity() const {
	return ConvertFromCDM::convert(data->Validity());
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

