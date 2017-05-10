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
 *  MeasurementState.cpp
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

#include "OSCLib/Data/OSCP/MDIB/MeasurementState.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"


namespace OSCLib {
namespace Data {
namespace OSCP {

MeasurementState::MeasurementState() : data(Defaults::MeasurementState()) {
}

MeasurementState::operator CDM::MeasurementState() const {
	return *data;
}

MeasurementState::MeasurementState(const CDM::MeasurementState & object) : data(new CDM::MeasurementState(object)) {

}

MeasurementState::MeasurementState(const MeasurementState & object) : data(new CDM::MeasurementState(*object.data)) {

}

MeasurementState::~MeasurementState() {

}

void MeasurementState::copyFrom(const MeasurementState & object) {
	*data = *object.data;
}

MeasurementState & MeasurementState:: operator=(const MeasurementState & object) {
	copyFrom(object);
	return *this;
}


MeasurementState & MeasurementState::setValidity(const MetricMeasurementValidity & value) {
	data->Validity(ConvertToCDM::convert(value));
	return *this;
}


MetricMeasurementValidity MeasurementState::getValidity() const {
	return ConvertFromCDM::convert(data->Validity());
}
	
MeasurementState & MeasurementState::setMode(const GenerationMode & value) {
	data->Mode(ConvertToCDM::convert(value));
	return *this;
}

bool MeasurementState::getMode(GenerationMode & out) const {
	if (data->Mode().present()) {
		out = ConvertFromCDM::convert(data->Mode().get());
		return true;
	}
	return false;
}

GenerationMode MeasurementState::getMode() const {
	return ConvertFromCDM::convert(data->Mode().get());
}
	
bool MeasurementState::hasMode() const {
	return data->Mode().present();
}
	
MeasurementState & MeasurementState::setQi(const double & value) {
	data->Qi(ConvertToCDM::convert(value));
	return *this;
}

bool MeasurementState::getQi(double & out) const {
	if (data->Qi().present()) {
		out = ConvertFromCDM::convert(data->Qi().get());
		return true;
	}
	return false;
}

double MeasurementState::getQi() const {
	return ConvertFromCDM::convert(data->Qi().get());
}
	
bool MeasurementState::hasQi() const {
	return data->Qi().present();
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

