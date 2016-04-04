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
 *  Author: besting, roehser
 */
 
/**
 * THIS FILE IS GENERATED AUTOMATICALLY! DO NOT MODIFY!
 *
 * YOUR CHANGES WILL BE OVERWRITTEN!
 * 
 * USE THE DEFINITION FILES IN THE FOLDER "codegenerator" INSTEAD!
 */

#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/LocalizedText.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

CodedValue::CodedValue() : data(Defaults::CodedValue()) {
}

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
	*data = *object.data;
}

CodedValue & CodedValue:: operator=(const CodedValue & object) {
	copyFrom(object);
	return *this;
}


CodedValue & CodedValue::setCodingSystemId(const std::string & value) {
	data->CodingSystemId(ConvertToCDM::convert(value));
	return *this;
}

bool CodedValue::getCodingSystemId(std::string & out) const {
	if (data->CodingSystemId().present()) {
		out = ConvertFromCDM::convert(data->CodingSystemId().get());
		return true;
	}
	return false;
}

std::string CodedValue::getCodingSystemId() const {
	return ConvertFromCDM::convert(data->CodingSystemId().get());
}
	
bool CodedValue::hasCodingSystemId() const {
	return data->CodingSystemId().present();
}
	
CodedValue & CodedValue::setVersionId(const std::string & value) {
	data->VersionId(ConvertToCDM::convert(value));
	return *this;
}

bool CodedValue::getVersionId(std::string & out) const {
	if (data->VersionId().present()) {
		out = ConvertFromCDM::convert(data->VersionId().get());
		return true;
	}
	return false;
}

std::string CodedValue::getVersionId() const {
	return ConvertFromCDM::convert(data->VersionId().get());
}
	
bool CodedValue::hasVersionId() const {
	return data->VersionId().present();
}
	
CodedValue & CodedValue::setCodeId(const std::string & value) {
	data->CodeId(ConvertToCDM::convert(value));
	return *this;
}


std::string CodedValue::getCodeId() const {
	return ConvertFromCDM::convert(data->CodeId());
}
	
CodedValue & CodedValue::addCodingSystemName(const LocalizedText & value) {
	data->CodingSystemName().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<LocalizedText> CodedValue::getCodingSystemNames() const {
	std::vector<LocalizedText> result;
	result.reserve(data->CodingSystemName().size());
	for (const auto & value: data->CodingSystemName()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void CodedValue::clearCodingSystemNames() {
	data->CodingSystemName().clear();
}

CodedValue & CodedValue::addConceptDescription(const LocalizedText & value) {
	data->ConceptDescription().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<LocalizedText> CodedValue::getConceptDescriptions() const {
	std::vector<LocalizedText> result;
	result.reserve(data->ConceptDescription().size());
	for (const auto & value: data->ConceptDescription()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void CodedValue::clearConceptDescriptions() {
	data->ConceptDescription().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

