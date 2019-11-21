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
 *  PhysicalConnectorInfo.cpp
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

#include "SDCLib/Data/SDC/MDIB/PhysicalConnectorInfo.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/LocalizedText.h"

namespace SDCLib {
namespace Data {
namespace SDC {


PhysicalConnectorInfo::PhysicalConnectorInfo(
) : data(Defaults::PhysicalConnectorInfoInit(
))
{}

PhysicalConnectorInfo::operator CDM::PhysicalConnectorInfo() const {
	return *data;
}

PhysicalConnectorInfo::PhysicalConnectorInfo(const CDM::PhysicalConnectorInfo & object)
: data(new CDM::PhysicalConnectorInfo(object))
{ }

PhysicalConnectorInfo::PhysicalConnectorInfo(const PhysicalConnectorInfo & object)
: data(std::make_shared<CDM::PhysicalConnectorInfo>(*object.data))
{ }

void PhysicalConnectorInfo::copyFrom(const PhysicalConnectorInfo & object) {
	data = std::make_shared<CDM::PhysicalConnectorInfo>(*object.data);
}

PhysicalConnectorInfo & PhysicalConnectorInfo:: operator=(const PhysicalConnectorInfo& object) {
	copyFrom(object);
	return *this;
}


PhysicalConnectorInfo & PhysicalConnectorInfo::setNumber(const int & value) {
	data->Number(ConvertToCDM::convert(value));
	return *this;
}

bool PhysicalConnectorInfo::getNumber(int & out) const {
	if (data->Number().present()) {
		out = ConvertFromCDM::convert(data->Number().get());
		return true;
	}
	return false;
}

int PhysicalConnectorInfo::getNumber() const {
	return ConvertFromCDM::convert(data->Number().get());
}

bool PhysicalConnectorInfo::hasNumber() const {
	return data->Number().present();
}

PhysicalConnectorInfo & PhysicalConnectorInfo::addLabel(const LocalizedText & value) {
	data->Label().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<LocalizedText> PhysicalConnectorInfo::getLabelList() const {
	std::vector<LocalizedText> result;
	result.reserve(data->Label().size());
	for (const auto & value: data->Label()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void PhysicalConnectorInfo::clearLabelList() {
	data->Label().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

