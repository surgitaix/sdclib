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
 *  Author: besting, buerger, roehser
 */

/**
 * THIS FILE IS GENERATED AUTOMATICALLY! DO NOT MODIFY!
 *
 * YOUR CHANGES WILL BE OVERWRITTEN!
 *
 * USE THE DEFINITION FILES IN THE FOLDER "codegenerator" INSTEAD!
 */

#include "SDCLib/Data/SDC/MDIB/ClinicalInfo.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/CodedValue.h"
#include "SDCLib/Data/SDC/MDIB/LocalizedText.h"
#include "SDCLib/Data/SDC/MDIB/RelatedMeasurement.h"

namespace SDCLib {
namespace Data {
namespace SDC {


ClinicalInfo::ClinicalInfo(
) : data(Defaults::ClinicalInfoInit(
))
{}

ClinicalInfo::operator CDM::ClinicalInfo() const {
	return *data;
}

ClinicalInfo::ClinicalInfo(const CDM::ClinicalInfo & object)
: data(new CDM::ClinicalInfo(object))
{ }

ClinicalInfo::ClinicalInfo(const ClinicalInfo & object)
: data(std::make_shared<CDM::ClinicalInfo>(*object.data))
{ }

void ClinicalInfo::copyFrom(const ClinicalInfo & object) {
	data = std::make_shared<CDM::ClinicalInfo>(*object.data);
}

ClinicalInfo & ClinicalInfo:: operator=(const ClinicalInfo& object) {
	copyFrom(object);
	return *this;
}


ClinicalInfo & ClinicalInfo::setType(const CodedValue & value) {
	data->setType(ConvertToCDM::convert(value));
	return *this;
}

bool ClinicalInfo::getType(CodedValue & out) const {
	if (data->getType().present()) {
		out = ConvertFromCDM::convert(data->getType().get());
		return true;
	}
	return false;
}

CodedValue ClinicalInfo::getType() const {
	return ConvertFromCDM::convert(data->getType().get());
}

bool ClinicalInfo::hasType() const {
	return data->getType().present();
}

ClinicalInfo & ClinicalInfo::setCode(const CodedValue & value) {
	data->setCode(ConvertToCDM::convert(value));
	return *this;
}

bool ClinicalInfo::getCode(CodedValue & out) const {
	if (data->getCode().present()) {
		out = ConvertFromCDM::convert(data->getCode().get());
		return true;
	}
	return false;
}

CodedValue ClinicalInfo::getCode() const {
	return ConvertFromCDM::convert(data->getCode().get());
}

bool ClinicalInfo::hasCode() const {
	return data->getCode().present();
}

ClinicalInfo & ClinicalInfo::setCriticality(const Criticality & value) {
	data->setCriticality(ConvertToCDM::convert(value));
	return *this;
}

bool ClinicalInfo::getCriticality(Criticality & out) const {
	if (data->getCriticality().present()) {
		out = ConvertFromCDM::convert(data->getCriticality().get());
		return true;
	}
	return false;
}

Criticality ClinicalInfo::getCriticality() const {
	return ConvertFromCDM::convert(data->getCriticality().get());
}

bool ClinicalInfo::hasCriticality() const {
	return data->getCriticality().present();
}

ClinicalInfo & ClinicalInfo::addDescription(const LocalizedText & value) {
	data->getDescription().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<LocalizedText> ClinicalInfo::getDescriptionList() const {
	std::vector<LocalizedText> result;
	result.reserve(data->getDescription().size());
	for (const auto & value: data->getDescription()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void ClinicalInfo::clearDescriptionList() {
	data->getDescription().clear();
}

ClinicalInfo & ClinicalInfo::addRelatedMeasurement(const RelatedMeasurement & value) {
	data->getRelatedMeasurement().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<RelatedMeasurement> ClinicalInfo::getRelatedMeasurementList() const {
	std::vector<RelatedMeasurement> result;
	result.reserve(data->getRelatedMeasurement().size());
	for (const auto & value: data->getRelatedMeasurement()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void ClinicalInfo::clearRelatedMeasurementList() {
	data->getRelatedMeasurement().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

