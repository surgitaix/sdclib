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
 *  Author: besting, roehser
 */
 
/**
 * THIS FILE IS GENERATED AUTOMATICALLY! DO NOT MODIFY!
 *
 * YOUR CHANGES WILL BE OVERWRITTEN!
 * 
 * USE THE DEFINITION FILES IN THE FOLDER "codegenerator" INSTEAD!
 */

#include "OSCLib/Data/OSCP/MDIB/SampleArrayValue.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/ApplyAnnotation.h"
#include "OSCLib/Data/OSCP/MDIB/RealTimeValueType.h"
#include "OSCLib/Data/OSCP/MDIB/Timestamp.h"
#include "OSCLib/Data/OSCP/MDIB/MetricQuality.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

SampleArrayValue::SampleArrayValue() : data(Defaults::SampleArrayValue()) {
}

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
	*data = *object.data;
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
	
SampleArrayValue & SampleArrayValue::setStart_Time(const Timestamp & value) {
	data->Start_Time(ConvertToCDM::convert(value));
	return *this;
}

bool SampleArrayValue::getStart_Time(Timestamp & out) const {
	if (data->Start_Time().present()) {
		out = ConvertFromCDM::convert(data->Start_Time().get());
		return true;
	}
	return false;
}

Timestamp SampleArrayValue::getStart_Time() const {
	return ConvertFromCDM::convert(data->Start_Time().get());
}
	
bool SampleArrayValue::hasStart_Time() const {
	return data->Start_Time().present();
}
	
SampleArrayValue & SampleArrayValue::setStop_Time(const Timestamp & value) {
	data->Stop_Time(ConvertToCDM::convert(value));
	return *this;
}

bool SampleArrayValue::getStop_Time(Timestamp & out) const {
	if (data->Stop_Time().present()) {
		out = ConvertFromCDM::convert(data->Stop_Time().get());
		return true;
	}
	return false;
}

Timestamp SampleArrayValue::getStop_Time() const {
	return ConvertFromCDM::convert(data->Stop_Time().get());
}
	
bool SampleArrayValue::hasStop_Time() const {
	return data->Stop_Time().present();
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

std::vector<ApplyAnnotation> SampleArrayValue::getApplyAnnotations() const {
	std::vector<ApplyAnnotation> result;
	result.reserve(data->ApplyAnnotation().size());
	for (const auto & value: data->ApplyAnnotation()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void SampleArrayValue::clearApplyAnnotations() {
	data->ApplyAnnotation().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

