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
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"

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


SampleArrayValue & SampleArrayValue::setType(const CodedValue & value) {
	data->Type(ConvertToCDM::convert(value));
	return *this;
}


CodedValue SampleArrayValue::getType() const {
	return ConvertFromCDM::convert(data->Type());
}
	
SampleArrayValue & SampleArrayValue::setValidity(const MeasurementValidity & value) {
	data->Validity(ConvertToCDM::convert(value));
	return *this;
}


MeasurementValidity SampleArrayValue::getValidity() const {
	return ConvertFromCDM::convert(data->Validity());
}
	
SampleArrayValue & SampleArrayValue::setMode(const GenerationMode & value) {
	data->Mode(ConvertToCDM::convert(value));
	return *this;
}


GenerationMode SampleArrayValue::getMode() const {
	return ConvertFromCDM::convert(data->Mode());
}
	
SampleArrayValue & SampleArrayValue::setQi(const QualityIndicator & value) {
	data->Qi(ConvertToCDM::convert(value));
	return *this;
}


QualityIndicator SampleArrayValue::getQi() const {
	return ConvertFromCDM::convert(data->Qi());
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
	
SampleArrayValue & SampleArrayValue::setAnnotationIndex(const unsigned int & value) {
	data->AnnotationIndex(ConvertToCDM::convert(value));
	return *this;
}


unsigned int SampleArrayValue::getAnnotationIndex() const {
	return ConvertFromCDM::convert(data->AnnotationIndex());
}
	
SampleArrayValue & SampleArrayValue::setSampleIndex(const unsigned int & value) {
	data->SampleIndex(ConvertToCDM::convert(value));
	return *this;
}


unsigned int SampleArrayValue::getSampleIndex() const {
	return ConvertFromCDM::convert(data->SampleIndex());
}
	
SampleArrayValue & SampleArrayValue::setSamples(const RealTimeValueType & value) {
	data->Samples(ConvertToCDM::convert(value));
	return *this;
}


RealTimeValueType SampleArrayValue::getSamples() const {
	return ConvertFromCDM::convert(data->Samples());
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

