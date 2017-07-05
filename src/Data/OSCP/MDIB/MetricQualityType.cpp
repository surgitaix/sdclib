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
 *  MetricQualityType.cpp
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

#include "OSCLib/Data/OSCP/MDIB/MetricQualityType.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"


namespace OSCLib {
namespace Data {
namespace OSCP {

MetricQualityType::MetricQualityType() : data(Defaults::MetricQualityType()) {
}

MetricQualityType::operator CDM::MetricQualityType() const {
	return *data;
}

MetricQualityType::MetricQualityType(const CDM::MetricQualityType & object) : data(new CDM::MetricQualityType(object)) {

}

MetricQualityType::MetricQualityType(const MetricQualityType & object) : data(new CDM::MetricQualityType(*object.data)) {

}

MetricQualityType::~MetricQualityType() {

}

void MetricQualityType::copyFrom(const MetricQualityType & object) {
	*data = *object.data;
}

MetricQualityType & MetricQualityType:: operator=(const MetricQualityType & object) {
	copyFrom(object);
	return *this;
}


MetricQualityType & MetricQualityType::setValidity(const MeasurementValidity & value) {
	data->Validity(ConvertToCDM::convert(value));
	return *this;
}


MeasurementValidity MetricQualityType::getValidity() const {
	return ConvertFromCDM::convert(data->Validity());
}
	
MetricQualityType & MetricQualityType::setMode(const GenerationMode & value) {
	data->Mode(ConvertToCDM::convert(value));
	return *this;
}


GenerationMode MetricQualityType::getMode() const {
	return ConvertFromCDM::convert(data->Mode());
}
	
MetricQualityType & MetricQualityType::setQi(const QualityIndicator & value) {
	data->Qi(ConvertToCDM::convert(value));
	return *this;
}


QualityIndicator MetricQualityType::getQi() const {
	return ConvertFromCDM::convert(data->Qi());
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

