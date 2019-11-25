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
 *  OperatingJurisdiction.cpp
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

#include "SDCLib/Data/SDC/MDIB/OperatingJurisdiction.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/CodedValue.h"
#include "SDCLib/Data/SDC/MDIB/LocalizedText.h"

namespace SDCLib {
namespace Data {
namespace SDC {

OperatingJurisdiction::OperatingJurisdiction() : data(Defaults::OperatingJurisdictionInit()) {
}

OperatingJurisdiction::operator CDM::OperatingJurisdiction() const {
	return *data;
}

OperatingJurisdiction::OperatingJurisdiction(const CDM::OperatingJurisdiction & object) : data(new CDM::OperatingJurisdiction(object)) {

}

OperatingJurisdiction::OperatingJurisdiction(const OperatingJurisdiction & object) : data(new CDM::OperatingJurisdiction(*object.data)) {

}

OperatingJurisdiction::~OperatingJurisdiction() {

}

void OperatingJurisdiction::copyFrom(const OperatingJurisdiction & object) {
	data = std::shared_ptr<CDM::OperatingJurisdiction>( new CDM::OperatingJurisdiction(*object.data));
}

OperatingJurisdiction & OperatingJurisdiction:: operator=(const OperatingJurisdiction & object) {
	copyFrom(object);
	return *this;
}


OperatingJurisdiction & OperatingJurisdiction::setType(const CodedValue & value) {
	data->setType(ConvertToCDM::convert(value));
	return *this;
}

bool OperatingJurisdiction::getType(CodedValue & out) const {
	if (data->getType().present()) {
		out = ConvertFromCDM::convert(data->getType().get());
		return true;
	}
	return false;
}

CodedValue OperatingJurisdiction::getType() const {
	return ConvertFromCDM::convert(data->getType().get());
}
	
bool OperatingJurisdiction::hasType() const {
	return data->getType().present();
}
	
OperatingJurisdiction & OperatingJurisdiction::setRoot(const Root & value) {
	data->setRoot(ConvertToCDM::convert(value));
	return *this;
}

bool OperatingJurisdiction::getRoot(Root & out) const {
	if (data->getRoot().present()) {
		out = ConvertFromCDM::convert(data->getRoot().get());
		return true;
	}
	return false;
}

Root OperatingJurisdiction::getRoot() const {
	return ConvertFromCDM::convert(data->getRoot().get());
}
	
bool OperatingJurisdiction::hasRoot() const {
	return data->getRoot().present();
}
	
OperatingJurisdiction & OperatingJurisdiction::setExtension(const Extension & value) {
	data->setExtension1(ConvertToCDM::convert(value));
	return *this;
}

bool OperatingJurisdiction::getExtension(Extension & out) const {
	if (data->getExtension1().present()) {
		out = ConvertFromCDM::convert(data->getExtension1().get());
		return true;
	}
	return false;
}

Extension OperatingJurisdiction::getExtension() const {
	return ConvertFromCDM::convert(data->getExtension1().get());
}
	
bool OperatingJurisdiction::hasExtension() const {
	return data->getExtension1().present();
}
	
OperatingJurisdiction & OperatingJurisdiction::addIdentifierName(const LocalizedText & value) {
	data->getIdentifierName().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<LocalizedText> OperatingJurisdiction::getIdentifierNameList() const {
	std::vector<LocalizedText> result;
	result.reserve(data->getIdentifierName().size());
	for (const auto & value: data->getIdentifierName()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void OperatingJurisdiction::clearIdentifierNameList() {
	data->getIdentifierName().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

