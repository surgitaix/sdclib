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
 *  Author: besting, roehser
 */
 
/**
 * THIS FILE IS GENERATED AUTOMATICALLY! DO NOT MODIFY!
 *
 * YOUR CHANGES WILL BE OVERWRITTEN!
 * 
 * USE THE DEFINITION FILES IN THE FOLDER "codegenerator" INSTEAD!
 */

#include "OSCLib/Data/OSCP/MDIB/WorkflowDetail.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/custom/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/PersonReference.h"
#include "OSCLib/Data/OSCP/MDIB/LocationReference.h"
#include "OSCLib/Data/OSCP/MDIB/InstanceIdentifier.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/ClinicalInfo.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

WorkflowDetail::WorkflowDetail() : data(Defaults::WorkflowDetail()) {
}

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
	*data = *object.data;
}

WorkflowDetail & WorkflowDetail:: operator=(const WorkflowDetail & object) {
	copyFrom(object);
	return *this;
}


WorkflowDetail & WorkflowDetail::setPatient(const PersonReference & value) {
	data->Patient(ConvertToCDM::convert(value));
	return *this;
}


PersonReference WorkflowDetail::getPatient() const {
	return ConvertFromCDM::convert(data->Patient());
}
	
WorkflowDetail & WorkflowDetail::setAssignedLocation(const LocationReference & value) {
	data->AssignedLocation(ConvertToCDM::convert(value));
	return *this;
}

bool WorkflowDetail::getAssignedLocation(LocationReference & out) const {
	if (data->AssignedLocation().present()) {
		out = ConvertFromCDM::convert(data->AssignedLocation().get());
		return true;
	}
	return false;
}

LocationReference WorkflowDetail::getAssignedLocation() const {
	return ConvertFromCDM::convert(data->AssignedLocation().get());
}
	
bool WorkflowDetail::hasAssignedLocation() const {
	return data->AssignedLocation().present();
}
	
WorkflowDetail & WorkflowDetail::setVisitNumber(const InstanceIdentifier & value) {
	data->VisitNumber(ConvertToCDM::convert(value));
	return *this;
}

bool WorkflowDetail::getVisitNumber(InstanceIdentifier & out) const {
	if (data->VisitNumber().present()) {
		out = ConvertFromCDM::convert(data->VisitNumber().get());
		return true;
	}
	return false;
}

InstanceIdentifier WorkflowDetail::getVisitNumber() const {
	return ConvertFromCDM::convert(data->VisitNumber().get());
}
	
bool WorkflowDetail::hasVisitNumber() const {
	return data->VisitNumber().present();
}
	
WorkflowDetail & WorkflowDetail::setRequestedOrderDetail(const RequestedOrderDetail & value) {
	data->RequestedOrderDetail(ConvertToCDM::convert(value));
	return *this;
}

bool WorkflowDetail::getRequestedOrderDetail(RequestedOrderDetail & out) const {
	if (data->RequestedOrderDetail().present()) {
		out = ConvertFromCDM::convert(data->RequestedOrderDetail().get());
		return true;
	}
	return false;
}

RequestedOrderDetail WorkflowDetail::getRequestedOrderDetail() const {
	return ConvertFromCDM::convert(data->RequestedOrderDetail().get());
}
	
bool WorkflowDetail::hasRequestedOrderDetail() const {
	return data->RequestedOrderDetail().present();
}
	
WorkflowDetail & WorkflowDetail::setPerformedOrderDetail(const PerformedOrderDetail & value) {
	data->PerformedOrderDetail(ConvertToCDM::convert(value));
	return *this;
}

bool WorkflowDetail::getPerformedOrderDetail(PerformedOrderDetail & out) const {
	if (data->PerformedOrderDetail().present()) {
		out = ConvertFromCDM::convert(data->PerformedOrderDetail().get());
		return true;
	}
	return false;
}

PerformedOrderDetail WorkflowDetail::getPerformedOrderDetail() const {
	return ConvertFromCDM::convert(data->PerformedOrderDetail().get());
}
	
bool WorkflowDetail::hasPerformedOrderDetail() const {
	return data->PerformedOrderDetail().present();
}
	
WorkflowDetail & WorkflowDetail::addDangerCode(const CodedValue & value) {
	data->DangerCode().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<CodedValue> WorkflowDetail::getDangerCodeLists() const {
	std::vector<CodedValue> result;
	result.reserve(data->DangerCode().size());
	for (const auto & value: data->DangerCode()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void WorkflowDetail::clearDangerCodeLists() {
	data->DangerCode().clear();
}

WorkflowDetail & WorkflowDetail::addRelevantClinicalInfo(const ClinicalInfo & value) {
	data->RelevantClinicalInfo().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<ClinicalInfo> WorkflowDetail::getRelevantClinicalInfoLists() const {
	std::vector<ClinicalInfo> result;
	result.reserve(data->RelevantClinicalInfo().size());
	for (const auto & value: data->RelevantClinicalInfo()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void WorkflowDetail::clearRelevantClinicalInfoLists() {
	data->RelevantClinicalInfo().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

