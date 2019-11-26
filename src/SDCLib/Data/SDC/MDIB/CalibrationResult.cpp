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
 *  CalibrationResult.cpp
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

#include "SDCLib/Data/SDC/MDIB/CalibrationResult.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/CodedValue.h"
#include "SDCLib/Data/SDC/MDIB/Measurement.h"

namespace SDCLib {
namespace Data {
namespace SDC {


CalibrationResult::CalibrationResult(
		CodedValue code
		,
		Measurement value
) : data(Defaults::CalibrationResultInit(
		code
		,
		value
))
{}

CalibrationResult::operator CDM::CalibrationResult() const {
	return *data;
}

CalibrationResult::CalibrationResult(const CDM::CalibrationResult & object)
: data(new CDM::CalibrationResult(object))
{ }

CalibrationResult::CalibrationResult(const CalibrationResult & object)
: data(std::make_shared<CDM::CalibrationResult>(*object.data))
{ }

void CalibrationResult::copyFrom(const CalibrationResult & object) {
	data = std::make_shared<CDM::CalibrationResult>(*object.data);
}

CalibrationResult & CalibrationResult:: operator=(const CalibrationResult& object) {
	copyFrom(object);
	return *this;
}


CalibrationResult & CalibrationResult::setCode(const CodedValue & value) {
	data->setCode(ConvertToCDM::convert(value));
	return *this;
}


CodedValue CalibrationResult::getCode() const {
	return ConvertFromCDM::convert(data->getCode());
}

CalibrationResult & CalibrationResult::setValue(const Measurement & value) {
	data->setValue(ConvertToCDM::convert(value));
	return *this;
}


Measurement CalibrationResult::getValue() const {
	return ConvertFromCDM::convert(data->getValue());
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

