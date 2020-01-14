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

#include "SDCLib/Data/SDC/MDIB/CalibrationInfo.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/CalibrationDocumentation.h"

namespace SDCLib {
namespace Data {
namespace SDC {


CalibrationInfo::CalibrationInfo(
) : data(Defaults::CalibrationInfoInit(
))
{}

CalibrationInfo::operator CDM::CalibrationInfo() const {
	return *data;
}

CalibrationInfo::CalibrationInfo(const CDM::CalibrationInfo & object)
: data(new CDM::CalibrationInfo(object))
{ }

CalibrationInfo::CalibrationInfo(const CalibrationInfo & object)
: data(std::make_shared<CDM::CalibrationInfo>(*object.data))
{ }

void CalibrationInfo::copyFrom(const CalibrationInfo & object) {
	data = std::make_shared<CDM::CalibrationInfo>(*object.data);
}

CalibrationInfo & CalibrationInfo:: operator=(const CalibrationInfo& object) {
	copyFrom(object);
	return *this;
}


CalibrationInfo & CalibrationInfo::setComponentCalibrationState(const CalibrationState & value) {
	data->setComponentCalibrationState(ConvertToCDM::convert(value));
	return *this;
}

bool CalibrationInfo::getComponentCalibrationState(CalibrationState & out) const {
	if (data->getComponentCalibrationState().present()) {
		out = ConvertFromCDM::convert(data->getComponentCalibrationState().get());
		return true;
	}
	return false;
}

CalibrationState CalibrationInfo::getComponentCalibrationState() const {
	return ConvertFromCDM::convert(data->getComponentCalibrationState().get());
}

bool CalibrationInfo::hasComponentCalibrationState() const {
	return data->getComponentCalibrationState().present();
}

CalibrationInfo & CalibrationInfo::setType(const CalibrationType & value) {
	data->setType(ConvertToCDM::convert(value));
	return *this;
}

bool CalibrationInfo::getType(CalibrationType & out) const {
	if (data->getType().present()) {
		out = ConvertFromCDM::convert(data->getType().get());
		return true;
	}
	return false;
}

CalibrationType CalibrationInfo::getType() const {
	return ConvertFromCDM::convert(data->getType().get());
}

bool CalibrationInfo::hasType() const {
	return data->getType().present();
}

CalibrationInfo & CalibrationInfo::setTime(const Timestamp & value) {
	data->setTime(ConvertToCDM::convert(value));
	return *this;
}

bool CalibrationInfo::getTime(Timestamp & out) const {
	if (data->getTime().present()) {
		out = ConvertFromCDM::convert(data->getTime().get());
		return true;
	}
	return false;
}

Timestamp CalibrationInfo::getTime() const {
	return ConvertFromCDM::convert(data->getTime().get());
}

bool CalibrationInfo::hasTime() const {
	return data->getTime().present();
}

CalibrationInfo & CalibrationInfo::addCalibrationDocumentation(const CalibrationDocumentation & value) {
	data->getCalibrationDocumentation().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<CalibrationDocumentation> CalibrationInfo::getCalibrationDocumentationList() const {
	std::vector<CalibrationDocumentation> result;
	result.reserve(data->getCalibrationDocumentation().size());
	for (const auto & value: data->getCalibrationDocumentation()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void CalibrationInfo::clearCalibrationDocumentationList() {
	data->getCalibrationDocumentation().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

