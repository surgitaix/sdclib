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
 *  PerformedOrderDetail.cpp
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

#include "SDCLib/Data/SDC/MDIB/PerformedOrderDetail.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/InstanceIdentifier.h"
#include "SDCLib/Data/SDC/MDIB/ClinicalInfo.h"
#include "SDCLib/Data/SDC/MDIB/PersonParticipation.h"
#include "SDCLib/Data/SDC/MDIB/CodedValue.h"
#include "SDCLib/Data/SDC/MDIB/ImagingProcedure.h"

namespace SDCLib {
namespace Data {
namespace SDC {


PerformedOrderDetail::PerformedOrderDetail(
) : data(Defaults::PerformedOrderDetailInit(
)) {}

PerformedOrderDetail::operator CDM::PerformedOrderDetail() const {
	return *data;
}

PerformedOrderDetail::PerformedOrderDetail(const CDM::PerformedOrderDetail & object) : data(new CDM::PerformedOrderDetail(object)) {

}

PerformedOrderDetail::PerformedOrderDetail(const PerformedOrderDetail & object) : data(new CDM::PerformedOrderDetail(*object.data)) {

}

PerformedOrderDetail::~PerformedOrderDetail() {

}

void PerformedOrderDetail::copyFrom(const PerformedOrderDetail & object) {
	data = std::shared_ptr<CDM::PerformedOrderDetail>( new CDM::PerformedOrderDetail(*object.data));
}

PerformedOrderDetail & PerformedOrderDetail:: operator=(const PerformedOrderDetail & object) {
	copyFrom(object);
	return *this;
}


PerformedOrderDetail & PerformedOrderDetail::setStart(const xml_schema::DateTime & value) {
	data->setStart(ConvertToCDM::convert(value));
	return *this;
}

bool PerformedOrderDetail::getStart(xml_schema::DateTime & out) const {
	if (data->getStart().present()) {
		out = ConvertFromCDM::convert(data->getStart().get());
		return true;
	}
	return false;
}

xml_schema::DateTime PerformedOrderDetail::getStart() const {
	return ConvertFromCDM::convert(data->getStart().get());
}

bool PerformedOrderDetail::hasStart() const {
	return data->getStart().present();
}

PerformedOrderDetail & PerformedOrderDetail::setEnd(const xml_schema::DateTime & value) {
	data->setEnd(ConvertToCDM::convert(value));
	return *this;
}

bool PerformedOrderDetail::getEnd(xml_schema::DateTime & out) const {
	if (data->getEnd().present()) {
		out = ConvertFromCDM::convert(data->getEnd().get());
		return true;
	}
	return false;
}

xml_schema::DateTime PerformedOrderDetail::getEnd() const {
	return ConvertFromCDM::convert(data->getEnd().get());
}

bool PerformedOrderDetail::hasEnd() const {
	return data->getEnd().present();
}

PerformedOrderDetail & PerformedOrderDetail::addPerformer(const PersonParticipation & value) {
	data->getPerformer().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<PersonParticipation> PerformedOrderDetail::getPerformerList() const {
	std::vector<PersonParticipation> result;
	result.reserve(data->getPerformer().size());
	for (const auto & value: data->getPerformer()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void PerformedOrderDetail::clearPerformerList() {
	data->getPerformer().clear();
}

PerformedOrderDetail & PerformedOrderDetail::addService(const CodedValue & value) {
	data->getService().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<CodedValue> PerformedOrderDetail::getServiceList() const {
	std::vector<CodedValue> result;
	result.reserve(data->getService().size());
	for (const auto & value: data->getService()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void PerformedOrderDetail::clearServiceList() {
	data->getService().clear();
}

PerformedOrderDetail & PerformedOrderDetail::addImagingProcedure(const ImagingProcedure & value) {
	data->getImagingProcedure().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<ImagingProcedure> PerformedOrderDetail::getImagingProcedureList() const {
	std::vector<ImagingProcedure> result;
	result.reserve(data->getImagingProcedure().size());
	for (const auto & value: data->getImagingProcedure()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void PerformedOrderDetail::clearImagingProcedureList() {
	data->getImagingProcedure().clear();
}

PerformedOrderDetail & PerformedOrderDetail::setFillerOrderNumber(const InstanceIdentifier & value) {
	data->setFillerOrderNumber(ConvertToCDM::convert(value));
	return *this;
}

bool PerformedOrderDetail::getFillerOrderNumber(InstanceIdentifier & out) const {
	if (data->getFillerOrderNumber().present()) {
		out = ConvertFromCDM::convert(data->getFillerOrderNumber().get());
		return true;
	}
	return false;
}

InstanceIdentifier PerformedOrderDetail::getFillerOrderNumber() const {
	return ConvertFromCDM::convert(data->getFillerOrderNumber().get());
}

bool PerformedOrderDetail::hasFillerOrderNumber() const {
	return data->getFillerOrderNumber().present();
}

PerformedOrderDetail & PerformedOrderDetail::addResultingClinicalInfo(const ClinicalInfo & value) {
	data->getResultingClinicalInfo().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<ClinicalInfo> PerformedOrderDetail::getResultingClinicalInfoList() const {
	std::vector<ClinicalInfo> result;
	result.reserve(data->getResultingClinicalInfo().size());
	for (const auto & value: data->getResultingClinicalInfo()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void PerformedOrderDetail::clearResultingClinicalInfoList() {
	data->getResultingClinicalInfo().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

