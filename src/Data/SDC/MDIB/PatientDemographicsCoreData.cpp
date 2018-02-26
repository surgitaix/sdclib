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

#include "OSCLib/Data/SDC/MDIB/PatientDemographicsCoreData.h"
#include "OSCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/SDC/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/SDC/MDIB/Measurement.h"
#include "OSCLib/Data/SDC/MDIB/CodedValue.h"

namespace SDCLib {
namespace Data {
namespace SDC {


PatientDemographicsCoreData::PatientDemographicsCoreData(
) : data(Defaults::PatientDemographicsCoreDataInit(
)) {}

PatientDemographicsCoreData::operator CDM::PatientDemographicsCoreData() const {
	return *data;
}

PatientDemographicsCoreData::PatientDemographicsCoreData(const CDM::PatientDemographicsCoreData & object) : data(new CDM::PatientDemographicsCoreData(object)) {

}

PatientDemographicsCoreData::PatientDemographicsCoreData(const PatientDemographicsCoreData & object) : data(new CDM::PatientDemographicsCoreData(*object.data)) {

}

PatientDemographicsCoreData::~PatientDemographicsCoreData() {

}

void PatientDemographicsCoreData::copyFrom(const PatientDemographicsCoreData & object) {
	data = std::shared_ptr<CDM::PatientDemographicsCoreData>( new CDM::PatientDemographicsCoreData(*object.data));
}

PatientDemographicsCoreData & PatientDemographicsCoreData:: operator=(const PatientDemographicsCoreData & object) {
	copyFrom(object);
	return *this;
}


PatientDemographicsCoreData & PatientDemographicsCoreData::setGivenname(const std::string & value) {
	data->Givenname(ConvertToCDM::convert(value));
	return *this;
}

bool PatientDemographicsCoreData::getGivenname(std::string & out) const {
	if (data->Givenname().present()) {
		out = ConvertFromCDM::convert(data->Givenname().get());
		return true;
	}
	return false;
}

std::string PatientDemographicsCoreData::getGivenname() const {
	return ConvertFromCDM::convert(data->Givenname().get());
}
	
bool PatientDemographicsCoreData::hasGivenname() const {
	return data->Givenname().present();
}
	
PatientDemographicsCoreData & PatientDemographicsCoreData::setFamilyname(const std::string & value) {
	data->Familyname(ConvertToCDM::convert(value));
	return *this;
}

bool PatientDemographicsCoreData::getFamilyname(std::string & out) const {
	if (data->Familyname().present()) {
		out = ConvertFromCDM::convert(data->Familyname().get());
		return true;
	}
	return false;
}

std::string PatientDemographicsCoreData::getFamilyname() const {
	return ConvertFromCDM::convert(data->Familyname().get());
}
	
bool PatientDemographicsCoreData::hasFamilyname() const {
	return data->Familyname().present();
}
	
PatientDemographicsCoreData & PatientDemographicsCoreData::setBirthname(const std::string & value) {
	data->Birthname(ConvertToCDM::convert(value));
	return *this;
}

bool PatientDemographicsCoreData::getBirthname(std::string & out) const {
	if (data->Birthname().present()) {
		out = ConvertFromCDM::convert(data->Birthname().get());
		return true;
	}
	return false;
}

std::string PatientDemographicsCoreData::getBirthname() const {
	return ConvertFromCDM::convert(data->Birthname().get());
}
	
bool PatientDemographicsCoreData::hasBirthname() const {
	return data->Birthname().present();
}
	
PatientDemographicsCoreData & PatientDemographicsCoreData::setTitle(const std::string & value) {
	data->Title(ConvertToCDM::convert(value));
	return *this;
}

bool PatientDemographicsCoreData::getTitle(std::string & out) const {
	if (data->Title().present()) {
		out = ConvertFromCDM::convert(data->Title().get());
		return true;
	}
	return false;
}

std::string PatientDemographicsCoreData::getTitle() const {
	return ConvertFromCDM::convert(data->Title().get());
}
	
bool PatientDemographicsCoreData::hasTitle() const {
	return data->Title().present();
}
	
PatientDemographicsCoreData & PatientDemographicsCoreData::addMiddlename(const std::string & value) {
	data->Middlename().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<std::string> PatientDemographicsCoreData::getMiddlenameList() const {
	std::vector<std::string> result;
	result.reserve(data->Middlename().size());
	for (const auto & value: data->Middlename()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void PatientDemographicsCoreData::clearMiddlenameList() {
	data->Middlename().clear();
}

PatientDemographicsCoreData & PatientDemographicsCoreData::setSex(const Sex & value) {
	data->Sex(ConvertToCDM::convert(value));
	return *this;
}

bool PatientDemographicsCoreData::getSex(Sex & out) const {
	if (data->Sex().present()) {
		out = ConvertFromCDM::convert(data->Sex().get());
		return true;
	}
	return false;
}

Sex PatientDemographicsCoreData::getSex() const {
	return ConvertFromCDM::convert(data->Sex().get());
}
	
bool PatientDemographicsCoreData::hasSex() const {
	return data->Sex().present();
}
	
PatientDemographicsCoreData & PatientDemographicsCoreData::setPatientType(const PatientType & value) {
	data->PatientType(ConvertToCDM::convert(value));
	return *this;
}

bool PatientDemographicsCoreData::getPatientType(PatientType & out) const {
	if (data->PatientType().present()) {
		out = ConvertFromCDM::convert(data->PatientType().get());
		return true;
	}
	return false;
}

PatientType PatientDemographicsCoreData::getPatientType() const {
	return ConvertFromCDM::convert(data->PatientType().get());
}
	
bool PatientDemographicsCoreData::hasPatientType() const {
	return data->PatientType().present();
}
	
PatientDemographicsCoreData & PatientDemographicsCoreData::setDateOfBirth(const DateOfBirth & value) {
	data->DateOfBirth(ConvertToCDM::convert(value));
	return *this;
}

bool PatientDemographicsCoreData::getDateOfBirth(DateOfBirth & out) const {
	if (data->DateOfBirth().present()) {
		out = ConvertFromCDM::convert(data->DateOfBirth().get());
		return true;
	}
	return false;
}

DateOfBirth PatientDemographicsCoreData::getDateOfBirth() const {
	return ConvertFromCDM::convert(data->DateOfBirth().get());
}
	
bool PatientDemographicsCoreData::hasDateOfBirth() const {
	return data->DateOfBirth().present();
}
	
PatientDemographicsCoreData & PatientDemographicsCoreData::setHeight(const Measurement & value) {
	data->Height(ConvertToCDM::convert(value));
	return *this;
}

bool PatientDemographicsCoreData::getHeight(Measurement & out) const {
	if (data->Height().present()) {
		out = ConvertFromCDM::convert(data->Height().get());
		return true;
	}
	return false;
}

Measurement PatientDemographicsCoreData::getHeight() const {
	return ConvertFromCDM::convert(data->Height().get());
}
	
bool PatientDemographicsCoreData::hasHeight() const {
	return data->Height().present();
}
	
PatientDemographicsCoreData & PatientDemographicsCoreData::setWeight(const Measurement & value) {
	data->Weight(ConvertToCDM::convert(value));
	return *this;
}

bool PatientDemographicsCoreData::getWeight(Measurement & out) const {
	if (data->Weight().present()) {
		out = ConvertFromCDM::convert(data->Weight().get());
		return true;
	}
	return false;
}

Measurement PatientDemographicsCoreData::getWeight() const {
	return ConvertFromCDM::convert(data->Weight().get());
}
	
bool PatientDemographicsCoreData::hasWeight() const {
	return data->Weight().present();
}
	
PatientDemographicsCoreData & PatientDemographicsCoreData::setRace(const CodedValue & value) {
	data->Race(ConvertToCDM::convert(value));
	return *this;
}

bool PatientDemographicsCoreData::getRace(CodedValue & out) const {
	if (data->Race().present()) {
		out = ConvertFromCDM::convert(data->Race().get());
		return true;
	}
	return false;
}

CodedValue PatientDemographicsCoreData::getRace() const {
	return ConvertFromCDM::convert(data->Race().get());
}
	
bool PatientDemographicsCoreData::hasRace() const {
	return data->Race().present();
}
	

} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

