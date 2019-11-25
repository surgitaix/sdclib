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
 *  WorkflowDetail.cpp
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

#include "SDCLib/Data/SDC/MDIB/WorkflowDetail.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/PersonReference.h"
#include "SDCLib/Data/SDC/MDIB/LocationReference.h"
#include "SDCLib/Data/SDC/MDIB/InstanceIdentifier.h"
#include "SDCLib/Data/SDC/MDIB/CodedValue.h"
#include "SDCLib/Data/SDC/MDIB/ClinicalInfo.h"
#include "SDCLib/Data/SDC/MDIB/RequestedOrderDetail.h"
#include "SDCLib/Data/SDC/MDIB/PerformedOrderDetail.h"

namespace SDCLib {
namespace Data {
namespace SDC {


WorkflowDetail::WorkflowDetail(
		PersonReference patient
) : data(Defaults::WorkflowDetailInit(
		patient
)) {}

WorkflowDetail::operator CDM::WorkflowDetail() const {
	return *data;
}

WorkflowDetail::WorkflowDetail(const CDM::WorkflowDetail & object) : data(new CDM::WorkflowDetail(object)) {

}

WorkflowDetail::WorkflowDetail(const WorkflowDetail & object) : data(new CDM::WorkflowDetail(*object.data)) {

}

WorkflowDetail::~WorkflowDetail() {

}

void WorkflowDetail::copyFrom(const WorkflowDetail & object) {
	data = std::shared_ptr<CDM::WorkflowDetail>( new CDM::WorkflowDetail(*object.data));
}

WorkflowDetail & WorkflowDetail:: operator=(const WorkflowDetail & object) {
	copyFrom(object);
	return *this;
}


WorkflowDetail & WorkflowDetail::setPatient(const PersonReference & value) {
	data->setPatient(ConvertToCDM::convert(value));
	return *this;
}


PersonReference WorkflowDetail::getPatient() const {
	return ConvertFromCDM::convert(data->getPatient());
}

WorkflowDetail & WorkflowDetail::setAssignedLocation(const LocationReference & value) {
	data->setAssignedLocation(ConvertToCDM::convert(value));
	return *this;
}

bool WorkflowDetail::getAssignedLocation(LocationReference & out) const {
	if (data->getAssignedLocation().present()) {
		out = ConvertFromCDM::convert(data->getAssignedLocation().get());
		return true;
	}
	return false;
}

LocationReference WorkflowDetail::getAssignedLocation() const {
	return ConvertFromCDM::convert(data->getAssignedLocation().get());
}

bool WorkflowDetail::hasAssignedLocation() const {
	return data->getAssignedLocation().present();
}

WorkflowDetail & WorkflowDetail::setVisitNumber(const InstanceIdentifier & value) {
	data->setVisitNumber(ConvertToCDM::convert(value));
	return *this;
}

bool WorkflowDetail::getVisitNumber(InstanceIdentifier & out) const {
	if (data->getVisitNumber().present()) {
		out = ConvertFromCDM::convert(data->getVisitNumber().get());
		return true;
	}
	return false;
}

InstanceIdentifier WorkflowDetail::getVisitNumber() const {
	return ConvertFromCDM::convert(data->getVisitNumber().get());
}

bool WorkflowDetail::hasVisitNumber() const {
	return data->getVisitNumber().present();
}

WorkflowDetail & WorkflowDetail::setRequestedOrderDetail(const RequestedOrderDetail & value) {
	data->setRequestedOrderDetail(ConvertToCDM::convert(value));
	return *this;
}

bool WorkflowDetail::getRequestedOrderDetail(RequestedOrderDetail & out) const {
	if (data->getRequestedOrderDetail().present()) {
		out = ConvertFromCDM::convert(data->getRequestedOrderDetail().get());
		return true;
	}
	return false;
}

RequestedOrderDetail WorkflowDetail::getRequestedOrderDetail() const {
	return ConvertFromCDM::convert(data->getRequestedOrderDetail().get());
}

bool WorkflowDetail::hasRequestedOrderDetail() const {
	return data->getRequestedOrderDetail().present();
}

WorkflowDetail & WorkflowDetail::setPerformedOrderDetail(const PerformedOrderDetail & value) {
	data->setPerformedOrderDetail(ConvertToCDM::convert(value));
	return *this;
}

bool WorkflowDetail::getPerformedOrderDetail(PerformedOrderDetail & out) const {
	if (data->getPerformedOrderDetail().present()) {
		out = ConvertFromCDM::convert(data->getPerformedOrderDetail().get());
		return true;
	}
	return false;
}

PerformedOrderDetail WorkflowDetail::getPerformedOrderDetail() const {
	return ConvertFromCDM::convert(data->getPerformedOrderDetail().get());
}

bool WorkflowDetail::hasPerformedOrderDetail() const {
	return data->getPerformedOrderDetail().present();
}

WorkflowDetail & WorkflowDetail::addDangerCode(const CodedValue & value) {
	data->getDangerCode().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<CodedValue> WorkflowDetail::getDangerCodeList() const {
	std::vector<CodedValue> result;
	result.reserve(data->getDangerCode().size());
	for (const auto & value: data->getDangerCode()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void WorkflowDetail::clearDangerCodeList() {
	data->getDangerCode().clear();
}

WorkflowDetail & WorkflowDetail::addRelevantClinicalInfo(const ClinicalInfo & value) {
	data->getRelevantClinicalInfo().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<ClinicalInfo> WorkflowDetail::getRelevantClinicalInfoList() const {
	std::vector<ClinicalInfo> result;
	result.reserve(data->getRelevantClinicalInfo().size());
	for (const auto & value: data->getRelevantClinicalInfo()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void WorkflowDetail::clearRelevantClinicalInfoList() {
	data->getRelevantClinicalInfo().clear();
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

