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

#include "OSCLib/Data/OSCP/MDIB/OperatingJurisdiction.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/LocalizedText.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

OperatingJurisdiction::OperatingJurisdiction() : data(Defaults::OperatingJurisdiction()) {
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
	*data = *object.data;
}

OperatingJurisdiction & OperatingJurisdiction:: operator=(const OperatingJurisdiction & object) {
	copyFrom(object);
	return *this;
}


OperatingJurisdiction & OperatingJurisdiction::setType(const CodedValue & value) {
	data->Type(ConvertToCDM::convert(value));
	return *this;
}

bool OperatingJurisdiction::getType(CodedValue & out) const {
	if (data->Type().present()) {
		out = ConvertFromCDM::convert(data->Type().get());
		return true;
	}
	return false;
}

CodedValue OperatingJurisdiction::getType() const {
	return ConvertFromCDM::convert(data->Type().get());
}
	
bool OperatingJurisdiction::hasType() const {
	return data->Type().present();
}
	
OperatingJurisdiction & OperatingJurisdiction::setRoot(const Root & value) {
	data->Root(ConvertToCDM::convert(value));
	return *this;
}

bool OperatingJurisdiction::getRoot(Root & out) const {
	if (data->Root().present()) {
		out = ConvertFromCDM::convert(data->Root().get());
		return true;
	}
	return false;
}

Root OperatingJurisdiction::getRoot() const {
	return ConvertFromCDM::convert(data->Root().get());
}
	
bool OperatingJurisdiction::hasRoot() const {
	return data->Root().present();
}
	
OperatingJurisdiction & OperatingJurisdiction::setExtension(const Extension & value) {
	data->Extension1(ConvertToCDM::convert(value));
	return *this;
}

bool OperatingJurisdiction::getExtension(Extension & out) const {
	if (data->Extension1().present()) {
		out = ConvertFromCDM::convert(data->Extension1().get());
		return true;
	}
	return false;
}

Extension OperatingJurisdiction::getExtension() const {
	return ConvertFromCDM::convert(data->Extension1().get());
}
	
bool OperatingJurisdiction::hasExtension() const {
	return data->Extension1().present();
}
	
OperatingJurisdiction & OperatingJurisdiction::addIdentifierName(const LocalizedText & value) {
	data->IdentifierName().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<LocalizedText> OperatingJurisdiction::getIdentifierNameLists() const {
	std::vector<LocalizedText> result;
	result.reserve(data->IdentifierName().size());
	for (const auto & value: data->IdentifierName()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void OperatingJurisdiction::clearIdentifierNameLists() {
	data->IdentifierName().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

