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
 *  PersonReference.cpp
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

#include "OSCLib/Data/OSCP/MDIB/PersonReference.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/BaseDemographics.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

PersonReference::PersonReference() : data(Defaults::PersonReference()) {
}

PersonReference::operator CDM::PersonReference() const {
	return *data;
}

PersonReference::PersonReference(const CDM::PersonReference & object) : data(new CDM::PersonReference(object)) {

}

PersonReference::PersonReference(const PersonReference & object) : data(new CDM::PersonReference(*object.data)) {

}

PersonReference::~PersonReference() {

}

void PersonReference::copyFrom(const PersonReference & object) {
	*data = *object.data;
}

PersonReference & PersonReference:: operator=(const PersonReference & object) {
	copyFrom(object);
	return *this;
}


PersonReference & PersonReference::addName(const BaseDemographics & value) {
	data->Name().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<BaseDemographics> PersonReference::getNames() const {
	std::vector<BaseDemographics> result;
	result.reserve(data->Name().size());
	for (const auto & value: data->Name()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void PersonReference::clearNames() {
	data->Name().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

