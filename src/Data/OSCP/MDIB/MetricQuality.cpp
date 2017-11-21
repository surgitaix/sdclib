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
 *  MetricQuality.cpp
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

#include "OSCLib/Data/OSCP/MDIB/MetricQuality.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"


namespace OSCLib {
namespace Data {
namespace OSCP {


MetricQuality::MetricQuality(
		MeasurementValidity validity
) : data(Defaults::MetricQualityInit(
		validity
)) {}

MetricQuality::operator CDM::MetricQuality() const {
	return *data;
}

MetricQuality::MetricQuality(const CDM::MetricQuality & object) : data(new CDM::MetricQuality(object)) {

}

MetricQuality::MetricQuality(const MetricQuality & object) : data(new CDM::MetricQuality(*object.data)) {

}

MetricQuality::~MetricQuality() {

}

void MetricQuality::copyFrom(const MetricQuality & object) {
	*data = *object.data;
}

MetricQuality & MetricQuality:: operator=(const MetricQuality & object) {
	copyFrom(object);
	return *this;
}


MetricQuality & MetricQuality::setValidity(const MeasurementValidity & value) {
	data->Validity(ConvertToCDM::convert(value));
	return *this;
}


MeasurementValidity MetricQuality::getValidity() const {
	return ConvertFromCDM::convert(data->Validity());
}
	
MetricQuality & MetricQuality::setMode(const GenerationMode & value) {
	data->Mode(ConvertToCDM::convert(value));
	return *this;
}

bool MetricQuality::getMode(GenerationMode & out) const {
	if (data->Mode().present()) {
		out = ConvertFromCDM::convert(data->Mode().get());
		return true;
	}
	return false;
}

GenerationMode MetricQuality::getMode() const {
	return ConvertFromCDM::convert(data->Mode().get());
}
	
bool MetricQuality::hasMode() const {
	return data->Mode().present();
}
	
MetricQuality & MetricQuality::setQi(const QualityIndicator & value) {
	data->Qi(ConvertToCDM::convert(value));
	return *this;
}

bool MetricQuality::getQi(QualityIndicator & out) const {
	if (data->Qi().present()) {
		out = ConvertFromCDM::convert(data->Qi().get());
		return true;
	}
	return false;
}

QualityIndicator MetricQuality::getQi() const {
	return ConvertFromCDM::convert(data->Qi().get());
}
	
bool MetricQuality::hasQi() const {
	return data->Qi().present();
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

