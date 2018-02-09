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
 *  SampleArrayValue.cpp
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

#include "OSCLib/Data/OSCP/MDIB/SampleArrayValue.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/ApplyAnnotation.h"
#include "OSCLib/Data/OSCP/MDIB/MetricQuality.h"
#include "OSCLib/Data/OSCP/MDIB/Annotation.h"

namespace OSCLib {
namespace Data {
namespace SDC {


SampleArrayValue::SampleArrayValue(
		MetricQuality metricquality
) : data(Defaults::SampleArrayValueInit(
		metricquality
)) {}

SampleArrayValue::operator CDM::SampleArrayValue() const {
	return *data;
}

SampleArrayValue::SampleArrayValue(const CDM::SampleArrayValue & object) : data(new CDM::SampleArrayValue(object)) {

}

SampleArrayValue::SampleArrayValue(const SampleArrayValue & object) : data(new CDM::SampleArrayValue(*object.data)) {

}

SampleArrayValue::~SampleArrayValue() {

}

void SampleArrayValue::copyFrom(const SampleArrayValue & object) {
	data = std::shared_ptr<CDM::SampleArrayValue>( new CDM::SampleArrayValue(*object.data));
}

SampleArrayValue & SampleArrayValue:: operator=(const SampleArrayValue & object) {
	copyFrom(object);
	return *this;
}


SampleArrayValue & SampleArrayValue::setMetricQuality(const MetricQuality & value) {
	data->MetricQuality(ConvertToCDM::convert(value));
	return *this;
}


MetricQuality SampleArrayValue::getMetricQuality() const {
	return ConvertFromCDM::convert(data->MetricQuality());
}
	
SampleArrayValue & SampleArrayValue::setStartTime(const Timestamp & value) {
	data->StartTime(ConvertToCDM::convert(value));
	return *this;
}

bool SampleArrayValue::getStartTime(Timestamp & out) const {
	if (data->StartTime().present()) {
		out = ConvertFromCDM::convert(data->StartTime().get());
		return true;
	}
	return false;
}

Timestamp SampleArrayValue::getStartTime() const {
	return ConvertFromCDM::convert(data->StartTime().get());
}
	
bool SampleArrayValue::hasStartTime() const {
	return data->StartTime().present();
}
	
SampleArrayValue & SampleArrayValue::setStopTime(const Timestamp & value) {
	data->StopTime(ConvertToCDM::convert(value));
	return *this;
}

bool SampleArrayValue::getStopTime(Timestamp & out) const {
	if (data->StopTime().present()) {
		out = ConvertFromCDM::convert(data->StopTime().get());
		return true;
	}
	return false;
}

Timestamp SampleArrayValue::getStopTime() const {
	return ConvertFromCDM::convert(data->StopTime().get());
}
	
bool SampleArrayValue::hasStopTime() const {
	return data->StopTime().present();
}
	
SampleArrayValue & SampleArrayValue::setDeterminationTime(const Timestamp & value) {
	data->DeterminationTime(ConvertToCDM::convert(value));
	return *this;
}

bool SampleArrayValue::getDeterminationTime(Timestamp & out) const {
	if (data->DeterminationTime().present()) {
		out = ConvertFromCDM::convert(data->DeterminationTime().get());
		return true;
	}
	return false;
}

Timestamp SampleArrayValue::getDeterminationTime() const {
	return ConvertFromCDM::convert(data->DeterminationTime().get());
}
	
bool SampleArrayValue::hasDeterminationTime() const {
	return data->DeterminationTime().present();
}
	
SampleArrayValue & SampleArrayValue::addAnnotation(const Annotation & value) {
	data->Annotation().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<Annotation> SampleArrayValue::getAnnotationList() const {
	std::vector<Annotation> result;
	result.reserve(data->Annotation().size());
	for (const auto & value: data->Annotation()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void SampleArrayValue::clearAnnotationList() {
	data->Annotation().clear();
}

SampleArrayValue & SampleArrayValue::setSamples(const RealTimeValueType & value) {
	data->Samples(ConvertToCDM::convert(value));
	return *this;
}

bool SampleArrayValue::getSamples(RealTimeValueType & out) const {
	if (data->Samples().present()) {
		out = ConvertFromCDM::convert(data->Samples().get());
		return true;
	}
	return false;
}

RealTimeValueType SampleArrayValue::getSamples() const {
	return ConvertFromCDM::convert(data->Samples().get());
}
	
bool SampleArrayValue::hasSamples() const {
	return data->Samples().present();
}
	
SampleArrayValue & SampleArrayValue::addApplyAnnotation(const ApplyAnnotation & value) {
	data->ApplyAnnotation().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<ApplyAnnotation> SampleArrayValue::getApplyAnnotationList() const {
	std::vector<ApplyAnnotation> result;
	result.reserve(data->ApplyAnnotation().size());
	for (const auto & value: data->ApplyAnnotation()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void SampleArrayValue::clearApplyAnnotationList() {
	data->ApplyAnnotation().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace OSCLib */

