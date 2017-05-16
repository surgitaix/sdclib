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
 *  RealTimeSampleArrayValue.cpp
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

#include "OSCLib/Data/OSCP/MDIB/RealTimeSampleArrayValue.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/Annotation.h"
#include "OSCLib/Data/OSCP/MDIB/RTValueType.h"
#include "OSCLib/Data/OSCP/MDIB/Timestamp.h"
#include "OSCLib/Data/OSCP/MDIB/MetricQuality.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

RealTimeSampleArrayValue::RealTimeSampleArrayValue() : data(Defaults::RealTimeSampleArrayValue()) {
}

RealTimeSampleArrayValue::operator CDM::RealTimeSampleArrayValue() const {
	return *data;
}

RealTimeSampleArrayValue::RealTimeSampleArrayValue(const CDM::RealTimeSampleArrayValue & object) : data(new CDM::RealTimeSampleArrayValue(object)) {

}

RealTimeSampleArrayValue::RealTimeSampleArrayValue(const RealTimeSampleArrayValue & object) : data(new CDM::RealTimeSampleArrayValue(*object.data)) {

}

RealTimeSampleArrayValue::~RealTimeSampleArrayValue() {

}

void RealTimeSampleArrayValue::copyFrom(const RealTimeSampleArrayValue & object) {
	*data = *object.data;
}

RealTimeSampleArrayValue & RealTimeSampleArrayValue:: operator=(const RealTimeSampleArrayValue & object) {
	copyFrom(object);
	return *this;
}


RealTimeSampleArrayValue & RealTimeSampleArrayValue::setMetricQuality(const MetricQuality & value) {
	data->MetricQuality(ConvertToCDM::convert(value));
	return *this;
}


MetricQuality RealTimeSampleArrayValue::getMetricQuality() const {
	return ConvertFromCDM::convert(data->MetricQuality());
}
	
RealTimeSampleArrayValue & RealTimeSampleArrayValue::setStart_Time(const Timestamp & value) {
	data->Start_Time(ConvertToCDM::convert(value));
	return *this;
}

bool RealTimeSampleArrayValue::getStart_Time(Timestamp & out) const {
	if (data->Start_Time().present()) {
		out = ConvertFromCDM::convert(data->Start_Time().get());
		return true;
	}
	return false;
}

Timestamp RealTimeSampleArrayValue::getStart_Time() const {
	return ConvertFromCDM::convert(data->Start_Time().get());
}
	
bool RealTimeSampleArrayValue::hasStart_Time() const {
	return data->Start_Time().present();
}
	
RealTimeSampleArrayValue & RealTimeSampleArrayValue::setStop_Time(const Timestamp & value) {
	data->Stop_Time(ConvertToCDM::convert(value));
	return *this;
}

bool RealTimeSampleArrayValue::getStop_Time(Timestamp & out) const {
	if (data->Stop_Time().present()) {
		out = ConvertFromCDM::convert(data->Stop_Time().get());
		return true;
	}
	return false;
}

Timestamp RealTimeSampleArrayValue::getStop_Time() const {
	return ConvertFromCDM::convert(data->Stop_Time().get());
}
	
bool RealTimeSampleArrayValue::hasStop_Time() const {
	return data->Stop_Time().present();
}
	
RealTimeSampleArrayValue & RealTimeSampleArrayValue::setDeterminationTime(const Timestamp & value) {
	data->DeterminationTime(ConvertToCDM::convert(value));
	return *this;
}

bool RealTimeSampleArrayValue::getDeterminationTime(Timestamp & out) const {
	if (data->DeterminationTime().present()) {
		out = ConvertFromCDM::convert(data->DeterminationTime().get());
		return true;
	}
	return false;
}

Timestamp RealTimeSampleArrayValue::getDeterminationTime() const {
	return ConvertFromCDM::convert(data->DeterminationTime().get());
}
	
bool RealTimeSampleArrayValue::hasDeterminationTime() const {
	return data->DeterminationTime().present();
}
	
RealTimeSampleArrayValue & RealTimeSampleArrayValue::setSamples(const RTValueType & value) {
	data->Samples(ConvertToCDM::convert(value));
	return *this;
}

bool RealTimeSampleArrayValue::getSamples(RTValueType & out) const {
	if (data->Samples().present()) {
		out = ConvertFromCDM::convert(data->Samples().get());
		return true;
	}
	return false;
}

RTValueType RealTimeSampleArrayValue::getSamples() const {
	return ConvertFromCDM::convert(data->Samples().get());
}
	
bool RealTimeSampleArrayValue::hasSamples() const {
	return data->Samples().present();
}
	
RealTimeSampleArrayValue & RealTimeSampleArrayValue::addAnnotation(const Annotation & value) {
	data->Annotation().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<Annotation> RealTimeSampleArrayValue::getAnnotations() const {
	std::vector<Annotation> result;
	result.reserve(data->Annotation().size());
	for (const auto & value: data->Annotation()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void RealTimeSampleArrayValue::clearAnnotations() {
	data->Annotation().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

