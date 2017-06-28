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
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/LocalizedText.h"
#include "OSCLib/Data/OSCP/MDIB/LocalizedText.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"

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


CodedValue & CodedValue::setCode(const CodeIdentifier & value) {
	data->Code(ConvertToCDM::convert(value));
	return *this;
}


CodeIdentifier CodedValue::getCode() const {
	return ConvertFromCDM::convert(data->Code());
}
	
CodedValue & CodedValue::setCodingSystem(const anyURI & value) {
	data->CodingSystem(ConvertToCDM::convert(value));
	return *this;
}


anyURI CodedValue::getCodingSystem() const {
	return ConvertFromCDM::convert(data->CodingSystem());
}
	
CodedValue & CodedValue::setCodingSystemVersion(const string & value) {
	data->CodingSystemVersion(ConvertToCDM::convert(value));
	return *this;
}


string CodedValue::getCodingSystemVersion() const {
	return ConvertFromCDM::convert(data->CodingSystemVersion());
}
	
CodedValue & CodedValue::setSymbolicCodeName(const SymbolicCodeName & value) {
	data->SymbolicCodeName(ConvertToCDM::convert(value));
	return *this;
}


SymbolicCodeName CodedValue::getSymbolicCodeName() const {
	return ConvertFromCDM::convert(data->SymbolicCodeName());
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

CodedValue & CodedValue::addTranslation(const CodedValue & value) {
	data->Translation().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<CodedValue> CodedValue::getTranslations() const {
	std::vector<CodedValue> result;
	result.reserve(data->Translation().size());
	for (const auto & value: data->Translation()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void CodedValue::clearTranslations() {
	data->Translation().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

