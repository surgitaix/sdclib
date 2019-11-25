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
 *  NeonatalPatientDemographicsCoreData.cpp
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

#include "SDCLib/Data/SDC/MDIB/NeonatalPatientDemographicsCoreData.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/Measurement.h"
#include "SDCLib/Data/SDC/MDIB/PersonReference.h"
#include "SDCLib/Data/SDC/MDIB/Measurement.h"
#include "SDCLib/Data/SDC/MDIB/CodedValue.h"

namespace SDCLib {
namespace Data {
namespace SDC {


NeonatalPatientDemographicsCoreData::NeonatalPatientDemographicsCoreData(
) : data(Defaults::NeonatalPatientDemographicsCoreDataInit(
)) {}

NeonatalPatientDemographicsCoreData::operator CDM::NeonatalPatientDemographicsCoreData() const {
	return *data;
}

NeonatalPatientDemographicsCoreData::NeonatalPatientDemographicsCoreData(const CDM::NeonatalPatientDemographicsCoreData & object) : data(new CDM::NeonatalPatientDemographicsCoreData(object)) {

}

NeonatalPatientDemographicsCoreData::NeonatalPatientDemographicsCoreData(const NeonatalPatientDemographicsCoreData & object) : data(new CDM::NeonatalPatientDemographicsCoreData(*object.data)) {

}

NeonatalPatientDemographicsCoreData::~NeonatalPatientDemographicsCoreData() {

}

void NeonatalPatientDemographicsCoreData::copyFrom(const NeonatalPatientDemographicsCoreData & object) {
	data = std::shared_ptr<CDM::NeonatalPatientDemographicsCoreData>( new CDM::NeonatalPatientDemographicsCoreData(*object.data));
}

NeonatalPatientDemographicsCoreData & NeonatalPatientDemographicsCoreData:: operator=(const NeonatalPatientDemographicsCoreData & object) {
	copyFrom(object);
	return *this;
}


NeonatalPatientDemographicsCoreData & NeonatalPatientDemographicsCoreData::setGivenname(const std::string & value) {
	data->setGivenname(ConvertToCDM::convert(value));
	return *this;
}

bool NeonatalPatientDemographicsCoreData::getGivenname(std::string & out) const {
	if (data->getGivenname().present()) {
		out = ConvertFromCDM::convert(data->getGivenname().get());
		return true;
	}
	return false;
}

std::string NeonatalPatientDemographicsCoreData::getGivenname() const {
	return ConvertFromCDM::convert(data->getGivenname().get());
}

bool NeonatalPatientDemographicsCoreData::hasGivenname() const {
	return data->getGivenname().present();
}

NeonatalPatientDemographicsCoreData & NeonatalPatientDemographicsCoreData::setFamilyname(const std::string & value) {
	data->setFamilyname(ConvertToCDM::convert(value));
	return *this;
}

bool NeonatalPatientDemographicsCoreData::getFamilyname(std::string & out) const {
	if (data->getFamilyname().present()) {
		out = ConvertFromCDM::convert(data->getFamilyname().get());
		return true;
	}
	return false;
}

std::string NeonatalPatientDemographicsCoreData::getFamilyname() const {
	return ConvertFromCDM::convert(data->getFamilyname().get());
}

bool NeonatalPatientDemographicsCoreData::hasFamilyname() const {
	return data->getFamilyname().present();
}

NeonatalPatientDemographicsCoreData & NeonatalPatientDemographicsCoreData::setBirthname(const std::string & value) {
	data->setBirthname(ConvertToCDM::convert(value));
	return *this;
}

bool NeonatalPatientDemographicsCoreData::getBirthname(std::string & out) const {
	if (data->getBirthname().present()) {
		out = ConvertFromCDM::convert(data->getBirthname().get());
		return true;
	}
	return false;
}

std::string NeonatalPatientDemographicsCoreData::getBirthname() const {
	return ConvertFromCDM::convert(data->getBirthname().get());
}

bool NeonatalPatientDemographicsCoreData::hasBirthname() const {
	return data->getBirthname().present();
}

NeonatalPatientDemographicsCoreData & NeonatalPatientDemographicsCoreData::setTitle(const std::string & value) {
	data->setTitle(ConvertToCDM::convert(value));
	return *this;
}

bool NeonatalPatientDemographicsCoreData::getTitle(std::string & out) const {
	if (data->getTitle().present()) {
		out = ConvertFromCDM::convert(data->getTitle().get());
		return true;
	}
	return false;
}

std::string NeonatalPatientDemographicsCoreData::getTitle() const {
	return ConvertFromCDM::convert(data->getTitle().get());
}

bool NeonatalPatientDemographicsCoreData::hasTitle() const {
	return data->getTitle().present();
}

NeonatalPatientDemographicsCoreData & NeonatalPatientDemographicsCoreData::addMiddlename(const std::string & value) {
	data->getMiddlename().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<std::string> NeonatalPatientDemographicsCoreData::getMiddlenameList() const {
	std::vector<std::string> result;
	result.reserve(data->getMiddlename().size());
	for (const auto & value: data->getMiddlename()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void NeonatalPatientDemographicsCoreData::clearMiddlenameList() {
	data->getMiddlename().clear();
}

NeonatalPatientDemographicsCoreData & NeonatalPatientDemographicsCoreData::setSex(const Sex & value) {
	data->setSex(ConvertToCDM::convert(value));
	return *this;
}

bool NeonatalPatientDemographicsCoreData::getSex(Sex & out) const {
	if (data->getSex().present()) {
		out = ConvertFromCDM::convert(data->getSex().get());
		return true;
	}
	return false;
}

Sex NeonatalPatientDemographicsCoreData::getSex() const {
	return ConvertFromCDM::convert(data->getSex().get());
}

bool NeonatalPatientDemographicsCoreData::hasSex() const {
	return data->getSex().present();
}

NeonatalPatientDemographicsCoreData & NeonatalPatientDemographicsCoreData::setPatientType(const PatientType & value) {
	data->setPatientType(ConvertToCDM::convert(value));
	return *this;
}

bool NeonatalPatientDemographicsCoreData::getPatientType(PatientType & out) const {
	if (data->getPatientType().present()) {
		out = ConvertFromCDM::convert(data->getPatientType().get());
		return true;
	}
	return false;
}

PatientType NeonatalPatientDemographicsCoreData::getPatientType() const {
	return ConvertFromCDM::convert(data->getPatientType().get());
}

bool NeonatalPatientDemographicsCoreData::hasPatientType() const {
	return data->getPatientType().present();
}

NeonatalPatientDemographicsCoreData & NeonatalPatientDemographicsCoreData::setDateOfBirth(const DateOfBirth & value) {
	data->setDateOfBirth(ConvertToCDM::convert(value));
	return *this;
}

bool NeonatalPatientDemographicsCoreData::getDateOfBirth(DateOfBirth & out) const {
	if (data->getDateOfBirth().present()) {
		out = ConvertFromCDM::convert(data->getDateOfBirth().get());
		return true;
	}
	return false;
}

DateOfBirth NeonatalPatientDemographicsCoreData::getDateOfBirth() const {
	return ConvertFromCDM::convert(data->getDateOfBirth().get());
}

bool NeonatalPatientDemographicsCoreData::hasDateOfBirth() const {
	return data->getDateOfBirth().present();
}

NeonatalPatientDemographicsCoreData & NeonatalPatientDemographicsCoreData::setHeight(const Measurement & value) {
	data->setHeight(ConvertToCDM::convert(value));
	return *this;
}

bool NeonatalPatientDemographicsCoreData::getHeight(Measurement & out) const {
	if (data->getHeight().present()) {
		out = ConvertFromCDM::convert(data->getHeight().get());
		return true;
	}
	return false;
}

Measurement NeonatalPatientDemographicsCoreData::getHeight() const {
	return ConvertFromCDM::convert(data->getHeight().get());
}

bool NeonatalPatientDemographicsCoreData::hasHeight() const {
	return data->getHeight().present();
}

NeonatalPatientDemographicsCoreData & NeonatalPatientDemographicsCoreData::setWeight(const Measurement & value) {
	data->setWeight(ConvertToCDM::convert(value));
	return *this;
}

bool NeonatalPatientDemographicsCoreData::getWeight(Measurement & out) const {
	if (data->getWeight().present()) {
		out = ConvertFromCDM::convert(data->getWeight().get());
		return true;
	}
	return false;
}

Measurement NeonatalPatientDemographicsCoreData::getWeight() const {
	return ConvertFromCDM::convert(data->getWeight().get());
}

bool NeonatalPatientDemographicsCoreData::hasWeight() const {
	return data->getWeight().present();
}

NeonatalPatientDemographicsCoreData & NeonatalPatientDemographicsCoreData::setRace(const CodedValue & value) {
	data->setRace(ConvertToCDM::convert(value));
	return *this;
}

bool NeonatalPatientDemographicsCoreData::getRace(CodedValue & out) const {
	if (data->getRace().present()) {
		out = ConvertFromCDM::convert(data->getRace().get());
		return true;
	}
	return false;
}

CodedValue NeonatalPatientDemographicsCoreData::getRace() const {
	return ConvertFromCDM::convert(data->getRace().get());
}

bool NeonatalPatientDemographicsCoreData::hasRace() const {
	return data->getRace().present();
}

NeonatalPatientDemographicsCoreData & NeonatalPatientDemographicsCoreData::setGestationalAge(const Measurement & value) {
	data->setGestationalAge(ConvertToCDM::convert(value));
	return *this;
}

bool NeonatalPatientDemographicsCoreData::getGestationalAge(Measurement & out) const {
	if (data->getGestationalAge().present()) {
		out = ConvertFromCDM::convert(data->getGestationalAge().get());
		return true;
	}
	return false;
}

Measurement NeonatalPatientDemographicsCoreData::getGestationalAge() const {
	return ConvertFromCDM::convert(data->getGestationalAge().get());
}

bool NeonatalPatientDemographicsCoreData::hasGestationalAge() const {
	return data->getGestationalAge().present();
}

NeonatalPatientDemographicsCoreData & NeonatalPatientDemographicsCoreData::setBirthLength(const Measurement & value) {
	data->setBirthLength(ConvertToCDM::convert(value));
	return *this;
}

bool NeonatalPatientDemographicsCoreData::getBirthLength(Measurement & out) const {
	if (data->getBirthLength().present()) {
		out = ConvertFromCDM::convert(data->getBirthLength().get());
		return true;
	}
	return false;
}

Measurement NeonatalPatientDemographicsCoreData::getBirthLength() const {
	return ConvertFromCDM::convert(data->getBirthLength().get());
}

bool NeonatalPatientDemographicsCoreData::hasBirthLength() const {
	return data->getBirthLength().present();
}

NeonatalPatientDemographicsCoreData & NeonatalPatientDemographicsCoreData::setBirthWeight(const Measurement & value) {
	data->setBirthWeight(ConvertToCDM::convert(value));
	return *this;
}

bool NeonatalPatientDemographicsCoreData::getBirthWeight(Measurement & out) const {
	if (data->getBirthWeight().present()) {
		out = ConvertFromCDM::convert(data->getBirthWeight().get());
		return true;
	}
	return false;
}

Measurement NeonatalPatientDemographicsCoreData::getBirthWeight() const {
	return ConvertFromCDM::convert(data->getBirthWeight().get());
}

bool NeonatalPatientDemographicsCoreData::hasBirthWeight() const {
	return data->getBirthWeight().present();
}

NeonatalPatientDemographicsCoreData & NeonatalPatientDemographicsCoreData::setHeadCircumference(const Measurement & value) {
	data->setHeadCircumference(ConvertToCDM::convert(value));
	return *this;
}

bool NeonatalPatientDemographicsCoreData::getHeadCircumference(Measurement & out) const {
	if (data->getHeadCircumference().present()) {
		out = ConvertFromCDM::convert(data->getHeadCircumference().get());
		return true;
	}
	return false;
}

Measurement NeonatalPatientDemographicsCoreData::getHeadCircumference() const {
	return ConvertFromCDM::convert(data->getHeadCircumference().get());
}

bool NeonatalPatientDemographicsCoreData::hasHeadCircumference() const {
	return data->getHeadCircumference().present();
}

NeonatalPatientDemographicsCoreData & NeonatalPatientDemographicsCoreData::setMother(const PersonReference & value) {
	data->setMother(ConvertToCDM::convert(value));
	return *this;
}

bool NeonatalPatientDemographicsCoreData::getMother(PersonReference & out) const {
	if (data->getMother().present()) {
		out = ConvertFromCDM::convert(data->getMother().get());
		return true;
	}
	return false;
}

PersonReference NeonatalPatientDemographicsCoreData::getMother() const {
	return ConvertFromCDM::convert(data->getMother().get());
}

bool NeonatalPatientDemographicsCoreData::hasMother() const {
	return data->getMother().present();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

