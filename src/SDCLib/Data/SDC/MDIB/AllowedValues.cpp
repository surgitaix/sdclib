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
 *  AllowedValues.cpp
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

#include "SDCLib/Data/SDC/MDIB/AllowedValues.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "osdm.hxx"


namespace SDCLib {
namespace Data {
namespace SDC {


AllowedValues::AllowedValues(
) : data(Defaults::AllowedValuesInit(
)) {}

AllowedValues::operator CDM::AllowedValues() const {
	return *data;
}

AllowedValues::AllowedValues(const CDM::AllowedValues & object) : data(new CDM::AllowedValues(object)) {

}

AllowedValues::AllowedValues(const AllowedValues & object) : data(new CDM::AllowedValues(*object.data)) {

}

AllowedValues::~AllowedValues() {

}

void AllowedValues::copyFrom(const AllowedValues & object) {
	data = std::shared_ptr<CDM::AllowedValues>( new CDM::AllowedValues(*object.data));
}

AllowedValues & AllowedValues:: operator=(const AllowedValues & object) {
	copyFrom(object);
	return *this;
}


AllowedValues & AllowedValues::addValue(const std::string & value) {
	data->Value().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<std::string> AllowedValues::getValueList() const {
	std::vector<std::string> result;
	result.reserve(data->Value().size());
	for (const auto & value: data->Value()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void AllowedValues::clearValueList() {
	data->Value().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

