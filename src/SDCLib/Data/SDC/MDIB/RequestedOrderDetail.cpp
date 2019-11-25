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
 *  RequestedOrderDetail.cpp
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

#include "SDCLib/Data/SDC/MDIB/RequestedOrderDetail.h"
#include "SDCLib/Data/SDC/MDIB/ConvertToCDM.h"
#include "SDCLib/Data/SDC/MDIB/ConvertFromCDM.h"
#include "SDCLib/Data/SDC/MDIB/Defaults.h"

#include "DataModel/osdm.hxx"

#include "SDCLib/Data/SDC/MDIB/PersonReference.h"
#include "SDCLib/Data/SDC/MDIB/InstanceIdentifier.h"
#include "SDCLib/Data/SDC/MDIB/PersonParticipation.h"
#include "SDCLib/Data/SDC/MDIB/CodedValue.h"
#include "SDCLib/Data/SDC/MDIB/ImagingProcedure.h"

namespace SDCLib {
namespace Data {
namespace SDC {


RequestedOrderDetail::RequestedOrderDetail(
		InstanceIdentifier placerordernumber
) : data(Defaults::RequestedOrderDetailInit(
		placerordernumber
)) {}

RequestedOrderDetail::operator CDM::RequestedOrderDetail() const {
	return *data;
}

RequestedOrderDetail::RequestedOrderDetail(const CDM::RequestedOrderDetail & object) : data(new CDM::RequestedOrderDetail(object)) {

}

RequestedOrderDetail::RequestedOrderDetail(const RequestedOrderDetail & object) : data(new CDM::RequestedOrderDetail(*object.data)) {

}

RequestedOrderDetail::~RequestedOrderDetail() {

}

void RequestedOrderDetail::copyFrom(const RequestedOrderDetail & object) {
	data = std::shared_ptr<CDM::RequestedOrderDetail>( new CDM::RequestedOrderDetail(*object.data));
}

RequestedOrderDetail & RequestedOrderDetail:: operator=(const RequestedOrderDetail & object) {
	copyFrom(object);
	return *this;
}


RequestedOrderDetail & RequestedOrderDetail::setStart(const xml_schema::DateTime & value) {
	data->setStart(ConvertToCDM::convert(value));
	return *this;
}

bool RequestedOrderDetail::getStart(xml_schema::DateTime & out) const {
	if (data->getStart().present()) {
		out = ConvertFromCDM::convert(data->getStart().get());
		return true;
	}
	return false;
}

xml_schema::DateTime RequestedOrderDetail::getStart() const {
	return ConvertFromCDM::convert(data->getStart().get());
}

bool RequestedOrderDetail::hasStart() const {
	return data->getStart().present();
}

RequestedOrderDetail & RequestedOrderDetail::setEnd(const xml_schema::DateTime & value) {
	data->setEnd(ConvertToCDM::convert(value));
	return *this;
}

bool RequestedOrderDetail::getEnd(xml_schema::DateTime & out) const {
	if (data->getEnd().present()) {
		out = ConvertFromCDM::convert(data->getEnd().get());
		return true;
	}
	return false;
}

xml_schema::DateTime RequestedOrderDetail::getEnd() const {
	return ConvertFromCDM::convert(data->getEnd().get());
}

bool RequestedOrderDetail::hasEnd() const {
	return data->getEnd().present();
}

RequestedOrderDetail & RequestedOrderDetail::addPerformer(const PersonParticipation & value) {
	data->getPerformer().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<PersonParticipation> RequestedOrderDetail::getPerformerList() const {
	std::vector<PersonParticipation> result;
	result.reserve(data->getPerformer().size());
	for (const auto & value: data->getPerformer()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void RequestedOrderDetail::clearPerformerList() {
	data->getPerformer().clear();
}

RequestedOrderDetail & RequestedOrderDetail::addService(const CodedValue & value) {
	data->getService().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<CodedValue> RequestedOrderDetail::getServiceList() const {
	std::vector<CodedValue> result;
	result.reserve(data->getService().size());
	for (const auto & value: data->getService()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void RequestedOrderDetail::clearServiceList() {
	data->getService().clear();
}

RequestedOrderDetail & RequestedOrderDetail::addImagingProcedure(const ImagingProcedure & value) {
	data->getImagingProcedure().push_back(ConvertToCDM::convert(value));
	return *this;
}

std::vector<ImagingProcedure> RequestedOrderDetail::getImagingProcedureList() const {
	std::vector<ImagingProcedure> result;
	result.reserve(data->getImagingProcedure().size());
	for (const auto & value: data->getImagingProcedure()) {
		result.push_back(ConvertFromCDM::convert(value));
	}
	return result;
}

void RequestedOrderDetail::clearImagingProcedureList() {
	data->getImagingProcedure().clear();
}

RequestedOrderDetail & RequestedOrderDetail::setReferringPhysician(const PersonReference & value) {
	data->setReferringPhysician(ConvertToCDM::convert(value));
	return *this;
}

bool RequestedOrderDetail::getReferringPhysician(PersonReference & out) const {
	if (data->getReferringPhysician().present()) {
		out = ConvertFromCDM::convert(data->getReferringPhysician().get());
		return true;
	}
	return false;
}

PersonReference RequestedOrderDetail::getReferringPhysician() const {
	return ConvertFromCDM::convert(data->getReferringPhysician().get());
}

bool RequestedOrderDetail::hasReferringPhysician() const {
	return data->getReferringPhysician().present();
}

RequestedOrderDetail & RequestedOrderDetail::setRequestingPhysician(const PersonReference & value) {
	data->setRequestingPhysician(ConvertToCDM::convert(value));
	return *this;
}

bool RequestedOrderDetail::getRequestingPhysician(PersonReference & out) const {
	if (data->getRequestingPhysician().present()) {
		out = ConvertFromCDM::convert(data->getRequestingPhysician().get());
		return true;
	}
	return false;
}

PersonReference RequestedOrderDetail::getRequestingPhysician() const {
	return ConvertFromCDM::convert(data->getRequestingPhysician().get());
}

bool RequestedOrderDetail::hasRequestingPhysician() const {
	return data->getRequestingPhysician().present();
}

RequestedOrderDetail & RequestedOrderDetail::setPlacerOrderNumber(const InstanceIdentifier & value) {
	data->setPlacerOrderNumber(ConvertToCDM::convert(value));
	return *this;
}


InstanceIdentifier RequestedOrderDetail::getPlacerOrderNumber() const {
	return ConvertFromCDM::convert(data->getPlacerOrderNumber());
}


} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

