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
 *  BaseDemographics.cpp
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

#include "OSCLib/Data/OSCP/MDIB/BaseDemographics.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"


namespace OSCLib {
namespace Data {
namespace OSCP {

BaseDemographics::BaseDemographics() : data(Defaults::BaseDemographics()) {
}

BaseDemographics::operator CDM::BaseDemographics() const {
	return *data;
}

BaseDemographics::BaseDemographics(const CDM::BaseDemographics & object) : data(new CDM::BaseDemographics(object)) {

}

BaseDemographics::BaseDemographics(const BaseDemographics & object) : data(new CDM::BaseDemographics(*object.data)) {

}

BaseDemographics::~BaseDemographics() {

}

void BaseDemographics::copyFrom(const BaseDemographics & object) {
	*data = *object.data;
}

BaseDemographics & BaseDemographics:: operator=(const BaseDemographics & object) {
	copyFrom(object);
	return *this;
}


BaseDemographics & BaseDemographics::setGivenname(const std::string & value) {
	data->Givenname(ConvertToCDM::convert(value));
	return *this;
}

bool BaseDemographics::getGivenname(std::string & out) const {
	if (data->Givenname().present()) {
		out = ConvertFromCDM::convert(data->Givenname().get());
		return true;
	}
	return false;
}

std::string BaseDemographics::getGivenname() const {
	return ConvertFromCDM::convert(data->Givenname().get());
}
	
bool BaseDemographics::hasGivenname() const {
	return data->Givenname().present();
}
	
BaseDemographics & BaseDemographics::setFamilyname(const std::string & value) {
	data->Familyname(ConvertToCDM::convert(value));
	return *this;
}

bool BaseDemographics::getFamilyname(std::string & out) const {
	if (data->Familyname().present()) {
		out = ConvertFromCDM::convert(data->Familyname().get());
		return true;
	}
	return false;
}

std::string BaseDemographics::getFamilyname() const {
	return ConvertFromCDM::convert(data->Familyname().get());
}
	
bool BaseDemographics::hasFamilyname() const {
	return data->Familyname().present();
}
	
BaseDemographics & BaseDemographics::setBirthname(const std::string & value) {
	data->Birthname(ConvertToCDM::convert(value));
	return *this;
}

bool BaseDemographics::getBirthname(std::string & out) const {
	if (data->Birthname().present()) {
		out = ConvertFromCDM::convert(data->Birthname().get());
		return true;
	}
	return false;
}

std::string BaseDemographics::getBirthname() const {
	return ConvertFromCDM::convert(data->Birthname().get());
}
	
bool BaseDemographics::hasBirthname() const {
	return data->Birthname().present();
}
	
BaseDemographics & BaseDemographics::setTitle(const std::string & value) {
	data->Title(ConvertToCDM::convert(value));
	return *this;
}

bool BaseDemographics::getTitle(std::string & out) const {
	if (data->Title().present()) {
		out = ConvertFromCDM::convert(data->Title().get());
		return true;
	}
	return false;
}

std::string BaseDemographics::getTitle() const {
	return ConvertFromCDM::convert(data->Title().get());
}
	
bool BaseDemographics::hasTitle() const {
	return data->Title().present();
}
	
BaseDemographics & BaseDemographics::addMiddlename(const std::string & value) {
	data->Middlename().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<std::string> BaseDemographics::getMiddlenameList() const {
	std::vector<std::string> result;
	result.reserve(data->Middlename().size());
	for (const auto & value: data->Middlename()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void BaseDemographics::clearMiddlenameList() {
	data->Middlename().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

