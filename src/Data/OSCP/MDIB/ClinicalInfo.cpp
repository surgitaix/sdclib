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
 *  ClinicalInfo.cpp
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

#include "OSCLib/Data/OSCP/MDIB/ClinicalInfo.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/LocalizedText.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

ClinicalInfo::ClinicalInfo() : data(Defaults::ClinicalInfo()) {
}

ClinicalInfo::operator CDM::ClinicalInfo() const {
	return *data;
}

ClinicalInfo::ClinicalInfo(const CDM::ClinicalInfo & object) : data(new CDM::ClinicalInfo(object)) {

}

ClinicalInfo::ClinicalInfo(const ClinicalInfo & object) : data(new CDM::ClinicalInfo(*object.data)) {

}

ClinicalInfo::~ClinicalInfo() {

}

void ClinicalInfo::copyFrom(const ClinicalInfo & object) {
	*data = *object.data;
}

ClinicalInfo & ClinicalInfo:: operator=(const ClinicalInfo & object) {
	copyFrom(object);
	return *this;
}


ClinicalInfo & ClinicalInfo::setType(const CodedValue & value) {
	data->Type(ConvertToCDM::convert(value));
	return *this;
}

bool ClinicalInfo::getType(CodedValue & out) const {
	if (data->Type().present()) {
		out = ConvertFromCDM::convert(data->Type().get());
		return true;
	}
	return false;
}

CodedValue ClinicalInfo::getType() const {
	return ConvertFromCDM::convert(data->Type().get());
}
	
bool ClinicalInfo::hasType() const {
	return data->Type().present();
}
	
ClinicalInfo & ClinicalInfo::addDescription(const LocalizedText & value) {
	data->Description().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<LocalizedText> ClinicalInfo::getDescriptionLists() const {
	std::vector<LocalizedText> result;
	result.reserve(data->Description().size());
	for (const auto & value: data->Description()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void ClinicalInfo::clearDescriptionLists() {
	data->Description().clear();
}

ClinicalInfo & ClinicalInfo::addRelatedMeasurement(const RelatedMeasurement & value) {
	data->RelatedMeasurement().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<RelatedMeasurement> ClinicalInfo::getRelatedMeasurementLists() const {
	std::vector<RelatedMeasurement> result;
	result.reserve(data->RelatedMeasurement().size());
	for (const auto & value: data->RelatedMeasurement()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void ClinicalInfo::clearRelatedMeasurementLists() {
	data->RelatedMeasurement().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

