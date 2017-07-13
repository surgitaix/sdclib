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
 *  Author: besting, roehser
 */
 
/**
 * THIS FILE IS GENERATED AUTOMATICALLY! DO NOT MODIFY!
 *
 * YOUR CHANGES WILL BE OVERWRITTEN!
 * 
 * USE THE DEFINITION FILES IN THE FOLDER "codegenerator" INSTEAD!
 */

#include "OSCLib/Data/OSCP/MDIB/NeonatalPatientDemographicsCoreData.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/Measurement.h"
#include "OSCLib/Data/OSCP/MDIB/PersonReference.h"
#include "OSCLib/Data/OSCP/MDIB/Measurement.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

NeonatalPatientDemographicsCoreData::NeonatalPatientDemographicsCoreData() : data(Defaults::NeonatalPatientDemographicsCoreData()) {
}

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
	*data = *object.data;
}

NeonatalPatientDemographicsCoreData & NeonatalPatientDemographicsCoreData:: operator=(const NeonatalPatientDemographicsCoreData & object) {
	copyFrom(object);
	return *this;
}


NeonatalPatientDemographicsCoreData & NeonatalPatientDemographicsCoreData::setGivenname(const std::string & value) {
	data->Givenname(ConvertToCDM::convert(value));
	return *this;
}

bool NeonatalPatientDemographicsCoreData::getGivenname(std::string & out) const {
	if (data->Givenname().present()) {
		out = ConvertFromCDM::convert(data->Givenname().get());
		return true;
	}
	return false;
}

std::string NeonatalPatientDemographicsCoreData::getGivenname() const {
	return ConvertFromCDM::convert(data->Givenname().get());
}
	
bool NeonatalPatientDemographicsCoreData::hasGivenname() const {
	return data->Givenname().present();
}
	
NeonatalPatientDemographicsCoreData & NeonatalPatientDemographicsCoreData::setFamilyname(const std::string & value) {
	data->Familyname(ConvertToCDM::convert(value));
	return *this;
}

bool NeonatalPatientDemographicsCoreData::getFamilyname(std::string & out) const {
	if (data->Familyname().present()) {
		out = ConvertFromCDM::convert(data->Familyname().get());
		return true;
	}
	return false;
}

std::string NeonatalPatientDemographicsCoreData::getFamilyname() const {
	return ConvertFromCDM::convert(data->Familyname().get());
}
	
bool NeonatalPatientDemographicsCoreData::hasFamilyname() const {
	return data->Familyname().present();
}
	
NeonatalPatientDemographicsCoreData & NeonatalPatientDemographicsCoreData::setBirthname(const std::string & value) {
	data->Birthname(ConvertToCDM::convert(value));
	return *this;
}

bool NeonatalPatientDemographicsCoreData::getBirthname(std::string & out) const {
	if (data->Birthname().present()) {
		out = ConvertFromCDM::convert(data->Birthname().get());
		return true;
	}
	return false;
}

std::string NeonatalPatientDemographicsCoreData::getBirthname() const {
	return ConvertFromCDM::convert(data->Birthname().get());
}
	
bool NeonatalPatientDemographicsCoreData::hasBirthname() const {
	return data->Birthname().present();
}
	
NeonatalPatientDemographicsCoreData & NeonatalPatientDemographicsCoreData::setTitle(const std::string & value) {
	data->Title(ConvertToCDM::convert(value));
	return *this;
}

bool NeonatalPatientDemographicsCoreData::getTitle(std::string & out) const {
	if (data->Title().present()) {
		out = ConvertFromCDM::convert(data->Title().get());
		return true;
	}
	return false;
}

std::string NeonatalPatientDemographicsCoreData::getTitle() const {
	return ConvertFromCDM::convert(data->Title().get());
}
	
bool NeonatalPatientDemographicsCoreData::hasTitle() const {
	return data->Title().present();
}
	
