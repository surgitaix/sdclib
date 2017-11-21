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
 *  CalibrationInfo.cpp
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

#include "OSCLib/Data/OSCP/MDIB/CalibrationInfo.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"


namespace OSCLib {
namespace Data {
namespace OSCP {


CalibrationInfo::CalibrationInfo(
) : data(Defaults::CalibrationInfoInit(
)) {}

CalibrationInfo::operator CDM::CalibrationInfo() const {
	return *data;
}

CalibrationInfo::CalibrationInfo(const CDM::CalibrationInfo & object) : data(new CDM::CalibrationInfo(object)) {

}

CalibrationInfo::CalibrationInfo(const CalibrationInfo & object) : data(new CDM::CalibrationInfo(*object.data)) {

}

CalibrationInfo::~CalibrationInfo() {

}

void CalibrationInfo::copyFrom(const CalibrationInfo & object) {
	*data = *object.data;
}

CalibrationInfo & CalibrationInfo:: operator=(const CalibrationInfo & object) {
	copyFrom(object);
	return *this;
}


CalibrationInfo & CalibrationInfo::setComponentCalibrationState(const CalibrationState & value) {
	data->ComponentCalibrationState(ConvertToCDM::convert(value));
	return *this;
}

bool CalibrationInfo::getComponentCalibrationState(CalibrationState & out) const {
	if (data->ComponentCalibrationState().present()) {
		out = ConvertFromCDM::convert(data->ComponentCalibrationState().get());
		return true;
	}
	return false;
}

CalibrationState CalibrationInfo::getComponentCalibrationState() const {
	return ConvertFromCDM::convert(data->ComponentCalibrationState().get());
}
	
bool CalibrationInfo::hasComponentCalibrationState() const {
	return data->ComponentCalibrationState().present();
}
	
CalibrationInfo & CalibrationInfo::setType(const CalibrationType & value) {
	data->Type(ConvertToCDM::convert(value));
	return *this;
}

bool CalibrationInfo::getType(CalibrationType & out) const {
	if (data->Type().present()) {
		out = ConvertFromCDM::convert(data->Type().get());
		return true;
	}
	return false;
}

CalibrationType CalibrationInfo::getType() const {
	return ConvertFromCDM::convert(data->Type().get());
}
	
bool CalibrationInfo::hasType() const {
	return data->Type().present();
}
	
CalibrationInfo & CalibrationInfo::setTime(const Timestamp & value) {
	data->Time(ConvertToCDM::convert(value));
	return *this;
}

bool CalibrationInfo::getTime(Timestamp & out) const {
	if (data->Time().present()) {
		out = ConvertFromCDM::convert(data->Time().get());
		return true;
	}
	return false;
}

Timestamp CalibrationInfo::getTime() const {
	return ConvertFromCDM::convert(data->Time().get());
}
	
bool CalibrationInfo::hasTime() const {
	return data->Time().present();
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

