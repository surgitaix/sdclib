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
 *  Author: besting, buerger, roehser
 */

/**
 * THIS FILE IS GENERATED AUTOMATICALLY! DO NOT MODIFY!
 *
 * YOUR CHANGES WILL BE OVERWRITTEN!
 *
 * USE THE DEFINITION FILES IN THE FOLDER "codegenerator" INSTEAD!
 */

#include "SDCLib/Data/SDC/MDIB/PersonReference.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/InstanceIdentifier.h"
#include "SDCLib/Data/SDC/MDIB/BaseDemographics.h"

namespace SDCLib {
namespace Data {
namespace SDC {


PersonReference::PersonReference(
) : data(Defaults::PersonReferenceInit(
))
{}

PersonReference::operator CDM::PersonReference() const {
	return *data;
}

PersonReference::PersonReference(const CDM::PersonReference & object)
: data(new CDM::PersonReference(object))
{ }

PersonReference::PersonReference(const PersonReference & object)
: data(std::make_shared<CDM::PersonReference>(*object.data))
{ }

void PersonReference::copyFrom(const PersonReference & object) {
	data = std::make_shared<CDM::PersonReference>(*object.data);
}

PersonReference & PersonReference:: operator=(const PersonReference& object) {
	copyFrom(object);
	return *this;
}


PersonReference & PersonReference::setName(const BaseDemographics & value) {
	data->Name(ConvertToCDM::convert(value));
	return *this;
}

bool PersonReference::getName(BaseDemographics & out) const {
	if (data->Name().present()) {
		out = ConvertFromCDM::convert(data->Name().get());
		return true;
	}
	return false;
}

BaseDemographics PersonReference::getName() const {
	return ConvertFromCDM::convert(data->Name().get());
}

bool PersonReference::hasName() const {
	return data->Name().present();
}

PersonReference & PersonReference::addIdentification(const InstanceIdentifier & value) {
	data->Identification().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<InstanceIdentifier> PersonReference::getIdentificationList() const {
	std::vector<InstanceIdentifier> result;
	result.reserve(data->Identification().size());
	for (const auto & value: data->Identification()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void PersonReference::clearIdentificationList() {
	data->Identification().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

