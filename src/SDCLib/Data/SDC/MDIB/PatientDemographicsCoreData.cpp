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
 *  PatientDemographicsCoreData.cpp
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

#include "SDCLib/Data/SDC/MDIB/PatientDemographicsCoreData.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/Measurement.h"
#include "SDCLib/Data/SDC/MDIB/CodedValue.h"

namespace SDCLib {
namespace Data {
namespace SDC {


PatientDemographicsCoreData::PatientDemographicsCoreData(
) : data(Defaults::PatientDemographicsCoreDataInit(
))
{}

PatientDemographicsCoreData::operator CDM::PatientDemographicsCoreData() const {
	return *data;
}

PatientDemographicsCoreData::PatientDemographicsCoreData(const CDM::PatientDemographicsCoreData & object)
: data(new CDM::PatientDemographicsCoreData(object))
{ }

PatientDemographicsCoreData::PatientDemographicsCoreData(const PatientDemographicsCoreData & object)
: data(std::make_shared<CDM::PatientDemographicsCoreData>(*object.data))
{ }

void PatientDemographicsCoreData::copyFrom(const PatientDemographicsCoreData & object) {
	data = std::make_shared<CDM::PatientDemographicsCoreData>(*object.data);
}

PatientDemographicsCoreData & PatientDemographicsCoreData:: operator=(const PatientDemographicsCoreData& object) {
	copyFrom(object);
	return *this;
}


PatientDemographicsCoreData & PatientDemographicsCoreData::setGivenname(const std::string & value) {
	data->setGivenname(ConvertToCDM::convert(value));
	return *this;
}

bool PatientDemographicsCoreData::getGivenname(std::string & out) const {
	if (data->getGivenname().present()) {
		out = ConvertFromCDM::convert(data->getGivenname().get());
		return true;
	}
	return false;
}

std::string PatientDemographicsCoreData::getGivenname() const {
	return ConvertFromCDM::convert(data->getGivenname().get());
}

bool PatientDemographicsCoreData::hasGivenname() const {
	return data->getGivenname().present();
}

PatientDemographicsCoreData & PatientDemographicsCoreData::setFamilyname(const std::string & value) {
	data->setFamilyname(ConvertToCDM::convert(value));
	return *this;
}

bool PatientDemographicsCoreData::getFamilyname(std::string & out) const {
	if (data->getFamilyname().present()) {
		out = ConvertFromCDM::convert(data->getFamilyname().get());
		return true;
	}
	return false;
}

std::string PatientDemographicsCoreData::getFamilyname() const {
	return ConvertFromCDM::convert(data->getFamilyname().get());
}

bool PatientDemographicsCoreData::hasFamilyname() const {
	return data->getFamilyname().present();
}

PatientDemographicsCoreData & PatientDemographicsCoreData::setBirthname(const std::string & value) {
	data->setBirthname(ConvertToCDM::convert(value));
	return *this;
}

bool PatientDemographicsCoreData::getBirthname(std::string & out) const {
	if (data->getBirthname().present()) {
		out = ConvertFromCDM::convert(data->getBirthname().get());
		return true;
	}
	return false;
}

std::string PatientDemographicsCoreData::getBirthname() const {
	return ConvertFromCDM::convert(data->getBirthname().get());
}

bool PatientDemographicsCoreData::hasBirthname() const {
	return data->getBirthname().present();
}

PatientDemographicsCoreData & PatientDemographicsCoreData::setTitle(const std::string & value) {
	data->setTitle(ConvertToCDM::convert(value));
	return *this;
}

bool PatientDemographicsCoreData::getTitle(std::string & out) const {
	if (data->getTitle().present()) {
		out = ConvertFromCDM::convert(data->getTitle().get());
		return true;
	}
	return false;
}

std::string PatientDemographicsCoreData::getTitle() const {
	return ConvertFromCDM::convert(data->getTitle().get());
}

bool PatientDemographicsCoreData::hasTitle() const {
	return data->getTitle().present();
}

PatientDemographicsCoreData & PatientDemographicsCoreData::addMiddlename(const std::string & value) {
	data->getMiddlename().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<std::string> PatientDemographicsCoreData::getMiddlenameList() const {
	std::vector<std::string> result;
	result.reserve(data->getMiddlename().size());
	for (const auto & value: data->getMiddlename()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void PatientDemographicsCoreData::clearMiddlenameList() {
	data->getMiddlename().clear();
}

PatientDemographicsCoreData & PatientDemographicsCoreData::setSex(const Sex & value) {
	data->setSex(ConvertToCDM::convert(value));
	return *this;
}

bool PatientDemographicsCoreData::getSex(Sex & out) const {
	if (data->getSex().present()) {
		out = ConvertFromCDM::convert(data->getSex().get());
		return true;
	}
	return false;
}

Sex PatientDemographicsCoreData::getSex() const {
	return ConvertFromCDM::convert(data->getSex().get());
}

bool PatientDemographicsCoreData::hasSex() const {
	return data->getSex().present();
}

PatientDemographicsCoreData & PatientDemographicsCoreData::setPatientType(const PatientType & value) {
	data->setPatientType(ConvertToCDM::convert(value));
	return *this;
}

bool PatientDemographicsCoreData::getPatientType(PatientType & out) const {
	if (data->getPatientType().present()) {
		out = ConvertFromCDM::convert(data->getPatientType().get());
		return true;
	}
	return false;
}

PatientType PatientDemographicsCoreData::getPatientType() const {
	return ConvertFromCDM::convert(data->getPatientType().get());
}

bool PatientDemographicsCoreData::hasPatientType() const {
	return data->getPatientType().present();
}

PatientDemographicsCoreData & PatientDemographicsCoreData::setDateOfBirth(const DateOfBirth & value) {
	data->setDateOfBirth(ConvertToCDM::convert(value));
	return *this;
}

bool PatientDemographicsCoreData::getDateOfBirth(DateOfBirth & out) const {
	if (data->getDateOfBirth().present()) {
		out = ConvertFromCDM::convert(data->getDateOfBirth().get());
		return true;
	}
	return false;
}

DateOfBirth PatientDemographicsCoreData::getDateOfBirth() const {
	return ConvertFromCDM::convert(data->getDateOfBirth().get());
}

bool PatientDemographicsCoreData::hasDateOfBirth() const {
	return data->getDateOfBirth().present();
}

PatientDemographicsCoreData & PatientDemographicsCoreData::setHeight(const Measurement & value) {
	data->setHeight(ConvertToCDM::convert(value));
	return *this;
}

bool PatientDemographicsCoreData::getHeight(Measurement & out) const {
	if (data->getHeight().present()) {
		out = ConvertFromCDM::convert(data->getHeight().get());
		return true;
	}
	return false;
}

Measurement PatientDemographicsCoreData::getHeight() const {
	return ConvertFromCDM::convert(data->getHeight().get());
}

bool PatientDemographicsCoreData::hasHeight() const {
	return data->getHeight().present();
}

PatientDemographicsCoreData & PatientDemographicsCoreData::setWeight(const Measurement & value) {
	data->setWeight(ConvertToCDM::convert(value));
	return *this;
}

bool PatientDemographicsCoreData::getWeight(Measurement & out) const {
	if (data->getWeight().present()) {
		out = ConvertFromCDM::convert(data->getWeight().get());
		return true;
	}
	return false;
}

Measurement PatientDemographicsCoreData::getWeight() const {
	return ConvertFromCDM::convert(data->getWeight().get());
}

bool PatientDemographicsCoreData::hasWeight() const {
	return data->getWeight().present();
}

PatientDemographicsCoreData & PatientDemographicsCoreData::setRace(const CodedValue & value) {
	data->setRace(ConvertToCDM::convert(value));
	return *this;
}

bool PatientDemographicsCoreData::getRace(CodedValue & out) const {
	if (data->getRace().present()) {
		out = ConvertFromCDM::convert(data->getRace().get());
		return true;
	}
	return false;
}

CodedValue PatientDemographicsCoreData::getRace() const {
	return ConvertFromCDM::convert(data->getRace().get());
}

bool PatientDemographicsCoreData::hasRace() const {
	return data->getRace().present();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

