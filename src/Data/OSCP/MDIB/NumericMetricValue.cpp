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
 *  NumericMetricValue.cpp
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

#include "OSCLib/Data/OSCP/MDIB/NumericMetricValue.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/MeasurementState.h"
#include "OSCLib/Data/OSCP/MDIB/Timestamp.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

NumericMetricValue::NumericMetricValue() : data(Defaults::NumericMetricValue()) {
}

NumericMetricValue::operator CDM::NumericMetricValue() const {
	return *data;
}

NumericMetricValue::NumericMetricValue(const CDM::NumericMetricValue & object) : data(new CDM::NumericMetricValue(object)) {

}

NumericMetricValue::NumericMetricValue(const NumericMetricValue & object) : data(new CDM::NumericMetricValue(*object.data)) {

}

NumericMetricValue::~NumericMetricValue() {

}

void NumericMetricValue::copyFrom(const NumericMetricValue & object) {
	*data = *object.data;
}

NumericMetricValue & NumericMetricValue:: operator=(const NumericMetricValue & object) {
	copyFrom(object);
	return *this;
}


NumericMetricValue & NumericMetricValue::setMetricQuality(const MetricQuality & value) {
	data->MetricQuality(ConvertToCDM::convert(value));
	return *this;
}


MetricQuality NumericMetricValue::getMetricQuality() const {
	return ConvertFromCDM::convert(data->MetricQuality());
}
	
NumericMetricValue & NumericMetricValue::setStart_Time(const Timestamp & value) {
	data->Start_Time(ConvertToCDM::convert(value));
	return *this;
}

bool NumericMetricValue::getStart_Time(Timestamp & out) const {
	if (data->Start_Time().present()) {
		out = ConvertFromCDM::convert(data->Start_Time().get());
		return true;
	}
	return false;
}

Timestamp NumericMetricValue::getStart_Time() const {
	return ConvertFromCDM::convert(data->Start_Time().get());
}
	
bool NumericMetricValue::hasStart_Time() const {
	return data->Start_Time().present();
}
	
NumericMetricValue & NumericMetricValue::setStop_Time(const Timestamp & value) {
	data->Stop_Time(ConvertToCDM::convert(value));
	return *this;
}

bool NumericMetricValue::getStop_Time(Timestamp & out) const {
	if (data->Stop_Time().present()) {
		out = ConvertFromCDM::convert(data->Stop_Time().get());
		return true;
	}
	return false;
}

Timestamp NumericMetricValue::getStop_Time() const {
	return ConvertFromCDM::convert(data->Stop_Time().get());
}
	
bool NumericMetricValue::hasStop_Time() const {
	return data->Stop_Time().present();
}
	
NumericMetricValue & NumericMetricValue::setDeterminationTime(const Timestamp & value) {
	data->DeterminationTime(ConvertToCDM::convert(value));
	return *this;
}

bool NumericMetricValue::getDeterminationTime(Timestamp & out) const {
	if (data->DeterminationTime().present()) {
		out = ConvertFromCDM::convert(data->DeterminationTime().get());
		return true;
	}
	return false;
}

Timestamp NumericMetricValue::getDeterminationTime() const {
	return ConvertFromCDM::convert(data->DeterminationTime().get());
}
	
bool NumericMetricValue::hasDeterminationTime() const {
	return data->DeterminationTime().present();
}
	
NumericMetricValue & NumericMetricValue::setValue(const double & value) {
	data->Value(ConvertToCDM::convert(value));
	return *this;
}

bool NumericMetricValue::getValue(double & out) const {
	if (data->Value().present()) {
		out = ConvertFromCDM::convert(data->Value().get());
		return true;
	}
	return false;
}

double NumericMetricValue::getValue() const {
	return ConvertFromCDM::convert(data->Value().get());
}
	
bool NumericMetricValue::hasValue() const {
	return data->Value().present();
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

