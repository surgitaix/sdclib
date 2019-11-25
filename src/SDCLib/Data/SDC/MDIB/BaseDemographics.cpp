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
 *  Author: besting, buerger, roehser
 */

/**
 * THIS FILE IS GENERATED AUTOMATICALLY! DO NOT MODIFY!
 *
 * YOUR CHANGES WILL BE OVERWRITTEN!
 *
 * USE THE DEFINITION FILES IN THE FOLDER "codegenerator" INSTEAD!
 */

#include "SDCLib/Data/SDC/MDIB/BaseDemographics.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"


namespace SDCLib {
namespace Data {
namespace SDC {


BaseDemographics::BaseDemographics(
) : data(Defaults::BaseDemographicsInit(
)) {}

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
	data = std::shared_ptr<CDM::BaseDemographics>( new CDM::BaseDemographics(*object.data));
}

BaseDemographics & BaseDemographics:: operator=(const BaseDemographics & object) {
	copyFrom(object);
	return *this;
}


BaseDemographics & BaseDemographics::setGivenname(const std::string & value) {
	data->setGivenname(ConvertToCDM::convert(value));
	return *this;
}

bool BaseDemographics::getGivenname(std::string & out) const {
	if (data->getGivenname().present()) {
		out = ConvertFromCDM::convert(data->getGivenname().get());
		return true;
	}
	return false;
}

std::string BaseDemographics::getGivenname() const {
	return ConvertFromCDM::convert(data->getGivenname().get());
}

bool BaseDemographics::hasGivenname() const {
	return data->getGivenname().present();
}

BaseDemographics & BaseDemographics::setFamilyname(const std::string & value) {
	data->setFamilyname(ConvertToCDM::convert(value));
	return *this;
}

bool BaseDemographics::getFamilyname(std::string & out) const {
	if (data->getFamilyname().present()) {
		out = ConvertFromCDM::convert(data->getFamilyname().get());
		return true;
	}
	return false;
}

std::string BaseDemographics::getFamilyname() const {
	return ConvertFromCDM::convert(data->getFamilyname().get());
}

bool BaseDemographics::hasFamilyname() const {
	return data->getFamilyname().present();
}

BaseDemographics & BaseDemographics::setBirthname(const std::string & value) {
	data->setBirthname(ConvertToCDM::convert(value));
	return *this;
}

bool BaseDemographics::getBirthname(std::string & out) const {
	if (data->getBirthname().present()) {
		out = ConvertFromCDM::convert(data->getBirthname().get());
		return true;
	}
	return false;
}

std::string BaseDemographics::getBirthname() const {
	return ConvertFromCDM::convert(data->getBirthname().get());
}

bool BaseDemographics::hasBirthname() const {
	return data->getBirthname().present();
}

BaseDemographics & BaseDemographics::setTitle(const std::string & value) {
	data->setTitle(ConvertToCDM::convert(value));
	return *this;
}

bool BaseDemographics::getTitle(std::string & out) const {
	if (data->getTitle().present()) {
		out = ConvertFromCDM::convert(data->getTitle().get());
		return true;
	}
	return false;
}

std::string BaseDemographics::getTitle() const {
	return ConvertFromCDM::convert(data->getTitle().get());
}

bool BaseDemographics::hasTitle() const {
	return data->getTitle().present();
}

BaseDemographics & BaseDemographics::addMiddlename(const std::string & value) {
	data->getMiddlename().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<std::string> BaseDemographics::getMiddlenameList() const {
	std::vector<std::string> result;
	result.reserve(data->getMiddlename().size());
	for (const auto & value: data->getMiddlename()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void BaseDemographics::clearMiddlenameList() {
	data->getMiddlename().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

