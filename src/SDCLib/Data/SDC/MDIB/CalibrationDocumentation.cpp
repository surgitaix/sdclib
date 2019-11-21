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
 *  Author: besting, buerger, roehser
 */

/**
 * THIS FILE IS GENERATED AUTOMATICALLY! DO NOT MODIFY!
 *
 * YOUR CHANGES WILL BE OVERWRITTEN!
 *
 * USE THE DEFINITION FILES IN THE FOLDER "codegenerator" INSTEAD!
 */

#include "SDCLib/Data/SDC/MDIB/CalibrationDocumentation.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/LocalizedText.h"
#include "SDCLib/Data/SDC/MDIB/CalibrationResult.h"

namespace SDCLib {
namespace Data {
namespace SDC {


CalibrationDocumentation::CalibrationDocumentation(
) : data(Defaults::CalibrationDocumentationInit(
))
{}

CalibrationDocumentation::operator CDM::CalibrationDocumentation() const {
	return *data;
}

CalibrationDocumentation::CalibrationDocumentation(const CDM::CalibrationDocumentation & object)
: data(new CDM::CalibrationDocumentation(object))
{ }

CalibrationDocumentation::CalibrationDocumentation(const CalibrationDocumentation & object)
: data(std::make_shared<CDM::CalibrationDocumentation>(*object.data))
{ }

void CalibrationDocumentation::copyFrom(const CalibrationDocumentation & object) {
	data = std::make_shared<CDM::CalibrationDocumentation>(*object.data);
}

CalibrationDocumentation & CalibrationDocumentation:: operator=(const CalibrationDocumentation& object) {
	copyFrom(object);
	return *this;
}


CalibrationDocumentation & CalibrationDocumentation::addDocumentation(const LocalizedText & value) {
	data->Documentation().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<LocalizedText> CalibrationDocumentation::getDocumentationList() const {
	std::vector<LocalizedText> result;
	result.reserve(data->Documentation().size());
	for (const auto & value: data->Documentation()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void CalibrationDocumentation::clearDocumentationList() {
	data->Documentation().clear();
}

CalibrationDocumentation & CalibrationDocumentation::addCalibrationResult(const CalibrationResult & value) {
	data->CalibrationResult().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<CalibrationResult> CalibrationDocumentation::getCalibrationResultList() const {
	std::vector<CalibrationResult> result;
	result.reserve(data->CalibrationResult().size());
	for (const auto & value: data->CalibrationResult()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void CalibrationDocumentation::clearCalibrationResultList() {
	data->CalibrationResult().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

