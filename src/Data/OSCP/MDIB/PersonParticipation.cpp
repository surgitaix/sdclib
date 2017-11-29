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
 *  PersonParticipation.cpp
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

#include "OSCLib/Data/OSCP/MDIB/PersonParticipation.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/InstanceIdentifier.h"
#include "OSCLib/Data/OSCP/MDIB/BaseDemographics.h"

namespace OSCLib {
namespace Data {
namespace OSCP {


PersonParticipation::PersonParticipation(
) : data(Defaults::PersonParticipationInit(
)) {}

PersonParticipation::operator CDM::PersonParticipation() const {
	return *data;
}

PersonParticipation::PersonParticipation(const CDM::PersonParticipation & object) : data(new CDM::PersonParticipation(object)) {

}

PersonParticipation::PersonParticipation(const PersonParticipation & object) : data(new CDM::PersonParticipation(*object.data)) {

}

PersonParticipation::~PersonParticipation() {

}

void PersonParticipation::copyFrom(const PersonParticipation & object) {
	data = std::shared_ptr<CDM::PersonParticipation>( new CDM::PersonParticipation(*object.data));
}

PersonParticipation & PersonParticipation:: operator=(const PersonParticipation & object) {
	copyFrom(object);
	return *this;
}


PersonParticipation & PersonParticipation::setName(const BaseDemographics & value) {
	data->Name(ConvertToCDM::convert(value));
	return *this;
}

bool PersonParticipation::getName(BaseDemographics & out) const {
	if (data->Name().present()) {
		out = ConvertFromCDM::convert(data->Name().get());
		return true;
	}
	return false;
}

BaseDemographics PersonParticipation::getName() const {
	return ConvertFromCDM::convert(data->Name().get());
}
	
bool PersonParticipation::hasName() const {
	return data->Name().present();
}
	
PersonParticipation & PersonParticipation::addIdentification(const InstanceIdentifier & value) {
	data->Identification().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<InstanceIdentifier> PersonParticipation::getIdentificationList() const {
	std::vector<InstanceIdentifier> result;
	result.reserve(data->Identification().size());
	for (const auto & value: data->Identification()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void PersonParticipation::clearIdentificationList() {
	data->Identification().clear();
}

PersonParticipation & PersonParticipation::addRole(const CodedValue & value) {
	data->Role().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<CodedValue> PersonParticipation::getRoleList() const {
	std::vector<CodedValue> result;
	result.reserve(data->Role().size());
	for (const auto & value: data->Role()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void PersonParticipation::clearRoleList() {
	data->Role().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

