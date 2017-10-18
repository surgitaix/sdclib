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
 *  CalibrationDocumentation.cpp
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

#include "OSCLib/Data/OSCP/MDIB/CalibrationDocumentation.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/LocalizedText.h"
#include "OSCLib/Data/OSCP/MDIB/CalibrationResult.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

CalibrationDocumentation::CalibrationDocumentation() : data(Defaults::CalibrationDocumentation()) {
}

CalibrationDocumentation::operator CDM::CalibrationDocumentation() const {
	return *data;
}

CalibrationDocumentation::CalibrationDocumentation(const CDM::CalibrationDocumentation & object) : data(new CDM::CalibrationDocumentation(object)) {

}

CalibrationDocumentation::CalibrationDocumentation(const CalibrationDocumentation & object) : data(new CDM::CalibrationDocumentation(*object.data)) {

}

CalibrationDocumentation::~CalibrationDocumentation() {

}

void CalibrationDocumentation::copyFrom(const CalibrationDocumentation & object) {
	*data = *object.data;
}

CalibrationDocumentation & CalibrationDocumentation:: operator=(const CalibrationDocumentation & object) {
	copyFrom(object);
	return *this;
}


CalibrationDocumentation & CalibrationDocumentation::addDocumentation(const LocalizedText & value) {
	data->Documentation().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<LocalizedText> CalibrationDocumentation::getDocumentationLists() const {
	std::vector<LocalizedText> result;
	result.reserve(data->Documentation().size());
	for (const auto & value: data->Documentation()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void CalibrationDocumentation::clearDocumentationLists() {
	data->Documentation().clear();
}

CalibrationDocumentation & CalibrationDocumentation::addCalibrationResult(const CalibrationResult & value) {
	data->CalibrationResult().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<CalibrationResult> CalibrationDocumentation::getCalibrationResultLists() const {
	std::vector<CalibrationResult> result;
	result.reserve(data->CalibrationResult().size());
	for (const auto & value: data->CalibrationResult()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void CalibrationDocumentation::clearCalibrationResultLists() {
	data->CalibrationResult().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

