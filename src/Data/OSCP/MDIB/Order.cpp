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
 *  Order.cpp
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

#include "OSCLib/Data/OSCP/MDIB/Order.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertToCDM.h"
#include "OSCLib/Data/OSCP/MDIB/ConvertFromCDM.h"
#include "OSCLib/Data/OSCP/MDIB/Defaults.h"

#include "osdm.hxx"

#include "OSCLib/Data/OSCP/MDIB/ClinicalInfo.h"
#include "OSCLib/Data/OSCP/MDIB/CodedValue.h"
#include "OSCLib/Data/OSCP/MDIB/ImagingProcedure.h"
#include "OSCLib/Data/OSCP/MDIB/InstanceIdentifier.h"
#include "OSCLib/Data/OSCP/MDIB/OrderDetail.h"
#include "OSCLib/Data/OSCP/MDIB/PersonReference.h"

namespace OSCLib {
namespace Data {
namespace OSCP {

Order::Order() : data(Defaults::Order()) {
}

Order::operator CDM::Order() const {
	return *data;
}

Order::Order(const CDM::Order & object) : data(new CDM::Order(object)) {

}

Order::Order(const Order & object) : data(new CDM::Order(*object.data)) {

}

Order::~Order() {

}

void Order::copyFrom(const Order & object) {
	*data = *object.data;
}

Order & Order:: operator=(const Order & object) {
	copyFrom(object);
	return *this;
}


Order & Order::setVisitNumber(const InstanceIdentifier & value) {
	data->VisitNumber(ConvertToCDM::convert(value));
	return *this;
}

bool Order::getVisitNumber(InstanceIdentifier & out) const {
	if (data->VisitNumber().present()) {
		out = ConvertFromCDM::convert(data->VisitNumber().get());
		return true;
	}
	return false;
}

InstanceIdentifier Order::getVisitNumber() const {
	return ConvertFromCDM::convert(data->VisitNumber().get());
}
	
bool Order::hasVisitNumber() const {
	return data->VisitNumber().present();
}
	
Order & Order::setPlacerOrderNumber(const InstanceIdentifier & value) {
	data->PlacerOrderNumber(ConvertToCDM::convert(value));
	return *this;
}


InstanceIdentifier Order::getPlacerOrderNumber() const {
	return ConvertFromCDM::convert(data->PlacerOrderNumber());
}
	
Order & Order::setFillerOrderNumber(const InstanceIdentifier & value) {
	data->FillerOrderNumber(ConvertToCDM::convert(value));
	return *this;
}

bool Order::getFillerOrderNumber(InstanceIdentifier & out) const {
	if (data->FillerOrderNumber().present()) {
		out = ConvertFromCDM::convert(data->FillerOrderNumber().get());
		return true;
	}
	return false;
}

InstanceIdentifier Order::getFillerOrderNumber() const {
	return ConvertFromCDM::convert(data->FillerOrderNumber().get());
}
	
bool Order::hasFillerOrderNumber() const {
	return data->FillerOrderNumber().present();
}
	
Order & Order::setPatient(const PersonReference & value) {
	data->Patient(ConvertToCDM::convert(value));
	return *this;
}


PersonReference Order::getPatient() const {
	return ConvertFromCDM::convert(data->Patient());
}
	
Order & Order::setReferringPhysician(const PersonReference & value) {
	data->ReferringPhysician(ConvertToCDM::convert(value));
	return *this;
}

bool Order::getReferringPhysician(PersonReference & out) const {
	if (data->ReferringPhysician().present()) {
		out = ConvertFromCDM::convert(data->ReferringPhysician().get());
		return true;
	}
	return false;
}

PersonReference Order::getReferringPhysician() const {
	return ConvertFromCDM::convert(data->ReferringPhysician().get());
}
	
bool Order::hasReferringPhysician() const {
	return data->ReferringPhysician().present();
}
	
Order & Order::setRequestingPhysician(const PersonReference & value) {
	data->RequestingPhysician(ConvertToCDM::convert(value));
	return *this;
}

bool Order::getRequestingPhysician(PersonReference & out) const {
	if (data->RequestingPhysician().present()) {
		out = ConvertFromCDM::convert(data->RequestingPhysician().get());
		return true;
	}
	return false;
}

PersonReference Order::getRequestingPhysician() const {
	return ConvertFromCDM::convert(data->RequestingPhysician().get());
}
	
bool Order::hasRequestingPhysician() const {
	return data->RequestingPhysician().present();
}
	
Order & Order::setRequestedOrderDetail(const OrderDetail & value) {
	data->RequestedOrderDetail(ConvertToCDM::convert(value));
	return *this;
}

bool Order::getRequestedOrderDetail(OrderDetail & out) const {
	if (data->RequestedOrderDetail().present()) {
		out = ConvertFromCDM::convert(data->RequestedOrderDetail().get());
		return true;
	}
	return false;
}

OrderDetail Order::getRequestedOrderDetail() const {
	return ConvertFromCDM::convert(data->RequestedOrderDetail().get());
}
	
bool Order::hasRequestedOrderDetail() const {
	return data->RequestedOrderDetail().present();
}
	
Order & Order::setPerformedOrderDetail(const OrderDetail & value) {
	data->PerformedOrderDetail(ConvertToCDM::convert(value));
	return *this;
}

bool Order::getPerformedOrderDetail(OrderDetail & out) const {
	if (data->PerformedOrderDetail().present()) {
		out = ConvertFromCDM::convert(data->PerformedOrderDetail().get());
		return true;
	}
	return false;
}

OrderDetail Order::getPerformedOrderDetail() const {
	return ConvertFromCDM::convert(data->PerformedOrderDetail().get());
}
	
bool Order::hasPerformedOrderDetail() const {
	return data->PerformedOrderDetail().present();
}
	
Order & Order::addReason(const ClinicalInfo & value) {
	data->Reason().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<ClinicalInfo> Order::getReasons() const {
	std::vector<ClinicalInfo> result;
	result.reserve(data->Reason().size());
	for (const auto & value: data->Reason()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void Order::clearReasons() {
	data->Reason().clear();
}

Order & Order::addDangerCode(const CodedValue & value) {
	data->DangerCode().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<CodedValue> Order::getDangerCodes() const {
	std::vector<CodedValue> result;
	result.reserve(data->DangerCode().size());
	for (const auto & value: data->DangerCode()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void Order::clearDangerCodes() {
	data->DangerCode().clear();
}

Order & Order::addRelevantClinicalInfo(const ClinicalInfo & value) {
	data->RelevantClinicalInfo().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<ClinicalInfo> Order::getRelevantClinicalInfos() const {
	std::vector<ClinicalInfo> result;
	result.reserve(data->RelevantClinicalInfo().size());
	for (const auto & value: data->RelevantClinicalInfo()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void Order::clearRelevantClinicalInfos() {
	data->RelevantClinicalInfo().clear();
}

Order & Order::addImagingProcedure(const ImagingProcedure & value) {
	data->ImagingProcedure().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<ImagingProcedure> Order::getImagingProcedures() const {
	std::vector<ImagingProcedure> result;
	result.reserve(data->ImagingProcedure().size());
	for (const auto & value: data->ImagingProcedure()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void Order::clearImagingProcedures() {
	data->ImagingProcedure().clear();
}


} /* namespace OSCP */
} /* namespace Data */
} /* namespace OSCLib */