NeonatalPatientDemographicsCoreData & NeonatalPatientDemographicsCoreData::addMiddlename(const std::string & value) {
	data->Middlename().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<std::string> NeonatalPatientDemographicsCoreData::getMiddlenameLists() const {
	std::vector<std::string> result;
	result.reserve(data->Middlename().size());
	for (const auto & value: data->Middlename()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void NeonatalPatientDemographicsCoreData::clearMiddlenameLists() {
	data->Middlename().clear();
}

NeonatalPatientDemographicsCoreData & NeonatalPatientDemographicsCoreData::setSex(const Sex & value) {
	data->Sex(ConvertToCDM::convert(value));
	return *this;
}

bool NeonatalPatientDemographicsCoreData::getSex(Sex & out) const {
	if (data->Sex().present()) {
		out = ConvertFromCDM::convert(data->Sex().get());
		return true;
	}
	return false;
}

Sex NeonatalPatientDemographicsCoreData::getSex() const {
	return ConvertFromCDM::convert(data->Sex().get());
}
	
bool NeonatalPatientDemographicsCoreData::hasSex() const {
	return data->Sex().present();
}
	
NeonatalPatientDemographicsCoreData & NeonatalPatientDemographicsCoreData::setPatientType(const PatientType & value) {
	data->PatientType(ConvertToCDM::convert(value));
	return *this;
}

bool NeonatalPatientDemographicsCoreData::getPatientType(PatientType & out) const {
	if (data->PatientType().present()) {
		out = ConvertFromCDM::convert(data->PatientType().get());
		return true;
	}
	return false;
}

PatientType NeonatalPatientDemographicsCoreData::getPatientType() const {
	return ConvertFromCDM::convert(data->PatientType().get());
}
	
bool NeonatalPatientDemographicsCoreData::hasPatientType() const {
	return data->PatientType().present();
}
	
NeonatalPatientDemographicsCoreData & NeonatalPatientDemographicsCoreData::setDateOfBirth(const DateOfBirthType & value) {
	data->DateOfBirth(ConvertToCDM::convert(value));
	return *this;
}

bool NeonatalPatientDemographicsCoreData::getDateOfBirth(DateOfBirthType & out) const {
	if (data->DateOfBirth().present()) {
		out = ConvertFromCDM::convert(data->DateOfBirth().get());
		return true;
	}
	return false;
}

DateOfBirthType NeonatalPatientDemographicsCoreData::getDateOfBirth() const {
	return ConvertFromCDM::convert(data->DateOfBirth().get());
}
	
bool NeonatalPatientDemographicsCoreData::hasDateOfBirth() const {
	return data->DateOfBirth().present();
}
	
NeonatalPatientDemographicsCoreData & NeonatalPatientDemographicsCoreData::setHeight(const Measurement & value) {
	data->Height(ConvertToCDM::convert(value));
	return *this;
}

bool NeonatalPatientDemographicsCoreData::getHeight(Measurement & out) const {
	if (data->Height().present()) {
		out = ConvertFromCDM::convert(data->Height().get());
		return true;
	}
	return false;
}

Measurement NeonatalPatientDemographicsCoreData::getHeight() const {
	return ConvertFromCDM::convert(data->Height().get());
}
	
bool NeonatalPatientDemographicsCoreData::hasHeight() const {
	return data->Height().present();
}
	
NeonatalPatientDemographicsCoreData & NeonatalPatientDemographicsCoreData::setWeight(const Measurement & value) {
	data->Weight(ConvertToCDM::convert(value));
	return *this;
}

bool NeonatalPatientDemographicsCoreData::getWeight(Measurement & out) const {
	if (data->Weight().present()) {
		out = ConvertFromCDM::convert(data->Weight().get());
		return true;
	}
	return false;
}

Measurement NeonatalPatientDemographicsCoreData::getWeight() const {
	return ConvertFromCDM::convert(data->Weight().get());
}
	
bool NeonatalPatientDemographicsCoreData::hasWeight() const {
	return data->Weight().present();
}
	
NeonatalPatientDemographicsCoreData & NeonatalPatientDemographicsCoreData::setRace(const CodedValue & value) {
	data->Race(ConvertToCDM::convert(value));
	return *this;
}

bool NeonatalPatientDemographicsCoreData::getRace(CodedValue & out) const {
	if (data->Race().present()) {
		out = ConvertFromCDM::convert(data->Race().get());
		return true;
	}
	return false;
}

CodedValue NeonatalPatientDemographicsCoreData::getRace() const {
	return ConvertFromCDM::convert(data->Race().get());
}
	
bool NeonatalPatientDemographicsCoreData::hasRace() const {
	return data->Race().present();
}
	
NeonatalPatientDemographicsCoreData & NeonatalPatientDemographicsCoreData::setGestationalAge(const Measurement & value) {
	data->GestationalAge(ConvertToCDM::convert(value));
	return *this;
}

bool NeonatalPatientDemographicsCoreData::getGestationalAge(Measurement & out) const {
	if (data->GestationalAge().present()) {
		out = ConvertFromCDM::convert(data->GestationalAge().get());
		return true;
	}
	return false;
}

Measurement NeonatalPatientDemographicsCoreData::getGestationalAge() const {
	return ConvertFromCDM::convert(data->GestationalAge().get());
}
	
bool NeonatalPatientDemographicsCoreData::hasGestationalAge() const {
	return data->GestationalAge().present();
}
	
NeonatalPatientDemographicsCoreData & NeonatalPatientDemographicsCoreData::setBirthLength(const Measurement & value) {
	data->BirthLength(ConvertToCDM::convert(value));
	return *this;
}

bool NeonatalPatientDemographicsCoreData::getBirthLength(Measurement & out) const {
	if (data->BirthLength().present()) {
		out = ConvertFromCDM::convert(data->BirthLength().get());
		return true;
	}
	return false;
}

Measurement NeonatalPatientDemographicsCoreData::getBirthLength() const {
	return ConvertFromCDM::convert(data->BirthLength().get());
}
	
bool NeonatalPatientDemographicsCoreData::hasBirthLength() const {
	return data->BirthLength().present();
}
	
NeonatalPatientDemographicsCoreData & NeonatalPatientDemographicsCoreData::setBirthWeight(const Measurement & value) {
	data->BirthWeight(ConvertToCDM::convert(value));
	return *this;
}

bool NeonatalPatientDemographicsCoreData::getBirthWeight(Measurement & out) const {
	if (data->BirthWeight().present()) {
		out = ConvertFromCDM::convert(data->BirthWeight().get());
		return true;
	}
	return false;
}

Measurement NeonatalPatientDemographicsCoreData::getBirthWeight() const {
	return ConvertFromCDM::convert(data->BirthWeight().get());
}
	
bool NeonatalPatientDemographicsCoreData::hasBirthWeight() const {
	return data->BirthWeight().present();
}
	
NeonatalPatientDemographicsCoreData & NeonatalPatientDemographicsCoreData::setHeadCircumference(const Measurement & value) {
	data->HeadCircumference(ConvertToCDM::convert(value));
	return *this;
}

bool NeonatalPatientDemographicsCoreData::getHeadCircumference(Measurement & out) const {
	if (data->HeadCircumference().present()) {
		out = ConvertFromCDM::convert(data->HeadCircumference().get());
		return true;
	}
	return false;
}

Measurement NeonatalPatientDemographicsCoreData::getHeadCircumference() const {
	return ConvertFromCDM::convert(data->HeadCircumference().get());
}
	
bool NeonatalPatientDemographicsCoreData::hasHeadCircumference() const {
	return data->HeadCircumference().present();
}
	
NeonatalPatientDemographicsCoreData & NeonatalPatientDemographicsCoreData::setMother(const PersonReference & value) {
	data->Mother(ConvertToCDM::convert(value));
	return *this;
}

bool NeonatalPatientDemographicsCoreData::getMother(PersonReference & out) const {
	if (data->Mother().present()) {
		out = ConvertFromCDM::convert(data->Mother().get());
		return true;
	}
	return false;
}

PersonReference NeonatalPatientDemographicsCoreData::getMother() const {
	return ConvertFromCDM::convert(data->Mother().get());
}
	
bool NeonatalPatientDemographicsCoreData::hasMother() const {
	return data->Mother().present();
}
	

} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

