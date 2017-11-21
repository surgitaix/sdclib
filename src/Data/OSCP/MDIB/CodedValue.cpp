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

#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/LocalizedText.h"

namespace OSCLib {
namespace Data {
namespace OSCP {


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
	*data = *object.data;
}

CodedValue & CodedValue:: operator=(const CodedValue & object) {
	copyFrom(object);
	return *this;
}


CodedValue & CodedValue::setCode(const CodeIdentifier & value) {
	data->Code(ConvertToCDM::convert(value));
	return *this;
}


CodeIdentifier CodedValue::getCode() const {
	return ConvertFromCDM::convert(data->Code());
}
	
CodedValue & CodedValue::setCodingSystem(const xml_schema::Uri & value) {
	data->CodingSystem(ConvertToCDM::convert(value));
	return *this;
}

bool CodedValue::getCodingSystem(xml_schema::Uri & out) const {
	if (data->CodingSystem().present()) {
		out = ConvertFromCDM::convert(data->CodingSystem().get());
		return true;
	}
	return false;
}

xml_schema::Uri CodedValue::getCodingSystem() const {
	return ConvertFromCDM::convert(data->CodingSystem().get());
}
	
bool CodedValue::hasCodingSystem() const {
	return data->CodingSystem().present();
}
	
CodedValue & CodedValue::setCodingSystemVersion(const std::string & value) {
	data->CodingSystemVersion(ConvertToCDM::convert(value));
	return *this;
}

bool CodedValue::getCodingSystemVersion(std::string & out) const {
	if (data->CodingSystemVersion().present()) {
		out = ConvertFromCDM::convert(data->CodingSystemVersion().get());
		return true;
	}
	return false;
}

std::string CodedValue::getCodingSystemVersion() const {
	return ConvertFromCDM::convert(data->CodingSystemVersion().get());
}
	
bool CodedValue::hasCodingSystemVersion() const {
	return data->CodingSystemVersion().present();
}
	
CodedValue & CodedValue::setSymbolicCodeName(const SymbolicCodeName & value) {
	data->SymbolicCodeName(ConvertToCDM::convert(value));
	return *this;
}

bool CodedValue::getSymbolicCodeName(SymbolicCodeName & out) const {
	if (data->SymbolicCodeName().present()) {
		out = ConvertFromCDM::convert(data->SymbolicCodeName().get());
		return true;
	}
	return false;
}

SymbolicCodeName CodedValue::getSymbolicCodeName() const {
	return ConvertFromCDM::convert(data->SymbolicCodeName().get());
}
	
bool CodedValue::hasSymbolicCodeName() const {
	return data->SymbolicCodeName().present();
}
	
CodedValue & CodedValue::addCodingSystemName(const LocalizedText & value) {
	data->CodingSystemName().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<LocalizedText> CodedValue::getCodingSystemNameList() const {
	std::vector<LocalizedText> result;
	result.reserve(data->CodingSystemName().size());
	for (const auto & value: data->CodingSystemName()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void CodedValue::clearCodingSystemNameList() {
	data->CodingSystemName().clear();
}

CodedValue & CodedValue::addConceptDescription(const LocalizedText & value) {
	data->ConceptDescription().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<LocalizedText> CodedValue::getConceptDescriptionList() const {
	std::vector<LocalizedText> result;
	result.reserve(data->ConceptDescription().size());
	for (const auto & value: data->ConceptDescription()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void CodedValue::clearConceptDescriptionList() {
	data->ConceptDescription().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

