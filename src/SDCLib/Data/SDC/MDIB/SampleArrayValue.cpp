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

#include "SDCLib/Data/SDC/MDIB/SampleArrayValue.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/ApplyAnnotation.h"
#include "SDCLib/Data/SDC/MDIB/MetricQuality.h"
#include "SDCLib/Data/SDC/MDIB/Annotation.h"

namespace SDCLib {
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
	data->setMetricQuality(ConvertToCDM::convert(value));
	return *this;
}


MetricQuality SampleArrayValue::getMetricQuality() const {
	return ConvertFromCDM::convert(data->getMetricQuality());
}

SampleArrayValue & SampleArrayValue::setStartTime(const Timestamp & value) {
	data->setStartTime(ConvertToCDM::convert(value));
	return *this;
}

bool SampleArrayValue::getStartTime(Timestamp & out) const {
	if (data->getStartTime().present()) {
		out = ConvertFromCDM::convert(data->getStartTime().get());
		return true;
	}
	return false;
}

Timestamp SampleArrayValue::getStartTime() const {
	return ConvertFromCDM::convert(data->getStartTime().get());
}

bool SampleArrayValue::hasStartTime() const {
	return data->getStartTime().present();
}

SampleArrayValue & SampleArrayValue::setStopTime(const Timestamp & value) {
	data->setStopTime(ConvertToCDM::convert(value));
	return *this;
}

bool SampleArrayValue::getStopTime(Timestamp & out) const {
	if (data->getStopTime().present()) {
		out = ConvertFromCDM::convert(data->getStopTime().get());
		return true;
	}
	return false;
}

Timestamp SampleArrayValue::getStopTime() const {
	return ConvertFromCDM::convert(data->getStopTime().get());
}

bool SampleArrayValue::hasStopTime() const {
	return data->getStopTime().present();
}

SampleArrayValue & SampleArrayValue::setDeterminationTime(const Timestamp & value) {
	data->setDeterminationTime(ConvertToCDM::convert(value));
	return *this;
}

bool SampleArrayValue::getDeterminationTime(Timestamp & out) const {
	if (data->getDeterminationTime().present()) {
		out = ConvertFromCDM::convert(data->getDeterminationTime().get());
		return true;
	}
	return false;
}

Timestamp SampleArrayValue::getDeterminationTime() const {
	return ConvertFromCDM::convert(data->getDeterminationTime().get());
}

bool SampleArrayValue::hasDeterminationTime() const {
	return data->getDeterminationTime().present();
}

SampleArrayValue & SampleArrayValue::addAnnotation(const Annotation & value) {
	data->getAnnotation().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<Annotation> SampleArrayValue::getAnnotationList() const {
	std::vector<Annotation> result;
	result.reserve(data->getAnnotation().size());
	for (const auto & value: data->getAnnotation()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void SampleArrayValue::clearAnnotationList() {
	data->getAnnotation().clear();
}

SampleArrayValue & SampleArrayValue::setSamples(const RealTimeValueType & value) {
	data->setSamples(ConvertToCDM::convert(value));
	return *this;
}

bool SampleArrayValue::getSamples(RealTimeValueType & out) const {
	if (data->getSamples().present()) {
		out = ConvertFromCDM::convert(data->getSamples().get());
		return true;
	}
	return false;
}

RealTimeValueType SampleArrayValue::getSamples() const {
	return ConvertFromCDM::convert(data->getSamples().get());
}

bool SampleArrayValue::hasSamples() const {
	return data->getSamples().present();
}

SampleArrayValue & SampleArrayValue::addApplyAnnotation(const ApplyAnnotation & value) {
	data->getApplyAnnotation().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<ApplyAnnotation> SampleArrayValue::getApplyAnnotationList() const {
	std::vector<ApplyAnnotation> result;
	result.reserve(data->getApplyAnnotation().size());
	for (const auto & value: data->getApplyAnnotation()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void SampleArrayValue::clearApplyAnnotationList() {
	data->getApplyAnnotation().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

