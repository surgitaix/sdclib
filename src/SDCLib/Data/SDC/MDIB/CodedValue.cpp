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
 *  CodedValue.cpp
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

#include "SDCLib/Data/SDC/MDIB/CodedValue.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/LocalizedText.h"
#include "SDCLib/Data/SDC/MDIB/Translation.h"

namespace SDCLib {
namespace Data {
namespace SDC {


CodedValue::CodedValue(
		CodeIdentifier code
) : data(Defaults::CodedValueInit(
		code
)) {}

CodedValue::operator CDM::CodedValue() const {
	return *data;
}

CodedValue::CodedValue(const CDM::CodedValue & object) : data(new CDM::CodedValue(object)) {

}

CodedValue::CodedValue(const CodedValue & object) : data(new CDM::CodedValue(*object.data)) {

}

CodedValue::~CodedValue() {

}

void CodedValue::copyFrom(const CodedValue & object) {
	data = std::shared_ptr<CDM::CodedValue>( new CDM::CodedValue(*object.data));
}

CodedValue & CodedValue:: operator=(const CodedValue & object) {
	copyFrom(object);
	return *this;
}


CodedValue & CodedValue::setCode(const CodeIdentifier & value) {
	data->setCode(ConvertToCDM::convert(value));
	return *this;
}


CodeIdentifier CodedValue::getCode() const {
	return ConvertFromCDM::convert(data->getCode());
}

CodedValue & CodedValue::setCodingSystem(const xml_schema::Uri & value) {
	data->setCodingSystem(ConvertToCDM::convert(value));
	return *this;
}

bool CodedValue::getCodingSystem(xml_schema::Uri & out) const {
	if (data->getCodingSystem().present()) {
		out = ConvertFromCDM::convert(data->getCodingSystem().get());
		return true;
	}
	return false;
}

xml_schema::Uri CodedValue::getCodingSystem() const {
	return ConvertFromCDM::convert(data->getCodingSystem().get());
}

bool CodedValue::hasCodingSystem() const {
	return data->getCodingSystem().present();
}

CodedValue & CodedValue::setCodingSystemVersion(const std::string & value) {
	data->setCodingSystemVersion(ConvertToCDM::convert(value));
	return *this;
}

bool CodedValue::getCodingSystemVersion(std::string & out) const {
	if (data->getCodingSystemVersion().present()) {
		out = ConvertFromCDM::convert(data->getCodingSystemVersion().get());
		return true;
	}
	return false;
}

std::string CodedValue::getCodingSystemVersion() const {
	return ConvertFromCDM::convert(data->getCodingSystemVersion().get());
}

bool CodedValue::hasCodingSystemVersion() const {
	return data->getCodingSystemVersion().present();
}

CodedValue & CodedValue::setSymbolicCodeName(const SymbolicCodeName & value) {
	data->setSymbolicCodeName(ConvertToCDM::convert(value));
	return *this;
}

bool CodedValue::getSymbolicCodeName(SymbolicCodeName & out) const {
	if (data->getSymbolicCodeName().present()) {
		out = ConvertFromCDM::convert(data->getSymbolicCodeName().get());
		return true;
	}
	return false;
}

SymbolicCodeName CodedValue::getSymbolicCodeName() const {
	return ConvertFromCDM::convert(data->getSymbolicCodeName().get());
}

bool CodedValue::hasSymbolicCodeName() const {
	return data->getSymbolicCodeName().present();
}

CodedValue & CodedValue::addCodingSystemName(const LocalizedText & value) {
	data->getCodingSystemName().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<LocalizedText> CodedValue::getCodingSystemNameList() const {
	std::vector<LocalizedText> result;
	result.reserve(data->getCodingSystemName().size());
	for (const auto & value: data->getCodingSystemName()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void CodedValue::clearCodingSystemNameList() {
	data->getCodingSystemName().clear();
}

CodedValue & CodedValue::addConceptDescription(const LocalizedText & value) {
	data->getConceptDescription().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<LocalizedText> CodedValue::getConceptDescriptionList() const {
	std::vector<LocalizedText> result;
	result.reserve(data->getConceptDescription().size());
	for (const auto & value: data->getConceptDescription()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void CodedValue::clearConceptDescriptionList() {
	data->getConceptDescription().clear();
}

CodedValue & CodedValue::addTranslation(const Translation & value) {
	data->getTranslation().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<Translation> CodedValue::getTranslationList() const {
	std::vector<Translation> result;
	result.reserve(data->getTranslation().size());
	for (const auto & value: data->getTranslation()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void CodedValue::clearTranslationList() {
	data->getTranslation().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

