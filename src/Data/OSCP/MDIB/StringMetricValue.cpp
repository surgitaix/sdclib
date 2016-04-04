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
 *  StringMetricValue.cpp
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

#include "OSCLib/Data/OSCP/MDIB/StringMetricValue.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/MeasurementState.h"
#include "OSCLib/Data/OSCP/MDIB/Timestamp.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

StringMetricValue::StringMetricValue() : data(Defaults::StringMetricValue()) {
}

StringMetricValue::operator CDM::StringMetricValue() const {
	return *data;
}

StringMetricValue::StringMetricValue(const CDM::StringMetricValue & object) : data(new CDM::StringMetricValue(object)) {

}

StringMetricValue::StringMetricValue(const StringMetricValue & object) : data(new CDM::StringMetricValue(*object.data)) {

}

StringMetricValue::~StringMetricValue() {

}

void StringMetricValue::copyFrom(const StringMetricValue & object) {
	*data = *object.data;
}

StringMetricValue & StringMetricValue:: operator=(const StringMetricValue & object) {
	copyFrom(object);
	return *this;
}


StringMetricValue & StringMetricValue::setMeasurementState(const MeasurementState & value) {
	data->MeasurementState(ConvertToCDM::convert(value));
	return *this;
}


MeasurementState StringMetricValue::getMeasurementState() const {
	return ConvertFromCDM::convert(data->MeasurementState());
}
	
StringMetricValue & StringMetricValue::setStart_Time(const Timestamp & value) {
	data->Start_Time(ConvertToCDM::convert(value));
	return *this;
}

bool StringMetricValue::getStart_Time(Timestamp & out) const {
	if (data->Start_Time().present()) {
		out = ConvertFromCDM::convert(data->Start_Time().get());
		return true;
	}
	return false;
}

Timestamp StringMetricValue::getStart_Time() const {
	return ConvertFromCDM::convert(data->Start_Time().get());
}
	
bool StringMetricValue::hasStart_Time() const {
	return data->Start_Time().present();
}
	
StringMetricValue & StringMetricValue::setStop_Time(const Timestamp & value) {
	data->Stop_Time(ConvertToCDM::convert(value));
	return *this;
}

bool StringMetricValue::getStop_Time(Timestamp & out) const {
	if (data->Stop_Time().present()) {
		out = ConvertFromCDM::convert(data->Stop_Time().get());
		return true;
	}
	return false;
}

Timestamp StringMetricValue::getStop_Time() const {
	return ConvertFromCDM::convert(data->Stop_Time().get());
}
	
bool StringMetricValue::hasStop_Time() const {
	return data->Stop_Time().present();
}
	
StringMetricValue & StringMetricValue::setObservationTime(const Timestamp & value) {
	data->ObservationTime(ConvertToCDM::convert(value));
	return *this;
}

bool StringMetricValue::getObservationTime(Timestamp & out) const {
	if (data->ObservationTime().present()) {
		out = ConvertFromCDM::convert(data->ObservationTime().get());
		return true;
	}
	return false;
}

Timestamp StringMetricValue::getObservationTime() const {
	return ConvertFromCDM::convert(data->ObservationTime().get());
}
	
bool StringMetricValue::hasObservationTime() const {
	return data->ObservationTime().present();
}
	
StringMetricValue & StringMetricValue::setValue(const std::string & value) {
	data->Value(ConvertToCDM::convert(value));
	return *this;
}

bool StringMetricValue::getValue(std::string & out) const {
	if (data->Value().present()) {
		out = ConvertFromCDM::convert(data->Value().get());
		return true;
	}
	return false;
}

std::string StringMetricValue::getValue() const {
	return ConvertFromCDM::convert(data->Value().get());
}
	
bool StringMetricValue::hasValue() const {
	return data->Value().present();
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

