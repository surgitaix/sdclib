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
 *  Author: besting, buerger, roehser
 */
 
/**
 * THIS FILE IS GENERATED AUTOMATICALLY! DO NOT MODIFY!
 *
 * YOUR CHANGES WILL BE OVERWRITTEN!
 * 
 * USE THE DEFINITION FILES IN THE FOLDER "codegenerator" INSTEAD!
 */

#include "OSCLib/Data/SDC/MDIB/StringMetricValue.h"
#include "OSCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/SDC/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/SDC/MDIB/MetricQuality.h"
#include "OSCLib/Data/SDC/MDIB/Annotation.h"

namespace SDCLib {
namespace Data {
namespace SDC {


StringMetricValue::StringMetricValue(
		MetricQuality metricquality
) : data(Defaults::StringMetricValueInit(
		metricquality
)) {}

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
	data = std::shared_ptr<CDM::StringMetricValue>( new CDM::StringMetricValue(*object.data));
}

StringMetricValue & StringMetricValue:: operator=(const StringMetricValue & object) {
	copyFrom(object);
	return *this;
}


StringMetricValue & StringMetricValue::setMetricQuality(const MetricQuality & value) {
	data->MetricQuality(ConvertToCDM::convert(value));
	return *this;
}


MetricQuality StringMetricValue::getMetricQuality() const {
	return ConvertFromCDM::convert(data->MetricQuality());
}
	
StringMetricValue & StringMetricValue::setStartTime(const Timestamp & value) {
	data->StartTime(ConvertToCDM::convert(value));
	return *this;
}

bool StringMetricValue::getStartTime(Timestamp & out) const {
	if (data->StartTime().present()) {
		out = ConvertFromCDM::convert(data->StartTime().get());
		return true;
	}
	return false;
}

Timestamp StringMetricValue::getStartTime() const {
	return ConvertFromCDM::convert(data->StartTime().get());
}
	
bool StringMetricValue::hasStartTime() const {
	return data->StartTime().present();
}
	
StringMetricValue & StringMetricValue::setStopTime(const Timestamp & value) {
	data->StopTime(ConvertToCDM::convert(value));
	return *this;
}

bool StringMetricValue::getStopTime(Timestamp & out) const {
	if (data->StopTime().present()) {
		out = ConvertFromCDM::convert(data->StopTime().get());
		return true;
	}
	return false;
}

Timestamp StringMetricValue::getStopTime() const {
	return ConvertFromCDM::convert(data->StopTime().get());
}
	
bool StringMetricValue::hasStopTime() const {
	return data->StopTime().present();
}
	
StringMetricValue & StringMetricValue::setDeterminationTime(const Timestamp & value) {
	data->DeterminationTime(ConvertToCDM::convert(value));
	return *this;
}

bool StringMetricValue::getDeterminationTime(Timestamp & out) const {
	if (data->DeterminationTime().present()) {
		out = ConvertFromCDM::convert(data->DeterminationTime().get());
		return true;
	}
	return false;
}

Timestamp StringMetricValue::getDeterminationTime() const {
	return ConvertFromCDM::convert(data->DeterminationTime().get());
}
	
bool StringMetricValue::hasDeterminationTime() const {
	return data->DeterminationTime().present();
}
	
StringMetricValue & StringMetricValue::addAnnotation(const Annotation & value) {
	data->Annotation().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<Annotation> StringMetricValue::getAnnotationList() const {
	std::vector<Annotation> result;
	result.reserve(data->Annotation().size());
	for (const auto & value: data->Annotation()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void StringMetricValue::clearAnnotationList() {
	data->Annotation().clear();
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
	

} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

